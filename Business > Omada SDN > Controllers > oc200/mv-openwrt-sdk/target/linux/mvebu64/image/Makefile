#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

define CompressGzip
	gzip -9n -c $(1) > $(2)
endef

define Image/Prepare
	cp $(KDIR)/vmlinux.elf $(BIN_DIR)/$(IMG_PREFIX)-vmlinux.elf
	$(call CompressGzip,$(KDIR)/vmlinux,$(KDIR)/vmlinux.bin.gz)
endef

# Marvell Armada-8040 development board router setup
define Image/BuildKernel/Profile/armada-a8k-8040-db
	cp $(KDIR)/Image $(BIN_DIR)/openwrt-armada-a8k-8040-db-Image
	cp $(KDIR)/Image.gz $(BIN_DIR)/openwrt-armada-a8k-8040-db-Image.gz
	cp $(DTS_DIR)/marvell/armada-8040-db-A.dtb $(BIN_DIR)/armada-a8k-8040-db-A.dtb
ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
	cp $(KDIR)/Image-initramfs $(BIN_DIR)/openwrt-armada-a8k-8040-db-Image-initramfs
endif
endef

# Marvell 8040 MACHIATOBin
define Image/BuildKernel/Profile/armada-a8k-MACHIATOBin
	cp $(KDIR)/Image $(BIN_DIR)/openwrt-armada-a8k-MACHIATOBin-Image
	cp $(KDIR)/Image.gz $(BIN_DIR)/openwrt-armada-a8k-MACHIATOBin-Image.gz
	cp $(DTS_DIR)/marvell/armada-8040-mcbin.dtb $(BIN_DIR)/armada-8040-mcbin.dtb
ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
	cp $(KDIR)/Image-initramfs $(BIN_DIR)/openwrt-armada-a8k-MACHIATOBin-Image-initramfs
endif
endef

# Marvell Armada-7040 development board router setup
define Image/BuildKernel/Profile/armada-a7k-7040-db
	cp $(KDIR)/Image $(BIN_DIR)/openwrt-armada-a7k-7040-db-Image
	cp $(KDIR)/Image.gz $(BIN_DIR)/openwrt-armada-a7k-7040-db-Image.gz
	cp $(DTS_DIR)/marvell/armada-7040-db-A.dtb $(BIN_DIR)/armada-7040-db-A.dtb
ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
	cp $(KDIR)/Image-initramfs $(BIN_DIR)/openwrt-armada-a7k-7040-db-Image-initramfs
endif
endef

# Marvell Armada 3720 Development Board DB-88F3720-DDR3
define Image/BuildKernel/Profile/armada-3720-db
	cp $(KDIR)/Image $(BIN_DIR)/openwrt-armada-3720-db-Image
	cp $(KDIR)/Image.gz $(BIN_DIR)/openwrt-armada-3720-db-Image.gz
	cp $(DTS_DIR)/marvell/armada-3720-db.dtb $(BIN_DIR)/armada-3720-db.dtb
ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
	cp $(KDIR)/Image-initramfs $(BIN_DIR)/openwrt-armada-3720-db-Image-initramfs
endif
endef

# Marvell Armada 3700 Community Board (ESPRESSObin)
define Image/BuildKernel/Profile/armada-ESPRESSObin
	cp $(KDIR)/root.squashfs $(BIN_DIR)/openwrt-armada-ESPRESSObin-root.squashfs
	cp $(KDIR)/Image $(BIN_DIR)/openwrt-armada-ESPRESSObin-Image
	cp $(KDIR)/Image.gz $(BIN_DIR)/openwrt-armada-ESPRESSObin-Image.gz
	cp $(DTS_DIR)/marvell/armada-3720-community.dtb $(BIN_DIR)/armada-3720-community.dtb
ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
	cp $(KDIR)/Image-initramfs $(BIN_DIR)/openwrt-armada-ESPRESSObin-Image-initramfs
endif
endef

# Marvell Armada 3700 Community Board (ECK)
define Image/BuildKernel/Profile/armada-eck
	cp $(KDIR)/Image $(BIN_DIR)/openwrt-armada-eck-Image
	cp $(KDIR)/Image.gz $(BIN_DIR)/openwrt-armada-eck-Image.gz
	cp $(DTS_DIR)/marvell/armada-3720-eck.dtb $(BIN_DIR)/openwrt-armada-eck.dtb
ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
	cp $(KDIR)/Image-initramfs $(BIN_DIR)/openwrt-armada-eck-Image-initramfs
endif
endef

# Marvell Armada 7040 Board (OC300)
define Image/BuildKernel/Profile/armada-oc300
	cp $(KDIR)/Image $(BIN_DIR)/openwrt-armada-oc300-Image
	cp $(KDIR)/Image.gz $(BIN_DIR)/openwrt-armada-oc300-Image.gz
	cp $(DTS_DIR)/marvell/armada-7040-oc300.dtb $(BIN_DIR)/openwrt-armada-oc300.dtb
ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
	cp $(KDIR)/Image-initramfs $(BIN_DIR)/openwrt-armada-oc300-Image-initramfs
endif
endef

define Image/Build/squashfs
    $(call prepare_generic_squashfs,$(KDIR)/root.squashfs)
	$(CP) $(KDIR)/root.squashfs $(BIN_DIR)/$(IMG_PREFIX)-root.squashfs	
endef

define Image/BuildKernel
	$(call Image/BuildKernel/Profile/$(PROFILE))
endef

define Image/Build
	$(call Image/Build/$(1))
ifeq ($(CONFIG_TARGET_ROOTFS_INITRAMFS),y)
	$(call Image/Build/Initramfs)
endif
endef

$(eval $(call BuildImage))
