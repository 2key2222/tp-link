
# Author: Erwin Waterlander
# Copyright (C) 2009-2014 Erwin Waterlander
# This file is distributed under the same license as the dos2unix package.

# This makefile is for use with MSYS and MinGW (mingw.org) target 32 bit (i686)
# http://www.mingw.org/
.PHONY: test check

UNIFILE=1
CC = gcc
prefix=c:/usr/local
ENABLE_NLS=

ifdef ENABLE_NLS
LIBS_EXTRA = -lintl -liconv
ZIPOBJ_EXTRA = bin/libintl-8.dll bin/libiconv-2.dll
endif

all:
	$(MAKE) all EXE=.exe ENABLE_NLS=$(ENABLE_NLS) LIBS_EXTRA="$(LIBS_EXTRA)" prefix=$(prefix) LINK="cp -f" CC=$(CC) UNIFILE=$(UNIFILE) CFLAGS_OS=-D_O_U16TEXT=0x20000

test: all
	cd test; $(MAKE) test

check: test

install:
	$(MAKE) install EXE=.exe ENABLE_NLS=$(ENABLE_NLS) LIBS_EXTRA="$(LIBS_EXTRA)" prefix=$(prefix) LINK="cp -f" CC=$(CC) UNIFILE=$(UNIFILE) CFLAGS_OS=-D_O_U16TEXT=0x20000

uninstall:
	$(MAKE) uninstall EXE=.exe prefix=$(prefix)

clean:
	$(MAKE) clean EXE=.exe ENABLE_NLS=$(ENABLE_NLS) prefix=$(prefix)

mostlyclean:
	$(MAKE) mostlyclean EXE=.exe ENABLE_NLS=$(ENABLE_NLS) prefix=$(prefix)

dist:
	$(MAKE) dist-zip EXE=.exe prefix=$(prefix) VERSIONSUFFIX="-win32" ZIPOBJ_EXTRA="${ZIPOBJ_EXTRA}" ENABLE_NLS=$(ENABLE_NLS)

strip:
	$(MAKE) strip LINK="cp -f" EXE=.exe

