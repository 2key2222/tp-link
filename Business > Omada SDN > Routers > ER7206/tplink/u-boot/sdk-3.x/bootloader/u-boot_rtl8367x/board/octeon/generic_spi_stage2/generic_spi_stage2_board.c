/*
 * (C) Copyright 2004-2014 Cavium Inc. <support@cavium.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/mipsregs.h>
#include <asm/arch/octeon_boot.h>
#include <asm/arch/octeon_board_common.h>
#include <asm/arch/lib_octeon_shared.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-app-init.h>
#include <asm/arch/octeon-model.h>

DECLARE_GLOBAL_DATA_PTR;

static const uint8_t tuple_addresses[] = {
	OCTEON_EVB7000_BOARD_EEPROM_TWSI_ADDR,
	OCTEON_EVB7000_SFF_BOARD_EEPROM_TWSI_ADDR,
};

/**
 * Let user know that i am alive..
 */
void blink_sys_led(void)
{
    int i = 0;

    printf("Blink SYS LED.\n");

    /* enable All LEDs */
    gpio_direction_output(1, 0);

    for (i = 0; i < 30; i++) 
    {
        /* Sys LED on */
        gpio_direction_output(0, i%2);
        mdelay(100);
    }
    
    /* keep light on to ALL port blinking. */
    gpio_direction_output(0, 1);
    mdelay(2000);

    gpio_direction_output(0, 0);
    gpio_direction_output(1, 1);
}

/**
 * Perform early board initialization
 */
int early_board_init(void)
{
	const int cpu_ref = DEFAULT_CPU_REF_FREQUENCY_MHZ;
	int i;
	//gd->board_type = CVMX_BOARD_TYPE_EVB7000_SFF;
	#if 0
        {
		for (i = 0; i < ARRAY_SIZE(tuple_addresses); i++) {
			gd->arch.tlv_addr = tuple_addresses[i];
			octeon_board_get_descriptor(CVMX_BOARD_TYPE_GENERIC,
						    1, 0);
			if (gd->board_type != CVMX_BOARD_TYPE_GENERIC) {
				debug("%s: found TLV EEPROM at address 0x%x\n",
				      __func__, gd->arch.tlv_addr);
				break;
			}
		}
		if (i == ARRAY_SIZE(tuple_addresses)) {
			puts("ERROR: Board TLV descriptor not found!  Cannot continue!\n"
			     "Use the tlv_eeprom command to program the board type.\n");
			//return -1;
		}
	}
	#endif
	octeon_board_get_descriptor(CVMX_BOARD_TYPE_EVB7000_SFF,1,0);
	gd->arch.ddr_ref_hertz = 50000000;

	/* NOTE: this is early in the init process, so the serial port is not
	 * yet configured
	 */
	octeon_board_get_clock_info(DEFAULT_DDR3_CLOCK_FREQ_MHZ);

	printf("%s: Board type: %s\n", __func__,
	       cvmx_board_type_to_string(gd->board_type));

	/* Read CPU clock multiplier */
	gd->cpu_clk = octeon_get_cpu_multiplier() * cpu_ref * 1000000;

    //early_board_init_r();

#if 0
    blink_sys_led();
#endif

	return 0;
}

/**
 * Perform initialization late in the init process
 */
void late_board_init(void)
{
	char buf[256];
	char *board_name;
	board_name = getenv("boardname");
	if (board_name) {
		sprintf(buf, "u-boot-octeon_%s.bin", board_name);
		setenv("octeon_stage3_bootloader", buf);
		debug("Detected board type %s\n", board_name);
		sprintf(buf, "%s (SPI stage 2)", board_name);
		setenv("prompt", buf);
	}
}
