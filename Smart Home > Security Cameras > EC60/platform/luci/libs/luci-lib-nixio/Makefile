#
# Copyright (C) 2008-2014 The LuCI Team <luci@lists.subsignal.org>
#
# This is free software, licensed under the Apache License, Version 2.0 .
#

include $(TOPDIR)/rules.mk

LUCI_TITLE:=NIXIO POSIX library
LUCI_DEPENDS:=+PACKAGE_luci-lib-nixio_openssl:libopenssl +PACKAGE_luci-lib-nixio_cyassl:libcyassl +SDK_HISI_3518E_V200:libmpp-3518e-v200 +liblua

export CONFIG_BOARD_NAME

include ../../luci.mk

# call BuildPackage - OpenWrt buildroot signature
