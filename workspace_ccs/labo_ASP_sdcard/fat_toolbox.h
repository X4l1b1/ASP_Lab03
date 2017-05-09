/*
 * fat_toolbox.h
 *
 *  Created on: 12 nov. 2012
 *      Author: Evangelina Lolivier-Exler
 */

#ifndef FAT_TOOLBOX_H_
#define FAT_TOOLBOX_H_

/* 1 cluster = 8 blocks of 512 B */
#define CLUSTER_SIZE	4096
/* max file size : 10 clusters */
#define MAX_FILE_SIZE 40960

extern int create_file(char *file_name,uchar *data,ulong nbyte);
extern void fill_array(uchar *data, ulong nbyte);
extern void scan_files (char* path);
extern int read_file(char *file_name);
extern int print_file_info(char *file_name);
extern int run_app(char *file_name);

#endif /* FAT_TOOLBOX_H_ */
