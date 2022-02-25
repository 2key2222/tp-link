/*
 * (C) Copyright 2013 Cavium, Inc. <support@cavium.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/mipsregs.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/octeon_board_common.h>
#include <asm/arch/octeon_fdt.h>
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/cvmx-helper-jtag.h>
#include <asm/gpio.h>
#include <asm/arch/cvmx-pcie.h>
#include <asm/arch/cvmx-qlm.h>
#include <i2c.h>
#include <asm/arch/cvmx-mdio.h>  //add by zhufeng
#include <asm/arch/cvmx-helper.h> 

#include <asm/arch/octeon_boot.h>
#include <asm/arch/octeon_board_common.h>
#include <asm/arch/octeon_fdt.h>
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/octeon_eth.h>

DECLARE_GLOBAL_DATA_PTR;


#define __D(code)  do{ \
                        printf(#code "\n"); \
                        code; \
                      }while(0)


void board_net_preinit(void)
{ 
    mdelay(120);
}



void board_net_postinit(void)
{

#if 0
    board_perform_led_test();
#endif

}
/**
 * Modify the device tree to remove all unused interface types.
 */
int board_fixup_fdt(void)
{
    const char *fdt_key;

    fdt_key = "0,sgmii";
    octeon_fdt_patch(working_fdt, fdt_key, NULL);
    #if 0
    if (gpio_get_value(3))
        fdt_key = "2,sata";
    else
        fdt_key = "2,pcie";
    octeon_fdt_patch(working_fdt, fdt_key, NULL);


    if (gpio_get_value(1) == 0)
        fdt_key = "0,qsgmii";
    else
        fdt_key = "0,xaui";

    octeon_fdt_patch(working_fdt, fdt_key, NULL);

    if (gpio_get_value(4) == 1) {
        puts("PCM mode detected, disabling MMC and USB power control\n");
        octeon_fdt_patch(working_fdt, "0,pcm", "cavium,pcm-trim");

    }
    #endif
    return 0;
}

int checkboard(void)
{
    int i,j,k;  //l;
    puts("DLM0:SGMII ports selected\n");
    i = octeon_configure_qlm(0,2500,CVMX_QLM_MODE_SGMII_DISABLED,0,0,1,0);

#if 0
    puts("DLM1:mini-PCIe 2X1 slots selected\n");
    j = octeon_configure_qlm(1,5000,CVMX_QLM_MODE_PCIE_2X1,1,1,1,0);
    
    puts("DLM2:SATA ports selected\n");
    k = octeon_configure_qlm(2,6000,CVMX_QLM_MODE_SATA_2X1,0,0,1,0);
#endif

#if 0
    int clk_to_use = 0; /* Clock used for DLM0 */

    if (gpio_get_value(2) == 0) {   /* DLM1_SEL */
        puts("SW4-2 on: mini-PCIe slots selected\n");
        octeon_configure_qlm(1, 5000, CVMX_QLM_MODE_PCIE_2X1, 1, 1, 0, 0);
    } else {
        if (gpio_get_value(3) == 1) {
            puts("SW4-2 off, SW4-3 off: PCIe 1x2 mode selected\n");
            octeon_configure_qlm(1, 5000, CVMX_QLM_MODE_PCIE_1X2,
                         1, 1, 0, 0);
        } else {
            int host_mode = cvmx_pcie_is_host_mode(0);
            printf("SW4-2 off, SW4-3 on: PCIe 1x4 %s mode selected\n",
                   host_mode ? "host" : "target");
            /* For PCIe target mode we need to use clock 1 for DLM0
             * since in this case clock 0 is coming from the PCIe
             * host.  Also, there's no need to configure the DLM
             * if we're in PCIe target (endpoint) mode.
             */
            if (host_mode)
                octeon_configure_qlm(1, 5000,
                             CVMX_QLM_MODE_PCIE,
                             1, 1, 0, 0);
            else
                clk_to_use = 1;

        }
    }

    if (gpio_get_value(1) == 0) {   /* DLM0_SEL */
        puts("SW4-1 on: QSGMII ports selected\n");
        debug("Configuring DLM0 for QSGMII/DISABLED\n");
        octeon_configure_qlm(0, 5000, CVMX_QLM_MODE_QSGMII_QSGMII,
                     0, 0, clk_to_use, 0);
        debug("Done.\n");
    } else {
        puts("SW4-1 off: RXAUI (10G) port selected\n");
        octeon_configure_qlm(0, 3125, CVMX_QLM_MODE_RXAUI,
                     0, 0, clk_to_use, 1);
    }


    if (gpio_get_value(3) != 0) {   /* DLM2_SEL */
        puts("SW4-3 off: SATA ports selected\n");
        octeon_configure_qlm(2, 3125, CVMX_QLM_MODE_SATA_2X1,
                     0, 0, 0, 0);
    }

    debug("Powering up Vitesse PHYs\n");
    gpio_direction_output(9, 0);    /* COMA mode */
    debug("Powering up USB ports\n");

#endif

    
    return 0;
}


/**
 * NOTE : *MUST* put it after board_mdio_init(); 
 * 
 * 
 */
int board_perform_led_test(void)
{
    printf("%s():%d ...\n", __FUNCTION__, __LINE__);

    /* disable All LEDs */
    __D( gpio_direction_output(1, 1); );

    /*  All LEDs turn GREEN */
    __D( cvmx_mdio_write(1,  8,  0x1d,   0x1b08); );
    __D( cvmx_mdio_write(1,  8,  0x1e,   0x00ff); );
    __D( cvmx_mdio_write(1,  8,  0x1d,   0x1b0c); );
    __D( cvmx_mdio_write(1,  8,  0x1e,   0x00ff); );
    __D( cvmx_mdio_write(0,  5,  0x1f,   0x0000); );
    __D( cvmx_mdio_write(0,  5,  0x00,   0x8000); );

    __D( mdelay(20); );

    __D( cvmx_mdio_write(0,  5,  0x00,   0x4000); );

    __D( mdelay(20); );

    __D( cvmx_mdio_write(0,  5,  0x1f,   0x0d04); );
    __D( cvmx_mdio_write(0,  5,  0x10,   0x0420); );

    /* Sys LED on */
    __D( gpio_direction_output(0, 1); );

    /* enable All LEDs */
    __D( gpio_direction_output(1, 0); );


    /* keep light on for # seconds. */
    __D( mdelay(1000); );

    /* P1-P5 LED(left) keep green, LED(right) turn yellow  */
    __D( cvmx_mdio_write(1,  8,  0x1d,   0x1b0c); );
    __D( cvmx_mdio_write(1,  8,  0x1e,   0x0000); );
    __D( cvmx_mdio_write(1,  8,  0x1d,   0x1b0a); );
    __D( cvmx_mdio_write(1,  8,  0x1e,   0x00ff); );
    __D( cvmx_mdio_write(0,  5,  0x10,   0x0021); );

    /* keep light on for # seconds. */
    __D( mdelay(1000); );


    /* disable All LEDs */
    __D( gpio_direction_output(1, 1); );

    __D( cvmx_mdio_write(1,  8,  0x1d,   0x1b08); );
    __D( cvmx_mdio_write(1,  8,  0x1e,   0x0000); );
    __D( cvmx_mdio_write(1,  8,  0x1d,   0x1b0a); );
    __D( cvmx_mdio_write(1,  8,  0x1e,   0x0000); );
    __D( cvmx_mdio_write(0,  5,  0x1f,   0x0000); );
    __D( cvmx_mdio_write(0,  5,  0x00,   0x1140); );

    printf("%s():%d ...\n", __FUNCTION__, __LINE__);

    return 0;
}

int board_perform_led_init(void)
{
    printf("%s():%d ...\n", __FUNCTION__, __LINE__);

    __D( cvmx_mdio_write(1,  8,  0x1d,   0x1b00); );
    __D( cvmx_mdio_write(1,  8,  0x1e,   0x0000); );


    __D( cvmx_mdio_write(1,  8,  0x1d,   0x1b03); );
    __D( cvmx_mdio_write(1,  8,  0x1e,   0x0342); );
    __D( cvmx_mdio_write(0,  5,  0x1f,   0x0d04); );
    __D( cvmx_mdio_write(0,  5,  0x10,   0x2362); );
    __D( cvmx_mdio_write(0,  5,  0x1f,   0x0000); );

    /* Sys LED off */
    __D( gpio_direction_output(0, 0); );

    /* enable All LEDs */
    __D( gpio_direction_output(1, 0); );

    printf("%s():%d ...\n", __FUNCTION__, __LINE__);

    return 0;
}



int early_board_init(void)
{
#if 0
    uint8_t val;

    /* Disable USB power */
    gpio_direction_output(18, 1);
    gpio_direction_output(19, 1);
    /* Enable COMA */
    gpio_direction_output(9, 1);
    gpio_direction_input(1);    /* DLM1_SEL */
    gpio_direction_input(2);    /* DLM2A_SEL */
    gpio_direction_input(3);    /* DLM2B_SEL */
    gpio_direction_input(4);    /* PCM select */

    gpio_direction_input(14);   /* SD/MMC Write Protect */
    gpio_direction_input(15);   /* SD/MMC Card Detect */
    mdelay(10);
#endif
    /* Populate global data from eeprom */
    octeon_board_get_clock_info(EVB7000_SFF_DEF_DRAM_FREQ);

    octeon_board_get_descriptor(CVMX_BOARD_TYPE_EVB7000_SFF, 1, 0);
#if 0
    /* Enable temperature and fan monitoring */
    i2c_set_bus_num(CONFIG_SYS_DTT_BUS_NUM);
    val = i2c_reg_read(CONFIG_SYS_I2C_DTT_ADDR, 0);
    /* Invert output, turn on tach, 2-wire analog and enable monitoring */
    val |= 0xd;
    i2c_reg_write(CONFIG_SYS_I2C_DTT_ADDR, 0, val);

    val = i2c_reg_read(CONFIG_SYS_I2C_DTT_ADDR, 1);
    /* Turn off tach 2 and remote 2 temperature sensor */
    val &= ~0x48;
    i2c_reg_write(CONFIG_SYS_I2C_DTT_ADDR, 1, val);
    /* Enable fan filtering for fan 1 */
    val = i2c_reg_read(CONFIG_SYS_I2C_DTT_ADDR, 0x23);
    val |= 1;
    i2c_reg_write(CONFIG_SYS_I2C_DTT_ADDR, 0x23, val);

    /* 800ms spin-up, 93.5KHz PWM, lowest speed 2647RPM */
    val = 0x3b;
    i2c_reg_write(CONFIG_SYS_I2C_DTT_ADDR, 0x20, val);

    val = 0x63; /* CPU fan enable temp 48C, range starts at 40C */
    i2c_reg_write(CONFIG_SYS_I2C_DTT_ADDR, 0x25, val);

    val = 0x52;
    /* PWM for fan 1 starts at 14%, 33% for fan 2 */
    i2c_reg_write(CONFIG_SYS_I2C_DTT_ADDR, 0x25, val);

#endif
    /* CN63XX has a fixed 50 MHz reference clock */
    gd->arch.ddr_ref_hertz = 50000000;

    octeon_board_get_mac_addr();

    printf("%s():%d ...\n", __FUNCTION__, __LINE__);

    return 0;
}

int disable_phy_eee(void)
{
    /**
     * RTL8211F EEE 
     * 
     */
    printf("Disable RTL8211F PHY's EEE feature.\n");
    __D(miiphy_write("mdio-octeon0", 5, 0x1f, 0x0000););
    __D(miiphy_write("mdio-octeon0", 5, 0x00, 0x8000););

    __D(mdelay(20););

    __D(miiphy_write("mdio-octeon0", 5, 0x1f, 0x0a4b););
    __D(miiphy_write("mdio-octeon0", 5, 0x11, 0x1110););
    __D(miiphy_write("mdio-octeon0", 5, 0x1f, 0x0000););
    __D(miiphy_write("mdio-octeon0", 5, 0x0d, 0x0007););
    __D(miiphy_write("mdio-octeon0", 5, 0x0e, 0x003c););
    __D(miiphy_write("mdio-octeon0", 5, 0x0d, 0x4007););
    __D(miiphy_write("mdio-octeon0", 5, 0x0e, 0x0000););

    /**
     * RTL8214C EEE 
     * 
     */
    printf("Disable RTL8214C PHY's EEE feature.\n");
    __D(miiphy_write("mdio-octeon1", 8, 0x1f, 0x0a5d););
    __D(miiphy_write("mdio-octeon1", 8, 0x1f, 0x0000););
}

#ifdef CONFIG_SWITCH_RTL8367X

/**
 * User-defined function called when the link state changes
 *
 * @param[in]	dev		Ethernet device
 * @param 	link_state	new link state
 *
 * NOTE: This is defined as a weak function so this overrides it.
 *
 * NOTE: This is required because the Qualcomm QCA8337 switch is totally broken
 * in how SGMII works.  Please do not use Qualcomm devices if they can be
 * avoided.  The QCA8334 will not work if autonegotiation is enabled on Octeon
 * when this device is initialized.  Autonegotiation on Octeon must be enabled
 * once the link comes up in order for traffic to flow, however.  This took a
 * significant amount of trial and error in order to make it work and is a
 * total hack since any sane device would just work.
 */
void board_net_set_link(struct eth_device *dev,
			cvmx_helper_link_info_t link_state)
{
	union cvmx_pcsx_mrx_control_reg control_reg;
	int index, interface;
	struct octeon_eth_info *oct_eth_info =
		(struct octeon_eth_info *)dev->priv;

	index = oct_eth_info->index;
	interface = oct_eth_info->interface;

	/* For some reason the QCA8337 switch requires that we start out with
	 * autonegotiation disabled.  When the link goes up we can enable
	 * autonegotiation.  When the link does down we need to power down
	 * PCS to reset it again.
	 */
	printf("%s(%s, link: %s)\n", __func__, dev->name,
	      link_state.s.link_up ? "up" : "down");
	control_reg.u64 = cvmx_read_csr(CVMX_PCSX_MRX_CONTROL_REG(index,
								  interface));
	printf("%s: PCS%d_MR%d_CONTROL_REG: before 0x%llx\n", __func__,
	      interface, index, control_reg.u64);
	control_reg.s.an_en = 0;	/* Turn autonegotiation off */
	control_reg.s.spdmsb = 1;	/* Set speed to 1Gbps */
	control_reg.s.spdlsb = 0;
	control_reg.s.dup = 1;		/* Set full duplex */
	control_reg.s.pwr_dn = 0;	/* Always Power on */

    printf("%s: PCS%d_MR%d_CONTROL_REG: after 0x%llx\n", __func__,
	      interface, index, control_reg.u64);

	cvmx_write_csr(CVMX_PCSX_MRX_CONTROL_REG(index, interface),
		       control_reg.u64);
	cvmx_read_csr(CVMX_PCSX_MRX_CONTROL_REG(index, interface));
	printf("%s: Done\n", __func__);
}

int late_board_init(void)
{

    printf("\r\n");
    printf("RTL8367S ###################################################\r\n");
    printf("RTL8367S ###################################################\r\n");
    printf("RTL8367S ###################################################\r\n");

    rtk_switch_init();

    printf("RTL8367S ###################################################\r\n");
    printf("RTL8367S ###################################################\r\n");
    printf("RTL8367S ###################################################\r\n");


    printf("\n Build %s %s \n", __DATE__, __TIME__);

    printf("\r\n");
}

#else
//add by zhufeng 
int late_board_init(void)
{
    int i,j,k,l;
    int date_1d[3] = {0x6602, 0x6601, 0x6600};
    int date_1e[8][3] =
        {
            {0x84D7, 0x0540, 0x00C0},
            {0xF994, 0x0541, 0x00C0},
            {0x29A1, 0x0542, 0x00C0},
            {0x3960, 0x0543, 0x00C0},
            {0x9728, 0x0544, 0x00C0},
            {0xF83F, 0x0545, 0x00C0},
            {0x9D85, 0x0423, 0x00C0},
            {0xD810, 0x0424, 0x00C0}
        };
    k = cvmx_mdio_write(0,5,0x1f,0xd04);
    l = cvmx_mdio_write(0,5,0x10,0x3012);
    cvmx_mdio_write(0,5,0x1f,0);
    //printf("1:k = %d,l = %d\n",k,l);

    //reset RTL8214C before write mii registers
    //cvmx_mdio_write(1,8,0,0x9140);
    cvmx_mdio_write(1,8,0x1d,0x1322);
    cvmx_mdio_write(1,8,0x1e,0x1);
    mdelay(200);
    //set RTL8214C registers to enable QSGMII interface and optimize the serdes parameter
    k = cvmx_mdio_write(1,8,0x1d,0x1d11);
    l = cvmx_mdio_write(1,8,0x1e,0x1506);
    //printf("2:k = %d,l = %d\n",k,l);

    for(i=0;i<8;i++)
    {
        for(j=0;j<3;j++)
        {
            k = cvmx_mdio_write(1,8,0x1d,date_1d[j]);
            //mdelay(100);
            l = cvmx_mdio_write(1,8,0x1e,date_1e[i][j]);
            //mdelay(100);
            //printf("3:k = %d,l = %d\n",k,l);
        }
    }

    cvmx_mdio_write(1,8,0x1d,0x1D11);
    cvmx_mdio_write(1,8,0x1e,0x1506);

    cvmx_mdio_write(1,8,0x1d,0x1D12);
    cvmx_mdio_write(1,8,0x1e,0x0800);



#if 0
    //set RTL8214C LED indication register
    cvmx_mdio_write(1,8,0x1d,0x1b00);
    cvmx_mdio_write(1,8,0x1e,0x14e0);
    cvmx_mdio_write(1,8,0x1d,0x1b03);
    cvmx_mdio_write(1,8,0x1e,0x690);

    //enable the led function   
    gpio_direction_output(1,0);
#endif

    board_perform_led_init();
    

    disable_phy_eee();

    printf("\r\n");
    printf("###################################################\r\n");
    printf("###################################################\r\n");
    printf("###################################################\r\n");
    printf("\r\n");
}
#endif
