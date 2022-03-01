/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmgt_ptn_support_list.c
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
#include "dkmgt_ptn.h"
#include "dkmgt_ptn_header.h"
#include "dkmgt_ptn_device_info.h"
#include "dkmgt_ptn_support_list.h"
#include "thirdparty/cJSON/cJSON.h"

/**************************************************************************************************/
/*                                       DEFINES                                                  */
/**************************************************************************************************/
#define __SUPPORT_LIST_ELEM(__json_root, __name, __size, __elem)	\
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
static void _ptn_support_list_dump(struct dkmgt_ptn_support_list *support_list)
{
	int i = 0;
	
    ASSERT(support_list);

#define __PP_16(a)   printf("%-16s = '%s'    ", #a, support_list->entry[i].a)
#define __PP_10(a)   printf("%-10s = '%s'    ", #a, support_list->entry[i].a)

	printf("#############################################################################\n");
	printf("#########            support list info                      #################\n");
	printf("#############################################################################\n");
	for (i = 0; i < support_list->cnt; i ++)
	{
	    __PP_10(product_name);
	    __PP_16(product_version);
	    __PP_10(special_id);
		printf("\n");
	}
	printf("#############################################################################\n");
}
#endif

int _support_list_json_parse(struct dkmgt_ptn_support_list *support_list, cJSON* json_root)
{
    cJSON *json_ptn_array = NULL;
    cJSON *json_ptn = NULL;
    int   ptn_cnt = 0;
    int   i = 0;

    ASSERT(json_root);
    ASSERT(support_list);

    memset((void*)support_list, 0, sizeof(struct dkmgt_ptn_support_list));

    json_ptn_array = cJSON_GetObjectItem(json_root, DKMGT_PTN_SUPPORT_LIST);
    if (NULL == json_ptn_array) {
        DOUT_ERROR("'%s' not found.", DKMGT_PTN_SUPPORT_LIST);
        goto error;
    }

    ptn_cnt = cJSON_GetArraySize(json_ptn_array);

    DOUT_TRACE("support list entry count %d", ptn_cnt);

    if (ptn_cnt > DKMGT_PTN_SUPPORT_LIST_MAX_CNT) {
       DOUT_ERROR("too much entry, %d/%d.", ptn_cnt, DKMGT_PTN_SUPPORT_LIST_MAX_CNT);
       goto error; 
    }

	support_list->cnt = ptn_cnt;
    for (i = 0; i < ptn_cnt; ++ i) {
        json_ptn = cJSON_GetArrayItem(json_ptn_array, i);
        ASSERT(json_ptn);

		__SUPPORT_LIST_ELEM(json_ptn, DKMGT_PTN_DEVICE_INFO_PRODUCT_NAME, DKMGT_PTN_DEVICE_INFO_PRODUCT_NAME_SIZE, 
			support_list->entry[i].product_name);
		__SUPPORT_LIST_ELEM(json_ptn, DKMGT_PTN_DEVICE_INFO_PRODUCT_VERSION, DKMGT_PTN_DEVICE_INFO_PRODUCT_VERSION_SIZE, 
			support_list->entry[i].product_version);
		__SUPPORT_LIST_ELEM(json_ptn, DKMGT_PTN_DEVICE_INFO_SPECIAL_ID, DKMGT_PTN_DEVICE_INFO_SPECIAL_ID_SIZE, 
			support_list->entry[i].special_id);
    }

    return 0;

error:
    return -1;
}

int _support_list_build_by_json_data(struct dkmgt_ptn_support_list *support_list,char* json_data, int json_len)
{
    cJSON * json = NULL;

    json = dkmgt_parse_json_data(json_data, json_len);
    if (NULL == json) {
        DOUT_ERROR("Failed to parse json.");
        goto error;
    }

    if (_support_list_json_parse(support_list, json) < 0) {
        DOUT_ERROR("Failed to parse json.");
        goto error;
    }

    if (NULL != json) {
        cJSON_Delete(json);
    }

    return 0;

error:
    if (NULL != json) {
        cJSON_Delete(json);
    }

    return -1;
}

struct dkmgt_ptn_support_list * dkmgt_support_list_build(
	struct dkmgt_firmware_ptn_table * firmware_ptn_table, 
	char* firmware_buf) 
{
    struct dkmgt_ptn_support_list * support_list = NULL;
    int ptn = 0;

    support_list = (struct dkmgt_ptn_support_list *)malloc(sizeof(struct dkmgt_ptn_support_list));
    if (NULL == support_list) {
        DOUT_ERROR("failed to alloc %d bytes.\n", (int)sizeof(struct dkmgt_ptn_support_list));
        goto error;
    }

    memset(support_list, 0, sizeof(struct dkmgt_ptn_support_list));

    for (ptn = 0; ptn < DKMGT_PTN_MAX_CNT; ++ ptn) {
		struct dkmgt_firmware_ptn_entry* firmware_ptn_entry = &(firmware_ptn_table->ptns[ptn]);
		
        if (0 == strcmp(firmware_ptn_entry->name, DKMGT_PTN_SUPPORT_LIST)) {
			struct dkmgt_ptn_header *ptn_header = NULL;

			ptn_header = dkmgt_ptn_header_build((char *)(firmware_buf + firmware_ptn_entry->offset), firmware_ptn_entry->length);
            if(NULL == ptn_header) {
                DOUT_ERROR("firmware partition [0x%08x] is not a valid partition.", firmware_ptn_entry->offset);
                goto error;
            }
			
            if (_support_list_build_by_json_data(support_list, 
					(char *)firmware_buf + firmware_ptn_entry->offset + sizeof(struct dkmgt_ptn_header), 
					ptn_header->length) < 0){
                DOUT_ERROR("Faield to parse support list of firmware.");
				free(ptn_header);
                goto error;
            }
			free(ptn_header);
        }
    }

#ifdef DEBUG
	_ptn_support_list_dump(support_list);
#endif

    return support_list;

error:
	if (NULL != support_list)
		free(support_list);
	
    return NULL;
}


int dkmgt_support_list_check(
	struct dkmgt_ptn_device_info * flash_devinfo,
	struct dkmgt_ptn_support_list * support_list) 
{
    int is_upgradable = -1;
	int	i = 0;

    if ((NULL == flash_devinfo) || (NULL == support_list)) {
        goto leave;
    }

	for (i = 0; i < support_list->cnt; i++)
	{
	    if ((0 == strcmp(flash_devinfo->product_name, support_list->entry[i].product_name)) &&
			(0 == strcmp(flash_devinfo->product_version, support_list->entry[i].product_version)) &&
			(0 == strcmp(flash_devinfo->special_id, support_list->entry[i].special_id)))
		{			
			DOUT_TRACE("match by entry %d (%s, %s, %s)!\n", i,
				support_list->entry[i].product_name, support_list->entry[i].product_version, support_list->entry[i].special_id);
	        is_upgradable = 1;
			break;
	    }
	}

leave:
    return is_upgradable;
}

