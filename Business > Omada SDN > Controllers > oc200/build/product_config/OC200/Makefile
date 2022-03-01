

ifndef PRODUCT_NAME
$(error "PRODUCT_NAME is required")
endif

CURR_DIR:=$(PWD)
ROOT_DIR:=$(PWD)/../../..

OPENWRT_SDK_DIR:=$(ROOT_DIR)/mv-openwrt-sdk
UBOOT_DIR:=$(ROOT_DIR)/mv-sdk/mv-uboot
ATF_DIR:=$(ROOT_DIR)/mv-sdk/atf
WTP_DIR:=$(ROOT_DIR)/mv-sdk/a3700-utils

UBOOT_TOOLCHAIN:=$(ROOT_DIR)/mv-openwrt-sdk/staging_dir/toolchain-aarch64_cortex-a53+neon-vfpv4_gcc-5.3.0_glibc-2.22/bin/aarch64-openwrt-linux-gnu-
export STAGING_DIR=$(ROOT_DIR)/mv-openwrt-sdk/staging_dir/toolchain-aarch64_cortex-a53+neon-vfpv4_gcc-5.3.0_glibc-2.22
export CROSS_COMPILE=$(UBOOT_TOOLCHAIN)
export BL33=$(UBOOT_DIR)/u-boot.bin

############################################################################################################################
###  uboot 

.PHONY:uboot
uboot:
	# build u-boot.bin
	$(MAKE) -C $(UBOOT_DIR) mvebu_eck-88f3720_defconfig
	$(MAKE) -C $(UBOOT_DIR) DEVICE_TREE=armada-3720-eck
	
	# build ATF
	$(MAKE) -C $(ATF_DIR) DEBUG=1 USE_COHERENT_MEM=0 LOG_LEVEL=20 SECURE=0 CLOCKSPRESET=CPU_1000_DDR_800 DDR_TOPOLOGY=2 BOOTDEV=SPINOR PARTNUM=0 WTP=$(WTP_DIR)/ PLAT=a3700 all fip

############################################################################################################################
###   sdk

.PHONY:sdk_prep
sdk_prep:
	@cp $(CURR_DIR)/mv.sdk.config $(OPENWRT_SDK_DIR)/.config
	@cp -f $(CURR_DIR)/config-4.4.52 $(OPENWRT_SDK_DIR)/target/linux/mvebu64/

.PHONY:sdk
sdk:sdk_prep
	$(MAKE) -C $(OPENWRT_SDK_DIR) V=s

