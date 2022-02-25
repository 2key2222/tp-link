/*
 * Copyright (C) 2011 Gabor Juhos <juhosg@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/magic.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>


#define TPLINK_HEADER_V1	0x01000000
#define MD5SUM_LEN		16

struct tplink_fw_header {
	uint32_t	version;	/* header version */
	char		vendor_name[24];
	char		fw_version[36];
	uint32_t	hw_id;		/* hardware id */
	uint32_t	hw_rev;		/* hardware revision */
	uint32_t	unk1;
	uint8_t		md5sum1[MD5SUM_LEN];
	uint32_t	unk2;
	uint8_t		md5sum2[MD5SUM_LEN];
	uint32_t	unk3;
	uint32_t	kernel_la;	/* kernel load address */
	uint32_t	kernel_ep;	/* kernel entry point */
	uint32_t	fw_length;	/* total length of the firmware */
	uint32_t	kernel_ofs;	/* kernel data offset */
	uint32_t	kernel_len;	/* kernel data length */
	uint32_t	rootfs_ofs;	/* rootfs data offset */
	uint32_t	rootfs_len;	/* rootfs data length */
	uint32_t	boot_ofs;	/* bootloader data offset */
	uint32_t	boot_len;	/* bootloader data length */
	uint8_t		pad[360];
} __attribute__ ((packed));

static struct tplink_fw_header *
tplink_read_header(struct mtd_info *mtd, size_t offset)
{
	struct tplink_fw_header *header;
	size_t header_len;
	size_t retlen;
	int ret;
	u32 t;

	header = vmalloc(sizeof(*header));
	if (!header)
		goto err;

	header_len = sizeof(struct tplink_fw_header);
	ret = mtd_read(mtd, offset, header_len, &retlen,
		       (unsigned char *) header);
	if (ret)
		goto err_free_header;

	if (retlen != header_len)
		goto err_free_header;

	/* sanity checks */
	t = be32_to_cpu(header->version);
	if (t != TPLINK_HEADER_V1)
		goto err_free_header;

	t = be32_to_cpu(header->kernel_ofs);
	if (t != header_len)
		goto err_free_header;

	return header;

err_free_header:
	vfree(header);
err:
	return NULL;
}

static int tplink_check_rootfs_magic(struct mtd_info *mtd, size_t offset)
{
	u32 magic;
	size_t retlen;
	int ret;

	ret = mtd_read(mtd, offset, sizeof(magic), &retlen,
		       (unsigned char *) &magic);
	if (ret)
		return ret;

	if (retlen != sizeof(magic))
		return -EIO;

	if (le32_to_cpu(magic) != SQUASHFS_MAGIC &&
	    magic != 0x19852003)
		return -EINVAL;

	return 0;
}

#if  defined(CONFIG_MTK_MACH_TL_R470_V6) || defined(CONFIG_MTK_MACH_TL_R480_V9)
static int tplink_parse_partitions(struct mtd_info *master,
				   struct mtd_partition **pparts,
				   struct mtd_part_parser_data *data)
{
	struct mtd_partition *parts;
	int nr_parts;
	int ret;

	printk("@@-----debug tplink flash parse--------\n");
	nr_parts = 10;
	parts = kzalloc(nr_parts * sizeof(struct mtd_partition), GFP_KERNEL);
	if (!parts) {
		ret = -ENOMEM;
		*pparts = NULL;
		return ret;
	}

	parts[0].name   = "bootloader";
	parts[0].offset = 0x00000000;
	parts[0].size   = 0x00040000;

	parts[1].name   = "kernel";
	parts[1].offset = 0x00040000;
	parts[1].size   = 0x00150000;

	parts[2].name   = "rootfs";
	parts[2].offset = 0x00190000;
	parts[2].size   = 0x00b90000;

	parts[3].name   = "device-info";
	parts[3].offset = 0x00d20000;
	parts[3].size   = 0x00020000;

	parts[4].name   = "support-list";
	parts[4].offset = 0x00d40000;
	parts[4].size   = 0x00010000;

	parts[5].name   = "firmware-info";
	parts[5].offset = 0x00d50000;
	parts[5].size   = 0x00010000;

	parts[6].name   = "tddp";
	parts[6].offset = 0x00d60000;
	parts[6].size   = 0x00010000;

	parts[7].name   = "log";
	parts[7].offset = 0x00d70000;
	parts[7].size   = 0x00020000;

	parts[8].name   = "rootfs_data";
	parts[8].offset = 0x00e00000;
	parts[8].size   = 0x00200000;

	parts[9].name  = "firmware";
	parts[9].offset= 0x00000000;
	parts[9].size  = 0x01000000; /* the whole 16MB flash. */

	*pparts = parts;
	return nr_parts;
}
#elif  defined(CONFIG_MTK_MACH_TL_R605_V1)
static int tplink_parse_partitions(struct mtd_info *master,
				   struct mtd_partition **pparts,
				   struct mtd_part_parser_data *data)
{
	struct mtd_partition *parts;
	int nr_parts;
	int ret;

	printk("@@-----debug tplink flash parse--------\n");
	nr_parts = 14;
	parts = kzalloc(nr_parts * sizeof(struct mtd_partition), GFP_KERNEL);
	if (!parts) {
		ret = -ENOMEM;
		*pparts = NULL;
		return ret;
	}

	parts[0].name   = "bootloader";
	parts[0].offset = 0x00000000;
	parts[0].size   = 0x00040000;
	
	parts[1].name   = "bootloader-fs";
	parts[1].offset = 0x00040000;
	parts[1].size   = 0x00030000;
	
	parts[2].name   = "extra-para";
	parts[2].offset = 0x00070000;
	parts[2].size   = 0x00010000;

	parts[3].name   = "kernel";
	parts[3].offset = 0x00080000;
	parts[3].size   = 0x00180000;

	parts[4].name   = "rootfs";
	parts[4].offset = 0x00200000;
	parts[4].size   = 0x00bf0000;

	parts[5].name   = "panic-oops";
	parts[5].offset = 0x00df0000;
	parts[5].size   = 0x00020000;
	
	parts[6].name   = "partition-table";
	parts[6].offset = 0x00e10000;
	parts[6].size   = 0x00010000;

	parts[7].name   = "device-info";
	parts[7].offset = 0x00e20000;
	parts[7].size   = 0x00010000;

	parts[8].name   = "support-list";
	parts[8].offset = 0x00e30000;
	parts[8].size   = 0x00010000;

	parts[9].name   = "firmware-info";
	parts[9].offset = 0x00e40000;
	parts[9].size   = 0x00010000;

	parts[10].name   = "tddp";
	parts[10].offset = 0x00e50000;
	parts[10].size   = 0x00010000;

	parts[11].name   = "log";
	parts[11].offset = 0x00e60000;
	parts[11].size   = 0x00020000;

	parts[12].name   = "rootfs_data";
	parts[12].offset = 0x00e80000;
	parts[12].size   = 0x00180000;

	parts[13].name  = "firmware";
	parts[13].offset= 0x00000000;
	parts[13].size  = 0x01000000; /* the whole 16MB flash. */

	*pparts = parts;
	return nr_parts;
}
#else
static int tplink_parse_partitions(struct mtd_info *master,
				   struct mtd_partition **pparts,
				   struct mtd_part_parser_data *data)
{
	struct mtd_partition *parts;
	int nr_parts;
	int ret;

	printk("@@-----debug r470/r480 tplink flash parse--------\n");
	nr_parts = 10;
	parts = kzalloc(nr_parts * sizeof(struct mtd_partition), GFP_KERNEL);
	if (!parts) {
		ret = -ENOMEM;
		*pparts = NULL;
		return ret;
	}

	parts[0].name   = "bootloader";
	parts[0].offset = 0x00000000;
	parts[0].size   = 0x00040000;

	parts[1].name   = "kernel";
	parts[1].offset = 0x00040000;
	parts[1].size   = 0x00150000;

	parts[2].name   = "rootfs";
	parts[2].offset = 0x00190000;
	parts[2].size   = 0x00b90000;

	parts[3].name   = "device-info";
	parts[3].offset = 0x00d20000;
	parts[3].size   = 0x00020000;

	parts[4].name   = "support-list";
	parts[4].offset = 0x00d40000;
	parts[4].size   = 0x00010000;

	parts[5].name   = "firmware-info";
	parts[5].offset = 0x00d50000;
	parts[5].size   = 0x00010000;

	parts[6].name   = "tddp";
	parts[6].offset = 0x00d60000;
	parts[6].size   = 0x00010000;

	parts[7].name   = "log";
	parts[7].offset = 0x00d70000;
	parts[7].size   = 0x00020000;

	parts[8].name   = "rootfs_data";
	parts[8].offset = 0x00e00000;
	parts[8].size   = 0x00200000;

	parts[9].name  = "firmware";
	parts[9].offset= 0x00000000;
	parts[9].size  = 0x01000000; /* the whole 16MB flash. */

	*pparts = parts;
	return nr_parts;
}
#endif

static struct mtd_part_parser tplink_parser = {
	.owner		= THIS_MODULE,
	.parse_fn	= tplink_parse_partitions,
	.name		= "tp-link",
};

static int __init tplink_parser_init(void)
{
	return register_mtd_parser(&tplink_parser);
}

module_init(tplink_parser_init);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org>");
