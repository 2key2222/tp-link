/*
   Copyright (c) 2013 Broadcom Corporation
   All Rights Reserved

    <:label-BRCM:2013:DUAL/GPL:standard
    
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

#ifdef CONFIG_DHD_RUNNER
#ifdef USE_BDMF_SHELL

#include "bdmf_shell.h"
#include "rdd.h"
#include "dhd_defs.h"
#include "rdpa_dhd_helper_basic.h"
#include "rdd_dhd_helper.h"

#if defined(BCM_DSL_RDP)
extern void *g_dhd_tx_post_mgmt_fr_base_ptr[RDPA_MAX_RADIOS];
extern uint32_t g_dhd_tx_post_mgmt_arr_entry_count[RDPA_MAX_RADIOS];
#endif
extern int flow_ring_format[];


#define MAKE_BDMF_SHELL_CMD_NOPARM(dir, cmd, help, cb) \
    bdmfmon_cmd_add(dir, cmd, cb, help, BDMF_ACCESS_ADMIN, NULL, NULL)

#define MAKE_BDMF_SHELL_CMD(dir, cmd, help, cb, parms...)   \
{                                                           \
    static bdmfmon_cmd_parm_t cmd_parms[]={                 \
        parms,                                              \
        BDMFMON_PARM_LIST_TERMINATOR                        \
    };                                                      \
    bdmfmon_cmd_add(dir, cmd, cb, help, BDMF_ACCESS_ADMIN, NULL, cmd_parms); \
}

static int _rdd_print_dhd_tx_post_desc(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
#if !defined(BCM_DSL_RDP)
    RDD_DHD_RADIO_INSTANCE_COMMON_B_DATA_DTS *radio_instance_table_ptr;
    RDD_DHD_RADIO_INSTANCE_COMMON_B_ENTRY_DTS *radio_instance_entry_ptr;
    uint32_t base_ptr;
#endif
    uint32_t radio_idx, ring_id, desc_num;
    rdpa_dhd_flring_cache_t *entry_ptr;

    radio_idx = (uint32_t)parm[0].value.unumber;
    ring_id = (uint32_t)parm[1].value.unumber;
    desc_num = (uint32_t)parm[2].value.unumber;

    bdmf_session_print(session, "TX POST descriptor\n");

#if defined(BCM_DSL_RDP)
    entry_ptr = (rdpa_dhd_flring_cache_t *)g_dhd_tx_post_mgmt_fr_base_ptr[radio_idx];
#else
    radio_instance_table_ptr = RDD_DHD_RADIO_INSTANCE_COMMON_B_DATA_PTR();
    radio_instance_entry_ptr = &radio_instance_table_ptr->entry[radio_idx];

    RDD_DHD_RADIO_INSTANCE_COMMON_B_ENTRY_TX_POST_MGMT_FR_BASE_PTR_READ(base_ptr, radio_instance_entry_ptr);

    entry_ptr = (rdpa_dhd_flring_cache_t *)(0xa0000000 | base_ptr) + ring_id;
#endif

    switch (flow_ring_format[radio_idx])
    {
        case FR_FORMAT_WI_WI64: /* Legacy Work Item */
        {
            RDD_DHD_TX_POST_DESCRIPTOR_DTS *desc_ptr;
            RDD_DHD_TX_POST_DESCRIPTOR_DTS desc;

#if defined(BCM_DSL_RDP)
            desc_ptr = (RDD_DHD_TX_POST_DESCRIPTOR_DTS *)PHYS_TO_VIRT((uintptr_t)(((uint64_t)__swap4bytes(entry_ptr->base_addr_high) << 32) + __swap4bytes(entry_ptr->base_addr_low))) + desc_num;
            bdmf_session_print(session, "flow ring %d cache address = 0x%8.8lx, descriptor %d address = 0x%8.8lx\n", ring_id, (unsigned long)entry_ptr, desc_num, (unsigned long)desc_ptr);
#else
            desc_ptr = (RDD_DHD_TX_POST_DESCRIPTOR_DTS *)(0xa0000000 | entry_ptr->base_addr_low) + desc_num;
#endif    

            memcpy(&desc, desc_ptr, sizeof(RDD_DHD_TX_POST_DESCRIPTOR_DTS));

            bdmf_session_print(session, "msg_type                 = 0x%4.4x\n", desc.msg_type);
            bdmf_session_print(session, "if_id                    = 0x%4.4x\n", desc.if_id);
            bdmf_session_print(session, "common_hdr_flags         = 0x%4.4x\n", desc.common_hdr_flags);
            bdmf_session_print(session, "epoch                    = 0x%4.4x\n", desc.epoch);
            bdmf_session_print(session, "request_id               = 0x%8.8x\n", desc.request_id);
            bdmf_session_print(session, "tx_eth_hdr_0             = 0x%8.8x\n", desc.tx_eth_hdr_0);
            bdmf_session_print(session, "tx_eth_hdr_1             = 0x%8.8x\n", desc.tx_eth_hdr_1);
            bdmf_session_print(session, "tx_eth_hdr_2             = 0x%8.8x\n", desc.tx_eth_hdr_2);
            bdmf_session_print(session, "tx_eth_hdr_3             = 0x%4.4x\n", desc.tx_eth_hdr_3);
            bdmf_session_print(session, "flags                    = 0x%4.4x\n", desc.flags);
            bdmf_session_print(session, "seg_cnt                  = 0x%4.4x\n", desc.seg_cnt);
            bdmf_session_print(session, "metadata_buf_addr_low    = 0x%8.8x\n", desc.metadata_buf_addr_low);
            bdmf_session_print(session, "metadata_buf_addr_hi     = 0x%8.8x\n", desc.metadata_buf_addr_hi);
            bdmf_session_print(session, "data_buf_addr_low        = 0x%8.8x\n", cpu_to_le32(desc.data_buf_addr_low));
            bdmf_session_print(session, "data_buf_addr_hi         = 0x%8.8x\n", desc.data_buf_addr_hi);
            bdmf_session_print(session, "meta_buf_len             = 0x%4.4x\n", desc.meta_buf_len);
            bdmf_session_print(session, "data_len                 = 0x%4.4x\n", cpu_to_le16(desc.data_len));
            
            break;
        }
        
        case FR_FORMAT_WI_CWI32: /* Compact Work Item with 32b haddr */
        {               
            RDD_DHD_TX_POST_DESCRIPTOR_CWI32_DTS *desc_ptr;
            RDD_DHD_TX_POST_DESCRIPTOR_CWI32_DTS desc;

#if defined(BCM_DSL_RDP)
            desc_ptr = (RDD_DHD_TX_POST_DESCRIPTOR_CWI32_DTS *)PHYS_TO_VIRT((uintptr_t)(((uint64_t)__swap4bytes(entry_ptr->base_addr_high) << 32) + __swap4bytes(entry_ptr->base_addr_low))) + desc_num;
            bdmf_session_print(session, "flow ring %d cache address = 0x%8.8lx, descriptor %d address = 0x%8.8lx\n", ring_id, (unsigned long)entry_ptr, desc_num, (unsigned long)desc_ptr);
#else
            desc_ptr = (RDD_DHD_TX_POST_DESCRIPTOR_CWI32_DTS *)(0xa0000000 | entry_ptr->base_addr_low) + desc_num;
#endif    

            memcpy(&desc, desc_ptr, sizeof(RDD_DHD_TX_POST_DESCRIPTOR_CWI32_DTS));

            bdmf_session_print(session, "if_id                    = 0x%4.4x\n", desc.if_id);
            bdmf_session_print(session, "request_id               = 0x%8.8x\n", desc.request_id);
            bdmf_session_print(session, "tx_eth_hdr_0             = 0x%8.8x\n", desc.tx_eth_hdr_0);
            bdmf_session_print(session, "tx_eth_hdr_1             = 0x%8.8x\n", desc.tx_eth_hdr_1);
            bdmf_session_print(session, "tx_eth_hdr_2             = 0x%8.8x\n", desc.tx_eth_hdr_2);
            bdmf_session_print(session, "tx_eth_hdr_3             = 0x%4.4x\n", desc.tx_eth_hdr_3);
            bdmf_session_print(session, "flags                    = 0x%4.4x\n", desc.flags);
            bdmf_session_print(session, "data_buf_addr            = 0x%8.8x\n", __swap4bytes(desc.data_buf_addr_low));
            bdmf_session_print(session, "data_len                 = 0x%4.4x\n", __swap2bytes(desc.data_len));
            bdmf_session_print(session, "flowid_override          = 0x%4.4x\n", __swap2bytes(desc.flowid_override));
            bdmf_session_print(session, "info                     = 0x%4.4x\n", __swap2bytes(desc.info));
            break;
        }

        default:
        {
            bdmf_print("ERROR: flow ring format: %d not supported\n", flow_ring_format[radio_idx]);
            
            BUG();                
        }
    } /* switch item_type */

    return 0;
}

static int _rdd_print_dhd_tx_complete_desc(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    RDD_DHD_RADIO_INSTANCE_COMMON_B_DATA_DTS *radio_instance_table_ptr;
    RDD_DHD_RADIO_INSTANCE_COMMON_B_ENTRY_DTS *radio_instance_entry_ptr;
    uint32_t desc_num, radio_idx, base_ptr;

    radio_idx = (uint32_t)parm[0].value.unumber;
    desc_num = (uint32_t)parm[1].value.unumber;

    radio_instance_table_ptr = RDD_DHD_RADIO_INSTANCE_COMMON_B_DATA_PTR();
    radio_instance_entry_ptr = &radio_instance_table_ptr->entry[radio_idx];

    RDD_DHD_RADIO_INSTANCE_COMMON_B_ENTRY_TX_COMPLETE_FR_BASE_PTR_READ(base_ptr, radio_instance_entry_ptr);

    bdmf_session_print(session, "TX COMPLETE descriptor\n");
    
    switch (flow_ring_format[radio_idx])
    {
        case FR_FORMAT_WI_WI64: /* Legacy Work Item */
        {
            RDD_DHD_TX_COMPLETE_DESCRIPTOR_DTS *desc_ptr;
            RDD_DHD_TX_COMPLETE_DESCRIPTOR_DTS desc;

#if !defined(FIRMWARE_INIT)
#if defined(BCM_DSL_RDP)
            desc_ptr = (RDD_DHD_TX_COMPLETE_DESCRIPTOR_DTS *)PHYS_TO_CACHED((uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_TX_COMPLETE_DESCRIPTOR_DTS)));
#else
            desc_ptr = (RDD_DHD_TX_COMPLETE_DESCRIPTOR_DTS *)(0xa0000000 | (uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_TX_COMPLETE_DESCRIPTOR_DTS)));
#endif
#else  /* FIRMWARE_INIT */
            desc_ptr = (RDD_DHD_TX_COMPLETE_DESCRIPTOR_DTS *)(uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_TX_COMPLETE_DESCRIPTOR_DTS));
#endif

#if (defined DSL_63138 || defined DSL_63148)
            bdmf_session_print(session, "descriptor %d address = 0x%8.8lx\n", desc_num, (unsigned long)desc_ptr);
#endif

            memcpy(&desc, desc_ptr, sizeof(RDD_DHD_TX_COMPLETE_DESCRIPTOR_DTS));

            bdmf_session_print(session, "msg_type                 = 0x%4.4x\n", desc.msg_type);
            bdmf_session_print(session, "if_id                    = 0x%4.4x\n", desc.if_id);
            bdmf_session_print(session, "common_hdr_flags         = 0x%4.4x\n", desc.common_hdr_flags);
            bdmf_session_print(session, "epoch                    = 0x%4.4x\n", desc.epoch);
            bdmf_session_print(session, "request_id               = 0x%8.8x\n", desc.request_id);
            bdmf_session_print(session, "status                   = 0x%4.4x\n", desc.status);
            bdmf_session_print(session, "flow_ring_id             = 0x%4.4x\n", desc.flow_ring_id);
            bdmf_session_print(session, "dma_done_mark          = 0x%8.8x\n", desc.dma_done_mark);

            break;
        }
        
        case FR_FORMAT_WI_CWI32: /* Compact Work Item with 32b haddr */
        {               
            RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32_DTS *desc_ptr;
            RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32_DTS desc;

#if !defined(FIRMWARE_INIT)
#if defined(BCM_DSL_RDP)
            desc_ptr = (RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32_DTS *)PHYS_TO_CACHED((uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32_DTS)));
#else
            desc_ptr = (RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32_DTS *)(0xa0000000 | (uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32_DTS)));
#endif
#else  /* FIRMWARE_INIT */
            desc_ptr = (RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32_DTS *)(uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32_DTS));
#endif

#if (defined DSL_63138 || defined DSL_63148)
            bdmf_session_print(session, "descriptor %d address = 0x%8.8lx\n", desc_num, (unsigned long)desc_ptr);
#endif

            memcpy(&desc, desc_ptr, sizeof(RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32_DTS));

            bdmf_session_print(session, "request_id               = 0x%8.8x\n", desc.request_id);
            
            break;
        }

        default:
        {
            bdmf_print("ERROR: flow ring format: %d not supported\n", flow_ring_format[radio_idx]);
            
            BUG();                
        }
    } /* switch item_type */

    return 0;
}

static int _rdd_print_dhd_rx_complete_desc(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    RDD_DHD_RADIO_INSTANCE_COMMON_B_DATA_DTS *radio_instance_table_ptr;
    RDD_DHD_RADIO_INSTANCE_COMMON_B_ENTRY_DTS *radio_instance_entry_ptr;
    uint32_t desc_num, radio_idx, base_ptr;

    radio_idx = (uint32_t)parm[0].value.unumber;
    desc_num = (uint32_t)parm[1].value.unumber;

    radio_instance_table_ptr = RDD_DHD_RADIO_INSTANCE_COMMON_B_DATA_PTR();
    radio_instance_entry_ptr = &radio_instance_table_ptr->entry[radio_idx];

    RDD_DHD_RADIO_INSTANCE_COMMON_B_ENTRY_RX_COMPLETE_FR_BASE_PTR_READ(base_ptr, radio_instance_entry_ptr);

    switch (flow_ring_format[radio_idx])
    {
        case FR_FORMAT_WI_WI64: /* Legacy Work Item */
        {
            RDD_DHD_RX_COMPLETE_DESCRIPTOR_DTS *desc_ptr;
            RDD_DHD_RX_COMPLETE_DESCRIPTOR_DTS desc;

#if !defined(FIRMWARE_INIT)
#if defined(BCM_DSL_RDP)
            desc_ptr = (RDD_DHD_RX_COMPLETE_DESCRIPTOR_DTS *)PHYS_TO_CACHED((uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_COMPLETE_DESCRIPTOR_DTS)));
#else
            desc_ptr = (RDD_DHD_RX_COMPLETE_DESCRIPTOR_DTS *)(0xa0000000 | (uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_COMPLETE_DESCRIPTOR_DTS)));
#endif
#else  /* FIRMWARE_INIT */
            desc_ptr = (RDD_DHD_RX_COMPLETE_DESCRIPTOR_DTS *)(uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_COMPLETE_DESCRIPTOR_DTS));
#endif

#if (defined DSL_63138 || defined DSL_63148)
            bdmf_session_print(session, "descriptor %d address = 0x%8.8lx\n", desc_num, (unsigned long)desc_ptr);
#endif

            memcpy(&desc, desc_ptr, sizeof(RDD_DHD_RX_COMPLETE_DESCRIPTOR_DTS));

            bdmf_session_print(session, "RX COMPLETE descriptor\n");
            bdmf_session_print(session, "msg_type                 = 0x%4.4x\n", desc.msg_type);
            bdmf_session_print(session, "if_id                    = 0x%4.4x\n", desc.if_id);
            bdmf_session_print(session, "common_hdr_flags         = 0x%4.4x\n", desc.common_hdr_flags);
            bdmf_session_print(session, "epoch                    = 0x%4.4x\n", desc.epoch);
            bdmf_session_print(session, "request_id               = 0x%8.8x\n", desc.request_id);
            bdmf_session_print(session, "compl_msg_hdr_status     = 0x%4.4x\n", desc.compl_msg_hdr_status);
            bdmf_session_print(session, "flow_ring_id             = 0x%4.4x\n", desc.flow_ring_id);
            bdmf_session_print(session, "data_len                 = 0x%4.4x\n", cpu_to_le16(desc.data_len));
            bdmf_session_print(session, "data_offset              = 0x%4.4x\n", cpu_to_le16(desc.data_offset));
            bdmf_session_print(session, "flags                    = 0x%4.4x\n", desc.flags);
            bdmf_session_print(session, "rx_status_0              = 0x%8.8x\n", desc.rx_status_0);
            bdmf_session_print(session, "rx_status_1                = 0x%8.8x\n", desc.rx_status_1);
            bdmf_session_print(session, "dma_done_mark          = 0x%8.8x\n", desc.dma_done_mark);

            break;
        }
        
        case FR_FORMAT_WI_CWI32: /* Compact Work Item with 32b haddr */
        {               
            RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32_DTS *desc_ptr;
            RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32_DTS desc;

#if !defined(FIRMWARE_INIT)
#if defined(BCM_DSL_RDP)
            desc_ptr = (RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32_DTS *)PHYS_TO_CACHED((uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32_DTS)));
#else
            desc_ptr = (RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32_DTS *)(0xa0000000 | (uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32_DTS)));
#endif
#else  /* FIRMWARE_INIT */
            desc_ptr = (RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32_DTS *)(uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32_DTS));
#endif

#if (defined DSL_63138 || defined DSL_63148)
            bdmf_session_print(session, "descriptor %d address = 0x%8.8lx\n", desc_num, (unsigned long)desc_ptr);
#endif

            memcpy(&desc, desc_ptr, sizeof(RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32_DTS));

            bdmf_session_print(session, "RX COMPLETE descriptor\n");
            bdmf_session_print(session, "if_id                    = 0x%4.4x\n", desc.if_id);
            bdmf_session_print(session, "request_id               = 0x%8.8x\n", desc.request_id);
            bdmf_session_print(session, "data_len                 = 0x%4.4x\n", cpu_to_le16(desc.data_len));
            bdmf_session_print(session, "data_offset              = 0x%4.4x\n", cpu_to_le16(desc.data_offset));
            bdmf_session_print(session, "flags                    = 0x%4.4x\n", desc.flags);

            break;
        }

        default:
        {
            bdmf_print("ERROR: flow ring format: %d not supported\n", flow_ring_format[radio_idx]);
            
            BUG();                
        }
    } /* switch item_type */

    return 0;
}

static int _rdd_print_dhd_rx_post_desc(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    RDD_DHD_RADIO_INSTANCE_COMMON_B_DATA_DTS *radio_instance_table_ptr;
    RDD_DHD_RADIO_INSTANCE_COMMON_B_ENTRY_DTS *radio_instance_entry_ptr;
    uint32_t desc_num, radio_idx, base_ptr;

    radio_idx = (uint32_t)parm[0].value.unumber;
    desc_num = (uint32_t)parm[1].value.unumber;

    radio_instance_table_ptr = RDD_DHD_RADIO_INSTANCE_COMMON_B_DATA_PTR();
    radio_instance_entry_ptr = &radio_instance_table_ptr->entry[radio_idx];

    RDD_DHD_RADIO_INSTANCE_COMMON_B_ENTRY_RX_POST_FR_BASE_PTR_READ(base_ptr, radio_instance_entry_ptr);

    switch (flow_ring_format[radio_idx])
    {
        case FR_FORMAT_WI_WI64: /* Legacy Work Item */
        {
            RDD_DHD_RX_POST_DESCRIPTOR_DTS *desc_ptr;
            RDD_DHD_RX_POST_DESCRIPTOR_DTS desc;

#if !defined(FIRMWARE_INIT)
#if defined(BCM_DSL_RDP)
            desc_ptr = (RDD_DHD_RX_POST_DESCRIPTOR_DTS *)PHYS_TO_CACHED((uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_POST_DESCRIPTOR_DTS)));
#else
            desc_ptr = (RDD_DHD_RX_POST_DESCRIPTOR_DTS*)(0xa0000000 | (uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_POST_DESCRIPTOR_DTS)));
#endif
#else  /* FIRMWARE_INIT */
            desc_ptr = (RDD_DHD_RX_POST_DESCRIPTOR_DTS *)(uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_POST_DESCRIPTOR_DTS));
#endif

#if (defined DSL_63138 || defined DSL_63148)
    bdmf_session_print(session, "descriptor %d address = 0x%8.8lx\n", desc_num, (unsigned long)desc_ptr);
#endif

            memcpy(&desc, desc_ptr, sizeof(RDD_DHD_RX_POST_DESCRIPTOR_DTS));

            bdmf_session_print(session, "RX POST descriptor\n");
            bdmf_session_print(session, "msg_type                 = 0x%4.4x\n", desc.msg_type);
            bdmf_session_print(session, "if_id                    = 0x%4.4x\n", desc.if_id);
            bdmf_session_print(session, "common_hdr_flags         = 0x%4.4x\n", desc.common_hdr_flags);
            bdmf_session_print(session, "epoch                    = 0x%4.4x\n", desc.epoch);
            bdmf_session_print(session, "request_id               = 0x%8.8x\n", desc.request_id);
            bdmf_session_print(session, "meta_buf_len             = 0x%4.4x\n", desc.meta_buf_len);
            bdmf_session_print(session, "data_len                 = 0x%4.4x\n", cpu_to_le16(desc.data_len));
            bdmf_session_print(session, "metadata_buf_addr_low    = 0x%8.8x\n", desc.metadata_buf_addr_low);
            bdmf_session_print(session, "metadata_buf_addr_hi     = 0x%8.8x\n", desc.metadata_buf_addr_hi);
            bdmf_session_print(session, "data_buf_addr_low        = 0x%8.8x\n", cpu_to_le32(desc.data_buf_addr_low));
            bdmf_session_print(session, "data_buf_addr_hi           = 0x%8.8x\n", desc.data_buf_addr_hi);

            break;
        }

        case FR_FORMAT_WI_CWI32: /* Compact Work Item with 32b haddr */
        {               
            RDD_DHD_RX_POST_DESCRIPTOR_CWI32_DTS *desc_ptr;
            RDD_DHD_RX_POST_DESCRIPTOR_CWI32_DTS desc;
            
#if !defined(FIRMWARE_INIT)
#if defined(BCM_DSL_RDP)
            desc_ptr = (RDD_DHD_RX_POST_DESCRIPTOR_CWI32_DTS *)PHYS_TO_CACHED((uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_POST_DESCRIPTOR_CWI32_DTS)));
#else
            desc_ptr = (RDD_DHD_RX_POST_DESCRIPTOR_CWI32_DTS*)(0xa0000000 | (uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_POST_DESCRIPTOR_CWI32_DTS)));
#endif
#else  /* FIRMWARE_INIT */
            desc_ptr = (RDD_DHD_RX_POST_DESCRIPTOR_CWI32_DTS *)(uint32_t)(base_ptr + desc_num * sizeof(RDD_DHD_RX_POST_DESCRIPTOR_CWI32_DTS));
#endif

#if (defined DSL_63138 || defined DSL_63148)
    bdmf_session_print(session, "descriptor %d address = 0x%8.8lx\n", desc_num, (unsigned long)desc_ptr);
#endif

            memcpy(&desc, desc_ptr, sizeof(RDD_DHD_RX_POST_DESCRIPTOR_CWI32_DTS));

            bdmf_session_print(session, "RX POST descriptor\n");
            bdmf_session_print(session, "request_id               = 0x%8.8x\n", desc.request_id);
            bdmf_session_print(session, "data_buf_addr_low        = 0x%8.8x\n", cpu_to_le32(desc.data_buf_addr_low));

            break;
        }

        default:
        {
            bdmf_print("ERROR: flow ring format: %d not supported\n", flow_ring_format[radio_idx]);
            
            BUG();                
        }
    } /* switch item_type */

    return 0;
}

static int _rdd_print_dhd_drop_counters(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    uint32_t i, j;
    uint16_t counter, group;

    bdmf_session_print(session, "SSID drop counters\n");

#if defined(BCM_DSL_RDP)
    for (j = 0; j < 3; j++)
#else
    for (j = 0; j < 2; j++)
#endif
    {
        bdmf_session_print(session, "Radio %d\n", j);
        group = DHD_SSID_DROP_PACKET_GROUP + j;
        for (i = 0; i < 16; i++)
        {
#if defined(BCM_DSL_RDP)
            rdd_2_bytes_counter_get(group, i, &counter);
#else
            rdd_2_bytes_counter_get(group, i, 0, &counter);
#endif
            bdmf_session_print(session, "\tSSID%d = %d\n", i, counter);
        }
    }
#if defined(BCM_DSL_RDP)
    rdd_2_bytes_counter_get(UPSTREAM_VARIOUS_PACKETS_GROUP, DHD_MALLOC_FAILED_OFFSET, &counter);
#else
    rdd_2_bytes_counter_get(UPSTREAM_VARIOUS_PACKETS_GROUP, DHD_MALLOC_FAILED_OFFSET, 0, &counter);
#endif
    bdmf_session_print(session, "Malloc failed = %d\n", counter);

#if defined(BCM_DSL_RDP)
    rdd_2_bytes_counter_get(UPSTREAM_VARIOUS_PACKETS_GROUP, DHD_IH_CONGESTION_OFFSET, &counter);
#else
    rdd_2_bytes_counter_get(UPSTREAM_VARIOUS_PACKETS_GROUP, DHD_IH_CONGESTION_OFFSET, 0, &counter);
#endif
    bdmf_session_print(session, "IH congestion = %d\n", counter);

    return 0;
}

static int _rdd_print_dhd_flow_rings_cache(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    int i;
    RDD_DHD_FLOW_RING_CACHE_LKP_ENTRY_DTS *cache_lkp_ptr, cache_lkp;
    RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY_DTS *cache_ctx_ptr, ctx_entry;
    RDD_DHD_BACKUP_INFO_CACHE_ENTRY_DTS *backup_info_ptr, backup_info;

    bdmf_session_print(session, "FlowRings Cache\n");

    cache_lkp_ptr = (RDD_DHD_FLOW_RING_CACHE_LKP_ENTRY_DTS *)RDD_US_DHD_FLOW_RING_CACHE_LKP_TABLE_PTR();
    cache_ctx_ptr = (RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY_DTS *)RDD_DHD_FLOW_RING_CACHE_CTX_TABLE_PTR();
    backup_info_ptr = (RDD_DHD_BACKUP_INFO_CACHE_ENTRY_DTS *)RDD_DHD_BACKUP_INFO_CACHE_TABLE_PTR();

    bdmf_session_print(session, "Ring ID  Radio  Inv  Base        PhySize  TotalSize   Flags       SSID  RD_Idx  WR_Idx  FirstIdx  LastIdx  BackupEntries\n");
    bdmf_session_print(session, "========================================================================================================================\n");

    for (i = 0; i < 16; i++, cache_lkp_ptr++, cache_ctx_ptr++, backup_info_ptr++)
    {
        /* Read Flowring cache entry */
        RDD_DHD_FLOW_RING_CACHE_LKP_ENTRY_FLOW_RING_ID_READ(cache_lkp.flow_ring_id, cache_lkp_ptr);
        RDD_DHD_FLOW_RING_CACHE_LKP_ENTRY_RADIO_IDX_READ(cache_lkp.radio_idx, cache_lkp_ptr);
        RDD_DHD_FLOW_RING_CACHE_LKP_ENTRY_INVALID_READ(cache_lkp.invalid, cache_lkp_ptr);
        bdmf_session_print(session, "%7d  %5d  %3d  ", cache_lkp.flow_ring_id, cache_lkp.radio_idx, cache_lkp.invalid);

        /* Read FlowRing context entry */
        RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY_FLOW_RING_BASE_LOW_READ(ctx_entry.flow_ring_base_low, cache_ctx_ptr);
        RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY_SIZE_READ(ctx_entry.size, cache_ctx_ptr);
        RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY_FLAGS_READ(ctx_entry.flags, cache_ctx_ptr);
        RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY_SSID_READ(ctx_entry.ssid, cache_ctx_ptr);
        RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY_RD_IDX_READ(ctx_entry.rd_idx, cache_ctx_ptr);
        RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY_WR_IDX_READ(ctx_entry.wr_idx, cache_ctx_ptr);

        RDD_DHD_BACKUP_INFO_CACHE_ENTRY_BACKUP_FIRST_INDEX_READ(backup_info.backup_first_index, backup_info_ptr);
        RDD_DHD_BACKUP_INFO_CACHE_ENTRY_BACKUP_LAST_INDEX_READ(backup_info.backup_last_index, backup_info_ptr);
        RDD_DHD_BACKUP_INFO_CACHE_ENTRY_BACKUP_NUM_ENTRIES_READ(backup_info.backup_num_entries, backup_info_ptr);
        RDD_DHD_BACKUP_INFO_CACHE_ENTRY_PHY_SIZE_READ(backup_info.phy_size, backup_info_ptr);

        bdmf_session_print(session, "0x%-9x  %-7d  %-10d   0x%-10x  %-4d  %-6d  %-6d  %-8d  %-7d  %-13d\n",
            ctx_entry.flow_ring_base_low, backup_info.phy_size, ctx_entry.size, ctx_entry.flags, ctx_entry.ssid, ctx_entry.rd_idx, ctx_entry.wr_idx,
            backup_info.backup_first_index, backup_info.backup_last_index, backup_info.backup_num_entries);
    }

    return 0;
}

static int _rdd_print_dhd_flow_rings_ddr(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    int i;
    uint32_t radio_idx;
    rdpa_dhd_flring_cache_t *entry_ptr;

    radio_idx = (uint32_t)parm[0].value.unumber;

    
    entry_ptr = (rdpa_dhd_flring_cache_t *)g_dhd_tx_post_mgmt_fr_base_ptr[radio_idx];
    if (!entry_ptr)
    {
        bdmf_session_print(session, "ERROR: Radio ring pointer is uninitialized.\n");
        return -1;
    }

    bdmf_session_print(session, "Total of %d rings allocated.  Displaying enabled rings only.\n", g_dhd_tx_post_mgmt_arr_entry_count[radio_idx]);
    bdmf_session_print(session, "Ring ID  Radio  Base        PhySize  TotalSize   Flags       SSID  FirstIdx  LastIdx  BackupEntries\n");
    bdmf_session_print(session, "===================================================================================================\n");

    for (i = 2; i < g_dhd_tx_post_mgmt_arr_entry_count[radio_idx]; i++)
    {
        // Short circuit if we come across an uninitialized ring descriptor
        if (!entry_ptr[i].base_addr_low) 
        {
            bdmf_session_print(session, "Invalid base address found, exitting.");
            break;
        }
        
        if (!(__swap2bytes(entry_ptr[i].flags) & FLOW_RING_FLAG_DISABLED))
        {
            bdmf_session_print(session, "%7d  %5d  0x%08x   %-7d  %-8d   0x%-10x  %-4d  %-8d  %-7d  %-13d\n", 
                i, 
                radio_idx,
                __swap4bytes(entry_ptr[i].base_addr_low),
                __swap2bytes(entry_ptr[i].phy_ring_size),
                __swap2bytes(entry_ptr[i].items),
                __swap2bytes(entry_ptr[i].flags) & ~FLOW_RING_FLAG_SSID_MASK,
                (__swap2bytes(entry_ptr[i].flags) & FLOW_RING_FLAG_SSID_MASK) >> FLOW_RING_FLAG_SSID_SHIFT,
                __swap2bytes(entry_ptr[i].backup_first_index),
                __swap2bytes(entry_ptr[i].backup_last_index),
                __swap2bytes(entry_ptr[i].backup_num_entries));
        }
    }

    return 0;
}

static int _rdd_set_dhd_coalescing_params(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    uint32_t radio_idx, coal_thresh, coal_timeout;

    RDD_DHD_RADIO_INSTANCE_COMMON_A_DATA_DTS *radio_instance_table_ptr;
    RDD_DHD_RADIO_INSTANCE_COMMON_A_ENTRY_DTS *radio_instance_entry_ptr;

    radio_idx = (uint32_t)parm[0].value.unumber;
    coal_thresh = (uint32_t)parm[1].value.unumber;
    coal_timeout = (uint32_t)parm[2].value.unumber;

    radio_instance_table_ptr = RDD_DHD_RADIO_INSTANCE_COMMON_A_DATA_PTR();
    radio_instance_entry_ptr = &radio_instance_table_ptr->entry[radio_idx];

    RDD_DHD_RADIO_INSTANCE_COMMON_A_ENTRY_COALESCING_MAX_COUNT_WRITE(coal_thresh, radio_instance_entry_ptr);
    RDD_DHD_RADIO_INSTANCE_COMMON_A_ENTRY_COALESCING_TIMEOUT_WRITE(coal_timeout, radio_instance_entry_ptr);

    return 0;
}

static int _rdd_print_dhd_coalescing_params(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    uint32_t coal_thresh, coal_timeout;
    int idx;

    RDD_DHD_RADIO_INSTANCE_COMMON_A_DATA_DTS *radio_instance_table_ptr;
    RDD_DHD_RADIO_INSTANCE_COMMON_A_ENTRY_DTS *radio_instance_entry_ptr;
    radio_instance_table_ptr = RDD_DHD_RADIO_INSTANCE_COMMON_A_DATA_PTR();

    bdmf_session_print(session, "\nDHD Interrupt Coalescing Parameters:\n");

    for (idx = 0; idx < 3; idx++)
    {
        radio_instance_entry_ptr = &radio_instance_table_ptr->entry[idx];
        RDD_DHD_RADIO_INSTANCE_COMMON_A_ENTRY_COALESCING_MAX_COUNT_READ(coal_thresh, radio_instance_entry_ptr);
        RDD_DHD_RADIO_INSTANCE_COMMON_A_ENTRY_COALESCING_TIMEOUT_READ(coal_timeout, radio_instance_entry_ptr);
        bdmf_session_print(session, "  Radio %d  -  Threshold:  %3d  -  Timeout(ms):  %3d\n", idx, coal_thresh, coal_timeout);
    }

    bdmf_session_print(session, "\n");

    return 0;
}

static int _rdd_set_dhd_tx_th(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    uint32_t low_th, high_th, excl_th;

    low_th = (uint32_t)parm[0].value.unumber;
    high_th = (uint32_t)parm[1].value.unumber;
    excl_th = (uint32_t)parm[2].value.unumber;

    return rdd_dhd_helper_tx_thresholds_set(low_th, high_th, excl_th);
}

static int _rdd_get_dhd_tx_th(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    uint32_t low_th, high_th, excl_th, used;

    rdd_dhd_helper_tx_thresholds_get(&low_th, &high_th, &excl_th);
    rdd_dhd_helper_tx_used_get(&used);

    bdmf_session_print(session,
                       "DHD TX BUFFER THRESHOLDS:\n    low  threshold = %d\n    high threshold = %d\n    "
                       "excl threshold = %d\n    used = %d\n",
                       low_th, high_th, excl_th, used);

    return 0;
}

static int _rdd_set_dhd_cpu_tx_th(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    uint32_t th;

    th = (uint32_t)parm[0].value.unumber;

    return rdd_dhd_helper_cpu_tx_threshold_set(th);
}

static int _rdd_get_dhd_cpu_tx_th(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    uint32_t th, used;

    rdd_dhd_helper_cpu_tx_threshold_get(&th);
    rdd_dhd_helper_cpu_tx_used_get(&used);

    bdmf_session_print(session,
                       "DHD CPU TX threshold = %d, used = %d\n",
                       th, used);

    return 0;
}

void rdd_dhd_helper_shell_cmds_init(bdmfmon_handle_t rdd_dir)
{
    MAKE_BDMF_SHELL_CMD(rdd_dir, "pdtxp", "print DHD TX POST descriptor", _rdd_print_dhd_tx_post_desc,
        BDMFMON_MAKE_PARM("radio_idx", "radio index", BDMFMON_PARM_NUMBER, 0),
        BDMFMON_MAKE_PARM("ring_id", "ring id", BDMFMON_PARM_NUMBER, 0),
        BDMFMON_MAKE_PARM("desc_id", "desc id", BDMFMON_PARM_NUMBER, 0));
    MAKE_BDMF_SHELL_CMD(rdd_dir, "pdrxp",   "print DHD RX POST descriptor", _rdd_print_dhd_rx_post_desc,
        BDMFMON_MAKE_PARM("radio_idx", "radio index", BDMFMON_PARM_NUMBER, 0),
        BDMFMON_MAKE_PARM("desc_id", "desc id", BDMFMON_PARM_NUMBER, 0));
    MAKE_BDMF_SHELL_CMD(rdd_dir, "pdtxc",   "print DHD TX COMPLETE descriptor", _rdd_print_dhd_tx_complete_desc,
        BDMFMON_MAKE_PARM("radio_idx", "radio index", BDMFMON_PARM_NUMBER, 0),
        BDMFMON_MAKE_PARM("desc_id", "desc id", BDMFMON_PARM_NUMBER, 0));
    MAKE_BDMF_SHELL_CMD(rdd_dir, "pdrxc",   "print DHD RX COMPLETE descriptor", _rdd_print_dhd_rx_complete_desc,
        BDMFMON_MAKE_PARM("radio_idx", "radio index", BDMFMON_PARM_NUMBER, 0),
        BDMFMON_MAKE_PARM("desc_id", "desc id", BDMFMON_PARM_NUMBER, 0));
    MAKE_BDMF_SHELL_CMD_NOPARM(rdd_dir, "pddc",  "print DHD drop counters", _rdd_print_dhd_drop_counters);
    MAKE_BDMF_SHELL_CMD_NOPARM(rdd_dir, "pdfrc",  "print DHD Flow Rings cache", _rdd_print_dhd_flow_rings_cache);
    MAKE_BDMF_SHELL_CMD(rdd_dir, "pdfrd",  "print DHD Flow Rings from ddr", _rdd_print_dhd_flow_rings_ddr,
        BDMFMON_MAKE_PARM("radio_idx", "radio index", BDMFMON_PARM_NUMBER, 0));
    MAKE_BDMF_SHELL_CMD(rdd_dir, "sdcp",   "set DHD coalescing parameters", _rdd_set_dhd_coalescing_params,
        BDMFMON_MAKE_PARM("radio_idx", "radio index", BDMFMON_PARM_NUMBER, 0),
        BDMFMON_MAKE_PARM("coal_thresh", "number of doorbells to coalesce", BDMFMON_PARM_NUMBER, 0),
        BDMFMON_MAKE_PARM("coal_timeout", "coalescing timeout (msec)", BDMFMON_PARM_NUMBER, 0));
    MAKE_BDMF_SHELL_CMD_NOPARM(rdd_dir, "pdcp",  "print DHD coalescing parameters", _rdd_print_dhd_coalescing_params);
    MAKE_BDMF_SHELL_CMD(rdd_dir, "sdfl",   "set DHD TX thresholds", _rdd_set_dhd_tx_th,
        BDMFMON_MAKE_PARM("low_prio_limit", "low_prio_limit", BDMFMON_PARM_NUMBER, 0),
        BDMFMON_MAKE_PARM("high_prio_limit", "high_prio_limit", BDMFMON_PARM_NUMBER, 0),
        BDMFMON_MAKE_PARM("excl_prio_limit", "excl_prio_limit", BDMFMON_PARM_NUMBER, 0));
    MAKE_BDMF_SHELL_CMD_NOPARM(rdd_dir, "gdfl",  "get DHD TX thresholds/used", _rdd_get_dhd_tx_th);
    MAKE_BDMF_SHELL_CMD(rdd_dir, "sdctl",   "set DHD CPU TX threshold", _rdd_set_dhd_cpu_tx_th,
        BDMFMON_MAKE_PARM("threshold", "threshold", BDMFMON_PARM_NUMBER, 0));
    MAKE_BDMF_SHELL_CMD_NOPARM(rdd_dir, "gdctl",  "get DHD CPU TX threshold/used", _rdd_get_dhd_cpu_tx_th);
}

#endif /* USE_BDMF_SHELL */
#endif /* CONFIG_DHD_RUNNER */
