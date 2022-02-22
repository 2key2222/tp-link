#!/bin/bash

# ./tplink_patch_clean.sh $(BASE_DIR)

tplink_build_dir=$1/build/tplink
echo "clean the tplink patch"

if [ -d $tplink_build_dir ]
then
    rm -rf $tplink_build_dir
fi
rm -rf $1/usrfs
rm -f $1/rootfs_deviceMap


    
