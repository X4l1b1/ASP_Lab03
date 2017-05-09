/*
 * applications.c
 *
 *  Created on: Apr 13, 2017
 *      Author: Camilo Cerna Pineda & Ludovic Richard
 */

#include "applications.h"

uchar gameStatus = 0;	//0 = init, 1 = running, 2 = you can press
vulong lastScore = 0;
vulong bestScore = 0;
vulong timerr = 0;

void jeuDeReaction()
{
	gameStatus = 0;	//0 = init, 1 = running, 2 = you can press
	lastScore = 0;
	bestScore = 0;
	timerr = 0;
	char s[50];
	vulong randomTime = -1;
	while(1){
		if(SWIsPressed(1)){
			fb_print_string("                                  ", 300, 120, 15);
			fb_print_string("        Get Ready !               ", 300, 270, 15);
			fb_print_string("                                  ", 300, 300, 15);
			randomTime = rand() % (TIME_MAX - TIME_MIN + 1) + TIME_MIN;
			write_timer_value(0);
			start_timer();	// étape 4
			gameStatus = 1;
			SetLed(1);		// Pour savoir que le jeu tourne
		}

		if(convertTimerToMs(read_timer_value()) >= randomTime)
		{
			randomTime = 100000;
			stop_timer();
			SetLed(0);
			gameStatus = 2;
			write_timer_value(0);
			start_timer();
		}


		timerr = read_timer_value();
		sprintf((uchar *)s," timer : %ld, ms : %ld           ", timerr, convertTimerToMs(timerr));
		fb_print_string(s, 300, 450, 15);
	}
}
