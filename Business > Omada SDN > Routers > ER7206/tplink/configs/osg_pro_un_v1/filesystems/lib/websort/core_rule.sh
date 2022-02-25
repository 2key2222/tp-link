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

#add groupname content
#delete groupname
{
    flock 8
    local type=$1
    case $type in
        add)
            local groupname=$2
            local content=$3
            urlset create $groupname ac website 200 # a number is needed,how much it allocated
            for i in $content;do
                echo $i | grep -q "^*." && i=${i:1} || i="\$${i}"
                i=${i}_
                urlset add $i $groupname
            done
            urlset add '#end#' $groupname
        ;;
        delete)
            local groupname=$2
            urlset destroy $groupname
        ;;

        update)
            local groupname=$2
            local content=$3

            urlset flush $groupname
            for i in $content;do
                echo $i | grep -q "^*." && i=${i:1} || i="\$${i}"
                i=${i}_
                urlset add $i $groupname
            done
             urlset add '#end#' $groupname
        ;;
        *)
            return
        ;;
    esac
} 8<>/tmp/web_sort

