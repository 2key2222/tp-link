#
# Basic targets for special product
#

export PLATFORM_TOOLS_DIR := $(PLATFORM_DIR)/staging_dir/host/bin
MKSQUASHFS_TOOL := $(PLATFORM_TOOLS_DIR)/mksquashfs4

sdk_path_check:
	@[ -d $(SDK_DIR)/$(SDK_NAME) ] || ln -sf ../../3516EV200_SDK $(SDK_DIR)/$(SDK_NAME)
	@[ -d $(SDK_DIR)/$(SDK_NAME) ] || { echo "please check symbol link of sdk dir !"; false; }
	@grep -rq $(SDK_VERSION) $(SDK_ROOT_DIR)/mpp/ko || {\
		echo "Pull 3516EV200_SDK to newest version !"; \
		pushd $(SDK_ROOT_DIR); git reset --hard HEAD; git clean -xdfq; git pull; popd; \
	}

toolchain: sdk_path_check
	@echo make $@ done.

firmware:
	@# clear old files
	@[ ! -d $(IMAGE_BASE_ROOTFS_DIR) ] || rm -rf $(IMAGE_BASE_ROOTFS_DIR)
	@[ ! -d $(IMAGE_SERVICE_PKG_FS_DIR) ] || rm -rf $(IMAGE_SERVICE_PKG_FS_DIR)
	@install -d $(IMAGE_BASE_ROOTFS_DIR)
	@install -d $(IMAGE_SERVICE_PKG_FS_DIR)
	@#-find $(SDK_ROOTFS_DIR) -name 'CVS' -o -name '.svn' -o -name '.#*' -o -name '*~' | xargs rm -rf
	
	@# copy kernel
	@cp -f $(SDK_IMAGE_DIR)/uImage_$(SDK_BOARD_TYPE) $(IMAGE_DIR)/uImage
			
	@# copy platform rootfs
	@cp -af $(PLATFORM_DIR)/build_dir/target-arm-openwrt-linux-uclibceabi/root-model_hisi_hi3518ev300-basefs/* $(IMAGE_BASE_ROOTFS_DIR)
	@#pushd $(IMAGE_BASE_ROOTFS_DIR);rm -rf usr/lib/opkg etc/modules.d etc/modules-boot.d etc/opkg etc/rc.button etc/uci-defaults;popd
	@cp -af $(PLATFORM_DIR)/build_dir/target-arm-openwrt-linux-uclibceabi/root-model_hisi_hi3518ev300/* $(IMAGE_SERVICE_PKG_FS_DIR)

	@# make
	@rm -rf $(IMAGE_DIR)/*.squashfs $(IMAGE_DIR)/*.jffs2
	@pushd $(IMAGE_BASE_ROOTFS_DIR)/lib/;$(TOOLCHAIN_EXPORT_PATH)/$(TOOLCHAIN_PREFIX)strip *.so*;popd
	@$(MKSQUASHFS_TOOL) $(IMAGE_BASE_ROOTFS_DIR) $(IMAGE_DIR)/rootfs.squashfs -b 64K -comp xz -noappend -all-root
	@$(MKSQUASHFS_TOOL) $(IMAGE_SERVICE_PKG_FS_DIR) $(IMAGE_DIR)/service-pkg.squashfs -b 64K -comp xz -noappend -all-root
	
sdk_makefile:
	@test ! -e $(SDK_DIR)/$(SDK_NAME)_patch/osdrv/Makefile || \
		cp -af $(SDK_DIR)/$(SDK_NAME)_patch/osdrv/Makefile $(SDK_DIR)/$(SDK_NAME)/osdrv

sdk.config: sdk_makefile hiboot_unpack
	@#cp -f $(CONFIG_DIR)/uboot.config $(SDK_UBOOT_DIR)/configs/$(SDK_BOARD_TYPE)_defconfig
	@#cp -f $(CONFIG_DIR)/uboot.xlsm $(SDK_DIR)/$(SDK_NAME)/osdrv/tools/pc/uboot_tools/$(SDK_TARGET_XLSM)

kernel.config: sdk_makefile hikernel_unpack
	@cp -f $(CONFIG_DIR)/kernel.config $(SDK_KERNEL_DIR)/arch/arm/configs/$(SDK_BOARD_TYPE)_full_defconfig

basefs.config:
	@cp -f $(CONFIG_DIR)/basefs.mk $(PLATFORM_DIR)/include/basefs.mk

sdk_patch: sdk_makefile sdk_path_check hiboot_unpack hikernel_unpack
	@[ -d $(SDK_DIR)/$(SDK_NAME)_patch ] && cp -af $(SDK_DIR)/$(SDK_NAME)_patch/* $(SDK_DIR)/$(SDK_NAME)
	@echo make $@ done.

sdk: sdk_patch hiboot hikernel hi_reg_tools;
sdk_menuconfig: menuconfig ;
sdk_clean: clean ;

