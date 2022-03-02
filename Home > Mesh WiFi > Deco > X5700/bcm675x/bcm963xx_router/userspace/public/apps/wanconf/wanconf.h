/***********************************************************************
 *
 * <:copyright-BRCM:2015:DUAL/GPL:standard
 * 
 *    Copyright (c) 2015 Broadcom 
 *    All Rights Reserved
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * :>
 *
 ************************************************************************/

#include <rdpa_types.h>


#define IFNAMESIZ (16)
#define wc_log_err(fmt, arg...) fprintf(stderr, "wanconf %s:%d >> " fmt "\n", __FILE__, __LINE__, ##arg);
#define wc_log(fmt, arg...) printf("wanconf: " fmt "\n", ##arg);
#define insmod(d) insmod_param(d, NULL)

#ifndef CONFIG_BCM963158
#define DETECTION_OK    ( 0)
#define DETECTION_ERROR (-1)

int try_wan_type_detect_and_set(rdpa_wan_type *wan_type);
#endif
