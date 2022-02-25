#!/bin/bash

# ./marvell_patch_clean.sh $(TOPDIR) $(call qstrip,$(BR2_TPLINK_PROJECT_NAME)) $(BUILD_DIR)

CPSS_KERNEL_MODULE_DIR=$1/../../ldk_marvell/cpss_work/cpss/cpssEnabler/mainExtDrv/src/gtExtDrv/linuxNoKernelModule/drivers
#clean CPSS kernel module directory
cd $CPSS_KERNEL_MODULE_DIR
make clean
#remove busybox clean flag file
rm -f $1/package/busybox/busybox-custom/built_$2
echo $3
rm -rf $3/busybox-1.25.0
#remove sdk compile source
rm -Rf $1/../../ldk_marvell/cpss_work/$2/*