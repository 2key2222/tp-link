/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmgt_file.c
 *@brief    simple wapper of file operations.
 *@details  
 *
 *@author   Gan Guoheng <ganguoheng@tp-link.net>
 *@version  1.0.0
 *@date     10Nov15
 *
 *@warning  
 *
 *@history  1.0.0, 10Nov15, Gan Guoheng, Create the file.
 */

#ifndef __DKMGT_FILE_H__
#define __DKMGT_FILE_H__

/**************************************************************************************************/
/*                                       CONFIGURATIONS                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      INCLUDE_FILES                                             */
/**************************************************************************************************/


#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

/**************************************************************************************************/
/*                                      DEFINES                                                   */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                     FUNCTIONS                                                  */
/**************************************************************************************************/
int dkmgt_file_read_by_offset(const char* file_path, int offset, char *buf, int buf_size, int * read_bytes);
int dkmgt_file_write_by_offset(const char* file_path, int offset, char *buf, int buf_size, int * write_bytes);
int dkmgt_file_write_by_offset_block_mode(const char* file_path, int offset, char *buf, int buf_size, 
	int block_size, int * write_bytes);
int dkmgt_file_read_by_offset_block_mode(const char* file_path, int offset, char *buf, 	int buf_size, 
	int block_size, int * read_bytes);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  /* __DKMGT_FILE_H__ */



