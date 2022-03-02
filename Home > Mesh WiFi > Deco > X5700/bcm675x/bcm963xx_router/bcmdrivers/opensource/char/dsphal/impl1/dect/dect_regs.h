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
#ifndef _DECT_REGS_H
#define _DECT_REGS_H

#include <bcm_map_part.h>

/*
 ** DECT IP Control Registers
 */
#define DECT_STARTCTL        (DECT_AHB_SHARED_RAM_BASE + 0x0818)
#define PCM_BUFF_CTL3        (DECT_AHB_SHARED_RAM_BASE + 0x082c)
#define PCM_BUFF_CTL7        (DECT_AHB_SHARED_RAM_BASE + 0x083c)
#define DECT_AHB_CHAN0_RX    (DECT_AHB_SHARED_RAM_BASE + 0x0a20)
#define DECT_AHB_CHAN1_RX    (DECT_AHB_SHARED_RAM_BASE + 0x0de0)
#define DECT_AHB_CHAN2_RX    (DECT_AHB_SHARED_RAM_BASE + 0x11a0)
#define DECT_AHB_CHAN3_RX    (DECT_AHB_SHARED_RAM_BASE + 0x1560)
#define DECT_AHB_CHAN0_TX    (DECT_AHB_SHARED_RAM_BASE + 0x0840)
#define DECT_AHB_CHAN1_TX    (DECT_AHB_SHARED_RAM_BASE + 0x0c00)
#define DECT_AHB_CHAN2_TX    (DECT_AHB_SHARED_RAM_BASE + 0x0fc0)
#define DECT_AHB_CHAN3_TX    (DECT_AHB_SHARED_RAM_BASE + 0x1380)
#define DECT_CLKEN           0x00000040

/*
 ** DECT IP Device Registers
 */
#define DECT_SHM_IRQ_DSP_INT                 0
#define DECT_SHM_IRQ_DSP_IRQ_OUT             1
#define DECT_SHM_IRQ_DIP_INT                 2
#define DECT_SHM_H2D_BUS_ERR                 3
#define DECT_SHM_IRQ_TX_DMA_DONE             4
#define DECT_SHM_IRQ_RX_DMA_DONE             5
#define DECT_SHM_IRQ_PLL_PHASE_LOCK          7  /* Skip reserved bit */
#define DECT_SHM_REG_DSP_BREAK               8
#define DECT_SHM_REG_DIP_BREAK               9
#define DECT_SHM_REG_IRQ_TO_IP               11 /* Skip reserved bit */
#define DECT_SHM_TX_DMA_DONE_TO_IP           12
#define DECT_SHM_RX_DMA_DONE_TO_IP           13

/*
 ** DECT Shim control definitions
 */
struct dect_shim_control
{
   uint32 dect_shm_ctrl;                     /* DECT shim control registers                     */
#define  APB_SWAP_MASK                       0x0000C000
#define  APB_SWAP_16_BIT                     0x00000000
#define  APB_SWAP_8_BIT                      0x00004000
#define  AHB_SWAP_MASK                       0x00003000
#define  AHB_SWAP_16_BIT                     0x00003000
#define  AHB_SWAP_8_BIT                      0x00002000
#define  AHB_SWAP_ACCESS                     0x00001000
#define  AHB_SWAP_NONE                       0x00000000
#define  UBUS3_SWAP                          0x00000400
#define  DECT_PULSE_COUNT_ENABLE             0x00000200
#define  PCM_PULSE_COUNT_ENABLE              0x00000100
#define  DECT_SOFT_RESET                     0x00000010
#define  PHCNT_CLK_SRC_PLL                   0x00000008
#define  PHCNT_CLK_SRC_XTAL                  0x00000000
#define  DECT_CLK_OUT_PLL                    0x00000004
#define  DECT_CLK_OUT_XTAL                   0x00000000
#define  DECT_CLK_CORE_PCM                   0x00000002
#define  DECT_CLK_CORE_DECT                  0x00000000
#define  DECT_PLL_REF_PCM                    0x00000001
#define  DECT_PLL_REF_DECT                   0x00000000

   uint32 dect_shm_pcm_clk_cntr;             /* PCM clock counter                               */
   uint32 dect_shm_dect_clk_cntr;            /* DECT clock counter                              */
   uint32 dect_shm_dect_clk_cntr_sh;         /* DECT clock counter snapshot                     */
   uint32 dect_shm_irq_enable;               /* DECT interrupt enable register                  */
   uint32 dect_shm_irq_status;               /* DECT Interrupt status register                  */
   uint32 dect_shm_irq_trig;                 /* DECT DSP ext IRQ trigger and IRQ test register  */
   uint32 dect_shm_dma_status;               /* DECT DMA STATUS register                        */
   uint32 dect_shim_dcxo_ctrl0;              /* DECT analog turnable XTAL control register0     */
   uint32 dect_shim_dcxo_ctrl1;              /* DECT analog turnable XTAL control register1     */
   uint32 dect_shim_pcm_ctrl;                /* PCM CLK control register                        */
#define  XTAL_DIV_EN                         0x00001000
   uint32 dect_shim_unused0;                 /* unused                                          */
   uint32 dect_shm_pll_reg_0;                /* DECT PLL configuration register 0, DECT_SHIM_PLL_CTRL0 in RDB  */
   uint32 dect_shm_pll_reg_1;                /* DECT PLL configuration register 1               */
   uint32 dect_shm_pll_reg_2;                /* DECT PLL Ndiv configuration register           */
   uint32 dect_shm_pll_reg_3;                /* DECT PLL Pdiv and Mdiv configuration register  */
};

#define DECT_CTRL ((volatile struct dect_shim_control * const) DECT_SHIM_CTRL_BASE)

struct dect_shim_dma_control
{
   uint32 dect_shm_dma_ctrl;                 /* DECT DMA control register                       */
#define DMA_CLEAR                            0x80000000
#define DMA_SWAP_16_BIT                      0x03000000
#define DMA_SWAP_8_BIT                       0x02000000
#define DMA_SWAP_NONE                        0x01000000
#define DMA_SUBWORD_SWAP_MASK                0x03000000
#define DMA_TRIG_CNT_CLK_SEL_PCM             0x00800000
#define DMA_TRIG_CNT_IRQ_EN                  0x00400000
#define DMA_RX_CNT_TRIG_EN                   0x00200000
#define DMA_TX_CNT_TRIG_EN                   0x00100000
#define DMA_RX_INT_TRIG_EN                   0x00080000
#define DMA_TX_INT_TRIG_EN                   0x00040000
#define DMA_RX_REG_TRIG_EN                   0x00020000
#define DMA_TX_REG_TRIG_EN                   0x00010000
#define DMA_RX_TRIG_FIRST                    0x00008000
#define MAX_BURST_CYCLE_MASK                 0x00001F00
#define MAX_BURST_CYCLE_SHIFT                8
#define RX_EN_3                              0x00000080
#define RX_EN_2                              0x00000040
#define RX_EN_1                              0x00000020
#define RX_EN_0                              0x00000010
#define TX_EN_3                              0x00000008
#define TX_EN_2                              0x00000004
#define TX_EN_1                              0x00000002
#define TX_EN_0                              0x00000001

   uint32 dect_shm_dma_trig_cnt_preset;      /* DECT DMA trigger counter preset value                */
   uint32 dect_shm_dma_ddr_saddr_tx_s0;      /* DECT DMA DDR buffer starting address for TX slot 0   */
   uint32 dect_shm_dma_ddr_saddr_tx_s1;      /* DECT DMA DDR buffer starting address for TX slot 1   */
   uint32 dect_shm_dma_ddr_saddr_tx_s2;      /* DECT DMA DDR buffer starting address for TX slot 2   */
   uint32 dect_shm_dma_ddr_saddr_tx_s3;      /* DECT DMA DDR buffer starting address for TX slot 3   */
   uint32 dect_shm_dma_ddr_saddr_rx_s0;      /* DECT DMA DDR buffer starting address for RX slot 0   */
   uint32 dect_shm_dma_ddr_saddr_rx_s1;      /* DECT DMA DDR buffer starting address for RX slot 1   */
   uint32 dect_shm_dma_ddr_saddr_rx_s2;      /* DECT DMA DDR buffer starting address for RX slot 2   */
   uint32 dect_shm_dma_ddr_saddr_rx_s3;      /* DECT DMA DDR buffer starting address for RX slot 3   */
   uint32 dect_shm_dma_ahb_saddr_tx_s01;     /* DECT DMA AHB shared memory buffer starting address for TX slots 0 and 1  */
   uint32 dect_shm_dma_ahb_saddr_tx_s23;     /* DECT DMA AHB shared memory buffer starting address for TX slots 2 and 3  */
   uint32 dect_shm_dma_ahb_saddr_rx_s01;     /* DECT DMA AHB shared memory buffer starting address for RX slots 0 and 1  */
   uint32 dect_shm_dma_ahb_saddr_rx_s23;     /* DECT DMA AHB shared memory buffer starting address for RX slots 2 and 3  */
   uint32 dect_shm_dma_xfer_size_tx;         /* DECT DMA TX slots transfer size of each trigger      */
   uint32 dect_shm_dma_xfer_size_rx;         /* DECT DMA RX slots transfer size of each trigger      */
   uint32 dect_shm_dma_buf_size_tx;          /* DECT DMA TX slots memory buffer size                 */
   uint32 dect_shm_dma_buf_size_rx;          /* DECT DMA RX slots memory buffer size                 */
   uint32 dect_shm_dma_offset_addr_tx_s01;   /* DECT DMA access offset address for TX slots 0 and 1  */
   uint32 dect_shm_dma_offset_addr_tx_s23;   /* DECT DMA access offset address for TX slots 2 and 3  */
   uint32 dect_shm_dma_offset_addr_rx_s01;   /* DECT DMA access offset address for RX slots 0 and 1  */
   uint32 dect_shm_dma_offset_addr_rx_s23;   /* DECT DMA access offset address for RX slots 2 and 3  */
   uint32 dect_shm_dma_xfer_cntr_tx;         /* DECT DMA transfer count per slot in number of DMA transfer size */
   uint32 dect_shm_dma_xfer_cntr_rx;         /* DECT DMA transfer count per slot in number of DMA transfer size */
};

#define DECT_DMA_CTRL ((volatile struct dect_shim_dma_control * const) DECT_SHIM_DMA_CTRL_BASE)

#endif /* _DECT_REGS_H */
