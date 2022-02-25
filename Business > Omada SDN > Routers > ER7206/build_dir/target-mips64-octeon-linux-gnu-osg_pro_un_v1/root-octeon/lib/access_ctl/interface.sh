#!/bin/sh


{
	flock 8
	/etc/init.d/access_ctl restart
} 8<>/tmp/interface_lock