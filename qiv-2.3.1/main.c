/*
退出是qiv_exit(0);
显示某张图片是 qiv_load_image(&main_img)
给好全局变量 image_idx
预设好 image_names[N]数组, 按照01,02,03顺序就是他里面的顺序
char		**image_names = NULL;  Filenames of the images 
int		image_idx = 0;  Index of current image displayed. 0 = 1st image 
循环等待部分

  Module       : main.c
  Purpose      : GDK/Imlib Quick Image Viewer (qiv)
  More         : see qiv README
  Homepage     : http://qiv.spiegl.de/
  Original     : http://www.klografx.net/qiv/
  Policy       : GNU GPL
*/

#include <gtk-2.0/gdk/gdkx.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef HAVE_MAGIC
#include <magic.h>
#endif

#include "qiv.h"
#include "main.h"

qiv_image main_img;
qiv_mgl   magnify_img; /* [lc] */
int fd; //rs232 port rw handle
int timeout = 0; //time out for if no feedback from 

static int check_extension(const char *);
static void qiv_signal_usr1();
static void qiv_signal_usr2();
static gboolean qiv_handle_timer(gpointer);
static void qiv_timer_restart(gpointer);

#ifdef HAVE_MAGIC
static int check_magic(magic_t cookie, const char *name);
#endif


int
set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf ("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf ("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void
set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf ("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf ("error %d setting term attributes", errno);
}

/*
...
char *portname = "/dev/ttyUSB0"
 ...
int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
if (fd < 0)
{
        error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
        return;
}

set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
set_blocking (fd, 0);                // set no blocking

write (fd, "hello!\n", 7);           // send 7 character greeting

usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus
                                     // receive 25:  approx 100 uS per char transmit
char buf [100];
int n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read
*/

int init232()
{
char *portname = "/dev/ttyUSB1";

fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
if (fd < 0)
{
        printf ("error %d opening %s: %s \n", errno, portname, strerror (errno));
        return(0);
}

set_interface_attribs (fd, B19200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
set_blocking (fd, 0);                // set no blocking
return(1);
}

unsigned char read232() 
// will send back status of reading:bit0,ie 1, is has 55 feedback, bit1, ie 2, is switching done
{
char buf [100];
int n,i;
unsigned char return_value=0;

n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read, n is number of byte read
printf("read: "); for(i=0;i<n;i++) printf("%d ", (unsigned int)buf[i]); printf("\n");

for (i=0;i<n;i++)
{
	if ((buf[i]!=55) && (buf[i]>10)) return_value |=2; // no exam 88 in case 232 wrong sending.
	if (buf[i]==55) return_value |=1;
}
return(return_value);
}

void send232(unsigned char char2send)  // The rs232 sending
{
unsigned char sending[1];

sending[0]=char2send;
printf("%d \n",char2send);
write (fd, sending, 1); 
}

int main(int argc, char **argv)
{
  struct timeval tv;
  int i;

  // [as] workaround for problem with X composite extension
  // is this still needed with imlib2 ??
  putenv("XLIB_SKIP_ARGB_VISUALS=1");

/*
  // [as] thinks that this is not portable enough
  // [lc]
  // I use a virtual screen of 1600x1200, and the resolution is 1024x768,
  // so I changed how screen_[x,y] is obtained; it seems that gtk 1.2
  // cannot give the geometry of viewport, so I borrowed from the source of
  // xvidtune the code for calling XF86VidModeGetModeLine, this requires
  // the linking option -lXxf86vm.
  XF86VidModeModeLine modeline;
  int dot_clock;
*/

  /* Randomize seed for 'true' random */
  gettimeofday(&tv,NULL);
  srand(tv.tv_usec*1000000+tv.tv_sec);

// Init the rs232 before everything, if no 232 connected, exit.
  if(init232()==0) exit(1); else printf("232 init success.\n");


  /* Initialize GDK */

  gdk_init(&argc,&argv);

  /* Set up our options, image list, etc */
  strncpy(select_dir, SELECT_DIR, sizeof select_dir);
  reset_mod(&main_img);

  options_read(argc, argv, &main_img);

#ifdef SUPPORT_LCMS
  /* read profiles if provided */
  if (cms_transform) 
  {
    if (source_profile) {
      h_source_profile = cmsOpenProfileFromFile(source_profile, "r");
    } else {
      h_source_profile = cmsCreate_sRGBProfile();
    }

    if (h_source_profile == NULL)
    {
      g_print("qiv: cannot create source color profile.\n");
      usage(argv[0],1);
    }
      
    if (display_profile) {
      h_display_profile = cmsOpenProfileFromFile(display_profile, "r");
    } else {
      h_display_profile = cmsCreate_sRGBProfile();
    }
    if (h_display_profile == NULL)
    {
      g_print("qiv: cannot create display color profile.\n");
      usage(argv[0],1);
    }

  }
  /* TYPE_BGRA_8 or TYPE_ARGB_8 depending on endianess */
  h_cms_transform = cmsCreateTransform(h_source_profile,
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
				       TYPE_BGRA_8,
				       h_display_profile,
				       TYPE_BGRA_8,
#else
				       TYPE_ARGB_8,
				       h_display_profile,
				       TYPE_ARGB_8,
#endif
				       INTENT_PERCEPTUAL, 0);
#endif

  /* Load things from GDK/Imlib */

  qiv_main_loop = g_main_new(TRUE);
  cmap = gdk_colormap_get_system();
  screen_x = gdk_screen_width();
  screen_y = gdk_screen_height();

  screen  = gdk_screen_get_default();
  num_monitors = gdk_screen_get_n_monitors(screen);
  monitor = malloc( num_monitors * sizeof(GdkRectangle));
  for(i=0; i< num_monitors ; i++)
  {
      gdk_screen_get_monitor_geometry(screen, i, &monitor[i]);
  }
  
  if(user_screen < num_monitors)
  {
    main_img.mon_id = user_screen;
  }

 /* statusbar with pango */
  layout = pango_layout_new(gdk_pango_context_get()); 
  fontdesc = pango_font_description_from_string (STATUSBAR_FONT);

  /* set fontsize to 8 if no fontsize is given */
  if(!pango_font_description_get_size(fontdesc))
  {
    pango_font_description_set_size(fontdesc,  PANGO_SCALE * STATUSBAR_FS);
  }
  metrics = pango_context_get_metrics (gdk_pango_context_get(), fontdesc, NULL);
  pango_layout_set_font_description (layout, fontdesc); 

  max_rand_num = images;

  if (!images) { /* No images to display */
    g_print("qiv: cannot load any images.\n");
    usage(argv[0],1);
  }

  /* get colors */

  color_alloc(STATUSBAR_BG, &text_bg);
  color_alloc(ERROR_BG, &error_bg);
  color_alloc(image_bg_spec, &image_bg);

  /* Display first image first, except in random mode */

  if (random_order)
    next_image(0);

  //disabled because 'params' is never used, see above
  //if (to_root || to_root_t || to_root_s) {
  //  params.flags |= PARAMS_VISUALID;
  //  (GdkVisual*)params.visualid = gdk_window_get_visual(GDK_ROOT_PARENT());
  //}

  /* Setup callbacks */

  gdk_event_handler_set(qiv_handle_event, &main_img, NULL);
  qiv_timer_restart(NULL);

  /* And signal catchers */

  signal(SIGTERM, finish);
  signal(SIGINT, finish);
  signal(SIGUSR1, qiv_signal_usr1);
  signal(SIGUSR2, qiv_signal_usr2);

  /* check for DPMS capability and disable it if slideshow
     was started from command options */
  dpms_check();
  if(slide){
    dpms_disable();
  }


  /* Load & display the first image */

  qiv_load_image(&main_img);

  if(watch_file){
    g_idle_add (qiv_watch_file, &main_img);
  }


  g_main_run(qiv_main_loop); /* will never return */
  return 0;
}


void qiv_exit(int code)
{
  if (cmap) gdk_colormap_unref(cmap);
  destroy_image(&main_img);
  dpms_enable();

  pango_font_description_free (fontdesc);
  g_object_unref (layout);
  pango_font_metrics_unref(metrics);

  g_main_destroy(qiv_main_loop);
  finish(SIGTERM);        /* deprecated, subject to change */
}


/*
 * functions for handling signals
 */

static void qiv_signal_usr1()
{
  next_image(1);
  qiv_load_image(&main_img);
}

static void qiv_signal_usr2()
{
  next_image(-1);
  qiv_load_image(&main_img);
}


/*
 * Slideshow timer function
 *
 * If this function returns false, the timer is destroyed
 * and qiv_timer_restart() is automatically called, which
 * then starts the timer again. Thus images which takes some
 * time to load will still be displayed for "delay" seconds.
 */

static gboolean qiv_handle_timer(gpointer data)
{
  /*if (*(int *)data || slide) {
    next_image(0);
    // disable screensaver during slideshow 
    XResetScreenSaver(GDK_DISPLAY());
    qiv_load_image(&main_img);
  }*/
	unsigned char n=0;
	
  send232(55);
  sleep(0.001); //wait 1ms
  n = read232();
  if (n==0) timeout++; else timeout =0; //if there is no feedback from 232 start timeout.
  if (timeout ==3) exit(1); //no 232 feedback for 300ms, exit program.
  return FALSE;
}


/*
 *    Slideshow timer (re)start function
 */

static void qiv_timer_restart(gpointer dummy) //循环调用，把给串口送定时ping和检测串口回ping放在这里
{
  g_timeout_add_full(G_PRIORITY_DEFAULT_IDLE, 100,
                     qiv_handle_timer, &slide,
                     qiv_timer_restart);
}

/* Filter images by extension */

void filter_images(int *images, char **image_names)
{
  int i = 0;
#ifdef HAVE_MAGIC
  magic_t cookie;

  cookie = magic_open(MAGIC_NONE);
  magic_load(cookie,NULL);
#endif

  while(i < *images) {
    if (check_extension(image_names[i])
#ifdef HAVE_MAGIC
            || check_magic(cookie, image_names[i])
#endif
       ) {
      i++;
    } else {
      int j = i;
      if (j < *images-1)
          image_idx--;
      while(j < *images-1) {
        image_names[j] = image_names[j+1];
        ++j;
      }
      --(*images);
    }
  }
#ifdef HAVE_MAGIC
  magic_close(cookie);
#endif
  if (image_idx < 0)
    image_idx = 0;
}

static int check_extension(const char *name)
{
  char *extn = strrchr(name, '.');
  int i;

  if (extn)
    for (i=0; image_extensions[i]; i++)
      if (strcasecmp(extn, image_extensions[i]) == 0)
        return 1;

  return 0;
}

#ifdef HAVE_MAGIC
static int check_magic(magic_t cookie, const char *name)
{
  const char *description=NULL;
  int i;
  int ret=0;

  description = magic_file(cookie, name);
  if(description)
  {
    for(i=0; image_magic[i]; i++ )
      if (strncasecmp(description, image_magic[i], strlen(image_magic[i])) == 0)
      {
        ret = 1;
        break;
      }
  }
  return ret;
}
#endif
