

#ifndef __SYS_SYSTEM_H__
#define __SYS_SYSTEM_H__

#include <sys/types.h>

#define MTD_CONFIG_LEN	64	/* max len of model, firmware version and product version */
#define MTD_MAC_LEN		18	/* MAC string length */
#define MTD_DEV_ID_LEN	20
#define MTD_OEM_ID_LEN	16
#define MTD_HW_ID_LEN	16	/* This is an MD5 value */
#define MTD_FW_ID_LEN	16	/* This is also an MD5 value */
#define MTD_TP_HEADER_LEN	512
#define MTD_MAC_HEX_LEN	6
#define MTD_CLOUD_ACCOUNT_LEN	128
#define MTD_REGION_STR_LEN	3	/* including '\0' */

#define MTD_CONF_MEMTEST_VALUE_START	0xaa
#define MTD_CONF_MEMTEST_VALUE_FAILED	0xcb
#define MTD_CONF_MEMTEST_VALUE_SUCCEED	0xcc
#define MTD_CONF_MEMTEST_VALUE_UNINIT	0xff

/* volatile region support */
#define MTD_DEFAULT_REGION		"UN"

#ifndef BOOL
#define BOOL int
#endif

#ifndef STRINGIZE
#define STRINGIZE_NX(A)	#A
#define STRINGIZE(A)	STRINGIZE_NX(A)
#endif

int sysMtdGetMemTestResult(unsigned char *valueOut);
int sysMtdSetMemTest(unsigned char value);

int sysMtdGetDevId(unsigned char devIdOut[MTD_DEV_ID_LEN]);
int sysMtdSetDevId(const unsigned char devId[MTD_DEV_ID_LEN]);

int sysMtdGetHwId(unsigned char hwIdOut[MTD_HW_ID_LEN]);
int sysMtdSetHwId(const unsigned char hwId[MTD_HW_ID_LEN]);

int sysMtdGetOemId(unsigned char oemIdOut[MTD_OEM_ID_LEN]);
int sysMtdSetOemId(const unsigned char oemId[MTD_OEM_ID_LEN]);

int sysMtdGetLastSoftwareVersion(char lastVerOut[MTD_CONFIG_LEN]);	// defined for future use: Software may do some special operation by different versions.
int sysMtdSetLastSoftwareVersionAsCurrent(void);

int sysMtdGetTpHeader(unsigned char headerOut[MTD_TP_HEADER_LEN]);
int sysMtdSetTpHeader(const unsigned char header[MTD_TP_HEADER_LEN]);

int sysMtdGetExtMicInfo(void *infoOut, size_t length);
int sysMtdSetExtMicInfo(const void *info, size_t length);

int sysMtdGetLedConf(unsigned char *confOut);
int sysMtdSetLedConf(const unsigned char conf);

int sysMtdGetApMacHex(unsigned char macHex[MTD_MAC_HEX_LEN]);
int sysMtdSetApMacHex(const unsigned char macHex[MTD_MAC_HEX_LEN]);

BOOL sysMtdMapCheck(void);

int sysMtdGetCloudAccount(char account[MTD_CLOUD_ACCOUNT_LEN]);
int sysMtdSetCloudAccount(const char account[MTD_CLOUD_ACCOUNT_LEN]);

int sysMtdSetRegionString(const char *regionStr);
int sysMtdGetRegionString(char *pRegionOut, size_t nRegionSize);

const char *sysMtdGetManufactorySoftwareVersion(void);
const char *sysMtdGetErrorString(void);

#endif	/* end of file */

