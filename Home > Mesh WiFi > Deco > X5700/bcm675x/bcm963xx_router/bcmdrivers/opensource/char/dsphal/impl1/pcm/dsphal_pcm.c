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
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>
#endif

#include <dsphal_chip.h>
#include <dsphal_pcm.h>
#include <pcm_regs.h>
#include <iudma.h>
#include <g711.h>

/****************************************************************************
* Local function declaration
****************************************************************************/
int         pcm_init(void);
int         pcm_start(void);
int         pcm_stop(void);
int         pcm_deinit(void);
static int  pcm_dma_init(void);
static int  pcm_dma_deinit(void);
static int  pcm_config_channel(struct dhchancfg *cfg);
static int  pcm_deconfig_channel(struct dhchancfg *cfg);
static int  pcm_open_channel(struct dhchancfg *cfg, int count);
static int  pcm_release_channel(struct dhchancfg *cfg, int count);
static void pcm_dma_read_cb(unsigned int chan, char *bufp, size_t size,
                            dma_addr_t bufp_dma);
static void pcm_dma_write_cb(unsigned int chan, char *bufp, size_t size,
                             dma_addr_t bufp_dma);
#ifdef BRCM_VOICE_DIRECT_EGRESS
static void pcm_write_direct(struct dhchancfg *cfg);
#endif
static int  pcm_swap_and_compress(struct dhchancfg *chan_cfg, char *bufp,
                                  int size);
static int  pcm_decompress_and_swap(struct dhchancfg *chan_cfg, char *bufp,
                                    int size);


/****************************************************************************
* Variables
****************************************************************************/
struct intf_hdlrs pcm_hdlr_table = {
   .init       = pcm_init,
   .deinit     = pcm_deinit,
   .config     = pcm_config_channel,
   .deconfig   = pcm_deconfig_channel,
   .open       = pcm_open_channel,
   .release    = pcm_release_channel,
};

/* Currently, we only have 1 PCM block, and hence only an RX and TX PCM DMA */
struct pcm_dma pcm_dma_cfg[NUM_PCM_DMA_CHAN] = {
   /* RX dma */
   {
      .chan_id     = PCM_DMA_CHANNEL_RX,
      .data_cb     = pcm_dma_read_cb,
      .direction   = DMA_FROM_DEVICE,
      .burst_size  = 1,
      .interrupt_chan = PCM_DMA_CHANNEL_RX,
      .tick        = PCM_MS_PER_TICK,
      .buffer      = { 0 },
   },

   /* TX dma */
   {
      .chan_id     = PCM_DMA_CHANNEL_TX,
#ifndef BRCM_VOICE_DIRECT_EGRESS
      .data_cb     = pcm_dma_write_cb,
#endif
      .direction   = DMA_TO_DEVICE,
      .burst_size  = 1,
      .interrupt_chan = PCM_DMA_CHANNEL_RX,
      .tick        = 0,
      .buffer      = { 0 },
   },
};

volatile unsigned int pcm_chan_ctrl = 0;
static unsigned int   pcm_enabled = 0;
static unsigned int   pcm_count = 0;
static unsigned short g711_buf[PCM_BYTES_PER_SAMPLE_WB * PCM_FRAMES_PER_TICK];
static char           temp_buf[PCM_BYTES_PER_SAMPLE_WB * PCM_FRAMES_PER_TICK];
#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
static char           alsa_buf[PCM_BYTES_PER_SAMPLE_WB * PCM_FRAMES_PER_TICK * BP_MAX_CHANNELS_PER_DEVICE];
#endif
/****************************************************************************
* Function implementation
****************************************************************************/


/*****************************************************************************
*  FUNCTION:   pcm_init
*
*  PURPOSE:    Handle initialization of PCM block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_init()
{
   int ret;

   if(pcm_enabled)
      return 0;

   /* Power up the block */
   ret = pcm_power_up();
   if(ret)
      goto err;
   pcm_pinmux();

   /* Configure the PCM clock */
   ret = pcm_clk_init();
   if(ret)
      goto err_power;
   pcm_enabled = 1;

   /* Clear the PCM timeslots */
   pcm_ts_init();
   pcm_ts_clear();
   return 0;

err_power:
   pcm_power_down();
err:
   return ret;
}


/*****************************************************************************
*  FUNCTION:   pcm_deinit
*
*  PURPOSE:    Handle deinitialization of PCM block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_deinit()
{
   int ret;

   if(!pcm_enabled)
      return 0;

   /* Stop PCM */
   pcm_stop();

   /* Ensure all the timeslots are cleared */
   pcm_ts_clear();

   /* Turn of the PCM block */
   ret = pcm_power_down();
   pcm_pinunmux();

   pcm_enabled = 0;

   return ret;
}


/*****************************************************************************
*  FUNCTION:   pcm_start
*
*  PURPOSE:    Start PCM
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_start()
{
   /* Enable PCM operation and set the cached pcm_chan_ctrl register */
   PCM->pcm_ctrl |= PCM_ENABLE;
#if !(defined(CONFIG_BCM96858) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM96856) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM963178) || defined(CONFIG_BCM947622) || defined(CONFIG_BCM96878))
   PCM->pcm_chan_ctrl = pcm_chan_ctrl;
#endif

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_stop

*
*  PURPOSE:    Stop PCM
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_stop()
{
   /* Stop PCM operation */
   PCM->pcm_ctrl &= ~PCM_ENABLE;

   /* Clear any pending interrupts */
   PCM->pcm_int_pending |= PCM->pcm_int_pending;

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_config_channel
*
*  PURPOSE:    Handle configuring the PCM channel prior to opening/releasing
*
*  PARAMETERS: cfg - channel configuration
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_config_channel(struct dhchancfg *cfg)
{
   int i, tsnum;
   BP_VOICE_CHANNEL *chan;
   struct pcm_chan_priv *priv;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   /* Setup the channel's private data */
   priv = kzalloc(sizeof(*priv), GFP_KERNEL);
   if(!priv)
      return -ENOMEM;
   priv->rx_dma = &pcm_dma_cfg[0];
   priv->tx_dma = &pcm_dma_cfg[1];
   cfg->priv = priv;

   pcm_count++;

#ifdef BRCM_VOICE_DIRECT_EGRESS
   cfg->direct_eg = pcm_write_direct;
#endif

   /* Add the channel to the timeslot map */
   chan  = &vp.voiceDevice[cfg->vp_dev].channel[cfg->vp_chan];
   tsnum = BP_PCM_TS_COUNT(chan->sampleComp, chan->sampleRate);

   /* Stop the PCM block to reconfigure timeslots */
#if !(defined(CONFIG_BCM96858) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM96856) || defined(CONFIG_BCM963178) || defined(CONFIG_BCM947622) || defined(CONFIG_BCM96878)) 
   pcm_stop();
#endif
   /* Allocate RX and TX timeslots */
   for(i = 0; i < tsnum; i++)
   {
      pcm_ts_alloc(&pcm_dma_cfg[0], chan->cfg.pcm.ts.rxTimeslot[i],
                   chan->cfg.pcm.pcmChanId);
      if(pcm_ts_impl == 1)
         pcm_ts_alloc(&pcm_dma_cfg[1], chan->cfg.pcm.ts.txTimeslot[i],
                      chan->cfg.pcm.pcmChanId);
   }

   /* Re-start the PCM block */
#if !(defined(CONFIG_BCM96858) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM96856) || defined(CONFIG_BCM963178) || defined(CONFIG_BCM947622) || defined(CONFIG_BCM96878)) 
   pcm_start();
#endif
   cfg->initialized = 1;

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_deconfig_channel
*
*  PURPOSE:    Handle configuring the PCM channel prior to opening/releasing
*
*  PARAMETERS: cfg    - channel configuration
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_deconfig_channel(struct dhchancfg *cfg)
{
   int i, tsnum;
   BP_VOICE_CHANNEL *chan;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   pcm_count--;

   if(!pcm_enabled)
      goto free_chan_data;

   chan  = &vp.voiceDevice[cfg->vp_dev].channel[cfg->vp_chan];
   tsnum = BP_PCM_TS_COUNT(chan->sampleComp, chan->sampleRate);

   /* Stop the PCM block to reconfigure timeslots */
#if !(defined(CONFIG_BCM96858) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM96856) || defined(CONFIG_BCM963178) || defined(CONFIG_BCM947622) || defined(CONFIG_BCM96878)) 
   pcm_stop();
#endif
   /* Deallocate RX and TX timeslots */
   for(i = 0; i < tsnum; i++)
   {
      pcm_ts_dealloc(&pcm_dma_cfg[0], chan->cfg.pcm.ts.rxTimeslot[i]);
      if(pcm_ts_impl == 1)
         pcm_ts_dealloc(&pcm_dma_cfg[1], chan->cfg.pcm.ts.txTimeslot[i]);
   }

   /* Re-start the PCM block */
#if !(defined(CONFIG_BCM96858) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM96856) || defined(CONFIG_BCM963178) || defined(CONFIG_BCM947622) || defined(CONFIG_BCM96878))
   pcm_start();
#endif
   cfg->initialized = 0;

free_chan_data:
   /* Free any private channel data */
   if(cfg->priv)
   {
      kfree(cfg->priv);
      cfg->priv = NULL;
   }

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_open_channel
*
*  PURPOSE:    Handle opening the PCM channel
*
*  PARAMETERS: cfg    - channel configuration
*              count  - number of active channels (after adding current)
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_open_channel(struct dhchancfg *cfg, int count)
{
   (void)cfg;
   (void)count;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   /* Handle PCM quirks */
   pcm_quirk_open(cfg, count);

   /* Only start the DMA once all the channels have been opened */
   if(count == pcm_count)
      pcm_dma_init();

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_release_channel
*
*  PURPOSE:    Handle releasing the given PCM channel
*
*  PARAMETERS: cfg    - channel configuration
*              count  - number of active channels (after removing current)
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_release_channel(struct dhchancfg *cfg, int count)
{
   (void)cfg;
   (void)count;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   if(count == 0)
      pcm_dma_deinit();

   /* Handle PCM quirks */
   pcm_quirk_release(cfg, count);

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_dma_init
*
*  PURPOSE:    Initialize the board's PCM DMA
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*  NOTES:      This function assumes it will only be called once to initialize
*              the DMA. Note that the enabled channels must be already set in
*              pcm_chan_ctrl.
*
*****************************************************************************/
static int pcm_dma_init()
{
   int i;
   int ret = -ENOMEM;
   unsigned long flags;

   /* Setup the DMA TX and RX channels */
   for(i = 0; i < ARRAY_SIZE(pcm_dma_cfg); i++)
   {
      struct pcm_dma *dma = &pcm_dma_cfg[i];

      /* Allocate all the required buffer area. */
      dma->buffer_size  = pcm_frame_size() * PCM_FRAMES_PER_TICK;
      dma->buffer_count = NUM_BUF_PER_CHAN;
      dma->buffer.cpu   = kmalloc(dma->buffer_size * dma->buffer_count,
                                  GFP_KERNEL | GFP_DMA);

      if(!dma->buffer.cpu)
      {
         DHLOG_ERR("%s: error allocating dma buffers\n", __func__);
         goto err_cleanup_iudma_chan;
      }

      dma->buffer.dma = dma_map_single(dhdev.device, dma->buffer.cpu,
                                        dma->buffer_size * dma->buffer_count,
                                        dma->direction);

      DHLOG_DEBUG("%s: chan %d buffer area 0x%p [0x%p] size %u\n", __func__, i,
            dma->buffer.cpu, (void*)dma->buffer.dma,
            (unsigned int)(dma->buffer_size * dma->buffer_count));

      /* Find the buffer address offset from the pre-allocated buffer */
      ret = iudma_request_chan(dma->chan_id, dma->buffer_count,
                               dma->buffer_size, &dma->buffer);
      if(ret)
      {
         DHLOG_ERR("%s: error while requesting iudma chan %d\n",
                __func__, dma->chan_id);
         goto err_cleanup_iudma_chan;
      }

      iudma_config_chan(dma->chan_id, dma->burst_size, dma->direction,
                        dma->data_cb, dma->interrupt_chan, dma->tick);

      iudma_enable_chan(dma->chan_id);
   }

   /* Make DMA and PCM atomic */
   local_irq_save(flags);
   iudma_start();
   pcm_start();
   local_irq_restore(flags);

   return 0;

err_cleanup_iudma_chan:
   /* Cleanup the current channel, if required */
   if(pcm_dma_cfg[i].buffer.cpu)
   {
      dma_unmap_single(dhdev.device, pcm_dma_cfg[i].buffer.dma,
            pcm_dma_cfg[i].buffer_size * pcm_dma_cfg[i].buffer_count,
            pcm_dma_cfg[i].direction);
      kfree(pcm_dma_cfg[i].buffer.cpu);
      pcm_dma_cfg[i].buffer.cpu = NULL;
      pcm_dma_cfg[i].buffer.dma = 0;
   }
   /* Cleanup the remaining configured channels */
   for(i--; i >= 0; i--)
   {
      iudma_release_chan(pcm_dma_cfg[i].chan_id);
      if(pcm_dma_cfg[i].buffer.cpu)
      {
         dma_unmap_single(dhdev.device, pcm_dma_cfg[i].buffer.dma,
               pcm_dma_cfg[i].buffer_size * pcm_dma_cfg[i].buffer_count,
               pcm_dma_cfg[i].direction);
         kfree(pcm_dma_cfg[i].buffer.cpu);
         pcm_dma_cfg[i].buffer.cpu = NULL;
         pcm_dma_cfg[i].buffer.dma = 0;
      }
   }
   return ret;
}


/*****************************************************************************
*  FUNCTION:   pcm_dma_deinit
*
*  PURPOSE:    Deinitialize the board's PCM DMA
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*  NOTES:      This function assumes it will only be called once to
*              deinitialize the DMA.
*
*****************************************************************************/
static int pcm_dma_deinit()
{
  unsigned int i;

   /* Release all the channels and disable the DMA */
   for(i = 0; i < ARRAY_SIZE(pcm_dma_cfg); i++)
   {
      iudma_release_chan(pcm_dma_cfg[i].chan_id);

      /* Free the allocated DMA buffers */
      if(pcm_dma_cfg[i].buffer.cpu)
      {
         dma_unmap_single(dhdev.device, pcm_dma_cfg[i].buffer.dma,
               pcm_dma_cfg[i].buffer_size * pcm_dma_cfg[i].buffer_count,
               pcm_dma_cfg[i].direction);
         kfree(pcm_dma_cfg[i].buffer.cpu);
         pcm_dma_cfg[i].buffer.cpu = NULL;
         pcm_dma_cfg[i].buffer.dma = 0;
      }
   }

   iudma_stop();

   return 0;
}

#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
extern unsigned int alsa_id;

static void pcm_multichan_read(char *in_buf, size_t size, char *dma_buf)
{
    unsigned int frame_size, frame_num, i;

    frame_size = pcm_frame_size();

    if (size > frame_size * PCM_FRAMES_PER_TICK) {
        return;
    }

    frame_num = size >> ((PCM_BYTES_PER_SAMPLE == 1) ? 0 : 1);

    for (i = 0; i < frame_num; i++) {
        if (PCM_BYTES_PER_SAMPLE == 1)
            in_buf[i] = dma_buf[i];
        else
            ((uint16_t*)in_buf)[i] = ((uint16_t*)dma_buf)[i];
    }

#ifdef CONFIG_BCM94908
    dh_swap_word((uint16_t*)in_buf, size);
#else
    dh_swap_byte((uint16_t*)in_buf, size);
#endif
}
#endif

/*****************************************************************************
*  FUNCTION:   pcm_dma_read_cb
*
*  PURPOSE:    Read callback for the PCM DMA. Deinterleaves and copies audio
*              data from the PCM buffer into each audio channel's buffer.
*
*  PARAMETERS: chan - DMA channel id
*              bufp - the DMA buffer
*              size - size of the buffer
*              bufp_dma - physical addr of bufp
*
*  RETURNS:    none
*
*  NOTES:      This function is called from the context of the DMA ISR
*
*****************************************************************************/
static void pcm_dma_read_cb(unsigned int chan, char *bufp, size_t size,
                            dma_addr_t bufp_dma)
{
   struct pcm_chan_priv* priv;
   unsigned int i, ret;
#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
   unsigned int bytes = 0;
#endif

   /* Get the frame size from the channel array */
   for(i = 0; i < ARRAY_SIZE(pcm_dma_cfg); i++)
   {
      if(pcm_dma_cfg[i].chan_id == chan)
         break;
   }
   if(i >= ARRAY_SIZE(pcm_dma_cfg))
   {
      DHLOG_DEBUG("%s: Couldn't find PCM dma config matching DMA channel %d\n",
                  __func__,  chan);
      return;
   }

   /* Iterate through each audio channel 'i'. Check to see if the channel is
    * enabled, if it is a PCM channel, and if has been setup for this DMA
    * channel. If it is, deinterleave audio data. Once we have processed all
    * timeslots in all frames, we copy the temporary buffer into the channel's
    * audio buffer and signal to any waiting applications that there is new
    * data for this channel.
    */
   for(i = 0; i < ARRAY_SIZE(chan_cfg); i++)
   {
      priv = (struct pcm_chan_priv*) chan_cfg[i].priv;

      /* Skip the channel if we shouldn't process it */
      if(!chan_cfg[i].enabled || chan_cfg[i].interface != DSPHAL_INTF_PCM)
         continue;
      if(!priv || priv->rx_dma->chan_id != chan)
         continue;

      dma_sync_single_for_cpu(dhdev.device, bufp_dma,
            priv->rx_dma->buffer_size, priv->rx_dma->direction);

      ret = pcm_deinterleave_chan(&chan_cfg[i], temp_buf, sizeof(temp_buf),
                                  bufp);
#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
      bytes += ret;
#endif

      /* If the data is compressed, we will need to decompress it */
      ret = pcm_decompress_and_swap(&chan_cfg[i], temp_buf, ret);

      /* Copy the data from our temporary buffer to the audio channel */
      dh_copy_ingress(&chan_cfg[i], temp_buf, ret);
   }
#ifdef CONFIG_BCM_DSP_ALSA_BRIDGE
   if (chan_cfg[alsa_id].enabled && (chan_cfg[alsa_id].interface == DSPHAL_INTF_ALSA) && (bytes > 0)) {
       pcm_multichan_read(alsa_buf, bytes, bufp);
       dh_copy_ingress(&chan_cfg[alsa_id], alsa_buf, bytes);
   }
#endif
}


/*****************************************************************************
*  FUNCTION:   pcm_dma_write_cb
*
*  PURPOSE:    Write callback for the PCM DMA. Interleaves and copies audio
*              data from each configured audio channel's buffer into the PCM
*              data buffer.
*
*  PARAMETERS: chan - DMA channel id
*              bufp - the DMA buffer
*              size - size of the buffer
*              bufp_dma - physical addr of bufp
*
*  RETURNS:    none
*
*  NOTES:      This function is called from the context of the DMA ISR
*
*****************************************************************************/
static void pcm_dma_write_cb(unsigned int chan, char *bufp, size_t size,
                             dma_addr_t bufp_dma)
{
   BP_VOICE_CHANNEL *bpch;
   struct pcm_chan_priv *priv;
   unsigned int i;
   size_t buf_size;

   /* Get the frame size from the channel array */
   for(i = 0; i < ARRAY_SIZE(pcm_dma_cfg); i++)
   {
      if(pcm_dma_cfg[i].chan_id == chan)
         break;
   }
   if(i >= ARRAY_SIZE(pcm_dma_cfg))
   {
      DHLOG_DEBUG("%s: Couldn't find PCM dma config matching DMA channel %d\n",
                  __func__,  chan);
      return;
   }

   /* Iterate through each audio channel 'i'. Check to see if the channel is
    * enabled, if is a PCM channel, and if has been setup for this DMA channel.
    * Then for each audio channel, copy any pending egress data into a
    * temporary buffer and interleave this data into the PCM DMA buffer.
    */
   for(i = 0; i < ARRAY_SIZE(chan_cfg); i++)
   {
      bpch = &vp.voiceDevice[chan_cfg[i].vp_dev].channel[chan_cfg[i].vp_chan];
      priv = (struct pcm_chan_priv*) chan_cfg[i].priv;

      /* Skip the channel if we shouldn't process it */
      if(!chan_cfg[i].enabled || chan_cfg[i].interface != DSPHAL_INTF_PCM)
         continue;
      if(!priv || priv->tx_dma->chan_id != chan)
         continue;

      /* Copy the data from the audio channel into our temporary buffer */
      buf_size = ( bpch->sampleRate == BP_VC_16KHZ ? 4 : 2 ) *
                 PCM_FRAMES_PER_TICK;                 

      dh_copy_egress(&chan_cfg[i], temp_buf, buf_size);

      /* Compress the data and/or swap bytes, if required */
      buf_size = pcm_swap_and_compress(&chan_cfg[i], temp_buf, buf_size);

      pcm_interleave_chan(&chan_cfg[i], temp_buf, buf_size, bufp);

      dma_sync_single_for_device(dhdev.device, bufp_dma,
            priv->tx_dma->buffer_size, priv->tx_dma->direction);
   }
}

#ifdef BRCM_VOICE_DIRECT_EGRESS
/*****************************************************************************
*  FUNCTION:   pcm_write_direct
*
*  PURPOSE:    Write directly to the PCM DMA. Interleaves and copies audio
*              data from a particular configured audio channel's buffer into
*              the PCM data buffer.
*
*  PARAMETERS: cfg  - channel config struct
*
*  RETURNS:    none
*
*****************************************************************************/
static void pcm_write_direct(struct dhchancfg *cfg)
{
   BP_VOICE_CHANNEL *bpch;
   size_t dma_size = 0, buf_size;
   char* dma_buf = NULL;
   struct pcm_chan_priv *priv = cfg->priv;

   if(!cfg->enabled || !priv)
      return;

   iudma_get_next_buf(priv->tx_dma->chan_id, &dma_buf, &dma_size);
   if(!dma_buf || !dma_size)
      return;

   bpch = &vp.voiceDevice[cfg->vp_dev].channel[cfg->vp_chan];

   buf_size = BP_PCM_TS_COUNT(bpch->sampleComp, bpch->sampleRate) *
              PCM_FRAMES_PER_TICK;
   dh_copy_egress(cfg, temp_buf, buf_size);
   /* Compress the data and/or swap bytes, if required */
   buf_size = pcm_swap_and_compress(cfg, temp_buf, buf_size);
   pcm_interleave_chan(cfg, temp_buf, buf_size, dma_buf);
}
#endif


/*****************************************************************************
*  FUNCTION:   pcm_swap_and_compress
*
*  PURPOSE:    Handles byte swapping and/or compression of PCM channel data, if
*              required
*
*  PARAMETERS: chan_cfg - channel config struct
*              bufp     - buffer to decompress
*              size     - buffer size
*
*  RETURNS:    new size of buffer (post compression)
*
*****************************************************************************/
static int pcm_swap_and_compress(struct dhchancfg *chan_cfg, char *bufp,
                                 int size)
{
   BP_VOICE_CHANNEL *bpch;
   int i;

   bpch = &vp.voiceDevice[chan_cfg->vp_dev].channel[chan_cfg->vp_chan];

   if(bpch->sampleComp != BP_VC_COMP_LINEAR)
   {
      if(chan_cfg->clearchan)
      {
         /* Expand the 8-bit samples into padded 16-bit samples */
         for(i = 0; i < size; i++)
            g711_buf[i] = bufp[i] & 0xFF;
         for(i = 0; i < size; i++)
            ((short*)bufp)[i] = g711_buf[i];
         return size * sizeof(short);
      }
      /* Compress into the temporary g711 buffer */
      else if(bpch->sampleComp == BP_VC_COMP_ULAW)
         ulaw_compress(size / sizeof(short), (short*)bufp, (short*)g711_buf);
      else
         alaw_compress(size / sizeof(short), (short*)bufp, (short*)g711_buf);

      /* Setup the correct buffer according to what the G711 API expects */
      for(i = 0; i < size / sizeof(short); i++)
         bufp[i] = (char) g711_buf[i];

      return size / sizeof(short);
   }
   else
   {
#ifdef CONFIG_BCM94908
      dh_swap_word((uint16_t*)bufp, size);
#else
      dh_swap_byte((uint16_t*)bufp, size);
#endif
   }

   /* By default, don't bother with any decompression */
   return size;
}


/*****************************************************************************
*  FUNCTION:   pcm_decompress_and_swap
*
*  PURPOSE:    Handles decompression of PCM channel data and byte swapping, if
*              required
*
*  PARAMETERS: chan_cfg - channel config struct
*              bufp - buffer to decompress
*              size - buffer size
*
*  RETURNS:    new size after decompression
*
*****************************************************************************/
static int pcm_decompress_and_swap(struct dhchancfg *chan_cfg, char *bufp,
                                   int size)
{
   BP_VOICE_CHANNEL *bpch;
   int i;

   bpch = &vp.voiceDevice[chan_cfg->vp_dev].channel[chan_cfg->vp_chan];

   if(bpch->sampleComp != BP_VC_COMP_LINEAR)
   {
      /* Setup the correct buffer according to what the G711 API expects */
      for(i = 0; i < size; i++)
         g711_buf[i] = bufp[i];

      if(chan_cfg->clearchan)
      {
         /* Expand the 8-bit samples into padded 16-bit samples */
         for(i = 0; i < size; i++)
            g711_buf[i] = bufp[i] & 0xFF;
         for(i = 0; i < size; i++)
            ((short*)bufp)[i] = g711_buf[i];
      }
      else if(bpch->sampleComp == BP_VC_COMP_ULAW)
         ulaw_expand(size, (short*)g711_buf, (short*)bufp);
      else
         alaw_expand(size, (short*)g711_buf, (short*)bufp);

      return size * sizeof(short);
   }
   else
   {
#ifdef CONFIG_BCM94908
      dh_swap_word((uint16_t*)bufp, size);
#else
      dh_swap_byte((uint16_t*)bufp, size);
#endif
   }
   /* By default, don't bother with any decompression */
   return size;
}

void __weak pcm_pinmux(void) { }
void __weak pcm_pinunmux(void) { }
void __weak pcm_ts_init(void) { }
int  __weak pcm_quirk_open(struct dhchancfg *cfg, int count) { return 0; }
int  __weak pcm_quirk_release(struct dhchancfg *cfg, int count) { return 0; }

