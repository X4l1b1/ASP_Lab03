/*
 * init.h
 *
 *  Created on: 22 mars 2012
 *  Author: Evangelina Lolivier-Exler
 *  Basic functions of initialization of the REPTAR board
 */

#ifndef INIT_H_
#define INIT_H_

#include <stdio.h>
#include <stdlib.h>
#include "gpio_toolbox.h"
#include "lcd_toolbox.h"
#include "timer_toolbox.h"
#include "bits.h"
#include "stddefs.h"
#include "gpio.h"
#include "padconf.h"
#include "lcd.h"
#include "prcm.h"
#include "intc.h"
#include "timer.h"

extern void GPIO_init();
extern void lcd_init();
extern void interrupt_init();
extern void timer_init();


#endif /* INIT_H_ */
