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

/**
 * FILE: lcd_toolbox.h
 * 
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-14
 */

#ifndef LCD_TOOLBOX_H_
#define LCD_TOOLBOX_H_

#include "stddefs.h"

#define LCD_CHAR_PER_LINE 100

/* LCD types definition */
typedef char* LCDString;
typedef unsigned char LCDLine; 
typedef int LCDAxis;
typedef enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    PURPLE,
    YELLOW,
    GREY,
    WHITE,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_PURPLE,
    BRIGHT_YELLOW,
    BRIGHT_WHITE,
} LCDColor;

typedef struct
{
    LCDAxis x, y;
} LCDPoint;

typedef struct
{
    LCDPoint a, b;
} LCDRectangle;

typedef struct
{
    LCDString title;
    LCDRectangle position;
    LCDColor bgcolor,
             fgcolor,
             border;
} LCDWindow;

// globals to keep track of foreground, background colors and x,y position
extern uchar lcd_color_depth; // 16 bits per pixel
extern uchar lcd_bg_color;    // 0 to 15, used as lookup into VGA color table
extern uchar lcd_fg_color;    // 0 to 15, used as lookup into VGA color table

extern void  udelay(int delay);
extern void  lcd_on();
extern void  lcd_off();
extern void  clear_screen    ();
extern ulong get_pixel_add   (LCDAxis x, LCDAxis y);
extern void  fb_set_pixel    (LCDAxis x, LCDAxis y, LCDColor color);
extern void  fb_print_char   (char cchar, LCDAxis x, LCDAxis y, LCDColor color);
extern void  fb_print_string (const char *pcbuffer, LCDAxis x, LCDAxis y, LCDColor color);

//others
/**
 * Trace horizontal line of given color on LCD.
 * 
 * @param row    [in] row number on LCD
 * @param begin  [in] first pixel number in row
 * @param end    [in] last  pixel number in row (excluded)
 * @param color  [in] color index in table <code>vga_lookup</code>
 */
void fb_draw_hline (LCDAxis row, LCDAxis begin, LCDAxis end, LCDColor color);

/**
 * Trace vertical line of given color on LCD.
 * 
 * @param col    [in] column number on LCD
 * @param begin  [in] first pixel number in column
 * @param end    [in] last  pixel number in column (excluded)
 * @param color  [in] color index in table <code>vga_lookup</code>
 */
void fb_draw_vline (LCDAxis col, LCDAxis begin, LCDAxis end, LCDColor color);

/**
 * LCD: Draw rectangle bound to given coordinate.
 * 
 * @param x0     [in] x coord of top left pixel
 * @param y0     [in] y coord of top left pixel
 * @param x1     [in] x coord of bottom right pixel
 * @param y1     [in] y coord of bottom right pixel
 * @param color  [in] color index in table <code>vga_lookup</code>
 */
void fb_draw_frame (LCDAxis x0, LCDAxis y0, LCDAxis x1, LCDAxis y1, LCDColor color);

/**
 * LCD: Draw rasterized (no anti-aliazing) line between given two points.
 * 
 * @param x0     [in] x coord of top left pixel
 * @param y0     [in] y coord of top left pixel
 * @param x1     [in] x coord of bottom right pixel
 * @param y1     [in] y coord of bottom right pixel
 * @param color  [in] color index in table <code>vga_lookup</code>
 */
extern void fb_draw_line (LCDAxis x0, LCDAxis y0, LCDAxis x1, LCDAxis y1, LCDColor color);

/**
 * LCD: Draw circle of given center and radius.
 * 
 * @param x0     [in] x coord of center pixel
 * @param y0     [in] y coord of center pixel
 * @param radius [in] (in pixels) of circle
 * @param color  [in] color index in table <code>vga_lookup</code>
 */
void fb_draw_circle (LCDAxis x0, LCDAxis y0, LCDAxis radius, LCDColor color);

/**
 * LCD: Display text in window box.
 * 
 * @param w      [in] window to display in
 * @param s      [in] string to display
 * @param line   [in] number of starting line
 * @param color  [in] color index in table <code>vga_lookup</code>
 */
void fb_window_print1 (LCDWindow* w, const LCDString s, LCDLine line, LCDColor color);

/**
 * LCD: Display text in window box. Use window foreground color.
 * 
 * @param w      [in] window to display in
 * @param s      [in] string to display
 * @param line   [in] number of starting line
 */
void fb_window_print2 (LCDWindow* w, const LCDString s, LCDLine line);

/**
 * LCD: Display window basics (frame, title, ...).
 * 
 * @param w  [in] window to display
 */
void fb_window_disp   (LCDWindow* w);

/**
 * LCD: Clear window area.
 * 
 * @param w  [in] window to clear
 */
void fb_window_clear  (LCDWindow* w);

#endif /* LCD_TOOLBOX_H_ */
