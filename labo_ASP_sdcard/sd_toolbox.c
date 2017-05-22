/*
 * sd_toolbox.c
 *
 *  Created on: 18 oct. 2012
 *      Author: Evangelina Lolivier-Exler
 */

#include "bits.h"
#include "stddefs.h"
#include "gpio_toolbox.h"
#include "padconf.h"
#include "prcm.h"
#include "mmchs.h"
#include "twl4030.h"
#include "i2c_toolbox.h"
#include <string.h>
#include <unistd.h>


vulong cid_reg[4], rca, csd_reg[4], scr_reg[2];
vulong buffer_data[1024];	// 8 512-byte blocks

int wait(int delay)
{
  int i;

  for (i = 0; i < delay; i++) ;
  return 0;
}

/**
 * \brief    Check if the card is write protected
 *
 * \return   0  if the card is not write protected
 *           1  if the card is write protected
 **/

int mmchs_is_card_write_protected()
{
	return ReadInput(GPIO_MOD5, MMC1_WP);
}

/**
 * \brief    Pass the MMC/SD command to the controller/card
 *
 * \param   cmdindx     Command index
 * \param   cmdArg      argument for the command
 *
 * \note: multiple block transfer not supported
 *
 * \return   none
 **/
void mmchs_send_command(ulong cmdindx,ulong cmdarg, uchar acmd, uchar nblocks)
{
	ulong cmd;

	// set command index
	cmd = 0;
	cmd |= cmdindx << MMCHS_CMD_INDX_SHIFT;

	// if command is read_single/multiple block or write single/multiple block or send_scr
    if (cmdindx == 17 || cmdindx == 25 || cmdindx == 18 ||cmdindx == 24 || cmdindx == 51 || (cmdindx == 6 && acmd == 0))
    {
    	// block size
    	MMCHS1_REG(MMCHS_BLK) = MMCHS_BLK_BLEN_512BYTESLEN;
    	// data present
        cmd |= (MMCHS_CMD_DP_DATA);
    	// set timeout to the max value possible
    	MMCHS1_REG(MMCHS_SYSCTL)&=~MMCHS_SYSCTL_DTO;
    	MMCHS1_REG(MMCHS_SYSCTL)|=MMCHS_SYSCTL_DTO_TCF27;

    	// multiple blocks
    	if (nblocks > 1)
    	{
        	// number of blocks
        	MMCHS1_REG(MMCHS_BLK) |= ((ulong)nblocks << MMCHS_BLK_NBLK_SHIFT);
        	// command flags: multiple blocks and block count enable
        	cmd |= (MMCHS_CMD_MSBS|MMCHS_CMD_BCE);
    	}

        // set data direction
        if (cmdindx == 17 || cmdindx == 18 || cmdindx == 51 || (cmdindx == 6 && acmd == 0))
        	cmd |= MMCHS_CMD_DDIR_READ;
    }

    switch (cmdindx)
    {
    	// R3
    	case 41:  cmd |= MMCHS_CMD_RSP_TYPE_48BITS;
		  	  	  break;
		// R1, R6, R7
    	case 3:
    	case 8:
    	case 17:
    	case 18:
    	case 23:
    	case 24:
    	case 25:
    	case 6:
    	case 13:
    	case 51:
    	case 55: cmd |= MMCHS_CMD_RSP_TYPE_48BITS;
    			  /* set index and CRC check enable */
    	    	  cmd |= (MMCHS_CMD_CICE_CHECK|MMCHS_CMD_CCCE_CHECK);
    			  break;
    	// R1b
    	case 7:
    	case 12:  cmd |= MMCHS_CMD_RSP_TYPE_48BITS_BUSY;
    			  /* set index and CRC check enable */
    	    	  cmd |= (MMCHS_CMD_CICE_CHECK|MMCHS_CMD_CCCE_CHECK);
    	    	  break;
    	// R2
    	case 2:
    	case 10:
    	case 9:  cmd |= MMCHS_CMD_RSP_TYPE_136BITS;
    			  /* set CRC check enable */
    	    	  cmd |= MMCHS_CMD_CCCE_CHECK;
	  	  	  	  break;
    }


    /* wait for the command line mmc1_cmd availability */
    while ((MMCHS1_REG(MMCHS_PSTATE) & MMCHS_PSTATE_CMDI) == MMCHS_PSTATE_CMDI_CMDDIS);

    /* Set the command/command argument */
    MMCHS1_REG(MMCHS_ARG) = cmdarg;
    MMCHS1_REG(MMCHS_CMD) = cmd;

    /* polls the CC bit of STAT waiting for the command completion */
    while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_CC)==0);

	// clear status CC bit
	MMCHS1_REG(MMCHS_STAT) = MMCHS_STAT_CC;

}

void mmc1_pad_conf()
{
	vulong PadConfVal1=0;

	/* PBIAS cells and power MIC programming */

	// power down the pins before changing the voltage (PBIAS0 cell, mmc1 pins)
	SET_REG32(CONTROL_PBIAS_LITE) &= ~PBIASLITEPWRDNZ0;
	// power down the pins before changing the voltage (PBIAS1 cell, gpio_126 et gpio_129)
	SET_REG32(CONTROL_PBIAS_LITE) &= ~PBIASLITEPWRDNZ1;
	SET_REG32(CONTROL_WKUP_CTRL) &= ~GPIO_IO_PWRDNZ;

	// set PBIAS0 VMODE to 3.0 V
	SET_REG32(CONTROL_PBIAS_LITE) |= PBIASLITEVMODE0;
	// set PBIAS1 VMODE to 1.8 V
	SET_REG32(CONTROL_PBIAS_LITE) &= ~PBIASLITEVMODE1;

	// change SIM_VDDS to 1.8 V (write PMIC registers)

	// change SDMMC1_VDDS to 3.0 V (write PMIC registers)
	twl4030_power_mmc_init();
	// wait until SDMMC1_VDDS reach 3.0 V
	wait(5000);
	// power up the pins
	SET_REG32(CONTROL_PBIAS_LITE) |= PBIASLITEPWRDNZ0;
	SET_REG32(CONTROL_PBIAS_LITE) |= PBIASLITEPWRDNZ1;
	SET_REG32(CONTROL_WKUP_CTRL)  |= GPIO_IO_PWRDNZ;
	wait(5000);
	// verify the power on the pins
	if((SET_REG32(CONTROL_PBIAS_LITE) & PBIASLITESUPPLYHIGH0) == 0)
	{
		// the power is still 1.8 V: power down pins
		SET_REG32(CONTROL_PBIAS_LITE) &= ~PBIASLITEPWRDNZ0;
		while(1);
	}

	if(SET_REG32(CONTROL_PBIAS_LITE) & PBIASLITESUPPLYHIGH1)
	{
		// the power is still 3.0 V: power down pins
		SET_REG32(CONTROL_PBIAS_LITE) &= ~PBIASLITEPWRDNZ1;
		SET_REG32(CONTROL_WKUP_CTRL) &= ~GPIO_IO_PWRDNZ;
	}





	/* System Control Module: PAD Configuration */


		PadConfVal1=0;

		PadConfVal1=	MXMode0	|PULLUDENABLE_OFF
							|PULLTYPESELECT_UP
							|INPUTENABLE_ON
							|OFFENABLE_OFF
							|OFFOUTENABLE_OUT
							|OFFOUTVALUE_LOW
							|OFFPULLUDENABLE_OFF
							|OFFPULLTYPESELECT_UP
							|WAKEUPENABLE_OFF;

		// MMC1_CLK:  enable the input buffer of the clock output
		// MMC1_CMD:  input / output (response received on these lines!)

		SET_REG32(CONTROL_PADCONF_MMC1_CLK)=PadConfVal1|(PadConfVal1<<16);

		// MMC1_DAT0 and MMC1_DAT1:  input/output, pull-ups on the REPTAR board
		SET_REG32(CONTROL_PADCONF_MMC1_DAT0)=PadConfVal1|(PadConfVal1<<16);

		// MMC1_DAT2 and MMC1_DAT3:  input/output, pull-ups on the REPTAR board
		SET_REG32(CONTROL_PADCONF_MMC1_DAT2)=PadConfVal1|(PadConfVal1<<16);

		// MMC1_WP: input, pull-up on the REPTAR board, GPIO_129
		// done in the GPIO_init() function

}

void change_frequency(ulong clkd)
{
	ulong sysctl;

	// clock disable output
	MMCHS1_REG(MMCHS_SYSCTL) &= ~MMCHS_SYSCTL_CEN;

	// clkd configuration
	sysctl = MMCHS1_REG(MMCHS_SYSCTL);
	sysctl &= ~MMCHS_SYSCTL_CLKD;
	sysctl |= clkd;
	MMCHS1_REG(MMCHS_SYSCTL) = sysctl;

	// wait for the clock stability
	while ((MMCHS1_REG(MMCHS_SYSCTL) & MMCHS_SYSCTL_ICS_READY)==0);
	// clock enable output
	MMCHS1_REG(MMCHS_SYSCTL) |= MMCHS_SYSCTL_CEN_ENABLE;

}

void mmchs1_conf()
{
	// enable the interface clock for the mmchs1 controller
	CORE_CM_REG(CM_ICLKEN)|=BIT24;
	// enable the functional clock for the mmchs1 controller
	CORE_CM_REG(CM_FCLKEN)|=BIT24;
	// software reset
	MMCHS1_REG(MMCHS_SYSCONFIG) |= MMCHS_SYSCONFIG_SOFTRESET_ONRESET;
	while ((MMCHS1_REG(MMCHS_SYSSTATUS)&MMCHS_SYSSTATUS_RESETDONE_DONE)==0);
	// reset the mmc lines
	MMCHS1_REG(MMCHS_SYSCTL) |= MMCHS_SYSCTL_SRA_RSTFORALLDESIGN;
	while ((MMCHS1_REG(MMCHS_SYSCTL) & MMCHS_SYSCTL_SRA) == MMCHS_SYSCTL_SRA_RSTFORALLDESIGN);

	// voltage capabilities initialization: only 3.0V, see REPTAR schematics
	MMCHS1_REG(MMCHS_CAPA)|= (MMCHS_CAPA_VS33_3V3_SUP);
	// SD bus voltage select
	MMCHS1_REG(MMCHS_HCTL) &= ~MMCHS_HCTL_SDVS;
	MMCHS1_REG(MMCHS_HCTL)|= MMCHS_HCTL_SDVS_3V3;
	// power on the SD bus
	MMCHS1_REG(MMCHS_HCTL)|= MMCHS_HCTL_SDBP_PWRON;
	// enable internal clock
	MMCHS1_REG(MMCHS_SYSCTL) |= MMCHS_SYSCTL_ICE_OSCILLATE;

//	// configure clock frequency: 80kHz is impossible, set 94kHz
//	change_frequency((ulong) MMCHS_SYSCTL_CLKD_DIV1023);

	// configure clock frequency: 200kHz (initialization mode) 100<f<400
	change_frequency((ulong) MMCHS_SYSCTL_CLKD_DIV480);


	// behavior of module in idle mode
	MMCHS1_REG(MMCHS_SYSCONFIG)|= MMCHS_SYSCONFIG_CLOCKACTIVITY_BOTH;
	MMCHS1_REG(MMCHS_SYSCONFIG)&=~MMCHS_SYSCONFIG_SIDLEMODE;
	MMCHS1_REG(MMCHS_SYSCONFIG)|= MMCHS_SYSCONFIG_SIDLEMODE_NOIDLE;
	MMCHS1_REG(MMCHS_SYSCONFIG)&= ~MMCHS_SYSCONFIG_ENAWAKEUP_ENABLED;
	MMCHS1_REG(MMCHS_SYSCONFIG)&= ~MMCHS_SYSCONFIG_AUTOIDLE_ON;

	// enable to set flag concerning command events in the STAT register
	MMCHS1_REG(MMCHS_IE) |= (MMCHS_IE_CTO_ENABLE|MMCHS_IE_CC_ENABLE|MMCHS_IE_CCRC_ENABLE
							|MMCHS_IE_CIE_ENABLE|MMCHS_IE_CEB_ENABLE);

	// enable to set flag concerning data events in the STAT register
	MMCHS1_REG(MMCHS_IE) |= (MMCHS_IE_DTO_ENABLE|MMCHS_IE_BRR_ENABLE|MMCHS_IE_TC_ENABLE
								|MMCHS_IE_DEB_ENABLE|MMCHS_IE_BADA_ENABLE
								|MMCHS_IE_CERR_ENABLE|MMCHS_IE_DCRC_ENABLE);


}


/**
 * \brief   This function initializes the MMCSD Card.
 *
 *
 * \returns  0 - Initialization is successful.
 *           1 - Initialization is failed.
 **/

int sdhc_init()
{
	ulong arg;
	int i;

	// send an initialization stream
	MMCHS1_REG(MMCHS_CON) |= MMCHS_CON_INIT_INITSTREAM;
	MMCHS1_REG(MMCHS_CMD)= 0x00000000;
	// wait for the end of the initialization (about 1ms)
	wait(1000);
	while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_CC)==0);
	// clear the CC flag
	MMCHS1_REG(MMCHS_STAT) = MMCHS_STAT_CC;
	// end the initialization sequence
	MMCHS1_REG(MMCHS_CON) &= ~MMCHS_CON_INIT;
	// clear STATUS register
	MMCHS1_REG(MMCHS_STAT)=0xFFFFFFFF;

//	// configure clock frequency: 200kHz (initialization mode) 100<f<400
//	change_frequency((ulong) MMCHS_SYSCTL_CLKD_DIV480);

	// send CMD0: go to idle state
	mmchs_send_command((ulong) 0,(ulong) 0, 0, 0);

	// send CMD8: send interface condition, voltage host supplied 2.7-3.6V
	arg=(ulong)(SD_VOLT_2P7_3P6|SD_CHECK_PATTERN);
	mmchs_send_command((ulong) 8, arg, 0, 0);
	// verify response (type R7), check pattern and voltage
	if (MMCHS1_REG(MMCHS_RSP10)!= arg) return 1;

	// Send CMD55 before ACMD41
	arg=0;
	mmchs_send_command((ulong) 55, arg, 0, 0);

	// send ACMD41: initialization command
	arg=(ulong)(SD_OCR_HIGH_CAPACITY|SD_OCR_VDD_WILDCARD);
	mmchs_send_command((ulong) 41, arg, 1, 0);
	// wait until initialization is completed (poll bit 31 of the response, type R3)
	while ((MMCHS1_REG(MMCHS_RSP10) & SD_OCR_CCS_BUSY)==0)
	{
	// card returns busy: re-send ACMD41
		wait(1000);
		// Send CMD55 before ACMD41
		arg=0;
		mmchs_send_command((ulong) 55, arg, 0, 0);

		// send ACMD41
		arg=(ulong)(SD_OCR_HIGH_CAPACITY|SD_OCR_VDD_WILDCARD);
		mmchs_send_command((ulong) 41, arg, 1, 0);
	}

	// verify card capacity (only High Capacity is supported)
	if ((MMCHS1_REG(MMCHS_RSP10) & SD_OCR_HIGH_CAPACITY) == 0) return 1;

	// Send CMD2, to enter in ident state
	mmchs_send_command((ulong) 2, arg, 0, 0);

	// Send CMD3, to get the card relative address (enter data transfer mode)
	mmchs_send_command((ulong) 3, arg, 0, 0);
	// Get the card address from the response (type R6)
	rca = SD_RCA_ADDR(MMCHS1_REG(MMCHS_RSP10));
	// If RCA is 0, assign a new RCA (0 is reserved for de-selection, see CMD7 description)
	if (rca==0)
	{
		// Send CMD3, to set new card relative address=0x01
		arg=(ulong)(0x01)<<16;
		mmchs_send_command((ulong) 3, arg, 0, 0);
	}
	arg=rca<<16;
	
	/////////////////////////////////////////////////
	//completer le code ici
	// get CID register
	// response (type R2) is the CID register, copy it in the global variable cid_reg
	mmchs_send_command((ulong)10, arg, 0, 0);
	cid_reg[0] = MMCHS1_REG(MMCHS_RSP10);
	cid_reg[1] = MMCHS1_REG(MMCHS_RSP32);
	cid_reg[2] = MMCHS1_REG(MMCHS_RSP54);
	cid_reg[3] = MMCHS1_REG(MMCHS_RSP76);

	
	// get CSD register
	// response (type R2) is the CSD register, copy it in the global variable csd_reg
	mmchs_send_command((ulong)9, arg, 0, 0);
	csd_reg[0] = MMCHS1_REG(MMCHS_RSP10);
	csd_reg[1] = MMCHS1_REG(MMCHS_RSP32);
	csd_reg[2] = MMCHS1_REG(MMCHS_RSP54);
	csd_reg[3] = MMCHS1_REG(MMCHS_RSP76);
    
	/////////////////////////////////////////////////

	/* switch frequency clock to 24 MHz (fpp max = 25 MHz) */

	change_frequency((ulong) MMCHS_SYSCTL_CLKD_DIV4);

	// Send CMD7: Select the card and go to transfer state
	mmchs_send_command((ulong) 7, arg, 0, 0);

	// clear STATUS register
	MMCHS1_REG(MMCHS_STAT)=0xFFFFFFFF;


	/* Send ACMD51 to get the SCR register */

	// Send CMD55 before ACMD51
	arg=rca<<16;
	mmchs_send_command((ulong) 55, arg, 0, 0);
	// send ACMD51
	mmchs_send_command((ulong) 51, arg, 1, 0);

	// wait for buffer read ready
		while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_BRR) == MMCHS_STAT_BRR_NOTREADY)
			wait(1000);
	// clear flag
		MMCHS1_REG(MMCHS_STAT) = MMCHS_STAT_BRR;
	// read first 4 bytes from the buffer
		scr_reg[1] = MMCHS1_REG(MMCHS_DATA);
		scr_reg[0] = MMCHS1_REG(MMCHS_DATA);
	// read the rest of the buffer
	for (i=0;i<126;i++)
	{
		buffer_data[i]=MMCHS1_REG(MMCHS_DATA);
	}
	// wait for transfer complete
	while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_TC) == 0)
			wait(1000);

	// clear status
	MMCHS1_REG(MMCHS_STAT) = 0XFFFFFFFF;


	// Send CMD55 before ACMD6
	arg=rca<<16;
	mmchs_send_command((ulong) 55, arg, 0, 0);

	// Send ACMD6 command to set the data bus width to 4 bits
	arg=(ulong)SD_BUS_WIDTH_4BIT;
	mmchs_send_command((ulong) 6, arg, 1, 0);
	// set data transfer width in the controller
	MMCHS1_REG(MMCHS_HCTL) |= MMCHS_HCTL_DTW_4_BITMODE;

	// send CMD6 to switch to high speed mode
	//arg = (ulong)((SD_SWITCH_MODE & SD_CMD6_GRP1_SEL) | (SD_CMD6_GRP1_HS));
	arg = (ulong)0xfffff1;
	mmchs_send_command((ulong) 6, arg, 0, 0);
	wait(1000000);

	// wait for buffer read ready
	while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_BRR) == MMCHS_STAT_BRR_NOTREADY);
	// clear flag
	MMCHS1_REG(MMCHS_STAT) = MMCHS_STAT_BRR;
	for (i=0;i<128;i++)
	{
	// read next 4 bytes from the buffer
		buffer_data[i] = MMCHS1_REG(MMCHS_DATA);
	}
	// wait for transfer complete
	while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_TC) == 0);
	// clear STAT
	MMCHS1_REG(MMCHS_STAT) = 0XFFFFFFFF;


	wait(10000);

	return 0;

}

/**
 * \brief   This function initializes the MMCSD Card.
 *
 *
 * \returns  0 - Initialization is successful.
 *           1 - Initialization is failed.
 **/
int mmc1_init()
{
	int status;

	/* configure i2c1 for interface the TPS65930 (to power the MMC controller) */
	i2c1_init();

	/* pad configuration */
	mmc1_pad_conf();

	/* MMC/SD CONTROLLER BUS CONFIGURATION */
	mmchs1_conf();

	/* card initialization: identification and selection */
	status = sdhc_init();

	return status;
}

/**
 * \brief   This function sends the write command to MMCSD card.
 *
 * \param    data          It determines the address from where data has to be read, must be an array of SD_BLOCK_LENGTH bytes
 * \param    block         It determines to which block data has to be written
 *
 * \returns  0 - successful written of data.
 *           1 - failure to write the data.
 **/
int mmchs_write_block(const vulong *data, ulong block)
{
	

	return 0;
}

/**
 * \brief   This function sends the read command to MMCSD card.
 *
 * \param    data          It determines the address to where data has to be written, must be an array of SD_BLOCK_LENGTH bytes
 * \param    block         It determines from which block data has to be read
 *
 * \returns  0 - successful written of data.
 *           1 - failure to write the data.
 **/
int mmchs_read_block(const vulong *data, ulong block)
{
	ulong arg;
	int k;
	vulong *data_ptr;

	// initialize data pointer to the destination address
	data_ptr = (vulong *) data;

	// clear STATUS register
	MMCHS1_REG(MMCHS_STAT)=0xFFFFFFFF;

	// enable to set flag concerning data events in the STAT register
	// disable buffer write flag
	MMCHS1_REG(MMCHS_IE) &= ~MMCHS_IE_BWR_ENABLE;
	// enable buffer read flag
	MMCHS1_REG(MMCHS_IE) |= MMCHS_IE_BRR_ENABLE;	

	/* wait for the data lines mmc1_dati availability */
	while ((MMCHS1_REG(MMCHS_PSTATE) & MMCHS_PSTATE_DATI) == MMCHS_PSTATE_DATI_CMDDIS);
	// Send CMD17 command: read single block
	arg=block;
	mmchs_send_command((ulong) 17, arg, 0, 1);

	// wait for buffer read ready
		while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_BRR) == MMCHS_STAT_BRR_NOTREADY);
	// clear flag
		MMCHS1_REG(MMCHS_STAT) = MMCHS_STAT_BRR;


	for (k=0;k<SD_BLOCK_LENGTH/4;k++)
	{
	// read next 4 bytes to the buffer
		*data_ptr = MMCHS1_REG(MMCHS_DATA);
		data_ptr++;
	}

	// wait for the end of the transfer
	while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_TC) == 0)
		wait(1000);
	// clear status TC bit
	MMCHS1_REG(MMCHS_STAT) = MMCHS_STAT_TC;


	return 0;
}

/**
 * \brief   This function sends the write command to MMCSD card.
 *
 * \param    data          It determines the address from where data has to be read, must be an array of SD_BLOCK_LENGTH bytes
 * \param    block         It determines to which block data has to be written
 * \param	 nblocks	   It determines the number of blocks to be written, max 8 (internal buffer size = cluster size)
 *
 * \returns  0 - successful written of data.
 *           1 - failure to write the data.
 **/
int mmchs_write_multiple_block(const uchar *data, ulong block, uchar nblocks) // TO TEST
{

	/*CMD24 adtc [31:0] data
address2 R1 WRITE_BLOCK In case of SDSC Card, block length is
set by the SET_BLOCKLEN
command1

In case of SDHC and SDXC Cards,
block length is fixed 512 Bytes
regardless of the SET_BLOCKLEN
command. 
CMD25 adtc [31:0] data
address2
R1 WRITE_MULTIPLE_B
LOCK
Continuously writes blocks of data until
a STOP_TRANSMISSION follows.
Block length is specified the same as
WRITE_BLOCK command. */
	return 0;
	
}

/**
 * \brief   This function sends the read command to MMCSD card.
 *
 * \param    data          It determines the address to where data has to be written, must be an array of SD_BLOCK_LENGTH bytes
 * \param    block         It determines from which block data has to be read
 * \param	 nblocks	   It determines the number of blocks to be read, max 8
 *
 * \returns  0 - successful written of data.
 *           1 - failure to write the data.
 **/
int mmchs_read_multiple_block(uchar *data, ulong block, uchar nblocks)
{
	/* USE COMMAND 18 Continuously transfers data blocks
from card to host until interrupted by a
STOP_TRANSMISSION command.
Block length is specified the same as
READ_SINGLE_BLOCK command. 
		OU COMMAND 6 nbocks fois READ_SINGLE_
BLOCK
In the case of a Standard Capacity SD
Memory Card, this command, this
command reads a block of the size
selected by the SET_BLOCKLEN
command. 1
In case of SDHC and SDXC Cards,
block length is fixed 512 Bytes
regardless of the SET_BLOCKLEN
command.*/
	// FAire attention : bien checker les diagrammes pour savoir quoi lire quand dans PSTAT
	// Faire ensuite attention a quelles commandes envoyer
	// SInon easy peasy lemon squizzy

ulong arg;
	int k;
	vulong *data_ptr;

	// initialize data pointer to the destination address
	data_ptr = (vulong *) data;

	// clear STATUS register
	MMCHS1_REG(MMCHS_STAT)=0xFFFFFFFF;

	// enable to set flag concerning data events in the STAT register
	// disable buffer write flag
	MMCHS1_REG(MMCHS_IE) &= ~MMCHS_IE_BWR_ENABLE;
	// enable buffer read flag
	MMCHS1_REG(MMCHS_IE) |= MMCHS_IE_BRR_ENABLE;	

	/* wait for the data lines mmc1_dati availability */
	while ((MMCHS1_REG(MMCHS_PSTATE) & MMCHS_PSTATE_DATI) == MMCHS_PSTATE_DATI_CMDDIS);
	// Send CMD17 command: read single block
	arg=block;
	mmchs_send_command((ulong) 18, arg, 0, 1);

	// wait for buffer read ready
		while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_BRR) == MMCHS_STAT_BRR_NOTREADY);
	// clear flag
		MMCHS1_REG(MMCHS_STAT) = MMCHS_STAT_BRR;


	for (k=0;k<SD_BLOCK_LENGTH*nblocks/4;k++)
	{
	// read next 4 bytes to the buffer
		*data_ptr = MMCHS1_REG(MMCHS_DATA);
		data_ptr++;
	}
	// CMD12 : STOP_TRANSMISSION, arg is stuff bits
	mmchs_send_command((ulong) 12, (ulong) 0, 0, 0);

	// wait for the end of the transfer
	while ((MMCHS1_REG(MMCHS_STAT) & MMCHS_STAT_TC) == 0) // Useless ?
		wait(1000);
	// clear status TC bit
	MMCHS1_REG(MMCHS_STAT) = MMCHS_STAT_TC;	

	return 0;
}


/**
 * \brief   This function returns card size.
 *
 *
 * \returns  card size in number of K bytes
 *
 **/
ulong read_card_size()
{
	//return card size in number of K bytes
	ulong size;

	//Completer le code 
	//CMD9 : SEND_CSD. arg[1] is card address
	mmchs_send_command((ulong) 9, rca, 0, 0);
	// C_SIZE : 22 bits [69..48]

	// Only 16 MSB are wanted
	ulong size_low = (MMCHS1_REG(MMCHS_RSP32) << 16) >> 16;

	// Only 6 LSB are wanted
	ulong size_high = (MMCHS1_REG(MMCHS_RSP54) << 26) >> 10;

	size = size_low | size_high;

	return (size + 1)*512;
}


/**
 * \brief   This function returns product name.
 *
 **/
void read_productname(uchar * name)
{

	//Modifier le code ici
	//CMD10 : SEND_CID, arg[1] is card address
	mmchs_send_command((ulong) 10, rca, 0, 0);
	
	// Product name PNM 40 [103:64] 
	// bits 95 to 64 
	int name_low 	= MMCHS1_REG(MMCHS_RSP54);
	// bits 127 to 96
	int name_high	= MMCHS1_REG(MMCHS_RSP76);

	uchar * p = (uchar*)&name_low;
	name[0]= p[0];
	name[1]= p[1];
	name[2]= p[2];
	name[3]= p[3];

	p = (uchar*)&name_high;
	name[4]= p[0];
	name[5]= '\0';
	//  MMCHS1_REG(MMCHS_RSP54) accède aux 
	// - MMCHS1_REG(MMCHS_RSP76) accède aux bits 127 à 96. 
	// Donc on veut tout RSP54 et les 8 premiers bits de RSP76

}







