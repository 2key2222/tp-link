#!/bin/sh
. /lib/pptp/pptp-startup.sh
. /lib/pppox/pppox-functions.sh
. /lib/pptp/pptp-ifdevice-info.sh

options="#debug\n#logfile /tmp/pptp-server.log\n\
auth\nlcp-echo-failure 3\n\
lcp-echo-interval 60\ndefault-asyncmap\nmtu 1420\n\
mru 1420\nnobsdcomp\nnodeflate\n\
proxyarp\n\
noccp\n\
mppe required,stateless\n\
novj\n\
require-mschap-v2\n\
refuse-chap\n\
refuse-mschap\n\
refuse-eap\n\
refuse-pap\n\
#ms-dns 172.16.1.1\n\
#plugin radius.so\n\
#radius-config-file /etc/radius.conf\n\
plugin ppp4tplink.so\n\
plugin libippool.so"

# $1 is for ,need to change this
local service=$1
local bindif=$2
local enable=$3
local mppe=$4
local authtype=$5
#echo "add-service" > /dev/console
local path=${pppox_pptp_server_path}/$service/config
mkdir -p $path  #path
touch $path/${pppox_pptptype}.type #/tmp/pptp/server/server2/config/pptp.type
touch $path/${pppox_configname} 

#/tmp/pptp/server/server2/config/myconfig
#config pns
     #   option bindif 'WAN2'
     #   option authtype 'local'
     #   option enable 'on'
uci -c ${path} add ${pppox_configname} pns
uci -c ${path} set ${pppox_configname}.@pns[-1].bindif=$bindif
uci -c ${path} set ${pppox_configname}.@pns[-1].authtype=$authtype
uci -c ${path} set ${pppox_configname}.@pns[-1].enable=$enable
uci -c ${path} commit ${pppox_configname}
	
#local devices=$(zone_get_effect_devices $bindif)
local if=$(zone_get_effect_main_wan_ifaces $bindif)
local devices=$(zone_get_device_byif $if)
pptp_set_ifdevice_info "${bindif}"  "${service}"
fifo_write "$service#$devices"
	#wan file is like 'service_name#effective_devices'
echo "$service#$devices" >>$pppox_pptp_server_path/wan  #tmp/pptp/server/wan
# for pppd started by pptpd,add a file called options.pptpd
echo -e $options >$path/options.pptpd
local lcp_echo=$(uci get pptp-server-global.@global[-1].lcpechointerval)
sed -r -i "/lcp-echo-interval/s/[[:digit:]]+/$lcp_echo/" $path/options.pptpd
enable_mppe $mppe $path options.pptpd
enable_packet $enable $bindif
echo "path ${pppox_pptp_server_path}/$service" >>$path/options.pptpd
echo "zonex ${bindif}" >> $path/options.pptpd
echo "tunnel-proto pptp" >> $path/options.pptpd

#standalone mode: need load vpn users
if [ ! -f /tmp/pppox.controller.mode ]; then
	pppox_reset_loadflag ${pppox_pptptype}
	#echo "pppox_reset_loadflag" > /dev/console
	pppox_load_user ${pppox_pptptype} $service
fi

