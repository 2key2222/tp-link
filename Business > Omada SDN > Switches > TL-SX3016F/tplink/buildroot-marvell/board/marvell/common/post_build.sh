#!/bin/bash

TARGET_DIR=$1
ARCH=$2
CROSS_COMPILE=$3
PROJECT_NAME=$4
BASE_DIR=$TARGET_DIR/..
TOP_DIR=$TARGET_DIR/../../..
CPSS_DIR=$TOP_DIR/../../ldk_marvell/cpss_work
CPSS_KERNEL_MODULE_DIR=$CPSS_DIR/cpss/cpssEnabler/mainExtDrv/src/gtExtDrv/linuxNoKernelModule/drivers
CPSS_DBG_FLAG_FILE=$CPSS_DIR/$PROJECT_NAME/cpss_dbg

echo $TARGET_DIR
echo $ARCH
echo $CROSS_COMPILE

#read -p "Press any key to continue..."

#kernel module compile & install
function kernel_module_build()
{	
	echo "**********Building CPSS Kernel Module**********"
	cd $CPSS_KERNEL_MODULE_DIR
	DIST=$BASE_DIR/build/linux-custom/
	. $CPSS_KERNEL_MODULE_DIR/cr_kernel_mod.sh
}

#busybox rootfs build
function busybox_rootfs_build()
{
	BUSYBOX_TAR_DIR=$TOP_DIR/package/busybox/busybox-custom
	#if busybox has been built, skip
	if [ ! -e $BUSYBOX_TAR_DIR/built_$PROJECT_NAME ]; then
		echo "**********Building CPSS RootFS**********"
		cp $TOP_DIR/board/marvell/common/busybox-1.25.0.config $CPSS_DIR/cpss/tools/build/toolkit/marvell_v7sft/
		cd $CPSS_DIR/cpss/tools/build/toolkit/marvell_v7sft/
		./crfs_arm_mv7sft.sh $TARGET_DIR $TOP_DIR/host/usr $BUSYBOX_TAR_DIR
		touch $BUSYBOX_TAR_DIR/built_$PROJECT_NAME
		mv -f $TARGET_DIR/busybox-1.25.0 $TARGET_DIR/../
	fi
}

#cpss appDemo rebuild
function cpss_appDemo_rebuild()
{
	if [ ! -e $CPSS_DBG_FLAG_FILE ]; then
		echo "**********CPSS Debug Disable**********"
	else
		echo $PROJECT_NAME
		cd $CPSS_DIR
		export PATH="$PATH:$TOP_DIR/host/usr/bin"
		export DEBUG_INFO=D_ON
		export COMPILATION_ROOT=$CPSS_DIR/$PROJECT_NAME/dbg
		mkdir $CPSS_DIR/$PROJECT_NAME/dbg
		./build_cpss.sh DX_ALL ARMv7_LK_4_4 CUST NOKERNEL CPSS_ENABLER_NOKM UTF_NO TM_NO
		$TOP_DIR/host/usr/arm-marvell-linux-gnueabi/bin/strip $PROJECT_NAME/dbg/appDemo
		cp $PROJECT_NAME/dbg/appDemo $BASE_DIR/
		read -p "Press any key to continue..."
		touch $TARGET_DIR/etc/cpssDbg
	fi
}
kernel_module_build
busybox_rootfs_build
cpss_appDemo_rebuild
echo "**********Copying files to target directory**********"
cp -f $CPSS_KERNEL_MODULE_DIR/*.ko $TARGET_DIR/lib/modules/
#cp -f $BASE_DIR/images/*.dtb $TARGET_DIR/boot/


