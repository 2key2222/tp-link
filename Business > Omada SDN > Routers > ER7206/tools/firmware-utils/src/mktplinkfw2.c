/*
 * Copyright (C) 2009 Gabor Juhos <juhosg@openwrt.org>
 *
 * This tool was based on:
 *   TP-Link WR941 V2 firmware checksum fixing tool.
 *   Copyright (C) 2008,2009 Wang Jian <lark@linux.net.cn>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>     /* for unlink() */
#include <libgen.h>
#include <getopt.h>     /* for getopt() */
#include <stdarg.h>
#include <errno.h>
#include <sys/stat.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include "tp_create_part_table.h"

#include "md5.h"

#define ALIGN(x,a) ({ typeof(a) __a = (a); (((x) + __a - 1) & ~(__a - 1)); })

#define HEADER_VERSION_V1	0x01000000
/* Ö§³Ö WVR300 ¾µÏñ±àÒë  zhoushengyong  */
#define HWID_TL_WVR300_V1           0x03000001
#define HWID_TL_WVR300_V2           0x03000002
#define HWID_TL_WVR300_V3           0x03000003

//for wvr450g
#define HWID_TL_WVR450G         0x45000001
#define HWID_TL_WVR7520G		0x75200001
#define HWID_TL_WVR1300G         0x13000001

#define CMD_LEN					200

#define MD5SUM_LEN	16

static flash_layout_index = 0;

typedef struct FLASH_MTD_PART_TABLE
{
	uint32_t	id;
	char	*name;
	uint32_t	addr;
	uint32_t	length;
	uint32_t	attr;/*read, write*/
} FLASH_MTD_PART_TABLE;

struct NM_FLASH_LAYOUT{
	char*	layout;
	uint32_t	hw_id;
	uint32_t	hw_rev;
	uint32_t	part_table_size;
	FLASH_MTD_PART_TABLE	part_table[MAX_MTD_PART_TABLE_SIZE];
};

struct NM_FLASH_LAYOUT nm_flash_layout[]=
{
	{
		.layout	=	"32M",
		.hw_id	=	1,
		.hw_rev	=	0,
		.part_table_size	= 6,
		.part_table	={
			{
				.id		= 0,
				.name	= FLASH_PART_UBOOT,
				.addr	= 0x00000000,
				.length = 0x00200000,
				.attr	= 0x4,/*read only*/
			},{
				.id		= 1,
				.name	= FLASH_PART_KERNEL,
				.addr	= 0x00200000,
				.length = 0x00800000,
				.attr	= 0x6,
			},{
				.id		= 2,
				.name	= FLASH_PART_ROOTFS,
				.addr	= 0x00a00000,
				.length	= 0x00f00000,
				.attr	= 0x6,
			},{
				.id		= 3,
				.name	= FLASH_PART_ROOTFS_DATA,
				.addr	= 0x01a00000,
				.length	= 0x00500000,/*length?*/
				.attr	= 0x6,
			},{
				.id		= 4,
				.name	= FLASH_PART_USER_CONFIG,
				.addr	= 0x01900000,
				.length = 0x00100000,
				.attr	= 0x6,
			},{
				.id		= 5,
				.name	= FLASH_PART_FIRMWARE,
				.addr	= 0x00000000,
				.length = 0x02000000,
				.attr	= 0x6,
			}
		}
	}
};

struct file_info {
	char		*file_name;	/* name of the file */
	uint32_t	file_size;	/* length of the file */
};

/*add partition table*/
struct flash_layout {
	char		*id;
	uint32_t	fw_max_len;
	uint32_t	kernel_la;
	uint32_t	kernel_ep;
	uint32_t	uboot_ofs;
	uint32_t	uboot_len;
	uint32_t	kernel_ofs;
	uint32_t	partition_table_ofs;
	uint32_t	partition_table_len;
	uint32_t	rootfs_ofs;
};

struct board_info {
	char		*id;
	uint32_t	hw_id;
	uint32_t	hw_rev;
	char		*layout_id;
};

/*
 * Globals
 */
static char *ofname;
static char *progname;
static char *vendor = "TP-LINK Technologies";
static char *version = "ver. 1.0";
static char *fw_ver = "0.0.0";
static uint32_t model = 0;

static char *part_table_name = "partition_table.json";
static char *support_list="0.0.0";

static char *board_id;
static struct board_info *board;
static char *layout_id;
static struct flash_layout *layout;
static char *opt_hw_id;
static char *opt_hw_rev;
static uint32_t hw_id;
static uint32_t hw_rev;
static int fw_ver_lo;
static int fw_ver_mid;
static int fw_ver_hi;
static struct file_info kernel_info;
static uint32_t kernel_la = 0;
static uint32_t kernel_ep = 0;
static uint32_t kernel_len = 0;
static struct file_info rootfs_info;
static uint32_t rootfs_ofs = 0;
static uint32_t rootfs_align;
static struct file_info boot_info;
static int combined;
static int strip_padding;
static int add_jffs2_eof;
static unsigned char jffs2_eof_mark[4] = {0xde, 0xad, 0xc0, 0xde};

static struct file_info inspect_info;
static int extract = 0;

/*default value*/
static char* alias = "";
static uint32_t magic = 0xa6;

char md5salt_normal[MD5SUM_LEN] = {
	0xdc, 0xd7, 0x3a, 0xa5, 0xc3, 0x95, 0x98, 0xfb,
	0xdd, 0xf9, 0xe7, 0xf4, 0x0e, 0xae, 0x47, 0x38,
};

char md5salt_boot[MD5SUM_LEN] = {
	0x8c, 0xef, 0x33, 0x5b, 0xd5, 0xc5, 0xce, 0xfa,
	0xa7, 0x9c, 0x28, 0xda, 0xb2, 0xe9, 0x0f, 0x42,
};

static struct flash_layout layouts[] = {
	{
		.id		= "8M",
		.fw_max_len	= 0x7c0000,/*all firmware except uboot and partition table*/
		.kernel_la	= 0x80060000,
		.kernel_ep	= 0x80060000,
		.kernel_ofs = 0x30000,
		.rootfs_ofs	= 0x140000,
		.uboot_ofs	= 0x00000,
		.uboot_len	= 0x20000,
		.partition_table_ofs	= 0x20000,
		.partition_table_len	= 0x10000
	}, {
		.id		= "16M",
		.fw_max_len	= 0xfc0000,/*all firmware except uboot and partition table*/
		.kernel_la	= 0x80060000,
		.kernel_ep	= 0x80060000,
		.kernel_ofs = 0x40000,
		.rootfs_ofs	= 0x140000,
		.uboot_ofs	= 0x00000,
		.uboot_len	= 0x20000,
		.partition_table_ofs	= 0x20000,
		.partition_table_len	= 0x10000
	}, {
		.id		= "32M",
		.fw_max_len	= 0x01e10000,/*all firmware except uboot and partition table*/
		.kernel_la	= 0x80060000,
		.kernel_ep	= 0x80060000,
		.kernel_ofs = 0x00200000,
		.rootfs_ofs	= 0x01000000,
		.uboot_ofs	= 0x000000,
		.uboot_len	= 0x200000,
		.partition_table_ofs	= 0x001f0000,
		.partition_table_len	= 0x10000
	}, {
		/* terminating entry */
	}
};

static struct board_info boards[] = {
	 /* zhoushengyong Add  */ 
	{
		.id             = "TL-WVR450G",
		.hw_id          = HWID_TL_WVR450G,
		.hw_rev         = 1,
		.layout_id      = "8M"
	},{
		.id				= "TL_WVR7520G",
		.hw_id			= HWID_TL_WVR7520G,
		.hw_rev			= 1,
		.layout_id		= "32M"
	},{
		.id				= "TL_WVR1300G",
		.hw_id			= HWID_TL_WVR1300G,
		.hw_rev			= 1,
		.layout_id		= "16M"
	},
	{		/* terminating entry */
	}
};

/*
 * Message macros
 */
#define ERR(fmt,args...) do { \
	fflush(0); \
	fprintf(stderr, "[%s] *** error: " fmt "\n", \
			progname, ##args ); \
} while (0)

#define ERRS(fmt, ...) do { \
	int save = errno; \
	fflush(0); \
	fprintf(stderr, "[%s] *** error: " fmt "\n", \
			progname, ##__VA_ARGS__); \
} while (0)

#define DBG(fmt, ...) do { \
	fprintf(stderr, "[%s] " fmt "\n", progname, ## __VA_ARGS__ ); \
} while (0)

#define DBG_INFO_PRT(fmt,args...) do {				\
	printf("func:%s,line:%d",__func__,__LINE__);		\
	printf(fmt,##args);									\
	printf("\n");										\
	}while(0)

void set_flash_out_index(){
	flash_layout_index = 0;
}
static struct board_info *find_board(char *id)
{
	struct board_info *ret;
	struct board_info *board;

	ret = NULL;
	for (board = boards; board->id != NULL; board++){
		if (strcasecmp(id, board->id) == 0) {
			ret = board;
			break;
		}
	};

	return ret;
}

static struct board_info *find_board_by_hwid(uint32_t hw_id)
{
	struct board_info *board;

	for (board = boards; board->id != NULL; board++) {
		if (hw_id == board->hw_id)
			return board;
	};

	return NULL;
}

static struct flash_layout *find_layout(char *id)
{
	struct flash_layout *ret;
	struct flash_layout *l;

	ret = NULL;
	for (l = layouts; l->id != NULL; l++){
		if (strcasecmp(id, l->id) == 0) {
			ret = l;
			break;
		}
	};

	return ret;
}

static void usage(int status)
{
	FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;
	struct board_info *board;

	fprintf(stream, "Usage: %s [OPTIONS...]\n", progname);
	fprintf(stream,
"\n"
"Options:\n"
"  -A <alias name> set the alias name for the firmware(default "")\n"
"  -B <board>      create image for the board specified with <board>\n"
"  -c              use combined kernel image\n"
"  -H <hwid>       use hardware id specified with <hwid>\n"
"  -F <id>         use flash layout specified with <id>\n"
"  -k <file>       read kernel image from the file <file>\n"
"  -r <file>       read rootfs image from the file <file>\n"
"  -p <file>       save partition table default(partiton_table.json)\n"
"  -o <file>       write output to the file <file>\n"
"  -s              strip padding from the end of the image\n"
"  -N <vendor>     set image vendor to <vendor>\n"
"  -V <version>    set image version to <version>\n"
"  -v <version>    set firmware version to <version>\n"
"  -h              show this screen\n"
	);

	exit(status);
}

static int get_md5(char *data, int size, char *md5)
{
	MD5_CTX ctx;

	MD5_Init(&ctx);
	MD5_Update(&ctx, data, size);
	MD5_Final(md5, &ctx);
}

static int get_file_stat(struct file_info *fdata)
{
	struct stat st;
	int res;

	if (fdata->file_name == NULL)
		return 0;

	res = stat(fdata->file_name, &st);
	if (res){
		ERRS("stat failed on %s", fdata->file_name);
		return res;
	}

	fdata->file_size = st.st_size;
	return 0;
}

static int read_to_buf(struct file_info *fdata, char *buf)
{
	FILE *f;
	int ret = EXIT_FAILURE;

	f = fopen(fdata->file_name, "r");
	if (f == NULL) {
		ERRS("could not open \"%s\" for reading", fdata->file_name);
		goto out;
	}

	errno = 0;
	fread(buf, fdata->file_size, 1, f);
	if (errno != 0) {
		ERRS("unable to read from file \"%s\"", fdata->file_name);
		goto out_close;
	}

	ret = EXIT_SUCCESS;

 out_close:
	fclose(f);
 out:
	return ret;
}

static int check_options(void)
{
	int ret;

	if (inspect_info.file_name) {
		ret = get_file_stat(&inspect_info);
		if (ret)
			return ret;

		return 0;
	} else if (extract) {
		ERR("no firmware for inspection specified");
		return -1;
	}

	if (board_id == NULL && opt_hw_id == NULL) {
		ERR("either board or hardware id must be specified");
		return -1;
	}

	if (board_id) {
		board = find_board(board_id);
		if (board == NULL) {
			ERR("unknown/unsupported board id \"%s\"", board_id);
			return -1;
		}
		if (layout_id == NULL)
			layout_id = board->layout_id;

		hw_id = board->hw_id;
		hw_rev = board->hw_rev;
	} else {
		if (layout_id == NULL) {
			ERR("flash layout is not specified");
			return -1;
		}
		hw_id = strtoul(opt_hw_id, NULL, 0);

		if (opt_hw_rev)
			hw_rev = strtoul(opt_hw_rev, NULL, 0);
		else
			hw_rev = 1;
	}

	layout = find_layout(layout_id);
	if (layout == NULL) {
		ERR("unknown flash layout \"%s\"", layout_id);
		return -1;
	}

	if (!kernel_la)
		kernel_la = layout->kernel_la;
	if (!kernel_ep)
		kernel_ep = layout->kernel_ep;
	if (!rootfs_ofs)
		rootfs_ofs = layout->rootfs_ofs;

	if (kernel_info.file_name == NULL) {
		ERR("no kernel image specified");
		return -1;
	}

	ret = get_file_stat(&kernel_info);
	if (ret)
		return ret;

	kernel_len = kernel_info.file_size;

	if (combined) {
		if (kernel_info.file_size >
		    layout->fw_max_len - layout->partition_table_len/* - sizeof(struct fw_header)*/) {
			ERR("kernel image is too big");
			return -1;
		}
	} else {
		if (rootfs_info.file_name == NULL) {
			ERR("no rootfs image specified");
			return -1;
		}

		ret = get_file_stat(&rootfs_info);
		if (ret)
			return ret;

		if (rootfs_align) {
			/*kernel_len += sizeof(struct fw_header);*/
			kernel_len = ALIGN(kernel_len, rootfs_align);
			/*kernel_len -= sizeof(struct fw_header);*/

			DBG("kernel length aligned to %u", kernel_len);

			if (kernel_len + rootfs_info.file_size >
			    layout->fw_max_len - layout->partition_table_len/* - sizeof(struct fw_header)*/) {
				ERR("images are too big");
				return -1;
			}
		} else {
			if (kernel_info.file_size >
			    rootfs_ofs - layout->partition_table_len/* - sizeof(struct fw_header)*/) {
				ERR("kernel image is too big");
				return -1;
			}

			if (rootfs_info.file_size >
			    (layout->fw_max_len - rootfs_ofs - layout->partition_table_len)) {
				ERR("rootfs image is too big");
				return -1;
			}
		}
	}

	if (ofname == NULL) {
		ERR("no output file specified");
		return -1;
	}

	ret = sscanf(fw_ver, "%d.%d.%d", &fw_ver_hi, &fw_ver_mid, &fw_ver_lo);
	if (ret != 3) {
		ERR("invalid firmware version '%s'", fw_ver);
		return -1;
	}

	return 0;
}
/*out_buf is the json data to be created*/
static void create_partition_table(struct FLASH_PART_TABLE_HEAD* in_hdr)
{
	if(NULL==in_hdr)
	{
		ERR("invalid input arguments");
		exit(EXIT_FAILURE);
	}
	uint32_t part_id = 0;
	uint32_t attr;
	/*the size of rootfs ???*/
	tplink_part_table_init();

	tplink_set_tp_fw_head(in_hdr);
	/*add partition table*/
	for(;part_id< nm_flash_layout[flash_layout_index].part_table_size;++part_id)	{
		tplink_part_table_add_elem(nm_flash_layout[flash_layout_index].part_table[part_id].id,
									nm_flash_layout[flash_layout_index].part_table[part_id].name,
									nm_flash_layout[flash_layout_index].part_table[part_id].addr,
									nm_flash_layout[flash_layout_index].part_table[part_id].length,
									nm_flash_layout[flash_layout_index].part_table[part_id].attr,
									"");
	}
	/*partitin table + kernel + rootfs + part_data*/

	/*add part table*/
	/*tplink_part_table_add_elem(part_id++,
								FLASH_PART_TABLE,
								FLASH_PART_TABLE_OFFS,
								FLASH_PART_TABLE_LEN,
								0x06,
								FLASH_PART_ROOTFS);
	*/
}

static void destroy_partition_table(){
	tplink_part_table_free();
}

static void fill_header(char *buf, int len){
	if(NULL == buf){
		PART_TABLE_PRT("input buf is invalid");
	}
	memset(buf,0,len);

	tplink_part_table_prt_all();
	tplink_fill_json();
	tplink_generate_json(buf,part_table_name);
}

static void get_file_md5sum(char* file,char* out_put,unsigned int length){
	FILE *fp;
	char cmd[CMD_LEN];
	memset(cmd,0,CMD_LEN);
	sprintf(cmd,"md5sum %s|cut -d \" \" -f 1",file);
	printf("executing command: %s\n",cmd);
	fp=popen(cmd,"r");
	if(!fp){
		ERR("fail to get the md5sum");
	}
	fgets(out_put,length,fp);
	printf("output of the command: %s",out_put);
	fclose(fp);
}

static void init_json_table()
{
//	struct FLASH_PART_TABLE_HEAD *hdr = (struct FLASH_PART_TABLE_HEAD *)buf;
	struct FLASH_PART_TABLE_HEAD *hdr = (struct FLASH_PART_TABLE_HEAD *)malloc(sizeof(struct FLASH_PART_TABLE_HEAD));

	memset(hdr, 0, sizeof(struct FLASH_PART_TABLE_HEAD));

	strncpy(hdr->layout,nm_flash_layout[flash_layout_index].layout,sizeof(nm_flash_layout[flash_layout_index].layout));
	strncpy(hdr->vendor_name, vendor, TP_NAME_LEN);
	strncpy(hdr->fw_version, version, TP_FW_VERSION_LEN);
	strncpy(hdr->support_list, support_list,TP_SUPPORT_LIST_LENGTH);
//get the kernel file md5sum
	get_file_md5sum(kernel_info.file_name,hdr->kernel_file_md5sum,FLASH_MD5_BUFFER_LEN);
	get_file_md5sum(rootfs_info.file_name,hdr->rootfs_file_md5sum,FLASH_MD5_BUFFER_LEN);

	hdr->model = hw_id;

	/*hdr->kernel_ofs = htonl(sizeof(struct FLASH_PART_TABLE_HEAD));*/
#ifdef FLASH_CHECK_SUPPORT
	strncpy(hdr->alias,alias,TP_NAME_LEN);
	hdr->magic_number = magic;

	hdr->hw_id	= nm_flash_layout[flash_layout_index].hw_id;
	hdr->hw_rev	= nm_flash_layout[flash_layout_index].hw_rev;

	hdr->ver_hi = fw_ver_hi;
	hdr->ver_mi = fw_ver_mid;
	hdr->ver_lo = fw_ver_lo;
#endif
	/*	insert the partition table to the buf*/
	create_partition_table(hdr);

	free(hdr);
}

static int pad_jffs2(char *buf, int currlen)
{
	int len;
	uint32_t pad_mask;

	len = currlen;
	pad_mask = (64 * 1024);
	while ((len < layout->fw_max_len) && (pad_mask != 0)) {
		uint32_t mask;
		int i;

		for (i = 10; i < 32; i++) {
			mask = 1 << i;
			if (pad_mask & mask)
				break;
		}

		len = ALIGN(len, mask);

		for (i = 10; i < 32; i++) {
			mask = 1 << i;
			if ((len & (mask - 1)) == 0)
				pad_mask &= ~mask;
		}

		for (i = 0; i < sizeof(jffs2_eof_mark); i++)
			buf[len + i] = jffs2_eof_mark[i];

		len += sizeof(jffs2_eof_mark);
	}

	return len;
}

static int write_fw(char *data, int len)
{
	FILE *f;
	int ret = EXIT_FAILURE;

	f = fopen(ofname, "w");
	if (f == NULL) {
		ERRS("could not open \"%s\" for writing", ofname);
		goto out;
	}

	errno = 0;
	fwrite(data, len, 1, f);
	if (errno) {
		ERRS("unable to write output file");
		goto out_flush;
	}

	DBG("firmware file \"%s\" completed", ofname);

	ret = EXIT_SUCCESS;

 out_flush:
	fflush(f);
	fclose(f);
	if (ret != EXIT_SUCCESS) {
		unlink(ofname);
	}
 out:
	return ret;
}

static int build_fw(void)
{
	int buflen;
	char *buf;
	char *p;
	int ret = EXIT_FAILURE;
	int writelen = 0;
	char tmp_md5[TP_PART_MD5SUM+1];

	init_json_table();
	
	buflen = layout->fw_max_len;

	buf = malloc(buflen);
	if (!buf) {
		ERR("no memory for buffer\n");
		goto out;
	}

	memset(buf, 0xff, buflen);
	p = buf + FLASH_PART_TABLE_LEN;

	ret = read_to_buf(&kernel_info, p);
	if (ret)
		goto out_free_buf;

	//writelen = kernel_len + FLASH_PART_TABLE_LEN;
	writelen = FLASH_PART_TABLE_LEN + nm_flash_layout[flash_layout_index].part_table[1].length;

	/*get the md5 sum*/
	memset(tmp_md5,0,TP_PART_MD5SUM+1);
	get_md5(p,nm_flash_layout[flash_layout_index].part_table[1].length,tmp_md5);/*get the kenerl md5sum*/
	//PART_TABLE_PRT("kernel md5 value(%s)",tmp_md5);
	tplink_part_table_add_md5sum("kernel",tmp_md5);

	p = buf + writelen;

	/*write the rootfs*/
	ret = read_to_buf(&rootfs_info, p);
	if (ret)
		goto out_free_buf;

	memset(tmp_md5,0,TP_PART_MD5SUM+1);
	get_md5(p,nm_flash_layout[flash_layout_index].part_table[2].length,tmp_md5);
	//PART_TABLE_PRT("rootfs md5 value(%s)",tmp_md5);
	tplink_part_table_add_md5sum("rootfs",tmp_md5);

	if (!strip_padding)
		writelen = buflen;

	fill_header(buf, FLASH_PART_TABLE_LEN);

	//ret = write_fw(buf, writelen);
	ret = write_fw(buf,strlen(buf));
	if (ret)
		goto out_free_buf;

	ret = EXIT_SUCCESS;

 out_free_buf:
	free(buf);
 out:
	return ret;
}

/* Helper functions to inspect_fw() representing different output formats */
static inline void inspect_fw_pstr(char *label, char *str)
{
	printf("%-23s: %s\n", label, str);
}

static inline void inspect_fw_phex(char *label, uint32_t val)
{
	printf("%-23s: 0x%08x\n", label, val);
}

static inline void inspect_fw_phexpost(char *label,
                                       uint32_t val, char *post)
{
	printf("%-23s: 0x%08x (%s)\n", label, val, post);
}

static inline void inspect_fw_phexdef(char *label,
                                      uint32_t val, uint32_t defval)
{
	printf("%-23s: 0x%08x                  ", label, val);

	if (val == defval)
		printf("(== OpenWrt default)\n");
	else
		printf("(OpenWrt default: 0x%08x)\n", defval);
}

static inline void inspect_fw_phexexp(char *label,
                                      uint32_t val, uint32_t expval)
{
	printf("%-23s: 0x%08x ", label, val);

	if (val == expval)
		printf("(ok)\n");
	else
		printf("(expected: 0x%08x)\n", expval);
}

static inline void inspect_fw_phexdec(char *label, uint32_t val)
{
	printf("%-23s: 0x%08x / %8u bytes\n", label, val, val);
}

static inline void inspect_fw_phexdecdef(char *label,
                                         uint32_t val, uint32_t defval)
{
	printf("%-23s: 0x%08x / %8u bytes ", label, val, val);

	if (val == defval)
		printf("(== OpenWrt default)\n");
	else
		printf("(OpenWrt default: 0x%08x)\n", defval);
}

static inline void inspect_fw_pmd5sum(char *label, uint8_t *val, char *text)
{
	int i;

	printf("%-23s:", label);
	for (i=0; i<MD5SUM_LEN; i++)
		printf(" %02x", val[i]);
	printf(" %s\n", text);
}
#if 0
static int inspect_fw(void)
{
	char *buf;
	struct FLASH_PART_TABLE_HEAD *hdr;
	uint8_t md5sum[MD5SUM_LEN];
	struct board_info *board;
	int ret = EXIT_FAILURE;

	buf = malloc(inspect_info.file_size);
	if (!buf) {
		ERR("no memory for buffer!\n");
		goto out;
	}

	ret = read_to_buf(&inspect_info, buf);
	if (ret)
		goto out_free_buf;
/*	hdr = (struct FLASH_PART_TABLE_HEAD *)buf;*/
	hdr = (struct FLASH_PART_TABLE_HEAD *)malloc(sizeof(struct FLASH_PART_TABLE_HEAD));

	inspect_fw_pstr("File name", inspect_info.file_name);
	inspect_fw_phexdec("File size", inspect_info.file_size);

	if (ntohl(hdr->version) != HEADER_VERSION_V1) {
		ERR("file does not seem to have V1 header!\n");
		goto out_free_buf;
	}

	inspect_fw_phexdec("Version 1 Header size", sizeof(struct FLASH_PART_TABLE_HEAD));

	if (ntohl(hdr->unk1) != 0)
		inspect_fw_phexdec("Unknown value 1", hdr->unk1);

	memcpy(md5sum, hdr->md5sum1, sizeof(md5sum));
	if (ntohl(hdr->boot_len) == 0)
		memcpy(hdr->md5sum1, md5salt_normal, sizeof(md5sum));
	else
		memcpy(hdr->md5sum1, md5salt_boot, sizeof(md5sum));
	get_md5(buf, inspect_info.file_size, hdr->md5sum1);

	if (memcmp(md5sum, hdr->md5sum1, sizeof(md5sum))) {
		inspect_fw_pmd5sum("Header MD5Sum1", md5sum, "(*ERROR*)");
		inspect_fw_pmd5sum("          --> expected", hdr->md5sum1, "");
	} else {
		inspect_fw_pmd5sum("Header MD5Sum1", md5sum, "(ok)");
	}
	if (ntohl(hdr->unk2) != 0)
		inspect_fw_phexdec("Unknown value 2", hdr->unk2);
	inspect_fw_pmd5sum("Header MD5Sum2", hdr->md5sum2,
	                   "(purpose yet unknown, unchecked here)");
	if (ntohl(hdr->unk3) != 0)
		inspect_fw_phexdec("Unknown value 3", hdr->unk3);

	printf("\n");

	inspect_fw_pstr("Vendor name", hdr->vendor_name);
	inspect_fw_pstr("Firmware version", hdr->fw_version);
	board = find_board_by_hwid(ntohl(hdr->hw_id));
	if (board) {
		layout = find_layout(board->layout_id);
		inspect_fw_phexpost("Hardware ID",
		                    ntohl(hdr->hw_id), board->id);
		inspect_fw_phexexp("Hardware Revision",
		                   ntohl(hdr->hw_rev), board->hw_rev);
	} else {
		inspect_fw_phexpost("Hardware ID",
		                    ntohl(hdr->hw_id), "unknown");
		inspect_fw_phex("Hardware Revision",
		                ntohl(hdr->hw_rev));
	}

	printf("\n");

	inspect_fw_phexdec("Kernel data offset",
	                   ntohl(hdr->kernel_ofs));
	inspect_fw_phexdec("Kernel data length",
	                   ntohl(hdr->kernel_len));
	if (board) {
		inspect_fw_phexdef("Kernel load address",
		                   ntohl(hdr->kernel_la),
		                   layout ? layout->kernel_la : 0xffffffff);
		inspect_fw_phexdef("Kernel entry point",
		                   ntohl(hdr->kernel_ep),
		                   layout ? layout->kernel_ep : 0xffffffff);
		inspect_fw_phexdecdef("Rootfs data offset",
		                      ntohl(hdr->rootfs_ofs),
		                      layout ? layout->rootfs_ofs : 0xffffffff);
	} else {
		inspect_fw_phex("Kernel load address",
		                ntohl(hdr->kernel_la));
		inspect_fw_phex("Kernel entry point",
		                ntohl(hdr->kernel_ep));
		inspect_fw_phexdec("Rootfs data offset",
		                   ntohl(hdr->rootfs_ofs));
	}
	inspect_fw_phexdec("Rootfs data length",
	                   ntohl(hdr->rootfs_len));
	inspect_fw_phexdec("Boot loader data offset",
	                   ntohl(hdr->boot_ofs));
	inspect_fw_phexdec("Boot loader data length",
	                   ntohl(hdr->boot_len));
	inspect_fw_phexdec("Total firmware length",
	                   ntohl(hdr->fw_length));

	if (extract) {
		FILE *fp;
		char *filename;

		printf("\n");

		filename = malloc(strlen(inspect_info.file_name) + 8);
		sprintf(filename, "%s-kernel", inspect_info.file_name);
		printf("Extracting kernel to \"%s\"...\n", filename);
		fp = fopen(filename, "w");
		if (fp)	{
			if (!fwrite(buf + ntohl(hdr->kernel_ofs),
			            ntohl(hdr->kernel_len), 1, fp)) {
				ERR("error in fwrite(): %s", strerror(errno));
			}
			fclose(fp);
		} else {
			ERR("error in fopen(): %s", strerror(errno));
		}
		free(filename);

		filename = malloc(strlen(inspect_info.file_name) + 8);
		sprintf(filename, "%s-rootfs", inspect_info.file_name);
		printf("Extracting rootfs to \"%s\"...\n", filename);
		fp = fopen(filename, "w");
		if (fp)	{
			if (!fwrite(buf + ntohl(hdr->rootfs_ofs),
			            ntohl(hdr->rootfs_len), 1, fp)) {
				ERR("error in fwrite(): %s", strerror(errno));
			}
			fclose(fp);
		} else {
			ERR("error in fopen(): %s", strerror(errno));
		}
		free(filename);
	}

 out_free_buf:
	free(buf);
 out:
	return ret;
}
#endif
int main(int argc, char *argv[])
{
	int ret = EXIT_FAILURE;
	int err;

	FILE *outfile;

	progname = basename(argv[0]);

	while ( 1 ) {
		int c;

		/*c = getopt(argc, argv, "a:B:H:E:F:L:V:N:W:ci:k:r:R:o:xhsjv:");*/
		c = getopt(argc, argv, "a:A:B:H:F:V:M:N:W:S:ci:k:r:R:o:xhsjv:p:");
		if (c == -1)
			break;

		switch (c) {
		case 'a':
			sscanf(optarg, "0x%x", &rootfs_align);
			break;
		/*add by guiyongshi*/
		case 'A':
			alias = optarg;
			break;
		case 'B':
			board_id = optarg;
			break;
		case 'H':
			opt_hw_id = optarg;
			break;
		/*case 'E':
			sscanf(optarg, "0x%x", &kernel_ep);
			break;*/
		case 'F':
			layout_id = optarg;
			break;
		case 'W':
			opt_hw_rev = optarg;
			break;
		/*case 'L':
			sscanf(optarg, "0x%x", &kernel_la);
			break;*/
		case 'V':
			version = optarg;
			break;
		case 'v':
			fw_ver = optarg;
			break;
		case 'M':
			sscanf(optarg, "0x%x", &magic);
			break;
		case 'N':
			vendor = optarg;
			break;
		case 'c':
			combined++;
			break;
		case 'k':
			kernel_info.file_name = optarg;
			break;
		case 'r':
			rootfs_info.file_name = optarg;
			break;
		case 'R':
			sscanf(optarg, "0x%x", &rootfs_ofs);
			break;
		case 'o':
			ofname = optarg;
			break;
		case 's':
			strip_padding = 1;
			break;
		case 'S':
			support_list = optarg;
			break;
		case 'i':
			inspect_info.file_name = optarg;
			break;
		case 'j':
			add_jffs2_eof = 1;
			break;
		case 'x':
			extract = 1;
			break;
		case 'p':
			part_table_name = optarg;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	ret = check_options();
	if (ret)
		goto out;

	set_flash_out_index();
	ret = build_fw();
/*
	if (!inspect_info.file_name)
		ret = build_fw();
	else
		ret = inspect_fw();
*/

 out:
	return ret;
}

