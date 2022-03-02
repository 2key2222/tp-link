/*
   Copyright (c) 2016 Broadcom
   All Rights Reserved

    <:label-BRCM:2016:DUAL/GPL:standard
    
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

#include "rdd.h"
#include "rdd_tunnels_parsing.h"

extern void f_global_ingress_vector_config ( uint32_t, rdpa_traffic_dir, bdmf_boolean );

void rdd_oren_tunnels_parsing_enable( bdmf_boolean  xi_tunneling_enable )
{
    f_global_ingress_vector_config ( GLOBAL_INGRESS_CONFIG_TUNNELING_ENABLE, rdpa_dir_ds, xi_tunneling_enable);
}

BL_LILAC_RDD_ERROR_DTE rdd_dual_stack_lite_tunnel_config ( bdmf_ipv6_t  *xi_ipv6_src_ip,
                                                           bdmf_ipv6_t  *xi_ipv6_dst_ip )
{
    RDD_DUAL_STACK_LITE_TABLE_DTS  *dual_stack_lite_table_ptr;
    RDD_DUAL_STACK_LITE_ENTRY_DTS  *dual_stack_lite_entry_ptr;
    uint32_t                       i,j;

    dual_stack_lite_table_ptr = ( RDD_DUAL_STACK_LITE_TABLE_DTS * )(DEVICE_ADDRESS( RUNNER_COMMON_1_OFFSET ) + DUAL_STACK_LITE_TABLE_ADDRESS - sizeof ( RUNNER_COMMON ) );

    for ( j = 0; j < RDD_DUAL_STACK_LITE_TABLE_SIZE; j++ )
    {
        dual_stack_lite_entry_ptr = &(dual_stack_lite_table_ptr->entry[j]); 

        for ( i = 0; i < 16; i++ )
        {
            RDD_DUAL_STACK_LITE_ENTRY_SRC_IP_WRITE ( xi_ipv6_src_ip->data[ i ], dual_stack_lite_entry_ptr, i );
            RDD_DUAL_STACK_LITE_ENTRY_DST_IP_WRITE ( xi_ipv6_dst_ip->data[ i ], dual_stack_lite_entry_ptr, i );
        }
    }
    
    return ( BL_LILAC_RDD_OK );
}

BL_LILAC_RDD_ERROR_DTE rdd_tunnel_cfg_get(uint32_t tunnel_idx, RDD_TUNNEL_ENTRY_DTS *tunnel_entry)
{
    RDD_TUNNEL_TABLE_DTS *tunnel_table;

    if (RDD_TUNNEL_TABLE_SIZE <=  tunnel_idx)
        return BL_LILAC_RDD_ERROR_ADD_CONTEXT_ENTRY;

    tunnel_table = RDD_TUNNEL_TABLE_PTR();
    tunnel_entry = &(tunnel_table->entry[tunnel_idx]);
    return ( BL_LILAC_RDD_OK );
}

BL_LILAC_RDD_ERROR_DTE rdd_tunnel_cfg_set(uint32_t tunnel_idx, RDD_TUNNEL_ENTRY_DTS *tunnel_entry)
{
    RDD_TUNNEL_TABLE_DTS *tunnel_table;
    RDD_TUNNEL_ENTRY_DTS *tunnel_entry_ptr;
    RDD_TUNNEL_DYNAMIC_FIELDS_TABLE_DTS *tunnel_dynamic_fields_table;
    RDD_TUNNEL_DYNAMIC_FIELDS_ENTRY_DTS *tunnel_dynamic_fields_entry;
    uint32_t i;
    uint16_t l3_chsum, l3_total_len;
    
    
    tunnel_dynamic_fields_table = RDD_TUNNEL_DYNAMIC_FIELDS_TABLE_PTR();
    tunnel_table = RDD_TUNNEL_TABLE_PTR();
  
    /* update tunnel for each flow cache task */
    for ( i = 0; i < RDD_TUNNEL_TABLE_SIZE; i++ )
    {
        tunnel_entry_ptr = &(tunnel_table->entry[i]);

        RDD_TUNNEL_ENTRY_LOCAL_IP_WRITE(tunnel_entry->local_ip, tunnel_entry_ptr);
        RDD_TUNNEL_ENTRY_TUNNEL_TYPE_WRITE(tunnel_entry->tunnel_type, tunnel_entry_ptr);
        RDD_TUNNEL_ENTRY_TUNNEL_HEADER_LENGTH_WRITE(tunnel_entry->tunnel_header_length, tunnel_entry_ptr);
        RDD_TUNNEL_ENTRY_IP_FAMILY_WRITE(tunnel_entry->ip_family, tunnel_entry_ptr);
        RDD_TUNNEL_ENTRY_LAYER3_OFFSET_WRITE(tunnel_entry->layer3_offset, tunnel_entry_ptr);
        memcpy( &(tunnel_table->entry[i].tunnel_header), tunnel_entry->tunnel_header, tunnel_entry->tunnel_header_length);
    }

    /* extract fields from tunnel header */
    memcpy( &l3_total_len, &(tunnel_entry->tunnel_header[tunnel_entry->layer3_offset + 2]), 2);
    memcpy( &l3_chsum, &(tunnel_entry->tunnel_header[tunnel_entry->layer3_offset + 10]), 2);
#ifdef FIRMWARE_INIT     
    l3_total_len = ( l3_total_len << 8 ) | ( l3_total_len >> 8 );
    l3_chsum = ( l3_chsum << 8 ) | ( l3_chsum >> 8 );
#endif
    tunnel_dynamic_fields_entry = &tunnel_dynamic_fields_table->entry[0];

    RDD_TUNNEL_DYNAMIC_FIELDS_ENTRY_L3_TOTAL_LEN_WRITE(l3_total_len, tunnel_dynamic_fields_entry);
    RDD_TUNNEL_DYNAMIC_FIELDS_ENTRY_L3_CHSUM_WRITE(l3_chsum, tunnel_dynamic_fields_entry);

    return ( BL_LILAC_RDD_OK );
}
