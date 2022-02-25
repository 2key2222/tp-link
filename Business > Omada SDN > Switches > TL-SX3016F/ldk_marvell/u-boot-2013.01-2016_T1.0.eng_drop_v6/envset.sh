# .bashrc
export CROSS_COMPILE_BH=/home/project/20161108_WebUI_upgrade/tplink/buildroot-marvell/host/usr/bin/arm-marvell-linux-gnueabi-
export CROSS_COMPILE=/home/project/20161108_WebUI_upgrade/tplink/buildroot-marvell/host/usr/bin/arm-marvell-linux-gnueabi-
export ARCH=arm

#./myclean.pl
make mrproper
./build.pl -b bobk_customer0 -v 2016_t1.0 -f spi -i spi
./build.pl -b armada_38x_customer0 -v 2016_t1.0 -f spi -i spi -r 38400