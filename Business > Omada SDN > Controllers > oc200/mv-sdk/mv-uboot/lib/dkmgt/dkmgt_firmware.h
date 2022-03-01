/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmt_firmware.h
 *@brief    Firmware making.
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

#ifndef __DKMGT_FIRMWARE_H__
#define __DKMGT_FIRMWARE_H__

/**************************************************************************************************/
/*                                       CONFIGURATIONS                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      INCLUDE_FILES                                             */
/**************************************************************************************************/
#include "dkmgt_ptn.h"


#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

/**************************************************************************************************/
/*                                      DEFINES                                                   */
/**************************************************************************************************/
#define DKMGT_FIRMWARE_CHECK_MD5		(0x000000001)
#define DKMGT_FIRMWARE_CHECK_RSA		(0x000000002)
#define DKMGT_FIRMWARE_CHECK_DEFAULT	(DKMGT_FIRMWARE_CHECK_RSA)

#define	DKMGT_FIRMWARE_HEADER_SIZE		(4096)
#define	DKMGT_FIRMWARE_RSA_SIZE			(128)
#define	DKMGT_FIRMWARE_RESERVED1_SIZE	(272)
#define	DKMGT_FIRMWARE_RESERVED2_SIZE	(3664)
#define DKMGT_FIRMWARE_MD5_SIZE         (16)

#define DKMGT_FIRMWARE_HEADER_MAGIC        (0xAA55D98F)

struct dkmgt_firmware_header
{
    uint32_t 	version;
    uint32_t 	magic;
    uint32_t 	header_length;
	uint32_t 	total_length;
    uint8_t		md5[DKMGT_FIRMWARE_MD5_SIZE];
	uint8_t		reserved1[DKMGT_FIRMWARE_RESERVED1_SIZE];
	uint8_t		rsa[DKMGT_FIRMWARE_RSA_SIZE];
	uint8_t		reserved2[DKMGT_FIRMWARE_RESERVED2_SIZE];
};

struct dkmgt_firmware_ptn_entry
{
    char        name[DKMGT_PTN_NAME_LEN];
    uint32_t    base;
    uint32_t    size;
    uint32_t    offset;
    uint32_t    length;
	uint32_t	type;
};

struct dkmgt_firmware_ptn_table
{
    struct dkmgt_firmware_ptn_entry ptns[DKMGT_PTN_MAX_CNT];
};

/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                     FUNCTIONS                                                  */
/**************************************************************************************************/
int dkmgt_get_firmwareversion(char *frmwareversion, int len);
int dkmgt_get_mac(char *macstring, int len);
int dkmgt_get_productinfo(char *productinfo, int len);
int dkmgt_factory(void);

int dkmgt_firmware_check(char* firmware, int firmware_size);
int dkmgt_firmware_upgrade(char* firmware, int firmware_size);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  /* __DKMGT_FIRMWARE_H__ */

