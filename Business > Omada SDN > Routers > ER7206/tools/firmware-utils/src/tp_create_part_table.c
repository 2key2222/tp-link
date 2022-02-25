#include <stdio.h>
#include <stdlib.h>
#include "tp_create_part_table.h"
#include "cJSON.h"
#include "md5.h"

#define TP_JSON_FILE_LENGTH	0x10000
static struct TP_PARTITION_ITEM *tp_head_table = NULL;
static struct TP_PARTITION_ITEM *tp_tail_table = NULL;

static struct FLASH_PART_TABLE_HEAD *tp_fw_head = NULL;

static char md5sum_init[TP_PART_MD5SUM] = {
	0xdc, 0xd7, 0x3a, 0xa5, 0xc3, 0x95, 0x98, 0xfb,
	0xdd, 0xf9, 0xe7, 0xf4, 0x0e, 0xae, 0x47, 0x38,
};

static int get_md5(char *data, int size, char *md5)
{
	MD5_CTX ctx;

	MD5_Init(&ctx);
	MD5_Update(&ctx, data, size);
	MD5_Final(md5, &ctx);
}

static cJSON* root;

IP_BOOL tplink_part_table_init()
{
	if(NULL !=tp_head_table){
		tplink_part_table_free();
		tp_head_table = NULL;
		tp_tail_table = NULL;
	}
	return IP_TRUE;
}

struct TP_PARTITION_ITEM *get_part_by_id(int id)
{
	if(id < 0)	
		return NULL;

	struct TP_PARTITION_ITEM* tp_part_table = tp_head_table;
	while(NULL !=tp_part_table){
		if(id == tp_part_table->id){
			return tp_part_table;
		}
		tp_part_table = tp_part_table->next;
	}

	return NULL;
}

/*provide interface to insert tplink-fw head info into json*/
IP_BOOL tplink_set_tp_fw_head(struct FLASH_PART_TABLE_HEAD *header)
{
	if(NULL == tp_fw_head)
	{
		tp_fw_head = (struct FLASH_PART_TABLE_HEAD*)malloc(sizeof(struct FLASH_PART_TABLE_HEAD));
		if(NULL == tp_fw_head)
		{
			fprintf(stderr,"fail to malloc memory for tp_fw_head\n");
			return IP_FALSE;
		}
	}

	memcpy(tp_fw_head,header,sizeof(struct FLASH_PART_TABLE_HEAD));
	return IP_TRUE;
}

/*interface to insert partition table info*/
IP_BOOL tplink_part_table_add_elem(int id,char* part,int addr,int offset,int attr,char* parent)
{
	IP_BOOL found = IP_FALSE;
	if(NULL == part){
		PART_TABLE_PRT("part is invalid");
		return IP_FALSE;
	}
	struct TP_PARTITION_ITEM *tmp_item = get_part_by_id(id);

	if(NULL == tmp_item){
		tmp_item = (TP_PARTITION_ITEM*)malloc(sizeof(TP_PARTITION_ITEM));

		if(NULL == tmp_item)
		{
			PART_TABLE_PRT("fail to malloc memory for id(%d)",id);
			return IP_FALSE;
		}
		memset(tmp_item,0,sizeof(TP_PARTITION_ITEM));
	}else{
		found = IP_TRUE;
	}

	tmp_item->id = id;
	strncpy(tmp_item->name,part,TP_NAME_LEN);
	tmp_item->addr = addr;
	tmp_item->offset = offset;
	tmp_item->attr = attr;
	strncpy(tmp_item->parent,parent,TP_NAME_LEN);

	if(found == IP_FALSE){
		if(NULL == tp_head_table){
			tp_head_table	= tmp_item;
			tp_tail_table	= tmp_item;
			tmp_item->next	= NULL;
		}else{
			tmp_item->next		= tp_tail_table->next;

			tp_tail_table->next	= tmp_item;
			tp_tail_table		= tp_tail_table->next;
		}
	}

//	PART_TABLE_PRT("add part :%s: success",part);

	return IP_TRUE;
}

IP_BOOL tplink_part_table_add_md5sum(char* part_name,char* md5sum){
	if(NULL==part_name || NULL==md5sum){
		PART_TABLE_PRT("input arguments invalid");
		return IP_FALSE;
	}

	TP_PARTITION_ITEM* tmp_item = tp_head_table;
	if(NULL == tp_head_table){
		PART_TABLE_PRT("fail to get the tp_head_table");
		return IP_FALSE;
	}

	while(tmp_item != NULL){
		if(0==strcmp(part_name,tmp_item->name)){
			strncpy(tmp_item->md5sum,md5sum,TP_PART_MD5SUM+1);
			return IP_TRUE;
		}
		tmp_item = tmp_item->next;
	}

	PART_TABLE_PRT("fail to find the part(%s).",part_name);
	return IP_FALSE;
}

/*IP_BOOL tplink_part_table_del_elem(int id);*/
static void _print_md5sum(char* data){
	int i=0;
	if(NULL == data)
		return;
	else{
		for(;i<TP_PART_MD5SUM+1;i++){
			printf("%c",data[i]);
		}
	}
}
IP_BOOL tplink_part_table_prt_all(){
	struct TP_PARTITION_ITEM *tmp_item = tp_head_table;
	printf("\n---------------------------------------------------------------------------------------------\n");
	for(;NULL != tmp_item;tmp_item = tmp_item->next){
		printf("ID:0x%x,Part name:%20s, addr:0x%x,offset:0x%x,attr:0x%x,md5sum:",tmp_item->id, \
				tmp_item->name,tmp_item->addr,tmp_item->offset,tmp_item->attr);
		_print_md5sum(tmp_item->md5sum);
		printf("\n");
	}
	printf("\n---------------------------------------------------------------------------------------------\n");
}

IP_BOOL tplink_fill_json()
{
	cJSON *table,*item,*id,*name,*addr,*len,*attr;
	struct TP_PARTITION_ITEM* tmp_item = tp_head_table;

	root = cJSON_CreateObject();

	if(NULL == tmp_item || NULL==tp_head_table){
		PART_TABLE_PRT("tp_fw_head or the partition table is NULL");
		return IP_FALSE;
	}

	if(NULL != tp_fw_head){
		printf("ADD tp_fw_head for the json file\n");
		cJSON_AddStringToObject(root,"layout",tp_fw_head->layout);
		cJSON_AddStringToObject(root,"vendor_name",tp_fw_head->vendor_name);
		cJSON_AddStringToObject(root,"fw_version",tp_fw_head->fw_version);

		cJSON_AddStringToObject(root,"support_list",tp_fw_head->support_list);

		cJSON_AddStringToObject(root,"kernel_file_md5sum",tp_fw_head->kernel_file_md5sum);
		cJSON_AddStringToObject(root,"rootfs_file_md5sum",tp_fw_head->rootfs_file_md5sum);
		cJSON_AddNumberToObject(root,"model",tp_fw_head->model);
#ifdef FLASH_CHECK_SUPPORT
		cJSON_AddStringToObject(root,"alias",tp_fw_head->alias);
		cJSON_AddNumberToObject(root,"magic_number",tp_fw_head->magic_number);

		cJSON_AddNumberToObject(root,"hw_id",tp_fw_head->hw_id);
		cJSON_AddNumberToObject(root,"hw_rev",tp_fw_head->hw_rev);

		cJSON_AddNumberToObject(root,"ver_high",tp_fw_head->ver_hi);
		cJSON_AddNumberToObject(root,"ver_mid",tp_fw_head->ver_mi);
		cJSON_AddNumberToObject(root,"ver_low",tp_fw_head->ver_lo);
#endif

	}
	
	cJSON_AddItemToObject(root,"partition table",table=cJSON_CreateArray());
	for(;NULL != tmp_item;tmp_item = tmp_item->next)
	{
		printf("ADD elem for the json file\n");
		cJSON_AddItemToArray(table,item=cJSON_CreateObject());
		cJSON_AddNumberToObject(item,"id",tmp_item->id);
		cJSON_AddStringToObject(item,"name",tmp_item->name);
		cJSON_AddNumberToObject(item,"addr",tmp_item->addr);
		cJSON_AddNumberToObject(item,"offset",tmp_item->offset);
		cJSON_AddNumberToObject(item,"attr",tmp_item->attr);
		cJSON_AddStringToObject(item,"parent",tmp_item->parent);
		cJSON_AddStringToObject(item,"md5sum",tmp_item->md5sum);
	}

	return IP_TRUE;
}

IP_BOOL tplink_generate_json(char* buf,char* out_name)/*root is the global*/
{
	char* out;
	//FILE* json_file;
	int json_file_len;
	int wrt_len = 0;

	out = cJSON_Print(root);

//	printf("\n--------------------------------------\n");
//	printf("%s\n",out);
//	printf("\n--------------------------------------\n");

	//strncpy(p,&json_file_len,sizeof(int));
	/*save the json file*/
#if 0
	json_file = fopen(out_name,"w+");
	if(NULL == json_file){
		printf("fail to open the parition_table.json\n");
		return IP_FALSE;
	}
	/*add json head for part table*/
#endif
	memcpy(buf,out,strlen(out));
	
	//fprintf(json_file,"%s",out);

	//fflush(json_file);
	//fclose(json_file);
	
	free(out);

	return IP_TRUE;
}

IP_BOOL tplink_part_table_free()
{
	struct TP_PARTITION_ITEM* tmp_item = tp_head_table;
	while(tmp_item != NULL)
	{
		tp_head_table = tp_head_table->next;
		free(tmp_item);
		tmp_item = tp_head_table;
	}
	tp_head_table = NULL;
	tp_tail_table = NULL;

	if(NULL !=tp_fw_head){
		free(tp_fw_head);
		tp_fw_head = NULL;
	}
	if(NULL != root){
		cJSON_Delete(root);
		root = NULL;
	}
	return IP_TRUE;
}
