/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 * Tom Rix <Tom.Rix at windriver.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Derived from code on omapzoom, git://git.omapzoom.com/repo/u-boot.git
 *
 * Copyright (C) 2007-2009 Texas Instruments, Inc.
 * Modified 24/10/2012 by Evangelina Lolivier-Exler: adapted to use our i2c functions
 */

#ifndef TWL4030_H
#define TWL4030_H



/* I2C chip addresses */

/* POWER */
#define TWL4030_CHIP_BACKUP				0x4b
#define TWL4030_CHIP_INT				0x4b
#define TWL4030_CHIP_PM_MASTER				0x4b
#define TWL4030_CHIP_PM_RECEIVER			0x4b
#define TWL4030_CHIP_RTC				0x4b
#define TWL4030_CHIP_SECURED_REG			0x4b


/*
 * Power Management Master (physical addresses)
 */
#define TWL4030_PM_MASTER_CFG_P1_TRANSITION		0x36
#define TWL4030_PM_MASTER_CFG_P2_TRANSITION		0x37
#define TWL4030_PM_MASTER_CFG_P3_TRANSITION		0x38
#define TWL4030_PM_MASTER_CFG_P123_TRANSITION		0x39
#define TWL4030_PM_MASTER_STS_BOOT			0x3A
#define TWL4030_PM_MASTER_CFG_BOOT			0x3B
#define TWL4030_PM_MASTER_SHUNDAN			0x3C
#define TWL4030_PM_MASTER_BOOT_BCI			0x3D
#define TWL4030_PM_MASTER_CFG_PWRANA1			0x3E
#define TWL4030_PM_MASTER_CFG_PWRANA2			0x3F
#define TWL4030_PM_MASTER_BGAP_TRIM			0x40
#define TWL4030_PM_MASTER_BACKUP_MISC_STS		0x41
#define TWL4030_PM_MASTER_BACKUP_MISC_CFG		0x42
#define TWL4030_PM_MASTER_BACKUP_MISC_TST		0x43
#define TWL4030_PM_MASTER_PROTECT_KEY			0x44
#define TWL4030_PM_MASTER_STS_HW_CONDITIONS		0x45
#define TWL4030_PM_MASTER_P1_SW_EVENTS			0x46
#define TWL4030_PM_MASTER_P2_SW_EVENTS			0x47
#define TWL4030_PM_MASTER_P3_SW_EVENTS			0x48
#define TWL4030_PM_MASTER_STS_P123_STATE		0x49
#define TWL4030_PM_MASTER_PB_CFG			0x4A
#define TWL4030_PM_MASTER_PB_WORD_MSB			0x4B
#define TWL4030_PM_MASTER_PB_WORD_LSB			0x4C
#define TWL4030_PM_MASTER_SEQ_ADD_W2P			0x52
#define TWL4030_PM_MASTER_SEQ_ADD_P2A			0x53
#define TWL4030_PM_MASTER_SEQ_ADD_A2W			0x54
#define TWL4030_PM_MASTER_SEQ_ADD_A2S			0x55
#define TWL4030_PM_MASTER_SEQ_ADD_S2A12			0x56
#define TWL4030_PM_MASTER_SEQ_ADD_S2A3			0x57
#define TWL4030_PM_MASTER_SEQ_ADD_WARM			0x58
#define TWL4030_PM_MASTER_MEMORY_ADDRESS		0x59
#define TWL4030_PM_MASTER_MEMORY_DATA			0x5A
#define TWL4030_PM_MASTER_SC_CONFIG			0x5B
#define TWL4030_PM_MASTER_SC_DETECT1			0x5C
#define TWL4030_PM_MASTER_SC_DETECT2			0x5D
#define TWL4030_PM_MASTER_WATCHDOG_CFG			0x5E
#define TWL4030_PM_MASTER_IT_CHECK_CFG			0x5F
#define TWL4030_PM_MASTER_VIBRATOR_CFG			0x60
#define TWL4030_PM_MASTER_DCDC_GLOBAL_CFG		0x61
#define TWL4030_PM_MASTER_VDD1_TRIM1			0x62
#define TWL4030_PM_MASTER_VDD1_TRIM2			0x63
#define TWL4030_PM_MASTER_VDD2_TRIM1			0x64
#define TWL4030_PM_MASTER_VDD2_TRIM2			0x65
#define TWL4030_PM_MASTER_VIO_TRIM1			0x66
#define TWL4030_PM_MASTER_VIO_TRIM2			0x67
#define TWL4030_PM_MASTER_MISC_CFG			0x68
#define TWL4030_PM_MASTER_LS_TST_A			0x69
#define TWL4030_PM_MASTER_LS_TST_B			0x6A
#define TWL4030_PM_MASTER_LS_TST_C			0x6B
#define TWL4030_PM_MASTER_LS_TST_D			0x6C
#define TWL4030_PM_MASTER_BB_CFG			0x6D
#define TWL4030_PM_MASTER_MISC_TST			0x6E
#define TWL4030_PM_MASTER_TRIM1				0x6F
/* P[1-3]_SW_EVENTS */
#define TWL4030_PM_MASTER_SW_EVENTS_STOPON_PWRON	(1 << 6)
#define TWL4030_PM_MASTER_SW_EVENTS_STOPON_SYSEN	(1 << 5)
#define TWL4030_PM_MASTER_SW_EVENTS_ENABLE_WARMRESET	(1 << 4)
#define TWL4030_PM_MASTER_SW_EVENTS_LVL_WAKEUP		(1 << 3)
#define TWL4030_PM_MASTER_SW_EVENTS_DEVACT		(1 << 2)
#define TWL4030_PM_MASTER_SW_EVENTS_DEVSLP		(1 << 1)
#define TWL4030_PM_MASTER_SW_EVENTS_DEVOFF		(1 << 0)

/* Power Management Receiver (physical addresses) */
#define TWL4030_PM_RECEIVER_SC_CONFIG			0x5B
#define TWL4030_PM_RECEIVER_SC_DETECT1			0x5C
#define TWL4030_PM_RECEIVER_SC_DETECT2			0x5D
#define TWL4030_PM_RECEIVER_WATCHDOG_CFG		0x5E
#define TWL4030_PM_RECEIVER_IT_CHECK_CFG		0x5F
#define TWL4030_PM_RECEIVER_VIBRATOR_CFG		0x5F
#define TWL4030_PM_RECEIVER_DC_TO_DC_CFG		0x61
#define TWL4030_PM_RECEIVER_VDD1_TRIM1			0x62
#define TWL4030_PM_RECEIVER_VDD1_TRIM2			0x63
#define TWL4030_PM_RECEIVER_VDD2_TRIM1			0x64
#define TWL4030_PM_RECEIVER_VDD2_TRIM2			0x65
#define TWL4030_PM_RECEIVER_VIO_TRIM1			0x66
#define TWL4030_PM_RECEIVER_VIO_TRIM2			0x67
#define TWL4030_PM_RECEIVER_MISC_CFG			0x68
#define TWL4030_PM_RECEIVER_LS_TST_A			0x69
#define TWL4030_PM_RECEIVER_LS_TST_B			0x6A
#define TWL4030_PM_RECEIVER_LS_TST_C			0x6B
#define TWL4030_PM_RECEIVER_LS_TST_D			0x6C
#define TWL4030_PM_RECEIVER_BB_CFG			0x6D
#define TWL4030_PM_RECEIVER_MISC_TST			0x6E
#define TWL4030_PM_RECEIVER_TRIM1			0x6F
#define TWL4030_PM_RECEIVER_TRIM2			0x70
#define TWL4030_PM_RECEIVER_DC_DC_TIMEOUT		0x71
#define TWL4030_PM_RECEIVER_VAUX1_DEV_GRP		0x72
#define TWL4030_PM_RECEIVER_VAUX1_TYPE			0x73
#define TWL4030_PM_RECEIVER_VAUX1_REMAP			0x74
#define TWL4030_PM_RECEIVER_VAUX1_DEDICATED		0x75
#define TWL4030_PM_RECEIVER_VAUX2_DEV_GRP		0x76
#define TWL4030_PM_RECEIVER_VAUX2_TYPE			0x77
#define TWL4030_PM_RECEIVER_VAUX2_REMAP			0x78
#define TWL4030_PM_RECEIVER_VAUX2_DEDICATED		0x79
#define TWL4030_PM_RECEIVER_VAUX3_DEV_GRP		0x7A
#define TWL4030_PM_RECEIVER_VAUX3_TYPE			0x7B
#define TWL4030_PM_RECEIVER_VAUX3_REMAP			0x7C
#define TWL4030_PM_RECEIVER_VAUX3_DEDICATED		0x7D
#define TWL4030_PM_RECEIVER_VAUX4_DEV_GRP		0x7E
#define TWL4030_PM_RECEIVER_VAUX4_TYPE			0x7F
#define TWL4030_PM_RECEIVER_VAUX4_REMAP			0x80
#define TWL4030_PM_RECEIVER_VAUX4_DEDICATED		0x81
#define TWL4030_PM_RECEIVER_VMMC1_DEV_GRP		0x82
#define TWL4030_PM_RECEIVER_VMMC1_TYPE			0x83
#define TWL4030_PM_RECEIVER_VMMC1_REMAP			0x84
#define TWL4030_PM_RECEIVER_VMMC1_DEDICATED		0x85
#define TWL4030_PM_RECEIVER_VMMC2_DEV_GRP		0x86
#define TWL4030_PM_RECEIVER_VMMC2_TYPE			0x87
#define TWL4030_PM_RECEIVER_VMMC2_REMAP			0x88
#define TWL4030_PM_RECEIVER_VMMC2_DEDICATED		0x89
#define TWL4030_PM_RECEIVER_VPLL1_DEV_GRP		0x8A
#define TWL4030_PM_RECEIVER_VPLL1_TYPE			0x8B
#define TWL4030_PM_RECEIVER_VPLL1_REMAP			0x8C
#define TWL4030_PM_RECEIVER_VPLL1_DEDICATED		0x8D
#define TWL4030_PM_RECEIVER_VPLL2_DEV_GRP		0x8E
#define TWL4030_PM_RECEIVER_VPLL2_TYPE			0x8F
#define TWL4030_PM_RECEIVER_VPLL2_REMAP			0x90
#define TWL4030_PM_RECEIVER_VPLL2_DEDICATED		0x91
#define TWL4030_PM_RECEIVER_VSIM_DEV_GRP		0x92
#define TWL4030_PM_RECEIVER_VSIM_TYPE			0x93
#define TWL4030_PM_RECEIVER_VSIM_REMAP			0x94
#define TWL4030_PM_RECEIVER_VSIM_DEDICATED		0x95
#define TWL4030_PM_RECEIVER_VDAC_DEV_GRP		0x96
#define TWL4030_PM_RECEIVER_VDAC_TYPE			0x97
#define TWL4030_PM_RECEIVER_VDAC_REMAP			0x98
#define TWL4030_PM_RECEIVER_VDAC_DEDICATED		0x99
#define TWL4030_PM_RECEIVER_VINTANA1_DEV_GRP		0x9A
#define TWL4030_PM_RECEIVER_VINTANA1_TYP		0x9B
#define TWL4030_PM_RECEIVER_VINTANA1_REMAP		0x9C
#define TWL4030_PM_RECEIVER_VINTANA1_DEDICATED		0x9D
#define TWL4030_PM_RECEIVER_VINTANA2_DEV_GRP		0x9E
#define TWL4030_PM_RECEIVER_VINTANA2_TYPE		0x9F
#define TWL4030_PM_RECEIVER_VINTANA2_REMAP		0xA0
#define TWL4030_PM_RECEIVER_VINTANA2_DEDICATED		0xA1
#define TWL4030_PM_RECEIVER_VINTDIG_DEV_GRP		0xA2
#define TWL4030_PM_RECEIVER_VINTDIG_TYPE		0xA3
#define TWL4030_PM_RECEIVER_VINTDIG_REMAP		0xA4
#define TWL4030_PM_RECEIVER_VINTDIG_DEDICATED		0xA5
#define TWL4030_PM_RECEIVER_VIO_DEV_GRP			0xA6
#define TWL4030_PM_RECEIVER_VIO_TYPE			0xA7
#define TWL4030_PM_RECEIVER_VIO_REMAP			0xA8
#define TWL4030_PM_RECEIVER_VIO_CFG			0xA9
#define TWL4030_PM_RECEIVER_VIO_MISC_CFG		0xAA
#define TWL4030_PM_RECEIVER_VIO_TEST1			0xAB
#define TWL4030_PM_RECEIVER_VIO_TEST2			0xAC
#define TWL4030_PM_RECEIVER_VIO_OSC			0xAD
#define TWL4030_PM_RECEIVER_VIO_RESERVED		0xAE
#define TWL4030_PM_RECEIVER_VIO_VSEL			0xAF
#define TWL4030_PM_RECEIVER_VDD1_DEV_GRP		0xB0
#define TWL4030_PM_RECEIVER_VDD1_TYPE			0xB1
#define TWL4030_PM_RECEIVER_VDD1_REMAP			0xB2
#define TWL4030_PM_RECEIVER_VDD1_CFG			0xB3
#define TWL4030_PM_RECEIVER_VDD1_MISC_CFG		0xB4
#define TWL4030_PM_RECEIVER_VDD1_TEST1			0xB5
#define TWL4030_PM_RECEIVER_VDD1_TEST2			0xB6
#define TWL4030_PM_RECEIVER_VDD1_OSC			0xB7
#define TWL4030_PM_RECEIVER_VDD1_RESERVED		0xB8
#define TWL4030_PM_RECEIVER_VDD1_VSEL			0xB9
#define TWL4030_PM_RECEIVER_VDD1_VMODE_CFG		0xBA
#define TWL4030_PM_RECEIVER_VDD1_VFLOOR			0xBB
#define TWL4030_PM_RECEIVER_VDD1_VROOF			0xBC
#define TWL4030_PM_RECEIVER_VDD1_STEP			0xBD
#define TWL4030_PM_RECEIVER_VDD2_DEV_GRP		0xBE
#define TWL4030_PM_RECEIVER_VDD2_TYPE			0xBF
#define TWL4030_PM_RECEIVER_VDD2_REMAP			0xC0
#define TWL4030_PM_RECEIVER_VDD2_CFG			0xC1
#define TWL4030_PM_RECEIVER_VDD2_MISC_CFG		0xC2
#define TWL4030_PM_RECEIVER_VDD2_TEST1			0xC3
#define TWL4030_PM_RECEIVER_VDD2_TEST2			0xC4
#define TWL4030_PM_RECEIVER_VDD2_OSC			0xC5
#define TWL4030_PM_RECEIVER_VDD2_RESERVED		0xC6
#define TWL4030_PM_RECEIVER_VDD2_VSEL			0xC7
#define TWL4030_PM_RECEIVER_VDD2_VMODE_CFG		0xC8
#define TWL4030_PM_RECEIVER_VDD2_VFLOOR			0xC9
#define TWL4030_PM_RECEIVER_VDD2_VROOF			0xCA
#define TWL4030_PM_RECEIVER_VDD2_STEP			0xCB
#define TWL4030_PM_RECEIVER_VUSB1V5_DEV_GRP		0xCC
#define TWL4030_PM_RECEIVER_VUSB1V5_TYPE		0xCD
#define TWL4030_PM_RECEIVER_VUSB1V5_REMAP		0xCE
#define TWL4030_PM_RECEIVER_VUSB1V8_DEV_GRP		0xCF
#define TWL4030_PM_RECEIVER_VUSB1V8_TYPE		0xD0
#define TWL4030_PM_RECEIVER_VUSB1V8_REMAP		0xD1
#define TWL4030_PM_RECEIVER_VUSB3V1_DEV_GRP		0xD2
#define TWL4030_PM_RECEIVER_VUSB3V1_TYPE		0xD3
#define TWL4030_PM_RECEIVER_VUSB3V1_REMAP		0xD4
#define TWL4030_PM_RECEIVER_VUSBCP_DEV_GRP		0xD5
#define TWL4030_PM_RECEIVER_VUSBCP_TYPE			0xD6
#define TWL4030_PM_RECEIVER_VUSBCP_REMAP		0xD7
#define TWL4030_PM_RECEIVER_VUSB_DEDICATED1		0xD8
#define TWL4030_PM_RECEIVER_VUSB_DEDICATED2		0xD9
#define TWL4030_PM_RECEIVER_REGEN_DEV_GRP		0xDA
#define TWL4030_PM_RECEIVER_REGEN_TYPE			0xDB
#define TWL4030_PM_RECEIVER_REGEN_REMAP			0xDC
#define TWL4030_PM_RECEIVER_NRESPWRON_DEV_GRP		0xDD
#define TWL4030_PM_RECEIVER_NRESPWRON_TYPE		0xDE
#define TWL4030_PM_RECEIVER_NRESPWRON_REMAP		0xDF
#define TWL4030_PM_RECEIVER_CLKEN_DEV_GRP		0xE0
#define TWL4030_PM_RECEIVER_CLKEN_TYPE			0xE1
#define TWL4030_PM_RECEIVER_CLKEN_REMAP			0xE2
#define TWL4030_PM_RECEIVER_SYSEN_DEV_GRP		0xE3
#define TWL4030_PM_RECEIVER_SYSEN_TYPE			0xE4
#define TWL4030_PM_RECEIVER_SYSEN_REMAP			0xE5
#define TWL4030_PM_RECEIVER_HFCLKOUT_DEV_GRP		0xE6
#define TWL4030_PM_RECEIVER_HFCLKOUT_TYPE		0xE7
#define TWL4030_PM_RECEIVER_HFCLKOUT_REMAP		0xE8
#define TWL4030_PM_RECEIVER_32KCLKOUT_DEV_GRP		0xE9
#define TWL4030_PM_RECEIVER_32KCLKOUT_TYPE		0xEA
#define TWL4030_PM_RECEIVER_32KCLKOUT_REMAP		0xEB
#define TWL4030_PM_RECEIVER_TRITON_RESET_DEV_GRP	0xEC
#define TWL4030_PM_RECEIVER_TRITON_RESET_TYPE		0xED
#define TWL4030_PM_RECEIVER_TRITON_RESET_REMAP		0xEE
#define TWL4030_PM_RECEIVER_MAINREF_DEV_GRP		0xEF
#define TWL4030_PM_RECEIVER_MAINREF_TYPE		0xF0
#define TWL4030_PM_RECEIVER_MAINREF_REMAP		0xF1

/* Voltage Selection in PM Receiver Module */
#define TWL4030_PM_RECEIVER_VAUX2_VSEL_18		0x05
#define TWL4030_PM_RECEIVER_VAUX3_VSEL_28		0x03
#define TWL4030_PM_RECEIVER_VPLL2_VSEL_18		0x05
#define TWL4030_PM_RECEIVER_VDAC_VSEL_18		0x03
#define TWL4030_PM_RECEIVER_VMMC1_VSEL_30		0x02
#define TWL4030_PM_RECEIVER_VMMC1_VSEL_32		0x03
#define TWL4030_PM_RECEIVER_VSIM_VSEL_18		0x03

/* Device Selection in PM Receiver Module */
#define TWL4030_PM_RECEIVER_DEV_GRP_P1			0x20
#define TWL4030_PM_RECEIVER_DEV_GRP_ALL			0xE0


/*
 * Power
 */

/* For hardware resetting */
void twl4030_power_reset_init(void);
/* For setting device group and voltage */
void twl4030_pmrecv_vsel_cfg(ushort vsel_reg, ushort vsel_val, ushort dev_grp, ushort dev_grp_sel);
/* For initializing power device */
void twl4030_power_init(void);
/* For initializing mmc power */
void twl4030_power_mmc_init(void);


#endif /* TWL4030_H */
