#!/bin/sh

add_cron_task()
{
	[ "$#" -eq 0 ] && return
	
	[ ! -f /etc/crontabs/root ] && touch /etc/crontabs/root
	echo "$@" > /tmp/.cron_task_save
	crontab -l | cat - /tmp/.cron_task_save | crontab -
	/etc/init.d/cron start
	rm -f /tmp/.cron_task_save
}

del_cron_task()
{
	[ "$#" -eq 0 ] && return

	[ ! -f /etc/crontabs/root ] && return

	crontab -l | sed "/$1/d" | crontab -
}
