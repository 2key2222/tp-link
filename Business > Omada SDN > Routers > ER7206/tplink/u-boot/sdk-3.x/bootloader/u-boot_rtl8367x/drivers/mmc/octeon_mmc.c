/***********************license start************************************
 * Copyright (c) 2012 - 2014 Cavium Inc. (support@cavium.com).  All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *     * Neither the name of Cavium Inc. nor the names of
 *       its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
 * OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
 * PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET
 * POSSESSION OR CORRESPONDENCE TO DESCRIPTION.  THE ENTIRE RISK ARISING OUT
 * OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 *
 *
 * For any questions regarding licensing please contact
 * support@cavium.com
 *
 ***********************license end**************************************/

#include <common.h>
#ifdef DEBUG
#include <command.h>
#endif
#include <mmc.h>
#include <part.h>
#include <malloc.h>
#include <errno.h>
#include <asm/arch/octeon_mmc.h>
#include <asm/io.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/octeon-feature.h>
#include <asm/arch/cvmx-access.h>
#include <asm/arch/cvmx-mio-defs.h>
#include <asm/arch/octeon_board_mmc.h>
#include <linux/list.h>
#include <div64.h>
#include <watchdog.h>
#include <asm/gpio.h>

/* Enable support for SD as well as MMC */
#define CONFIG_OCTEON_MMC_SD

#define POWER_ON_TIME		40	/* See SD 4.1 spec figure 6-5 */
/*
 * Due to how MMC is implemented in the OCTEON processor it is not
 * possible to use the generic MMC support.  However, this code
 * implements all of the MMC support found in the generic MMC driver
 * and should be compatible with it for the most part.
 *
 * Currently both MMC and SD/SDHC are supported.
 */

/**
 * Timeout used when waiting for commands to complete.  We need to keep this
 * above the hardware watchdog timeout which is usually limited to 1000ms
 */
#define WATCHDOG_COUNT		(1100)	/* in msecs */

/**
 * Long timeout for commands which might take a while to complete.
 */
#define MMC_TIMEOUT_LONG	1000
/**
 * Short timeout used for most commands in msecs
 */
#define MMC_TIMEOUT_SHORT	10

#ifndef CONFIG_OCTEON_MAX_MMC_SLOT
# define CONFIG_OCTEON_MAX_MMC_SLOT		4
#endif

#ifndef CONFIG_OCTEON_MMC_MIN_BUS_SPEED_HZ
# define CONFIG_OCTEON_MMC_MIN_BUS_SPEED_HZ		400000
#endif

#ifndef CONFIG_OCTEON_MMC_SD
# undef IS_SD
# define IS_SD(x) (0)
#endif

#ifndef CONFIG_SYS_MMC_MAX_BLK_COUNT
#define CONFIG_SYS_MMC_MAX_BLK_COUNT	8192
#else
#error CONFIG_SYS_MMC_MAX_BLK_COUNT already defined!
#endif

#define MMC_CMD_FLAG_CTYPE_XOR(x)	(((x) & 3) << 16)
#define MMC_CMD_FLAG_RTYPE_XOR(x)	(((x) & 7) << 20)
#define MMC_CMD_FLAG_OFFSET(x)		(((x) & 0x3f) << 24)
#define MMC_CMD_FLAG_IGNORE_CRC_ERR	(1 << 30)
#define MMC_CMD_FLAG_STRIP_CRC		(1 << 31)

DECLARE_GLOBAL_DATA_PTR;

static LIST_HEAD(mmc_devices);
static struct mmc	mmc_dev[CONFIG_OCTEON_MAX_MMC_SLOT];
static struct mmc_host	mmc_host[CONFIG_OCTEON_MAX_MMC_SLOT];
static struct octeon_mmc_info mmc_info;

static int cur_dev_num = -1;
static int init_time = 1;
static int init_dev_num = 1;

static int last_bus_id = -1;

int mmc_set_blocklen(struct mmc *mmc, int len);

static int mmc_send_cmd_timeout(struct mmc *mmc, struct mmc_cmd *cmd,
				struct mmc_data *data, uint32_t flags,
				uint timeout);

static int mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data, uint32_t flags);

static int mmc_send_acmd(struct mmc *mmc, struct mmc_cmd *cmd,
			 struct mmc_data *data, uint32_t flags);

static void mmc_set_ios(struct mmc *mmc);

static void mmc_switch_dev(struct mmc *mmc);

#ifdef CONFIG_OCTEON_MMC_SD
static int sd_set_ios(struct mmc *mmc);
#endif

#ifdef DEBUG
const char *mmc_reg_str(uint64_t reg)
{
	switch (reg) {
	case CVMX_MIO_NDF_DMA_CFG:	return "MIO_NDF_DMA_CFG";
	case CVMX_MIO_NDF_DMA_INT:	return "MIO_NDF_DMA_INT";
	case CVMX_MIO_NDF_DMA_INT_EN:	return "MIO_NDF_DMA_INT_EN";
	case CVMX_MIO_EMM_CFG:		return "MIO_EMM_CFG";
	case CVMX_MIO_EMM_MODEX(0):	return "MIO_EMM_MODE0";
	case CVMX_MIO_EMM_MODEX(1):	return "MIO_EMM_MODE1";
	case CVMX_MIO_EMM_MODEX(2):	return "MIO_EMM_MODE2";
	case CVMX_MIO_EMM_MODEX(3):	return "MIO_EMM_MODE3";
	case CVMX_MIO_EMM_SWITCH:	return "MIO_EMM_SWITCH";
	case CVMX_MIO_EMM_DMA:		return "MIO_EMM_DMA";
	case CVMX_MIO_EMM_CMD:		return "MIO_EMM_CMD";
	case CVMX_MIO_EMM_RSP_STS:	return "MIO_EMM_RSP_STS";
	case CVMX_MIO_EMM_RSP_LO:	return "MIO_EMM_RSP_LO";
	case CVMX_MIO_EMM_RSP_HI:	return "MIO_EMM_RSP_HI";
	case CVMX_MIO_EMM_INT:		return "MIO_EMM_INT";
	case CVMX_MIO_EMM_INT_EN:	return "MIO_EMM_INT_EN";
	case CVMX_MIO_EMM_WDOG:		return "MIO_EMM_WDOG";
	case CVMX_MIO_EMM_SAMPLE:	return "MIO_EMM_SAMPLE";
	case CVMX_MIO_EMM_STS_MASK:	return "MIO_EMM_STS_MASK";
	case CVMX_MIO_EMM_RCA:		return "MIO_EMM_RCA";
	case CVMX_MIO_EMM_BUF_IDX:	return "MIO_EMM_BUF_IDX";
	case CVMX_MIO_EMM_BUF_DAT:	return "MIO_EMM_BUF_DAT";
	default:			return "UNKNOWN";
	}
}
#endif

static inline void mmc_write_csr(uint64_t reg, uint64_t value)
{
#ifdef DEBUG_CSR
	printf("\t%s: %s <= 0x%llx\n", __func__, mmc_reg_str(reg), value);
#endif
	cvmx_write_csr(reg, value);
}

static inline uint64_t mmc_read_csr(uint64_t reg)
{
	uint64_t value = cvmx_read_csr(reg);
#ifdef DEBUG_CSR
	printf("\t%s: %s => 0x%llx\n", __func__, mmc_reg_str(reg), value);
#endif
	return value;
}

#ifdef DEBUG
static void mmc_print_status(uint32_t status)
{
	static const char *state[] = {
		"Idle",		/* 0 */
		"Ready",	/* 1 */
		"Ident",	/* 2 */
		"Standby",	/* 3 */
		"Tran",		/* 4 */
		"Data",		/* 5 */
		"Receive",	/* 6 */
		"Program",	/* 7 */
		"Dis",		/* 8 */
		"Btst",		/* 9 */
		"Sleep",	/* 10 */
		"reserved",	/* 11 */
		"reserved",	/* 12 */
		"reserved",	/* 13 */
		"reserved",	/* 14 */
		"reserved"	/* 15 */ };
	if (status & R1_APP_CMD)
		puts("MMC ACMD\n");
	if (status & R1_SWITCH_ERROR)
		puts("MMC switch error\n");
	if (status & R1_READY_FOR_DATA)
		puts("MMC ready for data\n");
	printf("MMC %s state\n", state[R1_CURRENT_STATE(status)]);
	if (status & R1_ERASE_RESET)
		puts("MMC erase reset\n");
	if (status & R1_WP_ERASE_SKIP)
		puts("MMC partial erase due to write protected blocks\n");
	if (status & R1_CID_CSD_OVERWRITE)
		puts("MMC CID/CSD overwrite error\n");
	if (status & R1_ERROR)
		puts("MMC undefined device error\n");
	if (status & R1_CC_ERROR)
		puts("MMC device error\n");
	if (status & R1_CARD_ECC_FAILED)
		puts("MMC internal ECC failed to correct data\n");
	if (status & R1_ILLEGAL_COMMAND)
		puts("MMC illegal command\n");
	if (status & R1_COM_CRC_ERROR)
		puts("MMC CRC of previous command failed\n");
	if (status & R1_LOCK_UNLOCK_FAILED)
		puts("MMC sequence or password error in lock/unlock device command\n");
	if (status & R1_CARD_IS_LOCKED)
		puts("MMC device locked by host\n");
	if (status & R1_WP_VIOLATION)
		puts("MMC attempt to program write protected block\n");
	if (status & R1_ERASE_PARAM)
		puts("MMC invalid selection of erase groups for erase\n");
	if (status & R1_ERASE_SEQ_ERROR)
		puts("MMC error in sequence of erase commands\n");
	if (status & R1_BLOCK_LEN_ERROR)
		puts("MMC block length error\n");
	if (status & R1_ADDRESS_ERROR)
		puts("MMC address misalign error\n");
	if (status & R1_OUT_OF_RANGE)
		puts("MMC address out of range\n");
}
#endif

#ifdef CONFIG_PARTITIONS
block_dev_desc_t *mmc_get_dev(int dev)
{
	struct mmc *mmc = find_mmc_device(dev);

	if (mmc)
		debug("%s: Found mmc device %d\n", __func__, dev);
	else
		debug("%s: mmc device %d not found\n", __func__, dev);

	if (!mmc || mmc_init(mmc))
		return NULL;
	return &mmc->block_dev;
}
#endif

static void mmc_print_registers(struct mmc *mmc)
{
#ifdef DEBUG
	struct mmc_host *host = NULL;
	int bus;
	cvmx_mio_ndf_dma_cfg_t ndf_dma_cfg;
	cvmx_mio_ndf_dma_int_t ndf_dma_int;
	cvmx_mio_emm_cfg_t emm_cfg;
	cvmx_mio_emm_modex_t emm_mode;
	cvmx_mio_emm_switch_t emm_switch;
	cvmx_mio_emm_dma_t emm_dma;
	cvmx_mio_emm_cmd_t emm_cmd;
	cvmx_mio_emm_rsp_sts_t emm_rsp_sts;
	cvmx_mio_emm_rsp_lo_t emm_rsp_lo;
	cvmx_mio_emm_rsp_hi_t emm_rsp_hi;
	cvmx_mio_emm_int_t emm_int;
	cvmx_mio_emm_wdog_t emm_wdog;
	cvmx_mio_emm_sample_t emm_sample;
	cvmx_mio_emm_sts_mask_t emm_sts_mask;
	cvmx_mio_emm_rca_t emm_rca;

	static const char *bus_width_str[] = {
		"1-bit data bus (power on)",
		"4-bit data bus",
		"8-bit data bus",
		"reserved (3)",
		"reserved (4)",
		"4-bit data bus (dual data rate)",
		"8-bit data bus (dual data rate)",
		"reserved (7)",
		"reserved (8)",
		"invalid (9)",
		"invalid (10)",
		"invalid (11)",
		"invalid (12)",
		"invalid (13)",
		"invalid (14)",
		"invalid (15)",
	};

	static const char *ctype_xor_str[] = {
		"No data",
		"Read data into Dbuf",
		"Write data from Dbuf",
		"Reserved"
	};

	static const char *rtype_xor_str[] = {
		"No response",
		"R1, 48 bits",
		"R2, 136 bits",
		"R3, 48 bits",
		"R4, 48 bits",
		"R5, 48 bits",
		"Reserved 6",
		"Reserved 7"
	};

	if (mmc) {
		host = (struct mmc_host *)mmc->priv;
		printf("%s: bus id: %u\n", __func__, host->bus_id);
	}

	ndf_dma_cfg.u64 = mmc_read_csr(CVMX_MIO_NDF_DMA_CFG);
	printf("MIO_NDF_DMA_CFG:\t\t0x%016llx\n", ndf_dma_cfg.u64);
	printf("\t63:\ten:\t\t%s\n", ndf_dma_cfg.s.en ? "enabled" : "disabled");
	printf("\t62:\trw:\t\t%s\n", ndf_dma_cfg.s.rw ? "write" : "read");
	printf("\t61:\tclr:\t\t%s\n", ndf_dma_cfg.s.clr ? "clear" : "not clear");
	printf("\t59:\tswap32:\t\t%s\n", ndf_dma_cfg.s.swap32 ? "yes" : "no");
	printf("\t58:\tswap16:\t\t%s\n", ndf_dma_cfg.s.swap16 ? "yes" : "no");
	printf("\t57:\tswap8:\t\t%s\n", ndf_dma_cfg.s.swap8 ? "yes" : "no");
	printf("\t56:\tendian:\t\t%s\n", ndf_dma_cfg.s.endian ? "little" : "big");
	printf("\t36-55:\tsize:\t\t%u\n", ndf_dma_cfg.s.size);
	printf("\t0-35:\tadr:\t\t0x%llx\n", (uint64_t)ndf_dma_cfg.s.adr);

	ndf_dma_int.u64 = mmc_read_csr(CVMX_MIO_NDF_DMA_INT);
	printf("\nMIO_NDF_DMA_INT:\t\t0x%016llx\n", ndf_dma_int.u64);
	printf("\t0:\tDone:\t\t%s\n", ndf_dma_int.s.done ? "yes" : "no");

	emm_cfg.u64 = mmc_read_csr(CVMX_MIO_EMM_CFG);
	printf("\nMIO_EMM_CFG:\t\t\t0x%016llx\n", emm_cfg.u64);
	printf("\t16:\tboot_fail:\t%s\n", emm_cfg.s.boot_fail ? "yes" : "no");
	printf("\t3:\tbus_ena3:\t%s\n", emm_cfg.s.bus_ena & 0x08 ? "yes" : "no");
	printf("\t2:\tbus_ena2:\t%s\n", emm_cfg.s.bus_ena & 0x04 ? "yes" : "no");
	printf("\t1:\tbus_ena1:\t%s\n", emm_cfg.s.bus_ena & 0x02 ? "yes" : "no");
	printf("\t0:\tbus_ena0:\t%s\n", emm_cfg.s.bus_ena & 0x01 ? "yes" : "no");

	for (bus = 0; bus < 4; bus++) {
		emm_mode.u64 = mmc_read_csr(CVMX_MIO_EMM_MODEX(bus));
		printf("\nMIO_EMM_MODE%u:\t\t\t0x%016llx\n", bus, emm_mode.u64);
		printf("\t48:\ths_timing:\t%s\n", emm_mode.s.hs_timing ? "yes" : "no");
		printf("\t40-42:\tbus_width:\t%s\n", bus_width_str[emm_mode.s.bus_width]);
		printf("\t32-35:\tpower_class\t%u\n", emm_mode.s.power_class);
		printf("\t16-31:\tclk_hi:\t\t%u\n", emm_mode.s.clk_hi);
		printf("\t0-15:\tclk_lo:\t\t%u\n", emm_mode.s.clk_lo);
	}

	emm_switch.u64 = mmc_read_csr(CVMX_MIO_EMM_SWITCH);
	printf("\nMIO_EMM_SWITCH:\t\t\t0x%016llx\n", emm_switch.u64);
	printf("\t60-61:\tbus_id:\t\t%u\n", emm_switch.s.bus_id);
	printf("\t59:\tswitch_exe:\t%s\n", emm_switch.s.switch_exe ? "yes" : "no");
	printf("\t58:\tswitch_err0:\t%s\n", emm_switch.s.switch_err0 ? "yes" : "no");
	printf("\t57:\tswitch_err1:\t%s\n", emm_switch.s.switch_err1 ? "yes" : "no");
	printf("\t56:\tswitch_err2:\t%s\n", emm_switch.s.switch_err2 ? "yes" : "no");
	printf("\t48:\ths_timing:\t%s\n", emm_switch.s.hs_timing ? "yes" : "no");
	printf("\t42-40:\tbus_width:\t%s\n", bus_width_str[emm_switch.s.bus_width]);
	printf("\t32-35:\tpower_class:\t%u\n", emm_switch.s.power_class);
	printf("\t16-31:\tclk_hi:\t\t%u\n", emm_switch.s.clk_hi);
	printf("\t0-15:\tclk_lo:\t\t%u\n", emm_switch.s.clk_lo);

	emm_dma.u64 = mmc_read_csr(CVMX_MIO_EMM_DMA);
	printf("\nMIO_EMM_DMA:\t\t\t0x%016llx\n", emm_dma.u64);
	printf("\t60-61:\tbus_id:\t\t%u\n", emm_dma.s.bus_id);
	printf("\t59:\tdma_val:\t%s\n", emm_dma.s.dma_val ? "yes" : "no");
	printf("\t58:\tsector:\t\t%s mode\n", emm_dma.s.sector ? "sector" : "byte");
	printf("\t57:\tdat_null:\t%s\n", emm_dma.s.dat_null ? "yes" : "no");
	printf("\t51-56:\tthres:\t\t%u\n", emm_dma.s.thres);
	printf("\t50:\trel_wr:\t\t%s\n", emm_dma.s.rel_wr ? "yes" : "no");
	printf("\t49:\trw:\t\t%s\n", emm_dma.s.rw ? "write" : "read");
	printf("\t48:\tmulti:\t\t%s\n", emm_dma.s.multi ? "yes" : "no");
	printf("\t32-47:\tblock_cnt:\t%u\n", emm_dma.s.block_cnt);
	printf("\t0-31:\tcard_addr:\t0x%x\n", emm_dma.s.card_addr);

	emm_cmd.u64 = mmc_read_csr(CVMX_MIO_EMM_CMD);
	printf("\nMIO_EMM_CMD:\t\t\t0x%016llx\n", emm_cmd.u64);
	printf("\t60-61:\tbus_id:\t\t%u\n", emm_cmd.s.bus_id);
	printf("\t59:\tcmd_val:\t%s\n", emm_cmd.s.cmd_val ? "yes" : "no");
	printf("\t55:\tdbuf:\t\t%u\n", emm_cmd.s.dbuf);
	printf("\t49-54:\toffset:\t\t%u\n", emm_cmd.s.offset);
	printf("\t41-42:\tctype_xor:\t%s\n", ctype_xor_str[emm_cmd.s.ctype_xor]);
	printf("\t38-40:\trtype_xor:\t%s\n", rtype_xor_str[emm_cmd.s.rtype_xor]);
	printf("\t32-37:\tcmd_idx:\t%u\n", emm_cmd.s.cmd_idx);
	printf("\t0-31:\targ:\t\t0x%x\n", emm_cmd.s.arg);

	emm_rsp_sts.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_STS);
	printf("\nMIO_EMM_RSP_STS:\t\t0x%016llx\n", emm_rsp_sts.u64);
	printf("\t60-61:\tbus_id:\t\t%u\n", emm_rsp_sts.s.bus_id);
	printf("\t59:\tcmd_val:\t%s\n", emm_rsp_sts.s.cmd_val ? "yes" : "no");
	printf("\t58:\tswitch_val:\t%s\n", emm_rsp_sts.s.switch_val ? "yes" : "no");
	printf("\t57:\tdma_val:\t%s\n", emm_rsp_sts.s.dma_val ? "yes" : "no");
	printf("\t56:\tdma_pend:\t%s\n", emm_rsp_sts.s.dma_pend ? "yes" : "no");
	printf("\t28:\tdbuf_err:\t%s\n", emm_rsp_sts.s.dbuf_err ? "yes" : "no");
	printf("\t23:\tdbuf:\t\t%u\n", emm_rsp_sts.s.dbuf);
	printf("\t22:\tblk_timeout:\t%s\n", emm_rsp_sts.s.blk_timeout ? "yes" : "no");
	printf("\t21:\tblk_crc_err:\t%s\n", emm_rsp_sts.s.blk_crc_err ? "yes" : "no");
	printf("\t20:\trsp_busybit:\t%s\n", emm_rsp_sts.s.rsp_busybit ? "yes" : "no");
	printf("\t19:\tstp_timeout:\t%s\n", emm_rsp_sts.s.stp_timeout ? "yes" : "no");
	printf("\t18:\tstp_crc_err:\t%s\n", emm_rsp_sts.s.stp_crc_err ? "yes" : "no");
	printf("\t17:\tstp_bad_sts:\t%s\n", emm_rsp_sts.s.stp_bad_sts ? "yes" : "no");
	printf("\t16:\tstp_val:\t%s\n", emm_rsp_sts.s.stp_val ? "yes" : "no");
	printf("\t15:\trsp_timeout:\t%s\n", emm_rsp_sts.s.rsp_timeout ? "yes" : "no");
	printf("\t14:\trsp_crc_err:\t%s\n", emm_rsp_sts.s.rsp_crc_err ? "yes" : "no");
	printf("\t13:\trsp_bad_sts:\t%s\n", emm_rsp_sts.s.rsp_bad_sts ? "yes" : "no");
	printf("\t12:\trsp_val:\t%s\n", emm_rsp_sts.s.rsp_val ? "yes" : "no");
	printf("\t9-11:\trsp_type:\t%s\n", rtype_xor_str[emm_rsp_sts.s.rsp_type]);
	printf("\t7-8:\tcmd_type:\t%s\n", ctype_xor_str[emm_rsp_sts.s.cmd_type]);
	printf("\t1-6:\tcmd_idx:\t%u\n", emm_rsp_sts.s.cmd_idx);
	printf("\t0:\tcmd_done:\t%s\n", emm_rsp_sts.s.cmd_done ? "yes" : "no");

	emm_rsp_lo.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_LO);
	printf("\nMIO_EMM_RSP_STS_LO:\t\t0x%016llx\n", emm_rsp_lo.u64);

	emm_rsp_hi.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_HI);
	printf("\nMIO_EMM_RSP_STS_HI:\t\t0x%016llx\n", emm_rsp_hi.u64);

	emm_int.u64 = mmc_read_csr(CVMX_MIO_EMM_INT);
	printf("\nMIO_EMM_INT:\t\t\t0x%016llx\n", emm_int.u64);
	printf("\t6:\tswitch_err:\t%s\n", emm_int.s.switch_err ? "yes" : "no");
	printf("\t5:\tswitch_done:\t%s\n", emm_int.s.switch_done ? "yes" : "no");
	printf("\t4:\tdma_err:\t%s\n", emm_int.s.dma_err ? "yes" : "no");
	printf("\t3:\tcmd_err:\t%s\n", emm_int.s.cmd_err ? "yes" : "no");
	printf("\t2:\tdma_done:\t%s\n", emm_int.s.dma_done ? "yes" : "no");
	printf("\t1:\tcmd_done:\t%s\n", emm_int.s.cmd_done ? "yes" : "no");
	printf("\t0:\tbuf_done:\t%s\n", emm_int.s.buf_done ? "yes" : "no");

	emm_wdog.u64 = mmc_read_csr(CVMX_MIO_EMM_WDOG);
	printf("\nMIO_EMM_WDOG:\t\t\t0x%016llx (%u)\n", emm_wdog.u64, emm_wdog.s.clk_cnt);

	emm_sample.u64 = mmc_read_csr(CVMX_MIO_EMM_SAMPLE);
	printf("\nMIO_EMM_SAMPLE:\t\t\t0x%016llx\n", emm_sample.u64);
	printf("\t16-25:\tcmd_cnt:\t%u\n", emm_sample.s.cmd_cnt);
	printf("\t0-9:\tdat_cnt:\t%u\n", emm_sample.s.dat_cnt);

	emm_sts_mask.u64 = mmc_read_csr(CVMX_MIO_EMM_STS_MASK);
	printf("\nMIO_EMM_STS_MASK:\t\t0x%016llx\n", emm_sts_mask.u64);

	emm_rca.u64 = mmc_read_csr(CVMX_MIO_EMM_RCA);
	printf("\nMIO_EMM_RCA:\t\t\t0x%016llx\n", emm_rca.u64);
	printf("\t0-15:\tcard_rca:\t%u\n", emm_rca.s.card_rca);
	puts("\n");
#endif /* DEBUG */
}

struct mmc *find_mmc_device(int dev_num)
{
	struct mmc *m;
	struct list_head *entry;

	debug("%s(%d)\n", __func__, dev_num);
	/* If nothing is available, try and initialize */
	if (list_empty(&mmc_devices)) {
		debug("MMC device not found, initializing\n");
		if (mmc_initialize(gd->bd))
			return NULL;
	}

	list_for_each(entry, &mmc_devices) {
		m = list_entry(entry, struct mmc, link);
		debug("  testing MMC dev %d == %d\n",
		      m->block_dev.dev, dev_num);
		if (m->block_dev.dev == dev_num)
			return m;
	}

	printf("MMC Device %d not found\n", dev_num);

	return NULL;
}

/**
 * Enables the MMC bus, disabling NOR flash and other boot bus device access
 *
 * @param mmc - bus to enable
 */
static void mmc_enable(struct mmc *mmc)
{
	cvmx_mio_emm_cfg_t emm_cfg;
	struct mmc_host *host = mmc->priv;

	emm_cfg.u64 = cvmx_read_csr(CVMX_MIO_EMM_CFG);
	emm_cfg.s.bus_ena |= 1 <<host->bus_id;
	cvmx_write_csr(CVMX_MIO_EMM_CFG, emm_cfg.u64);
	debug("%s(%d)\n", __func__, host->bus_id);
}

/**
 * Disables the MMC bus, enabling NOR flash and other boot bus device access
 *
 * @param mmc - bus to disable
 */
static void mmc_disable(struct mmc *mmc)
{
	cvmx_mio_emm_cfg_t emm_cfg;
	struct mmc_host *host = mmc->priv;
	debug("%s(%d):\n", __func__, host->bus_id);
	emm_cfg.u64 = cvmx_read_csr(CVMX_MIO_EMM_CFG);
	emm_cfg.s.bus_ena &= ~(1 <<host->bus_id);
	debug("before:\n");
	mmc_print_registers(mmc);
	cvmx_write_csr(CVMX_MIO_EMM_CFG, emm_cfg.u64);
	debug("after:\n");
	mmc_print_registers(mmc);
	last_bus_id = -1;
}

/**
 * Sets the hardware MMC watchdog in microseconds
 *
 * @param[in]	mmc	pointer to MMC data structure
 * @param	timeout	How long to wait in usecs
 */
static void mmc_set_watchdog(const struct mmc *mmc, ulong timeout)
{
	cvmx_mio_emm_wdog_t emm_wdog;

	emm_wdog.u64 = 0;
	emm_wdog.s.clk_cnt = (u64)timeout * mmc->clock / 1000000;
	cvmx_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);
}

/**
 * This function must be called when it is possible that the MMC bus has changed
 *
 * @param mmc - pointer to MMC data structure
 */
static inline void mmc_switch_dev(struct mmc *mmc)
{
	cvmx_mio_emm_switch_t emm_switch;
	cvmx_mio_emm_wdog_t emm_wdog;
	cvmx_mio_emm_sample_t emm_sample;
	cvmx_mio_emm_rca_t emm_rca;
	cvmx_mio_emm_sts_mask_t emm_sts_mask;

	struct mmc_host *host = (struct mmc_host *)mmc->priv;

	if (host->bus_id == last_bus_id)
		return;

	emm_switch.u64 = mmc_read_csr(CVMX_MIO_EMM_SWITCH);
#ifdef DEBUG
	emm_rca.u64 = mmc_read_csr(CVMX_MIO_EMM_RCA);
	debug("%s: Switching from:\n"
	      "\tbus id: %d, clock period: %d, width: %d, rca: 0x%x, high speed: %d to\n"
	      "\tbus id: %d, clock period: %d, width: %d, rca: 0x%x, high speed: %d\n",
	      __func__, last_bus_id, emm_switch.s.clk_lo * 2,
	      emm_switch.s.bus_width, emm_switch.s.hs_timing,
	      emm_rca.s.card_rca, host->bus_id,
	      host->clk_period, host->bus_width, mmc->rca,
	      !!(mmc->card_caps & MMC_MODE_HS));
#endif
	/* mmc_write_csr(CVMX_MIO_EMM_CFG, 1 << host->bus_id);*/
	emm_switch.s.bus_width = host->bus_width;
	emm_switch.s.hs_timing = !!(mmc->card_caps & MMC_MODE_HS);
	emm_switch.s.clk_hi = (host->clk_period + 1) / 2;
	emm_switch.s.clk_lo = (host->clk_period + 1) / 2;
	emm_switch.s.bus_id = host->bus_id;
	emm_switch.s.power_class = host->power_class;
	debug("%s: Setting MIO_EMM_SWITCH to 0x%llx\n", __func__, emm_switch.u64);
	emm_switch.s.bus_id = 0;
	mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	udelay(100);
	emm_switch.s.bus_id = host->bus_id;
	mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	debug("Switching RCA to 0x%x\n", mmc->rca);
	emm_rca.u64 = 0;
	emm_rca.s.card_rca = mmc->rca;
	mmc_write_csr(CVMX_MIO_EMM_RCA, emm_rca.u64);
	last_bus_id = host->bus_id;
	mdelay(100);
	/* Update the watchdog to 1 second */
	emm_wdog.u64 = 0;
	emm_wdog.s.clk_cnt = mmc->clock / 100;
	cvmx_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);

	emm_sample.u64 = 0;
	emm_sample.s.cmd_cnt = host->cmd_clk_skew;
	emm_sample.s.dat_cnt = host->dat_clk_skew;
	cvmx_write_csr(CVMX_MIO_EMM_SAMPLE, emm_sample.u64);
	/* Set status mask */
	emm_sts_mask.u64 = 0;
	emm_sts_mask.s.sts_msk = 1 << 7 | 1 << 22 | 1 << 23 | 1 << 19;
	mmc_write_csr(CVMX_MIO_EMM_STS_MASK, emm_sts_mask.u64);

	mmc_print_registers(mmc);
}

/**
 * Reads one or more sectors into memory
 *
 * @param mmc	mmc data structure
 * @param src	source sector number
 * @param dst	pointer to destination address to read into
 * @param size	number of sectors to read
 *
 * @return number of sectors read
 */
int mmc_read(struct mmc *mmc, u64 src, uchar *dst, int size)
{
	uint64_t dma_addr;
	cvmx_mio_emm_dma_t emm_dma;
	cvmx_mio_ndf_dma_cfg_t ndf_dma;
	cvmx_mio_ndf_dma_int_t ndf_dma_int;
	cvmx_mio_emm_rsp_sts_t rsp_sts;
	cvmx_mio_emm_int_t emm_int;
	cvmx_mio_emm_sts_mask_t emm_sts_mask;
	cvmx_mio_emm_wdog_t emm_wdog;
	int timeout;
	int dma_retry_count = 0;
	struct mmc_cmd cmd;
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	ulong start_time;

	debug("%s(src: 0x%llx, dst: 0x%p, size: %d)\n", __func__, src, dst, size);
#ifdef DEBUG
	memset(dst, 0xEE, size * mmc->read_bl_len);
#endif
	mmc_switch_dev(mmc);

	debug("Setting block length to %d\n", mmc->read_bl_len);
	if (!IS_SD(mmc) || (IS_SD(mmc) && mmc->high_capacity))
		mmc_set_blocklen(mmc, mmc->read_bl_len);

	/* Clear DMA interrupt */
	ndf_dma_int.u64 = 0;
	ndf_dma_int.s.done = 1;
	mmc_write_csr(CVMX_MIO_NDF_DMA_INT, ndf_dma_int.u64);

	/* Enable appropriate errors */
	emm_sts_mask.u64 = 0;
	emm_sts_mask.s.sts_msk = R1_BLOCK_READ_MASK;
	mmc_write_csr(CVMX_MIO_EMM_STS_MASK, emm_sts_mask.u64);

	dma_addr = cvmx_ptr_to_phys(dst);
	debug("%s: dma address: 0x%llx\n", __func__, dma_addr);

	emm_wdog.u64 = 0;
	emm_wdog.s.clk_cnt = 0x1ffffff;
	cvmx_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);

	ndf_dma.u64 = 0;
	ndf_dma.s.en = 1;
	ndf_dma.s.size = ((uint64_t)(size * mmc->read_bl_len) / 8) - 1;
	ndf_dma.s.adr = dma_addr;
	debug("%s: Writing 0x%llx to mio_ndf_dma_cfg\n", __func__, ndf_dma.u64);
	mmc_write_csr(CVMX_MIO_NDF_DMA_CFG, ndf_dma.u64);

	emm_dma.u64 = 0;
	emm_dma.s.bus_id = host->bus_id;
	emm_dma.s.dma_val = 1;
	emm_dma.s.sector = mmc->high_capacity ? 1 : 0;
	/* NOTE: For SD we can only support multi-block transfers if
	 * bit 33 (CMD_SUPPORT) is set in the SCR register.
	 */
	if ((size > 1)
	    && ((IS_SD(mmc) && (host->flags & OCTEON_MMC_FLAG_SD_CMD23))
		|| !IS_SD(mmc)))
		emm_dma.s.multi = 1;
	else
		emm_dma.s.multi = 0;

	emm_dma.s.block_cnt = size;
	if (!mmc->high_capacity)
		src *= mmc->read_bl_len;
	emm_dma.s.card_addr = src;

	debug("%s: card address: 0x%llx, size: %d, multi: %d\n",
	      __func__, src, size, emm_dma.s.multi);
	/* Clear interrupt */
	emm_int.u64 = mmc_read_csr(CVMX_MIO_EMM_INT);
	mmc_write_csr(CVMX_MIO_EMM_INT, emm_int.u64);

	timeout = 5000 + 1000 * size;
	mmc_set_watchdog(mmc, timeout * 1000 - 1000);

	debug("%s: Writing 0x%llx to mio_emm_dma\n", __func__, emm_dma.u64);
	mmc_write_csr(CVMX_MIO_EMM_DMA, emm_dma.u64);

retry_dma:
	start_time = get_timer(0);
	do {
		ndf_dma_int.u64 = mmc_read_csr(CVMX_MIO_NDF_DMA_INT);

		if (ndf_dma_int.s.done) {
			mmc_write_csr(CVMX_MIO_NDF_DMA_INT, ndf_dma_int.u64);
			break;
		}

		WATCHDOG_RESET();
		udelay(1);
	} while (get_timer(start_time) < timeout);

	rsp_sts.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_STS);

	if (!ndf_dma_int.s.done || timeout <= 0 || rsp_sts.s.dma_val
	    || rsp_sts.s.dma_pend) {
		ndf_dma.u64 = mmc_read_csr(CVMX_MIO_NDF_DMA_CFG);
		emm_dma.u64 = mmc_read_csr(CVMX_MIO_EMM_DMA);
		emm_int.u64 = mmc_read_csr(CVMX_MIO_EMM_INT);
		debug("%s: Error detected:\n", __func__);
		if (timeout <= 0)
			debug("Timed out\n");
		mmc_print_registers(mmc);
		if (timeout <= 0) {
			printf("%s(mmc, 0x%llx, %p, %d)\n",
			       __func__, src, dst, size);
			printf("MMC read DMA timeout, status: 0x%llx, interrupt status: 0x%llx\n",
			       rsp_sts.u64, emm_int.u64);
			printf("\tMIO_EMM_DMA: 0x%llx, last command: %d\n",
			       emm_dma.u64, rsp_sts.s.cmd_idx);
			printf("\tMIO_EMM_RSP_LO: 0x%llx, HI: 0x%llx\n",
			       cvmx_read_csr(CVMX_MIO_EMM_RSP_LO),
			       cvmx_read_csr(CVMX_MIO_EMM_RSP_HI));
		} else {
			if (rsp_sts.s.blk_timeout)
				printf("Block timeout error detected\n");
			if (rsp_sts.s.blk_crc_err)
				printf("Block CRC error detected\n");
		}
		if (dma_retry_count++ < 3) {
			/* DMA still pending, terminate it */
			emm_dma.s.dma_val = 1;
			emm_dma.s.dat_null = 1;
			timeout = 2000 * size;
			cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
			cmd.cmdarg = 0;
			cmd.resp_type = MMC_RSP_R1b;
			if (mmc_send_cmd(mmc, &cmd, NULL, 0))
				printf("Error sending stop transmission cmd\n");
#ifdef DEBUG
			int i;
			for (i = 0; i < 512; i++) {
				if (i % 16 == 0)
					printf("\n0x%03x: ", i);
				if (i % 16 == 8)
					puts("- ");
				printf("%02x ", (uint32_t)dst[i]);
			}
			puts("\n");
#endif
			mmc_write_csr(CVMX_MIO_EMM_DMA, emm_dma.u64);
			debug("Retrying MMC read DMA\n");
			goto retry_dma;
		} else {
			cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
			cmd.cmdarg = 0;
			cmd.resp_type = MMC_RSP_R1b;
			if (mmc_send_cmd(mmc, &cmd, NULL, 0))
				printf("Error sending stop transmission cmd\n");
			printf("mmc read block %llu, size %d DMA failed, terminating...\n",
			       src, size);
			emm_dma.s.dma_val = 1;
			emm_dma.s.dat_null = 1;
			mmc_write_csr(CVMX_MIO_EMM_DMA, emm_dma.u64);
			timeout = 2000 * size;
			do {
				ndf_dma_int.u64 =
					mmc_read_csr(CVMX_MIO_NDF_DMA_INT);
				if (ndf_dma_int.s.done)
					break;
				udelay(1);
			} while (timeout-- > 0);
			if (timeout < 0)
				puts("Error: MMC read DMA failed to terminate!\n");
			return 0;
		}
	}

	if (dma_retry_count)
		debug("Success after %d DMA retries\n", dma_retry_count);

	if (timeout <= 0) {
		printf("MMC read block %llu timed out\n", src);
		debug("Read status 0x%llx\n", rsp_sts.u64);
		emm_dma.u64 = mmc_read_csr(CVMX_MIO_EMM_DMA);
		debug("EMM_DMA: 0x%llx\n", emm_dma.u64);

		cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
		cmd.cmdarg = 0;
		cmd.resp_type = MMC_RSP_R1b;
		if (mmc_send_cmd(mmc, &cmd, NULL, 0))
			printf("Error sending stop transmission cmd\n");
		return 0;
	}
	debug("Read status 0x%llx\n", rsp_sts.u64);

	emm_dma.u64 = mmc_read_csr(CVMX_MIO_EMM_DMA);
	debug("EMM_DMA: 0x%llx\n", emm_dma.u64);
#ifdef DEBUG
	int i;
	for (i = 0; i < 512; i++) {
		if (i % 16 == 0)
			printf("\n0x%03x: ", i);
		if (i % 16 == 8)
			puts("- ");
		printf("%02x ", (uint32_t)dst[i]);
	}
	puts("\n");
#endif
	return size - emm_dma.s.block_cnt;
}

/**
 * Writes sectors to MMC device
 *
 * @param[in,out] mmc - MMC device to write to
 * @param start - starting sector to write to
 * @param size - number of sectors to write
 * @param src - pointer to source address of buffer containing sectors
 *
 * @return number of sectors or 0 if none.
 *
 * NOTE: This checks the GPIO write protect if it is present
 */
static ulong
mmc_write(struct mmc *mmc, ulong start, int size, const void *src)
{
	uint64_t dma_addr;
	cvmx_mio_emm_dma_t emm_dma;
	cvmx_mio_ndf_dma_cfg_t ndf_dma;
	cvmx_mio_ndf_dma_int_t ndf_dma_int;
	cvmx_mio_emm_rsp_sts_t rsp_sts;
	cvmx_mio_emm_int_t emm_int;
	cvmx_mio_emm_sts_mask_t emm_sts_mask;
	cvmx_mio_emm_buf_idx_t emm_buf_idx;
	struct mmc_cmd cmd;
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	int timeout;
	int dma_retry_count = 0;
	int rc;
	int multi;
	ulong start_time;
	int timed_out = 0;

	debug("%s(start: %lu, size: %d, src: 0x%p)\n", __func__, start,
	      size, src);

	mmc_switch_dev(mmc);

	/* Poll for ready status */
	timeout = 10000;	/* 10 seconds */
	start_time = get_timer(0);
	do {
		memset(&cmd, 0, sizeof(cmd));
		cmd.cmdidx = MMC_CMD_SEND_STATUS;
		cmd.cmdarg = mmc->rca << 16;
		cmd.resp_type = MMC_RSP_R1;
		rc = mmc_send_cmd(mmc, &cmd, NULL, 0);
		if (rc) {
			printf("%s: Error getting device status\n", __func__);
			return 0;
		} else if (cmd.response[0] & R1_READY_FOR_DATA) {
			break;
		}
		udelay(1);
	} while (get_timer(start_time) < timeout);
	debug("%s: Device status: 0x%x\n", __func__, cmd.response[0]);
	if (timeout == 0) {
		printf("%s: Device timed out waiting for empty buffer, response: 0x%x\n",
		       __func__, cmd.response[0]);
		return 0;
	}

	/* NOTE: For SD we can only support multi-block transfers if
	 * bit 33 (CMD_SUPPORT) is set in the SCR register.
	 */
	multi = ((size > 1)
		 && ((IS_SD(mmc) && (host->flags & OCTEON_MMC_FLAG_SD_CMD23))
		     || !IS_SD(mmc)));
	emm_buf_idx.u64 = 0;
	emm_buf_idx.s.inc = 1;
	mmc_write_csr(CVMX_MIO_EMM_BUF_IDX, emm_buf_idx.u64);

	/* Clear DMA interrupt */
	ndf_dma_int.u64 = 0;
	ndf_dma_int.s.done = 1;
	mmc_write_csr(CVMX_MIO_NDF_DMA_INT, ndf_dma_int.u64);

	/* Enable appropriate errors */
	emm_sts_mask.u64 = 0;
	emm_sts_mask.s.sts_msk = R1_BLOCK_WRITE_MASK;
	mmc_write_csr(CVMX_MIO_EMM_STS_MASK, emm_sts_mask.u64);

	if (!IS_SD(mmc) || (IS_SD(mmc) && mmc->high_capacity))
		mmc_set_blocklen(mmc, mmc->write_bl_len);

	dma_addr = cvmx_ptr_to_phys((uchar *)src);

	ndf_dma.u64 = 0;
	ndf_dma.s.en = 1;
	ndf_dma.s.rw = 1;
	ndf_dma.s.clr = 0;
	ndf_dma.s.size = ((uint64_t)(size * 512) / 8) - 1;
	ndf_dma.s.adr = dma_addr;
	debug("%s: Writing 0x%llx to mio_ndf_dma_cfg\n", __func__, ndf_dma.u64);
	debug("DMA address: 0x%llx\n", dma_addr);

	emm_dma.u64 = 0;
	emm_dma.s.bus_id = host->bus_id;
	emm_dma.s.dma_val = 1;
	emm_dma.s.sector = mmc->high_capacity ? 1 : 0;
	emm_dma.s.rw = 1;
	emm_dma.s.rel_wr = 0;
	emm_dma.s.multi = multi;

	if (!mmc->high_capacity)
		start *= mmc->write_bl_len;

	emm_dma.s.block_cnt = size;
	emm_dma.s.card_addr = start;
	/* Clear interrupt */
	ndf_dma_int.u64 = 0;
	ndf_dma_int.s.done = 1;
	mmc_write_csr(CVMX_MIO_NDF_DMA_INT, ndf_dma_int.u64);
	emm_int.u64 = 0;
	emm_int.s.dma_done = 1;
	emm_int.s.cmd_err = 1;
	emm_int.s.dma_err = 1;
	mmc_write_csr(CVMX_MIO_EMM_INT, emm_int.u64);
	debug("%s: Writing 0x%llx to mio_emm_dma\n", __func__, emm_dma.u64);
	mmc_write_csr(CVMX_MIO_NDF_DMA_CFG, ndf_dma.u64);
	mmc_write_csr(CVMX_MIO_EMM_DMA, emm_dma.u64);

	timeout = 500000 + 1000 * size;
	mmc_set_watchdog(mmc, timeout - 1000);
retry_dma:

	start_time = get_timer(0);
	do {
#ifdef DEBUG
		if (ctrlc()) {
			printf("Interrupted by user\n");
			break;
		}
#endif

		rsp_sts.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_STS);
		if (((rsp_sts.s.dma_val == 0) || (rsp_sts.s.dma_pend == 1))
		    && rsp_sts.s.cmd_done)
			break;

		WATCHDOG_RESET();
		udelay(1);
		timed_out = get_timer(start_time) >= timeout;
	} while (!timed_out);
	if (timed_out) {
		printf("%s: write command completion timeout for cmd %d\n",
		       __func__, rsp_sts.s.cmd_idx);
	}
	/*rsp_sts.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_STS);*/
	debug("emm_rsp_sts: 0x%llx, cmd: %d, response: 0x%llx\n",
	      rsp_sts.u64, rsp_sts.s.cmd_idx,
	      mmc_read_csr(CVMX_MIO_EMM_RSP_LO));
	if (rsp_sts.s.cmd_val || timeout <= 0 || rsp_sts.s.dma_val
	    || rsp_sts.s.dma_pend) {
		emm_dma.u64 = mmc_read_csr(CVMX_MIO_EMM_DMA);
		emm_int.u64 = mmc_read_csr(CVMX_MIO_EMM_INT);
		printf("%s: Error detected: MIO_EMM_RSP_STS: 0x%llx, "
		       "MIO_EMM_DMA: 0x%llx,\n\tMIO_NDF_DMA_CFG: 0x%llx, timeout: %d\n",
		       __func__, rsp_sts.u64, emm_dma.u64,
		       mmc_read_csr(CVMX_MIO_NDF_DMA_CFG), timeout);
		printf("Last command index: %d\n", rsp_sts.s.cmd_idx);
		printf("emm_int: 0x%llx\n", emm_int.u64);
		mdelay(10);
		rsp_sts.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_STS);
		printf("Re-read rsp_sts: 0x%llx, cmd_idx: %d\n", rsp_sts.u64,
		       rsp_sts.s.cmd_idx);
		printf("  RSP_LO: 0x%llx\n", mmc_read_csr(CVMX_MIO_EMM_RSP_LO));
		if (timeout <= 0) {
			printf("%s(mmc, 0x%lx, %d, 0x%p)\n",
			       __func__, start, size, src);
			printf("MMC write DMA timeout, status: 0x%llx, interrupt status: 0x%llx\n",
			       rsp_sts.u64, emm_int.u64);
			printf("\tMIO_EMM_DMA: 0x%llx, last command: %d\n",
			       emm_dma.u64, rsp_sts.s.cmd_idx);
		} else {
			if (rsp_sts.s.blk_timeout)
				printf("Block timeout error detected\n");
			if (rsp_sts.s.blk_crc_err)
				printf("Block CRC error detected\n");
			if (rsp_sts.s.dma_val) {
				printf("DMA still valid\n");
			}
		}

		if (dma_retry_count++ < 3 && rsp_sts.s.dma_pend) {
			/* DMA still pending, terminate it */
			emm_dma.s.dma_val = 1;
			timeout = 2000 * size;
			cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
			cmd.cmdarg = 0;
			cmd.resp_type = MMC_RSP_R1b;
			mmc_send_cmd(mmc, &cmd, NULL, 0);
			mmc_write_csr(CVMX_MIO_EMM_DMA, emm_dma.u64);
			debug("Retrying MMC write DMA\n");
			goto retry_dma;
		} else {
			emm_dma.s.dma_val = 1;
			emm_dma.s.dat_null = 1;
			mmc_write_csr(CVMX_MIO_EMM_DMA, emm_dma.u64);
			timeout = 2000 * size;
			do {
				ndf_dma_int.u64 =
					mmc_read_csr(CVMX_MIO_NDF_DMA_INT);
				if (ndf_dma_int.s.done)
					break;
				udelay(1);
			} while (--timeout > 0);
			if (timeout <= 0)
				puts("Error: MMC write DMA failed to terminate!\n");
			return 0;
		}
	}

	if (dma_retry_count)
		debug("Success after %d DMA retries\n", dma_retry_count);

	if (timeout <= 0) {
		printf("MMC write block %lu timed out\n", start);
		debug("Write status 0x%llx\n", rsp_sts.u64);
		emm_dma.u64 = mmc_read_csr(CVMX_MIO_EMM_DMA);
		debug("EMM_DMA: 0x%llx\n", emm_dma.u64);

		cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
		cmd.cmdarg = 0;
		cmd.resp_type = MMC_RSP_R1b;
		if (mmc_send_cmd(mmc, &cmd, NULL, 0))
			printf("Error sending stop transmission cmd\n");
		return 0;
	}
	debug("Write status 0x%llx\n", rsp_sts.u64);

#if 1
	/* Poll status if we can't send data right away */
	if (!((timeout > 0)
	     && (rsp_sts.s.cmd_idx == MMC_CMD_SEND_STATUS)
	     && rsp_sts.s.cmd_done
	     && ((mmc_read_csr(CVMX_MIO_EMM_RSP_LO) >> 8) & R1_READY_FOR_DATA))) {
		/* Poll for ready status */
		timeout = 10000;	/* 10 seconds */
		do {
			memset(&cmd, 0, sizeof(cmd));
			cmd.cmdidx = MMC_CMD_SEND_STATUS;
			cmd.cmdarg = mmc->rca << 16;
			cmd.resp_type = MMC_RSP_R1;
			rc = mmc_send_cmd(mmc, &cmd, NULL, 0);
			if (rc) {
				printf("%s: Error getting post device status\n",
				       __func__);
				return 0;
			}
			if (cmd.response[0] & R1_READY_FOR_DATA)
				break;
			mdelay(1);
		} while (--timeout > 0);
		if (timeout == 0) {
			printf("%s: Device timed out waiting for empty buffer\n",
			       __func__);
			return 0;
		}
	}
#endif
	emm_dma.u64 = mmc_read_csr(CVMX_MIO_EMM_DMA);
	debug("EMM_DMA: 0x%llx\n", emm_dma.u64);

	return size - emm_dma.s.block_cnt;
}

static ulong mmc_erase_t(struct mmc *mmc, ulong start, lbaint_t blkcnt)
{
	struct mmc_cmd cmd;
	ulong end;
	int err, start_cmd, end_cmd;

	if (mmc->high_capacity)
		end = start + blkcnt - 1;
	else {
		end = (start + blkcnt - 1) * mmc->write_bl_len;
		start *= mmc->write_bl_len;
	}

	if (!mmc_getcd(mmc)) {
		printf("%s: Error: Card not detected\n", __func__);
		return 0;
	}

	if (IS_SD(mmc)) {
		start_cmd = SD_CMD_ERASE_WR_BLK_START;
		end_cmd = SD_CMD_ERASE_WR_BLK_END;
	} else {
		start_cmd = MMC_CMD_ERASE_GROUP_START;
		end_cmd = MMC_CMD_ERASE_GROUP_END;
	}

	cmd.cmdidx = start_cmd;
	cmd.cmdarg = start;
	cmd.resp_type = MMC_RSP_R1;

	err = mmc_send_cmd(mmc, &cmd, NULL, 0);
	if (err)
		goto err_out;

	cmd.cmdidx = end_cmd;
	cmd.cmdarg = end;
	cmd.resp_type = MMC_RSP_R1b;

	err = mmc_send_cmd(mmc, &cmd, NULL, 0);
	if (err)
		goto err_out;

	return 0;

err_out:
	puts("mmc erase failed\n");
	return err;
}

/**
 * Reads blkcnt sectors from the specified device into the specified buffer
 * @param dev_num	Device number to read from
 * @param start		Starting sector number
 * @param blkcnt	Number of sectors to read
 * @param[out] dst	Pointer to buffer to contain the data
 *
 * @return number of blocks read or 0 if error
 */
static ulong mmc_bread(int dev_num, lbaint_t start, lbaint_t blkcnt, void *dst)
{
	lbaint_t cur, blocks_todo = blkcnt;
	struct mmc *mmc = find_mmc_device(dev_num);
	unsigned char bounce_buffer[4096];

	debug("%s(%d, %llu, %llu, %p)\n", __func__, dev_num, start,
	      (uint64_t)blkcnt, dst);
	if (!mmc)
		return 0;

	if (blkcnt == 0)
		return 0;

	if ((start + blkcnt) > mmc->block_dev.lba) {
		printf("MMC: block number 0x%llx exceeds max(0x%llx)\n",
		       (uint64_t)(start + blkcnt),
		       (uint64_t)mmc->block_dev.lba);
		return 0;
	}

	if (!mmc_getcd(mmc)) {
		printf("%s: Error: Card not detected\n", __func__);
		return 0;
	}

	mmc_enable(mmc);
	if (((ulong)dst) & 7) {
		debug("%s: Using bounce buffer due to alignment\n", __func__);
		do {
			if (mmc_read(mmc, start, bounce_buffer, 1) != 1)
				return 0;
			memcpy(dst, bounce_buffer, mmc->read_bl_len);
			WATCHDOG_RESET();
			dst += mmc->read_bl_len;
			start++;
			blocks_todo--;
		} while (blocks_todo > 0);
	} else {
		do {
			cur = min(blocks_todo, mmc->b_max);
			if (mmc_read(mmc, start, dst, cur) != cur) {
				blkcnt = 0;
				break;
			}
			WATCHDOG_RESET();
			blocks_todo -= cur;
			start += cur;
			dst += cur * mmc->read_bl_len;
		} while (blocks_todo > 0);
	}
	mmc_disable(mmc);

	return blkcnt;
}

/**
 * Writes blkcnt sectors to the specified device from the specified buffer
 * @param dev_num	Device number to write to
 * @param start		Starting sector number
 * @param blkcnt	Number of sectors to write
 * @param[in] src	Pointer to buffer that contains the data
 *
 * @return number of blocks written or 0 if error
 */
static ulong mmc_bwrite(int dev_num, lbaint_t start, lbaint_t blkcnt,
			const void *src)
{
	lbaint_t cur, blocks_todo = blkcnt;
	struct mmc *mmc = find_mmc_device(dev_num);
	unsigned char bounce_buffer[4096];

	debug("%s(%d, %llu, %llu, %p)\n", __func__, dev_num, start,
	      (uint64_t)blkcnt, src);
	if (!mmc) {
		printf("MMC Write: device %d not found\n", dev_num);
		return 0;
	}

	if (blkcnt == 0)
		return 0;
	if ((start + blkcnt) > mmc->block_dev.lba) {
		printf("MMC: block number 0x%llx exceeds max(0x%llx)\n",
		       (uint64_t)(start + blkcnt),
		       (uint64_t)mmc->block_dev.lba);
		return 0;
	}
	if (!mmc_getcd(mmc)) {
		printf("%s: Error: Card not detected\n", __func__);
			return 0;
		}

	if (mmc_getwp(mmc)) {
		printf("%s: Failed due to write protect switch\n", __func__);
			return 0;
		}
	mmc_enable(mmc);
	if (((ulong)src) & 7) {
		debug("%s: Using bounce buffer due to alignment\n", __func__);
		do {
			memcpy(bounce_buffer, src, mmc->write_bl_len);
			if (mmc_write(mmc, start, 1, bounce_buffer) != 1)
				return 0;
			WATCHDOG_RESET();
			src += mmc->write_bl_len;
			start++;
			blocks_todo--;
		} while (blocks_todo > 0);
	} else {
		do {
			ulong ret;
			cur = min(blocks_todo, mmc->b_max);
			ret = mmc_write(mmc, start, cur, src);
			if (ret != cur) {
				printf("%s: ERROR: Not enough blocks written (%lu != %lu)\n",
				       __func__, ret, (long unsigned int)cur);
				blkcnt = 0;
				break;
			}
			WATCHDOG_RESET();
			blocks_todo -= cur;
			start += cur;
			src += cur * mmc->write_bl_len;
		} while (blocks_todo > 0);
	}
	mmc_disable(mmc);
	return blkcnt;
}

static ulong
mmc_berase(int dev_num, lbaint_t start, lbaint_t blkcnt)
{
	int err = 0;
	struct mmc *mmc = find_mmc_device(dev_num);
	lbaint_t blk = 0, blk_r = 0;

	if (!mmc)
		return 0;

	if ((start % mmc->erase_grp_size) || (blkcnt % mmc->erase_grp_size))
		printf("\n\nCaution!  Your device's erase group is 0x%x\n"
		       "The erase range would be changed to 0x%llx~0x%llx\n\n",
		       mmc->erase_grp_size,
		       (uint64_t)(start & ~(mmc->erase_grp_size - 1)),
		       (uint64_t)((start + blkcnt + mmc->erase_grp_size)
				  & ~(mmc->erase_grp_size - 1)) - 1);

	mmc_enable(mmc);
	while (blk < blkcnt) {
		blk_r = ((blkcnt - blk) > mmc->erase_grp_size) ?
			mmc->erase_grp_size : (blkcnt - blk);
		err = mmc_erase_t(mmc, start + blk, blk_r);
		if (err)
			break;

		blk += blk_r;
	}
	mmc_disable(mmc);

	return blk;
}

int mmc_register(struct mmc *mmc)
{
	int i;
	int found_free = 0;
	const struct mmc *fmmc = NULL;

	/* First try and find a free device number to use */
	for (i = 1; i < init_dev_num; i++) {
		fmmc = find_mmc_device(i);
		if (fmmc == mmc) {
			/* We're already registered, use existing dev */
			break;
		} else if (!fmmc) {
			mmc->block_dev.dev = i;
			found_free = 1;
			debug("%s: Found free device %d\n", __func__, i);
			break;
		}
	}
	/* Otherwise allocate a new one */
	if (!found_free) {
		debug("%s: Allocating new device %d\n", __func__, init_dev_num);
		mmc->block_dev.dev = init_dev_num++;
	}
	if (cur_dev_num < 0)
		mmc_set_dev(mmc->block_dev.dev);

	mmc->block_dev.if_type = IF_TYPE_MMC;
	debug("%s: Registering mmc device %d\n", __func__, mmc->block_dev.dev);
	mmc->block_dev.removable = 1;
	mmc->block_dev.block_read = mmc_bread;
	mmc->block_dev.block_write = mmc_bwrite;
	mmc->block_dev.block_erase = mmc_berase;
	if (!mmc->b_max)
		mmc->b_max = CONFIG_SYS_MMC_MAX_BLK_COUNT;

	INIT_LIST_HEAD(&mmc->link);

	if (mmc != fmmc)
		list_add_tail(&mmc->link, &mmc_devices);

	return 0;
}

void print_mmc_devices(char separator)
{
	struct mmc *m;
	struct list_head *entry;

        /* If nothing is available, try and initialize */
        if (list_empty(&mmc_devices))
                mmc_initialize(gd->bd);

        list_for_each(entry, &mmc_devices) {
		m = list_entry(entry, struct mmc, link);
		printf("%s: %d", m->name, m->block_dev.dev);
		if (entry->next != &mmc_devices)
			printf("%c ", separator);
	}
	printf("\n");
}

void print_mmc_device_info(struct mmc *mmc)
{
	struct mmc_host *host;
	const char *type;
	const char *version;
	uint32_t card_type;
	int prev = 0;
	int i;
	static const char *cbx_str[4] = {
		"Card (removable)",
		"BGA (Discrete embedded)",
		"POP",
		"Reserved"
	};

	host = (struct mmc_host *)mmc->priv;
	card_type = host->ext_csd[EXT_CSD_CARD_TYPE];
	if (IS_SD(mmc)) {
		if (mmc->high_capacity)
			type = "SDHC or SDXC";
		else
			type = "SD";
	} else {
		type = "MMC";
	}

	switch (mmc->version) {
#ifdef CONFIG_OCTEON_MMC_SD
	case SD_VERSION_2:
	case SD_VERSION_3:
		if (mmc->scr[0] & (1 << 16)) {
			if (mmc->scr[0] & (1 << 10))
				version = "SD 4.XX";
			else
				version = "SD 3.0X";
		} else {
			version = "SD 2.00";
		}
		break;
	case SD_VERSION_1_10:		version = "SD 1.10";		break;
	case SD_VERSION_1_0:		version = "SD 1.0";		break;
#endif
	case MMC_VERSION_4:
		switch (host->ext_csd[EXT_CSD_REV]) {
			case 0:		version = "MMC v4.0";		break;
			case 1:		version = "MMC v4.1";		break;
			case 2:		version = "MMC v4.2";		break;
			case 3:		version = "MMC v4.3";		break;
			case 4:		version = "MMC v4.4 (obsolete)";break;
			case 5:		version = "MMC v4.41";		break;
			case 6:		version = "MMC v4.5";		break;
			default:	version = "MMC > v4.5";		break;
		}
		break;
	case MMC_VERSION_3:		version = "MMC 3";		break;
	case MMC_VERSION_2_2:		version = "MMC 2.2";		break;
	case MMC_VERSION_1_4:		version = "MMC 1.4";		break;
	case MMC_VERSION_1_2:		version = "MMC 1.2";		break;
	case MMC_VERSION_UNKNOWN:	version = "MMC Unknown";	break;
	default:			version = "Unknown";		break;
	}

	printf("Name:                  %s\n", mmc->name);
	printf("Type:                  %s\n", type);
	printf("Version:               %s\n", version);
	printf("Manufacturer ID:       0x%02x\n", (mmc->cid[0] >> 24) & 0xff);
	if (IS_SD(mmc)) {
		printf("OEM ID:                %c%c\n",
		       (mmc->cid[0] >> 16) & 0xff, (mmc->cid[0] >> 8) & 0xff);
	} else {
		printf("Device Type:           %s\n",
		       cbx_str[(mmc->cid[0] >> 16) & 3]);
		printf("OEM ID:                0x%02x\n",
		       (mmc->cid[0] >> 8) & 0xff);
	}
	printf("Vendor:                %s\n", mmc->block_dev.vendor);
	printf("Product:               %s\n", mmc->block_dev.product);
	printf("Revision:              %s\n", mmc->block_dev.revision);
	if (IS_SD(mmc)) {
		printf("Manufacturing Date:    %d/%d\n",
		       (mmc->cid[3] >> 8) & 0xf,
		       ((mmc->cid[3] >> 12) & 0xff) + 2000);
	} else {
		int start_year;
		if ((host->ext_csd[EXT_CSD_REV] > 4)
		    && ((mmc->cid[3] >> 8) & 0xf) <= 12)
			start_year = 2013;
	else
			start_year = 1997;
		printf("Manufacturing Date:    %d/%d\n",
		       (mmc->cid[3] >> 12) & 0xf,
		       ((mmc->cid[3] >> 8) & 0xf) + start_year);
	}
	printf("Capacity:              %llu bytes\n", mmc->capacity);
	printf("Read block length:     %u\n", mmc->read_bl_len);
	printf("Write block length:    %u\n", mmc->write_bl_len);
	printf("High capacity:         %s\n", mmc->high_capacity ? "yes" : "no");
	printf("Bus width:             %u bits\n", mmc->bus_width);
	printf("Bus frequency:         %u\n", mmc->clock);
	if (!mmc->card_caps & MMC_MODE_HS)
		printf("Transfer frequency:    %u\n", mmc->tran_speed);
	printf("Bus DDR:               %s\n",
	       ((mmc->host_caps & mmc->card_caps) & MMC_MODE_DDR) ? "yes" : "no");
	if (!IS_SD(mmc))
		printf("Erase group size:      %u\n", mmc->erase_grp_size);
	printf("Relative Card Address: 0x%x\n", mmc->rca);
	if (IS_SD(mmc)) {
		const char *sd_security;
		switch((mmc->scr[0] >> 20) & 7) {
		case 0:
			sd_security = "None";
			break;
		case 1:
			sd_security = "Not Used";
			break;
		case 2:
			sd_security = "SDSC Card (Security Version 1.01)";
			break;
		case 3:
			sd_security = "SDHC Card (Security Version 2.00)";
			break;
		case 4:
			sd_security = "SDXC Card (Security Version 3.xx)";
			break;
		default:
			sd_security = "Reserved/Unknown";
			break;
		}
		printf("SD Security:           %s\n", sd_security);
		if ((mmc->scr[0] >> 11) & 7)
			printf("SD Extended Security supported\n");

		if (mmc->scr[0] & 2)
			printf("SD Set Block Count (CMD23) supported\n");
		if (mmc->scr[0] & 1)
			printf("SDXC Speed Class Control supported\n");
	}
	if (card_type != 0) {
		puts("Supported bus speeds:    ");
		if (card_type & EXT_CSD_CARD_TYPE_26) {
			puts(" 26MHz");
			prev = 1;
		}
		if (card_type & EXT_CSD_CARD_TYPE_52) {
			if (prev)
				putc(',');
			puts(" 52MHz");
			prev = 1;
		}
		if (card_type & EXT_CSD_CARD_TYPE_DDR_1_8V) {
			if (prev)
				putc(',');
			puts(" DDR 1.8V");
			prev = 1;
		}
		if (card_type & EXT_CSD_CARD_TYPE_DDR_1_2V) {
			if (prev)
				putc(',');
			puts(" DDR 1.2V");
			prev = 1;
		}
	}
	if (!IS_SD(mmc)) {
		puts("\nExtended CSD register");
		for (i = 0; i < 512; i++) {
			if (i % 16 == 0)
				printf("\n0x%03x: ", i);
			if (i % 16 == 8)
				puts("- ");
			printf("%02x ", (uint32_t)host->ext_csd[i]);
		}
		puts("\n");
	}
}

int mmc_set_blocklen(struct mmc *mmc, int len)
{
	struct mmc_cmd cmd;
	int err;

	mmc_switch_dev(mmc);

	if (mmc->card_caps & MMC_MODE_DDR) {
		debug("MMC set block length skipped in DDR mode\n");
		return 0;
	}

	cmd.cmdidx = MMC_CMD_SET_BLOCKLEN;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = len;

	debug("%s: Setting block length to %d\n", __func__, len);
	err = mmc_send_cmd(mmc, &cmd, NULL, 0);
	if (err)
		printf("%s: Error setting block length to %d\n", __func__, len);

	return err;
}

int mmc_set_dev(int dev_num)
{
	debug("%s(%d)\n", __func__, dev_num);
	if (dev_num > 0 && dev_num < init_dev_num) {
		cur_dev_num = dev_num;
		return 0;
	} else
		return -1;
}

int __board_mmc_getcd(struct mmc *mmc)
{
	return -1;
}
int board_mmc_getcd(struct mmc *mmc)
	__attribute__((weak, alias("__board_mmc_getcd")));


int mmc_legacy_init(int dev_num)
{
	struct mmc *mmc;
	int rc;

	mmc = find_mmc_device(dev_num);
	if (mmc == NULL) {
		printf("Error: could not find MMC device %d\n", dev_num);
		return -1;
	}
	rc = mmc_init(mmc);
	if (rc) {
		printf("Error: could not initialize MMC device %d\n", dev_num);
	}
	return rc;
}

/* Wait for a command to respond */
static int
oct_mmc_wait_cmd(int bus_id, int cmd_idx, int flags, uint timeout)
{
	cvmx_mio_emm_rsp_sts_t emm_rsp_sts;
	unsigned long base_time;
	ulong time = 0;

	base_time = get_timer(0);

	do {
		emm_rsp_sts.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_STS);
		if (emm_rsp_sts.s.cmd_done || emm_rsp_sts.s.rsp_timeout)
			break;
		WATCHDOG_RESET();
		udelay(1);
		time += 1;
	} while (get_timer(base_time) < timeout + 10);

	debug("%s: bus_id: %d, cmd_idx: %d response is 0x%llx after %lu ms (%lu loops)\n",
	      __func__, bus_id, cmd_idx, emm_rsp_sts.u64, get_timer(base_time),
	      time);
	if (!emm_rsp_sts.s.cmd_done) {
		debug("%s: Wait for command index %d timed out\n",
		      __func__, cmd_idx);
#ifdef DEBUG
		mmc_print_registers(NULL);
#endif
		return TIMEOUT;
	}
	if (bus_id >= 0 && emm_rsp_sts.s.bus_id != bus_id) {
		debug("%s: Mismatch bus_id, expected %d for cmd idx %d, got %d\n",
		      __func__, bus_id, cmd_idx, emm_rsp_sts.s.bus_id);
#ifdef DEBUG
		mmc_print_registers(NULL);
#endif
		return -1;	/* Wrong bus ID */
	}
	if (emm_rsp_sts.s.rsp_timeout
	    || (emm_rsp_sts.s.rsp_crc_err &&
		!(flags & MMC_CMD_FLAG_IGNORE_CRC_ERR))
	    || emm_rsp_sts.s.rsp_bad_sts) {
		uint64_t status = cvmx_read_csr(CVMX_MIO_EMM_RSP_LO) >> 8;
		debug("%s: Bad response for bus id %d, cmd id %d:\n"
		      "\trsp_timeout: %d\n"
		      "\trsp_bad_sts: %d\n"
		      "\trsp_crc_err: %d\n",
		     __func__, bus_id, cmd_idx,
		     emm_rsp_sts.s.rsp_timeout,
		     emm_rsp_sts.s.rsp_bad_sts,
	             emm_rsp_sts.s.rsp_crc_err);
#ifdef DEBUG
		mmc_print_registers(NULL);
#endif
		if (emm_rsp_sts.s.rsp_type == 1 && emm_rsp_sts.s.rsp_bad_sts) {
			debug("\tResponse status: 0x%llx\n", status & 0xffffffff);
#ifdef DEBUG
			mmc_print_status(status);
			mmc_print_registers(NULL);
#endif
		}
		return -1;
	}
	if (emm_rsp_sts.s.cmd_idx != cmd_idx) {
		debug("%s: response for bus id %d, cmd idx %d mismatch command index %d\n",
		      __func__, bus_id, cmd_idx, emm_rsp_sts.s.cmd_idx);
#ifdef DEBUG
		mmc_print_registers(NULL);
#endif
		return -1;
	}
	return 0;
}

#if 0
static int
mmc_wait_cmd(int bus_id, int cmd_idx)
{
	return oct_mmc_wait_cmd(bus_id, cmd_idx, 0);
}
#endif

static int
mmc_send_cmd_timeout(struct mmc *mmc, struct mmc_cmd *cmd,
		     struct mmc_data *data,
		     uint32_t flags, uint timeout)
{
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	cvmx_mio_emm_cmd_t emm_cmd;
	cvmx_mio_emm_buf_idx_t emm_buf_idx;
	cvmx_mio_emm_buf_dat_t emm_buf_dat;
	cvmx_mio_emm_wdog_t emm_wdog;
	u64 resp_lo;
	u64 resp_hi;
	int i;
	int bus_id = host->bus_id;

	if (bus_id != last_bus_id)
		mmc_switch_dev(mmc);

	/* Set the hardware timeout */
	emm_wdog.u64 = 0;
	emm_wdog.s.clk_cnt = timeout * mmc->clock / 1000;
	cvmx_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);

	/* Clear any interrupts */
	mmc_write_csr(CVMX_MIO_EMM_INT, mmc_read_csr(CVMX_MIO_EMM_INT));
	emm_cmd.u64 = 0;
	emm_cmd.s.cmd_val = 1;
	emm_cmd.s.bus_id = bus_id;
	emm_cmd.s.cmd_idx = cmd->cmdidx;
	emm_cmd.s.arg = cmd->cmdarg;
	emm_cmd.s.ctype_xor = (flags >> 16) & 3;
	emm_cmd.s.rtype_xor = (flags >> 20) & 7;
	emm_cmd.s.offset = (flags >> 24) & 0x3f;

	debug("mmc cmd: %d, arg: 0x%x flags: 0x%x reg: 0x%llx\n",
	      cmd->cmdidx, cmd->cmdarg, flags, emm_cmd.u64);

	if (data && data->flags & MMC_DATA_WRITE) {
		const char *src = data->src;
		if (!src) {
			printf("%s: Error, source buffer is NULL\n", __func__);
			return -1;
		}
		if (data->blocksize > 512) {
			printf("%s: Error: data size %u exceeds 512\n",
			       __func__, data->blocksize);
		}
		emm_buf_idx.u64 = 0;
		emm_buf_idx.s.inc = 1;
		mmc_write_csr(CVMX_MIO_EMM_BUF_IDX, emm_buf_idx.u64);
		for (i = 0; i < (data->blocksize + 7) / 8; i++) {
			memcpy(&emm_buf_dat.u64, src, sizeof(emm_buf_dat));
			mmc_write_csr(CVMX_MIO_EMM_BUF_DAT, emm_buf_dat.u64);
			debug("mmc cmd: buffer 0x%x: 0x%llx\n",
			      i*8, emm_buf_dat.u64);
			src += sizeof(emm_buf_dat);
		}
		debug("mmc cmd: wrote %d 8-byte blocks to buffer\n", i);
	}
	mmc_write_csr(CVMX_MIO_EMM_CMD, emm_cmd.u64);

	if (oct_mmc_wait_cmd(bus_id, cmd->cmdidx, flags, timeout)) {
		if (!init_time)
			debug("mmc cmd: Error waiting for bus %d, command index %d to complete\n",
			       bus_id, cmd->cmdidx);
		return TIMEOUT;
	}
	debug("%s: Response flags: 0x%x\n", __func__, cmd->resp_type);
	if (!cmd->resp_type & MMC_RSP_PRESENT) {
		debug("%s: no response expected for command index %d, returning\n",
		      __func__, cmd->cmdidx);
		return 0;
	}

	resp_lo = mmc_read_csr(CVMX_MIO_EMM_RSP_LO);
	if (cmd->resp_type & MMC_RSP_136) {
		resp_hi = mmc_read_csr(CVMX_MIO_EMM_RSP_HI);
		debug("mmc cmd: response hi: 0x%016llx\n", resp_hi);
		cmd->response[0] = resp_hi >> 32;
		cmd->response[1] = resp_hi & 0xffffffff;
		cmd->response[2] = resp_lo >> 32;
		cmd->response[3] = resp_lo & 0xffffffff;
	} else if ((cmd->resp_type & MMC_RSP_CRC)
		   || (flags & MMC_CMD_FLAG_STRIP_CRC)) {	/* No CRC */
		cmd->response[0] = (resp_lo >> 8) & 0xffffffff;
	} else {
		cmd->response[0] = resp_lo & 0xffffffff;
	}
	debug("mmc cmd: response lo: 0x%016llx\n", resp_lo);
	if (data && data->flags & MMC_DATA_READ) {
		char *dest = data->dest;

		if (!dest) {
			printf("%s: Error, destination buffer NULL!\n",
			       __func__);
			return -1;
		}
		if (data->blocksize > 512) {
			printf("%s: Error: data size %u exceeds 512\n",
			       __func__, data->blocksize);
		}
		emm_buf_idx.u64 = 0;
		emm_buf_idx.s.inc = 1;
		mmc_write_csr(CVMX_MIO_EMM_BUF_IDX, emm_buf_idx.u64);
		for (i = 0; i < (data->blocksize + 7) / 8; i++) {
			emm_buf_dat.u64 = mmc_read_csr(CVMX_MIO_EMM_BUF_DAT);
			memcpy(dest, &emm_buf_dat.u64, sizeof(emm_buf_dat));
			       dest += sizeof(emm_buf_dat);
		}
	}
	return 0;
}

static int mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data, uint32_t flags)
{
	uint timeout;
	/**
	 * This constant has a 1 bit for each command which should have a short
	 * timeout and a 0 for each bit with a long timeout.  Currently the
	 * following commands have a long timeout:
	 *   CMD6, CMD17, CMD18, CMD24, CMD25, CMD32, CMD33, CMD35, CMD36 and
	 *   CMD38.
	 */
	static const uint64_t timeout_short = 0xFFFFFFA4FCF9FFDFULL;

	if (cmd->cmdidx >= 64) {
		printf("%s: Error: command index %d is out of range\n",
		       __func__, cmd->cmdidx);
		return -1;
	}
	if (timeout_short & (1ULL << cmd->cmdidx))
		timeout = MMC_TIMEOUT_SHORT;
	else if (cmd->cmdidx == 6 && IS_SD(mmc))
		timeout = 2560;
	else
		timeout = MMC_TIMEOUT_LONG;
	return mmc_send_cmd_timeout(mmc, cmd, data, flags, timeout);
}


static int mmc_send_acmd(struct mmc *mmc, struct mmc_cmd *cmd,
			 struct mmc_data *data, uint32_t flags)
{
	struct mmc_cmd acmd;
	int err;

	acmd.cmdidx = MMC_CMD_APP_CMD;
	acmd.cmdarg = mmc->rca << 16;
	acmd.resp_type = MMC_RSP_R1;

	if (!IS_SD(mmc)) {
		debug("%s: Error, not SD card\n", __func__);
		return -1;
	}
	err = mmc_send_cmd(mmc, &acmd, NULL, 0);
	if (err) {
		printf("%s: Error sending ACMD to SD card\n", __func__);
		return err;
	}
	if (cmd)
		return mmc_send_cmd(mmc, cmd, data, flags);
	else
		return 0;
}

/* Change the bus width */
static void mmc_set_bus_width(struct mmc *mmc, uint width)
{
	mmc->bus_width = width;
}

static int mmc_pre_idle(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int err;

	cmd.cmdidx = MMC_CMD_GO_IDLE_STATE;
	cmd.cmdarg = 0xf0f0f0f0;	/* Software Reset */
	cmd.resp_type = MMC_RSP_NONE;

	err = mmc_send_cmd(mmc, &cmd, NULL, 0);
	if (err)
		debug("%s: error %d\n", __func__, err);
	else
		mdelay(20);
	return err;
}

static int mmc_go_idle(struct mmc* mmc)
{
	struct mmc_cmd cmd;
	int err;
	int i;

	for (i = 0; i < 5; i++) {
		debug("%s: Going idle try %d\n", __func__, i);
		/* Do this 5 times to clear the bus */
		cmd.cmdidx = MMC_CMD_GO_IDLE_STATE;
		cmd.cmdarg = 0;
		cmd.resp_type = MMC_RSP_NONE;

		err = mmc_send_cmd(mmc, &cmd, NULL, 0);
		if (err)
			return err;
	}
	mdelay(20);	/* Wait 20ms */
	return 0;
}

#ifdef CONFIG_OCTEON_MMC_SD
static int sd_send_relative_addr(struct mmc *mmc)
{
	int err;
	struct mmc_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.cmdidx = SD_CMD_SEND_RELATIVE_ADDR;
	cmd.cmdarg = 0;
	cmd.resp_type = MMC_RSP_R6;
	err = mmc_send_cmd_timeout(mmc, &cmd, NULL, MMC_CMD_FLAG_RTYPE_XOR(2), 2);
	if (err) {
		printf("%s: error sending command\n", __func__);
		return err;
	}
	mmc->rca = cmd.response[0] >> 16;
	mmc_write_csr(CVMX_MIO_EMM_RCA, mmc->rca);
	debug("%s: SD RCA is %d (0x%x)\n", __func__, mmc->rca, mmc->rca);
	debug("%s: MIO_EMM_RCA: 0x%llx\n", __func__,
	      cvmx_read_csr(CVMX_MIO_EMM_RCA));
	return 0;
}
#endif

static int mmc_set_relative_addr(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));

	cmd.cmdidx = MMC_CMD_SET_RELATIVE_ADDR;
	cmd.cmdarg = mmc->rca << 16;
	cmd.resp_type = MMC_RSP_R1;
	err = mmc_send_cmd(mmc, &cmd, NULL, 0);
	if (err)
		printf("%s: Failed to set RCA to %d\n", __func__, mmc->rca);

	return err;
}

static int mmc_select_card(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int err;

	debug("%s: entry\n", __func__);
	memset(&cmd, 0, sizeof(cmd));

	cmd.cmdidx = MMC_CMD_SELECT_CARD;
	cmd.resp_type = MMC_RSP_R1b;
	cmd.cmdarg = mmc->rca << 16;

	err = mmc_send_cmd(mmc, &cmd, NULL, 0);
	if (err)
		printf("%s: Error selecting card with rca %d\n",
		       __func__, mmc->rca);
	else
		mmc_write_csr(CVMX_MIO_EMM_RCA, mmc->rca);
	return err;
}

static int mmc_all_send_cid(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));

	debug("%s: Getting CID\n", __func__);
	cmd.cmdidx = MMC_CMD_ALL_SEND_CID;
	cmd.resp_type = MMC_RSP_R2;
	cmd.cmdarg = 0;
	err = mmc_send_cmd(mmc, &cmd, NULL, 0);
	if (err) {
		printf("%s: Error getting all CID\n", __func__);
		return err;
	}

	memcpy(mmc->cid, &cmd.response[0], 16);
#ifdef DEBUG
	print_buffer(0, mmc->cid, 1, 16, 0);
	debug("\tManufacturer: 0x%x\n", mmc->cid[0] >> 24);
	if (!IS_SD(mmc)) {
		debug("\tDevice/BGA:   ");
		switch ((mmc->cid[0] >> 16) & 3) {
		case 0:
			debug("Device (removable)\n");
			break;
		case 1:
			debug("BGA (Discrete embedded)\n");
			break;
		case 2:
			debug("POP\n");
			break;
		default:
			debug("Reserved\n");
			break;
		}
	}
	if (IS_SD(mmc)) {
		debug("\tOID:          %02x%02x\n", (mmc->cid[0] >> 16) & 0xff,
		      (mmc->cid[0] >> 8) & 0xff);
		debug("\tProduct Name: %c%c%c%c%c\n", mmc->cid[0] & 0xff,
		      (mmc->cid[1] >> 24) & 0xff, (mmc->cid[1] >> 16) & 0xff,
		      (mmc->cid[1] >> 8) & 0xff, mmc->cid[1] & 0xff);
		debug("\tProduct Revision: %d.%d\n",
		      (mmc->cid[2] >> 20) & 0xf, (mmc->cid[2] >> 16) & 0xf);
		debug("\tProduct Serial Number: 0x%x\n",
		      ((mmc->cid[2] & 0xffffff) << 8) | ((mmc->cid[3] >> 24) & 0xff));
		debug("\tManufacturing Date: %d/%d\n", (mmc->cid[3] >> 8) & 0xf,
		      ((mmc->cid[3] >> 12) & 0xff) + 2000);
	} else {
		debug("\tOID:          0x%x\n", (mmc->cid[0] >> 8) & 0xFF);
		debug("\tProduct Name: %c%c%c%c%c%c\n", mmc->cid[0] & 0xff,
		      (mmc->cid[1] >> 24) & 0xff, (mmc->cid[1] >> 16) & 0xff,
		      (mmc->cid[1] >> 8) & 0xff, mmc->cid[1] & 0xff,
		      (mmc->cid[2] >> 24) & 0xff);
		debug("\tProduct Revision: %d.%d\n",
		      (mmc->cid[2] >> 20) & 0xf, (mmc->cid[2] >> 16) & 0xf);
		debug("\tProduct Serial Number: 0x%x\n",
		      ((mmc->cid[2] & 0xffff) << 16) | ((mmc->cid[3] >> 16) & 0xffff));
		debug("\tManufacturing Date: %d/%d\n", (mmc->cid[3] >> 12) & 0xf,
		      ((mmc->cid[3] >> 8) & 0xf) + 1997);
	}
#endif
	return 0;
}

static int mmc_get_csd(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));

	cmd.cmdidx = MMC_CMD_SEND_CSD;
	cmd.resp_type = MMC_RSP_R2;
	cmd.cmdarg = mmc->rca << 16;
	err = mmc_send_cmd(mmc, &cmd, NULL, 0);
	if (err) {
		printf("%s: Error getting CSD\n", __func__);
		return err;
	}
	mmc->csd[0] = cmd.response[0];
	mmc->csd[1] = cmd.response[1];
	mmc->csd[2] = cmd.response[2];
	mmc->csd[3] = cmd.response[3];
	debug("%s: CSD: 0x%08x 0x%08x 0x%08x 0x%08x\n", __func__,
	      mmc->csd[0], mmc->csd[1], mmc->csd[2], mmc->csd[3]);
	return 0;
}

#ifdef CONFIG_OCTEON_MMC_SD
static int sd_set_bus_width_speed(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	int err;
#ifdef DEBUG
	struct mmc_host *host = mmc->priv;
	debug("%s(%d) width: %d %d\n", __func__, host->bus_id,
	      mmc->bus_width, host->bus_width);
#endif

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmdidx = SD_CMD_APP_SET_BUS_WIDTH;
	cmd.resp_type = MMC_RSP_R1;

	debug("card caps: 0x%x\n", mmc->card_caps);
	if (mmc->card_caps & MMC_MODE_4BIT) {
		/* Set SD bus width to 4 */
		cmd.cmdarg = 2;

		err = mmc_send_acmd(mmc, &cmd, NULL, 0);
		if (err) {
			printf("%s: Error setting bus width\n", __func__);
			return err;
		}
		mmc_set_bus_width(mmc, 4);
	} else {
		/* Set SD bus width to 1 */
		cmd.cmdarg = 0;

		err = mmc_send_acmd(mmc, &cmd, NULL, 0);
		if (err) {
			printf("%s: Error setting bus width\n", __func__);
			return err;
		}
		mmc_set_bus_width(mmc, 1);
	}
	if (mmc->card_caps & MMC_MODE_HS)
		mmc_set_clock(mmc, 50000000);
	else
		mmc_set_clock(mmc, 25000000);
	return sd_set_ios(mmc);
}
#endif

static int mmc_set_bus_width_speed(struct mmc *mmc)
{
	debug("%s: card caps: 0x%x\n", __func__, mmc->card_caps);
	if (mmc->card_caps & MMC_MODE_8BIT) {
		debug("%s: Set bus width to 8 bits\n", __func__);
		mmc_set_bus_width(mmc, 8);
	} else if (mmc->card_caps & MMC_MODE_4BIT) {
		debug("%s: Set bus width to 4 bits\n", __func__);
		/* Set the card to use 4 bit */
		mmc_set_bus_width(mmc, 4);
	}
	if (mmc->card_caps & MMC_MODE_HS) {
		debug("%s: Set high-speed mode\n", __func__);
		if (mmc->card_caps & MMC_MODE_HS_52MHz) {
			debug("%s: Set clock speed to 52MHz\n",
			      __func__);
			mmc_set_clock(mmc, 52000000);
		} else {
			mmc_set_clock(mmc, 26000000);
			debug("%s: Set clock speed to 26MHz\n",
			      __func__);
		}
	} else {
		debug("%s: Set clock speed to 20MHz\n", __func__);
		mmc_set_clock(mmc, 20000000);
	}
	mmc_set_ios(mmc);
	return 0;
}

#ifdef CONFIG_OCTEON_MMC_SD
int sd_send_op_cond(struct mmc *mmc)
{
	int timeout = 1000;
	int err;
	struct mmc_cmd cmd;
	uint32_t flags = MMC_CMD_FLAG_RTYPE_XOR(3) | MMC_CMD_FLAG_STRIP_CRC;

	debug("In %s\n", __func__);
	mmc->rca = 0;

	do {
		cmd.cmdidx = SD_CMD_APP_SEND_OP_COND;
		cmd.resp_type = MMC_RSP_R3;

		/*
		 * Most cards do not answer if some reserved bits
		 * in the ocr are set.  However, some controllers
		 * can set bit 7 (reserved low voltages), but
		 * how to manage low voltage SD cards is not yet
		 * specified.
		 */
		cmd.cmdarg = mmc->voltages & OCR_VOLTAGE_MASK;

		if (mmc->version == SD_VERSION_2) {
			cmd.cmdarg |= OCR_HCS;
			debug("%s: SD 2.0 compliant card, voltages: 0x%x\n",
			      __func__, cmd.cmdarg);
		} else if (mmc->version == SD_VERSION_3) {
			cmd.cmdarg |= OCR_HCS | OCR_XPC;
			debug("%s: SD 3.0 compliant card, arg: 0x%x\n",
			      __func__, cmd.cmdarg);
		}

		err = mmc_send_acmd(mmc, &cmd, NULL, flags);
		if (err) {
			debug("%s: Error sending SD command, might be MMC\n",
			      __func__);
			return err;
		}

		debug("%s response: 0x%x\n", __func__, cmd.response[0]);
		mdelay(1);
	} while ((!(cmd.response[0] & OCR_BUSY)) && timeout--);

	if (timeout <= 0) {
		printf("%s: Timed out\n", __func__);
		return TIMEOUT;
	}

	if ((mmc->version != SD_VERSION_2) || (mmc->version != SD_VERSION_3))
		mmc->version = SD_VERSION_1_0;

	mmc->ocr = cmd.response[0];
	mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);

	debug("%s: MMC high capacity mode %sdetected.\n",
	      __func__, mmc->high_capacity ? "" : "NOT ");
	return 0;
}
#endif

int mmc_send_op_cond(struct mmc *mmc)
{
	int timeout = WATCHDOG_COUNT;
	struct mmc_cmd cmd;
	int err;

	do {
		cmd.cmdidx = MMC_CMD_SEND_OP_COND;
		cmd.resp_type = MMC_RSP_R3;
		cmd.cmdarg = OCR_HCS | mmc->voltages;

		err = mmc_send_cmd(mmc, &cmd, NULL, MMC_CMD_FLAG_STRIP_CRC);
		if (err) {
			if (!init_time)
				debug("%s: Returned %d\n", __func__, err);
			return err;
		}
		debug("%s: response 0x%x\n", __func__, cmd.response[0]);
		if (cmd.response[0] & OCR_BUSY)
			break;
		mdelay(1);
	} while (timeout--);

	if (timeout <= 0) {
		printf("%s: Timed out!", __func__);
		return TIMEOUT;
	}

	mmc->version = MMC_VERSION_UNKNOWN;
	mmc->ocr = cmd.response[0];

	mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);

#ifdef DEBUG
	debug("%s: OCR: 0x%x\n", __func__, mmc->ocr);
	if (mmc->ocr & 0x80)
		debug("\t1.70-1.95V\n");
	if (mmc->ocr & 0x3f00)
		debug("\t2.0-2.6V\n");
	if (mmc->ocr & 0x007f8000)
		debug("\t2.7-3.6V\n");
	debug("\tAccess Mode: %s\n",
	      (mmc->ocr & 0x40000000) == 0x40000000 ? "sector" : "byte");
	debug("\tHigh Capacity: %s\n", mmc->ocr & OCR_HCS ? "yes" : "no");
#endif
	return 0;
}

/* Get the extended CSD register */
int mmc_send_ext_csd(struct mmc *mmc)
{
	struct mmc_cmd cmd;
	struct mmc_data data;
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	int err;

	debug("%s: bus: %d\n", __func__, host->bus_id);
#if 0
	if (host->have_ext_csd) {
		debug("%s: Already have ext_csd\n", __func__);
#ifdef DEBUG
		int i;
		for (i = 0; i < 512; i++) {
			if (i % 16 == 0)
				printf("\n0x%03x: ", i);
			if (i % 16 == 8)
				puts("- ");
			printf("%02x ", (uchar)host->ext_csd[i]);
		}
		puts("\n");
#endif
		return 0;
	}
#endif
	mmc_switch_dev(mmc);
	mmc_set_blocklen(mmc, 512);

	cmd.cmdidx = MMC_CMD_SEND_EXT_CSD;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = 0;
	data.dest = (char *)host->ext_csd;
	data.blocks = 1;
	data.blocksize = 512;
	data.flags = MMC_DATA_READ;

	err = mmc_send_cmd(mmc, &cmd, &data, 0);

	if (err) {
		printf("%s: Error getting extended CSD\n", __func__);
	} else {
		debug("%s: Got good response\n", __func__);
		host->have_ext_csd = 1;
#ifdef DEBUG
		int i;
		for (i = 0; i < 512; i++) {
			if (i % 16 == 0)
				printf("\n0x%03x: ", i);
			if (i % 16 == 8)
				puts("- ");
			printf("%02x ", (uchar)host->ext_csd[i]);
		}
		puts("\n");
#endif
	}
	return err;
}

/* NOTE: We don't use this function since OCTEON handles this in hardware */
int mmc_switch(struct mmc *mmc, u8 set, u8 index, u8 value)
{
	struct mmc_cmd cmd;

	cmd.cmdidx = MMC_CMD_SWITCH;
	cmd.resp_type = MMC_RSP_R1b;
	cmd.cmdarg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
		(index << 16) |
		(value << 8);

	return mmc_send_cmd(mmc, &cmd, NULL, 0);
}

int mmc_switch_part(int dev_num, unsigned int part_num)
{
	struct mmc *mmc = find_mmc_device(dev_num);
	if (!mmc)
		return -1;

	debug("%s: Switching to partition %d\n", __func__, part_num);
	mmc_switch_dev(mmc);
	return mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PART_CONF,
			  (mmc->part_config & ~PART_ACCESS_MASK)
			  | (part_num & PART_ACCESS_MASK));
}
#ifdef CONFIG_OCTEON_MMC_SD
static int sd_set_ios(struct mmc *mmc)
{
	cvmx_mio_emm_switch_t emm_switch;
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	int clock = mmc->clock;

	debug("%s: clock: %d (max %d), width %d\n",
	      __func__, clock, mmc->f_max, mmc->bus_width);
	if (mmc->bus_width > 4)
		mmc->bus_width = 4;
	host->clk_period = (host->sclock + clock - 1) / clock;
	host->power_class = 10;
	emm_switch.u64 = 0;
	emm_switch.s.hs_timing = (mmc->card_caps & MMC_MODE_HS) ? 1 : 0;
	/* No DDR for now */
	host->bus_width = (mmc->bus_width == 4) ? 1 : 0;
	emm_switch.s.bus_width = host->bus_width;
	emm_switch.s.clk_hi = (host->clk_period + 1) / 2;
	emm_switch.s.clk_lo = (host->clk_period + 1) / 2;
	emm_switch.s.power_class = host->power_class;
	debug("%s: Writing emm_switch value 0x%llx\n",
	      __func__, emm_switch.u64);
	mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	emm_switch.s.bus_id = host->bus_id;
	udelay(100);
	mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	mdelay(20);
#ifdef DEBUG
	mmc_print_registers(mmc);
#endif
	return 0;
}
#endif

static void mmc_set_ios(struct mmc *mmc)
{
	cvmx_mio_emm_switch_t emm_switch;
	cvmx_mio_emm_rsp_sts_t emm_sts;
	cvmx_mio_emm_wdog_t emm_wdog;
	cvmx_mio_emm_sample_t emm_sample;
	int switch_timeout_ms = 2550;
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	int timeout = 2000;
	char cardtype;
	int hs_timing = 0;
	int ddr = 0;
	int bus_width;
	int power_class = 10;
	int clock = mmc->clock;
	uint32_t flags = 0;

	debug("In %s\n", __func__);
	debug("Starting clock is %uHz\n", clock);
	mmc->card_caps = 0;

	/* Only version 4 supports high speed */
	if (mmc->version < MMC_VERSION_4)
		return;

	if (clock == 0) {
		puts("mmc switch: Error, clock is zero!\n");
		return;
	}

	mmc_switch_dev(mmc);

	cardtype = host->ext_csd[EXT_CSD_CARD_TYPE] & 0x3f;
	debug("%s: card type flags (device_type): 0x%x\n", __func__, cardtype);
	if (cardtype & EXT_CSD_CARD_TYPE_26) {
		hs_timing = 1;
		debug("\tHigh-Speed eMMC 26MHz at rated device voltage(s)\n");
	}
	if (cardtype & EXT_CSD_CARD_TYPE_52) {
		debug("\tHigh-Speed eMMC 52MHz at rated device voltage(s)\n");
		mmc->card_caps |= MMC_MODE_HS_52MHz;
		hs_timing = 1;
	}
	if (cardtype & EXT_CSD_CARD_TYPE_DDR_1_8V) {
		debug("\tHigh-Speed DDR eMMC 52MHz at 1.8V or 3V I/O\n");
		hs_timing = 1;
		if ((mmc->voltages & MMC_VDD_165_195)
		    || getenv("octeon_mmc_ddr"))
			ddr = 1;
	}
	if (cardtype & EXT_CSD_CARD_TYPE_DDR_1_2V) {
		debug("\tHigh-Speed DDR eMMC 52MHz at 1.2V I/O\n");
		hs_timing = 1;
		/* DDR only works at 1.2V which OCTEON doesn't support */
		ddr = 0;
	}
	if (cardtype & (1 << 4))
		debug("\tHS200 Single Data Rate eMMC 200MHz at 1.8V I/O\n");
	if (cardtype & (1 << 5))
		debug("\tHS200 Single Data Rate eMMC 200MHz at 1.2V I/O\n");

	mmc->bus_width = host->max_width;
	debug("\tMax bus width: %d\n", host->max_width);
	/* Limit bus width to 4 for SD */
	if (IS_SD(mmc) && mmc->bus_width > 4)
		mmc->bus_width = 4;

	/* NOTE: We only use DDR mode for SD cards.  For MMC DDR will be enabled
	 * later after the bus width is detected since DDR mode is not allowed
	 * when detecting the bus width.
	 */
	switch (mmc->bus_width) {
	case 8:
		if (ddr && IS_SD(mmc))
			bus_width = EXT_CSD_DDR_BUS_WIDTH_8;
		else
			bus_width = EXT_CSD_BUS_WIDTH_8;
		break;
	case 4:
		if (ddr && IS_SD(mmc))
			bus_width = EXT_CSD_DDR_BUS_WIDTH_4;
		else
			bus_width = EXT_CSD_BUS_WIDTH_4;
		break;
	case 1:
		bus_width = EXT_CSD_BUS_WIDTH_1;
		break;
	default:
		printf("%s: Unknown bus width %d\n", __func__, mmc->bus_width);
		return;
	}

	if (hs_timing) {
		if (cardtype & MMC_HS_52MHZ && mmc->f_max >= 50000000) {
			mmc->card_caps |= MMC_MODE_HS_52MHz | MMC_MODE_HS;
			clock = min(52000000, mmc->f_max);
			debug("High-speed 52MHz timing mode detected\n");
		} else {
			mmc->card_caps |= MMC_MODE_HS;
			clock = min(26000000, mmc->f_max);
			debug("High-speed 26MHz timing mode detected\n");
		}
		if (ddr) {
			mmc->card_caps |= MMC_MODE_DDR;
			debug("DDR mode enabled\n");
		}
	} else {
		if (mmc->tran_speed)
			clock = min(clock, mmc->tran_speed);
		else
			clock = min(clock, 20000000);
		debug("High-speed clock mode NOT detected, setting to %dhz\n",
		      clock);
	}
	host->bus_width = bus_width;
	mmc_set_clock(mmc, clock);
	debug("%s: Clock set to %u Hz\n", __func__, mmc->clock);

	switch_timeout_ms = host->ext_csd[EXT_CSD_GENERIC_CMD6_TIME] * 4;
	if (switch_timeout_ms == 0) {
		switch_timeout_ms = 2550 * 4;
		debug("extended CSD generic cmd6 timeout not specified\n");
	} else
		debug("extended CSD generic cmd6 timeout %d ms\n",
		      switch_timeout_ms);

	/* Adjust clock skew */
	emm_sample.u64 = 0;
	emm_sample.s.cmd_cnt = host->cmd_clk_skew;
	emm_sample.s.dat_cnt = host->dat_clk_skew;
	cvmx_write_csr(CVMX_MIO_EMM_SAMPLE, emm_sample.u64);
	debug("%s: Setting command clock skew to %d, data to %d sclock cycles\n",
	      __func__, host->cmd_clk_skew, host->dat_clk_skew);

again:
	host->clk_period = (host->sclock + mmc->clock - 1) / mmc->clock;

	debug("%s: Setting clock period to %d for MMC clock: %d, hs: %d\n",
	      __func__, host->clk_period, mmc->clock, hs_timing);

	/* Set the watchdog since the switch operation can be long */
	emm_wdog.u64 = 0;
	emm_wdog.s.clk_cnt =
		((u64)clock * 1000 + switch_timeout_ms - 1) / switch_timeout_ms;
	debug("%s: Setting watchdog to %d ms (0x%llx), clock: %u\n", __func__,
	      switch_timeout_ms, (u64)emm_wdog.s.clk_cnt, clock);
	cvmx_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);

	emm_switch.u64 = 0;
	emm_switch.s.bus_id = host->bus_id;
	emm_switch.s.switch_exe = 1;
	emm_switch.s.hs_timing = hs_timing;
	emm_switch.s.bus_width = bus_width;
	emm_switch.s.power_class = power_class;
	host->power_class = power_class;
	emm_switch.s.clk_hi = (host->clk_period + 1) / 2;
	emm_switch.s.clk_lo = (host->clk_period + 1) / 2;

	debug("%s: Writing 0x%llx to mio_emm_switch\n",
	      __func__, emm_switch.u64);
	mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	udelay(100);

	timeout = switch_timeout_ms + 10;
	do {
		emm_sts.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_STS);
		if (!emm_sts.s.switch_val)
			break;
		mdelay(1);
	} while (timeout-- > 0);
	if (timeout <= 0) {
		printf("%s: switch command timed out, bus = %d, status=0x%llx\n",
		       __func__, host->bus_id, emm_sts.u64);
		return;
	}

	emm_switch.u64 = mmc_read_csr(CVMX_MIO_EMM_SWITCH);
	debug("Switch command response: 0x%llx, switch: 0x%llx\n",
	      emm_sts.u64, emm_switch.u64);
#if defined(DEBUG)
	cvmx_mio_emm_rsp_lo_t emm_rsp_lo;
	emm_rsp_lo.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_LO);
	debug("Switch response lo: 0x%llx\n", emm_rsp_lo.u64);
#endif

	if ((emm_switch.s.switch_err0 | emm_switch.s.switch_err1
	     | emm_switch.s.switch_err2) && emm_sts.s.rsp_crc_err &&
	    mmc->clock > 20000000) {
		debug("%s: emm_switch error detected\n", __func__);
		mmc_print_registers(mmc);
		/* A CRC error occurred so try adjusting some things */
		/* If we're in DDR mode, turn off DDR. */
		switch (bus_width) {
		case EXT_CSD_DDR_BUS_WIDTH_8:
			bus_width = EXT_CSD_BUS_WIDTH_8;
			debug("%s: Switching from DDR 8 to non-DDR 8\n",
			      __func__);
			goto again;
		case EXT_CSD_DDR_BUS_WIDTH_4:
			bus_width = EXT_CSD_BUS_WIDTH_4;
			debug("%s: Switching from DDR 4 to non-DDR 4\n",
			      __func__);
			goto again;
		default:
			break;
		}
		/* A CRC error occurred during the switch operation, try slowing
		 * things down by 5MHz down to about 20MHz.
		 */
		mmc->clock = max(mmc->clock - 5000000, 20000000);
		if (mmc->clock == 20000000)
			hs_timing = 0;
		host->clk_period = (host->sclock + mmc->clock - 1) / mmc->clock;
		debug("%s: bus_id %d detected CRC error, slowing clock down to %d and setting clock period to %d cycles\n",
		      __func__, host->bus_id, mmc->clock, host->clk_period);
		goto again;
	}
	if (emm_switch.s.switch_err0) {
		/* Error while performing POWER_CLASS switch */
		if (power_class > 0) {
			power_class--;
			host->power_class = power_class;
			debug("%s: Trying power class %d\n",
			      __func__, power_class);
			goto again;
		}
		printf("%s: Error setting power class\n", __func__);
		return;
	}
	if (emm_switch.s.switch_err1) {
		/* Error while performing HS_TIMING switch */
		if (ddr) {
			ddr = 0;
			debug("%s: Turning off DDR mode\n", __func__);
			mmc->card_caps &= ~MMC_MODE_DDR;
			if (bus_width == EXT_CSD_DDR_BUS_WIDTH_8)
				bus_width = EXT_CSD_BUS_WIDTH_8;
			else if (bus_width == EXT_CSD_DDR_BUS_WIDTH_4)
				bus_width = EXT_CSD_BUS_WIDTH_4;
			goto again;
		}
		if (hs_timing) {
			if (clock > 26000000) {
				clock = 26000000;
				debug("%s: Reducing clock to 26MHz\n", __func__);
			} else {
				hs_timing = 0;
				debug("%s: Turning off high-speed timing\n",
				      __func__);
			}
			mmc_set_clock(mmc, clock);
			goto again;
		}
		printf("%s: Error setting hs timing\n", __func__);
		return;
	}

	/* CMD19 and CMD14 are only supported for MMC devices and only in
	 * the single data rate mode.  In the dual data rate mode these
	 * commands are illegal.
	 */
	if (!IS_SD(mmc)) {	/* Only MMC supports bus testing */
		debug("Testing bus width %d\n", mmc->bus_width);
		/* Test bus width */
		if (!emm_switch.s.switch_err2 &&
		    (bus_width != EXT_CSD_DDR_BUS_WIDTH_8) &&
		    (bus_width != EXT_CSD_DDR_BUS_WIDTH_4)) {
			/* Width succeeded, test the bus */
			struct mmc_cmd mmc_cmd;
			struct mmc_data mmc_data;
			uint8_t buffer[11];

			debug("Testing bus width %d (%d)\n",
			      mmc->bus_width, bus_width);
			mmc_data.src = (char *)buffer;
			mmc_data.blocks = 1;
			mmc_data.flags = MMC_DATA_WRITE;

			switch (mmc->bus_width) {
			case 8:
				buffer[0] = 0x55;
				buffer[1] = 0xaa;
				buffer[2] = 0x00;
				buffer[3] = 0x00;
				buffer[4] = 0x00;
				buffer[5] = 0x00;
				buffer[6] = 0x00;
				buffer[7] = 0x00;
				buffer[8] = 0x05;
				buffer[9] = 0xd4;
				buffer[10] = 0xff;
				mmc_data.blocksize = 11;
				break;
			case 4:
				buffer[0] = 0x5a;
				buffer[1] = 0x00;
				buffer[2] = 0x00;
				buffer[3] = 0x00;
				buffer[4] = 0x99;
				buffer[5] = 0x50;
				buffer[6] = 0x0f;
				mmc_data.blocksize = 7;
				break;
			case 1:
				buffer[0] = 0x80;
				buffer[1] = 0x70;
				buffer[2] = 0x78;
				buffer[3] = 0x01;
				mmc_data.blocksize = 4;
				break;
			default:
				printf("Unknown bus width %d\n", mmc->bus_width);
				return;
			}

#ifdef DEBUG
			print_buffer(0, buffer, 1, mmc_data.blocksize, 0);
#endif
			mmc_cmd.cmdarg = 0;
			mmc_cmd.cmdidx = 19;	/* BUSTEST_W */
			mmc_cmd.resp_type = MMC_RSP_R1;
        		flags = MMC_CMD_FLAG_CTYPE_XOR(0) | MMC_CMD_FLAG_OFFSET(63);
	        	if (mmc_send_cmd(mmc, &mmc_cmd, &mmc_data, flags) != 0)
        			puts("Warning: problem sending BUSTEST_W command\n");

			debug("BUSTEST_W response is 0x%x 0x%x 0x%x 0x%x\n",
			      mmc_cmd.response[0], mmc_cmd.response[1],
			      mmc_cmd.response[2], mmc_cmd.response[3]);
			mdelay(1);

			mmc_data.blocksize -= 2;
			memset(buffer, 0, sizeof(buffer));
			mmc_cmd.cmdarg = 0;
			mmc_cmd.cmdidx = 14;	/* BUSTEST_R */
			mmc_cmd.resp_type = MMC_RSP_R1;
        		flags = MMC_CMD_FLAG_OFFSET(63);
			memset(buffer, 0, sizeof(buffer));
			mmc_data.dest = (char *)buffer;
			mmc_data.blocks = 1;
			mmc_data.flags = MMC_DATA_READ;
        		if (mmc_send_cmd(mmc, &mmc_cmd, &mmc_data, flags) != 0)
        			puts("Warning: problem sending BUSTEST_R command\n");

			debug("BUSTEST_R response is 0x%x %x %x %x\n",
			      mmc_cmd.response[0], mmc_cmd.response[1],
			      mmc_cmd.response[2], mmc_cmd.response[3]);
#ifdef DEBUG
			print_buffer(0, buffer, 1, sizeof(buffer), 0);
#endif
			switch (bus_width) {
			case EXT_CSD_DDR_BUS_WIDTH_8:
				if (buffer[0] != 0xaa || buffer[1] != 0x55) {
					debug("DDR Bus width 8 test failed, returned "
					      "0x%02x%02x, expected 0xAA55, trying "
					      "bus width 8\n",
					      buffer[0], buffer[1]);
					bus_width = EXT_CSD_DDR_BUS_WIDTH_4;
					mmc->bus_width = 4;
					goto again;
				}
				break;
			case EXT_CSD_DDR_BUS_WIDTH_4:
				if (buffer[0] != 0xa5) {
					debug("DDR Bus width 4 test failed, returned "
					      "0x%02x%02x, expected 0xA5, trying "
					      "bus width %d\n",
					      buffer[0], buffer[1], host->max_width);
					bus_width = (host->max_width == 8) ?
							EXT_CSD_BUS_WIDTH_8
							: EXT_CSD_BUS_WIDTH_4;
					mmc->bus_width = host->max_width;
					goto again;
				}
				break;
			case EXT_CSD_BUS_WIDTH_8:
				if (buffer[0] != 0xaa || buffer[1] != 0x55) {
					debug("Bus width 8 test failed, returned "
					      "0x%02x%02x, expected 0xAA55, trying bus width 4\n",
					      buffer[0], buffer[1]);
					bus_width = EXT_CSD_BUS_WIDTH_4;
					mmc->bus_width = 4;
					goto again;
				}
				break;
			case EXT_CSD_BUS_WIDTH_4:
				if (buffer[0] != 0xa5) {
					debug("DDR bus width 4 test failed, returned "
					      "0x%02x, expected 0xA5, trying bus width 1\n",
					      buffer[0]);
					bus_width = EXT_CSD_BUS_WIDTH_1;
					mmc->bus_width = 1;
					goto again;
				}
				break;
			case EXT_CSD_BUS_WIDTH_1:
				if ((buffer[0] & 0xc0) != 0x40) {
					debug("DDR bus width 1 test failed, returned "
					      "0x%02x, expected 0x4x, trying bus width 1\n",
					      buffer[0]);
					return;
				}
				break;
			default:
				break;
			}
		}

		if (emm_switch.s.switch_err2) {
			/* Error while performing BUS_WIDTH switch */
			switch (bus_width) {
			case EXT_CSD_DDR_BUS_WIDTH_8:
				debug("DDR bus width 8 failed, trying DDR bus width 4\n");
				bus_width = EXT_CSD_DDR_BUS_WIDTH_4;
				goto again;
			case EXT_CSD_DDR_BUS_WIDTH_4:
				debug("DDR bus width 4 failed, trying bus width %d\n",
				      host->max_width);
				bus_width = (host->max_width == 8) ?
						EXT_CSD_BUS_WIDTH_8
						: EXT_CSD_BUS_WIDTH_4;
				goto again;
			case EXT_CSD_BUS_WIDTH_8:
				debug("Bus width 8 failed, trying bus width 4\n");
				bus_width = EXT_CSD_BUS_WIDTH_4;
				goto again;
			case EXT_CSD_BUS_WIDTH_4:
				debug("Bus width 4 failed, trying bus width 1\n");
				bus_width = EXT_CSD_BUS_WIDTH_1;
				goto again;
			default:
				printf("%s: Could not set bus width\n", __func__);
				return;
			}
		}
	}

	if (ddr) {
		mmc->card_caps |= MMC_MODE_DDR;

		switch (mmc->bus_width) {
		case 8:
			bus_width = EXT_CSD_DDR_BUS_WIDTH_8;
			break;
		case 4:
			bus_width = EXT_CSD_DDR_BUS_WIDTH_4;
			break;
		default:
			puts("Error: MMC DDR mode only supported with bus widths of 4 or 8!\n");
			return;
		}
		emm_switch.u64 = 0;
		emm_switch.s.bus_id = host->bus_id;
		emm_switch.s.switch_exe = 1;
		emm_switch.s.hs_timing = hs_timing;
		emm_switch.s.bus_width = bus_width;
		emm_switch.s.power_class = host->power_class;
		emm_switch.s.clk_hi = (host->clk_period + 1) / 2;
		emm_switch.s.clk_lo = (host->clk_period + 1) / 2;
		mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
		udelay(100);

		timeout = switch_timeout_ms + 10;
		do {
			emm_sts.u64 = mmc_read_csr(CVMX_MIO_EMM_RSP_STS);
			if (!emm_sts.s.switch_val)
				break;
			mdelay(1);
		} while (timeout-- > 0);
		if (timeout < 0) {
			printf("Error: MMC timed out when converting to DDR mode\n");
			return;
		}
	}
	/* Store the bus width */
	host->bus_width = emm_switch.s.bus_width;
	/* Set watchdog for command timeout */
	emm_wdog.u64 = 0;
	emm_wdog.s.clk_cnt = mmc->clock;
	mmc_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);

	debug("%s: Set hs: %d, clock: %u, bus width: %d, power class: %d, watchdog: %u\n",
	      __func__, hs_timing, mmc->clock, bus_width, power_class,
	      emm_wdog.s.clk_cnt);
	return;
}

/* Set the clock speed.
 *
 * NOTE: The clock speed will be limited to the maximum supported clock speed.
 */
void mmc_set_clock(struct mmc *mmc, uint clock)
{
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	cvmx_mio_emm_switch_t emm_switch;
	cvmx_mio_emm_wdog_t emm_wdog;
	unsigned bus;

	debug("%s: min: %u, max: %u, trans: %u, hs: %u, set: %u\n",
	      __func__, mmc->f_min, mmc->f_max, mmc->tran_speed,
	      (mmc->card_caps & MMC_MODE_HS) ? 1 : 0, clock);
	if (clock == 0) {
		printf("%s: ERROR: Cannot set clock to zero!\n", __func__);
		return;
	}
	clock = min(clock, mmc->f_max);
	clock = max(clock, mmc->f_min);
	if (mmc->tran_speed && !(mmc->card_caps & MMC_MODE_HS)) {
		clock = min(clock, mmc->tran_speed);
		debug("%s: Limiting clock to trans speed %u\n",
		      __func__, mmc->tran_speed);
	}
	debug("%s: Setting clock to %uHz\n", __func__, clock);
	mmc->clock = clock;
	host->clk_period = (host->sclock + clock - 1) / clock;

	/* Write the change to the hardware */
	emm_switch.u64 = mmc_read_csr(CVMX_MIO_EMM_SWITCH);
	emm_switch.s.clk_hi = emm_switch.s.clk_lo = (host->clk_period + 1) / 2;
	bus = emm_switch.s.bus_id;
	emm_switch.s.bus_id = 0;
	mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	udelay(1200);
	emm_switch.s.bus_id = bus;
	mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	udelay(1200);

	emm_wdog.u64 = 0;
	emm_wdog.s.clk_cnt = mmc->clock;
	cvmx_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);
}

#ifdef CONFIG_OCTEON_MMC_SD
int sd_switch(struct mmc *mmc, int mode, int group, u8 value, u32 *resp)
{
	struct mmc_cmd cmd;
	struct mmc_data data;
	int err;

	debug("%s(mmc, %d, %d, %u, 0x%p)\n",
	      __func__, mode, group, value, resp);
	/* Switch the frequency */
	cmd.cmdidx = SD_CMD_SWITCH_FUNC;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = (mode << 31) | 0xffffff;
	cmd.cmdarg &= ~(0xf << (group * 4));
	cmd.cmdarg |= value << (group * 4);

	data.dest = (char *)resp;
	data.blocksize = 64;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;

	err = mmc_send_cmd(mmc, &cmd, &data,  MMC_CMD_FLAG_CTYPE_XOR(1));
	if (err) {
		printf("%s: failed, rc: %d\n", __func__, err);
		return err;
	}
	memcpy(resp, &cmd.response[0], sizeof(cmd.response));
	return 0;
}

int sd_change_freq(struct mmc *mmc)
{
	int err;
	struct mmc_cmd cmd;
	uint32_t scr[2];
	uint32_t switch_status[16];
	struct mmc_data data;
	int timeout;
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	uint32_t flags;

	debug("In %s\n", __func__);

#ifdef DEBUG
	memset(scr, 0x55, sizeof(scr));
	memset(switch_status, 0xaa, sizeof(switch_status));
#endif
	mmc->card_caps = 0;

	cmd.cmdidx = SD_CMD_APP_SEND_SCR;
	cmd.resp_type = MMC_RSP_R1;
	cmd.cmdarg = 0;
	flags = MMC_CMD_FLAG_RTYPE_XOR(1) | MMC_CMD_FLAG_CTYPE_XOR(1)
		    | MMC_CMD_FLAG_OFFSET(63);

	timeout = 3;

retry_scr:
	data.dest = (char *)&scr;
	data.blocksize = 8;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;

	err = mmc_send_acmd(mmc, &cmd, &data, flags);

	if (err) {
		debug("Retrying send SCR\n");
		if (timeout--)
			goto retry_scr;

		return err;
	}

	mmc->scr[0] = __be32_to_cpu(scr[0]);
	mmc->scr[1] = __be32_to_cpu(scr[1]);

	debug("%s: SCR=0x%08x 0x%08x\n", __func__, mmc->scr[0], mmc->scr[1]);
	switch ((mmc->scr[0] >> 24) & 0xf) {
		case 0:
			mmc->version = SD_VERSION_1_0;
			break;
		case 1:
			mmc->version = SD_VERSION_1_10;
			break;
		case 2:
			mmc->version = SD_VERSION_2;
			if ((mmc->scr[0] >> 15) & 0x1)
				mmc->version = SD_VERSION_3;
			break;
		default:
			mmc->version = SD_VERSION_1_0;
			break;
	}

	/* Version 1.0 doesn't support switching */
	if (mmc->version == SD_VERSION_1_0) {
		debug("%s: Returning for SD version 1.0\n", __func__);
		return 0;
	}

	timeout = 4;
	while (timeout--) {
		err = sd_switch(mmc, SD_SWITCH_CHECK, 0, 1, switch_status);

		if (err) {
			debug("%s: Error calling sd_switch\n", __func__);
			return err;
		}

		/* The high-speed function is busy.  Try again */
		if (!(__be32_to_cpu(switch_status[7]) & SD_HIGHSPEED_BUSY)) {
			debug("%s: high speed function is !busy, done\n",
			      __func__);
			break;
		}
		mdelay(1);
	}

#ifdef DEBUG
	int i;
	for (i = 0; i < 16; i++) {
		if (!(i & 3))
			debug("\n%02x: ", i * 4);
		debug("%08x ", switch_status[i]);
	}
	puts("\n");
#endif

	if (mmc->scr[0] & SD_DATA_4BIT && host->max_width >= 4) {
		mmc->card_caps |= MMC_MODE_4BIT;
		mmc->bus_width = 4;
		debug("%s: SD 4 bit mode detected\n", __func__);
	} else {
		debug("%s: SD 4-bit mode NOT detected\n", __func__);
	}
	if (mmc->scr[0] & 2) {
		host->flags |= OCTEON_MMC_FLAG_SD_CMD23;
		debug("%s: SD CMD23 support detected\n", __func__);
	}
#ifdef DEBUG
	debug("\tmax current: %u ma\n", switch_status[0] >> 16);
	if (switch_status[0] & 0xffff) {
		debug("\tGroup 6 functions supported: ");
		for (i = 0; i < 16; i++)
			if ((switch_status[0] >> i) & 1)
				debug("%i ", i);
		debug("\n");
	}
	if (switch_status[1] & 0xffff0000) {
		debug("\tGroup 5 functions supported: ");
		for (i = 0; i < 16; i++)
			if ((switch_status[1] >> (i + 16)) & 1)
				debug("%i ", i);
		debug("\n");
	}
	if (switch_status[1] & 0xffff) {
		debug("\tGroup 4 functions supported: ");
		for (i = 0; i < 16; i++)
			if ((switch_status[1] >> i) & 1)
				debug("%i ", i);
		debug("\n");
	}
	if (switch_status[2] & 0xffff0000) {
		debug("\tGroup 3 functions supported: ");
		for (i = 0; i < 16; i++)
			if ((switch_status[2] >> (i + 16)) & 1)
				debug("%i ", i);
		debug("\n");
	}
	if (switch_status[2] & 0x0000ffff) {
		debug("\tGroup 2 functions supported: ");
		for (i = 0; i < 16; i++)
			if ((switch_status[1] >> i) & 1)
				debug("%i ", i);
		debug("\n");
	}
	if (switch_status[3] & 0xffff0000) {
		debug("\tGroup 1 functions supported: ");
		for (i = 0; i < 16; i++)
			if ((switch_status[2] >> (i + 16)) & 1)
				debug("%i ", i);
		debug("\n");
	}
	if (switch_status[3] & 0x0000f000)
		debug("\tGroup 6 functions selected: 0x%x\n",
		      (switch_status[3] >> 12) & 0xF);
	if (switch_status[3] & 0x00000f00)
		debug("\tGroup 5 functions selected: 0x%x\n",
		      (switch_status[3] >> 8) & 0xF);

	if (switch_status[3] & 0x000000f0)
		debug("\tGroup 4 functions selected: 0x%x\n",
		      (switch_status[3] >> 4) & 0xF);
	if (switch_status[3] & 0x0000000f)
		debug("\tGroup 3 functions selected: 0x%x\n",
		      switch_status[3] & 0xF);
	if (switch_status[4] & 0xf0000000)
		debug("\tGroup 2 functions selected: 0x%x\n",
		      (switch_status[4] >> 28) & 0xF);
	if (switch_status[4] & 0x0f000000)
		debug("\tGroup 1 functions selected: 0x%x\n",
		      (switch_status[4] >> 24) & 0xF);
	debug("\tData structure version: %d\n", (switch_status[4] >> 16) & 0xff);

	if (!(__be32_to_cpu(switch_status[4] & SD_HIGHSPEED_SUPPORTED)))
		debug("%s: high speed mode not supported\n", __func__);
	else
		debug("%s: high speed mode supported\n", __func__);

#endif	/* DEBUG */

	err = sd_switch(mmc, SD_SWITCH_SWITCH, 0, 1, switch_status);

	if (err) {
		debug("%s: switch failed\n", __func__);
		return err;
	}

#ifdef DEBUG
	for (i = 0; i < 16; i++) {
		if (!(i & 3))
			debug("\n%02x: ", i * 4);
		debug("%08x ", switch_status[i]);
	}
	puts("\n");
#endif
	if ((__be32_to_cpu(switch_status[4]) & 0x0f000000) == 0x01000000) {
		mmc->card_caps |= MMC_MODE_HS;
		debug("%s: High speed mode supported\n", __func__);
	}

	return 0;
}
#endif

int mmc_send_if_cond(struct mmc *mmc)
{
#ifdef CONFIG_OCTEON_MMC_SD
	struct mmc_cmd cmd;
	int err;
	cvmx_mio_emm_wdog_t emm_wdog;
	uint32_t flags;

	/* We only need a very short timeout here */
	emm_wdog.u64 = 0;
	emm_wdog.s.clk_cnt = 1024;
	cvmx_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);

	cmd.cmdidx = SD_CMD_SEND_IF_COND;
	/* We set the bit if the host supports voltages between 2.7 and 3.6 V */
	cmd.cmdarg = ((mmc->voltages & OCR_VOLTAGE_MASK) != 0) << 8 | 0xaa;
	cmd.resp_type = MMC_RSP_R7;
	flags = MMC_CMD_FLAG_CTYPE_XOR(1) | MMC_CMD_FLAG_RTYPE_XOR(2);

	err = mmc_send_cmd(mmc, &cmd, NULL, flags);

	/* Restore timeout */
	emm_wdog.s.clk_cnt = mmc->clock;
	cvmx_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);

	if (err) {
		debug("%s failed\n", __func__);
		return err;
	}

	if ((cmd.response[0] & 0xff) != 0xaa) {
		debug("%s: Unusable error, response is 0x%x\n",
		      __func__, cmd.response[0]);
		return UNUSABLE_ERR;
	} else {
		mmc->version = SD_VERSION_2;
		debug("%s: SD version 2 detected\n", __func__);
	}
#endif
	return 0;
}

void mmc_reset_bus(struct mmc *mmc, int preserve_switch)
{
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	cvmx_mio_emm_cfg_t emm_cfg;
	cvmx_mio_emm_switch_t emm_switch;

	if (preserve_switch) {
		emm_switch.u64 = mmc_read_csr(CVMX_MIO_EMM_SWITCH);
		if (emm_switch.s.bus_id != host->bus_id) {
			emm_switch.s.bus_id = host->bus_id;
			mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
		}
	}

	/* Reset the bus */
	emm_cfg.u64 = mmc_read_csr(CVMX_MIO_EMM_CFG);
	emm_cfg.u64 &= ~(1 << host->bus_id);
	mmc_write_csr(CVMX_MIO_EMM_CFG, emm_cfg.u64);
	mdelay(20);	/* Wait 20ms */
	emm_cfg.u64 |= 1 << host->bus_id;
	mmc_write_csr(CVMX_MIO_EMM_CFG, emm_cfg.u64);

	mdelay(20);

	/* Restore switch settings */
	if (preserve_switch) {
		emm_switch.s.switch_exe = 0;
		emm_switch.s.switch_err0 = 0;
		emm_switch.s.switch_err1 = 0;
		emm_switch.s.switch_err2 = 0;
		emm_switch.s.clk_hi = (host->clk_period + 1) / 2;
		emm_switch.s.clk_lo = (host->clk_period + 1) / 2;
		emm_switch.s.bus_id = 0;
		mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
		udelay(100);
		emm_switch.s.bus_id = host->bus_id;
		mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	}
}

int mmc_startup(struct mmc *mmc)
{
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	u64 cmult, csize, capacity;
	int err;
	uint mult, freq;
	cvmx_mio_emm_switch_t emm_switch;
	cvmx_mio_emm_wdog_t emm_wdog;
	cvmx_mio_emm_cfg_t emm_cfg;
	cvmx_mio_emm_sts_mask_t emm_sts_mask;

	/* frequency bases */
	/* divided by 10 to be nice to platforms without floating point */
	static const int fbase[] = {
		10000,
		100000,
		1000000,
		10000000,
		0, 0, 0, 0
	};

	/* Multiplier values for TRAN_SPEED.  Multiplied by 10 to be nice
	* to platforms without floating point.
	*/
	static const int multipliers[] = {
		0,	/* reserved */
		10, 12, 13, 15, 20, 26, 30, 35,
		40, 45, 50, 52, 55, 60, 70, 80 };

	debug("%s: bus_id: %d\n", __func__, host->bus_id);

	mmc->rca = 0;

	/* Clear interrupt status */
	mmc_write_csr(CVMX_MIO_EMM_INT, mmc_read_csr(CVMX_MIO_EMM_INT));

	/* Enable the bus */
	emm_cfg.u64 = mmc_read_csr(CVMX_MIO_EMM_CFG);
	emm_cfg.u64 |= (1 << host->bus_id);
	debug("%s: writing 0x%llx to mio_emm_cfg\n", __func__, emm_cfg.u64);
	mmc_write_csr(CVMX_MIO_EMM_CFG, emm_cfg.u64);
	mdelay(2);

	/* Set clock period */
	host->clk_period = (host->sclock + mmc->clock - 1) / mmc->clock;

	/* Default to RCA of 1 */
	mmc_write_csr(CVMX_MIO_EMM_RCA, 1);

	/* Set the bus speed and width */
	emm_switch.u64 = 0;
	emm_switch.s.bus_width = EXT_CSD_BUS_WIDTH_1;
	emm_switch.s.power_class = 10;
	emm_switch.s.clk_hi = emm_switch.s.clk_lo = (host->clk_period + 1) / 2;
	mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	emm_switch.s.bus_id = host->bus_id;
	udelay(1200);
	mmc_write_csr(CVMX_MIO_EMM_SWITCH, emm_switch.u64);
	udelay(1200);

	last_bus_id = host->bus_id;

#ifdef DEBUG
	debug("%s: Set clock period to %d clocks, sclock: %u\n", __func__,
	      emm_switch.s.clk_hi + emm_switch.s.clk_lo, host->sclock);
#endif
	/* Set watchdog for command timeout */
	if (host->bus_id == 0)
		emm_wdog.u64 = 0;
	else
		emm_wdog.u64 = mmc_read_csr(CVMX_MIO_EMM_WDOG);
	emm_wdog.s.clk_cnt = mmc->clock;
	debug("Setting command timeout value to %u\n", emm_wdog.s.clk_cnt);
	mmc_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);

	mdelay(10);	/* Wait 10ms */

	/* Set status mask */
	emm_sts_mask.u64 = 0;
	emm_sts_mask.s.sts_msk = 1 << 7 | 1 << 22 | 1 << 23 | 1 << 19;
	mmc_write_csr(CVMX_MIO_EMM_STS_MASK, emm_sts_mask.u64);

	/* Reset the card */
	debug("Resetting card\n");
	if ((err = mmc_pre_idle(mmc))) {
		mmc_print_registers(mmc);
		if (!init_time)
			printf("%s: Could not enter pre-idle state\n", __func__);
		return err;
	}
	if ((err = mmc_go_idle(mmc))) {
		mmc_print_registers(mmc);
		if (!init_time)
			printf("%s: Could not reset MMC card\n", __func__);
		return err;
	}

#ifdef CONFIG_OCTEON_MMC_SD
	/* Note that this doesn't work yet on the CN61XX pass 1.0.
	 * The CN61XX pass 1.0 has an errata where only 8-bit wide buses are
	 * supported due to checksum errors on narrower busses.
	 */
	debug("Testing for SD version 2, voltages: 0x%x\n", mmc->voltages);
	/* Test for SD version 2 */
	err = mmc_send_if_cond(mmc);
#endif
	/* Now try to get the SD card's operating condition */
	if (!err && IS_SD(mmc)) {
#ifdef CONFIG_OCTEON_MMC_SD
		debug("Getting SD card operating condition\n");
		err = sd_send_op_cond(mmc);
		if (err == TIMEOUT) {
			debug("Cannot get SD operating condition, trying MMC\n");
			err = mmc_send_op_cond(mmc);
			if (err) {
				printf("Card did not respond to voltage select!\n");
				return UNUSABLE_ERR;
			}
		}

		if (err) {
			err = mmc_send_op_cond(mmc);
			if (err) {
				puts("MMC Init: Error recovering after SD Version 2 test\n");
				return UNUSABLE_ERR;
			}
		}
#endif
	} else {
		mdelay(100);
		/* Clear interrupt status */
		mmc_write_csr(CVMX_MIO_EMM_INT, mmc_read_csr(CVMX_MIO_EMM_INT));
		debug("Resetting card for MMC\n");
		mmc_pre_idle(mmc);
		mdelay(2);
		mmc_go_idle(mmc);
		mdelay(2);

		debug("Getting MMC card operating condition\n");
		err = mmc_send_op_cond(mmc);
		if (err == TIMEOUT) {
			debug("Trying again...\n");
			/* Resetting MMC bus */
			mmc_reset_bus(mmc, TRUE);
			debug("%s: Going idle\n", __func__);
			mmc_pre_idle(mmc);
			mmc_go_idle(mmc);
			err = mmc_send_op_cond(mmc);
			if (err) {
				debug("MMC Init: Card did not respond to voltage select\n");
				return UNUSABLE_ERR;
			}
		} else if (err) {
			debug("Resetting MMC bus\n");
			/* Resetting MMC bus */
			mmc_reset_bus(mmc, TRUE);
			debug("%s: Going idle\n", __func__);
			mmc_pre_idle(mmc);
			mmc_go_idle(mmc);
			mdelay(100);
			err = mmc_send_op_cond(mmc);
			if (err) {
				puts("MMC Init: Error recovering after SD Version 2 test\n");
				return UNUSABLE_ERR;
			}
		}
	}

	debug("%s: Getting CID\n", __func__);
	err = mmc_all_send_cid(mmc);
	if (err) {
		printf("%s: Error getting CID\n", __func__);
		return err;
	}

	/* For MMC cards, set the Relative Address.
	 * For SD cards, get the Relative address.
	 * This also puts the cards into Standby State.
	 */
	if (IS_SD(mmc)) {
#ifdef CONFIG_OCTEON_MMC_SD
		debug("%s: Getting SD relative address\n", __func__);
		err = sd_send_relative_addr(mmc);
		if (err) {
			printf("%s: Error getting RCA\n", __func__);
			return err;
		}
#endif
	} else {
		mmc->rca = host->bus_id + 0x10;	/* RCA must be > 1 */
		debug("%s: Setting MMC relative address to %d\n",
		      __func__, mmc->rca);
		err = mmc_set_relative_addr(mmc);
		if (err) {
			mmc_print_registers(mmc);
			printf("%s: Error setting MMC RCA to %d\n",
			       __func__, mmc->rca);
			return err;
		}
#if 0
		mmc_write_csr(CVMX_MIO_EMM_RCA, mmc->rca);
#endif
	}

	debug("Getting CSD\n");
	err = mmc_get_csd(mmc);
	if (err) {
		printf("%s: Error getting CSD\n", __func__);
		cvmx_mio_emm_switch_t emm_switch;
		emm_switch.u64 = mmc_read_csr(CVMX_MIO_EMM_SWITCH);
		printf("clk period: %d\n",
		       emm_switch.s.clk_hi + emm_switch.s.clk_lo);
		return err;
	}
	if (mmc->version == MMC_VERSION_UNKNOWN) {
		int version = (mmc->csd[0] >> 26) & 0xf;

		switch (version) {
			case 0:
				mmc->version = MMC_VERSION_1_2;
				debug("MMC version 1.2 detected\n");
				break;
			case 1:
				mmc->version = MMC_VERSION_1_4;
				debug("MMC version 1.4 detected\n");
				break;
			case 2:
				mmc->version = MMC_VERSION_2_2;
				debug("MMC version 2.2 detected\n");
				break;
			case 3:
				mmc->version = MMC_VERSION_3;
				debug("MMC version 3 detected\n");
				break;
			case 4:
				mmc->version = MMC_VERSION_4;
				debug("MMC version 4 detected\n");
				break;
			default:
				mmc->version = MMC_VERSION_1_2;
				debug("MMC version 1.2 (unknown) detected\n");
				break;
		}
	}

	freq = fbase[(mmc->csd[0] & 7)];
	mult = multipliers[((mmc->csd[0] >> 3) & 0xf)];

#ifdef DEBUG
	int i, classes;
	i = 0;
	classes = (mmc->csd[1] >> 20) & 0x7ff;
	debug("Classes supported: ");
	while (classes) {
		if (classes & 1)
			debug("%i ", i);
		classes >>= 1;
		i++;
	}
	debug("\n%s: Read block length: %u\n", __func__,
	      1 << ((mmc->csd[1] >> 16) & 0xF));
#endif

	if (IS_SD(mmc))
		switch (mmc->csd[0] & 0x7f) {
		case 0x0b:	mmc->tran_speed = 50000000;	break;
		case 0x2b:	mmc->tran_speed = 200000000;	break;
		case 0x32:	mmc->tran_speed = 25000000;	break;
		case 0x5a:	mmc->tran_speed = 50000000;	break;
		default:
			printf("Unknown tran_speed value 0x%x in SD CSD register\n",
			       mmc->csd[0] & 0x7f);
			mmc->tran_speed = 25000000;
			break;
		}
	else
		mmc->tran_speed = freq * mult;
	debug("%s CSD tran_speed: %u\n",
	      IS_SD(mmc) ? "SD" : "MMC", mmc->tran_speed);

	mmc->read_bl_len = 1 << ((mmc->csd[3] >> 22) & 0xf);

	if (IS_SD(mmc))
		mmc->write_bl_len = mmc->read_bl_len;
	else
		mmc->write_bl_len = 1 << ((mmc->csd[3] >> 22) & 0xf);

	if (mmc->high_capacity) {
		csize = (mmc->csd[1] & 0x3f) << 16
			| (mmc->csd[2] & 0xffff0000) >> 16;
		cmult = 8;
	} else {
		csize = (mmc->csd[1] & 0x3ff) << 2
			| (mmc->csd[2] & 0x00038000) >> 16;
		cmult = (mmc->csd[2] & 0x00038000) >> 15;
	}

	mmc->capacity = (csize + 1) << (cmult + 2);
	mmc->capacity *= mmc->read_bl_len;
	debug("%s: capacity: %llu bytes\n", __func__, mmc->capacity);
	debug("%s: read to write program time factor: %d\n", __func__,
	      1 << ((mmc->csd[0] >> 26) & 7));

	mmc->erase_grp_size = 1;
	mmc->read_bl_len = min(mmc->read_bl_len, 512);
	mmc->write_bl_len = min(mmc->write_bl_len, 512);

	/* Select the card and put it into Transfer Mode */

	debug("%s: Selecting card to rca %d\n", __func__, mmc->rca);

	err = mmc_select_card(mmc);
	if (err) {
		printf("%s: Error selecting card\n", __func__);
		return err;
	}

	if (IS_SD(mmc)) {
		debug("SD version: ");
		switch(mmc->version) {
		case SD_VERSION_3:	debug("3\n");		break;
		case SD_VERSION_2:	debug("2\n");		break;
		case SD_VERSION_1_0:	debug("1.0\n");		break;
		case SD_VERSION_1_10:	debug("1.10\n");	break;
		default:		debug("Undefined\n");	break;
		}

		debug("sd version 0x%x\n", mmc->version);
	} else {
		debug("MMC version: ");
		switch (mmc->version) {
		case MMC_VERSION_UNKNOWN:	debug("UNKNOWN\n");	break;
		case MMC_VERSION_1_2:		debug("1.2\n");		break;
		case MMC_VERSION_1_4:		debug("1.4\n");		break;
		case MMC_VERSION_2_2:		debug("2.2\n");		break;
		case MMC_VERSION_3:		debug("3\n");		break;
		case MMC_VERSION_4:		debug("4\n");		break;
		default:			debug("Undefined\n");	break;
		}

		debug("mmc version 0x%x\n", mmc->version);
		if (mmc->version >= MMC_VERSION_4) {
		/* Check ext_csd version and capacity */
			err = mmc_send_ext_csd(mmc);
			if (err) {
				printf("%s: Error: cannot read extended CSD\n",
				       __func__);
				return -1;
			}
			if (host->ext_csd[EXT_CSD_REV] >= 2) {
				capacity = host->ext_csd[EXT_CSD_SEC_CNT] << 0
					| host->ext_csd[EXT_CSD_SEC_CNT + 1] << 8
					| host->ext_csd[EXT_CSD_SEC_CNT + 2] << 16
					| host->ext_csd[EXT_CSD_SEC_CNT + 3] << 24;
				debug("MMC EXT CSD reports capacity of %llu sectors (0x%llx bytes)\n",
				      capacity, capacity * 512);
				capacity *= 512;
				if (((capacity >> 20) > 2 * 1024)
				    && mmc->high_capacity)
					mmc->capacity = capacity;
			}
			if (host->ext_csd[EXT_CSD_ERASE_GROUP_DEF]) {
				mmc->erase_grp_size =
					host->ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE]
						* 512 * 1024;
			} else {
				int erase_gsz, erase_gmul;
				erase_gsz = (mmc->csd[2] & 0x00007c00) >> 10;
				erase_gmul = (mmc->csd[2] & 0x000003e0) >> 5;
				mmc->erase_grp_size = (erase_gsz + 1)
							* (erase_gmul + 1);
			}
			debug("%s: erase group size %d\n",
			      __func__, mmc->erase_grp_size);
			if (host->ext_csd[EXT_CSD_PARTITIONING_SUPPORT] & PART_SUPPORT) {
				mmc->part_config = host->ext_csd[EXT_CSD_PART_CONF];
				debug("%s: partitioning config 0x%x\n", __func__,
				      mmc->part_config);
			}
			debug("%s: part config: 0x%x\n", __func__,
			      mmc->part_config);
			if (host->ext_csd[EXT_CSD_CARD_TYPE]
			    & EXT_CSD_CARD_TYPE_26) {
				mmc->card_caps |= MMC_MODE_HS;
				debug("%s: high-speed mode supported\n",
				      __func__);
			}
			if (host->ext_csd[EXT_CSD_CARD_TYPE]
			    & EXT_CSD_CARD_TYPE_52) {
				mmc->card_caps |=
					MMC_MODE_HS_52MHz | MMC_MODE_HS;
				debug("%s: high-speed 52MHz mode supported\n",
				      __func__);
			}
		}
	}

	debug("%s: Changing frequency\n", __func__);
#ifdef CONFIG_OCTEON_MMC_SD
	if (IS_SD(mmc)) {
		err = sd_change_freq(mmc);
	} else
#endif
	{
		mmc_set_ios(mmc);
		err = 0;
	}
	if (err) {
		printf("%s: Error changing frequency\n", __func__);
		return err;
	}

	/* Restrict card's capabilities by what the host can do. */
	debug("%s: MMC card caps: 0x%x, host caps: 0x%x\n",
	      __func__, mmc->card_caps, mmc->host_caps);
	mmc->card_caps &= mmc->host_caps;


	if (IS_SD(mmc)) {
#ifdef CONFIG_OCTEON_MMC_SD
		err = sd_set_bus_width_speed(mmc);
		if (err) {
			printf("%s: Error setting SD bus width and/or speed\n",
			       __func__);
			return err;
		}
#endif
	} else {
		err = mmc_set_bus_width_speed(mmc);
		if (err) {
			printf("%s: Error setting MMC bus width and/or speed\n",
			       __func__);
			return err;
		}
	}

	err = mmc_set_blocklen(mmc, mmc->read_bl_len);
	if (err) {
		printf("%s: Error setting block length to %d\n",
		       __func__, mmc->read_bl_len);
		return err;
	}

	/* Set watchdog for command timeout again */
	emm_wdog.u64 = 0;
	emm_wdog.s.clk_cnt = 256000 + (10 * mmc->clock) / 8;
	mmc_write_csr(CVMX_MIO_EMM_WDOG, emm_wdog.u64);

	/* Fill in device description */
	debug("%s: Filling in block descriptor\n",  __func__);
	mmc->block_dev.lun = 0;
	mmc->block_dev.type = 0;
	mmc->block_dev.blksz = mmc->read_bl_len;
	mmc->block_dev.lba = lldiv(mmc->capacity, mmc->read_bl_len);
	if (IS_SD(mmc)) {
		sprintf(mmc->block_dev.vendor, "Man %02x Snr %08x",
			mmc->cid[0] >> 24,
		(mmc->cid[2] << 8) | (mmc->cid[3] >> 24));
		sprintf(mmc->block_dev.product, "%c%c%c%c%c",
			mmc->cid[0] & 0xff,
		mmc->cid[1] >> 24, (mmc->cid[1] >> 16) & 0xff,
		(mmc->cid[1] >> 8) & 0xff, mmc->cid[1] & 0xff);
	} else {
		sprintf(mmc->block_dev.vendor, "Man %06x Snr %08x",
			mmc->cid[0] >> 8,
			(mmc->cid[2] << 8) | (mmc->cid[3] >> 24));
		sprintf(mmc->block_dev.product, "%c%c%c%c%c%c",
			mmc->cid[0] & 0xff,
		mmc->cid[1] >> 24, (mmc->cid[1] >> 16) & 0xff,
		(mmc->cid[1] >> 8) & 0xff, mmc->cid[1] & 0xff,
		(mmc->cid[2] >> 24) & 0xff);
	}
	debug("%s: %s\n", __func__, mmc->block_dev.vendor);
	debug("%s: %s\n", __func__, mmc->block_dev.product);
	if (IS_SD(mmc))
		sprintf(mmc->block_dev.revision,"%d.%d",
			(mmc->cid[2] >> 28) & 0xf,
		(mmc->cid[2] >> 24) & 0xf);
	else
		sprintf(mmc->block_dev.revision,"%d.%d",
			(mmc->cid[2] >> 20) & 0xf,
		(mmc->cid[2] >> 16) & 0xf);
	debug("%s: %s\n", __func__, mmc->block_dev.revision);

	return 0;
}

/**
 * This is the external mmc_send_cmd function.  It was required that
 * the internal version support flags so this version is required.
 */
static int octeon_mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd,
			       struct mmc_data *data)
{
	return mmc_send_cmd(mmc, cmd, data, 0);
}

int __mmc_getwp(struct mmc *mmc)
{
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	int bus = host->bus_id;
	int val = 0;

	if (mmc_info.slot[bus].wp_gpio >= 0) {
		val = gpio_get_value(mmc_info.slot[bus].wp_gpio);
		debug("%s(%d): gpio %d returned %d\n", __func__, bus,
		      mmc_info.slot[bus].wp_gpio, val);
		if (mmc_info.slot[bus].wp_active_low)
			val = !val;
	}
	return val;
}
int mmc_getwp(struct mmc *mmc) __attribute__((weak, alias("__mmc_getwp")));

int __mmc_getcd(struct mmc *mmc)
{
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	int bus = host->bus_id;
	int val = 1;

	if (mmc_info.slot[bus].cd_gpio >= 0) {
		val = gpio_get_value(mmc_info.slot[bus].cd_gpio);
		debug("%s(%d): gpio %d returned %d\n", __func__, bus,
		      mmc_info.slot[bus].cd_gpio, val);
		if (mmc_info.slot[bus].cd_active_low)
			val = !val;
	}
	return val;
}
int mmc_getcd(struct mmc *mmc) __attribute__((weak, alias("__mmc_getcd")));

void __mmc_set_power(struct mmc *mmc, int on)
{
	struct mmc_host *host = (struct mmc_host *)mmc->priv;
	int bus = host->bus_id;
	int val;

	if (mmc_info.slot[bus].power_gpio >= 0) {
		if (mmc_info.slot[bus].power_active_low)
			val = !on;
		else
			val = !!on;
		gpio_direction_output(mmc_info.slot[bus].power_gpio, val);
		debug("%s(%d, %s) set GPIO %d to %d\n", __func__, bus,
		      on ? "on" : "off", mmc_info.slot[bus].power_gpio, val);
		/* Give time for power to settle */
		if (on)
			mdelay(POWER_ON_TIME);
	}
}
void mmc_set_power(struct mmc *mmc, int on)
	__attribute__((weak, alias("__mmc_set_power")));

int mmc_initialize(bd_t *bis)
{
	struct mmc *mmc;
	struct mmc_host *host;
	int bus_id = 0;
	int rc;
	cvmx_mio_emm_cfg_t emm_cfg;
	int repeat;
	uint64_t clock_period;
	int found = 0;

	/* Get MMC information from the FDT */
	if ((rc = octeon_boot_bus_mmc_get_info(&mmc_info)) != 0)
		goto out;

	init_time = 1;	/* Suppress error messages */
	INIT_LIST_HEAD(&mmc_devices);
	mmc_set_dev(-1);

	/* Disable all MMC slots */
	emm_cfg.u64 = 0;
	mmc_write_csr(CVMX_MIO_EMM_CFG, emm_cfg.u64);
	mdelay(100);

	rc = -1;

	/* Power down all MMC devices */
	for (bus_id = 0; bus_id < CONFIG_OCTEON_MAX_MMC_SLOT; bus_id++) {
		if (mmc_info.slot[bus_id].chip_sel < 0) {
			debug("%s: Skipping MMC bus %d\n", __func__, bus_id);
			continue;
		}
		debug("Initializing MMC bus %d data structures\n", bus_id);
		mmc = &mmc_dev[bus_id];
		host = &mmc_host[bus_id];
		memset(mmc, 0, sizeof(*mmc));
		memset(host, 0, sizeof(*host));
		mmc->priv = (void *)host;
		mmc->priv = (void *)host;
		sprintf(mmc->name, "Octeon MMC/SD%d", bus_id);
		mmc->version = MMC_VERSION_UNKNOWN;
		mmc->rca = bus_id + 0x10;
		mmc->clock = CONFIG_OCTEON_MMC_MIN_BUS_SPEED_HZ;
		host->bus_id = bus_id;
		host->mmc = mmc;
		host->dev_index = bus_id;
		host->sector_mode = 0;
		host->sclock = cvmx_clock_get_rate(CVMX_CLOCK_SCLK);
		clock_period = 1000000000000ULL / host->sclock;
		debug("%s: sclock period: %llu ps\n",
		      __func__, clock_period);
		host->cmd_clk_skew = (mmc_info.slot[bus_id].cmd_clk_skew
				      + clock_period / 2)
				/ clock_period;
		debug("%s: command clock skew: %u sclock cycles\n",
		      __func__, host->cmd_clk_skew);

		host->dat_clk_skew = (mmc_info.slot[bus_id].dat_clk_skew
				      + clock_period / 2)
				/ clock_period;
		debug("%s: data clock skew: %u sclock cycles\n",
		      __func__, host->dat_clk_skew);
		host->bus_width = EXT_CSD_BUS_WIDTH_1;
		host->cd_gpio = mmc_info.slot[bus_id].cd_gpio;
		host->cd_active_low = mmc_info.slot[bus_id].cd_active_low;
		if (host->cd_gpio != -1)
			gpio_direction_input(host->cd_gpio);

		host->wp_gpio = mmc_info.slot[bus_id].wp_gpio;
		host->wp_active_low = mmc_info.slot[bus_id].wp_active_low;
		if (host->wp_gpio != -1)
			gpio_direction_input(host->wp_gpio);

		host->power_gpio = mmc_info.slot[bus_id].power_gpio;
		host->power_active_low = mmc_info.slot[bus_id].power_active_low;

		debug("Powering down MMC slot %d\n", bus_id);
		mmc_set_power(mmc, 0);
	}
	mdelay(100);
	/* Power them all up */
	for (bus_id = 0; bus_id < CONFIG_OCTEON_MAX_MMC_SLOT; bus_id++) {
		if (mmc_info.slot[bus_id].chip_sel < 0) {
			debug("%s: Skipping MMC bus %d\n", __func__, bus_id);
			continue;
		}
		mmc = &mmc_dev[bus_id];
		debug("Powering up MMC slot %d\n", bus_id);
		mmc_set_power(mmc, 1);
	}
	mdelay(POWER_ON_TIME);

	for (bus_id = 0; bus_id < CONFIG_OCTEON_MAX_MMC_SLOT; bus_id++) {
		/* Skip slot if not in device tree */
		if (mmc_info.slot[bus_id].chip_sel < 0) {
			debug("%s: Skipping MMC bus %d\n", __func__, bus_id);
			continue;
		}

		mmc = &mmc_dev[bus_id];
		host = mmc->priv;

		if (!mmc_getcd(mmc)) {
			debug("%s: Skipping empty slot %d\n", __func__, bus_id);
			continue;
		}

		for (repeat = 0; repeat < 2; repeat++) {
			host->bus_width = EXT_CSD_BUS_WIDTH_1;

			debug("%s: Calling mmc_init for %s, try %d\n",
			      __func__, mmc->name, repeat);
			rc = mmc_init(mmc);
			if (!rc) {
				found++;
				break;
			} else {
				debug("MMC device %d initialization failed, try %d\n",
				      bus_id, repeat);
				mmc_pre_idle(mmc);
				mmc_go_idle(mmc);
			}
		}
	}
	init_time = 0;

out:
	if (found)
		print_mmc_devices(',');
	else
		printf("not available\n");
	return rc;
}

int mmc_init(struct mmc *mmc)
{
	struct mmc_host *host = (struct mmc_host *)(mmc->priv);
	int rc;
	int cs;

	if (!octeon_has_feature(OCTEON_FEATURE_MMC))
		return 0;

	debug("%s: Entry\n", __func__);

	cs = host->bus_id;
	mmc_enable(mmc);

	mmc->f_min = CONFIG_OCTEON_MMC_MIN_BUS_SPEED_HZ;
	mmc->clock = mmc->f_min;
	mmc->f_max = mmc_info.slot[cs].max_frequency;
#ifdef CONFIG_OCTEON_MMC_MAX_FREQUENCY
	mmc->f_max = min(mmc->f_max, CONFIG_OCTEON_MMC_MAX_FREQUENCY);
#endif
	mmc->f_max = min(mmc->f_max, getenv_ulong("mmc_max_freq", 10, 52000000));
	mmc->b_max = CONFIG_SYS_MMC_MAX_BLK_COUNT;
	host->sclock = cvmx_clock_get_rate(CVMX_CLOCK_SCLK);
	debug("%s: sclock: %u\n", __func__, host->sclock);

	/* Set up the host capabilities */
	if (mmc->f_max > 20000000) {
		mmc->host_caps |= MMC_MODE_HS;
		debug("  Enabling HS mode, f_max: %d\n", mmc->f_max);
	}
	if (mmc->f_max >= 52000000) {
		mmc->host_caps |= MMC_MODE_HS_52MHz;
		debug("  Enabling HS 52 mode\n");
	}

	host->max_width = 1;
	if (mmc_info.slot[cs].bus_max_width >= 4) {
		mmc->host_caps |= MMC_MODE_4BIT;
		host->max_width = 4;
		debug("  Enabling 4-bit support\n");
	}
	if (mmc_info.slot[cs].bus_max_width == 8) {
		mmc->host_caps |= MMC_MODE_8BIT;
		host->max_width = 8;
		debug("  Enabling 8-bit support\n");
	}
	mmc->bus_width = host->max_width;
	debug("%s: Max bus width: %d\n", __func__,
	      mmc_info.slot[cs].bus_max_width);
	mmc->host_caps |= MMC_MODE_DDR;
	mmc->send_cmd = octeon_mmc_send_cmd;
	mmc->set_ios = mmc_set_ios;
	mmc->init = NULL;
	mmc->getcd = mmc_getcd;
	mmc->getwp = mmc_getwp;
	mmc->voltages = getenv_ulong("mmc_voltages", 16, 0);
	if (!mmc->voltages)
		mmc->voltages =  MMC_VDD_27_28 | MMC_VDD_28_29 | MMC_VDD_29_30 |
				 MMC_VDD_30_31 | MMC_VDD_31_32 | MMC_VDD_32_33 |
				 MMC_VDD_33_34 | MMC_VDD_34_35 | MMC_VDD_35_36;
	mmc->voltages &= OCR_VOLTAGE_MASK;

	mmc_set_bus_width(mmc, 1);
	mmc_set_clock(mmc, mmc->f_min);

	rc = mmc_startup(mmc);

	mmc_disable(mmc);
	if (rc == 0) {
		host->initialized = 1;
		if (!host->registered) {
			debug("Registering MMC device %d\n", host->bus_id);
			mmc_register(mmc);
			host->registered = 1;
		}
		if (get_mmc_num() < 0)
			mmc_set_dev(mmc->block_dev.dev);
		debug("Initializing partitions\n");
		init_part(&mmc->block_dev);
	} else if (!list_empty(&mmc_devices)) {
		debug("mmc dev %d initialization failed\n", mmc->block_dev.dev);
		struct list_head *entry;

		list_for_each(entry, &mmc_devices) {
			if (list_entry(entry, struct mmc, link) == mmc) {
				debug("%s: Deleting from list\n", __func__);
				list_del(entry);
				break;
			}
		}
		/* Change current device to first good device if we fail */
		mmc = list_first_entry(&mmc_devices, struct mmc, link);
		mmc_set_dev(mmc ? mmc->block_dev.dev : -1);
	}

	return rc;
}

int get_mmc_num(void)
{
	return cur_dev_num;
}
#ifdef DEBUG
int do_oct_mmc(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	mmc_initialize(gd->bd);
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(octmmc, 2, 1, do_oct_mmc, "Octeon MMC initialization", NULL);
#endif
