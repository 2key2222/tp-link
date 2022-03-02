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

#include <linux/errno.h>
#include <linux/jiffies.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/delay.h>

#include <dsphal_dect.h>

/****************************************************************************
* Typedefs and Constants
****************************************************************************/
#define get_user_arg(uarg, karg)                                      \
   do {                                                               \
      int ret;                                                        \
      if(!uarg) {                                                     \
         DHLOG_ERR("%s: no argument passed\n", __FUNCTION__);         \
         return -EINVAL;                                              \
      }                                                               \
      ret = copy_from_user(&karg, (void*)uarg, sizeof(karg));         \
      if(ret != 0) {                                                  \
         DHLOG_ERR("%s: error copying arg to kernel (%d)\n",          \
                   __FUNCTION__, ret);                                \
         return -EFAULT;                                              \
      }                                                               \
   } while(0)

#define put_user_arg(uarg, karg)                                      \
   do {                                                               \
      int ret;                                                        \
      ret = copy_to_user((void*)uarg, &karg, sizeof(karg));           \
      if(ret != 0 ) {                                                 \
         DHLOG_ERR("%s: error copying arg to userspace (%d)\n",       \
                   __FUNCTION__, ret);                                \
         return -EFAULT;                                              \
      }                                                               \
   } while(0)

#define validate_chan(id)                                             \
   do {                                                               \
      if(id >= num_ept) {                                             \
         DHLOG_ERR("%s: channel id %u is outside limits\n",           \
                   __FUNCTION__, id);                                 \
         return -EINVAL;                                              \
      }                                                               \
   } while(0)


/****************************************************************************
* Local function declaration
****************************************************************************/
static long dhio_init(struct dhpriv *priv, unsigned long arg);
static long dhio_enable(struct dhpriv *priv, unsigned long arg);
static long dhio_setloglevel(struct dhpriv *priv, unsigned long arg);
static long dhio_getnumept(struct dhpriv *priv, unsigned long arg);
static long dhio_getchancfg(struct dhpriv *priv, unsigned long arg);
static long dhio_setclearchan(struct dhpriv *priv, unsigned long arg);
static long dhio_setdsprate(struct dhpriv *priv, unsigned long arg);
static long dhio_waittick(struct dhpriv *priv, unsigned long arg);
static long dhio_settickenable(struct dhpriv *priv, unsigned long arg);
static long dhio_setdectstackstatus(struct dhpriv *priv, unsigned long arg);
static long dhio_setvoiceidle(struct dhpriv *priv, unsigned long arg);


/****************************************************************************
* Variables
****************************************************************************/

const struct ioctl_hdlr ioctl_hdlr_table[] = {
   { DSPHAL_CMD_INIT,               dhio_init,               1 },
   { DSPHAL_CMD_ENABLE,             dhio_enable,             0 },
   { DSPHAL_CMD_SETLOGLEVEL,        dhio_setloglevel,        0 },
   { DSPHAL_CMD_GETNUMEPT,          dhio_getnumept,          0 },
   { DSPHAL_CMD_GETCHANCFG,         dhio_getchancfg,         0 },
   { DSPHAL_CMD_SETDSPRATE,         dhio_setdsprate,         0 },
   { DSPHAL_CMD_SETCLEARCHAN,       dhio_setclearchan,       0 },
   { DSPHAL_CMD_WAITTICK,           dhio_waittick,           0 },
   { DSPHAL_CMD_SETTICKENABLE,      dhio_settickenable,      1 },
   { DSPHAL_CMD_SETDECTSTACKSTATUS, dhio_setdectstackstatus, 0 },
   { DSPHAL_CMD_SETVOICEIDLE,       dhio_setvoiceidle,       1 },

   { DH_INVALID,                    NULL,                    0 },
};


/****************************************************************************
* Function implementation
****************************************************************************/

static long dhio_init(struct dhpriv *priv, unsigned long arg)
{
   /* Validation */
   if(!priv)
      return -EFAULT;
   if(priv->chancfg)
   {
      DHLOG_ERR("%s: driver channel already initialized\n", __FUNCTION__);
      return -EINVAL;
   }

   validate_chan((unsigned int)arg);

   priv->chancfg = &chan_cfg[arg];

   /* Handle the 'open' for the interface */
   dh_intf_open_handler(&chan_cfg[arg]);

   DHLOG_DEBUG("%s: opened channel %lu\n", __FUNCTION__, arg);
   return 0;
}

static long dhio_enable(struct dhpriv *priv, unsigned long arg)
{
   struct dsphal_cmdenable karg;
   (void)priv;

   get_user_arg(arg, karg);
   validate_chan(karg.id);

   /* Enable or disable the channel */
   if(karg.enable)
      dh_enable_channel(karg.id);
   else
      dh_disable_channel(karg.id);

   DHLOG_DEBUG("%s: %sabled channel %u\n", __FUNCTION__,
          karg.enable ? "en" : "dis", karg.id);
   return 0;
}

static long dhio_setloglevel(struct dhpriv *priv, unsigned long arg)
{
   (void)priv;

   loglevel = arg;
   return 0;
}

static long dhio_getnumept(struct dhpriv *priv, unsigned long arg)
{
   (void)priv;
   (void)arg;

   return num_ept;
}

static long dhio_getchancfg(struct dhpriv *priv, unsigned long arg)
{
   struct dsphal_chancfg karg;
   struct dhchancfg *cfg;
   unsigned long flags;

   (void)priv;

   get_user_arg(arg, karg);
   validate_chan(karg.id);

   spin_lock_irqsave(&chan_cfg[karg.id].lock, flags);

   /* Fill in channel configuration */
   cfg = &chan_cfg[karg.id];

   karg.type      = cfg->type;
   karg.interface = cfg->interface;
   karg.rate      = cfg->rate;
   karg.enabled   = cfg->enabled;

   spin_unlock_irqrestore(&chan_cfg[karg.id].lock, flags);

   /* Copy back to userspace */
   put_user_arg(arg, karg);
   return 0;
}

static long dhio_setclearchan(struct dhpriv *priv, unsigned long arg)
{
   struct dsphal_cmdenable karg;
   unsigned long flags;
   (void)priv;

   get_user_arg(arg, karg);
   validate_chan(karg.id);

   spin_lock_irqsave(&chan_cfg[karg.id].lock, flags);

   if(vp.voiceDevice[chan_cfg[karg.id].vp_dev].
         channel[chan_cfg[karg.id].vp_chan].sampleComp == BP_VC_COMP_LINEAR)
   {
      DHLOG_WARNING("%s: channel %u does not support clearchannel\n",
                    __FUNCTION__, karg.id);
      goto out;
   }

   if(karg.enable != chan_cfg[karg.id].clearchan)
   {
      chan_cfg[karg.id].clearchan = karg.enable;
      DHLOG_DEBUG("%s: %sabled clearchannel for channel %u\n",
                  __FUNCTION__, karg.enable ? "en" : "dis", karg.id);
   }

out:
   spin_unlock_irqrestore(&chan_cfg[karg.id].lock, flags);
   return 0;
}

static long dhio_setdsprate(struct dhpriv *priv, unsigned long arg)
{
   (void)priv;

   if(!arg)
      return -EINVAL;

   dsp_rate = arg;
   return 0;
}

static long dhio_waittick(struct dhpriv *priv, unsigned long arg)
{
   (void)priv;
   (void)arg;

   /* Record the end time of the DSP thread just behind the head of the dsp thread */
   if(atomic_read(&debug_stats.dsp_start.head) !=
         ((atomic_read(&debug_stats.dsp_end.head) + 1) &
          (DEBUG_STATS_RINGBUF_SIZE - 1))) {
      atomic_set(&debug_stats.dsp_end.head,
            ((atomic_read(&debug_stats.dsp_start.head) - 1) &
             (DEBUG_STATS_RINGBUF_SIZE - 1)));
   }
   dh_debug_record_time(&debug_stats.dsp_end);

   /* Wait on tick */
   if(wait_event_interruptible(tick_q, atomic_read(&tick)))
      return -EINTR;
   atomic_dec(&tick);

   /* Record the start time of the DSP thread */
   debug_stats.dsp_tick_count++;
   dh_debug_record_time(&debug_stats.dsp_start);

   return 0;
}

static long dhio_settickenable(struct dhpriv *priv, unsigned long arg)
{
   (void)priv;
   (void)arg;

   if(!dsp_rate)
   {
      DHLOG_ERR("%s: dsp tick rate is unknown\n", __FUNCTION__);
      return -EINVAL;
   }

   /* Make sure the timer is enabled and set to the DSP rate */
   dh_reg_tick_source(DH_TICK_SOURCE_TIMER, dsp_rate);

   tick_enabled = arg;
   atomic_set(&tick, 0);

   return 0;
}

static long dhio_setdectstackstatus(struct dhpriv *priv, unsigned long arg)
{
   (void)priv;
   (void)arg;

#ifdef CONFIG_BCM_DECT_SUPPORT
   dect_set_stack_status(arg);
   priv->dect_handle = 1;
#endif /* CONFIG_BCM_DECT_SUPPORT */
   return 0;
}

static long dhio_setvoiceidle(struct dhpriv *priv, unsigned long arg)
{
   (void)priv;

   DHLOG_DEBUG("%s: set interfaces to %s\n", __func__, arg ? "idle" : "active");
   dh_idle_interfaces((int)arg);
   return 0;
}
