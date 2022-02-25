# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     zone_init.sh
# bief     Config the zone info
# author   Yuan Fengjia
# vesion   1.0.0
# history  1.0.0, 13May15, Yuanfengjia, Ceate the file

. /lib/pppox/pppox-wheader.sh

singlewan=0
WAN1=WAN1

scan_interfaces() {
	local config="$1"
	local ifname type device l3dev proto t_poe_enable 
	
	#echo "config=$config"
	
	config_get type "$config" type
	#echo "type=$type"
	
	config_get ifname "$config" ifname
	#echo "ifname=$ifname"
	
	config_get device "$config" device "$ifname"
	#echo "device=$device"
	
	config_get proto "$config" proto
	#echo "proto=$proto"

	
	[ "lan" == "$config" ] && {
	  uci_set zone LAN if_eth lan
          uci_set zone LAN dev_eth br-lan
          uci_commit zone
	}
	
	[ "static" == "$proto" ] || [ "dhcp" == "$proto" ] || [ "bigpond" == "$proto" ] && {
	  #echo "eth interafce"
	  if [ "$type" == "bridge" ]; then
	    device="br-$config"
	  elif [ -n "$ifname" -a -n "$device" ]; then
	    device="$ifname"
	  fi

	  [ "wan1_eth" == "$config" ] && { 
	    #echo "wan1 eth interafce"
            uci_set zone ${WAN1} if_eth "$config"
            uci_set zone ${WAN1} dev_eth "$device"
	    [ "$type" == "bridge" ] && uci_set zone ${WAN1} dev_eth br-wan1_eth
            uci_commit zone
    }
    
    [ "wan2_eth" == "$config" ] && { 
      #echo "wan2 eth interafce"
      uci_set zone WAN2 if_eth "$config"
      uci_set zone WAN2 dev_eth "$device"
      uci_commit zone
    }
    
    [ "wan3_eth" == "$config" ] && { 
      #echo "wan3 eth interafce"
      uci_set zone WAN3 if_eth "$config"
      uci_set zone WAN3 dev_eth "$device"
      uci_commit zone
    }
    
    [ "wan4_eth" == "$config" ] && { 
      #echo "wan4 eth interafce"
      uci_set zone WAN4 if_eth "$config"
      uci_set zone WAN4 dev_eth "$device"
      uci_commit zone
    }
  }

  config_get t_poe_enable  "$config" t_poe_enable 
  [ "pppoe" == "$proto" -a "1" == "$t_poe_enable" ] && {
    #echo "pppoe interafce"
    [ "wan1_poe" == "$config" ] && {
      #echo "wan1 pppoe interafce"
      uci_set zone ${WAN1} if_1 "$config"
      uci_set zone ${WAN1} dev_1 ${pppoe_header}${config}
      uci_commit zone
    }
    
    [ "wan2_poe" == "$config" ] && {
      #echo "wan2 pppoe interafce"
      uci_set zone WAN2 if_1 "$config"
      uci_set zone WAN2 dev_1 ${pppoe_header}${config}
      uci_commit zone
    }
    
    [ "wan3_poe" == "$config" ] && {
      #echo "wan3 pppoe interafce"
      uci_set zone WAN3 if_1 "$config"
      uci_set zone WAN3 dev_1 ${pppoe_header}${config}
      uci_commit zone
    }
    
    [ "wan4_poe" == "$config" ] && {
      #echo "wan4 pppoe interafce"
      uci_set zone WAN4 if_1 "$config"
      uci_set zone WAN4 dev_1 ${pppoe_header}${config}
      uci_commit zone
    }
  }
  
  [ "pptp" == "$proto" -a "1" == "$t_poe_enable" ] && {
    #echo "pptp interafce"
    [ "wan1_poe" == "$config" ] && {
      #echo "wan1 pptp interafce"
      uci_set zone ${WAN1} if_1 "$config"
      uci_set zone ${WAN1} dev_1 ${pptp_header}${config}
      uci_commit zone
    }
    
    [ "wan2_poe" == "$config" ] && {
      #echo "wan2 pptp interafce"
      uci_set zone WAN2 if_1 "$config"
      uci_set zone WAN2 dev_1 ${pptp_header}${config}
      uci_commit zone
    }
    
    [ "wan3_poe" == "$config" ] && {
      #echo "wan3 pptp interafce"
      uci_set zone WAN3 if_1 "$config"
      uci_set zone WAN3 dev_1 ${pptp_header}${config}
      uci_commit zone
    }
    
    [ "wan4_poe" == "$config" ] && {
      #echo "wan4 pptp interafce"
      uci_set zone WAN4 if_1 "$config"
      uci_set zone WAN4 dev_1 ${pptp_header}${config}
      uci_commit zone
    }
  }
  
  [ "l2tp" == "$proto" -a "1" == "$t_poe_enable" ] && {
    #echo "l2tp interafce"
    [ "wan1_poe" == "$config" ] && {
      #echo "wan1 l2tp interafce"
      uci_set zone ${WAN1} if_1 "$config"
      uci_set zone ${WAN1} dev_1 ${l2tp_header}${config}
      uci_commit zone
    }
    
    [ "wan2_poe" == "$config" ] && {
      #echo "wan2 l2tp interafce"
      uci_set zone WAN2 if_1 "$config"
      uci_set zone WAN2 dev_1 ${l2tp_header}${config}
      uci_commit zone
    }
    
    [ "wan3_poe" == "$config" ] && {
      #echo "wan3 l2tp interafce"
      uci_set zone WAN3 if_1 "$config"
      uci_set zone WAN3 dev_1 ${l2tp_header}${config}
      uci_commit zone
    }
    
    [ "wan4_poe" == "$config" ] && {
      #echo "wan4 l2tp interafce"
      uci_set zone WAN4 if_1 "$config"
      uci_set zone WAN4 dev_1 ${l2tp_header}${config}
      uci_commit zone
    }
  }
  
}

scan_l2tp_interfaces() {
    local lac="$1"
    local tunnelname=""
   
    config_get tunnelname "$lac" tunnelname
    [ -n "$tunnelname" ] && {
        uci set zone.$tunnelname=iface
        uci_set zone $tunnelname iface "$tunnelname"
        uci_set zone $tunnelname dev "lt-${tunnelname}"
        uci_add_list zone VPN iface $tunnelname
        uci_commit zone
    }
}

scan_pptp_interfaces() {
    local pnc="$1"
    local tunnelname=""
    
    config_get tunnelname "$pnc" tunnelname
    [ -n "$tunnelname" ] && {
        uci set zone.$tunnelname=iface
        uci_set zone $tunnelname iface "$tunnelname"
        uci_set zone $tunnelname dev "pt-${tunnelname}"
        uci_add_list zone VPN iface $tunnelname
        uci_commit zone
    }
}

zone_conf_clean() {

  
  uci -q delete zone.LAN
  
  [ "${singlewan}" = "1" ] && uci -q delete zone.${WAN1}
  uci -q delete zone.WAN
  uci -q delete zone.WAN1  
  uci -q delete zone.WAN2                                    
  uci -q delete zone.WAN3                                    
  uci -q delete zone.WAN4                           
                                                                                               
  local ifaces=""                              
  config_load zone                             
  config_get ifaces VPN iface                                            
  for i in $ifaces                                           
  do                                                                                                   
      uci delete zone.$i                                     
  done                                                                                      
  uci -q delete zone.VPN                       
                                               
  uci set zone.LAN=zone                        
  uci set zone.${WAN1}=zone                            
  uci set zone.WAN2=zone                               
  uci set zone.WAN3=zone                               
  uci set zone.WAN4=zone                       
  uci set zone.VPN=zone                             
  uci_commit zone    
}

zone_conf_build() {
  singlewan=`uci get network.@interface_mode[0].singlewan 2>/dev/null`
  [ "${singlewan}" = "1" ] && WAN1=WAN
  zone_conf_clean
  
  config_load network
  config_foreach scan_interfaces interface
  
  #scan VPN interface
  config_load l2tp-client
  config_foreach scan_l2tp_interfaces lac
  
  config_load pptp-client
  config_foreach scan_pptp_interfaces pnc
}
