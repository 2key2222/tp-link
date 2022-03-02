#
# Makefile for Shortcut FE.
#

obj-m += shortcut-fe.o

ifdef SFE_SUPPORT_IPV6
obj-m += shortcut-fe-ipv6.o
endif

obj-m += shortcut-fe-cm.o

shortcut-fe-objs := \
	sfe_ipv4.o

ifeq ($(findstring DSFE_PPP_HEADER, $(EXTRA_CFLAGS)), DSFE_PPP_HEADER)
shortcut-fe-objs += sfe_ppp.o
endif

ifdef SFE_SUPPORT_IPV6
shortcut-fe-ipv6-objs := \
	sfe_ipv6.o
endif

ifdef SFE_SUPPORT_IPV6
ccflags-y += -DIFNAME_6TO4=\"6to4-wanv6\"
endif

shortcut-fe-cm-objs := \
	sfe_cm.o

