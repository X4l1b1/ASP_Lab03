/*
 * lcd.h
 *
 *  Created on: 22 mai 2012
 *  Author: Evangelina Lolivier-Exler
 *  Display Subsystem (DSS) Configuration Registers for DM37
 */

#ifndef LCD_H_
#define LCD_H_

#define FRAME_BUFFER_ADDR    	0x80500000
#define LCD_BUF(_x_)			*(vushort *)(FRAME_BUFFER_ADDR + _x_)	// Frame Buffer
#define LOOPS_PER_USEC			10

// defines for the display geometry - 480x800 TFT
#define PIXELS_PER_ROW			800
#define PIXELS_PER_COL			480
#define BITS_PER_PIXEL			16
#define TOP						0
#define BOTTOM					(PIXELS_PER_COL-1)
#define LEFT					0
#define RIGHT					(PIXELS_PER_ROW-1)
#define CENTER_X				(PIXELS_PER_ROW/2)
#define CENTER_Y				(PIXELS_PER_COL/2)
//#define ROWS_PER_SCREEN			20
//#define COLS_PER_SCREEN			30
#define CHAR_PER_LINE			(PIXELS_PER_ROW/FONT_WIDTH)		// FONT_WIDTH defined in fb_fonts
#define LINES_PER_SCREEN		(PIXELS_PER_COL/FONT_HEIGHT)

#define LCD_BG_DEF				1
#define LCD_FG_DEF				14

#define LCD_FB_SIZE(_depth_)				(((PIXELS_PER_COL * PIXELS_PER_ROW) * _depth_) / 8)

#define LCD_ROW_SIZE(_depth_)				((PIXELS_PER_ROW * _depth_) / 8)

#define LCD_GET_ADD(_row_, _col_, _depth_)	(((((_row_ * PIXELS_PER_ROW) * FONT_HEIGHT) \
											  + (_col_ * FONT_WIDTH)) \
											  * _depth_) / 8)
/* DSS BASE ADDRESS */
#define DSS_BASE_ADD		0x48050000

/* ACCESS MACROS */
#define DSS_REG(_x_)  *(vulong *)(DSS_BASE_ADD + _x_) // _x_ is an offset with respect to the base address

/* OMAP3 DSS registers */

#define SYSCONFIG			 0x10
#define SYSSTATUS			 0x14


/* DISPLAY CONTROLLER BASE ADDRESSES */
#define DSS_DISPC_BASE_ADD		0x48050400

/* ACCESS MACROS */
#define LCD_REG(_x_)  *(vulong *)(DSS_DISPC_BASE_ADD + _x_) // _x_ is an offset with respect to the base address

/* OMAP3 DSS DISPC registers */

#define control				 0x40
#define config				 0x44
#define default_color0		 0x4C
#define default_color1		 0x50
#define trans_color0		 0x54
#define trans_color1		 0x58
#define line_status			 0x5C
#define line_number			 0x60
#define timing_h			 0x64
#define timing_v			 0x68
#define pol_freq			 0x6C
#define divisor				 0x70
#define global_alpha		 0x74
#define size_dig			 0x78
#define size_lcd			 0x7C
#define gfx_ba0		 		 0x80
#define gfx_size	 		 0x8C
#define gfx_attributes		 0xA0
#define gfx_preload			 0x22C



/* Few Register Offsets */
#define FRAME_MODE_SHIFT			1
#define TFTSTN_SHIFT				3
#define DATALINES_SHIFT				8
#define GFX_FORMAT_SHIFT			1
#define GFX_SIZEY_SHIFT				16

#define SPLASH_SOLID_COLOR	0x00FF00F8

#endif /* LCD_H_ */
