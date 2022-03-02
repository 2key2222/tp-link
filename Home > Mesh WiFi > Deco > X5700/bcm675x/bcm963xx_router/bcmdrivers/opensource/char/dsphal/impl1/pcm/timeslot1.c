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
#endif
#include <dsphal_chip.h>
#include <dsphal_pcm.h>

#define PCM_MAX_CHAN    8
#define PCM_MAX_TS      32

/****************************************************************************
* Variables
****************************************************************************/
const int pcm_ts_impl = 1;

struct dma_ts_cfg
{
   /* DMA channel ID */
   unsigned int chan_id;
   /* Array of bits that correspond to timeslot enable bits for the timeslot
    * control register */
   unsigned int ch_ctl_bits[PCM_MAX_CHAN];
   int          ch_ts16_map[PCM_MAX_CHAN];
   int          ts_ch_map[PCM_MAX_TS];
};

static struct dma_ts_cfg ts_cfgs[] = {
   /* RX dma */
   {
      .chan_id     = PCM_DMA_CHANNEL_RX,
      .ch_ctl_bits = { PCM_RX0_EN, PCM_RX1_EN, PCM_RX2_EN, PCM_RX3_EN,
                       PCM_RX4_EN, PCM_RX5_EN, PCM_RX6_EN, PCM_RX7_EN,
                     },
   },

   /* TX dma */
   {
      .chan_id     = PCM_DMA_CHANNEL_TX,
      .ch_ctl_bits = { PCM_TX0_EN, PCM_TX1_EN, PCM_TX2_EN, PCM_TX3_EN,
                       PCM_TX4_EN, PCM_TX5_EN, PCM_TX6_EN, PCM_TX7_EN,
                     },
   }
};


/****************************************************************************
* Function implementation
****************************************************************************/

/*****************************************************************************
*  FUNCTION:   pcm_ts_init
*
*  PURPOSE:    Initialize the PCM timeslot settings
*
*  PARAMETERS: none
*
*  RETURNS:    nothing
*
*****************************************************************************/
void pcm_ts_init(void)
{
   int i, j;

   /* Reset all the timeslot-channel mappings to -1 */
   for(i = 0; i < ARRAY_SIZE(ts_cfgs); i++)
   {
      for(j = 0; j < ARRAY_SIZE(ts_cfgs[i].ts_ch_map); j++)
         ts_cfgs[i].ts_ch_map[j] = -1;
      for(j = 0; j < ARRAY_SIZE(ts_cfgs[i].ch_ts16_map); j++)
         ts_cfgs[i].ch_ts16_map[j] = -1;
   }
}

/*****************************************************************************
*  FUNCTION:   pcm_ts_alloc
*
*  PURPOSE:    Allocate an 8-bit PCM timeslot for a PCM audio channel
*
*  PARAMETERS: dma        - pointer to PCM dma config
*              ts         - 8-bit timeslot id
*              pcm_chan   - PCM channel id
*
*  RETURNS:    nothing
*
*****************************************************************************/
void pcm_ts_alloc(const struct pcm_dma *dma, int ts, int pcm_chan)
{
   struct dma_ts_cfg *ts_cfg = NULL;
   int ts_reg, shift, ts16, chan_id;
   int i;

   for(i = 0; i < ARRAY_SIZE(ts_cfgs); i++)
   {
      if(ts_cfgs[i].chan_id == dma->chan_id)
      {
         ts_cfg = &ts_cfgs[i];
         break;
      }
   }
   if(!ts_cfg)
   {
      DHLOG_ERR("%s: Unable to find timeslot control table for DMA "
                "channel %d.\n", __func__, dma->chan_id);
      return;
   }
   if(ts >= PCM_MAX_TS)
   {
      DHLOG_ERR("%s: ts %d outside possible range [0, %d].\n", __func__,
                ts, PCM_MAX_TS - 1);
      return;
   }

   /* The PCM deals with 16-bit timeslots, so we need to divide our input
    * channels by 2 */
   ts16 = ts >> 1;

   /* Allocate a new PCM DMA channel for the timeslot */
   if(ts_cfg->ts_ch_map[ts] == -1)
   {
      for(i = 0; i < ARRAY_SIZE(ts_cfg->ch_ts16_map); i++)
      {
         if(ts_cfg->ch_ts16_map[i] == -1)
         {
            /* Assign both 8-bit timeslots to the same 16-bit channel */
            chan_id = i;
            ts_cfg->ch_ts16_map[chan_id]       = ts16;
            ts_cfg->ts_ch_map[ts & ~0x1]       = chan_id;
            ts_cfg->ts_ch_map[(ts & ~0x1) + 1] = chan_id;
            break;
         }
      }
      if(i >= ARRAY_SIZE(ts_cfg->ch_ts16_map))
      {
         DHLOG_ERR("%s: No more available channels in DMA buffer\n", __func__);
         return;
      }
   }
   else
      chan_id = ts_cfg->ts_ch_map[ts];

   /* Find the register offset and calculate the ts value shift for the
    * register settings. Timeslots are allocated as 4 bit values from MSB to
    * LSB */
   ts_reg = ts16 / 8;
   shift = (8 - ((ts16 % 8) + 1)) * 4;

   /* Set the new PCM register setting */
   PCM->pcm_slot_alloc_tbl[ts_reg] &= ~(0xf << shift);
   PCM->pcm_slot_alloc_tbl[ts_reg] |= ((PCM_TS_VALID | chan_id) << shift);
   /* Cache the pcm channel control - this register can only be written to once
    * the PCM control is enabled */
   pcm_chan_ctrl                   |= ts_cfg->ch_ctl_bits[chan_id];

   DHLOG_INFO("%s: DMA %d timeslot [8-bit %d, 16-bit %d] assigned to "
         "channel %d as buffer channel %d\n", __func__, dma->chan_id, ts, ts16,
         pcm_chan, chan_id);
}


/*****************************************************************************
*  FUNCTION:   pcm_ts_dealloc
*
*  PURPOSE:    Deallocate an 8-bit RX and TX PCM timeslots
*
*  PARAMETERS: dma  - pointer to PCM dma config
*              ts   - 8-bit timeslot id
*
*  RETURNS:    nothing
*
*****************************************************************************/
void pcm_ts_dealloc(const struct pcm_dma *dma, int ts)
{
   struct dma_ts_cfg *ts_cfg = NULL;
   int ts_reg, shift, ts16, chan;
   int i, found;

   for(i = 0; i < ARRAY_SIZE(ts_cfgs); i++)
   {
      if(ts_cfgs[i].chan_id == dma->chan_id)
      {
         ts_cfg = &ts_cfgs[i];
         break;
      }
   }
   if(!ts_cfg)
   {
      DHLOG_ERR("%s: Unable to find timeslot control table for DMA "
                "channel %d.\n", __func__, dma->chan_id);
      return;
   }
   if(ts >= PCM_MAX_TS)
   {
      DHLOG_ERR("%s: ts %d outside possible range [0, %d].\n", __func__,
                ts, PCM_MAX_TS - 1);
      return;
   }

   chan = ts_cfg->ts_ch_map[ts];

   /* The PCM deals with 16-bit timeslots, so we need to divide our input
    * channels by 2 */
   ts16 = ts >> 1;

   /* Find the register offset and calculate the ts value shift for the
    * register settings */
   ts_reg = ts16 / 8;
   shift = (8 - (ts16 & 0x7) - 1) * 4;

   /* Set the new PCM register setting */
   PCM->pcm_slot_alloc_tbl[ts_reg] &= ~(0xf << shift);
   pcm_chan_ctrl                   &= ~ts_cfg->ch_ctl_bits[chan];
   ts_cfg->ts_ch_map[ts]            = -1;
   DHLOG_INFO("%s: DMA %d timeslot [8-bit %d, 16-bit %d] unassigned\n",
              __func__, dma->chan_id, ts, ts16);

   /* If there are no more timeslots using this channel, unmap the channel */
   found = 0;
   for(i = 0; i < ARRAY_SIZE(ts_cfg->ts_ch_map); i++)
   {
      if(ts_cfg->ts_ch_map[i] == chan) {
         found = 1;
         break;
      }
   }
   if(!found)
      ts_cfg->ch_ts16_map[chan] = -1;
}


/*****************************************************************************
*  FUNCTION:   pcm_ts_clear
*
*  PURPOSE:    Clear the timeslot allocation tables
*
*  PARAMETERS: none
*
*  RETURNS:    nothing
*
*****************************************************************************/
void pcm_ts_clear()
{
   int i;
   for(i = 0; i < PCM_MAX_TIMESLOT_REGS; i++)
      PCM->pcm_slot_alloc_tbl[i] = 0;

   /* Reset the channel control and the cached value */
   PCM->pcm_chan_ctrl = 0;
   pcm_chan_ctrl = 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_deinterleave_chan
*
*  PURPOSE:    Deinterleaves and copies audio data for a particular channel
*              from the PCM DMA buffer to the channel's ingress buffer.
*
*  PARAMETERS: chan_cfg   - audio channel config struct
*              in_buf     - ingress audio buffer
*              max_size   - max size of ingress buffer
*              dma_buf    - the dma buffer
*
*  RETURNS:    none
*
*****************************************************************************/
int pcm_deinterleave_chan(struct dhchancfg *chan_cfg, char *in_buf,
                          size_t max_size, char *dma_buf)
{
   BP_PCM_TS_CFG *tscfg;
   struct dma_ts_cfg *ts_cfg = &ts_cfgs[0];
   unsigned int frame_size, frame_offset;
   unsigned int ts_count, ch_offset;
   unsigned int i, j, k;

   frame_size = pcm_frame_size();
   tscfg = &vp.voiceDevice[chan_cfg->vp_dev].channel[chan_cfg->vp_chan].
            cfg.pcm.ts;

  /* Iterate through every frame 'j'. For each frame, we iterate through the
   * channel's configured timeslots and copy (in order) the bytes from the
   * frame at timeslot offsets 'k' into the ingress audio buffer.
   *
   * In order to optimize the transfer to each PCM FIFO, the DMA buffer places
   * 4 8-bit samples (or 2 16-bit samples) per PCM channel back to back.
   * Timeslots are mapped into these channels based on the pcm_chan_ctrl
   * config. This means the buffer layout is as follows:
   *
   *
   *            |--------- 32 bits ---------|
   *            |8 bits|
   *
   *             <- FRAME 0 -> <- FRAME 1 ->
   *            |  channel 0  |  channel 0  |  <-- word0 contains data
   *            |  channel 1  |  channel 1  |      for channel 0 for
   *            |  channel 2  |  channel 2  |      frames 0 and 1.
   *            |  channel 3  |  channel 3  |
   *                         ...
   *            |  channel 7  |  channel 7  |
   *             ---------------------------
   *             <- FRAME 2 -> <- FRAME 3 ->
   *            |  channel 0  |  channel 0  |
   *            |  channel 1  |  channel 1  |
   *            |  channel 2  |  channel 2  |
   *            |  channel 3  |  channel 3  |
   *                         ...
   *            |  channel 7  |  channel 7  |
   *             ---------------------------
   *                        etc.
   *
   */

   /* Find the number of allocated timeslots */
   for(k = 0; k < ARRAY_SIZE(tscfg->rxTimeslot) &&
         tscfg->rxTimeslot[k] >= 0; k++);
   ts_count = k;

   /* For each frame 'j' in the PCM buffer */
   i = 0;
   for(j = 0; j < PCM_FRAMES_PER_TICK; j++)
   {
      frame_offset = (j & ~0x1) * frame_size + 2 * (j & 0x1);
      /* For each timeslot 'k' in the channel */
      for(k = 0; k < ts_count; k++)
      {
         ch_offset = ts_cfg->ts_ch_map[tscfg->rxTimeslot[k]];
         ch_offset = pcm_get_rx_ch_index(ch_offset);
         ch_offset = (ch_offset * 4) + (tscfg->rxTimeslot[k] & 0x1);

         /* Copy the byte from timeslot offset 'ts' from frame 'j' */
         in_buf[i] = dma_buf[frame_offset + ch_offset];
         i++;
         if(i >= max_size)
            goto out;
      }
   }

out:
   return i;
}

/*****************************************************************************
*  FUNCTION:   pcm_interleave_chan
*
*  PURPOSE:    Interleaves and copies audio data for a particular channel into
*              the PCM DMA buffer.
*
*  PARAMETERS: chan_cfg   - audio channel config struct
*              eg_buf     - egress audio buffer
*              size       - size of data to copy from egress buffer
*              dma_buf    - the dma buffer
*
*  RETURNS:    none
*
*****************************************************************************/
void pcm_interleave_chan(struct dhchancfg *chan_cfg, char *eg_buf, size_t size,
                         char *dma_buf)
{
   BP_PCM_TS_CFG *tscfg;
   struct dma_ts_cfg *ts_cfg = &ts_cfgs[1];
   unsigned int frame_size, frame_offset;
   unsigned int ts_count, ch_offset;
   unsigned int i, j, k;

   frame_size = pcm_frame_size();
   tscfg = &vp.voiceDevice[chan_cfg->vp_dev].channel[chan_cfg->vp_chan].
            cfg.pcm.ts;

   /* Find the number of allocated timeslots */
   for(k = 0; k < ARRAY_SIZE(tscfg->txTimeslot) &&
         tscfg->txTimeslot[k] >= 0; k++);
   ts_count = k;

   i = 0;
   frame_offset = 0;
   /* For each frame 'j', iterate through the channel's configured timeslots
    * and copy (in order) the bytes from the temporary buffer into frame 'j' at
    * timeslot offsets 'k'. */
   for(j = 0; j < PCM_FRAMES_PER_TICK; j++)
   {
      frame_offset = (j & ~0x1) * frame_size + 2 * (j & 0x1);
      /* For each timeslot configured, copy the audio data */
      for(k = 0; k < ts_count; k++)
      {
         ch_offset = ts_cfg->ts_ch_map[tscfg->txTimeslot[k]];
         ch_offset = pcm_get_tx_ch_index(ch_offset);
         ch_offset = (ch_offset * 4) + (tscfg->txTimeslot[k] & 0x1);

         /* copy the byte into timeslot offset 'ts' from frame 'j' */
         dma_buf[frame_offset + ch_offset] = eg_buf[i];
         i++;
      }
   }
}


/*****************************************************************************
*  FUNCTION:   pcm_frame_size
*
*  PURPOSE:    Calculate the size of a single frame in the PCM DMA buffer.
*
*  PARAMETERS: none
*
*  RETURNS:    size, in bytes, of the pcm frame
*
*****************************************************************************/
size_t pcm_frame_size(void)
{
   return PCM_FRAME_BUF_SIZE(PCM_MAX_CHAN * PCM_BYTES_PER_SAMPLE);
}
