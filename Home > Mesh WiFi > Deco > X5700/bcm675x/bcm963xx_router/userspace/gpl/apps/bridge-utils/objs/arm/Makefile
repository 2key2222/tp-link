
DESTDIR=
KERNEL_HEADERS=-I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/../toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include

INSTALL=/usr/bin/install -c

prefix=/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/targets/TP6755/fs.build/gpl
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
sbindir=${exec_prefix}/sbin
mandir=${prefix}/share/man
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

