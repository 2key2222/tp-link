/*
 * Copyright 2013-2014 Cavium, Inc. <support@cavium.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <spi-config.h>
#include <tinylibc.h>
#include <spi.h>
#include <cvmx-bootloader.h>

#include "tiny_stdio.c"
#include "tinylibc.c"
#include "spi.c"
#include "cvmx-l2c-defs.h"

extern int cvmx_node;
extern int cvmx_uart;
extern unsigned long timestamp;
extern uint64_t cpu_speed;
extern unsigned long __start, __end, _edata;

extern void jump_to_bootloader(uint64_t addr);
typedef void (*move_and_start_t)(uint64_t dest, uint64_t src_start,
				 uint64_t src_end);

extern void move_and_start(uint64_t dest, uint64_t src_start, uint64_t src_end);
extern char move_and_start_end;


int find_header(int node, int cs, int start_offset, int end_offset,
		int interval, struct bootloader_header *header,
		int flags __attribute__((unused)))
{
	int offset;
	u8 spi_addr[4];
	int rc;
	int alen = 3;
	int addr_offset;

	for (offset = start_offset; offset < end_offset; offset += interval) {
		spi_addr[0] = (offset >> 24) & 0xff;
		spi_addr[1] = (offset >> 16) & 0xff;
		spi_addr[2] = (offset >> 8) & 0xff;
		spi_addr[3] = offset & 0xff;
		if (offset >> 24) {
			alen = 4;
			spi_addr[0] = (offset >> 24) & 0xff;
		}

		addr_offset = sizeof(spi_addr) - alen;

		printf("Searching offset %d\r", offset);
		rc = spi_read(node, cs, &spi_addr[addr_offset], alen,
			      header, sizeof(*header));
		if (rc < 0) {
			puts("Error reading bootloader header\n");
			return -1;
		}
#ifdef DEBUG
		print_buffer(offset, header, 1, sizeof(*header), 0);
#endif
		if (octeon_validate_bootloader_header(header))
			return offset;
	}
	return -1;
}

int load_spi(int node, int cs, int offset, u64 addr)
{
	struct bootloader_header *header = (struct bootloader_header *)addr;
	u8 *buffer;
	uint start;
	uint image_size;
	int fn_size;
	move_and_start_t fn_ptr;
	int rc;
	u8 spi_addr[3];
	u8 __attribute__((unused)) id[5];

	spi_init();

#ifdef CONFIG_SPI_NOR
	if (spi_read_id(node, cs, id))
		puts("Error reading ID\n");
	else
		printf("SPI ID: %02x:%02x:%02x:%02x:%02x\n",
		       id[0], id[1], id[2], id[3], id[4]);
#endif

	start = (uint)((char *)&_edata - (char *)&__start);
	start += CONFIG_HEADER_SEARCH_INCREMENT - 1;
	start &= ~(CONFIG_HEADER_SEARCH_INCREMENT - 1);

	offset = find_header(node, cs, start, CONFIG_HEADER_SEARCH_END,
			     CONFIG_HEADER_SEARCH_INCREMENT, header, 0);
	if (offset < 0)
		puts("header not found\n");
	else {
		printf("header found at offset 0x%x\n", offset);

		printf("Image %d.%d: address: 0x%lx, header length: %d, data length: %d\n",
		       header->maj_rev, header->min_rev, header->address,
		       header->hlen, header->dlen);
		buffer = CASTPTR(uint8_t, STAGE2_LOAD_ADDR);
		image_size = header->hlen + header->dlen;
		l2c_lock_mem_region(STAGE2_LOAD_ADDR, image_size + 256);
		spi_addr[0] = (offset >> 16) & 0xff;
		spi_addr[1] = (offset >> 8) & 0xff;
		spi_addr[2] = offset & 0xff;
		debug("Reading %u bytes to address %p\n", image_size, buffer);
		rc = spi_read(node, cs, spi_addr, sizeof(spi_addr),
			      buffer, image_size);
		if (rc < 0) {
			puts("Error reading stage 1.5 bootloader\n");
			return -1;
		}
		printf("Validating data...\n");
		if (octeon_validate_data((struct bootloader_header *)buffer)) {
			puts("Corrupted stage 1.5 bootloader\n");
			return -1;
		}
		fn_size = (void *)(&move_and_start_end) - (void *)(&move_and_start);
		fn_ptr = (move_and_start_t)
		((uint8_t *)((STAGE2_LOAD_ADDR + image_size + 64) & ~7ull));
		memcpy(fn_ptr, &move_and_start, fn_size);
		printf("Starting stage 1.5 bootloader at 0x%llx\n", STAGE2_START_ADDR);

		CVMX_ICACHE_INVALIDATE;
		CVMX_ICACHE_INVALIDATE2;
		fn_ptr(STAGE2_START_ADDR, STAGE2_LOAD_ADDR, image_size);
	}

	return 0;
}

int main(void)
{
	cvmx_l2c_wpar_ppx_t l2c_wpar_ppx;

	/* Turn way partitioning back on */
	l2c_wpar_ppx.u64 = 0;
	l2c_wpar_ppx.s.mask = 0;
	cvmx_write_csr(CVMX_L2C_WPAR_PPX(0), l2c_wpar_ppx.u64);

	cvmx_node = cvmx_get_node_num();

	cpu_speed = octeon_get_cpu_speed();

	octeon_set_uart(UART_NODE, UART_PORT);
	octeon_set_baudrate(UART_BAUD_RATE, 0);
	puts("SPI stage 1 bootloader\n");
	load_spi(0, 0, 0x2000, STAGE2_LOAD_ADDR);

	puts("Stage 1.5 bootloader did not start\n");
	octeon_do_reset();
	return 0;
}
