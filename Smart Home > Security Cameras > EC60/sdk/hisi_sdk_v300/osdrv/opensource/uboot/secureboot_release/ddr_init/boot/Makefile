CSRC  = $(wildcard *.c) 
SSRC  = $(wildcard *.S) 

CFLAGS += -nostdinc
SFLAGS += $(CFLAGS)

CSRC += $(SOC)/lowlevel_init_v300.c

#.SILENT:

default: 
	echo "  CC    $(CSRC)"
	echo "$(CC) $(CFLAGS) $(CSRC)"
	$(CC) $(CFLAGS) $(CSRC) -I ../drv
	echo "  CC    $(SSRC)"
	$(CC) $(SFLAGS) $(SSRC)

clean:
	rm *.o *.a -f
