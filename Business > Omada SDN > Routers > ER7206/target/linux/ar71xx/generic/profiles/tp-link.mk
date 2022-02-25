#
# Copyright (C) 2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

#################################################################
####for TL-R600VPNV4
#################################################################
define Profile/TLR600VPNV4
        NAME:=TP-LINK TL-R600VPNV4
endef   
        
define Profile/TLR600VPNV4/Description
        Package set optimized for the TP-LINK TL-R600VPNV4.
endef
$(eval $(call Profile,TLR600VPNV4))

#################################################################
####for TL-ER604WV3
#################################################################
define Profile/TLER604WV3
        NAME:=TP-LINK TL-ER604WV3
        PACKAGES+=kmod-qca-wifi-perf qca-hostap qca-spectral qca-hostapd-cli qca-wpa-supplicant
endef   
        
define Profile/TLER604WV3/Description
        Package set optimized for the TP-LINK TL-ER604WV3.
endef
$(eval $(call Profile,TLER604WV3))
################################################################
