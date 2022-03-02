
#***********************************************************************
#
#  <:copyright-BRCM:2015:DUAL/GPL:standard
#  
#     Copyright (c) 2015 Broadcom 
#     All Rights Reserved
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License, version 2, as published by
#  the Free Software Foundation (the "GPL").
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  
#  A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
#  writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
#  Boston, MA 02111-1307, USA.
#  
#  :>
#
#***********************************************************************/

EXE = wanconf
OBJS = wanconf.o wan_type_sensing.o wanconf_rdpa.o

LIBS = -lcms_util -lgen_util -lbcm_boardctl -lbcm_util -lbcm_flashutil -lsys_util

all dynamic install: conditional_build

#
# Set our CommEngine directory (by splitting the pwd into two words
# at /userspace and taking the first word only).
# Then include the common defines under CommEngine.
#
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))

include $(BUILD_DIR)/make.common

ifneq ($(strip $(BUILD_BRCM_CMS)),)
LIBS += -lcms_msg
endif

ifneq ($(strip $(BUILD_PMD)),)
CFLAGS += -DPMD_JSON_LIB
LIBS += -L$(BCM_FSBUILD_DIR)/private/lib -lpmd -L$(BCM_FSBUILD_DIR)/public/lib -ljson-c
PMD_LIB_RPATH = -Wl,-rpath,$(BCM_FSBUILD_DIR)/private/lib -Wl,-rpath,$(BCM_FSBUILD_DIR)/public/lib
endif

clean: generic_clean
	rm -f $(INSTALL_DIR)/bin/$(EXE)
	rm -f $(INSTALL_DIR)/etc/init.d/wanconf.sh
	rm -f $(INSTALL_DIR)/etc/rc3.d/S85wanconf

ifeq ($(strip $(RELEASE_BUILD)),)
	rm -f $(INSTALL_DIR)/etc/init.d/xrnd_init.sh
	rm -f $(INSTALL_DIR)/etc/rc3.d/S95xrndinit
endif
	rm -f $(EXE)
	rm -f $(OBJS)
	rm -f *.d

ifneq ($(strip $(WAN_AUTODETECT)),)	
conditional_build: $(EXE) generic_exe_install
	mkdir -p $(INSTALL_DIR)/etc/init.d
	mkdir -p $(INSTALL_DIR)/etc/rc3.d
	install scripts/wanconf.sh $(INSTALL_DIR)/etc/init.d
	(cd $(INSTALL_DIR)/etc/rc3.d; rm -f S85wanconf; ln -s ../init.d/wanconf.sh S85wanconf)

ifeq ($(strip $(RELEASE_BUILD)),)
	install scripts/xrnd_init.sh $(INSTALL_DIR)/etc/init.d
	(cd $(INSTALL_DIR)/etc/rc3.d; rm -f S95xrndinit; ln -s ../init.d/xrnd_init.sh S95xrndinit)
endif	


#
# Private apps and libs are allowed to include header files from the
# private and public directories.
#
# WARNING: Do not modify this section unless you understand the
# license implications of what you are doing.

ALLOWED_INCLUDE_PATHS := -I.\
                         -I$(BUILD_DIR)/userspace/public/include  \
                         -I$(BUILD_DIR)/userspace/public/include/$(OALDIR) \
                         -I$(BUILD_DIR)/userspace/private/include  \
                         -I$(BUILD_DIR)/userspace/private/include/$(OALDIR) \
                         -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD)  \
                         -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD)

# RDPA part
ALLOWED_INCLUDE_PATHS += -I$(PROJECT_DIR)/rdp/drivers/rdpa_gpl/include/ \
                         -I$(PROJECT_DIR)/target/bdmf/framework \
                         -I$(PROJECT_DIR)/target/bdmf/system \
                         -I$(PROJECT_DIR)/target/bdmf/system/sim \
                         -I$(PROJECT_DIR)/target/rdpa_gpl \
                         -I$(PROJECT_DIR)/target/rdpa_user \
                         -I$(PROJECT_DIR)/target/rdpa_user/include \
                         -I$(PROJECT_DIR)/target/rdpa_user/include/autogen/autogen

#
# Private apps and libs are allowed to link with libraries from the
# private and public directories.
#
# WARNING: Do not modify this section unless you understand the
# license implications of what you are doing.
#
ALLOWED_LIB_DIRS := /lib:/lib/private:/lib/public


ifeq ($(BRCM_PON_WAN_TYPE_AUTO_DETECT),y)
CFLAGS += -DPON_WAN_TYPE_AUTO_DETECT
endif
CFLAGS += -Werror -Wfatal-errors
LIBS += -lrt -lrdpactl -lbdmf

#
# Implicit rule will make the .c into a .o
# Implicit rule is $(CC) -c $(CPPFLAGS) $(CFLAGS)
# See Section 10.2 of Gnu Make manual
# 
$(EXE): $(OBJS)
	$(CC) $(BCM_LD_FLAGS) -o $@ $(OBJS) -Wl,-rpath,$(CMS_LIB_RPATH) $(CMS_LIB_PATH) $(PMD_LIB_RPATH) $(LIBS)


#
# Include the rule for making dependency files.
# The '-' in front of the second include suppresses
# error messages when make cannot find the .d files.
# It will just regenerate them.
# See Section 4.14 of Gnu Make.
#

include $(BUILD_DIR)/make.deprules

$(OBJS): wanconf.c wan_type_sensing.c wanconf_rdpa.c
	$(CC) -c $(CFLAGS) wanconf.c wan_type_sensing.c wanconf_rdpa.c -DKERNELVER=\"${LINUX_VER_STR}\"
else
conditional_build: 
	@echo "skip wanconf"
endif

-include $(OBJS:.o=.d)

