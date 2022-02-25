client_options="#debug\n#logfile /tmp/pptp-client.log\n\
noipdefault\n\
noauth\n\
lcp-echo-failure 3\n\
lcp-echo-interval 60\n\
nobsdcomp\n\
nodeflate\n\
refuse-eap\n\
idle 0\n\
noccp\n\
novj\n\
mppe required,stateless\n\
plugin ppp4tplink.so\n\
maxfail 0"

options="#debug\n#logfile /tmp/pptp-server.log\n\
auth\nlcp-echo-failure 3\n\
lcp-echo-interval 60\ndefault-asyncmap\nmtu 1420\n\
mru 1420\nnobsdcomp\nnodeflate\n\
proxyarp\n\
noccp\n\
novj\n\
mppe required,stateless\n\
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

. /lib/zone/zone_api.sh

# $1 username; $2 password ; $3 pns ;$4 outif
client_start_pppd(){
	local username=$1
	local password=$2
	local pns=$3
	local outif=$4
	local client_path=$5
	local iface=$(zone_get_iface_bydev $outif)
	local zonex=$(zone_get_zone_byif $iface)

    /usr/sbin/pppd nodetach \
	+ipv6 \
	nodefaultroute \
	usepeerdns \
	persist \
	maxfail 0 \
	user $username password $password \
	ip-up-script /lib/netifd/ppp-up \
	ipv6-up-script /lib/netifd/ppp-up \
	ip-down-script /lib/netifd/ppp-down \
	ipv6-down-script /lib/netifd/ppp-down \
	plugin pptp.so \
	pptp_server $pns \
	file ${client_path}/options.pptp \
	zonex $zonex \
	tunnel-proto pptp \
	outif $outif &
}
