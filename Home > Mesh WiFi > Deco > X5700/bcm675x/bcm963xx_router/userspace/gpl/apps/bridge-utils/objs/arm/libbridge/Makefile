
KERNEL_HEADERS=-I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/../toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/arm-buildroot-linux-gnueabi/sysroot/usr/include
srcdir=../../../bridge-utils-1.5/libbridge

AR=ar
RANLIB=/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/../toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-ranlib

CC=/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/../toolchain/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc
CFLAGS = -Wall -g $(KERNEL_HEADERS) -Os -march=armv7-a -fomit-frame-pointer -mno-thumb-interwork -mabi=aapcs-linux -marm -fno-common -ffixed-r8 -msoft-float -D__ARM_ARCH_7A__ -Werror=return-type -Werror=uninitialized -Wno-date-time -Wno-cpp -I/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/kernel -I.

prefix=/home/ubuntu/tp-link/GPL_X5700_1/bcm675x/bcm963xx_router/targets/TP6755/fs.build/gpl
exec_prefix=${prefix}
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

%.o: $(srcdir)/%.c $(srcdir)/libbridge.h $(srcdir)/libbridge_private.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

libbridge_compat.o:	$(srcdir)/libbridge_compat.c $(srcdir)/if_index.c
	$(CC) $(CFLAGS) -c libbridge_compat.c

