/*
 * timer_toolbox.h
 *
 *  Created on: Apr 11, 2017
 *      Author: redsuser
 */

#ifndef TIMER_TOOLBOX_H_
#define TIMER_TOOLBOX_H_

#include "timer.h"
#include "stddefs.h" // pour vulong
#include "bits.h"

void start_timer();
void stop_timer();
vulong read_timer_value();
void write_timer_value(vulong value);
vulong convertTimerToMs(vulong value);
vulong convertMsToTimer(vulong value);



#endif /* TIMER_TOOLBOX_H_ */
