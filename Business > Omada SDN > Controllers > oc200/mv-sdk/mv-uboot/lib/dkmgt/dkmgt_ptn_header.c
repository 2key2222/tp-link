/*! Copyright (c) TP-LINK TECHNOLOGIES CO., LTD.
 *
 *@file     dkmgt_ptn_header.h
 *@brief    Partition Header Handlers.
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
#include "dkmgt_ptn_header.h"

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
#ifdef DEBUG
static void dkmgt_ptn_header_dump(struct dkmgt_ptn_header *  header)
{
    if (!header) {
        return;
    }

    printf("version     0x%08X\n", header->version);
    printf("magic       0x%08X\n", header->magic);
    printf("length      0x%08X (%d)\n", header->length, header->length);
    printf("checksum    0x%08X\n", header->checksum);
}
#endif

struct dkmgt_ptn_header * dkmgt_ptn_header_build(char *ptn_buf, int ptn_buf_size)
{
	struct dkmgt_ptn_header *header = NULL;

	if ((ptn_buf == NULL) || (ptn_buf_size < sizeof(struct dkmgt_ptn_header)))
		return NULL;

	header = malloc(sizeof(struct dkmgt_ptn_header));
	memset((char *)header, 0, sizeof(struct dkmgt_ptn_header));
	memcpy((char *)header, ptn_buf, sizeof(struct dkmgt_ptn_header));
	
    header->magic = ntohl(header->magic);
    header->version = ntohl(header->version);
    header->length = ntohl(header->length);
    header->checksum = ntohl(header->checksum);
		
    if ((DKMGT_PTN_HEADER_MAGIC != header->magic)) {
        DOUT_ERROR("Magic unmatch.magic [0x%08X -- 0x%08X]", header->magic, DKMGT_PTN_HEADER_MAGIC);
        return NULL;
    }

    if (0 != header->checksum) {
        /* not use */;
    }

#ifdef DEBUG
	dkmgt_ptn_header_dump(header);
#endif

    return header;
}


/**************************************************************************************************/
/*                                       GLOBAL_FUNCTIONS                                         */
/**************************************************************************************************/


