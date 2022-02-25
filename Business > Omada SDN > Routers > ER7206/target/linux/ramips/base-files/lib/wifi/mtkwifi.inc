#!/bin/sh
# 2018 Hua Shao <hua.shao@mediatek.com>

# $1 -> profile path
# normally we don't need this, /sbin/wifi provides a better solution

load_l1profile() {
	if [ "$1" == "" ]; then
		l1profile=/etc/wireless/l1profile.dat
	else
		l1profile=$1
	fi

	for line in `cat ${l1profile}`; do
		if echo $line | grep -q "="; then true; else continue; fi
		key=`echo $line | awk -F "=" '{print $1}'`
		value=`echo $line | awk -F "=" '{print $2}'`
		eval $key=\"$value\"
	done

	L1CHIPS="$INDEX0 $INDEX1 $INDEX2"
	L1DEVNAMES=""

	for i in 0 1 2; do
		eval INDEX=INDEX${i}

		# get dbdc
		eval profile="\${${INDEX}_profile_path}"
		[ "${profile}" == "" ] && continue
		if echo ${profile} | grep -q ";"; then
			eval ${INDEX}_DBDC=1
			#echo ${INDEX}_DBDC=1
		else
			eval ${INDEX}_DBDC=0
			#echo ${INDEX}_DBDC=0
		fi

		# get devname
		eval dev=\${${INDEX}}
		eval dev1=\$${dev}_1
		eval dev2=\$${dev}_2
		eval dev3=\$${dev}_3
		eval dbdc=\${${INDEX}_DBDC}
		if [ "$dev1" == "" ]; then
			eval INDEX${i}_devname=${dev}_1
			#echo INDEX${i}_devname=${dev}_1
			eval ${dev}_1=1
			if [ "$dbdc" == "1" ]; then
				L1DEVNAMES="${dev}_1_1 ${dev}_1_2 ${L1DEVNAMES}"
			else
				L1DEVNAMES="${dev}_1 ${L1DEVNAMES}"
			fi
		elif [ "$dev2" == "" ]; then
			eval INDEX${i}_devname=${dev}_2
			#echo INDEX${i}_devname=${dev}_2
			eval ${dev}_2=1
			if [ "$dbdc" == "1" ]; then
				L1DEVNAMES="${dev}_2_1 ${dev}_2_2 ${L1DEVNAMES}"
			else
				L1DEVNAMES="${dev}_2 ${L1DEVNAMES}"
			fi
		elif [ "$dev3" == "" ]; then
			eval INDEX${i}_devname=${dev}_3
			#echo INDEX${i}_devname=${dev}_3
			eval ${dev}_3=1
			if [ "$dbdc" == "1" ]; then
				L1DEVNAMES="${dev}_3_1 ${dev}_3_2 ${L1DEVNAMES}"
			else
				L1DEVNAMES="${dev}_3 ${L1DEVNAMES}"
			fi
		else
			>&2 echo "too much!"
		fi
	done

	eval dev1=\$${INDEX0}_1
	eval dev2=\$${INDEX0}_2
	if [ "$dev1" == "1" ]; then
		INDEX0_devname=${INDEX0}_1
		eval ${INDEX0}_1=1
	elif [ "$dev2" == "1" ]; then
		INDEX0_devname=${INDEX0}_2
		eval ${INDEX0}_2=1
	else
		>&2 echo "too much!"
	fi

	for line in `cat ${l1profile}`; do
		if echo $line | grep -q "="; then true; else continue; fi

		INDEX=`echo $line | awk -F "_" '{print $1}'`
		KEY=`echo $line | awk -F "=" '{print $1}' | sed 's/INDEX[0-9]_//g'`
		if echo $KEY | grep -q -E "INDEX[0-9]"; then KEY="chipname"; fi
		VALUE=`echo $line | awk -F "=" '{print $2}'`

		eval DEVNAME=\${${INDEX}_devname}
		eval DBDC=\${${INDEX}_DBDC}

		if [ "$DBDC" == "1" ]; then
			if echo $VALUE | grep -q ";"; then
				v1=`echo $VALUE | awk -F ";" '{print $1}'`;
				v2=`echo $VALUE | awk -F ";" '{print $2}'`;
				#echo ${DEVNAME}_1_${KEY}=$v1
				#echo ${DEVNAME}_2_${KEY}=$v2
				eval ${DEVNAME}_1_${KEY}=$v1
				eval ${DEVNAME}_2_${KEY}=$v2
			else
				#echo ${DEVNAME}_1_${KEY}=$VALUE
				#echo ${DEVNAME}_2_${KEY}=$VALUE
				eval ${DEVNAME}_1_${KEY}=$VALUE
				eval ${DEVNAME}_2_${KEY}=$VALUE
			fi
		else
			#echo ${DEVNAME}_${KEY}=${VALUE}
			eval ${DEVNAME}_${KEY}=${VALUE}
		fi
	done

	#echo L1CHIPS=$L1CHIPS
	#echo L1DEVNAMES=$L1DEVNAMES
}


profile_backup() {
	echo "profile_backup"
}


profile_diff() {
	echo "profile_diff"
}



# vifs_up and vifs_down accept ifname patterns, for example:
#
#	 vifs_up ra0			 -- ra0
#	 vifs_up rai0			-- rai0
#	 vifs_up ra?			 -- ra0, ra1, ..., ra9, raa, rab, ....
#	 vifs_up ra*			 -- ra0, rai0, ra1, rai1asdfasdfasdf, ....
#	 vifs_up ra[0-9]		 -- ra0, ra1, ..., ra9
#	 vifs_up ra1[1-3]		-- ra11, ra12, ra13
#	 vifs_up ra[0-9]*		-- ra0, ra1, ..., ra10, ra11, ....

vifs_up() {
	[ "$1" == "" ] && exit
	ifname=$1 # can be pattern
	cd /sys/class/net
	for vif in `ls -d *${ifname} 2>/dev/null`; do
		ifconfig $vif up;
	done
}

vifs_down() {
	[ "$1" == "" ] && exit
	ifname=$1 # can be pattern
	cd /sys/class/net
	for vif in `ls -d *${ifname} 2>/dev/null`; do
		ifconfig $vif down;
	done
}


# common API for mt76xx drivers
# $1 = devname
# $2 = driver
mt76xx_up() {
	devname=`echo $1 | sed 's/\./_/g'`
	driver=$2

	[ -f /lib/modules/`uname -r`/${driver}.ko ] && modprobe ${driver}.ko

	if [ "$devname" == "" ]; then
		for devname in $L1DEVICES; do
			eval init_compatible=\$${devname}_init_compatible
			if [ "${init_compatible}" == "${driver}" ]; then
				devs="$devname $devs"
			fi
		done
	else
		devs=$devname
	fi

	for devname in $devs; do
		eval main_ifname=\$${devname}_main_ifname
		eval ext_ifname=\$${devname}_ext_ifname
		vifs_up ${main_ifname}
		vifs_up ${ext_ifname}*
	done
}




# $1 = devname
# $2 = driver
mt76xx_down() {
	devname=`echo $1 | sed 's/\./_/g'`
	driver=$2

	if [ "$devname" == "" ]; then
		for devname in $L1DEVICES; do
			eval init_compatible=\$${devname}_init_compatible
			if [ "${init_compatible}" == "${driver}" ]; then
				devs="$devname $devs"
			fi
		done
	else
		devs=$devname
	fi

	for devname in $devs; do
		eval main_ifname=\$${devname}_main_ifname
		eval ext_ifname=\$${devname}_ext_ifname
		vifs_down ${main_ifname}
		vifs_down ${ext_ifname}*
	done
}


# $1 = devname
# $2 = driver
mt76xx_reload() {
	devname=`echo $1 | sed 's/\./_/g'`
	driver=$2

	# 1. call uci2dat to save uci changes into profile
	uci2dat -u /etc/config/wireless -l /etc/wireless/l1profile.dat

	# 2. check if we can do quick reload
	uci changes wireless

	# maybe we should backup_profile + diff_profile

	if [ 1 ]; then
		# normal reload
		mt76xx_down ${devname} ${driver}
		mt76xx_up ${devname} ${driver}
	else # good, able to do quick reload
		echo "here we use iwpriv to update wifi feature on-the-fly"
	fi
}




# $1 = devname
# $2 = driver
mt76xx_restart() {
	devname=`echo $1 | sed 's/\./_/g'`
	driver=$2
	mt76xx_down ${devname} ${driver}

	[ -f /lib/modules/`uname -r`/${driver}.ko ] || echo "failed to detect ${driver}.ko"
	if [ -d /sys/module/${driver} ]; then
		rmmod ${driver};
		modprobe ${driver}.ko;
	else
		# if wifi driver is built-in, it's necessary action to reboot the device
		echo reboot_required > /tmp/mtk/wifi/reboot_required
	fi

	mt76xx_reload ${devname} ${driver}
}


# $1 = devname
# $2 = driver
mt76xx_detect() {
	dat2uci -l /etc/wireless/l1profile.dat -u /etc/config/wireless
}


# $1 = devname
# $2 = driver
mt76xx_status() {
	iwconfig
}

# $1 = devname
# $2 = driver
mt76xx_hello() {
	echo "mt76xx_hello($@)"
}

