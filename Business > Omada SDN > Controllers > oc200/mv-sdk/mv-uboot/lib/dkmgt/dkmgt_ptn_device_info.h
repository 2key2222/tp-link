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

#ifndef __DKMGT_PTN_DEVICE_INFO_H__
#define __DKMGT_PTN_DEVICE_INFO_H__

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
#define DKMGT_PTN_DEVICE_INFO_VENDOR_NAME		"vendor_name"
#define DKMGT_PTN_DEVICE_INFO_VENDOR_URL		"vendor_url"
#define DKMGT_PTN_DEVICE_INFO_PRODUCT_NAME		"product_name"
#define DKMGT_PTN_DEVICE_INFO_PRODUCT_VERSION	"product_version"
#define DKMGT_PTN_DEVICE_INFO_PRODUCT_ID		"product_id"
#define DKMGT_PTN_DEVICE_INFO_SPECIAL_ID		"special_id"
#define DKMGT_PTN_DEVICE_INFO_LANGUAGE			"language"
#define DKMGT_PTN_DEVICE_INFO_REGION			"region"
#define DKMGT_PTN_DEVICE_INFO_HW_ID				"hw_id"
#define DKMGT_PTN_DEVICE_INFO_OEM_ID			"oem_id"
#define DKMGT_PTN_DEVICE_INFO_PUBLIC_KEY		"public_key"
#define DKMGT_PTN_DEVICE_INFO_LICENSE_KEY		"license_key"

#define DKMGT_PTN_DEVICE_INFO_VENDOR_NAME_SIZE			(64)
#define DKMGT_PTN_DEVICE_INFO_VENDOR_URL_SIZE			(256)
#define DKMGT_PTN_DEVICE_INFO_PRODUCT_NAME_SIZE			(64)
#define DKMGT_PTN_DEVICE_INFO_PRODUCT_VERSION_SIZE		(16)
#define DKMGT_PTN_DEVICE_INFO_PRODUCT_ID_SIZE			(64)
#define DKMGT_PTN_DEVICE_INFO_SPECIAL_ID_SIZE			(64)
#define DKMGT_PTN_DEVICE_INFO_LANGUAGE_SIZE				(16)
#define DKMGT_PTN_DEVICE_INFO_REGION_SIZE    	        (16)
#define DKMGT_PTN_DEVICE_INFO_HW_ID_SIZE             	(64)
#define DKMGT_PTN_DEVICE_INFO_OEM_ID_SIZE             	(64)
#define DKMGT_PTN_DEVICE_INFO_PUBLIC_KEY_SIZE           (256)
#define DKMGT_PTN_DEVICE_INFO_LICENSE_KEY_SIZE          (256)

/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/

struct dkmgt_ptn_device_info {
    char vendor_name[DKMGT_PTN_DEVICE_INFO_VENDOR_NAME_SIZE];
    char vendor_url[DKMGT_PTN_DEVICE_INFO_VENDOR_URL_SIZE];
    char product_name[DKMGT_PTN_DEVICE_INFO_PRODUCT_NAME_SIZE];
    char product_version[DKMGT_PTN_DEVICE_INFO_PRODUCT_VERSION_SIZE];
    char product_id[DKMGT_PTN_DEVICE_INFO_PRODUCT_ID_SIZE];
    char special_id[DKMGT_PTN_DEVICE_INFO_SPECIAL_ID_SIZE];
    char language[DKMGT_PTN_DEVICE_INFO_LANGUAGE_SIZE];
    char region[DKMGT_PTN_DEVICE_INFO_REGION_SIZE];
    char hw_id[DKMGT_PTN_DEVICE_INFO_HW_ID_SIZE];
    char oem_id[DKMGT_PTN_DEVICE_INFO_OEM_ID_SIZE];
    char public_key[DKMGT_PTN_DEVICE_INFO_PUBLIC_KEY_SIZE];   /* not used */
    char license_key[DKMGT_PTN_DEVICE_INFO_LICENSE_KEY_SIZE]; /* not used */
};


/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                     FUNCTIONS                                                  */
/**************************************************************************************************/

struct dkmgt_ptn_device_info * dkmgt_device_info_build(struct dkmgt_ptn_table* ptn_table);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  /* __DKMGT_PTN_DEVICE_INFO_H__ */



