#
# Copyright (C) 2008-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=swconfig
PKG_RELEASE:=10

PKG_MAINTAINER:=Felix Fietkau <nbd@openwrt.org>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/swconfig
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  DEPENDS:=
  TITLE:=Switch configuration utility
endef

ifeq ($(CONFIG_IPF_PLATFORM_QCA), y)
TARGET_CPPFLAGS := \
	-D_GNU_SOURCE \
	-I$(STAGING_DIR)/usr/include/libnl-tiny \
	-I$(PKG_BUILD_DIR) \
	$(TARGET_CPPFLAGS) \
	-I$(LINUX_DIR)/user_headers/include

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		LIBS="$(TARGET_LDFLAGS) -lnl-tiny -lm -luci"
endef

define Package/swconfig/install
	$(INSTALL_DIR) $(1)/sbin $(1)/lib/network $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/swconfig $(1)/sbin/swconfig
ifneq ($(CONFIG_PRODUCT_IS_SGMAC), y)
	$(INSTALL_DATA) ./filesystem/switch.sh $(1)/lib/network/
	$(INSTALL_DATA) ./filesystem/vlan_func.sh $(1)/lib/network/
	$(CP) ./filesystem/switch $(1)/etc/init.d/
endif
endef
endif

ifeq ($(CONFIG_IPF_PLATFORM_BCM), y)
define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
endef

define Package/swconfig/install
	$(INSTALL_DIR) $(1)/sbin $(1)/lib/network $(1)/etc/init.d
#	$(INSTALL_BIN) $(PKG_BUILD_DIR)/swconfig $(1)/sbin/swconfig
ifneq ($(CONFIG_PRODUCT_IS_SGMAC), y)
	$(INSTALL_DATA) ./filesystem/switch.sh $(1)/lib/network/
	$(INSTALL_DATA) ./filesystem/vlan_func.sh $(1)/lib/network/
	$(CP) ./filesystem/switch_bcm $(1)/etc/init.d/switch
endif
endef
endif

$(eval $(call BuildPackage,swconfig))
