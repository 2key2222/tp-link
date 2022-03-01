/*
 * (C) Copyright 2011
 * Joe Hershberger, National Instruments, joe.hershberger@ni.com
 *
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>

#include "rtk_switch.h"
#include "stat.h"
#include "smi.h"

#include "rtl8367c_asicdrv_phy.h"
#include "rtl8367c_asicdrv.h"


static int dump_rtk_stat_per_port(int port)
{
    rtk_stat_port_cntr_t counter = {0};
    rtk_api_ret_t ret = 0;

    ret = rtk_stat_port_getAll(port, &counter);
    if (ret != 0) {
        printf("rtk_stat_port_getAll(%d) failed, ret = %d\n", port, ret);
    }

#define __PR(x) printf("  %-56s = %10llu\r\n", #x, (uint64_t)counter.x)

    printf("--------------------------------------------\n");

    __PR(ifInOctets);
    __PR(dot3StatsFCSErrors);
    __PR(dot3StatsSymbolErrors);
    __PR(dot3InPauseFrames);
    __PR(dot3ControlInUnknownOpcodes);
    __PR(etherStatsFragments);
    __PR(etherStatsJabbers);
    __PR(ifInUcastPkts);
    __PR(etherStatsDropEvents);
    __PR(etherStatsOctets);
    __PR(etherStatsUndersizePkts);
    __PR(etherStatsOversizePkts);
    __PR(etherStatsPkts64Octets);
    __PR(etherStatsPkts65to127Octets);
    __PR(etherStatsPkts128to255Octets);
    __PR(etherStatsPkts256to511Octets);
    __PR(etherStatsPkts512to1023Octets);
    __PR(etherStatsPkts1024toMaxOctets);
    __PR(etherStatsMcastPkts);
    __PR(etherStatsBcastPkts);
    __PR(ifOutOctets);
    __PR(dot3StatsSingleCollisionFrames);
    __PR(dot3StatsMultipleCollisionFrames);
    __PR(dot3StatsDeferredTransmissions);
    __PR(dot3StatsLateCollisions);
    __PR(etherStatsCollisions);
    __PR(dot3StatsExcessiveCollisions);
    __PR(dot3OutPauseFrames);
    __PR(dot1dBasePortDelayExceededDiscards);
    __PR(dot1dTpPortInDiscards);
    __PR(ifOutUcastPkts);
    __PR(ifOutMulticastPkts);
    __PR(ifOutBrocastPkts);
    __PR(outOampduPkts);
    __PR(inOampduPkts);
    __PR(pktgenPkts);
    __PR(inMldChecksumError);
    __PR(inIgmpChecksumError);
    __PR(inMldSpecificQuery);
    __PR(inMldGeneralQuery);
    __PR(inIgmpSpecificQuery);
    __PR(inIgmpGeneralQuery);
    __PR(inMldLeaves);
    __PR(inIgmpLeaves);
    __PR(inIgmpJoinsSuccess);
    __PR(inIgmpJoinsFail);
    __PR(inMldJoinsSuccess);
    __PR(inMldJoinsFail);
    __PR(inReportSuppressionDrop);
    __PR(inLeaveSuppressionDrop);
    __PR(outIgmpReports);
    __PR(outIgmpLeaves);
    __PR(outIgmpGeneralQuery);
    __PR(outIgmpSpecificQuery);
    __PR(outMldReports);
    __PR(outMldLeaves);
    __PR(outMldGeneralQuery);
    __PR(outMldSpecificQuery);
    __PR(inKnownMulticastPkts);
    __PR(ifInMulticastPkts);
    __PR(ifInBroadcastPkts);
    __PR(ifOutDiscards);

    printf("--------------------------------------------\n");

    return 0;
}


static int do_rtk_port_stat(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int port = 0;
    //rtk_stat_port_cntr_t counter = {0};
    //rtk_api_ret_t ret = 0;

	if (argc < 3)
		return CMD_RET_USAGE;

    if (!strcmp(argv[1], "show"))
    {
        port = simple_strtoul(argv[2], NULL, 10);

        printf("Dump Port : %d\n", port);

        dump_rtk_stat_per_port(port);
    }
    else if (!strcmp(argv[1], "reset")) 
    {
        if (!strcmp(argv[2], "all")) 
        {
            printf("Reset All Port.\n");
            rtk_stat_global_reset();
        }
        else
        {
            port = simple_strtoul(argv[2], NULL, 10);

            printf("Reset Port : %d\n", port);

            rtk_stat_port_reset(port);
        }
    }
    else
    {
        return CMD_RET_USAGE;
    }

	return 0;
}

static int do_rtk_phy_reg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    uint32_t addr = 0;
    uint32_t reg = 0;
    uint32_t data = 0;

    int ret = 0;

    if (argc < 4)
		return CMD_RET_USAGE;

    if (!strcmp(argv[1], "read"))
    {
        if (argc != 4)
            return CMD_RET_USAGE;

        addr = simple_strtoul(argv[2], NULL, 10);
        reg = simple_strtoul(argv[3], NULL, 16);
        ret = rtl8367c_getAsicPHYReg(addr, reg, &data);
        printf("AsicPHYReg READ %d : phy %d reg 0x%x value 0x%x\n", ret, addr, reg, data);
    }
    else if (!strcmp(argv[1], "write"))
    {
        if (argc != 5)
            return CMD_RET_USAGE;

        addr = simple_strtoul(argv[2], NULL, 10);
        reg = simple_strtoul(argv[3], NULL, 16);
        data = simple_strtoul(argv[4], NULL, 16);
        ret = rtl8367c_setAsicPHYReg(addr, reg, data);
        printf("AsicPHYReg WRITE %d : phy %d reg 0x%x value 0x%x\n", ret, addr, reg, data);
    }
    else
        return CMD_RET_USAGE;

    return 0;
}

static int do_rtk_asic_reg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    //uint32_t addr = 0;
    uint32_t reg = 0;
    uint32_t data = 0;

    int ret = 0;

    if (argc < 3)
		return CMD_RET_USAGE;

    if (!strcmp(argv[1], "read"))
    {
        if (argc != 3)
            return CMD_RET_USAGE;

        reg = simple_strtoul(argv[2], NULL, 16);
        ret = rtl8367c_getAsicReg(reg, &data);
        printf("getAsicReg %d : reg 0x%x value 0x%x\n", ret, reg, data);

    }
    else if (!strcmp(argv[1], "write"))
    {
        if (argc != 4)
            return CMD_RET_USAGE;

        reg = simple_strtoul(argv[2], NULL, 16);
        data = simple_strtoul(argv[3], NULL, 16);
        ret = rtl8367c_setAsicReg(reg, data);
        printf("setAsicReg %d : reg 0x%x value 0x%x\n", ret, reg, data);
    }
    else
        return CMD_RET_USAGE;

    return 0;
}

static int do_rtk_smi_debug(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    /*int port = 0;
    rtk_stat_port_cntr_t counter = {0};
    rtk_api_ret_t ret = 0;*/

	if (argc != 2)
		return CMD_RET_USAGE;

    if (!strcmp(argv[1], "on"))
    {
        smi_debug(1);
    }
    else if (!strcmp(argv[1], "off")) 
    {
        smi_debug(0);
    }
    else
    {
        return CMD_RET_USAGE;
    }

	return 0;
}


U_BOOT_CMD(
	rtk_port_stat,	3,	1,	do_rtk_port_stat,
	"RTK Port MIB counter commands",
	"show <port>      - show MIB counter of port <port>\n"
	"rtk_port_stat reset <port>     - reset MIB counter of port <port>\n"
	"rtk_port_stat reset all        - reset MIB counter of all ports\n"
);


U_BOOT_CMD(
	rtk_phy_reg,	5,	1,	do_rtk_phy_reg,
	"RTK phy register commands",
	"read   <addr> <reg>        - read phy <addr> register <reg>\n"
	"rtk_phy_reg write  <addr> <reg> <data> - write phy <addr> register <reg> with value <data>\n"
);

U_BOOT_CMD(
	rtk_asic_reg,	5,	1,	do_rtk_asic_reg,
	"RTK asic register commands",
	"read   <reg>        - read asic register <reg>\n"
	"rtk_asic_reg write  <reg> <data> - write asic register <reg> with value <data>\n"
);


U_BOOT_CMD(
	rtk_smi_debug,	2,	1,	do_rtk_smi_debug,
	"RTK SMI debug",
    " { off | on }   - Debug info OFF/ON"
);
