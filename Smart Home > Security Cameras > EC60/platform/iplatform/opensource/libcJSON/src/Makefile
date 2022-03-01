CC      ?= gcc
CFLAGS  ?= 
LDFLAGS ?= 
LIBS	+= -shared -fpic
SOURCE  := $(wildcard *.c)
TARGET_LIB := libcJSON.so
all:
	$(CC) $(LDFLAGS) $(CFLAGS) $(LIBS) -o $(TARGET_LIB) $(SOURCE) -ldl
.PHONY: clean
clean:
	rm *.so *.o *~ -rf
