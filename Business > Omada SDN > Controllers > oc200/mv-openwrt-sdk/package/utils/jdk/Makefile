#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=openjdk
PKG_VERSION:=1.8.0-u60-b23

PKG_SOURCE:=openjdk-8u60-b23-linux-arm64.tar.gz
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/jdk
  SUBMENU:=Java
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Openjdk Embedded
  URL:=http://openjdk.java.net
  DEPENDS:=+libthread-db
endef

define Package/jdk/description
 Openjdk Embedded.
endef

define Build/Configure/Default
endef

define Build/Compile
endef


define Package/jdk/install
	$(INSTALL_DIR) $(1)/bin
	$(CP) $(PKG_BUILD_DIR)/bin/* $(1)/bin
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_BUILD_DIR)/lib/* $(1)/lib
endef

$(eval $(call BuildPackage,jdk))
