#!/bin/sh

PreStartSystem()
{
	echo "pre start system..."
	if test -e /proc/version
	then
		echo
	else
		hostname MARVELL_LINUX
		HOME=/root

		test -d /dev/shm || mkdir /dev/shm
		test -d /dev/pts || mkdir /dev/pts

		mount -t proc   proc /proc
		mount -t sysfs  sysfs /sys
		mount -t tmpfs  -n none /dev/shm
		mount -t devpts -o mode=0622 none /dev/pts	
		echo /sbin/mdev > /proc/sys/kernel/hotplug
		mdev -s
		#/usr/sbin/telnetd -l /bin/sh -f /etc/welcome
		kernel_ver=`uname -r`
		#create modules.dep file to make modinfo command run
		mkdir -p /lib/modules/
		touch /lib/modules//modules.dep
		#for module_f in /lib/modules/${kernel_ver%%-*}/*.ko /lib/modules/*.ko
		#do
		#	if [ -e $module_f ]
		#	then
		#	insmod $module_f
		#	fi
		#done
		insmod /lib/modules/mvDmaDrv.ko
		insmod /lib/modules/mvIntDrv.ko
		insmod /lib/modules/mvMbusDrv.ko
		if [ -e /lib/modules/mvEthDrv.ko ];then
			insmod /lib/modules/mvEthDrv.ko
		fi
		#insmod /lib/modules/4.4.52-devel-18.02.3/kernel/fs/squashfs/squashfs.ko
		date 103015052019
		# Start the network interface
		/sbin/ifconfig lo 127.0.0.1
		rm -f /tmp/tasks
	fi	
	export LD_PRELOAD=/lib/libSegFault.so	
	uname -nrsv
	#cat /etc/motd
	echo "pre start system OK!"
	#exec /bin/sh
}

CheckProcess()  
{  
    if [ "$1" = "" ];  
    then  
	    return 1  
    fi  
  
    PROCESS_NUM=`ps -ef | grep "$1" | grep -v "grep" | wc -l`  
    if [ $PROCESS_NUM -eq 1 ];  
    then  
        return 0  
    else  
        return 1  
    fi      
}  

CheckFiles()
{
	mntPath=/tplink/image
	files=" $mntPath/app/sbin/core
			$mntPath/app/sbin/monitor.cfg
			$mntPath/app/sbin/scm
			/lib/modules/ethdriver.ko"

	for file in $files
	do
		if [ ! -f "$file" ];then
			return 1
		fi
	done
	
	return 0
}

TryMntFs()
{
	mntRet=0

	mount -t squashfs $1 /tplink/image
	mntRet=$?
	if [ $mntRet -eq 0 ];then
		return 1
	fi
	umount /tplink/image
	return 0
}

InitCore()
{
	cpssFlagFile=/etc/cpssDbg
	mntBlk=/dev/mtdblock3

	exepath="/tplink/image"
	if [ ! -d "$exepath" ];then
		mkdir $exepath
	fi
	
	exepath="/tplink/usrapp"
	if [ ! -d "$exepath" ];then
		mkdir $exepath
	fi

	AREA=`cat /proc/mtd | grep "usrimg2@main" | awk '{print $1}'`
	if [ "$AREA" = "mtd4:" ];
	then
		mntBlk=/dev/mtdblock4
	fi
	TryMntFs $mntBlk
	CheckFiles
	CHKFLAG=$?
	if [ $CHKFLAG -eq 1 ];
	then
		echo "retry mount!"
		umount /tplink/image
		TryMntFs $mntBlk
		CheckFiles
		CHKFLAG=$?
		if [ $CHKFLAG -eq 1 ];
		then
			echo "check area fail ,mount anther area!"
			umount /tplink/image
			if [ "$AREA" = "mtd4:" ];
			then
				mntBlk=/dev/mtdblock3
			else
				mntBlk=/dev/mtdblock4
			fi
			TryMntFs $mntBlk
			fsType=$?
		fi
	fi

	mount -t jffs2 /dev/mtdblock5 /tplink/usrapp
	exepath="/tplink/exe"
	if [ ! -d "$exepath" ];then
		mkdir $exepath
	fi
	
	if [ -e $cpssFlagFile ];then
		mkdir /tplink/cpss_image
		mount -t squashfs /dev/mtdblock4 /tplink/cpss_image
	fi
	
	mkdir /exe
	mount -t tmpfs none /exe
	cp -rf /tplink/image/* /exe
	ln -sf /exe/* /tplink/exe/
	rm /exe/app/sbin/core
	ln -s /tplink/image/app/sbin/core  /exe/app/sbin/core
	rm /exe/app/sbin/cli_server
	ln -s /tplink/image/app/sbin/cli_server  /exe/app/sbin/cli_server
	rm /exe/app/sbin/snmpd
	ln -s /tplink/image/app/sbin/snmpd  /exe/app/sbin/snmpd
	rm /exe/app/sbin/httpd
	ln -s /tplink/image/app/sbin/httpd  /exe/app/sbin/httpd
	rm /exe/lib/libipcrypto.so.0
	ln -s /tplink/image/lib/libipcrypto.so.0 /exe/lib/libipcrypto.so.0
	
	mknod /dev/tp-eth c 127 0
	export LD_LIBRARY_PATH=/tplink/exe/lib
	export PATH="$PATH:/tplink/exe/app/sbin"
	export TZ=CST-8
	if [ ! -f "/etc/fw_env.config" ];then
		echo "/dev/mtd1       0x0000      0x10000      0x10000" > /etc/fw_env.config
	fi
	chmod 777 /usr/bin/fw_printenv
	ln -s /usr/bin/fw_printenv /usr/bin/fw_setenv	
	touch /exe/mtdinfo
	/usr/bin/fw_printenv "mtdparts" > /exe/mtdinfo
}
   
if [ 1 ] ; then
	PreStartSystem
    InitCore	
    CheckProcess "monitor"  
    CheckQQ_RET=$?  
    if [ $CheckQQ_RET -eq 1 ];  
    then  
     killall -9 monitor 1> /dev/null 2>&1
     cd /etc
     ./monitor  
    fi  
    sleep 2  
fi  



