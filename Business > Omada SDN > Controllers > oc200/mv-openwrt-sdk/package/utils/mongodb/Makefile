#
# Copyright (C) 2011-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mongodb
PKG_VERSION:=3.4.10

PKG_SOURCE:=$(PKG_NAME)-src-r$(PKG_VERSION).tar.gz
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-src-r$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/scons.mk

SCONS_ENV_TMP = \
	TARGET_ARCH="$(CONFIG_ARCH)" \
	MONGO_DISTARCH="$(CONFIG_ARCH)" \
	CC="${TOOLCHAIN_DIR}/bin/$(TARGET_CC_NOCACHE)" \
	CXX="${TOOLCHAIN_DIR}/bin/$(TARGET_CXX_NOCACHE)" \
	CFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	CCFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	CXXFLAGS="$(TARGET_CFLAGS) $(EXTRA_CFLAGS)" \
	CPPPATH="$(TARGET_CPPFLAGS) $(EXTRA_CPPFLAGS)" \
	LINKFLAGS="$(TARGET_LDFLAGS) $(EXTRA_LDFLAGS)" \
	LIBPATH=$(LINKFLAGS)

SCONS_ENV = $(subst -march=armv8-a, -march=armv8-a+crc, ${SCONS_ENV_TMP})

SCONS_OPTION = \
	--propagate-shell-environment \
	--disable-warnings-as-errors

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
	(cd $(PKG_BUILD_DIR); scons VERBOSE=on $(SCONS_ENV) $(SCONS_OPTION) all)
endef

define Package/mongodb/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongo $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mongod $(1)/usr/bin
endef

$(eval $(call BuildPackage,mongodb))
