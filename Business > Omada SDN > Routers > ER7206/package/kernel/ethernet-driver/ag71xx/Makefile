#
# Copyright (C) 2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=ethernet
PKG_RELEASE:=1

#ifeq ("$(findstring RTL,${CONFIG_SWITCH_TYPE})", "RTL")
	CONFIG_SWITCH_VENDOR:=realtek
#else
#	CONFIG_SWITCH_VENDOR:=atheros
#endif

include $(INCLUDE_DIR)/package.mk

define KernelPackage/ethernet
  SECTION:=kernel
  CATEGORY:=$(TPLINK_CATEGORY)
  SUBMENU:=kernel modules
  TITLE:=Kernel modules for ethernet driver
  FILES:=$(PKG_BUILD_DIR)/$(CONFIG_SWITCH_VENDOR)/ag71xx/ag71xx.ko
  KCONFIG:=
  AUTOLOAD:=$(call AutoLoad,20,ag71xx)
endef

define KernelPackage/ethernet/description
 Kernel module for slp ethernet
endef

define KernelPackage/ethernet/config
  source "$(SOURCE)/Config.in"
endef

# macro for the KBuild Makefile
EXTRA_KCONFIG:= \
	CONFIG_ETHERNET=y \
	CONFIG_NET_VENDOR_ATHEROS=$(CONFIG_SWITCH_VENDOR) \
	CONFIG_AG71XX=m \
	CONFIG_AG71XX_DEBUG=n \
	CONFIG_AG71XX_DEBUG_FS=n \
	CONFIG_AG71XX_AR8216_SUPPORT=y \
	$(if $(CONFIG_ATH79_SOC_QCA9558),CONFIG_ATH79_SOC_QCA9558=y) \
	$(if $(CONFIG_ATH79_SOC_QCA9533),CONFIG_ATH79_SOC_QCA9533=y) \
	$(if $(CONFIG_ATH79_SOC_QCA9531),CONFIG_ATH79_SOC_QCA9531=y) \
	$(if $(CONFIG_ATH79_SOC_QCA9561),CONFIG_ATH79_SOC_QCA9561=y) \
	$(if $(CONFIG_ATH79_SOC_QCA9563),CONFIG_ATH79_SOC_QCA9563=y) \
	$(if $(CONFIG_RTL8367S),CONFIG_RTL8367S=y) \
	$(if $(CONFIG_RTL8370MB),CONFIG_RTL8370MB=y) \
	$(if $(CONFIG_AG71XX_SKIP_UBOOT_GMAC_INIT),CONFIG_AG71XX_SKIP_UBOOT_GMAC_INIT=y) \
	$(if $(CONFIG_AG71XX_USE_PORT0_AS_WAN),CONFIG_AG71XX_USE_PORT0_AS_WAN=y) \
	$(if $(CONFIG_AG71XX_S17_EXCHANGE_MAC06),CONFIG_AG71XX_S17_EXCHANGE_MAC06=y) \
	$(if $(CONFIG_AG71XX_DISABLE_GMAC_RXFC),CONFIG_AG71XX_DISABLE_GMAC_RXFC=y) \
	$(if $(CONFIG_AG71XX_DISABLE_GMAC_TXFC),CONFIG_AG71XX_DISABLE_GMAC_TXFC=y)
# macro for the source file
EXTRA_CFLAGS:= \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=m,%,$(filter %=m,$(EXTRA_KCONFIG)))) \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=y,%,$(filter %=y,$(EXTRA_KCONFIG)))) \
	$(if $(CONFIG_ATH79_SOC_QCA9558),-DCONFIG_ATH79_SOC_QCA9558) \
	$(if $(CONFIG_ATH79_SOC_QCA9533),-DCONFIG_ATH79_SOC_QCA9533) \
	$(if $(CONFIG_ATH79_SOC_QCA9531),-DCONFIG_ATH79_SOC_QCA9531)

ifdef CONFIG_AG71XX_PLC_CONNECTED_PORT
  ifneq ($(CONFIG_AG71XX_PLC_CONNECTED_PORT),0)
	EXTRA_CFLAGS += -DCONFIG_AG71XX_PLC_CONNECTED_PORT=$(CONFIG_AG71XX_PLC_CONNECTED_PORT)
  endif
endif

ifeq ($(CONFIG_AG71XX_LAN_WAN_PHY_SWAP),y)
	EXTRA_CFLAGS += -DAG71XX_LAN_WAN_PHY_SWAP
endif
ifeq ($(CONFIG_AG71XX_SRAM_DESCRIPTORS),y)
	EXTRA_CFLAGS += -DCONFIG_AG71XX_SRAM_DESCRIPTORS=y
endif

MAKE_OPTS:= \
	ARCH="$(LINUX_KARCH)" \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	M="$(PKG_BUILD_DIR)" \
	EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
	$(EXTRA_KCONFIG)

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
	find $(PKG_BUILD_DIR)/ -name ".svn" | xargs rm -rf
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules CONFIG_DEBUG_SECTION_MISMATCH=y
endef

$(eval $(call KernelPackage,ethernet))
