#!/bin/sh

NAME="policy_route"

#$1: rule_name
#$2: timeobj
add_timeobj()
{
	if [ -n "$1" ]; then
		. /lib/time_mngt/timeobj_api.sh

		timeobj_api_add $2 $NAME $1
		timeobj_api_commit $NAME
	fi
}

#$1: policy_rule
check_timeobj_dir()
{
	config_get timeobj $1 timeobj

	[ "$timeobj" == "$del_timeobj" ] && flag=1

}

#clean the policy route tmp file
#$1: timeobj
clean_balance_policy_route_tmp()
{
	local del_timeobj=$1 flag=0

	. /lib/functions.sh

	config_load $NAME

	config_foreach check_timeobj_dir policy_rule

	if [ $flag -eq 0 ]; then
		rm /tmp/policy_route/$del_timeobj -rf &> /dev/null
	fi
}

#$1: rules_name
#$2: timeobj_name
del_timeobj()
{
	[ -z "$1" -o -z "$2"] && return 1

	local rule_num=0 time_num=0

	. /lib/time_mngt/timeobj_api.sh

	rule_num=`echo "$1" |awk -F " " '{print NF-1}'`
	time_num=`echo "$2" |awk -F " " '{print NF-1}'`

	[ "$rule_num" -ne "$time_num" ] && return 1

	#one rule and timeobj
	if [ $rule_num -eq 0 ]; then

		timeobj_api_delete $2 $NAME $1
		timeobj_api_commit $NAME

		clean_balance_policy_route_tmp $2
	elif [ $rule_num -ge 1 ]; then	
		for i in `seq $(($rule_num+1))`;do
			rule=`echo "$1" | cut -d " " -f $i`
			timeobj=`echo "$2" | cut -d " " -f $i`

			timeobj_api_delete $timeobj $NAME $rule
			timeobj_api_commit $NAME

			clean_balance_policy_route_tmp $timeobj
		done
	fi
}

handle_timeobj()
{		
	config_get name $1 name
	config_get timeobj $1 timeobj
	
	if [ -n "$name" -a "$rule_name" == "$name" ]; then
		#check the directory		
		dir_time=/tmp/policy_route/$timeobj
		if [ ! -d "$dir_time$timeobj" ]; then
			mkdir -p $dir_time 
		fi
		
		#check the file of timeobj
		time_file=$dir_time"/state"
		if [ ! -f "$time_file" ]; then
			touch "$time_file" 
		fi	

		echo $enable >$time_file
	fi
}

#$1: rule_name
#$2: enable or not
policy_route_handle_timeobj()
{
	local rule_name=$1
	local enable=$2

	. /lib/functions.sh

	config_load $NAME

	config_foreach handle_timeobj policy_rule

	/etc/init.d/policy_route restart
}

#$1: old_rule_name
#$2: old_timeobj
#$3: new_rule_name
#$4: new_timeobj
update_timeobj()
{
	. /lib/time_mngt/timeobj_api.sh

	if [ "$2" != "Any" ] ; then
		timeobj_api_delete $2 $NAME $1
		timeobj_api_commit $NAME

		clean_balance_policy_route_tmp $2
	fi

	if [ "$4" != "Any" ]; then
		timeobj_api_add $4 $NAME $3
		timeobj_api_commit $NAME			
	fi
}



