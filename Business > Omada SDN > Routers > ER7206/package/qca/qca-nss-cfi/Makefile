include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=qca-nss-cfi
PKG_RELEASE:=2

PKG_SOURCE_DIR:=$(TPLINK_DIR)/package/qca/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

PKG_BUILD_DEPENDS:=ocf-crypto-headers

ifeq ($(findstring 4.4, $(LINUX_VERSION)),)
 CRYPTO_API_MODULE:=$(PKG_BUILD_DIR)/cryptoapi/qca-nss-cfi-cryptoapi.ko
endif

define KernelPackage/qca-nss-cfi
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Devices
  #DEPENDS:=@TARGET_ipq806x +kmod-qca-nss-crypto +kmod-crypto-ocf @!LINUX_3_18
  DEPENDS:=@TARGET_ipq806x +kmod-qca-nss-crypto @!LINUX_3_18
  TITLE:=Kernel driver for NSS cfi
  FILES:=$(PKG_BUILD_DIR)/ocf/qca-nss-cfi-ocf.ko \
	 $(PKG_BUILD_DIR)/ipsec/qca-nss-ipsec.ko \
	 $(CRYPTO_API_MODULE)
  #AUTOLOAD:=$(call AutoLoad,59,qca-nss-cfi-ocf qca-nss-cfi-cryptoapi qca-nss-ipsec)
  AUTOLOAD:=$(call AutoLoad,59,qca-nss-cfi-cryptoapi)
endef

define KernelPackage/qca-nss-cfi/Description
This package contains a NSS cfi driver for QCA chipset
endef

EXTRA_CFLAGS+= \
	-DCONFIG_NSS_DEBUG_LEVEL=4 \
	-I$(STAGING_DIR)/usr/include/qca-nss-crypto \
	-I$(STAGING_DIR)/usr/include/crypto \
	-I$(STAGING_DIR)/usr/include/qca-nss-drv \

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(PKG_SOURCE_DIR)/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		CC="$(TARGET_CC)" \
		modules
endef

$(eval $(call KernelPackage,qca-nss-cfi))
