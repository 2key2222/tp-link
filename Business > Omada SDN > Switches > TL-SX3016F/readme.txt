TP-LINK switch GPL code readme

1. This package contains GPL code for switch TL-SX3016F(UN) 1.0.
2. All components have been built successfully on CentOS Linux release 6.0.

Build Instructions
1. All build targets are in "TL-SX3016F_GPL/tplink/buildroot-marvell/" and "TL-SX3016F_GPL/ldk_marvell/u-boot-2013.01-2016_T1.0.eng_drop_v6", you should enter the directory to build components.

2. Toolchain binary is avaliable in this package. The directory is "TL-SX3016F_GPL/tplink/buildroot-marvell/host/usr/bin/".

3. Building steps:
 1) put TL-SX3016F_GPL in directory /project/trunk
 2) cd /project/trunk/TL-SX3016F_GPL/tplink/buildroot-marvell
 3) make O=build/tl-sx3016f tplink-tl-sx3016f_defconfig
 4) make O=build/tl-sx3016f
 After step4 completed, The linux kernel image, rootfs filesystem will be found in directory "TL-SX3016F_GPL/tplink/buildroot-marvell/build/tl-sx3016f/images".
 
 5) cd /project/trunk/TL-SX3016F_GPL/ldk_marvell/u-boot-2013.01-2016_T1.0.eng_drop_v6
 6) export CROSS_COMPILE=/project/trunk/TL-SX3016F_GPL/tplink/buildroot-marvell/host/usr/bin/arm-marvell-linux-gnueabi-
 7) export CROSS_COMPILE_BH=/project/trunk/TL-SX3016F_GPL/tplink/buildroot-marvell/host/usr/bin/arm-marvell-linux-gnueabi-
 8) export ARCH=arm
 9) make mrproper
 10) ./build.pl -b armada_38x_customer0 -v 2016_t1.0 -f spi -i spi
 After step10 completed, uboot will be found in directory "TL-SX3016F_GPL/ldk_marvell/u-boot-2013.01-2016_T1.0.eng_drop_v6".