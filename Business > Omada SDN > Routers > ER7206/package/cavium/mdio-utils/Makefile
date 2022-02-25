#
# Copyright (C) 2007-2014 OpenWrt.org
# Copyright (C) 2010 Vertical Communications
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/version.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=mdio-utils
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/mdio-utils
  SECTION:=base
  CATEGORY:=Cavium Octeon SDK
  DEPENDS:=
  TITLE:=Cavium Octeon SDK debug utilities.
  URL:=http://www.cavium.com/
  VERSION:=$(PKG_RELEASE)-$(REVISION)
endef

define Build/Compile/Default

endef
Build/Compile = $(Build/Compile/Default)


define Package/mdio-utils/description
  Cavium Octeon SDK debug utilities
endef

define Build/Prepare
	echo "Build/Prepare"
	mkdir -p $(PKG_BUILD_DIR)
endef

define Package/mdio-utils/install
	echo "Package/mdio-utils/install"
	mkdir -p $(1)/usr/sbin/
	$(CP) ./files/oct-* $(1)/usr/sbin/
	chmod 1777 $(1)/usr/sbin/oct-*
endef

$(eval $(call BuildPackage,mdio-utils))
