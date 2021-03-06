/*
 * ***************************************************************************
 * Copyright (C) 2016 Marvell International Ltd.
 * ***************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of Marvell nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ***************************************************************************
 */

#include <arch_helpers.h>
#include <plat_marvell.h>
#include <debug.h>
#include <dram_if.h>
#include <mv_ddr_if.h>

#include <mv_ddr_atf_wrapper.h>
#include <apn806/mv_ddr_plat.h>
#include <apn806/mv_ddr_static.h>
#include <mv_ddr_topology.h>

struct dram_config dram_cfg;

/*
 * This function may modify the default DRAM parameters
 * based on information recieved from SPD or bootloader
 * configuration located on non volatile storage
 */
int update_dram_info(struct dram_config *cfg)
{
	INFO("Gathering DRAM information\n");
	return 0;
}

void *plat_get_dram_data(void)
{
	/* Update DRAM for dynamic platforms */
	update_dram_info(&dram_cfg);

	return &dram_cfg;
}

/*
 * This struct provides the DRAM training code with
 * the appropriate board DRAM configuration
 */
static struct mv_ddr_topology_map board_topology_map = {
/* FIXME: MISL board 2CS 4Gb x8 devices of micron - 2133P */
	DEBUG_LEVEL_ERROR,
	0x1, /* active interfaces */
	/* cs_mask, mirror, dqs_swap, ck_swap X subphys */
	{ { { {0x1, 0x0, 0, 0},
	      {0x1, 0x0, 0, 0},
	      {0x1, 0x0, 0, 0},
	      {0x1, 0x0, 0, 0},
	      {0x1, 0x0, 0, 0},
	      {0x1, 0x0, 0, 0},
	      {0x1, 0x0, 0, 0},
	      {0x1, 0x0, 0, 0},
	      {0x1, 0x0, 0, 0} },
	   SPEED_BIN_DDR_2400U,		/* speed_bin */
	   MV_DDR_DEV_WIDTH_16BIT,	/* sdram device width */
	   MV_DDR_DIE_CAP_8GBIT,	/* die capacity */
	   MV_DDR_FREQ_SAR,		/* frequency */
	   0, 0,			/* cas_l, cas_wl */
	   MV_DDR_TEMP_LOW} },		/* temperature */
	BUS_MASK_32BIT,	/* subphys mask */
	MV_DDR_CFG_DEFAULT,		/* ddr configuration data source */
	{ {0} },			/* raw spd data */
	{0},				/* timing parameters */
	{				/* electrical configuration */
		{			/* memory electrical configuration */
			MV_DDR_RTT_NOM_PARK_RZQ_DIV5,	/* rtt_nom */
			{
				MV_DDR_RTT_NOM_PARK_RZQ_DISABLE, /* rtt_park 1cs */
				MV_DDR_RTT_NOM_PARK_RZQ_DISABLE  /* rtt_park 2cs */
			},
			{
				MV_DDR_RTT_WR_DYN_ODT_OFF,	/* rtt_wr 1cs */
				MV_DDR_RTT_WR_DYN_ODT_OFF		/* rtt_wr 2cs */
			},
			MV_DDR_DIC_RZQ_DIV5	/* dic */
		},
		{			/* phy electrical configuration */
			MV_DDR_OHM_30,	/* data_drv_p */
			MV_DDR_OHM_30,	/* data_drv_n */
			MV_DDR_OHM_30,	/* ctrl_drv_p */
			MV_DDR_OHM_30,	/* ctrl_drv_n */
			{
				MV_DDR_OHM_60,	/* odt_p 1cs */
				MV_DDR_OHM_120	/* odt_p 2cs */
			},
			{
				MV_DDR_OHM_60,	/* odt_n 1cs */
				MV_DDR_OHM_120	/* odt_n 2cs */
			},
		},
		{			/* mac electrical configuration */
			MV_DDR_ODT_CFG_NORMAL,		/* odtcfg_pattern */
			MV_DDR_ODT_CFG_ALWAYS_ON,	/* odtcfg_write */
			MV_DDR_ODT_CFG_NORMAL,		/* odtcfg_read */
		},
	}
};

struct mv_ddr_topology_map *mv_ddr_topology_map_get(void)
{
	/* Return the board topology as defined in the board code */
	return &board_topology_map;
}

struct dram_config *mv_ddr_dram_config_get(void)
{
	/* Return dram configuration as defined in the board code */
	return &dram_cfg;
}
