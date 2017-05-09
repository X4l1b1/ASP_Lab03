/*
 * gpio_toolbox.h
 *
 *  Created on: 22 mars 2012
 *  Author: Evangelina Lolivier-Exler
 *  prototypes for GPIO access
 */

#ifndef GPIO_TOOLBOX_H_
#define GPIO_TOOLBOX_H_

#include "stddefs.h"
#include "bits.h"

#define GPIO_MOD5	5
#define LED0		BIT15
#define LED1		BIT13
#define SW0			BIT12
#define SW1			BIT14
#define GPIO_MOD6	6
#define SW2			BIT7
#define GPIO_MOD4	4
#define SW3			BIT1
#define SW4			BIT30

#define MMC1_WP		BIT1

extern void SetOutput(uchar module, ulong bitmask);
extern void ClearOutput(uchar module, ulong bitmask);
extern uchar ReadInput(uchar module, ulong bitmask);
extern void ToggleOutput(uchar module, ulong bitmask);
extern void UnmaskIRQ(uchar module, ulong bitmask);
extern void MaskIRQ(uchar module, ulong bitmask);

#endif /* GPIO_TOOLBOX_H_ */
