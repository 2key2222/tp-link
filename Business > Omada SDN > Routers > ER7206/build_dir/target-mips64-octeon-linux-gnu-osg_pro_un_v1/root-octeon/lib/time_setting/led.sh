#!/bin/sh

config="system"

# section name
# led on/off
set_led_default() {
	local section="$1"
	local ledval="$2"

	local ledon="$(uci get ${config}.${section}.ledon)"
	local ledoff="$(uci get ${config}.${section}.ledoff)"

	case "${ledval}" in
	"on")
		uci set ${config}.${section}.default="${ledon}"
		;;
	*)
		uci set ${config}.${section}.default="${ledoff}"
		;;
	esac
}

local single=$(uci get network.global.singlewan)
local wanmod=$(uci get network.global.wanmode)

[ "${single}" != "0" ] && wanmod="1"

set_led_default switch_led_1 "off"
set_led_default switch_led_2 "off"
set_led_default switch_led_3 "off"
set_led_default switch_led_4 "off"
set_led_default switch_led_5 "off"

case "$wanmod" in
	"1")
		set_led_default switch_led_1 "on"
		;;
	"2")
		set_led_default switch_led_1 "on"
		set_led_default switch_led_2 "on"
		;;
	"3")
		set_led_default switch_led_1 "on"
		set_led_default switch_led_2 "on"
		set_led_default switch_led_3 "on"
		;;
	"4")
		set_led_default switch_led_1 "on"
		set_led_default switch_led_2 "on"
		set_led_default switch_led_3 "on"
		set_led_default switch_led_4 "on"
		;;
	*)
		;;
esac

uci commit ${config}