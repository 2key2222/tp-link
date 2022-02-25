# Copyright(c) 2011-2013 Shenzhen TP-LINK Technologies Co.Ltd.
#
# /usr/lib/dynamic_dns/dynamic_dns_noip.sh
# Written by Guo Dongxian<guodongxian@tp-link.com.cn>, April 2014
#
# This script is used to parse no-ip server return code and convert
# to TP New UI status code

. /lib/zone/zone_api.sh
. /usr/lib/ddns/dynamic_dns_log.sh

NOIP_RETCODE_GOOD=8001
NOIP_RETCODE_ERR=8002
NOIP_RETCODE_UNKNOWN=8003

NOIP_RETCODE_NOCHG=9000

NOIP_RETCODE_NOHOST=9001
NOIP_RETCODE_NOT_DONATOR=9002

NOIP_RETCODE_BADAUTH=9101
NOIP_RETCODE_BADAGENT=9102

NOIP_RETCODE_ABUSE=9201
NOIP_RETCODE_911=9202

# no-ip state
NOIP_STATE_RUN_OK=0     # ok
NOIP_STATE_STOP=1       # stop
NOIP_STATE_CONNECTING=2 # connecting
NOIP_STATE_BADAUTH=3    # badauth
NOIP_STATE_BADHOST=4    # badhost     

NOIP_HTTP_ERR_PATH=/tmp/noip.error
NOIP_NSLOOKUP_TMO=10

noip_retrieve_prog()
{
    # Linux-DUC/2.1.3?
    local user_agent=
    
    if [ -z "$user_agent" ]; then
        noip_prog="/usr/bin/curl"
    else
        noip_prog="/usr/bin/curl -U ${user_agent}"
    fi
    
    echo "$noip_prog"
}

noip_state_init()
{
    uci_set_state ddns "noip_${1}" "" ddns_state
    uci_set_state ddns "noip_${1}" state $NOIP_STATE_CONNECTING
}

noip_update()
{
    local prog="$1"
    local url="$2"
    local iface="$3"
    local devname=$(echo $iface | awk '{print toupper($0)}')
    local ifname=$(zone_get_effect_main_wan_devices $devname)
    #echo if_name=$ifname > /dev/console
    noip_result=1
    
    if [ -n "$prog" -a -n "$url" ]
    then
        request=$( ${prog} --interface ${ifname} "${url}" 2>"/tmp/${iface}_noip.error" )
        if [ $? -gt 0 ]; then
            noip_result=1
        else
            noip_result=0        
        fi
    fi
    
    echo "$noip_result"
}

noip_parse_retcode()
{
    local service_id="$1"
    local iface_name="$2"
    local http_res=$(cat "/tmp/${iface_name}_noip.error"|grep -o "curl")

    noip_code=''
    if [ -n "$http_res" -a "$http_res" == "curl" ]; then
        # Only check 4xx http error code
        local http_code=$(cat "/tmp/${iface_name}_noip.error"|grep -o "4[0-9][0-9]")
        case $http_code in
            401) noip_code=$NOIP_RETCODE_BADAUTH ;;
            404) 
                noip_code=$NOIP_RETCODE_ERR 
                ddns_syslog $DDNS_LOG_NTC_CONN_SVR_FAIL "noip" "$iface_name" "$3"
            ;;
            *) 
                noip_code=$NOIP_RETCODE_UNKNOWN
                #ddns_syslog $DDNS_LOG_WNG_SVR_RESET "noip" "$iface_name" "$3"
            ;;
        esac
    else
        local result=$(cat /var/run/dynamic_dns/${service_id}_${iface_name}.retcode|awk -F ' ' '{print $1}')
        case $result in
            good)       noip_code=$NOIP_RETCODE_GOOD ;;
            nochg)  
            local ip=$(cat /var/run/dynamic_dns/${service_id}_${iface_name}.retcode|awk -F ' ' '{print $2}')
            if [ -n "$ip" ]; then
                noip_code=$NOIP_RETCODE_GOOD
            else
                noip_code=$NOIP_RETCODE_NOCHG 
           fi  
           ;;
            nohost)     noip_code=$NOIP_RETCODE_NOHOST ;;
            abuse)      noip_code=$NOIP_RETCODE_ABUSE ;;
            badauth)    noip_code=$NOIP_RETCODE_BADAUTH ;;
            !donator)   noip_code=$NOIP_RETCODE_NOT_DONATOR ;;
            badagent)   noip_code=$NOIP_RETCODE_BADAGENT ;;
            911)        noip_code=$NOIP_RETCODE_911 ;;
            *)          noip_code=$NOIP_RETCODE_ERR ;;
        esac
        #ddns_syslog $DDNS_LOG_INF_RETCODE "noip" $result "$iface_name" "$3"
    fi
    
    # After parsing, then remove the temp http response code file
    rm -f "/tmp/${iface_name}_noip.error"

    echo "$noip_code"
}

noip_set_state()
{
    local code="$1"

    [ -z "$code" -o '' -eq "$code" ] && {
        uci_toggle_state ddns "noip_${2}" state $NOIP_STATE_STOP
        ddns_syslog $DDNS_LOG_NTC_LOGIN_FAIL "noip" "$2" "$3"
        return    
    }

    if [ $code -eq $NOIP_RETCODE_GOOD ]; then
        uci_toggle_state ddns "noip_${2}" state $NOIP_STATE_RUN_OK
        ddns_syslog $DDNS_LOG_NTC_LOGIN_SUCC "noip" "$2" "$3"
    elif [ $code -eq $NOIP_RETCODE_UNKNOWN ]; then
        uci_toggle_state ddns "noip_${2}" state $NOIP_STATE_CONNECTING
        #ddns_syslog $DDNS_LOG_INF_CONNING "noip" "$2" "$3"
    elif [ $code -eq $NOIP_RETCODE_BADAUTH ]; then
        uci_toggle_state ddns "noip_${2}" state $NOIP_STATE_BADAUTH
        ddns_syslog $DDNS_LOG_NTC_ACC_INCORRECT "noip" "$2" "$3"
    elif [ $code -eq $NOIP_RETCODE_NOHOST ]; then
        uci_toggle_state ddns "noip_${2}" state $NOIP_STATE_BADHOST
        ddns_syslog $DDNS_LOG_NTC_DOMAIN_FAIL "noip" "$2" "$3"
    else
        uci_toggle_state ddns "noip_${2}" state $NOIP_STATE_STOP 
        ddns_syslog $DDNS_LOG_NTC_LOGIN_FAIL "noip" "$2" "$3"
    fi
    
    return    
}

noip_check()
{
    local s=$(uci_get_state ddns "noip_${3}" state)
    
    config_get domain "noip_${3}" domain
    
    [ -n "$s" ] && {
        if [ $s -eq $NOIP_STATE_CONNECTING ]; then
            network_get_dnsserver dns "$1"
            for d in $dns; do
                [ -n "$d" ] && {
                    local ns=$(dnslookup -t $NOIP_NSLOOKUP_TMO $domain $d|head -n 1|grep -o "$ip_regex")
                    [ "$ns" == "$2" ] && {
                        # When finding server can update ip address, then changing state: connection->succeed 
                        uci_toggle_state ddns "noip_${3}" state $NOIP_STATE_RUN_OK  
                        ddns_syslog $DDNS_LOG_NTC_LOGIN_SUCC "noip" "$3" "$4"                
                        return 0
                    }           
                }
            done        
        fi
    }

    return 1
}

noip_retry_interval()
{
    noip_retry_int=
    local s=$(uci_get_state ddns "noip_${1}" state)

    local chk_int chk_unit chk_int_sec
    config_get chk_int "noip_${1}" check_interval
    config_get chk_unit "noip_${1}" check_unit

    [ "$chk_int" != "never" ] && {
        case "$check_unit" in
	        "days" )
		        chk_int_sec=$(($chk_int*60*60*24))
		    ;;
	        "hours" )
		        chk_int_sec=$(($chk_int*60*60))
		    ;;
	        "minutes" )
		        chk_int_sec=$(($chk_int*60))
		    ;;
	        "seconds" )
		        chk_int_sec=$chk_int
		    ;;
	        * )
		        #default is seconds
		        chk_int_sec=$chk_int
		    ;;
        esac
    }

    if [ "$s" -eq $NOIP_STATE_BADHOST ]; then
        noip_retry_int=${chk_int_sec:-"never"}
    elif [ "$s" -eq $NOIP_STATE_BADAUTH ]; then
        noip_retry_int=${chk_int_sec:-"never"}
    elif [ "$s" -eq $NOIP_STATE_STOP ]; then
        noip_retry_int=$((60*1)) # 5 minutes
    else
        noip_retry_int='' # Default, read it from config
    fi

    echo "$noip_retry_int"
}

