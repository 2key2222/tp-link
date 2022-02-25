#
# Copyright (c) 2014 Shenzhen TP-LINK Technologies Co.Ltd.
#

BUILD_DIR:=.
SDK_DIR:=../openwrt
SUBMAKE:=$(MAKE) $(FLAGS)

all: bootstrap build

config:
	cp ipf.config $(SDK_DIR)/.config;
	cp linux-3.3.config $(SDK_DIR)/target/linux/ar71xx/config-3.3;
	cp feeds.conf $(SDK_DIR)/feeds.conf;

bootstrap: config
	$(SUBMAKE) -C $(SDK_DIR) bootstrap

build:
	$(SUBMAKE) -C $(SDK_DIR)
