#
# Makefile for the misc_led driver
#

obj-$(CONFIG_MISC_BUTTON_AW9136)	+= aw9136.o

EXTRA_CFLAGS += -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD)  -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD)

clean:
	rm -f core *.ko *.o *.a *.s
