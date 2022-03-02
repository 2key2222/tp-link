#***********************************************************************
#
#  Copyright (c) 2012  Broadcom Corporation
#  All Rights Reserved
#
#***********************************************************************/

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

APP = openvswitch-2.8.7

clean:
	rm -rf $(INSTALL_DIR)/etc/openvswitch
	rm -rf $(INSTALL_DIR)/opt/modules/openvswitch
	@if [ -e $(APP)/Makefile ]; then \
	cd $(APP); $(MAKE) clean ;$(MAKE) uninstall; \
	rm -f Makefile; \
	cd datapath/linux; $(MAKE) clean;  \
	fi

# The next line is a hint to our release scripts
# GLOBAL_RELEASE_SCRIPT_CALL_DISTCLEAN
distclean: clean
	rm -rf $(APP)

#.PHONY: check_untar_patch_configure conditional_build


ifneq ($(strip $(BUILD_OPENVSWITCH)),)

export PKG_CONFIG_LIBDIR=$(BCM_FSBUILD_DIR)/public/lib:$(BCM_FSBUILD_DIR)/gpl/lib
export PKG_CONFIG_PATH=$(BCM_FSBUILD_DIR)/public/lib/pkgconfig:$(BCM_FSBUILD_DIR)/gpl/lib/pkgconfig

ifneq ($(strip $(BRCM_OVS_SUPPORT_MCAST)),)
BCM_CFLAGS = -DCONFIG_BCM_OVS_MCAST
BCM_CPPFLAGS = -I$(CURR_DIR)/../../../../bcmdrivers/opensource/include/bcm963xx/ -I$(CURR_DIR)/../../../private/include/ -I$(CURR_DIR)/../../../public/include/
BCM_LIBS = -L$(CURR_DIR)/../../../private/libs/bcmmcast/ -lbcmmcast
else
BCM_CFLAGS = 
BCM_CPPFLAGS = 
BCM_LIBS = 
endif

ifneq ($(strip $(BRCM_OVS_SUPPORT)),)
BCM_CFLAGS += -DCONFIG_BCM_OVS
endif

check_untar_patch_configure: sanity_check
	@if [ ! -e $(APP)/.untar_complete ]; then \
    	echo "Untarring original $(APP) source"; \
	    (tar xkf $(APP).tar.gz 2> /dev/null || true); \
    		echo "Applying patches to $(APP)" ; \
		patch -p1 -b -N -s -d$(APP) < $(APP).patch ; \
		touch $(APP)/.untar_complete; \
        fi; \

conditional_build: check_untar_patch_configure
	CURRENT_ARCH=$(KERNEL_ARCH) TOOLCHAIN_TOP= $(MAKE) inner_kernelmodulebuild 
	CURRENT_ARCH=$(PROFILE_ARCH) TOOLCHAIN_TOP= $(MAKE) userspace_build 

inner_kernelmodulebuild:
		(cd $(APP); unset CFLAGS; \
		./configure --host=$(TOOLCHAIN_PREFIX) \
        --target=$(TOOLCHAIN_PREFIX) \
        --prefix=$(INSTALL_DIR) \
        --sbindir=$(INSTALL_DIR)/bin \
		--localstatedir=/var \
		--with-logdir=/var/log/openvswitch \
		--with-rundir=/var/run/openvswitch \
		--with-dbdir=/var/openvswitch \
		--with-linux=$(KERNEL_DIR) \
		--with-linux-source=$(KERNEL_DIR) \
		--datadir=$(INSTALL_DIR)/etc/openvswitch \
		--disable-maintainer-mode \
		LDFLAGS='-L$(INSTALL_DIR)/lib -L$(INSTALL_DIR)/lib/public' \
		KARCH=$(ARCH) \
		); 
	cd $(APP)/datapath/linux; $(MAKE)
	install -m 777 -d $(INSTALL_DIR)/opt/modules/openvswitch
	install -m 644 ./$(APP)/datapath/linux/openvswitch.ko  $(INSTALL_DIR)/opt/modules/openvswitch/openvswitch.ko 	
		
userspace_build:
	    (cd $(APP); unset CFLAGS; \
		./configure --host=$(TOOLCHAIN_PREFIX) \
        --target=$(TOOLCHAIN_PREFIX) \
        --prefix=$(INSTALL_DIR) \
        --sbindir=$(INSTALL_DIR)/bin \
		--localstatedir=/var \
		--with-logdir=/var/log/openvswitch \
		--with-rundir=/var/run/openvswitch \
		--with-dbdir=/var/openvswitch \
		--with-linux=$(KERNEL_DIR) \
		--with-linux-source=$(KERNEL_DIR) \
		--datadir=$(INSTALL_DIR)/etc/openvswitch \
		--disable-maintainer-mode \
		LDFLAGS='-L$(INSTALL_DIR)/lib -L$(INSTALL_DIR)/lib/public' \
		CPPFLAGS='$(BCM_CPPFLAGS)' \
		LIBS='$(BCM_LIBS)' \
		KARCH=$(ARCH) \
		CFLAGS='$(BCM_CFLAGS)' \
		); 
	cd $(APP); $(MAKE) 
	cd $(APP); $(MAKE) install-exec
	cd $(APP); $(MAKE) install-pkgdataDATA
	install -m 777 -d $(INSTALL_DIR)/etc/openvswitch/scripts	
	install -m 755 scripts/startopenVS.sh $(INSTALL_DIR)/etc/openvswitch/scripts
	install -m 755 scripts/stopopenVS.sh $(INSTALL_DIR)/etc/openvswitch/scripts
else
conditional_build: sanity_check
	@echo "skipping $(APP) (not configured)"
endif
