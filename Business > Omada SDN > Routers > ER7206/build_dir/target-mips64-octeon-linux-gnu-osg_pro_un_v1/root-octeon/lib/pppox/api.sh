#!/bin/sh
#author: wangdechu

iface_ref_del()                                                                                             
{                                                                                                           
        [ -n "$1" ] || return 1                                                                               

		local config=network 
		
        for inface in $1; do                                                                                 
                ref=`uci get network.$inface.t_reference 2>/dev/null`                                       
                if [ -n "$ref" ]; then                                                                      
                        ref=$((ref-1))                                                         
                        [ ${ref} -lt 0 ] && ref=0           
                        uci set network.$inface.t_reference=$ref                                            
                else                                                                                        
                        ref=`uci get l2tp-client.$inface.t_reference 2>/dev/null`
						if [ -n "$ref" ]; then                                                                      
							ref=$((ref-1))                                                     
                            [ ${ref} -lt 0 ] && ref=0                 
							uci set l2tp-client.$inface.t_reference=$ref
							config=l2tp-client
						else
							ref=`uci get pptp-client.$inface.t_reference 2>/dev/null`
							if [ -n "$ref" ]; then                                                                      
								ref=$((ref-1))                                                 
                                [ ${ref} -lt 0 ] && ref=0                   
								uci set pptp-client.$inface.t_reference=$ref
								config=pptp-client
							else
								config=
							fi
						fi
                fi
        done
		uci commit network    
		uci commit l2tp-client  
		uci commit pptp-client  
}    

iface_ref_add()                                                                                             
{                                                                                                           
        [ -n "$1" ] || return 1                                                                               

		local config=network 
		
        for inface in $1; do                                                                                 
                ref=`uci get network.$inface.t_reference 2>/dev/null`                                       
                if [ -n "$ref" ]; then                                                                      
                        ref=$((ref+1))                                                                     
                        uci set network.$inface.t_reference=$ref                                            
                else                                                                                        
                        ref=`uci get l2tp-client.$inface.t_reference 2>/dev/null`
						if [ -n "$ref" ]; then                                                                      
							ref=$((ref+1))                                                                     
							uci set l2tp-client.$inface.t_reference=$ref
							config=l2tp-client
						else
							ref=`uci get pptp-client.$inface.t_reference 2>/dev/null`
							if [ -n "$ref" ]; then                                                                      
								ref=$((ref+1))                                                                     
								uci set pptp-client.$inface.t_reference=$ref
								config=pptp-client
							else
								config=
							fi
						fi
                fi
        done
		uci commit network    
		uci commit l2tp-client  
		uci commit pptp-client  
} 

iface_ref_update()
{
	local minus_interface=$1
	local plus_interface=$2
	[ x"$minus_interface" = "x" -o  x"$plus_interface" = "x" ] && return 1
	iface_ref_del $minus_interface
	iface_ref_add $plus_interface
}

iface_qos_del()
{
	[ -n "$1" ] || return 1  
	local config=qos
	local section=setting
	local option=interface
	
	for inface in $1; do                                                                                 
        uci delete ${config}.${inface}
		uci del_list ${config}.${section}.${option}=${inface}
    done
	uci commit ${qos}
}

deal_with_qos_ref()
{
	iface_ref_del "$1"
	iface_qos_del "$2"
}   

