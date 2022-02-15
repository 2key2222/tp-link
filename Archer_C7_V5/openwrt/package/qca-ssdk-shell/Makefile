#
# Copyright (c) 2014 The Linux Foundation. All rights reserved.
#


include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=qca-ssdk-shell
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

LOCAL_VARIANT=$(patsubst qca-ssdk-shell-%,%,$(patsubst qca-ssdk-shell-%,%,$(BUILD_VARIANT)))
include $(INCLUDE_DIR)/package.mk

define Package/qca-ssdk-shell
  SECTION:=QCA
  CATEGORY:=Utilities
  TITLE:=Shell application for QCA SSDK
endef


define Package/qca-ssdk-shell/Description
  This package contains a qca-ssdk shell application for QCA chipset
endef

define Package/qca-ssdk-shell/config
	menu "qca-ssdk-shell custom configuration"

	config QCA_SSDK_SHELL_PRODUCT_CONFIG
		string "Product configuration file name."
		default "default"
		help
			All avaliable configuration files can be found under 'configs' directory of source directory.

	endmenu
endef


ifneq ($(CONFIG_PACKAGE_qca-ssdk-shell),)
	QCA_SSDK_SHELL_PRODUCT_CONFIG:=$(CONFIG_QCA_SSDK_SHELL_PRODUCT_CONFIG)
endif

ifeq ($(QCA_SSDK_SHELL_PRODUCT_CONFIG),)
	QCA_SSDK_SHELL_PRODUCT_CONFIG:=default
endif

QCASSDK_CONFIG_OPTS+= TOOL_PATH=$(TOOLCHAIN_DIR)/bin/ \
                SYS_PATH=$(LINUX_SRC_DIR) \
                SYS_BUILD_DIR=$(LINUX_DIR) \
                TOOLPREFIX=$(TARGET_CROSS) \
                KVER=$(LINUX_VERSION) \
                ARCH=$(LINUX_KARCH) \
                PRODUCT_CONFIG_FILE=$(QCA_SSDK_SHELL_PRODUCT_CONFIG)

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(strip $(QCASSDK_CONFIG_OPTS))
endef

define Package/qca-ssdk-shell/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/bin/ssdk_sh $(1)/usr/sbin/
	#$(INSTALL_DIR) $(1)/lib/iptv
	#$(INSTALL_DATA) ./filesystem/lib/iptv/*.sh $(1)/lib/iptv
endef


$(eval $(call BuildPackage,qca-ssdk-shell))
