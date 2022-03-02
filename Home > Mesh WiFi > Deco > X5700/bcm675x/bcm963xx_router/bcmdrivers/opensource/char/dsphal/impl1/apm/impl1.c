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

#include <pmc/pmc_apm.h>

#include <dsphal.h>
#include <dsphal_chip.h>
#include <dsphal_apm.h>


/****************************************************************************
* Typedefs and Constants
****************************************************************************/
#define DPLL_LOCK_MAX_WAIT    500
#define DPLL_LOCK_RETRY_CNT   2

/* Pointer to APM ACP channel config registers (from <chip>_map.h) */
struct apm_acp_ch
{
   volatile uint32_t *test_config;
   volatile uint32_t *eq_config;
   volatile uint32_t *hybal_config;
   volatile uint32_t *int_config_1;
   volatile uint32_t *int_config_2;
   volatile uint32_t *pm_config_1;
   volatile uint32_t *pm_config_2;
   volatile uint32_t *pm_config_3;
   volatile uint32_t *cic_config;
   volatile uint32_t *asrc_dec_config;
   volatile uint32_t *fcw_config_1;
   volatile uint32_t *fcw_config_2;
   volatile uint32_t *digmod_config;
};

struct apm_chan_cfg_device
{
   uint32_t dma_int_enable_bits;
   uint32_t dma_enable_bits;
};

/****************************************************************************
* Local variables
****************************************************************************/
#ifdef APM_DMA_SUPPORT
static struct apm_acp_ch acp_cfg[] = {
   /* Channel A */
   {
      .test_config     = (volatile uint32_t *)&APM->reg_cha_test_config,
      .eq_config       = (volatile uint32_t *)&APM->reg_cha_eq_config,
      .hybal_config    = (volatile uint32_t *)&APM->reg_cha_hybal_config,
      .int_config_1    = (volatile uint32_t *)&APM->reg_cha_int_config_1,
      .int_config_2    = (volatile uint32_t *)&APM->reg_cha_int_config_2,
      .pm_config_1     = (volatile uint32_t *)&APM->reg_cha_pm_config_1,
      .pm_config_2     = (volatile uint32_t *)&APM->reg_cha_pm_config_2,
      .pm_config_3     = (volatile uint32_t *)&APM->reg_cha_pm_config_3,
      .cic_config      = (volatile uint32_t *)&APM->reg_cha_cic_config,
      .asrc_dec_config = (volatile uint32_t *)&APM->reg_cha_asrc_dec_config,
      .fcw_config_1    = (volatile uint32_t *)&APM->reg_cha_fcw_config_1,
      .fcw_config_2    = (volatile uint32_t *)&APM->reg_cha_fcw_config_2,
      .digmod_config   = (volatile uint32_t *)&APM->reg_cha_digmod_config,
   },

   /* Channel B */
   {
      .test_config     = (volatile uint32_t *)&APM->reg_chb_test_config,
      .eq_config       = (volatile uint32_t *)&APM->reg_chb_eq_config,
      .hybal_config    = (volatile uint32_t *)&APM->reg_chb_hybal_config,
      .int_config_1    = (volatile uint32_t *)&APM->reg_chb_int_config_1,
      .int_config_2    = (volatile uint32_t *)&APM->reg_chb_int_config_2,
      .pm_config_1     = (volatile uint32_t *)&APM->reg_chb_pm_config_1,
      .pm_config_2     = (volatile uint32_t *)&APM->reg_chb_pm_config_2,
      .pm_config_3     = (volatile uint32_t *)&APM->reg_chb_pm_config_3,
      .cic_config      = (volatile uint32_t *)&APM->reg_chb_cic_config,
      .asrc_dec_config = (volatile uint32_t *)&APM->reg_chb_asrc_dec_config,
      .fcw_config_1    = (volatile uint32_t *)&APM->reg_chb_fcw_config_1,
      .fcw_config_2    = (volatile uint32_t *)&APM->reg_chb_fcw_config_2,
      .digmod_config   = (volatile uint32_t *)&APM->reg_chb_digmod_config,
   }
};

static struct apm_chan_cfg_device apm_dev_cfg[] = {
   /* Channel A */
   {
      .dma_int_enable_bits = DMA_A_RX | DMA_RX_OVERFLOW_A,
      .dma_enable_bits     = RX_DMA_ENABLE_A,
   },
   {
      .dma_int_enable_bits = DMA_A_TX | DMA_TX_UNDERFLOW_A,
      .dma_enable_bits     = TX_DMA_ENABLE_A,
   },
   /* Channel B */
   {
      .dma_int_enable_bits = DMA_B_RX | DMA_RX_OVERFLOW_B,
      .dma_enable_bits     = RX_DMA_ENABLE_B,
   },
   {
      .dma_int_enable_bits = DMA_B_TX | DMA_TX_UNDERFLOW_B,
      .dma_enable_bits     = TX_DMA_ENABLE_B,
   },
};
#endif /* APM_DMA_SUPPORT */

/****************************************************************************
* Local function declaration
****************************************************************************/
#ifdef APM_DMA_SUPPORT
#ifdef APM_DPLL_SUPPORT
static void apm_pll_cfg(void);
static void apm_dpll_wait_lock(void);
#endif /* APM_DPLL_SUPPORT */
static void apm_reg_cfg(enum dh_sample_rate rate);
static void apm_acp_chan_cfg(struct apm_acp_ch *chan,
                             enum dh_sample_rate rate);
#endif /* APM_DMA_SUPPORT */


/****************************************************************************
* Externed functions
****************************************************************************/
extern int apm_cfg_pll_div(void);
extern void pmc_apm_power_up(void);
extern void pmc_apm_power_down(void);

/****************************************************************************
* Functions
****************************************************************************/
void apm_power_up(void)
{
   pmc_apm_power_up();
}

void apm_power_down(void)
{
   pmc_apm_power_down();
}

#ifdef APM_DMA_SUPPORT
/*****************************************************************************
*  FUNCTION:   apm_dma_init
*
*  PURPOSE:    Initialize APM
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int apm_dma_init(void)
{
   /* apm_dma_init does the same thing as apm_dma_deinit */
   return apm_dma_deinit();
}


/*****************************************************************************
*  FUNCTION:   apm_dma_deinit
*
*  PURPOSE:    Stop APM
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int apm_dma_deinit(void)
{
   /* Ensure all device interrupts are cleared and masked out to start */
   APM->apm_dev_irq_mask &= ~(apm_dev_cfg[0].dma_int_enable_bits |
                              apm_dev_cfg[1].dma_int_enable_bits |
                              apm_dev_cfg[2].dma_int_enable_bits |
                              apm_dev_cfg[3].dma_int_enable_bits);
   APM->apm_dev_irq_pend |= apm_dev_cfg[0].dma_int_enable_bits |
                            apm_dev_cfg[1].dma_int_enable_bits |
                            apm_dev_cfg[2].dma_int_enable_bits |
                            apm_dev_cfg[3].dma_int_enable_bits;

   /* Place the channels under soft reset */
   APM->reg_cha_eq_config |= SOFT_INIT;
   APM->reg_chb_eq_config |= SOFT_INIT;

   return 0;
}


/*****************************************************************************
*  FUNCTION:   apm_dma_start
*
*  PURPOSE:    Enable APM DMA interrupts
*
*  PARAMETERS: priv - APM private data
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int apm_dma_start(struct apm_chan_priv *priv)
{
   /* Clear interrupts and enable masks */
   APM->apm_dev_irq_pend |= apm_dev_cfg[priv->rx_dma->chan_id].dma_int_enable_bits |
                            apm_dev_cfg[priv->tx_dma->chan_id].dma_int_enable_bits;
   APM->apm_dev_irq_mask |= apm_dev_cfg[priv->tx_dma->chan_id].dma_int_enable_bits |
                            apm_dev_cfg[priv->rx_dma->chan_id].dma_int_enable_bits;

   /* Enable TX first, then RX */
   APM->apm_dev_control |= apm_dev_cfg[priv->tx_dma->chan_id].dma_enable_bits;
   *acp_cfg[priv->apm_chan_id].eq_config &= ~SOFT_INIT;
   APM->apm_dev_control |= apm_dev_cfg[priv->rx_dma->chan_id].dma_enable_bits;

   return 0;
}


/*****************************************************************************
*  FUNCTION:   apm_dma_stop
*
*  PURPOSE:    Disable APM DMA interrupts
*
*  PARAMETERS: priv - APM private data
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int apm_dma_stop(struct apm_chan_priv *priv)
{
   /* Clear interrupts and enable masks */
   APM->apm_dev_irq_mask &= ~(apm_dev_cfg[priv->rx_dma->chan_id].dma_int_enable_bits |
                              apm_dev_cfg[priv->tx_dma->chan_id].dma_int_enable_bits);
   APM->apm_dev_irq_pend |= apm_dev_cfg[priv->rx_dma->chan_id].dma_int_enable_bits |
                            apm_dev_cfg[priv->tx_dma->chan_id].dma_int_enable_bits;
   *acp_cfg[priv->apm_chan_id].eq_config |= SOFT_INIT;
   return 0;
}


/*****************************************************************************
*  FUNCTION:   apm_clk_init
*
*  PURPOSE:    Configure the APM clock
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
int apm_clk_init(void)
{
   enum dh_sample_rate rate = DSPHAL_RATE_8KHZ;
   int i;

   /* Find the sampling rate of the first APM channel and assume all the other
    * channels have the same rate */
   for(i = 0; i < ARRAY_SIZE(chan_cfg); i++)
   {
      if(chan_cfg[i].interface != DSPHAL_INTF_APM)
         continue;
      rate = chan_cfg[i].rate;
      break;
   }

   DHLOG_INFO("%s: starting APM clock at sample rate %d KHz\n", __func__,
               (rate == DSPHAL_RATE_16KHZ ? 16 : 8));

#ifdef APM_DPLL_SUPPORT
   /* Setup the APM clock PLL */
   apm_pll_cfg();
#endif /* APM_DPLL_SUPPORT */

   /* Configure the APM registers */
   apm_reg_cfg(rate);

   return 0;
}


#ifdef APM_DPLL_SUPPORT
/*****************************************************************************
*  FUNCTION:   apm_pll_cfg
*
*  PURPOSE:    Configure and start the APM DPLL
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
static void apm_pll_cfg(void)
{
   int standalone;

   DPLL->dpll_control &= ~(DPLL_SOFT_INIT | DPLL_FORCE_ACQ | DPLL_OPEN_LOOP | DPLL_CONST_K);
   DPLL->dpll_control &= DPLL_CTRL_K0_CLEAR;
   DPLL->dpll_control |= DPLL_PHASE_THRESH << DPLL_PHS_THSHLD_SHIFT;
   DPLL->dpll_control |= DPLL_K0;
   DPLL->dpll_nom_freq = DPLL_NOM_FREQ;

   standalone = apm_cfg_pll_div();

   /* Force loop aquisition */
   DPLL->dpll_control |= DPLL_FORCE_ACQ;
   DPLL->dpll_control &= ~DPLL_FORCE_ACQ;

   /* Wait for the DPLL to lock */
   if(!standalone)
      apm_dpll_wait_lock();
   else
      DHLOG_DEBUG("%s: DPLL lock wait skipped; stand_alone mode\n", __func__);
}


/*****************************************************************************
*  FUNCTION:   apm_dpll_wait_lock
*
*  PURPOSE:    Wait for the DPLL to lock, if configured
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
static void apm_dpll_wait_lock(void)
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

      if (temp & (DPLL_IN_SYNC | DPLL_ACQ_FREQ_VALID))
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
      msleep(1);
   }
#else
   DHLOG_DEBUG("%s: DPLL lock wait skipped, dpll_status = 0x%08x",
               __func__, (unsigned int)DPLL->dpll_status);
#endif /* BRCM_VOICE_DPLL_LOCK_WAIT */
}
#endif /* APM_DPLL_SUPPORT */


/*****************************************************************************
*  FUNCTION:   apm_reg_cfg
*
*  PURPOSE:    Configure and enable APM registers
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
static void apm_reg_cfg(enum dh_sample_rate rate)
{
   /* Load frequency control word */
   if(rate == DSPHAL_RATE_8KHZ)
      APM->reg_fcw_config_1 = APM_FCW_INPUT    & FCW_REG;
   else
      APM->reg_fcw_config_1 = APM_FCW_INPUT_WB & FCW_REG;

   /* Toggle bits for loading FCW into channels A and B */
   APM->reg_fcw_config_2 = (0xF << FCW_LIMIT_SHIFT) & FCW_LIMIT;
   APM->reg_fcw_config_2 = ( 1 << LOAD_MISC_B_SHIFT )
                         | ( 1 << LOAD_MISC_A_SHIFT )
                         | ( 1 << LOAD_FCW_NOM_B_SHIFT )
                         | ( 1 << LOAD_FCW_NOM_A_SHIFT )
                         | ( 1 << LOAD_NTP_SHIFT )
                         | ((0xF << FCW_LIMIT_SHIFT) & FCW_LIMIT);
   APM->reg_fcw_config_2 = (0xF << FCW_LIMIT_SHIFT) & FCW_LIMIT;

   /* Load NTP control registers */
   APM->reg_ntp_config_1 = 0x176 & NTP_TIME_DVD;
   APM->reg_ntp_config_2 = 0 & NTP_READ_TIME;

   /* Configure ACP registers for channel A & B */
   apm_acp_chan_cfg(&acp_cfg[0], rate);
   apm_acp_chan_cfg(&acp_cfg[1], rate);

   /* Set soft init bit to start using new register values */
   APM->reg_ser_config  = (1 << SOFT_INIT_AP_SHIFT) & SOFT_INIT_AP;
   APM->reg_ser_config |= (0 << SER_TST_CLKS_SHIFT) & SER_TST_CLKS;
   APM->reg_ser_config |= (0 << AUD_SER_TST_FCW_MUX_CTRL_SHIFT) & AUD_SER_TST_FCW_MUX_CTRL;
   APM->reg_ser_config |= (0 << SER_MUX_SEL_SHIFT) & SER_MUX_SEL;

   /* Clear soft init bits */
   APM->reg_cha_eq_config &= ~SOFT_INIT;
   APM->reg_chb_eq_config &= ~SOFT_INIT;
   APM->reg_ser_config    &= ~SOFT_INIT_AP;

   /* Clear and disable all device interrupts */
   APM->apm_dev_irq_pend = apm_dev_cfg[0].dma_int_enable_bits |
                           apm_dev_cfg[1].dma_int_enable_bits |
                           apm_dev_cfg[2].dma_int_enable_bits |
                           apm_dev_cfg[3].dma_int_enable_bits;
   APM->apm_dev_irq_mask &= ~(apm_dev_cfg[0].dma_int_enable_bits |
                              apm_dev_cfg[1].dma_int_enable_bits |
                              apm_dev_cfg[2].dma_int_enable_bits |
                              apm_dev_cfg[3].dma_int_enable_bits);

   APM->reg_apm_irq_pend_1 = 0xffffffff;
   APM->reg_apm_irq_pend_2 = 0xffffffff;
   APM->reg_apm_irq_pend_3 = 0xffffffff;

   /* Initialize codec configuration registers */
   APM->reg_codec_config_0 = 0x00000000;
   APM->reg_codec_config_1 = 0x00000000;

   /* Determine shuffler settings */
   APM->reg_codec_config_2 = 0x00100000;
   APM->reg_codec_config_3 = 0x00010000;

   APM->reg_codec_config_4 = 0x00000000;

   /* Disable DC offset injection */
   APM->reg_codec_config_5 = 0x00000012;

   APM->reg_codec_config_6 = 0x00000000;
   APM->reg_codec_config_7 = 0x00000000;
   APM->reg_codec_config_8 = 0x00000000;
}


/*****************************************************************************
*  FUNCTION:   apm_acp_chan_cfg
*
*  PURPOSE:    Configure and enable ACP registers for a channel
*
*  PARAMETERS: none
*
*  RETURNS:    none
*
*****************************************************************************/
static void apm_acp_chan_cfg(struct apm_acp_ch *chan, enum dh_sample_rate rate)
{
   /* Clear the bits at RX_IN_MUX_CTRL to set input to RX data */
   *chan->test_config  = (0 << RX_IN_MUX_CTRL_SHIFT) & RX_IN_MUX_CTRL;
   *chan->test_config |= 0 << NETWORK_LPBK_SHIFT;
   *chan->test_config |= (0 << RX_98K_MUX_CTRL_SHIFT) & RX_98K_MUX_CTRL;
   *chan->test_config |= (1 << ADC_MUX_CTRL_SHIFT) & ADC_MUX_CTRL;
   *chan->test_config |= 0 << ADC_DAC_LPBK_SHIFT;
   *chan->test_config |= 0 << RX_TX_98K_LPBK_SHIFT;
   *chan->test_config |= 0 << SLEW_INSTANT_SHIFT;
   *chan->test_config |= 1 << ASRC_EN_SHIFT;

   /* Initializes state machines and registers */
   *chan->eq_config  = (0x4F << EQ_RX_NUM_TAPS_SHIFT) & EQ_RX_NUM_TAPS;
   *chan->eq_config |= (0x4F << EQ_TX_NUM_TAPS_SHIFT) & EQ_TX_NUM_TAPS;
   *chan->eq_config |= (0x6 << EQ_RX_SHFT_SHIFT) & EQ_RX_SHFT;
   *chan->eq_config |= (0xA << EQ_TX_SHFT_SHIFT) & EQ_TX_SHFT;
   *chan->eq_config |=  0 << EQ_RX_IMP_RESP_SHIFT;
   *chan->eq_config |=  0 << EQ_TX_IMP_RESP_SHIFT;
   *chan->eq_config |=  1 << EQ_TX_ENABLE_SHIFT;
   *chan->eq_config |=  1 << EQ_RX_ENABLE_SHIFT;
   *chan->eq_config |=  1 << SOFT_INIT_SHIFT;

   /* Disable Y-filter to turn off sidetone */
   *chan->hybal_config  = (0x05 << HISPD_HYBAL_SHFT_SHIFT) & HISPD_HYBAL_SHFT;
   *chan->hybal_config |= (0x10 << LOSPD_HYBAL_SHFT_SHIFT) & LOSPD_HYBAL_SHFT;
   *chan->hybal_config |=  1 << HISPD_HYBAL_EN_SHIFT;
   *chan->hybal_config |=  0 << LOSPD_HYBAL_EN_SHIFT;
   *chan->hybal_config |= (4 << HISPD_HYBAL_SMPL_OFFSET_SHIFT) & HISPD_HYBAL_SMPL_OFFSET;
   *chan->hybal_config |=  1 << YFLTR_EN_SHIFT;
   *chan->hybal_config |=  0 << HPF_EN_SHIFT;
   *chan->hybal_config |= (0 << LOSPD_HYBAL_SMPL_OFFSET_SHIFT) & LOSPD_HYBAL_SMPL_OFFSET;

   /* Set ASRC_INT_COEFF_SEL for low frequency (8/16 kHz sampling ) */
   *chan->int_config_1  = (0x13 << ASRC_INT_NUM_SECT_SHIFT) & ASRC_INT_NUM_SECT;
   *chan->int_config_1 |= (2 << ASRC_INT_HRNR_SHFT_SHIFT) & ASRC_INT_HRNR_SHFT;
   *chan->int_config_1 |=  0 << ASRC_INT_SYM_ASYM_SHIFT;
   *chan->int_config_1 |= (0 << ASRC_INT_COEFF_SEL_SHIFT) & ASRC_INT_COEFF_SEL;

   *chan->int_config_2  =  0x720A & ASRC_INT_SCALE;
   *chan->int_config_2 |= (3 << ASRC_INT_FIR_SHFT_SHIFT) & ASRC_INT_FIR_SHFT;
   *chan->int_config_2 |= (0 << ASRC_SLEW_SPEED_SHIFT) & ASRC_SLEW_SPEED;

   *chan->pm_config_1  = (0 << PM_ON_TIME_SHIFT) & PM_ON_TIME;
   *chan->pm_config_1 |= (0 << PM_OFF_TIME_SHIFT) & PM_OFF_TIME;
   *chan->pm_config_1 |=  0 << PM_FREQ_16_12_SHIFT;

   *chan->pm_config_2  = (0 << PM_SCALE_SHIFT) & PM_SCALE;
   *chan->pm_config_2 |= (0 << PM_RISE_INC_SHIFT) & PM_RISE_INC;
   *chan->pm_config_2 |= (0 << PM_FALL_INC_SHIFT) & PM_FALL_INC;

   *chan->pm_config_3  =  0 << PM_ENABLE_SHIFT;
   *chan->pm_config_3 |= (0 << PM_BURST_LENGTH_SHIFT) & PM_BURST_LENGTH;
   *chan->pm_config_3 |=  0 << PM_BURST_CONT_SHIFT;
   *chan->pm_config_3 |=  0 << PM_BURST_START_SHIFT;

   /* Configure CIC register values */
   *chan->cic_config  = (4 << CIC_DEC_SHFT_SHIFT) & CIC_DEC_SHFT;
   *chan->cic_config |= (4 << CIC_INC_SHFT_SHIFT) & CIC_INC_SHFT;
   *chan->cic_config |=  1 << CIC_DEC_EQ_EN_SHIFT;
   *chan->cic_config |=  1 << CIC_INC_EQ_EN_SHIFT;

   /* Set ASRC_DEC_COEFF_SEL for low frequency (8/16 kHz sampling) */
   *chan->asrc_dec_config  = (0xD11 << ASRC_DEC_SCALE_SHIFT) & ASRC_DEC_SCALE;
   *chan->asrc_dec_config |= (0x13 << ASRC_DEC_NUM_SECT_SHIFT) & ASRC_DEC_NUM_SECT;
   *chan->asrc_dec_config |= (3 << ASRC_DEC_SHFT_SHIFT) & ASRC_DEC_SHFT;
   *chan->asrc_dec_config |=  0 << ASRC_DEC_SYM_ASYM_SHIFT;
   *chan->asrc_dec_config |= (0 << ASRC_DEC_COEFF_SEL_SHIFT) & ASRC_DEC_COEFF_SEL;

   if(rate == DSPHAL_RATE_8KHZ)
   {
      *chan->fcw_config_1  = APM_FCW_SCALE & FCW_SCALE;
      *chan->fcw_config_2  = (APM_FCW_SHIFT << FCW_SHFT_SHIFT) & FCW_SHFT;
   }
   else
   {
      *chan->fcw_config_1  = APM_FCW_SCALE_WB & FCW_SCALE;
      *chan->fcw_config_2  = (APM_FCW_SHIFT_WB << FCW_SHFT_SHIFT) & FCW_SHFT;
   }
   *chan->fcw_config_2 |= (APM_FCW_CLK_SOURCE << CLOCK_SOURCE_SHIFT) & CLOCK_SOURCE;

   *chan->digmod_config  = (0x80 << DIGMOD_DITH_SCALE_SHIFT) & DIGMOD_DITH_SCALE;
   *chan->digmod_config |=  0 << DIGMOD_DEM_DIS_SHIFT;
   *chan->digmod_config |=  0 << DIGMOD_DEM_TONE_SHIFT;
}
#endif /* APM_DMA_SUPPORT */

