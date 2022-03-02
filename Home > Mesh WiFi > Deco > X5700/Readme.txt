TPLINK GPL code for Deco X5700 1.0

Build Guide:

Step 1:
1. cd bcm675x/toolchain
2. tar -jxvf crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1.Rel1.10.tar.bz2

Step 2:
1. cd bcm675x/bcm963xx_router
2. make PROFILE=TP6755

Step 3:
1. cd iplatform
2. make

Notice:
1. When you are tring to build GPL code, the make program will automatic download
   some other source code packages that it needs from Internet, please make sure 
   your Linux PC have good Internet connection.

2. If you are of the opinion that TP-LINK should offer further source code subject
   to the GPL, please contact us under 'support@tp-link.com'.
