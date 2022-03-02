/* lib/version.h.  Generated from version.h.in by configure.
 *
 * Quagga version
 * Copyright (C) 1997, 1999 Kunihiro Ishiguro
 * 
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.  
 */

#ifndef _ZEBRA_VERSION_H
#define _ZEBRA_VERSION_H

#ifdef GIT_VERSION
#include "gitversion.h"
#endif

#ifndef GIT_SUFFIX
#define GIT_SUFFIX ""
#endif
#ifndef GIT_INFO
#define GIT_INFO ""
#endif

#define QUAGGA_PROGNAME   "Quagga"

#define QUAGGA_VERSION     "1.2.4" GIT_SUFFIX

#define ZEBRA_BUG_ADDRESS "https://bugzilla.quagga.net"

#define QUAGGA_URL "http://www.quagga.net"

#define QUAGGA_COPYRIGHT "Copyright 1996-2005 Kunihiro Ishiguro, et al."

#define QUAGGA_CONFIG_ARGS "CFLAGS= -DSUPPORT_DDR_SELF_REFRESH_PWRSAVE -DSUPPORT_ETH_PWRSAVE -DSUPPORT_ENERGY_EFFICIENT_ETHERNET   -DLINUX -DCHIP_47622 -DCONFIG_BCM947622 -Os -march=armv7-a -fomit-frame-pointer -mno-thumb-interwork -mabi=aapcs-linux -marm -fno-common -ffixed-r8 -msoft-float -D__ARM_ARCH_7A__ -Werror=return-type -Werror=uninitialized -Wno-date-time -Wall -Darm -g -fPIC  -I. -I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/userspace/public/include -I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/userspace/public/include/linux -I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/userspace/private/include -I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/userspace/private/include/linux -I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/../toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/include -L/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/../toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/lib -Werror=return-type -Werror=uninitialized -Wno-date-time -DCONFIG_BCM_MAX_GEM_PORTS=1 -DBUILD_BRCM_UNFWLCFG -I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/userspace/private/libs/wlcsm/include -DBRCM_WLAN -DWIRELESS -DDSLCPE -DBCA_CPEROUTER -DBCA_HNDROUTER -DCONFIG_TP_IMAGE -DCONFIG_TP_BCM_QOS_PATCH LDFLAGS= -L/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/targets/TP6755/fs.install/lib LIBS= --host=arm-buildroot-linux-gnueabi --target=arm-buildroot-linux-gnueabi --enable-user=admin --enable-group=root --disable-vtysh --disable-bgpd --disable-doc --disable-ripngd --disable-ospfd --disable-ospfclient --disable-ospf6d --disable-nhrpd --disable-watchquagga --disable-isisd --disable-pimd --disable-bgp-announce --prefix=/"

pid_t pid_output (const char *);

#ifndef HAVE_DAEMON
int daemon(int, int);
#endif

#endif /* _ZEBRA_VERSION_H */
