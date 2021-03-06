################################################################################
#
# Build the squashfs root filesystem image
#
################################################################################

ROOTFS_SQUASHFS_DEPENDENCIES = host-squashfs

ifeq ($(BR2_TARGET_ROOTFS_SQUASHFS4_LZ4),y)
ROOTFS_SQUASHFS_ARGS += -comp lz4 -Xhc
else
ifeq ($(BR2_TARGET_ROOTFS_SQUASHFS4_LZO),y)
ROOTFS_SQUASHFS_ARGS += -comp lzo
else
ifeq ($(BR2_TARGET_ROOTFS_SQUASHFS4_LZMA),y)
ROOTFS_SQUASHFS_ARGS += -comp lzma
else
ifeq ($(BR2_TARGET_ROOTFS_SQUASHFS4_XZ),y)
ROOTFS_SQUASHFS_ARGS += -comp xz
else
ROOTFS_SQUASHFS_ARGS += -comp gzip
endif
endif
endif
endif

define ROOTFS_SQUASHFS_CMD
	$(HOST_DIR)/usr/bin/mksquashfs $(TARGET_DIR)/../usrfs/image usrimage.sqfs -noappend $(ROOTFS_SQUASHFS_ARGS) &&\
	mv ./usrimage.sqfs $(TARGET_DIR)/../images/ &&\
	if [ -e $(TARGET_DIR)/../appDemo ]; then \
		mkdir -p $(TARGET_DIR)/../usrfs/image_cpss/bin; \
		mv $(TARGET_DIR)/../appDemo $(TARGET_DIR)/../usrfs/image_cpss/bin/; \
		$(HOST_DIR)/usr/bin/mksquashfs $(TARGET_DIR)/../usrfs/image_cpss cpssimage.sqfs -noappend $(ROOTFS_SQUASHFS_ARGS); \
		mv ./cpssimage.sqfs $(TARGET_DIR)/../images/; \
	fi
endef

$(eval $(call ROOTFS_TARGET,squashfs))
