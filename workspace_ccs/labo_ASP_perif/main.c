/*---------------------------------------------------------------------------------------
* But               : Petit programme pour etre charge dans le micro et affiche avec dump
* Auteur            : Evangelina LOLIVIER-EXLER
* Date              : 29.07.2008
* Version           : 1.0
* Fichier           : demo.c
*----------------------------------------------------------------------------------------*/

/**
 * FILE: main.c
 * 
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-07
 */

#include "cfg.h"
#include "stddefs.h"

// BEGIN: added by students
#include "init.h"
#include "lcd.h"
#include "lcd_toolbox.h"
#include "react_game.h"
// END:   added by students

/* Global variables */

vulong AppStack_svr[APPSTACKSIZE/4];
vulong AppStack_irq[APPSTACKSIZE/4];
int t[8];

// BEGIN: added by students
void general_init (void);
// END:   added by students

/* main */
int main(void)
{

    // BEGIN: added by students
    general_init();
    clear_screen();
    react_game_reset();
    
    do
    {
        react_game_init();
        react_game_start();
        react_game_stop();
        react_game_result();
    } while (react_game_continue());

    clear_screen();
    fb_print_string("THE END !!!", 0, 0, BRIGHT_RED);
    
    while(1);

    return(0);
}

// BEGIN: added by students
void general_init (void)
{
    lcd_off();
    lcd_init();
    lcd_on();
    GPIO_init();
    interrupt_init();
    timer_init();
}
// END:   added by students

