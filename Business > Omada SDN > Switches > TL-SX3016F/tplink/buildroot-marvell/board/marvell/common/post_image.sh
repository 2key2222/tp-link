#!/bin/bash

BINARIES_DIR=$1
BOARD_DIR=$BINARIES_DIR/../../../board/marvell/common
MKIMAGE=$BINARIES_DIR/../../../host/usr/bin/mkimage

echo $BINARIES_DIR

FDT_NAME=marvell.its 
#OUTPUT_NAME=uImage_$4.img
#if [ -z $4 ]; then
OUTPUT_NAME=uImage.img
#fi

cp $MKIMAGE $BINARIES_DIR/
cp $BOARD_DIR/$FDT_NAME $BINARIES_DIR/
cd $BINARIES_DIR
#mv *.dtb msys-ac3-rd.dtb
#read -p "Press any key to continue..."
./mkimage -f $FDT_NAME $BINARIES_DIR/$OUTPUT_NAME
rm mkimage
rm $BINARIES_DIR/$FDT_NAME
cd -

