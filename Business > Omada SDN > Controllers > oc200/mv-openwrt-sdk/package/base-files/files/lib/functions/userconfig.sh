#!/bin/sh
# Copyright (C) 2006-2013 OpenWrt.org
# Copyright (C) 2010 Vertical Communications

DEFAULT_CONFIG_DIR=/rom/etc/config
RUNNING_USER_CONFIG_DIR=/etc/config
USER_CONFIG_DIR=/userconfig
USER_CONFIG_TAR=userconfig.tar

sync_romconfig_to_userconfig() {
	tmp_def_file=/tmp/def_file
	tmp_user_file=/tmp/user_file

	find ${DEFAULT_CONFIG_DIR}/ -type f > ${tmp_def_file}
	find ${RUNNING_USER_CONFIG_DIR}/ -type f > ${tmp_user_file}

	for file in `cat ${tmp_def_file}`
	do
		filename=`basename ${file}`
		if [ `cat ${tmp_user_file} | grep ${filename} | wc -l` == "0" ]; then
			newfile=${file/\/rom/}
			echo "sync config: ${file} -> ${newfile}"
			mkdir -p `dirname ${newfile}`
			cp ${file} ${newfile}
			sync
		fi			
	done
	rm ${tmp_def_file}
	rm ${tmp_user_file}
}

restore_userconfig() {
	rm -rf ${USER_CONFIG_DIR}/*
	sync
}

save_userconfig() {
	cd ${RUNNING_USER_CONFIG_DIR} && tar -cf /tmp/${USER_CONFIG_TAR} . 

	[ -f /tmp/${USER_CONFIG_TAR} ] && {
		tpcrypt -e -i /tmp/${USER_CONFIG_TAR} -o /tmp/${USER_CONFIG_TAR}.dec
		rm -f /tmp/${USER_CONFIG_TAR}
	}

	[ -f /tmp/${USER_CONFIG_TAR}.dec ] && {
		cp -f /tmp/${USER_CONFIG_TAR}.dec ${USER_CONFIG_DIR}/ && sync
		rm -f /tmp/${USER_CONFIG_TAR}.dec
	}
}

apply_userconfig() {
	[ -f ${USER_CONFIG_DIR}/${USER_CONFIG_TAR}.dec ] && {
		tpcrypt -d -i ${USER_CONFIG_DIR}/${USER_CONFIG_TAR}.dec -o /tmp/${USER_CONFIG_TAR} 
	}

	[ -f /tmp/${USER_CONFIG_TAR} ] && {
		cd ${RUNNING_USER_CONFIG_DIR} && tar -xf /tmp/${USER_CONFIG_TAR} . 
		rm -f /tmp/${USER_CONFIG_TAR}
	}
}

update_userconfig() {
	apply_userconfig
	sync_romconfig_to_userconfig
}
