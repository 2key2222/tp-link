#
# Makefile for the Atheros AR71xx built-in ethernet macs
#

ag71xx-y	+= ag71xx_main.o
ag71xx-y	+= ag71xx_ethtool.o
ag71xx-y	+= ag71xx_phy.o
ag71xx-y	+= ag71xx_mdio.o
ag71xx-y	+= ag71xx_ar7240.o
ag71xx-y	+= ag71xx_gmac_ctrl.o
ag71xx-y	+= ag71xx_phy_ctrl.o
ag71xx-y	+= ag71xx_mii_ctrl.o

# make eth platform device file into driver
ag71xx-y	+= dev-eth.o

# make phy driver built into ethernet driver
ag71xx-$(CONFIG_ATH79_SOC_QCA9558)	+= phys/ar8216.o
ag71xx-$(CONFIG_ATH79_SOC_QCA9563)	+= phys/ar8216.o

ag71xx-$(CONFIG_AG71XX_DEBUG_FS)	+= ag71xx_debugfs.o
ag71xx-$(CONFIG_AG71XX_AR8216_SUPPORT)	+= ag71xx_ar8216.o

obj-$(CONFIG_AG71XX)	+= ag71xx.o

