/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmgt_utils.c
 *@brief    utils for all apps.
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

#ifndef __DKMGT_COMMON_H__
#define __DKMGT_COMMON_H__

/**************************************************************************************************/
/*                                       CONFIGURATIONS                                           */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      INCLUDE_FILES                                             */
/**************************************************************************************************/

#include "thirdparty/cJSON/cJSON.h"


#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

/**************************************************************************************************/
/*                                      DEFINES                                                   */
/**************************************************************************************************/
//#define DEBUG
#undef DEBUG

#define DKMGT_FLASH_BLOCK_SIZE          (1024*64)

#define ASSERT(expr) assert(expr)

#ifdef DEBUG
#define DOUT_TRACE(fmt, args...) printf("[TRACE]%s:%d | " fmt "\n", __FILE__, __LINE__, ##args)
#else
#define DOUT_TRACE(fmt, args...)
#endif

#define DOUT_INFO(fmt, args...) \
        printf("[INFO]%s:%d | " fmt "\n", __FILE__, __LINE__, ##args)

#define DOUT_ERROR(fmt, args...) \
        printf("[ERROR]%s:%d | " fmt "\n", __FILE__, __LINE__, ##args)

#define DOUT_LEAVE(err,errVal) \
        do\
        {\
            err = errVal;\
            goto leave;\
        } while ( 0 )

/**************************************************************************************************/
/*                                      TYPES                                                     */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                      VARIABLES                                                 */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                     FUNCTIONS                                                  */
/**************************************************************************************************/

/* WARNING: the 'json_data' *MAY* not have a terminator. */
cJSON* dkmgt_parse_json_data(char * json_data, int json_len);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  /* __DKMGT_COMMON_H__ */



