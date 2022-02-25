# Copyright (c) 2013 The Linux Foundation. All rights reserved.
#
include $(TOPDIR)/rules.mk

ARCH:=arm
BOARD:=ipq806x
BOARDNAME:=Qualcomm Atheros IPQ806X
FEATURES:=squashfs gpio
CPU_TYPE:=cortex-a7
MAINTAINER:=John Crispin <blogic@openwrt.org>

KERNELNAME:=zImage Image dtbs

LINUX_VERSION:=3.14.77
KERNEL_PATCHVER:=3.14.77

include $(INCLUDE_DIR)/target.mk
DEFAULT_PACKAGES += 

define Target/Description
	Build firmware images for IPQ806x based boards.
endef

$(eval $(call BuildTarget))
