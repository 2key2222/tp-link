#!/bin/bash

find $1/rootfs.ncust* -exec bash -c 'mv $0 ${0/rootfs.ncust/custfs.ubi}' {} \;

