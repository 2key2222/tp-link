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

#include <linux/delay.h>

#include <dsphal_pcm.h>


/****************************************************************************
* Local function declaration
****************************************************************************/
static void pcm_pll_cfg(void);
static void pcm_reg_cfg(void);


/****************************************************************************
* Functions
****************************************************************************/

/*****************************************************************************
*  FUNCTION:   pcm_power_up
*
*  PURPOSE:    Handle powering up of the PCM block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_power_up(void)
{
   /* Enable clock to pcm block */
   PERF->blkEnables |= PCM_CLK_EN;

   /* Soft reset the PCM block */
   PERF->softResetB &= ~SOFT_RST_PCM;

   msleep(50);

   /* Clear the reset of the PCM block */
   PERF->softResetB |= SOFT_RST_PCM;

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_power_down
*
*  PURPOSE:    Handle powering down of the PCM block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_power_down(void)
{
   /* Power off the PCM block */
   PERF->blkEnables &= ~PCM_CLK_EN;

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_clk_init
*
*  PURPOSE:    Configure the PCM clock
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int pcm_clk_init( void )
{
   DHLOG_INFO("%s: starting PCM clock\n", __func__);

   /* Setup the PCM clock PLL */
   pcm_pll_cfg();

   /* Configure the PCM register */
   pcm_reg_cfg();

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_pll_cfg
*
*  PURPOSE:    Configure and start the PCM DPLL
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
static void pcm_pll_cfg()
{
   /* Power up PLL */
   PCM->pcm_pll_ctrl1 &= ~(PCM_PLL_PWRDN | PCM_PLL_PWRDN_CH1 | PCM_PLL_REFCMP_PWRDN );

   /* Setup initial parameters */
   PCM->pcm_pll_ctrl1    = PCM_PLL_CTRL_1;
   PCM->pcm_pll_ctrl2    = PCM_PLL_CTRL_2;
   PCM->pcm_pll_ctrl3    = PCM_PLL_CTRL_3;
   PCM->pcm_pll_ctrl4    = PCM_PLL_CTRL_4;
#ifdef PCM_PLL_CH2_SUPPORT
   PCM->pcm_pll_ch2_ctrl = PCM_PLL_CH2_CTRL;
#endif

   if( vp.numDectLines )
   {
      /* If DECT is enabled, set the PCM clock based on the DECT clock */
      DHLOG_NOTICE("%s: PCM clock syncing to DECT clock\n", __func__);
      PCM->pcm_pll_ctrl1    = PCM_PLL_CTRL_1_DECT;
      PCM->pcm_pll_ctrl2    = PCM_PLL_CTRL_2_DECT;
      PCM->pcm_pll_ctrl4   |= PCM_PLL_CTRL_4_DECT;
#ifdef PCM_PLL_CH2_SUPPORT
      PCM->pcm_pll_ch2_ctrl = PCM_PLL_CH2_CTRL_DECT;
#endif
   }
#ifdef PCM_ISI_SUPPORT
   else if(vp.flags & BP_FLAG_ISI_SUPPORT)
   {
      DHLOG_NOTICE("%s: PCM clock in ISI mode\n", __func__);
      PCM->pcm_pll_ctrl1    = PCM_PLL_CTRL_1_ISI;
      PCM->pcm_pll_ctrl2    = PCM_PLL_CTRL_2_ISI;
      PCM->pcm_pll_ctrl3    = PCM_PLL_CTRL_3_ISI;
#ifdef PCM_PLL_CH2_SUPPORT
      PCM->pcm_pll_ch2_ctrl = PCM_PLL_CH2_CTRL_ISI;
#endif
   }
#endif /* PCM_ISI_SUPPORT */
#ifdef PCM_ZSI_SUPPORT
   else if(vp.flags & BP_FLAG_ZSI_SUPPORT)
   {
      DHLOG_NOTICE("%s: PCM clock in ZSI mode\n", __func__);
      PERF->blkEnables   |= (HS_SPI_CLK_EN | PCM_CLK_EN);
      PERF->softResetB   |= (SOFT_RST_PCM | SOFT_RST_SPI);

      MISC->miscIddqCtrl &= ~MISC_IDDQ_CTRL_PCM;

#ifdef CONFIG_BCM963268
      PCM->pcm_pll_ch2_ctrl &= ~(0x1 << 16); /* BCM63268_C0 onwards */
#endif
   }
#endif /* PCM_ZSI_SUPPORT */
   else
   {
      DHLOG_NOTICE("%s: PCM clock in normal mode\n", __func__);
   }

#if defined(PCM_PLL_CH3_SUPPORT) && defined(BRCM_NTR_SUPPORT)
   /* If NTR is enabled, always use the NTR settings */
   PCM->pcm_pll_ch3_ctrl = PCM_PLL_CH3_CTRL;
#endif

#if defined(PCM_ISI_SUPPORT) || defined(PCM_ZSI_SUPPORT)
   PCM->pcm_msif_intf = 
#ifdef PCM_ISI_SUPPORT
      (vp.flags & BP_FLAG_ISI_SUPPORT) ? PCM_MSIF_ENABLE :
#endif
#ifdef PCM_ZSI_SUPPORT
      (vp.flags & BP_FLAG_ZSI_SUPPORT) ? PCM_ZDS_ENABLE :
#endif
      PCM_MSIF_DISABLE;
#endif /* defined(PCM_ISI_SUPPORT) || defined(PCM_ZSI_SUPPORT) */

   /* Remove Analog Reset */
   PCM->pcm_pll_ctrl1 &= ~PCM_PLL_ARESET;

   /* Clear clk 16 reset */
   PCM->pcm_pll_ctrl1 &= ~PCM_CLK16_RESET;

   msleep(10);

   if((PCM->pcm_pll_stat & PCM_PLL_LOCK) != PCM_PLL_LOCK)
      DHLOG_WARNING("%s: PLL didn't lock to programmed output frequency "
             "(0x%08X)", __func__, (unsigned int)PCM->pcm_pll_stat);

   /* Remove Digital Reset */
   PCM->pcm_pll_ctrl1 &= ~PCM_PLL_DRESET;

   DHLOG_DEBUG("%s: PLL init completed. PLL registers set to:\n", __func__);
   DHLOG_DEBUG("   pcm_pll_ctrl1    (0x%08x)\n", (unsigned int)PCM->pcm_pll_ctrl1);
   DHLOG_DEBUG("   pcm_pll_ctrl2    (0x%08x)\n", (unsigned int)PCM->pcm_pll_ctrl2);
   DHLOG_DEBUG("   pcm_pll_ctrl3    (0x%08x)\n", (unsigned int)PCM->pcm_pll_ctrl3);
   DHLOG_DEBUG("   pcm_pll_ctrl4    (0x%08x)\n", (unsigned int)PCM->pcm_pll_ctrl4);
#if defined(PCM_ISI_SUPPORT) || defined(PCM_ZSI_SUPPORT)
   DHLOG_DEBUG("   pcm_msif_intf    (0x%08x)\n", (unsigned int)PCM->pcm_msif_intf);
#endif
#ifdef PCM_PLL_CH2_SUPPORT
   DHLOG_DEBUG("   pcm_pll_ch2_ctrl (0x%08x)\n", (unsigned int)PCM->pcm_pll_ch2_ctrl);
#endif
#ifdef PCM_PLL_CH3_SUPPORT
   DHLOG_DEBUG("   pcm_pll_ch3_ctrl (0x%08x)\n", (unsigned int)PCM->pcm_pll_ch3_ctrl);
#endif
}


/*****************************************************************************
*  FUNCTION:   pcm_reg_cfg
*
*  PURPOSE:    Configure and enable PCM registers
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
static void pcm_reg_cfg()
{
   PCM->pcm_ctrl = PCM_BITS_PER_FRAME_256
                 | PCM_FS_TRIG
                 | PCM_CLOCK_INV
                 | PCM_DATA_OFF
#ifdef BRCM_NTR_SUPPORT
                 | PCM_NTR_ENABLE
#endif /* NTR_SUPPORT */
                 | PCM_DATA_16_8;

#if defined(PCM_ISI_SUPPORT) || defined(PCM_ZSI_SUPPORT)
   if(vp.flags & BP_FLAG_ISI_SUPPORT && PCM->pcm_msif_intf & PCM_MSIF_ENABLE)
      PCM->pcm_ctrl |= PCM_CLOCK_SEL_ISI << PCM_CLOCK_SEL_SHIFT;
   else
#endif /* defined(PCM_ISI_SUPPORT) || defined(PCM_ZSI_SUPPORT) */
      PCM->pcm_ctrl |= PCM_CLOCK_SEL_PCM << PCM_CLOCK_SEL_SHIFT;

   PCM->pcm_chan_ctrl = 0;

   /* Clear overflow/underflow PCM interrupts at the PCM level */
   PCM->pcm_int_pending |=  PCM_TX_UNDERFLOW | PCM_RX_OVERFLOW;

   /* Disable PCM over/underflow interrupts, DSP utilizes PCM DMA interrupts only */
   PCM->pcm_int_mask &=  ~(PCM_TX_UNDERFLOW | PCM_RX_OVERFLOW);
}
