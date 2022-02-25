#
# Copyright (C) 2015 MediaTek
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/MT7623_EMMC
    NAME:=Default Profile
    PACKAGES:=\
        e2fsprogs \
        block-mount fstools \
        kmod-usb-core kmod-usb-storage \
        kmod-fs-vfat kmod-fs-ext4 kmod-fs-ntfs
endef


define Profile/MT7623_EMMC/Description
	Basic MT7623 SoC support
endef
$(eval $(call Profile,MT7623_EMMC))


