/*
 * timer.h
 *
 *  Created on: 10 mai 2012
 *  Author: Evangelina Lolivier-Exler
 *  Register definitions for the DM3730 microcontroller
 */

#ifndef TIMER_H_
#define TIMER_H_

/* BASE ADDRESSES */
#define GPT1_BASE_ADD	0x48318000
#define GPT2_BASE_ADD	0x49032000
#define GPT3_BASE_ADD	0x49034000
#define GPT4_BASE_ADD	0x49036000
#define GPT5_BASE_ADD	0x49038000
#define GPT6_BASE_ADD	0x4903A000
#define GPT7_BASE_ADD	0x4903C000
#define GPT8_BASE_ADD	0x4903E000
#define GPT9_BASE_ADD	0x49040000
#define GPT10_BASE_ADD	0x48086000
#define GPT11_BASE_ADD	0x48088000

/* ACCESS MACROS */
#define GPT1_REG(_x_)  *(vulong *)(GPT1_BASE_ADD + _x_) // _x_ is an offset with respect to the base address
#define GPT2_REG(_x_)  *(vulong *)(GPT2_BASE_ADD + _x_)
#define GPT3_REG(_x_)  *(vulong *)(GPT3_BASE_ADD + _x_)
#define GPT4_REG(_x_)  *(vulong *)(GPT4_BASE_ADD + _x_)
#define GPT5_REG(_x_)  *(vulong *)(GPT5_BASE_ADD + _x_)
#define GPT6_REG(_x_)  *(vulong *)(GPT6_BASE_ADD + _x_)
#define GPT7_REG(_x_)  *(vulong *)(GPT7_BASE_ADD + _x_)
#define GPT8_REG(_x_)  *(vulong *)(GPT8_BASE_ADD + _x_)
#define GPT9_REG(_x_)  *(vulong *)(GPT9_BASE_ADD + _x_)
#define GPT10_REG(_x_)  *(vulong *)(GPT10_BASE_ADD + _x_)
#define GPT11_REG(_x_)  *(vulong *)(GPT11_BASE_ADD + _x_)

/* OMAP3 GPT registers offsets for all banks - page 2741*/
#define TIDR			0x000
#define TIOCP_CFG		0x010
#define TISTAT			0x014
#define TISR			0x018
#define TIER			0x01C
#define TWER			0x020
#define TCLR			0x024
#define TCRR			0x028
#define TLDR			0x02C
#define TTGR			0x030
#define TWPS			0x034
#define TMAR			0x038
#define TCAR1			0x03C
#define TSICR			0x040
#define TCAR2			0x044


#endif /* TIMER_H_ */
