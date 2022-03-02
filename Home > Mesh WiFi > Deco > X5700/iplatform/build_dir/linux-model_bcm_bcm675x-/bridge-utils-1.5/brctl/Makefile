
KERNEL_HEADERS=-I/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/bcm963xx_router/kernel/linux-4.1

CC=arm-buildroot-linux-gnueabi-gcc
CFLAGS= -Wall  
LDFLAGS=-L/home/ubuntu/tp-link/GPL_X5700_1/iplatform/staging_dir/target-arm-openwrt-linux-uclibc-/usr/lib -L/home/ubuntu/tp-link/GPL_X5700_1/iplatform/staging_dir/target-arm-openwrt-linux-uclibc-/lib -Wl,-rpath-link,/home/ubuntu/tp-link/GPL_X5700_1/iplatform/staging_dir/target-arm-openwrt-linux-uclibc-/usr/lib -L/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/lib -L/home/ubuntu/tp-link/GPL_X5700_1/iplatform/../bcm675x/toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/lib 
INCLUDE=-I../libbridge $(KERNEL_HEADERS) 
LIBS= -L ../libbridge -lbridge 

prefix=/usr
exec_prefix=/usr
bindir=/usr/bin
sbindir=/usr/sbin
mandir=/usr/man

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

%.o: %.c brctl.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< 

clean:
	rm -f *.o brctl core

