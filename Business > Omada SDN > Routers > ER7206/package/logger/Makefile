include $(TOPDIR)/rules.mk

PKG_NAME:=logger
PKG_VERSION:=1.0

PKG_SOURCE_DIR:=$(TOPDIR)/package/$(PKG_NAME)


include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/liblogger
  SECTION:=TP-LINK
  CATEGORY:=$(TPLINK_CATEGORY)
  SUBMENU:=Apps
  MAINTAINER:=TP-LINK
  DEPENDS:= +libuci +libiconv-full
  TITLE:=Sytem Log libs
endef

define Package/liblogger/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/liblogger.so $(1)/usr/lib
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -u $(PKG_SOURCE_DIR)/* $(PKG_BUILD_DIR)/
endef


define Build/Compile

endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_SOURCE_DIR)/logger.h $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/liblogger.so $(1)/usr/lib
endef


$(eval $(call BuildPackage,liblogger))

