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


#ifndef _RDD_AG_PROCESSING_H_
#define _RDD_AG_PROCESSING_H_

#include "rdd.h"

typedef struct
{
    bdmf_boolean sa_lookup_en;
    bdmf_boolean da_lookup_en;
    uint8_t sa_lookup_miss_action;
    uint8_t da_lookup_miss_action;
    bdmf_boolean ingress_congestion;
    bdmf_boolean discard_prty;
} rdd_vport_cfg_entry_t;

int rdd_ag_processing_vport_cfg_entry_get(uint32_t _entry, rdd_vport_cfg_entry_t *vport_cfg_entry);
int rdd_ag_processing_vport_cfg_entry_set(uint32_t _entry, rdd_vport_cfg_entry_t *vport_cfg_entry);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_us_start_set(uint8_t qm_queue_us_start);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_us_start_get(uint8_t *qm_queue_us_start);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_us_end_set(uint8_t qm_queue_us_end);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_us_end_get(uint8_t *qm_queue_us_end);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_ds_start_set(uint8_t qm_queue_ds_start);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_ds_start_get(uint8_t *qm_queue_ds_start);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_ds_end_set(uint8_t qm_queue_ds_end);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_ds_end_get(uint8_t *qm_queue_ds_end);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_epon_start_set(uint8_t qm_queue_epon_start);
int rdd_ag_processing_queue_dynamic_mng_table_qm_queue_epon_start_get(uint8_t *qm_queue_epon_start);
int rdd_ag_processing_vport_cfg_table_loopback_en_set(uint32_t _entry, bdmf_boolean loopback_en);
int rdd_ag_processing_vport_cfg_table_loopback_en_get(uint32_t _entry, bdmf_boolean *loopback_en);
int rdd_ag_processing_vport_cfg_table_mirroring_en_set(uint32_t _entry, bdmf_boolean mirroring_en);
int rdd_ag_processing_vport_cfg_table_mirroring_en_get(uint32_t _entry, bdmf_boolean *mirroring_en);
int rdd_ag_processing_vport_cfg_table_egress_isolation_en_set(uint32_t _entry, bdmf_boolean egress_isolation_en);
int rdd_ag_processing_vport_cfg_table_egress_isolation_en_get(uint32_t _entry, bdmf_boolean *egress_isolation_en);
int rdd_ag_processing_vport_cfg_table_ingress_isolation_en_set(uint32_t _entry, bdmf_boolean ingress_isolation_en);
int rdd_ag_processing_vport_cfg_table_ingress_isolation_en_get(uint32_t _entry, bdmf_boolean *ingress_isolation_en);
int rdd_ag_processing_vport_cfg_table_bridge_and_vlan_ingress_lookup_method_set(uint32_t _entry, bdmf_boolean bridge_and_vlan_ingress_lookup_method);
int rdd_ag_processing_vport_cfg_table_bridge_and_vlan_ingress_lookup_method_get(uint32_t _entry, bdmf_boolean *bridge_and_vlan_ingress_lookup_method);
int rdd_ag_processing_vport_cfg_table_bridge_and_vlan_egress_lookup_method_set(uint32_t _entry, bdmf_boolean bridge_and_vlan_egress_lookup_method);
int rdd_ag_processing_vport_cfg_table_bridge_and_vlan_egress_lookup_method_get(uint32_t _entry, bdmf_boolean *bridge_and_vlan_egress_lookup_method);
int rdd_ag_processing_vport_cfg_table_protocol_filters_dis_set(uint32_t _entry, uint8_t protocol_filters_dis);
int rdd_ag_processing_vport_cfg_table_protocol_filters_dis_get(uint32_t _entry, uint8_t *protocol_filters_dis);
int rdd_ag_processing_vport_cfg_table_ingress_congestion_set(uint32_t _entry, bdmf_boolean ingress_congestion);
int rdd_ag_processing_vport_cfg_table_ingress_congestion_get(uint32_t _entry, bdmf_boolean *ingress_congestion);
int rdd_ag_processing_vport_cfg_table_ingress_filter_profile_set(uint32_t _entry, uint8_t ingress_filter_profile);
int rdd_ag_processing_vport_cfg_table_ingress_filter_profile_get(uint32_t _entry, uint8_t *ingress_filter_profile);
int rdd_ag_processing_vport_cfg_table_ls_fc_cfg_set(uint32_t _entry, bdmf_boolean ls_fc_cfg);
int rdd_ag_processing_vport_cfg_table_ls_fc_cfg_get(uint32_t _entry, bdmf_boolean *ls_fc_cfg);
int rdd_ag_processing_vport_cfg_table_egress_isolation_map_set(uint32_t _entry, uint32_t egress_isolation_map);
int rdd_ag_processing_vport_cfg_table_egress_isolation_map_get(uint32_t _entry, uint32_t *egress_isolation_map);

#endif /* _RDD_AG_PROCESSING_H_ */
