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

#include <dsphal_apm.h>
#include <dsphal_pcm.h>

#include <shared_utils.h>
#include <board.h>

#include <pmc/pmc_drv.h>
#include <pmc/BPCM.h>
#ifdef BRCM_NTR_SUPPORT
#include <rdpa_api.h>

extern rdpa_wan_type get_rdpa_wan_type(void);
#endif /* BRCM_NTR_SUPPORT */


/* --- Function Declarations ------------------------------------------------ */
void pmc_apm_power_up(void);
void pmc_apm_power_down(void);
void pmc_pcm_power_up(void);
void pmc_pcm_power_down(void);
int apm_cfg_pll_div(void);


/* --- Functions ------------------------------------------------------------ */
void pmc_apm_power_up(void)
{
   BPCM_SR_CONTROL sr_control;
   unsigned int *miscPmcUbusActivePortControlReg = (unsigned int*)0xb3e80040;

   /* Enable 200Mhz Clock via BPCM. All FCW calculations are based on this 200Mhz Clock */
   WriteZoneRegister(PMB_ADDR_CHIP_CLKRST, 0, BPCMZoneRegOffset(config2), 0);

   udelay(1000);

   /* RESET APM via BPCM ( Block Power Control Module ) */
   ResetDevice(PMB_ADDR_APM);
   ResetZone(PMB_ADDR_APM, APM_Zone_Main);
   ResetZone(PMB_ADDR_APM, APM_Zone_Audio);

   /* Register APM address space/Ubus port */
   *miscPmcUbusActivePortControlReg |= (1<<13);

   /* Assert APM SoftResets via BPCM */
   ReadBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), &sr_control.Reg32);
   sr_control.Bits.sr |= ( BPCM_APM_SRESET_AUDIO_N | BPCM_APM_SRESET_200_N  |
                    BPCM_APM_SRESET_HVGA_N  | BPCM_APM_SRESET_HVGB_N |
                    BPCM_APM_SRESET_BMU_N  ) ;
   WriteBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), sr_control.Reg32);

   udelay(1000);

   /* De-Assert APM SoftResets via BPCM */
   ReadBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), &sr_control.Reg32);
   sr_control.Bits.sr &= ~( BPCM_APM_SRESET_AUDIO_N | BPCM_APM_SRESET_200_N  |
                     BPCM_APM_SRESET_HVGA_N  | BPCM_APM_SRESET_HVGB_N |
                     BPCM_APM_SRESET_BMU_N  ) ;
   WriteBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), sr_control.Reg32);

   udelay(1000);
}

void pmc_apm_power_down(void)
{
   unsigned int * miscPmcUbusActivePortControlReg = (unsigned int*)0xb3e80040;

   /* de-register APM register space/ubus port */
   *miscPmcUbusActivePortControlReg &= ~(1<<13);

   /* Power off zones */
   PowerOffZone(PMB_ADDR_APM, APM_Zone_Audio);
   //PowerOffZone(PMB_ADDR_APM, APM_Zone_Main );
}

void apm_pinmux()
{
   /* Add PinMux for HVG_DRIVER_A/B pins (TODO:Remove Magic Numbers) */
   set_pinmux( 49, PINMUX_APM ); /* GPIO49 - HVG_DRIVER_A */
   set_pinmux( 50, PINMUX_APM ); /* GPIO50 - HVG_DRIVER_B */
}

void apm_pinunmux()
{
   /* Set for HVG_DRIVER_A/B pins GPIO and drive a logic 0 */
   set_pinmux( 49, PINMUX_GPIO ); /* GPIO49 - HVG_DRIVER_A */
   set_pinmux( 50, PINMUX_GPIO ); /* GPIO50 - HVG_DRIVER_B */
   kerSysSetGpio( 49, kGpioInactive );
   kerSysSetGpio( 50, kGpioInactive );
}

void pmc_pcm_power_up()
{
   BPCM_SR_CONTROL sr_control;

   /* RESET PCM via BPCM ( Block Power Control Module ) */
   ResetZone(PMB_ADDR_APM, APM_Zone_PCM);

   /* Assert PCM SoftResets via BPCM */
   ReadBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), &sr_control.Reg32);
   sr_control.Bits.sr |= ( BPCM_APM_SRESET_PCM_N );
   WriteBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), sr_control.Reg32);

   /* Sleep to ensure full soft reset */
   msleep(100);

   /* De-assert PCM SoftResets via BPCM */
   ReadBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), &sr_control.Reg32);
   sr_control.Bits.sr &= ~( BPCM_APM_SRESET_PCM_N );
   WriteBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), sr_control.Reg32);

    /* Sleep to ensure full soft reset */
   msleep(100);
}

void pmc_pcm_power_down()
{
   BPCM_SR_CONTROL sr_control;

   /* Assert PCM SoftResets via BPCM */
   ReadBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), &sr_control.Reg32);
   sr_control.Bits.sr |= ( BPCM_APM_SRESET_PCM_N );
   WriteBPCMRegister(PMB_ADDR_APM, BPCMRegOffset(sr_control), sr_control.Reg32);

   /* Sleep to ensure full soft reset */
   msleep(100);

   PowerOffZone(PMB_ADDR_APM, APM_Zone_PCM);
}

void pcm_pinmux()
{
   /* Add PinMux for PCM pins (TODO:Remove Magic Numbers) */
   set_pinmux( 0, PINMUX_PCM ); /* GPIO0 - PCM_SDIN */
   set_pinmux( 1, PINMUX_PCM ); /* GPIO1 - PCM_SDOUT */
   set_pinmux( 2, PINMUX_PCM ); /* GPIO2 - PCM_CLK */
   set_pinmux( 3, PINMUX_PCM ); /* GPIO3 - PCM_FS */
}


int apm_cfg_pll_div()
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
         APM->dpll_div = (31 << DPLL_REF_DIV_SHIFT) | 8191;
         DHLOG_INFO("%s: DPLL programmed for GPON refclk @ 256Khz\n",
                     __func__);
         return 0;

      case rdpa_wan_epon:
         /* Local clk is generated via DPLL NCO @ 65.536Mhz
          * Ref clk from EPON Serdes is @ 40Khz
          * Phase comparator compares both clocks @ 8Khz
          * 8Khz = 65.536Mhz / (8191+1) = 40Khz / (4+1)
          * local_div = 8191, ref_div = 4 */
         APM->dpll_div = (4 << DPLL_REF_DIV_SHIFT) | 8191;
         DHLOG_INFO("%s: DPLL programmed for EPON refclk @ 40Khz\n",
                     __func__);
         return 0;

      default:
         DHLOG_INFO("%s: Unknown WAN mode, using standalone\n",
                     __func__);
         break;
   }
#endif
   return 1;
}

