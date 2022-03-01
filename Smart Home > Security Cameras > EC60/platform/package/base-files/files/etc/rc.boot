#!/bin/sh
# Copyright (C) 2006-2012 OpenWrt.org

. $IPKG_INSTROOT/lib/functions.sh
. $IPKG_INSTROOT/lib/functions/service.sh
. $IPKG_INSTROOT/lib/functions/procd.sh

USE_PROCD=0

rc_procd() {
	[ -n "$USE_PROCD" ] && {
		procd_open_service "$(basename ${basescript:-$initscript})" "$initscript"
		"$@"
		procd_close_service
	}
}

start() {
	[ -n "$USE_PROCD" ] && {
		rc_procd start_service "$@"
		if eval "type service_started" 2>/dev/null >/dev/null; then
			service_started
		fi
	}
}

stop() {
	[ -n "$USE_PROCD" ] && {
		stop_service "$@"
		procd_kill "$(basename ${basescript:-$initscript})" "$1"
	}
}

reload() {
	[ -n "$USE_PROCD" ] && {
		if eval "type reload_service" 2>/dev/null >/dev/null; then
			reload_service "$@"
		else
			start
		fi
	}
}

restart() {
	trap '' TERM
	stop "$@"
	start "$@"
}

boot() {
	start "$@"
}

depends() {
	return 0
}

start_service() {
	return 0
}

stop_service() {
	return 0
}

service_triggers() {
	return 0
}

service_running() {
	return 0
}

${INIT_TRACE:+set -x}

for initscript in /etc/rc.d/S*; do 
	basescript=$(readlink "$initscript")
	(. "$initscript" && "$1")&
	wait
done
