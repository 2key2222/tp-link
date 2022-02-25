#
# Copyright (c) 2013 The Linux Foundation. All rights reserved.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=qca-ssdk
PKG_SOURCE_PROTO:=git
PKG_BRANCH:=master
PKG_RELEASE:=1

include $(INCLUDE_DIR)/local-development.mk
ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_VERSION:=$(shell git ls-remote $(PKG_SOURCE_URL) $(PKG_BRANCH) | cut -b -7)
endif
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_VERSION)

LOCAL_VARIANT=$(patsubst qca-ssdk-%,%,$(patsubst qca-ssdk-%,%,$(BUILD_VARIANT)))
include $(INCLUDE_DIR)/package.mk

define KernelPackage/qca-ssdk/default-nohnat
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Devices
  TITLE:=Kernel driver for QCA SSDK
  FILES:=$(PKG_BUILD_DIR)/build/bin/qca-ssdk.ko
  AUTOLOAD:=$(call AutoLoad,50,qca-ssdk)
  PROVIDES:=qca-ssdk
endef

define KernelPackage/qca-ssdk-nohnat
$(call KernelPackage/qca-ssdk/default-nohnat)
  VARIANT:=nohnat
endef

define KernelPackage/qca-ssdk-nohnat/Description
This package contains a qca-ssdk driver for QCA chipset
endef

define KernelPackage/qca-ssdk-hnat
$(call KernelPackage/qca-ssdk/default-nohnat)
  TITLE+= (hnat)
  VARIANT:=hnat
endef

define KernelPackage/qca-ssdk-hnat/Description
This package contains a qca-ssdk-hnat driver for QCA chipset
endef

define KernelPackage/qca-ssdk-hnat/config
	menu "qca-ssdk-hnat custom configuration"

	config QCA_SSDK_HNAT_PRODUCT_CONFIG
		string "Product configuration file name."
		default "default"
		help
			All avaliable configuration files can be found under 'configs' directory of source directory.

	endmenu
endef

define KernelPackage/qca-ssdk-nohnat/config
	menu "qca-ssdk-nohnat custom configuration"

	config QCA_SSDK_NOHNAT_PRODUCT_CONFIG
		string "Product configuration file name."
		default "default"
		help
			All avaliable configuration files can be found under 'configs' directory of source directory.

	endmenu
endef

ifneq ($(CONFIG_PACKAGE_kmod-qca-ssdk-hnat),)
	QCA_SSDK_PRODUCT_CONFIG:=$(CONFIG_QCA_SSDK_HNAT_PRODUCT_CONFIG)
endif
ifneq ($(CONFIG_PACKAGE_kmod-qca-ssdk-nohnat),)
	QCA_SSDK_PRODUCT_CONFIG:=$(CONFIG_QCA_SSDK_NOHNAT_PRODUCT_CONFIG)
endif

ifeq ($(QCA_SSDK_PRODUCT_CONFIG),)
	QCA_SSDK_PRODUCT_CONFIG:=default
endif

QCASSDK_CONFIG_OPTS+= TOOL_PATH=$(TOOLCHAIN_DIR)/bin/ \
                SYS_PATH=$(LINUX_SRC_DIR) \
                SYS_BUILD_DIR=$(LINUX_DIR) \
                TOOLPREFIX=$(TARGET_CROSS) \
                KVER=$(LINUX_VERSION) \
                ARCH=$(LINUX_KARCH) \
                PRODUCT_CONFIG_FILE=$(QCA_SSDK_PRODUCT_CONFIG)

ifeq ($(LOCAL_VARIANT),hnat)
    QCASSDK_CONFIG_OPTS+= HNAT_FEATURE=enable
endif

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/qca-ssdk
	$(INSTALL_DIR) $(1)/usr/include/qca-ssdk/api
	$(CP) -rf $(PKG_BUILD_DIR)/include/api/sw_ioctl.h $(1)/usr/include/qca-ssdk/api
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(strip $(QCASSDK_CONFIG_OPTS))
endef

define KernelPackage/qca-ssdk-hnat/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/etc/init.d/qca-hnat-start $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) ./files/usr/sbin/qca-hnat $(1)/usr/sbin
endef

$(eval $(call KernelPackage,qca-ssdk-nohnat))
$(eval $(call KernelPackage,qca-ssdk-hnat))
