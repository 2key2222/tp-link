# $Id: Makefile.in,v 1.5 2014/06/17 13:06:08 dtucker Exp $

sysconfdir=/etc/ssh
piddir=/var/run
srcdir=.
top_srcdir=../..


CC=/project/trunk/MV-AC3_GPL/tplink/buildroot-marvell/build/mv-ac3/host/usr/bin/arm-marvell-linux-gnueabi-gcc
LD=/project/trunk/MV-AC3_GPL/tplink/buildroot-marvell/build/mv-ac3/host/usr/bin/arm-marvell-linux-gnueabi-gcc
CFLAGS=-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -Os  -Qunused-arguments -Wall -Wpointer-arith -Wuninitialized -Wsign-compare -Wformat-security -Wno-pointer-sign -Wno-unused-result -fno-strict-aliasing -D_FORTIFY_SOURCE=2 -ftrapv -fno-builtin-memset -fstack-protector-all -fPIE 
CPPFLAGS=-I. -I.. -I$(srcdir) -I$(srcdir)/.. -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -DHAVE_CONFIG_H
EXEEXT=
LIBCOMPAT=../libopenbsd-compat.a
LIBS=-lcrypto -lrt -ldl -lutil -lz -lnsl  -lcrypt -lresolv
LDFLAGS=-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -Os  -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -fstack-protector-all -pie $(LIBCOMPAT)

TESTPROGS=closefromtest$(EXEEXT) snprintftest$(EXEEXT) strduptest$(EXEEXT) \
	strtonumtest$(EXEEXT) opensslvertest$(EXEEXT)

all:	t-exec ${OTHERTESTS}

%$(EXEEXT):	%.c $(LIBCOMPAT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $< $(LIBCOMPAT) $(LIBS)

t-exec:	$(TESTPROGS)
	@echo running compat regress tests
	@for TEST in ""$?; do \
		echo "run test $${TEST}" ... 1>&2; \
		./$${TEST}$(EXEEXT) || exit $$? ; \
	done
	@echo finished compat regress tests

clean:
	rm -f *.o *.a core $(TESTPROGS) valid.out

distclean: clean
	rm -f Makefile *~
