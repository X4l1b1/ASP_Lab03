// Code based on:
// www.martinhubacek.cz
// Martin Hub��ek 21.4.2012
// Modified by Evangelina LOLIVIER-EXLER on 29/11/2012,
//				- added hierarchical menus
//				- change display refreshing method
//				- added buttons control

#include "lcd_toolbox.h"
#include "menu_toolbox.h"
#include "gpio_toolbox.h"
#include "bits.h"

extern void display_sd_info();

char actualLanguage = LANGUAGE_ENGLISH;
button_t  keyPress=BTN_NULL;


volatile int menuPreselect = -1;

/*
 * Displays menu
 *
 *
 * Global value menuPreselect preselects item in menu before calling showMenu,
 *                      if menuPreselect = -1 then this option is disabled
 *
 *
*/
void showMenu(menu_t *menu) {

        unsigned char menuItemNb = 0;
        unsigned char lastmenuItemNb = 255;
        unsigned char cursorTopPos = 0;
        unsigned char menuTopPos = 0;
        uchar refresh_all=1;
        item_t *iList = menu->items;

        unsigned char i;
  
        //unsigned char buffer[20];

        //
        // Get number of items in menu, search for the first NULL
        //
        int len = 0;
        for (; iList->title != 0; iList++)
          len++;

        // iList points to the top of the items list
        iList = menu->items;

        // Functional :)
        // menuItemNb, menuTopPos, cursorTopPos
        if(menuPreselect != -1)
        {
          // If item on the first screen
          if(menuPreselect < MENU_LINES)
          {
                  menuItemNb = menuPreselect;
                  cursorTopPos = menuPreselect;
                  menuTopPos = 0;
          } else {
                 // Item is on other screen
                  menuItemNb = menuPreselect;
                  cursorTopPos = MENU_LINES - 1;
                  menuTopPos = menuPreselect - cursorTopPos;
          }
        }



        // Main menu loop
        for(;;) {

                // If your system allows idle mode
                #ifdef SLEEP
                        SysCtlSleep();
                #endif

               if(keyPress) {
                        
                  //
                  // Down
                  //
                if(keyPress == BTN_DOWN)
                  {
                        if(menuItemNb != len-1)
                        {
                        menuItemNb++;

                        if(cursorTopPos >= MENU_LINES-1)
                          menuTopPos++;
                        else
                          cursorTopPos++;

                        } else {
                                menuItemNb = 0;
                                cursorTopPos = 0;
                                menuTopPos = 0;
                        }
                  }

                  //
                  // Up
                  //
                 if(keyPress == BTN_UP)
                  {
                        if(menuItemNb != 0)
                        {
                        menuItemNb--;

                        if(cursorTopPos > 0)
                          cursorTopPos--;
                        else
                          menuTopPos--;
                          } else {
                                menuItemNb = len-1;

                                if(len <= MENU_LINES)
                                {
                                        menuTopPos = 0;
                                } else {
                                        menuTopPos = menuItemNb;
                                }
                                if(menuTopPos > len - MENU_LINES && len >= MENU_LINES)
                                {
                                        menuTopPos = len - MENU_LINES;
                                }

                                cursorTopPos = menuItemNb - menuTopPos;
                          }
                  }


                  //
                  // Enter
                  //
                 if(keyPress == BTN_ENTER || keyPress == BTN_RIGHT)
                  {
                        keyPress = 0;
                        menuPreselect = -1;
                        // enter to the sub-menu
                        if ( iList[menuItemNb].submenu != 0)
                        	showMenu(iList[menuItemNb].submenu);
                        else if ( iList[menuItemNb].function_ptr != 0)
                        {
                         	(iList[menuItemNb].function_ptr)(iList[menuItemNb].data);
                         	refresh_all = 1;
                        }

                  }


                  //
                  // Left - back
                  //
                  if(keyPress == BTN_LEFT)
                  {
                        keyPress = 0;
                        menuPreselect = -1;
                        // back to the parent menu
                        if (menu->parent != 0)
                         	showMenu(menu->parent);
                        else
                        // main menu: exit
                        	return;

                  }

                                keyPress = 0;

                        } // if(keyPress)

                //
                // If menu item changed -> refresh screen
                //
                if(lastmenuItemNb != menuItemNb)
                {
                	if (refresh_all == 1)
                	{
                		displayClear();
                		display_sd_info();
                		displayString(menu->title,0,0);
                	}


                  i = 0;
                  while((i + menuTopPos) < len &&   i < MENU_LINES)
                  {
                        if((menuItemNb == i + menuTopPos) && (MENU_LINES > 1))
                        {
                        	/* clear arrow on the previous line */
                        	if (i==0)
                        		clearString(ARROW_SYMBOL, 0, ROW(len));
                        	else
                        		clearString(ARROW_SYMBOL, 0, ROW((i-1)%len+1));
                        	/* clear arrow on the next line */
                        	clearString(ARROW_SYMBOL, 0, ROW((i+1)%len+1));
                        	/* draw arrow on the current line */
                            displayString(ARROW_SYMBOL, 0, ROW(i+1));
                        }

                        if (refresh_all == 1)
                        {
                        	if(MENU_LINES > 1)
                        	  displayString(iList[menuTopPos + i].title, COL(1+ARROW_GAP), ROW(i+1));
                        	else
                        	  displayString(iList[menuTopPos + i].title, COL(0), ROW(i+1));
                        }
                        i++;
                  }

                        #ifdef displayDraw
                          displayDraw();
                        #endif

                  lastmenuItemNb = menuItemNb;
                  refresh_all = 0;
                }

                /* wait for a button to be pressed */
                keyPress = sw_polling();

                        
        }   
        
}


/*
 * Temperature edit dialog
 * str - text to display
 * temp - pointer to the temperature, WARNING it's in decicelsius:
 *                      value 326 means = 32,6�C
 *                      value -15 means = -1,5�C
 * increment - increment, for editing celsius number enter 10
 *                                                      for editing thenth of celesius enter 1
 *
 * returns - 1 if user pressed key right
 *                      0 if user pressed key left
 */
#ifdef MENU_EDIT_TEMPERATURE
uint8_t menuEditTemp(const char* str, int* temp, int increment)
{
        int editTemp = *temp;

        for(;;)
        {

        displayClear();
        displayString(str, 0, 0);

        lcd_gotoxy(2,1);
        //displayNumber(editTemp, 1);

        while(keyPress == 0);

        switch(keyPress)
        {

                case BTN_UP:
                        keyPress = 0;
                        editTemp += increment;
                        break;

                case BTN_DOWN:
                        keyPress = 0;
                        editTemp -= increment;
                        break;

                case BTN_RIGHT:
                        keyPress = 0;
                        *temp = editTemp;
                        return 1;
                        break;

                case BTN_LEFT:
                        keyPress = 0;
                        return 0;
                        break;

        }
        }
}
#endif //MENU_EDIT_TEMPERATURE

/*
 * Time edit dialog
 * str - Instruction text
 * pHourst - pointer to the hours
 * pMinutes - pointer to the minutes
 *
 * returns -  1 if the user confirmed value by pressing BTN_RIGHT
 *                        0 if the user pressed BTN_LEFT
 */
#ifdef MENU_EDIT_TIME
int8_t menuEditTime(char *str, uint8_t* pHours, uint8_t* pMinutes)
{
        int8_t hours, minutes, deciMinutes;

        unsigned char editPos = 0;
        unsigned char editGoto[] = {1, 3, 4};

        unsigned char relX = 4, relY = 3;

        hours = *pHours;
        minutes = *pMinutes % 10;
        deciMinutes = *pMinutes / 10;


        for(;;)
        {
                lcdBufferClear();
                lcdBufferString(str, COL(0),ROW(1));

                lcdBufferDrawUnderline((editPos == 0) ? 1 : 0);
                lcdBufferNumber2(hours, COL(relX), ROW(relY));

                lcdBufferDrawUnderline(0);
                lcdBufferString(":", COL(relX+2), ROW(relY));

                lcdBufferDrawUnderline((editPos == 1) ? 1 : 0);
                lcdBufferNumber(deciMinutes, COL(relX+3), ROW(relY));
                lcdBufferDrawUnderline((editPos == 2) ? 1 : 0);
                lcdBufferNumber(minutes, COL(relX+4), ROW(relY));

                lcdBufferDrawUnderline(0);
                //lcd_gotoxy(editGoto[editPos] + relX, relY);
                
                lcdBufferDraw();

                //lcd_command(LCD_DISP_ON_CURSOR);

                while(keyPress == 0);

                //lcd_command(LCD_DISP_ON);

                switch(keyPress)
                {
                        case BTN_LEFT:
                                keyPress = 0;
                                if(editPos == 0)
                                        return 0;
                                editPos--;
                                break;

                        case BTN_RIGHT:
                                keyPress = 0;
                                if(editPos == 2)
                                {
                                        *pHours = hours;
                                        *pMinutes = deciMinutes*10 + minutes;
                                        return 1;
                                }
                                editPos++;
                                break;

                        case BTN_UP:
                                keyPress = 0;
                                if(editPos == 0)
                                {
                                        hours++;
                                        if(hours > 23)
                                                hours = 0;
                                }
                                if(editPos == 1)
                                {
                                        deciMinutes++;
                                        if(deciMinutes > 5)
                                                deciMinutes = 0;
                                }
                                if(editPos == 2)
                                {
                                        minutes++;
                                        if(minutes > 9)
                                                minutes = 0;
                                }
                                break;

                        case BTN_DOWN:
                                keyPress = 0;
                                if(editPos == 0)
                                {
                                        hours--;
                                        if(hours < 0)
                                                hours = 23;
                                }
                                if(editPos == 1)
                                {
                                        deciMinutes--;
                                        if(deciMinutes < 0)
                                                deciMinutes = 5;
                                }
                                if(editPos == 2)
                                {
                                        minutes--;
                                        if(minutes < 0)
                                                minutes = 9;
                                }
                                break;

                        default:
                                keyPress = 0;
                                break;

                }

        }
}
#endif // MENU_EDIT_TIME


//
// Shows text on screen and wait for any keypress
//
int8_t menuMsgBox(const char *str)
{
        displayClear();
        displayString(str,0,0);
#ifdef displayDraw
        displayDraw();
#endif

        while(keyPress == 0);
        keyPress = 0;

        return 1;

}

/* polling of buttons: use the return to set the variable keyPress */
button_t sw_polling()
{
	if (readSW0())
	{
		while(readSW0());
		return BTN_DOWN;
	}
	if (readSW1())
	{
		while(readSW1());
		return BTN_UP;
	}
	if (readSW2())
	{
		while(readSW2());
		return BTN_ENTER;
	}
	if (readSW3())
	{
		while(readSW3());
		return BTN_LEFT;
	}

	return BTN_NULL;
}


/*
 * Edit number by pressing keys up/down
 *
 * str - string with instructions
 * val - pointer to the edited value
 * unit - string useful for units (m, kg..), displays behind the number
 * inc - increment/decrement
 * valMin - minimal value, inclusive
 * valMax - maximal value, inclusive
 *
 * returns - 1 if user confirmed edited number by BTN_RIGHT
 *                 - 0 if user pressed key BTN_LEFT
 */
#ifdef MENU_EDIT_NUMBER
uint8_t menuEditNumber(const char *str, int16_t *val, const char *unit, uint8_t inc, int16_t valMin, int16_t valMax)
{
        int16_t actVal = *val;
        int16_t posx = COL(0);
        int16_t posy = ROW(0);

        for(;;)
        {
                displayClear();
                displayString(str, posx, posy);
                displayNumber(actVal, posx + COL(strlen(str)), posy);
                displayString(unit, posx + COL(strlen(str) + 3), posy);

                displayDraw();

                while(keyPress == 0);

                switch(keyPress)
                {
                        case BTN_LEFT:
                                keyPress = 0;
                                return 0;
                                break;
                        
                        case BTN_RIGHT:
                                keyPress = 0;
                                *val = actVal;
                                return 1;
                                break;

                        case BTN_UP:
                                keyPress = 0;
                                if(actVal + inc <= valMax)
                                        actVal += inc;
                                break;


                        case BTN_DOWN:
                                keyPress = 0;
                                if(actVal - inc >= valMin)
                                        actVal -= inc;
                                break;

                }

        }
}
#endif //MENU_EDIT_NUMBER
