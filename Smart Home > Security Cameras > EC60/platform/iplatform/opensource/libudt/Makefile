#
# Copyright (c) 2016 Shenzhen TP-LINK Technologies Co.Ltd.
#
# Author  : Guo Hongwei<guohongwei@tp-link.net>
# Version : 1.0
# Date    : 8 Mar, 2016
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libudt
PKG_VERSION:=4.0.0

include $(INCLUDE_DIR)/uclibc++.mk
include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  MAINTAINER:=TP-LINK
  DEPENDS:=$(CXX_DEPENDS)
  TITLE:=UDP-based Data Transfer (UDT) Library
endef

define Package/$(PKG_NAME)/Description
	UDP-based Data Transfer (UDT) Library
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -u ./src/* $(PKG_BUILD_DIR)/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lib/*.so $(1)/usr/lib
endef

define Build/InstallDev
	mkdir -p $(STAGING_DIR)/usr/include
	$(CP) $(PKG_BUILD_DIR)/include/* $(STAGING_DIR)/usr/include/
	mkdir -p $(STAGING_DIR)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/lib/*.so $(STAGING_DIR)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
