
KERNEL_HEADERS=-I/home/ubuntu/Archer_C7_V5/openwrt/build_dir/linux-ar71xx_generic/linux-3.3.8

AR=ar
RANLIB=mips-openwrt-linux-uclibc-ranlib

CC=mips-openwrt-linux-uclibc-gcc
CFLAGS = -Wall -g -Os -pipe -mips32r2 -mtune=74kc -fno-caller-saves -freorder-blocks -fhonour-copts -Wno-error=unused-but-set-variable -msoft-float  $(KERNEL_HEADERS)

prefix=/usr
exec_prefix=/usr
includedir=${prefix}/include
libdir=${exec_prefix}/lib

libbridge_SOURCES= \
	libbridge_devif.c \
	libbridge_if.c \
	libbridge_init.c \
	libbridge_misc.c 

libbridge_OBJECTS=$(libbridge_SOURCES:.c=.o)

all:	libbridge.a

# At present there is no need for a bridge-utils-devel package
install:


clean:
	rm -f *.o libbridge.a

libbridge.a:	$(libbridge_OBJECTS)
	$(AR) rcs $@ $(libbridge_OBJECTS)
	$(RANLIB) $@

%.o: %.c libbridge.h libbridge_private.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

libbridge_compat.o:	libbridge_compat.c if_index.c
	$(CC) $(CFLAGS) -c libbridge_compat.c

