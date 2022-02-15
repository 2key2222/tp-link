
KERNEL_HEADERS=-I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/linux-ar71xx_generic/linux-3.3.8

CC=mips-openwrt-linux-uclibc-gcc
CFLAGS= -Wall -Os -pipe -mips32r2 -mtune=74kc -fno-caller-saves -freorder-blocks -fhonour-copts -Wno-error=unused-but-set-variable -msoft-float 
LDFLAGS=-L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/target-mips_r2_uClibc-0.9.33.2/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/usr/lib -L/home/ubuntu/Archer_C7_V5/openwrt/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/lib 
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

