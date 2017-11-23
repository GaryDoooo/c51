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

int fd; //rs232 port rw handle
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

int init232()
{
char *portname = "/dev/ttyUSB0";

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
unsigned char buf [100];
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
  unsigned char input;

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

  while(1){
  printf("Input a number: ");
  scanf("%d",&i);
  input=i;
  printf("will send: %d\n",input);
  send232(input);
  sleep(0.001);
  read232();
  }
}
