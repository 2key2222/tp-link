#
# Copyright (C) 2009-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=nginx
PKG_VERSION:=1.8.1
PKG_OLD_VERSION:=1.4.7
PKG_NGX_VERSION:=1.8.1
PKG_LUA_VERSION:=0.10.5
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_NGX_VERSION).tar.gz
PKG_SOURCE_URL:=http://nginx.org/download/
PKG_MD5SUM:=2e91695074dbdfbf1bcec0ada9fda462
PKG_MAINTAINER:=Thomas Heil <heil@terminal-consulting.de>
PKG_LICENSE:=2-clause BSD-like license

PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

PKG_CONFIG_DEPENDS := \
	CONFIG_NGINX_SSL \
	CONFIG_NGINX_LUA \
	CONFIG_NGINX_PCRE \
	CONFIG_NGINX_HTTP_CACHE \
	CONFIG_NGINX_HTTP_GZIP

include $(INCLUDE_DIR)/package.mk

define Package/nginx
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Web Servers/Proxies
  TITLE:=Nginx web server
  URL:=http://nginx.org/
  DEPENDS:=+NGINX_PCRE:libpcre +(NGINX_SSL||NGINX_HTTP_CACHE||NGINX_HTTP_AUTH_BASIC):libopenssl +NGINX_HTTP_GZIP:zlib +libpthread +NGINX_LUA:liblua +librt
  MENU:=1
endef

define Package/nginx/description
 nginx is an HTTP and reverse proxy server, as well as a mail proxy server,
 written by Igor Sysoev.
endef

define Package/nginx/config
  source "$(SOURCE)/Config.in"
endef

config_files=nginx.conf mime.types fastcgi_params koi-utf koi-win win-utf

define Package/nginx/conffiles
/etc/nginx/
/www/luci-static/resources/authserver/
endef

ADDITIONAL_MODULES:=
ifeq ($(CONFIG_NGINX_SSL),y)
  ADDITIONAL_MODULES += --with-http_ssl_module
endif
ifeq ($(CONFIG_NGINX_LUA),y)
  ADDITIONAL_MODULES += --add-module=$(PKG_BUILD_DIR)/lua-nginx-module-$(PKG_LUA_VERSION)
endif
ifneq ($(CONFIG_NGINX_HTTP_CACHE),y)
  ADDITIONAL_MODULES += --without-http-cache
endif
ifneq ($(CONFIG_NGINX_PCRE),y)
  ADDITIONAL_MODULES += --without-pcre
endif
ifneq ($(CONFIG_NGINX_HTTP_GZIP),y)
  ADDITIONAL_MODULES += --without-http_gzip_module
endif

define Build/Configure
	# TODO: fix --crossbuild
	(cd $(PKG_BUILD_DIR) ;\
		$(if $(CONFIG_NGINX_LUA),LUA_INC=$(STAGING_DIR)/usr/include LUA_LIB=$(STAGING_DIR)/usr/lib) \
		./configure \
			--crossbuild=Linux::$(ARCH) \
			--prefix=/usr \
			--conf-path=/etc/nginx/nginx.conf \
			$(ADDITIONAL_MODULES) \
			--error-log-path=/var/log/nginx/error.log \
			--pid-path=/var/run/nginx.pid \
			--lock-path=/var/lock/nginx.lock \
			--http-log-path=/var/log/nginx/access.log \
			--http-client-body-temp-path=/var/lib/nginx/body \
			--with-cc="$(TARGET_CC)" \
			--with-cc-opt="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
			--with-ld-opt="$(TARGET_LDFLAGS) -lrt" )
endef

define Package/nginx/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/nginx $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/nginx
	$(INSTALL_DATA) $(addprefix $(PKG_INSTALL_DIR)/etc/nginx/,$(config_files)) $(1)/etc/nginx/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/nginx.init $(1)/etc/init.d/nginx
	$(INSTALL_DIR) $(1)/usr/lib/lua/ngx_authserver/
	${CP} -rf $(TPLINK_DIR)/opensource/$(PKG_NAME)/files/ngx_authserver/lua/*  $(1)/usr/lib/lua/ngx_authserver/
	$(INSTALL_DIR) $(1)/www/luci-static/resources/authserver/
	${CP} -rf $(TPLINK_DIR)/opensource/$(PKG_NAME)/files/ngx_authserver/resources/* $(1)/www/luci-static/resources/authserver/
	${CP} -rf $(TPLINK_DIR)/opensource/$(PKG_NAME)/files/nginx/nginx.conf $(1)/etc/nginx/
	$(INSTALL_DIR) $(1)/etc/hotplug.d/bridgescripts
	$(INSTALL_BIN) $(TPLINK_DIR)/opensource/$(PKG_NAME)/files/nginx/etc/hotplug.d/bridgescripts/* $(1)/etc/hotplug.d/bridgescripts/
	$(INSTALL_DIR) $(1)/etc/cfgsync.d
	$(INSTALL_BIN) $(TPLINK_DIR)/opensource/$(PKG_NAME)/files/nginx/etc/cfgsync.d/* $(1)/etc/cfgsync.d/
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	$(if $(CONFIG_NGINX_LUA),$(call Prepare/lua-nginx))
endef

define Download/lua-nginx
	VERSION:=d3ab0edd45bffe1b9a36abdf5bff544de436ccee
	SUBDIR:=lua-nginx
	FILE:=lua-nginx-module-$(PKG_LUA_VERSION).tar.gz
	URL:=https://github.com/chaoslawful/lua-nginx-module.git
	PROTO:=git
endef

define  Prepare/lua-nginx
	$(eval $(call Download,lua-nginx))
	gzip -dc $(DL_DIR)/$(FILE) | tar -C $(PKG_BUILD_DIR) $(TAR_OPTIONS)
	$(call PatchDir,$(PKG_BUILD_DIR),./patches-lua-nginx)
endef


$(eval $(call BuildPackage,nginx))

