#include <stdint.h>
#include <string.h>

#ifndef _TP_CREATE_PART_TABLE_H_
#define _TP_CREATE_PART_TABLE_H_

#define PART_TABLE_PRT(args,fmt...) do {	\
fprintf(stderr,"%s,func:%s,line %d:",__FILE__,__func__,__LINE__);\
fprintf(stderr,args,##fmt);\
fprintf(stderr,"\n");\
} while(0)
#define FLASH_LAYOUT_LEN	20
#define TP_FW_VERSION_LEN	60
#define TP_PART_MD5SUM	16
#define TP_NAME_LEN	30

#define FLASH_PART_TABLE_OFFS	0x01900000 /*in the  rootfs*/
#define FLASH_PART_TABLE_LEN	0x00010000 /*64k*/

#define FLASH_PART_UBOOT	"bootloader"
#define FLASH_PART_KERNEL	"kernel"
#define FLASH_PART_ROOTFS	"rootfs"
#define FLASH_PART_ROOTFS_DATA	"rootfs_data"
#define FLASH_PART_FIRMWARE		"firmware"
#define FLASH_PART_USER_CONFIG	"default_config"

#define FLASH_PART_TABLE		"part_table"
#define MAX_MTD_PART_TABLE_SIZE	10

#define TP_SUPPORT_LIST_LENGTH 20
#define FLASH_MD5_BUFFER_LEN	40
#define FLASH_CHECK_SUPPORT

typedef enum{
	IP_FALSE = 0,
	IP_TRUE
} IP_BOOL;

typedef struct TP_PARTITION_ITEM
{
	int id;
	char name[TP_NAME_LEN];
	unsigned int addr;
	int offset;
	int attr;
	char md5sum[TP_PART_MD5SUM+1];
	char parent[TP_NAME_LEN];
	struct TP_PARTITION_ITEM* next;
} TP_PARTITION_ITEM;

typedef struct FLASH_PART_TABLE_HEAD
{
	char	layout[FLASH_LAYOUT_LEN];/*make sure the layout is the same*/
	uint32_t	model;
	char	vendor_name[TP_NAME_LEN];
	char	fw_version[TP_FW_VERSION_LEN];
	char	support_list[TP_SUPPORT_LIST_LENGTH];
	char	kernel_file_md5sum[FLASH_MD5_BUFFER_LEN+1];
	char	rootfs_file_md5sum[FLASH_MD5_BUFFER_LEN+1];
#ifdef FLASH_CHECK_SUPPORT
    char    alias[TP_NAME_LEN];/*alias name*/
    uint32_t    product_id;/*support product id*/
    uint32_t    special_id;/*support special id*/
    char    magic_number;/*default magic number 0xa5*/
    uint32_t    hw_id;/*hardware informtion*/
    uint32_t    hw_rev;
    uint32_t    ver_hi;/*software information*/
    uint32_t    ver_mi;
    uint32_t    ver_lo;
#endif
} FLASH_PART_TABLE_HEAD;

/*provide interface to insert tplink-fw head info into json*/
IP_BOOL tplink_set_tp_fw_head(struct FLASH_PART_TABLE_HEAD *header);

/*provide interface to insert tplink-fw parition info into json*/
IP_BOOL tplink_part_table_init();
IP_BOOL tplink_part_table_add_elem(int id,char* part,int addr,int offset,int attr,char* parent);
IP_BOOL tplink_part_table_add_md5sum(char* part_name,char* md5sum);

IP_BOOL tplink_part_table_prt_all();
IP_BOOL tplink_part_table_prt_elem(int id);

/*functions are used to fill json.*/
IP_BOOL tplink_fill_json();
IP_BOOL tplink_generate_json(char* buf,char* out_name);

IP_BOOL tplink_part_table_free();

#endif /*~_TP_CREATE_PART_TABLE_H_*/
