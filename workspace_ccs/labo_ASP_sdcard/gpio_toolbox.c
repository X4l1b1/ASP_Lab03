/*
 * gpio_toolbox.c
 *
 *  Created on: 14 mars 2017
 *  Author: Ludovic Richard & Camilo Pineda Serna
 *  fonctions for GPIO access
 */


#include "gpio_toolbox.h"



extern void SetLed (uchar nLed){
	switch(nLed){
	case 0 :
		SetOutput(5, BIT15);
		break;
	case 1 :
		SetOutput(5, BIT13);
		break;
	default :
		break;
	}
}

extern void ResetLed (uchar nLed){
	switch(nLed){
	case 0 :
		ClearOutput(5, BIT15);
		break;
	case 1 :
		ClearOutput(5, BIT13);
		break;
	default :
		break;
	}
}

extern void ToggleLed (uchar nLed){
	switch(nLed){
	case 0 :
		ToggleOutput(5, BIT15);
		break;
	case 1 :
		ToggleOutput(5, BIT13);
		break;
	default :
		break;
	}
}

extern uchar ReadLed (uchar nLed){
	switch(nLed){
	case 0 :
		return ReadInput(5, BIT15);
	case 1 :
		return ReadInput(5, BIT13);
	default :
		break;
	}
}

extern uchar SWIsPressed (uchar nSW){
	switch(nSW){
	case 0 :
		return ReadInput (5, BIT12);
	case 1 :
		return ReadInput (5, BIT14);
	default :
		return 0;
	}
}

/**
 * module c'est le gpio, toujours le 5 pour les 2 sw et les 2 leds
 * bitmask ce qu'on veut appliquer
 */
extern void SetOutput(uchar module, ulong bitmask){
	switch (module) {
	case 5 :
		{
			GPIO5_REG(OMAP_GPIO_SETDATAOUT) = bitmask;
			break;
		}
	}
}

extern void ClearOutput(uchar module, ulong bitmask){
	switch (module) {
	case 5 :
		{
			GPIO5_REG(OMAP_GPIO_CLEARDATAOUT) = bitmask;
			break;
		}
	}
}

extern uchar ReadInput(uchar module, ulong bitmask){
	switch (module) {
	case 5 :
		{
			// must return 0 or 1 because we return an uchar
			return GPIO5_REG(OMAP_GPIO_DATAIN) & bitmask ? 1 : 0;
		}
	}
	return 0;
}

extern void ToggleOutput(uchar module, ulong bitmask){
	switch (module) {
	case 5 :
		{
			GPIO5_REG(OMAP_GPIO_DATAOUT) ^= bitmask;
			break;
		}
	}
}

extern void UnmaskIRQ(uchar module, ulong bitmask){
	//GPIO5_REG(module) |= bitmask;
}

extern void MaskIRQ(uchar module, ulong bitmask){

}

