/****************************************************************************
 *
 * <:copyright-BRCM:2015:DUAL/GPL:voice
 * 
 *    Copyright (c) 2015 Broadcom 
 *    All Rights Reserved
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * :>
 *
 ***************************************************************************/

#include <dsphal.h>

#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/mutex.h>


/****************************************************************************
* Typedefs and Constants
****************************************************************************/
#define DEBUG_BUF_SIZE      16384 /* Must be a power of 2 */

struct debug_chan_cfg
{
   struct dentry     *fp;
   unsigned int      started;
   wait_queue_head_t queue;
   spinlock_t        lock;
   struct med_buf    buf;

   uint64_t          num_copies;
   uint32_t          bufslips;
};

struct debug_cfg
{
   unsigned int          enabled;
   struct dhchancfg      *chan_cfg;
   struct debug_chan_cfg egress;
   struct debug_chan_cfg ingress;
};

struct debug_memcfg
{
   struct dentry  *fp;

   void           *mem;
   int            size;
   int            groupsize;

   struct list_head list;
};


/****************************************************************************
* Global Variables
****************************************************************************/
struct debug_stats debug_stats = { 0 };


#ifdef CONFIG_DEBUG_FS
/****************************************************************************
* Local function declaration
****************************************************************************/
#ifdef BRCM_VOICE_DSPHAL_CAPTURE
static int  dh_debug_start_channel(struct debug_chan_cfg *dc);
static void dh_debug_stop_channel(struct debug_chan_cfg *dc);
static void dh_debug_copy_data(struct debug_chan_cfg *dc, char *buf,
                               size_t size);

static int          dh_debug_open(struct inode *inode, struct file *filp);
static int          dh_debug_release(struct inode *inode, struct file *filp);
static ssize_t      dh_debug_read(struct file *filp, char __user *buf,
                                  size_t count, loff_t *f_pos);
static ssize_t      dh_debug_write(struct file *filp, const char __user *buf,
                                   size_t count, loff_t *f_pos);
static unsigned int dh_debug_poll(struct file *filp,
                                  struct poll_table_struct *wait);
#endif /* BRCM_VOICE_DSPHAL_CAPTURE */
static loff_t       dh_debug_llseek(struct file *filp, loff_t offset,
                                    int origin);
static int     dh_memdebug_open(struct inode *inode, struct file *filp);
static ssize_t dh_memdebug_read(struct file *filp, char __user *buf,
                                size_t count, loff_t *fpos);
static ssize_t dh_memdebug_write(struct file *filp, const char __user *buf,
                                 size_t count, loff_t *f_pos);

static void debug_time_stats(struct debug_time_ringbuf *start,
                             struct debug_time_ringbuf *end,
                             uint64_t *max, uint64_t *min,
                             uint64_t *avg, unsigned long *stdev);

/****************************************************************************
* Variables
****************************************************************************/
static struct dentry *dsphal_dir;
static struct dentry *mem_dir;

static struct debug_cfg debug_cfg[BP_MAX_VOICE_CHAN];
static LIST_HEAD(debug_memcfg_head);
static const struct file_operations memdbg_fops = {
   .owner    = THIS_MODULE,
   .llseek   = dh_debug_llseek,
   .open     = dh_memdebug_open,
   .read     = dh_memdebug_read,
   .write    = dh_memdebug_write,
};
#ifdef BRCM_VOICE_DSPHAL_CAPTURE
static const struct file_operations debug_fops = {
   .owner    = THIS_MODULE,
   .llseek   = dh_debug_llseek,
   .open     = dh_debug_open,
   .release  = dh_debug_release,
   .read     = dh_debug_read,
   .poll     = dh_debug_poll,
   .write    = dh_debug_write,
};
#endif /* BRCM_VOICE_DSPHAL_CAPTURE */

static const char *tick_source_str_map[] = {
   "none", 
   "kernel timer",
   "iudma",
   "dect",
};
DEFINE_MUTEX(print_lock);
#define DEFINE_SIMPLE_STRING(__fops, __read, __write)  \
static const struct file_operations __fops = {         \
   .owner    = THIS_MODULE,                            \
   .llseek   = dh_debug_llseek,                        \
   .read     = __read,                                 \
   .write    = __write,                                \
};

#define RING_INDEX(x, buf) ((x) & (unsigned int)(ARRAY_SIZE(buf) - 1))

#define DBPRINTF_SETUP() \
   char tmp[256];        \
   size_t size;          \
   ssize_t ret = 0;      \
   if(*f_pos) return 0;  \
   mutex_lock(&print_lock)

#define DBPRINTF_END()        \
   *f_pos += ret;             \
   mutex_unlock(&print_lock); \
   return ret

#define DBPRINTF(fmt, ...)                                    \
   do {                                                       \
      size_t uncopied = 0;                                    \
      size = scnprintf(tmp, sizeof(tmp), fmt, ##__VA_ARGS__); \
      uncopied = copy_to_user(&buf[ret], tmp, size);          \
      ret += (size - uncopied);                               \
   } while(0)


/****************************************************************************
* Function implementation
****************************************************************************/
#ifdef BRCM_VOICE_DSPHAL_CAPTURE
void dh_debug_setup_channel(struct dhchancfg *cfg)
{
   char debug_name[50];

   debug_cfg[cfg->id].enabled  = 1;
   debug_cfg[cfg->id].chan_cfg = cfg;

   /* Create egress HALCAP file */
   debug_cfg[cfg->id].egress.buf.size = DEBUG_BUF_SIZE;
   if(cfg->rate == DSPHAL_RATE_16KHZ)
      debug_cfg[cfg->id].egress.buf.size *= 2;
   sprintf(debug_name, "egress%d", cfg->id);
   debug_cfg[cfg->id].egress.fp = debugfs_create_file(debug_name, S_IRUSR,
         dsphal_dir, &debug_cfg[cfg->id].egress, &debug_fops);

   /* Create ingress HALCAP file */
   debug_cfg[cfg->id].ingress.buf.size = DEBUG_BUF_SIZE;
   if(cfg->rate == DSPHAL_RATE_16KHZ)
      debug_cfg[cfg->id].ingress.buf.size *= 2;
   sprintf(debug_name, "ingress%d", cfg->id);
   debug_cfg[cfg->id].ingress.fp = debugfs_create_file(debug_name, S_IRUSR,
         dsphal_dir, &debug_cfg[cfg->id].ingress, &debug_fops);
}

void dh_debug_close_channel(struct dhchancfg *cfg)
{
   if (debug_cfg[cfg->id].enabled)  
   {
      /* Make sure the egress and ingress channels are stopped */
      dh_debug_stop_channel(&debug_cfg[cfg->id].egress);
      dh_debug_stop_channel(&debug_cfg[cfg->id].ingress);

      debugfs_remove(debug_cfg[cfg->id].egress.fp);
      debugfs_remove(debug_cfg[cfg->id].ingress.fp);
      debug_cfg[cfg->id].enabled = 0;
   }
}

void dh_debug_egress(struct dhchancfg *cfg, char *buf, size_t size)
{
   debug_cfg[cfg->id].egress.num_copies++;
   dh_debug_copy_data(&debug_cfg[cfg->id].egress, buf, size);
}

void dh_debug_ingress(struct dhchancfg *cfg, char *buf, size_t size)
{
   debug_cfg[cfg->id].ingress.num_copies++;
   dh_debug_copy_data(&debug_cfg[cfg->id].ingress, buf, size);
}
#else
void dh_debug_setup_channel(struct dhchancfg *cfg) { }
void dh_debug_close_channel(struct dhchancfg *cfg) { }
void dh_debug_egress(struct dhchancfg *cfg, char *buf, size_t size) { }
void dh_debug_ingress(struct dhchancfg *cfg, char *buf, size_t size) { }
#endif /* BRCM_VOICE_DSPHAL_CAPTURE */

void dh_debug_bufslip(struct dhchancfg *cfg, enum direction dir)
{
   if(dir == DH_EGRESS) {
      debug_cfg[cfg->id].egress.bufslips++;
      debug_stats.total_underruns++;
   }
   else {
      debug_cfg[cfg->id].ingress.bufslips++;
      debug_stats.total_overruns++;
   }
}

#ifdef __arm__
#define clock_mask        0x3fffffff
#else
#define clock_mask        (unsigned long)-1
#endif
static unsigned int       clock_rate_usec;

inline unsigned long read_cpu_counter(void)
{
   unsigned long time;
#if defined(__arm__)
   time = sched_clock();
#elif defined(__AARCH64EL__)
   asm volatile("MRS %0, CNTPCT_EL0" : "=r" (time));
#else
   asm volatile("mfc0 %0,$9; nop" : "=r" (time));
#endif
   return time;
}

void dh_debug_record_time(struct debug_time_ringbuf *buf)
{
   int head;
   if(!debug_stats.enable_extended_stats)
      return;
   head = atomic_read(&buf->head);
   buf->time[head] = read_cpu_counter();

   atomic_set(&buf->head, RING_INDEX(head + 1, buf->time));
}

void dh_debug_isr(enum ticksource src)
{
   debug_stats.isr_counts[src]++;
}

void dh_debug_reg_mem(void *mem, int size, int groupsize, char *namefmt, ...)
{
   struct list_head    *pos;
   struct debug_memcfg *entry = NULL;
   char name[128];
   va_list vargs;

   list_for_each(pos, &debug_memcfg_head)
   {
      entry = list_entry(pos, struct debug_memcfg, list);
      if(entry->mem == mem)
      {
         DHLOG_WARNING("%s: memory at 0x%p is already registered\n", __func__,
                       mem);
         return;
      }
   }

   /* Add the entry to the list */
   if(list_empty(&debug_memcfg_head))
      mem_dir = debugfs_create_dir("mem", dsphal_dir);
   entry = kmalloc(sizeof(*entry), GFP_KERNEL);
   entry->mem        = mem;
   entry->size       = size;
   entry->groupsize  = groupsize;
   INIT_LIST_HEAD(&entry->list);
   list_add(&entry->list, &debug_memcfg_head);

   va_start(vargs, namefmt);
   vsnprintf(name, sizeof(name), namefmt, vargs);
   va_end(vargs);

   /* Add the entry to debugfs */
   entry->fp = debugfs_create_file(name, S_IRUSR, mem_dir, entry,
                                   &memdbg_fops);
}

void dh_debug_unreg_mem(void *mem)
{
   struct list_head    *pos;
   struct debug_memcfg *entry = NULL;

   list_for_each(pos, &debug_memcfg_head)
   {
      entry = list_entry(pos, struct debug_memcfg, list);
      if(entry->mem == mem)
      {
         DHLOG_DEBUG("%s: memory debug at 0x%p unregistered\n", __func__, mem);
         list_del(&entry->list);
         kfree(entry);
         break;
      }
   }

   if(list_empty(&debug_memcfg_head))
      debugfs_remove(mem_dir);
}

#ifdef BRCM_VOICE_DSPHAL_CAPTURE
static int dh_debug_start_channel(struct debug_chan_cfg *dc)
{
   unsigned int started;
   unsigned long flags;

   spin_lock_irqsave(&dc->lock, flags);
   started = dc->started;
   spin_unlock_irqrestore(&dc->lock, flags);

   if(started)
      return -EBUSY;

   dc->buf.buf = kzalloc(dc->buf.size, GFP_KERNEL);
   if(!dc->buf.buf) {
      DHLOG_ERR("%s: unable to allocate memory\n", __func__);
      return -ENOMEM;
   }
   atomic_set(&dc->buf.head, 0);
   atomic_set(&dc->buf.tail, 0);

   /* Enable the debug channel */
   spin_lock_irqsave(&dc->lock, flags);
   dc->started = 1;
   spin_unlock_irqrestore(&dc->lock, flags);

   return 0;
}

static void dh_debug_stop_channel(struct debug_chan_cfg *dc)
{
   unsigned long flags;

   /* Disable the debug channel */
   spin_lock_irqsave(&dc->lock, flags);
   dc->started = 0;
   spin_unlock_irqrestore(&dc->lock, flags);

   if(dc->buf.buf)
      kfree(dc->buf.buf);

   dc->buf.buf = NULL;

   wake_up_interruptible(&dc->queue);
}

static void dh_debug_copy_data(struct debug_chan_cfg *dc, char *buf,
                               size_t size)
{
   struct med_buf *media = &dc->buf;
   unsigned long head, tail, flags;
   size_t copy_size, space;

   spin_lock_irqsave(&dc->lock, flags);
   if(!dc->started)
      goto out;

   head = atomic_read(&media->head);
   tail = atomic_read(&media->tail);
   space = CIRC_SPACE(head, tail, media->size);
   copy_size = min(size, space);

   /* Copy buffer. If the buffer does not wrap, we can do the copy in one go.
    * If the buffer does wrap, we need to do the copy in two parts */
   if(head + copy_size < media->size)
      memcpy(&media->buf[head], &buf[0], copy_size);
   else
   {
      memcpy(&media->buf[head], &buf[0], media->size - head);
      memcpy(&media->buf[0], &buf[media->size - head],
             copy_size - (media->size - head));
   }

   /* Update the head and notify any waiting threads */
   atomic_set(&media->head, (head + copy_size) & (media->size - 1));

out:
   wake_up_interruptible(&dc->queue);
   spin_unlock_irqrestore(&dc->lock, flags);
}

static int dh_debug_open(struct inode *inode, struct file *filp)
{
   struct debug_chan_cfg *dc = inode->i_private;

   if(!dc)
      return -ENOENT;
   filp->private_data = dc;

   return dh_debug_start_channel(dc);
}

static int dh_debug_release(struct inode *inode, struct file *filp)
{
   struct debug_chan_cfg *dc = filp->private_data;

   if(!dc)
      return -ENOENT;

   dh_debug_stop_channel(dc);
   return 0;
}

static ssize_t dh_debug_read(struct file *filp, char __user *buf,
                             size_t count, loff_t *f_pos)
{
   struct debug_chan_cfg *dc = filp->private_data;
   struct med_buf *media;
   unsigned long head, tail, flags;
   size_t size;
   int ret;

   if(!dc)
      return -EINVAL;
   media = &dc->buf;

   spin_lock_irqsave(&dc->lock, flags);
   if(!dc->started)
   {
      spin_unlock_irqrestore(&dc->lock, flags);
      return 0;
   }
   spin_unlock_irqrestore(&dc->lock, flags);

   /* Check if we need to wait for new data */
   tail = atomic_read(&media->tail);
   if(CIRC_CNT(atomic_read(&media->head), tail, media->size) == 0)
   {
      ret = wait_event_interruptible(dc->queue,
            CIRC_CNT(atomic_read(&media->head), tail, media->size) > 0 ||
            !dc->started);
      if(ret)
         return ret;
      /* If we were woken up because the channel was disabled, return 0 */
      if(!dc->started)
         return 0;
   }

   /* Read the head just once and calculate how much data we should copy */
   head = atomic_read(&media->head);
   size = CIRC_CNT(head, tail, media->size);
   size = min(size, count);

   /* Copy buffer to userspace. If the buffer does not wrap, we can do 
    * the copy in one go. If the buffer does wrap, we need to do the copy
    * in two parts */
   if( tail + size < media->size )
      ret = copy_to_user(&buf[0], &media->buf[tail], size);
   else
   {
      ret = copy_to_user(&buf[0], &media->buf[tail],
                         media->size - tail);
      ret += copy_to_user(&buf[media->size - tail], &media->buf[0],
                          size - (media->size - tail));
   }

   /* Update the tail */
   atomic_set(&media->tail, (tail + (size - ret)) & (media->size - 1));

   if(ret)
      DHLOG_NOTICE("%s: Unable to copy data (%d)\n", __func__, ret);

   /* Return the number of bytes copied. In the case of no errors,
    * ret will be 0 */
   *f_pos += (size - ret);
   return size - ret;
}

static ssize_t dh_debug_write(struct file *filp, const char __user *buf,
                              size_t count, loff_t *f_pos)
{
   return -EINVAL;
}

static unsigned int dh_debug_poll(struct file *filp,
                                  struct poll_table_struct *wait)
{
   struct debug_chan_cfg *dc = filp->private_data;
   unsigned int mask = 0;
   unsigned long flags;

   if(!dc)
      return -EINVAL;

   /* Return if the channel is not started */
   spin_lock_irqsave(&dc->lock, flags);
   if(!dc->started)
   {
      spin_unlock_irqrestore(&dc->lock, flags);
      return 0;
   }
   spin_unlock_irqrestore(&dc->lock, flags);

   poll_wait(filp, &dc->queue, wait);
   if(CIRC_CNT(atomic_read(&dc->buf.head), atomic_read(&dc->buf.tail),
               dc->buf.size) > 0)
      mask |= POLLIN | POLLRDNORM;

   return mask;
}
#endif /* BRCM_VOICE_DSPHAL_CAPTURE */

static loff_t dh_debug_llseek(struct file *filp, loff_t offset, int origin)
{
   return -ESPIPE;
}

static int dh_memdebug_open(struct inode *inode, struct file *filp)
{
   struct debug_memcfg *mem = inode->i_private;

   if(!mem)
      return -ENOENT;
   filp->private_data = mem;
   return 0;
}

static ssize_t dh_memdebug_read(struct file *filp, char __user *buf,
                                size_t count, loff_t *f_pos)
{
   struct debug_memcfg *mem = filp->private_data;
   char linebuf[128] = {0};
   int rowsize = 16;
   int i;
   DBPRINTF_SETUP();

   for(i = 0; i < mem->size; i += rowsize)
   {
      if(i + rowsize > mem->size)
         rowsize = (i + rowsize) - mem->size;
      if(rowsize <= 0)
         break;

      hex_dump_to_buffer(mem->mem + i, rowsize, rowsize, mem->groupsize,
                         linebuf, sizeof(linebuf), 0);
      DBPRINTF("[0x%p]:  %s\n", mem->mem + i, linebuf);
   }
   DBPRINTF("\n");
   DBPRINTF_END();
}
static ssize_t dh_memdebug_write(struct file *filp, const char __user *buf,
                                 size_t count, loff_t *f_pos)
{
   return -EINVAL;
}

static ssize_t dh_hal_stats_read(struct file *filp, char __user *buf,
                                 size_t count, loff_t *f_pos)
{
   int i;
   DBPRINTF_SETUP();

   DBPRINTF("\t HAL STATISTICS\n");
   DBPRINTF("\t----------------\n");
   DBPRINTF("dsp clock source    : %s\n", (tick_owner < DH_TICK_SOURCE_MAX) ?
            tick_source_str_map[tick_owner] : "unknown");
   DBPRINTF("iudma interrupts    : %llu\n",
            debug_stats.isr_counts[DH_TICK_SOURCE_IUDMA]);
   DBPRINTF("iudma realigns      : %llu\n",
            debug_stats.dma_realigns[DH_TICK_SOURCE_IUDMA]);
   DBPRINTF("iudma restarts      : %llu\n",
            debug_stats.dma_restarts[DH_TICK_SOURCE_IUDMA]);
#ifdef CONFIG_BCM_DECT_SUPPORT
   DBPRINTF("dect dma interrupts : %llu\n",
            debug_stats.isr_counts[DH_TICK_SOURCE_DECT]);
   DBPRINTF("dect dma realigns   : %llu\n",
            debug_stats.dma_realigns[DH_TICK_SOURCE_DECT]);
#endif
#if defined(CONFIG_BCM96858)
   DBPRINTF("pcm tx underflow    : %d\n", debug_stats.tx_underflow_counter);
   DBPRINTF("pcm rx overflow     : %d\n", debug_stats.rx_overflow_counter);
#endif
   DBPRINTF("\n\t\t  Egress\t\t  Ingress\n");
   DBPRINTF("\t\t----------\t\t-----------\n");
   DBPRINTF("\t\tunderruns    : %llu", debug_stats.total_underruns);
   DBPRINTF("\toverruns     : %llu\n", debug_stats.total_overruns);
   for(i = 0; i < ARRAY_SIZE(debug_cfg); i++)
   {
      struct med_buf *eg, *in;
      if(!debug_cfg[i].enabled)
         continue;
      eg = &debug_cfg[i].chan_cfg->eg_buf;
      in = &debug_cfg[i].chan_cfg->ing_buf;

      DBPRINTF("\nchannel %d", i);

      DBPRINTF("\taudio copies : %llu", debug_cfg[i].egress.num_copies);
      DBPRINTF("\taudio copies : %llu\n", debug_cfg[i].ingress.num_copies);
      DBPRINTF("\t\tunderruns    : %u", debug_cfg[i].egress.bufslips);
      DBPRINTF("\toverruns     : %u\n", debug_cfg[i].ingress.bufslips);
      DBPRINTF("\t\tbuf size     : %u", CIRC_CNT(atomic_read(&eg->head),
                                                 atomic_read(&eg->tail),
                                                 eg->size));
      DBPRINTF("\tbuf size     : %u\n", CIRC_CNT(atomic_read(&in->head),
                                                 atomic_read(&in->tail),
                                                 in->size));
      DBPRINTF("\t\twatermark    : %u", eg->watermark);
      DBPRINTF("\twatermark    : %u\n", in->watermark);
   }

   DBPRINTF_END();
}

static ssize_t dh_hal_stats_write(struct file *file,
      const char __user *user_buf, size_t count, loff_t *ppos)
{
   int i;

   if (count) {
      debug_stats.total_underruns = 0;
      debug_stats.total_overruns = 0;
#if defined(CONFIG_BCM96858)
      debug_stats.tx_underflow_counter=0;
      debug_stats.rx_overflow_counter = 0;
#endif
      memset(&debug_stats.isr_counts, 0, sizeof(debug_stats.isr_counts));
      memset(&debug_stats.dma_realigns, 0, sizeof(debug_stats.dma_realigns));
      for (i = 0; i < ARRAY_SIZE(debug_cfg); i++) {
         debug_cfg[i].egress.num_copies = 0;
         debug_cfg[i].ingress.num_copies = 0;
         debug_cfg[i].egress.bufslips = 0;
         debug_cfg[i].ingress.bufslips = 0;
      }
      DHLOG_NOTICE("Cleared HAL stats\n");
   }
   return count;
}
DEFINE_SIMPLE_STRING(debug_hal_stats_fops, dh_hal_stats_read,
                     dh_hal_stats_write);

static ssize_t dh_dsp_stats_read(struct file *filp, char __user *buf,
                                 size_t count, loff_t *f_pos)
{
   DBPRINTF_SETUP();

   DBPRINTF("\t DSP STATISTICS\n");
   DBPRINTF("\t----------------\n");
   DBPRINTF("dsp rate           : %u msec\n", dsp_rate);
   DBPRINTF("clock source       : %s\n", (tick_owner < DH_TICK_SOURCE_MAX) ?
            tick_source_str_map[tick_owner] : "unknown");
   DBPRINTF("clock rate         : %u msec\n", tick_rate);
   DBPRINTF("tick_enabled       : %d\n", tick_enabled);
   DBPRINTF("hal ticks          : %llu\n", debug_stats.hal_tick_count);
   DBPRINTF("dsp ticks          : %llu\n", debug_stats.dsp_tick_count);
   DBPRINTF("dsp underruns      : %llu\n", debug_stats.dsp_underruns);
   DBPRINTF("peak dsp underruns : %llu\n", debug_stats.dsp_underruns_peak);

   DBPRINTF_END();
}

static ssize_t dh_dsp_stats_write(struct file *file,
      const char __user *user_buf, size_t count, loff_t *ppos)
{
   if (count) {
      debug_stats.hal_tick_count = 0;
      debug_stats.dsp_tick_count = 0;
      debug_stats.dsp_underruns = 0;
      debug_stats.dsp_underruns_peak = 0;
      DHLOG_NOTICE("Cleared DSP stats\n");
   }
   return count;
}
DEFINE_SIMPLE_STRING(debug_dsp_stats_fops, dh_dsp_stats_read,
                     dh_dsp_stats_write);

static void dh_debug_clear_extended_stats(void)
{
#define clear_time_ringbuf(buf) do { \
      memset(&buf, 0, sizeof(buf));  \
      atomic_set(&buf.head, 0);      \
   } while(0)

   clear_time_ringbuf(debug_stats.hal_tick);
   clear_time_ringbuf(debug_stats.dsp_start);
   clear_time_ringbuf(debug_stats.dsp_end);
   atomic_set(&debug_stats.dsp_end.head, DEBUG_STATS_RINGBUF_SIZE - 1);
}

static ssize_t dh_debug_enable_extended_read(struct file *file,
      char __user *user_buf, size_t count, loff_t *ppos)
{
   char buf[3];

   if (debug_stats.enable_extended_stats)
      buf[0] = 'Y';
   else
      buf[0] = 'N';
   buf[1] = '\n';
   buf[2] = 0x00;
   return simple_read_from_buffer(user_buf, count, ppos, buf, 2);
}

static ssize_t dh_debug_enable_extended_write(struct file *file,
      const char __user *user_buf, size_t count, loff_t *ppos)
{
   char buf[32];
   size_t buf_size;
   bool bv;

   buf_size = min(count, (sizeof(buf)-1));
   if (copy_from_user(buf, user_buf, buf_size))
      return -EFAULT;

   buf[buf_size] = '\0';

   if (strtobool(buf, &bv) == 0 && bv != debug_stats.enable_extended_stats)
   {
      /* If we are enabling the stats, make sure all the buffers are cleared */
      if(bv)
         dh_debug_clear_extended_stats();

      DHLOG_NOTICE("%sabling extended statistics\n", bv ? "En" : "Dis");
      debug_stats.enable_extended_stats = bv;
   }

   return count;
}
DEFINE_SIMPLE_STRING(debug_enable_extended_fops, dh_debug_enable_extended_read,
                     dh_debug_enable_extended_write);

static ssize_t dh_dsp_ext_stats_read(struct file *filp, char __user *buf,
                                     size_t count, loff_t *f_pos)
{
   uint64_t max, min, avg;
   unsigned long stdev;
   DBPRINTF_SETUP();

   DBPRINTF("\t EXTENDED DSP STATISTICS\n");
   DBPRINTF("\t-------------------------\n");
   DBPRINTF("      extended statistics : %s\n",
            debug_stats.enable_extended_stats ? "running" : "stopped");
   DBPRINTF("   num time samples saved : %d (%d msec)\n", DEBUG_STATS_RINGBUF_SIZE,
            DEBUG_STATS_RINGBUF_SIZE * dsp_rate);

   debug_time_stats(&debug_stats.hal_tick, NULL, &max, &min, &avg, &stdev);
   DBPRINTF("\n");
   DBPRINTF("                           (times in usec)\n");
   DBPRINTF("HAL tick rate         max : %llu\n", max);
   DBPRINTF("                  average : %llu\n", avg);
   DBPRINTF("                      min : %llu\n", min);
   DBPRINTF("                  std dev : %lu\n", stdev);

   debug_time_stats(&debug_stats.dsp_start, NULL, &max, &min, &avg, &stdev);
   DBPRINTF("\n");
   DBPRINTF("DSP tick rate         max : %llu\t\n", max);
   DBPRINTF("                  average : %llu\n", avg);
   DBPRINTF("                      min : %llu\n", min);
   DBPRINTF("                  std dev : %lu\n", stdev);

   debug_time_stats(&debug_stats.dsp_start, &debug_stats.dsp_end, &max, &min,
                    &avg, &stdev);
   DBPRINTF("\n");
   DBPRINTF("DSP run time          max : %llu\n", max);
   DBPRINTF("                  average : %llu\n", avg);
   DBPRINTF("                      min : %llu\n", min);
   DBPRINTF("                  std dev : %lu\n", stdev);

   debug_time_stats(&debug_stats.hal_tick, &debug_stats.dsp_start, &max, &min,
                    &avg, &stdev);
   DBPRINTF("\n");
   DBPRINTF("ISR->DSP start        max : %llu\n", max);
   DBPRINTF("                  average : %llu\n", avg);
   DBPRINTF("                      min : %llu\n", min);
   DBPRINTF("                  std dev : %lu\n", stdev);

   DBPRINTF_END();
}

static ssize_t dh_dsp_ext_stats_write(struct file *file,
      const char __user *user_buf, size_t count, loff_t *ppos)
{
   if(count) {
      unsigned int enabled = debug_stats.enable_extended_stats;
      debug_stats.enable_extended_stats = 0;
      dh_debug_clear_extended_stats();
      DHLOG_NOTICE("Cleared extended statistics\n");
      debug_stats.enable_extended_stats = enabled;
   }
   return count;
}
DEFINE_SIMPLE_STRING(debug_dsp_ext_stats_fops, dh_dsp_ext_stats_read,
                     dh_dsp_ext_stats_write);

void __init dh_debug_init(void)
{
   struct dentry *stats_dir;
   unsigned int i;

   memset(&debug_cfg, 0, sizeof(debug_cfg));
   memset(&debug_stats, 0, sizeof(debug_stats));
   for(i = 0; i < ARRAY_SIZE(debug_cfg); i++)
   {
      spin_lock_init(&debug_cfg[i].egress.lock);
      init_waitqueue_head(&debug_cfg[i].egress.queue);
      spin_lock_init(&debug_cfg[i].ingress.lock);
      init_waitqueue_head(&debug_cfg[i].ingress.queue);
   }

   dsphal_dir = debugfs_create_dir("dsphal", NULL);
   stats_dir  = debugfs_create_dir("stats", dsphal_dir);

   debugfs_create_file("dsp-stats", S_IRUGO | S_IWUSR, stats_dir, NULL,
                       &debug_dsp_stats_fops);
   debugfs_create_file("dsp-extended-stats", S_IRUGO | S_IWUSR, stats_dir,
                       NULL, &debug_dsp_ext_stats_fops);
   debugfs_create_file("hal-stats", S_IRUGO | S_IWUSR, stats_dir, NULL,
                       &debug_hal_stats_fops);
   debugfs_create_file("enable-extended-stats", S_IRUGO | S_IWUSR, stats_dir,
                       NULL, &debug_enable_extended_fops);
#ifdef __arm__
   clock_rate_usec = 1000;
#elif defined(__AARCH64EL__)
   asm volatile("MRS %0, CNTFRQ_EL0" : "=r" (clock_rate_usec));
   clock_rate_usec = clock_rate_usec / 1000000;   
#else
   clock_rate_usec = 200;
   debugfs_create_u32("mips-c0-rate-usec", S_IRUGO | S_IWUSR, stats_dir,
                      &clock_rate_usec);
#endif
}

void dh_debug_deinit(void)
{
   struct list_head    *pos;
   struct debug_memcfg *entry;

   debugfs_remove_recursive(dsphal_dir);

list_del:
   list_for_each(pos, &debug_memcfg_head)
   {
      entry = list_entry(pos, struct debug_memcfg, list);
      list_del(&entry->list);
      kfree(entry);
      goto list_del;
   }
}

static void debug_time_stats(struct debug_time_ringbuf *start,
                             struct debug_time_ringbuf *end,
                             uint64_t *max, uint64_t *min,
                             uint64_t *avg, unsigned long *stdev)
{
   uint64_t lmax = 0, lmin, lavg = 0, lvar = 0, tmp;
   unsigned long head_start, head_end;
   unsigned int i, count = 0;

   lmin = (uint64_t)-1;
   head_start = atomic_read(&start->head);
   if(end)
      head_end = atomic_read(&end->head);
   else
      head_end = head_start;

   /* Calculate min/max */
   i = max(head_start, head_end) + 2;
   do {
      if(end)
         tmp = end->time[i] - start->time[i];
      else
         tmp = start->time[i] - start->time[RING_INDEX(i - 1, start->time)];
      tmp &= clock_mask;

      if(tmp > lmax) lmax = tmp;
      if(tmp < lmin) lmin = tmp;
      lavg += tmp;
      count++;

      i = RING_INDEX(i + 1, end->time);
   } while(i != head_end);

   /* Calculate average */
   if(count)
      do_div(lavg, count * clock_rate_usec);

   /* Calculate variance */
   i = max(head_start, head_end) + 2;
   do {
      int64_t diff;

      if(end)
         tmp = end->time[i] - start->time[i];
      else
         tmp = start->time[i] - start->time[RING_INDEX(i - 1, start->time)];
      tmp &= clock_mask;
      do_div(tmp, clock_rate_usec);

      diff = (tmp - lavg) * (tmp - lavg);
      lvar += diff;

      i = RING_INDEX(i + 1, end->time);
   } while(i != head_end);
   if(count)
      do_div(lvar, count * clock_rate_usec);

   do_div(lmax, clock_rate_usec);
   do_div(lmin, clock_rate_usec);
   *max = lmax;
   *min = lmin;
   *avg = lavg;
   *stdev = int_sqrt(lvar);
}

#else /* !CONFIG_DEBUG_FS */

void dh_debug_init(void) { }
void dh_debug_deinit(void) { }
void dh_debug_setup_channel(struct dhchancfg *cfg) { }
void dh_debug_close_channel(struct dhchancfg *cfg) { }
void dh_debug_egress(struct dhchancfg *cfg, char *buf, size_t size) { }
void dh_debug_ingress(struct dhchancfg *cfg, char *buf, size_t size) { }
void dh_debug_bufslip(struct dhchancfg *cfg, enum direction dir) { }
void dh_debug_record_time(struct debug_time_ringbuf *buf) { }
void dh_debug_isr(enum ticksource src) { }

#endif
