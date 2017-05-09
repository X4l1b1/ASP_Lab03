/*
 * gpio.h
 *
 *  Created on: 21 mars 2012
 *  Author: Evangelina Lolivier-Exler
 *  Register definitions for the DM3730 microcontroller
 */

#ifndef __ASSEMBLY__


/* BASE ADDRESSES */
#define GPIO_MOD1_BASE_ADD	0x48310000
#define GPIO_MOD2_BASE_ADD	0x49050000
#define GPIO_MOD3_BASE_ADD	0x49052000
#define GPIO_MOD4_BASE_ADD	0x49054000
#define GPIO_MOD5_BASE_ADD	0x49056000
#define GPIO_MOD6_BASE_ADD	0x49058000


/* ACCESS MACROS */
#define GPIO1_REG(_x_)  *(vulong *)(GPIO_MOD1_BASE_ADD + _x_) // _x_ is an offset with respect to the base address
#define GPIO2_REG(_x_)  *(vulong *)(GPIO_MOD2_BASE_ADD + _x_)
#define GPIO3_REG(_x_)  *(vulong *)(GPIO_MOD3_BASE_ADD + _x_)
#define GPIO4_REG(_x_)  *(vulong *)(GPIO_MOD4_BASE_ADD + _x_)
#define GPIO5_REG(_x_)  *(vulong *)(GPIO_MOD5_BASE_ADD + _x_)
#define GPIO6_REG(_x_)  *(vulong *)(GPIO_MOD6_BASE_ADD + _x_)


/* OMAP3 GPIO registers */
#define OMAP_GPIO_REVISION			0x0000
#define OMAP_GPIO_SYSCONFIG			0x0010
#define OMAP_GPIO_SYSSTATUS			0x0014
#define OMAP_GPIO_IRQSTATUS1		0x0018
#define OMAP_GPIO_IRQSTATUS2		0x0028
#define OMAP_GPIO_IRQENABLE2		0x002c
#define OMAP_GPIO_IRQENABLE1		0x001c
#define OMAP_GPIO_WAKE_EN			0x0020
#define OMAP_GPIO_CTRL				0x0030
#define OMAP_GPIO_OE				0x0034
#define OMAP_GPIO_DATAIN			0x0038
#define OMAP_GPIO_DATAOUT			0x003c
#define OMAP_GPIO_LEVELDETECT0		0x0040
#define OMAP_GPIO_LEVELDETECT1		0x0044
#define OMAP_GPIO_RISINGDETECT		0x0048
#define OMAP_GPIO_FALLINGDETECT		0x004c
#define OMAP_GPIO_DEBOUNCE_EN		0x0050
#define OMAP_GPIO_DEBOUNCE_VAL		0x0054
#define OMAP_GPIO_CLEARIRQENABLE1	0x0060
#define OMAP_GPIO_CLEARIRQENABLE2	0x0070
#define OMAP_GPIO_SETIRQENABLE1		0x0064
#define OMAP_GPIO_SETIRQENABLE2		0x0074
#define OMAP_GPIO_CLEARWKUENA		0x0080
#define OMAP_GPIO_SETWKUENA			0x0084
#define OMAP_GPIO_CLEARDATAOUT		0x0090
#define OMAP_GPIO_SETDATAOUT		0x0094


#endif
