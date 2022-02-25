#!/bin/sh
#
# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief      create web_sort urlset
# author     luopei
# version    1.0.0 
# date         30Dec2015
# history     30Dec2015    luopei    Create the file
#   
. /lib/websort/config.sh

fw_load_one(){
    local members
    local name

    config_get members $1 members
    config_get name $1 name

     urlset create $name ac website 200 # a number is needed,how much it allocated
    for i in $members;do
        echo $i | grep '^*.' && i=${i:1} || i="\$${i}"
        i=${i}_
        urlset add $i $name
    done
    urlset add '#end#' $name
}

websort_start(){
    fw_config_append websort
    config_foreach fw_load_one websort
}

websort_stop(){
    urlset destroy website #some flag
}

websort_restart(){
    websort_stop
    websort_start
}

websort_reload(){
    websort_restart
}

