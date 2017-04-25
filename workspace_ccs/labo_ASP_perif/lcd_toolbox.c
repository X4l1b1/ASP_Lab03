/* ----------------------------------------------------------------------
  Institut ReDS - HEIG-VD Yverdon-les-Bains
 ------------------------------------------------------------------------

 Auteur : Evangelina LOLIVIER-EXLER
 Email  : evangelina.lolivier-exler@heig-vd.ch
 Date   : 17/09/2008
 Modified: 24/05/2012 REPTAR board adaptation
 Description : LCD toolbox
 -----------------------------------------------------------------------
*/

/**
 * FILE: lcd_toolbox.c
 * 
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-07
 */
#include "lcd_toolbox.h"

#include "lcd.h"
#include "fb_fonts.h"
#include "vga_lookup.h"
#include "bits.h"
#include "stddefs.h"
#include "gpio.h"
#include "prcm.h"

#include "students_tools.h"

// globals to keep track of foreground, background colors and x,y position
uchar lcd_color_depth = 16;    // 16 bits per pixel
uchar lcd_bg_color    =  3;    // 0 to 15, used as lookup into VGA color table
uchar lcd_fg_color    =  8;    // 0 to 15, used as lookup into VGA color table

/* BEGIN: Bresenham algorithm utils */
// BRESENHAM: functions to switch from octant to octant 0 and vice-versa
typedef void (*bresenham_octant_f) (LCDAxis* x, LCDAxis* y);
static void octant_0 (LCDAxis* x, LCDAxis* y) {}
static void octant_1 (LCDAxis* x, LCDAxis* y) { XWAP(*x, *y); }
static void octant_2 (LCDAxis* x, LCDAxis* y) { *x = -(*x - PIXELS_PER_ROW); XWAP(*x, *y); }
static void octant_3 (LCDAxis* x, LCDAxis* y) { *x = -(*x - PIXELS_PER_ROW); }
static void octant_4 (LCDAxis* x, LCDAxis* y) { *x = -(*x); *y = -(*y);}
static void octant_5 (LCDAxis* x, LCDAxis* y) { *x = -(*x); *y = -(*y); XWAP(*x, *y); }
static void octant_6 (LCDAxis* x, LCDAxis* y) { *y = -(*y - PIXELS_PER_ROW); XWAP(*x, *y); }
static void octant_7 (LCDAxis* x, LCDAxis* y) { *y = -(*y); }

static const bresenham_octant_f bresenham_lut_0_from[] = {
    octant_0, octant_3, octant_7, octant_4, octant_1, octant_2, octant_6, octant_5
};

static const bresenham_octant_f bresenham_lut_0_to[] = {
    octant_0, octant_3, octant_7, octant_4, octant_1, octant_6, octant_2, octant_5 // swap 2, 6
};

/**
 * BRESENHAM: Compute original octant index of lut.
 * 
 * @param x  [in] position or delta in x axis
 * @param y  [in] position or delta in y axis
 */
static int compute_octant (LCDAxis x, LCDAxis y)
{
    /*
     * To simplify computation, we use following encoding:
     *
     * abs(y) > abs(x) | sgn(y) | sgn(x) | idx | octant
     *               0        0        0     0        0
     *               0        0        1     1        3
     *               0        1        0     2        7
     *               0        1        1     3        4
     *               1        0        0     4        1
     *               1        0        1     5      2/6
     *               1        1        0     6      6/2
     *               1        1        1     7        5
     */
    return BIT_TST(x, BIT_SIZE(x) - 1) | ((BIT_TST(y, BIT_SIZE(y) - 1) << 1) | (ABS(y) > ABS(x) ? 4 : 0));
}
/* END:   Bresenham algorithm utils */

/**
 * Set color pixels between begin (included) and end (excluded).
 * 
 * @remark numbers are in [0, PIXELS_PER_ROW * PIXELS_PER_COL]
 * 
 * @param begin  [in] first pixel number (as unidimentional array index)
 * @param end    [in] last  pixel number (as unidimentional array index)
 * @param step   [in] offset of next pixel
 * @param color  [in] index in table <code>vga_lookup</code>
 */
static void fb_set_pixel_foreach (LCDAxis begin, LCDAxis end, LCDAxis step, LCDColor color)
{
    for (; begin < end; begin += step)
    {
        LCD_BUF(begin * BITS_PER_PIXEL / 8) = vga_lookup[color];
    }
}

/**
 * Print string inside bound box.
 * If string is bigger than bounds, string is printed circularly.
 * 
 * @param pcbuffer  [in] string to print in inside bounds
 * @param x0        [in] x coord of top left pixel
 * @param y0        [in] y coord of top left pixel
 * @param x1        [in] x coord of bottom right pixel
 * @param y1        [in] y coord of bottom right pixel
 * @param color     [in] color index in table <code>vga_lookup</code>
 */
static void fb_boxed_print (const char *pcbuffer, LCDAxis x0, LCDAxis y0, LCDAxis x1, LCDAxis y1, LCDColor color)
{
    /* DONE */
    LCDAxis x = x0,
            y = y0;

    for (; *pcbuffer != '\0'; ++pcbuffer)
    {
        if (*pcbuffer == '\n' || x + FONT_WIDTH > x1)
        {
            x  = x0;
            y += FONT_HEIGHT;
            if (y > y1)
            {
                y = y0;
            }
        }

        if (*pcbuffer != '\n')
        {
            fb_print_char(*pcbuffer, x, y, color);
            x += FONT_WIDTH;
        }
    }
}

//------------------------------------------------------------------------------
// Delay for some usecs. - Not accurate
// and no Cache
void udelay (int delay)
{
    volatile int i;
    for ( i = LOOPS_PER_USEC * delay; i ; i--)
    ;
}



///--------------------------------------------------------------------------
// lcd_on
//
// This function turns on the DM3730 Display Controller
//
void lcd_on ()
{
    // Enable the clocks to the DISPC
    // enable functional clock (will be enable with the LCD_on function)
    DSS_CM_REG(CM_FCLKEN)|=BIT0;
    // enable interfaces clocks (L3 and L4)  (will be enable with the LCD_on function)
    DSS_CM_REG(CM_ICLKEN)|=BIT0;

    // power up the LCD
    udelay(10000);
    // LCD output enable
    LCD_REG(control)|= BIT0;
    udelay(10000);
}

//--------------------------------------------------------------------------
// lcd_off
//
// This function turns off the DM3730 Display Controller
//
void lcd_off ()
{
    // power down the LCD
    udelay(10000);
    
    // digital output disable
    LCD_REG(control)&=~BIT1;
    // LCD output disable
    LCD_REG(control)&=~BIT0;
    udelay(10000);
}

// ------------------------------------------------------------------
// get_pixel_add return the address of a pixel with respect to the frame buffer start address
ulong get_pixel_add (LCDAxis x, LCDAxis y)
{
    /* DONE in step 1 */
    return (y * PIXELS_PER_ROW + x) * BITS_PER_PIXEL / 8;
}

// ------------------------------------------------------------------
// fb_set_pixel sets a pixel to the specified color (between 0 et 15).
void fb_set_pixel (LCDAxis x, LCDAxis y, LCDColor color)
{
    /* DONE */
    if (x < PIXELS_PER_ROW && y < PIXELS_PER_COL)
    {
        LCD_BUF(get_pixel_add(x, y)) = vga_lookup[color];
    }
}

// ------------------------------------------------------------------
// fb_print_char prints a character at the specified location.
//
void fb_print_char (char cchar, LCDAxis x, LCDAxis y, LCDColor color)
{
    /* DONE in step 1 */
    LCDAxis i, j;
    for (i = 0; i < FONT_WIDTH; ++i)
    {
        for (j = 0; j < FONT_HEIGHT; ++j)
        {
            if (fb_font_data[cchar - FIRST_CHAR][j] & (1 << (BIT_SIZE(fb_font_data[0][0]) - i)))
            {
                fb_set_pixel(x + i, y + j, color);
            }
        }
    }
}

// ------------------------------------------------------------------
// fb_print_string prints a string at the specified location.(30 characters max)
//
void fb_print_string (const char *pcbuffer, LCDAxis x, LCDAxis y, LCDColor color)
{
    /* DONE in step 1 */
    fb_boxed_print(pcbuffer, x, y, PIXELS_PER_ROW - 1, PIXELS_PER_COL - 1, color);
}

// ------------------------------------------------------------------
//
// This function clear the screen
//
void clear_screen ()
{
    /* DONE in step 1 */
    fb_set_pixel_foreach(0, PIXELS_PER_ROW * PIXELS_PER_COL, 1, LCD_BG_DEF);
}

// ADDITIONAL FUNCTIONS
void fb_draw_hline (LCDAxis row, LCDAxis begin, LCDAxis end, LCDColor color)
{
    row *= PIXELS_PER_ROW;
    fb_set_pixel_foreach(begin + row, end + row, 1, color);
}

void fb_draw_vline (LCDAxis col, LCDAxis begin, LCDAxis end, LCDColor color)
{
    fb_set_pixel_foreach(begin * PIXELS_PER_ROW + col, end * PIXELS_PER_ROW + col, PIXELS_PER_ROW, color);
}

void fb_draw_frame (LCDAxis x0, LCDAxis y0, LCDAxis x1, LCDAxis y1, LCDColor color)
{
    fb_draw_hline(y0, x0, x1 + 1, color);
    fb_draw_hline(y1, x0, x1 + 1, color);
    fb_draw_vline(x0, y0, y1 + 1, color);
    fb_draw_vline(x1, y0, y1 + 1, color);
}

void fb_draw_line (LCDAxis x0, LCDAxis y0, LCDAxis x1, LCDAxis y1, LCDColor color)
{
    /* BRESENHAM ALGORITHM: integer version */

    // prepare data for right octant
    int octant = compute_octant(x1 - x0, y1 - y0);
    LCDAxis dx, dy, err;

    // convert to octant 0
    bresenham_lut_0_from[octant](&x0, &y0);
    bresenham_lut_0_from[octant](&x1, &y1);
    
    // locales for computing
    dx  = x1 - x0;
    dy  = y1 - y0;
    err = 2 * dy - dx;
    
    for (; x0 <= x1; ++x0)
    {
        // swap back to original octant, draw and return to octant 0
        bresenham_lut_0_to[octant](&x0, &y0);
        fb_set_pixel(x0, y0, color);
        bresenham_lut_0_from[octant](&x0, &y0);
        
        // drawing error computing
        if (err > 0)
        {
            ++y0;
            err -= 2 * dx;
        }
        err += 2 * dy;
    }
}

void fb_draw_circle (LCDAxis x0, LCDAxis y0, LCDAxis radius, LCDColor color)
{
    /* BRESENHAM ALGORITHM: circle version */
    LCDAxis x   = radius,
            y   = 0,
            err = 0;

    while (x >= y)
    {
        // set pixel in each octants, from 0 to 7
        fb_set_pixel(x0 + x, y0 + y, color);
        fb_set_pixel(x0 + y, y0 + x, color);
        fb_set_pixel(x0 - y, y0 + x, color);
        fb_set_pixel(x0 - x, y0 + y, color);
        fb_set_pixel(x0 - x, y0 - y, color);
        fb_set_pixel(x0 - y, y0 - x, color);
        fb_set_pixel(x0 + y, y0 - x, color);
        fb_set_pixel(x0 + x, y0 - y, color);
        
        // drawing error computing
        if (err <= 0)
        {
            ++y;
            err += 2 * y + 1;
        }
        else
        {
            --x;
            err -= 2 * x + 1;
        }
    }
}

void fb_window_print1 (LCDWindow* w, const LCDString s, LCDLine line, LCDColor color)
{
    fb_boxed_print(
        s,
        w->position.a.x + 3,
        w->position.a.y + 3 + FONT_HEIGHT + line * FONT_HEIGHT,
        w->position.b.x - 3,
        w->position.b.y - 3,
        color
    );
}

void fb_window_print2 (LCDWindow* w, const LCDString s, LCDLine line)
{
    fb_window_print1(w, s, line, w->fgcolor);
}

void fb_window_disp (LCDWindow* w)
{
    fb_window_clear(w);
    fb_draw_frame(w->position.a.x, w->position.a.y, w->position.b.x, w->position.b.y, w->border);
    fb_draw_frame(w->position.a.x + 2, w->position.a.y + FONT_HEIGHT + 3, w->position.b.x - 2, w->position.b.y - 2, w->border);
    fb_boxed_print(
        w->title,
        w->position.a.x + 2,
        w->position.a.y + 2,
        w->position.b.x - 3,
        w->position.a.y + 3 + FONT_HEIGHT,
        w->border
    );
}

void fb_window_clear (LCDWindow* w)
{
    LCDAxis i, row;
    for (i = w->position.a.y; i < w->position.b.y; ++i)
    {
        row = i * PIXELS_PER_ROW;
        fb_set_pixel_foreach(w->position.a.x + row, w->position.b.x + row + 1, 1, w->bgcolor);
    }
}
