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
#ifndef _DSPHAL_CHIP_H
#define _DSPHAL_CHIP_H

#include <bcm_map_part.h>
#ifndef _CFE_
#include <bcm_intr.h>
#endif

/*****************************************************************************
** BCM 63138 (impl2)
*****************************************************************************/
#if defined(CONFIG_BCM963138)
   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_ID_PCM_0
   #define IUDMA_NUM_CHANNELS       6

   #ifndef APM_BASE
   #define APM_BASE                 (IO_ADDRESS(0x80000000) + 0x00100000)
   #endif
   #define PCM_BASE                 (IO_ADDRESS(0x80000000) + 0x00100200)
   #define IUDMA_BASE               (IO_ADDRESS(0x80000000) + 0x00100800)
   #define DECT_SHIM_CTRL_BASE      (IO_ADDRESS(0x80000000) + 0x00050000)
   #define DECT_SHIM_DMA_CTRL_BASE  (IO_ADDRESS(0x80000000) + 0x00050050)
   #define DECT_AHB_SHARED_RAM_BASE (IO_ADDRESS(0x80000000) + 0x00040000)

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_DSL                       1
   #define PCM_NTR_CTRL_CLEAR                (~0xF0000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */
   /* Due to a quirk in the 63138/63148, the timeslots are shifted forward by
    * 16bits and wrap around at the end of the frame */
   #define pcm_get_rx_ch_index(x)   (((x) + 1) & 0x7)

   /* DECT settings */
   #define DECT_AHB_BASE_ADDR       DECT_AHB_REG_PHYS_BASE


/*****************************************************************************
** BCM 63148 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM963148)
   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_ID_PCM_0
   #define IUDMA_NUM_CHANNELS       6
   #define DMA_COHERENT_BITS        28

   #ifndef APM_BASE
   #define APM_BASE                 (IO_ADDRESS(0x80000000) + 0x00100000)
   #endif
   #define PCM_BASE                 (IO_ADDRESS(0x80000000) + 0x00100200)
   #define IUDMA_BASE               (IO_ADDRESS(0x80000000) + 0x00100800)
   #define DECT_SHIM_CTRL_BASE      (IO_ADDRESS(0x80000000) + 0x00050000)
   #define DECT_SHIM_DMA_CTRL_BASE  (IO_ADDRESS(0x80000000) + 0x00050050)
   #define DECT_AHB_SHARED_RAM_BASE (IO_ADDRESS(0x80000000) + 0x00040000)

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_DSL                       1
   #define PCM_NTR_CTRL_CLEAR                (~0xF0000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */
   /* Due to a quirk in the 63138/63148, the rx timeslots are shifted forward
    * by 16bits and wrap around at the end of the frame */
   #define pcm_get_rx_ch_index(x)   (((x) + 1) & 0x7)

   /* DECT settings */
   #define DECT_AHB_BASE_ADDR       DECT_AHB_REG_PHYS_BASE


/*****************************************************************************
** BCM 63268 (impl1)
*****************************************************************************/
#elif defined(CONFIG_BCM963268)
   /* General settings & supported components */
   #define PCM_ISI_SUPPORT          1
   #define PCM_ZSI_SUPPORT          1
   #define PCM_PLL_CH2_SUPPORT      1
   #define PCM_PLL_CH3_SUPPORT      1
   #define iudma_get_irq_num()      INTERRUPT_ID_PCM_DMA_0
   #define IUDMA_NUM_CHANNELS       2

   #define PCM_BASE                 0xb000b000
   #define IUDMA_BASE               0xb000b800
   #define DECT_SHIM_CTRL_BASE      0xb000a000
   #define DECT_SHIM_DMA_CTRL_BASE  0xb000a050
   #define DECT_AHB_SHARED_RAM_BASE 0xb06f0000

   /* PCM settings */
   #define PCM_NTR_DSL              1
   #define PCM_DMA_CHANNEL_RX       0
   #define PCM_DMA_CHANNEL_TX       1
   #define PCM_PLL_CTRL_1           0x1C311114 /* Set P1=1, P2=1, Ndiv=49, M1div=20, using 20Mhz for PCM PLL => 49.152Mhz  (w/ndiv_frac) */
   #define PCM_PLL_CTRL_2           0x0226E978 /* VCO<1600Mhz, Ndiv_mode=MFB, NDIV_FRAC=0x26E978 => 49.152MHz */
   #define PCM_PLL_CTRL_3           0x210064C0
   #define PCM_PLL_CTRL_4           0x00000015 /* Set reference clock to 20Mhz XTAL */
   #define PCM_PLL_CH2_CTRL         0x00000028 /* Turn on PCM PLL CH2, M2DIV=40 => 24.576MHz */
   #define PCM_PLL_CH3_CTRL         0x00000078 /* Turn on PCM PLL CH3, M3DIV=240 => 8.192MHz */
   #define PCM_PLL_CTRL_1_DECT      0x1C80111B /* Set P1=1, P2=1, Ndiv=128, M1div=27, using DECT XTAL for PCM PLL => 49.152Mhz  (w/o ndiv_frac) */
   #define PCM_PLL_CTRL_2_DECT      0xC0000000 /* VCO<1600Mhz, Ndiv_mode=N-mode, NDIV_FRAC=0 => 49.152Mhz */
   #define PCM_PLL_CTRL_4_DECT      0x01000000 /* Set reference clock to DECT XTAL */
   #define PCM_PLL_CH2_CTRL_DECT    0x00000036 /* Turn on PCM PLL CH2, M2DIV=80 => 24.576 */
   #define PCM_PLL_CTRL_1_ISI       0x1C621128 /* Set P1=1, P2=1, Ndiv=98, M1div=40, using 20Mhz for PCM PLL => 49.152Mhz  (w/ndiv_frac) */
   #define PCM_PLL_CTRL_2_ISI       0x124DD2F1 /* VCO>=1600Mhz, Ndiv_mode=MFB, NDIV_FRAC=0x4DD2F1 => 49.152Mhz */
   #define PCM_PLL_CTRL_3_ISI       0x38000700
   #define PCM_PLL_CH2_CTRL_ISI     0x00000050 /* Turn on PCM PLL CH2, M2DIV=80 => 24.576 */

   #define PCM_MSIF_DISABLE         0x00000000 /* Turn off MSIF */
   #define PCM_MSIF_ENABLE          0x00000001 /* Turn on MSIF */
   #define PCM_ZDS_ENABLE           0x00000002 /* Turn on ZDS */
   #define PCM_CLOCK_SEL_ISI        0x7
   #define PCM_CLOCK_SEL_PCM        0x2



/*****************************************************************************
** BCM 63381 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM963381)
   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_ID_PCM_DMA_0
   #define IUDMA_NUM_CHANNELS       2

   #define PCM_BASE                 0xb0010c00
   #define IUDMA_BASE               0xb0011000

   /* DPLL settings */
   #define DPLL                     PCM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_DSL                       1
   #define PCM_NTR_CTRL_CLEAR                (~0x70000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       0
   #define PCM_DMA_CHANNEL_TX       1
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for MISC */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

   /* Due to a quirk in the 63381, the rx timeslots are shifted forward by
    * 16bits and wrap around at the end of the frame */
   #define pcm_get_rx_ch_index(x)   (((x) + 1) & 0x7)

/*****************************************************************************
** BCM 6838 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM96838)
   /* General settings & supported components */
   #define APM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_ID_APM_IUDMA
   #define IUDMA_NUM_CHANNELS       6

   #ifndef APM_BASE
   #define APM_BASE                 0xb3a00000
   #endif
   #define PCM_BASE                 0xb3a00200
   #define APM_HVG_BASE             0xb3a00300
   #define IUDMA_BASE               0xb3a00800

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* APM settings */
   #define APM_DMA_CHANNEL_RX_A     0
   #define APM_DMA_CHANNEL_TX_A     1
   #define APM_DMA_CHANNEL_RX_B     2
   #define APM_DMA_CHANNEL_TX_B     3
   #define APM_FCW_INPUT            0x0a7c5ac4
   #define APM_FCW_SCALE            0x10000000
   #define APM_FCW_SHIFT            0
   #define APM_FCW_INPUT_WB         0x14f8b589
   #define APM_FCW_SCALE_WB         0x20000000
   #define APM_FCW_SHIFT_WB         0
   #ifdef BRCM_NTR_SUPPORT
   #  define APM_FCW_CLK_SOURCE     0
   #else
   #  define APM_FCW_CLK_SOURCE     1
   #endif

   /* PCM settings */
   #define PCM_NTR_PON              1
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

   /* Due to a quirk in the 6838, the rx timeslots are shifted forward by
    * 16bits and wrap around at the end of the frame */
   #define pcm_get_rx_ch_index(x)   (((x) + 1) & 0x7)

/*****************************************************************************
** BCM 6848 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM96848)
   /* General settings & supported components */
   #define APM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_ID_PCM_DMA_0
   #define IUDMA_NUM_CHANNELS       2

   #define PCM_BASE                 0xb0010c00
   #define IUDMA_BASE               0xb0011000

   /* DPLL settings */
   #define DPLL                     PCM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* PCM settings */
   #define PCM_NTR_PON              1
   #define PCM_DMA_CHANNEL_RX       0
   #define PCM_DMA_CHANNEL_TX       1
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

   /* Due to a quirk in the 6848, the rx timeslots are shifted forward by
    * 16bits and wrap around at the end of the frame */
   #define pcm_get_rx_ch_index(x)   (((x) + 1) & 0x7)

/*****************************************************************************
** BCM 6211x (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM94908)
   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_PCM_DMA_IRQ
   #define IUDMA_NUM_CHANNELS       2

   #define IUDMA_BASE               PCM_DMA_BASE

   /* DPLL settings */
   #define DPLL                     PCM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_RTR                       1  /* NTR for Router */
   #define PCM_NTR_CTRL_CLEAR                (~0x70000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       0
   #define PCM_DMA_CHANNEL_TX       1
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

   /* Due to a quirk in the 6211x, the rx timeslots are shifted forward by
    * 16bits and wrap around at the end of the frame */
   #define pcm_get_rx_ch_index(x)   (((x) + 1) & 0x7)

/*****************************************************************************
** BCM 6858 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM96858)
   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_PCM_DMA_IRQ
   #define IUDMA_NUM_CHANNELS       6

   #define IUDMA_BASE               PCM_DMA_BASE

   #define PCM_LOW_VOICE_DENSITY    1   /*6858B0 PCM channels are limited by OTP */
   #define PCM_SAMPLE_SIZE          0x00C00000
   #define PCM_SAMPLE_SIZE_SHIFT    22
   #define PCM_SAMPLE_SIZE_8        0
   #define PCM_SAMPLE_SIZE_16       1
   #define PCM_SAMPLE_SIZE_32       2
   #define PCM_CLK_DIV              0x0001C000
   #define PCM_CLK_DIV_SHIFT        14
   #define PCM_FRAME_SIZE           0x000000FF
   #define PCM_FRAME_SIZE_SHIFT     0

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_PON                       1
   #define PCM_NTR_CTRL_CLEAR                (~0x70000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_ZSI        0x7         /* div/?? clock divider for ZSI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

/*****************************************************************************
** BCM 63158 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM963158)
   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_PCM_DMA_IRQ
   #define IUDMA_NUM_CHANNELS       6

   #define IUDMA_BASE               PCM_DMA_BASE

   #define PCM_SAMPLE_SIZE          0x00C00000
   #define PCM_SAMPLE_SIZE_SHIFT    22
   #define PCM_SAMPLE_SIZE_8        0
   #define PCM_SAMPLE_SIZE_16       1
   #define PCM_SAMPLE_SIZE_32       2
   #define PCM_CLK_DIV              0x0001C000
   #define PCM_CLK_DIV_SHIFT        14
   #define PCM_FRAME_SIZE           0x000000FF
   #define PCM_FRAME_SIZE_SHIFT     0

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_PON                       1
   #define PCM_NTR_CTRL_CLEAR                (~0x70000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_ZSI        0x7         /* div/?? clock divider for ZSI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

/*****************************************************************************
** BCM 68460 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM96846)

   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_PCM_DMA_IRQ
   #define IUDMA_NUM_CHANNELS       6

   #define IUDMA_BASE               PCM_DMA_BASE

   #define PCM_SAMPLE_SIZE          0x00C00000
   #define PCM_SAMPLE_SIZE_SHIFT    22
   #define PCM_SAMPLE_SIZE_8        0
   #define PCM_SAMPLE_SIZE_16       1
   #define PCM_SAMPLE_SIZE_32       2
   #define PCM_CLK_DIV              0x0001C000
   #define PCM_CLK_DIV_SHIFT        14
   #define PCM_FRAME_SIZE           0x000000FF
   #define PCM_FRAME_SIZE_SHIFT     0

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_PON                       1
   #define PCM_NTR_CTRL_CLEAR                (~0x70000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_ZSI        0x7         /* div/?? clock divider for ZSI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

/*****************************************************************************
** BCM 68560 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM96856)

   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_PCM_DMA_IRQ
   #define IUDMA_NUM_CHANNELS       6

   #define IUDMA_BASE               PCM_DMA_BASE

   #define PCM_SAMPLE_SIZE          0x00C00000
   #define PCM_SAMPLE_SIZE_SHIFT    22
   #define PCM_SAMPLE_SIZE_8        0
   #define PCM_SAMPLE_SIZE_16       1
   #define PCM_SAMPLE_SIZE_32       2
   #define PCM_CLK_DIV              0x0001C000
   #define PCM_CLK_DIV_SHIFT        14
   #define PCM_FRAME_SIZE           0x000000FF
   #define PCM_FRAME_SIZE_SHIFT     0

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_PON                       1
   #define PCM_NTR_CTRL_CLEAR                (~0x70000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_ZSI        0x7         /* div/?? clock divider for ZSI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

/*****************************************************************************
** BCM 63178 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM963178)
   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_PCM_DMA_IRQ
   #define IUDMA_NUM_CHANNELS       6

   #define IUDMA_BASE               PCM_DMA_BASE

   #define PCM_SAMPLE_SIZE          0x00C00000
   #define PCM_SAMPLE_SIZE_SHIFT    22
   #define PCM_SAMPLE_SIZE_8        0
   #define PCM_SAMPLE_SIZE_16       1
   #define PCM_SAMPLE_SIZE_32       2
   #define PCM_CLK_DIV              0x0001C000
   #define PCM_CLK_DIV_SHIFT        14
   #define PCM_FRAME_SIZE           0x000000FF
   #define PCM_FRAME_SIZE_SHIFT     0

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_DSL                       0  /* Set PCM_NTR_DSL to 1 when BRCM_NTR_SUPPORT enabled */
   #define PCM_NTR_CTRL_CLEAR                (~0x70000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_ZSI        0x7         /* div/?? clock divider for ZSI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

/*****************************************************************************
** BCM 47622 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM947622)
   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_PCM_DMA_IRQ
   #define IUDMA_NUM_CHANNELS       6

   #define IUDMA_BASE               PCM_DMA_BASE

   #define PCM_SAMPLE_SIZE          0x00C00000
   #define PCM_SAMPLE_SIZE_SHIFT    22
   #define PCM_SAMPLE_SIZE_8        0
   #define PCM_SAMPLE_SIZE_16       1
   #define PCM_SAMPLE_SIZE_32       2
   #define PCM_CLK_DIV              0x0001C000
   #define PCM_CLK_DIV_SHIFT        14
   #define PCM_FRAME_SIZE           0x000000FF
   #define PCM_FRAME_SIZE_SHIFT     0

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_PON                       1
   #define PCM_NTR_CTRL_CLEAR                (~0x70000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_ZSI        0x7         /* div/?? clock divider for ZSI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */

/*****************************************************************************
** BCM 6878 (impl2)
*****************************************************************************/
#elif defined(CONFIG_BCM96878)

   /* General settings & supported components */
   #define PCM_DPLL_SUPPORT         1
   #define iudma_get_irq_num()      INTERRUPT_PCM_DMA_IRQ
   #define IUDMA_NUM_CHANNELS       6

   #define IUDMA_BASE               PCM_DMA_BASE

   #define PCM_SAMPLE_SIZE          0x00C00000
   #define PCM_SAMPLE_SIZE_SHIFT    22
   #define PCM_SAMPLE_SIZE_8        0
   #define PCM_SAMPLE_SIZE_16       1
   #define PCM_SAMPLE_SIZE_32       2
   #define PCM_CLK_DIV              0x0001C000
   #define PCM_CLK_DIV_SHIFT        14
   #define PCM_FRAME_SIZE           0x000000FF
   #define PCM_FRAME_SIZE_SHIFT     0

   /* DPLL settings */
   #define DPLL                     APM
   #define DPLL_CTRL_K0_CLEAR       ~0xF
   #define DPLL_PHASE_THRESH        5
   #define DPLL_K0                  12
   #define DPLL_NOM_FREQ            0xa7c5ac47

   /* NTR control settings */
   #define PCM_NTR_PON                       1
   #define PCM_NTR_CTRL_CLEAR                (~0x70000000)
   #define PCM_NTR_IN_CTRL_SHIFT             29 /* shift for PCM_NTR_IN clock routing field */
   #define PCM_NTR_IN_CTRL_SEL_DECT_NTR      3  /* Selection for routing DECT refclk as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_0    2  /* Selection for routing VDSL_NTR[0] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_NTR_1    1  /* Selection for routing VDSL_NTR[1] as PCM_NTR_IN */
   #define PCM_NTR_IN_CTRL_SEL_VDSL_GPIO     0  /* Selection for routing NTR_PULES_IN as PCM_NTR_IN */

   /* PCM settings */
   #define PCM_DMA_CHANNEL_RX       4
   #define PCM_DMA_CHANNEL_TX       5
   #define P_NCO_FCW_MISC           0xa7c5ac47  /* 0xa7c5ac47 for DPLL */
   #define P_PCM_NCO_SHIFT          0x0         /* 0x0 for DPLL, 0x1 for MISC */
   #define P_PCM_NCO_MUX_CNTL_DPLL  0x2         /* 0x2 for DPLL */
   #define P_PCM_NCO_MUX_CNTL_MISC  0x3         /* 0x3 for MISC */
   #define PCM_CLK_CNTL_1_ISI       0x60000000  /* PCM_NCO clk_out = 24.576Mhz. */
   #define PCM_CLK_CNTL_1_ZSI       0xc0000000  /* PCM_NCO clk_out = 49.152Mhz. */
   #define PCM_CLK_CNTL_1_PCM       0x40000000  /* PCM_NCO clk_out = 16.384Mhz. */
   #define PCM_MSIF_ENABLE          0x00000001  /* R_MSIF_ENABLE = 1 */
   #define PCM_ZDS_ENABLE           0x00000001  /* R_ZDS_ENABLE = 1 */
   #define PCM_NCO_MUX_SHIFT        4
   #define PCM_CLOCK_SEL_ISI        0x7         /* div/12 clock divider for ISI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_ZSI        0x7         /* div/?? clock divider for ZSI mode input clock of 24.576Mhz */
   #define PCM_CLOCK_SEL_PCM        0x2         /* div/8 clock divider for PCM/ZSI mode input clock of 16.384Mhz */
#else
   #error "No DSPHAL supported on this chip"
#endif



/* Common defines */
#ifndef DMA_COHERENT_BITS
#   define DMA_COHERENT_BITS        32
#endif
#ifndef pcm_get_tx_ch_index
#   define pcm_get_tx_ch_index(x)   (x)
#endif
#ifndef pcm_get_rx_ch_index
#   define pcm_get_rx_ch_index(x)   (x)
#endif


#endif /* _DSPHAL_CHIP_H */
