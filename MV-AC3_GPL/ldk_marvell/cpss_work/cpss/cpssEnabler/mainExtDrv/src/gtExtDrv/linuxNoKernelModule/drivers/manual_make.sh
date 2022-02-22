#!/usr/bin/env bash
#
# A script to build mvDrvDrv.ko manually
#
# Edit next line and set $DIST to kernel's source path
DIST=/media/large_workspace2/stack/ldk/CPSS/cpss_work/lsp/uni/4.4/kernel/

#
# These variables are for Marvell's ARM LSP only:
#
export ARCH=arm
export CROSS_COMPILE=/media/large_workspace2/stack/tplink/buildroot/ext-tools/le/armv7-marvell-linux-gnueabi-softfp-4.6.4_64K_i686_20160226/bin/arm-marvell-linux-gnueabi-



make -C $DIST M=`pwd` modules
