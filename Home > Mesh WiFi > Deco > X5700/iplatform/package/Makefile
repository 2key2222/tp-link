#
# Copyright (C) 2006-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

curdir:=package

-include $(TMP_DIR)/.packagedeps
$(curdir)/builddirs:=$(sort $(package-) $(package-y) $(package-m))
ifeq ($(SDK),1)
  $(curdir)/builddirs-install:=.
else
  $(curdir)/builddirs-default:=. $(sort $(package-y) $(package-m))
  $(curdir)/builddirs-prereq:=. $(sort $(prereq-y) $(prereq-m))
  $(curdir)/builddirs-install:=. $(filter-out base-files,$(sort $(package-y))) $(filter base-files,$(package-y))
endif
ifneq ($(IGNORE_ERRORS),)
  $(curdir)/builddirs-ignore-compile:= $(if $(filter n m y, $(IGNORE_ERRORS)),$(foreach m,$(IGNORE_ERRORS),$(package-$(subst n,,$(m)))),$(package-m) $(package-))
endif

$(curdir)/install:=$(curdir)/install-cleanup

$(curdir)/cleanup: $(TMP_DIR)/.build
	- find $(STAGING_DIR_ROOT) -type d | $(XARGS) chmod 0755
	rm -rf $(TARGET_DIR) $(STAGING_DIR_ROOT)

ifdef CONFIG_USE_MKLIBS
  define mklibs
	rm -rf $(TMP_DIR)/mklibs-progs $(TMP_DIR)/mklibs-out
	# first find all programs and add them to the mklibs list
	find $(STAGING_DIR_ROOT) -type f -perm +100 -exec \
		file -r -N -F '' {} + | \
		awk ' /executable.*dynamically/ { print $$1 }' > $(TMP_DIR)/mklibs-progs
	# find all loadable objects that are not regular libraries and add them to the list as well
	find $(STAGING_DIR_ROOT) -type f -name \*.so\* -exec \
		file -r -N -F '' {} + | \
		awk ' /shared object/ { print $$1 }' >> $(TMP_DIR)/mklibs-progs
	mkdir -p $(TMP_DIR)/mklibs-out
	$(STAGING_DIR_HOST)/bin/mklibs -D \
		-d $(TMP_DIR)/mklibs-out \
		--sysroot $(STAGING_DIR_ROOT) \
		-L /lib \
		-L /usr/lib \
		-L /usr/lib/ebtables \
		--ldlib $(patsubst $(STAGING_DIR_ROOT)/%,/%,$(firstword $(wildcard \
			$(foreach name,ld-uClibc.so.* ld-linux.so.* ld-*.so, \
			  $(STAGING_DIR_ROOT)/lib/$(name) \
			)))) \
		--target $(REAL_GNU_TARGET_NAME) \
		`cat $(TMP_DIR)/mklibs-progs` 2>&1
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

define push_git_build_stats
	GIT_CONFIG="--git-dir=$(BIN_DIR)/manifest/.git --work-tree=$(BIN_DIR)/manifest"; \
	[ -e "$(BIN_DIR)/manifest/.git" ] || { \
		  git $${GIT_CONFIG} init; \
	}; \
	git $${GIT_CONFIG} remote add origin $(CONFIG_GIT_BUILD_STATS_REPO); \
	git $${GIT_CONFIG} fetch --all; \
	git $${GIT_CONFIG} reset origin/$(CONFIG_GIT_BUILD_STATS_BRANCH); \
	git $${GIT_CONFIG} add manifest.txt; \
	git $${GIT_CONFIG} commit -asm "build on $$(date)"; \
	git $${GIT_CONFIG} push origin HEAD:$(CONFIG_GIT_BUILD_STATS_BRANCH);
endef

# where to build (and put) .ipk packages

PKG_INFO_DIR := $(STAGING_DIR)/pkginfo

OPKG:= \
  IPKG_NO_SCRIPT=1 \
  IPKG_TMP=$(TMP_DIR)/ipkg \
  IPKG_INSTROOT=$(TARGET_DIR) \
  IPKG_CONF_DIR=$(STAGING_DIR)/etc \
  IPKG_OFFLINE_ROOT=$(TARGET_DIR) \
  $(XARGS) $(STAGING_DIR_HOST)/bin/opkg \
	--offline-root $(TARGET_DIR) \
	--force-depends \
	--force-overwrite \
	--force-postinstall \
	--force-maintainer \
	--add-dest root:/ \
	--add-arch all:100 \
	--add-arch $(if $(ARCH_PACKAGES),$(ARCH_PACKAGES),$(BOARD)):200

PACKAGE_INSTALL_FILES:= \
	$(foreach pkg,$(sort $(package-y)), \
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

$(curdir)/rootfs-prepare: $(TMP_DIR)/.build
	- find $(STAGING_DIR_ROOT) -type d | $(XARGS) chmod 0755
	rm -rf $(TARGET_DIR)
	[ -d $(TARGET_DIR)/tmp ] || mkdir -p $(TARGET_DIR)/tmp
	@$(FIND) `sed -e 's|.*|$(PACKAGE_DIR)/&_*.ipk|' $(PACKAGE_INSTALL_FILES)` | sort -u | $(OPKG) install
	@for file in $(PACKAGE_INSTALL_FILES); do \
		[ -s $$file.flags ] || continue; \
		for flag in `cat $$file.flags`; do \
			$(OPKG) flag $$flag < $$file; \
		done; \
	done || true

	@-$(MAKE) package/preconfig
	@if [ -d $(TOPDIR)/files ]; then \
               ( cd $(TOPDIR)/files; find -type f ) | \
                       ( cd $(TARGET_DIR); while :; do \
                               read FILE; \
                               [ -z "$$FILE" ] && break; \
                               [ -L "$$FILE" ] || continue; \
                               echo "Removing symlink $(TARGET_DIR)/$$FILE"; \
                               rm -f "$$FILE"; \
                       done; ); \
               $(CP) $(TOPDIR)/files/. $(TARGET_DIR); \
	fi
	@mkdir -p $(TARGET_DIR)/etc/rc.d
	@( \
		cd $(TARGET_DIR); \
		for script in ./usr/lib/opkg/info/*.postinst; do \
			IPKG_INSTROOT=$(TARGET_DIR) $$(which bash) $$script; \
		done; \
		for script in ./etc/init.d/*; do \
			grep '#!/bin/sh /etc/rc.common' $$script >/dev/null || continue; \
			IPKG_INSTROOT=$(TARGET_DIR) $$(which bash) ./etc/rc.common $$script enable; \
		done || true \
	)
	@-find $(TARGET_DIR) -name CVS   | $(XARGS) rm -rf
	@-find $(TARGET_DIR) -name .svn  | $(XARGS) rm -rf
	@-find $(TARGET_DIR) -name '.#*' | $(XARGS) rm -f
#	rm -f $(TARGET_DIR)/usr/lib/opkg/info/*.postinst

	mkdir -p $(BIN_DIR)/manifest
	OPKG_T="$(STAGING_DIR_HOST)/bin/opkg \
		--offline-root=$(TARGET_DIR) \
		--add-arch $(if $(ARCH_PACKAGES),$(ARCH_PACKAGES),$(BOARD)):200 \
		--add-arch all:100"; \
	pkgs="`$${OPKG_T} list-installed | awk '{print $$1}'`"; \
	for pkg in $${pkgs}; do \
		$${OPKG_T} info $${pkg} | grep -v Installed-Time; \
		f=$$($${OPKG_T} files $${pkg} | sort | grep ^/); \
		[ -n "$$f" ] && { du -ch $$f | sed 's,$(TARGET_DIR),,g'; echo; } \
	done > $(BIN_DIR)/manifest/manifest.txt

	$(if $(CONFIG_GIT_BUILD_STATS_REPO),$(call push_git_build_stats))

	rm -rf $(TARGET_DIR)/usr/lib/opkg
	$(call mklibs)

$(curdir)/index: FORCE
	@(cd $(PACKAGE_DIR); $(SCRIPT_DIR)/ipkg-make-index.sh . 2>&1 > Packages && \
		gzip -9c Packages > Packages.gz \
	)

$(curdir)/flags-install:= -j1

$(eval $(call stampfile,$(curdir),package,prereq,.config))
$(eval $(call stampfile,$(curdir),package,cleanup,$(TMP_DIR)/.build))
$(eval $(call stampfile,$(curdir),package,compile,$(TMP_DIR)/.build))
$(eval $(call stampfile,$(curdir),package,install,$(TMP_DIR)/.build))
$(eval $(call stampfile,$(curdir),package,rootfs-prepare,$(TMP_DIR)/.build))

$(eval $(call subdir,$(curdir)))
