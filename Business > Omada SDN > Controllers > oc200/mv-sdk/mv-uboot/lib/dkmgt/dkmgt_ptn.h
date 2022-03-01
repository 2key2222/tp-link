/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmgt_ptn.h
 *@brief    partition table
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

#ifndef __DKMGT_PTN_H__
#define __DKMGT_PTN_H__

/**************************************************************************************************/
/*                                       CONFIGURATIONS                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      INCLUDE_FILES                                             */
/**************************************************************************************************/
#include "thirdparty/cJSON/cJSON.h"

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

/**************************************************************************************************/
/*                                      DEFINES                                                   */
/**************************************************************************************************/
#define DKMGT_PTN_NAME_LEN              (32)
#define DKMGT_PTN_MAX_CNT               (32)
#define DKMGT_PTN_ENCAP_TYPE_LEN        (64)

#define DKMGT_PTN_BUILD_CONFIG      	"build_config"
#define DKMGT_PTN_BUILD_FOLDER       	"build_folder"
#define DKMGT_PTN_SOFTWARE_VERSION    	"software_version"
#define DKMGT_PTN_FIRMWARE_FORMAT     	"firmware_format"
#define DKMGT_PTN_PARTITION_LAYOUT_NOR  "partition-layout-nor"
#define DKMGT_PTN_PARTITION_LAYOUT_EMMC	"partition-layout-emmc"

#define DKMGT_PTN_PARTITION_TABLE     	"partitions"
#define DKMGT_PTN_FIRMWARE_INFO       	"firmware-info"
#define DKMGT_PTN_DEVICE_INFO       	"device-info"
#define DKMGT_PTN_SUPPORT_LIST       	"support-list"
#define DKMGT_PTN_DISK_SIZE           	"disk-size"
#define DKMGT_PTN_DEVICE           		"device"
#define DKMGT_PTN_NAME			        "name"
#define DKMGT_PTN_BASE       			"base"
#define DKMGT_PTN_SIZE        			"size"
#define DKMGT_PTN_WRITE_TO_FLASH        "write_to_flash"
#define DKMGT_PTN_WRITE_TO_UP	        "write_to_up"
#define DKMGT_PTN_ENCAP_TYPE        	"encap_type"

#define DKMGT_PTN_ENCAP_TYPE_HEADER		"header"
#define DKMGT_PTN_ENCAP_TYPE_GENERATE	"generate"
#define DKMGT_PTN_ENCAP_TYPE_PADDING	"padding"
#define DKMGT_PTN_ENCAP_TYPE_PARTITION	"partition"

#define DKMGT_PTN_DEVICE_MAX_LEN		(512)

/* original partition.json size */
#define DKMGT_PTN_BUFFER_SIZE    		(DKMGT_PTN_MAX_CNT*1024)

/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/
struct dkmgt_ptn_entry
{
    char        name[DKMGT_PTN_NAME_LEN];
    uint32_t    base;
    uint32_t    size;
    uint32_t	layout;
    bool        write_to_flash;
    bool        write_to_up;
    char        encap_type[DKMGT_PTN_ENCAP_TYPE_LEN];
};

enum dkmgt_ptn_layout_type
{
	DKMGT_PTN_LAYOUT_TYPE_NOR = 0,
	DKMGT_PTN_LAYOUT_TYPE_EMMC = 1,
	DKMGT_PTN_LAYOUT_TYPE_MAX = 2,
};

struct dkmgt_ptn_layout
{
    uint64_t disk_size;
    uint32_t cnt;
    char    device[DKMGT_PTN_DEVICE_MAX_LEN];
    struct dkmgt_ptn_entry ptns[DKMGT_PTN_MAX_CNT];
};

struct dkmgt_ptn_table
{
    struct dkmgt_ptn_layout   		ptn_layout[DKMGT_PTN_LAYOUT_TYPE_MAX]; /* 0 - nor, 1 - emc */
};

/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                     FUNCTIONS                                                  */
/**************************************************************************************************/
struct dkmgt_ptn_entry *dkmgt_ptn_get_ptn_entry(struct dkmgt_ptn_table * ptn_table, char* ptn_name);
struct dkmgt_ptn_table* dkmgt_ptn_table_build(char* device, uint32_t ptn_base);
void dkmgt_ptn_table_show(char* device, uint32_t ptn_base);
void dkmgt_ptn_table_dump(struct dkmgt_ptn_table * ptn_table);
char* dkmgt_ptn_entry_read(char *device, uint32_t ptn_base, char *ptn_name, int *ptn_size);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  /* __DKMGT_PTN_H__ */
