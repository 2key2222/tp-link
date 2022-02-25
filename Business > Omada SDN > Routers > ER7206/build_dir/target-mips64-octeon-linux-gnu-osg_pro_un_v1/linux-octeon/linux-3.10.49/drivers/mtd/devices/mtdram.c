/*
 * mtdram - a test mtd device
 * Author: Alexander Larsson <alex@cendio.se>
 *
 * Copyright (c) 1999 Alexander Larsson <alex@cendio.se>
 * Copyright (c) 2005 Joern Engel <joern@wh.fh-wedel.de>
 *
 * This code is GPL
 *
 */

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/ioport.h>
#include <linux/vmalloc.h>
#include <linux/init.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/mtdram.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>
#include <linux/mount.h>
#include <linux/path.h>

static unsigned long total_size = CONFIG_MTDRAM_TOTAL_SIZE;
static unsigned long erase_size = CONFIG_MTDRAM_ERASE_SIZE;
#define MTDRAM_TOTAL_SIZE (total_size * 1024)
#define MTDRAM_ERASE_SIZE (erase_size * 1024)

#ifdef MODULE
module_param(total_size, ulong, 0);
MODULE_PARM_DESC(total_size, "Total device size in KiB");
module_param(erase_size, ulong, 0);
MODULE_PARM_DESC(erase_size, "Device erase block size in KiB");
#endif

// We could store these in the mtd structure, but we only support 1 device..
static struct mtd_info *mtd_info;
static dev_t squashfs_mtdroot_dev;
static dev_t squashfs_mtdram_dev;

static int ram_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	memset((char *)mtd->priv + instr->addr, 0xff, instr->len);
	instr->state = MTD_ERASE_DONE;
	mtd_erase_callback(instr);
	return 0;
}

static int ram_point(struct mtd_info *mtd, loff_t from, size_t len,
		size_t *retlen, void **virt, resource_size_t *phys)
{
	*virt = mtd->priv + from;
	*retlen = len;
	return 0;
}

static int ram_unpoint(struct mtd_info *mtd, loff_t from, size_t len)
{
	return 0;
}

/*
 * Allow NOMMU mmap() to directly map the device (if not NULL)
 * - return the address to which the offset maps
 * - return -ENOSYS to indicate refusal to do the mapping
 */
static unsigned long ram_get_unmapped_area(struct mtd_info *mtd,
					   unsigned long len,
					   unsigned long offset,
					   unsigned long flags)
{
	return (unsigned long) mtd->priv + offset;
}

static int ram_read(struct mtd_info *mtd, loff_t from, size_t len,
		size_t *retlen, u_char *buf)
{
	memcpy(buf, mtd->priv + from, len);
	*retlen = len;
	return 0;
}

static int ram_write(struct mtd_info *mtd, loff_t to, size_t len,
		size_t *retlen, const u_char *buf)
{
	memcpy((char *)mtd->priv + to, buf, len);
	*retlen = len;
	return 0;
}

static ssize_t mtdram_get_sysobj_attr(struct device *dev, struct device_attribute *attr, char *buf)
{
	if (squashfs_mtdroot_dev && squashfs_mtdram_dev) {
		return snprintf(buf, (ssize_t)PAGE_SIZE, "squashfs,rootdev=%d,ramdev=%d\n", squashfs_mtdroot_dev, squashfs_mtdram_dev);
	} else {
		return 0;
	}
}
static ssize_t mtdram_set_sysobj_attr(struct device *dev, struct device_attribute *attr, char *buf, size_t size)
{
	struct block_device *bdev = NULL;
	struct super_block *mtdroot_sblk = NULL;
	struct super_block *mtdram_sblk = NULL;
	char *p = buf;
	char *str = NULL;
	u8 root_min, root_maj;
	u8 ram_min, ram_maj;
	int len = 0;
	int err = 0;

	/* skip squashfs, */
	len = strlen("squashfs,");
	if (strncmp(p, "squashfs,", len)) {
		err = -EINVAL;
		goto errout;
	}
	p += len;

	/* skip ramdev= */
	len = strlen("rootdev=");
	if (strncmp(p, "rootdev=", len)) {
		err = -EINVAL;
		goto errout;
	}
	p += len;

	/* get & skip root maj */
	str = p;	
	if (!(p = strstr(p, ":"))) {
		err = -EINVAL;
		goto errout;
	}
	*p++ = '\0';
	if (kstrtos8(str, 0, &root_maj) < 0) {
		err = -EINVAL;
		goto errout;
	}
	/* get & skip root min */ 
	str = p;	
	if (!(p = strstr(p, ","))) {
		err = -EINVAL;
		goto errout;
	}
	*p++ = '\0';
	if (kstrtos8(str, 0, &root_min) < 0) {
		err = -EINVAL;
		goto errout;
	}

	/* skip ramdev */
	len = strlen("ramdev=");
	if (strncmp(p, "ramdev=", len)) {
		err = -EINVAL;
		goto errout;
	}
	p += len;

	/* get & skip root maj */
	str = p;	
	if (!(p = strstr(p, ":"))) {
		err = -EINVAL;
		goto errout;
	}
	*p++ = '\0';
	if (kstrtos8(str, 0, &ram_maj) < 0) {
		err = -EINVAL;
		goto errout;
	}
	/* get & skip root min */ 
	str = p;
	if (kstrtos8(str, 0, &ram_min) < 0) {
		err = -EINVAL;
		goto errout;
	}

	/* get mtdroot super block */
	bdev = bdget(MKDEV(root_maj, root_min));
	if (IS_ERR(bdev)) {
		printk(KERN_ERR"rootdev=%d,%d\n", root_maj, root_min);
		err = PTR_ERR(bdev);
		goto errout;
	}
	mtdroot_sblk = get_super(bdev);
	if (!mtdroot_sblk) {
		err = -ENODEV;
		bdput(bdev);
		goto errout;	
	}
	if (mtdroot_sblk->ram_sblk) {
		err = -EBUSY;
		bdput(bdev);
		drop_super(mtdroot_sblk);
		goto errout;
	}
	bdput(bdev);

	/* get mtdram super block */
	bdev = bdget(MKDEV(ram_maj, ram_min));
	if (IS_ERR(bdev)) {
		printk(KERN_ERR"ramdev=%d,%d, fs=%s\n", ram_maj, ram_min, current->fs->root.mnt->mnt_sb->s_type->name);
		err = PTR_ERR(bdev);
		drop_super(mtdroot_sblk);
		goto errout;
	}
	mtdram_sblk = get_super(bdev);
	if (!mtdram_sblk) {	
		err = -ENODEV;
		bdput(bdev);
		drop_super(mtdroot_sblk);
		goto errout;
	}
	bdput(bdev);

	/* bind mtdram super block to mtdroot super block */
	RCU_INIT_POINTER(mtdroot_sblk->ram_sblk, mtdram_sblk);
	printk(KERN_ERR"fs:%s, mtd(%d:%d) changed to mtd(%d:%d)\n", mtdroot_sblk->s_type->name, 
		MAJOR(mtdroot_sblk->s_dev), MINOR(mtdroot_sblk->s_dev), 
		MAJOR(mtdram_sblk->s_dev), MINOR(mtdram_sblk->s_dev));
	drop_super(mtdroot_sblk);
	// drop_super of mtdram_sblk by mtdroot_sblk's squashfs_kill_block_super.

	squashfs_mtdroot_dev = MKDEV(root_maj, root_min);
	squashfs_mtdram_dev  = MKDEV(ram_maj, ram_min);
	return size;

errout:
	return err;
}

static const struct device_attribute mtdram_sysobj_attr =
	__ATTR(mtdram, S_IWUSR | S_IRUGO, mtdram_get_sysobj_attr, mtdram_set_sysobj_attr);

static struct kobject *mtdram_sysobj;
static void __exit cleanup_mtdram(void)
{
	sysfs_remove_file(mtdram_sysobj, &mtdram_sysobj_attr.attr);
	kobject_put(mtdram_sysobj);
	if (mtd_info) {
		mtd_device_unregister(mtd_info);
		vfree(mtd_info->priv);
		kfree(mtd_info);
	}
}

static const char * const mtdram_part_types[] = {NULL};

int mtdram_init_device(struct mtd_info *mtd, void *mapped_address,
		unsigned long size, char *name)
{
	memset(mtd, 0, sizeof(*mtd));

	/* Setup the MTD structure */
	mtd->name = name;
	mtd->type = MTD_RAM;
	mtd->flags = MTD_CAP_RAM;
	mtd->size = size;
	mtd->writesize = 1;
	mtd->writebufsize = 64; /* Mimic CFI NOR flashes */
	mtd->erasesize = MTDRAM_ERASE_SIZE;
	mtd->priv = mapped_address;

	mtd->owner = THIS_MODULE;
	mtd->_erase = ram_erase;
	mtd->_point = ram_point;
	mtd->_unpoint = ram_unpoint;
	mtd->_get_unmapped_area = ram_get_unmapped_area;
	mtd->_read = ram_read;
	mtd->_write = ram_write;

	if (mtd_device_parse_register(mtd, mtdram_part_types, NULL, NULL, 0))
		return -EIO;

	return 0;
}

static int __init init_mtdram(void)
{
	void *addr;
	int err;

	if (!total_size)
		return -EINVAL;

	/* Allocate some memory */
	mtd_info = kmalloc(sizeof(struct mtd_info), GFP_KERNEL);
	if (!mtd_info)
		return -ENOMEM;

	addr = vmalloc(MTDRAM_TOTAL_SIZE);
	if (!addr) {
		kfree(mtd_info);
		mtd_info = NULL;
		return -ENOMEM;
	}
	err = mtdram_init_device(mtd_info, addr, MTDRAM_TOTAL_SIZE, "mtdram");
	if (err) {
		vfree(addr);
		kfree(mtd_info);
		mtd_info = NULL;
		return err;
	}
	memset(mtd_info->priv, 0xff, MTDRAM_TOTAL_SIZE);

	/*
	* Create sys/fast_classifier
	*/
	mtdram_sysobj = kobject_create_and_add("mtdram", NULL);
	if (!mtdram_sysobj) {
		printk(KERN_ERR"failed to register mtdram_sysobj\n");
		if (mtd_info) {
                	mtd_device_unregister(mtd_info);
                	vfree(mtd_info->priv);
                	kfree(mtd_info);
		}
		mtd_info = NULL;
		return -1;
	}

	err = sysfs_create_file(mtdram_sysobj, &mtdram_sysobj_attr.attr);
	if (err) {
		printk(KERN_ERR"failed to register debug dev: %d\n", err);
		kobject_put(mtdram_sysobj);
		if (mtd_info) {
                	mtd_device_unregister(mtd_info);
                	vfree(mtd_info->priv);
                	kfree(mtd_info);
		}
		mtd_info = NULL;
		return err;
	}
	return err;
}

module_init(init_mtdram);
module_exit(cleanup_mtdram);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Larsson <alexl@redhat.com>");
MODULE_DESCRIPTION("Simulated MTD driver for testing");
