#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/armada-oc300
  NAME:=OC300 (TP-Link Cloudkey)
  CPU_TYPE:=cortex-a53
  CPU_SUBTYPE:=neon-vfpv4
  PACKAGES= kmod-usb-core kmod-usb2 kmod-usb3 kmod-usb-storage kmod-mmc mmc-utils pciutils
endef

define Profile/armada-oc300/Description
 Package set compatible with the Armada 7040 Board.
endef

$(eval $(call Profile,armada-oc300))
