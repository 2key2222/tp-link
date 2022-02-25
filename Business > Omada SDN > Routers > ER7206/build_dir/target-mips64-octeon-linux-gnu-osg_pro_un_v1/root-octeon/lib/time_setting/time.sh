#!/bin/sh

set_timezone(){
   sed -i "/\sTZ/d" /etc/profile
   echo "export TZ=$1" >> /etc/profile
}

get_time(){
	timezone="`cat /etc/profile |grep "\<export TZ\>" |cut -d '=' -f 2`"
	export TZ=${timezone}
	local now="`date +%A%t%H:%M:%S%t%m/%d/%Y`"
	echo $now
}

get_timezone(){
	timezone="`cat /etc/profile |grep "\<export TZ\>" |cut -d '=' -f 2`"
}