#############################################################
#
# Build the jffs2 root filesystem image
#
#############################################################

JFFS2_OPTS := -e 0x10000

JFFS2_OPTS += -p 

JFFS2_OPTS += -l 

JFFS2_OPTS += -n

JFFS2_OPTS += -s 0x1000

ROOTFS_USRJFFS2_DEPENDENCIES = host-mtd

define ROOTFS_USRJFFS2_CMD
	$(HOST_DIR)/usr/sbin/mkfs.jffs2 $(JFFS2_OPTS) -d $(TARGET_DIR)/../usrfs/app -o usrapp.jffs2 &&\
	mv ./usrapp.jffs2 $(TARGET_DIR)/../images/ && \
	cp -rf $(TARGET_DIR)/../usrfs/exe/* $(TARGET_DIR)/tplink/
endef

$(eval $(call ROOTFS_TARGET,usrjffs2))
