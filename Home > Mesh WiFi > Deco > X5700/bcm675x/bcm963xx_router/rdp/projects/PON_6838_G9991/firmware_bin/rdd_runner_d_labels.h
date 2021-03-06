#ifndef RUNNER_D_CODE_ADDRESSES
#define RUNNER_D_CODE_ADDRESSES

#define runner_d_start_task_initialization_task		(0x14)
#define runner_d_initialization_task		(0x14)
#define runner_d_start_task_timer_scheduler_set		(0x21F4)
#define runner_d_timer_scheduler_set		(0x21F4)
#define runner_d_start_task_cpu_tx_wakeup_request		(0x1EDC)
#define runner_d_cpu_tx_wakeup_request		(0x1EDC)
#define runner_d_start_task_lan_cpu_wakeup_request		(0x488)
#define runner_d_lan_cpu_wakeup_request		(0x488)
#define runner_d_start_task_lan_broadcom_switch_wakeup_request		(0x4C0)
#define runner_d_lan_broadcom_switch_wakeup_request		(0x4C0)
#define runner_d_start_task_lan_normal_wakeup_request		(0x1D8)
#define runner_d_lan_normal_wakeup_request		(0x1D8)
#define runner_d_start_task_upstream_flooding_wakeup_request		(0x23E0)
#define runner_d_upstream_flooding_wakeup_request		(0x23E0)
#define runner_d_start_task_debug_routine		(0xF0)
#define runner_d_debug_routine		(0xF0)
#define runner_d_start_task_lan_direct_to_cpu_wakeup_request		(0x45C)
#define runner_d_lan_direct_to_cpu_wakeup_request		(0x45C)
#define runner_d_start_task_cpu_rx_int_coalesce_timer_1st_wakeup_request		(0x2900)
#define runner_d_cpu_rx_int_coalesce_timer_1st_wakeup_request		(0x2900)
#define runner_d_ingress_classification_key_src_ip		(0x1A0C)
#define runner_d_ingress_classification_key_dst_ip		(0x1A58)
#define runner_d_ingress_classification_key_ipv6_flow_label		(0x1AA4)
#define runner_d_ingress_classification_key_generic_rule_1		(0x1ACC)
#define runner_d_ingress_classification_key_generic_rule_2		(0x1AD4)
#define runner_d_ingress_classification_key_outer_tpid		(0x1B40)
#define runner_d_ingress_classification_key_inner_tpid		(0x1B4C)
#define runner_d_ingress_classification_key_src_port		(0x1B6C)
#define runner_d_ingress_classification_key_dst_port		(0x1B8C)
#define runner_d_ingress_classification_key_outer_vlan		(0x1BAC)
#define runner_d_ingress_classification_key_inner_vlan		(0x1BC4)
#define runner_d_ingress_classification_key_dst_mac		(0x1BE0)
#define runner_d_ingress_classification_key_src_mac		(0x1BE8)
#define runner_d_ingress_classification_key_ether_type		(0x1C10)
#define runner_d_ingress_classification_key_ip_protocol		(0x1C24)
#define runner_d_ingress_classification_key_dscp		(0x1C48)
#define runner_d_ingress_classification_key_ssid		(0x1C64)
#define runner_d_ingress_classification_key_ingress_port		(0x1C7C)
#define runner_d_ingress_classification_key_outer_pbits		(0x1C8C)
#define runner_d_ingress_classification_key_inner_pbits		(0x1CA4)
#define runner_d_ingress_classification_key_number_of_vlans		(0x1CC0)
#define runner_d_ingress_classification_key_layer3_protocol		(0x1CD0)
#define runner_d_global_register_update_r0		(0x21B4)
#define runner_d_global_register_update_r1		(0x21BC)
#define runner_d_global_register_update_r2		(0x21C4)
#define runner_d_global_register_update_r3		(0x21CC)
#define runner_d_global_register_update_r4		(0x21D4)
#define runner_d_global_register_update_r5		(0x21DC)
#define runner_d_global_register_update_r6		(0x21E4)
#define runner_d_global_register_update_r7		(0x21EC)
#define runner_d_upstream_ingress_rate_limiter_budget_allocate		(0x226C)
#define runner_d_upstream_quasi_budget_allocate		(0x22EC)

#endif
