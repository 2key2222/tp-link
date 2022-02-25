#!/bin/sh

NGINX_CONF="/etc/nginx/nginx.conf"
WIFIDOG_CONF="/etc/wifidog.conf"

modify_nginx_port()
{
	if [ ! -f $NGINX_CONF ]; then
		echo "file not exist" 
		exit
	fi

	sed -i "1,70s/listen       [0-9]\+;/listen       $1;/" $NGINX_CONF

	sed -i "s/HTTPPort [0-9]\+/HTTPPort $1/" $WIFIDOG_CONF
}

modify_nginx_port $1