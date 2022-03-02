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

/****************************************************************************
* Externs and types
****************************************************************************/
#ifdef BRCM_NTR_SUPPORT
#include <rdpa_api.h>
#include <rdpa_drv.h>
#include <rdpa_types.h>
extern rdpa_wan_type rdpa_wan_type_get(void);
#endif /* BRCM_NTR_SUPPORT */
extern struct pcm_dma pcm_dma_cfg[];

/****************************************************************************
* External functions
****************************************************************************/
int pcm_init(void);
int pcm_start(void);
int pcm_stop(void);
int pcm_deinit(void);


/****************************************************************************
* Function implementation
****************************************************************************/
void pcm_cfg_dpll_div(void)
{
#ifdef BRCM_NTR_SUPPORT
  *(unsigned int*)(WAN_BASE + 0x48) |= 0x40000000;
  *(unsigned int*)(WAN_BASE + 0x4C) &= ~( 0xf << 8);

   /* Setup DPLL registers based on WAN type */
   switch (rdpa_wan_type_get())
   {
     case rdpa_wan_gpon:
         /* Generate 40KHz ntr_sync_pulse clock */
         *(unsigned int*)(WAN_BASE + 0x4c) |= (3 << 8); 
         /* Local clk is generated via DPLL NCO @ 65.536Mhz
          * Ref clk from EPON Serdes is @ 40Khz
          * Phase comparator compares both clocks @ 8Khz
          * 8Khz = 65.536Mhz / (8191+1) = 40Khz / (4+1)
          * local_div = 8191, ref_div = 4 */
         DPLL->dpll_div = (4 << DPLL_REF_DIV_SHIFT) | 8191;
         DHLOG_INFO("%s: DPLL programmed for GPON refclk @ 40KHz\n",
                     __func__);
         break;

      case rdpa_wan_epon:
         /* Generate 5MHz ntr_sync_pulse clock */
         *(unsigned int*)(WAN_BASE + 0x4c) |= (10 << 8);
         /* Local clk is generated via DPLL NCO @ 65.536Mhz
          * Ref clk from EPON Serdes is @ 5MHz
          * Phase comparator compares both clocks @ 8Khz
          * 8Khz = 65.536Mhz / (8191+1) = 5MHz / (624+1)
          * local_div = 8191, ref_div = 624 */
         DPLL->dpll_div = (624 << DPLL_REF_DIV_SHIFT) | 8191;
         DHLOG_INFO("%s: DPLL programmed for EPON refclk @ 5MHz\n",
                     __func__);
         break;
      case rdpa_wan_xgpon:
      case rdpa_wan_xepon:
         /* Generate 40KHz ntr_sync_pulse clock */
         *(unsigned int*)(WAN_BASE + 0x4c) |= (2 << 8);
         /* Local clk is generated via DPLL NCO @ 65.536Mhz
          * Ref clk from EPON Serdes is @ 40Khz
          * Phase comparator compares both clocks @ 8Khz
          * 8Khz = 65.536Mhz / (8191+1) = 40Khz / (4+1)
          * local_div = 8191, ref_div = 4 */
         DPLL->dpll_div = (4 << DPLL_REF_DIV_SHIFT) | 8191;
         DHLOG_INFO("%s: DPLL programmed for xEPON/xGPON refclk @ 40KHz\n",
                     __func__);
         break;


      default:
         DHLOG_INFO("%s: Unknown WAN mode, using standalone\n",
                     __func__);
         break;
   }
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
