# Copyight(c) 2008-2015 Shenzhen TP-LINK Technologies Co.Ltd.
# file     zone_init.sh
# bief     Config the zone info
# author   Yuan Fengjia
# vesion   1.0.0
# history  1.0.0, 13May15, Yuanfengjia, Ceate the file

. /lib/zone/zone_init_all.sh

zone_conf_build_wan()
{
	zone_conf_build
}

zone_conf_build_lan()
{
	zone_conf_build
}

[ -e /lib/vnet/vnet_zone_init.sh ] && {
	. /lib/vnet/vnet_zone_init.sh

	zone_conf_build()
	{
		$(. /lib/zone/zone_init_all.sh; zone_conf_build)
		vnet_rebuild_zones
	}

	zone_conf_build_wan()
	{
		$(. /lib/zone/zone_init_all.sh; zone_conf_build)
	}

	zone_conf_build_lan()
	{
		vnet_rebuild_zones
	}
}

