#
# Copyright (C) 2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

define Profile/TL_R470Tv6
        NAME:=TP-LINK TL-R470T+ V6
endef   
        
define Profile/TL_R470Tv6/Description
        Package set for the TP-LINK TL-R470T+ V6.
endef
$(eval $(call Profile,TL_R470Tv6))



define Profile/TL_R480Tv9
        NAME:=TP-LINK TL-R480T+ V9
endef   
        
define Profile/TL_R480Tv9/Description
        Package set for the TP-LINK TL-R480T+ V9.
endef
$(eval $(call Profile,TL_R480Tv9))


define Profile/OSG_v1
        NAME:=Omada Security Gateway(UN) 1.0
endef   
        
define Profile/OSG_v1/Description
        Package set for the Omada Security Gateway(UN) 1.0.
endef
$(eval $(call Profile,OSG_v1))