
DESTDIR=
KERNEL_HEADERS=-I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/linux-ar71xx_generic/linux-3.3.8

INSTALL=/usr/bin/install -c

prefix=/usr
exec_prefix=/usr
bindir=/usr/bin
sbindir=/usr/sbin
mandir=/usr/man
distdir = $(PACKAGE)-$(VERSION)

SUBDIRS=libbridge brctl doc

all:
	for x in $(SUBDIRS); do $(MAKE) $(MFLAGS) -C $$x ; done

clean:
	for x in $(SUBDIRS); do $(MAKE) $(MFLAGS) -C $$x clean ; done

distclean:	clean
	rm -f config.log
	rm -f config.cache
	rm -f config.status

maintainer-clean: distclean
	rm -f Makefile
	rm -f brctl/Makefile
	rm -f libbridge/Makefile
	rm -f doc/Makefile

install:
	for x in $(SUBDIRS); do $(MAKE) $(MFLAGS) -C $$x install; done

