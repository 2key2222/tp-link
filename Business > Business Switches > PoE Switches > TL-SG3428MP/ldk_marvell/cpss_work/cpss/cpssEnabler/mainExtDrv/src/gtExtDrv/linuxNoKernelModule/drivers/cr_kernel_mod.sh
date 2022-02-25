#!/usr/bin/env bash
#
# A script to build mvDrvDrv.ko manually
#
# Edit next line and set $DIST to kernel's source path
if [ -z "${DIST}" ]; then
	DIST=/media/large_workspace2/stack/ldk/CPSS/cpss_work/lsp/uni/4.4/kernel/
fi
#
# These variables are for Marvell's ARM LSP only:
#
echo $ARCH
echo $CROSS_COMPILE
export ARCH
export CROSS_COMPILE

make -C $DIST M=`pwd` modules
