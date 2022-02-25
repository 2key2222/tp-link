#!/bin/sh
. /lib/zone/zone_api.sh
. /lib/firewall/core_tpfirewall.sh


case ${ACTION} in
	DELETE)  
		[ -n "${interfaces}" ] && {
		    echo "interfaces=$interfaces" >> /tmp/firewall_wanhook.log    
		    interfaces=${interfaces//,/ } 
			for element in $interfaces   
			do  
				echo "element=$element"  >> /tmp/firewall_wanhook.log
				# local inter=$(zone_get_effect_ifaces $element)  
				fw_event_interface "$element" del
			done  
		}
	;;
	ADD)
		#[ -n "${interfaces}" ] && {
		#    echo "interfaces=$interfaces" >> /tmp/firewall_wanhook.log    
		#    interfaces=${interfaces//,/ } 
		#	for element in $interfaces   
		#	do  
		#		echo "element=$element"  >> /tmp/firewall_wanhook.log
		#		local inter=$(zone_get_effect_ifaces $element)  
		#		fw_event_interface "$inter" add
		#	done  
		#}
	;;
	WANMOD)
		[ -n "${interfaces}" ] && {
		    echo "interfaces=$interfaces" >> /tmp/firewall_wanhook.log    
		    interfaces=${interfaces//,/ } 
			for element in $interfaces   
			do  
				echo "element=$element"  >> /tmp/firewall_wanhook.log
				#local inter=$(zone_get_effect_ifaces $element)  
				fw_event_interface "$element" del
				#fw_event_interface "$element" add
			done  
		}
	;;
esac