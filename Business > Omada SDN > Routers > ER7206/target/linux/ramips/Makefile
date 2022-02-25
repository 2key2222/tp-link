#
# Copyright (C) 2008-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

ARCH:=mipsel
BOARD:=ramips
BOARDNAME:=MTK/Ralink APSoC (MIPS)
SUBTARGETS:=mt7621
FEATURES:=squashfs jffs2

LINUX_VERSION:=3.10.108
KERNEL_PATCHVER:=3.10.108


include $(INCLUDE_DIR)/target.mk
DEFAULT_PACKAGES += busybox_custom conntrack-tools swconfig

define Target/Description
	Build firmware images for MTK/Ralink APSoC based boards.
endef

$(eval $(call BuildTarget))
