/*******************************************************************************
Copyright (C) 2016 Marvell International Ltd.

This software file (the "File") is owned and distributed by Marvell
International Ltd. and/or its affiliates ("Marvell") under the following
alternative licensing terms.  Once you have made an election to distribute the
File under one of the following license alternatives, please (i) delete this
introductory statement regarding license alternatives, (ii) delete the three
license alternatives that you have not elected to use and (iii) preserve the
Marvell copyright notice above.

********************************************************************************
Marvell Commercial License Option

If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.

********************************************************************************
Marvell GPL License Option

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 2 of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************************
Marvell GNU General Public License FreeRTOS Exception

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File in accordance with the terms and conditions of the Lesser
General Public License Version 2.1 plus the following FreeRTOS exception.
An independent module is a module which is not derived from or based on
FreeRTOS.
Clause 1:
Linking FreeRTOS statically or dynamically with other modules is making a
combined work based on FreeRTOS. Thus, the terms and conditions of the GNU
General Public License cover the whole combination.
As a special exception, the copyright holder of FreeRTOS gives you permission
to link FreeRTOS with independent modules that communicate with FreeRTOS solely
through the FreeRTOS API interface, regardless of the license terms of these
independent modules, and to copy and distribute the resulting combined work
under terms of your choice, provided that:
1. Every copy of the combined work is accompanied by a written statement that
details to the recipient the version of FreeRTOS used and an offer by yourself
to provide the FreeRTOS source code (including any modifications you may have
made) should the recipient request it.
2. The combined work is not itself an RTOS, scheduler, kernel or related
product.
3. The independent modules add significant and primary functionality to
FreeRTOS and do not merely extend the existing functionality already present in
FreeRTOS.
Clause 2:
FreeRTOS may not be used for any competitive or comparative purpose, including
the publication of any form of run time or compile time metric, without the
express permission of Real Time Engineers Ltd. (this is the norm within the
industry and is intended to ensure information accuracy).

********************************************************************************
Marvell BSD License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File under the following licensing terms.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.

	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

	* Neither the name of Marvell nor the names of its contributors may be
	  used to endorse or promote products derived from this software without
	  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#include "ddr3_init.h"

/* Device attributes structures */
enum mv_ddr_dev_attribute ddr_dev_attributes[MAX_DEVICE_NUM][MV_ATTR_LAST];
int ddr_dev_attr_init_done[MAX_DEVICE_NUM] = { 0 };

static inline u32 pattern_table_get_killer_word16(u8 dqs, u8 index);
static inline u32 pattern_table_get_sso_word(u8 sso, u8 index);
static inline u32 pattern_table_get_vref_word(u8 index);
static inline u32 pattern_table_get_vref_word16(u8 index);
static inline u32 pattern_table_get_sso_full_xtalk_word(u8 bit, u8 index);
static inline u32 pattern_table_get_sso_full_xtalk_word16(u8 bit, u8 index);
static inline u32 pattern_table_get_sso_xtalk_free_word(u8 bit, u8 index);
static inline u32 pattern_table_get_sso_xtalk_free_word16(u8 bit, u8 index);
static inline u32 pattern_table_get_isi_word(u8 index);
static inline u32 pattern_table_get_isi_word16(u8 index);

#if defined(CONFIG_DDR4)
u8 pattern_killer_map[KILLER_PATTERN_LENGTH * 2] = {
	0x01,
	0x00,
	0x01,
	0xff,
	0xfe,
	0xfe,
	0x01,
	0xfe,
	0x01,
	0xfe,
	0x01,
	0x01,
	0xfe,
	0x01,
	0xfe,
	0x00,
	0xff,
	0x00,
	0xff,
	0x00,
	0xff,
	0x00,
	0xff,
	0x01,
	0x00,
	0xff,
	0x00,
	0xff,
	0x00,
	0x00,
	0x00,
	0xfe,
	0xfe,
	0xff,
	0x00,
	0x00,
	0xff,
	0xff,
	0x00,
	0xff,
	0x00,
	0xff,
	0xff,
	0x00,
	0x00,
	0xff,
	0x00,
	0xff,
	0xfe,
	0x00,
	0xfe,
	0xfe,
	0x00,
	0xff,
	0xff,
	0x01,
	0x01,
	0xff,
	0xff,
	0x00,
	0x00,
	0x00,
	0x00,
	0xff
};
static inline u32 pattern_table_get_killer_word_4(u8 dqs, u8 index)
{
	u8 byte;

	if (index >= (KILLER_PATTERN_LENGTH * 2)) {
		DEBUG_TRAINING_IP(DEBUG_LEVEL_ERROR, ("Error: %s: wrong index [%u]\n", __func__, index));
		return 0;
	}

	byte = pattern_killer_map[index];

	switch (byte) {
	case 0x01:
	    byte = 1 << dqs;
	    break;
	case 0xfe:
	    byte = 0xff & ~(1 << dqs);
	    break;
	default:
	    break;
	}

	return byte | (byte << 8) | (byte << 16) | (byte << 24);
}
#else /* !CONFIG_DDR4 */
/* List of allowed frequency listed in order of enum hws_ddr_freq */
u32 freq_val[DDR_FREQ_LAST] = {
	0,			/*DDR_FREQ_LOW_FREQ */
	400,			/*DDR_FREQ_400, */
	533,			/*DDR_FREQ_533, */
	666,			/*DDR_FREQ_667, */
	800,			/*DDR_FREQ_800, */
	933,			/*DDR_FREQ_933, */
	1066,			/*DDR_FREQ_1066, */
	311,			/*DDR_FREQ_311, */
	333,			/*DDR_FREQ_333, */
	467,			/*DDR_FREQ_467, */
	850,			/*DDR_FREQ_850, */
	600,			/*DDR_FREQ_600 */
	300,			/*DDR_FREQ_300 */
	900,			/*DDR_FREQ_900 */
	360,			/*DDR_FREQ_360 */
	1000			/*DDR_FREQ_1000 */
};

/* Table for CL values per frequency for each speed bin index */
struct cl_val_per_freq cas_latency_table[] = {
	/*
	 * 400M   667M     933M   311M     467M  600M    360
	 * 100M    533M    800M    1066M   333M    850M      900
	 * 1000 (the order is 100, 400, 533 etc.)
	 */
	/* DDR3-800D */
	{ {6, 5, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 5, 0, 5, 0} },
	/* DDR3-800E */
	{ {6, 6, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 6, 0, 6, 0} },
	/* DDR3-1066E */
	{ {6, 5, 6, 0, 0, 0, 0, 5, 5, 6, 0, 0, 5, 0, 5, 0} },
	/* DDR3-1066F */
	{ {6, 6, 7, 0, 0, 0, 0, 6, 6, 7, 0, 0, 6, 0, 6, 0} },
	/* DDR3-1066G */
	{ {6, 6, 8, 0, 0, 0, 0, 6, 6, 8, 0, 0, 6, 0, 6, 0} },
	/* DDR3-1333F* */
	{ {6, 5, 6, 7, 0, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1333G */
	{ {6, 5, 7, 8, 0, 0, 0, 5, 5, 7, 0, 8, 5, 0, 5, 0} },
	/* DDR3-1333H */
	{ {6, 6, 8, 9, 0, 0, 0, 6, 6, 8, 0, 9, 6, 0, 6, 0} },
	/* DDR3-1333J* */
	{ {6, 6, 8, 10, 0, 0, 0, 6, 6, 8, 0, 10, 6, 0, 6,  0}
	 /* DDR3-1600G* */},
	{ {6, 5, 6, 7, 8, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1600H */
	{ {6, 5, 6, 8, 9, 0, 0, 5, 5, 6, 0, 8, 5, 0, 5, 0} },
	/* DDR3-1600J */
	{ {6, 5, 7, 9, 10, 0, 0, 5, 5, 7, 0, 9, 5, 0, 5, 0} },
	/* DDR3-1600K */
	{ {6, 6, 8, 10, 11, 0, 0, 6, 6, 8, 0, 10, 6, 0, 6, 0 } },
	/* DDR3-1866J* */
	{ {6, 5, 6, 8, 9, 11, 0, 5, 5, 6, 11, 8, 5, 0, 5, 0} },
	/* DDR3-1866K */
	{ {6, 5, 7, 8, 10, 11, 0, 5, 5, 7, 11, 8, 5, 11, 5, 11} },
	/* DDR3-1866L */
	{ {6, 6, 7, 9, 11, 12, 0, 6, 6, 7, 12, 9, 6, 12, 6, 12} },
	/* DDR3-1866M* */
	{ {6, 6, 8, 10, 11, 13, 0, 6, 6, 8, 13, 10, 6, 13, 6, 13} },
	/* DDR3-2133K* */
	{ {6, 5, 6, 7, 9, 10, 11, 5, 5, 6, 10, 7, 5, 11, 5, 11} },
	/* DDR3-2133L */
	{ {6, 5, 6, 8, 9, 11, 12, 5, 5, 6, 11, 8, 5, 12, 5, 12} },
	/* DDR3-2133M */
	{ {6, 5, 7, 9, 10, 12, 13, 5, 5, 7, 12, 9, 5, 13, 5, 13} },
	/* DDR3-2133N* */
	{ {6, 6, 7, 9, 11, 13, 14, 6, 6, 7, 13, 9, 6, 14,  6, 14} },
	/* DDR3-1333H-ext */
	{ {6, 6, 7, 9, 0, 0, 0, 6, 6, 7, 0, 9, 6, 0, 6, 0} },
	/* DDR3-1600K-ext */
	{ {6, 6, 7, 9, 11, 0, 0, 6, 6, 7, 0, 9, 6, 0, 6, 0} },
	/* DDR3-1866M-ext */
	{ {6, 6, 7, 9, 11, 13, 0, 6, 6, 7, 13, 9, 6, 13, 6, 13} },
};

/* Table for CWL values per speedbin index */
struct cl_val_per_freq cas_write_latency_table[] = {
	/*
	 * 400M   667M     933M   311M     467M  600M    360
	 * 100M    533M    800M    1066M   333M    850M      900
	 * (the order is 100, 400, 533 etc.)
	 */
	/* DDR3-800D  */
	{ {5, 5, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 5, 0, 5, 0} },
	/* DDR3-800E  */
	{ {5, 5, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 5, 0, 5, 0} },
	/* DDR3-1066E  */
	{ {5, 5, 6, 0, 0, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1066F  */
	{ {5, 5, 6, 0, 0, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1066G  */
	{ {5, 5, 6, 0, 0, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1333F*  */
	{ {5, 5, 6, 7, 0, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1333G  */
	{ {5, 5, 6, 7, 0, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1333H  */
	{ {5, 5, 6, 7, 0, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1333J*  */
	{ {5, 5, 6, 7, 0, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1600G*  */
	{ {5, 5, 6, 7, 8, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1600H  */
	{ {5, 5, 6, 7, 8, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1600J  */
	{ {5, 5, 6, 7, 8, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1600K  */
	{ {5, 5, 6, 7, 8, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1866J*  */
	{ {5, 5, 6, 7, 8, 9, 0, 5, 5, 6, 9, 7, 5, 0, 5, 0} },
	/* DDR3-1866K  */
	{ {5, 5, 6, 7, 8, 9, 0, 5, 5, 6, 9, 7, 5, 0, 5, 0} },
	/* DDR3-1866L  */
	{ {5, 5, 6, 7, 8, 9, 0, 5, 5, 6, 9, 7, 5, 9, 5, 9} },
	/* DDR3-1866M*   */
	{ {5, 5, 6, 7, 8, 9, 0, 5, 5, 6, 9, 7, 5, 9, 5, 9} },
	/* DDR3-2133K*  */
	{ {5, 5, 6, 7, 8, 9, 10, 5, 5, 6, 9, 7, 5, 9, 5, 10} },
	/* DDR3-2133L  */
	{ {5, 5, 6, 7, 8, 9, 10, 5, 5, 6, 9, 7, 5, 9, 5, 10} },
	/* DDR3-2133M  */
	{ {5, 5, 6, 7, 8, 9, 10, 5, 5, 6, 9, 7, 5, 9, 5, 10} },
	/* DDR3-2133N*  */
	{ {5, 5, 6, 7, 8, 9, 10, 5, 5, 6, 9, 7, 5, 9, 5, 10} },
	/* DDR3-1333H-ext  */
	{ {5, 5, 6, 7, 0, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1600K-ext  */
	{ {5, 5, 6, 7, 8, 0, 0, 5, 5, 6, 0, 7, 5, 0, 5, 0} },
	/* DDR3-1866M-ext  */
	{ {5, 5, 6, 7, 8, 9, 0, 5, 5, 6, 9, 7, 5, 9, 5, 9} },
};

u8 twr_mask_table[] = {
	10,
	10,
	10,
	10,
	10,
	1,			/* 5 */
	2,			/* 6 */
	3,			/* 7 */
	4,			/* 8 */
	10,
	5,			/* 10 */
	10,
	6,			/* 12 */
	10,
	7,			/* 14 */
	10,
	0			/* 16 */
};

u8 cl_mask_table[] = {
	0,
	0,
	0,
	0,
	0,
	0x2,
	0x4,
	0x6,
	0x8,
	0xa,
	0xc,
	0xe,
	0x1,
	0x3,
	0x5,
	0x5
};

u8 cwl_mask_table[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0x1,
	0x2,
	0x3,
	0x4,
	0x5,
	0x6,
	0x7,
	0x8,
	0x9,
	0x9
};

/* RFC values (in ns) */
u16 rfc_table[] = {
	90,			/* 512M */
	110,			/* 1G */
	160,			/* 2G */
	260,			/* 4G */
	350,			/* 8G */
	0,			/* TODO: placeholder for 16-Mbit dev width */
	0,			/* TODO: placeholder for 32-Mbit dev width */
	0,			/* TODO: placeholder for 12-Mbit dev width */
	0			/* TODO: placeholder for 24-Mbit dev width */
};

u32 speed_bin_table_t_rc[] = {
	50000,
	52500,
	48750,
	50625,
	52500,
	46500,
	48000,
	49500,
	51000,
	45000,
	46250,
	47500,
	48750,
	44700,
	45770,
	46840,
	47910,
	43285,
	44220,
	45155,
	46090
};

u32 speed_bin_table_t_rcd_t_rp[] = {
	12500,
	15000,
	11250,
	13125,
	15000,
	10500,
	12000,
	13500,
	15000,
	10000,
	11250,
	12500,
	13750,
	10700,
	11770,
	12840,
	13910,
	10285,
	11220,
	12155,
	13090,
};
#endif /* CONFIG_DDR4 */

enum {
	PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_AGGRESSOR = 0,
	PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_VICTIM
};

static u8 pattern_killer_pattern_table_map[KILLER_PATTERN_LENGTH * 2][2] = {
	/*Aggressor / Victim */
	{1, 0},
	{0, 0},
	{1, 0},
	{1, 1},
	{0, 1},
	{0, 1},
	{1, 0},
	{0, 1},
	{1, 0},
	{0, 1},
	{1, 0},
	{1, 0},
	{0, 1},
	{1, 0},
	{0, 1},
	{0, 0},
	{1, 1},
	{0, 0},
	{1, 1},
	{0, 0},
	{1, 1},
	{0, 0},
	{1, 1},
	{1, 0},
	{0, 0},
	{1, 1},
	{0, 0},
	{1, 1},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 1},
	{0, 1},
	{1, 1},
	{0, 0},
	{0, 0},
	{1, 1},
	{1, 1},
	{0, 0},
	{1, 1},
	{0, 0},
	{1, 1},
	{1, 1},
	{0, 0},
	{0, 0},
	{1, 1},
	{0, 0},
	{1, 1},
	{0, 1},
	{0, 0},
	{0, 1},
	{0, 1},
	{0, 0},
	{1, 1},
	{1, 1},
	{1, 0},
	{1, 0},
	{1, 1},
	{1, 1},
	{1, 1},
	{1, 1},
	{1, 1},
	{1, 1},
	{1, 1}
};

static u8 pattern_vref_pattern_table_map[] = {
	/* 1 means 0xffffffff, 0 is 0x0 */
	0xb8,
	0x52,
	0x55,
	0x8a,
	0x33,
	0xa6,
	0x6d,
	0xfe
};

#if !defined(CONFIG_DDR4)
/* Return speed Bin value for selected index and t* element */
u32 speed_bin_table(u8 index, enum speed_bin_table_elements element)
{
	u32 result = 0;

	switch (element) {
	case SPEED_BIN_TRCD:
	case SPEED_BIN_TRP:
		result = speed_bin_table_t_rcd_t_rp[index];
		break;
	case SPEED_BIN_TRAS:
		if (index < SPEED_BIN_DDR_1066G)
			result = 37500;
		else if (index < SPEED_BIN_DDR_1333J)
			result = 36000;
		else if (index < SPEED_BIN_DDR_1600K)
			result = 35000;
		else if (index < SPEED_BIN_DDR_1866M)
			result = 34000;
		else
			result = 33000;
		break;
	case SPEED_BIN_TRC:
		result = speed_bin_table_t_rc[index];
		break;
	case SPEED_BIN_TRRD1K:
		if (index < SPEED_BIN_DDR_800E)
			result = 10000;
		else if (index < SPEED_BIN_DDR_1066G)
			result = 7500;
		else if (index < SPEED_BIN_DDR_1600K)
			result = 6000;
		else
			result = 5000;
		break;
	case SPEED_BIN_TRRD2K:
		if (index < SPEED_BIN_DDR_1066G)
			result = 10000;
		else if (index < SPEED_BIN_DDR_1600K)
			result = 7500;
		else
			result = 6000;
		break;
	case SPEED_BIN_TPD:
		if (index < SPEED_BIN_DDR_800E)
			result = 7500;
		else if (index < SPEED_BIN_DDR_1333J)
			result = 5625;
		else
			result = 5000;
		break;
	case SPEED_BIN_TFAW1K:
		if (index < SPEED_BIN_DDR_800E)
			result = 40000;
		else if (index < SPEED_BIN_DDR_1066G)
			result = 37500;
		else if (index < SPEED_BIN_DDR_1600K)
			result = 30000;
		else if (index < SPEED_BIN_DDR_1866M)
			result = 27000;
		else
			result = 25000;
		break;
	case SPEED_BIN_TFAW2K:
		if (index < SPEED_BIN_DDR_1066G)
			result = 50000;
		else if (index < SPEED_BIN_DDR_1333J)
			result = 45000;
		else if (index < SPEED_BIN_DDR_1600K)
			result = 40000;
		else
			result = 35000;
		break;
	case SPEED_BIN_TWTR:
		result = 7500;
		break;
	case SPEED_BIN_TRTP:
		result = 7500;
		break;
	case SPEED_BIN_TWR:
		result = 15000;
		break;
	case SPEED_BIN_TMOD:
		result = 15000;
		break;
	case SPEED_BIN_TXPDLL:
		result = 24000;
		break;
	default:
		break;
	}

	return result;
}

static inline u32 pattern_table_get_killer_word(u8 dqs, u8 index)
{
	u8 i, byte = 0;
	u8 role;

	for (i = 0; i < 8; i++) {
		role = (i == dqs) ?
			(PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_AGGRESSOR) :
			(PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_VICTIM);
		byte |= pattern_killer_pattern_table_map[index][role] << i;
	}

	return byte | (byte << 8) | (byte << 16) | (byte << 24);
}
#endif /* !CONFIG_DDR4 */

static inline u32 pattern_table_get_killer_word16(u8 dqs, u8 index)
{
	u8 i, byte0 = 0, byte1 = 0;
	u8 role;

	for (i = 0; i < 8; i++) {
		role = (i == dqs) ?
			(PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_AGGRESSOR) :
			(PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_VICTIM);
		byte0 |= pattern_killer_pattern_table_map[index * 2][role] << i;
		byte1 |= pattern_killer_pattern_table_map[index * 2 + 1][role] << i;
	}

	return byte0 | (byte0 << 8) | (byte1 << 16) | (byte1 << 24);
}

static inline u32 pattern_table_get_sso_word(u8 sso, u8 index)
{
	u8 step = sso + 1;

	if (0 == ((index / step) & 1))
		return 0x0;
	else
		return 0xffffffff;
}

static inline u32 pattern_table_get_sso_full_xtalk_word(u8 bit, u8 index)
{
	u8 byte = (1 << bit);

	if ((index & 1) == 1)
		byte = ~byte;

	return byte | (byte << 8) | (byte << 16) | (byte << 24);

}

static inline u32 pattern_table_get_sso_xtalk_free_word(u8 bit, u8 index)
{
	u8 byte = (1 << bit);

	if ((index & 1) == 1)
		byte = 0;

	return byte | (byte << 8) | (byte << 16) | (byte << 24);
}

static inline u32 pattern_table_get_isi_word(u8 index)
{
	u8 i0 = index % 32;
	u8 i1 = index % 8;
	u32 word;

	if (i0 > 15)
		word = ((i1 == 5) | (i1 == 7)) ? 0xffffffff : 0x0;
	else
		word = (i1 == 6) ? 0xffffffff : 0x0;

	word = ((i0 % 16) > 7) ? ~word : word;

	return word;
}

static inline u32 pattern_table_get_sso_full_xtalk_word16(u8 bit, u8 index)
{
	u8 byte = (1 << bit);

	if ((index & 1) == 1)
		byte = ~byte;

	return byte | (byte << 8) | ((~byte) << 16) | ((~byte) << 24);
}

static inline u32 pattern_table_get_sso_xtalk_free_word16(u8 bit, u8 index)
{
	u8 byte = (1 << bit);

	if ((index & 1) == 0)
		return (byte << 16) | (byte << 24);
	else
		return byte | (byte << 8);
}

static inline u32 pattern_table_get_isi_word16(u8 index)
{
	u8 i0 = index % 16;
	u8 i1 = index % 4;
	u32 word;

	if (i0 > 7)
		word = (i1 > 1) ? 0x0000ffff : 0x0;
	else
		word = (i1 == 3) ? 0xffff0000 : 0x0;

	word = ((i0 % 8) > 3) ? ~word : word;

	return word;
}

static inline u32 pattern_table_get_vref_word(u8 index)
{
	if (0 == ((pattern_vref_pattern_table_map[index / 8] >>
		   (index % 8)) & 1))
		return 0x0;
	else
		return 0xffffffff;
}

static inline u32 pattern_table_get_vref_word16(u8 index)
{
	if (0 == pattern_killer_pattern_table_map
	    [PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_VICTIM][index * 2] &&
	    0 == pattern_killer_pattern_table_map
	    [PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_VICTIM][index * 2 + 1])
		return 0x00000000;
	else if (1 == pattern_killer_pattern_table_map
		 [PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_VICTIM][index * 2] &&
		 0 == pattern_killer_pattern_table_map
		 [PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_VICTIM][index * 2 + 1])
		return 0xffff0000;
	else if (0 == pattern_killer_pattern_table_map
		 [PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_VICTIM][index * 2] &&
		 1 == pattern_killer_pattern_table_map
		 [PATTERN_KILLER_PATTERN_TABLE_MAP_ROLE_VICTIM][index * 2 + 1])
		return 0x0000ffff;
	else
		return 0xffffffff;
}

#if !defined(CONFIG_DDR4)
static inline u32 pattern_table_get_static_pbs_word(u8 index)
{
	u16 temp;

	temp = ((0x00ff << (index / 3)) & 0xff00) >> 8;

	return temp | (temp << 8) | (temp << 16) | (temp << 24);
}
#endif /* !CONFIG_DDR4 */

u32 pattern_table_get_word(u32 dev_num, enum hws_pattern type, u8 index)
{
	u32 pattern;
	struct mv_ddr_topology_map *tm = mv_ddr_topology_map_get();

	if (DDR3_IS_16BIT_DRAM_MODE(tm->bus_act_mask) == 0) {
		/* 32/64-bit patterns */
		switch (type) {
		case PATTERN_PBS1:
		case PATTERN_PBS2:
#if !defined(CONFIG_DDR4)
			if (index == 0 || index == 2 || index == 5 ||
			    index == 7)
				pattern = PATTERN_55;
			else
				pattern = PATTERN_AA;
			break;
#endif /* !CONFIG_DDR4 */
		case PATTERN_PBS3:
#if !defined(CONFIG_DDR4)
			if (0 == (index & 1))
				pattern = PATTERN_55;
			else
				pattern = PATTERN_AA;
#endif /* !CONFIG_DDR4 */
			break;
		case PATTERN_RL:
#if !defined(CONFIG_DDR4)
			if (index < 6)
				pattern = PATTERN_00;
			else
				pattern = PATTERN_80;
#else /* CONFIG_DDR4 */
			pattern = PATTERN_00;
#endif /* !CONFIG_DDR4 */
			break;
		case PATTERN_STATIC_PBS:
#if !defined(CONFIG_DDR4)
			pattern = pattern_table_get_static_pbs_word(index);
#endif /* !CONFIG_DDR4 */
			break;
		case PATTERN_KILLER_DQ0:
		case PATTERN_KILLER_DQ1:
		case PATTERN_KILLER_DQ2:
		case PATTERN_KILLER_DQ3:
		case PATTERN_KILLER_DQ4:
		case PATTERN_KILLER_DQ5:
		case PATTERN_KILLER_DQ6:
		case PATTERN_KILLER_DQ7:
#if !defined(CONFIG_DDR4)
			pattern = pattern_table_get_killer_word(
#else /* CONFIG_DDR4 */
			pattern = pattern_table_get_killer_word_4(
#endif /* !CONFIG_DDR4 */
				(u8)(type - PATTERN_KILLER_DQ0), index);
			break;
#if defined(CONFIG_64BIT)
		case PATTERN_KILLER_DQ0_64:
		case PATTERN_KILLER_DQ1_64:
		case PATTERN_KILLER_DQ2_64:
		case PATTERN_KILLER_DQ3_64:
		case PATTERN_KILLER_DQ4_64:
		case PATTERN_KILLER_DQ5_64:
		case PATTERN_KILLER_DQ6_64:
		case PATTERN_KILLER_DQ7_64:
#if !defined(CONFIG_DDR4)
			pattern = pattern_table_get_killer_word(
#else /* CONFIG_DDR4 */
			pattern = pattern_table_get_killer_word_4(
#endif /* !CONFIG_DDR4 */
				(u8)(type - PATTERN_KILLER_DQ0_64), index + 32);
			break;
#endif /* CONFIG_64BIT */
		case PATTERN_RL2:
#if !defined(CONFIG_DDR4)
			if (index < 6)
				pattern = PATTERN_00;
			else
				pattern = PATTERN_01;
#else /* !CONFIG_DDR4 */
			pattern = PATTERN_FF;
#endif /* CONFIG_DDR4 */
			break;
		case PATTERN_TEST:
			if (index > 1 && index < 6)
				pattern = PATTERN_00;
			else
				pattern = PATTERN_FF;
			break;
		case PATTERN_FULL_SSO0:
		case PATTERN_FULL_SSO1:
		case PATTERN_FULL_SSO2:
		case PATTERN_FULL_SSO3:
			pattern = pattern_table_get_sso_word(
				(u8)(type - PATTERN_FULL_SSO0), index);
			break;
		case PATTERN_VREF:
			pattern = pattern_table_get_vref_word(index);
			break;
#if defined(CONFIG_64BIT)
		case PATTERN_VREF_64:
			pattern = pattern_table_get_vref_word(index + 32);
			break;
#endif /* CONFIG_64BIT */
		case PATTERN_SSO_FULL_XTALK_DQ0:
		case PATTERN_SSO_FULL_XTALK_DQ1:
		case PATTERN_SSO_FULL_XTALK_DQ2:
		case PATTERN_SSO_FULL_XTALK_DQ3:
		case PATTERN_SSO_FULL_XTALK_DQ4:
		case PATTERN_SSO_FULL_XTALK_DQ5:
		case PATTERN_SSO_FULL_XTALK_DQ6:
		case PATTERN_SSO_FULL_XTALK_DQ7:
			pattern = pattern_table_get_sso_full_xtalk_word(
				(u8)(type - PATTERN_SSO_FULL_XTALK_DQ0), index);
			break;
#if defined(CONFIG_64BIT)
		case PATTERN_SSO_FULL_XTALK_DQ0_64:
		case PATTERN_SSO_FULL_XTALK_DQ1_64:
		case PATTERN_SSO_FULL_XTALK_DQ2_64:
		case PATTERN_SSO_FULL_XTALK_DQ3_64:
		case PATTERN_SSO_FULL_XTALK_DQ4_64:
		case PATTERN_SSO_FULL_XTALK_DQ5_64:
		case PATTERN_SSO_FULL_XTALK_DQ6_64:
		case PATTERN_SSO_FULL_XTALK_DQ7_64:
			pattern = pattern_table_get_sso_full_xtalk_word(
				(u8)(type - PATTERN_SSO_FULL_XTALK_DQ0_64), index + 32);
			break;
#endif /* CONFIG_64BIT */
		case PATTERN_SSO_XTALK_FREE_DQ0:
		case PATTERN_SSO_XTALK_FREE_DQ1:
		case PATTERN_SSO_XTALK_FREE_DQ2:
		case PATTERN_SSO_XTALK_FREE_DQ3:
		case PATTERN_SSO_XTALK_FREE_DQ4:
		case PATTERN_SSO_XTALK_FREE_DQ5:
		case PATTERN_SSO_XTALK_FREE_DQ6:
		case PATTERN_SSO_XTALK_FREE_DQ7:
			pattern = pattern_table_get_sso_xtalk_free_word(
				(u8)(type - PATTERN_SSO_XTALK_FREE_DQ0), index);
			break;
#if defined(CONFIG_64BIT)
		case PATTERN_SSO_XTALK_FREE_DQ0_64:
		case PATTERN_SSO_XTALK_FREE_DQ1_64:
		case PATTERN_SSO_XTALK_FREE_DQ2_64:
		case PATTERN_SSO_XTALK_FREE_DQ3_64:
		case PATTERN_SSO_XTALK_FREE_DQ4_64:
		case PATTERN_SSO_XTALK_FREE_DQ5_64:
		case PATTERN_SSO_XTALK_FREE_DQ6_64:
		case PATTERN_SSO_XTALK_FREE_DQ7_64:
			pattern = pattern_table_get_sso_xtalk_free_word(
				(u8)(type - PATTERN_SSO_XTALK_FREE_DQ0_64), index + 32);
			break;
#endif /* CONFIG_64BIT */
		case PATTERN_ISI_XTALK_FREE:
			pattern = pattern_table_get_isi_word(index);
			break;
#if defined(CONFIG_64BIT)
		case PATTERN_ISI_XTALK_FREE_64:
			pattern = pattern_table_get_isi_word(index + 32);
			break;
#endif /* CONFIG_64BIT */
#if defined(CONFIG_DDR4)
		case PATTERN_KILLER_DQ0_INV:
		case PATTERN_KILLER_DQ1_INV:
		case PATTERN_KILLER_DQ2_INV:
		case PATTERN_KILLER_DQ3_INV:
		case PATTERN_KILLER_DQ4_INV:
		case PATTERN_KILLER_DQ5_INV:
		case PATTERN_KILLER_DQ6_INV:
		case PATTERN_KILLER_DQ7_INV:
			pattern = ~pattern_table_get_killer_word_4(
				(u8)(type - PATTERN_KILLER_DQ0_INV), index);
			break;
#if defined(CONFIG_64BIT)
		case PATTERN_KILLER_DQ0_INV_64:
		case PATTERN_KILLER_DQ1_INV_64:
		case PATTERN_KILLER_DQ2_INV_64:
		case PATTERN_KILLER_DQ3_INV_64:
		case PATTERN_KILLER_DQ4_INV_64:
		case PATTERN_KILLER_DQ5_INV_64:
		case PATTERN_KILLER_DQ6_INV_64:
		case PATTERN_KILLER_DQ7_INV_64:
			pattern = ~pattern_table_get_killer_word_4(
				(u8)(type - PATTERN_KILLER_DQ0_INV_64), index + 32);
			break;
#endif /* CONFIG_64BIT */
		case PATTERN_RESONANCE_1T:
		case PATTERN_RESONANCE_2T:
		case PATTERN_RESONANCE_3T:
		case PATTERN_RESONANCE_4T:
		case PATTERN_RESONANCE_5T:
		case PATTERN_RESONANCE_6T:
		case PATTERN_RESONANCE_7T:
		case PATTERN_RESONANCE_8T:
		case PATTERN_RESONANCE_9T:
			{
				u8 t_num = (u8)(type - PATTERN_RESONANCE_1T);
				u8 t_end = (59 / t_num) * t_num;
				if (index < t_end)
					pattern = ((index % (t_num * 2)) >= t_num) ? 0xffffffff : 0x00000000;
				else
					pattern = ((index % 2) == 0) ? 0xffffffff : 0x00000000;
			}
			break;
		case PATTERN_ZERO:
			pattern = PATTERN_00;
			break;
		case PATTERN_ONE:
			pattern = PATTERN_FF;
			break;
		case PATTERN_VREF_INV:
			pattern = ~pattern_table_get_vref_word(index);
			break;
#endif /* CONFIG_DDR4 */
		default:
			DEBUG_TRAINING_IP(DEBUG_LEVEL_ERROR, ("Error: %s: pattern type [%d] not supported\n",
							      __func__, (int)type));
			pattern = 0;
			break;
		}
	} else {
		/* 16bit patterns */
		switch (type) {
		case PATTERN_PBS1:
		case PATTERN_PBS2:
		case PATTERN_PBS3:
#if !defined(CONFIG_DDR4)
			pattern = PATTERN_55AA;
#endif /* !CONFIG_DDR4 */
			break;
		case PATTERN_RL:
#if !defined(CONFIG_DDR4)
			if (index < 3)
				pattern = PATTERN_00;
			else
				pattern = PATTERN_80;
#else /* CONFIG_DDR4 */
			pattern = PATTERN_00;
#endif /* !CONFIG_DDR4 */
			break;
		case PATTERN_STATIC_PBS:
#if !defined(CONFIG_DDR4)
			pattern = PATTERN_00FF;
#endif /* !CONFIG_DDR4 */
			break;
		case PATTERN_KILLER_DQ0:
		case PATTERN_KILLER_DQ1:
		case PATTERN_KILLER_DQ2:
		case PATTERN_KILLER_DQ3:
		case PATTERN_KILLER_DQ4:
		case PATTERN_KILLER_DQ5:
		case PATTERN_KILLER_DQ6:
		case PATTERN_KILLER_DQ7:
			pattern = pattern_table_get_killer_word16(
				(u8)(type - PATTERN_KILLER_DQ0), index);
			break;
		case PATTERN_RL2:
#if !defined(CONFIG_DDR4)
			if (index < 3)
				pattern = PATTERN_00;
			else
				pattern = PATTERN_01;
#endif /* !CONFIG_DDR4 */
			break;
		case PATTERN_TEST:
#if !defined(CONFIG_DDR4)
			if ((index == 0) || (index == 3))
				pattern = 0x00000000;
			else
				pattern = 0xFFFFFFFF;
#else /* CONFIG_DDR4 */
			if ((index > 1) && (index < 6))
				pattern = PATTERN_20;
			else
				pattern = PATTERN_00;
#endif /* !CONFIG_DDR4 */
			break;
		case PATTERN_FULL_SSO0:
#if !defined(CONFIG_DDR4)
			pattern = 0x0000ffff;
			break;
#endif /* !CONFIG_DDR4 */
		case PATTERN_FULL_SSO1:
		case PATTERN_FULL_SSO2:
		case PATTERN_FULL_SSO3:
			pattern = pattern_table_get_sso_word(
#if !defined(CONFIG_DDR4)
				(u8)(type - PATTERN_FULL_SSO1), index);
#else /* CONFIG_DDR4 */
				(u8)(type - PATTERN_FULL_SSO0), index);
#endif /* !CONFIG_DDR4 */
			break;
		case PATTERN_VREF:
			pattern = pattern_table_get_vref_word16(index);
			break;
		case PATTERN_SSO_FULL_XTALK_DQ0:
		case PATTERN_SSO_FULL_XTALK_DQ1:
		case PATTERN_SSO_FULL_XTALK_DQ2:
		case PATTERN_SSO_FULL_XTALK_DQ3:
		case PATTERN_SSO_FULL_XTALK_DQ4:
		case PATTERN_SSO_FULL_XTALK_DQ5:
		case PATTERN_SSO_FULL_XTALK_DQ6:
		case PATTERN_SSO_FULL_XTALK_DQ7:
			pattern = pattern_table_get_sso_full_xtalk_word16(
				(u8)(type - PATTERN_SSO_FULL_XTALK_DQ0), index);
			break;
		case PATTERN_SSO_XTALK_FREE_DQ0:
		case PATTERN_SSO_XTALK_FREE_DQ1:
		case PATTERN_SSO_XTALK_FREE_DQ2:
		case PATTERN_SSO_XTALK_FREE_DQ3:
		case PATTERN_SSO_XTALK_FREE_DQ4:
		case PATTERN_SSO_XTALK_FREE_DQ5:
		case PATTERN_SSO_XTALK_FREE_DQ6:
		case PATTERN_SSO_XTALK_FREE_DQ7:
			pattern = pattern_table_get_sso_xtalk_free_word16(
				(u8)(type - PATTERN_SSO_XTALK_FREE_DQ0), index);
			break;
		case PATTERN_ISI_XTALK_FREE:
			pattern = pattern_table_get_isi_word16(index);
			break;
#if defined(CONFIG_DDR4)
		case PATTERN_KILLER_DQ0_INV:
		case PATTERN_KILLER_DQ1_INV:
		case PATTERN_KILLER_DQ2_INV:
		case PATTERN_KILLER_DQ3_INV:
		case PATTERN_KILLER_DQ4_INV:
		case PATTERN_KILLER_DQ5_INV:
		case PATTERN_KILLER_DQ6_INV:
		case PATTERN_KILLER_DQ7_INV:
			pattern = ~pattern_table_get_killer_word16(
				(u8)(type - PATTERN_KILLER_DQ0_INV), index);
			break;
		case PATTERN_RESONANCE_1T:
		case PATTERN_RESONANCE_2T:
		case PATTERN_RESONANCE_3T:
		case PATTERN_RESONANCE_4T:
		case PATTERN_RESONANCE_5T:
		case PATTERN_RESONANCE_6T:
		case PATTERN_RESONANCE_7T:
		case PATTERN_RESONANCE_8T:
		case PATTERN_RESONANCE_9T:
			{
				u8 t_num = (u8)(type - PATTERN_RESONANCE_1T);
				u8 t_end = (59 / t_num) * t_num;
				if (index < t_end)
					pattern = ((index % (t_num * 2)) >= t_num) ? 0xffffffff : 0x00000000;
				else
					pattern = ((index % 2) == 0) ? 0xffffffff : 0x00000000;
			}
			break;
		case PATTERN_VREF_INV:
			pattern = ~pattern_table_get_vref_word16(index);
			break;
#endif /* CONFIG_DDR4 */
		default:
			DEBUG_TRAINING_IP(DEBUG_LEVEL_ERROR, ("Error: %s: pattern type [%d] not supported\n",
							      __func__, (int)type));
			pattern = 0;
			break;
		}
	}

	return pattern;
}

/* Device attribute functions */
void ddr3_tip_dev_attr_init(u32 dev_num)
{
	u32 attr_id;

	for (attr_id = 0; attr_id < MV_ATTR_LAST; attr_id++)
		ddr_dev_attributes[dev_num][attr_id] = 0xFF;

	ddr_dev_attr_init_done[dev_num] = 1;
}

u32 ddr3_tip_dev_attr_get(u32 dev_num, enum mv_ddr_dev_attribute attr_id)
{
	if (ddr_dev_attr_init_done[dev_num] == 0)
		ddr3_tip_dev_attr_init(dev_num);

	return ddr_dev_attributes[dev_num][attr_id];
}

void ddr3_tip_dev_attr_set(u32 dev_num, enum mv_ddr_dev_attribute attr_id, u32 value)
{
	if (ddr_dev_attr_init_done[dev_num] == 0)
		ddr3_tip_dev_attr_init(dev_num);

	ddr_dev_attributes[dev_num][attr_id] = value;
}
