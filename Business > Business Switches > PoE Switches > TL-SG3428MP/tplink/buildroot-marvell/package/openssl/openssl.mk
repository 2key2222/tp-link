#############################################################
#
# openssl
#
#############################################################
OPENSSL_VERSION = 1.0.2q
#OPENSSL_VERSION = 0.9.8za
#OPENSSL_VERSION = 1.0.1c
OPENSSL_SITE = http://www.openssl.org/source
OPENSSL_LICENSE = OpenSSL or SSLeay
OPENSSL_LICENSE_FILES = LICENSE
OPENSSL_INSTALL_STAGING = YES
OPENSSL_DEPENDENCIES = zlib
OPENSSL_TARGET_ARCH = generic32
OPENSSL_CFLAGS = $(TARGET_CFLAGS)
OPENSSL_CFLAGS += -DOPENSSL_SYSNAME_LINUX

ifeq ($(BR2_PACKAGE_OPENSSL_BIN),)
define OPENSSL_DISABLE_APPS
	$(SED) '/^build_apps/! s/build_apps//' $(@D)/Makefile.org
	$(SED) '/^DIRS=/ s/apps//' $(@D)/Makefile.org
endef
endif

OPENSSL_PRE_CONFIGURE_HOOKS += OPENSSL_DISABLE_APPS

ifeq ($(BR2_PACKAGE_OPENSSL_OCF),y)
	OPENSSL_CFLAGS += -DHAVE_CRYPTODEV -DUSE_CRYPTODEV_DIGESTS
	OPENSSL_DEPENDENCIES += ocf-linux
endif

# Some architectures are optimized in OpenSSL
ifeq ($(ARCH),arm)
ifneq ($(BR2_generic_arm),y)
ifneq ($(BR2_arm610),y)
ifneq ($(BR2_arm710),y)
#	OPENSSL_TARGET_ARCH = armv4
endif
endif
endif
endif
ifeq ($(ARCH),powerpc)
	OPENSSL_TARGET_ARCH = ppc
endif
ifeq ($(ARCH),x86_64)
	OPENSSL_TARGET_ARCH = x86_64
endif

# Workaround for bug #3445
ifeq ($(BR2_x86_i386),y)
	OPENSSL_TARGET_ARCH = generic32 386
endif

define OPENSSL_CONFIGURE_CMDS
	(cd $(@D); \
		$(TARGET_CONFIGURE_ARGS) \
		$(TARGET_CONFIGURE_OPTS) \
		./Configure \
			linux-$(OPENSSL_TARGET_ARCH) \
			--prefix=/usr \
			--openssldir=/etc/ssl \
			threads \
			$(if $(BR2_PREFER_STATIC_LIB),no-shared,shared) \
			no-asm \
			no-rc5 \
			enable-weak-ssl-ciphers \
			enable-camellia \
			enable-mdc2 \
			enable-tlsext \
			$(if $(BR2_PREFER_STATIC_LIB),zlib,zlib-dynamic) \
			$(if $(BR2_PREFER_STATIC_LIB),no-dso) \
	)
	$(SED) "s:-march=[-a-z0-9] ::" -e "s:-mcpu=[-a-z0-9] ::g" $(@D)/Makefile
	$(SED) "s:-O[0-9]:$(OPENSSL_CFLAGS):" $(@D)/Makefile
endef

define OPENSSL_BUILD_CMDS
	$(MAKE1) -C $(@D) all build-shared
	$(MAKE1) -C $(@D) do_linux-shared
endef

define OPENSSL_INSTALL_STAGING_CMDS
	$(MAKE1) -C $(@D) INSTALL_PREFIX=$(STAGING_DIR) install
endef

define OPENSSL_INSTALL_TARGET_CMDS
	$(MAKE1) -C $(@D) INSTALL_PREFIX=$(TARGET_DIR) install
	ln -s libcrypto.so.1.0.0  $(TARGET_DIR)/usr/lib/libcrypto.so.0.9.8
	ln -s libssl.so.1.0.0  $(TARGET_DIR)/usr/lib/libssl.so.0.9.8
endef

define OPENSSL_REMOVE_DEV_FILES
	rm -rf $(TARGET_DIR)/usr/lib/ssl
endef

ifneq ($(BR2_HAVE_DEVFILES),y)
OPENSSL_POST_INSTALL_TARGET_HOOKS += OPENSSL_REMOVE_DEV_FILES
endif

define OPENSSL_INSTALL_FIXUPS
	rm -f $(TARGET_DIR)/usr/bin/c_rehash
endef

OPENSSL_POST_INSTALL_TARGET_HOOKS += OPENSSL_INSTALL_FIXUPS

ifneq ($(BR2_PREFER_STATIC_LIB),y)

# libraries gets installed read only, so strip fails
define OPENSSL_INSTALL_FIXUPS_SHARED
	if [ -d $(TARGET_DIR)/usr/lib/engines ]; then \
	chmod +w $(TARGET_DIR)/usr/lib/engines/lib*.so;\
	fi
	for i in $(addprefix $(TARGET_DIR)/usr/lib/,libcrypto.so.* libssl.so.*); \
	do chmod +w $$i; done
endef

OPENSSL_POST_INSTALL_TARGET_HOOKS += OPENSSL_INSTALL_FIXUPS_SHARED

endif

define OPENSSL_REMOVE_OPENSSL_ENGINES
	rm -rf $(TARGET_DIR)/usr/lib/engines
endef

ifneq ($(BR2_PACKAGE_OPENSSL_ENGINES),y)
#OPENSSL_POST_INSTALL_TARGET_HOOKS += OPENSSL_REMOVE_OPENSSL_ENGINES
endif

define OPENSSL_UNINSTALL_CMDS
	rm -rf $(addprefix $(TARGET_DIR)/,etc/ssl usr/bin/openssl usr/include/openssl)
	rm -rf $(addprefix $(TARGET_DIR)/usr/lib/,ssl engines libcrypto* libssl* pkgconfig/libcrypto.pc)
	rm -rf $(addprefix $(STAGING_DIR)/,etc/ssl usr/bin/openssl usr/include/openssl)
	rm -rf $(addprefix $(STAGING_DIR)/usr/lib/,ssl engines libcrypto* libssl* pkgconfig/libcrypto.pc)
endef

$(eval $(generic-package))
