#!/bin/sh
#author: wangdechu
#
#do not change this file
#

pppox_l2tp_main_path=/tmp/l2tp
pppox_pptp_main_path=/tmp/pptp
pppox_pppoe_main_path=/tmp/pppoe

#server path of l2tp pptp pppoe
pppox_l2tp_server_path=${pppox_l2tp_main_path}/server
pppox_pptp_server_path=${pppox_pptp_main_path}/server
pppox_pppoe_server_path=${pppox_pppoe_main_path}/server

#client path of l2tp pptp pppoe
pppox_l2tp_client_path=${pppox_l2tp_main_path}/client
pppox_pptp_client_path=${pppox_pptp_main_path}/client
pppox_pppoe_client_path=${pppox_pppoe_main_path}/client

#type of l2tp pptp pppoe
pppox_l2tptype=l2tp
pppox_pptptype=pptp
pppox_pppoetype=pppoe
pppox_autotype=auto

#pppd info path
pppox_ppppath=/tmp/ppp

#something about user-secrets
pppox_user_configname=user-secrets
pppox_user_options="username password type networktype localip ippool ms_dns maxsessions netmode remotesubnet workmode local_network serverlist"
pppox_if_config=if-config
pppox_user_secrets=user-secrets
pppox_profile=-profile
pppox_profilex=-profilex

#tmp path for dealing with user-secrets
pppox_path=/tmp/pppox
pppox_l2tp_path=${pppox_path}/l2tp
pppox_pptp_path=${pppox_path}/pptp
pppox_pppoe_path=${pppox_path}/pppoe

#common name of config for l2tp pptp pppoe, no matter server or client
pppox_configname=myconfig

#plugin name used for pppd
pppox_ppp4tplinkso=ppp4tplink.so
pppox_ippoolso=libippool.so