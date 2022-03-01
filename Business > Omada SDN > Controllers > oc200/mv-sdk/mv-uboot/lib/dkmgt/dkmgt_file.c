/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmgt_file.c
 *@brief    simple wapper of file operations.
 *@details  
 *
 *@author   Gan Guoheng <ganguoheng@tp-link.net>
 *@version  1.0.0
 *@date     10Nov15
 *
 *@warning  
 *
 *@history  1.0.0, 10Nov15, Gan Guoheng, Create the file.
 */

/**************************************************************************************************/
/*                                       CONFIGURATIONS                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       INCLUDE_FILES                                            */
/**************************************************************************************************/
#include <common.h>
#include <stdlib.h>
#include <linux/ctype.h>

#include "dkmgt_common.h"
#include "dkmgt_file.h"
#include <mmc.h>
#include <spi.h>
#include <spi_flash.h>

#define MMC_BLOCK_SIZE	(512)

/**************************************************************************************************/
/*                                       DEFINES                                                  */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       TYPES                                                    */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       EXTERN_PROTOTYPES                                        */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       LOCAL_PROTOTYPES                                         */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       VARIABLES                                                */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       LOCAL_FUNCTIONS                                          */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                       PUBLIC_FUNCTIONS                                         */
/**************************************************************************************************/
static int _spi_write(int offset, char *buf, int buf_size)
{
	int ret;
	struct spi_flash *flash;

	/* Probe the SPI bus to get the flash device */
	flash = spi_flash_probe(CONFIG_ENV_SPI_BUS,
				CONFIG_ENV_SPI_CS,
				CONFIG_SF_DEFAULT_SPEED,
				CONFIG_SF_DEFAULT_MODE);
	if (!flash) {
		printf("Failed to probe SPI Flash\n");
		return -ENOMEDIUM;
	}

	ret = spi_flash_update(flash, offset, buf_size, (void *)buf);
	if (ret)
		printf("spi_flash_update Error!\n");

	return 0;
}

static int _spi_read(int offset, char *buf, int buf_size)
{
	int ret;
	struct spi_flash *flash;

	/* Probe the SPI bus to get the flash device */
	flash = spi_flash_probe(CONFIG_ENV_SPI_BUS,
				CONFIG_ENV_SPI_CS,
				CONFIG_SF_DEFAULT_SPEED,
				CONFIG_SF_DEFAULT_MODE);
	if (!flash) {
		printf("Failed to probe SPI Flash\n");
		return -ENOMEDIUM;
	}

	ret = spi_flash_read(flash, offset, buf_size, (void *)buf);
	if (ret)
		printf("spi_flash_read Error!\n");

	return 0;
}

static struct mmc *_init_mmc_device(int dev, bool force_init)
{
	struct mmc *mmc;
	int part = 0;
	int ret = 0;
	
	mmc = find_mmc_device(dev);
	if (!mmc) {
		printf("no mmc device at slot %x\n", dev);
		return NULL;
	}

	if (force_init)
		mmc->has_init = 0;
	if (mmc_init(mmc))
		return NULL;
	
	ret = blk_select_hwpart_devnum(IF_TYPE_MMC, dev, part);
	//printf("switch to partitions #%d, %s\n",  part, (!ret) ? "OK" : "ERROR");
	if (ret)
		return NULL;
	
	return mmc;
}

int dkmgt_file_read_by_offset(const char* device, int offset, char *buf, int buf_size, int * read_bytes) 
{
	struct mmc *mmc;
	u32 blk, cnt, n;
	void *addr;

	addr = buf;
	blk = offset / MMC_BLOCK_SIZE;
	if ((buf_size % MMC_BLOCK_SIZE) == 0)
		cnt = buf_size / MMC_BLOCK_SIZE;
	else
		cnt = buf_size / MMC_BLOCK_SIZE + 1;

	mmc = _init_mmc_device(0, true);
	if (!mmc)
		return -1;

	//printf("MMC read: dev # %d, block # %d, count %d ... ", 0, blk, cnt);

	n = blk_dread(mmc_get_blk_desc(mmc), blk, cnt, addr);
	/* flush cache after read */
	flush_cache((ulong)addr, cnt * 512); /* FIXME */
	//printf("%d blocks read: %s\n", n, (n == cnt) ? "OK" : "ERROR");

	*read_bytes = buf_size;
	return (n == cnt) ? 0 : -1;
}

int dkmgt_file_write_by_offset(const char* device, int offset, char *buf, int buf_size, int * write_bytes) 
{
	struct mmc *mmc;
	u32 blk, cnt, n;
	void *addr;

	addr = buf;
	blk = offset / MMC_BLOCK_SIZE;
	if ((buf_size % MMC_BLOCK_SIZE) == 0)
		cnt = buf_size / MMC_BLOCK_SIZE;
	else
		cnt = buf_size / MMC_BLOCK_SIZE + 1;

	mmc = _init_mmc_device(0, true);
	if (!mmc)
		return -1;

	if (mmc_getwp(mmc) == 1) {
		printf("Error: card is write protected!\n");
		return -1;
	}
#if 0
	printf("MMC erase: dev # %d, block # %d, count %d ... ",
	       0, blk, cnt);
	n = blk_derase(mmc_get_blk_desc(mmc), blk, cnt);
	printf("%d blocks erased: %s\n", n, (n == cnt) ? "OK" : "ERROR");
#endif
	printf("MMC write: dev # %d, block # %d, count %d ... ",
	       0, blk, cnt);
	n = blk_dwrite(mmc_get_blk_desc(mmc), blk, cnt, addr);
	printf("%d blocks written: %s\n", n, (n == cnt) ? "OK" : "ERROR");

	return (n == cnt) ? 0 : -1;
}


int dkmgt_file_write_by_offset_block_mode(
	const char* file_path, 
	int offset, 
	char *buf, 
	int buf_size, 
	int block_size, 
	int * write_bytes) 
{
	return _spi_write(offset, buf, buf_size);
}

int dkmgt_file_read_by_offset_block_mode(
	const char* file_path, 
	int offset, 
	char *buf, 
	int buf_size, 
	int block_size, 
	int * read_bytes) 
{
	return _spi_read(offset, buf, buf_size);
}

/**************************************************************************************************/
/*                                       GLOBAL_FUNCTIONS                                         */
/**************************************************************************************************/


