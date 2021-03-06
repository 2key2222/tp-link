/*
 *  Atheros AR71xx built-in ethernet mac driver
 *
 *  Copyright (c) 2013 Qualcomm Atheros, Inc.
 *  Copyright (C) 2008-2010 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 *
 *  Based on Atheros' AG7100 driver
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include "ag71xx.h"
#include "ag71xx_ctrl.h"
#include "phys/ar8216.h"
#include "dev-eth.h"			/* add by Wu Yin, 07Jul14 */
#ifdef CONFIG_OF
#include <linux/of.h>
#include <linux/of_platform.h>
#endif

#ifndef UNUSED
#define UNUSED(__x)	(void)(__x)
#endif

void (*wan_status_handle)(int) = NULL;
EXPORT_SYMBOL(wan_status_handle);

static int ag71xx_gmac_num = 0;

#ifdef CONFIG_TP_FLASH_VERIFY
extern int flash_verify_result();
#ifdef CONFIG_AG71XX_WAN_DEV_NAME
#define WAN_DEV_NAME    CONFIG_AG71XX_WAN_DEV_NAME
#else
#define WAN_DEV_NAME    "eth0"
#endif
#endif

#if defined(CONFIG_ATH79_SOC_QCA9563)
extern ar8216_change_vlan_phylink(struct phy_device *phydev, int vid, bool linkup);
#endif

#ifdef CONFIG_ATH79_SOC_QCA9558
static struct ag71xx *ag71xx_gmac0_ag = NULL;
static struct ag71xx *ag71xx_gmac1_ag = NULL;
#define AR8327_PHY_NUM 				5
#define AP135_MAC0_OFFSET		0
#define AP135_MAC1_OFFSET		6
#elif (defined(CONFIG_ATH79_SOC_QCA9531) || defined(CONFIG_ATH79_SOC_QCA9561))
#define AP147_MAC0_OFFSET		0
#define AP147_MAC1_OFFSET		6
#endif

#define AG71XX_DEFAULT_MSG_ENABLE	\
	(NETIF_MSG_DRV			\
	| NETIF_MSG_PROBE		\
	| NETIF_MSG_LINK		\
	| NETIF_MSG_TIMER		\
	| NETIF_MSG_IFDOWN		\
	| NETIF_MSG_IFUP		\
	| NETIF_MSG_RX_ERR		\
	| NETIF_MSG_TX_ERR)

static int ag71xx_msg_level = -1;

#ifdef CONFIG_ATH79_SOC_QCA9563
u32 ar8216_phy_read(u32 address, u32 reg);
void ar8216_phy_write(u32 address, u32 reg,u32 data);
#endif

module_param_named(msg_level, ag71xx_msg_level, int, 0);
MODULE_PARM_DESC(msg_level, "Message level (-1=defaults,0=none,...,16=all)");

#define AR8327_REG_PORT0_STATUS		0x7c
#ifdef CONFIG_AG71XX_SRAM_DESCRIPTORS
#define MAX_AG71XX_USING_SRAM		2
#define MAX_AG71XX_SRAM_RINGS		(MAX_AG71XX_USING_SRAM) * 2
static unsigned long ag71xx_ring_bufs[MAX_AG71XX_SRAM_RINGS] = {
	0x1d000008UL,
	0x1d001008UL,
	0x1d002008UL,
	0x1d003008UL
};
#endif /* CONFIG_AG71XX_SRAM_DESCRIPTORS */

#ifdef CONFIG_ATH79_SOC_QCA9558
static void qca9558_sw_restart(struct ag71xx *ag);
#endif

#ifdef DEBUG
static void ag71xx_dump_dma_regs(struct ag71xx *ag)
{
	DBG("%s: dma_tx_ctrl=%08x, dma_tx_desc=%08x, dma_tx_status=%08x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_TX_CTRL),
		ag71xx_rr(ag, AG71XX_REG_TX_DESC),
		ag71xx_rr(ag, AG71XX_REG_TX_STATUS));

	DBG("%s: dma_rx_ctrl=%08x, dma_rx_desc=%08x, dma_rx_status=%08x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_RX_CTRL),
		ag71xx_rr(ag, AG71XX_REG_RX_DESC),
		ag71xx_rr(ag, AG71XX_REG_RX_STATUS));
}

static void ag71xx_dump_regs(struct ag71xx *ag)
{
	DBG("%s: mac_cfg1=%08x, mac_cfg2=%08x, ipg=%08x, hdx=%08x, mfl=%08x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_MAC_CFG1),
		ag71xx_rr(ag, AG71XX_REG_MAC_CFG2),
		ag71xx_rr(ag, AG71XX_REG_MAC_IPG),
		ag71xx_rr(ag, AG71XX_REG_MAC_HDX),
		ag71xx_rr(ag, AG71XX_REG_MAC_MFL));
	DBG("%s: mac_ifctl=%08x, mac_addr1=%08x, mac_addr2=%08x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_MAC_IFCTL),
		ag71xx_rr(ag, AG71XX_REG_MAC_ADDR1),
		ag71xx_rr(ag, AG71XX_REG_MAC_ADDR2));
	DBG("%s: fifo_cfg0=%08x, fifo_cfg1=%08x, fifo_cfg2=%08x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG0),
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG1),
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG2));
	DBG("%s: fifo_cfg3=%08x, fifo_cfg4=%08x, fifo_cfg5=%08x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG3),
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG4),
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG5));
}

static inline void ag71xx_dump_intr(struct ag71xx *ag, char *label, u32 intr)
{
	DBG("%s: %s intr=%08x %s%s%s%s%s%s\n",
		ag->dev->name, label, intr,
		(intr & AG71XX_INT_TX_PS) ? "TXPS " : "",
		(intr & AG71XX_INT_TX_UR) ? "TXUR " : "",
		(intr & AG71XX_INT_TX_BE) ? "TXBE " : "",
		(intr & AG71XX_INT_RX_PR) ? "RXPR " : "",
		(intr & AG71XX_INT_RX_OF) ? "RXOF " : "",
		(intr & AG71XX_INT_RX_BE) ? "RXBE " : "");
}
#else /* !DEBUG */
#define ag71xx_dump_dma_regs(__ag)
#define ag71xx_dump_regs(__ag)
#define ag71xx_dump_intr(__ag, __label, __intr)
#endif /* DEBUG */

static void ag71xx_ring_free(struct ag71xx_ring *ring)
{
	if (ring->descs_cpu) {
		if (ring->iomem) {
			iounmap(ring->iomem);
		} else {
			dma_free_coherent(NULL, ring->size * ring->desc_size,
					  ring->descs_cpu, ring->descs_dma);
		}
	}
}

static int ag71xx_ring_alloc(struct ag71xx *ag, struct ag71xx_ring *ring,
			     unsigned int id)
{
	int i;

	ring->desc_size = sizeof(struct ag71xx_desc);
#if 0
	if (ring->desc_size % cache_line_size()) {
		DBG("ag71xx: ring %p, desc size %u rounded to %u\n",
			ring, ring->desc_size,
			roundup(ring->desc_size, cache_line_size()));
		ring->desc_size = roundup(ring->desc_size, cache_line_size());
	}
#endif
#ifdef CONFIG_AG71XX_SRAM_DESCRIPTORS
	if (id < MAX_AG71XX_USING_SRAM) {
		DBG("ag71xx: descriptors in SRAM\n");
		ring->iomem = ioremap_nocache(ag71xx_ring_bufs[id], 0x1000);
		if (ring->iomem == NULL)
			return -ENOMEM;

		ring->descs_cpu = (u8 *)ring->iomem;
		ring->descs_dma = ((dma_addr_t)(ring->iomem) & 0x1fffffff);
		goto descs_allocated;
	}
#else
	UNUSED(id);
#endif /* CONFIG_AG71XX_SRAM_DESCRIPTORS */
	ring->iomem = NULL;
	ring->descs_cpu = dma_alloc_coherent(NULL,
					     ring->size * ring->desc_size,
					     &ring->descs_dma,
					     GFP_ATOMIC);
	if (!ring->descs_cpu) {
		return -ENOMEM;
	}

#ifdef CONFIG_AG71XX_SRAM_DESCRIPTORS
descs_allocated:
#endif /* CONFIG_AG71XX_SRAM_DESCRIPTORS */
	/* The even numbered ring at the beginning, odd gets the end */
	if ((id & 0x1) == 0) {
		ring->buf = &ag->ring_bufs[0];
	} else {
		/*
		 * This looks weird but tries very hard to avoid aliasing
		 * problems in the D-cache.
		 */
		unsigned int rings_total;
		rings_total = AG71XX_TX_RING_SIZE_MAX + AG71XX_RX_RING_SIZE_MAX;
		ring->buf = &ag->ring_bufs[rings_total - ring->size];
	}

	for (i = 0; i < ring->size; i++) {
		int idx = i * ring->desc_size;
		ring->buf[i].desc = (struct ag71xx_desc *)&ring->descs_cpu[idx];
		DBG("ag71xx: ring %p, desc %d at %p\n",
			ring, i, ring->buf[i].desc);
	}

	return 0;
}

static void ag71xx_ring_tx_clean(struct ag71xx *ag)
{
	struct ag71xx_ring *ring = &ag->tx_ring;
	struct net_device *dev = ag->dev;
	unsigned int bytes_compl = 0;
	unsigned int pkts_compl = 0;
	struct ag71xx_buf *dirty = ring->dirty;
	unsigned int used = ring->used;

	if (!ring->buf) {
		return;
	}

	while (used) {
		struct ag71xx_desc *desc = dirty->desc;
		struct sk_buff *skb;

		/*
		 * If the descriptor is not marked as empty then mark it as
		 * empty and record a TX error.
		 */
		if (!(desc->ctrl & DESC_EMPTY)) {
			desc->ctrl = DESC_EMPTY;
			dev->stats.tx_errors++;
		}

		skb = dirty->skb;
		dirty->skb = NULL;
		dirty = dirty->next;

		bytes_compl += skb->len;
		pkts_compl++;
		dev_kfree_skb(skb);

		used--;
	}

	ring->dirty = dirty;
	ring->used = used;

	netdev_completed_queue(dev, pkts_compl, bytes_compl);
}

static void ag71xx_ring_tx_init(struct ag71xx *ag)
{
	struct ag71xx_ring *ring = &ag->tx_ring;
	unsigned int mask = ring->mask;
	unsigned int size = ring->size;
	int i, next;

	for (i = 0; i < size; i++) {
		struct ag71xx_buf *buf = &ring->buf[i];
		struct ag71xx_desc *desc = buf->desc;
		
		next = (i == (size - 1)) ? 0 : (i+1);
		desc->next = (u32)(ring->descs_dma + 
						ring->desc_size * next);

		desc->ctrl = DESC_EMPTY;
		buf->skb = NULL;
		buf->next = &ring->buf[next];
	}

	ring->curr = ring->buf;
	ring->dirty = ring->buf;
	ring->used = 0;
	netdev_reset_queue(ag->dev);
}

static void ag71xx_ring_rx_clean(struct ag71xx *ag)
{
	struct ag71xx_ring *ring = &ag->rx_ring;
	struct net_device *dev = ag->dev;
	int i;

	if (!ring->buf) {
		return;
	}

	for (i = 0; i < ring->size; i++) {
		struct ag71xx_buf *buf = &ring->buf[i];
		struct sk_buff *skb = buf->skb;

		if (skb) {
			dma_unmap_single(&dev->dev, buf->dma_addr,
					 ag->rx_buf_size, DMA_FROM_DEVICE);
			dev_kfree_skb(skb);
			buf->skb = NULL;
		}
	}
}

static int ag71xx_ring_rx_init(struct ag71xx *ag)
{
	struct ag71xx_ring *ring = &ag->rx_ring;
	struct net_device *dev = ag->dev;
	unsigned int mask = ring->mask;
	unsigned int size = ring->size;
	unsigned int rx_buf_size = ag->rx_buf_size;
	unsigned int rx_buf_offset = ag->rx_buf_offset;
	unsigned int i, next;

	for (i = 0; i < size; i++) {
		struct ag71xx_buf *buf = &ring->buf[i];
		struct ag71xx_desc *desc = buf->desc;
		struct sk_buff *skb;

		next = (i == (size - 1)) ? 0 : (i+1);
		desc->next = (u32)(ring->descs_dma + 
						ring->desc_size * next);

		skb = dev_alloc_skb(rx_buf_size + rx_buf_offset);
		if (unlikely(!skb)) {
			return -ENOMEM;
		}

		skb_reserve(skb, rx_buf_offset);

		buf->skb = skb;
		buf->next = &ring->buf[next];
		buf->dma_addr = dma_map_single(&dev->dev, skb->data,
					       rx_buf_size, DMA_FROM_DEVICE);

		desc->data = (u32)buf->dma_addr;
		desc->ctrl = DESC_EMPTY;
	}

	ring->curr = ring->buf;
	ring->dirty = ring->buf;
	ring->used = size;

	return 0;
}

static int ag71xx_rings_init(struct ag71xx *ag)
{
	unsigned int rings_total;
	int ret;

	rings_total = AG71XX_TX_RING_SIZE_MAX + AG71XX_RX_RING_SIZE_MAX;
	ag->ring_bufs = kzalloc((rings_total * sizeof(struct ag71xx_buf)),
				GFP_KERNEL);

	if (!ag->ring_bufs)
		return -ENOMEM;

	ret = ag71xx_ring_alloc(ag, &ag->tx_ring, (ag->gmac_num * 2));
	if (ret)
		return ret;

	ag71xx_ring_tx_init(ag);

	ret = ag71xx_ring_alloc(ag, &ag->rx_ring, (ag->gmac_num * 2) + 1);
	if (ret)
		return ret;

	ret = ag71xx_ring_rx_init(ag);
	return ret;
}

static void ag71xx_rings_cleanup(struct ag71xx *ag)
{
	ag71xx_ring_rx_clean(ag);
	ag71xx_ring_free(&ag->rx_ring);

	ag71xx_ring_tx_clean(ag);
	netdev_reset_queue(ag->dev);
	ag71xx_ring_free(&ag->tx_ring);

	if (ag->ring_bufs)
		kfree(ag->ring_bufs);
}

static unsigned char *ag71xx_speed_str(struct ag71xx *ag)
{
	switch (ag->speed) {
	case SPEED_1000:
		return "1000";
	case SPEED_100:
		return "100";
	case SPEED_10:
		return "10";
	}

	return "?";
}

static void ag71xx_hw_set_macaddr(struct ag71xx *ag, unsigned char *mac)
{
	u32 t;

	t = (((u32)mac[5]) << 24) | (((u32)mac[4]) << 16)
	    | (((u32)mac[3]) << 8) | ((u32)mac[2]);

	ag71xx_wr(ag, AG71XX_REG_MAC_ADDR1, t);

	t = (((u32)mac[1]) << 24) | (((u32)mac[0]) << 16);
	ag71xx_wr(ag, AG71XX_REG_MAC_ADDR2, t);
}

static void ag71xx_dma_reset(struct ag71xx *ag)
{
	u32 val;
	int i;

	ag71xx_dump_dma_regs(ag);

	/* stop RX and TX */
	ag71xx_wr(ag, AG71XX_REG_RX_CTRL, 0);
	ag71xx_wr(ag, AG71XX_REG_TX_CTRL, 0);

	/*
	 * give the hardware some time to really stop all rx/tx activity
	 * clearing the descriptors too early causes random memory corruption
	 */
	mdelay(1);

	/* clear descriptor addresses */
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, ag->stop_desc_dma);
	ag71xx_wr(ag, AG71XX_REG_RX_DESC, ag->stop_desc_dma);

	/* clear pending RX/TX interrupts */
	for (i = 0; i < 256; i++) {
		ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_PR);
		ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_PS);
	}

	/* clear pending errors */
	ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_BE | RX_STATUS_OF);
	ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_BE | TX_STATUS_UR);

	val = ag71xx_rr(ag, AG71XX_REG_RX_STATUS);
	if (val)
		pr_alert("%s: unable to clear DMA Rx status: %08x\n",
			 ag->dev->name, val);

	val = ag71xx_rr(ag, AG71XX_REG_TX_STATUS);

	/* mask out reserved bits */
	val &= ~0xff000000;

	if (val)
		pr_alert("%s: unable to clear DMA Tx status: %08x\n",
			 ag->dev->name, val);

	ag71xx_dump_dma_regs(ag);
}

#if defined(CONFIG_AG71XX_DISABLE_GMAC_TXFC)
#define MAC_CFG1_INIT	(MAC_CFG1_RXE | MAC_CFG1_TXE | \
			 MAC_CFG1_SRX | MAC_CFG1_STX | \
			 MAC_CFG1_RFC)
#elif defined(CONFIG_AG71XX_DISABLE_GMAC_RXFC)
#define MAC_CFG1_INIT	(MAC_CFG1_RXE | MAC_CFG1_TXE | \
			 MAC_CFG1_SRX | MAC_CFG1_STX | \
			 MAC_CFG1_TFC)
#else
#define MAC_CFG1_INIT	(MAC_CFG1_RXE | MAC_CFG1_TXE | \
			 MAC_CFG1_SRX | MAC_CFG1_STX | \
			 MAC_CFG1_TFC | MAC_CFG1_RFC)
#endif

#define FIFO_CFG0_INIT	(FIFO_CFG0_ALL << FIFO_CFG0_ENABLE_SHIFT)

#define FIFO_CFG4_INIT	(FIFO_CFG4_DE | FIFO_CFG4_DV | FIFO_CFG4_FC | \
			 FIFO_CFG4_CE | FIFO_CFG4_CR | FIFO_CFG4_LM | \
			 FIFO_CFG4_LO | FIFO_CFG4_OK | FIFO_CFG4_MC | \
			 FIFO_CFG4_BC | FIFO_CFG4_DR | FIFO_CFG4_LE | \
			 FIFO_CFG4_CF | FIFO_CFG4_PF | FIFO_CFG4_UO | \
			 FIFO_CFG4_VT)

#define FIFO_CFG5_INIT	(FIFO_CFG5_DE | FIFO_CFG5_DV | FIFO_CFG5_FC | \
			 FIFO_CFG5_CE | FIFO_CFG5_LO | FIFO_CFG5_OK | \
			 FIFO_CFG5_MC | FIFO_CFG5_BC | FIFO_CFG5_DR | \
			 FIFO_CFG5_CF | FIFO_CFG5_PF | FIFO_CFG5_VT | \
			 FIFO_CFG5_LE | FIFO_CFG5_FT | FIFO_CFG5_16 | \
			 FIFO_CFG5_17 | FIFO_CFG5_SF)

static void ag71xx_hw_stop(struct ag71xx *ag)
{
	/* disable all interrupts and stop the rx/tx engine */
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);

#ifdef CONFIG_ATH79_SOC_QCA9563
	if (pdata->is_qca9561 && ag->phy_dev) {
		//ar8216_phy_write((u32)ag->phy_dev->priv, AR8327_REG_PORT0_STATUS, 0x0);
		u32 value = 0;
		value = ar8216_phy_read((u32)ag->phy_dev->priv, AR8327_REG_PORT0_STATUS);
		value &= (~((1<<2) | (1<<3)));
		ar8216_phy_write((u32)ag->phy_dev->priv, AR8327_REG_PORT0_STATUS, value);
	}
#endif
	ag71xx_wr(ag, AG71XX_REG_MAC_CFG1,0x0);
	ag71xx_wr(ag, AG71XX_REG_INT_ENABLE, 0);
	ag71xx_wr(ag, AG71XX_REG_RX_CTRL, 0);
	ag71xx_wr(ag, AG71XX_REG_TX_CTRL, 0);
}

static void ag71xx_hw_setup(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);

#ifdef CONFIG_ATH79_SOC_QCA9563
	if (pdata->is_qca9561 && ag->phy_dev) {
		//ar8216_phy_write((u32)ag->phy_dev->priv, AR8327_REG_PORT0_STATUS, 0x0);
		u32 value = 0;
		value = ar8216_phy_read((u32)ag->phy_dev->priv, AR8327_REG_PORT0_STATUS);
		value &= (~((1<<2) | (1<<3)));
		ar8216_phy_write((u32)ag->phy_dev->priv, AR8327_REG_PORT0_STATUS, value);
	}
#endif

	/* setup MAC configuration registers */
	ag71xx_wr(ag, AG71XX_REG_MAC_CFG1, 0x0);

	ag71xx_sb(ag, AG71XX_REG_MAC_CFG2,
		  MAC_CFG2_PAD_CRC_EN | MAC_CFG2_LEN_CHECK);

	/* setup max frame length */
	if(ag->dev->mtu < AG71XX_TX_MTU_LEN)
		ag71xx_wr(ag, AG71XX_REG_MAC_MFL, AG71XX_TX_MTU_LEN);
	else
		ag71xx_wr(ag, AG71XX_REG_MAC_MFL, ag->dev->mtu);

	/* setup FIFO configuration registers */
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG0, FIFO_CFG0_INIT);
	if (pdata->is_ar724x) {
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG1, pdata->fifo_cfg1);
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG2, pdata->fifo_cfg2);
	} else {
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG1, 0x0fff0000);
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG2, 0x00001fff);
	}
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG4, FIFO_CFG4_INIT);
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG5, FIFO_CFG5_INIT);
}

static void ag71xx_hw_init(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	u32 reset_mask = pdata->reset_bit;

	ag71xx_hw_stop(ag);

	if (pdata->is_ar724x) {
		u32 reset_phy = reset_mask;

		reset_phy &= AR71XX_RESET_GE0_PHY | AR71XX_RESET_GE1_PHY;
		reset_mask &= ~(AR71XX_RESET_GE0_PHY | AR71XX_RESET_GE1_PHY);

		ath79_device_reset_set(reset_phy);
		mdelay(50);
		ath79_device_reset_clear(reset_phy);
		mdelay(200);
	}

	ag71xx_sb(ag, AG71XX_REG_MAC_CFG1, MAC_CFG1_SR);
	udelay(20);

	ath79_device_reset_set(reset_mask);
	mdelay(100);
	ath79_device_reset_clear(reset_mask);
	mdelay(200);

	ag71xx_hw_setup(ag);

	ag71xx_dma_reset(ag);
}

static void ag71xx_fast_reset(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	struct net_device *dev = ag->dev;
	u32 reset_mask = pdata->reset_bit;
	u32 rx_ds, tx_ds;
	u32 mii_reg;

	reset_mask &= AR71XX_RESET_GE0_MAC | AR71XX_RESET_GE1_MAC;

	mii_reg = ag71xx_rr(ag, AG71XX_REG_MII_CFG);
	rx_ds = ag71xx_rr(ag, AG71XX_REG_RX_DESC);
	tx_ds = ag71xx_rr(ag, AG71XX_REG_TX_DESC);

	ath79_device_reset_set(reset_mask);
	udelay(10);
	ath79_device_reset_clear(reset_mask);
	udelay(10);

	ag71xx_dma_reset(ag);
	ag71xx_hw_setup(ag);

	ag71xx_wr(ag, AG71XX_REG_RX_DESC, rx_ds);
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, tx_ds);
	ag71xx_wr(ag, AG71XX_REG_MII_CFG, mii_reg);

	ag71xx_hw_set_macaddr(ag, dev->dev_addr);
}

static void ag71xx_hw_start(struct ag71xx *ag)
{

	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	/* start RX engine */
	ag71xx_wr(ag, AG71XX_REG_RX_CTRL, RX_CTRL_RXE);

	/* enable interrupts */
	ag71xx_wr(ag, AG71XX_REG_INT_ENABLE, AG71XX_INT_INIT);

#ifdef CONFIG_ATH79_SOC_QCA9563
	if(pdata->is_qca9561 &&  ag->phy_dev) {
		/* Enable Switch Mac0's - tx,rx,flowctrl,duplx ,speed */
		//ar8216_phy_write((u32)ag->phy_dev->priv, AR8327_REG_PORT0_STATUS, 0xfe);
		u32 value = 0;
		value = ar8216_phy_read((u32)ag->phy_dev->priv, AR8327_REG_PORT0_STATUS);
		value |= 0xfe;
		ar8216_phy_write((u32)ag->phy_dev->priv, AR8327_REG_PORT0_STATUS, value);
	}
#endif

	ag71xx_wr(ag, AG71XX_REG_MAC_CFG1, MAC_CFG1_INIT);
}

#ifdef CONFIG_ATH79_SOC_QCA9558

/**********************************************************
* FUNCTION		: qca9558_sw_restart()
* AUTHOR		: liyi<liyi@tp-link.net>
* DESCRIPTION	: use qca9558 to restart switch(ar8327n) 
* INPUT			: ag71xx structure pointer
* OUTPUT		: N/A
* RETURN		: N/A
* OTHERS		: 
***********************************************************/
static void qca9558_sw_restart(struct ag71xx *ag)
{
/* 
 * The QCA9558 chip can't access its MII register through GMAC1,
 * in its datasheet writes "All MAC/PHY registers are accessed via  
 * the MII address and MII control registers of GMAC0 only. GMAC1 MII 
 * address and control registers are not used. The details of the 
 * Ethernet MAC/PHY that are accessible through the MAC0 MII address"
 * so here the GMAC0's(usually means eth0, whose phy_dev is not null)
 * ag71xx structure is restored in ag71xx_gmac0_ag variable and is used 
 * when eth1(whose phy_dev is null) need to be resetted, which means to
 * restart eth1-related switch ports.
 * comment by liyi<liyi@tp-link.net>
 */
	struct phy_device *phydev = NULL;
	u16 i = 0;

	if (ag71xx_gmac0_ag && ag71xx_gmac1_ag && (ag == ag71xx_gmac1_ag))
	{
		phydev = ag71xx_gmac0_ag->phy_dev;
	if (!phydev) {
		pr_debug("phydev is null!\n");
		return;
	}

	/* 1 2 3 4 are regnum of phys in lan switch, 0 is wan port */
	for (i = 1; i < AR8327_PHY_NUM; ++i) {
			qca9558_phy_write(phydev, MII_BMCR, BMCR_RESET | BMCR_ANENABLE, i);
	}

	}
}
#endif

static int ag71xx_change_vlan_phylink(struct net_device* dev, int vid, bool linkup)
{
	int ret = 0;
	struct ag71xx *ag = NULL;

	/* do sanity check */
	if (NULL == dev || (vid != 1 && vid != 2) || (linkup != 0 && linkup != 1))
	{
		return -1;
	}
	ag = netdev_priv(dev);

	if (NULL == ag->phy_dev)
	{
		return 0;
	}

#if defined(CONFIG_ATH79_SOC_QCA9563)
	ret = ar8216_change_vlan_phylink(ag->phy_dev, vid, linkup);
#else
	// built-in switch not implemented
#endif

	return ret;
}

static void ag71xx_disable_inline_chksum_engine(struct ag71xx *ag)
{
	void __iomem *dam = ioremap_nocache(QCA956X_DAM_RESET_OFFSET,
			QCA956X_DAM_RESET_SIZE);
	if (!dam) {
		dev_err(&ag->dev, "unable to ioremap DAM_RESET_OFFSET\n");
	} else {
		/*
		 * can not use the wr, rr functions since this is outside of
		 * the normal ag71xx register block
		 */
		__raw_writel(__raw_readl(dam) & ~QCA956X_INLINE_CHKSUM_ENG, dam);
		(void)__raw_readl(dam);
		iounmap(dam);
	}
}

void ag71xx_link_adjust(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	u32 cfg2;
	u32 ifctl;
	u32 fifo5;

	if (!ag->link) {
		
		/* stop queue first in case of tx timeout,add by Wu Yin, 10Oct15 */
		ag->tx_stopped = true;
		netif_stop_queue(ag->dev);

		ag71xx_hw_stop(ag);
		netif_carrier_off(ag->dev);
		if (netif_msg_link(ag))
			pr_info("%s: link down\n", ag->dev->name);
		return;
	}

	if (!pdata->is_qca9561 && pdata->is_ar724x)
		ag71xx_fast_reset(ag);

	cfg2 = ag71xx_rr(ag, AG71XX_REG_MAC_CFG2);
	cfg2 &= ~(MAC_CFG2_IF_1000 | MAC_CFG2_IF_10_100 | MAC_CFG2_FDX);
	cfg2 |= (ag->duplex) ? MAC_CFG2_FDX : 0;

	ifctl = ag71xx_rr(ag, AG71XX_REG_MAC_IFCTL);
	ifctl &= ~(MAC_IFCTL_SPEED);

	fifo5 = ag71xx_rr(ag, AG71XX_REG_FIFO_CFG5);
	fifo5 &= ~FIFO_CFG5_BM;

#ifdef CONFIG_ATH79_SOC_QCA9558
	/* always 1000MF */
	cfg2 |= MAC_CFG2_IF_1000;
	fifo5 |= FIFO_CFG5_BM;
#else
	switch (ag->speed) {
	case SPEED_1000:
		cfg2 |= MAC_CFG2_IF_1000;
		fifo5 |= FIFO_CFG5_BM;
		break;
	case SPEED_100:
		cfg2 |= MAC_CFG2_IF_10_100;
		ifctl |= MAC_IFCTL_SPEED;
		break;
	case SPEED_10:
		cfg2 |= MAC_CFG2_IF_10_100;
		break;
	default:
		BUG();
		return;
	}
#endif

	if (pdata->is_ar91xx)
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG3, 0x00780fff);
	else if (pdata->is_ar724x)
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG3, pdata->fifo_cfg3);
	else
		ag71xx_wr(ag, AG71XX_REG_FIFO_CFG3, 0x008001ff);

	if (pdata->set_speed)
	{
		pdata->set_speed(ag->speed);
	}

	ag71xx_wr(ag, AG71XX_REG_MAC_CFG2, cfg2);
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG5, fifo5);
	ag71xx_wr(ag, AG71XX_REG_MAC_IFCTL, ifctl);

#ifndef CONFIG_ATH79_SOC_QCA9558
	if (pdata->is_qca956x) {
		ag71xx_disable_inline_chksum_engine(ag);
	}
#endif

	ag71xx_hw_start(ag);

	/* add by Wu Yin, 10Oct15 */
	netif_start_queue(ag->dev);
	ag->tx_stopped = false;

	netif_carrier_on(ag->dev);
#ifndef CONFIG_ATH79_SOC_QCA9563
	if (netif_msg_link(ag))
		pr_info("%s: link up (%sMbps/%s duplex)\n",
			ag->dev->name,
			ag71xx_speed_str(ag),
			(DUPLEX_FULL == ag->duplex) ? "Full" : "Half");
#endif
	DBG("%s: fifo_cfg0=%#x, fifo_cfg1=%#x, fifo_cfg2=%#x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG0),
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG1),
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG2));

	DBG("%s: fifo_cfg3=%#x, fifo_cfg4=%#x, fifo_cfg5=%#x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG3),
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG4),
		ag71xx_rr(ag, AG71XX_REG_FIFO_CFG5));

	DBG("%s: mac_cfg2=%#x, mac_ifctl=%#x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_MAC_CFG2),
		ag71xx_rr(ag, AG71XX_REG_MAC_IFCTL));
}

static int ag71xx_open(struct net_device *dev)
{
	struct ag71xx *ag = netdev_priv(dev);
	int ret;

#ifdef CONFIG_TP_FLASH_VERIFY
	/* disable wan port when flash verify failed */
	if (flash_verify_result() != 0  && !strncmp(dev->name, WAN_DEV_NAME, IFNAMSIZ))
	{
		return -1;
	}
#endif

	/*
	 * Compute the RX buffer size.
	 */
	if (dev->mtu > AG71XX_TX_MTU_LEN) {
		ag->rx_buf_size = dev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN + NET_SKB_PAD + NET_IP_ALIGN;
	} else {
		ag->rx_buf_size = AG71XX_RX_BUF_SIZE;
	}

	/*
	 * Compute the RX buffer offset.  On AR71xx/AR91xx packets must be
	 * 4-byte aligned.
	 *
	 * When using builtin AR8216 support, hardware adds a 2-byte header,
	 * so we don't need any extra alignment in that case.
	 */
	if (!ag71xx_get_pdata(ag)->is_ar724x || ag71xx_has_ar8216(ag)) {
		ag->rx_buf_offset = AG71XX_HACK_WIFI_HEADROOM;
	} else {
		ag->rx_buf_offset = AG71XX_HACK_WIFI_HEADROOM + NET_IP_ALIGN;
	}

	ret = ag71xx_rings_init(ag);
	if (ret) {
		ag71xx_rings_cleanup(ag);
		return ret;
	}

	napi_enable(&ag->napi);

	netif_carrier_off(dev);
	ag71xx_phy_start(ag);

	ag71xx_wr(ag, AG71XX_REG_TX_DESC, ag->tx_ring.descs_dma);
	ag71xx_wr(ag, AG71XX_REG_RX_DESC, ag->rx_ring.descs_dma);

	ag71xx_hw_set_macaddr(ag, dev->dev_addr);

	netif_start_queue(dev);
	ag->tx_stopped = false;

	return 0;
}

static int ag71xx_stop(struct net_device *dev)
{
	struct ag71xx *ag = netdev_priv(dev);
	unsigned long flags;

	netif_carrier_off(dev);
	ag71xx_phy_stop(ag);

	spin_lock_irqsave(&ag->lock, flags);

	ag->tx_stopped = true;
	netif_stop_queue(dev);
	
#ifdef CONFIG_ATH79_SOC_QCA9558
	qca9558_sw_restart(ag);
#endif

	ag71xx_hw_stop(ag);
	ag71xx_dma_reset(ag);

	napi_disable(&ag->napi);

	spin_unlock_irqrestore(&ag->lock, flags);

	ag71xx_rings_cleanup(ag);

	return 0;
}

static netdev_tx_t ag71xx_hard_start_xmit(struct sk_buff *skb,
					  struct net_device *dev)
{
	struct ag71xx *ag = netdev_priv(dev);
	struct ag71xx_ring *ring = &ag->tx_ring;
	struct ag71xx_buf *curr = ring->curr;
	struct ag71xx_desc *desc = curr->desc;
	unsigned int used = ring->used;
	unsigned int size = ring->size;
	unsigned int len;
	dma_addr_t dma_addr;

	/*
	 * We shouldn't ever see our ring fully used and reach here but just in case!
	 */
	if (unlikely(used == size)) {
		DBG("%s: tx queue full\n", dev->name);
		ag->tx_stopped = true;
		netif_stop_queue(dev);
		goto err_drop;
	}

	if (unlikely(ag71xx_has_ar8216(ag))) {
		ag71xx_add_ar8216_header(ag, skb);
	}

	len = skb->len;
	if (unlikely(len <= 0)) {
		DBG("%s: packet len is too small\n", dev->name);
		goto err_drop;
	}

	netdev_sent_queue(dev, len);
	curr->skb = skb;
	curr->len = len;

	dma_addr = dma_map_single(&dev->dev, skb->data, len, DMA_TO_DEVICE);

	/* setup descriptor fields */
	desc->data = (u32)dma_addr;
	ag71xx_get_pdata(ag)->ddr_flush();
	desc->ctrl = len & DESC_PKTLEN_M;

	curr = curr->next;
	ring->curr = curr;

	used++;
	ring->used = used;

	/*
	 * If our transmit ring is full then stop transmitting.
	 */
	if (unlikely(used == size)) {
		DBG("%s: tx queue full\n", ag->dev->name);
		ag->tx_stopped = true;
		netif_stop_queue(dev);
	}

	DBG("%s: packet injected into TX queue\n", ag->dev->name);

	dev->trans_start = jiffies;

	wmb();
	/* enable TX engine */
	ag71xx_wr_fast(ag->tx_ctrl_reg, TX_CTRL_TXE);
	ag71xx_wr_flush(ag->tx_ctrl_reg);

	return NETDEV_TX_OK;

err_drop:
	dev->stats.tx_dropped++;

	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}

static int ag71xx_do_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct ag71xx *ag = netdev_priv(dev);
	int ret;

	switch (cmd) {
	case SIOCETHTOOL:
		if (ag->phy_dev == NULL)
			break;

		spin_lock_irq(&ag->lock);
		ret = phy_ethtool_ioctl(ag->phy_dev, (void *) ifr->ifr_data);
		spin_unlock_irq(&ag->lock);
		return ret;

	case SIOCSIFHWADDR:
		if (copy_from_user
			(dev->dev_addr, ifr->ifr_data, sizeof(dev->dev_addr)))
			return -EFAULT;
		return 0;

	case SIOCGIFHWADDR:
		if (copy_to_user
			(ifr->ifr_data, dev->dev_addr, sizeof(dev->dev_addr)))
			return -EFAULT;
		return 0;

	case SIOCGMIIPHY:
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		if (ag->phy_dev == NULL)
			break;

		return phy_mii_ioctl(ag->phy_dev, ifr, cmd);
/*BEGIN: Add For ethreg*/
	case ATHR_GMAC_CTRL_IOC:
         ret = ag71xx_gmac_ctrl(dev,ifr,cmd);
         return 0;
  

	case ATHR_PHY_CTRL_IOC:
         ret = ag71xx_phy_ctrl(dev,ifr,cmd);
         return 0;

	case ATHR_MII_CTRL_IOC:
		 ret = ag71xx_mii_ctrl(dev, ifr, cmd);
		 return 0;
/*END: Add for ethreg*/
	default:
		break;
	}

	return -EOPNOTSUPP;
}

static void ag71xx_tx_timeout(struct net_device *dev)
{
	struct ag71xx *ag = netdev_priv(dev);

	if (netif_msg_tx_err(ag))
		pr_info("%s: tx timeout\n", ag->dev->name);

	schedule_work(&ag->restart_work);
}

static void ag71xx_restart_work_func(struct work_struct *work)
{
	struct ag71xx *ag = container_of(work, struct ag71xx, restart_work);

/* go heavy reset, modified by Wu Yin, 10Oct15 */
#if 0
	if (ag71xx_get_pdata(ag)->is_ar724x) {
		ag->link = 0;
		ag71xx_link_adjust(ag);
		return;
	}
#endif

	ag71xx_stop(ag->dev);
	ag71xx_open(ag->dev);
}

static bool ag71xx_check_dma_stuck(struct ag71xx *ag, struct net_device *dev)
{
	u32 rx_sm, tx_sm, rx_fd;

	if (likely(time_before(jiffies, dev->trans_start + HZ / 10)))
		return false;

	if (!netif_carrier_ok(dev))
		return false;

	rx_sm = ag71xx_rr(ag, AG71XX_REG_RX_SM);
	if ((rx_sm & 0x7) == 0x3 && ((rx_sm >> 4) & 0x7) == 0x6)
		return true;

	tx_sm = ag71xx_rr(ag, AG71XX_REG_TX_SM);
	rx_fd = ag71xx_rr(ag, AG71XX_REG_FIFO_DEPTH);
	if (((tx_sm >> 4) & 0x7) == 0 && ((rx_sm & 0x7) == 0) &&
	    ((rx_sm >> 4) & 0x7) == 0 && rx_fd == 0)
		return true;

	return false;
}

static int ag71xx_tx_packets(struct ag71xx *ag, struct net_device *dev,
			     bool is_ar7240)
{
	struct ag71xx_ring *ring = &ag->tx_ring;
	unsigned int sent = 0;
	unsigned int bytes_compl = 0;
	struct ag71xx_buf *dirty = ring->dirty;
	struct ag71xx_desc *desc;
	unsigned int used = ring->used;
	struct sk_buff *skb;

	DBG("%s: processing TX ring\n", dev->name);

	/*
	 * If we haven't transmitted anything then we're done!
	 */
	if (!used)
		return sent;

	/*
	 * Start by looking at the SKB that will be up next.
	 */
	skb = dirty->skb;
	desc = dirty->desc;

	do {
		struct sk_buff *next_skb;

		if (unlikely(!(desc->ctrl & DESC_EMPTY))) {
			if (is_ar7240) {
				if (unlikely(ag71xx_check_dma_stuck(ag, dev))) {
					schedule_work(&ag->restart_work);
				}
			}
			break;
		}

		sent++;
		bytes_compl += dirty->len;

		dirty->skb = NULL;
		dirty = dirty->next;
		next_skb = dirty->skb;
		desc = dirty->desc;

		/*
		 * There's a good chance that the next SKB may be cold in
		 * the cache so try to give some help.
		 */
		if (likely(next_skb)) {
			prefetch(skb_shinfo(next_skb));
			prefetch(&next_skb->users);
		}

		ag71xx_wr_fast(ag->tx_status_reg, TX_STATUS_PS);

		dev_kfree_skb(skb);

		skb = next_skb;

		used--;
	} while (used);

	ag71xx_wr_flush(ag->tx_status_reg);

	ring->dirty = dirty;
	ring->used = used;

	dev->stats.tx_bytes += bytes_compl;
	dev->stats.tx_packets += sent;

	DBG("%s: %u packets sent out\n", dev->name, sent);

	/*
	 * Mark the amount of work we've done.
	 */
	netdev_completed_queue(dev, sent, bytes_compl);

	/*
	 * If our transmit queue was previously stopped because we'd run out
	 * of space and we've now successfully freed some space then restart
	 * the transmit queue again.
	 */
	if (unlikely(ag->tx_stopped) && sent) {
		netif_wake_queue(dev);
		ag->tx_stopped = false;
	}

	return sent;
}

static int ag71xx_rx_packets(struct ag71xx *ag, struct net_device *dev, int limit)
{
	struct ag71xx_ring *ring = &ag->rx_ring;
	struct ag71xx_buf *curr = ring->curr;
	struct ag71xx_desc *desc = curr->desc;
	unsigned int rx_buf_size = ag->rx_buf_size;
	unsigned int rx_buf_offset = ag->rx_buf_offset;
	int received = 0;
	struct sk_buff *skb;
	bool has_ar8216;

	has_ar8216 = ag71xx_has_ar8216(ag);

	/*
	 * Start by looking at the SKB that will be up next.
	 */
	skb = curr->skb;

	/*
	 * Process newly received packets.
	 */
	do {
		u32 desc_ctrl;
		struct sk_buff *next_skb;
		struct sk_buff *new_skb;
		int pktlen;

		/*
		 * Is our descriptor marked as empty?  If it is then we're done.
		 */
		desc_ctrl = desc->ctrl;
		ag71xx_get_pdata(ag)->ddr_flush();
		if (unlikely(desc_ctrl & DESC_EMPTY)) {
			//break;
			/* enable this WAR only for AP152 which has only one gmac */
			if (ag71xx_get_pdata(ag)->is_qca9561 && (ag71xx_gmac_num == 1)) {
				u32 rx_status = ag71xx_rr_fast(ag->rx_status_reg);
				if ((((rx_status >> 16) & 0xff) > 1) && (desc->ctrl & DESC_EMPTY)) {
					while (desc->ctrl & DESC_EMPTY) {
						curr = curr->next;
						desc = curr->desc;
						skb = curr->skb;
					}
				} else
					break;
			} else
			break;
		}

		/*
		 * Speed up eth_type_trans() since it will inspect the packet
		 * payload and write the protocol.  Strictly speaking this is a
		 * little premature as the next SKB alloc could fail but in
		 * practice it never will so this is good :-)
		 */
		prefetch(skb->data);
		prefetch(&skb->protocol);

		/*
		 * When we receive a packet we also allocate a new buffer.  If
		 * for some reason we can't allocate the buffer then we're not
		 * going to try to process the received buffer yet either.
		 */
		new_skb = dev_alloc_skb(rx_buf_size + rx_buf_offset);
		if (unlikely(!new_skb)) {
			break;
		}

		skb_reserve(new_skb, rx_buf_offset);

		/*
		 * This is where we'd unmap our buffer from the GMAC in a
		 * general use of the DMA API.  On a MIPS platform this would
		 * be a complete no-op so we don't bother:
		 *
		 * dma_unmap_single(&dev->dev, curr->dma_addr,
		 *		    rx_buf_size, DMA_FROM_DEVICE);
		 */

		/*
		 * Update the descriptor records to account for the new SKB.
		 */
		curr->skb = new_skb;
		curr->dma_addr = dma_map_single(&dev->dev, new_skb->data,
						rx_buf_size, DMA_FROM_DEVICE);

		desc->data = (u32)curr->dma_addr;
		wmb();
		desc->ctrl = DESC_EMPTY;

		/*
		 * Move forward to what will be the next RX descriptor.
		 */
		curr = curr->next;
		next_skb = curr->skb;
		desc = curr->desc;

		/*
		 * Our next skb is almost certainly cold in the cache as we last
		 * saw it when we replenished this slot.  We'll take cache
		 * misses on almost every access.  Try to mitigate this by
		 * issuing some prefetches.
		 *
		 * Note that what we're prefetching here are the fields that
		 * we'll need within the next iteration of this function.
		 */
		if (likely(next_skb)) {
			/*
			 * For a MIPS platform we shouldn't issue more than 3
			 * prefetches at a time.
			 */
			prefetch(&next_skb->data);
			prefetch(&next_skb->tail);
			prefetch(&next_skb->len);
		}

		/*
		 * Notify the GMAC that we received the packet.
		 */
		ag71xx_wr_fast(ag->rx_status_reg, RX_STATUS_PR);

		/*
		 * Determine the size of the packet we just received.
		 */
		pktlen = desc_ctrl & DESC_PKTLEN_M;
		pktlen -= ETH_FCS_LEN;

		/*
		 * Update device stats.
		 */
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += pktlen;

		/*
		 * Set up the length of the skb.
		 */
		skb->tail += pktlen;
		skb->len += pktlen;

		if (unlikely(has_ar8216)) {
			int err = ag71xx_remove_ar8216_header(ag, skb, pktlen);
			if (err) {
				dev->stats.rx_dropped++;
				dev_kfree_skb(skb);
				goto next;
			}
		}

		skb->protocol = eth_type_trans(skb, dev);
		skb_checksum_none_assert(skb);
		netif_receive_skb(skb);

next:
		skb = next_skb;
		received++;
	} while (received < limit);

	ag71xx_wr_flush(ag->rx_status_reg);

	ring->curr = curr;
	return received;
}

static int ag71xx_poll(struct napi_struct *napi, int limit)
{
	struct ag71xx *ag = container_of(napi, struct ag71xx, napi);
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	struct net_device *dev = ag->dev;
	unsigned long flags;
	u32 status;
	int tx_done;
	int rx_done;

	//pdata->ddr_flush();

	/*
	 * First empty any packets that we have transmitted!  In theory it might
	 * seem better to handle packets that we've received but we
	 * really want to get packets that completed TX to be used to replenish
	 * the RX descriptor ring and keeping those two operations adjacent
	 * will help keep any recycled skbs hotter in the D-cache.
	 */
	tx_done = ag71xx_tx_packets(ag, dev, pdata->is_ar7240);
	rx_done = ag71xx_rx_packets(ag, dev, limit);

	ag71xx_debugfs_update_napi_stats(ag, rx_done, tx_done);

	status = ag71xx_rr_fast(ag->rx_status_reg);
	if (unlikely(status & RX_STATUS_OF)) {
		ag71xx_wr_fast(ag->rx_status_reg, RX_STATUS_OF);
		ag71xx_wr_flush(ag->rx_status_reg);
		dev->stats.rx_fifo_errors++;

		/* restart RX */
		ag71xx_wr_fast(ag->rx_ctrl_reg, RX_CTRL_RXE);
		ag71xx_wr_flush(ag->rx_ctrl_reg);
	}

	if (rx_done < limit) {
		DBG("%s: disable polling mode, rx=%d, tx=%d,limit=%d\n",
			dev->name, rx_done, tx_done, limit);

		napi_complete(napi);

		/* enable interrupts */
		spin_lock_irqsave(&ag->lock, flags);
		ag71xx_int_enable(ag, AG71XX_INT_POLL);
		spin_unlock_irqrestore(&ag->lock, flags);
		return rx_done;
	}

more:
	DBG("%s: stay in polling mode, rx=%d, tx=%d, limit=%d\n",
			dev->name, rx_done, tx_done, limit);
	return rx_done;
}

static irqreturn_t ag71xx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct ag71xx *ag = netdev_priv(dev);
	u32 status;

	status = ag71xx_rr_fast(ag->int_status_reg);
	ag71xx_dump_intr(ag, "raw", status);

	if (unlikely(!status))
		return IRQ_NONE;

	if (unlikely(status & AG71XX_INT_ERR)) {
		if (status & AG71XX_INT_TX_BE) {
			ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_BE);
			dev_err(&dev->dev, "TX BUS error\n");
		}
		if (status & AG71XX_INT_RX_BE) {
			ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_BE);
			dev_err(&dev->dev, "RX BUS error\n");
		}
	}

	if (likely(status & AG71XX_INT_POLL)) {
		ag71xx_int_disable(ag, AG71XX_INT_POLL);
		DBG("%s: enable polling mode\n", dev->name);
		napi_schedule(&ag->napi);
	}

	ag71xx_debugfs_update_int_stats(ag, status);

	return IRQ_HANDLED;
}

#ifdef CONFIG_NET_POLL_CONTROLLER
/*
 * Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable interrupts. It's not called while
 * the interrupt routine is executing.
 */
static void ag71xx_netpoll(struct net_device *dev)
{
	disable_irq(dev->irq);
	ag71xx_interrupt(dev->irq, dev);
	enable_irq(dev->irq);
}
#endif
static int ag71xx_change_mtu(struct net_device *dev, int new_mtu)
{
	int ret;

	if (new_mtu < 68 || new_mtu > AG71XX_JUMBO_LEN)
		return -EINVAL;

	if (!netif_running(dev)) {
		dev->mtu = new_mtu;
		return 0;
	}

	ag71xx_stop(dev);
	printk("%s:%s new_mtu is %d\n",__func__,dev->name,new_mtu);

	dev->mtu = new_mtu;

	ret = ag71xx_open(dev);
	if (ret)
		dev_close(dev);

	return ret;
}

static const struct net_device_ops ag71xx_netdev_ops = {
	.ndo_open		= ag71xx_open,
	.ndo_stop		= ag71xx_stop,
	.ndo_start_xmit		= ag71xx_hard_start_xmit,
	.ndo_do_ioctl		= ag71xx_do_ioctl,
	.ndo_tx_timeout		= ag71xx_tx_timeout,
	.ndo_change_mtu		= ag71xx_change_mtu,
	.ndo_set_mac_address	= eth_mac_addr,
	.ndo_validate_addr	= eth_validate_addr,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller	= ag71xx_netpoll,
#endif
	/*.ndo_vlan_change_phylink	= ag71xx_change_vlan_phylink,*/
};

#ifdef CONFIG_OF
static void ag71xx_of_gmac_setup(struct platform_device *pdev, u32 mask)
{
	struct resource *res;
	void __iomem *cfg_base;

	if (!(res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "cfg_base")))
		return;

	cfg_base = ioremap_nocache(res->start, res->end - res->start + 1);
	if (!cfg_base) {
		dev_err(&pdev->dev, "unable to ioremap cfg_base\n");
		return;
	}

	__raw_writel(__raw_readl(cfg_base) | mask, cfg_base);
	/* flush write */
	(void)__raw_readl(cfg_base);

	iounmap(cfg_base);
}

static int ag71xx_of_pdata_update(struct platform_device *pdev)
{
	u32 value[4];
	const phandle *ph;
	struct device_node *mdio;
	struct platform_device *pdev_mdio;
	struct ag71xx_platform_data *pdata = pdev->dev.platform_data;

	if (!pdev->dev.of_node)
		return -EINVAL;

	ph = of_get_property(pdev->dev.of_node, "mdio-handle", NULL);
	if (!ph) {
		dev_err(&pdev->dev, "No mdio-handle in dtb\n");
		return -EINVAL;
	}

	mdio = of_find_node_by_phandle(*ph);
	if (!mdio) {
		dev_err(&pdev->dev, "No mdio device found by phandle\n");
		return -EINVAL;
	}

	pdev_mdio = of_find_device_by_node(mdio);
	pdata->mii_bus_dev = &pdev_mdio->dev;
	of_node_put(mdio);

	if (!of_property_read_u32(pdev->dev.of_node, "eth-cfg", &value[0]))
		ag71xx_of_gmac_setup(pdev, value[0]);

	if (pdata->update_pll &&
			!of_property_read_u32_array(pdev->dev.of_node, "eth-pll-data", value, 3))
		pdata->update_pll(value[0], value[1], value[2]);

	if (!of_property_read_u32_array(pdev->dev.of_node, "eth-phy-cfg", value, 4)) {
		pdata->phy_if_mode = value[0];
		pdata->phy_mask = value[1];
		pdata->speed = value[2];
		pdata->duplex = value[3];
	}

	if (!of_property_read_u32_array(pdev->dev.of_node, "eth-fifo-cfg", value, 3)) {
		pdata->fifo_cfg1 = value[0];
		pdata->fifo_cfg2 = value[1];
		pdata->fifo_cfg3 = value[2];
	}

	if (pdata->switch_data &&
			!of_property_read_u32_array(pdev->dev.of_node, "eth-sw-cfg", value, 2)) {
		pdata->switch_data->phy4_mii_en = value[0];
		pdata->switch_data->phy_poll_mask = value[1];
	}

	return 0;
}
#else
static int ag71xx_of_pdata_update(struct platform_device *pdev)
{
	return -EINVAL;
}
#endif

static int __devinit ag71xx_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct resource *res;
	struct ag71xx *ag;
	struct ag71xx_desc *ag_stop_desc;
	struct ag71xx_platform_data *pdata;
	int err;

	pdata = pdev->dev.platform_data;
	if (!pdata) {
		dev_err(&pdev->dev, "no platform data specified\n");
		err = -ENXIO;
		goto err_out;
	}

	if (pdata->mii_bus_dev == NULL &&
		ag71xx_of_pdata_update(pdev))
	{
		dev_err(&pdev->dev, "no MII bus device specified\n");
		err = -EINVAL;
		goto err_out;
	}

	dev = alloc_etherdev(sizeof(*ag));
	if (!dev) {
		dev_err(&pdev->dev, "alloc_etherdev failed\n");
		err = -ENOMEM;
		goto err_out;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);

	ag = netdev_priv(dev);
	ag->pdev = pdev;
	ag->dev = dev;
	ag->msg_enable = netif_msg_init(ag71xx_msg_level,
					AG71XX_DEFAULT_MSG_ENABLE);
	ag->gmac_num = ag71xx_gmac_num++;
	spin_lock_init(&ag->lock);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mac_base");
	if (!res) {
		dev_err(&pdev->dev, "no mac_base resource found\n");
		err = -ENXIO;
		goto err_out;
	}

	ag->mac_base = ioremap_nocache(res->start, res->end - res->start + 1);
	if (!ag->mac_base) {
		dev_err(&pdev->dev, "unable to ioremap mac_base\n");
		err = -ENOMEM;
		goto err_free_dev;
	}

	ag->rx_ctrl_reg = ag->mac_base + AG71XX_REG_RX_CTRL;
	ag->rx_status_reg = ag->mac_base + AG71XX_REG_RX_STATUS;
	ag->tx_ctrl_reg = ag->mac_base + AG71XX_REG_TX_CTRL;
	ag->tx_status_reg = ag->mac_base + AG71XX_REG_TX_STATUS;
	ag->int_status_reg = ag->mac_base + AG71XX_REG_INT_STATUS;

	dev->irq = platform_get_irq(pdev, 0);
	err = request_irq(dev->irq, ag71xx_interrupt,
			  IRQF_DISABLED,
			  dev->name, dev);
	if (err) {
		dev_err(&pdev->dev, "unable to request IRQ %d\n", dev->irq);
		goto err_unmap_base;
	}

	dev->base_addr = (unsigned long)ag->mac_base;
	dev->netdev_ops = &ag71xx_netdev_ops;
	dev->ethtool_ops = &ag71xx_ethtool_ops;

	INIT_WORK(&ag->restart_work, ag71xx_restart_work_func);

	ag->tx_ring.size = AG71XX_TX_RING_SIZE_DEFAULT;
	ag->tx_ring.mask = AG71XX_TX_RING_SIZE_DEFAULT - 1;
	ag->rx_ring.size = AG71XX_RX_RING_SIZE_DEFAULT;
	ag->rx_ring.mask = AG71XX_RX_RING_SIZE_DEFAULT - 1;

	ag_stop_desc = dma_alloc_coherent(NULL,
		sizeof(struct ag71xx_desc), &ag->stop_desc_dma, GFP_KERNEL);

	if (!ag_stop_desc)
		goto err_free_irq;

	ag_stop_desc->data = 0;
	ag_stop_desc->ctrl = 0;
	ag_stop_desc->next = (u32)ag->stop_desc_dma;
	ag->stop_desc = ag_stop_desc;

	memcpy(dev->dev_addr, pdata->mac_addr, ETH_ALEN);

	netif_napi_add(dev, &ag->napi, ag71xx_poll, AG71XX_NAPI_WEIGHT);

	err = register_netdev(dev);
	if (err) {
		dev_err(&pdev->dev, "unable to register net device\n");
		goto err_free_desc;
	}

	pr_info("%s: Atheros AG71xx at 0x%08lx, irq %d\n",
		dev->name, dev->base_addr, dev->irq);

	ag71xx_dump_regs(ag);

	ag71xx_hw_init(ag);

	ag71xx_dump_regs(ag);

	err = ag71xx_phy_connect(ag);
	if (err)
		goto err_unregister_netdev;

#ifdef CONFIG_ATH79_SOC_QCA9558
	/* get pointer of gmac0 and gmac1 ag object by phy_dev instead of devname, add by Wu Yin, 11Aug14 */
	if (ag->phy_dev)
	{
		ag71xx_gmac0_ag = ag;
	}
	else
	{
		ag71xx_gmac1_ag = ag;
	}
#endif
	
	err = ag71xx_debugfs_init(ag);
	if (err)
		goto err_phy_disconnect;

	platform_set_drvdata(pdev, dev);

	return 0;

err_phy_disconnect:
	ag71xx_phy_disconnect(ag);
err_unregister_netdev:
	unregister_netdev(dev);
err_free_desc:
	dma_free_coherent(NULL, sizeof(struct ag71xx_desc), ag->stop_desc,
			  ag->stop_desc_dma);
err_free_irq:
	free_irq(dev->irq, dev);
err_unmap_base:
	iounmap(ag->mac_base);
err_free_dev:
	kfree(dev);
err_out:
	platform_set_drvdata(pdev, NULL);
	return err;
}

static int __devexit ag71xx_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);

	if (dev) {
		struct ag71xx *ag = netdev_priv(dev);

		ag71xx_debugfs_exit(ag);
		ag71xx_phy_disconnect(ag);
		unregister_netdev(dev);
		free_irq(dev->irq, dev);
		iounmap(ag->mac_base);
		kfree(dev);
		platform_set_drvdata(pdev, NULL);
	}

	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id ag71xx_of_match_table[] = {
	{.compatible = "qcom,ag71xx-eth"},
	{}
};
#else
#define ag71xx_of_match_table NULL
#endif

static struct platform_driver ag71xx_driver = {
	.probe		= ag71xx_probe,
	.remove		= __exit_p(ag71xx_remove),
	.driver = {
		.name	= AG71XX_DRV_NAME,
		.of_match_table = ag71xx_of_match_table,
	}
};

static int __init ag71xx_module_init(void)
{
	int ret;
	u8 *art = (u8 *) KSEG1ADDR(0x1fff0000);	/* add by Wu Yin, 07Jul14 */

#ifdef CONFIG_ATH79_SOC_QCA9558
	/* init platform device first,add by Wu Yin, 07Jul14 */
	ath79_register_mdio(0, 0x0);
	ath79_init_mac(ath79_eth0_data.mac_addr, art + AP135_MAC0_OFFSET, 0);

	/* GMAC0 is connected to an AR8327 switch */
	ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_RGMII;
	ath79_eth0_data.phy_mask = BIT(0);
	ath79_eth0_data.mii_bus_dev = &ath79_mdio0_device.dev;
	ath79_eth0_pll_data.pll_1000 = 0x06000000;

	ath79_register_eth(0);
	ath79_init_mac(ath79_eth1_data.mac_addr, art + AP135_MAC1_OFFSET, 0);
	ath79_eth1_data.phy_if_mode = PHY_INTERFACE_MODE_SGMII;
	ath79_eth1_data.speed = SPEED_1000;
	ath79_eth1_data.duplex = DUPLEX_FULL;
	ath79_register_eth(1);

#elif CONFIG_ATH79_SOC_QCA9531
	ath79_register_mdio(0, 0x0);
	ath79_register_mdio(1, 0x0);

	/* WAN port */
	ath79_init_mac(ath79_eth0_data.mac_addr, art + AP147_MAC0_OFFSET, 0);
	ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_MII;
	ath79_eth0_data.speed = SPEED_100;
	ath79_eth0_data.duplex = DUPLEX_FULL;
#ifndef AG71XX_LAN_WAN_PHY_SWAP
	ath79_eth0_data.phy_mask = BIT(4);
#else
	ath79_eth0_data.phy_mask = BIT(0);
#endif
	ath79_register_eth(0);

	/* LAN ports */
	ath79_init_mac(ath79_eth1_data.mac_addr, art + AP147_MAC1_OFFSET, 0);
	ath79_eth1_data.phy_if_mode = PHY_INTERFACE_MODE_GMII;
	ath79_eth1_data.speed = SPEED_1000;
	ath79_eth1_data.duplex = DUPLEX_FULL;
#ifndef AG71XX_LAN_WAN_PHY_SWAP
	ath79_switch_data.phy_poll_mask |= BIT(4);
#else
	ath79_switch_data.phy_poll_mask |= BIT(0);
#endif
	ath79_switch_data.phy4_mii_en = 1;
	ath79_register_eth(1);
#elif (defined(CONFIG_ATH79_SOC_QCA9563))
	ath79_register_mdio(0, 0x0);
	/* only one gmac */
	ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_SGMII;
	ath79_eth0_data.speed = SPEED_1000;
	ath79_eth0_data.duplex = DUPLEX_FULL;
	ath79_eth0_data.phy_mask = BIT(0);
	ath79_eth0_data.force_link = 1;
    ath79_switch_data.phy_poll_mask |= BIT(0);
	ath79_eth0_data.mii_bus_dev = &ath79_mdio0_device.dev;
	ath79_eth0_pll_data.pll_1000 = 0x06000000;
	ath79_register_eth(0);
#endif
	
	ret = ag71xx_debugfs_root_init();
	if (ret)
		goto err_out;

	ret = ag71xx_mdio_driver_init();
	if (ret)
		goto err_debugfs_exit;

#if (defined(CONFIG_ATH79_SOC_QCA9558) || defined(CONFIG_ATH79_SOC_QCA9563))
	ret = ar8216_init();
	if (ret)
		goto err_mdio_exit;
#endif

	ret = platform_driver_register(&ag71xx_driver);
	if (ret)
#if (defined(CONFIG_ATH79_SOC_QCA9558) || defined(CONFIG_ATH79_SOC_QCA9563))
		goto err_ar8216_exit;
#else
		goto err_mdio_exit;
#endif

	return 0;

#if (defined(CONFIG_ATH79_SOC_QCA9558) || defined(CONFIG_ATH79_SOC_QCA9563))
err_ar8216_exit:
	ar8216_exit();
#endif
err_mdio_exit:
	ag71xx_mdio_driver_exit();
err_debugfs_exit:
	ag71xx_debugfs_root_exit();
err_out:
	return ret;
}

static void __exit ag71xx_module_exit(void)
{
	platform_driver_unregister(&ag71xx_driver);
	ag71xx_mdio_driver_exit();
#if (defined(CONFIG_ATH79_SOC_QCA9558) || defined(CONFIG_ATH79_SOC_QCA9563))
	ar8216_exit();
#endif
	ag71xx_debugfs_root_exit();
}

module_init(ag71xx_module_init);
module_exit(ag71xx_module_exit);

MODULE_VERSION(AG71XX_DRV_VERSION);
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org>");
MODULE_AUTHOR("Imre Kaloz <kaloz@openwrt.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" AG71XX_DRV_NAME);
