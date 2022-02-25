#!/bin/sh /etc/rc.common
# Copyright(c) 2011-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file      nat_config.sh
# brief    
# author    Chen chen
# version   1.1.0
# date      21Apr15
# history   arg 1.0.0, 21Apr15, Chen chen, Create the file.
#           arg 1.1.0, 21Dec17, Zhangzhongwei, Rewrite the file.

NAT_READY=/tmp/nat.ready

# Root chain names
NAT_PREROUTNIG_ROOT="prerouting_rule"
NAT_POSTROUTING_ROOT="postrouting_rule"

# Modules chain names
MOD_VPN="vpn"
MOD_ONE="onenat"
MOD_VS="vs"
MOD_PT="pt"
MOD_NAPT="multinat"
MOD_UPNP="upnp"
MOD_DMZ="dmz"

NAT_ZONE_LAN="lan"
