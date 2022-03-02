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
#ifndef _CFE_
#include <linux/delay.h>
#endif

#include <dsphal_pcm.h>
#include <bcm_pinmux.h>

extern struct pcm_dma pcm_dma_cfg[];
/****************************************************************************
* External functions
****************************************************************************/
int pcm_init(void);
int pcm_start(void);
int pcm_stop(void);
int pcm_deinit(void);
void pcm_cfg_dpll_div(void)
{
#ifdef BRCM_NTR_SUPPORT
    *(unsigned int*)(WAN_BASE + 0x34) |= (3 << 10);
    *(unsigned int*)(WAN_BASE + 0x34) &= ~0x00000300;
    *(unsigned int*)(NTR_BASE) |= 0x03;
#if 0 
/* This is to test and measure the NTR output clk via GPIO14. */
    bcm_set_pinmux( 14, PINMUX_1 ); /* GPIO14- A_NTR_OUT */
    *(unsigned int*)(NTR_BASE + 0x340) =   0xF4240 ;
    *(unsigned int*)(NTR_BASE + 0x344) = 0xa0;
#endif

    *(unsigned int*)(NTR_BASE + 0x348) = 0xF4240;
    *(unsigned int*)(NTR_BASE + 0x34c) = 0xa0;

   /* Local clk is generated via DPLL NCO @ 65.536Mhz
    * Ref clk from EPON Serdes is @ 40kHz
    * Phase comparator compares both clocks @ 8Khz
    * 8Khz = 65.536Mhz / (8191+1) = 40khz / (4+1)
    * local_div = 8191, ref_div = 0 */
    DPLL->dpll_div = (4 << DPLL_REF_DIV_SHIFT) | 8191;

    DHLOG_INFO("%s: DPLL programmed for NCO refclk @ 40khz\n",
            __func__);

#endif /* BRCM_NTR_SUPPORT */
}


int pcm_quirk_open(struct dhchancfg *cfg, int count)
{
   int i, tsnum, ret;
   BP_VOICE_CHANNEL *chan;

   /* Ensure PCM block is powered */
   ret = pcm_init();
   if(ret)
      return ret;

   if(cfg->initialized)
      return 0;

   /* Add the channel to the timeslot map */
   chan  = &vp.voiceDevice[cfg->vp_dev].channel[cfg->vp_chan];
   tsnum = BP_PCM_TS_COUNT(chan->sampleComp, chan->sampleRate);

   /* Allocate RX and TX timeslots */
   for(i = 0; i < tsnum; i++)
   {
      pcm_ts_alloc(&pcm_dma_cfg[0], chan->cfg.pcm.ts.rxTimeslot[i],
                   chan->cfg.pcm.pcmChanId);
   }

   cfg->initialized = 1;

   return 0;
}

int pcm_quirk_release(struct dhchancfg *cfg, int count)
{
   (void)cfg;

   /* Make sure config is deinitialized */
   cfg->initialized = 0;

   if(count > 0)
      return 0;

   /* Shutdown the PCM block */
   return pcm_deinit();
}
