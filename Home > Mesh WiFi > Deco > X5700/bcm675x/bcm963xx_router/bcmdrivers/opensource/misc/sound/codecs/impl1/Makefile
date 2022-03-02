#
# Makefile for the bcm63xx codec driver
#

snd-soc-cs4345-objs := cs4345.o
snd-soc-es7210-objs := es7210.o
snd-soc-ad82584f-objs := ad82584f.o
snd-soc-pcm5100-objs := pcm5100.o
snd-soc-tlv320dac3203-objs := tlv320dac3203.o
snd-soc-tlv320adc3101-objs := tlv320adc3101.o
obj-$(CONFIG_SND_SOC_CS4345)	+= snd-soc-cs4345.o
obj-$(CONFIG_SND_SOC_ES7210)    += snd-soc-es7210.o
obj-$(CONFIG_SND_SOC_AD82584F)	+= snd-soc-ad82584f.o
obj-$(CONFIG_SND_SOC_PCM5100)	+= snd-soc-pcm5100.o
obj-$(CONFIG_SND_SOC_MAPLELEAF)	+= snd-soc-tlv320dac3203.o
obj-$(CONFIG_SND_SOC_MAPLELEAF)	+= snd-soc-tlv320adc3101.o

EXTRA_CFLAGS += -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMSHARED_PUB_PATH)/$(BRCM_BOARD)

clean:
	rm -f core *.ko *.o *.a *.s