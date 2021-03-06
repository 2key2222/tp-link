#
#
# Copyright (c) 2014, The Linux Foundation. All rights reserved.
#
#  Permission to use, copy, modify, and/or distribute this software for any
#  purpose with or without fee is hereby granted, provided that the above
#  copyright notice and this permission notice appear in all copies.
#
#  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#


if [ "$ACTION" = "released" -a "$BUTTON" = "wps" -a $SEEN -lt 2 ]; then
	echo "" > /dev/console
	echo "WPS PUSH BUTTON EVENT DETECTED" > /dev/console
	for dir in /var/run/hostapd-*; do
		[ -d "$dir" ] || continue
		for vap_dir in $dir/ath*; do
		[ -r "$vap_dir" ] || continue
		config_load wireless
		config_get_bool vap_disabled ${vap_dir#"$dir/"} disabled 0
		config_get_bool wifi_disabled ${dir#"/var/run/hostapd-"} disabled 0
		config_get_bool disabled_all ${dir#"/var/run/hostapd-"} disabled_all 0
		config_get_bool wps_enabled ${vap_dir#"$dir/"} wps 0
		if [ "$vap_disabled" = "1" ] || [ "$wifi_disabled" = "1" ] || [ "$disabled_all" = "1" ] || [ "$wps_enabled" = "0" ]; then
			continue
		fi
		hostapd_cli -i "${vap_dir#"$dir/"}" -p "$dir" wps_pbc
		done
	done

	status=`wifi wps ath0 status` 
	echo "$status" | grep -q 'Overlap' && ledcli WPS_OVERLAP_TP
fi
