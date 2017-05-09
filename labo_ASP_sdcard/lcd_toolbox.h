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

#define FONT_WIDTH	8
#define FONT_HEIGHT 16


  // globals to keep track of foreground, background colors and x,y position
  extern uchar lcd_color_depth;		// 16 bits per pixel
  extern uchar lcd_bg_color;		// 0 to 15, used as lookup into VGA color table
  extern uchar lcd_fg_color;		// 0 to 15, used as lookup into VGA color table

  extern ulong line_nb;
  extern ulong current_y;
  extern uchar lcd_line[];


  extern void udelay(int delay);
  extern void lcd_on();
  extern void lcd_off();
  extern void clear_screen();
  extern ulong get_pixel_add (ulong X, ulong Y);
  extern void fb_set_pixel(ulong X, ulong Y, uchar color);
  extern void fb_print_char(uchar cchar, ulong x, ulong y, uchar color);
  extern ulong fb_print_string(uchar *pcbuffer, ulong x, ulong y, uchar color);

  //application game
  extern void fill_frame(int x0, int y0, int x1, int y1, int color);
  extern void fb_draw_line(int x0, int y0, int x1, int y1, uchar color);
  void fb_draw_frame(int x0, int y0, int x1, int y1, uchar color);
  extern ulong get_current_y();
  extern void clear_line_nb(ulong line_nb);
  //others
  extern void fb_clear_line(ulong line_nb);
  extern void fill_lcd_line(uchar c);
  extern void fb_print_buffer(uint line_nb, int bp, uchar *buff_ptr);
 


#endif /* LCD_TOOLBOX_H_ */
