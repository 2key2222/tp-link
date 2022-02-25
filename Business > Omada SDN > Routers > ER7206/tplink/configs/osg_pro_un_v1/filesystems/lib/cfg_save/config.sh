#!/bin/sh 
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     cfg_save config.sh
# brief    
# author   Qian Xujun
# version  1.0.0
# date     11Nov15
# histry   arg 1.0.0, 08June15, Chen chen, Create the file.

. /lib/functions/userconfig.sh

if [ $# -eq 1 ]; then
    if [ "$1" == "save" ];then
        cfg_save_to_flash
        exit
    elif [ "$1" == "status" ];then
        cfg_status_get
        exit
    elif [ "$1" == "modify" ];then
        cfg_modify
        cfg_save_to_flash
        exit
    elif [ "$1" == "modify_no_save" ]; then
        cfg_modify
        exit
    elif [ "$1" == "pwd_modify" ];then
        dft_pwd_modify
        exit
    elif [ "$1" == "check_dft_pwd" ];then
        pwd_check_isdftcfg
        exit
    elif [ "$1" == "firstboot" ];then
        cfg_reset_to_dftcfg
        exit
    elif [ "$1" == "check_default" ];then
        cfg_check_isdftcfg
        exit
    else
        echo "Invalid option para."
        exit
    fi  
else
    echo "Invalid func para."
    exit
fi

