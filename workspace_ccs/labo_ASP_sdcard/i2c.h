/*
 * i2c.h
 *
 *  Created on: 23 oct. 2012
 *  Author: Evangelina Lolivier-Exler
 *  Register definitions for the DM3730 microcontroller
 *  Multimaster High-Speed I2C Controller
 */

#ifndef I2C_H_
#define I2C_H_

/* BASE ADDRESS */
#define I2C1_BASE_ADD		0x48070000
#define I2C2_BASE_ADD		0x48072000
#define I2C3_BASE_ADD		0x48060000


/* ACCESS MACROS */

/* CAUTION: the i2c registers are limited to 16-bit accesses */

#define I2C1_REG(_x_)  *(vushort *)(I2C1_BASE_ADD + _x_) // _x_ is an offset with respect to the base address
#define I2C2_REG(_x_)  *(vushort *)(I2C2_BASE_ADD + _x_)
#define I2C3_REG(_x_)  *(vushort *)(I2C3_BASE_ADD + _x_)

/* OMAP3 I2C registers offsets */
#define I2C_STAT		0x0008
#define I2C_SYSS		0x0010
#define I2C_BUF			0x0014
#define I2C_CNT			0x0018
#define I2C_DATA		0x001C
#define I2C_SYSC		0x0020
#define I2C_CON			0x0024
#define I2C_SA			0x002C
#define I2C_PSC			0x0030
#define I2C_SCLL		0x0034
#define I2C_SCLH		0x0038

/* I2C masks */

/* I2C System Status Register (I2C_SYSS): */

#define I2C_SYSS_RDONE          (1 << 0)  /* Internal reset monitoring */

/* I2C Status Register (I2C_STAT): */

#define I2C_STAT_XDR	(1 << 14) /* Transmit draining */
#define I2C_STAT_BB		(1 << 12) /* Bus busy */
#define I2C_STAT_ROVR	(1 << 11) /* Receive overrun */
#define I2C_STAT_XUDF	(1 << 10) /* Transmit underflow */
#define I2C_STAT_AAS	(1 << 9)  /* Address as slave */
#define I2C_STAT_GC		(1 << 5)  /* General call */
#define I2C_STAT_XRDY	(1 << 4)  /* Transmit data ready */
#define I2C_STAT_RRDY	(1 << 3)  /* Receive data ready */
#define I2C_STAT_ARDY	(1 << 2)  /* Register access ready */
#define I2C_STAT_NACK	(1 << 1)  /* No acknowledgment interrupt enable */
#define I2C_STAT_AL		(1 << 0)  /* Arbitration lost interrupt enable */

/* I2C Configuration Register (I2C_CON): */

#define I2C_CON_EN		(1 << 15)  /* I2C module enable */
#define I2C_CON_BE		(1 << 14)  /* Big endian mode */
#define I2C_CON_STB		(1 << 11)  /* Start byte mode (master mode only) */
#define I2C_CON_MST		(1 << 10)  /* Master/slave mode */
#define I2C_CON_TRX		(1 << 9)   /* Transmitter/receiver mode */
				   /* (master mode only) */
#define I2C_CON_XA		(1 << 8)   /* Expand address */
#define I2C_CON_STP		(1 << 1)   /* Stop condition (master mode only) */
#define I2C_CON_STT		(1 << 0)   /* Start condition (master mode only) */

/* SYSC */
#define I2C_SYSC_AUTOIDLE   (0x0001u)
#define I2C_SYSC_AUTOIDLE_SHIFT   (0x0000u)
#define I2C_SYSC_AUTOIDLE_OFF   (0x0u)
#define I2C_SYSC_AUTOIDLE_ON   (0x1u << I2C_SYSC_AUTOIDLE_SHIFT)
             
#define I2C_SYSC_CLOCKACTIVITY   (0x0300u)
#define I2C_SYSC_CLOCKACTIVITY_SHIFT   (0x0008u)
#define I2C_SYSC_CLOCKACTIVITY_BOTH   (0x3u << I2C_SYSC_CLOCKACTIVITY_SHIFT)
#define I2C_SYSC_CLOCKACTIVITY_FUNC   (0x2u << I2C_SYSC_CLOCKACTIVITY_SHIFT)
#define I2C_SYSC_CLOCKACTIVITY_NONE   (0x0u)           
#define I2C_SYSC_CLOCKACTIVITY_IFCE   (0x1u << I2C_SYSC_CLOCKACTIVITY_SHIFT)
             
#define I2C_SYSC_ENAWAKEUP   (0x0004u)
#define I2C_SYSC_ENAWAKEUP_SHIFT   (0x00000002u)
#define I2C_SYSC_ENAWAKEUP_DISABLED   	(0x0u)
#define I2C_SYSC_ENAWAKEUP_ENABLED   	(0x1u << I2C_SYSC_ENAWAKEUP_SHIFT)
            
#define I2C_SYSC_IDLEMODE   (0x0018u)
#define I2C_SYSC_IDLEMODE_SHIFT   (0x0003u)
#define I2C_SYSC_IDLEMODE_FORCE   (0x0u)
#define I2C_SYSC_IDLEMODE_NOIDLE  (0x1u << I2C_SYSC_IDLEMODE_SHIFT)
#define I2C_SYSC_IDLEMODE_SMART   (0x2u << I2C_SYSC_IDLEMODE_SHIFT)
            
#define I2C_SYSC_SOFTRESET   (0x0002u)
#define I2C_SYSC_SOFTRESET_SHIFT   (0x0001u)
#define I2C_SYSC_SOFTRESET_NORESET   (0x0u)
#define I2C_SYSC_SOFTRESET_ONRESET   (0x1u << I2C_SYSC_SOFTRESET_SHIFT)

/* I2C Buffer Configuration Register (I2C_BUF): */

#define I2C_BUF_XTRSH			(0x003Fu)
#define I2C_BUF_RTRSH			(0x3F00u)
#define I2C_BUF_RTRSH_SHIFT		(0x0008u)
#define TXFIFO_CLR				(1 << 6)






#endif /* I2C_H_ */
