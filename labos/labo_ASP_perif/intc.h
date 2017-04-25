/*
 * intc.h
 *
 *  Created on: 8 mai 2012
 *  Author: Evangelina Lolivier-Exler
 *  Register definitions for the DM3730 microcontroller
 */

#ifndef INTC_H_
#define INTC_H_

/* BASE ADDRESSES */
#define MPU_INTC_BASE_ADD	0x48200000

/* ACCESS MACROS */
#define MPU_INTC_REG(_x_)  *(vulong *)(MPU_INTC_BASE_ADD + _x_) // _x_ is an offset with respect to the base address

/* OMAP3 INTC registers offsets for all banks */
#define INTC_REVISION		0x0000
#define INTC_SYSCONFIG		0x0010
#define INTC_SYSSTATUS		0x0014
#define INTC_SIR_IRQ		0x0040
#define INTC_SIR_FIQ		0x0044
#define INTC_CONTROL		0x0048
#define INTC_PROTECTION		0x004C
#define INTC_IDLE			0x0050
#define INTC_IRQ_PRIORITY	0x0060
#define INTC_FIQ_PRIORITY	0x0060
#define INTC_THRESHOLD		0x0068

/* OMAP3 INTC registers offsets for bank 0 only */
#define INTC_MIR0			0x0084
#define INTC_MIR_CLEAR0		0x0088
#define INTC_MIR_SET0		0x008C
#define INTC_PENDING_IRQ0	0x0098

/* OMAP3 INTC registers offsets for bank 1 only */
#define INTC_MIR1			0x00A4
#define INTC_MIR_CLEAR1		0x00A8
#define INTC_MIR_SET1		0x00AC
#define INTC_PENDING_IRQ1	0x00B8


#endif /* INTC_H_ */
