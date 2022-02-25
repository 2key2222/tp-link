#
# Copyright (C) 2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/OSG_v1
        NAME:=Omada Security Gateway(UN) 1.0
endef   
        
define Profile/OSG_v1/Description
        Package set for the Omada Security Gateway(UN) 1.0.
endef
$(eval $(call Profile,OSG_v1))