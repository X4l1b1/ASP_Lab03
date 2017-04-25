/* ----------------------------------------------------------------------
  Institut ReDS - HEIG-VD Yverdon-les-Bains
 ------------------------------------------------------------------------

 Auteur : Evangelina LOLIVIER-EXLER
 Email  : evangelina.lolivier-exler@heig-vd.ch
 Date   : 17/09/2008
 Modified: 24/05/2012 REPTAR board adaptation
 Description : LCD toolbox header
 -----------------------------------------------------------------------
*/

#ifndef LCD_TOOLBOX_H_
#define LCD_TOOLBOX_H_

  #include "stddefs.h"


  // globals to keep track of foreground, background colors and x,y position
  extern uchar lcd_color_depth;		// 16 bits per pixel
  extern uchar lcd_bg_color;		// 0 to 15, used as lookup into VGA color table
  extern uchar lcd_fg_color;		// 0 to 15, used as lookup into VGA color table


  extern void udelay(int delay);
  extern void lcd_on();
  extern void lcd_off();
  extern void clear_screen();
  extern ulong get_pixel_add (ulong X, ulong Y);
  extern void fb_set_pixel(ulong X, ulong Y, uchar color);
  extern void fb_print_char(uchar cchar, ulong x, ulong y, uchar color);
  extern void fb_print_string(uchar *pcbuffer, ulong x, ulong y, uchar color);

  //others
  extern void fb_draw_line(int x0, int y0, int x1, int y1, uchar color);
  void fb_draw_frame(int x0, int y0, int x1, int y1, uchar color);
 


#endif /* LCD_TOOLBOX_H_ */
