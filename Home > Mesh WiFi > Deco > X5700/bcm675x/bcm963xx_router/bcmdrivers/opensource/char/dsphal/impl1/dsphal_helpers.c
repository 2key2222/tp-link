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

#ifndef _CFE_
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/timer.h>
#endif

#define INTF_INITIALIZED       0x1

/****************************************************************************
* Variables
****************************************************************************/
static unsigned int intf_initialized[DSPHAL_INTF_MAX] = { 0 };

static const struct map_ptr intf_hdlr_table[] = {
#ifdef PCM_SUPPORT
   { DSPHAL_INTF_PCM,  &pcm_hdlr_table    },
#endif /* PCM_SUPPORT */
#ifdef APM_SUPPORT
   { DSPHAL_INTF_APM,  &apm_hdlr_table    },
#endif /* PCM_SUPPORT */
#ifdef CONFIG_BCM_DECT_SUPPORT
   { DSPHAL_INTF_DECT, &dect_hdlr_table   },
#endif /* CONFIG_BCM_DECT_SUPPORT */
#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
   { DSPHAL_INTF_ALSA, &alsa_hdlr_table   },
#endif

   { DH_INVALID,       NULL               },
};

static const struct map_ptr isr_hdlr_table[] = {
   { DH_TICK_SOURCE_IUDMA,  &iudma_isr_table   },
#ifdef CONFIG_BCM_DECT_SUPPORT
   { DH_TICK_SOURCE_DECT,   &dect_isr_table    },
#endif
   { DH_INVALID,            NULL               },
};

static const struct map type_map[] = {
   { BP_VCTYPE_NONE, DSPHAL_TYPE_NONE },
   { BP_VCTYPE_SLIC, DSPHAL_TYPE_FXS  },
   { BP_VCTYPE_DAA,  DSPHAL_TYPE_FXO  },
   { BP_VCTYPE_DECT, DSPHAL_TYPE_DECT },
   { BP_VCTYPE_AUDIO, DSPHAL_TYPE_ALSA},
   { DH_INVALID,     DH_INVALID       },
};

static const struct map intf_map[] = {
   { BP_VDTYPE_PCM,  DSPHAL_INTF_PCM  },
   { BP_VDTYPE_APM,  DSPHAL_INTF_APM  },
   { BP_VDTYPE_DECT, DSPHAL_INTF_DECT },
   { BP_VDTYPE_AUDIO, DSPHAL_INTF_ALSA},
   { DH_INVALID,     DH_INVALID       },
};

static const struct map sample_rate_map[] = {
   { BP_VC_8KHZ,     DSPHAL_RATE_8KHZ  },
   { BP_VC_16KHZ,    DSPHAL_RATE_16KHZ },

   { DH_INVALID,     DH_INVALID        },
};

static const struct map_ptr tick_source_map[] = {
   { DH_TICK_SOURCE_NONE,  "NONE"  },
   { DH_TICK_SOURCE_TIMER, "TIMER" },
   { DH_TICK_SOURCE_IUDMA, "IUDMA" },
   { DH_TICK_SOURCE_DECT,  "DECT"  },

   { DH_INVALID,           NULL    },
};

static struct timer_list ticktimer;
static volatile unsigned int tick_count;
static unsigned int tick_rates[DH_TICK_SOURCE_MAX] = { 0 };

#if defined(BRCM_VOICE_DSPHAL_EGRESS_1KHZ_TONE) || defined(BRCM_VOICE_DSPHAL_INGRESS_1KHZ_TONE)
static const short onekhz_tone[] = {
   0x0000, 0x3e94, 0x5880, 0x3e94, 0x0000, 0xc16c, 0xa780, 0xc16c
};
#endif


/****************************************************************************
* Local Function Definitions
****************************************************************************/
static int dh_init_interface(enum dh_intf intf);
static int dh_set_channel_enable(int id, int enable);
static void dsp_tick_timer(unsigned long arg);


/****************************************************************************
* Function implementation
****************************************************************************/

/*****************************************************************************
*  FUNCTION:   dh_init_interfaces
*
*  PURPOSE:    Initialize all configured audio interfaces
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
int dh_init_interfaces()
{
#if defined(CONFIG_BCM_DECT_SUPPORT) || defined(APM_SUPPORT) || defined(PCM_SUPPORT)
   int ret = 0;
#endif

   /* Interface blocks must be enabled in a particular order */
#ifdef CONFIG_BCM_DECT_SUPPORT
   ret = dh_init_interface(DSPHAL_INTF_DECT);
   if(ret)
      goto err;
#endif /* CONFIG_BCM_DECT_SUPPORT */
#ifdef APM_SUPPORT
   ret = dh_init_interface(DSPHAL_INTF_APM);
   if(ret)
      goto err;
#endif /* APM_SUPPORT */
#ifdef PCM_SUPPORT
   ret = dh_init_interface(DSPHAL_INTF_PCM);
   if(ret)
      goto err;
#endif /* PCM_SUPPORT */
#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
   ret = dh_init_interface(DSPHAL_INTF_ALSA);
   if(ret)
      goto err;
#endif /* CONFIG_BCM_DSP_ALSA_BRIDGE */

   return 0;

#if defined(CONFIG_BCM_DECT_SUPPORT) || defined(APM_SUPPORT) || defined(PCM_SUPPORT)
err:
   dh_deinit_interfaces();
   return ret;
#endif
}


/*****************************************************************************
*  FUNCTION:   dh_init_interface
*
*  PURPOSE:    Call an interface's initialization handler
*
*  PARAMETERS: intf - interface type
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
#if defined(CONFIG_BCM_DECT_SUPPORT) || defined(APM_SUPPORT) || defined(PCM_SUPPORT) || defined(CONFIG_BCM_DSP_ALSA_BRIDGE)
static int dh_init_interface(enum dh_intf intf)
{
   const struct intf_hdlrs *hdlrs;
   int ret = 0;

   hdlrs = dh_map_ptr(intf_hdlr_table, intf);
   if(hdlrs && hdlrs->init)
      ret = hdlrs->init();
   if(!ret)
      intf_initialized[intf] |= INTF_INITIALIZED;

   return ret;
}
#endif

/*****************************************************************************
*  FUNCTION:   dh_deinit_interfaces
*
*  PURPOSE:    Deinitialize all configured audio interfaces
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
int dh_deinit_interfaces()
{
   const struct intf_hdlrs *hdlrs;
   int i;

   /* Deinitialize the interfaces */
   for(i = 0; i < ARRAY_SIZE(intf_initialized); i++)
   {
      hdlrs = dh_map_ptr(intf_hdlr_table, i);
      if(intf_initialized[i] & INTF_INITIALIZED)
      {
         if(hdlrs && hdlrs->deinit)
            hdlrs->deinit();
         intf_initialized[i] &= ~INTF_INITIALIZED;
      }
   }
   return 0;
}

/*****************************************************************************
*  FUNCTION:   dh_idle_interfaces
*
*  PURPOSE:    Sets all interfaces to idle or active
*
*  PARAMETERS: idle - 0 for active, idle otherwise
*
*  RETURNS:    none
*
*****************************************************************************/
void dh_idle_interfaces(int idle)
{
   const struct isr_hdlrs *hdlrs;
   int i;

   idle = idle ? 1 : 0;
   for(i = 0; i < ARRAY_SIZE(isr_hdlr_table); i++)
   {
      hdlrs = isr_hdlr_table[i].ptr;
      if(hdlrs && hdlrs->idle)
         hdlrs->idle(idle);
   }
}

/*****************************************************************************
*  FUNCTION:   dh_configure_channel
*
*  PURPOSE:    Configure a media channel based on the boardparms ids
*
*  PARAMETERS: dev  - boardparms device index
*              chan - boardparms channel index
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
int dh_configure_channel(int dev, int chan)
{
   struct dhchancfg *cfg;
   BP_VOICE_DEVICE *vd = &vp.voiceDevice[dev];
   BP_VOICE_CHANNEL *vc = &vp.voiceDevice[dev].channel[chan];
   const struct intf_hdlrs *hdlrs;
   unsigned long flags = 0;

   /* If this voice channel is not active, don't configure anything */
   if(vc->status != BP_VC_ACTIVE)
   {
      DHLOG_DEBUG("%s: ignoring non-active device %d channel %d\n",
                  __func__, dev, chan);
      return 0;
   }
   if(vc->id >= ARRAY_SIZE(chan_cfg))
   {
      DHLOG_ALERT("%s: channel id %d is out of range (dev %d, chan %d)\n",
                  __func__, vc->id, dev, chan);
      return -EINVAL;
   }

   DHLOG_INFO("%s: device %d, channel %d, id %d, devType %d, "
          "intfType %d, status %d, chanType %d, rate %d Hz, comp %d\n",
          __func__, dev, chan, vc->id, vd->voiceDeviceType,
          vd->audioInterfaceType, vc->status, vc->type,
          vc->sampleRate == BP_VC_8KHZ ? 8000 : 16000, vc->sampleComp);

   spin_lock_irqsave(&chan_cfg[vc->id].lock, flags);

   cfg            = &chan_cfg[vc->id];
   cfg->id        = vc->id;
   cfg->vp_dev    = dev;
   cfg->vp_chan   = chan;
   cfg->type      = dh_map(type_map, vc->type);
   cfg->rate      = dh_map(sample_rate_map, vc->sampleRate);
   cfg->interface = dh_map(intf_map, vd->audioInterfaceType);

   /* Set buffer size and allocate */
   if(vp.voiceDevice[dev].channel[chan].sampleRate == BP_VC_16KHZ)
      cfg->eg_buf.size = cfg->ing_buf.size = BUF_SIZE_WB;
   else
      cfg->eg_buf.size = cfg->ing_buf.size = BUF_SIZE;

   cfg->eg_buf.buf  = kzalloc(cfg->eg_buf.size, GFP_IOFS);
   atomic_set(&cfg->eg_buf.head, 0);
   atomic_set(&cfg->eg_buf.tail, 0);

   cfg->ing_buf.buf = kzalloc(cfg->ing_buf.size, GFP_IOFS);
   atomic_set(&cfg->ing_buf.head, 0);
   atomic_set(&cfg->ing_buf.tail, 0);

   num_ept++;

   spin_unlock_irqrestore(&chan_cfg[vc->id].lock, flags);

   hdlrs = dh_map_ptr(intf_hdlr_table, cfg->interface);
   if(hdlrs && hdlrs->config)
      hdlrs->config(cfg);

   dh_debug_setup_channel(cfg);

   return 0;
}

/*****************************************************************************
*  FUNCTION:   dh_deconfigure_channel
*
*  PURPOSE:    Deconfigures a media channel based on the boardparms ids
*
*  PARAMETERS: id - channel index
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
int dh_deconfigure_channel(int id)
{
   struct dhchancfg *cfg = &chan_cfg[id];
   const struct intf_hdlrs *hdlrs;
   unsigned long flags = 0;

   hdlrs = dh_map_ptr(intf_hdlr_table, cfg->interface);
   if(hdlrs && hdlrs->deconfig)
      hdlrs->deconfig(cfg);

   spin_lock_irqsave(&cfg->lock, flags);

   /* Cleanup the channel buffers */
   kfree(cfg->eg_buf.buf);
   kfree(cfg->ing_buf.buf);

   cfg->enabled     = 0;

   spin_unlock_irqrestore(&cfg->lock, flags);

   dh_debug_close_channel(cfg);

   return 0;
}

/*****************************************************************************
*  FUNCTION:   dh_enable_channel
*
*  PURPOSE:    Enables a media channel
*
*  PARAMETERS: id - channel index
*
*  RETURNS:    0 on success, error code otherwise
*
*  NOTES:      This function assumes the id given is valid. No checking is
*              performed on it.
*
*****************************************************************************/
int dh_enable_channel(int id)
{
   return dh_set_channel_enable(id, 1);
}

/*****************************************************************************
*  FUNCTION:   dh_disable_channel
*
*  PURPOSE:    Disables a media channel
*
*  PARAMETERS: id - channel index
*
*  RETURNS:    0 on success, error code otherwise
*
*  NOTES:      This function assumes the id given is valid. No checking is
*              performed on it.
*
*****************************************************************************/
int dh_disable_channel(int id)
{
   return dh_set_channel_enable(id, 0);
}

/*****************************************************************************
*  FUNCTION:   dh_intf_open_handler
*
*  PURPOSE:    Handle the interface startup
*
*  PARAMETERS: cfg - channel config
*
*  RETURNS:    none
*
*****************************************************************************/
void dh_intf_open_handler(struct dhchancfg *cfg)
{
   const struct intf_hdlrs *hdlrs;

   hdlrs = dh_map_ptr(intf_hdlr_table, cfg->interface);
   if(hdlrs && hdlrs->open)
      hdlrs->open(cfg, atomic_inc_return(&open_cnt[cfg->interface]));
}

/*****************************************************************************
*  FUNCTION:   dh_intf_release_handler
*
*  PURPOSE:    Handle the interface release
*
*  PARAMETERS: cfg - channel config
*
*  RETURNS:    none
*
*****************************************************************************/
void dh_intf_release_handler(struct dhchancfg *cfg)
{
   const struct intf_hdlrs *hdlrs;

   hdlrs = dh_map_ptr(intf_hdlr_table, cfg->interface);
   if(hdlrs && hdlrs->release)
      hdlrs->release(cfg, atomic_dec_return(&open_cnt[cfg->interface]));

   /* Wake up anyone waiting for data */
   wake_up_interruptible( &cfg->queue );
}


/*****************************************************************************
*  FUNCTION:   dh_copy_ingress
*
*  PURPOSE:    Copies data from the DMAs into the channel's audio buffer and
*              signal anyone waiting for the data
*
*  PARAMETERS: cfg  - channel config
*              buf  - pointer to linear data buffer to copy from
*              size - size of data to copy
*
*  RETURNS:    none
*
*****************************************************************************/
void dh_copy_ingress(struct dhchancfg *cfg, char *buf, size_t size)
{
   struct med_buf *media = &cfg->ing_buf;
   unsigned long head, tail;
   size_t copy_size, space;
#ifdef BRCM_VOICE_DSPHAL_INGRESS_1KHZ_TONE
   unsigned int i;
   short *bufp = (short*)buf;
   for(i = 0; i < size >> 1; i++)
      bufp[i] = onekhz_tone[i & 0x7];
#endif /* BRCM_VOICE_DSPHAL_INGRESS_1KHZ_TONE */

   head = atomic_read(&media->head);
   tail = atomic_read(&media->tail);
   space = CIRC_SPACE(head, tail, media->size);
   copy_size = min(size, space);
   if(space < media->watermark)
      copy_size = 0;
   /* make sure copy_size if even */
   copy_size &= ~1;

   /* Copy buffer. If the buffer does not wrap, we can do the copy in one go.
    * If the buffer does wrap, we need to do the copy in two parts */
   if( head + copy_size < media->size )
      memcpy(&media->buf[head], &buf[0], copy_size);
   else
   {
      memcpy(&media->buf[head], &buf[0], media->size - head);
      memcpy(&media->buf[0], &buf[media->size - head],
             copy_size - (media->size - head));
   }

   /* If we have an ingress overrun, block copying any further data until there
    * is at least the normal buffer size space in the buffer */
   if(size != copy_size)
   {
      dh_debug_bufslip(cfg, DH_INGRESS);
      media->watermark = size;
   }
   else if(media->watermark && space >= media->watermark)
      media->watermark = 0;

   /* Update the head and notify any waiting threads */
   atomic_set(&media->head, (head + copy_size) & (media->size - 1));
#ifdef DSPHAL_BLOCKING_READ
   wake_up_interruptible(&cfg->queue);
#endif

   dh_debug_ingress(cfg, buf, size);
}

void dh_copy_ingress_out(struct dhchancfg *cfg, char *buf, size_t size)
{
   struct med_buf *media = &cfg->ing_buf;
   unsigned long head, tail;
   size_t copy_size, available;
#ifdef BRCM_VOICE_DSPHAL_EGRESS_1KHZ_TONE
   unsigned int i;
   short *bufp = (short*)buf;
   for(i = 0; i < size >> 1; i++)
      bufp[i] = onekhz_tone[i & 0x7];
#endif /* BRCM_VOICE_DSPHAL_EXGRESS_1KHZ_TONE */

   head = atomic_read(&media->head);
   tail = atomic_read(&media->tail);

   available = CIRC_CNT(head, tail, media->size);
   copy_size = min(size, available);
   if(available < media->watermark)
      copy_size = 0;
   /* make sure copy_size is even */
   copy_size &= ~1;

#ifndef BRCM_VOICE_DSPHAL_EGRESS_1KHZ_TONE
   /* Copy buffer. If the buffer does not wrap, we can do the copy in one go.
    * If the buffer does wrap, we need to do the copy in two parts */
   if( tail + copy_size < media->size )
      memcpy(&buf[0], &media->buf[tail], copy_size);
   else
   {
      memcpy(&buf[0], &media->buf[tail], media->size - tail);
      memcpy(&buf[media->size - tail], &media->buf[0],
             copy_size - (media->size - tail));
   }

   /* If we have an egress underrun, block copying any further data until there
    * is at least the normal buffer size data available in the buffer */
   if(size != copy_size)
   {
      dh_debug_bufslip(cfg, DH_EGRESS);
      memset(&buf[copy_size], 0, size - copy_size);
      media->watermark = size;
   }
   else if(media->watermark && available >= media->watermark)
      media->watermark = 0;

#endif /* !BRCM_VOICE_DSPHAL_EGRESS_1KHZ_TONE */

   /* Update the tail */
   atomic_set(&media->tail, (tail + copy_size) & (media->size - 1));

   dh_debug_egress(cfg, buf, size);

   /* If there is still media in the buffer after copying, flush it */
   if(head != atomic_read(&media->tail))
      atomic_set(&media->tail, head);
}

/*****************************************************************************
*  FUNCTION:   dh_copy_egress
*
*  PURPOSE:    Copies data from the audio channel's buffer into the temporary
*              buffer passed
*
*  PARAMETERS: cfg  - channel config
*              buf  - pointer to linear data buffer to copy into
*              size - size of data to copy
*
*  RETURNS:    none
*
*****************************************************************************/
void dh_copy_egress(struct dhchancfg *cfg, char *buf, size_t size)
{
   struct med_buf *media = &cfg->eg_buf;
   unsigned long head, tail;
   size_t copy_size, available;
#ifdef BRCM_VOICE_DSPHAL_EGRESS_1KHZ_TONE
   unsigned int i;
   short *bufp = (short*)buf;
   for(i = 0; i < size >> 1; i++)
      bufp[i] = onekhz_tone[i & 0x7];
#endif /* BRCM_VOICE_DSPHAL_EXGRESS_1KHZ_TONE */

   head = atomic_read(&media->head);
   tail = atomic_read(&media->tail);

   available = CIRC_CNT(head, tail, media->size);
   copy_size = min(size, available);
   if(available < media->watermark)
      copy_size = 0;
   /* make sure copy_size is even */
   copy_size &= ~1;

#ifndef BRCM_VOICE_DSPHAL_EGRESS_1KHZ_TONE
   /* Copy buffer. If the buffer does not wrap, we can do the copy in one go.
    * If the buffer does wrap, we need to do the copy in two parts */
   if( tail + copy_size < media->size )
      memcpy(&buf[0], &media->buf[tail], copy_size);
   else
   {
      memcpy(&buf[0], &media->buf[tail], media->size - tail);
      memcpy(&buf[media->size - tail], &media->buf[0],
             copy_size - (media->size - tail));
   }

   /* If we have an egress underrun, block copying any further data until there
    * is at least the normal buffer size data available in the buffer */
   if(size != copy_size)
   {
      dh_debug_bufslip(cfg, DH_EGRESS);
      memset(&buf[copy_size], 0, size - copy_size);
      media->watermark = size;
   }
   else if(media->watermark && available >= media->watermark)
      media->watermark = 0;

#endif /* !BRCM_VOICE_DSPHAL_EGRESS_1KHZ_TONE */

   /* Update the tail */
   atomic_set(&media->tail, (tail + copy_size) & (media->size - 1));

   dh_debug_egress(cfg, buf, size);

   /* If there is still media in the buffer after copying, flush it */
   if(head != atomic_read(&media->tail))
      atomic_set(&media->tail, head);
}


/*****************************************************************************
*  FUNCTION:   dh_get_boardparms
*
*  PURPOSE:    Retrieve the voice boardparms
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error code otherwise
*
*****************************************************************************/
int dh_get_boardparms()
{
   char boardIdStr[BP_BOARD_ID_LEN];
   char baseBoardIdStr[BP_BOARD_ID_LEN];
   int ret = -EINVAL;

   /* First we need to get the board ID from the main BOARD_PARAMETERS table.
    * Once we get the board ID we will use it as index to the voice tables */
   if(BpGetBoardId(baseBoardIdStr) != BP_SUCCESS)
      DHLOG_ERR("%s: Failed to obtain Base board id string!\n"
                "   *** Please verify that Base board configuration id is "
                "properly set up on the CFE prompt\n", __func__);
   else if(BpGetVoiceBoardId(boardIdStr) != BP_SUCCESS)
      DHLOG_ERR("%s: Failed to obtain Voice board id string!\n"
                "   *** Please verify that Voice board configuration id "
                "is properly set up on the CFE prompt!\n", __func__);
   /* Get the voice voice parameters based on the board id string and baseboard
    * id string. */
   else if((ret = BpGetVoiceParms(boardIdStr, &vp, baseBoardIdStr)) != BP_SUCCESS)
      DHLOG_ERR("%s: Failed to obtain voice parameters (%d)!\n",
                __func__, ret);
   else
      ret = 0;

   return ret;
}

/*****************************************************************************
*  FUNCTION:   dh_set_channel_enable
*
*  PURPOSE:    Enables or disables a media channel
*
*  PARAMETERS: id     - channel index
*              enable - 1 to enable, 0 to disable
*
*  RETURNS:    0 on success, error code otherwise
*
*  NOTES:      This function assumes the id given is valid. No checking is
*              performed on it.
*
*****************************************************************************/
static int dh_set_channel_enable(int id, int enable)
{
   unsigned long flags = 0;

   spin_lock_irqsave(&chan_cfg[id].lock, flags);

   /* If already in the right state, no need to do anything */
   if(chan_cfg[id].enabled == enable)
      goto out;

   chan_cfg[id].enabled = enable;

out:
   spin_unlock_irqrestore(&chan_cfg[id].lock, flags);
   return 0;
}

/*****************************************************************************
*  FUNCTION:   dh_map
*
*  PURPOSE:    Map to value based on item
*
*  PARAMETERS: map  - mapping table to use
*              item  - item to map
*
*  RETURNS:    mapped value on success, DH_INVALID otherwise
*
*****************************************************************************/
long dh_map(const struct map *map, long item)
{
   int i;
   for(i = 0; map[i].item != DH_INVALID; i++)
   {
      if(map[i].item == item)
         return map[i].value;
   }

   return DH_INVALID;
}

/*****************************************************************************
*  FUNCTION:   dh_map_ptr
*
*  PURPOSE:    Map to pointer based on item
*
*  PARAMETERS: map  - mapping table to use
*              item  - item to map
*
*  RETURNS:    mapped pointer on success, NULL otherwise
*
*****************************************************************************/
void* dh_map_ptr(const struct map_ptr *map, long item)
{
   int i;
   for(i = 0; map[i].item != DH_INVALID; i++)
   {
      if(map[i].item == item)
         return map[i].ptr;
   }

   return NULL;
}

/*****************************************************************************
*  FUNCTION:   dh_swap_word
*
*  PURPOSE:    Swap 16bit samples within a word
*
*  PARAMETERS: buf  - buffer pointing the samples
*              size - length of the buffer in bytes
*
*  RETURNS:    Nothing.
*
*****************************************************************************/
void dh_swap_word (uint16_t* bufp, int size)
{
   uint16_t tmp;
   int i = 0;
   for(i = 0; i < size >> 1; i += 2)
   {
      tmp       = bufp[i];
      bufp[i]   = bufp[i+1];
      bufp[i+1] = tmp;
   }
}

/*****************************************************************************
*  FUNCTION:   dh_swap_byte
*
*  PURPOSE:    Swap byte within a 16bit sample
*
*  PARAMETERS: buf  - buffer pointing the samples
*              size - length of the buffer in bytes
*
*  RETURNS:    Nothing.
*
*****************************************************************************/
void dh_swap_byte (uint16_t* bufp, int size)
{
   int i = 0;
   for(i = 0; i < size >> 1; i++)
      bufp[i] = ntohs(bufp[i]);
}

/*****************************************************************************
*  FUNCTION:   dh_reg_tick_source
*
*  PURPOSE:    Register a new DSP tick source. If the new tick source is of
*              higher priority than the current owner, switch owners.
*
*  PARAMETERS: source - the new source of the tick
*              rate   - the rate (in msec) of the ticks
*
*  RETURNS:    Nothing.
*
*****************************************************************************/
void dh_reg_tick_source(enum ticksource source, unsigned int rate)
{
   if(source < DH_TICK_SOURCE_NONE || source >= DH_TICK_SOURCE_MAX)
   {
      DHLOG_ERR("%s: invalid tick source %d\n", __func__, source);
      return;
   }

   if(rate && dsp_rate % rate)
   {
      DHLOG_ERR("%s: tick rate (%d) must be evenly divisible into dsp rate "
                "(%d)\n", __func__, rate, dsp_rate);
      return;
   }

   /* Save tick rate for source */
   tick_rates[source] = rate;

   /* If this source is a lesser priority than the current source, ignore the
    * request */
   if(source <= tick_owner)
      return;

   /* Cleanup data for current tick owner */
   switch(tick_owner)
   {
      case DH_TICK_SOURCE_TIMER:
         del_timer_sync(&ticktimer);
         break;

      default:
         break;
   }

   /* Setup new owner */
   DHLOG_INFO("%s: new owner %s, rate %dms\n", __func__,
         (char*)dh_map_ptr(tick_source_map, source), rate);
   tick_owner = source;
   tick_rate  = rate;
   tick_count = 0;

   switch(source)
   {
      case DH_TICK_SOURCE_TIMER:
         init_timer(&ticktimer);
         ticktimer.data = msecs_to_jiffies(rate);
         ticktimer.function = dsp_tick_timer;
         ticktimer.expires = jiffies + ticktimer.data;
         add_timer(&ticktimer);
         break;

      default:
         break;
   }
}

/*****************************************************************************
*  FUNCTION:   dh_unreg_tick_source
*
*  PURPOSE:    Unregister the DSP tick source, unsetting the current owner if
*              required.
*
*  PARAMETERS: source - the source of the tick to unregister
*
*  RETURNS:    Nothing.
*
*****************************************************************************/
void dh_unreg_tick_source(enum ticksource source)
{
   int i;
   if(source < DH_TICK_SOURCE_NONE || source >= DH_TICK_SOURCE_MAX)
   {
      DHLOG_ERR("%s: invalid tick source %d\n", __func__, source);
      return;
   }

   /* Unset the source from the registered tick sources list */
   tick_rates[source] = 0;
   DHLOG_DEBUG("%s: unregistered source %s\n", __func__,
               (char*)dh_map_ptr(tick_source_map, source));

   /* If the active tick owner was the current tick source, set the next
    * highest priority source as the owner */
   if(tick_owner == source)
   {
      /* If we are running the timer, make sure to cleanup before registering
       * anything else */
      if(tick_owner == DH_TICK_SOURCE_TIMER)
         del_timer_sync(&ticktimer);

      tick_owner = DH_TICK_SOURCE_NONE;
      for(i = ARRAY_SIZE(tick_rates) - 1; i >= 0; i--)
      {
         if(tick_rates[i])
         {
            dh_reg_tick_source(i, tick_rates[i]);
            break;
         }
      }

      if(i < 0)
         dh_reg_tick_source(DH_TICK_SOURCE_NONE, 0);

      if(tick_owner == DH_TICK_SOURCE_NONE)
         tick_enabled = 0;
   }
}

/*****************************************************************************
*  FUNCTION:   dh_tick
*
*  PURPOSE:    Send the DSP tick to userspace.
*
*  PARAMETERS: type - the tick source type
*
*  RETURNS:    Nothing.
*
*****************************************************************************/
void dh_tick(enum ticksource source)
{
   if(tick_owner == source && tick_enabled)
   {
      tick_count++;
      if(tick_count * tick_rate >= dsp_rate)
      {
         int hal_tick = atomic_read(&tick);
         dh_debug_record_time(&debug_stats.hal_tick);

         atomic_add(max((tick_count * tick_rate) / dsp_rate,
                        (unsigned int)1), &tick);
#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
         alsa_tick_handler();
#endif
         tick_count = 0;
         wake_up_interruptible_all(&tick_q);

         /* Debug stats update */
         if(hal_tick)
            debug_stats.dsp_underruns++;
         if(hal_tick > debug_stats.dsp_underruns_peak)
            debug_stats.dsp_underruns_peak = hal_tick;
         debug_stats.hal_tick_count++;
      }
   }
}

/*****************************************************************************
*  FUNCTION:   dsp_tick_timer
*
*  PURPOSE:    Timer function that signals the DSP tick.
*
*  PARAMETERS: arg - the rate in jiffies of the timer
*
*  RETURNS:    Nothing.
*
*****************************************************************************/
static void dsp_tick_timer(unsigned long arg)
{
   /* Signal that the DSP is ready to tick */
   dh_tick(DH_TICK_SOURCE_TIMER);

   mod_timer(&ticktimer, ticktimer.expires + arg);
}

