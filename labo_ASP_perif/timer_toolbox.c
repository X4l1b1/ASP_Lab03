/*
 * timer_toolbox.c
 *
 *  Created on: Apr 11, 2017
 *      Author: redsuser
 */

#include "timer_toolbox.h"


void start_timer()
{
	GPT1_REG(TCLR) |= BIT0;
}

void stop_timer()
{
	GPT1_REG(TCLR) &= ~BIT0;
}

vulong read_timer_value()
{
	return GPT1_REG(TCRR);
}

void write_timer_value(vulong value)
{
	GPT1_REG(TCRR) = value;
}
vulong convertTimerToMs(vulong value)
{
	return value/32;
}

vulong convertMsToTimer(vulong value)
{
	return value*32;
}
