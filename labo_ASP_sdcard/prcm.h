/*
 * prcm.h
 *
 *  Created on: 24 mai 2012
 *  Author: Evangelina Lolivier-Exler
 *  Register definitions for the DM3730 microcontroller
 *  Power Reset and Clock Management (PRCM)
 *
 */

#ifndef PRCM_H_
#define PRCM_H_

/* CLOCK CONFIGURATION (PRCM MODULE) */

/* BASE ADDRESSES */
#define CORE_CM_BASE_ADD	0x48004A00
#define WKUP_CM_BASE_ADD	0x48004C00
#define PER_CM_BASE_ADD		0x48005000
#define DSS_CM_BASE_ADD		0x48004E00

/* ACCESS MACROS */
#define CORE_CM_REG(_x_)  *(vulong *)(CORE_CM_BASE_ADD + _x_) // _x_ is an offset with respect to the base address
#define WKUP_CM_REG(_x_)  *(vulong *)(WKUP_CM_BASE_ADD + _x_)
#define PER_CM_REG(_x_)  *(vulong *)(PER_CM_BASE_ADD + _x_)
#define DSS_CM_REG(_x_)  *(vulong *)(DSS_CM_BASE_ADD + _x_)

/* OMAP3 PRCM registers offsets */
#define CM_FCLKEN		0x0000		// for CORE_CM that's the FCLKEN1
#define CM_ICLKEN		0x0010		// for CORE_CM that's the ICLKEN1
#define CM_CLKSEL		0x0040

#define PER_M4X2		2	/* 432MHz: CM_CLKSEL_DSS-dss1 */
#define DDS1_FIELD_MSK	0x0000003F



#endif /* PRCM_H_ */
