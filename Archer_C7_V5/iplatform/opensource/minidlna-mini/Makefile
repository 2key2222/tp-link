#
# Copyright (C) 2010-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=minidlna-mini
PKG_VERSION:=1.1.2
PKG_RELEASE:=1

#PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
#PKG_SOURCE_URL:=@SF/minidlna
#PKG_MD5SUM:=65cebffaf9b57bf30fbfcf2a3a3253e6

PKG_BUILD_PARALLEL:=0
PKG_BUILD_DEPENDS:=util-linux
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

$(warning $(CONFIG_PACKAGE_minidlna-parsing-support))
$(warning $(CONFIG_PACKAGE_minidlna-image-limit))

define Package/minidlna-mini/Default
  SECTION:=multimedia-mini
  CATEGORY:=TP-LINK iplatform apps
  SUBMENU:=USB Storage Sharing
  #URL:=http://minidlna.sourceforge.net/
endef

define Package/minidlna-mini
  $(call Package/minidlna-mini/Default)
  TITLE:=UPnP A/V & DLNA Media Server
  DEPENDS:= +libpthread +libsqlite3 +libubox +libubus +libogg +libiconv-full +zlib +libbz2 \
  	+libid3tag +libflac +libvorbis +libuuid +libtiff \
  	$(ICONV_DEPENDS) $(INTL_DEPENDS)
endef

define Package/minidlna-parsing-support
  $(call Package/minidlna-mini/Default)
  TITLE:=Media parsing support
  DEPENDS:=@(PACKAGE_minidlna)
endef

define Package/minidlna-image-limit
  $(call Package/minidlna-mini/Default)
  TITLE:=Limit image's size of parsed
  DEPENDS:=@(PACKAGE_minidlna)
endef

define Package/minidlna-image-limit/config
  select PACKAGE_minidlna-parsing-support
endef

define Package/minidlna-mini/description
  MiniDLNA (aka ReadyDLNA) is server software with the aim of
  being fully compliant with DLNA/UPnP-AV clients.
endef

define Package/minidlna-mini/conffiles
/etc/config/minidlna
/etc/minidlna.conf
endef

TARGET_CPPFLAGS += \
	-I$(STAGING_DIR)/usr/include \
	-I$(STAGING_DIR)/usr/include/FLAC \
	-I$(STAGING_DIR)/usr/include/libavcodec \
	-I$(STAGING_DIR)/usr/include/libavformat \
	-I$(STAGING_DIR)/usr/include/libavutil \
	-I$(STAGING_DIR)/usr/include/libexif \
	-I$(STAGING_DIR)/usr/include/uuid \
	-I$(STAGING_DIR)/usr/include/vorbis \
	-I$(ICONV_PREFIX)/include \
	-I$(INTL_PREFIX)/include \
	-D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 \

ifneq ($(CONFIG_PACKAGE_minidlna-parsing-support),)
	TARGET_CPPFLAGS += -DMEDIA_PARSING_SUPPORT
endif
ifneq ($(CONFIG_PACKAGE_minidlna-image-limit),)
	TARGET_CPPFLAGS += -DIMAGE_PARSING_LIMIT
endif
ifneq ($(CONFIG_arm),)
	TARGET_CPPFLAGS += -D__ARM__
endif

TARGET_LDFLAGS += \
	-L$(ICONV_PREFIX)/lib \
	-L$(INTL_PREFIX)/lib \
	-Wl,-rpath-link=$(STAGING_DIR)/usr/lib \

MAKE_FLAGS +=\
	CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)" \
	ICONV_LIBS="-liconv $(if $(INTL_FULL),-lintl)" \

CONFIGURE_ARGS += \
	--program-prefix="$(STAGING_DIR)/usr" \
	--with-libiconv-prefix="$(ICONV_PREFIX)" \
	--with-libintl-prefix="$(INTL_PREFIX)" \
	--with-os-name="TP-Link Linux" \
	--with-os-version="$(LINUX_VERSION)" \
	--with-os-url="http://www.tp-link.com/" \
	--with-db-path="/var/run/minidlna" \
	--with-log-path="/var/log" \

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Package/minidlna-mini/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/minidlnad $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./filesystem/etc/init.d/minidlna $(1)/etc/init.d/minidlna
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./filesystem/etc/config/minidlna $(1)/etc/config/minidlna
endef

define Package/minidlna-mini/conffiles
/etc/config/minidlna
endef

$(eval $(call BuildPackage,minidlna-mini))
#$(eval $(call BuildPackage,minidlna-parsing-support))
#$(eval $(call BuildPackage,minidlna-image-limit))
