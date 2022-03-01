CC      ?= gcc
CFLAGS  ?= 
LDFLAGS ?= 
LIBS	+= -shared -fpic
SOURCE  := $(wildcard *.c)
TARGET_LIB := libcBase64.so

all:
	$(CC) $(LDFLAGS) $(CFLAGS) $(LIBS) -o $(TARGET_LIB) $(SOURCE)

.PHONY: clean
clean:
	rm *.so *.o *~ -rf
