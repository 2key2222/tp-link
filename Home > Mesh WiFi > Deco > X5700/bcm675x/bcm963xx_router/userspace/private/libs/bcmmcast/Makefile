LIB = libbcmmcast.so
default: dynamic


libbcmmcast.so:
	cp libbcmmcast.so_$(PROFILE).save libbcmmcast.so

dynamic: generic_private_lib_install

clean:
	rm -f libbcmmcast.so

CURR_DIR := $(shell pwd)
BUILD_DIR := $(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR := $(word 1, $(BUILD_DIR))
include $(BUILD_DIR)/make.common
