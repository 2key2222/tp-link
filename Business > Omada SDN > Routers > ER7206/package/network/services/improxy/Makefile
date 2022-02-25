#
# Copyright (c) 2014 The Linux Foundation. All rights reserved.
# Copyright (C) 2010-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=improxy
PKG_VERSION:=1.0
PKG_RELEASE:=1
PKG_REV:=08bf9b8f378409e56df11a4dd796b2d309121ee5

PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)

PKG_FILES_DIR:=$(TPLINK_DIR)/opensource/$(PKG_NAME)/files
PKG_SOURCE_DIR:=$(TPLINK_DIR)/opensource/$(PKG_NAME)/src

include $(INCLUDE_DIR)/package.mk

ifeq ($(CONFIG_PACKAGE_hwnat),y)
TARGET_CFLAGS += -DINC_HWNAT
endif

define Package/improxy
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
#  DEPENDS:=+libpthread
  TITLE:=Multicast Proxy for IGMP/MLD
endef

define Package/improxy/description
	Improxy is an IGMP/MLD Proxy daemon written in c for Linux. It is lightweight and do not depend on any thirdparty library.
endef

define Package/improxy/conffiles
/etc/config/improxy
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/improxy \
		CC="$(TARGET_CC)" \
		CXX="$(TARGET_CXX)" \
		CFLAGS="$(TARGET_CFLAGS)"
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)/improxy
	$(CP) -u $(PKG_SOURCE_DIR)/* $(PKG_BUILD_DIR)/improxy
endef

define Package/improxy/install
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) $(PKG_FILES_DIR)/etc/config/improxy.config $(1)/etc/config/improxy
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_FILES_DIR)/etc/init.d/improxy.init $(1)/etc/init.d/improxy
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/improxy/improxy $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/hotplug.d/iface
	$(INSTALL_BIN) $(PKG_FILES_DIR)/etc/hotplug.d/iface/improxy.hotplug $(1)/etc/hotplug.d/iface/50-improxy
	$(INSTALL_DIR) $(1)/etc/hotplug.d/firewall
	$(INSTALL_BIN) $(PKG_FILES_DIR)/etc/hotplug.d/firewall/improxy.hotplug $(1)/etc/hotplug.d/firewall/50-improxy
endef

define Package/improxyvnet
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
#  DEPENDS:=+libpthread
  TITLE:=Vnet Multicast Proxy for IGMP/MLD
endef

define Package/improxyvnet/description
	Improxy is an IGMP/MLD Proxy daemon written in c for Linux. It is lightweight and do not depend on any thirdparty library.
endef

define Package/improxyvnet/install
	$(INSTALL_DIR) $(1)/etc/hotplug.d/vnet
	$(INSTALL_BIN) $(PKG_FILES_DIR)/etc/hotplug.d/vnet/improxy.hotplug $(1)/etc/hotplug.d/vnet/50-improxy
endef

$(eval $(call BuildPackage,improxy))
$(eval $(call BuildPackage,improxyvnet))
