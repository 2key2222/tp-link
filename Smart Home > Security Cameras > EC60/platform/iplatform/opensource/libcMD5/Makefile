include $(TOPDIR)/rules.mk

PKG_NAME:=libcMD5
PKG_RELEASE:=1
PKG_VERSION:=1.0

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=TP-LINK
	DEPENDS:=
	CATEGORY:=TP-LINK iplatform apps
	TITLE:=$(PKG_NAME).so
endef

define Package/$(PKG_NAME)/description
	library for deal with MD5
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libcMD5.so $(1)/usr/lib/
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/md5.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libcMD5.so $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
