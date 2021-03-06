/*
   Copyright (c) 2015 Broadcom
   All Rights Reserved

    <:label-BRCM:2015:DUAL/GPL:standard
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation (the "GPL").
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    
    A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
    writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
    
:>
*/



/* This is an automated file. Do not edit its contents. */


#include "bdmf_shell.h"
#include "rdd_map_auto.h"
#include "rdd_runner_reg_dump.h"
#include "rdd_runner_reg_dump_addrs.h"
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT BASIC_RATE_LIMITER_TABLE_DS =
{
	16,
	{
		{ dump_RDD_BASIC_RATE_LIMITER_DESCRIPTOR, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_SCHEDULING_QUEUE_TABLE =
{
	8,
	{
		{ dump_RDD_SCHEDULING_QUEUE_DESCRIPTOR, 0x800 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_BBH_TX_EGRESS_COUNTER_TABLE =
{
	8,
	{
		{ dump_RDD_BBH_TX_EGRESS_COUNTER_ENTRY, 0xd00 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT REGISTERS_BUFFER =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xd40 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_TM_ACTION_PTR_TABLE =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xdc0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT BUDGET_ALLOCATION_TIMER_VALUE =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xde2 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_BB_DESTINATION_TABLE =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xde4 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT SCHEDULING_FLUSH_GLOBAL_CFG =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xde6 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_SCHEDULING_GLOBAL_FLUSH_CFG =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xde7 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_TM_FLOW_CNTR_TABLE =
{
	1,
	{
		{ dump_RDD_TM_FLOW_CNTR_ENTRY, 0xde8 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_BBH_TX_QUEUE_ID_TABLE =
{
	4,
	{
		{ dump_RDD_BBH_TX_QUEUE_ID_ENTRY, 0xdf0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT TASK_IDX =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xdf8 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT SRAM_DUMMY_STORE =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xdfc },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_FIRST_QUEUE_MAPPING =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xdfd },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DEBUG_PRINT_CORE_LOCK =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xdfe },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT BASIC_SCHEDULER_TABLE_DS =
{
	16,
	{
		{ dump_RDD_BASIC_SCHEDULER_DESCRIPTOR, 0xe00 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_PD_FIFO_TABLE =
{
	16,
	{
		{ dump_RDD_PROCESSING_TX_DESCRIPTOR, 0x1000 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT UPDATE_FIFO_TABLE =
{
	4,
	{
		{ dump_RDD_UPDATE_FIFO_ENTRY, 0x1500 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT RUNNER_GLOBAL_REGISTERS_INIT =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1520 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_SCHEDULING_AGGREGATION_CONTEXT_VECTOR =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1540 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_SCHEDULING_FLUSH_VECTOR =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1560 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_SCHEDULING_QUEUE_AGING_VECTOR =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1580 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DEBUG_SCRATCHPAD =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1598 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT RATE_LIMITER_VALID_TABLE_DS =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x15c0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DEBUG_PRINT_TABLE =
{
	16,
	{
		{ dump_RDD_DEBUG_PRINT_INFO, 0x15d0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT FPM_GLOBAL_CFG =
{
	12,
	{
		{ dump_RDD_FPM_GLOBAL_CFG, 0x15e0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_TM_BBH_QUEUE_TABLE =
{
	4,
	{
		{ dump_RDD_BBH_QUEUE_DESCRIPTOR, 0x1600 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT COMPLEX_SCHEDULER_TABLE =
{
	64,
	{
		{ dump_RDD_COMPLEX_SCHEDULER_DESCRIPTOR, 0x1800 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT RUNNER_PROFILING_TRACE_BUFFER =
{
	4,
	{
		{ dump_RDD_TRACE_EVENT, 0x1c00 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT RX_FLOW_TABLE_1 =
{
	2,
	{
		{ dump_RDD_RX_FLOW_ENTRY, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_METER_TABLE_1 =
{
	8,
	{
		{ dump_RDD_CPU_RX_METER_ENTRY, 0x280 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RING_INTERRUPT_COUNTER_TABLE_1 =
{
	8,
	{
		{ dump_RDD_CPU_RING_INTERRUPT_COUNTER_ENTRY, 0x300 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_INTERRUPT_COALESCING_TABLE_1 =
{
	16,
	{
		{ dump_RDD_CPU_INTERRUPT_COALESCING_ENTRY, 0x390 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DIRECT_PROCESSING_PD_TABLE_1 =
{
	16,
	{
		{ dump_RDD_PROCESSING_RX_DESCRIPTOR, 0x3a0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DS_CPU_REASON_TO_METER_TABLE_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x3c0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_SCRATCHPAD_1 =
{
	8,
	{
		{ dump_RDD_BYTES_8, 0x400 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_SRAM_PD_FIFO_1 =
{
	16,
	{
		{ dump_RDD_PROCESSING_TX_DESCRIPTOR, 0x600 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT US_CPU_RX_METER_TABLE_1 =
{
	8,
	{
		{ dump_RDD_CPU_RX_METER_ENTRY, 0x700 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_REASON_AND_VPORT_TO_METER_TABLE_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x780 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_INTERRUPT_ID_DDR_ADDR_1 =
{
	8,
	{
		{ dump_RDD_DDR_ADDRESS, 0x7f8 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT RUNNER_PROFILING_TRACE_BUFFER_1 =
{
	4,
	{
		{ dump_RDD_TRACE_EVENT, 0x800 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_COPY_PD_FIFO_TABLE_1 =
{
	16,
	{
		{ dump_RDD_PROCESSING_TX_DESCRIPTOR, 0xa00 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT US_CPU_REASON_TO_METER_TABLE_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xa40 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT REGISTERS_BUFFER_1 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xa80 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_VPORT_TO_METER_TABLE_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb00 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_INTERRUPT_ID_DDR_ADDR_1 =
{
	8,
	{
		{ dump_RDD_DDR_ADDRESS, 0xb28 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_PSRAM_GET_NEXT_SCRATCHPAD_1 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xb30 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT RUNNER_GLOBAL_REGISTERS_INIT_1 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xb40 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT SCRATCH_1 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xb60 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT UPDATE_FIFO_TABLE_1 =
{
	4,
	{
		{ dump_RDD_UPDATE_FIFO_ENTRY, 0xb80 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_COPY_DISPATCHER_CREDIT_TABLE_1 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xba0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_INTERRUPT_SCRATCH_1 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xbac },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_RING_DESCRIPTOR_TABLE_1 =
{
	16,
	{
		{ dump_RDD_CPU_RING_DESCRIPTOR, 0xbb0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_COPY_UPDATE_FIFO_TABLE_1 =
{
	4,
	{
		{ dump_RDD_UPDATE_FIFO_ENTRY, 0xbc0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_RING_INDEX_DDR_ADDR_TABLE_1 =
{
	8,
	{
		{ dump_RDD_DDR_ADDRESS, 0xbe0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_INTERRUPT_COALESCING_TABLE_1 =
{
	16,
	{
		{ dump_RDD_CPU_INTERRUPT_COALESCING_ENTRY, 0xbf0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT PD_FIFO_TABLE_1 =
{
	16,
	{
		{ dump_RDD_PROCESSING_TX_DESCRIPTOR, 0xc00 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_REASON_TO_TC_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xc20 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT TC_TO_CPU_RXQ_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xc60 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT EXC_TC_TO_CPU_RXQ_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xca0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_FEED_RING_DESCRIPTOR_TABLE_1 =
{
	16,
	{
		{ dump_RDD_CPU_RING_DESCRIPTOR, 0xce0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_LOCAL_SCRATCH_1 =
{
	8,
	{
		{ dump_RDD_BYTES_8, 0xcf0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT VPORT_TO_CPU_OBJ_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xd00 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DEBUG_SCRATCHPAD_1 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xd28 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DEBUG_PRINT_TABLE_1 =
{
	16,
	{
		{ dump_RDD_DEBUG_PRINT_INFO, 0xd50 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT FPM_GLOBAL_CFG_1 =
{
	12,
	{
		{ dump_RDD_FPM_GLOBAL_CFG, 0xd60 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT TASK_IDX_1 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xd6c },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_RING_INTERRUPT_COUNTER_TABLE_1 =
{
	8,
	{
		{ dump_RDD_CPU_RING_INTERRUPT_COUNTER_ENTRY, 0xd70 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_COPY_LOCAL_SCRATCH_1 =
{
	8,
	{
		{ dump_RDD_BYTES_8, 0xd78 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_INTERRUPT_SCRATCH_1 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xd80 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DIRECT_PROCESSING_EPON_CONTROL_SCRATCH_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xd88 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT SRAM_DUMMY_STORE_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xd89 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_FEED_RING_INTERRUPT_COUNTER_MAX_1 =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xd8a },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_FEED_RING_INTERRUPT_THRESHOLD_1 =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xd8c },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_FEED_RING_INTERRUPT_COUNTER_1 =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xd8e },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT MAC_TYPE_1 =
{
	1,
	{
		{ dump_RDD_MAC_TYPE_ENTRY, 0xd90 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DEBUG_PRINT_CORE_LOCK_1 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xd91 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_SHADOW_RD_IDX_1 =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xe00 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_SHADOW_WR_IDX_1 =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xe80 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RING_DESCRIPTORS_TABLE_1 =
{
	16,
	{
		{ dump_RDD_CPU_RING_DESCRIPTOR, 0x3000 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_TX_SCRATCHPAD_2 =
{
	8,
	{
		{ dump_RDD_BYTES_8, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT RUNNER_PROFILING_TRACE_BUFFER_2 =
{
	4,
	{
		{ dump_RDD_TRACE_EVENT, 0x1000 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT TX_FLOW_TABLE_2 =
{
	1,
	{
		{ dump_RDD_TX_FLOW_ENTRY, 0x1200 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT QUEUE_THRESHOLD_VECTOR_2 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1340 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT TASK_IDX_2 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1364 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_INTERRUPT_ID_DDR_ADDR_2 =
{
	8,
	{
		{ dump_RDD_DDR_ADDRESS, 0x1368 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_TX_FPM_POOL_NUMBER_MAPPING_TABLE_2 =
{
	1,
	{
		{ dump_RDD_FPM_POOL_NUMBER, 0x1370 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_TX_RING_TABLE_2 =
{
	16,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0x1380 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_SRAM_PD_FIFO_2 =
{
	16,
	{
		{ dump_RDD_PROCESSING_TX_DESCRIPTOR, 0x1400 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT REGISTERS_BUFFER_2 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1500 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT RUNNER_GLOBAL_REGISTERS_INIT_2 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1580 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT FPM_REPLY_2 =
{
	8,
	{
		{ dump_RDD_BYTES_8, 0x15a0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_INTERRUPT_COALESCING_TABLE_2 =
{
	16,
	{
		{ dump_RDD_CPU_INTERRUPT_COALESCING_ENTRY, 0x15b0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_TX_EGRESS_UPDATE_FIFO_TABLE_2 =
{
	4,
	{
		{ dump_RDD_UPDATE_FIFO_ENTRY, 0x15c0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_2 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x15e0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CORE_ID_TABLE_2 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x15ec },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT SRAM_DUMMY_STORE_2 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x15ed },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DEBUG_PRINT_CORE_LOCK_2 =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x15ee },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_2 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x15f0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_TX_INGRESS_UPDATE_FIFO_TABLE_2 =
{
	4,
	{
		{ dump_RDD_UPDATE_FIFO_ENTRY, 0x1600 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_RING_DESCRIPTOR_TABLE_2 =
{
	16,
	{
		{ dump_RDD_CPU_RING_DESCRIPTOR, 0x1620 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_RING_INDEX_DDR_ADDR_TABLE_2 =
{
	8,
	{
		{ dump_RDD_DDR_ADDRESS, 0x1630 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_TX_EGRESS_PD_FIFO_TABLE_2 =
{
	16,
	{
		{ dump_RDD_PROCESSING_TX_DESCRIPTOR, 0x1640 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RX_INTERRUPT_ID_DDR_ADDR_2 =
{
	8,
	{
		{ dump_RDD_DDR_ADDRESS, 0x1660 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_RING_INTERRUPT_COUNTER_TABLE_2 =
{
	8,
	{
		{ dump_RDD_CPU_RING_INTERRUPT_COUNTER_ENTRY, 0x1668 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DEBUG_PRINT_TABLE_2 =
{
	16,
	{
		{ dump_RDD_DEBUG_PRINT_INFO, 0x1670 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_TX_INGRESS_PD_FIFO_TABLE_2 =
{
	16,
	{
		{ dump_RDD_PROCESSING_TX_DESCRIPTOR, 0x1680 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT DEBUG_SCRATCHPAD_2 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x16a0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT FPM_GLOBAL_CFG_2 =
{
	12,
	{
		{ dump_RDD_FPM_GLOBAL_CFG, 0x16d0 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_INTERRUPT_SCRATCH_2 =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x1700 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_SHADOW_RD_IDX_2 =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0x1780 },
		{ 0, 0 },
	}
};
#endif
#if defined XRDP_CFE
static DUMP_RUNNERREG_STRUCT CPU_RECYCLE_SHADOW_WR_IDX_2 =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0x1800 },
		{ 0, 0 },
	}
};
#endif

TABLE_STRUCT RUNNER_TABLES[NUMBER_OF_TABLES] =
{
#if defined XRDP_CFE
	{ "BASIC_RATE_LIMITER_TABLE_DS", 1, CORE_0_INDEX, &BASIC_RATE_LIMITER_TABLE_DS, 128, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_SCHEDULING_QUEUE_TABLE", 1, CORE_0_INDEX, &DS_TM_SCHEDULING_QUEUE_TABLE, 160, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_BBH_TX_EGRESS_COUNTER_TABLE", 1, CORE_0_INDEX, &DS_TM_BBH_TX_EGRESS_COUNTER_TABLE, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "REGISTERS_BUFFER", 1, CORE_0_INDEX, &REGISTERS_BUFFER, 32, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_TM_ACTION_PTR_TABLE", 1, CORE_0_INDEX, &DS_TM_TM_ACTION_PTR_TABLE, 17, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "BUDGET_ALLOCATION_TIMER_VALUE", 1, CORE_0_INDEX, &BUDGET_ALLOCATION_TIMER_VALUE, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_BB_DESTINATION_TABLE", 1, CORE_0_INDEX, &DS_TM_BB_DESTINATION_TABLE, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "SCHEDULING_FLUSH_GLOBAL_CFG", 1, CORE_0_INDEX, &SCHEDULING_FLUSH_GLOBAL_CFG, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_SCHEDULING_GLOBAL_FLUSH_CFG", 1, CORE_0_INDEX, &DS_TM_SCHEDULING_GLOBAL_FLUSH_CFG, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_TM_FLOW_CNTR_TABLE", 1, CORE_0_INDEX, &DS_TM_TM_FLOW_CNTR_TABLE, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_BBH_TX_QUEUE_ID_TABLE", 1, CORE_0_INDEX, &DS_TM_BBH_TX_QUEUE_ID_TABLE, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "TASK_IDX", 1, CORE_0_INDEX, &TASK_IDX, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "SRAM_DUMMY_STORE", 1, CORE_0_INDEX, &SRAM_DUMMY_STORE, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_FIRST_QUEUE_MAPPING", 1, CORE_0_INDEX, &DS_TM_FIRST_QUEUE_MAPPING, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DEBUG_PRINT_CORE_LOCK", 1, CORE_0_INDEX, &DEBUG_PRINT_CORE_LOCK, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "BASIC_SCHEDULER_TABLE_DS", 1, CORE_0_INDEX, &BASIC_SCHEDULER_TABLE_DS, 32, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_PD_FIFO_TABLE", 1, CORE_0_INDEX, &DS_TM_PD_FIFO_TABLE, 80, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "UPDATE_FIFO_TABLE", 1, CORE_0_INDEX, &UPDATE_FIFO_TABLE, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "RUNNER_GLOBAL_REGISTERS_INIT", 1, CORE_0_INDEX, &RUNNER_GLOBAL_REGISTERS_INIT, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_SCHEDULING_AGGREGATION_CONTEXT_VECTOR", 1, CORE_0_INDEX, &DS_TM_SCHEDULING_AGGREGATION_CONTEXT_VECTOR, 5, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_SCHEDULING_FLUSH_VECTOR", 1, CORE_0_INDEX, &DS_TM_SCHEDULING_FLUSH_VECTOR, 5, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_SCHEDULING_QUEUE_AGING_VECTOR", 1, CORE_0_INDEX, &DS_TM_SCHEDULING_QUEUE_AGING_VECTOR, 5, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DEBUG_SCRATCHPAD", 1, CORE_0_INDEX, &DEBUG_SCRATCHPAD, 10, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "RATE_LIMITER_VALID_TABLE_DS", 1, CORE_0_INDEX, &RATE_LIMITER_VALID_TABLE_DS, 4, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DEBUG_PRINT_TABLE", 1, CORE_0_INDEX, &DEBUG_PRINT_TABLE, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "FPM_GLOBAL_CFG", 1, CORE_0_INDEX, &FPM_GLOBAL_CFG, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_TM_BBH_QUEUE_TABLE", 1, CORE_0_INDEX, &DS_TM_BBH_QUEUE_TABLE, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "COMPLEX_SCHEDULER_TABLE", 1, CORE_0_INDEX, &COMPLEX_SCHEDULER_TABLE, 16, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "RUNNER_PROFILING_TRACE_BUFFER", 1, CORE_0_INDEX, &RUNNER_PROFILING_TRACE_BUFFER, 128, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "RX_FLOW_TABLE", 1, CORE_1_INDEX, &RX_FLOW_TABLE_1, 320, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_CPU_RX_METER_TABLE", 1, CORE_1_INDEX, &DS_CPU_RX_METER_TABLE_1, 16, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RING_INTERRUPT_COUNTER_TABLE", 1, CORE_1_INDEX, &CPU_RING_INTERRUPT_COUNTER_TABLE_1, 18, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_INTERRUPT_COALESCING_TABLE", 1, CORE_1_INDEX, &CPU_RECYCLE_INTERRUPT_COALESCING_TABLE_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DIRECT_PROCESSING_PD_TABLE", 1, CORE_1_INDEX, &DIRECT_PROCESSING_PD_TABLE_1, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DS_CPU_REASON_TO_METER_TABLE", 1, CORE_1_INDEX, &DS_CPU_REASON_TO_METER_TABLE_1, 64, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_SCRATCHPAD", 1, CORE_1_INDEX, &CPU_RX_SCRATCHPAD_1, 64, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_SRAM_PD_FIFO", 1, CORE_1_INDEX, &CPU_RECYCLE_SRAM_PD_FIFO_1, 16, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "US_CPU_RX_METER_TABLE", 1, CORE_1_INDEX, &US_CPU_RX_METER_TABLE_1, 16, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_REASON_AND_VPORT_TO_METER_TABLE", 1, CORE_1_INDEX, &CPU_REASON_AND_VPORT_TO_METER_TABLE_1, 120, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_INTERRUPT_ID_DDR_ADDR", 1, CORE_1_INDEX, &CPU_RECYCLE_INTERRUPT_ID_DDR_ADDR_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "RUNNER_PROFILING_TRACE_BUFFER", 1, CORE_1_INDEX, &RUNNER_PROFILING_TRACE_BUFFER_1, 128, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_COPY_PD_FIFO_TABLE", 1, CORE_1_INDEX, &CPU_RX_COPY_PD_FIFO_TABLE_1, 4, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "US_CPU_REASON_TO_METER_TABLE", 1, CORE_1_INDEX, &US_CPU_REASON_TO_METER_TABLE_1, 64, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "REGISTERS_BUFFER", 1, CORE_1_INDEX, &REGISTERS_BUFFER_1, 32, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_VPORT_TO_METER_TABLE", 1, CORE_1_INDEX, &CPU_VPORT_TO_METER_TABLE_1, 40, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_INTERRUPT_ID_DDR_ADDR", 1, CORE_1_INDEX, &CPU_RX_INTERRUPT_ID_DDR_ADDR_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_PSRAM_GET_NEXT_SCRATCHPAD", 1, CORE_1_INDEX, &CPU_RX_PSRAM_GET_NEXT_SCRATCHPAD_1, 4, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "RUNNER_GLOBAL_REGISTERS_INIT", 1, CORE_1_INDEX, &RUNNER_GLOBAL_REGISTERS_INIT_1, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "SCRATCH", 1, CORE_1_INDEX, &SCRATCH_1, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "UPDATE_FIFO_TABLE", 1, CORE_1_INDEX, &UPDATE_FIFO_TABLE_1, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_COPY_DISPATCHER_CREDIT_TABLE", 1, CORE_1_INDEX, &CPU_RX_COPY_DISPATCHER_CREDIT_TABLE_1, 3, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_INTERRUPT_SCRATCH", 1, CORE_1_INDEX, &CPU_RX_INTERRUPT_SCRATCH_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_RING_DESCRIPTOR_TABLE", 1, CORE_1_INDEX, &CPU_RECYCLE_RING_DESCRIPTOR_TABLE_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_COPY_UPDATE_FIFO_TABLE", 1, CORE_1_INDEX, &CPU_RX_COPY_UPDATE_FIFO_TABLE_1, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_RING_INDEX_DDR_ADDR_TABLE", 1, CORE_1_INDEX, &CPU_RECYCLE_RING_INDEX_DDR_ADDR_TABLE_1, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_INTERRUPT_COALESCING_TABLE", 1, CORE_1_INDEX, &CPU_INTERRUPT_COALESCING_TABLE_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "PD_FIFO_TABLE", 1, CORE_1_INDEX, &PD_FIFO_TABLE_1, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_REASON_TO_TC", 1, CORE_1_INDEX, &CPU_REASON_TO_TC_1, 64, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "TC_TO_CPU_RXQ", 1, CORE_1_INDEX, &TC_TO_CPU_RXQ_1, 64, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "EXC_TC_TO_CPU_RXQ", 1, CORE_1_INDEX, &EXC_TC_TO_CPU_RXQ_1, 64, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_FEED_RING_DESCRIPTOR_TABLE", 1, CORE_1_INDEX, &CPU_FEED_RING_DESCRIPTOR_TABLE_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_LOCAL_SCRATCH", 1, CORE_1_INDEX, &CPU_RX_LOCAL_SCRATCH_1, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "VPORT_TO_CPU_OBJ", 1, CORE_1_INDEX, &VPORT_TO_CPU_OBJ_1, 40, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DEBUG_SCRATCHPAD", 1, CORE_1_INDEX, &DEBUG_SCRATCHPAD_1, 10, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DEBUG_PRINT_TABLE", 1, CORE_1_INDEX, &DEBUG_PRINT_TABLE_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "FPM_GLOBAL_CFG", 1, CORE_1_INDEX, &FPM_GLOBAL_CFG_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "TASK_IDX", 1, CORE_1_INDEX, &TASK_IDX_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_RING_INTERRUPT_COUNTER_TABLE", 1, CORE_1_INDEX, &CPU_RECYCLE_RING_INTERRUPT_COUNTER_TABLE_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_COPY_LOCAL_SCRATCH", 1, CORE_1_INDEX, &CPU_RX_COPY_LOCAL_SCRATCH_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_INTERRUPT_SCRATCH", 1, CORE_1_INDEX, &CPU_RECYCLE_INTERRUPT_SCRATCH_1, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DIRECT_PROCESSING_EPON_CONTROL_SCRATCH", 1, CORE_1_INDEX, &DIRECT_PROCESSING_EPON_CONTROL_SCRATCH_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "SRAM_DUMMY_STORE", 1, CORE_1_INDEX, &SRAM_DUMMY_STORE_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_FEED_RING_INTERRUPT_COUNTER_MAX", 1, CORE_1_INDEX, &CPU_FEED_RING_INTERRUPT_COUNTER_MAX_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_FEED_RING_INTERRUPT_THRESHOLD", 1, CORE_1_INDEX, &CPU_FEED_RING_INTERRUPT_THRESHOLD_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_FEED_RING_INTERRUPT_COUNTER", 1, CORE_1_INDEX, &CPU_FEED_RING_INTERRUPT_COUNTER_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "MAC_TYPE", 1, CORE_1_INDEX, &MAC_TYPE_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DEBUG_PRINT_CORE_LOCK", 1, CORE_1_INDEX, &DEBUG_PRINT_CORE_LOCK_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_SHADOW_RD_IDX", 1, CORE_1_INDEX, &CPU_RECYCLE_SHADOW_RD_IDX_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_SHADOW_WR_IDX", 1, CORE_1_INDEX, &CPU_RECYCLE_SHADOW_WR_IDX_1, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RING_DESCRIPTORS_TABLE", 1, CORE_1_INDEX, &CPU_RING_DESCRIPTORS_TABLE_1, 16, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_TX_SCRATCHPAD", 1, CORE_2_INDEX, &CPU_TX_SCRATCHPAD_2, 512, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "RUNNER_PROFILING_TRACE_BUFFER", 1, CORE_2_INDEX, &RUNNER_PROFILING_TRACE_BUFFER_2, 128, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "TX_FLOW_TABLE", 1, CORE_2_INDEX, &TX_FLOW_TABLE_2, 320, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "QUEUE_THRESHOLD_VECTOR", 1, CORE_2_INDEX, &QUEUE_THRESHOLD_VECTOR_2, 9, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "TASK_IDX", 1, CORE_2_INDEX, &TASK_IDX_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_INTERRUPT_ID_DDR_ADDR", 1, CORE_2_INDEX, &CPU_RECYCLE_INTERRUPT_ID_DDR_ADDR_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_TX_FPM_POOL_NUMBER_MAPPING_TABLE", 1, CORE_2_INDEX, &CPU_TX_FPM_POOL_NUMBER_MAPPING_TABLE_2, 16, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_TX_RING_TABLE", 1, CORE_2_INDEX, &CPU_TX_RING_TABLE_2, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_SRAM_PD_FIFO", 1, CORE_2_INDEX, &CPU_RECYCLE_SRAM_PD_FIFO_2, 16, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "REGISTERS_BUFFER", 1, CORE_2_INDEX, &REGISTERS_BUFFER_2, 32, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "RUNNER_GLOBAL_REGISTERS_INIT", 1, CORE_2_INDEX, &RUNNER_GLOBAL_REGISTERS_INIT_2, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "FPM_REPLY", 1, CORE_2_INDEX, &FPM_REPLY_2, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_INTERRUPT_COALESCING_TABLE", 1, CORE_2_INDEX, &CPU_RECYCLE_INTERRUPT_COALESCING_TABLE_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_TX_EGRESS_UPDATE_FIFO_TABLE", 1, CORE_2_INDEX, &CPU_TX_EGRESS_UPDATE_FIFO_TABLE_2, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE", 1, CORE_2_INDEX, &CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_2, 3, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CORE_ID_TABLE", 1, CORE_2_INDEX, &CORE_ID_TABLE_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "SRAM_DUMMY_STORE", 1, CORE_2_INDEX, &SRAM_DUMMY_STORE_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DEBUG_PRINT_CORE_LOCK", 1, CORE_2_INDEX, &DEBUG_PRINT_CORE_LOCK_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE", 1, CORE_2_INDEX, &CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_2, 3, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_TX_INGRESS_UPDATE_FIFO_TABLE", 1, CORE_2_INDEX, &CPU_TX_INGRESS_UPDATE_FIFO_TABLE_2, 8, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_RING_DESCRIPTOR_TABLE", 1, CORE_2_INDEX, &CPU_RECYCLE_RING_DESCRIPTOR_TABLE_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_RING_INDEX_DDR_ADDR_TABLE", 1, CORE_2_INDEX, &CPU_RECYCLE_RING_INDEX_DDR_ADDR_TABLE_2, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_TX_EGRESS_PD_FIFO_TABLE", 1, CORE_2_INDEX, &CPU_TX_EGRESS_PD_FIFO_TABLE_2, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RX_INTERRUPT_ID_DDR_ADDR", 1, CORE_2_INDEX, &CPU_RX_INTERRUPT_ID_DDR_ADDR_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_RING_INTERRUPT_COUNTER_TABLE", 1, CORE_2_INDEX, &CPU_RECYCLE_RING_INTERRUPT_COUNTER_TABLE_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DEBUG_PRINT_TABLE", 1, CORE_2_INDEX, &DEBUG_PRINT_TABLE_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_TX_INGRESS_PD_FIFO_TABLE", 1, CORE_2_INDEX, &CPU_TX_INGRESS_PD_FIFO_TABLE_2, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "DEBUG_SCRATCHPAD", 1, CORE_2_INDEX, &DEBUG_SCRATCHPAD_2, 10, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "FPM_GLOBAL_CFG", 1, CORE_2_INDEX, &FPM_GLOBAL_CFG_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_INTERRUPT_SCRATCH", 1, CORE_2_INDEX, &CPU_RECYCLE_INTERRUPT_SCRATCH_2, 2, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_SHADOW_RD_IDX", 1, CORE_2_INDEX, &CPU_RECYCLE_SHADOW_RD_IDX_2, 1, 1, 1 },
#endif
#if defined XRDP_CFE
	{ "CPU_RECYCLE_SHADOW_WR_IDX", 1, CORE_2_INDEX, &CPU_RECYCLE_SHADOW_WR_IDX_2, 1, 1, 1 },
#endif
};
