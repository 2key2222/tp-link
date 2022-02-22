#!/bin/bash

##############################################################
#                                                            #
#          crfs_arm.sh  - Create Root File System            #
#                                                            #
#       Written by Aharon Gadot <aharong@marvell.com>        #
#                     Sep 01, 2006                           #
#                                                            #
#      Building root filesystem for embedded Linux system    #
#                                                            #
##############################################################
#
## functions
#
busybox_versions_supported="1.25.0 1.01"

usage_exit() {
	echo
	echo "Incorrect parameters"
	echo "Usage: crfs_arm_mv7sft.sh <ROOTFS_PATH> <MV7SFT_PATH> <BUSYBOX_PATH>"
	echo
	echo "Examples: "
	echo
	echo "1. Little endian: "
	echo
	echo " ./crfs_arm_mv7sft.sh /tftpboot/rootfs_arm-mv7sft \\"
	echo "       /swtools/devtools/gnueabi/arm_le/armv7-marvell-linux-gnueabi-softfp \\"
	echo "       /swtools/devsources/root_fs/files/busybox "
#        echo ""
#        echo "2. Big endian: "
#        echo
#        echo " ./crfs_arm_mv7sft.sh /tftpboot/rootfs_arm-mv7sft-be \\"
#        echo "      /swtools/devtools/gnueabi/arm_be/armeb-linux-gnueabi \\"
#        echo "      /swtools/devsources/root_fs/files/busybox "
#        echo ""
        exit 1
}

#
## main
#

HERE=`dirname $0`
HERE="`cd \"$HERE\" 2>/dev/null && pwd || echo \"$HERE\"`"
echo ""
if [ -n "$1" ]
then
  if [ "$1" = "--help" ]
  then
	echo "Usage: crfs_arm_mv7sft.sh <ROOTFS_PATH> <MV7SFT_PATH> <BUSYBOX_PATH>."
	echo " Create root filesystem for ARM CPU in path given by <ROOTFS_PATH>."
	echo " <BUSYBOX_PATH> must contain busybox-1.01.tar.bz2 or busybox-1.01.tar.gz file"
	echo " Busybox source can be downloaded from http://busybox.net/downloads/."
	echo " <MV7SFT_PATH> - path where MV7SFT toolchain or newer package was installed."
	echo ""
	echo "Example: "
	echo " ./crfs_arm_mv7sft.sh /tftpboot/rootfs_arm-mv7sft \\"
	echo "      /swtools/devtools/gnueabi/arm_le/armv7-marvell-linux-gnueabi-softfp \\"
	echo "      /swtools/devsources/root_fs/files/busybox "
	echo ""
	exit 0
  fi
fi

if [ $# -ne 3 ]
then
	usage_exit
fi

dname=`dirname "$1"`
bname=`basename "$1"`
start_path="`cd \"$dname\" 2>/dev/null && pwd || echo \"$dname\"`/$bname"
if [ -e $1 ]
then
	echo "File system root: $start_path"
else
	echo "Creating file system root: $start_path"
	/bin/mkdir $start_path
fi

cd $HERE
runtime_files_bz2_uu=runtime_files.tar.bz2.uu
if [ -f $runtime_files_bz2_uu ]
then
	runtime_files=/tmp/__runtime_files_$$
	rm -rf ${runtime_files}
	mkdir -p ${runtime_files}
	cd ${runtime_files}
	uudecode $HERE/${runtime_files_bz2_uu}
	bunzip2 -dc runtime_files.tar.bz2 | tar -xvf -
	mv runtime_files/* .
	cd $HERE
fi

dname=`dirname "$2"`
bname=`basename "$2"`
mv7sft="`cd \"$dname\" 2>/dev/null && pwd || echo \"$dname\"`/$bname"
if [ -e $mv7sft ]
then
	echo "MV7SFT path: $mv7sft"
else
	echo "MV7SFT not found in $2. Exiting..."
	echo ""
	exit 1
fi

if echo $mv7sft | grep 'arm_be'  || echo $mv7sft | grep 'armeb' || echo $mv7sft | grep 'armbe' ; then
	eb=eb
	endian=be
	endianess_string="big endian"
else
	eb=
	endian=le
	endianess_string="little endian"
fi
echo "Endianess $endianess_string"
dname=`dirname "$3"`
bname=`basename "$3"`
busybox_path="`cd \"$dname\" 2>/dev/null && pwd || echo \"$dname\"`/$bname"

user_path=$(pwd)
cd $start_path
bbversion=""
for ver in $busybox_versions_supported
do
	if [ -e $busybox_path/busybox-$ver.tar.bz2 ]
	then
		bbversion=$ver
		echo "Uncompressing Busybox tar.bz2 archive..."
		tar xjf $busybox_path/busybox-$bbversion.tar.bz2
		echo -e "\bDone.\n"
		break
	elif [ -e $busybox_path/busybox-$ver.tar.gz ]
	then
		bbversion=$ver
		echo "Uncompressing Busybox tar.gz archive..."
		tar xzf $busybox_path/busybox-$bbversion.tar.gz
		echo -e "\bDone.\n"
		break
	fi
done
if [ "$bbversion" = "" ]
then
	echo "Busybox $busybox_versions_supported archive not found at path $busybox_path. Exiting..."
	echo ""
	exit 1
fi

#create file structure
#---------------------
mkdir bin
mkdir sbin
mkdir root
mkdir home
mkdir home/user
mkdir mnt
mkdir mnt/flash
mkdir mnt/nfs
mkdir etc
mkdir proc
mkdir sys
mkdir tmp
mkdir lib
mkdir lib/modules
mkdir usr
mkdir usr/lib
mkdir usr/bin
mkdir usr/local
mkdir usr/sbin
mkdir usr/share
mkdir var
mkdir var/lib
mkdir var/lock
mkdir var/log
mkdir var/run
mkdir var/tmp
mkdir tplink
mkdir tplink/app
mkdir tplink/data
mkdir tplink/kmod
mkdir tplink/lib

echo "Creating devices"
#create structure of devices
#---------------------------
cd $start_path
mkdir dev
cd dev

#create dev folders
mkdir pts
mkdir shm
mkdir net

cat >../../rootfs_deviceMap <<eof
#<path>       <type> <mode> <uid> <gid> <major> <minor> <start> <inc> <count>
/dev/loop0       b 640 0 0   7   0 0 0 -
/dev/loop1       b 640 0 0   7   1 0 0 -
/dev/ram0        b 640 0 0   1   0 0 0 -
/dev/ram1        b 640 0 0   1   1 0 0 -
/dev/mtdblock0   b 640 0 0  31   0 0 0 -
/dev/mtdblock1   b 640 0 0  31   1 0 0 -
/dev/mtdblock2   b 640 0 0  31   2 0 0 -
/dev/mtdblock3   b 640 0 0  31   3 0 0 -
/dev/mtdblock4   b 640 0 0  31   4 0 0 -
/dev/mtdblock5   b 640 0 0  31   5 0 0 -
/dev/mtdblock6   b 640 0 0  31   6 0 0 -
/dev/mem         c 640 0 0   1   1 0 0 -
/dev/null        c 640 0 0   1   3 0 0 -
/dev/zero        c 640 0 0   1   5 0 0 -
/dev/random      c 640 0 0   1   8 0 0 -
/dev/ptyp0       c 640 0 0   2   0 0 0 -
/dev/ptyp1       c 640 0 0   2   1 0 0 -
/dev/ptyp2       c 640 0 0   2   2 0 0 -
/dev/ttyp0       c 640 0 0   3   0 0 0 -
/dev/ttyp1       c 640 0 0   3   1 0 0 -
/dev/ttyp2       c 640 0 0   3   2 0 0 -
/dev/tty0        c 640 0 0   4   0 0 0 -
/dev/ttyS0       c 640 0 0   4  64 0 0 -
/dev/tty         c 640 0 0   5   0 0 0 -
/dev/console     c 640 0 0   5   1 0 0 -
/dev/ptmx        c 640 0 0   5   2 0 0 -
/dev/sda         b 640 0 0   8   0 0 0 -
/dev/sda1        b 640 0 0   8   1 0 0 -
/dev/sda2        b 640 0 0   8   2 0 0 -
/dev/sda3        b 640 0 0   8   3 0 0 -
/dev/net/tun     c 640 0 0  10 200 0 0 -
/dev/mtd0        c 640 0 0  90   0 0 0 -
/dev/mtd0ro      c 640 0 0  90   1 0 0 -
/dev/mtd1        c 640 0 0  90   2 0 0 -
/dev/mtd1ro      c 640 0 0  90   3 0 0 -
/dev/mtd2        c 640 0 0  90   4 0 0 -
/dev/mtd2ro      c 640 0 0  90   5 0 0 -
/dev/mtd3        c 640 0 0  90   6 0 0 -
/dev/mtd3ro      c 640 0 0  90   7 0 0 -
/dev/mtd4        c 640 0 0  90   8 0 0 -
/dev/mtd4ro      c 640 0 0  90   9 0 0 -
/dev/mtd5        c 640 0 0  90   10 0 0 -
/dev/mtd5ro      c 640 0 0  90   11 0 0 -
/dev/mtd6        c 640 0 0  90   12 0 0 -
/dev/mtd6ro      c 640 0 0  90   13 0 0 -
/dev/mvROS       c 640 0 0 250   0 0 0 -
/dev/mvPP        c 640 0 0 244   0 0 0 -
/dev/mvKernelExt c 640 0 0 244   1 0 0 -
/dev/i2c-0       c 640 0 0  89   0 0 0 -
/dev/i2c-1       c 640 0 0  89   1 0 0 -
/dev/dragonite   c 640 0 0  10 240 0 0 -
eof
# create links
ln -s ttyS0 ttys0
ln -s ttyS0 tty5
ln -s ttyp1 tty1
ln -s mtd0  mtd

echo "Building libraries"
# copy libraries
# --------------
cd $start_path

cd usr/bin
usr_bin_path=`pwd`

cd ../../lib
lib_path=`pwd`

mv7sft_libc_root=$mv7sft/arm${eb}-marvell-linux-gnueabi/libc
mv7sft_lib=$mv7sft_libc_root/lib
mv7sft_lib2=$mv7sft_lib
mv7sft_prefix=$mv7sft/bin/arm${eb}-marvell-linux-gnueabi-

cd  $mv7sft_lib
cp -d libc-* libc.* libm*  ld-* libcrypt* libpthread* libdl* librt* libSegFault* $lib_path

if [ "$COPY_GDBSERVER" != "" -a -f $mv7sft_libc_root/usr/bin/gdbserver ]; then
	cp -p $mv7sft_libc_root/usr/bin/gdbserver $lib_path/../usr/bin
	${mv7sft_prefix}strip $lib_path/../usr/bin/gdbserver
fi
if [ "$runtime_files" != "" ]; then
	cp $runtime_files/usr/bin/*  ${lib_path}/../usr/bin
	chmod +x ${lib_path}/../usr/bin/*
fi

cd  $mv7sft_lib2
cp -d libgcc_s* $lib_path

# strip the libraries except libthread_db
${mv7sft_prefix}strip ${lib_path}/l* > /dev/null 2>&1

cp -d $mv7sft_lib/libthread_db* $lib_path

cd $lib_path
rm -f *orig*

echo "Creating etc files"
# create init files
# -----------------
cd $start_path
cd etc

# creating passwd
echo -e "root::0:0:root:/root:/bin/sh\n\nuser::500:500:Linux User,,,:/home/user:/bin/sh\n" >./passwd

# creating group
echo -e "root:x:1:root\nuser:x:500:\n" >./group
# creating inittab
dash=""
test "$bbversion" = "1.25.0" && dash="-"
cat << EOF > ./inittab
# autoexec
::respawn:${dash}/etc/init.sh

# Stuff to do when restarting the init process
::restart:${dash}/sbin/init
EOF

# creating motd
cat << EOF > ./motd


Welcome to Embedded Linux
           _  _
          | ||_|
          | | _ ____  _   _  _  _
          | || |  _ \\| | | |\\ \\/ /
          | || | | | | |_| |/    \\
          |_||_|_| |_|\\____|\\_/\\_/

          On Marvell's ARMADAXP board

For further information on the Marvell products check:
http://www.marvell.com/

toolchain=mv7sft ${endianess_string}

Enjoy!

EOF


# creating welcome file for telnet
cat << EOF > ./welcome


Welcome to Embedded Linux Telnet
           _  _
          | ||_|
          | | _ ____  _   _  _  _
          | || |  _ \\| | | |\\ \\/ /
          | || | | | | |_| |/    \\
          |_||_|_| |_|\\____|\\_/\\_/

          On Marvell's ARM board

toolchain=mv7sft ${endianess_string}

For further information on the Marvell products check:
http://www.marvell.com/
EOF

# creating init.sh
current_date=$(date +%m%d%H%M%Y)
current_date1=$(date)


# creating README.txt
cat << EOF > ./README.txt

File system building information
--------------------------------

build_date = ${current_date1}

sdk_prefix = ${mv7sft}

lib        = \${sdk_prefix}/arm${eb}-mv7sft-linux-gnueabi/libc/lib

cmd_prefix = \${sdk_prefix}/bin/arm${eb}-mv7sft-linux-gnueabi-

gdbserver  = ${gdbserver_file}

EOF

# creating init.sh

cat << EOF > ./init.sh
#!/bin/sh
if test -e /proc/version
then
 echo
else

 hostname MARVELL_LINUX
 HOME=/root

 test -d /dev/shm || mkdir /dev/shm
 test -d /dev/pts || mkdir /dev/pts

 mount -t proc   proc /proc
 mount -t sysfs  none /sys
 mount -t tmpfs  -n -o size=128M none /dev/shm
 mount -t devpts -o mode=0622    none /dev/pts

 /usr/sbin/telnetd -l /bin/sh -f /etc/welcome

 kernel_ver=\`uname -r\`
 #create modules.dep file to make modinfo command run
 mkdir -p /lib/modules/${kernel_ver}
 touch /lib/modules/${kernel_ver}/modules.dep
 for module_f in /lib/modules/\${kernel_ver%%-*}/*.ko /lib/modules/*.ko
 do
   if [ -e \$module_f ]
   then
     insmod \$module_f
   fi
 done


date $current_date

 # Start the network interface
 /sbin/ifconfig lo 127.0.0.1

 rm -f /tmp/tasks

fi

export LD_PRELOAD=/lib/libSegFault.so

# print logo
# clear
echo
echo
echo
echo
uname -nrsv
cat /etc/motd

if test -e /usr/bin/appDemo
then
  if test -e /usr/local/auto_run.txt
  then
   echo PTK nfs, not running appDemo
  else
    /usr/bin/appDemo
  fi
else
  echo /usr/bin/appDemo not found
fi

exec /bin/sh
EOF

chmod 777 init.sh

# creating fstab
cat << EOF > ./fstab
/dev/nfs                /                       nfs     defaults        0 0
none                    /proc                   proc    defaults        0 0
none                    /sys                    sysfs   defaults        0 0
none                    /dev/shm                tmpfs   size=64M        0 0
none                    /dev/pts                devpts  mode=0622       0 0
EOF

# creating .config file for busybox
cd $start_path/busybox-$bbversion/

if [ -f $HERE/busybox-$bbversion.patch ]; then
	patch -p1 < $HERE/busybox-$bbversion.patch
fi
sed 's!\(CROSS_COMPILER_PREFIX="\).*"!\1'$mv7sft_prefix'"!' $HERE/busybox-$bbversion.config > ./.config

# make and install Busybox
echo -e "Compiling Busybox application. This process may take several minutes.\nPlease wait...\n\n"
if [ "$bbversion" = "1.01" -o "$bbversion" = "1.2.1" ]
then
	#make TARGET_ARCH=arm CROSS=$mv7sft_prefix PREFIX=../. all install >/dev/null 2>/dev/null
	make TARGET_ARCH=arm CROSS=$mv7sft_prefix PREFIX=../. include/config.h
	make TARGET_ARCH=arm CROSS=$mv7sft_prefix PREFIX=../. all install
else
	# 1.25+
	export HOST_EXTRACFLAGS="-Wno-strict-aliasing -Wno-unused-result -Wno-format-security"
	make CONFIG_PREFIX=../. oldconfig
	make CONFIG_PREFIX=../. all install
fi
if [ $? -ne 0 ]; then
    echo -e "\nFailed to build busybox.\n"
    exit 1
fi
ln -s ./bin/busybox $start_path/init

echo -e "Build extra tools..."
for f in $HERE/*.c
do
	test -f $f || continue
	echo "  compile /usr/bin/`basename $f .c`"
	${mv7sft_prefix}gcc -Wall -s $f -o $start_path/usr/bin/`basename $f .c`
done

## SatR
#if [ -f "$CPSS_PATH/tools/satr/Makefile" ]; then
#	mkdir satr
#	echo "  compile satr..."
#	make -C $CPSS_PATH/tools/satr V=0 \
#			ARCH=arm CROSS_COMPILE=$mv7sft_prefix \
#			OUT_DIR=`pwd`/satr \
#			TARGET_DIR=$start_path/usr/bin \
#			install
#fi


echo -e "\nCompilation completed.\n"

# remove Busybox sources
#cd ..
#rm -rf busybox*
#if [ "$runtime_files" != "" ]; then
#	rm -rf ${runtime_files}
#fi

echo ""
echo "Filesystem created successfuly"
echo ""

