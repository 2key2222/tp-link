#
# Copyright (c) 2013 Qualcomm Atheros, Inc..
#
# All Rights Reserved.
# Qualcomm Atheros Confidential and Proprietary.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=qca-legacy-uboot
PKG_SOURCE_PROTO:=git
PKG_BRANCH:=1.1
PKG_RELEASE:=1

include $(INCLUDE_DIR)/local-development.mk
ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_VERSION:=$(shell git ls-remote $(PKG_SOURCE_URL) $(PKG_BRANCH) | cut -b -7)
endif
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_VERSION)

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)/$(BUILD_VARIANT)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

UBOOT_MAKE_OPTS:= \
    LZMA=$(STAGING_DIR_HOST)/bin/lzma \
    ARCH=mips \
    CPU=mips \
    CROSS_COMPILE=$(TARGET_CROSS)

ifdef BUILD_VARIANT
UBOOT_CONFIG:=$(patsubst UBOOT_CONFIG_TARGET=%,%,\
        $(filter UBOOT_CONFIG_TARGET%,\
            $(shell cat ./configs/$(BUILD_VARIANT)-$(BOARD)$(if $(SUBTARGET),_$(SUBTARGET)).mk)))
UBOOT_IMAGE:=$(if $(IMAGE),$(IMAGE),openwrt-$(BOARD)-$(BUILD_VARIANT)-qca-legacy-uboot.bin)
T_UBOOT_IMAGE:=$(if $(IMAGE),$(IMAGE),openwrt-$(BOARD)-$(BUILD_VARIANT)-qca-legacy-tuboot.bin)
UBOOT_MAKE_OPTS+=$(patsubst MAKEOPTS_%,%,\
        $(filter MAKEOPTS_%,\
            $(shell cat ./configs/$(BUILD_VARIANT)-$(BOARD)$(if $(SUBTARGET),_$(SUBTARGET)).mk)))
endif

ifneq ($(CONFIG_PACKAGE_NM_PTN_TABLE_BASE),)
  UBOOT_MAKE_OPTS+= NM_PTN_TABLE_BASE=$(CONFIG_PACKAGE_NM_PTN_TABLE_BASE)
endif
ifneq ($(CONFIG_PACKAGE_NM_FLASH_SIZE),)
  UBOOT_MAKE_OPTS+= NM_FLASH_SIZE=$(CONFIG_PACKAGE_NM_FLASH_SIZE)
endif
ifneq ($(CONFIG_PACKAGE_NM_PTN_NUM_MAX),)
  UBOOT_MAKE_OPTS+= NM_PTN_NUM_MAX=$(CONFIG_PACKAGE_NM_PTN_NUM_MAX)
endif
ifneq ($(CONFIG_DOUBLE_UBOOT),)
  UBOOT_MAKE_OPTS+= CFG_DOUBLE_BOOT_SECOND=$(CONFIG_DOUBLE_UBOOT) TP_FIRMWARE_RECOVERY=0 WEBFAILSAFE_SERVER=0
endif
ifneq ($(CONFIG_BOOT_WEBPAGE_PRODUCT_TAG),)
   export CONFIG_BOOT_WEBPAGE_PRODUCT_TAG:=$(CONFIG_BOOT_WEBPAGE_PRODUCT_TAG)
endif

define Build/Prepare
	$(call Build/Prepare/Default)
endef

define Build/Configure
	($(foreach var,$(strip $(UBOOT_MAKE_OPTS)), export $(var);) \
		$(MAKE) -C $(PKG_BUILD_DIR) mrproper);
	($(foreach var,$(strip $(UBOOT_MAKE_OPTS)), export $(var);) \
		$(MAKE) -C $(PKG_BUILD_DIR) $(UBOOT_CONFIG)_config \
			BUILDVERSION=$(PKG_VERSION)-$(PKG_RELEASE));
endef

define Build/Compile
	($(foreach var,$(strip $(UBOOT_MAKE_OPTS)), export $(var);) \
		$(MAKE) -C $(PKG_BUILD_DIR) all);
endef

define Build/InstallDev
endef

define Package/qca-legacy-uboot/common
  define Package/qca-legacy-uboot-$(1)
    SECTION:=boot
    CATEGORY:=Boot Loaders
    TITLE:=U-boot for $(1)
    DEPENDS:=@TARGET_ar71xx $(2)
    URL:=http://www.denx.de/wiki/U-Boot
    VARIANT:=$(1)
  endef

  define Package/qca-legacy-uboot-$(1)/config
    config DOUBLE_UBOOT
      bool "Enable double boot support"
      depends on PACKAGE_qca-legacy-uboot-$(1)
      default n

    config CONFIG_BOOT_WEBPAGE_PRODUCT_TAG
      string "Product hardware version"
      depends on PACKAGE_qca-legacy-uboot-$(1)
      default "Unknown"
  endef
endef

define Package/qca-legacy-uboot/nor
  $(call Package/qca-legacy-uboot/common,$(1),$(2))

  define Package/qca-legacy-uboot-$(1)/install
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/tuboot.bin $(BIN_DIR)/$(UBOOT_IMAGE)
#	$(INSTALL_DATA) $(PKG_BUILD_DIR)/u-boot.bin $(BIN_DIR)/$(UBOOT_IMAGE)
  endef

  $$(eval $$(call BuildPackage,qca-legacy-uboot-$(1)))
endef

define Package/qca-legacy-uboot/nand
  $(call Package/qca-legacy-uboot/common,$(1),+qca-romboot-$(2))

  define Package/qca-legacy-uboot-$(1)/install
	UTILPATH=$(STAGING_DIR_HOST)/bin $(STAGING_DIR_HOST)/bin/mk2stage-$(2) \
		-1 $(STAGING_DIR)/boot/openwrt-$(BOARD)-$(2)-rombootdrv.bin \
		-2 $(PKG_BUILD_DIR)/u-boot.bin \
		-o $(BIN_DIR)/$(patsubst %.bin,%.2fw,$(UBOOT_IMAGE))
  endef

  $$(eval $$(call BuildPackage,qca-legacy-uboot-$(1)))
endef

#$(eval $(call Package/qca-legacy-uboot/nor,ap121))
#$(eval $(call Package/qca-legacy-uboot/nor,ap135))
#$(eval $(call Package/qca-legacy-uboot/nand,ap135-nand,qca955x))
#$(eval $(call Package/qca-legacy-uboot/nor,ap136))
#$(eval $(call Package/qca-legacy-uboot/nor,db12x))
#$(eval $(call Package/qca-legacy-uboot/nand,cus227,ar934x))
#$(eval $(call Package/qca-legacy-uboot/nor,ap143))
#$(eval $(call Package/qca-legacy-uboot/nor,ap147-8M))
#$(eval $(call Package/qca-legacy-uboot/nor,ap147-16M))
#$(eval $(call Package/qca-legacy-uboot/nor,ap151-8M))
#$(eval $(call Package/qca-legacy-uboot/nor,ap151-16M))
#$(eval $(call Package/qca-legacy-uboot/nor,ap152-8M))
#$(eval $(call Package/qca-legacy-uboot/nor,ap152-16M))
$(eval $(call Package/qca-legacy-uboot/nor,c7v4))
$(eval $(call Package/qca-legacy-uboot/nor,wr1043nv5_eu))
