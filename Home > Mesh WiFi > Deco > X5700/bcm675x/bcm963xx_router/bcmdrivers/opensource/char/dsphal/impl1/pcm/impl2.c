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

#include <pmc/pmc_pcm.h>

#include <dsphal.h>
#include <dsphal_chip.h>
#include <dsphal_pcm.h>
#include <dsphal_apm.h>

/* Maximum number of 10ms iterations to wait for DPLL lock */
#define DPLL_LOCK_MAX_WAIT    500
#define DPLL_LOCK_RETRY_CNT   2

/****************************************************************************
* Local function declaration
****************************************************************************/
static unsigned long pcm_nco_mux_cfg(void);
static void pcm_nco_init(void);
#ifdef PCM_DPLL_SUPPORT
static void pcm_pll_cfg(void);
static void pcm_dpll_wait_lock(void);
#endif /* PCM_DPLL_SUPPORT */
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
   pmc_pcm_power_up();
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
   pmc_pcm_power_down();
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

   /* Setup the PCM clock NCO */
   pcm_nco_init();

   /* Configure the PCM registers */
   pcm_reg_cfg();

   return 0;
}


/*****************************************************************************
*  FUNCTION:   pcm_nco_mux_cfg
*
*  PURPOSE:    Setup the NCO mux, depending on the configured PLL requirements
*
*  PARAMETERS: none
*
*  RETURNS:    nco mux source
*
*****************************************************************************/
static unsigned long pcm_nco_mux_cfg()
{
   unsigned long nco_mux_cfg = 0;

#ifdef PCM_NTR_DSL
# ifdef BRCM_NTR_SUPPORT
   /* set the DPLL refclk source to VDSL_NTR[0] clock */
   MISC->miscAdsl_clock_sample &= PCM_NTR_CTRL_CLEAR;
   MISC->miscAdsl_clock_sample |=
      (PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0 << PCM_NTR_IN_CTRL_SHIFT);
   DHLOG_INFO("%s: syncing PLL to VDSL_NTR[0] output\n", __func__);

   /* Set PCM NCO FCW source as DPLL */
   nco_mux_cfg = P_PCM_NCO_MUX_CNTL_DPLL;
# else /* BRCM_NTR_SUPPORT */
   if( vp.numDectLines )
   {
      /* set the DPLL refclk source to DECT clock */
      MISC->miscAdsl_clock_sample &= PCM_NTR_CTRL_CLEAR;
      MISC->miscAdsl_clock_sample |=
         (PCM_NTR_IN_CTRL_SEL_DECT_NTR << PCM_NTR_IN_CTRL_SHIFT);
      DHLOG_INFO("%s: syncing PLL to DECT_NTR output\n", __func__);

      /* Set PCM NCO FCW source as DPLL */
      nco_mux_cfg = P_PCM_NCO_MUX_CNTL_DPLL;
   }
   else
   {
      /* Set PCM NCO FCW source as MISC */
      nco_mux_cfg = P_PCM_NCO_MUX_CNTL_MISC;

      DHLOG_INFO("%s: using MISC for NCO FCW\n", __func__);
   }
# endif /* !BRCM_NTR_SUPPORT */
#endif /* PCM_NTR_DSL */

#if (defined(PCM_NTR_PON) || defined(PCM_NTR_RTR))
# ifdef BRCM_NTR_SUPPORT
   nco_mux_cfg = P_PCM_NCO_MUX_CNTL_DPLL;
# else
   nco_mux_cfg = P_PCM_NCO_MUX_CNTL_MISC;
# endif
#endif /* PCM_NTR_PON */

   return nco_mux_cfg;
}

/*****************************************************************************
*  FUNCTION:   pcm_nco_init
*
*  PURPOSE:    Initialize the PCM NCO
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
static void pcm_nco_init()
{
   unsigned long nco_mux_cfg = pcm_nco_mux_cfg();

#ifdef PCM_DPLL_SUPPORT
   /* initialize the PCM DPLL */
   pcm_pll_cfg();
#endif /* PCM_DPLL_SUPPORT */

   /* Load MISC register with target FCW from DPLL, and set NCO and enable bits
    * depending on the clock type */
   PCM->reg_pcm_clk_cntl_0 = P_NCO_FCW_MISC;

   if(vp.flags & BP_FLAG_ISI_SUPPORT)
   {
      DHLOG_NOTICE("%s: PCM clock in ISI mode\n", __func__);
      PCM->reg_pcm_clk_cntl_1 = PCM_CLK_CNTL_1_ISI;
      PCM->pcm_msif_intf      = PCM_MSIF_ENABLE;
   }
   else if(vp.flags & BP_FLAG_ZSI_SUPPORT)
   {
      DHLOG_NOTICE("%s: PCM clock in ZSI mode\n", __func__);
      PCM->reg_pcm_clk_cntl_1 = PCM_CLK_CNTL_1_ZSI;
      PCM->pcm_zds_intf       = PCM_ZDS_ENABLE;
   }
   else
   {
      DHLOG_NOTICE("%s: PCM clock in normal mode\n", __func__);
      PCM->reg_pcm_clk_cntl_1 = PCM_CLK_CNTL_1_PCM;
   }

   /* Soft-init PCM NCO */
   PCM->reg_pcm_clk_cntl_2 = (P_PCM_NCO_SHIFT & PCM_NCO_SHIFT)
         | ((nco_mux_cfg << PCM_NCO_MUX_SHIFT) & PCM_NCO_MUX_CNTL)
         |  (PCM_NCO_SOFT_INIT);
   PCM->reg_pcm_clk_cntl_2 = (P_PCM_NCO_SHIFT & PCM_NCO_SHIFT)
         | ((nco_mux_cfg << PCM_NCO_MUX_SHIFT) & PCM_NCO_MUX_CNTL);

   if( nco_mux_cfg == P_PCM_NCO_MUX_CNTL_MISC )
   {
      /* Load the MISC FCW */
      PCM->reg_pcm_clk_cntl_2 = (P_PCM_NCO_SHIFT & PCM_NCO_SHIFT)
         | ((nco_mux_cfg << PCM_NCO_MUX_SHIFT) & PCM_NCO_MUX_CNTL)
         |  (PCM_NCO_LOAD_MISC);
      PCM->reg_pcm_clk_cntl_2 = (P_PCM_NCO_SHIFT & PCM_NCO_SHIFT)
         | ((nco_mux_cfg << PCM_NCO_MUX_SHIFT) & PCM_NCO_MUX_CNTL);

      DHLOG_DEBUG("%s: loading MISC FCW to PCM NCO: 0x%08x\n",
             __func__, (unsigned int)PCM->reg_pcm_clk_cntl_0 );
   }
}

#ifdef PCM_DPLL_SUPPORT
/*****************************************************************************
*  FUNCTION:   pcm_pll_cfg
*
*  PURPOSE:    Configure and start the PCM DPLL, if required
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
static void pcm_pll_cfg()
{
#if (defined(PCM_NTR_DSL) || defined(PCM_NTR_PON) || defined(PCM_NTR_RTR))
# ifndef BRCM_NTR_SUPPORT
   /* If we do not have NTR support and DECT is not configured, no need to
    * setup the PLL. */
   if(!vp.numDectLines)
      return;
# endif /* BRCM_NTR_SUPPORT */

#ifdef PCM_NTR_DSL
   DHLOG_DEBUG("%s: miscAdsl_clock_sample 0x%08x @ 0x%p\n",
          __func__, (unsigned int)MISC->miscAdsl_clock_sample,
          &(MISC->miscAdsl_clock_sample));
#endif
   /* suspend the operation of the PLL first */
   DPLL->dpll_control |= DPLL_SOFT_INIT;
   DPLL->dpll_control &= ~(DPLL_FORCE_ACQ | DPLL_OPEN_LOOP | DPLL_CONST_K);
   DPLL->dpll_control &= DPLL_CTRL_K0_CLEAR;
   DPLL->dpll_control |= DPLL_PHASE_THRESH << DPLL_PHS_THSHLD_SHIFT;
   DPLL->dpll_control |= DPLL_K0;
   DPLL->dpll_nom_freq = DPLL_NOM_FREQ;
   msleep(1);
   DPLL->dpll_control &= ~DPLL_SOFT_INIT;  
   msleep(1);

   /* Config the DPLL divider */
   pcm_cfg_dpll_div();

   /* Force loop aquisition */
   DPLL->dpll_control |=  DPLL_FORCE_ACQ;
   DPLL->dpll_control &= ~DPLL_FORCE_ACQ;

   /* Wait for the DPLL to lock */
   pcm_dpll_wait_lock();
#endif /* PCM_NTR_DSL */
}

/*****************************************************************************
*  FUNCTION:   pcm_cfg_dpll_div
*
*  PURPOSE:    Configure the PCM DPLL divider
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
void __weak pcm_cfg_dpll_div(void)
{
   /* Setup the DPLL divider according to the following:
    * 8KHz reference clock
    * ====================
    *    ref_div   = 1    => 8Khz VDSL_NTR refclk   / 1    = 8Khz clock to comparator
    *    local_div = 8192 => 65.536Mhz local clock  / 8192 = 8Khz clock to comparator

    * 16KHz reference clock
    * =====================
    *    ref_div   = 2    => 16Khz VDSL_NTR refclk  / 2    = 8Khz clock to comparator
    *    local_div = 8192 => 65.536Mhz local clock  / 8192 = 8Khz clock to comparator

    * 256KHz reference clock
    * ======================
    *    ref_div   = 32   => 256Khz VDSL_NTR refclk / 32   = 8Khz clock to comparator
    *    local_div = 8192 => 65.536Mhz local clock  / 8192 = 8Khz clock to comparator
    *
    * DECT reference clock
    * ====================
    *    ref_div   = 81   => 10.368Mhz DECT refclk  / 81   = 128Khz clock to comparator
    *    local_div = 512  => 65.536Mhz local clock  / 512  = 128Khz clock to comparator
    *
    * Note that all values should be subtracted by 1 before being set in the register
    */
#if defined(BRCM_NTR_REF_CLK_8KHZ)
   DPLL->dpll_div = (0  << DPLL_REF_DIV_SHIFT) | 8191;
#elif defined(BRCM_NTR_REF_CLK_16KHZ)
   DPLL->dpll_div = (1  << DPLL_REF_DIV_SHIFT) | 8191;
#elif defined(BRCM_NTR_REF_CLK_256KHZ)
   DPLL->dpll_div = (31 << DPLL_REF_DIV_SHIFT) | 8191;
#else
   /* implicitly in the DECT case */
   DPLL->dpll_div = (80 << DPLL_REF_DIV_SHIFT) | 511;
#endif /* BRCM_NTR_REF_CLK_xKHZ */
}

/*****************************************************************************
*  FUNCTION:   pcm_dpll_wait_lock
*
*  PURPOSE:    Wait for the DPLL to lock, if configured
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
static void pcm_dpll_wait_lock(void)
{
#ifdef BRCM_VOICE_DPLL_LOCK_WAIT
   volatile unsigned int temp = 0;
   unsigned int i = 0, retry = 0;

   /* Wait for the DPLL_IN_SYNC and DPLL_ACQ_FREQ_VALID bits to be set */
   temp = DPLL->dpll_status;
   while( 1 )
   {
      temp = DPLL->dpll_status;
      i++;

      if ((temp & DPLL_IN_SYNC) && (temp & DPLL_ACQ_FREQ_VALID))
      {
         DHLOG_DEBUG("%s: DPLL locked, iteration = %u, "
               "dpll_status = 0x%08x, dpll_acq_freq = 0x%08x\n", __func__,
               i, temp, (unsigned int)DPLL->dpll_acq_freq);
         return;
      }
      else if ( i == DPLL_LOCK_MAX_WAIT )
      {
         DHLOG_ERR("%s: DPLL failed to lock, dpll_status = 0x%08x, "
               "retry count %d\n", __func__, temp, retry);
         retry++;
         i = 0;
         if(retry >= DPLL_LOCK_RETRY_CNT)
            break;

      }
      msleep(10);
   }
#else
   DHLOG_DEBUG("%s: DPLL lock wait skipped, dpll_status = 0x%08x",
          __func__, (unsigned int)DPLL->dpll_status);
#endif /* BRCM_VOICE_DPLL_LOCK_WAIT */
}
#endif /* PCM_DPLL_SUPPORT */

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
static void pcm_reg_cfg(void)
{
   /* PCM Control */
   PCM->pcm_ctrl = PCM_AP_SEL
                 | PCM_BITS_PER_FRAME_256
                 | (0 << PCM_SLAVE_SEL_SHIFT)
                 | (1 << PCM_CLOCK_INV_SHIFT)
                 | (0 << PCM_FS_INVERT_SHIFT)
                 | (0 << PCM_FS_FREQ_16_8_SHIFT)
                 | (0 << PCM_FS_LONG_SHIFT)
                 | (1 << PCM_FS_TRIG_SHIFT)
                 | (1 << PCM_DATA_OFF_SHIFT)
                 | (1 << PCM_DATA_16_8_SHIFT)
                 | (0 << PCM_LSB_FIRST_SHIFT)
                 | (0 << PCM_LOOPBACK_SHIFT)
                 | (0 << PCM_EXTCLK_SEL_SHIFT);

   /* Set pcm clk to 2.048Mhz */
   if(vp.flags & BP_FLAG_ISI_SUPPORT && (PCM->pcm_msif_intf & PCM_MSIF_ENABLE))
      PCM->pcm_ctrl |= PCM_CLOCK_SEL_ISI << PCM_CLOCK_SEL_SHIFT;
   else
      PCM->pcm_ctrl |= PCM_CLOCK_SEL_PCM << PCM_CLOCK_SEL_SHIFT;

#ifdef APM_SUPPORT
   /* Make sure the APM interrupts are cleared and disabled */
   APM->apm_dev_irq_pend |= DMA_PCM_RX | DMA_PCM_TX;
   APM->apm_dev_irq_mask &= ~( DMA_PCM_RX | DMA_PCM_TX );
#endif /* APM_SUPPORT */

   /* Make sure the PCM interrupts are cleared and disabled */
   PCM->pcm_int_mask = 0;
}
