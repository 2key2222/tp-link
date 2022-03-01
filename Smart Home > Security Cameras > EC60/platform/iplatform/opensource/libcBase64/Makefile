include $(TOPDIR)/rules.mk

PKG_NAME:=libcBase64
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
	library for deal with Base64
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libcBase64.so $(1)/usr/lib/
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/base64.h $(STAGING_DIR)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libcBase64.so $(1)/usr/lib/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
