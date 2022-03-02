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
#include <dsphal_pcm.h>
#include <linux/sort.h>

#if defined(PCM_LOW_VOICE_DENSITY)
#   define PCM_MAX_TS      16
#else
#   define PCM_MAX_TS      32
#endif
#define PCM_MAX_CHAN PCM_MAX_TS/2   
#define PCM_MAP_MAX 0xffff
/****************************************************************************
* Variables
****************************************************************************/
const int pcm_ts_impl = 2;
static int pcm_chan_count = 0;

struct dma_ts_cfg
{
   int ts_map[PCM_MAX_TS/2]; // devide by two because we use ts16
   int pcm_map[PCM_MAX_CHAN];
};

static struct dma_ts_cfg ts_cfg_txrx = {};
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
   int j;                       
   for(j = 0; j < ARRAY_SIZE(ts_cfg_txrx.ts_map); j++)
   {
      /* Reset all the timeslot-channel mappings to -1 */
      ts_cfg_txrx.ts_map[j] = -1;
      /* Set defaults to a bigger number than PCM_MAX_CHAN to prevent errors in sort functions */
      ts_cfg_txrx.pcm_map[j] = PCM_MAP_MAX;
   }
}

/*****************************************************************************
*  FUNCTION:   compare
*
*  PURPOSE:    find if arg1 is bigger, smaller, or equal to arg2. 
*              This is to be used by the sort function
*
*  PARAMETERS: elem1 and elem2
*
*  RETURNS:    1 if elem1 bigger
*              -1 if elem2 is bigger
*              0 if they are equal
*
*****************************************************************************/
static int compare (const void * elem1, const void * elem2) 
{
   int f = *((int*)elem1);
   int s = *((int*)elem2);
   if (f > s) return  1;
   if (f < s) return -1;
   return 0;
}

/*****************************************************************************
*  FUNCTION:   find_offset
*
*  PURPOSE:    Find the index/offset for a given value
*
*  PARAMETERS: offsets    - array of ts16 
*              value      - value to be found
*
*  RETURNS:    offset or -1 if not found
*
*****************************************************************************/

static inline int find_offset( const int offsets[], int size, int value)
{
   int i = 0;
   while ( i < size && offsets[i] != value ) 
      i++;
   return ( i == size ? -1 : i );
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
void pcm_ts_alloc( const struct pcm_dma *dma, int ts, int pcm_chan)
{
   int ts16, ts_reg, ts_loc, chan_id, i;
   struct dma_ts_cfg *ts_cfg = &ts_cfg_txrx;

   if(ts >= PCM_MAX_TS)
   {
      DHLOG_ERR("%s: ts %d outside possible range [0, %d].\n", __func__,
                ts, PCM_MAX_TS - 1);
      return;
   }

   /* The PCM deals with 16-bit timeslots, so we need to divide our input
    * channels by 2 */
   ts16 = ts >> 1;

   /* Find the register offset, where time slot bit can be set.
    * Each register can set 32 time slots and there are in total 4 registers */
   ts_reg = ts16 >> 5;
   /* Find the time slot position within the register */
   ts_loc = ts16 & 0x1F;
  
   /* Allocate a new PCM DMA channel for the timeslot */
   if(ts_cfg->ts_map[ts16] == -1)
   {
      for(chan_id = 0; chan_id < ARRAY_SIZE(ts_cfg->pcm_map); chan_id++)
      {
         if(ts_cfg->pcm_map[chan_id] == PCM_MAP_MAX)
         {
            /* Assign both 8-bit timeslots to the same 16-bit channel */
            ts_cfg->ts_map[ts16] = chan_id;
            ts_cfg->pcm_map[chan_id] = ts16;
            sort (ts_cfg->pcm_map, ARRAY_SIZE(ts_cfg->pcm_map), sizeof(ts_cfg->pcm_map[0]), &compare, NULL);
            break;
         }
      }
      if(chan_id >= ARRAY_SIZE(ts_cfg->pcm_map))
      {
         DHLOG_ERR("%s: No more available channels. chan_id=%d arSize=%d\n", __func__,chan_id, ARRAY_SIZE(ts_cfg->pcm_map) );
         return;
      }
   }

   /* Set the new PCM register setting */
   if(!(PCM->pcm_slot_alloc_tbl[ts_reg] & (1 << ts_loc)))
   {
      pcm_chan_count++;
      PCM->pcm_slot_alloc_tbl[ts_reg] |= (1 << ts_loc);
   }
   /* Cache the pcm channel control - this register can only be written to once
    * the PCM control is enabled */
   pcm_chan_ctrl |= (1 << ts_loc);
   for( i = 0 ; i < ARRAY_SIZE(ts_cfg->pcm_map) && ts_cfg->pcm_map[i]!=PCM_MAP_MAX ; i++) 
      DHLOG_DEBUG("%s: Chan %d ts16 %d updated offset = %d\n", __func__, ts_cfg->ts_map[i], ts_cfg->pcm_map[i], i);

   DHLOG_INFO("%s: DMA timeslot [8-bit %d, 16-bit %d] assigned to "
              "PCM channel %d\n", __func__, ts, ts16, pcm_chan);
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
   int ts16, ts_reg, ts_loc, chan_id;
   chan_id = 0;
   ts_loc = 0; 
   struct dma_ts_cfg *ts_cfg = &ts_cfg_txrx;

   if(ts >= PCM_MAX_TS)
   {
      DHLOG_ERR("%s: ts %d outside possible range [0, %d].\n", __func__,
                ts16, PCM_MAX_TS - 1);
      return;
   }

   /* The PCM deals with 16-bit timeslots, so we need to divide our input
    * channels by 2 */
   ts16 = ts >> 1;

   /* Find the register offset, where time slot bit can be set.
    * Each register can set 32 time slots */
   ts_reg = ts16 >> 5;
   /* Find the time slot position within the register */
   ts_loc = ts16 & 0x1F;

   /* Set the new PCM register setting */
   if(PCM->pcm_slot_alloc_tbl[ts_reg] & (1 << ts_loc))
   {
      pcm_chan_count--;
      PCM->pcm_slot_alloc_tbl[ts_reg] &= ~(1 << ts_loc);
      pcm_chan_ctrl                   &= ~(1 << ts_loc);
   }
   ts_cfg->ts_map[ts16] = -1;
   chan_id = find_offset( ts_cfg->pcm_map, PCM_MAX_CHAN, ts16);
   if (chan_id == -1 )
      DHLOG_ERR("%s: ts %d index not found.\n", __func__, ts);

   ts_cfg->pcm_map[chan_id] = PCM_MAP_MAX;
   sort (ts_cfg->pcm_map, sizeof(ts_cfg->pcm_map)/sizeof(ts_cfg->pcm_map[0]), sizeof(ts_cfg->pcm_map[0]), &compare, NULL);
 
   DHLOG_INFO("%s: DMA timeslot [8-bit %d, 16-bit %d] unassigned\n",
              __func__, ts, ts16);
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
   int i, j;
   for(i = 0; i < PCM_MAX_TIMESLOT_REGS; i++)
   {
      for(j = 0; j < 8 * sizeof(PCM->pcm_slot_alloc_tbl[0]); j++)
      {
         /* PCM block slot alloc register can only change by 1 bit at a time...
          * so make it happy */
         PCM->pcm_slot_alloc_tbl[i] &= ~(1 << j);
      }
   }

   /* Reset the channel control and the cached value */
   pcm_chan_ctrl = 0;
   pcm_chan_count = 0;             
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
*  RETURNS:    size of data copied into egress buffer
*
*****************************************************************************/
int pcm_deinterleave_chan(struct dhchancfg *chan_cfg, char *in_buf,
                          size_t max_size, char *dma_buf)
{
   BP_PCM_TS_CFG *tscfg;
   unsigned int frame_size, sample_offset, frame_length, ts16, 
                ch_offset, j, k, ts_count, buf_idx;
   struct dma_ts_cfg *ts_cfg = &ts_cfg_txrx;
   ts16 = -1;
   /* For each sample in the buffer */
   buf_idx = 0;
   /* get the frame size in bytes */
   frame_size = pcm_frame_size();
   tscfg = &vp.voiceDevice[chan_cfg->vp_dev].channel[chan_cfg->vp_chan].
            cfg.pcm.ts;

   /* Find the number of allocated timeslots */
   for(ts_count = 0; ts_count < ARRAY_SIZE(tscfg->txTimeslot) &&
         tscfg->txTimeslot[ts_count] >= 0; ts_count++);

   /* Convert frame_size in terms of bytes or short integers  */
   frame_length = frame_size >> ((PCM_BYTES_PER_SAMPLE == 1) ? 0 : 1);
   /* For each frame 'j', place the sample in the ingress buffer */
   for(j = 0; j < PCM_FRAMES_PER_TICK; j++)
   {
      sample_offset = (j * frame_length);
      /* Find the offset, where sample will be placed for chan_cfg->pcm_map */
      for (k = 0 ; k < ts_count ; k+=2)
      {
         ts16 = tscfg->txTimeslot[k] >> 1; 
         ch_offset = find_offset( ts_cfg->pcm_map, PCM_MAX_CHAN, ts16);
         if (ch_offset == -1 )
         {
            DHLOG_ERR("%s: ts %d offset not found.\n", __func__,
                  tscfg->txTimeslot[k]);
            break;
         }

         if (PCM_BYTES_PER_SAMPLE == 1)
            in_buf[buf_idx] = dma_buf[sample_offset + ch_offset];
         else
            ((uint16_t*)in_buf)[buf_idx] = ((uint16_t*)dma_buf)[sample_offset + ch_offset];
         buf_idx++;
      }
   }

   return (buf_idx * PCM_BYTES_PER_SAMPLE);
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
*              frame_size - size of a PCM frame, in bytes
*
*  RETURNS:    none
*
*****************************************************************************/
void pcm_interleave_chan(struct dhchancfg *chan_cfg, char *eg_buf, size_t size,
                         char *dma_buf)
{
   BP_PCM_TS_CFG *tscfg;
   unsigned int frame_size, sample_offset, frame_length, ts16, 
                ch_offset, j, k, ts_count, buf_idx;
   struct dma_ts_cfg *ts_cfg = &ts_cfg_txrx;
   ts16=-1;
   /* For each sample in the buffer */
   buf_idx = 0;
   /* get the frame size in bytes */
   frame_size = pcm_frame_size();
   tscfg = &vp.voiceDevice[chan_cfg->vp_dev].channel[chan_cfg->vp_chan].
            cfg.pcm.ts;

   /* Find the number of allocated timeslots */
   for(ts_count = 0; ts_count < ARRAY_SIZE(tscfg->txTimeslot) &&
         tscfg->txTimeslot[ts_count] >= 0; ts_count++);
   /* Convert frame_size in terms of bytes or short integers  */
   frame_length = frame_size >> ((PCM_BYTES_PER_SAMPLE == 1) ? 0 : 1);
   /* For each frame 'j', copy the sample from the egress buffer */
   for(j = 0; j < PCM_FRAMES_PER_TICK; j++)
   {
      sample_offset = (j * frame_length);
      /* Time slots are passed as 8-bit but we process as 16-bit so increment the K by 2*/ 
      for (k = 0 ; k < ts_count ; k+=2)
      {
         ts16 = tscfg->txTimeslot[k] >> 1; 
         /* Find the offset, where sample will be placed for chan_cfg->pcm_map */
         ch_offset = find_offset( ts_cfg->pcm_map, PCM_MAX_CHAN, ts16);
         if (ch_offset == -1 )
         {
            DHLOG_ERR("%s: ts %d offset not found.\n", __func__,
                  tscfg->txTimeslot[k]);
            break;
         }
 
         if (PCM_BYTES_PER_SAMPLE == 1)
           dma_buf[sample_offset + ch_offset] = eg_buf[buf_idx];
         else
            ((uint16_t*)dma_buf)[sample_offset + ch_offset] = ((uint16_t*)eg_buf)[buf_idx];
         buf_idx++;
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
   size_t frame_size;

   /* Frame size must always be a multiple of 64-bits */
   frame_size = PCM_FRAME_BUF_SIZE(pcm_chan_count * PCM_BYTES_PER_SAMPLE);
   frame_size = (frame_size + 7) & ~0x7;
   return frame_size;
}
