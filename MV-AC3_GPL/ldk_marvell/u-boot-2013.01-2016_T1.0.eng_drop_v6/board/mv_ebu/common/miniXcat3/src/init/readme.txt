Mickey  22-DEC-2015

Adding support for PHY 1680:
Set the one of the below definitions:

/* Set only one of the PHY types used in this project (xCAT3-DB is using 1548) */
#define SUPPORT_PHY_1548 
#undef  SUPPORT_PHY_1680 

-------------------------------------------------------------
Mickey  04-NOV-2015

This is a preliminary drop of the mini_xcat3 package for U-Boot.
This package provide reference code to enable In-Band port #0 as the logical connection to the CPU egiga-1 MAC port.
                 
Package content:
1.   Main package directory Name - independent code package
board\mv_ebu\common\miniXcat3
2.   Makefile - Enabling the compilation of the package (Look for: MAKE_MINIXCAT3 = yes)
board\mv_ebu\common\Makefile
3.   Command line - Defining the U-Boot command line that running the related package.
common\cmd_test.c

General Guidelines and info:
1.   The code was developed and tested over Marvell XCAT3-DB only.
2.   It supports enabling In-Band port #0 only. Adding more ports to port #0 can be added by generating EEPROM sequence with CPSS appDemo and copy it to the related scripts.
3.   Connection to CPU - Direct SGMII connection between Interface #31 to CPU egiga-1 MAC 
4.   PVE configuration is used to forward traffic to/from In-band port-0 to Interface #31
5.   PHY initialization - This code package includes PHY 1548 initialization sequence 
   (That's the PHY assembled on XCAT3-DB). 
   In case another PHY initialization is required (e.g. 1680) - you may propagate the setting from CPSS code function name:  
6.   The code package includes also routines for RD/WR internal registers; please check the main function name: miniXcat3_main
7.   How to test:
   a.   Integrate the code to target U-Boot and build new U-Boot version
   b.   Program the new image to the SPI/NAND FLASH
   c.   Reset the board
   d.   Run the command: mini_xcat3 to initialize in-band port-0 
   e.   Connect Ethernet cable between port#0 to external Host computer 
   f.   Ping from the U-Boot command line to the external Host computer 
8.   The package is intended for FW upgrade only; once the upgrade process is finished - board reset is mandatory.  
   In case reset won't be issued - CPSS initialization might be failed. (CPSS assumes all Switch configuration is in Default mode)
9.   Functions that may cause the CPU to hang; serdesPowerDown, softReset - use U-Boot 'reset' command to perform system reset.


--------------------------------------------------------

Mickey  29-Oct-2015

Start integrating to U-Boot;
