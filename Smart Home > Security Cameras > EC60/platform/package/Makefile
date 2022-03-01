#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

curdir:=package

include $(INCLUDE_DIR)/feeds.mk

-include $(TMP_DIR)/.packagedeps
$(curdir)/builddirs:=$(sort $(package-) $(package-y) $(package-m))
$(curdir)/builddirs-install:=.
$(curdir)/builddirs-default:=. $(sort $(package-y) $(package-m))
$(curdir)/builddirs-prereq:=. $(sort $(prereq-y) $(prereq-m))
ifneq ($(IGNORE_ERRORS),)
  package-y-filter := $(package-y)
  package-m-filter := $(filter-out $(package-y),$(package-m))
  package-n-filter := $(filter-out $(package-y) $(package-m),$(package-))
  package-ignore-errors := $(filter n m y,$(IGNORE_ERRORS))
  package-ignore-errors := $(if $(package-ignore-errors),$(package-ignore-errors),n m)
  $(curdir)/builddirs-ignore-download := $(foreach m,$(package-ignore-errors),$(package-$(m)-filter))
  $(curdir)/builddirs-ignore-compile := $(foreach m,$(package-ignore-errors),$(package-$(m)-filter))
endif

ifdef CONFIG_USE_MKLIBS
  define mklibs
	rm -rf $(TMP_DIR)/mklibs-progs $(TMP_DIR)/mklibs-out
	# first find all programs and add them to the mklibs list
	find $(STAGING_DIR_ROOT) -type f -perm /100 -exec \
		file -r -N -F '' {} + | \
		awk ' /executable.*dynamically/ { print $$1 }' > $(TMP_DIR)/mklibs-progs
	# find all loadable objects that are not regular libraries and add them to the list as well
	find $(STAGING_DIR_ROOT) -type f -name \*.so\* -exec \
		file -r -N -F '' {} + | \
		awk ' /shared object/ { print $$1 }' > $(TMP_DIR)/mklibs-libs
	mkdir -p $(TMP_DIR)/mklibs-out
	$(STAGING_DIR_HOST)/bin/mklibs -D \
		-d $(TMP_DIR)/mklibs-out \
		--sysroot $(STAGING_DIR_ROOT) \
		`cat $(TMP_DIR)/mklibs-libs | sed 's:/*[^/]\+/*$$::' | uniq | sed 's:^$(STAGING_DIR_ROOT):-L :'` \
		--ldlib $(patsubst $(STAGING_DIR_ROOT)/%,/%,$(firstword $(wildcard \
			$(foreach name,ld-uClibc.so.* ld-linux.so.* ld-*.so, \
			  $(STAGING_DIR_ROOT)/lib/$(name) \
			)))) \
		--target $(REAL_GNU_TARGET_NAME) \
		`cat $(TMP_DIR)/mklibs-progs $(TMP_DIR)/mklibs-libs` 2>&1
	$(RSTRIP) $(TMP_DIR)/mklibs-out
	for lib in `ls $(TMP_DIR)/mklibs-out/*.so.* 2>/dev/null`; do \
		LIB="$${lib##*/}"; \
		DEST="`ls "$(TARGET_DIR)/lib/$$LIB" "$(TARGET_DIR)/usr/lib/$$LIB" 2>/dev/null`"; \
		[ -n "$$DEST" ] || continue; \
		echo "Copying stripped library $$lib to $$DEST"; \
		cp "$$lib" "$$DEST" || exit 1; \
	done
  endef
endif

# where to build (and put) .ipk packages
OPKG_TEMPLATE= \
  IPKG_NO_SCRIPT=1 \
  IPKG_TMP=$(TMP_DIR)/ipkg \
  IPKG_INSTROOT=$(1) \
  IPKG_CONF_DIR=$(STAGING_DIR)/etc \
  IPKG_OFFLINE_ROOT=$(1) \
  $(XARGS) $(STAGING_DIR_HOST)/bin/opkg \
	--offline-root $(1) \
	--force-depends \
	--force-overwrite \
	--force-postinstall \
	--force-maintainer \
	--add-dest root:/ \
	--add-arch all:100 \
	--add-arch $(if $(ARCH_PACKAGES),$(ARCH_PACKAGES),$(BOARD)):200

PACKAGE_INSTALL_FILES_TEMPLATE= \
	$(foreach pkg,$(sort $(1)), \
		$(foreach variant, \
			$(if $(strip $(package/$(pkg)/variants)), \
				$(package/$(pkg)/variants), \
				$(if $(package/$(pkg)/default-variant), \
					$(package/$(pkg)/default-variant), \
					default \
				) \
			), \
			$(PKG_INFO_DIR)/$(lastword $(subst /,$(space),$(pkg))).$(variant).install \
		) \
	)

ifeq ($(CONFIG_INSTALL_BASEFS),y)
  include $(INCLUDE_DIR)/basefs.mk
  package-yy:=$(sort $(package-y))
  package-y:=$(filter-out $(package-basefs),$(package-yy))
  package-basefs:=$(filter $(package-basefs),$(package-yy))
  package-basefs-volatile:=$(filter $(package-basefs-volatile),$(package-yy))
  package-y+=$(package-basefs-volatile)
  TARGET_DIR_BASEFS:=$(TARGET_DIR)-basefs
  PACKAGE_INSTALL_FILES_BASEFS:=$(call PACKAGE_INSTALL_FILES_TEMPLATE,$(package-basefs))
endif

PACKAGE_INSTALL_FILES:=$(call PACKAGE_INSTALL_FILES_TEMPLATE,$(package-y))

$(curdir)/cleanup: $(TMP_DIR)/.build
	rm -rf $(STAGING_DIR_ROOT)

define install_template
	rm -rf $(1)
	[ -d $(1)/tmp ] || mkdir -p $(1)/tmp
	@$(FIND) `sed -e 's|.*|$(PACKAGE_DIR)$(if $(CONFIG_PER_FEED_REPO),/*)/&_*.ipk|' $(2)` | sort -u | $(call OPKG_TEMPLATE,$(1)) install
	@for file in $(PACKAGE_INSTALL_FILES); do \
		[ -s $$file.flags ] || continue; \
		for flag in `cat $$file.flags`; do \
			$(OPKG) flag $$flag < $$file; \
		done; \
	done || true
	@-$(MAKE) package/preconfig
	@if [ -d $(TOPDIR)/files ]; then \
		$(call file_copy,$(TOPDIR)/files/.,$(1)); \
	fi
	@mkdir -p $(1)/etc/rc.d
	@( \
		cd $(1); \
		$(if $(CONFIG_INSTALL_BASEFS),\
			$(if $(filter $(1),$(TARGET_DIR)),\
				cp $(TARGET_DIR_BASEFS)/etc/rc.common $(1)/etc/; \
				mkdir -p $(1)/lib/functions; \
				cp $(TARGET_DIR_BASEFS)/lib/functions.sh $(1)/lib/; \
				cp $(TARGET_DIR_BASEFS)/lib/functions/service.sh $(1)/lib/functions/; \
			)\
		)\
		for script in ./usr/lib/opkg/info/*.postinst; do \
			IPKG_INSTROOT=$(1) $$(which bash) $$script; \
		done; \
		for script in ./etc/init.d/*; do \
			grep '#!/bin/sh /etc/rc.common' $$script >/dev/null || continue; \
			IPKG_INSTROOT=$(1) $$(which bash) ./etc/rc.common $$script enable; \
		done || true \
		$(if $(CONFIG_INSTALL_BASEFS),\
			$(if $(filter $(1),$(TARGET_DIR)),\
				rm $(1)/etc/rc.common; \
				rm $(1)/lib/functions.sh; \
				rm $(1)/lib/functions/service.sh; \
				rmdir --ignore-fail-on-non-empty -p $(1)/lib/functions; \
			)\
		)\
	)
	@-find $(1) -name CVS   | $(XARGS) rm -rf
	@-find $(1) -name .svn  | $(XARGS) rm -rf
	@-find $(1) -name '.#*' | $(XARGS) rm -f
	rm -f $(1)/usr/lib/opkg/info/*.postinst*
	rm -f $(1)/usr/lib/opkg/info/*.prerm*
	$(if $(CONFIG_CLEAN_IPKG),rm -rf $(1)/usr/lib/opkg)
endef

$(curdir)/install: $(TMP_DIR)/.build
	- find $(STAGING_DIR_ROOT) -type d | $(XARGS) chmod 0755
	$(if $(CONFIG_INSTALL_BASEFS),$(call install_template,$(TARGET_DIR_BASEFS),$(PACKAGE_INSTALL_FILES_BASEFS)))
	$(call install_template,$(TARGET_DIR),$(PACKAGE_INSTALL_FILES))
	$(if $(CONFIG_INSTALL_BASEFS),@(cat $(TARGET_DIR_BASEFS)/usr/lib/opkg/status \
		$(TARGET_DIR)/usr/lib/opkg/status | tee $(TARGET_DIR)/usr/lib/opkg/status))
	$(call mklibs)

PASSOPT=""
PASSARG=""
ifndef CONFIG_OPKGSMIME_PASSPHRASE
  ifneq ($(call qstrip,$(CONFIG_OPKGSMIME_PASSFILE)),)
    PASSOPT="-passin"
    PASSARG="file:$(call qstrip,$(CONFIG_OPKGSMIME_PASSFILE))"
  endif
endif

PACKAGE_SUBDIRS=.
ifneq ($(CONFIG_PER_FEED_REPO),)
  ifneq ($(CONFIG_PER_FEED_REPO_ADD_DISABLED),)
    PACKAGE_SUBDIRS=base $(FEEDS_AVAILABLE)
  else
    PACKAGE_SUBDIRS=base $(FEEDS_ENABLED)
  endif
endif

$(curdir)/index: FORCE
	@echo Generating package index...
	@for d in $(PACKAGE_SUBDIRS); do ( \
		mkdir -p $(PACKAGE_DIR)/$$d; \
		cd $(PACKAGE_DIR)/$$d || continue; \
		$(SCRIPT_DIR)/ipkg-make-index.sh . 2>&1 > Packages && \
			gzip -9c Packages > Packages.gz; \
	); done
ifdef CONFIG_SIGNED_PACKAGES
	@echo Signing package index...
	@for d in $(PACKAGE_SUBDIRS); do ( \
		[ -d $(PACKAGE_DIR)/$$d ] && \
			cd $(PACKAGE_DIR)/$$d || continue; \
		$(STAGING_DIR_HOST)/bin/usign -S -m Packages -s $(BUILD_KEY); \
	); done
else
ifeq ($(call qstrip,$(CONFIG_OPKGSMIME_KEY)),)
	@echo Signing key has not been configured
else
ifeq ($(call qstrip,$(CONFIG_OPKGSMIME_CERT)),)
	@echo Certificate has not been configured
else
	@echo Signing package index...
	@for d in $(PACKAGE_SUBDIRS); do ( \
		[ -d $(PACKAGE_DIR)/$$d ] && \
			cd $(PACKAGE_DIR)/$$d || continue; \
		openssl smime -binary -in Packages.gz \
			-out Packages.sig -outform PEM -sign \
			-signer $(CONFIG_OPKGSMIME_CERT) \
			-inkey $(CONFIG_OPKGSMIME_KEY) \
			$(PASSOPT) $(PASSARG); \
	); done
endif
endif
endif

$(curdir)/preconfig:

$(curdir)/flags-install:= -j1

$(eval $(call stampfile,$(curdir),package,prereq,.config))
$(eval $(call stampfile,$(curdir),package,cleanup,$(TMP_DIR)/.build))
$(eval $(call stampfile,$(curdir),package,compile,$(TMP_DIR)/.build))
$(eval $(call stampfile,$(curdir),package,install,$(TMP_DIR)/.build))

$(eval $(call subdir,$(curdir)))
