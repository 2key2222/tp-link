# this file will be included in 
#     /lib/wifi/mt{chipname}.sh

repair_wireless_uci() {
    echo "repair_wireless_uci" >>/tmp/wifi.log
    vifs=`uci show wireless | grep "=wifi-iface" | sed -n "s/=wifi-iface//gp"`
    echo $vifs >>/tmp/wifi.log

    ifn5g=0
    ifn2g=0
    for vif in $vifs; do
        local netif nettype device netif_new
        echo  "<<<<<<<<<<<<<<<<<" >>/tmp/wifi.log
        netif=`uci -q get ${vif}.ifname`
        nettype=`uci -q get ${vif}.network`
        device=`uci -q get ${vif}.device`
        if [ "$device" == "" ]; then
            echo "device cannot be empty!!" >>/tmp/wifi.log
            return
        fi
        echo "device name $device!!" >>/tmp/wifi.log
        echo "netif $netif" >>/tmp/wifi.log
        echo "nettype $nettype" >>/tmp/wifi.log
    
        case "$device" in
            mt7620 | mt7602e | mt7603e | mt7628 )
                netif_new="ra"${ifn2g}
                ifn2g=$(( $ifn2g + 1 ))
                ;;
            mt7610e | mt7612e )
                netif_new="rai"${ifn5g}
                ifn5g=$(( $ifn5g + 1 ))
                ;;
            * )
                echo "device $device not recognized!! " >>/tmp/wifi.log
                ;;
        esac                    
    
        echo "ifn5g = ${ifn5g}, ifn2g = ${ifn2g}" >>/tmp/wifi.log
        echo "netif_new = ${netif_new}" >>/tmp/wifi.log
            
        if [ "$netif" == "" ]; then
            echo "ifname empty, we'll fix it with ${netif_new}" >>/tmp/wifi.log
            uci -q set ${vif}.ifname=${netif_new}
        fi
        if [ "$nettype" == "" ]; then
            nettype="lan"
            echo "nettype empty, we'll fix it with ${nettype}" >>/tmp/wifi.log
            uci -q set ${vif}.network=${nettype}
        fi
        echo  ">>>>>>>>>>>>>>>>>" >>/tmp/wifi.log
    done
    uci changes >>/tmp/wifi.log
    uci commit
}


sync_uci_with_dat() {
    echo "sync_uci_with_dat($1,$2,$3,$4)" >>/tmp/wifi.log
    local device="$1"
    local datpath="$2"
    uci2dat -d $device -f $datpath > /tmp/uci2dat.log
}



chk8021x() {
        local x8021x="0" encryption device="$1" prefix
        #vifs=`uci show wireless | grep "=wifi-iface" | sed -n "s/=wifi-iface//gp"`
        echo "u8021x dev $device" > /tmp/802.$device.log
        config_get vifs "$device" vifs
        for vif in $vifs; do
                config_get ifname $vif ifname
                echo "ifname = $ifname" >> /tmp/802.$device.log
                config_get encryption $vif encryption
                echo "enc = $encryption" >> /tmp/802.$device.log
                case "$encryption" in
                        wpa+*)
                                [ "$x8021x" == "0" ] && x8021x=1
                                echo 111 >> /tmp/802.$device.log
                                ;;
                        wpa2+*)
                                [ "$x8021x" == "0" ] && x8021x=1
                                echo 1l2 >> /tmp/802.$device.log
                                ;;
                        wpa-mixed*)
                                [ "$x8021x" == "0" ] && x8021x=1
                                echo 1l3 >> /tmp/802.$device.log
                                ;;
                esac
                ifpre=$(echo $ifname | cut -c1-3)
                echo "prefix = $ifpre" >> /tmp/802.$device.log
                if [ "$ifpre" == "rai" ]; then
                    prefix="rai"
                else
                    prefix="ra"
                fi
                if [ "1" == "$x8021x" ]; then
                    break
                fi
        done
        echo "x8021x $x8021x, pre $prefix" >>/tmp/802.$device.log
        if [ "1" == $x8021x ]; then
            if [ "$prefix" == "ra" ]; then
                echo "killall 8021xd" >>/tmp/802.$device.log
                killall 8021xd
                echo "/bin/8021xd -d 9" >>/tmp/802.$device.log
                /bin/8021xd -d 9 >> /tmp/802.$device.log 2>&1
            else # $prefixa == rai
                echo "killall 8021xdi" >>/tmp/802.$device.log
                killall 8021xdi
                echo "/bin/8021xdi -d 9" >>/tmp/802.$device.log
                /bin/8021xdi -d 9 >> /tmp/802.$device.log 2>&1
            fi
        else
            if [ "$prefix" == "ra" ]; then
                echo "killall 8021xd" >>/tmp/802.$device.log
                killall 8021xd
            else # $prefixa == rai
                echo "killall 8021xdi" >>/tmp/802.$device.log
                killall 8021xdi
            fi
        fi
}


# $1=device, $2=module
reinit_wifi() {
    echo "reinit_wifi($1,$2,$3,$4)" >>/tmp/wifi.log
    local device="$1"
    local module="$2"
    config_get vifs "$device" vifs

    # shut down all vifs first
    for vif in $vifs; do
        config_get ifname $vif ifname
        ifconfig $ifname down
    done

    # in some case we have to reload drivers. (mbssid eg)
    #ref=`cat /sys/module/$module/refcnt`
    #if [ $ref != "0" ]; then
    #    # but for single driver, we only need to reload once.
    #    echo "$module ref=$ref, skip reload module" >>/tmp/wifi.log
    #else
    #    echo "rmmod $module" >>/tmp/wifi.log
    #    rmmod $module
    #    echo "insmod $module" >>/tmp/wifi.log
    #    insmod $module
    #fi

    # bring up vifs
    for vif in $vifs; do
        config_get ifname $vif ifname
        config_get disabled $vif disabled
        echo "ifconfig $ifname down" >>/tmp/wifi.log
        if [ "$disabled" == "1" ]; then
            echo "$ifname marked disabled, skip" >>/tmp/wifi.log
            continue
        else
            echo "ifconfig $ifname up" >>/tmp/wifi.log
            ifconfig $ifname up
        fi
    done

    chk8021x $device
}

prepare_ralink_wifi() {
    echo "prepare_ralink_wifi($1,$2,$3,$4)" >>/tmp/wifi.log
    local device=$1
    config_get channel $device channel
    config_get ssid $2 ssid
    config_get mode $device mode
    config_get ht $device ht
    config_get country $device country
    config_get regdom $device regdom

    # HT40 mode can be enabled only in bgn (mode = 9), gn (mode = 7)
    # or n (mode = 6).
    HT=0
    [ "$mode" = 6 -o "$mode" = 7 -o "$mode" = 9 ] && [ "$ht" != "20" ] && HT=1

    # In HT40 mode, a second channel is used. If EXTCHA=0, the extra
    # channel is $channel + 4. If EXTCHA=1, the extra channel is
    # $channel - 4. If the channel is fixed to 1-4, we'll have to
    # use + 4, otherwise we can just use - 4.
    EXTCHA=0
    [ "$channel" != auto ] && [ "$channel" -lt "5" ] && EXTCHA=1
    
}

# added by YangDi, order vap
order_vifs(){
	local all_vifs="$@"
	local ordered_vifs
	local host_vifs
	local guest_vifs
	local wds_vifs
	local v
	
	for v in $all_vifs; do
		case "$v" in
			ra0|rai0) append host_vifs "$v";;
			apcli*) append wds_vifs "$v";;
			*) append guest_vifs "$v";;
		esac
	done

	append ordered_vifs "$host_vifs"
	append ordered_vifs "$guest_vifs"
	append ordered_vifs "$wds_vifs"

	echo ${ordered_vifs}
}
# end

scan_ralink_wifi() {
    local device="$1"
    local module="$2"
    local vifs mode ap sta disabled
	
    config_get vifs "$device" vifs
    for vif in $vifs; do
        config_get_bool disabled "$vif" disabled
        [ $disabled == 0 ] || continue
		
        config_get mode "$vif" mode
        append "$mode" "$vif"
    done
    config_set "$device" vifs "$(order_vifs ${ap:+$ap }${sta:$sta})"
	
    echo "scan_ralink_wifi($1,$2,$3,$4)" >>/tmp/wifi.log
    #repair_wireless_uci
    sync_uci_with_dat $device /etc/wireless/$device/$module.dat
}

disable_ralink_wifi() {
    echo "disable_ralink_wifi($1,$2,$3,$4)" >>/tmp/wifi.log
    local device="$1"
    config_get vifs "$device" vifs
    for vif in $vifs; do
        config_get ifname $vif ifname
        ifconfig $ifname down
    done

    # kill any running ap_clients
    killall ap_client || true
}

add_guest_to_br()
{
	local guest_ifaces=$(uci show "guest_network" | grep "ifname" | cut -d "=" -f 2)
	
	for ifname in $guest_ifaces; do
		brctl addif br-lan "$ifname"
	done
}

enable_ralink_wifi() {
    echo "enable_ralink_wifi($1,$2,$3,$4)" >>/tmp/wifi.log
    local device="$1"
    config_get vifs "$device" vifs

    # bring up vifs
    for vif in $vifs; do
        config_get ifname $vif ifname
        config_get disabled $vif disabled
        ifconfig $ifname down
        echo "ifconfig $ifname down" >>/dev/null
        if [ "$disabled" == "1" ]; then
            echo "$ifname marked disabled, skip" >>/dev/null
            continue
        else
            echo "ifconfig $ifname up" >>/dev/null
            ifconfig $ifname up
        fi
        local net_cfg bridge
        net_cfg="$(find_net_config "$vif")"
        [ -z "$net_cfg" ] || {
            bridge="$(bridge_interface "$net_cfg")"
            config_set "$vif" bridge "$bridge"
            start_net "$ifname" "$net_cfg"
        }
        set_wifi_up "$vif" "$ifname"
    done
	
	[ "1" == "$WIFI_FIRST_START" ] && add_guest_to_br
}

detect_ralink_wifi() {
	# create /tmp/etc/mtk_wireless
	/usr/bin/lua "/lib/wifi/translate.lua" "create_mtk_uci"
	# /etc/config/wireless and /tmp/etc/mtk_wireless
	/usr/bin/lua "/lib/wifi/translate.lua" "web2cfg"
}

# added by YandDi, for get macaddr tail
get_mac_tail(){
	[ -z $1 ] && echo 'AABBCC' && return 1
	
	local config=$1
	local dev=$2
	local offset=8
	local tail
	local tmp=
	
	[ -n "$3" ] && offset=$((12-$3))
	
	tmp=$(uci_get "$config" "$dev" "macaddr")
	tmp=${tmp//:/}
	tmp=${tmp:$offset}
	tail=$(echo "${tmp}" | tr "[a-z]" "[A-Z]")
	
	echo ${tail}
}
# end #

#begin: added by YangDi
# Force all clients to renew ip address if DUT's lan ip is updated.
slp_reload_wifi(){
	local host_ifnames=$(uci -c "/tmp/etc/" show "mtk_wireless" | grep "ifname" | grep "ra" | cut -d "=" -f 2)
	local guest_ifnames=$(uci show "guest_network" | grep "ifname" | cut -d "=" -f 2)
	local all_ifnames="$host_ifnames $guest_ifnames"
	local br_vifs=$(brctl show)
	local is_in_br is_up
	
	# Kickout all AP's clients to force them re-assoc.
	# Why choose kickout but NOT simpel down/up interface? 
	# Because guest reload will down/up all VAPs(include apcli*) to update encryption config and
	# this will trigger notify smart dhcp module again.
	for ifname in $all_ifnames; do
		local sta_mac_entries mac
		is_in_br=$(echo "$br_vifs" | grep "$ifname")
		is_up=$(ifconfig "$ifname" | grep "UP")
		
		if [ -n "$is_in_br" -a -n "$is_up" ]; then
			sta_mac_entries=$(iwpriv "$ifname" "get_mac_table" | grep -o "[0-9a-fA-F]\{12\}")
			for m in $sta_mac_entries; do
				mac="${m:0:2}:${m:2:2}:${m:4:2}:${m:6:2}:${m:8:2}:${m:10:2}"
				iwpriv "$ifname" set DisConnectSta="$mac"
				echo "iwpriv $ifname set DisConnectSta=$mac" > /dev/null
			done
		fi
	done
}
#end: added by YangDi

# begin: added by YangDi
mtk_turbo_cmd()
{
	local ifname="$1"
	local switch="$2"
	
	/usr/sbin/iwpriv "$ifname" set obtw=disable
	case "$switch" in
	# turbo ON
	1)
	iwpriv "$ifname" set obtw=cck1m_8_cck5m_8_ofdm6m_8_ofdm12m_8_ofdm24m_4_ofdm48m_3_ofdm54m_0_ht20mcs0_8_ht20mcs1_8_ht20mcs3_8_ht20mcs5_4_ht20mcs6_3_ht20mcs7_1_ht40mcs0_8_ht40mcs1_8_ht40mcs3_8_ht40mcs5_4_ht40mcs6_3_ht40mcs7_1;
	return 0
	;;
	# turbo OFF
	0)
	iwpriv "$ifname" set obtw=cck1m_0_cck5m_0_ofdm6m_0_ofdm12m_0_ofdm24m_0_ofdm48m_0_ofdm54m_0_ht20mcs0_0_ht20mcs1_0_ht20mcs3_0_ht20mcs5_0_ht20mcs6_0_ht20mcs7_0_ht40mcs0_0_ht40mcs1_0_ht40mcs3_0_ht40mcs5_0_ht40mcs6_0_ht40mcs7_0;
	return 0
	;;
	esac
	
	return 1
}

mtk_set_turbo()
{
	local SCRIPT_TURBO="/lib/turbo/turbo.sh"
	local host2g_ifname host2g_disabled guest2g_enabled guest2g_ifname turboon2g
	local is_2g4_led_on=0
	local ret=1
	
	host2g_disabled=$(uci_get wireless ra0 disabled)
	host2g_ifname=$(uci_get wireless ra0 ifname)
	guest2g_enabled=$(uci_get guest_network guest_2g enable)
	guest2g_ifname=$(uci_get guest_network guest_2g ifname)
	turboon2g=$(uci_get wireless mt7628 turboon)
	
	if [ "0" == "$host2g_disabled" -o "1" == "$guest2g_enabled" ]; then
		is_2g4_led_on=1
	fi

	# 2.4G turbo set
	# host or guest must exist
	if [ -e /sys/class/net/$host2g_ifname -o -e /sys/class/net/$guest2g_ifname ]; then
		if [ "1" == "$is_2g4_led_on" ]; then
			# we only use host2g ifname because it works in all vaps.
			mtk_turbo_cmd "$host2g_ifname" "$turboon2g"
			ret="$?"
		else
			# all 2.4G vap down, we should turn off turbo LED.
			if [ -f "$SCRIPT_TURBO" ]; then
				. "$SCRIPT_TURBO"
				if eval "type switch_led"; then
					switch_led "off"
				fi
			fi
		fi
	fi
	
	# 5G turbo set : NOT support NOW.
	
	return $ret
}

mtk_sys_led_blink()
{
	local interval="100"
	local system_led_gpio_base_path="/sys/class/leds/slp:status/"
	
	if [ "$1" -gt 0 ]; then
		interval="$1"
	fi
	
	echo "$interval" > "${system_led_gpio_base_path}delay_on"
	echo "$interval" > "${system_led_gpio_base_path}delay_off"
}

mtk_calculate_check()
{
	local calibration_file="/tmp/calibration"
	local cal=$(cat "$calibration_file")
	
	if [ 0 == "$cal" ]; then
		mtk_sys_led_blink 100
	fi
}
# end: added by YangDi


