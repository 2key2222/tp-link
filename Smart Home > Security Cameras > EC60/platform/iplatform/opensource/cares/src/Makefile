#****************************************************************************
#    Copyright (C), 2016-xxx, TP-LINK
# 
#    File Name    : Makefile
#    Version      : 1.0
#    Author       : liziliang
#    Created      : 2016-04-14
#****************************************************************************/
CONFIGDIR := c-ares-1.13.0
SUBDIRS := c-ares-1.13.0
CURDIR_PATH := $(shell pwd)

CONFIGURE_ARGS := --enable-shared
CONFIGURE_ARGS += CC=$(CONFIG_TOOLCHAIN_PREFIX)gcc
CONFIGURE_ARGS += LD=$(CONFIG_TOOLCHAIN_PREFIX)ld
CONFIGURE_ARGS += CPPFLAGS=-I$(CONFIG_TOOLCHAIN_ROOT)/usr/include/
CONFIGURE_ARGS += "CXXFLAGS= -O2 -I$(CONFIG_TOOLCHAIN_ROOT)/usr/include/"
CONFIGURE_ARGS += LDFLAGS=-L$(CONFIG_TOOLCHAIN_ROOT)/usr/lib/
CONFIGURE_ARGS += '--target=arm-openwrt-linux-uclibc' '--host=arm-openwrt-linux-uclibc' '--build=i686-linux-gnu' '--program-prefix=' '--program-suffix=' '--prefix=/usr' '--exec-prefix=/usr' '--bindir=/usr/bin' '--sbindir=/usr/sbin' '--libexecdir=/usr/lib' '--sysconfdir=/etc' '--datadir=/usr/share' '--localstatedir=/var' '--mandir=/usr/man' '--infodir=/usr/info' '--enable-shared'

STRIP := $(CONFIG_TOOLCHAIN_PREFIX)strip


all:
	@echo =======CONFIGURE_ARGS:$(CONFIGURE_ARGS)
	cd $(CONFIGDIR) && ./configure $(CONFIGURE_ARGS) && \
	cd $(CURDIR_PATH)/$(SUBDIRS) && make
	$(STRIP) $(CURDIR_PATH)/$(SUBDIRS)/.libs/libcares.so*
	cp -a $(CURDIR_PATH)/$(SUBDIRS)/.libs/libcares.so* $(CURDIR_PATH)/
	
.PHONY: clean
clean:
	cd $(SUBDIRS) && \
        make clean

distclean:
	cd $(SUBDIRS) && \
        make distclean
