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

#include <linux/delay.h>

#include <dsphal_pcm.h>

#include <bcm_pinmux.h>

#ifdef BRCM_NTR_SUPPORT
#include <rdpa_api.h>

extern rdpa_wan_type get_rdpa_wan_type(void);
#endif /* BRCM_NTR_SUPPORT */

void pcm_pinmux()
{
   /* Add PinMux for PCM pins (TODO:Remove Magic Numbers) */
   bcm_set_pinmux( 0, PINMUX_PCM ); /* GPIO0 - PCM_SDIN */
   bcm_set_pinmux( 1, PINMUX_PCM ); /* GPIO1 - PCM_SDOUT */
   bcm_set_pinmux( 2, PINMUX_PCM ); /* GPIO2 - PCM_CLK */
   bcm_set_pinmux( 3, PINMUX_PCM ); /* GPIO3 - PCM_FS */
}

void pcm_cfg_dpll_div(void)
{
#ifdef BRCM_NTR_SUPPORT
   /* Setup DPLL registers based on WAN type */
   switch (get_rdpa_wan_type())
   {
      case rdpa_wan_gpon:
         /* Local clk is generated via DPLL NCO @ 65.536Mhz
          * Ref clk from GPON Serdes is @ 256Khz
          * Phase comparator compares both clocks @ 8Khz
          * 8Khz = 65.536Mhz / (8191+1) = 256Khz / (31+1)
          * local_div = 8191, ref_div = 31 */
         PCM->dpll_div = (31 << DPLL_REF_DIV_SHIFT) | 8191;
         DHLOG_INFO("%s: DPLL programmed for GPON refclk @ 256Khz\n",
                     __func__);
         break;

      case rdpa_wan_epon:
         /* Local clk is generated via DPLL NCO @ 65.536Mhz
          * Ref clk from EPON Serdes is @ 40Khz
          * Phase comparator compares both clocks @ 8Khz
          * 8Khz = 65.536Mhz / (8191+1) = 40Khz / (4+1)
          * local_div = 8191, ref_div = 4 */
         PCM->dpll_div = (4 << DPLL_REF_DIV_SHIFT) | 8191;
         DHLOG_INFO("%s: DPLL programmed for EPON refclk @ 40Khz\n",
                     __func__);
         break;

      default:
         DHLOG_INFO("%s: Unknown WAN mode, using standalone\n",
                     __func__);
         break;
   }
#endif
}
