/*
 * padconf.h
 *
 *  Created on: 22 mai 2012
 *  Author: Evangelina Lolivier-Exler
 */

#ifndef PADCONF_H_
#define PADCONF_H_

/* Control pad configuration registers */

/* GPIO */
/* GPIO_130 (15:0) and GPIO_131 (31:16) */
#define CONTROL_PADCONF_MMC2_CLK		0x48002158
/* GPIO_140 (15:0) and GPIO_141 (31:16) */
#define CONTROL_PADCONF_MCBSP3_DX		0x4800216C
/* GPIO_142 (15:0) and GPIO_143 (31:16) */
#define CONTROL_PADCONF_MCBSP3_CLKX		0x48002170
/* GPIO_28 (15:0) BACKLIGHT LCD FOR RESISTIVE DISPLAY (REPTAR PROTO1 ONLY) */
#define CONTROL_PADCONF_ETK_D14			0x48002170

/* DSS */
/* DSS_PCLK (15:0) and HSYNC (31:16) */
#define CONTROL_PADCONF_DSS_PCLK	0x480020D4
/* VSYNC (15:0) and ACBIAS (31:16) */
#define CONTROL_PADCONF_DSS_VSYNC	0x480020D8
/* DSS_DATA0 (15:0) and DSS_DATA1 (31:16) */
#define CONTROL_PADCONF_DATA0		0x480020DC
/* DSS_DATA2 (15:0) and DSS_DATA3 (31:16) */
#define CONTROL_PADCONF_DATA2		0x480020E0
/* DSS_DATA4 (15:0) and DSS_DATA5 (31:16) */
#define CONTROL_PADCONF_DATA4		0x480020E4
/* DSS_DATA6 (15:0) and DSS_DATA7 (31:16) */
#define CONTROL_PADCONF_DATA6		0x480020E8
/* DSS_DATA8 (15:0) and DSS_DATA9 (31:16) */
#define CONTROL_PADCONF_DATA8		0x480020EC
/* DSS_DATA10 (15:0) and DSS_DATA11 (31:16) */
#define CONTROL_PADCONF_DATA10		0x480020F0
/* DSS_DATA12 (15:0) and DSS_DATA13 (31:16) */
#define CONTROL_PADCONF_DATA12		0x480020F4
/* DSS_DATA14 (15:0) and DSS_DATA15 (31:16) */
#define CONTROL_PADCONF_DATA14		0x480020F8
/* DSS_DATA16 (15:0) and DSS_DATA17 (31:16) */
#define CONTROL_PADCONF_DATA16		0x480020FC
/* DSS_DATA18 (15:0) and DSS_DATA19 (31:16) */
#define CONTROL_PADCONF_DATA18		0x48002100
/* DSS_DATA20 (15:0) and DSS_DATA21 (31:16) */
#define CONTROL_PADCONF_DATA20		0x48002104
/* DSS_DATA22 (15:0) and DSS_DATA23 (31:16) */
#define CONTROL_PADCONF_DATA22		0x48002108


/* ACCESS MACROS */
#define SET_REG32(_x_)  *(vulong *)(_x_)	// _x_ must be a 32-bits address

/* options for pad_conf registers */

/* MUX mode */
#define MXMode0	0x0000
#define MXMode1	0x0001
#define MXMode2	0x0002
#define MXMode3	0x0003
#define MXMode4	0x0004
#define MXMode5	0x0005
#define MXMode6	0x0006
#define MXMode7	0x0007

/* Pull */
#define PULLUDENABLE_OFF	0		// pull-up/pull-down functionality disabled
#define PULLUDENABLE_ON		BIT3	// pull-up/pull-down functionality enabled
#define PULLTYPESELECT_DWN	0		// pull-down selected for the pin
#define PULLTYPESELECT_UP	BIT4	// pull-up selected for the pin


/* input enable */
#define INPUTENABLE_OFF		0		// input disable. Pin is configured in output only mode
#define INPUTENABLE_ON		BIT8	// input enable. Pin is configured in bidirectional mode

/* Off mode */
/* Note: Off mode is actif when the register 0x48002270 CONTROL_PADCONF_OFF(0)=1 or SYS_OFF_MODE=1 on the PRCM module */
#define OFFENABLE_OFF			0		// off mode values doesn't override the pin state when off mode is actif
#define OFFENABLE_ON			BIT9	// off mode values override the pin state when off mode is actif
#define OFFOUTENABLE_OUT		0		// enable Off mode output value
#define OFFOUTENABLE_IN			BIT10	// disable Off mode output value (mode input set)
#define OFFOUTVALUE_LOW			0		// set the output to "0"
#define OFFOUTVALUE_HI			BIT11	// set the output to "1"
#define OFFPULLUDENABLE_OFF		0		// pull-up/dwn is disabled during off mode
#define OFFPULLUDENABLE_ON		BIT12	// pull-up/dwn is enabled during off mode
#define OFFPULLTYPESELECT_DWN	0		// pull-down is selected during off mode
#define OFFPULLTYPESELECT_UP	BIT13	// pull-up is selected during off mode

/* Wake up */
#define WAKEUPENABLE_OFF		0		// disable wake-up detection on input
#define WAKEUPENABLE_ON			BIT14	// enable wake-up detection on input



#endif /* PADCONF_H_ */
