#
# Copyright (C) 2009-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

img_head:=TL-ER7520Gv1_en_1.0.0
partition_table:="partition.json"
build_date:=$(shell date +%Y%m%d)
#build_time:=$(shell date +%H%M%S)
build_time:=$(shell expr $(shell date +%s) - $(shell date -d $(shell date +%x) +%s))
img_version:="$(img_head)_[$(build_date)-re$(build_time)]"
soft_version:="Build.$(build_date).Rel.$(build_time)"
boot_loader_file="$(TOPDIR)/tplink/u-boot/bootloader.bin"
#product_name:=$(shell cat $(TOPDIR)/.model)

define Image/BuildKernel
	# Workaround pre-SDK-1.9.0 u-boot versions not handling the .notes section
	$(TARGET_CROSS)strip -R .notes $(KDIR)/vmlinux.elf -o $(BIN_DIR)/$(IMG_PREFIX)-vmlinux.elf
	$(STAGING_DIR_HOST)/bin/lzma e $(BIN_DIR)/$(IMG_PREFIX)-vmlinux.elf $(BIN_DIR)/$(IMG_PREFIX)-vmlinux.lzma
	#dd if=$(KDIR)/vmlinux.bin.l7 of=$(BIN_DIR)/$(IMG_PREFIX)-vmlinux.lzma bs=65536 conv=sync
endef

define Image/Build/squashfs
    $(call prepare_generic_squashfs,$(KDIR)/root.squashfs)
endef

define Image/Build/ext4/erlite
	mkdir -p $(KDIR)/sysupgrade-erlite/
	echo "BOARD=erlite" > $(KDIR)/sysupgrade-erlite/CONTROL
	$(CP) $(KDIR)/vmlinux.elf $(KDIR)/sysupgrade-erlite/kernel
	$(CP) $(KDIR)/root.ext4 $(KDIR)/sysupgrade-erlite/root
	(cd $(KDIR); $(TAR) cvf \
		$(BIN_DIR)/$(IMG_PREFIX)-erlite-sysupgrade.tar sysupgrade-erlite)
endef

define Image/Build/ext4
    $(call Image/Build/ext4/erlite)
endef

define Image/Build/cleanup
	rm -rf $(BIN_DIR)/$(IMG_PREFIX)-upgrade*.bin
	rm -rf $(BIN_DIR)/$(img_head)*up.bin
endef

define Image/Build/TPLINK
	$(call Image/Build/cleanup)
#	$(STAGING_DIR_HOST)/bin/mktplinkfw2 -H 0x75200001 -W 1 -F 32M -V $(soft_version) -v "1.0.0" -S "0.0.0,1.0.0" -k $(BIN_DIR)/$(IMG_PREFIX)-vmlinux.elf -r $(BIN_DIR)/$(IMG_PREFIX)-root.squashfs -o $(BIN_DIR)/$(partition_table)
	#$(STAGING_DIR_HOST)/bin/mktplinkfw2 -H 0x75200001 -W 1 -F 32M -V $(soft_version) -v "1.0.0" -S "0.0.0,1.0.0" -k $(BIN_DIR)/$(IMG_PREFIX)-vmlinux.elf -r $(BIN_DIR)/$(IMG_PREFIX)-root.squashfs -o $(BIN_DIR)/$(partition_table)
	#cp $(boot_loader_file) $(BIN_DIR)/bootloader.bin
	#cd $(BIN_DIR);tar -cf $(img_version)_up.bin $(IMG_PREFIX)-vmlinux.elf $(IMG_PREFIX)-root.squashfs bootloader.bin $(partition_table)
	-cp -f $(TOPDIR)/tplink/configs/$(PRODUCT)/*.json $(BIN_DIR)/
	-cd $(BIN_DIR) && rm -f *_*flash*.bin *_up.bin && $(STAGING_DIR_HOST)/bin/dkmgt_firmware_make -b -m model.json

	cd $(BIN_DIR) ; \
	flash_bin_name=`find . -name '*_nandflash.bin' -type f | cut -c 3-` ; \
	flash_image_prefix=`find . -name '*_nandflash.bin' -type f | sed 's/_nandflash.bin//g'` ; \
	cp -f $$$${flash_image_prefix}_nandflash.bin $$$${flash_image_prefix}_nandflash_noecc.bin ; \
	nand_image_creator bch < $$$${flash_image_prefix}_nandflash_noecc.bin > $$$${flash_image_prefix}_nandflash.bin ; \
	cp -f $$$${flash_image_prefix}_oldnandflash.bin $$$${flash_image_prefix}_oldnandflash_noecc.bin ; \
	nand_image_creator default < $$$${flash_image_prefix}_oldnandflash_noecc.bin > $$$${flash_image_prefix}_oldnandflash.bin ; \
	soft_ver=`echo $$$${flash_bin_name} | grep -o -P '[0-9]\.[0-9]\.[0-9]'`; \
	soft_date=`echo $$$${flash_bin_name} | grep -o -P '[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]'`; \
	soft_time=`echo $$$${flash_bin_name} | grep -o -P 'rel[0-9][0-9][0-9][0-9][0-9]' | grep -o -P '[0-9][0-9][0-9][0-9][0-9]'`; \
	sub_dir="$$$${soft_ver} Build $$$${soft_date} Rel.$$$${soft_time}"; \
	mkdir -p $(TOPDIR)/image/$(PRODUCT)/"$$$${sub_dir}" ; \
	cp -f $(BIN_DIR)/openwrt-octeon-root.squashfs $(TOPDIR)/image/$(PRODUCT)/"$$$${sub_dir}" ; \
	cp -f $(BIN_DIR)/openwrt-octeon-vmlinux.lzma $(TOPDIR)/image/$(PRODUCT)/"$$$${sub_dir}" ; \
	if [ -f $(SCRIPT_DIR)/firmware-signature ]; then \
		$(SCRIPT_DIR)/firmware-signature *_up.bin; \
	fi; \
	cp -f $(BIN_DIR)/*.bin $(TOPDIR)/image/$(PRODUCT)/"$$$${sub_dir}"
endef

define Image/Build
	$(call Image/Build/$(1))
	dd if=$(KDIR)/root.$(1) of=$(BIN_DIR)/$(IMG_PREFIX)-root.$(1) bs=128k conv=sync
	$(call Image/Build/TPLINK)
endef

$(eval $(call BuildImage))
