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


#ifndef _RDD_AG_REAS_H_
#define _RDD_AG_REAS_H_

#include "rdd.h"

int rdd_ag_reas_g9991_reassembly_error_cntrs_table_packets_set(uint32_t _entry, uint32_t packets);
int rdd_ag_reas_g9991_reassembly_error_cntrs_table_packets_get(uint32_t _entry, uint32_t *packets);
int rdd_ag_reas_g9991_reassembly_error_cntrs_table_bytes_set(uint32_t _entry, uint32_t bytes);
int rdd_ag_reas_g9991_reassembly_error_cntrs_table_bytes_get(uint32_t _entry, uint32_t *bytes);

#endif /* _RDD_AG_REAS_H_ */
