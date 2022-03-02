/****************************************************************************
 *
 * <:copyright-BRCM:2015:DUAL/GPL:voice
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
 ****************************************************************************/
#ifndef _BCM_DSPHAL_H
#define _BCM_DSPHAL_H

#include <linux/ioctl.h>

/****************************************************************************
* Typedefs and Constants
****************************************************************************/
#define DSPHAL_DEV_NAME                "dsphal"
#define DEV_MAJOR                      350
#define DEV_MINOR                      0

#define DSPHAL_CMD_INIT                _IOW (DEV_MAJOR,  0, unsigned int)
#define DSPHAL_CMD_ENABLE              _IOWR(DEV_MAJOR,  1, struct dsphal_cmdenable)
#define DSPHAL_CMD_SETLOGLEVEL         _IOW (DEV_MAJOR,  2, unsigned int)
#define DSPHAL_CMD_GETNUMEPT           _IO  (DEV_MAJOR,  3)
#define DSPHAL_CMD_GETCHANCFG          _IOWR(DEV_MAJOR,  4, struct dsphal_chancfg)
#define DSPHAL_CMD_SETCLEARCHAN        _IOW (DEV_MAJOR,  5, struct dsphal_cmdenable)
#define DSPHAL_CMD_SETDSPRATE          _IOW (DEV_MAJOR,  6, unsigned int)
#define DSPHAL_CMD_WAITTICK            _IO  (DEV_MAJOR,  7)
#define DSPHAL_CMD_SETTICKENABLE       _IOW (DEV_MAJOR,  8, unsigned int)
#define DSPHAL_CMD_SETDECTSTACKSTATUS  _IOW (DEV_MAJOR,  9, unsigned int)
#define DSPHAL_CMD_SETVOICEIDLE        _IOW (DEV_MAJOR, 10, unsigned int)

/* Channel type */
enum dh_type
{
   DSPHAL_TYPE_NONE,
   DSPHAL_TYPE_FXS,
   DSPHAL_TYPE_FXO,
   DSPHAL_TYPE_DECT,
   DSPHAL_TYPE_ALSA
};

/* Channel sampling rate */
enum dh_sample_rate
{
   DSPHAL_RATE_8KHZ,
   DSPHAL_RATE_16KHZ,
};

/* Channel audio interface type */
enum dh_intf
{
   DSPHAL_INTF_PCM,
   DSPHAL_INTF_APM,
   DSPHAL_INTF_DECT,
   DSPHAL_INTF_ALSA,

   DSPHAL_INTF_MAX
};

struct dsphal_cmdenable
{
   unsigned int    id;
   unsigned int    enable;
} __attribute__((aligned(4),packed));

struct dsphal_chancfg
{
   unsigned int         id;
   int                  type;
   int                  interface;
   int                  rate;
   unsigned int         enabled;
} __attribute__((aligned(4),packed));

#endif /* _BCM_DSPHAL_H */
