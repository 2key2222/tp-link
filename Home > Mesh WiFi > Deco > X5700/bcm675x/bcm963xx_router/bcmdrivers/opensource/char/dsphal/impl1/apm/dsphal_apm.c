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
#include <linux/slab.h>

#include <dsphal_apm.h>


/****************************************************************************
* Local function declaration
****************************************************************************/
#ifdef APM_DMA_SUPPORT
static int  apm_config_channel(struct dhchancfg *cfg);
static int  apm_deconfig_channel(struct dhchancfg *cfg);
static int  apm_open_channel(struct dhchancfg *cfg, int count);
static int  apm_release_channel(struct dhchancfg *cfg, int count);
static int  apm_dma_chan_init(struct dhchancfg *chan, struct apm_dma *dma);
static int  apm_dma_chan_deinit(struct dhchancfg *cfg, struct apm_dma *dma);
static void apm_dma_read_cb(unsigned int chan, char *bufp, size_t size,
                            dma_addr_t bufp_dma);
static void apm_dma_write_cb(unsigned int chan, char *bufp, size_t size,
                             dma_addr_t bufp_dma);
#ifdef BRCM_VOICE_DIRECT_EGRESS
static void apm_write_direct(struct dhchancfg *cfg);
#endif
static void apm_swap_bytes(char *bufp, size_t size);
#endif /* APM_DMA_SUPPORT */


/****************************************************************************
* Variables
****************************************************************************/
struct intf_hdlrs apm_hdlr_table = {
   .init       = apm_init,
   .deinit     = apm_deinit,
#ifdef APM_DMA_SUPPORT
   .config     = apm_config_channel,
   .deconfig   = apm_deconfig_channel,
   .open       = apm_open_channel,
   .release    = apm_release_channel,
#endif /* APM_DMA_SUPPORT */
};

#ifdef APM_DMA_SUPPORT
static struct apm_dma apm_dma_cfg[] = {
   /* RX A dma */
   {
      .chan_id        = APM_DMA_CHANNEL_RX_A,
      .data_cb        = apm_dma_read_cb,
      .direction      = DMA_FROM_DEVICE,
      .burst_size     = 1,
      .interrupt_chan = APM_DMA_CHANNEL_RX_A,
      .tick           = 0,
   },

   /* TX A dma */
   {
      .chan_id        = APM_DMA_CHANNEL_TX_A,
#ifndef BRCM_VOICE_DIRECT_EGRESS
      .data_cb        = apm_dma_write_cb,
#endif
      .direction      = DMA_TO_DEVICE,
      .burst_size     = 1,
      .interrupt_chan = APM_DMA_CHANNEL_RX_A,
      .tick           = 0,
   },

   /* RX B dma */
   {
      .chan_id        = APM_DMA_CHANNEL_RX_B,
      .data_cb        = apm_dma_read_cb,
      .direction      = DMA_FROM_DEVICE,
      .burst_size     = 1,
      .interrupt_chan = APM_DMA_CHANNEL_RX_A,
      .tick           = 0,
   },

   /* TX B dma */
   {
      .chan_id        = APM_DMA_CHANNEL_TX_B,
#ifndef BRCM_VOICE_DIRECT_EGRESS
      .data_cb        = apm_dma_write_cb,
#endif
      .direction      = DMA_TO_DEVICE,
      .burst_size     = 1,
      .interrupt_chan = APM_DMA_CHANNEL_RX_A,
      .tick           = 0,
   },
};

static int apm_channels_reg = 0;
#endif /* APM_DMA_SUPPORT */

/****************************************************************************
* Function implementation
****************************************************************************/

/*****************************************************************************
*  FUNCTION:   apm_init
*
*  PURPOSE:    Handle powering up of the APM block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int apm_init(void)
{
   int ret = 0;

   /* Power up the APM block */
   apm_power_up();
   apm_pinmux();

#ifdef APM_DMA_SUPPORT
   /* Configure the APM clock */
   ret = apm_clk_init();
   if(ret)
      goto err_power;

   return 0;

err_power:
   apm_power_down();
#endif /* APM_DMA_SUPPORT */
   return ret;
}


/*****************************************************************************
*  FUNCTION:   apm_deinit
*
*  PURPOSE:    Handle deinitialization of the APM block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int apm_deinit(void)
{
#ifdef APM_DMA_SUPPORT
   apm_power_down();
#endif /* APM_DMA_SUPPORT */
   apm_pinunmux();
   return 0;
}

#ifdef APM_DMA_SUPPORT
/*****************************************************************************
*  FUNCTION:   apm_config_channel
*
*  PURPOSE:    Handle configuring the APM channel prior to opening/releasing
*
*  PARAMETERS: cfg - channel configuration
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
static int apm_config_channel(struct dhchancfg *cfg)
{
   int ret = -ENOMEM, i;
   BP_VOICE_CHANNEL *chan;
   struct apm_chan_priv *priv;
   struct apm_dma *rx_dma, *tx_dma;

   /* Setup the channel's private data */
   priv = kzalloc(sizeof(*priv), GFP_KERNEL);
   if(!priv)
      goto out;

   /* Based on the board params, we attach the channel to the appropriate
    * APM DMA */
   chan = &vp.voiceDevice[cfg->vp_dev].channel[cfg->vp_chan];
   priv->apm_chan_id = chan->cfg.apm.chan;
#ifdef BRCM_VOICE_APM_CHANNEL_SWAP
   priv->apm_chan_id ^= 1;
#endif
   switch(priv->apm_chan_id)
   {
      case BP_APM_CHAN_A:
         rx_dma = &apm_dma_cfg[0];
         tx_dma = &apm_dma_cfg[1];
         break;

      case BP_APM_CHAN_B:
         rx_dma = &apm_dma_cfg[2];
         tx_dma = &apm_dma_cfg[3];
         break;

      default:
         DHLOG_ERR("%s: APM channel %d has no DMA channel assigned\n",
                   __func__, cfg->id);
         ret = -EINVAL;
         goto err_cleanup_priv;
   }
   priv->rx_dma = rx_dma;
   priv->tx_dma = tx_dma;
   cfg->priv    = priv;
#ifdef BRCM_VOICE_DIRECT_EGRESS
   cfg->direct_eg = apm_write_direct;
#endif

   /* If this is the first APM channel registered, set it as the tick owner and
    * interrupt handler master */
   apm_channels_reg++;
   if(apm_channels_reg == 1)
   {
      struct apm_dma *dma_ticker = tx_dma;
      DHLOG_NOTICE("%s: Using DMA channel %d to drive APM\n", __func__,
                   dma_ticker->chan_id);
      dma_ticker->tick = APM_MS_PER_TICK;
      for(i = 0; i < ARRAY_SIZE(apm_dma_cfg); i++)
         apm_dma_cfg[i].interrupt_chan = dma_ticker->chan_id;
   }

   /* Initialize the DMAs for this channel */
   ret = apm_dma_chan_init(cfg, rx_dma);
   if(ret)
      goto err_cleanup_dma_reg;
   ret = apm_dma_chan_init(cfg, tx_dma);
   if(ret)
      goto err_cleanup_rx_dma;

   return 0;

err_cleanup_rx_dma:
   apm_dma_chan_deinit(cfg, priv->rx_dma);
err_cleanup_dma_reg:
   apm_channels_reg--;
err_cleanup_priv:
   kfree(priv);
   cfg->priv = NULL;
out:
   return ret;
}


/*****************************************************************************
*  FUNCTION:   apm_deconfig_channel
*
*  PURPOSE:    Handle configuring the APM channel prior to opening/releasing
*
*  PARAMETERS: cfg    - channel configuration
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
static int apm_deconfig_channel(struct dhchancfg *cfg)
{
   struct apm_chan_priv *priv;

   priv = (struct apm_chan_priv*) cfg->priv;
   if(!priv)
      return 0;

   /* Cleanup the DMAs for this channel */
   apm_dma_chan_deinit(cfg, priv->rx_dma);
   apm_dma_chan_deinit(cfg, priv->tx_dma);
   apm_channels_reg--;

   /* Free the private channel data */
   kfree(cfg->priv);
   cfg->priv = NULL;

   return 0;
}


/*****************************************************************************
*  FUNCTION:   apm_open_channel
*
*  PURPOSE:    Handle opening the APM channel
*
*  PARAMETERS: cfg    - channel configuration
*              count  - number of active channels (after adding current)
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
static int apm_open_channel(struct dhchancfg *cfg, int count)
{
   struct apm_chan_priv *priv = (struct apm_chan_priv *)cfg->priv;

   /* If this is the first channel opened, reset the APM dma interrupts */
   if(count == 1)
      apm_dma_init();

   /* Enable interrupts for this APM DMA */
   apm_dma_start(priv);

   /* Start each iudma channel */
   iudma_enable_chan(priv->rx_dma->chan_id);
   iudma_enable_chan(priv->tx_dma->chan_id);

   /* If we have any channel enabled, start the DMA */
   if(count == 1)
      iudma_start();

   return 0;
}


/*****************************************************************************
*  FUNCTION:   apm_release_channel
*
*  PURPOSE:    Handle releasing the given APM channel
*
*  PARAMETERS: cfg    - channel configuration
*              count  - number of active channels (after removing current)
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
static int apm_release_channel(struct dhchancfg *cfg, int count)
{
   struct apm_chan_priv *priv = (struct apm_chan_priv *)cfg->priv;

   /* Disable interrupts for this APM DMA */
   apm_dma_stop(priv);

   /* If this is the last channel closed, clear the APM DMA interrupts */
   if(count == 0) {
      iudma_stop();
      apm_dma_deinit();
   }

   return 0;
}


/*****************************************************************************
*  FUNCTION:   apm_dma_chan_init
*
*  PURPOSE:    Initialize an APM channel's DMA
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*  NOTES:      This function assumes it will only be called once to initialize
*              the DMA.
*
*****************************************************************************/
static int apm_dma_chan_init(struct dhchancfg *chan, struct apm_dma *dma)
{
   int ret = -ENOMEM;

   /* Calculate the buffer size */
   dma->buffer_size  = APM_BYTES_PER_SAMPLE;
   dma->buffer_size *= (chan->rate == DSPHAL_RATE_8KHZ) ? APM_SAMPLES_PER_MS :
                       APM_SAMPLES_PER_MS_WB;
   dma->buffer_size *= APM_MS_PER_TICK;
   dma->buffer_count = APM_NUM_BUF_PER_CHAN;

   dma->buffer.cpu   = kmalloc(dma->buffer_size * dma->buffer_count,
                               GFP_KERNEL | GFP_DMA);
   if(!dma->buffer.cpu)
   {
      DHLOG_ERR("%s: error allocating dma buffers\n", __func__);
      goto out;
   }

   dma->buffer.dma = dma_map_single(dhdev.device, dma->buffer.cpu,
                                    dma->buffer_size * dma->buffer_count,
                                    dma->direction);

   DHLOG_DEBUG("%s: chan %d buffer area 0x%p [0x%x] size %d\n", __func__,
               chan->id, dma->buffer.cpu, dma->buffer.dma,
               dma->buffer_size * dma->buffer_count);

   ret = iudma_request_chan(dma->chan_id, dma->buffer_count, dma->buffer_size,
                            &dma->buffer);
   if(ret)
   {
      DHLOG_ERR("%s: error while requesting iudma chan %d\n", __func__,
                chan->id);
      goto err_cleanup_iudma_chan;
   }

   iudma_config_chan(dma->chan_id, dma->burst_size, dma->direction,
                     dma->data_cb, dma->interrupt_chan, dma->tick);
   return 0;

err_cleanup_iudma_chan:
   iudma_release_chan(dma->chan_id);

   if(dma->buffer.cpu)
   {
      dma_unmap_single(dhdev.device, dma->buffer.dma,
            dma->buffer_size * dma->buffer_count, dma->direction);
      kfree(dma->buffer.cpu);
   }
out:
   return ret;
}


/*****************************************************************************
*  FUNCTION:   apm_dma_chan_deinit
*
*  PURPOSE:    Deinitialize an APM channel's DMA
*
*  PARAMETERS: cfg - audio channel config
*              dma - APM dma structure
*
*  RETURNS:    0 on success, error otherwise
*
*  NOTES:      This function assumes it will only be called once to
*              deinitialize the DMA.
*
*****************************************************************************/
static int apm_dma_chan_deinit(struct dhchancfg *cfg, struct apm_dma *dma)
{
   /* Release the DMA channel */
   iudma_release_chan(dma->chan_id);

   /* Free the allocated DMA buffers and descriptors */
   if(dma->buffer.cpu)
   {
      dma_unmap_single(dhdev.device, dma->buffer.dma,
            dma->buffer_size * dma->buffer_count, dma->direction);
      kfree(dma->buffer.cpu );
   }
   dma->buffer.cpu   = NULL;
   dma->buffer_size  = 0;
   dma->buffer_count = 0;

   return 0;
}


/*****************************************************************************
*  FUNCTION:   apm_dma_read_cb
*
*  PURPOSE:    Read callback for the APM DMA. Copies audio data from the APM
*              DMA buffer into each audio channel's buffer.
*
*  PARAMETERS: chan - DMA channel id
*              bufp - the DMA buffer
*              size - size of the buffer
*
*  RETURNS:    none
*
*  NOTES:      This function is called from the context of the DMA ISR
*
*****************************************************************************/
static void apm_dma_read_cb(unsigned int chan, char *bufp, size_t size,
                            dma_addr_t bufp_dma)
{
   struct apm_chan_priv *priv;
   int i;

   /* Find the right audio channel and copy the ingress samples */
   for(i = 0; i < ARRAY_SIZE(chan_cfg); i++)
   {
      if(!chan_cfg[i].enabled || chan_cfg[i].interface != DSPHAL_INTF_APM)
         continue;

      priv = (struct apm_chan_priv*) chan_cfg[i].priv;
      if(!priv || priv->rx_dma->chan_id != chan)
         continue;

      dma_sync_single_for_cpu(dhdev.device, bufp_dma,
            priv->rx_dma->buffer_size, priv->rx_dma->direction);

      apm_swap_bytes(bufp, size);
      dh_copy_ingress(&chan_cfg[i], bufp, size);
      break;
   }
}


/*****************************************************************************
*  FUNCTION:   apm_dma_write_cb
*
*  PURPOSE:    Write callback for the APM DMA. Copies audio data from each
*              configured audio channel's buffer into the APM DMA buffer.
*
*  PARAMETERS: chan - DMA channel id
*              bufp - the DMA buffer
*              size - size of the buffer
*
*  RETURNS:    none
*
*  NOTES:      This function is called from the context of the DMA ISR
*
*****************************************************************************/
static void apm_dma_write_cb(unsigned int chan, char *bufp, size_t size,
                             dma_addr_t bufp_dma)
{
   struct apm_chan_priv *priv;
   int i;

   /* Find the right audio channel and copy the egress samples */
   for(i = 0; i < ARRAY_SIZE(chan_cfg); i++)
   {
      if(!chan_cfg[i].enabled || chan_cfg[i].interface != DSPHAL_INTF_APM)
         continue;

      priv = (struct apm_chan_priv*) chan_cfg[i].priv;
      if(!priv || priv->tx_dma->chan_id != chan)
         continue;

      dh_copy_egress(&chan_cfg[i], bufp, size);
      apm_swap_bytes(bufp, size);

      dma_sync_single_for_device(dhdev.device, bufp_dma,
            priv->tx_dma->buffer_size, priv->tx_dma->direction);
      break;
   }
}


#ifdef BRCM_VOICE_DIRECT_EGRESS
/*****************************************************************************
*  FUNCTION:   apm_write_direct
*
*  PURPOSE:    Write directly to the APM DMA. Copies audio data from a
*              particular configured audio channel's buffer into the APM DMA
*              buffer.
*
*  PARAMETERS: cfg  - channel config struct
*
*  RETURNS:    none
*
*****************************************************************************/
static void apm_write_direct(struct dhchancfg *cfg)
{
   size_t dma_size = 0;
   char* dma_buf = NULL;
   struct apm_chan_priv *priv = cfg->priv;

   if(!cfg->enabled || !priv)
      return;

   iudma_get_next_buf(priv->tx_dma->chan_id, &dma_buf, &dma_size);
   if(!dma_buf || !dma_size)
      return;

   dh_copy_egress(cfg, dma_buf, priv->tx_dma->buffer_size);
   apm_swap_bytes(dma_buf, priv->tx_dma->buffer_size);
}
#endif


/*****************************************************************************
*  FUNCTION:   apm_byte_swap
*
*  PURPOSE:    Swap bytes, if necessary
*
*  PARAMETERS: bufp - the buffer to swap
*              size - size of the buffer
*
*  RETURNS:    none
*
*****************************************************************************/
static void apm_swap_bytes(char *bufp, size_t size)
{
   uint16_t *swapbufp;
   unsigned int i;

   /* Perform byte swapping if required */
   swapbufp = (uint16_t*) bufp;
   for(i = 0; i < size >> 1; i++)
      swapbufp[i] = ntohs(swapbufp[i]);
}
#endif /* APM_DMA_SUPPORT */

void __weak apm_pinmux(void) { }
void __weak apm_pinunmux(void) { }

