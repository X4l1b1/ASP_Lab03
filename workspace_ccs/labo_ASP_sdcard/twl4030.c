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
 * twl4030_power_reset_init is derived from code on omapzoom,
 * git://git.omapzoom.com/repo/u-boot.git
 *
 * Copyright (C) 2007-2009 Texas Instruments, Inc.
 *
 * twl4030_power_init is from cpu/omap3/common.c, power_init_r
 *
 * (C) Copyright 2004-2008
 * Texas Instruments, <www.ti.com>
 *
 * Author :
 *      Sunil Kumar <sunilsaini05 at gmail.com>
 *      Shashi Ranjan <shashiranjanmca05 at gmail.com>
 *
 * Derived from Beagle Board and 3430 SDP code by
 *      Richard Woodruff <r-woodruff2 at ti.com>
 *      Syed Mohammed Khasim <khasim at ti.com>
 *
 */

#include "stddefs.h"
#include "twl4030.h"
#include "i2c_toolbox.h"

extern int wait(int delay);

///*
// * Power Reset
// */
//void twl4030_power_reset_init(void)
//{
//        ushort val = 0;
//        if (twl4030_i2c_read_ushort(TWL4030_CHIP_PM_MASTER, &val,
//                                TWL4030_PM_MASTER_P1_SW_EVENTS)) {
//                printf("Error:TWL4030: failed to read the power register\n");
//                printf("Could not initialize hardware reset\n");
//        } else {
//                val |= TWL4030_PM_MASTER_SW_EVENTS_STOPON_PWRON;
//                if (twl4030_i2c_write_ushort(TWL4030_CHIP_PM_MASTER, val,
//                                         TWL4030_PM_MASTER_P1_SW_EVENTS)) {
//                        printf("Error:TWL4030: failed to write the power register\n");
//                        printf("Could not initialize hardware reset\n");
//                }
//        }
//}

/*
 * Set Device Group and Voltage
 */
void twl4030_pmrecv_vsel_cfg(ushort vsel_reg, ushort vsel_val,
                                ushort dev_grp_reg, ushort dev_grp_val)
{
        /* Select the Voltage */
        if (i2c1_write_byte(TWL4030_CHIP_PM_RECEIVER,vsel_reg,vsel_val))
        {        	// retry
        	wait(1000);
        	i2c1_write_byte(TWL4030_CHIP_PM_RECEIVER,vsel_reg,vsel_val);
        }

        /* Select the Device Group (enable the supply if dev_grp_sel != 0) */
        if (i2c1_write_byte(TWL4030_CHIP_PM_RECEIVER,dev_grp_reg,dev_grp_val))
        {        	// retry
             wait(1000);
             i2c1_write_byte(TWL4030_CHIP_PM_RECEIVER,dev_grp_reg,dev_grp_val);
        }
}

void twl4030_power_init(void)
{
        /* set VAUX3 to 2.8V */
        twl4030_pmrecv_vsel_cfg(TWL4030_PM_RECEIVER_VAUX3_DEDICATED,
                                TWL4030_PM_RECEIVER_VAUX3_VSEL_28,
                                TWL4030_PM_RECEIVER_VAUX3_DEV_GRP,
                                TWL4030_PM_RECEIVER_DEV_GRP_P1);

        /* set VPLL2 to 1.8V */
        twl4030_pmrecv_vsel_cfg(TWL4030_PM_RECEIVER_VPLL2_DEDICATED,
                                TWL4030_PM_RECEIVER_VPLL2_VSEL_18,
                                TWL4030_PM_RECEIVER_VPLL2_DEV_GRP,
                                TWL4030_PM_RECEIVER_DEV_GRP_ALL);

        /* set VDAC to 1.8V */
        twl4030_pmrecv_vsel_cfg(TWL4030_PM_RECEIVER_VDAC_DEDICATED,
                                TWL4030_PM_RECEIVER_VDAC_VSEL_18,
                                TWL4030_PM_RECEIVER_VDAC_DEV_GRP,
                                TWL4030_PM_RECEIVER_DEV_GRP_P1);
}

void twl4030_power_mmc_init(void)
{
    	/* Set VSIM to 1.8 Volts */
    	twl4030_pmrecv_vsel_cfg(TWL4030_PM_RECEIVER_VSIM_DEDICATED,
                            TWL4030_PM_RECEIVER_VSIM_VSEL_18,
                            TWL4030_PM_RECEIVER_VSIM_DEV_GRP,
                            TWL4030_PM_RECEIVER_DEV_GRP_P1);

        /* Set VMMC1 to 3.15 Volts */
        twl4030_pmrecv_vsel_cfg(TWL4030_PM_RECEIVER_VMMC1_DEDICATED,
                                TWL4030_PM_RECEIVER_VMMC1_VSEL_32,
                                TWL4030_PM_RECEIVER_VMMC1_DEV_GRP,
                                TWL4030_PM_RECEIVER_DEV_GRP_P1);

}


