#!/bin/sh
# Copyright (C) 2006-2013 OpenWrt.org
# Copyright (C) 2010 Vertical Communications

#add directories here
RAMFS_DIRS="/etc/ /www/luci-static/resources/authserver/"


get_conffiles() {
    local file="$1"  
    ( (sed -ne '/^[[:space:]]*$/d; /^#/d; p' /etc/sysupgrade.conf /lib/upgrade/keep.d/* 2>/dev/null);opkg list-changed-conffiles ) | sort -u > "$file"    
} 

get_cfg_sync() {
    local file="$1"    
    find /etc/cfgsync.d/ -type f|sort -n > "$file"
}

cfg_dftcfg_to_usercfg() {

    if [ `ls /tmp/userconfig | wc -l` != "0" ]; then
        echo "rm remain files in userconfig" > /dev/console
        rm -rf /tmp/userconfig/*
    fi

    get_conffiles "/tmp/conffiles.tmp"

    echo "Copy romconfig to userconfig"
    [ "$fs_overlay_support" == "n" ] && {
        for dir in $RAMFS_DIRS;
        do
            tmp_dir=/tmp/`basename ${dir}`_tmp           
            cp -a ${dir} ${tmp_dir}
            mount -t ramfs -n none ${dir}
            cp -a ${tmp_dir}/* ${dir}
            rm -rf ${tmp_dir}        
        done        
    }

    #copy conffiles to jffs2
    cfg_dir=/tmp/userconfig
    for CONFFILES in `cat /tmp/conffiles.tmp`
    do
        DIR=${CONFFILES%/*}
        #echo "mkdir ${cfg_dir}${DIR}"
        mkdir -p ${cfg_dir}${DIR}
        #DIR or FILE
        STRLEN=${#CONFFILES}
        let "STRLEN-=1"
        STRTYPE=${CONFFILES:$STRLEN}
        if [ "$STRTYPE" == "/" ];then
            PARENT_DIR=`dirname $CONFFILES`
            #echo "cp -a ${CONFFILES} ${cfg_dir}${PARENT_DIR}"
            cp -a ${CONFFILES} ${cfg_dir}${PARENT_DIR}       
        else
            #echo "cp -a ${CONFFILES} ${cfg_dir}${CONFFILES}"
            cp -a ${CONFFILES} ${cfg_dir}${CONFFILES}              
        fi
    done	

    rm /tmp/conffiles.tmp

    touch "/tmp/userconfig/userpwd_default.tmp"
    echo "Default" > "/tmp/userconfig/userpwd_default.tmp"
    cp "/tmp/userconfig/userpwd_default.tmp" "/tmp/userpwd_default.tmp"

    touch "/tmp/userconfig/userconfig_default.tmp"
    echo "Default" > "/tmp/userconfig/userconfig_default.tmp"
    cp "/tmp/userconfig/userconfig_default.tmp" "/tmp/userconfig_default.tmp"
}

cfg_userconfig_to_memory() {
	get_conffiles "/tmp/conffiles.tmp"
	get_cfg_sync "/tmp/cfgsync.tmp"

    if [ ! -f "/tmp/userconfig/userconfig_default.tmp" ];then
	echo "Warning:Detect userconfig_default file not exist!" > /dev/console
	touch "/tmp/userconfig/userconfig_default.tmp"
	echo "Default" > "/tmp/userconfig/userconfig_default.tmp"
    fi

    echo "Copy userconfig to memory"
    [ "$fs_overlay_support" == "n" ] && {
        for dir in $RAMFS_DIRS;
        do
            tmp_dir=/tmp/`basename ${dir}`_tmp           
            cp -a ${dir} ${tmp_dir}
            mount -t ramfs -n none ${dir}
            cp -a ${tmp_dir}/* ${dir}
            rm -rf ${tmp_dir}        
        done        
    }

    #Configuration compatibility
    cfg_dir=/tmp/userconfig
    for CFGSYNC in `cat /tmp/cfgsync.tmp`
    do
        chmod 0700 $CFGSYNC
        $CFGSYNC "/" "/tmp/userconfig/"
    done
    #copy jffs2 to conffiles
    for CONFFILES in `cat /tmp/conffiles.tmp`
    do
        isDiff=`diff ${cfg_dir}${CONFFILES} ${CONFFILES} 2>/dev/null|wc -l`
        if [ ! -e "${CONFFILES}" ] || [ $isDiff -gt 0 ];then
            DIR=${CONFFILES%/*}
            #echo "mkdir -p ${DIR}"
            mkdir -p ${DIR}
            #DIR or FILE
            STRLEN=${#CONFFILES}
            let "STRLEN-=1"
            STRTYPE=${CONFFILES:$STRLEN}                           
            if [ "$STRTYPE" == "/" ];then
                PARENT_DIR=`dirname $CONFFILES`
                #echo "cp -a ${cfg_dir}${CONFFILES} ${PARENT_DIR}"
                cp -a ${cfg_dir}${CONFFILES} ${PARENT_DIR}
            else
                #echo "cp -a ${cfg_dir}${CONFFILES} ${CONFFILES}"
                cp -a ${cfg_dir}${CONFFILES} ${CONFFILES}
            fi                        
        fi
    done	

    cp "/tmp/userconfig/userconfig_default.tmp" "/tmp/userconfig_default.tmp"
    cp "/tmp/userconfig/userpwd_default.tmp" "/tmp/userpwd_default.tmp"
	
    rm /tmp/conffiles.tmp
    rm /tmp/cfgsync.tmp    
}

cfg_copy()
{
fs=$(find  "$1")
for i in $fs;
do
    [ -d $i ] && {
        mkdir -p $2/$i
       }
done

for i in $fs;
do
    [ -f $i ] && {
        if [ -f $2/$i ] ;then
            difs=$(diff -q $i  $2/$i)
            [ -z "$difs" ] || cp -f $i  $2/$i
        else
            cp -f $i $2/$i
        fi
       }
done

}

cfg_save_to_flash() {

    exec 3<>"/tmp/cfg_save.stat"
    flock -w 30 3
    [ $? -eq 1 ] && { echo "lock fail"; exit; }
    
    #status=`cat /tmp/cfg_save.stat`    
    #if [ "$status" == "Saved" ];then
    #    echo "Saved"
    #    exit
    #fi    
    touch "/tmp/conffiles.tmp"
    get_conffiles "/tmp/conffiles.tmp"
    echo "Saving" > "/tmp/cfg_save.stat"
    
    cfg_dir=/tmp/userconfig
    for configs in `cat /tmp/conffiles.tmp`
    do
        DIR=${configs%/*}
        mkdir -p ${cfg_dir}${DIR}
        #DIR or FILE
        STRLEN=${#configs}
        let "STRLEN-=1"
        STRTYPE=${configs:$STRLEN}
        
        isDiff=`diff ${configs} ${cfg_dir}${configs} 2>/dev/null|wc -l`
        if [ ! -e "${cfg_dir}${configs}" ] || [ $isDiff -gt 0 ];then
            if [ "$STRTYPE" == "/" ];then
                cfg_copy ${configs} ${cfg_dir} 
            else
                #echo "cp -a ${configs} ${cfg_dir}${configs}"
                cp -a ${configs} ${cfg_dir}${configs}
            fi
        fi
    done    
    cat /dev/null > /tmp/conffiles.tmp
    
    cp "/tmp/userconfig_default.tmp" "/tmp/userconfig/userconfig_default.tmp"
    cp "/tmp/userpwd_default.tmp" "/tmp/userconfig/userpwd_default.tmp"
    echo "Saved" > "/tmp/cfg_save.stat"
    echo "Saved"
}

cfg_reset_to_dftcfg() {

    exec 3<>"/tmp/cfg_save.stat"
    flock -w 30 3
    [ $? -eq 1 ] && { echo "lock fail"; return 1; } 

    rm -f /tmp/userconfig/userconfig_default.tmp
    rm -rf /tmp/userconfig/*

    echo "Saved" > "/tmp/cfg_save.stat"
    return 0
}

cfg_modify() {
    exec 3<>"/tmp/cfg_save.stat"
    flock -w 30 3 
    [ $? -eq 1 ] && { echo "lock fail"; exit; } 
    
    echo "Modify" > "/tmp/userconfig_default.tmp" 
    echo "Not Saved" > "/tmp/cfg_save.stat"
    echo "Modify OK"

}

dft_pwd_modify() {
	
    echo "Modify" > "/tmp/userconfig_default.tmp" 
    echo "Modify" > "/tmp/userpwd_default.tmp" 
    echo "Modify OK"
	
    #cfg_save_to_flash
    cp "/etc/config/accountmgnt" "/tmp/userconfig/etc/config/accountmgnt"
    
    cp "/tmp/userconfig_default.tmp" "/tmp/userconfig/userconfig_default.tmp"
    cp "/tmp/userpwd_default.tmp" "/tmp/userconfig/userpwd_default.tmp"
}
cfg_status_get() {
    exec 3<>"/tmp/cfg_save.stat"
    flock -w 30 3 
    [ $? -eq 1 ] && { echo "Saved"; exit; }
    
    cat "/tmp/cfg_save.stat"
}

cfg_check_isdftcfg() {
    if [ -f "/tmp/userconfig_default.tmp" ];then
        cat "/tmp/userconfig_default.tmp"
    else
        echo "Default"
    fi
}

pwd_check_isdftcfg() {
    if [ -f "/tmp/userpwd_default.tmp" ]; then
        cat "/tmp/userpwd_default.tmp"
    else
        echo "Default"
    fi
}

cfg_file_check_isdftcfg() {
    if [ -n "$1" ]; then
        isDiff=`diff /etc/config/$1 /tmp/.default_config/$1 2>/dev/null|wc -l`
        if [ $isDiff -gt 0 ]; then
            echo -n "Modified"
        else
            echo -n "Default"
        fi
    else
        echo -n "Error"
    fi
}

cfg_memory_reset_to_dftcfg() {
    local config="$1"
    cp /tmp/.default_config/$config /etc/config/$config
}

rootfs_init_etc_ramfs() {
    [ ! -e /tmp/.default_config ] && mkdir -p /tmp/.default_config
    cp -rf /etc/config/* /tmp/.default_config/ 
    echo "=========================USERCONFIG INITIAL======================"
    if [ -f "/tmp/userconfig/userconfig_default.tmp" ] ; then
        cfg_userconfig_to_memory
    else
        cfg_dftcfg_to_usercfg
    fi
    
    touch /tmp/cfg_save.stat
    echo "Saved" > "/tmp/cfg_save.stat"
    echo "=========================USERCONFIG DONE======================"
}
