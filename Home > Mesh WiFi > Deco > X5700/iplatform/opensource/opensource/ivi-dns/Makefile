#
# Copyright (c) 2017 Shenzhen TP-LINK Technologies Co.Ltd.
#
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ivi-dns
PKG_VERSION:=0.2

include $(INCLUDE_DIR)/package.mk

define Package/ivi-dns
  	SUBMENU:=IPv6
  	SECTION:=ipv6
    CATEGORY:=TP-LINK iplatform apps
    URL:=http://www.tp-link.com/
    TITLE:=ivi dns for TP-LINK
endef

define Package/ivi-dns/Description
	This is a app module for v6plus
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -u ./src/* $(PKG_BUILD_DIR)/
endef

define Package/ivi-dns/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ividns $(1)/usr/bin
endef

$(eval $(call BuildPackage,ivi-dns))
