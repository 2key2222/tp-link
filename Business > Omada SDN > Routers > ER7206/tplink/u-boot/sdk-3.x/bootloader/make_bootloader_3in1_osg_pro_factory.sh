#!/bin/sh

#Author: ganguoheng@tp-link.net
#Date  : 2015/09/28 
#
# Flash Layout :
#
# 0x00000000 - spi-boot.bin
# 0x00010000 - u-boot-octeon_generic_spi_stage2.bin
# 0x00081000 - u-boot-octeon_evb7000_sff.bin
# 0x001F0000 - bootloader_6120v2_env.bin
# 0x00200000 - kernel
#
#

MODEL=OSG_PRO

echo "make ${MODEL}_factory bootloader : ..."

rm -rf bootloader_3in1_${MDOEL}.bin bootloader_${MODEL}_stage1.bin bootloader_${MODEL}_stage2.bin bootloader_${MODEL}_stage3.bin

dd if=spi-boot/spi-boot.bin of=bootloader_${MODEL}_stage1.bin bs=65536 count=1 conv=sync

dd if=u-boot_rtl8367x/u-boot-octeon_generic_spi_stage2.bin of=bootloader_${MODEL}_stage2.bin bs=462848 count=1 conv=sync

dd if=u-boot_rtl8367x/u-boot-octeon_evb7000_sff.bin of=bootloader_${MODEL}_stage3.bin bs=1503232 count=1 conv=sync

dd if=bootloader_nothing_env.bin of=bootloader_${MODEL}_stage3_env.bin bs=65536 count=1 conv=sync

cat bootloader_${MODEL}_stage1.bin bootloader_${MODEL}_stage2.bin bootloader_${MODEL}_stage3.bin bootloader_${MODEL}_stage3_env.bin > bootloader_3in1_${MODEL}_factory.bin

echo "make ${MODEL}_factory bootloader : DONE!"


