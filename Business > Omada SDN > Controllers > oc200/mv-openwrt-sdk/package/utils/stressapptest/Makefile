#
# Copyright (C) 2011-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=stressapptest
PKG_VERSION:=1.0.8

PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/stressapptest/stressapptest.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=26fcba94bec5be64839e48800e556ef11c94b55f
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/stressapptest
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libstdcpp +libpthread +librt
  TITLE:=Stressapptest
endef

define Package/stressapptest/description
 stress app test.
endef

define Build/Configure
	$(call Build/Configure/Default,--build=aarch64-openwrt-linux-gnu)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CXX="$(TARGET_CXX)" \
		CFLAGS="$(TARGET_CFLAGS)" \
		INSTALL_PREFIX="$(PKG_INSTALL_DIR)"
endef

define Package/stressapptest/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/stressapptest $(1)/usr/bin
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
