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
#include <linux/cdev.h>
#include <linux/circ_buf.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/compat.h>

#include <dsphal_chip.h>
#include <dsphal_dect.h>


/****************************************************************************
* Local function declaration
****************************************************************************/
static int          dsphal_open(struct inode *inode, struct file *filp);
static int          dsphal_release(struct inode *inode, struct file *filp);
static long         dsphal_ioctl(struct file *filp, unsigned int cmd,
                                 unsigned long arg);
#ifdef CONFIG_COMPAT
static long         dsphal_compat_ioctl(struct file *filp, unsigned int cmd,
                                 unsigned long arg);
#endif
static loff_t       dsphal_llseek(struct file *filp, loff_t offset,
                                  int origin);
static ssize_t      dsphal_read(struct file *filp, char __user *buf,
                                size_t count, loff_t *f_pos);
static ssize_t      dsphal_write(struct file *filp, const char __user *buf,
                                 size_t count, loff_t *f_pos);
static unsigned int dsphal_poll(struct file *filp,
                                struct poll_table_struct *wait);

/****************************************************************************
* Variables
****************************************************************************/
struct dhdev      dhdev;
unsigned int      loglevel;
VOICE_BOARD_PARMS vp;
struct dhchancfg  chan_cfg[BP_MAX_VOICE_CHAN];
atomic_t          open_cnt[DSPHAL_INTF_MAX];
unsigned int      num_ept;

unsigned int      dsp_rate;
volatile int      tick_enabled;
enum ticksource   tick_owner;
unsigned int      tick_rate;
wait_queue_head_t tick_q;
atomic_t          tick;

DEFINE_SEMAPHORE(lock);

static const struct file_operations dsphal_fops = {
   .owner          = THIS_MODULE,
   .llseek         = dsphal_llseek,
#ifdef CONFIG_COMPAT
   .compat_ioctl   = dsphal_compat_ioctl,
#endif
   .unlocked_ioctl = dsphal_ioctl,
   .open           = dsphal_open,
   .release        = dsphal_release,
   .read           = dsphal_read,
   .poll           = dsphal_poll,
   .write          = dsphal_write,
};


/****************************************************************************
* Function implementation
****************************************************************************/

/*****************************************************************************
*  FUNCTION:   dsphal_open
*
*  PURPOSE:    Handle the driver opening
*
*  PARAMETERS: inode - pointer to the kernel inode struct
*              filp  - pointer to the kernel file struct
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
static int dsphal_open(struct inode *inode, struct file *filp)
{
   struct dhpriv *priv;

   /* Allocate and initialize data for this user */
   priv = kzalloc( sizeof(*priv), GFP_KERNEL );
   filp->private_data = priv;
   if(!priv)
      return -ENOMEM;

   atomic_inc(&dhdev.open_count);
   return 0;
}

/*****************************************************************************
*  FUNCTION:   dsphal_release
*
*  PURPOSE:    Handle the driver releasal
*
*  PARAMETERS: inode - pointer to the kernel inode struct
*              filp  - pointer to the kernel file struct
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
static int dsphal_release(struct inode *inode, struct file *filp)
{
   struct dhpriv *priv = (struct dhpriv*) filp->private_data;

   /* If we have allocated private data, make sure to clean it up */
   if(priv)
   {
      /* Disable the channel */
      if(priv->chancfg) {
         dh_disable_channel(priv->chancfg->id);
         dh_intf_release_handler(priv->chancfg);
      }

      /* If the dect task stops, make sure to deregister the DECT */
#ifdef CONFIG_BCM_DECT_SUPPORT
      if(priv->dect_handle)
         dect_set_stack_status(0);
#endif /* CONFIG_BCM_DECT_SUPPORT */

      kfree(priv);
   }

   if(atomic_dec_return(&dhdev.open_count) == 0)
      tick_enabled = 0;
   return 0;
}

/*****************************************************************************
*  FUNCTION:   dsphal_ioctl
*
*  PURPOSE:    Handle the driver ioctl
*
*  PARAMETERS: filp  - pointer to the kernel file struct
*              cmd   - ioctl number
*              arg   - ioctl argument
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
static long dsphal_ioctl(struct file *filp, unsigned int cmd,
                         unsigned long arg)
{
   long ret;
   int i;

   /* Try to find the appropriate ioctl handler */
   for(i = 0; ioctl_hdlr_table[i].cmd != DH_INVALID; i++)
   {
      if(ioctl_hdlr_table[i].cmd != cmd)
         continue;

      if(ioctl_hdlr_table[i].hdlr)
      {
         if(ioctl_hdlr_table[i].needs_lock)
         {
            if(down_interruptible(&lock))
               return -ERESTARTSYS;
         }

         ret = ioctl_hdlr_table[i].hdlr((struct dhpriv*)filp->private_data, arg);

         if(ioctl_hdlr_table[i].needs_lock)
            up(&lock);
         return ret;
      }

      DHLOG_WARNING("%s: No handler for ioctl (%u)\n", __func__, cmd);
      return 0;
   }

   DHLOG_ERR("%s: Invalid ioctl (%u)\n", __func__, cmd);
   return -EINVAL;
}

#ifdef CONFIG_COMPAT
/*****************************************************************************
*  FUNCTION:   dsphal_compat_ioctl
*
*  PURPOSE:    Handle the driver 32bit ioctl
*
*  PARAMETERS: filp  - pointer to the kernel file struct
*              cmd   - ioctl number
*              arg   - ioctl argument
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
static long dsphal_compat_ioctl(struct file *filp, unsigned int cmd,
                                unsigned long arg)
{
   /* A place-holder for pointer conversion in case it is required */
   return dsphal_ioctl(filp, cmd, arg);
}
#endif

/*****************************************************************************
*  FUNCTION:   dsphal_llseek
*
*  PURPOSE:    Handle the driver llseek
*
*  PARAMETERS: filp   - pointer to the kernel file struct
*              offset
*              origin
*
*  RETURNS:    -ESPIPE - llseek is not supported
*
*****************************************************************************/
static loff_t dsphal_llseek(struct file *filp, loff_t offset, int origin)
{
   return -ESPIPE;
}

/*****************************************************************************
*  FUNCTION:   dsphal_read
*
*  PURPOSE:    Handle the driver read
*
*  PARAMETERS: filp  - pointer to the drive file
*              buf   - userspace buffer
*              count - requested length to read
*              fpos  - file offset
*
*  RETURNS:    number of bytes read on success, error code otherwise
*
*****************************************************************************/
static ssize_t dsphal_read(struct file *filp, char __user *buf, size_t count,
                           loff_t *f_pos)
{
   struct dhpriv* priv = (struct dhpriv*)filp->private_data;
   struct med_buf *media;
   unsigned long head, tail;
   size_t size;
   int ret;

   /* Validation checks */
   if(!priv || !priv->chancfg)
   {
      DHLOG_ERR("%s: read without channel configured\n", __func__);
      return -EINVAL;
   }
   if(!buf || !count)
   {
      DHLOG_ERR("%s: no buffer or invalid size\n", __func__);
      return -EINVAL;
   }

   media = &priv->chancfg->ing_buf;

   /* Return if the channel is not enabled */
   spin_lock(&priv->chancfg->lock);
   if(!priv->chancfg->enabled)
   {
      spin_unlock(&priv->chancfg->lock);
      return 0;
   }
   spin_unlock(&priv->chancfg->lock);

   /* Check if we need to wait for new data */
   tail = atomic_read(&media->tail);
   if(CIRC_CNT(atomic_read(&media->head), tail, media->size) == 0)
   {
#ifdef DSPHAL_BLOCKING_READ
      ret = wait_event_interruptible(priv->chancfg->queue,
            CIRC_CNT(atomic_read(&media->head), tail, media->size) > 0 ||
            !priv->chancfg->enabled);
      if(ret)
         return ret;
      /* If we were woken up because the channel was disabled, return 0 */
      if(!priv->chancfg->enabled)
         return 0;
#else
      return 0;
#endif
   }

   /* Read the head just once and calculate how much data we should copy */
   head = atomic_read(&media->head);
   size = CIRC_CNT(head, tail, media->size);
   size = min(size, count);
   /* Make sure size is even */
   size &= ~1;

   /* Copy buffer to userspace. If the buffer does not wrap, we can do 
    * the copy in one go. If the buffer does wrap, we need to do the copy
    * in two parts */
   if( tail + size < media->size )
      ret = copy_to_user(buf, &media->buf[tail], size);
   else
   {
      ret  = copy_to_user(buf, &media->buf[tail],
                          media->size - tail);
      ret += copy_to_user(&buf[media->size - tail], &media->buf[0],
                          size - (media->size - tail));
   }

   /* Update the tail */
   atomic_set(&media->tail, (tail + (size - ret)) & (media->size - 1));

   /* If there is still media in the buffer after copying, flush it */
   if(tail != atomic_read(&media->head))
   {
      atomic_set(&media->tail, head);
      media->watermark = 0;
   }

   if(ret)
      DHLOG_NOTICE("%s: Unable to copy data (%d)\n", __func__, ret);

   /* Return the number of bytes copied. In the case of no errors,
    * ret will be 0 */
   *f_pos += (size - ret);
   return size - ret;
}

/*****************************************************************************
*  FUNCTION:   dsphal_write
*
*  PURPOSE:    Handle the driver write
*
*  PARAMETERS: filp  - pointer to the drive file
*              buf   - userspace buffer
*              count - requested length to write
*              fpos  - file offset
*
*  RETURNS:    number of bytes written on success, error code otherwise
*
*****************************************************************************/
static ssize_t dsphal_write(struct file *filp, const char __user *buf,
                            size_t count, loff_t *f_pos)
{
   struct dhpriv* priv = (struct dhpriv*)filp->private_data;
   struct med_buf *media;
   unsigned long head, tail;
   size_t size;
   int ret;

   /* Validation checks */
   if(!priv || !priv->chancfg)
   {
      DHLOG_ERR("%s: write without channel configured\n", __func__);
      return -EINVAL;
   }
   if(!buf || !count)
   {
      DHLOG_ERR("%s: no buffer or invalid size\n", __func__);
      return -EINVAL;
   }

   media = &priv->chancfg->eg_buf;

   /* Return if the channel is not enabled */
   spin_lock(&priv->chancfg->lock);
   if(!priv->chancfg->enabled)
   {
      spin_unlock(&priv->chancfg->lock);
      return 0;
   }
   spin_unlock(&priv->chancfg->lock);

   /* Read the tail just once and calculate how much data we should copy */
   head = atomic_read(&media->head);
   tail = atomic_read(&media->tail);
   size = CIRC_SPACE(head, tail, media->size);
   size = min(size, count);
   /* Make sure size is even */
   size &= ~1;

   /* Copy buffer from userspace. If the buffer does not wrap, we can do the
    * copy in one go. If the buffer does wrap, we need to do the copy in two
    * parts */
   if( head + size < media->size )
      ret  = copy_from_user(&media->buf[head], buf, size);
   else
   {
      ret  = copy_from_user(&media->buf[head], buf, media->size - head);
      ret += copy_from_user(&media->buf[0], buf + media->size - head,
                            size - (media->size - head));
   }

   /* Update the head */
   atomic_set(&media->head, (head + (size - ret)) & (media->size - 1));

   /* Try to write directly to an interface's buffer to minimize latency */
   if(priv->chancfg->direct_eg)
      priv->chancfg->direct_eg(priv->chancfg);

   if(ret)
      DHLOG_NOTICE("%s: Unable to copy data (%d)\n", __func__, ret);

   /* Return the number of bytes copied. In the case of no errors,
    * ret will be 0 */
   *f_pos += (size - ret);
   return size - ret;
}

/*****************************************************************************
*  FUNCTION:   dsphal_poll
*
*  PURPOSE:    Handle the driver poll
*
*  PARAMETERS: filp - pointer to the driver file
*              wait - pointer to poll_table_struct
*
*  RETURNS:    mask of availability of read/write
*
*****************************************************************************/
static unsigned int dsphal_poll(struct file *filp,
                                struct poll_table_struct *wait)
{
   struct dhpriv* priv = (struct dhpriv*)filp->private_data;
   unsigned int mask = 0;

   if(!priv || !priv->chancfg)
   {
      DHLOG_ERR("%s: poll without channel configured\n", __func__);
      return -EINVAL;
   }

   /* Return if the channel is not enabled */
   spin_lock(&priv->chancfg->lock);
   if(!priv->chancfg->enabled)
   {
      spin_unlock(&priv->chancfg->lock);
      return mask;
   }
   spin_unlock(&priv->chancfg->lock);

   poll_wait(filp, &priv->chancfg->queue, wait);
   if(CIRC_CNT(atomic_read(&priv->chancfg->ing_buf.head),
               atomic_read(&priv->chancfg->ing_buf.tail),
               priv->chancfg->eg_buf.size) > 0)
      mask |= POLLIN | POLLRDNORM;

   if(CIRC_SPACE(atomic_read(&priv->chancfg->eg_buf.head),
                 atomic_read(&priv->chancfg->eg_buf.tail),
                 priv->chancfg->ing_buf.size) > 0)
      mask |= POLLOUT;

   return mask;
}

/*****************************************************************************
*  FUNCTION:   dsphal_init
*
*  PURPOSE:    Handle the module initialization.
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
static int __init dsphal_init(void)
{
   int dev, chan, ret = -ENOMEM;

   loglevel = 8;
   DHLOG_NOTICE("%s: Starting DSPHAL driver.\n", __func__);

   /* Initialize boardparms */
   memset(&vp, 0, sizeof(vp));
   if(dh_get_boardparms())
      return -EINVAL;
#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
   /* insert virtual device in boardparms table */
   if(dh_add_boardparm_channel()) 
       return -EINVAL;
#endif

   /* Initialize the device variables */
   memset(&chan_cfg, 0, sizeof(chan_cfg));
   for(chan = 0; chan < ARRAY_SIZE(chan_cfg); chan++)
   {
      init_waitqueue_head( &chan_cfg[chan].queue );
      spin_lock_init( &chan_cfg[chan].lock );
   }
   for(dev = 0; dev < ARRAY_SIZE(open_cnt); dev++)
      atomic_set(&open_cnt[dev], 0);
   dh_debug_init();

   /* Initialize the DSP tick owner */
   init_waitqueue_head(&tick_q);
   atomic_set(&tick, 0);
   dsp_rate = 0;
   tick_owner = DH_TICK_SOURCE_NONE;
   tick_rate  = 0;
   tick_enabled = 0;

   /* create the character device */
   cdev_init(&dhdev.dh_cdev, &dsphal_fops);
   cdev_add(&dhdev.dh_cdev, MKDEV(DEV_MAJOR, DEV_MINOR), 1);

   /* create device class and device name */
   dhdev.class = class_create(THIS_MODULE, DSPHAL_DEV_NAME);
   if(!dhdev.class)
   {
      DHLOG_ALERT("%s: error creating device class\n", __func__);
      goto err_cdev_cleanup;
   }
   dhdev.device = device_create(dhdev.class, NULL, MKDEV(DEV_MAJOR, DEV_MINOR),
                                NULL, DSPHAL_DEV_NAME);
   if(!dhdev.device)
   {
      DHLOG_ALERT("%s: error creating device\n", __func__);
      goto err_class_cleanup;
   }

   atomic_set(&dhdev.open_count, 0);

   if (dma_coerce_mask_and_coherent(dhdev.device, DMA_BIT_MASK(DMA_COHERENT_BITS))) {
      DHLOG_ALERT("%s: error creating device mask\n", __func__);
      goto err_class_cleanup;
   }

   /* Initialize each of the configured audio interfaces */
   ret = dh_init_interfaces();
   if(ret)
      goto out;

   /* Configure each of the voice channels */
   num_ept = 0;
   for(dev = 0; dev < BP_MAX_VOICE_DEVICES; dev++)
   {
      if(vp.voiceDevice[dev].voiceDeviceType == BP_VD_NONE)
         break;

      for(chan = 0; chan < BP_MAX_CHANNELS_PER_DEVICE; chan++)
         dh_configure_channel(dev, chan);
   }

   return 0;

err_class_cleanup:
   class_destroy(dhdev.class);
err_cdev_cleanup:
   cdev_del(&dhdev.dh_cdev);
   dh_deinit_interfaces();
out:
   return ret;
}

/*****************************************************************************
*  FUNCTION:   dsphal_deinit
*
*  PURPOSE:    Handle the module deinitialization.
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
static void __exit dsphal_deinit(void)
{
   int i;
   DHLOG_NOTICE("%s: Cleaning up DSPHAL driver...\n", __func__);

   /* Disable all active channels and cleanup */
   for(i = 0; i < ARRAY_SIZE(chan_cfg); i++)
   {
      dh_disable_channel(i);
      dh_deconfigure_channel(i);
   }

   dh_debug_deinit();

   dh_deinit_interfaces();

   /* Make sure the timer is unregistered */
   dh_unreg_tick_source(DH_TICK_SOURCE_TIMER);

   /* destroy the device and device class */
   device_destroy(dhdev.class, MKDEV(DEV_MAJOR, DEV_MINOR));
   class_destroy(dhdev.class);

   /* delete the character device */
   cdev_del(&dhdev.dh_cdev);

   DHLOG_NOTICE("%s: DSPHAL driver unloaded OK.\n", __func__);
}

module_init(dsphal_init);
module_exit(dsphal_deinit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("BRCM VoIP DSPHAL driver");

