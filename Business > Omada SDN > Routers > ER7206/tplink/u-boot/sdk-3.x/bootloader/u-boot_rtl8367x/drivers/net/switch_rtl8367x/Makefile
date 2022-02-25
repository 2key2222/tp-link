#
# (C) Copyright 2008
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

include $(TOPDIR)/config.mk

LIB	:= $(obj)libswitch_rtl8367x.o

# low level api
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_acl.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_cputag.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_dot1x.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_eav.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_eee.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_fc.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_green.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_hsb.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_igmp.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_inbwctrl.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_interrupt.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_led.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_lut.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_meter.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_mib.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_mirror.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_misc.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_oam.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_phy.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_port.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_portIsolation.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_qos.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_rldp.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_rma.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_scheduling.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_storm.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_svlan.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_trunking.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_unknownMulticast.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtl8367c_asicdrv_vlan.o

# high level api
COBJS-$(CONFIG_SWITCH_RTL8367X) += acl.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += cpu.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += dot1x.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += eee.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += igmp.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += interrupt.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += l2.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += leaky.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += led.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += mirror.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += oam.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += port.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += ptp.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += qos.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rate.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += rldp.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += smi.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += stat.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += storm.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += svlan.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += trap.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += trunk.o
COBJS-$(CONFIG_SWITCH_RTL8367X) += vlan.o


# init api
COBJS-$(CONFIG_SWITCH_RTL8367X) += rtk_switch.o

# cmd api
COBJS-$(CONFIG_SWITCH_RTL8367X) += cmd_rtk.o


COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))


CFLAGS += -I./

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
