/*  定义按键输入，检测按键输入并做反应。
留下q和esc是退出，空格下一张，backspace上一张。
  Module       : event.c
  Purpose      : Handle GDK events
  More         : see qiv README
  Policy       : GNU GPL
  Homepage     : http://qiv.spiegl.de/
  Original     : http://www.klografx.net/qiv/
*/

#include <stdio.h>
#include <string.h>
#include <gdk/gdkx.h>
#include <gdk/gdkkeysyms.h>
#include <ctype.h>
#include "qiv.h"

#define STEP 3 //When using KP arrow, number of step for seeing all the image.

static int    jumping;
static int    extcommand; // [lc]
static char    jcmd[100];
static int    jidx;
static int    cursor_timeout;
static gboolean displaying_textwindow = FALSE;

static void qiv_enable_mouse_events(qiv_image *q)
{
  gdk_window_set_events(q->win, gdk_window_get_events(q->win) &
                        ~GDK_POINTER_MOTION_HINT_MASK);
}

static void qiv_disable_mouse_events(qiv_image *q)
{
  gdk_window_set_events(q->win, gdk_window_get_events(q->win) |
                        GDK_POINTER_MOTION_HINT_MASK);
}

static gboolean qiv_cursor_timeout(gpointer data)
{
  qiv_image *q = data;

  cursor_timeout = 0;
  hide_cursor(q);
  qiv_enable_mouse_events(q);
  return FALSE;
}

static void qiv_set_cursor_timeout(qiv_image *q)
{
  if (!cursor_timeout)
    cursor_timeout = g_timeout_add(1000, qiv_cursor_timeout, q);
  qiv_disable_mouse_events(q);
}

static void qiv_cancel_cursor_timeout(qiv_image *q)
{
  hide_cursor(q);
  if (cursor_timeout) {
    g_source_remove(cursor_timeout);
    cursor_timeout = 0;
  }
}

static void qiv_drag_image(qiv_image *q, int move_to_x, int move_to_y,
                           const char *action_msg, const char *stalled_msg)
{
  int moved = 0;

  if (move_to_x < 0 - q->win_w)
    move_to_x = 0 - q->win_w;
  else if (move_to_x > monitor[q->mon_id].width)
    move_to_x = monitor[q->mon_id].width;
  if (q->win_x != move_to_x) {
    q->win_x = move_to_x;
    moved = 1;
  }

  if (move_to_y < 0 - q->win_h)
    move_to_y = 0 - q->win_h;
  else if (move_to_y > monitor[q->mon_id].height)
    move_to_y = monitor[q->mon_id].height;
  if (q->win_y != move_to_y) {
    q->win_y = move_to_y;
    moved = 1;
  }

  if (moved || !stalled_msg)
    snprintf(infotext, sizeof infotext, "%s", action_msg);
  else
    snprintf(infotext, sizeof infotext, "%s", stalled_msg);
  update_image(q, MOVED);
}

void qiv_display_text_window(qiv_image *q, const char *infotextdisplay,
                             const char *strs[], const char *continue_msg)
{
  int temp, text_w = 0, text_h, i, maxlines;
  int x, y, width, height, text_left;

  int ascent;
  int descent;

  ascent  = PANGO_PIXELS(pango_font_metrics_get_ascent(metrics));
  descent = PANGO_PIXELS(pango_font_metrics_get_descent(metrics));

  if (fullscreen) {
    x = y = 0;
    width = monitor[q->mon_id].width;
    height = monitor[q->mon_id].height;
  } else {
    x = y = 0;
    width = q->win_w;
    height = q->win_h;
  }

  /* Calculate maximum number of lines to display */
  if (ascent + descent > 0)
    maxlines = height / (ascent + descent) - 3;
  else
    maxlines = 60;

  pango_layout_set_text(layout, continue_msg, -1);
  pango_layout_get_pixel_size (layout, &text_w, NULL);
  for (i = 0; strs[i] && i < maxlines; i++) {
    pango_layout_set_text(layout, strs[i], -1);
    pango_layout_get_pixel_size (layout, &temp, NULL);
    if (text_w < temp) text_w = temp;
  }

  text_h = (i + 2) * ( ascent + descent );

  snprintf(infotext, sizeof infotext, "%s", infotextdisplay);
  update_image(q, MIN_REDRAW);

  text_left = width/2 - text_w/2 - 4;
  if (text_left < 2)  text_left = 2;            /* if window/screen is smaller than text */

  gdk_draw_rectangle(q->win, q->bg_gc, y,
                     x + text_left,
                     y + height/2 - text_h/2 - 4,
                     x + text_w + 7, text_h + 7);
  gdk_draw_rectangle(q->win, q->status_gc, y + 1,
                     x + text_left + 1,
                     y + height/2 - text_h/2 - 3,
                     x + text_w + 6, text_h + 6);
  for (i = 0; strs[i] && i < maxlines; i++) {
       pango_layout_set_text(layout, strs[i], -1);
       gdk_draw_layout (q->win, q->text_gc, x + text_left + 4, y + height/2 - text_h/2  +
                  i * (ascent + descent), layout);
  }

  /* Display Push Any Key... message */
  pango_layout_set_text(layout, continue_msg, -1);
  pango_layout_get_pixel_size (layout, &temp, NULL);
  gdk_draw_layout (q->win, q->text_gc, 
                   x + width/2 - temp/2,
                   y + height/2 - text_h/2 - descent + (i+1) * (ascent + descent),
                   layout);
  displaying_textwindow = TRUE;

  /* print also on console */
  if (0) {
    int i;
    for (i = 0; strs[i] != NULL; i++) {
      printf("%s\n", strs[i]);
    }
  }
}

void qiv_handle_event(GdkEvent *ev, gpointer data)
{
  gboolean exit_slideshow = FALSE;
  qiv_image *q = data;
  Window xwindow;
  int move_step;
  const char *mess[2]={ jcmd, NULL};

  // get windows position if not in fullscreen mode
  // (because the user might have moved the window our since last redraw)
  if (!fullscreen) {
    gdk_window_get_position(q->win, &q->win_x, &q->win_y);
//    g_print("position   : q->win_x = %d, q->win_y = %d, q->win_w = %d, mon = %d\n", q->win_x, q->win_y, q->win_w,q->mon_id);
  }
  q->mon_id = gdk_screen_get_monitor_at_window(screen, q->win);

  switch(ev->type) {
    case GDK_DELETE:
      qiv_exit(0);  //这个就是退出程序。
      break;

    case GDK_EXPOSE:
      if (!q->exposed) {
        q->exposed = 1;
        qiv_set_cursor_timeout(q);
      }
      if(fullscreen) {
        if(center) center_image(q);
        update_image(q, FULL_REDRAW);
      }
      break;

    case GDK_LEAVE_NOTIFY:
      if (magnify && !fullscreen) {
        gdk_window_hide(magnify_img.win);
      }
      gdk_pointer_ungrab(CurrentTime);
      gdk_keyboard_ungrab(CurrentTime);
      break;

    case GDK_ENTER_NOTIFY:
      if(do_grab || (fullscreen && !disable_grab))
      {
        gdk_keyboard_grab(q->win, FALSE, CurrentTime);
        gdk_pointer_grab(q->win, FALSE,
            GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_ENTER_NOTIFY_MASK |
            GDK_LEAVE_NOTIFY_MASK | GDK_POINTER_MOTION_MASK, NULL, NULL, CurrentTime);
      }

    case GDK_CONFIGURE:
      if (magnify && !fullscreen) {
        gdk_window_get_root_origin(q->win,
                                   &magnify_img.frame_x, &magnify_img.frame_y);
        // printf("GDK_CONFIGURE get_root_origin  %d %d\n",
        //        magnify_img.frame_x, magnify_img.frame_y);
      }
      // gdk_draw_rectangle(q->win, q->status_gc, 1, 10, 10, 50, 50);
      if (statusbar_window && !fullscreen) {
#ifdef DEBUG
        g_print("*** print statusbar at (%d, %d)\n", MAX(2,q->win_w-q->text_w-10), MAX(2,q->win_h-q->text_h-10));
#endif
        // printf(">>> statusbar_w %d %d %d %d\n",
        //        MAX(2,q->win_w-text_w-10), MAX(2,q->win_h-text_h-10), text_w+5, text_h+5);

        gdk_draw_rectangle(q->win, q->bg_gc, 0,
                           MAX(2,q->win_w-q->text_w-10), MAX(2,q->win_h-q->text_h-10),
                           q->text_w+5, q->text_h+5);
        gdk_draw_rectangle(q->win, q->status_gc, 1,
                           MAX(3,q->win_w-q->text_w-9), MAX(3,q->win_h-q->text_h-9),
                           q->text_w+4, q->text_h+4);

        pango_layout_set_text(layout, q->win_title, -1);
        pango_layout_get_pixel_size (layout, &(q->text_w), &(q->text_h));
        gdk_draw_layout (q->win, q->text_gc, MAX(5,q->win_w-q->text_w-7),  MAX(5,q->win_h-7-q->text_h), layout);
      }

      break;

    case GDK_BUTTON_PRESS:
      jumping=0;              /* abort jump mode if a button is pressed */
      qiv_cancel_cursor_timeout(q);
      if (fullscreen && ev->button.button == 1) {
        q->drag = 1;
//        q->drag_start_x = ev->button.x;
//        q->drag_start_y = ev->button.y;
        q->drag_start_x = ev->button.x_root;
        q->drag_start_y = ev->button.y_root;
        q->drag_win_x = q->win_x;
        q->drag_win_y = q->win_y;
        qiv_enable_mouse_events(q);
      }
      break;

    case GDK_MOTION_NOTIFY:
      if (q->drag) {
        int move_x, move_y;
        move_x = (int)(ev->button.x_root - q->drag_start_x);
        move_y = (int)(ev->button.y_root - q->drag_start_y);
        if (q->drag == 1 && (ABS(move_x) > 3 || ABS(move_y) > 3)) {
          /* distinguish from simple mouse click... */
          q->drag = 2;
          show_cursor(q);
        }
        if (q->drag > 1 && (q->win_x != q->drag_win_x + move_x ||
                            q->win_y != q->drag_win_y + move_y)) {
          GdkEvent *e;
          qiv_disable_mouse_events(q);
          qiv_drag_image(q, q->drag_win_x + move_x, q->drag_win_y + move_y, "(Drag)", NULL);
          /* el cheapo mouse motion compression */
          while (gdk_events_pending()) {
            /* [tw] why check if "e" not NULL? */
            if((e = gdk_event_get())) {
              if (e->type == GDK_BUTTON_RELEASE) {
                gdk_event_put(e);
                gdk_event_free(e);
                break;
              }
              gdk_event_free(e);
            }
          }
          qiv_enable_mouse_events(q);
        }
      }
      else {
        show_cursor(q);
        // printf(" motion_notify magnify %d  is_hint %d\n", magnify, ev->motion.is_hint);
        if (magnify && !fullscreen) {
          gint xcur, ycur;
          if (ev->motion.is_hint) {
            gdk_window_get_pointer(q->win, &xcur, &ycur, NULL);
            update_magnify(q, &magnify_img,REDRAW, xcur, ycur); // [lc]
          }
          // update_magnify(q, &magnify_img,REDRAW, ev->motion.x,  ev->motion.y);
        } else {
          qiv_set_cursor_timeout(q);
        }
      }
      break;

    /* Use release instead of press (Fixes bug with junk being sent
     * to underlying xterm window on exit) */
    case GDK_BUTTON_RELEASE:
      exit_slideshow = TRUE;
      

    case GDK_KEY_PRESS: //这里是检测按键输入的地方。

      exit_slideshow = TRUE;    /* Abort slideshow on any key by default */
      qiv_cancel_cursor_timeout(q);
   #ifdef DEBUG
      g_print("*** key:\n");    /* display key-codes */
      g_print("\tstring: %s\n",ev->key.string);
      g_print("\tkeyval: %d\n",ev->key.keyval);
   #endif

      if (displaying_textwindow && !extcommand ) { // [lc]
        /* Hide the text window if it is showing */
        displaying_textwindow = FALSE;
        if(fullscreen)
        {
          update_image(q, FULL_REDRAW);
        }
        else
        {
          update_image(q, MIN_REDRAW);
        }

        break;
      }

      if (jumping || extcommand) {  // [lc] todo: Backspace,
        if(ev->key.keyval == GDK_KEY_Escape) {
          extcommand = 0;
          jidx = 0;
          displaying_textwindow = FALSE;
          update_image(q, FULL_REDRAW);
          break;
        }
        if(ev->key.keyval == GDK_KEY_BackSpace) {
          jidx--;
          jcmd[jidx]='\0';
          qiv_display_text_window(q, "(Sending Command)", mess,
                                  "Press <Return> to send, <Esc> to abort"); // [lc]
          break;
        }
        if((ev->key.keyval == GDK_KEY_Return) ||
           (ev->key.keyval == GDK_KEY_KP_Enter) ||
           (jidx == 99)) {     /* 99 digits already typed */
          jcmd[jidx] = '\0';
          if (jumping) {
            jump2image(jcmd);
          qiv_load_image(q);
          jumping=0;
        }
          else {      // extcommand=1
            int numlines = 0;
            const char **lines;

            extcommand=0;
            /* Hide the text window if it is showing */
            displaying_textwindow = FALSE;
            update_image(q, MIN_REDRAW);
            run_command(q, jcmd, image_names[image_idx], &numlines, &lines);
            if (lines && numlines)
              qiv_display_text_window(q, "(Command output)", lines, "Push any key...");
          }
        }
        /* else record keystroke if not null */
        else if(ev->key.string && *(ev->key.string) != '\0') {
          jcmd[jidx++]=*(ev->key.string);
          jcmd[jidx] = '\0';
          if (extcommand)
            qiv_display_text_window(q, "(Sending Command)", mess,
                                    "Press <Return> to send, <Esc> to abort"); // [lc]
        }
      } else {
        guint keyval = ev->key.keyval;
        if(vikeys) {
               if (keyval == 'h') keyval = GDK_Left;
          else if (keyval == 'j') keyval = GDK_Down;
          else if (keyval == 'k') keyval = GDK_Up;
          else if (keyval == 'l') keyval = GDK_Right;
          else
            switch (keyval) {
              case 'H':
              case 'J':
              case 'K':
              case 'L':
                keyval = tolower(keyval);
                break;
            }
        }
        switch (keyval) {

          case GDK_KEY_Escape:  //保留，退出程序
          case 'q':
            qiv_exit(0);
            break;

          case ' ':  //保留，空格下一张
          next_image:
            snprintf(infotext, sizeof infotext, "(Next picture)");
            next_image(1);
            qiv_load_image(q);
            if(magnify && !fullscreen) {
              gdk_window_hide(magnify_img.win); // [lc]
//              gdk_flush();
//              gdk_window_get_root_origin(q->win,
//                                         &magnify_img.frame_x, &magnify_img.frame_y);
//              printf(">>> frame %d %d\n", magnify_img.frame_x, magnify_img.frame_y);
//              setup_magnify(q, &magnify_img);
            }
            break;

         case GDK_KEY_BackSpace:  //保留，上一张
          previous_image:
            snprintf(infotext, sizeof infotext, "(Previous picture)");
            next_image(-1);
            if(magnify && !fullscreen)    gdk_window_hide(magnify_img.win); // [lc]
            qiv_load_image(q);
            break;

          default:
            exit_slideshow = FALSE;
            break;
        }
      }
    default:
      break;
  }
  if (exit_slideshow) {
    slide=0;
    dpms_enable();
  }
}
