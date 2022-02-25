#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ejre
PKG_VERSION:=1.7.0_75

PKG_SOURCE:=ejre-7u75-fcs-b13-linux-arm-vfp-hflt-client_headless-18_dec_2014.tar.gz
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/ejre
  SUBMENU:=Java
  SECTION:=lang
  CATEGORY:=Languages
  TITLE:=Oracle Java SE Embedded version 7 Update 75
  URL:=http://www.oracle.com
endef

define Package/jamvm/description
 Oracle Java SE Embedded version 7 Update 75.
endef

define Build/Configure/Default
endef

define Build/Compile
endef


define Package/ejre/install
	$(INSTALL_DIR) $(1)/bin
	$(CP) -r $(PKG_BUILD_DIR)/bin/* $(1)/bin
	$(INSTALL_DIR) $(1)/lib
	$(CP) -r $(PKG_BUILD_DIR)/lib/* $(1)/lib
endef

$(eval $(call BuildPackage,ejre))
