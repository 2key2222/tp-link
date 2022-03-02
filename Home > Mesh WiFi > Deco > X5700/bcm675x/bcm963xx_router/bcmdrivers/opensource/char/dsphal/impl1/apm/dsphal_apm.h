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
#ifndef _DSPHAL_APM_H
#define _DSPHAL_APM_H

#include <linux/dma-mapping.h>

#include <bcm_map_part.h>

#include <dsphal.h>
#include <dsphal_chip.h>
#include <apm_regs.h>
#include <iudma.h>

/****************************************************************************
* Typedefs and Constants
****************************************************************************/
#define APM_MS_PER_TICK            5
#define APM_NUM_BUF_PER_CHAN       2 /* double-buffer scheme */

#define APM_BYTES_PER_SAMPLE       sizeof(uint16_t)
#define APM_SAMPLES_PER_MS         8
#define APM_SAMPLES_PER_MS_WB      16

/* Structure that defines the DMA configuration */
struct apm_dma
{
   /* DMA channel ID */
   unsigned int chan_id;
   /* Pointer to data callback to call when interrupt fires */
   void         (*data_cb)(unsigned int chan, char *bufp, size_t size,
                           dma_addr_t bufp_dma);
   /* Direction of DMA */
   enum dma_data_direction direction;
   /* Burst size */
   int          burst_size;
   /* The id of the channel's interrupt that calls this channel's data
    * callback. Note that if this is the same as the channel id, the interrupt
    * will be automatically enabled for this channel, otherwise it will be
    * disabled. */
   int          interrupt_chan;
   /* The time in msec at which this channel interrupt generates an tick.
    * If 0, the channel does not generate a tick */
   int          tick;

   struct dma_addr buffer;
   /* Size of individual buffer */
   size_t       buffer_size;
   /* Number of buffers for a given channel */
   unsigned int buffer_count;
};

/* Private data saved in each configured channel's config */
struct apm_chan_priv
{
   struct apm_dma *rx_dma;
   struct apm_dma *tx_dma;
   unsigned int    apm_chan_id;
};


/****************************************************************************
* Function Definitions
****************************************************************************/
/* called by dsphal internally, implemented in chip-specific files */
int apm_init(void);
int apm_deinit(void);
void apm_power_up(void);
void apm_power_down(void);
int apm_clk_init(void);
#ifdef APM_DMA_SUPPORT
int apm_dma_init(void);
int apm_dma_deinit(void);
int apm_dma_start(struct apm_chan_priv *priv);
int apm_dma_stop(struct apm_chan_priv *priv);
#endif /* APM_DMA_SUPPORT */
void apm_pinmux(void);
void apm_pinunmux(void);

#endif /* _DSPHAL_PCM_H */
