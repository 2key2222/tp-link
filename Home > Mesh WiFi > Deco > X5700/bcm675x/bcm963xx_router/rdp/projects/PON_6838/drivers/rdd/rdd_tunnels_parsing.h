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

#ifndef _RDD_TUNNELS_PARSING_6838_H
#define _RDD_TUNNELS_PARSING_6838_H

void rdd_oren_tunnels_parsing_enable(bdmf_boolean  xi_tunneling_enable);
BL_LILAC_RDD_ERROR_DTE rdd_dual_stack_lite_tunnel_config(bdmf_ipv6_t *xi_ipv6_src_ip, bdmf_ipv6_t *xi_ipv6_dst_ip);

BL_LILAC_RDD_ERROR_DTE rdd_tunnel_cfg_get(uint32_t tunnel_idx, RDD_TUNNEL_ENTRY_DTS *tunnel_entry);
BL_LILAC_RDD_ERROR_DTE rdd_tunnel_cfg_set(uint32_t tunnel_idx, RDD_TUNNEL_ENTRY_DTS *tunnel_entry);

#endif

