################################################################################
#
# cpio to archive target filesystem
#
################################################################################

ifeq ($(BR2_ROOTFS_DEVICE_CREATION_STATIC),y)

define ROOTFS_CPIO_ADD_INIT
	if [ ! -e $(TARGET_DIR)/init ]; then \
		ln -sf sbin/init $(TARGET_DIR)/init; \
	fi
endef

else
# devtmpfs does not get automounted when initramfs is used.
# Add a pre-init script to mount it before running init
define ROOTFS_CPIO_ADD_INIT
	if [ ! -e $(TARGET_DIR)/init ]; then \
		$(INSTALL) -m 0755 fs/cpio/init $(TARGET_DIR)/init; \
	fi
endef

PACKAGES_PERMISSIONS_TABLE += /dev/console c 622 0 0 5 1 - - -$(sep)

endif # BR2_ROOTFS_DEVICE_CREATION_STATIC

ROOTFS_CPIO_PRE_GEN_HOOKS += ROOTFS_CPIO_ADD_INIT

define ROOTFS_CPIO_CMD
	cp -f $(BR2_TPLINK_SOURCE_DIR_STRIP)/monitor/shell/inittab_marvell $(TARGET_DIR)/etc/inittab &&\
	cp -ar $(BR2_TPLINK_SOURCE_DIR_STRIP)/archive/$(BR2_TPLINK_PROJECT_NAME)/usr/lib/*  $(TARGET_DIR)/tplink/lib/ &&\
	rm -rf $(TARGET_DIR)/tplink/lib/*.so $(TARGET_DIR)/tplink/lib/*.la $(TARGET_DIR)/tplink/lib/*.a &&\
	rename .0.0.0 .0 $(TARGET_DIR)/tplink/lib/*.0.0.0 &&\
	rename .0.0 .0 $(TARGET_DIR)/tplink/lib/*.0.0 &&\
	rm -f $(TARGET_DIR)/bin/dd &&\
	rm -f $(TARGET_DIR)/bin/ed &&\
	rm -f $(TARGET_DIR)/bin/egrep &&\
	rm -f $(TARGET_DIR)/bin/fgrep &&\
	rm -f $(TARGET_DIR)/bin/gzexe &&\
	rm -f $(TARGET_DIR)/bin/gzip &&\
	rm -f $(TARGET_DIR)/bin/chgrp &&\
	rm -f $(TARGET_DIR)/bin/chown &&\
	rm -f $(TARGET_DIR)/bin/iostat &&\
	rm -f $(TARGET_DIR)/bin/zcat &&\
	rm -f $(TARGET_DIR)/bin/more &&\
	rm -f $(TARGET_DIR)/sbin/halt &&\
	rm -f $(TARGET_DIR)/sbin/poweroff &&\
	rm -f $(TARGET_DIR)/sbin/route &&\
	rm -f $(TARGET_DIR)/sbin/modinfo &&\
	rm -f $(TARGET_DIR)/sbin/rmmod &&\
	rm -f $(TARGET_DIR)/usr/bin/[ &&\
	rm -f $(TARGET_DIR)/usr/bin/[[ &&\
	rm -f $(TARGET_DIR)/usr/bin/bzcat &&\
	rm -f $(TARGET_DIR)/usr/bin/bzcmp &&\
	rm -f $(TARGET_DIR)/usr/bin/bzdiff &&\
	rm -f $(TARGET_DIR)/usr/bin/bzegrep &&\
	rm -f $(TARGET_DIR)/usr/bin/bzfgrep &&\
	rm -f $(TARGET_DIR)/usr/bin/bzgrep &&\
	rm -f $(TARGET_DIR)/usr/bin/bzip2* &&\
	rm -f $(TARGET_DIR)/usr/bin/bzless &&\
	rm -f $(TARGET_DIR)/usr/bin/bzmore &&\
	rm -f $(TARGET_DIR)/usr/bin/clear &&\
	rm -f $(TARGET_DIR)/usr/bin/expand &&\
	rm -f $(TARGET_DIR)/usr/bin/expr &&\
	rm -f $(TARGET_DIR)/usr/bin/find &&\
	rm -f $(TARGET_DIR)/usr/bin/head &&\
	rm -f $(TARGET_DIR)/usr/bin/hexdump &&\
	rm -f $(TARGET_DIR)/usr/bin/hd &&\
	rm -f $(TARGET_DIR)/usr/bin/id &&\
	rm -f $(TARGET_DIR)/usr/bin/killall &&\
	rm -f $(TARGET_DIR)/usr/bin/lsusb &&\
	rm -f $(TARGET_DIR)/usr/bin/lspci &&\
	rm -f $(TARGET_DIR)/usr/bin/nc &&\
	rm -f $(TARGET_DIR)/usr/bin/nslookup &&\
	rm -f $(TARGET_DIR)/usr/bin/pci* &&\
	rm -f $(TARGET_DIR)/usr/bin/sort &&\
	rm -f $(TARGET_DIR)/usr/bin/top &&\
	rm -f $(TARGET_DIR)/usr/bin/ssh* &&\
	rm -f $(TARGET_DIR)/usr/bin/strings &&\
	rm -f $(TARGET_DIR)/usr/bin/tail &&\
	rm -f $(TARGET_DIR)/usr/bin/tee &&\
	rm -f $(TARGET_DIR)/usr/bin/test &&\
	rm -f $(TARGET_DIR)/usr/bin/tftp &&\
	rm -f $(TARGET_DIR)/usr/bin/tr &&\
	rm -f $(TARGET_DIR)/usr/bin/traceroute &&\
	rm -f $(TARGET_DIR)/usr/bin/yes	&&\
	rm -f $(TARGET_DIR)/usr/bin/vlock &&\
	rm -f $(TARGET_DIR)/usr/bin/unix2* &&\
	rm -f $(TARGET_DIR)/usr/bin/mac2unix* &&\
	rm -f $(TARGET_DIR)/usr/sbin/telnetd &&\
	rm -f $(TARGET_DIR)/usr/sbin/ip6tables* &&\
	rm -f $(TARGET_DIR)/usr/sbin/sftp &&\
	rm -f $(TARGET_DIR)/usr/sbin/sshd &&\
	rm -f $(TARGET_DIR)/lib/libthread_db* &&\
	rm -f $(TARGET_DIR)/lib/libsmartcols* &&\
	rm -f $(TARGET_DIR)/usr/lib/liblzo2* &&\
	rm -f $(TARGET_DIR)/usr/lib/libsmartcols* &&\
	rm -f $(TARGET_DIR)/usr/lib/libvx2linux* &&\
	rm -f $(TARGET_DIR)/usr/lib/libz* &&\
	cp $(TARGET_DIR)/../host/usr/arm-buildroot-linux-gnueabi/sysroot/lib/libnss_dns.so.2  $(TARGET_DIR)/lib/libnss_dns.so.2 &&\
	cp $(TARGET_DIR)/../host/usr/arm-buildroot-linux-gnueabi/sysroot/lib/libnss_dns-2.15.so  $(TARGET_DIR)/lib/libnss_dns-2.15.so&&\
	cp $(TARGET_DIR)/usr/lib/xtables/libipt_REJECT.so  $(TARGET_DIR)/usr/lib/libipt_REJECT.so &&\
	cp $(TARGET_DIR)/usr/lib/xtables/libxt_tcp.so  $(TARGET_DIR)/usr/lib/libxt_tcp.so &&\
	rm -f $(TARGET_DIR)/usr/lib/xtables/* &&\
	mv $(TARGET_DIR)/usr/lib/libipt_REJECT.so  $(TARGET_DIR)/usr/lib/xtables/libipt_REJECT.so &&\
	mv $(TARGET_DIR)/usr/lib/libxt_tcp.so  $(TARGET_DIR)/usr/lib/xtables/libxt_tcp.so &&\
	rm -f $(TARGET_DIR)/usr/libexec/* &&\
	rm -rf $(TARGET_DIR)/usr/share/locale &&\
	rm -rf $(TARGET_DIR)/../usrfs &&\
	mkdir -p $(TARGET_DIR)/../usrfs &&\
	mkdir -p $(TARGET_DIR)/../usrfs/image &&\
	mkdir -p $(TARGET_DIR)/../usrfs/app &&\
	mkdir -p $(TARGET_DIR)/../usrfs/exe &&\
	mkdir -p $(TARGET_DIR)/../usrfs/app/conf &&\
	mkdir -p $(TARGET_DIR)/../usrfs/app/log &&\
	mkdir -p $(TARGET_DIR)/../usrfs/app/data &&\
	cp -rf $(TARGET_DIR)/tplink/*  $(TARGET_DIR)/../usrfs/exe &&\
	cp -rf $(TARGET_DIR)/../usrfs/exe/data/ca.* $(TARGET_DIR)/../usrfs/app/data &&\
	cd $(TARGET_DIR)/../usrfs/exe/ && \
	cp -rf $(TARGET_DIR)/../usrfs/exe/* $(TARGET_DIR)/../usrfs/image/&&\
	rm -rf $(TARGET_DIR)/tplink/* &&\
	cd $(TARGET_DIR) && find . | cpio --quiet -o -H newc > $@
endef

$(BINARIES_DIR)/rootfs.cpio.uboot: $(BINARIES_DIR)/rootfs.cpio host-uboot-tools
	$(MKIMAGE) -A $(MKIMAGE_ARCH) -T ramdisk \
		-C none -d $<$(ROOTFS_CPIO_COMPRESS_EXT) $@

ifeq ($(BR2_TARGET_ROOTFS_CPIO_UIMAGE),y)
ROOTFS_CPIO_POST_TARGETS += $(BINARIES_DIR)/rootfs.cpio.uboot
endif

$(eval $(call ROOTFS_TARGET,cpio))
