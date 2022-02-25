#!/bin/sh /etc/rc.common

enable_all_phy(){
        oct-linux-mdio 1 0x8 0 0x1040 #GE1
        oct-linux-mdio 1 0x9 0 0x1040 #GE2
        oct-linux-mdio 1 0xa 0 0x1040 #GE3
        oct-linux-mdio 1 0xb 0 0x1040 #GE4
        oct-linux-mdio 0 0x5 0 0x1040 #GE5
}

disable_all_phy(){
    oct-linux-mdio 1 0x8 0 0x1840 #GE1
        oct-linux-mdio 1 0x9 0 0x1840 #GE2
        oct-linux-mdio 1 0xa 0 0x1840 #GE3
        oct-linux-mdio 1 0xb 0 0x1840 #GE4
        oct-linux-mdio 0 0x5 0 0x1840 #GE5
}

enable_phy_GE5(){
        oct-linux-mdio 1 0x8 0 0x1840 #GE1
        oct-linux-mdio 1 0x9 0 0x1840 #GE2
        oct-linux-mdio 1 0xa 0 0x1840 #GE3
        oct-linux-mdio 1 0xb 0 0x1840 #GE4
        oct-linux-mdio 0 0x5 0 0x1040 #GE5
}