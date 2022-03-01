#
# Copyright (c) 2016 Shenzhen TP-LINK Technologies Co.Ltd.
#
# Author  : Guo Hongwei<guohongwei@tp-link.net>
# Version : 1.0
# Date    : 8 Mar, 2016
#

include $(TOPDIR)/rules.mk

PKG_NAME:=logModel
PKG_VERSION:=1.1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  MAINTAINER:=TP-LINK
  DEPENDS:= +libpthread +libuci +libubox
  TITLE:=logModel for cameos
endef

define Package/$(PKG_NAME)/Description
	This is the log module for cameos
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -u ./src/* $(PKG_BUILD_DIR)/
	mkdir -p $(PKG_BUILD_DIR)/output/daemon
	mkdir -p $(PKG_BUILD_DIR)/output/demo
	mkdir -p $(PKG_BUILD_DIR)/output/libapi
	mkdir -p $(PKG_BUILD_DIR)/output/tools
	mkdir -p $(PKG_BUILD_DIR)/output/shellApi
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DATA) ./filesystem/etc/syslog.conf $(1)/etc

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./filesystem/etc/init.d/logModelInit $(1)/etc/init.d

	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/output/daemon/syslogd $(1)/usr/bin

	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/output/tools/logCtrl $(1)/usr/bin

	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/output/shellApi/logApi $(1)/usr/sbin
	$(INSTALL_BIN) ./filesystem/usr/sbin/logModel.sh $(1)/usr/sbin
	$(INSTALL_BIN) ./filesystem/usr/sbin/logLevel.sh $(1)/usr/sbin

	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/output/libapi/liblogApi.* $(1)/usr/lib
endef

define Build/InstallDev
	mkdir -p $(STAGING_DIR)/usr/include
	$(CP) $(PKG_BUILD_DIR)/inc/logApi.h $(STAGING_DIR)/usr/include/
	mkdir -p $(STAGING_DIR)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/output/libapi/liblogApi.* $(STAGING_DIR)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
