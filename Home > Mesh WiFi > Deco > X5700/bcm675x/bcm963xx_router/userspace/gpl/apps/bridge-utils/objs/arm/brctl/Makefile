
KERNEL_HEADERS=-I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/../toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include

srcdir=../../../bridge-utils-1.5/brctl

CC=/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/../toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc
CFLAGS= -Wall -Os -march=armv7-a -fomit-frame-pointer -mno-thumb-interwork -mabi=aapcs-linux -marm -fno-common -ffixed-r8 -msoft-float -D__ARM_ARCH_7A__ -Werror=return-type -Werror=uninitialized -Wno-date-time -Wno-cpp -I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/kernel
LDFLAGS=-L/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/targets/TP6755/fs.install/lib
INCLUDE=-I$(srcdir)/../libbridge -I../libbridge $(KERNEL_HEADERS) 
LIBS= -L ../libbridge -lbridge 

prefix=/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/targets/TP6755/fs.build/gpl
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
sbindir=${exec_prefix}/sbin
mandir=${prefix}/share/man

INSTALL=/usr/bin/install -c


common_SOURCES= brctl_cmd.c brctl_disp.c 
brctl_SOURCES=  brctl.c $(common_SOURCES)

common_OBJECTS= $(common_SOURCES:.c=.o)
brctl_OBJECTS= $(brctl_SOURCES:.c=.o)

OBJECTS= $(common_OBJECTS) $(brctl_OBJECTS)

PROGRAMS= brctl 


all:	$(PROGRAMS)

install: $(PROGRAMS)
	mkdir -p $(DESTDIR)$(sbindir)
	$(INSTALL) -m 755 $(PROGRAMS) $(DESTDIR)$(sbindir)

brctl:	$(brctl_OBJECTS) ../libbridge/libbridge.a
	$(CC) $(LDFLAGS) $(brctl_OBJECTS) $(LIBS) -o brctl

%.o: $(srcdir)/%.c $(srcdir)/brctl.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< 

clean:
	rm -f *.o brctl core

