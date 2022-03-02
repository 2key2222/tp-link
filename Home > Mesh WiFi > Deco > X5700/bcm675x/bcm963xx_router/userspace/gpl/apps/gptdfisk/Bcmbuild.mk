
gptfdisk: conditional_build 

# BRCM_SUPPORTS_MULTIARCH_BUILD

APP := gptfdisk-1.0.3
BIN := sgdisk
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))
include $(BUILD_DIR)/make.common

export LINUX_VER_STR TOOLCHAIN_PREFIX

ifneq ($(strip $(BUILD_GPTFDISK)),)
conditional_build: all
else
conditional_build:
	@echo "skipping gptfdisk (not configured)"
endif

all: check_config
	mkdir -p $(INSTALL_DIR)/bin
	$(MAKE) -C $(APP) $(BIN) CXX=$(CC) LDFLAGS="-std=gnu++98 -lstlport -lpthread -lm -L$(BCM_FSBUILD_DIR)/public/lib" CFLAGS="-std=gnu++98 -I$(BCM_FSBUILD_DIR)/public/include  -I$(BCM_FSBUILD_DIR)/public/include/stlport/" CXXFLAGS="-std=gnu++98 -I$(BCM_FSBUILD_DIR)/public/include -I$(BCM_FSBUILD_DIR)/public/include/stlport/"
	cp $(APP)/sgdisk $(INSTALL_DIR)/bin/

check_config: $(APP)/Makefile

$(APP)/Makefile: configure

configure: $(APP).tar.gz 
	(tar xkzf $(APP).tar.gz 2> /dev/null || true)
	echo "Applying patches to $(APP)" ; \
	patch -p1 -b -N -s -d$(APP) < $(APP).patch ; \
	echo "gptfdisk is untarred"

clean:
	rm -f $(INSTALL_DIR)/bin/$(BIN)
	rm -rf $(APP)

bcm_dorel_distclean: distclean

distclean: clean

shell:
	bash -i

