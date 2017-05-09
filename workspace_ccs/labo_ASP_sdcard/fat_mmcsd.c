
#include "diskio.h"
#include "stddefs.h"
#include "i2c_toolbox.h"
#include "sd_toolbox.h"
#include "ff.h"



typedef struct _fatDevice
{
    /* Pointer to underlying device/controller */
    void *dev;
    
    /* File system pointer */
    FATFS *fs;

	/* state */
	unsigned int initDone;

}fatDevice;


#define DRIVE_NUM_MMCSD     0
#define DRIVE_NUM_MAX      	 1


fatDevice fat_devices[DRIVE_NUM_MAX];


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS
disk_initialize(
    BYTE bValue)                /* Physical drive number (0) */
{
   
    if (DRIVE_NUM_MAX <= bValue)
    {
        return STA_NODISK;
    }
    
    if ((DRIVE_NUM_MMCSD == bValue) && (fat_devices[bValue].initDone != 1))
    {

        /* SD Card init */
    	i2c1_init();

        if (mmc1_init())
        {
           return STA_NOINIT;
        }
        else
		fat_devices[bValue].initDone = 1;
    }
        
    return 0;
}



/*-----------------------------------------------------------------------*/
/* Returns the current status of a drive                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
    BYTE drv)                   /* Physical drive number (0) */
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* This function reads sector(s) from the disk drive                     */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE drv,               /* Physical drive number (0) */
    BYTE* buff,             /* Pointer to the data buffer to store read data */
    DWORD sector,           /* Physical drive number (0) */
    BYTE count)             /* Sector count (1..255) */
{
	if (drv == DRIVE_NUM_MMCSD)
	{
    	/* READ BLOCK */
		if(mmchs_read_multiple_block(buff, sector, count))
		{
			return RES_ERROR;
		}
		else
			return RES_OK;

    }

	return RES_ERROR;
}



/*-----------------------------------------------------------------------*/
/* This function writes sector(s) to the disk drive                     */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
DRESULT disk_write (
    BYTE ucDrive,           /* Physical drive number (0) */
    const BYTE* buff,       /* Pointer to the data to be written */
    DWORD sector,           /* Start sector number (LBA) */
    BYTE count)             /* Sector count (1..255) */
{
	if (ucDrive == DRIVE_NUM_MMCSD)
	{
    	/* WRITE BLOCK */
		if (mmchs_write_multiple_block(buff, (ulong) sector, (uchar) count))
	    {
        	return RES_ERROR;
		}
		else
			return RES_OK;
	}

    return RES_ERROR;
}
#endif /* _READONLY */

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE drv,               /* Physical drive number (0) */
    BYTE ctrl,              /* Control code */
    void *buff)             /* Buffer to send/receive control data */
{

	return RES_OK;
}

/*---------------------------------------------------------*/
/* User Provided Timer Function for FatFs module           */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support a real time clock.          */

DWORD get_fattime (void)
{
    return    ((2007UL-1980) << 25) // Year = 2007
            | (6UL << 21)           // Month = June
            | (5UL << 16)           // Day = 5
            | (11U << 11)           // Hour = 11
            | (38U << 5)            // Min = 38
            | (0U >> 1)             // Sec = 0
            ;
}
