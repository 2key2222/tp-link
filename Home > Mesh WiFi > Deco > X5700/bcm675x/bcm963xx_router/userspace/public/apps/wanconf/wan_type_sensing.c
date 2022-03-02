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

#if !defined(CONFIG_BCM963158)

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include "rdpa_types.h"
#include "opticaldet.h"
#include "wanconf.h"
#if !defined(PON_WAN_TYPE_AUTO_DETECT)
#include "board.h"
#include "cms_psp.h"
#endif
#include "pmd.h"


#if defined(PON_WAN_TYPE_AUTO_DETECT)
#if defined(PMD_JSON_LIB)
extern int load_pmd_calibration_data(pmd_calibration_parameters *calibration_binary);
#endif

static int detect_wan_type(rdpa_wan_type *wan_type)
{
    int fd, ret;
    pmd_wan_type_auto_detect_settings pmd_wan_auto_detect = {0};

    *wan_type = rdpa_wan_none;
    fd = open("/dev/wantypedetect", O_RDWR);
    if (fd < 0)
    {
        wc_log_err("%s: %s\n", "/dev/wantypedetect", strerror(errno));
        return DETECTION_ERROR;
    }

#if defined(PMD_JSON_LIB)
    ret = load_pmd_calibration_data(&(pmd_wan_auto_detect.calibration_parameters_from_json));
    if (!ret)
    {
        pmd_wan_auto_detect.is_calibration_file_valid = 1;
    }
#endif

    ret = ioctl(fd, OPTICALDET_IOCTL_DETECT, &pmd_wan_auto_detect);
    close(fd);

    if (ret)
    {
        wc_log_err("ioctl failed, Errno[%s] ret=%d\n", strerror(errno), ret);
        return DETECTION_ERROR;
    }

    *wan_type = *(rdpa_wan_type *)&pmd_wan_auto_detect; /* read/write pointer */
    return DETECTION_OK;
}

#elif defined(CONFIG_BCM96838)

static int detect_wan_type(rdpa_wan_type *wan_type, int *epon2g)
{
    int fd, ret, val;

    *wan_type = rdpa_wan_none;

    fd = open("/dev/wantypedetect", O_RDWR);
    if (fd < 0)
    {
        wc_log_err("%s: %s\n", "/dev/wantypedetect", strerror(errno));
        return DETECTION_ERROR;
    }

    /* block till Optical Signal is detected */
    wc_log("block till Optical Signal is detected...\n");
    ret = ioctl(fd, OPTICALDET_IOCTL_SD, &val);
    if (ret)
    {
        close(fd);
        wc_log_err("ioctl failed, Errno[%s] ret=%d\n", strerror(errno), ret);
        return DETECTION_ERROR;
    }

    wc_log("Optical Signal is detected!\n");

    /* got a signal. Define the type of the signal : GPON, EPON, AE */
    ret = ioctl(fd, OPTICALDET_IOCTL_DETECT, &val);
    if (ret)
        wc_log_err("ioctl failed, Errno[%s] ret=%d\n", strerror(errno), ret);

    close(fd);

    *wan_type = val & RDPA_WAN_MASK;
    *epon2g = val & EPON2G;
    
    return DETECTION_OK;
}

static char *wan_type_str(rdpa_wan_type wan_type)
{
    switch (wan_type)
    {
    case rdpa_wan_gpon:
        return RDPA_WAN_TYPE_VALUE_GPON;
    case rdpa_wan_epon:
        return RDPA_WAN_TYPE_VALUE_EPON;
    case rdpa_wan_gbe: /* Detection code will return rdpa_wan_gbe for AE */
        return RDPA_WAN_TYPE_VALUE_GBE;
    case rdpa_wan_xgpon:
        return RDPA_WAN_TYPE_VALUE_XGPON1;
    case rdpa_wan_xepon:
        return RDPA_WAN_TYPE_VALUE_EPON;
    default:
        return NULL;
    }
}

#endif


static rdpa_wan_type detect_and_set_scratchpad(void)
{
    rdpa_wan_type wan_type = rdpa_wan_none;

#if defined(PON_WAN_TYPE_AUTO_DETECT)
    if (detect_wan_type(&wan_type))
    {
        wan_type = rdpa_wan_none;
    }
#elif defined(CONFIG_BCM96838)
    char *wanStr = NULL;
    int epon2g = 0;

    while (!wanStr)
    {
        if (!detect_wan_type(&wan_type, &epon2g))
            wanStr = wan_type_str(wan_type);
        else
            return rdpa_wan_none;

        if (!wanStr)
            wc_log_err("Failed to autodetect, retrying\n");
    }

    /* Set detected WAN in scratchpad */

    wc_log("cmsPsp_set wanStr = %s\n", wanStr);
    if (cmsPsp_set(RDPA_WAN_TYPE_PSP_KEY, wanStr, strlen(wanStr)))
    {
        wc_log_err("cmsPsp_set failed to set new "RDPA_WAN_TYPE_PSP_KEY" = %s\n", wanStr);
        return rdpa_wan_none;
    }

    if (wan_type == rdpa_wan_gbe) /* Detect rdpa_wan_gbe is always AE! */
    {
        char *emac_str = "EMAC5";

        if (cmsPsp_set(RDPA_WAN_OEMAC_PSP_KEY, emac_str, strlen(emac_str)))
            return rdpa_wan_none;
    }
    else if (wan_type == rdpa_wan_epon)
    {
        char wan_rate[PSP_BUFLEN_16] ={};

        sprintf(wan_rate, "%s%s", epon2g ? RDPA_WAN_RATE_2_5G : RDPA_WAN_RATE_1G, RDPA_WAN_RATE_1G);
        if (cmsPsp_set(RDPA_WAN_RATE_PSP_KEY, wan_rate, strlen(wan_rate)))
            return rdpa_wan_none;
    }
#endif

    return wan_type;
}


int try_wan_type_detect_and_set(rdpa_wan_type *wan_type)
{
    int ret;

    *wan_type = rdpa_wan_none;

    ret = system("insmod /lib/modules/"KERNELVER"/extra/wantypedet.ko");
    if (ret)
    {
        wc_log_err("Failed to load wantypedet.ko (rc=%d)\n", ret);
        return DETECTION_ERROR;
    }

    *wan_type = detect_and_set_scratchpad();

    ret = system("rmmod wantypedet.ko");
    if (ret)
        wc_log_err("Failed to unload wantypedet.ko (rc=%d)\n", ret);

    return DETECTION_OK;
}

#endif
