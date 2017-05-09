/*
 * sd_toolbox.h
 *
 *  Created on: 18 oct. 2012
 *      Author: redsuser
 */

#ifndef SD_TOOLBOX_H_
#define SD_TOOLBOX_H_

extern int mmc1_init();
extern int mmchs_write_block(ulong *data, ulong block);
extern int mmchs_read_block(ulong *data, ulong block);
extern int mmchs_write_multiple_block(const uchar *data, ulong block, uchar nblocks);
extern int mmchs_read_multiple_block(uchar *data, ulong block, uchar nblocks);
extern int mmchs_is_card_write_protected();

extern ulong read_card_size();
extern void read_productname(uchar * name);

#endif /* SD_TOOLBOX_H_ */
