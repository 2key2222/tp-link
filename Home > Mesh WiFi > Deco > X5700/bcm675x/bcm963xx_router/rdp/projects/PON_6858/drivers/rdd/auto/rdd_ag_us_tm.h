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


#ifndef _RDD_AG_US_TM_H_
#define _RDD_AG_US_TM_H_

#include "rdd.h"

int rdd_ag_us_tm_scheduling_queue_descriptor_get(uint32_t _entry, rdd_scheduling_queue_descriptor_t *scheduling_queue_descriptor);
int rdd_ag_us_tm_scheduling_queue_descriptor_set(uint32_t _entry, rdd_scheduling_queue_descriptor_t *scheduling_queue_descriptor);
int rdd_ag_us_tm_scheduling_queue_table_enable_set(uint32_t _entry, bdmf_boolean enable);
int rdd_ag_us_tm_scheduling_queue_table_enable_get(uint32_t _entry, bdmf_boolean *enable);
int rdd_ag_us_tm_scheduling_queue_table_rate_limit_enable_set(uint32_t _entry, bdmf_boolean rate_limit_enable);
int rdd_ag_us_tm_scheduling_queue_table_rate_limit_enable_get(uint32_t _entry, bdmf_boolean *rate_limit_enable);
int rdd_ag_us_tm_scheduling_queue_table_rate_limiter_index_set(uint32_t _entry, uint8_t rate_limiter_index);
int rdd_ag_us_tm_scheduling_queue_table_rate_limiter_index_get(uint32_t _entry, uint8_t *rate_limiter_index);
int rdd_ag_us_tm_scheduling_queue_table_quantum_number_set(uint32_t _entry, uint8_t quantum_number);
int rdd_ag_us_tm_scheduling_queue_table_quantum_number_get(uint32_t _entry, uint8_t *quantum_number);
int rdd_ag_us_tm_wan_0_bb_destination_table_set(uint16_t bits);
int rdd_ag_us_tm_wan_0_bb_destination_table_get(uint16_t *bits);
int rdd_ag_us_tm_scheduling_global_flush_cfg_set(uint8_t bits);
int rdd_ag_us_tm_scheduling_global_flush_cfg_get(uint8_t *bits);
int rdd_ag_us_tm_bbh_tx_us_wan_0_fifo_bytes_threshold_set(uint16_t bits);
int rdd_ag_us_tm_bbh_tx_us_wan_0_fifo_bytes_threshold_get(uint16_t *bits);
int rdd_ag_us_tm_scheduling_flush_vector_set(uint32_t _entry, uint32_t bits);
int rdd_ag_us_tm_scheduling_flush_vector_get(uint32_t _entry, uint32_t *bits);
int rdd_ag_us_tm_flush_aggregation_task_disable_set(uint8_t bits);
int rdd_ag_us_tm_flush_aggregation_task_disable_get(uint8_t *bits);
int rdd_ag_us_tm_wan_0_bbh_tx_fifo_size_set(uint8_t bits);
int rdd_ag_us_tm_wan_0_bbh_tx_fifo_size_get(uint8_t *bits);
int rdd_ag_us_tm_first_queue_mapping_set(uint8_t bits);
int rdd_ag_us_tm_first_queue_mapping_get(uint8_t *bits);
int rdd_ag_us_tm_tx_octets_counters_table_packets_set(uint32_t _entry, uint32_t packets);
int rdd_ag_us_tm_tx_octets_counters_table_packets_get(uint32_t _entry, uint32_t *packets);
int rdd_ag_us_tm_tx_octets_counters_table_bytes_set(uint32_t _entry, uint32_t bytes);
int rdd_ag_us_tm_tx_octets_counters_table_bytes_get(uint32_t _entry, uint32_t *bytes);

int rdd_ag_us_tm_basic_scheduler_table_us_quantum_number_set(uint32_t _entry, uint8_t quantum_number);
int rdd_ag_us_tm_basic_scheduler_table_us_quantum_number_get(uint32_t _entry, uint8_t *quantum_number);

int rdd_ag_us_tm_complex_scheduler_rl_cfg_get(uint32_t _entry, rdd_complex_scheduler_rl_cfg_t *complex_scheduler_rl_cfg);
int rdd_ag_us_tm_complex_scheduler_rl_cfg_set(uint32_t _entry, rdd_complex_scheduler_rl_cfg_t *complex_scheduler_rl_cfg);
int rdd_ag_us_tm_complex_scheduler_table_dwrr_offset_pir_set(uint32_t _entry, uint8_t dwrr_offset_pir);
int rdd_ag_us_tm_complex_scheduler_table_dwrr_offset_pir_get(uint32_t _entry, uint8_t *dwrr_offset_pir);
int rdd_ag_us_tm_complex_scheduler_table_dwrr_offset_sir_set(uint32_t _entry, uint8_t dwrr_offset_sir);
int rdd_ag_us_tm_complex_scheduler_table_dwrr_offset_sir_get(uint32_t _entry, uint8_t *dwrr_offset_sir);
int rdd_ag_us_tm_complex_scheduler_table_slot_budget_bit_vector_0_set(uint32_t _entry, uint32_t slot_budget_bit_vector_0);
int rdd_ag_us_tm_complex_scheduler_table_slot_budget_bit_vector_0_get(uint32_t _entry, uint32_t *slot_budget_bit_vector_0);
int rdd_ag_us_tm_complex_scheduler_table_quantum_number_set(uint32_t _entry, uint8_t quantum_number);
int rdd_ag_us_tm_complex_scheduler_table_quantum_number_get(uint32_t _entry, uint8_t *quantum_number);

#endif /* _RDD_AG_US_TM_H_ */
