/*
 * test_menu.c
 *
 *  Created on: 04 dec 2012
 *  Author: Evangelina Lolivier-Exler
 *  This program tests the use of menu_toolbox.c
 */

#include "bits.h"
#include "init.h"
#include "gpio_toolbox.h"
#include "cfg.h"
#include "stddefs.h"
#include "lcd_toolbox.h"
#include "lcd.h"
#include "menu_toolbox.h"

#include "sd_toolbox.h"
#include "ff.h"
#include "fat_toolbox.h"
#include "stddefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Work area (file system object) for logical drive */
FATFS fs;

/* MENUS */

/* the last item of each menu must be initialized to NULL 			*/
/* Main menu has a maximum of 11 items, corresponding to 10 files   */
/* in the SD card plus the NULL item 								*/
item_t mainMenuItems[11];
/* each sub-menu has 3 items: read, info and run plus the NULL item */
item_t subMenuItems[11][4];

/* names of the 10 files, each name of a max of 12 characters (8.3 + NULL) */
char fileNames[10][12];

menu_t mainMenu = {"Picomon - Files on the SD card",0, mainMenuItems};
menu_t subMenu[10];


void initMenusTree()
{
	   FILINFO finfo;
	    DIR dirs;
	    char* path="";
	    int i=0;

	    ///////////////////////////////////////////////////
	    // Completer le code ici
	    //
	    // Utiliser comme exemple la fonction scan_files()
	    // Vous devez parcourir les differents fichiers contenu dans la carte SD
	    // On ne supportera pas l'acces aux dossiers.
	    //
	    // Le menu est complété par la partie du code {} ci-dessous en récupérant
	    // le nom de chaque fichier par la variable suivante : &finfo.fname[0]
	    //
	    ///////////////////////////////////////////////////
	    {
	        	/* Main menu item title = file name */
	        	memcpy(&fileNames[i][0],&finfo.fname[0],sizeof(fileNames[i]));
	        	mainMenuItems[i].title = &fileNames[i][0];
	        	/* Main menu sub-menu: choice between read or show file info */
	        	mainMenuItems[i].submenu = &subMenu[i];
	        	/* Main menu function and data pointers for each item = NULL */
	        	mainMenuItems[i].function_ptr = 0;
	        	mainMenuItems[i].data = 0;
	        	/* sub-menu title = file name */
	        	subMenu[i].title = &fileNames[i][0];
	        	subMenu[i].parent = &mainMenu;
	        	/* sub-menu items tables: choice between read or show file info */
	        	subMenu[i].items = subMenuItems[i];
	    		/* Sub-menu i: title, function and data pointers for each item */
	        	/* read file */
	        	subMenuItems[i][0].title = "Read file";
	        	subMenuItems[i][0].function_ptr = (function_t) read_file;
	        	subMenuItems[i][0].data = &fileNames[i][0];
	        	subMenuItems[i][0].submenu = 0;
	        	/* show info */
	        	subMenuItems[i][1].title = "Show File information";
	        	subMenuItems[i][1].function_ptr = (function_t) print_file_info;
	        	subMenuItems[i][1].data = &fileNames[i][0];
	        	subMenuItems[i][1].submenu = 0;
	        	/* run application */
	        	subMenuItems[i][2].title = "Load and run ELF application";
	        	subMenuItems[i][2].function_ptr = (function_t) run_app;
	        	subMenuItems[i][2].data = &fileNames[i][0];
	        	subMenuItems[i][2].submenu = 0;

	        	/* last item */
	        	subMenuItems[i][3].title = 0;
	        	subMenuItems[i][3].function_ptr = 0;
	        	subMenuItems[i][3].data = 0;
	        	subMenuItems[i][3].submenu = 0;

	        	i++;
	    }

	    /* initialize last items to NULL */

    	/* Main menu item title = file name */
    	mainMenuItems[i].title = 0;
    	/* Main menu sub-menu: choice between read or show file info */
    	mainMenuItems[i].submenu = 0;
    	/* Main menu function and data pointers for each item = NULL */
    	mainMenuItems[i].function_ptr = 0;
    	mainMenuItems[i].data = 0;

    	/* read file */
    	subMenuItems[i][0].title = 0;
    	subMenuItems[i][0].function_ptr = 0;
    	subMenuItems[i][0].data = 0;
    	subMenuItems[i][0].submenu = 0;
    	/* show info */
    	subMenuItems[i][1].title = 0;
    	subMenuItems[i][1].function_ptr = 0;
    	subMenuItems[i][1].data = 0;
    	subMenuItems[i][1].submenu = 0;
    	/* last item */
    	subMenuItems[i][2].title = 0;
    	subMenuItems[i][2].function_ptr = 0;
    	subMenuItems[i][2].data = 0;
    	subMenuItems[i][2].submenu = 0;
}

void display_sd_info()
{
	int sdcard_size;
	uchar name_pnm[6];

	// Print info
	sprintf((char *)lcd_line, "**** SD card info ****");
	fb_print_string(lcd_line,0, get_current_y(), lcd_fg_color);
	line_nb++;

	// Print name
	read_productname(name_pnm);
	sprintf((char *)lcd_line, "Card name : %s", name_pnm);
	fb_print_string(lcd_line,0, get_current_y(), lcd_fg_color);
	line_nb++;

	// Print size
	sdcard_size=read_card_size();
	sprintf((char *)lcd_line, "Card size = %d KB", sdcard_size);
	fb_print_string(lcd_line,0, get_current_y(), lcd_fg_color);
	line_nb++;
}


int test_menu(void){
	// GPIO initialization
	GPIO_init();
	turnOffLed0();
	turnOffLed1();

	//clear LCD
	clear_screen();

    // Register a work area to logical drive 0
    f_mount(0, &fs);

    // Menu initialization
    initMenusTree();

    // show main menu
    showMenu(&mainMenu);

    // Unregister a work area before discard it
    f_mount(0, NULL);

	return 0;
}
