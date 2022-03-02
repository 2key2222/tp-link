#
# Makefile for the DSPHAL driver
#

obj-$(CONFIG_BCM_DSPHAL) += dsphal.o
dsphal-objs := dsphal_core.o dsphal_helpers.o dsphal_ioctl.o dsphal_debug.o
dsphal-objs += dma/iudma.o
dsphal-objs += g711/g711.o

# Per-chip files
include $(src)/chip.mk

subdir-ccflags-y += -I$(src)/dma -I$(src)/pcm -I$(src)/apm -I$(src)/dect -I$(src)/chip -I$(src)/alsa -I$(src)/g711 -I$(src)
subdir-ccflags-y += -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PUB_PATH)
subdir-ccflags-y += -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PRIV_PATH)/$(BRCM_BOARD)

# Voice defs
ifneq ($(strip $(BCM_VOICE_SUPPORT)),)
include $(BUILD_DIR)/make.voice
endif
subdir-ccflags-y += $(VOICE_CFLAGS)

ifneq ($(strip $(CONFIG_BCM_VOICE_DPLL_LOCK_WAIT)),)
	subdir-ccflags-y += -DBRCM_VOICE_DPLL_LOCK_WAIT
endif

ifneq ($(strip $(CONFIG_BCM_VOICE_DSPHAL_EGRESS_1KHZ_TONE)),)
	subdir-ccflags-y += -DBRCM_VOICE_DSPHAL_EGRESS_1KHZ_TONE
endif

ifneq ($(strip $(CONFIG_BCM_VOICE_DSPHAL_INGRESS_1KHZ_TONE)),)
	subdir-ccflags-y += -DBRCM_VOICE_DSPHAL_INGRESS_1KHZ_TONE
endif

ifneq ($(strip $(CONFIG_BCM_VOICE_DSPHAL_CAPTURE)),)
	subdir-ccflags-y += -DBRCM_VOICE_DSPHAL_CAPTURE
endif

-include $(TOPDIR)/Rules.make

clean:
	rm -f core *.o *.a *.s
