# nand image creator

include $(TOPDIR)/rules.mk

PKG_NAME:=linux-nand
PKG_RELEASE:=1

PKG_FILES_DIR:=$(TOPDIR)/tools/$(PKG_NAME)

include $(INCLUDE_DIR)/host-build.mk

define Host/Prepare
	mkdir -p $(HOST_BUILD_DIR)
	$(CP) -rf $(PKG_FILES_DIR)/* $(HOST_BUILD_DIR)/
endef

define Host/Configure
endef

define Host/Compile

endef

define Host/Install
	$(INSTALL_DIR) $(STAGING_DIR_HOST)/bin
	$(INSTALL_BIN) $(HOST_BUILD_DIR)/nand_image_creator $(STAGING_DIR_HOST)/bin
endef

$(eval $(call HostBuild))
