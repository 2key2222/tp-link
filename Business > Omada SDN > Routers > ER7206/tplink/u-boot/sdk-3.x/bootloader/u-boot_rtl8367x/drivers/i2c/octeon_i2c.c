/***********************license start************************************
 * Copyright (c) 2004-2013 Cavium Inc. (support@cavium.com). All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *     * Neither the name of Cavium Inc. nor the names of
 *       its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
 * OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
 * PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET
 * POSSESSION OR CORRESPONDENCE TO DESCRIPTION.  THE ENTIRE RISK ARISING OUT
 * OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 *
 *
 * For any questions regarding licensing please contact
 * support@cavium.com
 *
 ***********************license end**************************************/

#include <common.h>
#include <linux/ctype.h>
#include <asm/arch/cvmx.h>
#include <asm/arch/cvmx-twsi.h>
#include <asm/arch/octeon_twsi.h>
#include <asm/arch/cvmx-core.h>
#include <asm/arch/octeon-model.h>
#include <watchdog.h>
#include <i2c.h>

#ifndef CONFIG_SYS_NUM_I2C_BUSES
# define CONFIG_SYS_NUM_I2C_BUSES	1
#endif

#ifndef CONFIG_SYS_MAX_I2C_BUS
# define CONFIG_SYS_MAX_I2C_BUS	0
#endif

#define OCTEON_I2C_TIMEOUT	50	/* 50ms */

/* Controller command and status bits */
#define TWSI_CTL_CE		0x80
#define TWSI_CTL_ENAB		0x40
#define TWSI_CTL_STA		0x20
#define TWSI_CTL_STP		0x10
#define TWSI_CTL_IFLG		0x08
#define TWSI_CTL_AAK		0x04

/* Some status values */
#define STAT_START		0x08
#define STAT_RSTART		0x10
#define STAT_TXADDR_ACK		0x18
#define STAT_TXDATA_ACK		0x28
#define STAT_RXADDR_ACK		0x40
#define STAT_RXADDR_NACK	0x48
#define STAT_RXDATA_ACK		0x50
#define STAT_IDLE		0xF8

DECLARE_GLOBAL_DATA_PTR;

/**
 * Sets the speed of the specified bus
 *
 * @param bus - bus number to set the speed of
 * @param speed - speed to set the bus to
 *
 * @return 0 on success, -1 on error.
 */
static uint octeon_i2c_set_bus_speed(struct i2c_adapter *adap,
				     unsigned int speed);

/**
 * Reads bytes from memory and copies to eeprom.
 * Only supports address size of 2 (16 bit internal address.)
 *
 * We can only write two bytes at a time to the eeprom, so in some cases
 * we need to to a read/modify/write.
 *
 * Note: can't do single byte write to last address in EEPROM
 *
 * @param adap   i2c adapter
 * @param chip   chip address
 * @param addr   internal address
 * @param alen   address length, must be 0, 1, or 2
 * @param buffer memory buffer pointer
 * @param len    number of bytes to write
 *
 * @return 0 on Success
 *         1 on Failure
 */
static int octeon_i2c_write(struct i2c_adapter *adap, uint8_t chip, uint addr,
			    int alen, uint8_t *buffer, int len);

/**
 * Holds the current bus speed.
 * NOTE: This can only be accessed if gd->flags & GD_FLG_RELOC is set!
 */

static uint32_t twsi_stop_delay[CONFIG_SYS_MAX_I2C_BUS + 1 ] = { 0, };

/* The following functions are used when the high-level I2C controller is
 * disabled.  The high-level controller is limited to no more than 8 bytes
 * for a read or write operation.  The low-level controller has no such
 * limitations but is more complex.
 */

/**
 * Write to the mio_twsx_sw_twsi register
 *
 * @param bus - TWSI bus number to write to
 * @param sw_twsi - register value to write.  Note that the v and r fields
 *                  are automatically set.
 */
static void octeon_i2c_write_sw(int bus, cvmx_mio_tws_sw_twsi_t sw_twsi)
{
	sw_twsi.s.v = 1;
	sw_twsi.s.r = 0;
	cvmx_write_csr(CVMX_MIO_TWSX_SW_TWSI(bus), sw_twsi.u64);
	do {
		sw_twsi.u64 = cvmx_read_csr(CVMX_MIO_TWSX_SW_TWSI(bus));
		WATCHDOG_RESET();
	} while (sw_twsi.s.v != 0);
}

/**
 * Read from the mio_twsx_sw_twsi register
 *
 * @param bus - bus number to read from
 * @param sw_twsi - used to specifyt the control register to read by the
 *                  op and eop_ia fields.
 *
 * @return mio_twsx_sw_twsi register value with the specified control register
 *                          in the d field.
 */
static cvmx_mio_tws_sw_twsi_t octeon_i2c_read_sw(int bus,
						 cvmx_mio_tws_sw_twsi_t sw_twsi)
{
	sw_twsi.s.v = 1;
	sw_twsi.s.r = 1;
	cvmx_write_csr(CVMX_MIO_TWSX_SW_TWSI(bus), sw_twsi.u64);
	do {
		sw_twsi.u64 = cvmx_read_csr(CVMX_MIO_TWSX_SW_TWSI(bus));
		WATCHDOG_RESET();
	} while (sw_twsi.s.v != 0);

	return sw_twsi;
}

/**
 * Writes to the mio_tws_int register
 *
 * @param bus - bus number to write to
 * @param int_reg - register value to write
 */
static void octeon_i2c_write_int(int bus, cvmx_mio_tws_int_t int_reg)
{
	cvmx_write_csr(CVMX_MIO_TWSX_INT(bus), int_reg.u64);
	cvmx_read_csr(CVMX_MIO_TWSX_INT(bus));
}

/**
 * Test the twsi control register interrupt flag bit used when the HLC is
 * disabled.
 *
 * @param bus - bus number to read from
 *
 * @return 1 if IFLG is set, 0 if clear
 */
static int octeon_i2c_test_iflg(int bus)
{
	cvmx_mio_tws_sw_twsi_t sw_twsi;

	sw_twsi.u64 = 0;
	sw_twsi.s.op = 6; 	/* EOP_IA */
	sw_twsi.s.eop_ia = TWSI_CTL;
	sw_twsi = octeon_i2c_read_sw(bus, sw_twsi);

	return sw_twsi.s.d & 0x08 ? 1 : 0;
}

/**
 * Reads the twsi status register
 *
 * @param bus - bus number to read from
 *
 * @return twsi status register value
 */
static uint8_t octeon_i2c_read_status(int bus)
{
	cvmx_mio_tws_sw_twsi_t sw_twsi;

	sw_twsi.u64 = 0;
	sw_twsi.s.op = 6;	/* EOP IA */
	sw_twsi.s.eop_ia = TWSI_STAT;
	sw_twsi = octeon_i2c_read_sw(bus, sw_twsi);
	return sw_twsi.s.d;
}

/**
 * Writes to the twsi data register
 *
 * @param bus - bus number to write to
 * @param value - data value to write
 */
static void octeon_i2c_write_data(int bus, uint32_t value)
{
	cvmx_mio_tws_sw_twsi_t sw_twsi;

	sw_twsi.u64 = 0;
	sw_twsi.s.op = 6;	/* EOP IA */
	sw_twsi.s.eop_ia = TWSI_DATA;
	sw_twsi.s.d = value;
	octeon_i2c_write_sw(bus, sw_twsi);
}

/**
 * Reads the TWSI data register
 *
 * @param bus - bus number to read from
 *
 * @return value of the TWSI data register
 */
static uint32_t octeon_i2c_read_data(int bus)
{
	cvmx_mio_tws_sw_twsi_t sw_twsi;

	sw_twsi.u64 = 0;
	sw_twsi.s.op = 6;	/* EOP IA */
	sw_twsi.s.eop_ia = TWSI_DATA;
	sw_twsi = octeon_i2c_read_sw(bus, sw_twsi);
	return sw_twsi.s.d;
}

/**
 * Writes to the twsi control register
 *
 * @param bus - bus number to write to
 * @param value - value to write to the control register
 */
static void octeon_i2c_write_ctl(int bus, uint32_t value)
{
	cvmx_mio_tws_sw_twsi_t sw_twsi;

	sw_twsi.u64 = 0;
	sw_twsi.s.op = 6;		/* EOP IA */
	sw_twsi.s.eop_ia = TWSI_CTL;	/* TWSI CTL */
	sw_twsi.s.d = value;
	octeon_i2c_write_sw(bus, sw_twsi);
}

/**
 * Resets the TWSI subsystem for the specified bus
 *
 * @param bus - bus number to reset
 *
 * @return 0 for success, -1 on error
 */
static int octeon_i2c_reset(int bus)
{
#ifndef CONFIG_OCTEON_SIM
	cvmx_mio_twsx_sw_twsi_t sw_twsi;
	int tries;
	uint8_t status = 0;

	debug("%s(%d)\n", __func__, bus);
	sw_twsi.u64 = 0;
	sw_twsi.s.op = 6;
	sw_twsi.s.eop_ia = TWSI_RST;
	octeon_i2c_write_sw(bus, sw_twsi);
	cvmx_wait_io(315);

	for (tries = 10; tries && status != STAT_IDLE; tries--) {
		status = octeon_i2c_read_status(bus);
		udelay(1);
	}
	if (status != STAT_IDLE) {
		printf("%s: TWSI bus %d did not enter idle state\n", __func__, bus);
		return -1;
	}
#endif
	return 0;
}
/**
 * Manually clear the I2C bus and send a stop
 *
 * @param bus - bus number to unblock
 */
static void octeon_i2c_unblock(int bus)
{
	int i;
	cvmx_mio_twsx_int_t int_reg;

	debug("%s: Unblocking bus %d\n", __func__, bus);
	int_reg.u64 = 0;
	for (i = 0; i < 9; i++) {
		int_reg.s.scl_ovr = 0;
		octeon_i2c_write_int(bus, int_reg);
		udelay(5);
		int_reg.s.scl_ovr = 1;
		octeon_i2c_write_int(bus, int_reg);
		udelay(5);
	}
	int_reg.s.sda_ovr = 1;
	octeon_i2c_write_int(bus, int_reg);
	int_reg.s.scl_ovr = 0;
	udelay(5);
	octeon_i2c_write_int(bus, int_reg);
	int_reg.u64 = 0;
	udelay(5);
	octeon_i2c_write_int(bus, int_reg);
	udelay(5);
}

/**
 * Wait for the iflg to be set
 *
 * @param bus - bus number to wait for
 *
 * @returns 0 on success, -1 on error
 */
static int octeon_i2c_wait(int bus)
{
	int timeout = OCTEON_I2C_TIMEOUT * 1000;

	while (!octeon_i2c_test_iflg(bus) && timeout-- > 0)
		udelay(1);

	if (timeout <= 0) {
		printf("%s: Timed out on bus %d\n", __func__, bus);
		return -1;
	}

	return 0;
}

/**
 * Sets the OCTEON I2C slave address
 *
 * @param bus - bus number to set the slave address on
 * @param slave_addr - slave address value to use
 */
void octeon_i2c_set_slave_address(int bus, uint16_t slave_addr)
{
	cvmx_mio_tws_sw_twsi_t sw_twsi;

	sw_twsi.u64 = 0;
	sw_twsi.s.op = 0x6;
	sw_twsi.s.eop_ia = TWSI_SLAVE_ADD;
	sw_twsi.s.d = slave_addr << 1;
	octeon_i2c_write_sw(bus, sw_twsi);

}

/**
 * Returns true if the status code indicates arbitration was lost
 *
 * @param code - twsi status register value
 *
 * @return 1 if arbitration was lost, 0 if not lost
 */
static int octeon_i2c_lost_arb(uint8_t code)
{
	switch (code) {
	/* Arbitration lost in address or data byte */
	case 0x38:
	/*
	 * Arbitration lost in address as master, slave address +
	 * write bit received, ACK transmitted.
	 */
	case 0x68:
	/*
	 * Arbitration lost in address as master, general call address
	 * received, ACK transmitted.
	 */
	case 0x78:
	/*
	 * Arbitration lost in address as master, slave address + read
	 * bit received, ACK transmitted.
	 */
	case 0xb0:
		return 1;
	default:
		return 0;
	}
}

/**
 * Enables or disables the high-level-controller for the specified bus
 *
 * @param bus - bus number to set
 * @param enable - set to 1 to enable, 0 to disable the HLC
 */
void octeon_i2c_hlc_enable(int bus, int enable)
{
	debug("%s: %s the hlc for bus %d\n", __func__,
	      enable ? "enabling" : "disabling", bus);
	if (enable)
		octeon_i2c_write_ctl(bus, TWSI_CTL_CE | TWSI_CTL_ENAB);
	else
		octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB);
}

/**
 * send START to the bus.
 * @param bus - bus number to send start on
 *
 * @returns 0 on success, -1 on error
 */
static int octeon_i2c_start(int bus)
{
	int result;
	uint8_t stat;

	debug("%s: Starting bus %d\n", __func__, bus);
	octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB | TWSI_CTL_STA);

	result = octeon_i2c_wait(bus);
	if (result) {
		stat = octeon_i2c_read_status(bus);
		if (stat == STAT_IDLE) {
			/*
			 * Controller refused to send start flag May
			 * be a client is holding SDA low - let's try
			 * to free it.
			 */
			debug("%s: Unblocking bus %d\n", __func__, bus);
			octeon_i2c_unblock(bus);

			octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB | TWSI_CTL_STA);
			result = octeon_i2c_wait(bus);
		}
		if (result) {
			debug("%s: timeout waiting for IDLE state\n", __func__);
			return result;
		}
	}

	stat = octeon_i2c_read_status(bus);
	if ((stat != STAT_START) && (stat != STAT_RSTART)) {
		debug("%s: Bad status on bus %d (0x%x)\n", __func__, bus, stat);
		return -1;
	}
	return 0;
}

/**
 * send STOP to the bus.
 * @param bus - bus number to send stop on
 *
 * @return 0 on success, -1 on failure
 */
static int octeon_i2c_bus_stop(int bus)
{
	uint8_t stat;

	debug("%s: Stopping bus %d\n", __func__, bus);
	octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB | TWSI_CTL_STP);
	stat = octeon_i2c_read_status(bus);
	if (stat != STAT_IDLE) {
		debug("%s: bad status on bus %d (0x%x)\n", __func__, bus, stat);
		return -1;
	}
	if (gd->flags & GD_FLG_RELOC)
		udelay(twsi_stop_delay[gd->cur_i2c_bus]);

	return 0;
}

/**
 * Send data to the bus
 *
 * @param bus	 bus to send data on
 * @param target Target chip address.
 * @param alen   Address length (1 for 7-bit, 2 for 10-bit)
 * @param data   Pointer to the data to be sent.
 * @param length Length of the data.
 * @param phase  which phase of a combined operation.
 *
 * @return 0 on Success, -1 on Error
 */
int octeon_i2c_bus_write(int bus, int target, int alen, const uint8_t *data,
			 int length, int phase)
{
	int i, result;
	uint8_t stat;

restart:
	debug("%s(%d, 0x%x, %d, 0x%p, %d, %d)\n", __func__, bus, target, alen, data,
	      length, phase);
	if (phase == 0) {
		result = octeon_i2c_start(bus);
		if (result) {
			debug("%s: Error sending start on bus %d, target 0x%x\n",
			      __func__, bus, target);
			return result;
		}

		/* Send the address which can be 7 or 10 bits */
		switch (alen) {
		case 2:
			debug("Warning: alen=2 not tested!\n");
			octeon_i2c_write_data(bus, (target >> 7) << 1);
			octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB);

			result = octeon_i2c_wait(bus);
			if (result)
				return result;

		case 1:
			octeon_i2c_write_data(bus, (target & 0x7f) << 1);
			octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB);

			result = octeon_i2c_wait(bus);
			if (result) {
				debug("%s: Timed out writing target 0x%x, bus %d\n",
				      __func__, target, bus);
				return result;
			}
			break;
		default:
			break;
		}
	}
	/* Send the data */
	for (i = 0; i < length; i++) {
		/* Check the status */
		stat = octeon_i2c_read_status(bus);
		if (phase == 0 && octeon_i2c_lost_arb(stat)) {
			debug("%s: Lost arbitration on bus %d, restarting...\n",
			      __func__, bus);
			goto restart;
		}

		if (stat != STAT_TXADDR_ACK && stat != STAT_TXDATA_ACK) {
			debug("%s: bad status before write (0x%x) when writing to target chip address 0x%x\n",
			      __func__, stat, target);
			return -1;
		}

		/* Send data byte */
		octeon_i2c_write_data(bus, data[i]);

		/* enable the bus */
		octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB);

		/* Wait for operation to finish */
		result = octeon_i2c_wait(bus);
		if (result) {
			debug("%s: Operation timed out on bus %d\n",
			      __func__, bus);
			return result;
		}
	}
	return 0;
}

/**
 * Receive data from the bus.
 *
 * @param bus	 The bus to read data from
 * @param target Target address.
 * @param alen   Address length (1 for 7-bit, 2 for 10-bit)
 * @param data   Pointer to the location to store the data.
 * @param length Length of the data.
 * @param phase  which phase of a combined operation.
 *
 * The address is sent over the bus, then the data is read.
 *
 * Returns number of bytes read or -1 on error
 */
static int octeon_i2c_bus_read(int bus, int target, int alen,
			       uint8_t *data, int length, int phase)
{
	int i, result;
	uint8_t stat;

	if (length < 1) {
		printf("%s: Length too short\n", __func__);
		return -1;
	}

restart:
	debug("%s(%d, 0x%x, %d, 0x%p, %d, %d)\n",
	      __func__, bus, target, alen, data, length, phase);
	result = octeon_i2c_start(bus);
	if (result) {
		debug("%s: Error sending start on bus %d, target 0x%x\n",
		      __func__, bus, target);
		return result;
	}

	/* Send the address which can be 7 or 10 bits */
	switch (alen) {
	case 2:
		octeon_i2c_write_data(bus, ((target >> 7) << 1) | 1);
		octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB);

		result = octeon_i2c_wait(bus);
		if (result)
			return result;
	case 1:
		octeon_i2c_write_data(bus, ((target & 0x7f) << 1) | 1);
		octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB);

		result = octeon_i2c_wait(bus);
		if (result) {
			debug("%s: Timed out writing target 0x%x, bus %d\n",
			      __func__, target, bus);
			return result;
		}
		break;
	default:
		printf("%s: Invalid address length %d\n", __func__, alen);
		return -1;
	}

	for (i = 0; i < length; i++) {
		stat = octeon_i2c_read_status(bus);
		debug("  status %d: 0x%x\n", i, stat);
		if (phase == 0 && octeon_i2c_lost_arb(stat)) {
			debug("%s: Lost arbitration on bus %d, restarting...\n",
			      __func__, bus);
			goto restart;
		}

		if ((stat != STAT_RXDATA_ACK) &&
		    (stat != STAT_RXADDR_ACK)) {
			debug("%s: bad status before read (0x%x), address 0x%x\n",
			      __func__, stat, target);
			return -1;
		}

		if (i + 1 < length)
			octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB | TWSI_CTL_AAK);
		else
			octeon_i2c_write_ctl(bus, TWSI_CTL_ENAB);

		result = octeon_i2c_wait(bus);
		if (result) {
			debug("%s: Operation timed out on bus %d\n",
			      __func__, bus);
			return -1;
		}

		data[i] = octeon_i2c_read_data(bus);
		debug("   data: 0x%x\n", data[i]);
	}
	return i;
}

/**
 * Reads bytes from eeprom and copies to DRAM.
 * Only supports address size of 2 (16 bit internal address.)
 *
 * @param adap   I2C adapter
 * @param chip   chip address
 * @param addr   internal address
 * @param alen   address length
 * @param buffer memory buffer pointer
 * @param len    number of bytes to read
 *
 * @return 0 on Success
 *         1 on Failure
 */
static int octeon_i2c_read(struct i2c_adapter *adap, uint8_t chip, uint addr,
			   int alen, uint8_t *buffer, int len)
{
	unsigned int bus;
	int result = -1;
	uint8_t addr_buf[2];

	bus = adap->hwadapnr;

	debug("%s: Reading device: %#04x address %#04x, alen=%d, len=%d\n",
	      __func__, chip, addr, alen, len);
	debug("  bus: %d\n", bus);

	if (alen > 2  || !buffer || len < 1)
		return 1;

	switch (alen) {
	case 2:
		addr_buf[0] = (addr >> 8) & 0xff;
		addr_buf[1] = addr & 0xff;
		break;
	case 1:
		addr_buf[0] = addr & 0xff;
		break;
	case 0:
		break;
	default:
		printf("%s: Invalid address length %d\n", __func__, alen);
		goto out;
	}

	result = octeon_i2c_bus_write(bus, chip, 1, addr_buf, alen, 0);
	if (result < 0) {
		debug("%s: Error sending address: 0x%x, addr len: %d\n",
		      __func__, addr, alen);
		goto out;
	}

	result = octeon_i2c_bus_read(bus, chip, 1, buffer, len, 1);
	if (result < 0) {
		printf("%s: Error reading bytes\n", __func__);
		goto out;
	}

	result = octeon_i2c_bus_stop(bus);
	if (result)
		debug("%s: Error sending stop to bus %d\n", __func__, bus);

out:
	return (result < 0) ? 1 : 0;
}

/**
 * Reads bytes from memory and copies to eeprom.
 * Only supports address size of 2 (16 bit internal address.)
 *
 * We can only write two bytes at a time to the eeprom, so in some cases
 * we need to to a read/modify/write.
 *
 * Note: can't do single byte write to last address in EEPROM
 *
 * @param adap   i2c adapter
 * @param chip   chip address
 * @param addr   internal address
 * @param alen   address length, must be 0, 1, or 2
 * @param buffer memory buffer pointer
 * @param len    number of bytes to write
 *
 * @return 0 on Success
 *         1 on Failure
 */
static int octeon_i2c_write(struct i2c_adapter *adap, uint8_t chip, uint addr,
			    int alen, uint8_t *buffer, int len)
{
	int result;
	unsigned int bus = adap->hwadapnr;
	uint8_t addr_buf[2];

	debug("%s: Writing device: %#04x address %#04x data %#04x,"
	      " alen=%d, len=%d\n", __func__, chip, addr, *buffer, alen, len);
	debug("  bus: %d\n", bus);
	if (alen > 2 || !buffer || !len)
		return 1;

	switch (alen) {
	case 2:
		addr_buf[0] = (addr >> 8) & 0xff;
		addr_buf[1] = addr & 0xff;
		break;
	case 1:
		addr_buf[0] = addr & 0xff;
		break;
	case 0:
		break;
	default:
		printf("%s: Invalid address length %d\n", __func__, alen);
		return 1;
	}
	result = octeon_i2c_bus_write(bus, chip, 1, addr_buf, alen, 0);
	if (result < 0) {
		printf("%s: Error sending address\n", __func__);
		return 1;
	}
	result = octeon_i2c_bus_write(bus, chip, 1, buffer, len, 1);
	if (result < 0)
		return 1;

	result = octeon_i2c_bus_stop(bus);

	return (result < 0) ? 1 : 0;

}

/**
 * Probe to see if a chip is present using single byte read.  Also good for
 * checking for the completion of EEPROM writes since the chip stops
 * responding until the write completes (typically 10mSec).
 *
 * @param adap    i2c adapter
 * @param chip    chip address
 */
int octeon_i2c_probe(struct i2c_adapter *adap, uint8_t chip)
{
	int result;
	int bus = adap->hwadapnr;
	uint8_t buffer[1];

	debug("%s(%p(%d), 0x%x)\n", __func__, adap, bus, chip);
	result = octeon_i2c_bus_read(bus, chip, 1, buffer, 1, 0);
	debug("result: %d\n", result);
	octeon_i2c_bus_stop(bus);
	return (result < 0);
}

void octeon_init_i2c_bus(struct i2c_adapter *adap, int speed, int slaveaddr)
{
#ifndef CONFIG_OCTEON_SIM_HW_DIFF
	if (gd->arch.i2c_initialized & 1 << adap->hwadapnr)
		return;

	octeon_i2c_set_bus_speed(adap, (unsigned)speed);

	if (slaveaddr && adap->hwadapnr == 0)
		octeon_i2c_set_slave_address(adap->hwadapnr, slaveaddr);

	octeon_i2c_reset(adap->hwadapnr);
	octeon_i2c_hlc_enable(adap->hwadapnr, 0);
	octeon_i2c_unblock(adap->hwadapnr);
	gd->arch.i2c_initialized |= 1 << adap->hwadapnr;
	mdelay(10);
#endif
}

/**
 * Function to set the TWSI bus speed
 *
 * @param bus - bus number to set
 * @param speed - speed in HZ to set the bus to
 *
 * @return 0
 */
static uint octeon_i2c_set_bus_speed(struct i2c_adapter *adap,
				     unsigned int speed)
{
#ifndef CONFIG_OCTEON_SIM_HW_DIFF
#ifndef TWSI_THP
# define TWSI_THP	    (24)	/* TCLK half period (default 24) */
#endif
	unsigned bus = adap->hwadapnr;
	int M_divider, N_divider;
	uint64_t io_clock_mhz;
	cvmx_mio_tws_sw_twsi_t sw_twsi;

	debug("%s: Setting bus %d to %u Hz\n", __func__, bus, speed);
	io_clock_mhz = cvmx_clock_get_rate(CVMX_CLOCK_SCLK) / 1000000;

	/* Slow down the TWSI clock, as the default is too fast in some
	 * cases.
	 */

	/*
	 * Set the TWSI clock to a conservative 100KHz.  Compute the
	 * clocks M divider based on the core clock.
	 *
	 *  TWSI freq = (core freq) / (20 x (M+1) x (thp+1) x 2^N)
	 * M = ((core freq) / (20 x (TWSI freq) x (thp+1) x 2^N)) - 1
	 */

	for (N_divider = 0; N_divider < 8; ++N_divider) {
		M_divider =
		    ((io_clock_mhz * 1000000) /
		     (20 * speed * (TWSI_THP + 1) * (1 << N_divider))) - 1;
		if (M_divider < 16)
			break;
	}

	sw_twsi.u64 = 0;
	sw_twsi.s.op = 6;
	sw_twsi.s.eop_ia = TWSI_CLKCTL_STAT;
	sw_twsi.s.d = ((M_divider & 0xf) << 3) | ((N_divider & 0x7) << 0);
	octeon_i2c_write_sw(bus, sw_twsi);
	mdelay(10);
#undef TWSI_THP
#endif
	return 0;
}

/**
 * Given a register address, for example from the device tree, return the
 * bus number.
 *
 * @param reg_addr - physical address of the base register for the TWSI CSRs
 *
 * @returns bus number or -1 on error.
 */
int octeon_i2c_reg_addr_to_bus(uint64_t reg_addr)
{
	switch (reg_addr) {
	case 0x1180000001000:
		return 0;
	case 0x1180000001200:
		return 1;
	default:
		printf("%s: Unknown reg address 0x%llx\n", __func__, reg_addr);
		return -1;
	}
}

int i2c_set_stop_delay(uint32_t delay)
{
        if (gd->flags & GD_FLG_RELOC) {
                twsi_stop_delay[i2c_get_bus_num()] = delay;
                return 0;
        }
        return -1;
}

uint32_t i2c_get_stop_delay(void)
{
        if (gd->flags & GD_FLG_RELOC)
                return twsi_stop_delay[i2c_get_bus_num()];
        else
                return 0;
}

int init_twsi_bus(void)
{
	i2c_init_all();
	return 0;
}

#if TWSI_BUS_SLAVE_ADDRESS
# define SLAVE_ADDR TWSI_BUS_SLAVE_ADDRESS
#else
# define SLAVE_ADDR 0
#endif

U_BOOT_I2C_ADAP_COMPLETE(octeon0, octeon_init_i2c_bus, octeon_i2c_probe,
			 octeon_i2c_read, octeon_i2c_write,
			 octeon_i2c_set_bus_speed, CONFIG_SYS_I2C_SPEED,
			 SLAVE_ADDR, 0);

#if CONFIG_SYS_MAX_I2C_BUS > 0
U_BOOT_I2C_ADAP_COMPLETE(octeon1, octeon_init_i2c_bus, octeon_i2c_probe,
			 octeon_i2c_read, octeon_i2c_write,
			 octeon_i2c_set_bus_speed, CONFIG_SYS_I2C_SPEED,
			 SLAVE_ADDR, 1);
#endif

#if CONFIG_SYS_MAX_I2C_BUS > 1
U_BOOT_I2C_ADAP_COMPLETE(octeon2, octeon_init_i2c_bus, octeon_i2c_probe,
			 octeon_i2c_read, octeon_i2c_write,
			 octeon_i2c_set_bus_speed, CONFIG_SYS_I2C_SPEED,
			 SLAVE_ADDR, 2);
#endif

#if CONFIG_SYS_MAX_I2C_BUS > 2
U_BOOT_I2C_ADAP_COMPLETE(octeon3, octeon_init_i2c_bus, octeon_i2c_probe,
			 octeon_i2c_read, octeon_i2c_write,
			 octeon_i2c_set_bus_speed, CONFIG_SYS_I2C_SPEED,
			 SLAVE_ADDR, 3);
#endif
