
rm_tmp_dir:
	@rm -rf $(TOPDIR)/tmp

tl-er7206_un_v1_config : osg_pro_un_v1_config
osg_pro_un_v1_config : rm_tmp_dir
	@if [ ! -d "$(TOPDIR)/staging_dir/toolchain-cavium-sdk-3.x" ]; then \
		echo unpacking $(TOPDIR)/dl/toolchain-cavium-sdk-3.x.tar.bz2 to $(TOPDIR)/staging_dir ; \
		mkdir -p $(TOPDIR)/staging_dir; \
		tar xjf $(TOPDIR)/dl/toolchain-cavium-sdk-3.x.tar.bz2 -C $(TOPDIR)/staging_dir; \
	fi

	@echo "prepare configs of $(subst _config,,$@) model."
	cp tplink/configs/$(subst _config,,$@)/$(subst _config,,$@).config ./.config
	cp tplink/configs/$(subst _config,,$@)/$(subst _config,,$@).kernel.config target/linux/octeon/config-3.10.49
