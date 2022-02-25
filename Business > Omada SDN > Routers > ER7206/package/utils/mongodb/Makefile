#
# Copyright (C) 2011-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mongodb
PKG_VERSION:=2.6.12

PKG_SOURCE:=$(PKG_NAME)-src-r$(PKG_VERSION).tar
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-src-r$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/scons.mk

SCONS_ENV = \
	ARCH="$(CONFIG_ARCH)" \
	CC="$(TARGET_CC_NOCACHE)" \
	CXX="$(TARGET_CXX_NOCACHE)" \
	CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	CCFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	CPPFLAGS="$(TARGET_CPPFLAGS) $(EXTRA_CPPFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS) $(EXTRA_LDFLAGS)" \
	DESTDIR="$(PKG_INSTALL_DIR)"

SCONS_OPTION = \
	--propagate-shell-environment \
	--disable-warnings-as-errors \
	--cc-use-shell-environment \
	--cxx-use-shell-environment

define Package/mongodb
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=mongodb database
  DEPENDS:=+libstdcpp +libpcap
  URL:=www.mongodb.com
  SUBMENU:=database
endef

define Package/mongodb/description
 mongodb database.
endef

define Build/Configure/Default
endef

define Build/Compile
	(cd $(PKG_BUILD_DIR); $(SCONS_ENV) scons $(SCONS_OPTION) all)
endef

define Package/mongodb/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongo $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongoexport $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongooplog $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongos $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongotop $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongod $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongofiles $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongoperf $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongosniff $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongodump $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongoimport $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongorestore $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongostat $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bsondump $(1)/usr/bin
endef

$(eval $(call BuildPackage,mongodb))
