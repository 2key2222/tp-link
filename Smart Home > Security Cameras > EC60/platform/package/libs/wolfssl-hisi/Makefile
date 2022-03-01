#
# Copyright (C) 2006-2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=wolfssl-hisi
PKG_NAME_BASE:=wolfssl
PKG_VERSION:=3.11.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME_BASE)-$(PKG_VERSION).zip
PKG_SOURCE_URL:=https://www.wolfssl.com/
PKG_MD5SUM:=df435eacae4f2f1a92a241e80a2106d9

PKG_FIXUP:=libtool autocmd
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1
PKG_LICENSE:=GPL-2.0+
PKG_AUTO_CMD=sed -i 's/\(soname_spec=[^}]*\)\(}\)/\1\2_hisi/g' configure
PKG_UNPACK=unzip -d $(PKG_BUILD_DIR) $(DL_DIR)/$(PKG_SOURCE);mv $(PKG_BUILD_DIR)/$(PKG_NAME_BASE)-$(PKG_VERSION)/* $(PKG_BUILD_DIR)/;rm -rf $(PKG_BUILD_DIR)/$(PKG_NAME_BASE)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/wolfssl-hisi
  SECTION:=libs
  SUBMENU:=SSL
  CATEGORY:=Libraries
  TITLE:=wolfssl-hisi library
  DEPENDS:=+SDK_HISI_3518E_V200:libmpp-3518e-v200
  URL:=http://www.wolfssl.com/
endef

define Package/wolfssl-hisi/description
wolfssl-hisi is an SSL library optimized for small footprint, both on disk and for
memory use.
endef

TARGET_CFLAGS += $(FPIC)

CONFIGURE_ARGS += \
	--enable-singlethreaded \
	--enable-opensslextra \
	--enable-sni \
	--enable-stunnel \
	--enable-ecc \
	--disable-examples \
	--disable-aesgcm \
	--enable-sslv3 \
	--enable-sep \
	--enable-fastmath \
	--enable-staticmemory

EXTRA_CFLAGS += -DTFM_ARM

ifeq ($(CONFIG_BOARD_NAME),"model_hisi_hi3518ev200")
	EXTRA_LDFLAGS += -lhi_cipher
	EXTRA_CPPFLAGS += -DBOARD_HI3518EV200
endif

#ifneq ($(CONFIG_TARGET_x86),)
#	CONFIGURE_ARGS += --enable-intelasm
#endif
#ifneq ($(CONFIG_TARGET_x86_64),)
#	CONFIGURE_ARGS += --enable-intelasm
#endif

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	#$(CP) $(PKG_INSTALL_DIR)/usr/lib/libwolfssl-hisi.{so*,la} $(1)/usr/lib/

	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libwolfssl.so.12.0.0 $(1)/usr/lib/libwolfssl_hisi.so.12.0.0
	ln -s libwolfssl_hisi.so.12.0.0 $(1)/usr/lib/libwolfssl_hisi.so
	ln -s libwolfssl_hisi.so.12.0.0 $(1)/usr/lib/libwolfssl_hisi.so.12
	ln -s libwolfssl_hisi.so $(1)/usr/lib/libcyassl_hisi.so
	
endef

define Package/wolfssl-hisi/install
	$(INSTALL_DIR) $(1)/usr/lib
	#$(CP) $(PKG_INSTALL_DIR)/usr/lib/libwolfssl-hisi.so* $(1)/usr/lib/

	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libwolfssl.so.12.0.0 $(1)/usr/lib/libwolfssl_hisi.so.12.0.0
	ln -s libwolfssl_hisi.so.12.0.0 $(1)/usr/lib/libwolfssl_hisi.so
	ln -s libwolfssl_hisi.so.12.0.0 $(1)/usr/lib/libwolfssl_hisi.so.12
	ln -s libwolfssl_hisi.so $(1)/usr/lib/libcyassl_hisi.so
	
endef

$(eval $(call BuildPackage,wolfssl-hisi))
