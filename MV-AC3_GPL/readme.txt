TP-LINK switch GPL code readme

1. This package contains GPL code for switches that use marvell ac3 chip.
2. All components have been built successfully on CentOS Linux release 6.0.

Build Instructions
1. All build targets are in "MV-AC3_GPL/tplink/buildroot-marvell/" and "MV-AC3_GPL/ldk_marvell/u-boot-2013.01-2016_T1.0.eng_drop_v6", you should enter the directory to build components.

2. Toolchain binary is avaliable in this package. The directory is "MV-AC3_GPL/tplink/buildroot-marvell/host/usr/bin/".

3. Building steps:
 1) put MV-AC3_GPL in directory /project/trunk
 2) cd /project/trunk/MV-AC3_GPL/tplink/buildroot-marvell
 3) make O=build/mv-ac3 tplink-mv-ac3_defconfig
 4) make O=build/mv-ac3
 After step4 completed, The linux kernel image, rootfs filesystem will be found in directory "MV-AC3_GPL/tplink/buildroot-marvell/build/mv-ac3/images".
 
 5) cd /project/trunk/MV-AC3_GPL/ldk_marvell/u-boot-2013.01-2016_T1.0.eng_drop_v6
 6) export CROSS_COMPILE=/project/trunk/MV-AC3_GPL/tplink/buildroot-marvell/host/usr/bin/arm-marvell-linux-gnueabi-
 7) export CROSS_COMPILE_BH=/project/trunk/MV-AC3_GPL/tplink/buildroot-marvell/host/usr/bin/arm-marvell-linux-gnueabi-
 8) export ARCH=arm
 9) make mrproper
 10) ./build.pl -f spi -v 2016_t1.0 -b ac3_rd -i spi -n COMMON_UBOOT
 After step10 completed, uboot will be found in directory "MV-AC3_GPL/ldk_marvell/u-boot-2013.01-2016_T1.0.eng_drop_v6".