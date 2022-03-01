

ifndef PRODUCT_NAME
$(error "PRODUCT_NAME is required")
endif

CURR_DIR:=$(PWD)
ROOT_DIR:=$(PWD)/../../..

OPENWRT_SDK_DIR:=$(ROOT_DIR)/mv-openwrt-sdk
export UBOOT_DIR=$(ROOT_DIR)/mv-sdk/mv-uboot
ATF_DIR:=$(ROOT_DIR)/mv-sdk/atf
DDR_DIR:=$(ROOT_DIR)/mv-sdk/mv-ddr-marvell

UBOOT_TOOLCHAIN:=$(ROOT_DIR)/mv-openwrt-sdk/staging_dir/toolchain-aarch64_cortex-a53+neon-vfpv4_gcc-5.3.0_glibc-2.22/bin/aarch64-openwrt-linux-gnu-
export STAGING_DIR=$(ROOT_DIR)/mv-openwrt-sdk/staging_dir/toolchain-aarch64_cortex-a53+neon-vfpv4_gcc-5.3.0_glibc-2.22
export CROSS_COMPILE=$(UBOOT_TOOLCHAIN)
export BL33=$(UBOOT_DIR)/u-boot.bin

############################################################################################################################
###  uboot 

.PHONY:uboot
uboot:
	# build u-boot.bin
	$(MAKE) -C $(UBOOT_DIR) mvebu_oc300-88f7040_defconfig
	$(MAKE) -C $(UBOOT_DIR) DEVICE_TREE=armada-7040-oc300
	
	# build ATF
	$(MAKE) -C $(ATF_DIR) DEBUG=1 USE_COHERENT_MEM=0 LOG_LEVEL=20 MARVELL_SECURE_BOOT=0 PLAT=a70x0 ARM_ARCH_MAJOR=8 ARCH=aarch64 MV_DDR_PATH=$(DDR_DIR)/ all fip

############################################################################################################################
###   sdk

.PHONY:sdk_prep
sdk_prep:
	@cp $(CURR_DIR)/oc300.sdk.config $(OPENWRT_SDK_DIR)/.config
	@cp -f $(CURR_DIR)/config-4.4.52 $(OPENWRT_SDK_DIR)/target/linux/mvebu64/

.PHONY:sdk
sdk:sdk_prep
	$(MAKE) -C $(OPENWRT_SDK_DIR) V=s
