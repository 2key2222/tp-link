include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

# Name and release number of this package
PKG_NAME:=shortcut_fe
PKG_RELEASE:=1
PKG_VERSION:=1.0

PKG_SOURCE_DIR:=$(TOPDIR)/package/qca/$(PKG_NAME)/src
PKG_FILES_DIR:=$(TOPDIR)/package/qca/$(PKG_NAME)/files

MAKE_ARGS:= \
	CROSS_COMPILE="$(KERNEL_CROSS)" \
	ARCH="$(LINUX_KARCH)" \
	KLIB_BUILD="$(LINUX_DIR)" \
	SFE_SUPPORT_IPV6=1

include $(INCLUDE_DIR)/package.mk

define Package/sfe
  SECTION:=TP-LINK
  CATEGORY:=$(TPLINK_CATEGORY)
  SUBMENU:=Apps
  MAINTAINER:=TP-LINK
  TITLE:=sfe
endef

define KernelPackage/$(PKG_NAME)
	SECTION:=kernel
	CATEGORY:=$(TPLINK_CATEGORY)
	SUBMENU:=kernel modules
	TITLE:=Kernel driver for SFE
	FILES:=$(PKG_BUILD_DIR)/shortcut-fe.ko $(PKG_BUILD_DIR)/fast-classifier.ko $(PKG_BUILD_DIR)/shortcut-fe-ipv6.ko
	#AUTOLOAD:=$(call AutoLoad,96,shortcut-fe shortcut-fe-ipv6 fast-classifier.ko)
	VERSION:=$(LINUX_VERSION)
	DEPENDS:= +kmod-ppp +kmod-ipv6
	KCONFIG:=CONFIG_NF_CONNTRACK_EVENTS=y CONFIG_SHORTCUT_FE_SUPPORT=y CONFIG_NF_FASTPATH_NAT_HOOK=y
	MAINTAINER:=Lin Zhifeng
	MENU:=1
endef

define KernelPackage/$(PKG_NAME)/description
	Shortcut-FE is an in-Linux-Kernel IP packet forwarding engine.
endef

define Build/Prepare	
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(PKG_SOURCE_DIR)/* $(PKG_BUILD_DIR)/

endef

define Build/Compile/$(PKG_NAME)
	$(MAKE) -C "$(PKG_BUILD_DIR)" $(MAKE_ARGS) \
	CFLAGS="$(TARGET_CFLAGS)" \
	CONFIG_STATISTICS="$(CONFIG_PACKAGE_kmod-statistics)" \
	modules
endef

define Build/Compile
	$(call Build/Compile/$(PKG_NAME))	
endef

define Package/sfe/install
    $(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_BIN) $(PKG_FILES_DIR)/etc/config/sfe $(1)/etc/config/sfe
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_FILES_DIR)/etc/init.d/sfe $(1)/etc/init.d/sfe
	
endef

$(eval $(call BuildPackage,sfe))
$(eval $(call KernelPackage,$(PKG_NAME)))
