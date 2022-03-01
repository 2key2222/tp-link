export PRODUCT_NAME=ALL

ifndef PRODUCT_NAME

ifeq (build_product_info.tmp, $(wildcard build_product_info.tmp))
include build_product_info.tmp
else
$(warning "Usage - make PRODUCT_NAME=xxx target(s)")
$(warning "PRODUCT_NAME - NC350 NC210")
$(warning "Targets - toolchain iplatform_prep sdk iplatform firmware platform ")
$(error "PRODUCT_NAME is must required for any target building in Makefile!")
endif

else
$(shell echo "PRODUCT_NAME=$(PRODUCT_NAME)" > build_product_info.tmp)
endif

ifeq ($(CLOUD), 1)
$(warning "CLOUD is yes.")
CLOUD_INFO="-c "$(BUILD_DIR)/product_configs/$(PRODUCT_NAME)/"cloudinfo.conf"
export CLOUD
else
CLOUD_INFO=""
endif





#
# our make tool
#
SUBMAKE:=$(MAKE)

#
# path name of common dirs 
#
BUILD_DIR:=$(PWD)
CONFIG_DIR:=$(BUILD_DIR)/product_configs/$(PRODUCT_NAME)
PLATFORM_DIR:=$(BUILD_DIR)/platform
IMAGE_DIR:=$(BUILD_DIR)/image/$(PRODUCT_NAME)
TOOLCHAIN_DIR:=$(BUILD_DIR)/toolchain
SDK_DIR:=$(BUILD_DIR)/sdk

#
# basic Vars for special product
#
include $(CONFIG_DIR)/basic.config



# default target
platform:

#
# basic targets for special product
#
include $(CONFIG_DIR)/product.mk
	
	

platform: iplatform_prep sdk iplatform firmware

iplatform.config: basefs.config
	@cp -f $(CONFIG_DIR)/iplatform.config $(PLATFORM_DIR)/.config

iplatform_prep: toolchain iplatform.config iplatform_package/symlinks sdk.config kernel.config basefs.config
	
iplatform: iplatform_world

%::
	$(if $(filter iplatform_%,$@),\
		@$(SUBMAKE) -C $(PLATFORM_DIR) $(patsubst iplatform_%, %, $@),\
		@$(SUBMAKE) -C $(SDK_BUILD_DIR) $@ $(SDK_FLAGS))

.PHONY: toolchain iplatform_prep iplatform platform firmware sdk \
	iplatform.config sdk.config kernel.config 
