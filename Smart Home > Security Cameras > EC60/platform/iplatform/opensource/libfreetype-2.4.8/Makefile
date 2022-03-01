#
# Copyright (c) 2016 Shenzhen TP-LINK Technologies Co.Ltd.
#
# Author  : liziliang@tp-link.net>
# Version : 1.0
# Date    : April 14, 2016
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libfreetype-2.4.8
PKG_VERSION:=1.0

LIB_NAME:= libfreetype.so.6 

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  MAINTAINER:=TP-LINK
  DEPENDS:= 
  TITLE:=libfreetype.so.6
endef

define Package/$(PKG_NAME)/Description
	lib for region to draw bitmap of words
endef

define Build/Prepare
	$(INSTALL_DIR) $(PKG_BUILD_DIR)
	$(CP) -u ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) DESTDIR="$(PKG_INSTALL_DIR)" all
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(LIB_NAME) $(1)/usr/lib
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include
	$(CP) $(PKG_BUILD_DIR)/freetype-2.4.8/include/*.h $(STAGING_DIR)/usr/include/
	$(CP) -r $(PKG_BUILD_DIR)/freetype-2.4.8/include/freetype/ $(STAGING_DIR)/usr/include/

	$(INSTALL_DIR) $(STAGING_DIR)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/$(LIB_NAME)  $(STAGING_DIR)/usr/lib/
endef

export TOPDIR
export CONFIG_TOOLCHAIN_PREFIX
export CONFIG_TOOLCHAIN_ROOT
export CONFIG_BOARD_NAME

$(eval $(call BuildPackage,$(PKG_NAME)))
