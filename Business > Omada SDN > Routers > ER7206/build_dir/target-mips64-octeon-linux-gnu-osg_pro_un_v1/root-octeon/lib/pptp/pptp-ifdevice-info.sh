#!/bin/sh
. /lib/pppox/pppox-default-variables.sh
. /lib/functions.sh
. /lib/zone/zone_api.sh

pptp_ifdevice_info=pptp-ifdevice-info
#1: WAN1, 2: client1|server1
pptp_set_ifdevice_info()
{
    local mif=$1
    local name=$2

    [ ! -f ${pppox_pptp_main_path}/${pptp_ifdevice_info} ] && touch ${pppox_pptp_main_path}/${pptp_ifdevice_info}

    mif=`zone_get_effect_main_wan_ifaces ${mif}`
    [ -z "${mif}" ] && { echo ""; return 0; }

    local device=`zone_get_device_byif ${mif}`
    device=${device%% *}

#   local lstate=`zone_get_iface_state ${mif}`
#   [ ${lstate} == "DOWN" ] && device=

    local ifsection
    local devsection
    if [ -n "${device}" ]; then 
        ifsection=if_${mif}
        ifsection=${ifsection//./_}
        #ifsection=${ifsection//-/_}
        devsection=dev_${device}
        devsection=${devsection//./_}
        #devsection=${devsection//-/_}
        uci -c ${pppox_pptp_main_path} set ${pptp_ifdevice_info}.${name}=info
        uci -c ${pppox_pptp_main_path} set ${pptp_ifdevice_info}.${name}.iff=${mif}
        uci -c ${pppox_pptp_main_path} set ${pptp_ifdevice_info}.${name}.dev=${device}
        uci -c ${pppox_pptp_main_path} commit ${pptp_ifdevice_info}
    fi
}

#1: client1|server1
pptp_remove_ifdevice_info()
{
    local name=$1
    uci -c ${pppox_pptp_main_path} delete ${pptp_ifdevice_info}.${name}
    uci -c ${pppox_pptp_main_path} commit ${pptp_ifdevice_info}
}
