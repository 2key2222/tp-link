##############################################
#
# factory boot for failsafe.
#
##############################################


include $(TOPDIR)/rules.mk

# Build in kernel build dir
include $(INCLUDE_DIR)/kernel.mk

# Name and release number of this package
PKG_NAME:=uboot
PKG_RELEASE:=1

# This specifies the directory where we're going to build the program. 
PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)
PKG_SRC_DIR:=$(TPLINK_DIR)/package/uboot/mtk_src
COMMON_SRC_DIR:=$(TPLINK_DIR)/package/uboot/shared_libs

include $(INCLUDE_DIR)/package.mk


define Package/$(PKG_NAME)
  SECTION:=TP-LINK
  CATEGORY:=$(TPLINK_CATEGORY)
  SUBMENU:=Apps
  MAINTAINER:=TP-LINK
  TITLE:=uboot-mtk
endef

define Package/uboot/config
  source "$(TPLINK_DIR)/package/uboot/Config.in"
endef



BUILD_PARAMS_ARCH:=$(if $(CONFIG_arm),arm,mips)
BUILD_PARAMS_CPU:=$(if $(CONFIG_arm),arm,mips)

UBOOT_MAKE_OPTS:= \
    LZMA=$(STAGING_DIR_HOST)/bin/lzma \
    ARCH=$(BUILD_PARAMS_ARCH) \
    CPU=$(BUILD_PARAMS_CPU) \
    CROSS_COMPILE=$(TARGET_CROSS)


#UBOOT_IMAGE:=$(if $(IMAGE),$(IMAGE),$(PROFILE)-uboot.bin)
#UBOOT_IMAGE_COMMON:=mtk7628-uboot.bin

ifdef CONFIG_PACKAGE_MER1200v1
UBOOT_MAKE_OPTS+=CFG_PRODUCT_MER1200v1=y
UBOOT_IMAGE:=mtk7628_mer1200v1_uboot.bin
endif

ifdef CONFIG_PACKAGE_MER1200Gv1
UBOOT_MAKE_OPTS+=CFG_PRODUCT_MER1200Gv1=y
UBOOT_IMAGE:=mer1200Gv1_uboot.bin
endif

ifdef CONFIG_PACKAGE_MER2600Gv1
UBOOT_MAKE_OPTS+=CFG_PRODUCT_MER2600Gv1=y
UBOOT_IMAGE:=mer2600Gv1_uboot.bin
endif

ifdef CONFIG_PACKAGE_R478v6
UBOOT_MAKE_OPTS+=CFG_PRODUCT_R478v6=y
UBOOT_IMAGE:=mtk7628_r478v6_uboot.bin
endif

ifdef CONFIG_PACKAGE_R478pv7
UBOOT_MAKE_OPTS+=CFG_PRODUCT_R478pv7=y
UBOOT_IMAGE:=mtk7628_r478pv7_uboot.bin
endif

ifdef CONFIG_PACKAGE_R473v5
UBOOT_MAKE_OPTS+=CFG_PRODUCT_R473v5=y
UBOOT_IMAGE:=mtk7628_r473v5_uboot.bin
endif

ifdef CONFIG_PACKAGE_R483v5
UBOOT_MAKE_OPTS+=CFG_PRODUCT_R483v5=y
UBOOT_IMAGE:=mtk7628_r483v5_uboot.bin
endif

ifdef CONFIG_PACKAGE_R488v5
UBOOT_MAKE_OPTS+=CFG_PRODUCT_R488v5=y
UBOOT_IMAGE:=mtk7628_r488v5_uboot.bin
endif

ifdef CONFIG_PACKAGE_kmod-rtl8309n_ssdk
UBOOT_MAKE_OPTS+=CFG_EXTERN_SWITCH_RTL8309N=y
endif

UBOOT_SOC_TYPE:=$(if $(CONFIG_UBOOT_SOC_QCA955x)\
	,board955x,$(if $(CONFIG_UBOOT_SOC_QCA953x)\
	,board953x,$(if $(CONFIG_UBOOT_SOC_QCA956x_ap151)\
	,board956x_ap151,$(if $(CONFIG_UBOOT_SOC_QCA956x_ap152)\
	,board956x_ap152,$(if $(CONFIG_UBOOT_SOC_MT7620n)\
	,mt7620n,$(if $(CONFIG_UBOOT_SOC_MT7628)\
	,mt7628,$(if $(CONFIG_UBOOT_SOC_MT7621)\
	,mt7621,$(if $(CONFIG_UBOOT_SOC_HI3518E)\
	,hi3518e,$(if $(CONFIG_UBOOT_SOC_HI3520D)\
	,hi3520d,$(if $(CONFIG_UBOOT_SOC_ipq806x_ap148)\
	,ap148,$(if $(CONFIG_UBOOT_SOC_ipq806x_ap160)\
	,ap160)))))))))))

UBOOT_BOARD_MK_FILE:=$(TPLINK_DIR)/package/uboot/configs/$(BOARD)_$(UBOOT_SOC_TYPE).mk


ifdef CONFIG_TARGET_mtk
ifeq ($(CONFIG_UBOOT_CFG_EXTERNAL_LNA),y)
UBOOT_MAKE_OPTS+=CFG_EXTERNAL_LNA=y
endif
UBOOT_MAKE_OPTS+=$(patsubst MAKEOPTS_%,%,\
        $(filter MAKEOPTS_%,\
            $(shell cat $(UBOOT_BOARD_MK_FILE))))
ifeq ($(CONFIG_UBOOT_CFG_NO_LEDS),y)
UBOOT_MAKE_OPTS+=CFG_NO_LEDS=y
endif
UBOOT_DRAM_TYPE:=$(if $(CONFIG_UBOOT_SDR)\
	,ON_BOARD_SDR=y,$(if $(CONFIG_UBOOT_DDR1)\
	,ON_BOARD_DDR1=y,$(if $(CONFIG_UBOOT_DDR2)\
	,ON_BOARD_DDR2=y)))
UBOOT_DRAM_SIZE:=$(if $(CONFIG_UBOOT_128M_DRAM_COMPONENT)\
	,ON_BOARD_128M_DRAM_COMPONENT=y,$(if $(CONFIG_UBOOT_256M_DRAM_COMPONENT)\
	,ON_BOARD_256M_DRAM_COMPONENT=y,$(if $(CONFIG_UBOOT_512M_DRAM_COMPONENT)\
	,ON_BOARD_512M_DRAM_COMPONENT=y,$(if $(CONFIG_UBOOT_1024M_DRAM_COMPONENT)\
	,ON_BOARD_1024M_DRAM_COMPONENT=y))))
endif

ifneq ($(CONFIG_UART_GPIO_RX_TX),)
UBOOT_MAKE_OPTS+= CFG_UART_GPIO_RX_TX=$(CONFIG_UART_GPIO_RX_TX)
endif

ifneq ($(CONFIG_UBOOT_CFG_EXTRA_FW),)
UBOOT_MAKE_OPTS+=CFG_EXTRA_FW=1
endif

ifdef CONFIG_UBOOT_EXTERNAL_RESET_GPIO
ifneq ($(CONFIG_UBOOT_EXTERNAL_RESET_GPIO),-1)
UBOOT_MAKE_OPTS+=EXTERNAL_RESET_GPIO=$(CONFIG_UBOOT_EXTERNAL_RESET_GPIO)
endif
endif

ifneq ($(CONFIG_UBOOT_CFG_NO_UIP),)
UBOOT_MAKE_OPTS:=$(patsubst CONFIG_UIP=%,,$(UBOOT_MAKE_OPTS))
endif

ifeq ($(CONFIG_UBOOT_RTL_SWITCH),y)
UBOOT_MAKE_OPTS+=USING_RTL_SWITCH=y
endif

ifneq ($(CONFIG_UBOOT_GPIO_MDI),)
ifneq ($(CONFIG_UBOOT_GPIO_MDI),-1)
UBOOT_MAKE_OPTS+=GPIO_MDI=$(CONFIG_UBOOT_GPIO_MDI)
endif
endif

ifneq ($(CONFIG_UBOOT_GPIO_MDO),)
ifneq ($(CONFIG_UBOOT_GPIO_MDO),-1)
UBOOT_MAKE_OPTS+=GPIO_MDO=$(CONFIG_UBOOT_GPIO_MDO)
endif
endif

ifneq ($(CONFIG_UBOOT_GPIO_MDC),)
ifneq ($(CONFIG_UBOOT_GPIO_MDC),-1)
UBOOT_MAKE_OPTS+=GPIO_MDC=$(CONFIG_UBOOT_GPIO_MDC)
endif
endif

ifneq ($(CONFIG_UBOOT_GPIO_SWITCH_RESET),)
ifneq ($(CONFIG_UBOOT_GPIO_SWITCH_RESET),-1)
UBOOT_MAKE_OPTS+=GPIO_SWITCH_RESET=$(CONFIG_UBOOT_GPIO_SWITCH_RESET)
endif
endif

ifneq ($(IMG_FACTORY_INFO_OFFSET),)
UBOOT_MAKE_OPTS+=CFG_FACTORY_INFO_OFFSET=$(IMG_FACTORY_INFO_OFFSET)
endif

ifneq ($(IMG_RADIO_OFFSET),)
UBOOT_MAKE_OPTS+=CFG_RADIO_OFFSET=$(IMG_RADIO_OFFSET)
endif


ifdef CONFIG_TARGET_hisilicon
UBOOT_MAKE_OPTS+=$(patsubst MAKEOPTS_%,%,\
        $(filter MAKEOPTS_%,\
            $(shell cat $(UBOOT_BOARD_MK_FILE))))
endif


# Specify what needs to be done to prepare for building the package.
# In our case, we need to copy the source files to the build directory.
# This is NOT the default.  The default uses the PKG_SOURCE_URL and the
# PKG_SOURCE which is not defined here to download the source from the web.
define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(PKG_SRC_DIR)/* $(PKG_BUILD_DIR)/; \
	$(CP) $(COMMON_SRC_DIR)/* $(PKG_BUILD_DIR)/
	find $(PKG_BUILD_DIR)/ -name ".svn" | xargs rm -rf
endef


define Build/Configure
	($(foreach var,$(strip $(UBOOT_MAKE_OPTS)), export $(var);) \
		$(MAKE) -C $(PKG_BUILD_DIR) mrproper);
	$(CP) $(UBOOT_BOARD_MK_FILE) $(PKG_BUILD_DIR)/.config
	echo $(UBOOT_DRAM_TYPE) >> $(PKG_BUILD_DIR)/.config
	echo $(UBOOT_DRAM_SIZE) >> $(PKG_BUILD_DIR)/.config
	$(MAKE) -C $(PKG_BUILD_DIR) slp_config
endef


# export STAGING_DIR_HOST for lzma base path
define Build/Compile
	(export STAGING_DIR_HOST=$(STAGING_DIR_HOST); $(foreach var,$(strip $(UBOOT_MAKE_OPTS)), export $(var);) \
		$(MAKE) -C $(PKG_BUILD_DIR) all);
endef

# if COMPRESSED_UBOOT is 1, then tuboot.bin is the final binary file.
# if COMPRESSED_UBOOT is 0, then u-boot.bin is the final binary file.
# the value of the parameter "COMPRESSED_UBOOT" is got from parsing the 
# variant "UBOOT_MAKE_OPTS" which is defined above.
ifdef CONFIG_TARGET_hisilicon
	UBOOT_TOOLS_DIR:=./uboot_tools/
endif

COMPRESSED_UBOOT=$(patsubst COMPRESSED_UBOOT=%,%,$(filter COMPRESSED_UBOOT=%, $(UBOOT_MAKE_OPTS)))
ifeq ($(COMPRESSED_UBOOT),y)
COMPRESSED_UBOOT=1
endif
ifeq ($(COMPRESSED_UBOOT),1)
	UBOOT_BINARY:=tuboot.bin
else
	UBOOT_BINARY:=u-boot.bin
endif

# cp bin file to kernel build dir for firmware making
ifdef CONFIG_TARGET_hisilicon
define Build/InstallDev
	cd $(PKG_BUILD_DIR); \
	$(UBOOT_TOOLS_DIR)mkboot.sh $(UBOOT_BINARY) $(UBOOT_TOOLS_DIR)reg_info_$(UBOOT_SOC_TYPE) $(UBOOT_BINARY); \
	$(CP) $(PKG_BUILD_DIR)/$(UBOOT_BINARY) $(KERNEL_BUILD_DIR)/uboot.bin; \
	$(CP) $(PKG_BUILD_DIR)/$(UBOOT_BINARY) $(BIN_DIR)/$(UBOOT_IMAGE)
endef
else
define Build/InstallDev
	$(CP) $(PKG_BUILD_DIR)/$(UBOOT_BINARY) $(KERNEL_BUILD_DIR)/uboot.bin
	$(CP) $(PKG_BUILD_DIR)/$(UBOOT_BINARY) $(BIN_DIR)/$(UBOOT_IMAGE)
	$(CP) $(PKG_BUILD_DIR)/$(UBOOT_BINARY) $(TOPDIR)/tplink/u-boot/$(UBOOT_IMAGE)
endef
endif

$(eval $(call BuildPackage,uboot))
