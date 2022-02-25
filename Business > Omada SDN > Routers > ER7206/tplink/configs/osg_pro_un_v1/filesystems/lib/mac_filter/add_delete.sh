#!/bin/sh

# Copyright (C) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# 
# brief      dynamically add or delete an entry from ipset
# author     Luo pei
# version    1.0.0 
# date         31Dec2015
# history     31Dec2015    Luopei    Create the file
#            

local action=$1

case $action in 
    add)
       local mac=$2
       ipset add mac_set $mac
    ;;
    del)
       local mac=$2
       ipset del mac_set $mac
    ;;
    *)
        return
    ;;
esac