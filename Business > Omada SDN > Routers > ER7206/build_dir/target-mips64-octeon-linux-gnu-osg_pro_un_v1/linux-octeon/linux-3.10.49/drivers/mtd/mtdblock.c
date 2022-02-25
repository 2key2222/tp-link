/*
 * Direct MTD block device access
 *
 * Copyright © 1999-2010 David Woodhouse <dwmw2@infradead.org>
 * Copyright © 2000-2003 Nicolas Pitre <nico@fluxnic.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/vmalloc.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/blktrans.h>
#include <linux/mutex.h>


struct mtdblk_dev {
	struct mtd_blktrans_dev mbd;
	int count;
	struct mutex cache_mutex;
	unsigned char *cache_data;
	unsigned long cache_offset;
	unsigned int cache_size;
	enum { STATE_EMPTY, STATE_CLEAN, STATE_DIRTY } cache_state;
};

static DEFINE_MUTEX(mtdblks_lock);

#define MTD_FIRMWARE  "firmware"
#define MTD_SUPP_MAX  64
struct mtdblock_part {
	struct mtd_info *mtd;
	struct mtd_info *master;
	uint64_t size;
	uint64_t offset;
};

static DEFINE_MUTEX(g_mtd_parts_mutex);
static struct mtdblock_part g_mtd_parts[MTD_SUPP_MAX];

extern void (*mtd_partition_notify)(struct mtd_info *master, struct mtd_info *part, uint64_t offset, int reg);

static int mtd_get_part_start_block(struct mtd_info *mtd, unsigned long part_offset,
			unsigned long part_size, unsigned long offset)
{
	int block = 0; /* block count in mtd */
	int block_size = mtd->erasesize;
	int part_block = 0;	/* block count in part */
	int part_block_good = 0; /* good block count in part */

	block = (part_offset / block_size);
	while (part_block < (part_size / block_size)) {
		if (mtd_block_isbad(mtd, block * block_size) > 0) {
			block++;
			part_block++;
			continue;
		}
		part_block_good++;
		if ((offset - part_offset) >= (part_block_good * block_size)) {
			block++;
			part_block++;
			continue;
		}
		break;
	}
	return block;
}

/*
 * In this mtd, find which block the 'offset_in_mtd' belongs to,
 */
static int mtd_get_start_block(struct mtd_info *mtd, unsigned long offset)
{
	int i = 0;
	struct mtdblock_part *this  = NULL;
	struct mtdblock_part *part = NULL;

	if (strcasecmp(MTD_FIRMWARE, mtd->name)) {
		return mtd_get_part_start_block(mtd, 0, mtd->size, offset);
	}

	mutex_lock(&g_mtd_parts_mutex);
	/* find the self part of this mtd */
	for (i = 0; i < MTD_SUPP_MAX; i++) {
		part = &g_mtd_parts[i];	
		if (part->mtd == mtd) {
			this = part;
			break;
		}
	}
	if (!this) {
		part = NULL;
		goto out;
	}

	/* find which sub part the 'offset_in_mtd' belongs to */
	for (i = 0; i < MTD_SUPP_MAX; i++) {
		part = &g_mtd_parts[i];
		if (!part->mtd) {
			continue;
		}
		/* self */
		if (this == part) {
			continue;
		}
		/* not same master */
		if (this->master != part->master) {
			continue;
		}
		/* not sub part of this mtd */	
		if (part->offset < this->offset ||
			(part->offset + part->size) > (this->offset + this->size)) {
			continue;
		}
		/*  not belongs to this sub part */
		if (offset < part->offset || offset >= (part->offset + part->size)) {
			continue;
		}
		
		/* success to find out the sub part */
		break;
	}
	if (i >= MTD_SUPP_MAX) {
		part = NULL;
	}
out:
	mutex_unlock(&g_mtd_parts_mutex);

	return mtd_get_part_start_block(mtd, part ? part->offset : 0, part ? part->size : mtd->size, offset);
}

static void mtdblock_part_notify(struct mtd_info *master, struct mtd_info *part, uint64_t offset, int reg)
{
	if (!master) {
		return;
	}

	mutex_lock(&g_mtd_parts_mutex);
	if (reg) {
		if (!part || part->index >= MTD_SUPP_MAX) {
			goto out;
		}
		g_mtd_parts[part->index].mtd    = part;
		g_mtd_parts[part->index].master = master;
		g_mtd_parts[part->index].size   = part->size;
		g_mtd_parts[part->index].offset = offset;
		printk(KERN_ERR"mtdblock: add part:mtd(%s), master(%s), offset(0x%08llx), size(0x%08llx)\n",
			part->name, master->name, offset, part->size);
	} else {
		if (part) {
			if (part->index >= MTD_SUPP_MAX) {
				goto out;
			}
			g_mtd_parts[part->index].mtd    = NULL;
			g_mtd_parts[part->index].master = NULL;
			g_mtd_parts[part->index].size   = 0;
			g_mtd_parts[part->index].offset = 0;
			printk(KERN_ERR"mtdblock: del part:mtd(%s), master(%s)\n",
				part->name, master->name);
		} else {
			int i = 0;

			for (i = 0; i < MTD_SUPP_MAX; i++) {
				if (g_mtd_parts[i].master != master) {
					continue;
				}
				printk(KERN_ERR"mtdblock: del part:mtd(%s), master(%s)\n",
					g_mtd_parts[i].mtd->name, master->name);
				g_mtd_parts[i].mtd    = NULL;
				g_mtd_parts[i].master = NULL;
				g_mtd_parts[i].size   = 0;
				g_mtd_parts[i].offset = 0;
			}
		}	
	}
out:
	mutex_unlock(&g_mtd_parts_mutex);
}

/*
 * Cache stuff...
 *
 * Since typical flash erasable sectors are much larger than what Linux's
 * buffer cache can handle, we must implement read-modify-write on flash
 * sectors for each block write requests.  To avoid over-erasing flash sectors
 * and to speed things up, we locally cache a whole flash sector while it is
 * being written to until a different sector is required.
 */

static void erase_callback(struct erase_info *done)
{
	wait_queue_head_t *wait_q = (wait_queue_head_t *)done->priv;
	wake_up(wait_q);
}

static int erase_block (struct mtd_info *mtd, unsigned long pos)
{
	struct erase_info erase;
	DECLARE_WAITQUEUE(wait, current);
	wait_queue_head_t wait_q;
	int ret;

	/*
	 * First, let's erase the flash block.
	 */

	init_waitqueue_head(&wait_q);
	erase.mtd = mtd;
	erase.callback = erase_callback;
	erase.addr = pos;
	erase.len = mtd->erasesize;
	erase.priv = (u_long)&wait_q;

	set_current_state(TASK_INTERRUPTIBLE);
	add_wait_queue(&wait_q, &wait);

	ret = mtd_erase(mtd, &erase);
	if (ret) {
		set_current_state(TASK_RUNNING);
		remove_wait_queue(&wait_q, &wait);
		printk (KERN_WARNING "mtdblock: erase of region [0x%lx, 0x%x] "
				     "on \"%s\" failed\n",
			pos, mtd->erasesize, mtd->name);
		return ret;
	}

	schedule();  /* Wait for erase to finish. */
	remove_wait_queue(&wait_q, &wait);

	return 0;
}

/* skip bad blocks when write to nand flash mtd device. */
static int nand_erase_write (struct mtd_info *mtd, unsigned long offset,
			int len, const char *buf)
{
	int ret = 0;
	int block = 0;	/* block count in mtd */
	int block_size       = mtd->erasesize;
	int block_in_offset  = offset % block_size; /* the read offset from block head */
	int block_max_offset = block_size; /* the max offset from block head */
	int block_offset     = 0; /* the block's head offset from mtd head . */
	size_t write_len = 0;
	size_t retlen = 0;

	if ((offset % block_size) || (len % block_size)) {
		return -EINVAL;	/* pos & len should aligin to block size */
	}

	block = mtd_get_start_block(mtd, offset); /* In the mtd, find which block 'offset' belongs to */
	while (block < (mtd->size / block_size)) {
		block_offset = block * block_size;
		if (mtd_block_isbad(mtd, block_offset) > 0) {
			block++;
			continue;
		}
		/* first to erase block */
		ret = erase_block(mtd, block_offset);
		if (ret < 0) {
			if (ret == -EIO) {
				ret = mtd_block_markbad(mtd, block_offset);
				if (ret < 0 && ret != -EOPNOTSUPP) {
					printk(KERN_ERR "mtdblock: block_markbad failed, aborting\n");
					return -EIO;
				}
			}
			block++;
			continue;
		}

		/* write data to good erased block, block by block */
		if ((block_in_offset + len) > block_max_offset) {
			ret = mtd_write(mtd, block_offset + block_in_offset, block_max_offset - block_in_offset, &write_len, buf + retlen);
			if (ret) {
				return ret;
			}
			if (write_len != (block_max_offset - block_in_offset)) {
				return -EIO;
			}
			retlen = retlen + write_len;
			len     = len - write_len;
			block_in_offset = 0;
		} else {
			ret = mtd_write(mtd, block_offset + block_in_offset, len, &write_len, buf + retlen);
			if (ret) {
				return ret;
			}
			if (write_len != len) {
				return -EIO;
			}
			retlen = retlen + write_len;
			len     = len - write_len;
			break;
		}
		block++;
	}
	return 0;
}

/* skip bad blocks when read from nand flash mtd device. */
static int mtd_read_skip_bad(struct mtd_info *mtd, loff_t offset, size_t len, size_t *retlen,
         u_char *buf)
{
	int ret = 0;
	int block = 0;
	int block_size       = mtd->erasesize;
	int block_in_offset  = offset % block_size; /* the offset from block head */
	int block_max_offset = block_size; /* the max offset from block head */
	int block_offset     = 0; /* the block's head offset from mtd head . */
	size_t read_len      = 0;

	if (mtd->type != MTD_NANDFLASH) {
		return mtd_read(mtd, offset, len, retlen, buf);
	}

	block = mtd_get_start_block(mtd, offset); /* In the mtd, find which block 'offset' belongs to */
	*retlen = 0;
	while (block < (mtd->size / block_size)) {
		block_offset = block * block_size;
		if (mtd_block_isbad(mtd, block_offset) > 0) {
			block++;
			continue;
		}

		/* read data from mtd, block by block */
		if ((block_in_offset + len) > block_max_offset) {
			ret = mtd_read(mtd, block_offset + block_in_offset, block_max_offset - block_in_offset, &read_len, buf + *retlen);
			if (ret) {
				return ret;
			}
			*retlen = *retlen + read_len;
			len     = len - read_len;
			block_in_offset = 0;
		} else {
			ret = mtd_read(mtd, block_offset + block_in_offset, len, &read_len, buf + *retlen);
			if (ret) {
				return ret;
			}
			*retlen = *retlen + read_len;
			len     = len - read_len;
			break;
		}
		block++;
	}
	return 0;
}

static int erase_write (struct mtd_info *mtd, unsigned long pos,
			int len, const char *buf)
{
	struct erase_info erase;
	DECLARE_WAITQUEUE(wait, current);
	wait_queue_head_t wait_q;
	size_t retlen;
	int ret;

	if (mtd->type == MTD_NANDFLASH) {
		return nand_erase_write(mtd, pos, len, buf);
	}

	/*
	 * First, let's erase the flash block.
	 */

	init_waitqueue_head(&wait_q);
	erase.mtd = mtd;
	erase.callback = erase_callback;
	erase.addr = pos;
	erase.len = len;
	erase.priv = (u_long)&wait_q;

	set_current_state(TASK_INTERRUPTIBLE);
	add_wait_queue(&wait_q, &wait);

	ret = mtd_erase(mtd, &erase);
	if (ret) {
		set_current_state(TASK_RUNNING);
		remove_wait_queue(&wait_q, &wait);
		printk (KERN_WARNING "mtdblock: erase of region [0x%lx, 0x%x] "
				     "on \"%s\" failed\n",
			pos, len, mtd->name);
		return ret;
	}

	schedule();  /* Wait for erase to finish. */
	remove_wait_queue(&wait_q, &wait);

	/*
	 * Next, write the data to flash.
	 */

	ret = mtd_write(mtd, pos, len, &retlen, buf);
	if (ret)
		return ret;
	if (retlen != len)
		return -EIO;
	return 0;
}


static int write_cached_data (struct mtdblk_dev *mtdblk)
{
	struct mtd_info *mtd = mtdblk->mbd.mtd;
	int ret;

	if (mtdblk->cache_state != STATE_DIRTY)
		return 0;

	pr_debug("mtdblock: writing cached data for \"%s\" "
			"at 0x%lx, size 0x%x\n", mtd->name,
			mtdblk->cache_offset, mtdblk->cache_size);

	ret = erase_write (mtd, mtdblk->cache_offset,
			   mtdblk->cache_size, mtdblk->cache_data);
	if (ret)
		return ret;

	/*
	 * Here we could arguably set the cache state to STATE_CLEAN.
	 * However this could lead to inconsistency since we will not
	 * be notified if this content is altered on the flash by other
	 * means.  Let's declare it empty and leave buffering tasks to
	 * the buffer cache instead.
	 */
	mtdblk->cache_state = STATE_EMPTY;
	return 0;
}


static int do_cached_write (struct mtdblk_dev *mtdblk, unsigned long pos,
			    int len, const char *buf)
{
	struct mtd_info *mtd = mtdblk->mbd.mtd;
	unsigned int sect_size = mtdblk->cache_size;
	size_t retlen;
	int ret;

	pr_debug("mtdblock: write on \"%s\" at 0x%lx, size 0x%x\n",
		mtd->name, pos, len);

	if (!sect_size)
		return mtd_write(mtd, pos, len, &retlen, buf);

	while (len > 0) {
		unsigned long sect_start = (pos/sect_size)*sect_size;
		unsigned int offset = pos - sect_start;
		unsigned int size = sect_size - offset;
		if( size > len )
			size = len;

		if (size == sect_size) {
			/*
			 * We are covering a whole sector.  Thus there is no
			 * need to bother with the cache while it may still be
			 * useful for other partial writes.
			 */
			ret = erase_write (mtd, pos, size, buf);
			if (ret)
				return ret;
		} else {
			/* Partial sector: need to use the cache */

			if (mtdblk->cache_state == STATE_DIRTY &&
			    mtdblk->cache_offset != sect_start) {
				ret = write_cached_data(mtdblk);
				if (ret)
					return ret;
			}

			if (mtdblk->cache_state == STATE_EMPTY ||
			    mtdblk->cache_offset != sect_start) {
				/* fill the cache with the current sector */
				mtdblk->cache_state = STATE_EMPTY;
				ret = mtd_read_skip_bad(mtd, sect_start, sect_size,
					       &retlen, mtdblk->cache_data);
				if (ret)
					return ret;
				if (retlen != sect_size)
					return -EIO;

				mtdblk->cache_offset = sect_start;
				mtdblk->cache_size = sect_size;
				mtdblk->cache_state = STATE_CLEAN;
			}

			/* write data to our local cache */
			memcpy (mtdblk->cache_data + offset, buf, size);
			mtdblk->cache_state = STATE_DIRTY;
		}

		buf += size;
		pos += size;
		len -= size;
	}

	return 0;
}


static int do_cached_read (struct mtdblk_dev *mtdblk, unsigned long pos,
			   int len, char *buf)
{
	struct mtd_info *mtd = mtdblk->mbd.mtd;
	unsigned int sect_size = mtdblk->cache_size;
	size_t retlen;
	int ret;

	pr_debug("mtdblock: read on \"%s\" at 0x%lx, size 0x%x\n",
			mtd->name, pos, len);

	if (!sect_size)
		return mtd_read(mtd, pos, len, &retlen, buf);

	while (len > 0) {
		unsigned long sect_start = (pos/sect_size)*sect_size;
		unsigned int offset = pos - sect_start;
		unsigned int size = sect_size - offset;
		if (size > len)
			size = len;

		/*
		 * Check if the requested data is already cached
		 * Read the requested amount of data from our internal cache if it
		 * contains what we want, otherwise we read the data directly
		 * from flash.
		 */
		if (mtdblk->cache_state != STATE_EMPTY &&
		    mtdblk->cache_offset == sect_start) {
			memcpy (buf, mtdblk->cache_data + offset, size);
		} else {
			ret = mtd_read_skip_bad(mtd, pos, size, &retlen, buf);
			if (ret)
				return ret;
			if (retlen != size)
				return -EIO;
		}

		buf += size;
		pos += size;
		len -= size;
	}

	return 0;
}

static int mtdblock_readsect(struct mtd_blktrans_dev *dev,
			      unsigned long block, char *buf)
{
	struct mtdblk_dev *mtdblk = container_of(dev, struct mtdblk_dev, mbd);
	return do_cached_read(mtdblk, block<<9, 512, buf);
}

static int mtdblock_writesect(struct mtd_blktrans_dev *dev,
			      unsigned long block, char *buf)
{
	struct mtdblk_dev *mtdblk = container_of(dev, struct mtdblk_dev, mbd);
	if (unlikely(!mtdblk->cache_data && mtdblk->cache_size)) {
		mtdblk->cache_data = vmalloc(mtdblk->mbd.mtd->erasesize);
		if (!mtdblk->cache_data)
			return -EINTR;
		/* -EINTR is not really correct, but it is the best match
		 * documented in man 2 write for all cases.  We could also
		 * return -EAGAIN sometimes, but why bother?
		 */
	}
	return do_cached_write(mtdblk, block<<9, 512, buf);
}

static int mtdblock_open(struct mtd_blktrans_dev *mbd)
{
	struct mtdblk_dev *mtdblk = container_of(mbd, struct mtdblk_dev, mbd);

	pr_debug("mtdblock_open\n");

	mutex_lock(&mtdblks_lock);
	if (mtdblk->count) {
		mtdblk->count++;
		mutex_unlock(&mtdblks_lock);
		return 0;
	}

	/* OK, it's not open. Create cache info for it */
	mtdblk->count = 1;
	mutex_init(&mtdblk->cache_mutex);
	mtdblk->cache_state = STATE_EMPTY;
	if (!(mbd->mtd->flags & MTD_NO_ERASE) && mbd->mtd->erasesize) {
		mtdblk->cache_size = mbd->mtd->erasesize;
		mtdblk->cache_data = NULL;
	}

	mutex_unlock(&mtdblks_lock);

	pr_debug("ok\n");

	return 0;
}

static void mtdblock_release(struct mtd_blktrans_dev *mbd)
{
	struct mtdblk_dev *mtdblk = container_of(mbd, struct mtdblk_dev, mbd);

	pr_debug("mtdblock_release\n");

	mutex_lock(&mtdblks_lock);

	mutex_lock(&mtdblk->cache_mutex);
	write_cached_data(mtdblk);
	mutex_unlock(&mtdblk->cache_mutex);

	if (!--mtdblk->count) {
		/*
		 * It was the last usage. Free the cache, but only sync if
		 * opened for writing.
		 */
		if (mbd->file_mode & FMODE_WRITE)
			mtd_sync(mbd->mtd);
		vfree(mtdblk->cache_data);
	}

	mutex_unlock(&mtdblks_lock);

	pr_debug("ok\n");
}

static int mtdblock_flush(struct mtd_blktrans_dev *dev)
{
	struct mtdblk_dev *mtdblk = container_of(dev, struct mtdblk_dev, mbd);

	mutex_lock(&mtdblk->cache_mutex);
	write_cached_data(mtdblk);
	mutex_unlock(&mtdblk->cache_mutex);
	mtd_sync(dev->mtd);
	return 0;
}

static void mtdblock_add_mtd(struct mtd_blktrans_ops *tr, struct mtd_info *mtd)
{
	struct mtdblk_dev *dev = kzalloc(sizeof(*dev), GFP_KERNEL);

	if (!dev)
		return;

	dev->mbd.mtd = mtd;
	dev->mbd.devnum = mtd->index;

	dev->mbd.size = mtd->size >> 9;
	dev->mbd.tr = tr;

	if (!(mtd->flags & MTD_WRITEABLE))
		dev->mbd.readonly = 1;

	if (add_mtd_blktrans_dev(&dev->mbd))
		kfree(dev);
}

static void mtdblock_remove_dev(struct mtd_blktrans_dev *dev)
{
	del_mtd_blktrans_dev(dev);
}

static struct mtd_blktrans_ops mtdblock_tr = {
	.name		= "mtdblock",
	.major		= 31,
	.part_bits	= 0,
	.blksize 	= 512,
	.open		= mtdblock_open,
	.flush		= mtdblock_flush,
	.release	= mtdblock_release,
	.readsect	= mtdblock_readsect,
	.writesect	= mtdblock_writesect,
	.add_mtd	= mtdblock_add_mtd,
	.remove_dev	= mtdblock_remove_dev,
	.owner		= THIS_MODULE,
};

static int __init init_mtdblock(void)
{
	RCU_INIT_POINTER(mtd_partition_notify, mtdblock_part_notify);
	return register_mtd_blktrans(&mtdblock_tr);
}

static void __exit cleanup_mtdblock(void)
{
	RCU_INIT_POINTER(mtd_partition_notify, NULL);
	deregister_mtd_blktrans(&mtdblock_tr);
}

module_init(init_mtdblock);
module_exit(cleanup_mtdblock);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nicolas Pitre <nico@fluxnic.net> et al.");
MODULE_DESCRIPTION("Caching read/erase/writeback block device emulation access to MTD devices");
