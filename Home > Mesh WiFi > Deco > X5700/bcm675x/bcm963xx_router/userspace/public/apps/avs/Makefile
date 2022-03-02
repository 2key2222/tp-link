

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

APP = avs-device-sdk-1.12

ifneq ($(strip $(BUILD_BEE)),)
INSTALL_PKG_DIR:=$(BCM_FSBUILD_DIR)/alexa
USERSPACE_DL_MODULES_BEEP_DIR=$(BUILD_DIR)/userspace/dlModules/beep
else
INSTALL_PKG_DIR:=$(INSTALL_DIR)
endif

.PHONY: install conditional_build check_versions

ifneq ($(strip $(BUILD_AVS_DEVICE_SDK)),)
conditional_build: $(APP)

else
conditional_build: sanity_check
	@echo "skipping $(APP) (not configured)"

endif

avs-device-sdk-1.12: sanity_check
	ln -f -s avs-device-sdk $(APP)
	(unzip -n -o $(APP).zip 2> /dev/null || true)
	mkdir -p $(CURR_DIR)/avs-build
	export PKG_CONFIG_LIBDIR=$(BCM_FSBUILD_DIR)/public/lib
	export PKG_CONFIG_PATH=$(BCM_FSBUILD_DIR)/public/lib/pkgconfig
	cd $(CURR_DIR)/avs-build; \
	cmake --debug-output --trace -DCMAKE_BUILD_TYPE=DEBUG \
	      -DACSDK_EMIT_SENSITIVE_LOGS=ON \
	      -DBROADCOM_TAB_KEY_DETECTOR=ON \
              -DPORTAUDIO=ON \
	      -DPORTAUDIO_LIB_PATH:PATH=$(BCM_FSBUILD_DIR)/public/lib/libportaudio.so \
	      -DPORTAUDIO_INCLUDE_DIR:PATH=$(BCM_FSBUILD_DIR)/public/include \
	      -DGSTREAMER_MEDIA_PLAYER=ON \
	      -DCMAKE_INSTALL_PREFIX:PATH=$(INSTALL_PKG_DIR) \
	      -DCMAKE_RANLIB=$(RANLIB) \
	      -DCMAKE_STRIP=$(STRIP) \
	      -DCMAKE_NM:FILEPATH=$(NM) \
	      -DCMAKE_OBJCOPY:FILEPATH=$(OBJCOPY) \
	      -DCMAKE_OBJDUMP=$(OBJDUMP) \
	      -DCMAKE_LINKER:FILEPATH=$(LD) \
	      -DCMAKE_AR:FILEPATH=$(AR) \
	      -DCMAKE_PREFIX_PATH:PATH="$(BCM_FSBUILD_DIR);$(BCM_FSBUILD_DIR)/public" \
	      -DCMAKE_FIND_ROOT_PATH:PATH="$(BCM_FSBUILD_DIR);$(BCM_FSBUILD_DIR)/public" \
	      -DCMAKE_EXE_LINKER_FLAGS:STRING="-L$(BCM_FSBUILD_DIR)/lib -L$(BCM_FSBUILD_DIR)/gpl/lib -L$(BCM_FSBUILD_DIR)/public/lib" \
	      $(CURR_DIR)/avs-device-sdk
	cd $(CURR_DIR)/avs-build; $(MAKE) CXX=$(CC)
	cd $(CURR_DIR)/avs-build; $(MAKE) -i install
	mkdir -p $(INSTALL_PKG_DIR)/share/sounds/alexa
	mkdir -p $(INSTALL_PKG_DIR)/share/alexa
	mkdir -p $(INSTALL_PKG_DIR)/etc/ssl/certs
	mkdir -p $(INSTALL_PKG_DIR)/etc/alexa
	mkdir -p $(INSTALL_PKG_DIR)/etc/alexa
	mkdir -p $(INSTALL_PKG_DIR)/usr/bin
	mkdir -p $(INSTALL_PKG_DIR)/lib
	mkdir -p $(INSTALL_PKG_DIR)/bin
	mkdir -p $(INSTALL_PKG_DIR)/dev/snd
	cp -d -f $(CURR_DIR)/avs-build/SampleApp/src/SampleApp $(INSTALL_PKG_DIR)/usr/bin
	cp -d -f $(CURR_DIR)/cert/cacert.pem $(INSTALL_PKG_DIR)/etc/ssl/certs/cert.pem
	cp -d -f $(CURR_DIR)/resource/* $(INSTALL_PKG_DIR)/share/sounds/alexa
ifneq ($(wildcard config/AlexaClientSDKConfig.json.brcm),)
	cp -d -f $(CURR_DIR)/config/Alexa*.json.brcm $(INSTALL_PKG_DIR)/share/alexa/AlexaClientSDKConfig.json
else
	cp -d -f $(CURR_DIR)/config/Alexa*.json $(INSTALL_PKG_DIR)/share/alexa
endif
	cp -d -f $(CURR_DIR)/config/asound.conf $(INSTALL_PKG_DIR)/etc
	cp -d -f $(CURR_DIR)/config/start_avs $(INSTALL_PKG_DIR)/bin
	chmod +x $(INSTALL_PKG_DIR)/bin/start_avs
	c_rehash $(INSTALL_PKG_DIR)/etc/ssl/certs
ifneq ($(strip $(BUILD_BEE)),)
#	install $(TOOLCHAIN_TOP)/usr/$(TOOLCHAIN_PREFIX)/sysroot/usr/lib/libstdc++.so.6 $(INSTALL_PKG_DIR)/lib
	$(SSTRIP) $(INSTALL_PKG_DIR)/usr/bin/* $(INSTALL_PKG_DIR)/lib/*.so* $(INSTALL_PKG_DIR)/usr/lib/*.so* $(INSTALL_PKG_DIR)/usr/lib/*/*.so*
	rm -fr $(INSTALL_PKG_DIR)/include
	tar czf avs.tar.gz -C $(INSTALL_PKG_DIR) .
	$(HOSTTOOLS_DIR)/beep/beepPkgBuilder -f avs-pkginfo.txt -d
	mv ./pkg_beep_*_*.tar.gz $(USERSPACE_DL_MODULES_BEEP_DIR)
endif

clean:
	rm -fr $(CURR_DIR)/$(APP)
	rm -fr $(CURR_DIR)/avs-build
	rm -fr $(CURR_DIR)/avs.tar.gz
	rm -fr $(INSTALL_PKG_DIR)/share/sounds/alexa
	rm -fr $(INSTALL_PKG_DIR)/share/alexa
	rm -fr $(INSTALL_PKG_DIR)/etc/ssl/certs
	rm -fr $(INSTALL_PKG_DIR)/etc/alexa
