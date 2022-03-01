include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=libcJSON
PKG_RELEASE:=1
PKG_VERSION:=1.0

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib 
TARGET_LDFLAGS += -L$(STAGING_DIR)/lib 


define Package/$(PKG_NAME)
	SECTION:=TP-LINK
	DEPENDS:=
	CATEGORY:=TP-LINK iplatform apps
	TITLE:=$(PKG_NAME).so
endef

define Package/$(PKG_NAME)/description
	library for deal with json string
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
	mkdir -p $(STAGING_DIR)/usr/include
	$(CP) ./src/*.h $(STAGING_DIR)/usr/include/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
	$(TARGET_CONFIGURE_OPTS) LDFLAGS="$(TARGET_LDFLAGS)" CFLAGS="$(TARGET_CFLAGS) -I$(LINUX_DIR)/include"
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libcJSON.so $(1)/usr/lib/
	$(INSTALL_DIR) $(STAGING_DIR)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libcJSON.so $(STAGING_DIR)/usr/lib/
endef
$(eval $(call BuildPackage,$(PKG_NAME)))
