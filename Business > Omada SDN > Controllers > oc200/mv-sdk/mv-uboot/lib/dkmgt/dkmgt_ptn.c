/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmgt_ptn.c
 *@brief    Partition table.
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
#include "dkmgt_file.h"
#include "thirdparty/cJSON/cJSON.h"

/**************************************************************************************************/
/*                                       DEFINES                                                  */
/**************************************************************************************************/

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


static bool _ptn_name_validate(char * name)
{
    char *p = NULL;

    ASSERT(name);

    p = name;

    while ('\0' != *p) {

        if (('a' <= *p && *p <= 'z') 
            || ('A' <= *p && *p <= 'Z') 
            || ('0' <= *p && *p <= '9')
            || ('-' == *p || '_' == *p || '.' == *p )) {
            /* check next */
        }
        else
        {
            return false;
        }

        p++;
    }

    return true;
}



static bool _ptn_layout_validate(struct dkmgt_ptn_layout * ptn_layout)
{
    int curr = 0;
    int prev = 0;

    ASSERT(ptn_layout);
    
    for (curr = 0; curr < ptn_layout->cnt; ++curr) {

        /* size *MUST* be > 0 */
        if (0 == ptn_layout->ptns[curr].size) {
            DOUT_ERROR("PTN[%s] size is 0.", ptn_layout->ptns[curr].name);
            return false;
        }

        /* check if disk overflow. */
        if ((ptn_layout->ptns[curr].base + ptn_layout->ptns[curr].size) > ptn_layout->disk_size) {
            DOUT_ERROR("PTN[%s,0x%08x,0x%08x] cause disk[0x%llX] overflow.", 
                       ptn_layout->ptns[curr].name,
                       ptn_layout->ptns[curr].base,
                       ptn_layout->ptns[curr].size,
                       (long long unsigned int)ptn_layout->disk_size);
            return false;
        }
        
        for (prev = 0; prev < curr; ++prev) {

            /* every ptn name *MUST* be unique. */
            if (0 == strcmp(ptn_layout->ptns[curr].name, ptn_layout->ptns[prev].name)) {
                DOUT_ERROR("PTN[%d] and PTN[%d] Name conflict : '%s'.", prev, curr, ptn_layout->ptns[curr].name);
                return false;
            }

            /* PTN[N]->base *MUST* >  PTN[N-1]->base */
            if (ptn_layout->ptns[curr].base <= ptn_layout->ptns[prev].base) {
                DOUT_ERROR("PTN[%s](%d) base(0x%08x) <= PTN[%s](%d) base(0x%08x).",
                           ptn_layout->ptns[curr].name, curr, ptn_layout->ptns[curr].base,
                           ptn_layout->ptns[prev].name, prev, ptn_layout->ptns[prev].base);
                return false;
            }

            /* PTN[N]'s base *MUST* >  PTN[N-1]->base + PTN[N-1]->size */
            if (ptn_layout->ptns[curr].base < (ptn_layout->ptns[prev].base + ptn_layout->ptns[prev].size)) {
                DOUT_ERROR("PTN[%s](%d) base(0x%08x) < PTN[%s](%d) base+size(0x%08x).",
                           ptn_layout->ptns[curr].name, curr, ptn_layout->ptns[curr].base,
                           ptn_layout->ptns[prev].name, prev, ptn_layout->ptns[prev].base + ptn_layout->ptns[prev].size);
                return false;
            }
        }
    }

    return true;
}

static int _ptn_table_partition_layout(cJSON* json_root, struct dkmgt_ptn_layout *ptn_layout, uint32_t layout)
{
    cJSON *json_ptn_array = NULL;
    cJSON *json_ptn = NULL;
    cJSON *json = NULL;
    int   ptn_cnt = 0;
    int   i = 0;

    ASSERT(json_root);
    ASSERT(ptn_layout);

    memset((void*)ptn_layout, 0, sizeof(struct dkmgt_ptn_layout));

    json = cJSON_GetObjectItem(json_root, DKMGT_PTN_DISK_SIZE);
    if (NULL == json) {
        DOUT_ERROR("'%s' not found.", DKMGT_PTN_DISK_SIZE);
        goto error;
    }

    ptn_layout->disk_size = (uint64_t)simple_strtoul(json->valuestring, NULL, 16);

    json = cJSON_GetObjectItem(json_root, DKMGT_PTN_DEVICE);
    if (NULL == json) {
        DOUT_ERROR("'%s' not found.", DKMGT_PTN_DEVICE);
        goto error;
    }	
	if (strlen(json->valuestring) >= DKMGT_PTN_DEVICE_MAX_LEN) {
		DOUT_ERROR("ptn json 'device' string len too long, '%s', %d/%d", json->valuestring, 
				   (int)strlen(json->valuestring), DKMGT_PTN_DEVICE_MAX_LEN);
		goto error;
	}
	snprintf(ptn_layout->device, sizeof(ptn_layout->device), "%s", json->valuestring);

    json_ptn_array = cJSON_GetObjectItem(json_root, DKMGT_PTN_PARTITION_TABLE);
    if (NULL == json_ptn_array) {
        DOUT_ERROR("'%s' not found.", DKMGT_PTN_PARTITION_TABLE);
        goto error;
    }

    ptn_cnt = cJSON_GetArraySize(json_ptn_array);

    DOUT_TRACE("ptn_cnt %d", ptn_cnt);

    if (ptn_cnt > DKMGT_PTN_MAX_CNT) {
       DOUT_ERROR("too much partitiions, %d/%d.", ptn_cnt, DKMGT_PTN_MAX_CNT);
       goto error; 
    }

    for (i = 0; i < ptn_cnt; ++ i) {

        json_ptn = cJSON_GetArrayItem(json_ptn_array, i);
        ASSERT(json_ptn);

        ptn_layout->ptns[ptn_layout->cnt].layout = layout;

        /* name */
        json = cJSON_GetObjectItem(json_ptn, DKMGT_PTN_NAME);
        if (NULL == json) {
            DOUT_ERROR("ptn json 'name' not found.\n");
            goto error;
        }

        if (cJSON_String != json->type) {
            DOUT_ERROR("ptn json 'name' must be String type.\n");
            goto error;
        }

        if (strlen(json->valuestring) >= DKMGT_PTN_NAME_LEN) {
            DOUT_ERROR("ptn json 'name' string len too long, '%s', %d/%d", json->valuestring, 
                       (int)strlen(json->valuestring), DKMGT_PTN_NAME_LEN);
            goto error;
        }

        if (!_ptn_name_validate(json->valuestring)) {
            DOUT_ERROR("ptn json 'name' (%s) validate failed.", json->valuestring);
            goto error;
        }

        snprintf(ptn_layout->ptns[ptn_layout->cnt].name,
                 sizeof(ptn_layout->ptns[ptn_layout->cnt].name),
                 "%s", 
                 json->valuestring);


        /* base */
        json = cJSON_GetObjectItem(json_ptn, DKMGT_PTN_BASE);
        if (NULL == json) {
            DOUT_ERROR("ptn json 'base' not found.\n");
            goto error;
        }

        if (cJSON_String != json->type) {
            DOUT_ERROR("ptn json 'base' must be String type.\n");
            goto error;
        }

        ptn_layout->ptns[ptn_layout->cnt].base = (uint32_t)simple_strtoul(json->valuestring, NULL, 16);

        /* size */
        json = cJSON_GetObjectItem(json_ptn, DKMGT_PTN_SIZE);
        if (NULL == json) {
            DOUT_ERROR("ptn json 'size' not found.\n");
            goto error;
        }

        if (cJSON_String != json->type) {
            DOUT_ERROR("ptn json 'size' must be String type.\n");
            goto error;
        }

        ptn_layout->ptns[ptn_layout->cnt].size = (uint32_t)simple_strtoul(json->valuestring, NULL, 16);

        /* write_to_flash */
        json = cJSON_GetObjectItem(json_ptn, DKMGT_PTN_WRITE_TO_FLASH);
        if (NULL == json) {
            DOUT_ERROR("ptn json 'write_to_flash' not found.\n");
            goto error;
        }

        if ((cJSON_True != json->type) && (cJSON_False != json->type)) {
            DOUT_ERROR("ptn json 'write_to_flash' must be bool type.\n");
            goto error;
        }

        ptn_layout->ptns[ptn_layout->cnt].write_to_flash = json->type;


        /* write_to_up */
        json = cJSON_GetObjectItem(json_ptn, DKMGT_PTN_WRITE_TO_UP);
        if (NULL == json) {
            DOUT_ERROR("ptn json 'write_to_up' not found.\n");
            goto error;
        }

        if ((cJSON_True != json->type) && (cJSON_False != json->type)) {
            DOUT_ERROR("ptn json 'write_to_up' must be bool type.\n");
            goto error;
        }

        ptn_layout->ptns[ptn_layout->cnt].write_to_up = json->type;


        /* encap_type */
        json = cJSON_GetObjectItem(json_ptn, DKMGT_PTN_ENCAP_TYPE);
        if (NULL == json) {
            DOUT_ERROR("ptn json 'encap_type' not found.\n");
            goto error;
        }

        if (cJSON_String != json->type) {
            DOUT_ERROR("ptn json 'encap_type' must be String type.\n");
            goto error;
        }

        if (strlen(json->valuestring) >= DKMGT_PTN_ENCAP_TYPE_LEN) {
            DOUT_ERROR("ptn json 'encap_type' string len too long, '%s', %d/%d", json->valuestring, 
                       (int)strlen(json->valuestring), DKMGT_PTN_ENCAP_TYPE_LEN);
            goto error;
        }

        snprintf(ptn_layout->ptns[ptn_layout->cnt].encap_type,
                 sizeof(ptn_layout->ptns[ptn_layout->cnt].encap_type),
                 "%s", 
                 json->valuestring);


        DOUT_TRACE("PTN %2d : name '%s' base 0x%08x size 0x%08x write_to_flash %d write_to_up %d encap_type %s",
               ptn_layout->cnt,
               ptn_layout->ptns[ptn_layout->cnt].name, 
               ptn_layout->ptns[ptn_layout->cnt].base, 
               ptn_layout->ptns[ptn_layout->cnt].size, 
               ptn_layout->ptns[ptn_layout->cnt].write_to_flash,
               ptn_layout->ptns[ptn_layout->cnt].write_to_up,
               ptn_layout->ptns[ptn_layout->cnt].encap_type);


        ptn_layout->cnt +=1;
    }

    if (!_ptn_layout_validate(ptn_layout)) {
        DOUT_ERROR("ptn table validate failed.");
        goto error;
    }

    return 0;

error:
    return -1;
}


/**************************************************************************************************/
/*                                       PUBLIC_FUNCTIONS                                         */
/**************************************************************************************************/


struct dkmgt_ptn_entry *dkmgt_ptn_get_ptn_entry(struct dkmgt_ptn_table * ptn_table, char* ptn_name)
{
    int ptn = 0;
	int layout = 0;

    for (layout = 0; layout < DKMGT_PTN_LAYOUT_TYPE_MAX; ++ layout)
	{
	    for (ptn = 0; ptn < ptn_table->ptn_layout[layout].cnt; ++ ptn) 
		{
	        if (0 == strcmp(ptn_table->ptn_layout[layout].ptns[ptn].name, ptn_name)) 
			{
	            return &(ptn_table->ptn_layout[layout].ptns[ptn]);
	        }
	    }
    }

    return NULL;
}

int dkmgt_ptn_table_build_by_json(cJSON * json_root, struct dkmgt_ptn_table *ptn_table)
{
    cJSON * json_ptn_layout = NULL;
    int ret = 0;

    json_ptn_layout = cJSON_GetObjectItem(json_root, DKMGT_PTN_PARTITION_LAYOUT_NOR);
    if (NULL == json_ptn_layout) {
        DOUT_ERROR("'%s' not found.", DKMGT_PTN_PARTITION_LAYOUT_NOR);
        goto error;
    }

    ret = _ptn_table_partition_layout(json_ptn_layout, &(ptn_table->ptn_layout[DKMGT_PTN_LAYOUT_TYPE_NOR]), DKMGT_PTN_LAYOUT_TYPE_NOR);
    if (ret < 0) {
        DOUT_ERROR("Failed to parse json[ptn_layout] -> ptn_layout struct.");
        goto error;
    }

    json_ptn_layout = cJSON_GetObjectItem(json_root, DKMGT_PTN_PARTITION_LAYOUT_EMMC);
    if (NULL == json_ptn_layout) {
        DOUT_ERROR("'%s' not found.", DKMGT_PTN_PARTITION_LAYOUT_EMMC);
        goto error;
    }

    ret = _ptn_table_partition_layout(json_ptn_layout, &(ptn_table->ptn_layout[DKMGT_PTN_LAYOUT_TYPE_EMMC]), DKMGT_PTN_LAYOUT_TYPE_EMMC);
    if (ret < 0) {
        DOUT_ERROR("Failed to parse json[ptn_layout] -> ptn_layout struct.");
        goto error;
    }

    return 0;

error:
    return -1;
}

struct dkmgt_ptn_table* dkmgt_ptn_table_build(char* device, uint32_t ptn_base)
{
	cJSON * json = NULL;
    struct dkmgt_ptn_table * ptn_table = NULL;
    int ret = 0;
    char* buf = NULL;
    int bufsize = DKMGT_PTN_BUFFER_SIZE;
    int read_bytes = 0;

    buf = malloc(bufsize);
    if (NULL == buf) {
        DOUT_ERROR("alloc %d bytes failed.", bufsize);
        goto error;        
    }

    memset(buf, 0, bufsize);

    ret = dkmgt_file_read_by_offset(device, ptn_base, buf, bufsize, &read_bytes);
    if (ret < 0) {
        DOUT_ERROR("failed to read ptn_table content.");
        goto error;
    }

	json = dkmgt_parse_json_data(buf, read_bytes);
	if (NULL == json) {
		DOUT_ERROR("Failed to parse json.");
		goto error;
	}
		
	ptn_table = (struct dkmgt_ptn_table *)malloc(sizeof(struct dkmgt_ptn_table));
	if (NULL == ptn_table) {
		DOUT_ERROR("failed to alloc %d bytes.\n", (int)sizeof(struct dkmgt_ptn_table));
		goto error;
	}
	
	memset(ptn_table, 0, sizeof(struct dkmgt_ptn_table));	
	ret = dkmgt_ptn_table_build_by_json(json, ptn_table);
	if (ret < 0) {
		DOUT_ERROR("Failed to parse json -> ptn table struct.");
		goto error;
	}
	
	if (NULL != json) {
		cJSON_Delete(json);
	}
	
    if (NULL != buf) {
        free(buf);
    }

    return ptn_table;

error:	
	if (NULL != json) {
		cJSON_Delete(json);
	}
	
    if (NULL != buf) {
        free(buf);
    }

    if (NULL != ptn_table) {
        free(ptn_table);
    }

    return NULL;
}

void dkmgt_ptn_table_dump(struct dkmgt_ptn_table * ptn_table)
{
    int layout = 0;
    int ptn = 0;
	struct dkmgt_ptn_layout *ptn_layout = NULL;

	printf("#############################################################################\n");
	printf("#########            partition table info                   #################\n");
	printf("#############################################################################\n");
    for (layout = 0; layout < DKMGT_PTN_LAYOUT_TYPE_MAX; ++ layout) {
		ptn_layout = &(ptn_table->ptn_layout[layout]);

	    printf("layout           : %d\n", layout);
	    printf("disk size        : 0x%llX\n", (long long unsigned int)ptn_layout->disk_size);
	    printf("device           : %s\n", ptn_layout->device);
	    printf("partition number : %u\n", ptn_layout->cnt);

	    printf("\n");

	    printf("partitions:\n");
	    printf("%5s %-24s %10s %10s %10s\n","index", "name", "base", "size(hex)", "size(dec)");
	    printf("---------------------------------------------------------------\n");
	    for (ptn = 0; ptn < ptn_layout->cnt; ++ ptn) {
	        printf("%5d %-24s 0x%08X 0x%08X %10u\n",
	               ptn,
	               ptn_layout->ptns[ptn].name, 
	               ptn_layout->ptns[ptn].base, 
	               ptn_layout->ptns[ptn].size, 
	               ptn_layout->ptns[ptn].size);
	    }
	    printf("---------------------------------------------------------------\n");
	    printf("---------------------------------------------------------------\n");
    }
	
	printf("#############################################################################\n");
}


void dkmgt_ptn_table_show(char* device, uint32_t ptn_base) 
{
    struct dkmgt_ptn_table *ptn_table = NULL;

    ptn_table = dkmgt_ptn_table_build(device, ptn_base);
    if (NULL == ptn_table) {
        DOUT_ERROR("Failed to build ptn table.");
        goto leave;
    }

    dkmgt_ptn_table_dump(ptn_table);

leave:
    if (NULL != ptn_table) {
        free(ptn_table);
    }

	return;
}

char* dkmgt_ptn_entry_read(char *device, uint32_t ptn_base, char *ptn_name, int *ptn_size) 
{
	struct dkmgt_ptn_table* ptn_table = NULL;
    struct dkmgt_ptn_entry *ptn_entry = NULL;
	char *ptn_buf = NULL;
	int ptn_buf_size = 0;
    int ret_bytes = 0;
	int ret = 0;

	ptn_table = dkmgt_ptn_table_build(device, ptn_base);
	if (ptn_table == NULL){
        DOUT_ERROR("Failed to build ptn_table of flash");
	   ret = -1;   
	   goto out;
   	}

#ifdef DEBUG
    dkmgt_ptn_table_dump(ptn_table);
#endif

    ptn_entry = dkmgt_ptn_get_ptn_entry(ptn_table, ptn_name);
    if (ptn_entry == NULL) {
        DOUT_ERROR("PTN[%s] not found.", ptn_name);
		ret = -1;
		goto out;
    }

    ptn_buf_size = ptn_entry->size;
    ptn_buf = malloc(ptn_buf_size);
    if (NULL == ptn_buf) {
        DOUT_ERROR("alloc %d bytes failed.", ptn_buf_size);
		ret = -1;
		goto out;
    }

    memset(ptn_buf, 0, ptn_buf_size);

    if (ptn_entry->layout == DKMGT_PTN_LAYOUT_TYPE_EMMC)
    {
        ret = dkmgt_file_read_by_offset(ptn_table->ptn_layout[DKMGT_PTN_LAYOUT_TYPE_EMMC].device, ptn_entry->base, ptn_buf, ptn_buf_size, &ret_bytes);
    }
    else if (ptn_entry->layout == DKMGT_PTN_LAYOUT_TYPE_NOR)
    {
        ret = dkmgt_file_read_by_offset_block_mode(ptn_table->ptn_layout[DKMGT_PTN_LAYOUT_TYPE_NOR].device, ptn_entry->base, ptn_buf, ptn_buf_size,DKMGT_FLASH_BLOCK_SIZE, &ret_bytes);
    }
    else
    {
        DOUT_ERROR("invalid layout type (%u).", ptn_entry->layout);
        goto out;
    }
	
    if (ret < 0) {
        DOUT_ERROR("failed to read ptn_table content.");
		goto out;
    }

	*ptn_size = ptn_entry->size;

out:

	if (ret == 0)
		return ptn_buf;
	else
	{
	    if (NULL != ptn_buf) {
	        free(ptn_buf);
	    }
		return NULL;
	}
}

/**************************************************************************************************/
/*                                       GLOBAL_FUNCTIONS                                         */
/**************************************************************************************************/


