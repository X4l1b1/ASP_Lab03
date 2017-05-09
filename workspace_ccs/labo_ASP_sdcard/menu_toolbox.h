// Code based on:
// www.martinhubacek.cz
// Martin Hub��ek 21.4.2012
// Modified by Evangelina LOLIVIER-EXLER on 29/11/2012,
//				- added hierarchical menus
//				- change display refreshing method
//				- added buttons control



#ifndef __MENU_H__
#define __MENU_H__

#include "lcd.h"
#include "lcd_toolbox.h"


// Define some macros according to your display APIs,
// used languages and configure menu size

// Your code has to provide events to the variable keyPress
// you have to feed this values from your keyboard interrupt routine!
// Necessary values are BTN_LEFT, BTN_RIGHT, BTN_UP and BTN_DOWN

// If you use different languages, define them here
#define LANGUAGE_ENGLISH 0

// Set rows/cols based on your font (for graphical displays)
#define FONT_WIDTH	8
#define FONT_HEIGHT 16

#define OFFSET_Y 100

#define ROW(x) ((x)*FONT_HEIGHT)
#define COL(y) ((y)*FONT_WIDTH)
// For character LCDs use definitions below
//#define ROW(x) (x)
//#define COL(y) (y)

// Number of items on one screen
// Not including title
#define MENU_LINES (LINES_PER_SCREEN-4)

// Symbol which is displayed in front of the selected item
// This symbol doesn't appear when MENU_LINES == 1
#define ARROW_SYMBOL ">"
// How many spaces is between arrow symbol and menu item
// useful to set zero on smaller displays
#define ARROW_GAP 1

// Clear display
#define displayClear()  clear_screen()

// Display string
#define displayString(str, posx, posy) fb_print_string((uchar *) (str), (ulong) (posx), (ulong) (posy + OFFSET_Y), lcd_fg_color)
// Clear string
#define clearString(str, posx, posy) 	fb_print_string((uchar *) (str), (ulong) (posx), (ulong) (posy + OFFSET_Y), lcd_bg_color)

// If you have separate functions for set position and print text, use define below
//#define displayString(str, posx, posy) {lcdGotoXY(posx, posy); lcdBufferString(str);}

// Display number
//#define displayNumber(str, posx, posy) lcdBufferNumber(str, posx, posy)
// If you have separate functions for set position and print number, use define below
//#define displayNumber(str, posx, posy) {lcdGotoXY(posx, posy); lcdBufferNumber(str)}

// Optional function to write buffer to display - comment if not used
//#define displayDraw()           fb_draw_frame(0,0, PIXELS_PER_ROW, PIXELS_PER_COL, lcd_fg_color)

/* functions to read the state of the REPTAR switches */
/* RETURN 1 if the button is pressed, else 0 	*/
#define readSW0()	ReadInput(GPIO_MOD5,SW0)
#define readSW1()	ReadInput(GPIO_MOD5,SW1)
#define readSW2()	ReadInput(GPIO_MOD6,SW2)
#define readSW3()	ReadInput(GPIO_MOD4,SW3)

/* functions to set the state of the REPTAR LEDs */
/* RETURN 1 if the button is pressed, else 0 	*/
#define turnOnLed0()	SetOutput(GPIO_MOD5, LED0)
#define turnOffLed0()	ClearOutput(GPIO_MOD5, LED0)
#define turnOnLed1()	SetOutput(GPIO_MOD5, LED1)
#define turnOffLed1()	ClearOutput(GPIO_MOD5, LED1)


// Optional edit dialogs
// Needs some more tweaking directly in menu.c according to your drawing routines
//#define MENU_EDIT_NUMBER
//#define MENU_EDIT_TIME
//#define MENU_EDIT_TEMPERATURE

// Some stdlib definitions according to your compiler
//#define strlen(x) ustrlen(x)

// Nothing more to configure, that's all
// -----------------------------------------
typedef enum BUTTON {
	BTN_NULL,
	BTN_DOWN,
	BTN_UP,
	BTN_LEFT,
	BTN_ENTER,
	BTN_RIGHT
}button_t;


extern button_t keyPress;

#define int8_t int16_t
#define uint8_t unsigned char
#define int16_t short

typedef void * (*function_t)(void *);

struct MENU;

typedef struct ITEM {
	char 			*title;
	struct MENU		*submenu;
	function_t		function_ptr;
	void			*data;
} item_t;

typedef struct MENU {
	char			*title;
	struct MENU		*parent;
	item_t			*items;
} menu_t;


extern char actualLanguage;

// Makro usnad�uj�c� zobrazen� �et�zce podle navolen�ho jazyka
// #define lcd_putsLang(name) lcd_puts(name[actualLanguage])

void showMenu(menu_t *menu);
int8_t menuMsgBox(const char *str);

#ifdef MENU_EDIT_TEMPERATURE
uint8_t menuEditTemp(const char* str, int* temp, int increment);
#endif

#ifdef MENU_EDIT_TIME
int8_t menuEditTime(char *str, uint8_t* pHours, uint8_t* pMinutes);
#endif

#ifdef MENU_EDIT_NUMBER
uint8_t menuEditNumber(const char *str, int16_t *val, const char *unit, uint8_t inc, int16_t valMin, int16_t valMax);
#endif


extern button_t sw_polling();


extern volatile int menuPreselect;

#endif
