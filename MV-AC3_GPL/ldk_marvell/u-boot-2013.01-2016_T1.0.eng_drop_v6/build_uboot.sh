# .bashrc
export CROSS_COMPILE_BH=/project/gtrunk/omada_switch_gpl/20161108_WebUI_upgrade/tplink/buildroot-marvell/host/usr/bin/arm-marvell-linux-gnueabi-
export CROSS_COMPILE=/project/gtrunk/omada_switch_gpl/20161108_WebUI_upgrade/tplink/buildroot-marvell/host/usr/bin/arm-marvell-linux-gnueabi-
export ARCH=arm

#./myclean.pl
make mrproper
#./build.pl -b bobk_customer0 -v 2016_t1.0 -f spi -i spi
#./build.pl -b armada_38x_customer0 -v 2016_t1.0 -f spi -i spi
./build.pl -f spi -v 2016_t1.0 -b ac3_rd -i spi –n COMMON_UBOOT