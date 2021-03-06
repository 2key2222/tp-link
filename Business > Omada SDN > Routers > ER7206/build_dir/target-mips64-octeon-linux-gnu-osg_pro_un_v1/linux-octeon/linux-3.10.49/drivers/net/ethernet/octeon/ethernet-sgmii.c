/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2012 Cavium, Inc.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a different license from Cavium.
 * Contact Cavium, Inc. for more information
**********************************************************************/
#include <linux/phy.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/ratelimit.h>
#include <linux/gpio.h>
#include <linux/proc_fs.h>
#include <net/dst.h>
#include <linux/seq_file.h>
#include <linux/fs.h>


#include <asm/octeon/octeon.h>
#include <asm/octeon/octeon-hw-status.h>

#include "ethernet-defines.h"
#include "octeon-ethernet.h"

#include <asm/octeon/cvmx-helper.h>

#include <asm/octeon/cvmx-gmxx-defs.h>
#include <asm/octeon/cvmx-npei-defs.h>

#include <asm/octeon/cvmx-helper-board.h>
#include <asm/octeon/cvmx-pcsx-defs.h>

#define INT_BIT_LOC_FAULT 20
#define INT_BIT_REM_FAULT 21

/* Although these functions are called cvm_oct_sgmii_*, they also
 * happen to be used for the XAUI ports as well.
 */
#define OCTEON_CARRIER_OFF_NUM  5
#define OCTEON_CARRIER_ON_NUM   3

#define SFP_DIR "sfp"
static char str[5] = {}; 
struct proc_dir_entry *sfp_dir;

static struct {
	uint8_t on_cnt	:3;
	uint8_t off_cnt	:4;
	uint8_t link	:1;
} net_device_carrier[256];

static ssize_t sfp_proc_write(struct file *file,const char __user *buffer,size_t count,loff_t *f_pos);

static void cvm_oct_sgmii_poll(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvmx_helper_link_info_t link_info;

	link_info = cvmx_helper_link_get(priv->ipd_port);
	if (link_info.u64 == priv->link_info)
		return;

	link_info = cvmx_helper_link_autoconf(priv->ipd_port);
	priv->link_info = link_info.u64;
	/* Tell the core */
	cvm_oct_set_carrier(priv, link_info);
}
static int cvm_oct_sgmii_hw_status(struct notifier_block *nb,
				   unsigned long val, void *v)
{
	struct octeon_ethernet *priv = container_of(nb, struct octeon_ethernet,
						    hw_status_notifier);

	if (val == OCTEON_HW_STATUS_SOURCE_ASSERTED) {
		struct octeon_hw_status_data *d = v;
		if (d->reg == CVMX_GMXX_RXX_INT_REG(priv->interface_port,
						    priv->interface) &&
		    (d->bit == INT_BIT_LOC_FAULT ||
		     d->bit == INT_BIT_REM_FAULT)) {
			cvmx_helper_link_autoconf(priv->ipd_port);
			return NOTIFY_STOP;
		}
	}
	return NOTIFY_DONE;
}

cvmx_helper_link_info_t agl_link_get(int port)
{
        cvmx_helper_link_info_t result;
	union cvmx_pcsx_miscx_ctl_reg pcsx_miscx_ctl_reg;
	union cvmx_pcsx_mrx_status_reg pcsx_mrx_status_reg;
	int interface = cvmx_helper_get_interface_num(port);
	int index = cvmx_helper_get_interface_index_num(port);
	pcsx_miscx_ctl_reg.u64 =
		cvmx_read_csr(CVMX_PCSX_MISCX_CTL_REG(index, interface));
	if (!pcsx_miscx_ctl_reg.s.mac_phy) {
		/* 1000BASE-X */
		if (pcsx_miscx_ctl_reg.s.mode) {
			pcsx_mrx_status_reg.u64 =
				cvmx_read_csr(CVMX_PCSX_MRX_STATUS_REG(index, interface));
			if(pcsx_mrx_status_reg.s.lnk_st)
			{
				if(NULL == str)
				{
					sfp_proc_write(NULL, "1", 1, 0);
				}
				else if(strcmp(str,"1") != 0)
				{
					sfp_proc_write(NULL, "1", 1, 0);
				}
			}
			else
			{
				if(NULL == str)
				{
					sfp_proc_write(NULL, "0", 1, 0);
				}
				else if(strcmp(str,"0") != 0)
				{
					sfp_proc_write(NULL, "0", 1, 0);
				}
			}

			if (port >= sizeof(net_device_carrier)) {
				result.s.link_up = pcsx_mrx_status_reg.s.lnk_st;
			} else {
				if (pcsx_mrx_status_reg.s.lnk_st) {
					net_device_carrier[port].off_cnt = 0;
					if (!net_device_carrier[port].link) {
						net_device_carrier[port].on_cnt++;
						if (net_device_carrier[port].on_cnt > OCTEON_CARRIER_ON_NUM) {
							net_device_carrier[port].on_cnt = 0;
							net_device_carrier[port].link = 1;
						}
					} else {
						net_device_carrier[port].on_cnt = 0;
					}
				} else {
					net_device_carrier[port].on_cnt = 0;
					if (net_device_carrier[port].link) {
						net_device_carrier[port].off_cnt++;
						if (net_device_carrier[port].off_cnt > OCTEON_CARRIER_OFF_NUM) {
							net_device_carrier[port].off_cnt = 0;
							net_device_carrier[port].link = 0;
						}
					} else {
						net_device_carrier[port].off_cnt = 0;
					}
				}
				result.s.link_up = net_device_carrier[port].link;
			}
			result.s.full_duplex = 1;
			result.s.speed = 1000;
		}
	} else {
        	result.s.full_duplex = 1;
        	result.s.link_up = 1;
        	result.s.speed = 1000;
	}
        return result;
}

int cvm_oct_sgmii_open(struct net_device *dev)
{
	struct octeon_hw_status_reg sr[3];
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	struct octeon_ethernet *priv = netdev_priv(dev);
	cvmx_helper_link_info_t link_info;
	cvmx_helper_interface_mode_t imode;
	int rv, i;
	u64 en_mask;

	rv = cvm_oct_phy_setup_device(dev);
	if (rv)
		return rv;

	gmx_cfg.u64 = cvmx_read_csr(priv->gmx_base + GMX_PRT_CFG);
	gmx_cfg.s.en = 1;
	cvmx_write_csr(priv->gmx_base + GMX_PRT_CFG, gmx_cfg.u64);

	if (octeon_is_simulation())
		return 0;

	if (priv->phydev) {
		int r = phy_read_status(priv->phydev);
		if (r == 0 && priv->phydev->link == 0)
			netif_carrier_off(dev);
		cvm_oct_adjust_link(dev);
	} else {
		link_info = cvmx_helper_link_get(priv->ipd_port);
		if (!link_info.s.link_up)
			netif_carrier_off(dev);
		priv->poll = cvm_oct_sgmii_poll;
		cvm_oct_sgmii_poll(dev);
	}
	imode = cvmx_helper_interface_get_mode(priv->interface);
	switch (imode) {
	case CVMX_HELPER_INTERFACE_MODE_XAUI:
	case CVMX_HELPER_INTERFACE_MODE_RXAUI:
		/* Handle GMXX_RXX_INT_REG[LOC_FAULT,REM_FAULT]*/
		priv->hw_status_notifier.priority = 10;
		priv->hw_status_notifier.notifier_call = cvm_oct_sgmii_hw_status;
		octeon_hw_status_notifier_register(&priv->hw_status_notifier);
		memset(sr, 0, sizeof(sr));
		i = 0;
		en_mask = 0;
		if (OCTEON_IS_OCTEONPLUS()) {
			sr[i].reg = 46; /* RML */
			sr[i].reg_is_hwint = 1;
			sr[i].has_child = 1;
			i++;
			sr[i].reg = CVMX_NPEI_RSL_INT_BLOCKS;
			/* GMX[priv->interface]*/
			sr[i].bit = priv->interface + 1;
			sr[i].has_child = 1;
			i++;
		} else if (octeon_has_feature(OCTEON_FEATURE_CIU2)) {
			/* PKT[AGX[priv->interface]]*/
			sr[i].reg = (6 << 6) | priv->interface;
			sr[i].reg_is_hwint = 1;
			sr[i].has_child = 1;
			i++;
		} else {
			/* INT_SUM1[AGX[priv->interface]]*/
			sr[i].reg = (1 << 6) | (priv->interface + 36);
			sr[i].reg_is_hwint = 1;
			sr[i].has_child = 1;
			i++;
		}
		sr[i].reg = CVMX_GMXX_RXX_INT_REG(priv->interface_port,
						  priv->interface);
		sr[i].mask_reg = CVMX_GMXX_RXX_INT_EN(priv->interface_port,
						      priv->interface);
		sr[i].ack_w1c = 1;

		sr[i].bit = INT_BIT_LOC_FAULT;
		en_mask |= 1ull << sr[i].bit;
		octeon_hw_status_add_source(sr);

		sr[i].bit = INT_BIT_REM_FAULT;
		en_mask |= 1ull << sr[i].bit;
		octeon_hw_status_add_source(sr);

		octeon_hw_status_enable(sr[i].reg, en_mask);
		break;
	default:
		break;
	}
	return 0;
}

int cvm_oct_sgmii_stop(struct net_device *dev)
{
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	struct octeon_ethernet *priv = netdev_priv(dev);

	gmx_cfg.u64 = cvmx_read_csr(priv->gmx_base + GMX_PRT_CFG);
	gmx_cfg.s.en = 0;
	cvmx_write_csr(priv->gmx_base + GMX_PRT_CFG, gmx_cfg.u64);

	if (priv->hw_status_notifier.notifier_call) {
		struct octeon_hw_status_reg sr;
		memset(&sr, 0, sizeof(sr));

		sr.reg = CVMX_GMXX_RXX_INT_REG(priv->interface_port,
					       priv->interface);
		sr.mask_reg = CVMX_GMXX_RXX_INT_EN(priv->interface_port,
						   priv->interface);
		sr.ack_w1c = 1;
		sr.bit = INT_BIT_LOC_FAULT;
		octeon_hw_status_remove_source(&sr);
		sr.bit = INT_BIT_REM_FAULT;
		octeon_hw_status_remove_source(&sr);
		octeon_hw_status_notifier_unregister(&priv->hw_status_notifier);
		priv->hw_status_notifier.notifier_call = NULL;
	}

	priv->poll = NULL;

	if (priv->phydev)
		phy_disconnect(priv->phydev);
	priv->phydev = NULL;

	return cvm_oct_common_stop(dev);
}

static void cvm_oct_sgmii_link_change(struct octeon_ethernet *priv,
				      cvmx_helper_link_info_t link_info)
{
	if (link_info.s.link_up)
		octeon_error_tree_enable(CVMX_ERROR_GROUP_ETHERNET,
					 priv->ipd_port);
	else
		octeon_error_tree_disable(CVMX_ERROR_GROUP_ETHERNET,
					  priv->ipd_port);
}
static int sfp_proc_show(struct seq_file *m, void *v)  
{
    seq_printf(m, "%s\n", str);
    return 0;  
}  

static ssize_t sfp_proc_write(struct file *file,const char __user *buffer,size_t count,loff_t *f_pos)
{
	if(NULL == buffer)
	{
		return 0;
	}
	if(count > 4)
	{
		count = 4;
	}
	int i;
	for(i = 0;i < count;i++)
	{
		str[i] = buffer[i];
	}
	return count;
}
static int sfp_proc_open(struct inode *innode,struct file *file)
{
	return single_open(file,sfp_proc_show,NULL);
}

static struct file_operations sfp_fops = {  
	.owner   = THIS_MODULE,  
	.open    = sfp_proc_open,  
	.release = single_release,  
	.read    = seq_read,  
	.llseek  = seq_lseek,  
	.write   = sfp_proc_write,  
};  

int cvm_oct_sgmii_init(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);
	sfp_dir = proc_create(SFP_DIR,0644,NULL,&sfp_fops);
	if(!sfp_dir)
	{
		return -ENOMEM;
	}

	cvm_oct_common_init(dev);
	dev->netdev_ops->ndo_stop(dev);
	priv->link_change = cvm_oct_sgmii_link_change;
	cvmx_override_board_link_get = agl_link_get;

	return 0;
}

void cvm_oct_sgmii_uninit(struct net_device *dev)
{
	struct octeon_ethernet *priv = netdev_priv(dev);

	cvmx_override_board_link_get = NULL;
	octeon_error_tree_disable(CVMX_ERROR_GROUP_ETHERNET,
				  priv->ipd_port);
}
