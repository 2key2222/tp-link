#
# Makefile for the Atheros AR71xx built-in ethernet macs
#

ag71xx-y	+= ag71xx_main.o
ag71xx-y	+= ag71xx_ethtool.o
ag71xx-y	+= ag71xx_phy.o
ag71xx-y	+= ag71xx_mdio.o
ag71xx-y	+= ag71xx_ar7240.o
ag71xx-y	+= ag71xx_gmac_ctrl.o
ag71xx-y	+= ag71xx_phy_ctrl.o
ag71xx-y	+= ag71xx_mii_ctrl.o

# make eth platform device file into driver
ag71xx-y	+= dev-eth.o

# make phy driver built into ethernet driver
ag71xx-$(CONFIG_RTL8367S)	+= phys/rtl8367s.o

#APIs  todo: remove, use sdk
ifeq ($(CONFIG_RTL8367S), y)
ag71xx-$(CONFIG_ATH79_SOC_QCA9563)	+= phys/rtl8367s_api.o
endif

ag71xx-$(CONFIG_AG71XX_DEBUG_FS)	+= ag71xx_debugfs.o
ag71xx-$(CONFIG_AG71XX_AR8216_SUPPORT)	+= ag71xx_ar8216.o

obj-$(CONFIG_AG71XX)	+= ag71xx.o

#sdk APIs
ifeq ($(CONFIG_RTL8370MB), y)
# low level api
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_acl.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_cputag.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_dot1x.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_eav.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_eee.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_fc.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_green.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_hsb.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_igmp.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_inbwctrl.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_interrupt.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_led.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_lut.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_meter.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_mib.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_mirror.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_misc.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_oam.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_phy.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_port.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_portIsolation.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_qos.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_rldp.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_rma.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_scheduling.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_storm.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_svlan.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_trunking.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_unknownMulticast.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_vlan.o
ag71xx-y	+= ./rtk_ssdk/rtl8367c_asicdrv_gpio.o

# high level api
ag71xx-y	+= ./rtk_ssdk/acl.o
ag71xx-y	+= ./rtk_ssdk/cpu.o
ag71xx-y	+= ./rtk_ssdk/dot1x.o
ag71xx-y	+= ./rtk_ssdk/eee.o
ag71xx-y	+= ./rtk_ssdk/igmp.o
ag71xx-y	+= ./rtk_ssdk/interrupt.o
ag71xx-y	+= ./rtk_ssdk/l2.o
ag71xx-y	+= ./rtk_ssdk/leaky.o
ag71xx-y	+= ./rtk_ssdk/led.o
ag71xx-y	+= ./rtk_ssdk/mirror.o
ag71xx-y	+= ./rtk_ssdk/oam.o
ag71xx-y	+= ./rtk_ssdk/port.o
ag71xx-y	+= ./rtk_ssdk/ptp.o
ag71xx-y	+= ./rtk_ssdk/qos.o
ag71xx-y	+= ./rtk_ssdk/rate.o
ag71xx-y	+= ./rtk_ssdk/rldp.o
ag71xx-y	+= ./rtk_ssdk/smi.o
ag71xx-y	+= ./rtk_ssdk/stat.o
ag71xx-y	+= ./rtk_ssdk/storm.o
ag71xx-y	+= ./rtk_ssdk/svlan.o
ag71xx-y	+= ./rtk_ssdk/trap.o
ag71xx-y	+= ./rtk_ssdk/trunk.o
ag71xx-y	+= ./rtk_ssdk/vlan.o


# init api
ag71xx-y	+= ./rtk_ssdk/rtk_switch.o
ag71xx-y	+= ./rtk_ssdk/init/rtl8370mb.o

# cmd api

endif
