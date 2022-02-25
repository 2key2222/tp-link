#!/bin/sh

. /lib/functions.sh

num2ip()
{
    num=$1
    a=$((num>>24&0xff))
    b=$((num>>16&0xff))
    c=$((num>>8&0xff))
    d=$((num&0xff))
 
    echo "$a.$b.$c.$d"
}

ip2num()
{
    ip=$1
    a=`echo $ip | awk -F'.' '{print $1}'`
    b=`echo $ip | awk -F'.' '{print $2}'`
    c=`echo $ip | awk -F'.' '{print $3}'`
    d=`echo $ip | awk -F'.' '{print $4}'`
 
    echo "$(((a<<24)+(b<<16)+(c<<8)+d))"
}

do_remote_management()
{
    oper="$1"
    pname="$2"
    _add_remote_management()
    {
        config_get name $1 name ""
        [ "$2" != "$name" ] && return
        config_get start $1 start_ip
        config_get end $1 end_ip

        s=$(ip2num "$start")
        e=$(ip2num "$end")
        m=0xFFFFFFFF

        while [ $((${s} & ${m})) -ne $((${e} & ${m})) ];
        do
            m=$((${m}<<1))
        done

        ip=$(num2ip $((${s} & ${m})))
        mask=0
        while [ $((${m} & 0xFFFFFFFF)) -ne 0 ];
        do
            mask=$((${mask}+1))
            m=$((${m}<<1))
        done

        eval "$oper \"\$2\" \"\$ip\" \"\$mask\"" 
    }
    config_load ippool
    config_foreach _add_remote_management ippool "$pname"
}

add_rule()
{
    uci_add remote_mngt rsa_rule "$1"
    uci_set remote_mngt "$1" ipaddr "$2/$3"
    uci_set remote_mngt "$1" enabled "on"
    uci_set remote_mngt "$1" edit "off"
    uci_commit remote_mngt
}

del_rule()
{
    uci_remove remote_mngt "$1"
    uci_commit remote_mngt
}

enable_remote_management()
{
    proto="$1"

    _enable_ippool()
    {
        config_get type "$1" type
        config_get ippool "$1" ippool
        [ "$type" != "$proto" ] && return
        do_remote_management add_rule "$ippool"
    }
    config_load user-secrets
    config_foreach _enable_ippool user
}


disable_remote_management()
{
    proto="$1"

    _disable_ippool()
    {
        config_get type "$1" type
        config_get ippool "$1" ippool
        [ "$type" != "$proto" ] && return
        do_remote_management del_rule "$ippool"
    }
    config_load user-secrets
    config_foreach _disable_ippool user
}

refresh_vpn_remote_management()
{
    _server_on()
    {
        config_get enable "$1" enable "off"
        [ "$enable" == "on" -o "$enable" == "yes" ] && export $2="on"
    }

    disable_remote_management l2tp
    disable_remote_management pptp

    export l2tp="off"
    config_load l2tp-server
    config_foreach _server_on lns l2tp
    [ "$l2tp" == "on" ] && enable_remote_management l2tp

    export pptp="off"
    config_load pptp-server
    config_foreach _server_on pns pptp
    [ "$pptp" == "on" ] && enable_remote_management pptp

    /etc/init.d/remote_mngt reload 2>&1 | tee /tmp/test.log
}
