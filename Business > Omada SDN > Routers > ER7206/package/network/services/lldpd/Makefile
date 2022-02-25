#
# Copyright (C) 2008-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=lldpd
PKG_VERSION:=1.0.4
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_DIR:=$(TPLINK_DIR)/opensource/$(PKG_NAME)/src
PKG_FILES_DIR:=$(TPLINK_DIR)/opensource/$(PKG_NAME)/files


#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=http://media.luffy.cx/files/lldpd
#PKG_MD5SUM:=9031734c69940dd79a0a175123275f83

#PKG_MAINTAINER:=Jo-Philipp Wich <jow@openwrt.org>

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

TARGET_CFLAGS+=--std=c99

include $(INCLUDE_DIR)/package.mk

define Package/lldpd
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Routing and Redirection
  TITLE:=Link Layer Discovery Protocol daemon
  URL:=https://github.com/vincentbernat/lldpd/wiki
  DEPENDS:=+libevent2 +USE_EGLIBC:libbsd +libjson-c +libxml2 +libssp
endef

define Package/lldpd/description
	LLDP (Link Layer Discovery Protocol) is an industry standard protocol designed
	to supplant proprietary Link-Layer protocols such as
	Extreme's EDP (Extreme Discovery Protocol) and
	CDP (Cisco Discovery Protocol).
	The goal of LLDP is to provide an inter-vendor compatible mechanism to deliver
	Link-Layer notifications to adjacent network devices.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -u $(PKG_SOURCE_DIR)/* $(PKG_BUILD_DIR)/
endef

define Package/lldpd/extra_provides
    echo "libssp.so.0"
endef

define Package/lldpd/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/usr/lib $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/lib/lldpd
	$(INSTALL_BIN) $(PKG_FILES_DIR)/*sh $(1)/lib/lldpd
	$(CP) $(PKG_INSTALL_DIR)/usr/sbin/lldp{cli,ctl,d} $(1)/usr/sbin/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/liblldpctl.so* $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_FILES_DIR)/lldpd.init $(1)/etc/init.d/lldpd
	$(INSTALL_DATA) $(PKG_FILES_DIR)/lldpd.config $(1)/etc/config/lldpd
ifneq ($(wildcard $(TOOLCHAIN_DIR)/lib/libssp.so),)
	#$(INSTALL_DIR) $(TARGET_DIR)/lib
	#$(INSTALL_DATA) $(TOOLCHAIN_DIR)/lib/libssp.so* $(TARGET_DIR)/lib

	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_DATA) $(TOOLCHAIN_DIR)/lib/libssp.so* $(1)/lib
endif
endef

define Package/lldpd/conffiles
/etc/config/lldpd
endef

TARGET_CFLAGS += -DTP_CUSTOM
TARGET_LDFLAGS += -ljson-c

#CONFIGURE_ARGS += \
#	--with-privsep-user=lldp \
#	--with-privsep-group=lldp \
#	--with-privsep-chroot=/var/run/lldp \
#	--with-readline=no \
#	--enable-dot3=no
	
CONFIGURE_ARGS += \
	--enable-privsep=no \
	--with-readline=no \
	--enable-dot3=no

$(eval $(call BuildPackage,lldpd))
