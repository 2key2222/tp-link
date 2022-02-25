# The IGEN simulator generator for GDB, the GNU Debugger.
#
# Copyright 2002, 2007, 2008, 2009, 2010 Free Software Foundation, Inc.
#
# Contributed by Andrew Cagney.
#
# This file is part of GDB.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

default: all


srcdir = .
srcroot = $(srcdir)/../..

prefix = /home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2
exec_prefix = ${prefix}

host_alias = i686-linux-gnu
target_alias = mips-openwrt-linux-uclibc
program_transform_name = s&^&mips-openwrt-linux-uclibc-&
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
tooldir = $(libdir)/$(target_alias)

datarootdir = ${prefix}/share
datadir = ${datarootdir}
mandir = ${datarootdir}/man
man1dir = $(mandir)/man1
man2dir = $(mandir)/man2
man3dir = $(mandir)/man3
man4dir = $(mandir)/man4
man5dir = $(mandir)/man5
man6dir = $(mandir)/man6
man7dir = $(mandir)/man7
man8dir = $(mandir)/man8
man9dir = $(mandir)/man9
infodir = ${datarootdir}/info
includedir = ${prefix}/include

SHELL = /bin/bash

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = /usr/bin/install -c
INSTALL_DATA = /usr/bin/install -c -m 644

AR = i686-linux-gnu-ar
CC = i686-linux-gnu-gcc
CFLAGS = -O2
RANLIB = i686-linux-gnu-ranlib

AR_FOR_BUILD = $(AR)
AR_FLAGS_FOR_BUILD = $(AR_FLAGS)
CC_FOR_BUILD = $(CC)
CFLAGS_FOR_BUILD = $(CFLAGS)
RANLIB_FOR_BUILD = $(RANLIB)

WARN_CFLAGS =  -Wimplicit -Wreturn-type -Wcomment -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wuninitialized
WERROR_CFLAGS = 
IGEN_WARN_CFLAGS = $(WARN_CFLAGS)
IGEN_WERROR_CFLAGS = $(WERROR_CFLAGS)

BISON = bison
MAKEINFO = makeinfo

.NOEXPORT:
MAKEOVERRIDES=

LIB_INCLUDES	= -I$(srcdir)/../../include
INCLUDES	= -I. -I$(srcdir) $(LIB_INCLUDES)

LIBIBERTY_LIB	= ../../libiberty/libiberty.a

BUILD_CFLAGS = \
	$(CFLAGS_FOR_BUILD) \
	$(IGEN_WARN_CFLAGS) \
	$(IGEN_WERROR_CFLAGS) \
	$(INCLUDES)
BUILD_LDFLAGS = 

all:	igen
#all:	tmp-filter tmp-table tmp-ld-insn tmp-ld-cache tmp-ld-decode tmp-gen

.c.o:
	$(CC_FOR_BUILD) -c $(BUILD_CFLAGS) $<


filter_filename.o: filter_filename.c filter_filename.h config.h ppc-config.h

IGEN_OBJS=\
	table.o \
	lf.o misc.o \
	filter_host.o \
	ld-decode.o \
	ld-cache.o \
	filter.o \
	ld-insn.o \
	gen-model.o \
	gen-itable.o \
	gen-icache.o \
	gen-semantics.o \
	gen-idecode.o \
	gen-support.o \
	gen-engine.o \
	gen.o

igen: igen.o $(IGEN_OBJS)
	$(CC_FOR_BUILD) $(BUILD_LDFLAGS) -o igen igen.o $(IGEN_OBJS) $(LIBIBERTY_LIB)

igen.o: igen.c misc.h filter_host.h lf.h table.h ld-decode.h ld-cache.h ld-insn.h filter.h gen-model.h gen-itable.h gen-icache.h gen-idecode.h gen-engine.h gen-semantics.h gen-support.h gen.h igen.h 
	$(CC_FOR_BUILD) $(BUILD_CFLAGS) -c $(srcdir)/igen.c

tmp-table: table.c table.h misc.o lf.o filter_host.o 
	$(CC_FOR_BUILD) $(BUILD_CFLAGS) $(BUILD_LDFLAGS) -o tmp-table -DMAIN $(srcdir)/table.c misc.o lf.o  filter_host.o $(BUILD_LIBS)

tmp-filter: filter.c filter.h lf.o misc.o filter_host.o
	$(CC_FOR_BUILD) $(BUILD_CFLAGS) $(BUILD_LDFLAGS) -o tmp-filter -DMAIN $(srcdir)/filter.c lf.o misc.o filter_host.o $(BUILD_LIBS)

tmp-ld-decode: ld-decode.h ld-decode.c filter.o misc.o lf.o table.o filter_host.o gen.h igen.h
	$(CC_FOR_BUILD) $(BUILD_CFLAGS) $(BUILD_LDFLAGS) -o tmp-ld-decode -DMAIN $(srcdir)/ld-decode.c filter.o misc.o lf.o table.o filter_host.o $(BUILD_LIBS)

tmp-ld-cache: ld-cache.c ld-cache.h ld-insn.o misc.o lf.o table.o filter_host.o gen.h igen.h
	$(CC_FOR_BUILD) $(BUILD_CFLAGS) $(BUILD_LDFLAGS) -o tmp-ld-cache -DMAIN $(srcdir)/ld-cache.c ld-insn.o filter.o misc.o lf.o table.o filter_host.o $(BUILD_LIBS)

tmp-ld-insn: ld-insn.c ld-insn.h misc.o lf.o table.o filter_host.o filter.o gen.h igen.h
	$(CC_FOR_BUILD) $(BUILD_CFLAGS) $(BUILD_LDFLAGS) -o tmp-ld-insn -DMAIN $(srcdir)/ld-insn.c misc.o lf.o table.o filter_host.o filter.o $(BUILD_LIBS)

tmp-gen: gen.c gen.h ld-insn.o ld-decode.o misc.o lf.o table.o filter_host.o filter.o gen.h igen.h
	$(CC_FOR_BUILD) $(BUILD_CFLAGS) $(BUILD_LDFLAGS) -o tmp-gen -DMAIN $(srcdir)/gen.c misc.o ld-insn.o ld-decode.o lf.o table.o filter_host.o filter.o $(BUILD_LIBS)

filter_host.o: filter_host.c filter_host.h
table.o: table.c misc.h filter_host.h lf.h table.h
lf.o: lf.c misc.h filter_host.h lf.h
filter.o: filter.c misc.h lf.h table.h filter.h
ld-decode.o: ld-decode.c misc.h lf.h table.h ld-decode.h igen.h
ld-cache.o: ld-cache.c misc.h lf.h table.h ld-cache.h igen.h
ld-insn.o: ld-insn.c misc.h lf.h table.h ld-insn.h gen.h igen.h
gen-model.o: gen-model.c misc.h lf.h table.h gen-model.h ld-decode.h gen.h igen.h ld-insn.h
gen-itable.o: gen-itable.c misc.h lf.h table.h gen-itable.h ld-decode.h gen.h igen.h ld-insn.h gen.h filter.h
gen-icache.o: gen-icache.c misc.h lf.h table.h gen-icache.h ld-decode.h gen.h igen.h ld-insn.h gen-semantics.h gen-idecode.h filter.h
gen-semantics.o: gen-semantics.c misc.h lf.h table.h gen-semantics.h ld-decode.h gen.h igen.h ld-insn.h filter.h
gen-idecode.o: gen-idecode.c misc.h lf.h table.h gen-idecode.h gen-icache.h gen-semantics.h ld-decode.h gen.h igen.h ld-insn.h  filter.h
gen-engine.o: gen-engine.c misc.h lf.h table.h gen-idecode.h gen-engine.h gen-icache.h gen-semantics.h ld-decode.h gen.h igen.h ld-insn.h filter.h
gen-support.o: gen-support.c misc.h lf.h table.h gen-support.h ld-decode.h gen.h igen.h ld-insn.h filter.h
gen.o: gen.c misc.h lf.h table.h gen-icache.h ld-decode.h gen.h igen.h ld-insn.h gen-semantics.h gen-idecode.h filter.h
misc.o: misc.c misc.h filter_host.h


tags etags: TAGS

TAGS:
	etags $(srcdir)/*.h $(srcdir)/*.c

clean mostlyclean:
	rm -f tmp-* *.[oasi] core igen

distclean realclean: clean
	rm -f TAGS Makefile config.cache config.status config.h defines.h stamp-h config.log

maintainer-clean: distclean
	rm -f *~ *.log ppc-config.h core *.core

Makefile: Makefile.in config.status
	CONFIG_FILES=Makefile CONFIG_HEADERS= $(SHELL) ./config.status

config.h: stamp-h ; @true
stamp-h: config.in config.status
	CONFIG_FILES= CONFIG_HEADERS=config.h:config.in $(SHELL) ./config.status

config.status: configure
	$(SHELL) ./config.status --recheck

install:
#
