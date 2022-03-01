/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmt_firmware.h
 *@brief    Firmware making.
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
#include <u-boot/md5.h>

#include "dkmgt_common.h"
#include "dkmgt_ptn.h"
#include "dkmgt_ptn_header.h"
#include "dkmgt_file.h"
#include "dkmgt_firmware.h"
#include "dkmgt_ptn_device_info.h"
#include "dkmgt_ptn_support_list.h"
#include "rsaVerify.h"

/**************************************************************************************************/
/*                                       DEFINES                                                  */
/**************************************************************************************************/
#define DKMGT_FW_HDR_MD5_BEGIN        (0X14)

/**************************************************************************************************/
/*                                       TYPES                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       EXTERN_PROTOTYPES                                        */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       LOCAL_PROTOTYPES                                         */
/**************************************************************************************************/
static unsigned char rsaPubKey[] = "BgIAAACkAABSU0ExAAQAAAEAAQD9lxDCQ5DFNSYJBriTmTmZlEMYVgGcZTO+AIwm" \
				"dVjhaeJI6wWtN7DqCaHQlOqJ2xvKNrLB+wA1NxUh7VDViymotq/+9QDf7qEtJHmesji" \
				"rvPN6Hfrf+FO4/hmjbVXgytHORxGta5KW4QHVIwyMSVPOvMC4A5lFIh+D1kJW5GXWtA==";
/**************************************************************************************************/
/*                                       VARIABLES                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       LOCAL_FUNCTIONS                                          */
/**************************************************************************************************/
void print_buf(unsigned char *data, int len )
{
    int i   = 0 ; 
    if ( NULL == data )
    {
        printf( "===\r\nData is NULL!\r\n" );
        return;
    }

    printf( "\r\n===============\r\n" );
    for ( i = 0; i < len; ++i )
    {
        printf( "%02X ", ( char )data[i] );
        if ( i % 16 == 15 )
        {
            printf( "\r\n" );
        }
    }

    printf( "\r\n===============\r\n" );

}

static void _md5_calc(char* buf, int len, uint8_t *digest) {
	#if 0
    MD5_CTX ctx;

    MD5_Init(&ctx);
    MD5_Update(&ctx, buf, len);
    MD5_Final(digest, &ctx);
	#endif
	return md5((unsigned char *)buf, len, digest);
}

#ifdef DEBUG
static void _firmware_header_dump(struct dkmgt_firmware_header * firmware_header) 
{
	int i = 0;
    if (NULL == firmware_header) {
        printf("firmware_header is null.\n");
        return;
    }

	printf("#############################################################################\n");
	printf("#########           firmware header info                    #################\n");
	printf("#############################################################################\n");
    printf("version       : 0x%08X \n", firmware_header->version);
    printf("magic         : 0x%08X \n", firmware_header->magic);
    printf("header_length : 0x%08X (%d)\n", firmware_header->header_length, firmware_header->header_length);
    printf("total_length  : 0x%08X (%d)\n", firmware_header->total_length, firmware_header->total_length);
    printf("md5_digest    : ");
	for (i = 0; i < DKMGT_FIRMWARE_MD5_SIZE; i ++)
		printf("%02X", firmware_header->md5[i]);
	
    printf("\n");
	printf("#############################################################################\n");
}
#endif

static int _firmware_header_check_rsa(char* buf, int buf_len)
{
	struct dkmgt_firmware_header * firmware_header = NULL;
	unsigned char md5[DKMGT_FIRMWARE_MD5_SIZE] = {0};
	unsigned char sig[DKMGT_FIRMWARE_RSA_SIZE] = {0};
	unsigned char tmp_sig[DKMGT_FIRMWARE_RSA_SIZE] = {0};
	int ret;

	firmware_header = (struct dkmgt_firmware_header *)buf;
	/*backup data*/
	memcpy(tmp_sig, firmware_header->rsa, DKMGT_FIRMWARE_RSA_SIZE);

	memcpy(sig, firmware_header->rsa, DKMGT_FIRMWARE_RSA_SIZE);

	/* fill with 0x0 */
	memset(firmware_header->rsa, 0x0, DKMGT_FIRMWARE_RSA_SIZE);

	_md5_calc(buf + DKMGT_FW_HDR_MD5_BEGIN, buf_len - DKMGT_FW_HDR_MD5_BEGIN, md5);

	ret = rsaVerifySignByBase64EncodePublicKeyBlob(rsaPubKey, strlen((char *)rsaPubKey),
                md5, DKMGT_FIRMWARE_MD5_SIZE, sig, DKMGT_FIRMWARE_RSA_SIZE);
	/* restore */
	memcpy(firmware_header->rsa, tmp_sig, DKMGT_FIRMWARE_RSA_SIZE);
	
	return (ret == 1) ? 0 : -1;
}

static int _firmware_header_check_md5(char* buf, int buf_len)
{
	struct dkmgt_firmware_header * firmware_header = NULL;
	unsigned char rsa_sig[DKMGT_FIRMWARE_RSA_SIZE] = {0};
	unsigned char md5_digest[DKMGT_FIRMWARE_MD5_SIZE] = {0};
    unsigned char md5_firmware[DKMGT_FIRMWARE_MD5_SIZE] = {0};

	firmware_header = (struct dkmgt_firmware_header *)buf;
	
	/* backup firmware md5 digest and rsa sign */
	memcpy(md5_firmware, firmware_header->md5, DKMGT_FIRMWARE_MD5_SIZE);
	memcpy(rsa_sig, firmware_header->rsa, DKMGT_FIRMWARE_RSA_SIZE);
	
	/* set zero before md5 */
	memset(firmware_header->md5, 0x0, DKMGT_FIRMWARE_MD5_SIZE);	
	memset(firmware_header->rsa, 0x0, DKMGT_FIRMWARE_RSA_SIZE);	

    _md5_calc(buf, buf_len, md5_digest);
	
	/* restore firmware md5 digest and rsa sign */
	memcpy(firmware_header->md5, md5_firmware, DKMGT_FIRMWARE_MD5_SIZE);
	memcpy(firmware_header->rsa, rsa_sig, DKMGT_FIRMWARE_RSA_SIZE);

    if (0 != memcmp(md5_digest, firmware_header->md5, DKMGT_FIRMWARE_MD5_SIZE)) {
        return -1;
    }

	return 0;
}

static int _firmware_header_check(char* firmware_buf, int firmware_size, struct dkmgt_firmware_header * firmware_header, int type) 
{
    if ((DKMGT_FIRMWARE_HEADER_MAGIC != firmware_header->magic)) {
        DOUT_ERROR("Invalid magic number.");
        return -UPGRADE_FILE_INVALID;
    }

    if (firmware_header->total_length != firmware_size) {
        DOUT_ERROR("firmware size un-match, firmware_size is %d header[total_len] is %d.", 
                   firmware_size, firmware_header->total_length);
        return -UPGRADE_FILE_INVALID;
    }

	if (type & DKMGT_FIRMWARE_CHECK_RSA)
	{
		if (_firmware_header_check_rsa(firmware_buf, firmware_size) < 0)
		{
			DOUT_ERROR("firmware RSA verify failed\n");
			return -UPGRADE_RSA_ERROR;
		}
		DOUT_INFO("rsa check pass");
	}
	
	if (type & DKMGT_FIRMWARE_CHECK_MD5)
	{
		if (_firmware_header_check_md5(firmware_buf, firmware_size) < 0)
		{
			DOUT_ERROR("firmware MD5 verify failed\n");
			return -UPGRADE_MD5_ERROR;
		}
		DOUT_INFO("md5 check pass");
	}

	return 0;
}

static struct dkmgt_firmware_header * _firmware_header_build(char* firmware_buf, int firmware_size) 
{
    struct dkmgt_firmware_header * firmware_header = NULL;

    firmware_header = malloc(sizeof(struct dkmgt_firmware_header));
    if (NULL == firmware_header) {
        DOUT_ERROR("Failed to alloc %d bytes memory.", (int)sizeof(struct dkmgt_firmware_header));
        return NULL;
    }

    memset(firmware_header, 0, sizeof(struct dkmgt_firmware_header));
    memcpy(firmware_header, firmware_buf, sizeof(struct dkmgt_firmware_header));

    firmware_header->version 	= ntohl(firmware_header->version);
    firmware_header->magic		= ntohl(firmware_header->magic);
    firmware_header->header_length	= ntohl(firmware_header->header_length);
    firmware_header->total_length	= ntohl(firmware_header->total_length);

#ifdef DEBUG
	_firmware_header_dump(firmware_header);
#endif
	
	return firmware_header;
}

#ifdef DEBUG
static void _firmware_ptn_table_dump(struct dkmgt_firmware_ptn_table* firmware_ptn_table)
{
	int ptn = 0;
	
	printf("#############################################################################\n");
	printf("#########            firmware ptn table                     #################\n");
	printf("#############################################################################\n");
	printf("%5s %-24s %10s %10s %10s %10s\n","index", "name", "base", "size", "offset", "length");
	printf("--------------------------------------------------------------------------\n");

	for (ptn = 0; ptn < DKMGT_PTN_MAX_CNT; ptn ++)
	{
		struct dkmgt_firmware_ptn_entry *firmware_ptn_entry = &(firmware_ptn_table->ptns[ptn]);

		if (firmware_ptn_entry->size == 0)
			continue;

		printf("%5d %-24s 0x%08X 0x%08X 0x%08X 0x%08X\n",
			   ptn,
			   firmware_ptn_entry->name, 
			   firmware_ptn_entry->base, 
			   firmware_ptn_entry->size, 
			   firmware_ptn_entry->offset,
			   firmware_ptn_entry->length);
	}
	printf("#############################################################################\n");
}
#endif

static struct dkmgt_firmware_ptn_table* _firmware_ptn_table_build(char* firmware_buf, int firmware_size)
{
    struct dkmgt_firmware_ptn_table *firmware_ptn_table = NULL;
	int ptn = 0;
	
    firmware_ptn_table = malloc(sizeof(struct dkmgt_firmware_ptn_table));
    if (NULL == firmware_ptn_table) {
        DOUT_ERROR("Failed to alloc %d bytes memory.", (int)sizeof(struct dkmgt_firmware_ptn_table));
        return NULL;
    }

	memset(firmware_ptn_table, 0, sizeof(struct dkmgt_firmware_ptn_table));
	memcpy(firmware_ptn_table, firmware_buf, sizeof(struct dkmgt_firmware_ptn_table));

	for (ptn = 0; ptn < DKMGT_PTN_MAX_CNT; ptn ++)
	{
		struct dkmgt_firmware_ptn_entry *firmware_ptn_entry = &(firmware_ptn_table->ptns[ptn]);
			
	    firmware_ptn_entry->base	= ntohl(firmware_ptn_entry->base);
	    firmware_ptn_entry->size	= ntohl(firmware_ptn_entry->size);
	    firmware_ptn_entry->offset	= ntohl(firmware_ptn_entry->offset);
	    firmware_ptn_entry->length	= ntohl(firmware_ptn_entry->length);
		firmware_ptn_entry->type	= ntohl(firmware_ptn_entry->type);
	}

#ifdef DEBUG
	_firmware_ptn_table_dump(firmware_ptn_table);
#endif

	return firmware_ptn_table;
}

static int _firmware_update_ptn(
	struct dkmgt_ptn_table * ptn_table,
	struct dkmgt_firmware_header * firmware_header, 
	struct dkmgt_firmware_ptn_table * firmware_ptn_table, 
	char* firmware_buf, 
	int firmware_size) 
{
	struct dkmgt_firmware_ptn_entry *firmware_ptn_entry = NULL;
	struct dkmgt_ptn_entry *ptn_entry= NULL;
	int ptn = 0;
	int ret = 0;
	int bytes = 0;
	char *device = NULL;

	for (ptn = 0; ptn < DKMGT_PTN_MAX_CNT; ++ ptn) {
		firmware_ptn_entry = &(firmware_ptn_table->ptns[ptn]);
		if (firmware_ptn_entry->size == 0) /* empty ptn entry */
			break;

		ptn_entry = dkmgt_ptn_get_ptn_entry(ptn_table, firmware_ptn_entry->name);

		if (ptn_entry == NULL) {
			DOUT_TRACE("PTN[%s] not found at device's disk, is new PTN.", firmware_ptn_entry->name);
		}
		if (ptn_entry->base != firmware_ptn_entry->base)
		{
	        DOUT_INFO("ptn[%s] moved from {0x%08x:0x%08x} to {0x%08x:0x%08x}.", 
	                   ptn_entry->name, ptn_entry->base, ptn_entry->size,
	                   firmware_ptn_entry->base, firmware_ptn_entry->size);
			DOUT_INFO("*** Attention, ptn move not support now ***");
		}

		DOUT_INFO("PTN[%s] update, base=0x%08x, size=0x%08x, content_size=0x%08x(%d).", 
				   firmware_ptn_entry->name, firmware_ptn_entry->base, firmware_ptn_entry->size, 
				   firmware_ptn_entry->length, firmware_ptn_entry->length);
		
		if (firmware_ptn_entry->type == DKMGT_PTN_LAYOUT_TYPE_NOR)
		{
			device = ptn_table->ptn_layout[DKMGT_PTN_LAYOUT_TYPE_NOR].device;
			dkmgt_file_write_by_offset_block_mode(device, firmware_ptn_entry->base, firmware_buf + firmware_ptn_entry->offset,
				firmware_ptn_entry->length, DKMGT_FLASH_BLOCK_SIZE, &bytes);
		}
		else if (firmware_ptn_entry->type == DKMGT_PTN_LAYOUT_TYPE_EMMC)
		{
			device = ptn_table->ptn_layout[DKMGT_PTN_LAYOUT_TYPE_EMMC].device;
			
			ret = dkmgt_file_write_by_offset(device, firmware_ptn_entry->base, firmware_buf + firmware_ptn_entry->offset,
				firmware_ptn_entry->length, &bytes);
		}
		else
		{
			DOUT_ERROR("PTN [%s] type %d is invalid.", firmware_ptn_entry->name, firmware_ptn_entry->type);
			ret= -1;
			goto out;
		}

		if (ret < 0) {
			DOUT_ERROR("PTN[%s] update failed, pos={0x%08x:0x%08x}.", 
				firmware_ptn_entry->name, firmware_ptn_entry->offset, firmware_ptn_entry->length);
			
			ret= -1;
			goto out;
		}
	}

out:
	return ret;
}

int _firmware_process(char* firmware, int firmware_size, char* device, uint32_t ptn_base, int upgrade) 
{
    struct dkmgt_ptn_table			*ptn_table = NULL;
    struct dkmgt_firmware_ptn_table *firmware_ptn_table = NULL;
    struct dkmgt_firmware_header 	*firmware_header = NULL;
    struct dkmgt_ptn_device_info 	*flash_devinfo = NULL;
    struct dkmgt_ptn_support_list 	*support_list = NULL;
    int 		ret = UPGRADE_SUCCESS;

    if ((NULL == firmware) ||  (ptn_base == 0) || (firmware_size <= 0)) {
        DOUT_ERROR("Invalid pass-in args, (%p,0x%X,%d)", firmware, ptn_base, firmware_size);
		ret = -UPGRADE_FAILED;
        goto out;
    }

    ptn_table = dkmgt_ptn_table_build(device, ptn_base);
    if (NULL == ptn_table) {
        DOUT_ERROR("Failed to build ptn_table of flash");
		ret = -UPGRADE_FAILED;
        goto out;
    }

#ifdef DEBUG
    dkmgt_ptn_table_dump(ptn_table);
#endif
	
    flash_devinfo = dkmgt_device_info_build(ptn_table);
    if (NULL == flash_devinfo) {
        DOUT_ERROR("Faield to build device info of flash");
		ret = -UPGRADE_FAILED;
        goto out;
    }
	
    firmware_header = _firmware_header_build(firmware, firmware_size);
    if (NULL == firmware_header) {
        DOUT_ERROR("Failed to build firmware header");
		ret = -UPGRADE_FAILED;
        goto out;
    }

	ret = _firmware_header_check(firmware, firmware_size, firmware_header, DKMGT_FIRMWARE_CHECK_DEFAULT);
    if (ret < 0) {
        goto out;
    }

	firmware_ptn_table = _firmware_ptn_table_build(firmware + firmware_header->header_length, 
		firmware_size - firmware_header->header_length);	
    if (NULL == firmware_ptn_table) {
        DOUT_ERROR("Failed to build firmware ptn_table");
		ret = -UPGRADE_FILE_INVALID;
        goto out;
    }

	support_list = dkmgt_support_list_build(firmware_ptn_table, firmware);
    if (NULL == support_list) {
        DOUT_ERROR("Faield to build supportlist of firmware.");
		ret = -UPGRADE_FAILED;
        goto out;
    }

    if (dkmgt_support_list_check(flash_devinfo, support_list) < 0) {
        DOUT_ERROR("Firmware is not allowed to upgrade into this device.");
		ret = -NOT_THIS_MODEL;
        goto out;
    }
    DOUT_INFO("Firmware is upgradable for this DEVICE. ");

	ret = -UPGRADE_CHECK_OK;
	if (upgrade)
	{
	    ret = _firmware_update_ptn(ptn_table, firmware_header, firmware_ptn_table, firmware, firmware_size);
	    if (ret < 0) {
	        DOUT_ERROR("Failed to upgrade firmware into this device.");
			ret = -UPGRADE_FAILED;
	        goto out;
	    }
		ret = -UPGRADE_SUCCESS;
	}


out:
    if (NULL != firmware_header) {
        free(firmware_header);
    }

    if (NULL != ptn_table) {
        free(ptn_table);
    }

    return (-ret);
}

int _emmc_firmware_process(char* firmware, int firmware_size, int upgrade)
{
    int 		bytes = 0;
    int 		ret = UPGRADE_SUCCESS;
    unsigned char md5_tmp[DKMGT_FIRMWARE_MD5_SIZE + 32] = {0}; /* 32 for "omada controller" */
    unsigned char md5_digest[DKMGT_FIRMWARE_MD5_SIZE] = {0};
    unsigned char md5_firmware[DKMGT_FIRMWARE_MD5_SIZE] = {0};
    char productinfo[32] = {0};

    if (firmware_size < DKMGT_FIRMWARE_MD5_SIZE)
    {
        ret = -UPGRADE_FILE_INVALID;
        goto out;
    }

    memset(productinfo, 0, sizeof(productinfo));
    #ifdef CONFIG_PRODUCT_INFO
    memcpy(productinfo, CONFIG_PRODUCT_INFO, strlen(CONFIG_PRODUCT_INFO));
    #else
    memcpy(productinfo, "OC200 v1.0", strlen("OC200 v1.0"));
    #endif

    /* copy md5 of firmware */
    memcpy(md5_firmware, firmware + firmware_size - DKMGT_FIRMWARE_MD5_SIZE, DKMGT_FIRMWARE_MD5_SIZE);

    _md5_calc(firmware, firmware_size - DKMGT_FIRMWARE_MD5_SIZE, md5_tmp);
    memcpy(md5_tmp + DKMGT_FIRMWARE_MD5_SIZE, productinfo, strlen(productinfo));
    _md5_calc((char* )md5_tmp, DKMGT_FIRMWARE_MD5_SIZE + strlen(productinfo), md5_digest);

    if (0 != memcmp(md5_digest, md5_firmware, DKMGT_FIRMWARE_MD5_SIZE))
    {
        ret = - UPGRADE_MD5_ERROR;
        goto out;
    }

    ret = -UPGRADE_CHECK_OK;
    if (upgrade)
    {
        /* write the whole emmc firmware */
        if (dkmgt_file_write_by_offset(NULL, 0, firmware, firmware_size - DKMGT_FIRMWARE_MD5_SIZE, &bytes) < 0)
        {
            DOUT_ERROR("Failed to upgrade emmc firmware into this device.");
            ret = -UPGRADE_FAILED;
            goto out;
        }
        ret = -UPGRADE_SUCCESS;
    }

out:
    return (-ret);
}

/**************************************************************************************************/
/*                                       PUBLIC_FUNCTIONS                                         */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       GLOBAL_FUNCTIONS                                         */
/**************************************************************************************************/
int dkmgt_firmware_check(char* firmware, int firmware_size) 
{
	/* check emmc firmware file first */
	if (UPGRADE_CHECK_OK == _emmc_firmware_process(firmware, firmware_size, 0))
		return UPGRADE_CHECK_OK;

	return _firmware_process(firmware, firmware_size, NULL, CONFIG_DKMGT_PARTITION_TABLE_BASE_ADDR, 0);
}

int dkmgt_firmware_upgrade(char* firmware, int firmware_size) 
{
	/* check emmc firmware file first */
	if (UPGRADE_SUCCESS == _emmc_firmware_process(firmware, firmware_size, 1))
		return UPGRADE_SUCCESS;

	return _firmware_process(firmware, firmware_size, NULL, CONFIG_DKMGT_PARTITION_TABLE_BASE_ADDR, 1);
}

int dkmgt_get_firmwareversion(char *frmwareversion, int len)
{
	struct dkmgt_ptn_header *ptn_header = NULL;
	cJSON * json_root = NULL;
	cJSON * json = NULL;
	int ptn_size = 0;
	char *ptn_buf = NULL;
	int ret = 0;
	
	ptn_buf = dkmgt_ptn_entry_read(NULL, CONFIG_DKMGT_PARTITION_TABLE_BASE_ADDR, "firmware-info", &ptn_size);
	if (ptn_buf == NULL)
		return -1;

	ptn_header = dkmgt_ptn_header_build(ptn_buf, ptn_size);
	if(NULL == ptn_header) {
		DOUT_ERROR("partition [%s] is not a valid partition.", "firmware-info");
		ret = -1;
		goto out;
	}
	 
	json_root = dkmgt_parse_json_data(ptn_buf + sizeof(struct dkmgt_ptn_header), ptn_header->length);
	if (NULL == json_root) {
		DOUT_ERROR("Failed to parse json.");
		ret = -1;
		goto out;
	}
	json = cJSON_GetObjectItem(json_root, "firmware-version");
	if (NULL == json) {
		DOUT_ERROR("ptn json 'name' not found.\n");
		ret = -1;
		goto out;
	}
	
	if (cJSON_String != json->type) {
		DOUT_ERROR("ptn json 'name' must be String type.\n");
		ret = -1;
		goto out;
	}
	
	snprintf(frmwareversion, len, "%s", json->valuestring);
	printf("firmware version is : %s\n", frmwareversion);
	
out:
	if (NULL != ptn_buf) {free(ptn_buf);}
	if (NULL != json_root) {cJSON_Delete(json_root);}
    if (NULL != ptn_header) {free(ptn_header);}
	
	return ret;
}

int dkmgt_get_mac(char *macstring, int len)
{
	struct dkmgt_ptn_header *ptn_header = NULL;
	cJSON * json_root = NULL;
	cJSON * json = NULL;
	int ptn_size = 0;
	char *ptn_buf = NULL;
	int ret = 0;
	
	ptn_buf = dkmgt_ptn_entry_read(NULL, CONFIG_DKMGT_PARTITION_TABLE_BASE_ADDR, "tddp", &ptn_size);
	if (ptn_buf == NULL)
		return -1;

	ptn_header = dkmgt_ptn_header_build(ptn_buf, ptn_size);
	if(NULL == ptn_header) {
		DOUT_ERROR("partition [%s] is not a valid partition.", "tddp");
		ret = -1;
		goto out;
	}
	 
	json_root = dkmgt_parse_json_data(ptn_buf + sizeof(struct dkmgt_ptn_header), ptn_header->length);
	if (NULL == json_root) {
		DOUT_ERROR("Failed to parse json.");
		ret = -1;
		goto out;
	}

	json = cJSON_GetObjectItem(json_root, "mac");
	if (NULL == json) {
		DOUT_ERROR("ptn json 'mac' not found.\n");
		ret = -1;
		goto out;
	}
	
	if (cJSON_String != json->type) {
		DOUT_ERROR("ptn json 'mac' must be String type.\n");
		ret = -1;
		goto out;
	}
	
	snprintf(macstring, len, "%s", json->valuestring);
	
out:
	if (NULL != ptn_buf) {free(ptn_buf);}
	if (NULL != json_root) {cJSON_Delete(json_root);}
	if (NULL != ptn_header) {free(ptn_header);}
	
	return ret;
}

int dkmgt_get_productinfo(char *productinfo, int len)
{
	struct dkmgt_ptn_header *ptn_header = NULL;
	cJSON * json_root = NULL;
	cJSON * json_devname = NULL;
	cJSON * json_devver = NULL;
	int ptn_size = 0;
	char *ptn_buf = NULL;
	int ret = 0;
	
	ptn_buf = dkmgt_ptn_entry_read(NULL, CONFIG_DKMGT_PARTITION_TABLE_BASE_ADDR, "device-info", &ptn_size);
	if (ptn_buf == NULL)
		return -1;

	ptn_header = dkmgt_ptn_header_build(ptn_buf, ptn_size);
	if(NULL == ptn_header) {
		DOUT_ERROR("partition [%s] is not a valid partition.", "device-info");
		ret = -1;
		goto out;
	}

	json_root = dkmgt_parse_json_data(ptn_buf + sizeof(struct dkmgt_ptn_header), ptn_header->length);
	if (NULL == json_root) {
		DOUT_ERROR("Failed to parse json.");
		ret = -1;
		goto out;
	}

	json_devname = cJSON_GetObjectItem(json_root, "product_name");
	if (NULL == json_devname) {
		DOUT_ERROR("ptn json 'product_name' not found.\n");
		ret = -1;
		goto out;
	}

	if (cJSON_String != json_devname->type) {
		DOUT_ERROR("ptn json 'product_name' must be String type.\n");
		ret = -1;
		goto out;
	}

	json_devver = cJSON_GetObjectItem(json_root, "product_version");
	if (NULL == json_devver) {
		DOUT_ERROR("ptn json 'product_version' not found.\n");
		ret = -1;
		goto out;
	}

	if (cJSON_String != json_devver->type) {
		DOUT_ERROR("ptn json 'product_version' must be String type.\n");
		ret = -1;
		goto out;
	}

	snprintf(productinfo, len, "%s v%s", json_devname->valuestring, json_devver->valuestring);
	
out:
	if (NULL != ptn_buf) {free(ptn_buf);}
	if (NULL != json_root) {cJSON_Delete(json_root);}
	if (NULL != ptn_header) {free(ptn_header);}
	
	return ret;
}

int dkmgt_factory(void)
{
	struct dkmgt_ptn_table* ptn_table = NULL;
	struct dkmgt_ptn_entry *ptn_entry = NULL;
	char zero_buf[1024*10] = {0};
	int ret_bytes = 0;
	int ret = 0;

	ptn_table = dkmgt_ptn_table_build(NULL, CONFIG_DKMGT_PARTITION_TABLE_BASE_ADDR);
	if (ptn_table == NULL){
		DOUT_ERROR("Failed to build ptn_table of flash");
	   ret = -1;   
	   goto out;
	}

	ptn_entry = dkmgt_ptn_get_ptn_entry(ptn_table, "user-config");
	if (ptn_entry == NULL) {
		DOUT_ERROR("PTN[%s] not found.", "user-config");
		ret = -1;
		goto out;
	}
	
	ret = dkmgt_file_write_by_offset(NULL, ptn_entry->base, zero_buf, sizeof(zero_buf), &ret_bytes);
	if (ret < 0) {
		DOUT_ERROR("PTN[%s] write zero failed.", "user-config");
		ret = -1;
		goto out;
	}
	
	ptn_entry = dkmgt_ptn_get_ptn_entry(ptn_table, "data");
	if (ptn_entry == NULL) {
		DOUT_ERROR("PTN[%s] not found.", "data");
		ret = -1;
		goto out;
	}
	
	ret = dkmgt_file_write_by_offset(NULL, ptn_entry->base, zero_buf, sizeof(zero_buf), &ret_bytes);
	if (ret < 0) {
		DOUT_ERROR("PTN[%s] write zero failed.", "data");
		ret = -1;
		goto out;
	}

out:
    if (NULL != ptn_table) {
        free(ptn_table);
    }

	return ret;
}

