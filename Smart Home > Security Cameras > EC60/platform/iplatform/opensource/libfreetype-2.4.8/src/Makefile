#****************************************************************************
#    Copyright (C), 2016-xxx, TP-LINK
# 
#    File Name    : Makefile
#    Version      : 1.0
#    Author       : liziliang
#    Created      : 2016-04-14
#****************************************************************************/
CONFIGDIR := freetype-2.4.8/builds/unix
SUBDIRS := freetype-2.4.8
CURDIR_PATH := $(shell pwd)

CONFIGURE_ARGS := --enable-shared
CONFIGURE_ARGS += CC=$(CONFIG_TOOLCHAIN_PREFIX)gcc
CONFIGURE_ARGS += LD=$(CONFIG_TOOLCHAIN_PREFIX)ld
CONFIGURE_ARGS += CFLAGS=-I$(CONFIG_TOOLCHAIN_ROOT)/usr/include/
CONFIGURE_ARGS += "CXXFLAGS= -O2 -I$(CONFIG_TOOLCHAIN_ROOT)/usr/include/"
CONFIGURE_ARGS += LDFLAGS=-L$(CONFIG_TOOLCHAIN_ROOT)/usr/lib/

STRIP := $(CONFIG_TOOLCHAIN_PREFIX)strip

CONFIGURE_ARGS += '--target=arm-openwrt-linux-uclibc' '--host=arm-openwrt-linux-uclibc' '--build=i686-linux-gnu' '--program-prefix=' '--program-suffix=' '--prefix=/usr' '--exec-prefix=/usr' '--bindir=/usr/bin' '--sbindir=/usr/sbin' '--libexecdir=/usr/lib' '--sysconfdir=/etc' '--datadir=/usr/share' '--localstatedir=/var' '--mandir=/usr/man' '--infodir=/usr/info' '--enable-shared'
CONFIGURE_ARGS += '--with-png=no'
CONFIGURE_ARGS += '--with-zlib=no'

# ifeq ($(CONFIG_TOOLCHAIN_PREFIX) , "arm-hisiv100nptl-linux-")
# CONFIGURE_ARGS += --host=arm-hisiv100nptl-linux
# else ifeq ($(CONFIG_TOOLCHAIN_PREFIX),"arm-hisiv300-linux-")
# CONFIGURE_ARGS += --host=arm-hisiv300-linux
# else ifeq ($(CONFIG_TOOLCHAIN_PREFIX),"mipsel-openwrt-linux-")
# CONFIGURE_ARGS += --host=mipsel-openwrt-linux
# endif



all:
	@echo =======CONFIGURE_ARGS:$(CONFIGURE_ARGS)
	cd $(CONFIGDIR) && ./configure $(CONFIGURE_ARGS) && \
	cd $(CURDIR_PATH)/$(SUBDIRS) && make
	$(STRIP) $(CURDIR_PATH)/$(SUBDIRS)/objs/.libs/libfreetype.so.6
	cp $(CURDIR_PATH)/$(SUBDIRS)/objs/.libs/libfreetype.so.6 $(CURDIR_PATH)/
	
.PHONY: clean
clean:
	cd $(SUBDIRS) && \
        make clean

distclean:
	cd $(SUBDIRS) && \
        make distclean
