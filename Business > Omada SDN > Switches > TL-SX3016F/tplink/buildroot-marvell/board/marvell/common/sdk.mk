################################################################################
#
# sdk
#
################################################################################

# you can override vars/cmds in tplink/sdk/sdk.mk

################################################################################
# vars/cmds
################################################################################
SDK_TARGET_DIR = $(call qstrip,$(BR2_TPLINK_SDK_TRG_DIR))
SDK_PROJECT_NAME = $(call qstrip,$(BR2_TPLINK_PROJECT_NAME))
#PP_TYPE DX_ALL PX_ALL DX/PX
SDK_SH_BUILD_PARAM += DX_ALL
#CPU & CHIPSET
SDK_SH_BUILD_PARAM += ARMv7_LK_4_4
#OPTIONAL PARAMETERS
SDK_SH_BUILD_PARAM +=  CUST NOKERNEL CPSS_LIB  UTF_NO
#TPLINK PARAMETERS
SDK_SH_BUILD_PARAM += TPLINK_$(SDK_PROJECT_NAME)
SDK_BUILD_DIR = $(SDK_TARGET_DIR)/$(SDK_PROJECT_NAME)

define SDK_BUILD_CMDS
	@echo "build sdk prev ###################################"
	if [ ! -e $(SDK_BUILD_DIR)/cpssDrvLib.a] ]; then
	export COMPILATION_ROOT=$(SDK_BUILD_DIR)
	export IMAGE_PATH=$(SDK_BUILD_DIR)
	export PATH=$$PATH:$(call qstrip,$(BR2_TOOLCHAIN_EXTERNAL_PATH))/bin
	@echo "$(PATH)"
	cd $(SDK_TARGET_DIR)
	./build_cpss.sh $(SDK_SH_BUILD_PARAM)
	cd $(OLDPWD)
	fi
	@echo "build sdk post ###################################"
endef

define SDK_INSTALL_TARGET_CMDS
	@echo "install sdk prev #################################"
	cp -a $(SDK_BUILD_DIR)/*.a  $(BR2_TPLINK_SOURCE_DIR_STRIP)/../archive/$(BR2_TPLINK_PROJECT_NAME)/
	@echo "install sdk post #################################"
endef

define SDK_CLEAN_CMDS
	rm -Rf $(SDK_BUILD_DIR)/*
endef

# can be overridden
define SDK_CONFIG_PATCH_CMDS
	:
endef


