/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmgt_ptn_device_info.c
 *@brief    build & parse PTN[device-info]
 *@details  
 *
 *@author   Gan Guoheng <ganguoheng@tp-link.net>
 *@version  1.0.0
 *@date     16Jan16
 *
 *@warning  
 *
 *@history  1.0.0, 16Jan16, Gan Guoheng, Create the file.
 */

#ifndef __DKMGT_PTN_SUPPORT_LIST_H__
#define __DKMGT_PTN_SUPPORT_LIST_H__

/**************************************************************************************************/
/*                                       CONFIGURATIONS                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      INCLUDE_FILES                                             */
/**************************************************************************************************/
#include "thirdparty/cJSON/cJSON.h"
#include "dkmgt_ptn.h"
#include "dkmgt_ptn_device_info.h"
#include "dkmgt_firmware.h"

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

/**************************************************************************************************/
/*                                      DEFINES                                                   */
/**************************************************************************************************/
#define	DKMGT_PTN_SUPPORT_LIST_MAX_CNT		(64)

/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/
struct dkmgt_ptn_support_list_entry {
	char product_name[DKMGT_PTN_DEVICE_INFO_PRODUCT_NAME_SIZE];
	char product_version[DKMGT_PTN_DEVICE_INFO_PRODUCT_VERSION_SIZE];
	char special_id[DKMGT_PTN_DEVICE_INFO_SPECIAL_ID_SIZE];
};
struct dkmgt_ptn_support_list {
	int		cnt;
	struct  dkmgt_ptn_support_list_entry entry[DKMGT_PTN_SUPPORT_LIST_MAX_CNT];
};


/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                     FUNCTIONS                                                  */
/**************************************************************************************************/
struct dkmgt_ptn_support_list * dkmgt_support_list_build(
	struct dkmgt_firmware_ptn_table * firmware_ptn_table, char* firmware_buf);

int dkmgt_support_list_check(struct dkmgt_ptn_device_info * flash_devinfo, 
	struct dkmgt_ptn_support_list * support_list);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  /* __DKMGT_PTN_SUPPORT_LIST_H__ */



