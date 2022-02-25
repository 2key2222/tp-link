#
# Copyright (C) 2008-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

ARCH:=mipsel
BOARD:=mtk
BOARDNAME:=MTK boards
SUBTARGETS:=generic
FEATURES:=squashfs jffs2

LINUX_VERSION:=3.10.14
KERNEL_PATCHVER=3.10.14

include $(INCLUDE_DIR)/target.mk
DEFAULT_PACKAGES += busybox_custom conntrack-tools swconfig

define Target/Description
	Build firmware images for MTK boards.
endef

$(eval $(call BuildTarget))
