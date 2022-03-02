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

#ifdef BRCM_NTR_SUPPORT
#include <rdpa_api.h>
#include <rdpa_drv.h>
#include <rdpa_types.h>
extern rdpa_wan_type rdpa_wan_type_get(void);
#endif /* BRCM_NTR_SUPPORT */

void pcm_cfg_dpll_div(void)
{
#ifdef BRCM_NTR_SUPPORT

  *(unsigned int*)(WAN_BASE + 0x48) |= 0x40000000;
  *(unsigned int*)(WAN_BASE + 0x4C) &= ~( 0xf << 8);

   /* Setup DPLL registers based on WAN type */
   switch (rdpa_wan_type_get())
   {
     case rdpa_wan_gpon:
         /* Generate 39.81KHz ntr_sync_pulse clock */
         *(unsigned int*)(WAN_BASE + 0x4c) |= (14 << 8); 
         /* Local clk is generated via DPLL NCO @ 65.536Mhz
          * Ref clk from EPON Serdes is @ 40Khz
          * Phase comparator compares both clocks @ 8Khz
          * 8Khz = 65.536Mhz / (8191+1) = 40Khz / (4+1)
          * local_div = 8191, ref_div = 4 */
         DPLL->dpll_div = (4 << DPLL_REF_DIV_SHIFT) | 8191;
         DHLOG_INFO("%s: DPLL programmed for GPON refclk @ 39.81KHz\n",
                     __func__);
         break;

      case rdpa_wan_epon:
         /* Generate 40KHz ntr_sync_pulse clock */
         *(unsigned int*)(WAN_BASE + 0x4c) |= (14 << 8);
         /* Local clk is generated via DPLL NCO @ 65.536Mhz
          * Ref clk from EPON Serdes is @ 40KHz
          * Phase comparator compares both clocks @ 8Khz
          * 8Khz = 65.536Mhz / (8191+1) = 40Khz / (4+1)
          * local_div = 8191, ref_div = 4 */
         DPLL->dpll_div = (4 << DPLL_REF_DIV_SHIFT) | 8191;
         DHLOG_INFO("%s: DPLL programmed for EPON refclk @ 40Khz\n",
                     __func__);
         break;

      default:
         DHLOG_INFO("%s: Unknown WAN mode, using standalone\n",
                     __func__);
         break;
   }
#endif /* BRCM_NTR_SUPPORT */
}
