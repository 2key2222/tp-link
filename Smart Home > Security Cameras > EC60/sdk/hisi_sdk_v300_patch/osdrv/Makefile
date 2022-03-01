##########################################################################################
#	prepare param
##########################################################################################
export OSDRV_DIR=$(shell pwd)
export OSDRV_CROSS
export CHIP?=hi3516ev200
export ARCH=arm
export CROSS_COMPILE=$(OSDRV_CROSS)-
export OSDRV_CROSS_CFLAGS
export BUILD_J
export KCFLAGS
BOOT_MEDIA?=spi

ifneq ($(BOOT_MEDIA),spi)
ifneq ($(BOOT_MEDIA),emmc)
$(error you must set valid BOOT_MEDIA:spi or emmc!)
endif
endif

ifeq ($(BUILD_J), )
BUILD_J:=20
endif

ifneq ($(CHIP),hi3516ev200)
ifneq ($(CHIP),hi3516ev300)
ifneq ($(CHIP),hi3518ev300)
ifneq ($(CHIP),hi3516dv200)
$(error you must set valid CHIP:hi3516ev200 or hi3516ev300  or hi3518ev300 or hi3516dv200!)
endif
endif
endif
endif
ifeq ($(OSDRV_CROSS), )
OSDRV_CROSS=arm-himix100-linux
endif

ifeq ($(OSDRV_CROSS),arm-himix200-linux)
ifeq ($(CHIP),hi3516ev200)
$(error hi3516ev200 does not support arm-himix200-linux toolchain!)
endif
ifeq ($(CHIP),hi3518ev300)
$(error hi3518ev300 does not support arm-himix200-linux toolchain!)
endif
endif

ifeq ($(OSDRV_CROSS),arm-himix100-linux)
LIB_TYPE:=uclibc
BUSYBOX_CFG:=config_v100_a7_softfp_neon
TOOLCHAIN_DIR:=arm-himix100-linux
TOOLCHAINI_VERSION:=
RUNTIME_LIB:=runtime_uclibc
CROSS_SPECIFIED:=y
endif

ifeq ($(OSDRV_CROSS),arm-himix200-linux)
LIB_TYPE:=glibc
BUSYBOX_CFG:=config_v200_a7_softfp_neon
TOOLCHAIN_DIR:=arm-himix200-linux
TOOLCHAINI_VERSION:=
RUNTIME_LIB:=runtime_glibc
CROSS_SPECIFIED:=y
endif

BUSYBOX_VER:=busybox-1.26.2
TOOLCHAIN_RUNTIME_LIB_C:=lib.tgz

TOOLCHAIN_RUNTIME_LIB:=a7_softfp_neon-vfpv4
OSDRV_CROSS_CFLAGS:=-mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4 -w

UBOOT_VER:=u-boot-2016.11
UBOOT_TAR:=$(UBOOT_VER).tgz
UBOOT:=u-boot-$(CHIP).bin
UBOOT_REG_BIN:=reg_info_$(CHIP).bin
ifeq ($(BOOT_MEDIA),emmc)
export UBOOT_CONFIG:=$(CHIP)_$(BOOT_MEDIA)_config
else
export UBOOT_CONFIG:=$(CHIP)_config
endif

KERNEL_VER:=linux-4.9.y
KERNEL_FULL_VER:=linux-4.9.37
KERNEL_TAR:=$(KERNEL_FULL_VER).tar.gz
KERNEL_PATCH:= $(KERNEL_FULL_VER).patch

UIMAGE:=uImage_$(CHIP)
ifeq ($(BOOT_MEDIA),emmc)
export KERNEL_CFG:=$(CHIP)_$(BOOT_MEDIA)_defconfig
else
export KERNEL_CFG:=$(CHIP)_full_defconfig
endif
export PUB_IMAGE:=$(CHIP)_$(BOOT_MEDIA)_image_$(LIB_TYPE)

EXT4_TOOL:=make_ext4fs
EXT4_IMAGE_BIN:=rootfs_$(CHIP)_96M.ext4
export PUB_BOARD:=board_$(LIB_TYPE)
export PUB_ROOTFS:=rootfs_$(LIB_TYPE)

JFFS2_IMAGE_BIN_64K:=rootfs_$(CHIP)_64k.jffs2
JFFS2_IMAGE_BIN_128K:=rootfs_$(CHIP)_128k.jffs2
JFFS2_IMAGE_BIN_256K:=rootfs_$(CHIP)_256k.jffs2

YAFFS2_VER:= yaffs2utils-0.2.9
YAFFS2_TAR:=$(YAFFS2_VER).tar.gz
YAFFS_TOOL:=mkyaffs2image100
YAFFS2_IMAGE_BIN_2K_4BIT:=rootfs_$(CHIP)_2k_4bit.yaffs2
YAFFS2_IMAGE_BIN_2K_24BIT:=rootfs_$(CHIP)_2k_24bit.yaffs2
YAFFS2_IMAGE_BIN_4K_4BIT:=rootfs_$(CHIP)_4k_4bit.yaffs2
YAFFS2_IMAGE_BIN_4K_24BIT:=rootfs_$(CHIP)_4k_24bit.yaffs2

GDB_VER:= gdb-7.9.1
GDB_TAR:=$(GDB_VER).tar.gz
NCURSES_VER:= ncurses-6.0
NCURSES_TAR:=$(NCURSES_VER).tar.gz
CRAMFS_VER:= util-linux-2.31
CRAMFS_TAR:=$(CRAMFS_VER).tar.gz
XZ_VER:= xz-5.2.2
XZ_TAR:=$(XZ_VER).tar.bz2
EX2FS_VER:= e2fsprogs-1.42.13
EX2FS_TAR:=$(EX2FS_VER).tar.gz
LZO_VER:= lzo-2.09
LZO_TAR:=$(LZO_VER).tar.gz
EUDEV_VER:= eudev-3.2.7
EUDEV_TAR:=$(EUDEV_VER).tar.gz
MTD_VER:= mtd-utils-2.0.2
MTD_TAR:=$(MTD_VER).tar.bz2
PC_MTD_VER:= mtd-utils-2.0.2
PC_MTD_TAR:=$(PC_MTD_VER).tar.bz2
ZLIB_VER:= zlib-1.2.11
ZLIB_TAR:=$(ZLIB_VER).tar.gz
PC_ZLIB_VER:= zlib-1.2.11
PC_ZLIB_TAR:=$(PC_ZLIB_VER).tar.gz
FS_ZLIB_VER:= zlib-1.2.11
FS_ZLIB_TAR:=$(FS_ZLIB_VER).tar.gz
LIBUUID_VER:= libuuid-1.0.3
LIBUUID_TAR:=$(LIBUUID_VER).tar.gz
GZIP_VER:= gzip-1.8
GZIP_TAR:=$(GZIP_VER).tar.gz
SQUASHFS_VER:= squashfs4.3
SQUASHFS_TAR:=$(SQUASHFS_VER).tar.gz
EXT4_UTILS_TAR:=extras-refs_tags_android-4.1.1_r1-ext4_utils.tar.gz

HIREGBING_PACKAGE_VER:=hiregbin-v5.0.1
ifeq ($(TARGET_XLSM),)
	ifeq ($(CHIP), hi3516ev200)
TARGET_XLSM:=Hi3516EV200-DMEB_2L-DDR2_1200M_64MB_16bit.xlsm
endif
ifeq ($(CHIP), hi3516ev300)
TARGET_XLSM:=Hi3516EV300-DMEB_4L-DDR3_1800M_128MB_16bit.xlsm
endif
ifeq ($(CHIP), hi3518ev300)
TARGET_XLSM:=Hi3518EV300-DMEB_2L-DDR2_1200M_64MB_16bit.xlsm
endif
ifeq ($(CHIP), hi3516dv200)
TARGET_XLSM:=Hi3516DV200-DMEB_2L-DDR3_1800M_512MB_16bit.xlsm
endif
endif

TOOLCHAIN_FILE:= $(shell which $(OSDRV_CROSS)-gcc )
TOOLCHAIN_DIR:=$(shell dirname $(shell dirname $(TOOLCHAIN_FILE)))
#ifneq ($(OSDRV_CROSS),arm-himix100-linux)
#RUNTIMELIB_DIR=$(shell dirname $(TOOLCHAIN_DIR))/$(RUNTIME_LIB)
#else
RUNTIMELIB_DIR=$(shell dirname $(TOOLCHAIN_DIR))/$(OSDRV_CROSS)/$(RUNTIME_LIB)
#endif
##########################################################################################
#	set task
##########################################################################################
ifeq ($(CROSS_SPECIFIED),y)
all: prepare hiboot hikernel hirootfs_prepare hibusybox hipctools hiboardtools hirootfs_build
notools: hiboot hikernel hinotools_prepare hirootfs_notools_build

clean: hiboot_clean hikernel_clean \
       hibusybox_clean hipctools_clean hiboardtools_clean hirootfs_clean

distclean:clean pub_clean
endif

a:=$(shell $(OSDRV_CROSS)-gcc --version)
b:=$(findstring $(TOOLCHAINI_VERSION),$(a))
c:= $(word 2, $(a))
##########################################################################################
#task [0]	prepare
##########################################################################################
prepare:
	mkdir $(OSDRV_DIR)/pub/$(PUB_IMAGE) -p
	mkdir $(OSDRV_DIR)/pub/bin/$(PUB_BOARD) -p
	mkdir $(OSDRV_DIR)/pub/bin/pc -p

##########################################################################################
#	prepare hiregbin tools
##########################################################################################
check_hiregbin:
HIREGBING_PACKAGE = $(shell find $(OSDRV_DIR)/tools/pc/uboot_tools/ \
					-name "$(HIREGBING_PACKAGE_VER).tgz")
#$(warning $(HIREGBING_PACKAGE))

ifeq ($(HIREGBING_PACKAGE), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(HIREGBING_PACKAGE_VER).tgz package !!                 ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

##########################################################################################
#	hiregbin_prepare
##########################################################################################
hiregbin_prepare:
	@echo "---------task [0]    hiregbin_prepare"
	tar xzf $(HIREGBING_PACKAGE) -C $(OSDRV_DIR)/tools/pc/uboot_tools
	chmod 777 $(OSDRV_DIR)/tools/pc/uboot_tools/$(HIREGBING_PACKAGE_VER)/hiregbin
	cp $(OSDRV_DIR)/tools/pc/uboot_tools/$(TARGET_XLSM) $(OSDRV_DIR)/tools/pc/uboot_tools/$(HIREGBING_PACKAGE_VER)
	pushd $(OSDRV_DIR)/tools/pc/uboot_tools/$(HIREGBING_PACKAGE_VER);./hiregbin $(TARGET_XLSM) $(UBOOT_REG_BIN);popd
	mv $(OSDRV_DIR)/tools/pc/uboot_tools/$(HIREGBING_PACKAGE_VER)/$(UBOOT_REG_BIN) $(OSDRV_DIR)/tools/pc/uboot_tools
	rm $(OSDRV_DIR)/tools/pc/uboot_tools/$(HIREGBING_PACKAGE_VER) -rf

##########################################################################################
hinotools_prepare:
	pushd $(OSDRV_DIR)/pub;tar xzf $(PUB_ROOTFS).tgz;popd

hiboot_unpack:
ifneq ($(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER), $(wildcard $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER)))
	@echo "---------unpacking uboot"
	pushd $(OSDRV_DIR)/opensource/uboot;tar xzf $(UBOOT_TAR) -C .;popd
	find $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER) | xargs touch
else
	@echo "---------uboot already unpacked"
endif

##########################################################################################
#task [1]	build uboot
##########################################################################################
hiboot: prepare hiregbin_prepare hiboot_unpack
	@echo "---------task [1]	build boot"
	pushd $(OSDRV_DIR)/opensource/uboot;tar xzf secureboot_release.tgz -C .;popd
	make -C $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER) ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- distclean
	make -C $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER) ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- $(UBOOT_CONFIG)
	pushd $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER);make ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- -j $(BUILD_J) >/dev/null;popd
	make -C $(OSDRV_DIR)/tools/pc/hi_gzip/ >/dev/null
	cp $(OSDRV_DIR)/tools/pc/hi_gzip/bin/gzip $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER)/arch/arm/cpu/armv7/$(CHIP)/hw_compressed -rf
	chmod +x $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER)/arch/arm/cpu/armv7/$(CHIP)/hw_compressed/gzip
	cp $(OSDRV_DIR)/tools/pc/uboot_tools/$(UBOOT_REG_BIN) $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER)/.reg
	pushd $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER);make ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- u-boot-z.bin >/dev/null;popd
	cp $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER)/u-boot-$(CHIP).bin $(OSDRV_DIR)/pub/$(PUB_IMAGE)
	cp $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER)/u-boot-$(CHIP).bin  $(OSDRV_DIR)/opensource/uboot/secureboot_release
	pushd $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER);make ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- env >/dev/null;popd

hiboot_clean:
	rm $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER) -rf
	rm $(OSDRV_DIR)/opensource/uboot/secureboot_release -rf
	rm $(OSDRV_DIR)/tools/pc/uboot_tools/$(UBOOT_REG_BIN) -rf
	make -C $(OSDRV_DIR)/tools/pc/hi_gzip/ clean
	rm -rf $(OSDRV_DIR)/tools/pc/uboot_tools/*.bin

##########################################################################################
#	check_package :kernel and yaffs2 source file
##########################################################################################
check_package:
PACKAGE_KERNEL=$(notdir $(wildcard $(OSDRV_DIR)/opensource/kernel/*.tar.xz))
ifeq ($(PACKAGE_KERNEL), $(KERNEL_TAR))
result=$(shell xz -d $(OSDRV_DIR)/opensource/kernel/$(PACKAGE_KERNEL)\
	   && echo "pass" || "fail")
$(warning $(result))
endif
PACKAGE_KERNEL = $(shell find $(OSDRV_DIR)/opensource/kernel/ \
					-name "$(KERNEL_FULL_VER).tar*")

ifeq ($(PACKAGE_YAFFS2), $(YAFFS2_TAR))
result=$(shell echo "pass" || "fail")
$(warning $(result))
endif
PACKAGE_YAFFS2 = $(shell find $(OSDRV_DIR)/tools/pc/mkyaffs2image/ \
					-name "$(YAFFS2_TAR)")

ifeq ($(PACKAGE_GDB), $(GDB_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_NCURSES), $(NCURSES_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_CRAMFS), $(CRAMFS_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_XZ), $(XZ_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_EX2FS), $(EX2FS_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_LZO), $(LZO_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_EUDEV), $(EUDEV_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_MTD), $(MTD_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_ZLIB), $(ZLIB_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_LIBUUID), $(LIBUUID_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_GZIP), $(GZIP_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_PC_MTD), $(PC_MTD_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_PC_ZLIB), $(PC_ZLIB_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_FS_ZLIB), $(FS_ZLIB_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_SQUASHFS), $(SQUASHFS_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

ifeq ($(PACKAGE_EXT4_UTILS), $(EXT4_UTILS_TAR))
	result=$(shell echo "pass" || "fail")
	$(warning $(result))
endif

PACKAGE_GDB = $(shell find $(OSDRV_DIR)/tools/board/gdb/ -name "$(GDB_TAR)")
PACKAGE_NCURSES = $(shell find $(OSDRV_DIR)/tools/board/gdb/ -name "$(NCURSES_TAR)")
PACKAGE_CRAMFS = $(shell find $(OSDRV_DIR)/tools/pc/cramfs_tool/ -name "$(CRAMFS_TAR)")
PACKAGE_XZ = $(shell find $(OSDRV_DIR)/tools/pc/squashfs4.3/ -name "$(XZ_TAR)")
PACKAGE_EX2FS = $(shell find $(OSDRV_DIR)/tools/board/e2fsprogs/ -name "$(EX2FS_TAR)")
PACKAGE_LZO = $(shell find $(OSDRV_DIR)/tools/pc/jffs2_tool/ -name "$(LZO_TAR)")
PACKAGE_EUDEV = $(shell find $(OSDRV_DIR)/tools/board/eudev-3.2.7/ -name "$(EUDEV_TAR)")
PACKAGE_MTD = $(shell find $(OSDRV_DIR)/tools/board/mtd-utils/ -name "$(MTD_TAR)")
PACKAGE_PC_MTD = $(shell find $(OSDRV_DIR)/tools/pc/jffs2_tool -name "$(PC_MTD_TAR)")
PACKAGE_PC_ZLIB = $(shell find $(OSDRV_DIR)/tools/pc/zlib/ -name "$(PC_ZLIB_TAR)")
PACKAGE_FS_ZLIB = $(shell find $(OSDRV_DIR)/tools/pc/squashfs4.3 -name "$(FS_ZLIB_TAR)")
PACKAGE_ZLIB = $(shell find $(OSDRV_DIR)/tools/board/mtd-utils/ -name "$(ZLIB_TAR)")
PACKAGE_LIBUUID = $(shell find $(OSDRV_DIR)/tools/board/mtd-utils/ -name "$(LIBUUID_TAR)")
PACKAGE_GZIP = $(shell find $(OSDRV_DIR)/tools/pc/hi_gzip/ -name "$(GZIP_TAR)")
PACKAGE_SQUASHFS = $(shell find $(OSDRV_DIR)/tools/pc/squashfs4.3 -name "$(SQUASHFS_TAR)")
PACKAGE_EXT4_UTILS = $(shell find $(OSDRV_DIR)/tools/pc/ext4_utils -name "$(EXT4_UTILS_TAR)")

ifeq ($(PACKAGE_KERNEL), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(KERNEL_FULL_VER) source file"				 )
$(warning "  Please download the compression package to osdrv/opensource/kernel/")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_YAFFS2), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(YAFFS2_TAR)  source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/mkyaffs2image/")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_GDB), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(GDB_TAR)  source file						")
$(warning "   Please download the compression package to osdrv/tools/board/gdb/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_NCURSES), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(NCURSES_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/board/gdb/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_CRAMFS), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(CRAMFS_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/cramfs_tool/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_XZ), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(XZ_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/squashfs4.3/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_EX2FS), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(EX2FS_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/board/e2fsprogs/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_LZO), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(LZO_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/jffs2_tool/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_EUDEV), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(EUDEV_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/board/eudev-3.2.7 ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_MTD), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(MTD_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/board/mtd-utils/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_ZLIB), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(ZLIB_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/board/mtd-utils/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_LIBUUID), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(LIBUUID_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/board/mtd-utils/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_GZIP), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(GZIP_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/hi_gzip/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_PC_MTD), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(PC_MTD_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/jffs2_tool ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_PC_ZLIB), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(PC_ZLIB_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/zlib/ ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_FS_ZLIB), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(FS_ZLIB_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/squashfs4.3 ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_SQUASHFS), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(SQUASHFS_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/squashfs4.3 ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

ifeq ($(PACKAGE_EXT4_UTILS), )
$(warning "---------------------------------------------------------------------")
$(warning "     Cannot found the $(EXT4_UTILS_TAR) source file		                ")
$(warning "   Please download the compression package to osdrv/tools/pc/ext4_utils ")
$(warning "---------------------------------------------------------------------")
$(error )
endif

hikernel_unpack:
ifneq ($(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER), $(wildcard $(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER)))
	@echo "---------unpacking kernel"
	tar xf $(PACKAGE_KERNEL) -C $(OSDRV_DIR)/opensource/kernel/
	mv $(OSDRV_DIR)/opensource/kernel/$(KERNEL_FULL_VER) $(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER)
	pushd $(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER);patch -p1 < ../$(KERNEL_PATCH);popd
	find $(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER) | xargs touch
else
	@echo "---------kernel already unpacked"
endif

##########################################################################################
#task [2]	build kernel
##########################################################################################
hikernel: prepare check_package hikernel_unpack
	@echo "---------task [2] build kernel"
	#rm $(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER) -rf
	make -C $(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER) ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- $(KERNEL_CFG)

	pushd $(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER);\
		make ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- -j $(BUILD_J) >/dev/null;\
		make ARCH=arm CROSS_COMPILE=$(OSDRV_CROSS)- uImage -j $(BUILD_J) >/dev/null;popd
	cp $(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER)/arch/arm/boot/uImage $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(UIMAGE)

hikernel_clean:
	rm $(OSDRV_DIR)/opensource/kernel/$(KERNEL_VER) -rf

##########################################################################################
#task [3]	prepare rootfs 
##########################################################################################
hirootfs_prepare: prepare
	@echo "---------task [3] prepare rootfs "
	rm $(OSDRV_DIR)/pub/$(PUB_ROOTFS)* -rf
	tar xzf $(OSDRV_DIR)/rootfs_scripts/rootfs.tgz -C $(OSDRV_DIR)/pub
	mv $(OSDRV_DIR)/pub/rootfs $(OSDRV_DIR)/pub/$(PUB_ROOTFS)
	tar xzf $(RUNTIMELIB_DIR)/$(TOOLCHAIN_RUNTIME_LIB)/$(TOOLCHAIN_RUNTIME_LIB_C) -C $(OSDRV_DIR)/pub/$(PUB_ROOTFS)
	pushd $(OSDRV_DIR)/pub/$(PUB_ROOTFS);$(CROSS_COMPILE)strip -d ./lib/*;popd
#	cp -af $(OSDRV_DIR)/opensource/uboot/$(UBOOT_VER)/tools/env/fw_printenv $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/bin
#	ln -sf fw_printenv $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/bin/fw_setenv

##########################################################################################
#task [4]	build busybox 
##########################################################################################
hibusybox: prepare
	@echo "---------task [4] build busybox "
	rm $(OSDRV_DIR)/opensource/busybox/$(BUSYBOX_VER) -rf
	tar xzf $(OSDRV_DIR)/opensource/busybox/$(BUSYBOX_VER).tgz -C $(OSDRV_DIR)/opensource/busybox
	find $(OSDRV_DIR)/opensource/busybox/$(BUSYBOX_VER) | xargs touch
	cp $(OSDRV_DIR)/opensource/busybox/$(BUSYBOX_VER)/$(BUSYBOX_CFG) \
		$(OSDRV_DIR)/opensource/busybox/$(BUSYBOX_VER)/.config
	pushd $(OSDRV_DIR)/opensource/busybox/$(BUSYBOX_VER)/;make -j $(BUILD_J) >/dev/null;popd
	make -C $(OSDRV_DIR)/opensource/busybox/$(BUSYBOX_VER) install
	cp -af $(OSDRV_DIR)/opensource/busybox/$(BUSYBOX_VER)/_install/* $(OSDRV_DIR)/pub/$(PUB_ROOTFS)

hibusybox_clean:
	rm $(OSDRV_DIR)/opensource/busybox/$(BUSYBOX_VER) -rf

##########################################################################################
#task [5]	build pc tools
##########################################################################################
hipctools: prepare
	@echo "---------task [5] build tools which run on pc"
	make -C $(OSDRV_DIR)/tools/pc/mkyaffs2image/
	cp $(OSDRV_DIR)/tools/pc/mkyaffs2image/bin/$(YAFFS_TOOL) $(OSDRV_DIR)/pub/bin/pc
	make -C $(OSDRV_DIR)/tools/pc/jffs2_tool/
	cp $(OSDRV_DIR)/tools/pc/jffs2_tool/mkfs.jffs2 $(OSDRV_DIR)/pub/bin/pc
	cp $(OSDRV_DIR)/tools/pc/jffs2_tool/mkfs.ubifs $(OSDRV_DIR)/pub/bin/pc
	cp $(OSDRV_DIR)/tools/pc/jffs2_tool/ubinize $(OSDRV_DIR)/pub/bin/pc
	make -C $(OSDRV_DIR)/tools/pc/cramfs_tool/
	cp $(OSDRV_DIR)/tools/pc/cramfs_tool/mkfs.cramfs $(OSDRV_DIR)/pub/bin/pc
	make -C $(OSDRV_DIR)/tools/pc/squashfs4.3/
	cp $(OSDRV_DIR)/tools/pc/squashfs4.3/mksquashfs $(OSDRV_DIR)/pub/bin/pc
#	make -C $(OSDRV_DIR)/tools/pc/lzma_tool/
#	cp $(OSDRV_DIR)/tools/pc/lzma_tool/lzma $(OSDRV_DIR)/pub/bin/pc
	make -C $(OSDRV_DIR)/tools/pc/ext4_utils/
	cp $(OSDRV_DIR)/tools/pc/ext4_utils/bin/$(EXT4_TOOL) $(OSDRV_DIR)/pub/bin/pc
	make -C $(OSDRV_DIR)/tools/pc/nand_production/fmc_nand_ecc_product_v100
	cp $(OSDRV_DIR)/tools/pc/nand_production/fmc_nand_ecc_product_v100/nand_product $(OSDRV_DIR)/pub/bin/pc

hipctools_clean:
	make -C $(OSDRV_DIR)/tools/pc/mkyaffs2image clean
	make -C $(OSDRV_DIR)/tools/pc/jffs2_tool distclean
	make -C $(OSDRV_DIR)/tools/pc/cramfs_tool distclean
	make -C $(OSDRV_DIR)/tools/pc/squashfs4.3 distclean
#	make -C $(OSDRV_DIR)/tools/pc/lzma_tool distclean
	make -C $(OSDRV_DIR)/tools/pc/ext4_utils clean
	rm $(OSDRV_DIR)/tools/pc/uboot_tools/$(HIREGBING_PACKAGE_VER) -rf
	make -C $(OSDRV_DIR)/tools/pc/nand_production/fmc_nand_ecc_product_v100 clean

hi_reg_tools: hirootfs_prepare
	make -C $(OSDRV_DIR)/tools/board/reg-tools-1.0.0
	cp -af $(OSDRV_DIR)/tools/board/reg-tools-1.0.0/bin/* $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/bin

hi_reg_tools_clean:
	make -C $(OSDRV_DIR)/tools/board/reg-tools-1.0.0 clean

##########################################################################################
#task [6]	build board tools
##########################################################################################
hiboardtools: hirootfs_prepare hiboardtools_clean hi_reg_tools
	@echo "---------task [6] build tools which run on board "
	make -C $(OSDRV_DIR)/tools/board/e2fsprogs
	cp -af $(OSDRV_DIR)/tools/board/e2fsprogs/bin/* $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/bin
	#make -C $(OSDRV_DIR)/tools/board/reg-tools-1.0.0
	#cp -af $(OSDRV_DIR)/tools/board/reg-tools-1.0.0/bin/* $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/bin
	make -C $(OSDRV_DIR)/tools/board/eudev-3.2.7/
	cp -af $(OSDRV_DIR)/tools/board/eudev-3.2.7/rootfs/. $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/
	make -C $(OSDRV_DIR)/tools/board/gdb
	cp $(OSDRV_DIR)/tools/board/gdb/gdb-$(OSDRV_CROSS) $(OSDRV_DIR)/pub/bin/$(PUB_BOARD)
	make -C $(OSDRV_DIR)/tools/board/mtd-utils/
	cp $(OSDRV_DIR)/tools/board/mtd-utils/bin/* $(OSDRV_DIR)/pub/bin/$(PUB_BOARD)

hiboardtools_clean: hi_reg_tools_clean
	make -C $(OSDRV_DIR)/tools/board/e2fsprogs distclean
	#make -C $(OSDRV_DIR)/tools/board/reg-tools-1.0.0 clean
	make -C $(OSDRV_DIR)/tools/board/eudev-3.2.7 clean
	make -C $(OSDRV_DIR)/tools/board/gdb distclean
	make -C $(OSDRV_DIR)/tools/board/mtd-utils distclean

##########################################################################################
#task [7]	build rootfs
##########################################################################################
hirootfs_build: hirootfs_prepare hibusybox hiboardtools  hipctools hirootfs_notools_build
hirootfs_notools_build:
	@echo "---------task [7] build rootfs"
	chmod 777 $(OSDRV_DIR)/pub/bin/$(PUB_BOARD)/*
	chmod 777 $(OSDRV_DIR)/pub/bin/pc/*
	rm $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/dev/* -rf
	rm $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/bin/himm -rf
	rm $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/bin/himc -rf
	rm $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/bin/himd -rf
	rm $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/bin/himd.l -rf
	pushd $(OSDRV_DIR)/pub/$(PUB_ROOTFS);ln -s sbin/init init;popd
	pushd $(OSDRV_DIR)/pub/$(PUB_ROOTFS); chmod 750 * -R; chmod 750 usr/* -R; popd
	pushd $(OSDRV_DIR)/pub/$(PUB_ROOTFS); chmod -w usr/bin -R; chmod -w usr/sbin -R; chmod -w sbin -R; popd

ifeq ($(BOOT_MEDIA),spi)
	pushd $(OSDRV_DIR)/pub/bin/pc;./mkfs.jffs2 -d $(OSDRV_DIR)/pub/$(PUB_ROOTFS) -l -e 0x40000 -o $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(JFFS2_IMAGE_BIN_256K);popd
	pushd $(OSDRV_DIR)/pub/bin/pc;./mkfs.jffs2 -d $(OSDRV_DIR)/pub/$(PUB_ROOTFS) -l -e 0x20000 -o $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(JFFS2_IMAGE_BIN_128K);popd
	pushd $(OSDRV_DIR)/pub/bin/pc;./mkfs.jffs2 -d $(OSDRV_DIR)/pub/$(PUB_ROOTFS) -l -e 0x10000 -o $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(JFFS2_IMAGE_BIN_64K);popd

	cp $(OSDRV_DIR)/tools/pc/ubi_sh/mkubiimg.sh $(OSDRV_DIR)/pub/$(PUB_IMAGE)
	chmod +x $(OSDRV_DIR)/pub/$(PUB_IMAGE)/mkubiimg.sh
	# build the pagesize = 2k, blocksize = 128k, part_size = 32M #
	pushd $(OSDRV_DIR)/pub/$(PUB_IMAGE);./mkubiimg.sh $(CHIP) 2k 128k $(OSDRV_DIR)/pub/$(PUB_ROOTFS) 32M $(OSDRV_DIR)/pub/bin/pc;popd
	# build the pagesize = 4k, blocksize = 256k, part_size = 50M #
	pushd $(OSDRV_DIR)/pub/$(PUB_IMAGE);./mkubiimg.sh $(CHIP) 4k 256k $(OSDRV_DIR)/pub/$(PUB_ROOTFS) 50M $(OSDRV_DIR)/pub/bin/pc;popd
	rm $(OSDRV_DIR)/pub/$(PUB_IMAGE)/mkubiimg.sh
endif
ifeq ($(BOOT_MEDIA),emmc)
	pushd $(OSDRV_DIR)/pub/bin/pc;./$(EXT4_TOOL) -l 96M -s $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(EXT4_IMAGE_BIN) $(OSDRV_DIR)/pub/$(PUB_ROOTFS);popd
endif
ifeq ($(BOOT_MEDIA),spi)
	pushd $(OSDRV_DIR)/pub/bin/pc;./$(YAFFS_TOOL) $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/ $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(YAFFS2_IMAGE_BIN_2K_4BIT) 1 2;popd
	chmod 644 $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(YAFFS2_IMAGE_BIN_2K_4BIT)
	pushd $(OSDRV_DIR)/pub/bin/pc;./$(YAFFS_TOOL) $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/ $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(YAFFS2_IMAGE_BIN_2K_24BIT) 1 4;popd
	chmod 644 $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(YAFFS2_IMAGE_BIN_2K_24BIT)
	pushd $(OSDRV_DIR)/pub/bin/pc;./$(YAFFS_TOOL) $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/ $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(YAFFS2_IMAGE_BIN_4K_4BIT) 2 2;popd
	chmod 644 $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(YAFFS2_IMAGE_BIN_4K_4BIT)
	pushd $(OSDRV_DIR)/pub/bin/pc;./$(YAFFS_TOOL) $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/ $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(YAFFS2_IMAGE_BIN_4K_24BIT) 2 4;popd
	chmod 644 $(OSDRV_DIR)/pub/$(PUB_IMAGE)/$(YAFFS2_IMAGE_BIN_4K_24BIT)
endif
	find $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/ -name '*svn' | xargs rm -rf
	pushd $(OSDRV_DIR)/pub/$(PUB_ROOTFS); chmod +w usr/bin -R; chmod +w usr/sbin -R; chmod +w sbin -R; popd
	pushd $(OSDRV_DIR)/pub;tar czf $(PUB_ROOTFS).tgz $(PUB_ROOTFS);rm $(PUB_ROOTFS) -rf;popd
	@echo "---------finish osdrv work"

hirootfs_clean:
ifeq ($(OSDRV_DIR)/pub/$(PUB_ROOTFS), $(wildcard $(OSDRV_DIR)/pub/$(PUB_ROOTFS)))
	pushd $(OSDRV_DIR)/pub/$(PUB_ROOTFS); chmod +w usr/bin -R; chmod +w usr/sbin -R; chmod +w sbin -R; popd
endif
	rm $(OSDRV_DIR)/pub/$(PUB_ROOTFS)/ -rf

##########################################################################################
#task [8]	clean pub
##########################################################################################
pub_clean:
	rm $(OSDRV_DIR)/pub/* -rf

