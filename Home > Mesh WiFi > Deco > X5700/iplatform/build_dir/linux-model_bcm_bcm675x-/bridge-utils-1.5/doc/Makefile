
DESTDIR=
KERNEL_HEADERS=-I/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/bcm963xx_router/kernel/linux-4.1

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
