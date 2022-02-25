
DESTDIR=
KERNEL_HEADERS=-I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/linux-ar71xx_generic/linux-3.3.8

INSTALL=/usr/bin/install -c

prefix=/usr
exec_prefix=/usr
bindir=/usr/bin
sbindir=/usr/sbin
mandir=/usr/man

SUBDIRS=libbridge brctl

all:

clean:

install:
	mkdir -p $(DESTDIR)$(mandir)/man8
	$(INSTALL) -m 644 brctl.8 $(DESTDIR)$(mandir)/man8
