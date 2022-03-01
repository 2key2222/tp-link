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

/**************************************************************************************************/
/*                                       CONFIGURATIONS                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       INCLUDE_FILES                                            */
/**************************************************************************************************/
#include <common.h>
#include <stdlib.h>
#include <linux/ctype.h>

#include "dkmgt_common.h"
#include "dkmgt_file.h"
#include "dkmgt_ptn_device_info.h"
#include "dkmgt_ptn_header.h"

#include "thirdparty/cJSON/cJSON.h"

/**************************************************************************************************/
/*                                       DEFINES                                                  */
/**************************************************************************************************/
#define __DEVICE_INFO_ELEM(__json_root, __name, __size, __elem)	\
({\
    cJSON *json = NULL;																				\
																									\
    json = cJSON_GetObjectItem(__json_root, __name);												\
    if (NULL == json) {																				\
        DOUT_ERROR("ptn json '%s' not found.", __name);												\
        goto error;																					\
    }																								\
																									\
    if (cJSON_String != json->type) {																\
        DOUT_ERROR("ptn json 'name' must be String type.");											\
        goto error;																					\
    }																								\
																									\
    if (strlen(json->valuestring) >= __size) {														\
        DOUT_ERROR("ptn json 'name' string len too long, '%s', %d/%d", json->valuestring, 			\
                   (int)strlen(json->valuestring), __size);											\
        goto error;																					\
    }																								\
																									\
    snprintf(__elem, __size, "%s", json->valuestring);												\
})

/**************************************************************************************************/
/*                                       TYPES                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       EXTERN_PROTOTYPES                                        */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       LOCAL_PROTOTYPES                                         */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       VARIABLES                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       LOCAL_FUNCTIONS                                          */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       PUBLIC_FUNCTIONS                                         */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       GLOBAL_FUNCTIONS                                         */
/**************************************************************************************************/
#ifdef DEBUG
void _ptn_device_info_dump(struct dkmgt_ptn_device_info *devinfo)
{
    ASSERT(devinfo);

#define __PP(a)   printf("%-32s = '%s'\n", #a, devinfo->a)

	printf("#############################################################################\n");
	printf("#########            device info                            #################\n");
	printf("#############################################################################\n");
    __PP(vendor_name);
    __PP(vendor_url);
    __PP(product_name);
    __PP(product_version);
    __PP(product_id);
    __PP(special_id);
    __PP(language);
    __PP(region);
    __PP(hw_id);
    __PP(oem_id);

	printf("#############################################################################\n");
}
#endif

int _device_info_json_parse(cJSON* json_root, struct dkmgt_ptn_device_info *devinfo)
{
    ASSERT(json_root);
    ASSERT(devinfo);

    memset((void*)devinfo, 0, sizeof(struct dkmgt_ptn_device_info));

	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_VENDOR_NAME, DKMGT_PTN_DEVICE_INFO_VENDOR_NAME_SIZE, devinfo->vendor_name);
	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_VENDOR_URL, DKMGT_PTN_DEVICE_INFO_VENDOR_URL_SIZE, devinfo->vendor_url);
	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_PRODUCT_NAME, DKMGT_PTN_DEVICE_INFO_PRODUCT_NAME_SIZE, devinfo->product_name);
	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_PRODUCT_VERSION, DKMGT_PTN_DEVICE_INFO_PRODUCT_VERSION_SIZE, devinfo->product_version);
	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_PRODUCT_ID, DKMGT_PTN_DEVICE_INFO_PRODUCT_ID_SIZE, devinfo->product_id);
	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_SPECIAL_ID, DKMGT_PTN_DEVICE_INFO_SPECIAL_ID_SIZE, devinfo->special_id);
	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_LANGUAGE, DKMGT_PTN_DEVICE_INFO_LANGUAGE_SIZE, devinfo->language);
	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_REGION, DKMGT_PTN_DEVICE_INFO_REGION_SIZE, devinfo->region);
	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_HW_ID, DKMGT_PTN_DEVICE_INFO_HW_ID_SIZE, devinfo->hw_id);
	__DEVICE_INFO_ELEM(json_root, DKMGT_PTN_DEVICE_INFO_OEM_ID, DKMGT_PTN_DEVICE_INFO_OEM_ID_SIZE, devinfo->oem_id);

	return 0;

error:
    return -1;
}

int _device_info_build_by_json_data(struct dkmgt_ptn_device_info* devinfo, char* json_data, int json_len)
{
    cJSON * json = NULL;
	int ret = 0;

    json = dkmgt_parse_json_data(json_data, json_len);
    if (NULL == json) {
        DOUT_ERROR("Failed to parse json.");
		ret = -1;
        goto out;
    }

    ret = _device_info_json_parse(json, devinfo);
    if (ret < 0) {
        DOUT_ERROR("Failed to parse json -> ptn table struct.");
		ret = -1;
        goto out;
    }

out:
    if (NULL != json) {
        cJSON_Delete(json);
    }

    return ret;
}

struct dkmgt_ptn_device_info * dkmgt_device_info_build(struct dkmgt_ptn_table * ptn_table)
{
    struct dkmgt_ptn_device_info * devinfo = NULL;
	struct dkmgt_ptn_entry *ptn_entry = NULL;
	struct dkmgt_ptn_header *ptn_header = NULL;
    char* ptn_buf = NULL;
    int ptn_buf_size = 0;
    int ret = 0;
    int read_bytes = 0;

    devinfo = (struct dkmgt_ptn_device_info *)malloc(sizeof(struct dkmgt_ptn_device_info));
    if (NULL == devinfo) {
        DOUT_ERROR("failed to alloc %d bytes.\n", (int)sizeof(struct dkmgt_ptn_device_info));
        goto error;
    }

    memset(devinfo, 0, sizeof(struct dkmgt_ptn_device_info));
	
    ptn_entry = dkmgt_ptn_get_ptn_entry(ptn_table, DKMGT_PTN_DEVICE_INFO);
    if (ptn_entry == NULL) {
        DOUT_ERROR("PTN[%s] not found.", DKMGT_PTN_DEVICE_INFO);
        goto error;
    }

    ptn_buf_size = ptn_entry->size;
    ptn_buf = malloc(ptn_buf_size);
    if (NULL == ptn_buf) {
        DOUT_ERROR("alloc %d bytes failed.", ptn_buf_size);
        goto error;
    }

    memset(ptn_buf, 0, ptn_buf_size);

    ret = dkmgt_file_read_by_offset(ptn_table->ptn_layout[ptn_entry->layout].device, ptn_entry->base, ptn_buf, ptn_buf_size, &read_bytes);
    if (ret < 0) {
        DOUT_ERROR("failed to read ptn_table content.");
        goto error;
    }
	
	ptn_header = dkmgt_ptn_header_build(ptn_buf, read_bytes);
	if(NULL == ptn_header) {
		DOUT_ERROR("partition [0x%08x] is not a valid partition.", ptn_entry->base);
		goto error;
	}
	
    if (_device_info_build_by_json_data(devinfo, ptn_buf + sizeof(struct dkmgt_ptn_header), ptn_header->length) < 0)
	{
        DOUT_ERROR("Faield to parse device info of FLASH.");
        goto error;
    }

    if (NULL != ptn_buf) {
        free(ptn_buf);
    }

    if (NULL != ptn_header) {
        free(ptn_header);
    }

#ifdef DEBUG
	_ptn_device_info_dump(devinfo);
#endif

    return devinfo;

error:

    if (NULL != ptn_buf) {
        free(ptn_buf);
    }

    if (NULL != ptn_header) {
        free(ptn_header);
    }

    if (NULL != devinfo) {
        free(devinfo);
    }

    return NULL;
}

