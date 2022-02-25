/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>


#include <asm/arch/cvmx.h>
#include <ata.h>
#include <part.h>
#include <fat.h>
#include <spi.h>
#include <spi_flash.h>
#include <../disk/part_dos.h>
#include <asm/arch/cvmx-bootloader.h>
#include <asm/gpio.h>
#include <asm/arch/lib_octeon.h>
#include <asm/arch/cvmx-l2c.h>

#include <nand.h>



#define CONFIG_SYS_MAX_NAND_DEVICE 1

extern int nand_curr_device;
extern nand_info_t nand_info[CONFIG_SYS_MAX_NAND_DEVICE];

#ifdef CONFIG_CMD_GO
# ifdef CONFIG_OCTEON
#  include <asm/arch/octeon_boot.h>
# endif
/* Allow ports to override the default behavior */
#ifndef CONFIG_TP_MODEL_OSG_PRO
__attribute__((weak))
unsigned long do_go_exec(ulong (*entry)(int, char * const []), int argc,
				 char * const argv[])
{
#ifdef CONFIG_OCTEON
	octeon_bootloader_shutdown();
#endif
	return entry (argc, argv);
}
#else
extern unsigned long do_go_exec(ulong (*entry)(int, char * const []), int argc,
				char * const argv[]);
#endif
DECLARE_GLOBAL_DATA_PTR;

#define CONFIG_OCTEON_FS_LOAD_ADDR  0x81200000


static int do_go(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong	addr, rc;
	int     rcode = 0;

	if (argc < 2)
		return CMD_RET_USAGE;

	addr = simple_strtoul(argv[1], NULL, 16);

	printf ("## Starting application at 0x%08lX ...\n", addr);

	/*
	 * pass address parameter as argv[0] (aka command name),
	 * and all remaining args
	 */
	rc = do_go_exec ((void *)addr, argc - 1, argv + 1);
	if (rc != 0) rcode = 1;

	printf ("## Application terminated, rc = 0x%lX\n", rc);
	return rcode;
}

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	go, CONFIG_SYS_MAXARGS, 1,	do_go,
	"start application at address 'addr'",
	"addr [arg ...]\n    - start application at address 'addr'\n"
	"      passing 'arg' as arguments"
);

#endif

U_BOOT_CMD(
	reset, 1, 0,	do_reset,
	"Perform RESET of the CPU",
	""
);
int do_loadfs(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	struct spi_flash *flash;
	struct bootloader_header *header;
	uint32_t addr;
	const int bus = 0;
	const int cs = 0;
	const int speed = CONFIG_SF_DEFAULT_SPEED;
	const int mode = SPI_MODE_3;
	void *buf;
	int len;
	int offset;
	int found_offset = -1;
	int found_size = 0;
	int rc;
	int failsafe;

	flash = spi_flash_probe(bus, cs, speed, mode);
	if (!flash) {
		printf("Failed to initialize SPI flash at %u:%u", bus, cs);
		return -1;
	}
	/* addr = getenv_ulong("octeon_fs_load_addr", 16,
			    CONFIG_OCTEON_FS_LOAD_ADDR); */
			    addr = 0x82200000;

	header = CASTPTR(struct bootloader_header, addr);
	buf = (void *)header;
#ifdef CONFIG_OCTEON_FAILSAFE_GPIO
	failsafe = gpio_direction_input(CONFIG_OCTEON_FAILSAFE_GPIO);
#else
	failsafe = 0;
#endif

	//offset = CONFIG_OCTEON_SPI_BOOT_START;
	offset = 0x200000;
	/*do {
		printf("1:offset:%x;len:%x;addr:%x\n",offset,sizeof(*header),header);
		if (spi_flash_read(flash, offset, sizeof(*header), header)) {
			printf("Could not read SPI flash to find bootloader\n");
			return -1;
		}

		if (!validate_bootloader_header(header) ||
		    (header->board_type != gd->arch.board_desc.board_type)) {
			offset += flash->erase_size;
			continue;
		}

		len = header->hlen + header->dlen - sizeof(*header);
		if (len < 0) {
			printf("Invalid length calculated, hlen: %d, dlen: %d\n",
			       header->hlen, header->dlen);
			offset += flash->erase_size;
			continue;
		}

		if (header->board_type == CVMX_BOARD_TYPE_GENERIC) {
			printf("Skip generic bootloader at offset 0x%x\n",
			      offset);
			offset += (len + flash->erase_size - 1) &
							~flash->erase_size;
			continue;
		}

		/* Read rest of bootloader */
		/*printf("2:offset:%x;len:%x;addr:%x\n",offset+sizeof(*header),len,&header[1]);
		rc = spi_flash_read(flash, offset + sizeof(*header), len,
				    &header[1]);
		if (rc) {
			printf("Could not read %d bytes from SPI flash\n",
			       header->dlen + header->hlen);
			return -1;
		}
		if (calculate_image_crc(header) != header->dcrc) {
			printf("Found corrupted image at offset 0x%x, continuing search\n",
			       offset);
			offset += flash->erase_size;
			continue;
		}
		found_offset = offset;
		found_size = header->hlen + header->dlen;
		printf("Found valid SPI bootloader at offset: 0x%x, size: %d bytes\n",
		       found_offset, found_size);
		if (failsafe)
			break;
		/* Skip past the current image to the next one */
		/*offset += (found_size + flash->erase_size - 1) &
							~(flash->erase_size);
	} while (offset < 0x600000);

	if (found_offset < 0) {
		printf("Could not find stage 3 bootloader\n");
		return -1;
	}/*

	/* If we searched for multiple bootloaders and didn't stop at the first
	 * one (i.e. failsafe) then re-read the last good one found into
	 * memory.
	 */
	/* if (found_offset != offset) {
		printf("still read\n");*/
		//rc = spi_flash_read(flash, found_offset, found_size, header);
	rc = spi_flash_read(flash, 0x281000, 0x17f000, header);
		if (rc) {
			printf("Error reading bootloader from offset 0x%x, size: 0x%x\n",
			       found_offset, found_size);
			return -1;
		}
	//}

	//do_go_exec(buf, argc - 1, argv + 1);

	return 0;
}


U_BOOT_CMD(loadfs,1,0,do_loadfs,
		"Load and execute the stage 3 bootloader",
	   "Load and execute the stage 3 bootloader"

);

#define CACHE_LINE_SIZE		128

void l2c_lock_line(uint64_t addr)
{
	addr |= (2ull << 62);
	asm("cache 31, 0(%[line])" :: [line] "r" (addr));	/* Lock L2 */
}

/**
 * Locks a memory region in the L2 cache
 *
 * @param start - start address to begin locking
 * @param len - length in bytes to lock
 */
void l2c_lock_mem_region(uint64_t start, uint64_t len)
{
	uint64_t end;

	/* Round start/end to cache line boundaries */
	len += start & (CACHE_LINE_SIZE - 1);
	start &= ~(CACHE_LINE_SIZE - 1);
	end = start + len;

	while (start <= end) {
		l2c_lock_line(start);
		start += CACHE_LINE_SIZE;
	}
	asm volatile("sync");
}


typedef void (*move_and_start_t)(uint64_t dest, uint64_t src_start,
				 uint64_t src_end);

extern void move_and_start(uint64_t dest, uint64_t src_start, uint64_t src_end);
extern char move_and_start_end;
#define LOAD_ADDR_TEST 0xFFFFFFFF82200000ull
#define START_ADDR_TEST 0xFFFFFFFF82000000ull

void do_cleancache(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
			  /*  CVMX_SYNC;
    CVMX_ICACHE_INVALIDATE;
	CVMX_ICACHE_INVALIDATE2;
    CVMX_DCACHE_INVALIDATE;*/

	/*CVMX_SYNCW;
		printf(" flushing L2 cache...\n");

		cvmx_l2c_flush();
		printf("  Invalidating icache\n");
		CVMX_ICACHE_INVALIDATE;
		printf("  Done.\n  Unlocking U-Boot from cache...\n\n");*/

		uint image_size = 1503232;
	int fn_size;
	move_and_start_t fn_ptr;

//	l2c_lock_mem_region(LOAD_ADDR_TEST, image_size + 256);

	fn_size = (void *)(&move_and_start_end) - (void *)(&move_and_start);
		fn_ptr = (move_and_start_t)
		((uint8_t *)((LOAD_ADDR_TEST + image_size + 64) & ~7ull));
		memcpy(fn_ptr, &move_and_start, fn_size);
		printf("Starting stage 1.5 bootloader at 0x%llx\n", START_ADDR_TEST);

		CVMX_ICACHE_INVALIDATE;
		CVMX_ICACHE_INVALIDATE2;
				cvmx_l2c_flush();
		fn_ptr(START_ADDR_TEST, LOAD_ADDR_TEST, image_size);

}

U_BOOT_CMD(cleancache,1,0,do_cleancache,
		"Load and execute the stage 3 bootloader",
	   "Load and execute the stage 3 bootloader"

);


int do_octbootfs(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	//struct spi_flash *flash;
	printf("loadboot\n");
	struct bootloader_header *header;
	uint32_t addr;
	//const int bus = 0;
	//const int cs = 0;
	//const int speed = CONFIG_SF_DEFAULT_SPEED;
	//const int mode = CONFIG_SF_DEFAULT_MODE;
	void *buf;
	int bufsize;
	int len;
	int offset;
	int found_offset = -1;
	int found_size = 0;
	int rc;
	int failsafe;

	nand_info_t *nand;
	int dev = nand_curr_device;
	nand = &nand_info[dev];
		//bufsize = raspi_read(buf, PARTI_PTN, bufsize);
	//nand_read_skip_bad(nand, PARTI_PTN, &bufsize, NULL, nand->size, buf);

	/*flash = spi_flash_probe(bus, cs, speed, mode);
	if (!flash) {
		printf("Failed to initialize SPI flash at %u:%u", bus, cs);
		return -1;
	}*/
	addr = getenv_ulong("octeon_stage3_load_addr", 16,
			    0x82200000);

	header = CASTPTR(struct bootloader_header, addr);
	buf = (void *)header;
#ifdef CONFIG_OCTEON_FAILSAFE_GPIO
	failsafe = gpio_direction_input(CONFIG_OCTEON_FAILSAFE_GPIO);
#else
	failsafe = 0;
#endif
offset = 0;
bufsize = 0x200000;

	if(nand_read_skip_bad(nand, offset, &bufsize, NULL, nand->size, header))
	{
		printf("errror\n");
	}
#if 0
	offset = 0x1000;
	bufsize = sizeof(*header);
	do {
		if (nand_read_skip_bad(nand, offset, &bufsize, NULL, nand->size, header)) {
			printf("Could not read SPI flash to find bootloader\n");
			return -1;
		}

		if (!validate_bootloader_header(header) ||
		    (header->board_type != gd->arch.board_desc.board_type)) {
			offset += nand->erasesize;
			continue;
		}

		len = header->hlen + header->dlen - sizeof(*header);
		if (len < 0) {
			printf("Invalid length calculated, hlen: %d, dlen: %d\n",
			       header->hlen, header->dlen);
			offset += nand->erasesize;
			continue;
		}

		if (header->board_type == CVMX_BOARD_TYPE_GENERIC) {
			debug("Skip generic bootloader at offset 0x%x\n",
			      offset);
			offset += (len + nand->erasesize - 1) &
							~nand->erasesize;
			continue;
		}

		/* Read rest of bootloader */
		/*rc = spi_flash_read(flash, offset + sizeof(*header), len,
				    &header[1]);*/
		rc = nand_read_skip_bad(nand, offset + sizeof(*header), &len, NULL, nand->size, &header[1]);
		if (rc) {
			printf("Could not read %d bytes from SPI flash\n",
			       header->dlen + header->hlen);
			return -1;
		}
		if (calculate_image_crc(header) != header->dcrc) {
			printf("Found corrupted image at offset 0x%x, continuing search\n",
			       offset);
			offset += nand->erasesize;
			continue;
		}
		found_offset = offset;
		found_size = header->hlen + header->dlen;
		printf("Found valid SPI bootloader at offset: 0x%x, size: %d bytes\n",
		       found_offset, found_size);
		if (failsafe)
			break;
		/* Skip past the current image to the next one */
		offset += (found_size + nand->erasesize - 1) &
							~(nand->erasesize);
	} while (offset < 0x600000);

	if (found_offset < 0) {
		printf("Could not find stage 3 bootloader\n");
		return -1;
	}

	/* If we searched for multiple bootloaders and didn't stop at the first
	 * one (i.e. failsafe) then re-read the last good one found into
	 * memory.
	 */
	if (found_offset != offset) {
		//rc = spi_flash_read(flash, found_offset, found_size, header);
		rc = nand_read_skip_bad(nand, found_offset, &found_size, NULL, nand->size, header);
		if (rc) {
			printf("Error reading bootloader from offset 0x%x, size: 0x%x\n",
			       found_offset, found_size);
			return -1;
		}
	}
#endif
	//do_go_exec(buf, argc - 1, argv + 1);

	return 0;
}

U_BOOT_CMD(octbootfs,1,0,do_octbootfs,
		"Load and execute the stage 3 bootloader",
	   "Load and execute the stage 3 bootloader"

);

