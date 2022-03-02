/****************************************************************************
 *
 * <:copyright-BRCM:2015:DUAL/GPL:standard
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

#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/mutex.h>
#include <sound/pcm.h>

#include <dsphal_alsa.h>


#define PCM_MS_PER_TICK            5
#define PCM_FRAMESYNC_RATE         16000
#define NUM_BUF_PER_CHAN           2 /* double-buffer scheme */
#define PCM_BYTES_PER_SAMPLE       sizeof(uint16_t)
#define PCM_FRAMES_PER_MS          (PCM_FRAMESYNC_RATE/1000)
#define PCM_FRAMES_PER_TICK        (PCM_FRAMES_PER_MS * PCM_MS_PER_TICK)
#define PCM_FRAME_BUF_SIZE(size)   ((size + 7) & (~7)) /* must be multiple of 8 bytes */
#define PCM_BYTES_PER_MS           (PCM_BYTES_PER_SAMPLE*PCM_FRAMES_PER_MS)
#define PCM_MAX_SUBSTREAMS         1

/****************************************************************************
* Local function declaration
****************************************************************************/
static int  alsa_init(void);
int         alsa_deinit(void);
static int  alsa_config_channel(struct dhchancfg *cfg);
static int  alsa_deconfig_channel(struct dhchancfg *cfg);
static int  alsa_open_channel(struct dhchancfg *cfg, int count);
static int  alsa_release_channel(struct dhchancfg *cfg, int count);
static void alsa_process_dsp_pcm( struct dhchancfg *cfg, struct alsa_dsp_pcm *dpcm, char *buf, int *elapsed_ptr );

/****************************************************************************
* Variables
****************************************************************************/

static BP_VOICE_DEVICE  virtual_dev = {
    .voiceDeviceType    = BP_VD_DECO_VOICE_X20_V1,     /* set virtual device as external dect */
    .audioInterfaceType = BP_VDTYPE_AUDIO,
    .spiCtrl.spiDevId   = -1,               /* no spi control */
    .spiCtrl.spiGpio    = 0,
    .requiresReset      = BP_RESET_NOT_REQUIRED, /* no reset */
    .resetGpio          = 0,               /* Reset GPIO */
    .channel[0].id      = 0,
    .channel[0].status  = BP_VC_ACTIVE,
    .channel[0].type    = BP_VCTYPE_AUDIO,
    .channel[0].sampleComp = BP_VC_COMP_LINEAR,
    .channel[0].sampleRate = BP_VC_16KHZ,
    .channel[0].cfg.dect.dectChanId = 0,
    .channel[1].id      = 1,
    .channel[1].status  = BP_VC_INACTIVE,
    .channel[2].id      = 2,
    .channel[2].status  = BP_VC_INACTIVE,
    .channel[3].id      = 3,
    .channel[3].status  = BP_VC_INACTIVE,
};

struct intf_hdlrs alsa_hdlr_table = {
   .init       = alsa_init,
   .deinit     = alsa_deinit,
   .config     = alsa_config_channel,
   .deconfig   = alsa_deconfig_channel,
   .open       = alsa_open_channel,
   .release    = alsa_release_channel,
};

volatile struct dh_alsa_chan_priv *alsa_cfg = NULL;
static unsigned int alsa_count = 0;
unsigned int alsa_id = 0;
char   playback_buf[PCM_BYTES_PER_SAMPLE * PCM_FRAMES_PER_TICK * BP_MAX_CHANNELS_PER_DEVICE+1];
char   capture_buf[PCM_BYTES_PER_SAMPLE * PCM_FRAMES_PER_TICK * BP_MAX_CHANNELS_PER_DEVICE+1];
struct dh_alsa_pcm_substream alsa_pcm_substream[PCM_MAX_SUBSTREAMS];
/****************************************************************************
* Function implementation
****************************************************************************/
/* alsa tick handler will run within ISR context */
int alsa_tick_handler(void)
{ 
    struct alsa_dsp_pcm *dpcm = NULL;
    struct dhchancfg  *alsa_chan_cfg = NULL;
    unsigned long flags;
    int pcm_idx = 0;
    int elapsed = 0;

    if( alsa_cfg == NULL )
        return 0 ;

    alsa_chan_cfg = alsa_cfg->cfg;
    if(!alsa_chan_cfg->initialized)
        return 0;

    memset(capture_buf, 0, sizeof(capture_buf));
    memset(playback_buf, 0, sizeof(playback_buf));

    if(tick_enabled)
    {
        /* move ingress samples from DSP to temp buffer */
        dh_copy_ingress_out(alsa_chan_cfg, capture_buf, PCM_BYTES_PER_MS*BP_MAX_CHANNELS_PER_DEVICE*dsp_rate);
    }

    spin_lock_irqsave(&alsa_chan_cfg->lock, flags);

    if(alsa_chan_cfg->priv == NULL)
    {
        spin_unlock_irqrestore(&alsa_chan_cfg->lock, flags);
        return 0;
    }

    if( alsa_chan_cfg->priv && !list_empty(&((struct dh_alsa_chan_priv *)alsa_chan_cfg->priv)->active_alsa_pcm_list))
    {
        list_for_each_entry(dpcm, &((struct dh_alsa_chan_priv *)alsa_chan_cfg->priv)->active_alsa_pcm_list, active_list )
        {
            if(dpcm == NULL)
            {
                spin_unlock_irqrestore(&alsa_chan_cfg->lock, flags);
                return 0;
            }
            if(dpcm->substream == NULL)
            {
                spin_unlock_irqrestore(&alsa_chan_cfg->lock, flags);
                return 0;
            }
            if(dpcm->substream->runtime == NULL)
            {
                list_del_init(&dpcm->active_list); 
                spin_unlock_irqrestore(&alsa_chan_cfg->lock, flags);
                return 0;
            }

            if( dpcm->substream->stream == SNDRV_PCM_STREAM_PLAYBACK )
                alsa_process_dsp_pcm( alsa_chan_cfg, dpcm, playback_buf, &elapsed );
            else
                alsa_process_dsp_pcm( alsa_chan_cfg, dpcm, capture_buf, &elapsed );

            if (elapsed && pcm_idx < PCM_MAX_SUBSTREAMS) {
                atomic_set(&alsa_pcm_substream[pcm_idx].valid, elapsed);
                alsa_pcm_substream[pcm_idx].substream = dpcm->substream;
            }
            pcm_idx++;
        }
    }
    
    spin_unlock_irqrestore(&alsa_chan_cfg->lock, flags);

    for (pcm_idx = 0; pcm_idx < PCM_MAX_SUBSTREAMS; pcm_idx++) {
         if (atomic_read(&alsa_pcm_substream[pcm_idx].valid)) {
             snd_pcm_period_elapsed(alsa_pcm_substream[pcm_idx].substream);
             atomic_set(&alsa_pcm_substream[pcm_idx].valid, 0);
         }
    }

    if(tick_enabled)
    {
       /* move playback samples to DSP buffer */
       //dh_copy_egress(alsa_chan_cfg, playback_buf, PCM_BYTES_PER_MS*dsp_rate);
    }

    return 0;  
}

/*****************************************************************************
*  FUNCTION:   alsa_init
*
*  PURPOSE:    Handle initialization of ALSA loopback block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int alsa_init()
{
   return alsa_card_dummy_init();
}


/*****************************************************************************
*  FUNCTION:   alsa_deinit
*
*  PURPOSE:    Handle deinitialization of ALSA loopback block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int alsa_deinit()
{
   alsa_card_dummy_exit();
   return 0;
}


/*****************************************************************************
*  FUNCTION:   alsa_config_channel
*
*  PURPOSE:    Handle configuring the PCM channel prior to opening/releasing
*
*  PARAMETERS: cfg - channel configuration
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int alsa_config_channel(struct dhchancfg *cfg)
{
   struct dh_alsa_chan_priv *priv;
   unsigned long flags;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   /* Setup the channel's private data */
   priv = kzalloc(sizeof(*priv), GFP_KERNEL);
   if(!priv)
      return -ENOMEM;
   
   priv->cfg = cfg;
   alsa_cfg  = priv;

   spin_lock_irqsave(&cfg->lock, flags);
   cfg->priv = priv;
   cfg->initialized = 1;
   INIT_LIST_HEAD(&priv->open_alsa_pcm_list);
   INIT_LIST_HEAD(&priv->active_alsa_pcm_list);
   spin_unlock_irqrestore(&cfg->lock, flags);

   alsa_count++;

   return 0;
}


/*****************************************************************************
*  FUNCTION:   alsa_deconfig_channel
*
*  PURPOSE:    Handle configuring the PCM channel prior to opening/releasing
*
*  PARAMETERS: cfg    - channel configuration
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int alsa_deconfig_channel(struct dhchancfg *cfg)
{
   struct dh_alsa_chan_priv *priv = NULL;
   unsigned long flags;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   alsa_count--;

   if(!alsa_count)
      goto free_chan_data;

free_chan_data:
   /* Free any private channel data */
   spin_lock_irqsave(&cfg->lock, flags);

   priv = (struct dh_alsa_chan_priv *)cfg->priv;
   cfg->initialized = 0;
   cfg->priv = NULL;

   spin_unlock_irqrestore(&cfg->lock, flags);

   alsa_cfg = NULL;
   if(priv)
   {
      kfree(priv);
   }

   return 0;
}


/*****************************************************************************
*  FUNCTION:   alsa_open_channel
*
*  PURPOSE:    Handle opening the ALSA loopback channel
*
*  PARAMETERS: cfg    - channel configuration
*              count  - number of active channels (after adding current)
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int alsa_open_channel(struct dhchancfg *cfg, int count)
{
   struct dh_alsa_chan_priv *priv = cfg->priv;
   (void)cfg;
   (void)count;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   set_bit( DH_ALSA_IN_SHIFT, &priv->valid );
   set_bit( DH_ALSA_EG_SHIFT, &priv->valid );
   /* mark the loopback cable as source and sink are ready on dsphal side */

   return 0;
}


/*****************************************************************************
*  FUNCTION:   alsa_release_channel
*
*  PURPOSE:    Handle releasing the given ALSA loopback channel
*
*  PARAMETERS: cfg    - channel configuration
*              count  - number of active channels (after removing current)
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int alsa_release_channel(struct dhchancfg *cfg, int count)
{
   struct dh_alsa_chan_priv *priv = cfg->priv;
   (void)cfg;
   (void)count;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   /* mark the loopback cable as source and sink are disabled on dsphal side */
   clear_bit( DH_ALSA_IN_SHIFT, &priv->valid );
   clear_bit( DH_ALSA_EG_SHIFT, &priv->valid );

   return 0;
}

/*****************************************************************************
*  FUNCTION:   dh_add_boardparm_channel
*
*  PURPOSE:    Added virtual device and channel in boardparm table for alsa dev
*              which read by dsphal core
*
*  PARAMETERS: vp - voice board parmaeter table, global variable
*              define in dsphal_core.c
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int dh_add_boardparm_channel(void)
{
   int  i, j, id = -1;
   BP_VOICE_DEVICE *vd = NULL;

   /* find empty device */
   for( i = 0; i < BP_MAX_VOICE_DEVICES; i++ )
   {
      if( vp.voiceDevice[i].voiceDeviceType == BP_VD_NONE ){
         vd = &(vp.voiceDevice[i]);
         break;
      }
   }

   /* find max channel id */
   for( i = 0; i < BP_MAX_VOICE_DEVICES; i++ )
   {
      if( vp.voiceDevice[i].voiceDeviceType != BP_VD_NONE ){
         for( j = 0; j < BP_MAX_CHANNELS_PER_DEVICE; j++ )
         {
            if(vp.voiceDevice[i].channel[j].status == BP_VC_ACTIVE)
               id = vp.voiceDevice[i].channel[j].id;
         }

      }
   }

   /* create new virtual device */
   if( vd ){
      id++;
      alsa_id = id;
      virtual_dev.channel[0].id = id;
      /* copy final device configuration to boardparm */
      memcpy(vd, (const void*)&virtual_dev, sizeof(virtual_dev));
         
      DHLOG_NOTICE("%s: create virtual device at %d, channel id %d.\n", __func__, i, id);
   }
   else{
      DHLOG_ALERT("%s: error creating virtual device\n", __func__);
      return -EINVAL;
   }

   return 0;
}

static void alsa_process_dsp_pcm( struct dhchancfg *cfg, struct alsa_dsp_pcm *dpcm, char *buf, int *elapsed_ptr )
{
	struct snd_pcm_runtime *runtime;
	struct snd_pcm_substream *substream;
	char *src = NULL;
	char *dst = NULL;
	unsigned int src_off = 0;
	unsigned int dst_off = 0;
    unsigned int src_size = 0;
    unsigned int dst_size = 0;
	int elapsed = 0;
    unsigned long flags;
    unsigned long delta, bytes = PCM_BYTES_PER_MS * BP_MAX_CHANNELS_PER_DEVICE * dsp_rate;

    /* get substream, runtime structure */
    substream = dpcm->substream;
    runtime = substream->runtime;
    /* hardcode samples size as 5ms 16kHz 16 bit sample */
    delta = bytes_to_frames(runtime, bytes) * HZ;

    /* aquire the pcm lock */
    spin_lock_irqsave(&dpcm->lock, flags);

    if( substream->stream == SNDRV_PCM_STREAM_PLAYBACK )
    {
        /* copy from ALSA to DSP */
        src = runtime->dma_area;
        src_off = frames_to_bytes(runtime, dpcm->frac_pos/HZ);
        src_size = frames_to_bytes( runtime, dpcm->frac_buffer_size/HZ);
        dst = buf;
        dst_off = 0;
        dst_size = bytes;
    }
    else
    {
        /* copy from DSP to ALSA */
        src = buf;
        src_off = 0;
        src_size = bytes;
        dst = runtime->dma_area;
        dst_off = frames_to_bytes(runtime, dpcm->frac_pos/HZ);
        dst_size = frames_to_bytes( runtime, dpcm->frac_buffer_size/HZ);
    }

    /* copy samples from src to dst */
    for (;;) {
        unsigned int size = bytes;
    
        /* calculates total size from current start pointer to the end
         * of buffer
         */
        if (src_off + size > src_size )
            size = src_size - src_off;

        if (dst_off + size > dst_size )
            size = dst_size - dst_off;

        /* copy sourc to destination buffer */
        memcpy(dst + dst_off, src + src_off, size);

        /* remaining buffer size */
        bytes -= size;

        /* make sure bytes never be negative value */
        ASSERT(bytes >= 0 );

        /* all buffer been copied to destination */
        if (!bytes)
            break;

        /* calculates remaining buffer start pointer */
        src_off = (src_off + size) % src_size;
        dst_off = (dst_off + size) % dst_size;
    }

    /* update ALSA side buffer pointer */
    dpcm->frac_pos += delta;
    while (dpcm->frac_pos >= dpcm->frac_buffer_size)
        dpcm->frac_pos -= dpcm->frac_buffer_size;

    while (dpcm->frac_period_rest <= delta) {
        elapsed++;
        dpcm->frac_period_rest += dpcm->frac_period_size;
    }
    dpcm->frac_period_rest -= delta;

    /* release lock */
    spin_unlock_irqrestore(&dpcm->lock, flags);

    if (elapsed_ptr) {
        *elapsed_ptr = elapsed;
    }

    /*if( elapsed ){
        snd_pcm_period_elapsed(substream);
    }*/
}
