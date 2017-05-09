/*
 * init.c
 *
 *  Created on: 21 mars 2012
 *      Author: Evangelina Lolivier-Exler
 *      Basic functions of initialization of the REPTAR board
 */

#include "bits.h"
#include "stddefs.h"
#include "gpio.h"
#include "gpio_toolbox.h"
#include "padconf.h"
#include "prcm.h"
#include "lcd.h"
#include "lcd_toolbox.h"


vulong PadConfValLED0=0;	// GPIO_141
vulong PadConfValLED1=0;	// GPIO_143
vulong PadConfValSW0=0;		// GPIO_142
vulong PadConfValSW1=0;		// GPIO_140

vulong PadConfVal=0;


void GPIO_init(){
	// initialization sequence: software reset
	GPIO5_REG(OMAP_GPIO_SYSCONFIG) |= BIT1;
	while ((GPIO5_REG(OMAP_GPIO_SYSSTATUS)&BIT0)==0);

	// initialization sequence: software reset
	GPIO4_REG(OMAP_GPIO_SYSCONFIG) |= BIT1;
	while ((GPIO4_REG(OMAP_GPIO_SYSSTATUS)&BIT0)==0);

	// initialization sequence: software reset
	GPIO6_REG(OMAP_GPIO_SYSCONFIG) |= BIT1;
	while ((GPIO6_REG(OMAP_GPIO_SYSSTATUS)&BIT0)==0);



	/* OUTPUTS */

	/* GPIOs configured as outputs */
	/* LED1 - D3 - GPIO_141 - PIN 67 */
	GPIO5_REG(OMAP_GPIO_OE) &= ~LED1;
	/* LED0 - D2 - GPIO_143 - PIN 71 */
	GPIO5_REG(OMAP_GPIO_OE) &= ~LED0;

	/* INPUTS */

	/* GPIOs configured as inputs */
	/* SW0 - GPIO_140 - PIN 65 */
	GPIO5_REG(OMAP_GPIO_OE) |= SW0;
	/* SW1 - GPIO_142 - PIN 69 */
	GPIO5_REG(OMAP_GPIO_OE) |= SW1;
	/* SW2 - GPIO_167 - PIN 57 */
	GPIO6_REG(OMAP_GPIO_OE) |= SW2;
	/* SW3 - GPIO_97 - PIN 59 */
	GPIO4_REG(OMAP_GPIO_OE) |= SW3;
	/* SW4 - GPIO_126 - PIN 62 */
	GPIO4_REG(OMAP_GPIO_OE) |= SW4;


	/* System Control Module: PAD Configuration */

	/* GPIOs 140 and 141 */

	PadConfValLED0=0;

	PadConfValLED0=	MXMode4
					|PULLUDENABLE_OFF
					|PULLTYPESELECT_UP
					|INPUTENABLE_OFF
					|OFFENABLE_ON
					|OFFOUTENABLE_OUT
					|OFFOUTVALUE_HI
					|OFFPULLUDENABLE_OFF
					|OFFPULLTYPESELECT_UP
					|WAKEUPENABLE_OFF;

	PadConfValSW1=0;

	PadConfValSW1=	MXMode4
					|PULLUDENABLE_ON
					|PULLTYPESELECT_DWN
					|INPUTENABLE_ON
					|OFFENABLE_ON
					|OFFOUTENABLE_IN
					|OFFOUTVALUE_HI
					|OFFPULLUDENABLE_ON
					|OFFPULLTYPESELECT_DWN
					|WAKEUPENABLE_OFF;


	SET_REG32(CONTROL_PADCONF_MCBSP3_DX)=PadConfValSW1|(PadConfValLED0<<16);

	
	/* GPIOs 142 and 143 */

	PadConfValLED1=0;

	PadConfValLED1=	MXMode4
						|PULLUDENABLE_OFF
						|PULLTYPESELECT_UP
						|INPUTENABLE_OFF
						|OFFENABLE_ON
						|OFFOUTENABLE_OUT
						|OFFOUTVALUE_HI
						|OFFPULLUDENABLE_OFF
						|OFFPULLTYPESELECT_UP
						|WAKEUPENABLE_OFF;
	PadConfValSW0=0;

	PadConfValSW0=	MXMode4
						|PULLUDENABLE_ON
						|PULLTYPESELECT_DWN
						|INPUTENABLE_ON
						|OFFENABLE_ON
						|OFFOUTENABLE_IN
						|OFFOUTVALUE_HI
						|OFFPULLUDENABLE_ON
						|OFFPULLTYPESELECT_DWN
						|WAKEUPENABLE_OFF;

	SET_REG32(CONTROL_PADCONF_MCBSP3_CLKX)=PadConfValSW0|(PadConfValLED1<<16);

	// MMC1_WP: input, pull-up on the REPTAR board, GPIO_129
	PadConfValSW0=0;

	PadConfValSW0=	MXMode4 |PULLUDENABLE_OFF
						|PULLTYPESELECT_UP
						|INPUTENABLE_ON
						|OFFENABLE_ON
						|OFFOUTENABLE_IN
						|OFFOUTVALUE_HI
						|OFFPULLUDENABLE_OFF
						|OFFPULLTYPESELECT_UP
						|WAKEUPENABLE_OFF;

	SET_REG32(CONTROL_PADCONF_GPIO128)|=(PadConfValSW0<<16);

	GPIO5_REG(OMAP_GPIO_OE) |= MMC1_WP;
	/* GPIO_126 SW3 */
	SET_REG32(CONTROL_PADCONF_GPIO127)   |= MXMode4 << 16;
	/* GPIO_97 SW2 */
	SET_REG32(CONTROL_PADCONF_CAM_XCLKA) |= MXMode4 << 16;



}

void lcd_init(){

	lcd_off();

	/* Clock configuration */
	// select DSS1_ALWON_FCLK frequency: DPLL4 divided by 2
	DSS_CM_REG(CM_CLKSEL)&=~DDS1_FIELD_MSK;
	DSS_CM_REG(CM_CLKSEL)|=PER_M4X2;
	// enable functional clock
	DSS_CM_REG(CM_FCLKEN)|= BIT0;
	// enable interfaces clocks (L3 and L4)  (must always be enable for access to the config registers)
	DSS_CM_REG(CM_ICLKEN)|= BIT0;



	/* System Control Module: PAD Configuration */

	// OUTPUT CONFIGURATION
	PadConfVal=0;

	PadConfVal	=	MXMode0
					|PULLUDENABLE_OFF
					|PULLTYPESELECT_UP
					|INPUTENABLE_OFF
					|OFFENABLE_ON
					|OFFOUTENABLE_OUT
					|OFFOUTVALUE_LOW
					|OFFPULLUDENABLE_OFF
					|OFFPULLTYPESELECT_UP
					|WAKEUPENABLE_OFF;

	/* DSS_PCLK (15:0) and HSYNC (31:16) */
	SET_REG32(CONTROL_PADCONF_DSS_PCLK)=PadConfVal|(PadConfVal<<16);
	/* VSYNC (15:0) and ACBIAS (31:16) */
	SET_REG32(CONTROL_PADCONF_DSS_VSYNC)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA0 (15:0) and DSS_DATA1 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA0)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA2 (15:0) and DSS_DATA3 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA2)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA4 (15:0) and DSS_DATA5 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA4)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA6 (15:0) and DSS_DATA7 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA6)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA8 (15:0) and DSS_DATA9 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA8)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA10 (15:0) and DSS_DATA11 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA10)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA12 (15:0) and DSS_DATA13 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA12)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA14 (15:0) and DSS_DATA15 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA14)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA16 (15:0) and DSS_DATA17 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA16)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA18 (15:0) and DSS_DATA19 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA18)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA20 (15:0) and DSS_DATA21 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA20)=PadConfVal|(PadConfVal<<16);
	/* DSS_DATA22 (15:0) and DSS_DATA23 (31:16) */
	SET_REG32(CONTROL_PADCONF_DATA22)=PadConfVal|(PadConfVal<<16);

	/* Display Subsystem (DSS) Configuration */
	DSS_REG(SYSCONFIG)|=BIT1;	// software reset
	while ((DSS_REG(SYSSTATUS)&BIT0)==0); // WAIT FOR RESET DONE

	// capacitive display parameters
	LCD_REG(timing_h)=0x0090097F; /* Horizontal timing */
	LCD_REG(timing_v)=0x00B00401; /* Vertical timing */
	LCD_REG(pol_freq)=0x00003000; /* Pol Freq */

	LCD_REG(divisor)=0x00010002; /* 33Mhz Pixel Clock */
	LCD_REG(size_lcd)=0x01df031f; /* 800x480 */
	LCD_REG(control)|= (0x01<<TFTSTN_SHIFT); /* panel_type: TFT */
	LCD_REG(control)|= (0x03<<DATALINES_SHIFT); /* data_lines: 24 Bit RGB */
	/* GPOUT0 AND GPOUT1: bypass mode */
	LCD_REG(control)|= BIT16;	// GPOUT1
	LCD_REG(control)|= BIT15;	// GPOUT0
	LCD_REG(config)= (0x02<<FRAME_MODE_SHIFT); /* load_mode: Frame Mode */
	LCD_REG(default_color0)=SPLASH_SOLID_COLOR;  /* ORANGE */
	LCD_REG(gfx_attributes)|= (0x6<<GFX_FORMAT_SHIFT); /* GRAPHICS FORMAT: RGB16 */
	LCD_REG(gfx_preload)=0x60;	// preload for TFT display
	LCD_REG(gfx_ba0)=FRAME_BUFFER_ADDR;	// graphics base address
	LCD_REG(gfx_size)|= (479<<GFX_SIZEY_SHIFT); /* number of lines of the graphics window */
	LCD_REG(gfx_size)|= 799; /* number of pixels per line of the graphics window */
	LCD_REG(gfx_attributes)|= BIT0;	//graphics layer enable
	LCD_REG(control)|= BIT5;	// go LCD -> the HW can update the internal registers

	lcd_on();

}

void isr_handler(){

	// Pour étape 5
	char s[50];
	timerValueWhenInterrupt = read_timer_value();
	//imerValueWhenInterrupt = timerr;
	stop_timer();
	ResetLed(0);
	ResetLed(1);
	switch(gameStatus)
	{
	case 0 : // le jeu n'a pas démarré donc ne rien faire
		break;
	case 1 : // pression précoce sur le bouton : effacer le best-score
		fb_print_string(        "         Cheater !            ", 300, 270, 15);
		bestScore = 0;	// Le meilleur score est effacé en cas de triche
		fb_print_string(        "                              ", 300, 80, 15);
		break;
	case 2 :  // pression correcte, calcul du temps de réaction.
		lastScore = convertTimerToMs(timerValueWhenInterrupt);
		gameStatus = 0;
		sprintf((uchar *)s,     "  Reaction time : %ld ms      ", lastScore);
		fb_print_string(s, 300, 270, 15);

		if(lastScore < 50)
			fb_print_string(    "     UNBELIEVABLE !!!         ", 300, 300, 15);
		else if(lastScore < 100)
			fb_print_string(    "        Amazing !             ", 300, 300, 15);
		else if(lastScore < 150)
			fb_print_string(    "         Great !              ", 300, 300, 15);
		else if(lastScore < 175)
			fb_print_string(    "        Not bad               ", 300, 300, 15);
		else if(lastScore < 200)
			fb_print_string(    "     Can be better...         ", 300, 300, 15);
		else if(lastScore < 250)
			fb_print_string(    "   That's not your day        ", 300, 300, 15);
		else
			fb_print_string(    "          Ugly !              ", 300, 300, 15);

		if(!bestScore | lastScore < bestScore)
		{
			bestScore = lastScore;
			fb_print_string(    "      NEW BEST SCORE !        ", 300, 120, 15);
		}

		sprintf((uchar *)s,     "    Best Score : %ld ms       ", bestScore);
		fb_print_string(s, 300, 80, 15);
		break;

	default :
		break;
	}


	/*
	// pour testerSetLed(1); étape 4
	char s[50] = {"            "};
	fb_print_string(s, 200, 300, 15);
	timerValueWhenInterrupt = read_timer_value();
	sprintf((uchar *)s, "%d", timerValueWhenInterrupt);
	fb_print_string(s, 200, 300, 15);
	stop_timer();
	write_timer_value(0);*/

	// Pour étape 3
	// Toggle led 0
	//ToggleLed(0);

	// Reset du flag d'interruption
	GPIO5_REG(OMAP_GPIO_IRQSTATUS1) = BIT12;		// Voir page 3524 : Mettre à 1 = clear (donc mettre à 0 le flag)

	// Autoriser une nouvelle interruption
	MPU_INTC_REG(INTC_CONTROL) |= BIT0;
>>>>>>> 387a2dd4853eada446fa47f3ec7eade6d2e28c4b
}



