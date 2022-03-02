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

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/interrupt.h>

#include <dsphal_chip.h>
#include <dsphal_dect.h>

/****************************************************************************
* Local function declaration
****************************************************************************/
static int  dect_init(void);
static int  dect_deinit(void);
static int  dect_open_channel(struct dhchancfg *cfg, int count);
static int  dect_release_channel(struct dhchancfg *cfg, int count);
static void dect_idle(int idle);

static int  dect_dma_init(void);
static int  dect_dma_deinit(void);
static void dect_dma_cfg_chan(struct dect_dma *cfg, unsigned int count,
                              size_t size);
static int  dect_dma_start(void);
static int  dect_dma_stop(void);
static void dect_dma_realign(int ignore_stats);

static void        dect_prime_chan_buf(struct dect_dma *cfg);
static void        dect_start_ip_audio(void);
static void        dect_stop_ip_audio(void);
static irqreturn_t dect_isr(int irq, void *dev_id);
static void        dect_channel_interrupt(struct dect_dma *cfg);


/****************************************************************************
* Variables
****************************************************************************/
static unsigned int dect_stack_started = 0;
static unsigned int dect_dma_initialized = 0;
static enum dect_dma_state dect_dma_state = DDS_STOPPED;
DEFINE_SPINLOCK(dect_lock);
static unsigned long dma_status_clear = 0;
static unsigned int dect_idle_status = 0;
static unsigned int dect_trig_en_cache = 0;
static unsigned int dect_shm_irq_en_cache = 0;

struct intf_hdlrs dect_hdlr_table = {
   .init       = dect_init,
   .deinit     = dect_deinit,
   .open       = dect_open_channel,
   .release    = dect_release_channel,
};

struct isr_hdlrs dect_isr_table = {
   .idle       = dect_idle,
};

static struct dect_dma dect_dma_cfg[] = {
   /* RX dma */
   {
      .chan_id       = 0,
      .direction     = DMA_FROM_DEVICE,
      .buffer        = { 0 },
      .interrupt_ch  = 0,
      .tick          = 0, 

      .ch_en_bits    = { RX_EN_0, RX_EN_1, RX_EN_2, RX_EN_3 },
      .irq_en_bits   = 1 << DECT_SHM_IRQ_RX_DMA_DONE,
      .shm_saddr_reg = { (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ddr_saddr_rx_s0,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ddr_saddr_rx_s1,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ddr_saddr_rx_s2,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ddr_saddr_rx_s3
                       },
      .ahb_saddr_reg = { (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ahb_saddr_rx_s01,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ahb_saddr_rx_s23,
                       },
      .ahb_saddr     = { DECT_AHB_CHAN0_TX, /* RX buffers are DECT IP's TX buffers */
                         DECT_AHB_CHAN1_TX,
                         DECT_AHB_CHAN2_TX,
                         DECT_AHB_CHAN3_TX
                       },
      .xfer_size     =   (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_xfer_size_rx,
      .xfer_counter  =   (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_xfer_cntr_rx,
      .dma_buf_size  =   (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_buf_size_rx,
      .dma_offsets   = { (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_offset_addr_rx_s01,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_offset_addr_rx_s23
                       },
      .dma_trig_bits = DMA_RX_REG_TRIG_EN,
   },

   /* TX dma */
   {
      .chan_id       = 1,
      .direction     = DMA_TO_DEVICE,
      .buffer        = { 0 },
      .interrupt_ch  = 0, /* Use the RX DMA's interrupt */
      .tick          = 0,

      .ch_en_bits    = { TX_EN_0, TX_EN_1, TX_EN_2, TX_EN_3 },
      .irq_en_bits   = 1 << DECT_SHM_IRQ_TX_DMA_DONE,
      .shm_saddr_reg = { (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ddr_saddr_tx_s0,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ddr_saddr_tx_s1,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ddr_saddr_tx_s2,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ddr_saddr_tx_s3
                       },
      .ahb_saddr_reg = { (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ahb_saddr_tx_s01,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_ahb_saddr_tx_s23,
                       },
      .ahb_saddr     = { DECT_AHB_CHAN0_RX, /* TX buffers are DECT IP's RX buffers */
                         DECT_AHB_CHAN1_RX,
                         DECT_AHB_CHAN2_RX,
                         DECT_AHB_CHAN3_RX
                       },
      .xfer_size     =   (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_xfer_size_tx,
      .xfer_counter  =   (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_xfer_cntr_tx,
      .dma_buf_size  =   (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_buf_size_tx,
      .dma_offsets   = { (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_offset_addr_tx_s01,
                         (volatile uint32_t*) &DECT_DMA_CTRL->dect_shm_dma_offset_addr_tx_s23
                       },
      .dma_trig_bits = DMA_TX_REG_TRIG_EN,
   },

};


/****************************************************************************
* Function implementation
****************************************************************************/

/*****************************************************************************
*  FUNCTION:   dect_block_reset
*
*  PURPOSE:    Handle resetting the DECT block
*
*  PARAMETERS: none
*
*  RETURNS:    nothing
*
*****************************************************************************/
void dect_block_reset(void)
{
   DECT_CTRL->dect_shm_ctrl |=  DECT_SOFT_RESET;
   mdelay(1);
   DECT_CTRL->dect_shm_ctrl &= ~DECT_SOFT_RESET;
}


/*****************************************************************************
*  FUNCTION:   dect_set_stack_status
*
*  PURPOSE:    Set whether the stack has started or stopped
*
*  PARAMETERS: started - 1 if stack is started, 0 otherwise
*
*  RETURNS:    nothing
*
*****************************************************************************/
void dect_set_stack_status(int started)
{
   unsigned long flags;
   spin_lock_irqsave(&dect_lock, flags);

   if(started != dect_stack_started)
   {
      DHLOG_DEBUG("%s: dect status set to %s\n", __func__,
                  started ? "started" : "stopped");
      dect_stack_started = started;
      if(dect_stack_started && dect_dma_initialized)
         dect_start_ip_audio();
      else
      {
         /* Make sure the DMA ends up stopped and unregister the DECT tick */
         dect_dma_state = DDS_STOPPED;
         dh_unreg_tick_source(DH_TICK_SOURCE_DECT);
      }
   }

   spin_unlock_irqrestore(&dect_lock, flags);
}


/*****************************************************************************
*  FUNCTION:   dect_init
*
*  PURPOSE:    Handle initialization of dect block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
static int dect_init()
{
   int ret;

   if(!vp.numDectLines)
      return 0;

   /* Power up the block */
   ret = dect_power_up();
   if(ret)
      goto err;

   /* Configure the dect clock */
   ret = dect_clk_init();
   if(ret)
      goto err_power;

   /* Reset the block and initialize the dma */
   dect_block_reset();
   ret = dect_dma_init();
   if(ret)
      goto err_clk;
   return 0;

err_clk:
   dect_clk_deinit();
   dect_block_reset();
err_power:
   dect_power_down();
err:
   return ret;
}


/*****************************************************************************
*  FUNCTION:   dect_deinit
*
*  PURPOSE:    Handle deinitialization of dect block
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
static int dect_deinit()
{
   if(!vp.numDectLines)
      return 0;

   dect_dma_deinit();
   dect_clk_deinit();
   dect_block_reset();

   /* Turn of the dect block */
   return dect_power_down();
}


/*****************************************************************************
*  FUNCTION:   dect_open_channel
*
*  PURPOSE:    Handle opening the dect channel
*
*  PARAMETERS: cfg    - channel configuration
*              count  - number of active channels (after adding current)
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
static int dect_open_channel(struct dhchancfg* cfg, int count)
{
   (void)cfg;
   (void)count;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   /* On the first opened channel, start the DMA */
   if(count == 1)
      dect_dma_start();

   return 0;
}


/*****************************************************************************
*  FUNCTION:   dect_release_channel
*
*  PURPOSE:    Handle releasing the given dect channel
*
*  PARAMETERS: cfg    - channel configuration
*              count  - number of active channels (after removing current)
*
*  RETURNS:    0 on success, error otherwise
*
*****************************************************************************/
static int dect_release_channel(struct dhchancfg* cfg, int count)
{
   (void)cfg;
   (void)count;

   DHLOG_DEBUG("%s: channel %d\n", __func__, cfg->id);

   /* On the last channel closed, stop the DMA */
   if(count == 0)
      dect_dma_stop();

   return 0;
}


/*****************************************************************************
*  FUNCTION:   dect_idle
*
*  PURPOSE:    Handle setting the DECT DMA to idle or active
*
*  PARAMETERS: idle - 0 for active, 1 for idle
*
*  RETURNS:    none
*
*****************************************************************************/
static void dect_idle(int idle)
{
   unsigned long flags;
   spin_lock_irqsave(&dect_lock, flags);

   if(dect_idle_status == idle)
      goto out;
   dect_idle_status = idle;
   if(!dect_dma_initialized)
      goto out;

   DHLOG_INFO("%s: dect dma set to %s\n", __func__, idle ? "idle" : "active");
   if(idle)
      DECT_CTRL->dect_shm_irq_enable &= ~dect_shm_irq_en_cache;
   else
      DECT_CTRL->dect_shm_irq_enable |= dect_shm_irq_en_cache;

out:
   spin_unlock_irqrestore(&dect_lock, flags);
}


/*****************************************************************************
*  FUNCTION:   dect_dma_init
*
*  PURPOSE:    Initialize the board's dect DMA
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*  NOTES:      This function assumes it will only be called once to initialize
*              the DMA. Note that the enabled channels must be already set in
*              dect_chan_ctrl.
*
*****************************************************************************/
static int dect_dma_init()
{
   int i;
   int ret = -ENOMEM;
   unsigned int buffer_size;
   struct dect_dma *cfg;
   unsigned long flags;

   if(dect_dma_initialized)
      return 0;

   /* Allocate all the required buffer area. We use a double-buffered scheme
    * for both RX and TX buffers, so we will have 4 buffers in total. Each
    * buffer/descriptor will also be aligned on a cacheline boundary, so
    * account for this in the size calculation. */
   buffer_size = ALIGN( DECT_DMA_BUF_SIZE, DECT_BUF_ALIGN_BYTES ) *
                 DECT_NUM_CHAN;

   spin_lock_irqsave(&dect_lock, flags);

   /* Setup the DMA TX and RX channels */
   for(i = 0; i < ARRAY_SIZE(dect_dma_cfg); i++)
   {
      cfg = &dect_dma_cfg[i];

      /* Allocate the buffers */
      cfg->buffer_size = buffer_size;
      cfg->buffer.cpu = dma_zalloc_coherent(dhdev.device, buffer_size,
            &cfg->buffer.dma, GFP_IOFS | GFP_DMA);
      if(!cfg->buffer.cpu)
      {
         DHLOG_ERR("%s: error allocating dma buffers\n", __func__);
         goto err_cleanup_dect_chan;
      }
      DHLOG_DEBUG("%s: chan %d buffer area 0x%p [0x%x] size %d\n", __func__, i,
            cfg->buffer.cpu, cfg->buffer.dma, buffer_size);

      dect_dma_cfg_chan(cfg, DECT_NUM_BUF_PER_CHAN, DECT_DMA_CHAN_SIZE);

      /* Enable the DMA interrupts if the channel is defined to generate its
       * own interrupt */
      if(dect_dma_cfg[i].interrupt_ch == dect_dma_cfg[i].chan_id)
      {
         dect_shm_irq_en_cache |= dect_dma_cfg[i].irq_en_bits;
         DECT_CTRL->dect_shm_irq_enable |= dect_dma_cfg[i].irq_en_bits;
         dma_status_clear |= dect_dma_cfg[i].irq_en_bits;
      }
   }

   /* Setup DMA control register: set burst size, give priority to RX DMA, and
    * setup byte swapping based on processor endianness. */
   DECT_DMA_CTRL->dect_shm_dma_ctrl &=
      ~(MAX_BURST_CYCLE_MASK | DMA_SUBWORD_SWAP_MASK);
   DECT_DMA_CTRL->dect_shm_dma_ctrl |= 8 << MAX_BURST_CYCLE_SHIFT
                                    | DMA_RX_TRIG_FIRST
#ifdef CONFIG_CPU_BIG_ENDIAN
                                    | DMA_SWAP_16_BIT;
#else
                                    | DMA_SWAP_8_BIT;
#endif /* !CONFIG_CPU_BIG_ENDIAN */

   /* Clear the interrupt status */
   DECT_CTRL->dect_shm_irq_status |= dma_status_clear;
   dect_dma_initialized = 1;

   ret = 0;
   goto out;

err_cleanup_dect_chan:
   /* Cleanup any configured channels */
   for(; i >= 0; i--)
   {
      if(dect_dma_cfg[i].buffer.cpu)
      {
         dma_free_coherent(dhdev.device, dect_dma_cfg[i].buffer_size,
               dect_dma_cfg[i].buffer.cpu, dect_dma_cfg[i].buffer.dma);
         dect_dma_cfg[i].buffer.cpu = NULL;
         dect_dma_cfg[i].buffer.dma = 0;
      }
   }
out:
   spin_unlock_irqrestore(&dect_lock, flags);
   return ret;
}


/*****************************************************************************
*  FUNCTION:   dect_dma_deinit
*
*  PURPOSE:    Deinitialize the board's dect DMA
*
*  PARAMETERS: none
*
*  RETURNS:    0 on success, error otherwise
*
*  NOTES:      This function assumes it will only be called once to
*              deinitialize the DMA.
*
*****************************************************************************/
static int dect_dma_deinit()
{
   unsigned int i;
   unsigned long flags;
   struct dma_addr buf_tmp = { 0 };
   size_t buf_size_tmp;

   /* Clear the DMA status */
   DECT_DMA_CTRL->dect_shm_dma_ctrl = DMA_CLEAR;
   DECT_DMA_CTRL->dect_shm_dma_ctrl = 0;

   /* Release all the channels and disable the DMA */
   for(i = 0; i < ARRAY_SIZE(dect_dma_cfg); i++)
   {
      spin_lock_irqsave(&dect_lock, flags);

      /* Disable the DMA as an interrupt source and clear any pending
       * interrupts */
      dect_shm_irq_en_cache &= ~dect_dma_cfg[i].irq_en_bits;
      DECT_CTRL->dect_shm_irq_enable &= ~dect_dma_cfg[i].irq_en_bits;
      DECT_CTRL->dect_shm_irq_status |= dect_dma_cfg[i].irq_en_bits;
      dma_status_clear &= ~dect_dma_cfg[i].irq_en_bits;

      /* Free the allocated DMA buffers */
      if(dect_dma_cfg[i].buffer.cpu)
      {
         buf_tmp = dect_dma_cfg[i].buffer;
         buf_size_tmp = dect_dma_cfg[i].buffer_size;

         dect_dma_cfg[i].buffer.cpu = NULL;
         dect_dma_cfg[i].buffer.dma = 0;
      }

      spin_unlock_irqrestore(&dect_lock, flags);

      /* dma_free_coherent can sleep, so we have to execute it with interrupts
       * enabled */
      if(buf_tmp.cpu)
         dma_free_coherent(dhdev.device, buf_size_tmp, buf_tmp.cpu,
                           buf_tmp.dma);
   }

   dect_dma_initialized = 0;
   return 0;
}


/*****************************************************************************
*  FUNCTION:   dect_dma_cfg_chan
*
*  PURPOSE:    Configure DECT channels inside DMA. Setup the DDR and AHB start
*              addresses, transfer size, transfer count, etc.
*
*  PARAMETERS: cfg   - pointer to dect dma channel cfg structure
*              count - number of DMA transfers
*              size  - size of each DMA transfer
*
*  RETURNS:    nothing
*
*  NOTE:       This function assumed the dect lock is held.
*
*****************************************************************************/
static void dect_dma_cfg_chan(struct dect_dma *cfg, unsigned int count,
                              size_t size)
{
   int i;

   /* Setup DMA config registers */
   *cfg->xfer_size    = 0;
   *cfg->dma_buf_size = 0;
   for(i = 0; i < ARRAY_SIZE(cfg->ahb_saddr_reg); i++)
      *cfg->ahb_saddr_reg[i] = 0;

   for(i = 0; i < DECT_NUM_CHAN; i++)
   {
      unsigned int slot_shift = (4 - (i + 1)) * 8;

      /* Set the DDR start address in the shim */
      *cfg->shm_saddr_reg[i] = (unsigned int)cfg->buffer.dma +
         i * ALIGN( size * count, DECT_BUF_ALIGN_BYTES );

      /* Set the AHB start addresses */
      *cfg->ahb_saddr_reg[i/2] |=
         ((cfg->ahb_saddr[i] - DECT_AHB_SHARED_RAM_BASE) & 0xFFFF) <<
         (i & 0x1 ? 0 : 16);

      /* Setup DMA transfer size in words and set the total size of DMA buffer
       * per slot in terms of transfer size. This is equivalent to the number
       * of buffers per DMA channel */
      *cfg->xfer_size    |= (size / sizeof(int)) << slot_shift;
      *cfg->dma_buf_size |= count << slot_shift;

      dect_prime_chan_buf(cfg);

      /* Enable DECT channel */
      DECT_DMA_CTRL->dect_shm_dma_ctrl |= cfg->ch_en_bits[i];
   }

   /* clear transfer counter */
   *cfg->xfer_counter = 0;
}


/*****************************************************************************
*  FUNCTION:   dect_dma_start
*
*  PURPOSE:    Start the dect DMA
*
*  PARAMETERS: none
*
*  RETURNS:    nothing
*
*  NOTES:      This function assumes it will only be called once to
*              start the DMA.
*
*****************************************************************************/
static int dect_dma_start(void)
{
   int ret;
   unsigned long flags;

   /* Setup the interrupt handler */
   ret = request_irq(INTERRUPT_ID_DECT_0, dect_isr, 0, "voip:dect", NULL);
   if(ret)
   {
      DHLOG_ERR("%s: unable to install interrupt %d (%d)\n", __func__,
                INTERRUPT_ID_DECT_0, ret);
      goto out;
   }

   DHLOG_INFO("%s: installed irq handler for interrupt %d\n",
               __func__, INTERRUPT_ID_DECT_0);

   spin_lock_irqsave(&dect_lock, flags);

   /* Allow the z-cross pulses from DECT IP to trigger DMA start */
   dect_trig_en_cache               |= DMA_TX_INT_TRIG_EN
                                    |  DMA_RX_INT_TRIG_EN;
   if(!dect_idle_status)
      DECT_DMA_CTRL->dect_shm_dma_ctrl |= dect_trig_en_cache;

   /* If the DECT stack has initialized already, we can now setup and start
    * buffer processing in the DECT IP. Otherwise, we have to wait until the
    * DECT stack initializes before really beginning the DMA */
   if(dect_stack_started)
      dect_start_ip_audio();

   spin_unlock_irqrestore(&dect_lock, flags);

out:
   return ret;
}


/*****************************************************************************
*  FUNCTION:   dect_dma_stop
*
*  PURPOSE:    Stop the dect DMA
*
*  PARAMETERS: none
*
*  RETURNS:    nothing
*
*  NOTES:      This function assumes it will only be called once to
*              stop the DMA.
*
*****************************************************************************/
static int dect_dma_stop(void)
{
   unsigned long flags;

   spin_lock_irqsave(&dect_lock, flags);

   dect_stop_ip_audio();

   spin_unlock_irqrestore(&dect_lock, flags);

   mdelay(20);

   dect_trig_en_cache &= ~(DMA_TX_INT_TRIG_EN | DMA_RX_INT_TRIG_EN);
   DECT_DMA_CTRL->dect_shm_dma_ctrl &= ~(DMA_TX_INT_TRIG_EN |
                                         DMA_RX_INT_TRIG_EN);

   free_irq(INTERRUPT_ID_DECT_0, NULL);

   return 0;
}


/*****************************************************************************
*  FUNCTION:   dect_dma_realign
*
*  PURPOSE:    Realign the DECT DMA and buffer processing. This function should
*              get called once per interrupt until the dect_dma_state is set to
*              DDS_RUNNING.
*
*  PARAMETERS: ignore_stats - if 1, do not increment realign stats
*
*  RETURNS:    nothing
*
*  NOTES:      This function assumes we are holding the dect lock
*
*****************************************************************************/
static void dect_dma_realign(int ignore_stats)
{
   int i;

   /* Sanity check */
   if(!dect_stack_started || !dect_dma_initialized)
      return;

   /* Make sure the DECT IP block is stopped */
   if(dect_dma_state == DDS_RUNNING)
      *(unsigned short*)DECT_STARTCTL = 0;
   dect_dma_state = DDS_STOPPED;

   /* The DECT IP block always starts processing buffer 0 in the AHB space.
    * The DECT DMA simply performs a direct copy between the AHB buffer and DDR
    * buffer at the given offsets (buffer 0 to buffer 0, buffer 1 to buffer 1,
    * etc.). We want the trigger the DECT DMA as late as possible to allow as
    * much time as possible for the DSP process to finish. To do this, we need
    * the DMA to point to the second page of the transfer so that once buffer
    * processing nears finishing on the first buffer, we start DMAing the
    * second.
    *
    * Normally this would mean we set the DMA offset to the beginning of the
    * second buffer and then start the DECT IP buffer processing. However, due
    * to the design of the DECT shim, we are unable to program this offset
    * directly. Thus, in order to align the DMA and the buffer processing, we
    * must force the DMA to run a 'dummy' transfer on the first page. This will
    * leave the DMA pointing to the second page. At this point we can start
    * DECT buffer processing as normal.
    *
    * Note: we only need to check one channel offset since the offsets should
    *       all be identical for all the other channels.
    */
   for(i = 0; i < ARRAY_SIZE(dect_dma_cfg); i++)
   {
      if(*dect_dma_cfg[i].dma_offsets[0] == 0x0)
      {
         dect_dma_state = DDS_ALIGNING_DMA;
         if(!ignore_stats)
            debug_stats.dma_realigns[DH_TICK_SOURCE_DECT]++;
         DHLOG_DEBUG("%s: kicking dma %d\n", __func__, i);
         /* Force start the DMA */
         DECT_DMA_CTRL->dect_shm_dma_ctrl |=  dect_dma_cfg[i].dma_trig_bits;
         DECT_DMA_CTRL->dect_shm_dma_ctrl &= ~dect_dma_cfg[i].dma_trig_bits;
      }
   }

   /* If all the DMA buffers are set correctly, start DECT buffer processing */
   if(dect_dma_state == DDS_STOPPED)
   {
      /* Set the offset of buffer processing at which the DECT IP sends a
       * z-cross pulse to trigger the DMA. This is currently set to near the
       * end of each 4-channel transfer. The full structure definition
       * (gDspSyncFBufData_t) can be found in the DECT release code. */
      (*(uint16_t**)PCM_BUFF_CTL3)[7] = DECT_ZCROSS_TRIG_POINT;
      (*(uint16_t**)PCM_BUFF_CTL7)[7] = DECT_ZCROSS_TRIG_POINT;

      *(unsigned short*)DECT_STARTCTL = 1;
      dect_dma_state = DDS_RUNNING;
   }
}


/*****************************************************************************
*  FUNCTION:   dect_prime_chan_buf
*
*  PURPOSE:    Handle priming/resetting the DECT channel buffers by writing to
*              AHB shared memory.
*
*  PARAMETERS: cfg - pointer to dect dma channel cfg structure
*
*  RETURNS:    nothing
*
*****************************************************************************/
static void dect_prime_chan_buf(struct dect_dma *cfg)
{
   int i, j;
   volatile unsigned int *ahb_buf;

   for(i = 0; i < DECT_NUM_CHAN; i++)
   {
      ahb_buf = (volatile uint32_t*)cfg->ahb_saddr[i];
      for(j = 0; j * sizeof(*ahb_buf) < cfg->buffer_size; j++)
         ahb_buf[j] = 0;
   }
}


/*****************************************************************************
*  FUNCTION:   dect_start_ip_audio
*
*  PURPOSE:    Sets up and starts buffer processing in the DECT IP
*
*  PARAMETERS: none
*
*  RETURNS:    nothing
*
*  NOTES:      This function assumes we are holding the dect lock and that the
*              DECT stack has started.
*
*****************************************************************************/
static void dect_start_ip_audio(void)
{
   int i;

   /* If we are configured to handle DECT interrupts, register DECT as a tick
    * source */
   for(i = 0; i < ARRAY_SIZE(dect_dma_cfg); i++)
   {
      if(dect_dma_cfg[i].tick)
      {
         dh_reg_tick_source(DH_TICK_SOURCE_DECT, dect_dma_cfg[i].tick);
         break;
      }
   }

   dect_dma_state = DDS_STOPPED;
   dect_dma_realign(0);
}


/*****************************************************************************
*  FUNCTION:   dect_stop_ip_audio
*
*  PURPOSE:    Stops buffer processing in the DECT IP
*
*  PARAMETERS: none
*
*  RETURNS:    nothing
*
*  NOTES:      This function assumes we are holding the dect lock and that the
*              DECT stack has started.
*
*****************************************************************************/
static void dect_stop_ip_audio(void)
{
   int i;
   /* Check if DMA is registered as a tick source for any channels and if so,
    * unregister it */
   for(i = 0; i < ARRAY_SIZE(dect_dma_cfg); i++)
   {
      if(dect_dma_cfg[i].tick)
         dh_unreg_tick_source(DH_TICK_SOURCE_DECT);
   }

   /* Stop the DMA */
   dect_dma_state = DDS_STOPPED;
   *(unsigned short*)DECT_STARTCTL = 0;
}


/*****************************************************************************
*  FUNCTION:   dect_isr
*
*  PURPOSE:    Interrupt Service Routine handler - calls the handlers for each
*              channel that has the interrupt bit set and handler enabled.
*
*  PARAMETERS: irq    - interrupt number
*              dev_id - ISR cookie passed in request_irq
*
*  RETURNS:    irq return value
*
*****************************************************************************/
static irqreturn_t dect_isr(int irq, void *dev_id)
{
   int i, tick = 0;
   unsigned long status, flags;
   (void)irq;
   (void)dev_id;

   if(!dect_idle_status)
      dh_debug_isr(DH_TICK_SOURCE_DECT);

   spin_lock_irqsave(&dect_lock, flags);

   status = DECT_CTRL->dect_shm_irq_status;

   /* Ack the DMA interrupts */
   DECT_CTRL->dect_shm_irq_status |= dma_status_clear;

   if(dect_dma_state == DDS_ALIGNING_DMA)
      dect_dma_realign(0);
   else if(dect_dma_state == DDS_RUNNING && !dect_idle_status)
   {
      /* Iterate through each channel and calls the interrupt handler for all
       * valid channels that have their interrupt bits set */
      for(i = 0; i < ARRAY_SIZE(dect_dma_cfg); i++)
      {
         if(!dect_dma_cfg[i].buffer_size || dect_dma_cfg[i].interrupt_ch !=
               dect_dma_cfg[i].chan_id)
            continue;

         if(status & dect_dma_cfg[i].irq_en_bits)
         {
            dect_channel_interrupt(&dect_dma_cfg[i]);
            if(dect_dma_cfg[i].tick)
               tick = 1;
         }
      }
   }

   spin_unlock_irqrestore(&dect_lock, flags);

   /* Signal that the DSP is ready to tick */
   if(tick)
      dh_tick(DH_TICK_SOURCE_DECT);

   return IRQ_HANDLED;
}


/*****************************************************************************
*  FUNCTION:   dect_channel_interrupt
*
*  PURPOSE:    Handles the interrupt for a specific channel
*
*  PARAMETERS: cfg - DMA config
*
*  RETURNS:    nothing
*
*  NOTES:      This function assumes we are holding the dect lock
*
*****************************************************************************/
static void dect_channel_interrupt(struct dect_dma *cfg)
{
   BP_VOICE_CHANNEL *bpch;
   unsigned int i, chan;
   unsigned int page_offset;

   /* Iterate through the audio channel list and process any DECT channels */
   for(i = 0; i < ARRAY_SIZE(chan_cfg); i++)
   {
      void* bufp;
      size_t size;

      /* Skip the channel if we shouldn't process it */
      if(!chan_cfg[i].enabled || chan_cfg[i].interface != DSPHAL_INTF_DECT)
         continue;

      bpch = &vp.voiceDevice[chan_cfg[i].vp_dev].channel[chan_cfg[i].vp_chan];
      chan = bpch->cfg.dect.dectChanId;

      /* page_offset is the index of the next page to DMA */
      page_offset  = *cfg->dma_offsets[chan/2] >> (chan & 0x1 ? 0 : 16);
      page_offset &= 0xffff;
      page_offset  = (page_offset < DECT_DMA_CHAN_SIZE) ? 1 : 0;

      /*
       * Setup the buffer pointer and size.
       * The DECT DMA buffers are arranged as follows.
       *
       *      80     =   160
       *    samples     bytes
       *  +----------+----------+----------+----------+
       *  | Ch0 Buf0 | Ch0 Buf1 | Ch1 Buf0 | Ch1 Buf1 |
       *  +----------+----------+----------+ ---------+
       *  | Ch2 Buf0 | Ch2 Buf1 | Ch3 Buf0 | Ch3 Buf1 |
       *  +----------+----------+----------+----------+
       */
      bufp  = cfg->buffer.cpu;
      bufp += (chan * DECT_NUM_BUF_PER_CHAN + page_offset) *
         DECT_DMA_CHAN_SIZE;
      size  = DECT_DMA_CHAN_SIZE;

      /* Copy the data to/from the channel's audio buffers */
      if(cfg->direction == DMA_TO_DEVICE)
         dh_copy_egress(&chan_cfg[i], bufp, size);
      else
         dh_copy_ingress(&chan_cfg[i], bufp, size);
   }

   /* If we are responding to a real interrupt, we need to go through the list
    * of all configured channels and find any that have attached to our
    * interrupt and invoke the channel_interrupt handler for those channels
    * as well. */
   if(cfg->interrupt_ch == cfg->chan_id)
   {
      for(i = 0; i < ARRAY_SIZE(dect_dma_cfg); i++)
      {
         if(dect_dma_cfg[i].chan_id == cfg->chan_id ||
            dect_dma_cfg[i].interrupt_ch != cfg->chan_id)
            continue;

         dect_channel_interrupt(&dect_dma_cfg[i]);
      }
   }
}

