
all dynamic install: conditional_build


#
# Set our CommEngine directory (by splitting the pwd into two words
# at /userspace and taking the first word only).
# Then include the common defines under CommEngine.
# You do not need to modify this part.
#
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))

include $(BUILD_DIR)/make.common

ifneq ($(strip $(BUILD_BRCM_CMS)),)
LIBS = -L$(INSTALL_DIR)/lib -lcms_msg -lcms_util -lgen_util -lbcm_util -lsys_util -lbcm_flashutil -lbcm_boardctl 
endif

ifeq ($(strip $(DESKTOP_LINUX)),y)
BCM_BLT32_FLAGS := $(BCM_LD_FLAGS)
export BCM_BLT32_FLAGS
endif

#
# Public apps are only allowed to include header files from the
# private and public directories.
#
# WARNING: Do not modify this section unless you understand the
# license implications of what you are doing.
#
ALLOWED_INCLUDE_PATHS := -I.\
                         -I$(BUILD_DIR)/userspace/public/include  \
                         -I$(BUILD_DIR)/userspace/public/include/$(OALDIR) \
                         -I$(BUILD_DIR)/userspace/private/include  \
                         -I$(BUILD_DIR)/userspace/private/include/$(OALDIR)

APP = quagga-1.2.4

clean:
	rm -f $(INSTALL_DIR)/lib/libzebra.so.1
	rm -f $(INSTALL_DIR)/bin/ripd
	rm -f $(INSTALL_DIR)/bin/zebra
	rm -rf $(APP)

# The next line is a hint to our release scripts
# GLOBAL_RELEASE_SCRIPT_CALL_DISTCLEAN
distclean: clean

#.PHONY: check_untar_patch_configure conditional_build

# Public apps are only allowed to link with libraries from the
# private and public directories.
#
# WARNING: Do not modify this section unless you understand the
# license implications of what you are doing.
#
ALLOWED_LIB_DIRS := /lib:/lib/private:/lib/public

ifneq ($(strip $(BUILD_ZEBRA)),)

check_untar_patch_configure: sanity_check
	@if [ ! -e $(APP)/Makefile ]; then \
    	echo "Untarring original $(APP) source"; \
	    (tar zxkf $(APP).tar.gz 2> /dev/null || true); \
	    (cd $(APP); patch -p1 < ../patch.quagga_cross; \
	    if [ "x$(BUILD_BRCM_CMS)" != "x" ]; then \
		patch -p1 < ../patch.quagga_cms; \
	    fi; \
	    ./configure CFLAGS="$(CFLAGS)" LDFLAGS="$(BCM_BLT32_FLAGS) -L$(INSTALL_DIR)/lib" LIBS="$(LIBS)" --host=$(TOOLCHAIN_PREFIX) \
        --target=$(TOOLCHAIN_PREFIX) \
        --enable-user=admin --enable-group=root --disable-vtysh --disable-bgpd --disable-doc --disable-ripngd \
		--disable-ospfd  --disable-ospfclient --disable-ospf6d --disable-nhrpd --disable-watchquagga --disable-isisd --disable-pimd --disable-bgp-announce \
        --prefix=/ ); \
        cd ..; \
	fi

conditional_build: check_untar_patch_configure
	cd $(APP); $(MAKE)
	install -m 755 $(APP)/ripd/.libs/ripd  $(INSTALL_DIR)/bin/ripd
	install -m 755 $(APP)/zebra/.libs/zebra $(INSTALL_DIR)/bin/zebra
	install -m 755 $(APP)/lib/.libs/libzebra.so.1.0.0 $(INSTALL_DIR)/lib/libzebra.so.1
else
conditional_build: sanity_check
	@echo "skipping $(APP) (not configured)"
endif

#
# Include the rule for making dependency files.
# The '-' in front of the second include suppresses
# error messages when make cannot find the .d files.
# It will just regenerate them.
# See Section 4.14 of Gnu Make.
#

include $(BUILD_DIR)/make.deprules

-include $(OBJS:.o=.d)



