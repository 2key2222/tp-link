#
# Copyright (C) 2008-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=sysstat
PKG_VERSION:=10.1.7
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://pagesperso-orange.fr/sebastien.godard
PKG_MD5SUM:=72e9d84efcbb366a988de09e958636e2

#PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/sysstat
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  SUBMENU:=Debug
  TITLE:=Sysstat performance monitoring tools
  URL:=http://pagesperso-orange.fr/sebastien.godard/index.html
endef

define Package/sysstat/description
  The sysstat utilities are a collection of performance monitoring tools for
  Linux. These include sar, sadf, mpstat, iostat, pidstat and sa tools.
endef

define Package/sysstat/conffiles
/etc/sysstat/sysstat.ioconf
/etc/sysstat/config
endef

CONFIGURE_VARS+= \
	sa_lib_dir="/usr/lib/sysstat" \
	sa_dir="/var/log/sysstat" \
	conf_dir="/etc/sysstat" \

CONFIGURE_ARGS+= \
	--disable-documentation \

define Build/Configure
	[ -f $(STAMP_CONFIGURED) ] || { \
		rm -f $(PKG_BUILD_DIR)/*.so.* $(PKG_BUILD_DIR)/*.a; \
		find $(PKG_BUILD_DIR) -name \*.o | xargs rm -f; \
	}
ifeq ($(CONFIG_IS_QCA956X), y)
	cd $(PKG_BUILD_DIR); \
		./configure --program-prefix="" --program-suffix="" --prefix=/usr --exec-prefix=/usr --bindir=/usr/bin --sbindir=/usr/sbin --libexecdir=/usr/lib --sysconfdir=/etc --datadir=/usr/share --localstatedir=/var --mandir=/usr/man --infodir=/usr/info --disable-nls   --disable-documentation --host=$(ARCH)-openwrt-linux
else
	cd $(PKG_BUILD_DIR); \
		./configure --program-prefix="" --program-suffix="" --prefix=/usr --exec-prefix=/usr --bindir=/usr/bin --sbindir=/usr/sbin --libexecdir=/usr/lib --sysconfdir=/etc --datadir=/usr/share --localstatedir=/var --mandir=/usr/man --infodir=/usr/info --disable-nls   --disable-documentation --host=$(LINUX_KARCH)
endif
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS) -lintl
endef


define Package/sysstat/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/{sadc,sa1,sa2,sar,sadf,iostat,mpstat,pidstat} $(1)/usr/bin/
endef

$(eval $(call BuildPackage,sysstat))
