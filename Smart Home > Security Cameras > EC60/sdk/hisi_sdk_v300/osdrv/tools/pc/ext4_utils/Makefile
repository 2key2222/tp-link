###############################################################################
#
#         Heli Creates it at September,22 2011.
###############################################################################
PREFIX         ?= $(shell pwd)
BIN_DIR         = $(PREFIX)/bin
EXT4_UTILS      = extras-refs_tags_android-4.1.1_r1-ext4_utils
###############################################################################
CC=gcc
AR=ar
CPP=cpp
LD=ld
RANLIB=ranlib
NM=nm
STRIP=strip

###############################################################################
all:
	@test -d $(PREFIX) || mkdir -p $(PREFIX)
	@test -d $(PREFIX)/$(EXT4_UTILS) || mkdir -p $(PREFIX)/$(EXT4_UTILS)
	tar -xzf $(EXT4_UTILS).tar.gz -C $(EXT4_UTILS)
	@test -d $(BIN_DIR)|| mkdir -p $(BIN_DIR)
	pushd $(PREFIX)/$(EXT4_UTILS);patch -p1 < ../hiext4_utils.patch;popd;
	cd $(PREFIX)/$(EXT4_UTILS);\
		make;cp make_ext4fs $(BIN_DIR);\
	cd -

clean:
	rm -rf $(PREFIX)/$(EXT4_UTILS)
	rm -rf $(PREFIX)/bin

distclean: clean
###############################################################################
.PHONY: clean distclean all
###############################################################################
