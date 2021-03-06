/***********************license start***************
 * Copyright (c) 2011  Cavium Inc. (support@cavium.com). All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.

 *   * Neither the name of Cavium Inc. nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.

 * This Software, including technical data, may be subject to U.S. export  control
 * laws, including the U.S. Export Administration Act and its  associated
 * regulations, and may be subject to export or import  regulations in other
 * countries.

 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR
 * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/

/**
 * @file
 *
 * Interface to the CN6XXX and CN70/71XX hardware HFA engine.
 *
 * <hr>$Revision: 49448 $<hr>
 */

#ifndef __CVMX_HFA_H__
#define __CVMX_HFA_H__

#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
#include <asm/octeon/cvmx-wqe.h>
#include <asm/octeon/cvmx-fpa.h>
#include <asm/octeon/cvmx-bootmem.h>
#include <asm/octeon/cvmx.h>
#include <asm/octeon/cvmx-config.h>

#ifdef CVMX_ENABLE_DFA_FUNCTIONS
/* DFA queue cmd buffers */

#define CVMX_FPA_DFA_POOL                   (4)             /**< DFA command buffers */
#define CVMX_FPA_DFA_POOL_SIZE              (2 * CVMX_CACHE_LINE_SIZE)
#endif

#else 
#include "cvmx-wqe.h"
#include "cvmx-fpa.h"
#include "cvmx-bootmem.h"
#ifndef CVMX_DONT_INCLUDE_CONFIG
#include "executive-config.h"
#include "cvmx-config.h"
#endif
#endif
#define HFA_MIPS_CAVIUM_L2C_FLUSH 2002

#define ENABLE_DEPRECATED	/* Set to enable the old 18/36 bit names */
#define CHECK_SIZE     128

#ifdef	__cplusplus
/* *INDENT-OFF* */
extern "C" {
/* *INDENT-ON* */
#endif

typedef union {
	uint64_t u64;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
        uint64_t varies0:34;
        uint64_t store_full:1;
        uint64_t varies1:2;
        uint64_t itype:3;
        uint64_t varies2:24;
#else
        uint64_t varies2:24;
        uint64_t itype:3;
        uint64_t varies1:2;
        uint64_t store_full:1;
        uint64_t varies0:34;
#endif
    };
    struct {
#ifdef __BIG_ENDIAN_BITFIELD
        uint64_t f1:3;
        uint64_t unused1:2;
        uint64_t snode:27;
        uint64_t gather_mode:1;
        uint64_t little_endian:1;
        uint64_t store_full:1;
        uint64_t load_through:1;
        uint64_t small:1;
        uint64_t itype:3;
        uint64_t unused0:2;
        uint64_t mbase:22;
#else
        uint64_t mbase:22;
        uint64_t unused0:2;
        uint64_t itype:3;
        uint64_t small:1;
        uint64_t load_through:1;
        uint64_t store_full:1;
        uint64_t little_endian:1;
        uint64_t gather_mode:1;
        uint64_t snode:27;
        uint64_t unused1:2;
        uint64_t f1:3;
#endif
    } walk;
    struct {
#ifdef __BIG_ENDIAN_BITFIELD
        uint64_t unused4:7;
        uint64_t dbase:9;
        uint64_t unused3:2;
        uint64_t cbase:14;
        uint64_t gather_mode:1;
        uint64_t little_endian:1;
        uint64_t store_full:1;
        uint64_t load_through:1;
        uint64_t unused2:1;
        uint64_t itype:3;
        uint64_t unused1:6;
        uint64_t dsize:10;
        uint64_t unused0:2;
        uint64_t pgid:6;
#else
        uint64_t pgid:6;
        uint64_t unused0:2;
        uint64_t dsize:10;
        uint64_t unused1:6;
        uint64_t itype:3;
        uint64_t unused2:1;
        uint64_t load_through:1;
        uint64_t store_full:1;
        uint64_t little_endian:1;
        uint64_t gather_mode:1;
        uint64_t cbase:14;
        uint64_t unused3:2;
        uint64_t dbase:9;
        uint64_t unused4:7;
#endif
    } cload;
    struct {
#ifdef __BIG_ENDIAN_BITFIELD
        uint64_t unused2:32;
        uint64_t gather_mode:1;
        uint64_t little_endian:1;
        uint64_t store_full:1;
        uint64_t load_through:1;
        uint64_t unused1:1;
        uint64_t itype:3;
        uint64_t unused0:2;
        uint64_t mbase:22;
#else
        uint64_t mbase:22;
        uint64_t unused0:2;
        uint64_t itype:3;
        uint64_t unused1:1;
        uint64_t load_through:1;
        uint64_t store_full:1;
        uint64_t little_endian:1;
        uint64_t gather_mode:1;
        uint64_t unused2:32;
#endif
    } mload;
    struct {
#ifdef __BIG_ENDIAN_BITFIELD
        uint64_t unused2:34;
        uint64_t store_full:1;
        uint64_t unused1:2;
        uint64_t itype:3;
        uint64_t unused0:24;
#else
        uint64_t unused0:24;
        uint64_t itype:3;
        uint64_t unused1:2;
        uint64_t store_full:1;
        uint64_t unused2:34;
#endif
    } free;
} cvmx_hfa_word0_t;

typedef union {
    uint64_t u64;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
        uint64_t varies0:24;
        uint64_t rptr:40;
#else
        uint64_t rptr:40;
        uint64_t varies0:24;
#endif
    };
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t rmax:16;
		uint64_t f2:8;
		uint64_t rptr:40;
#else
		uint64_t rptr:40;
		uint64_t f2:8;
		uint64_t rmax:16;
#endif
	} walk;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t unused1:13;
		uint64_t rmax:3;
		uint64_t unused0:8;
		uint64_t rptr:40;
#else
		uint64_t rptr:40;
		uint64_t unused0:8;
		uint64_t rmax:3;
		uint64_t unused1:13;
#endif
	} cload;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t unused1:4;
		uint64_t rmax:12;
		uint64_t unused0:8;
		uint64_t rptr:40;
#else
		uint64_t rptr:40;
		uint64_t unused0:8;
		uint64_t rmax:12;
		uint64_t unused1:4;
#endif
	} mload;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t unused:24;
		uint64_t rptr:40;
#else
		uint64_t rptr:40;
		uint64_t unused:24;
#endif
	} free;
} cvmx_hfa_word1_t;

typedef union {
    uint64_t u64;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
        uint64_t varies0:20;
        uint64_t clmsk:4;
        uint64_t varies1:40;
#else
        uint64_t varies1:40;
        uint64_t clmsk:4;
        uint64_t varies0:20;
#endif
    };
    struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t dlen:16;
	    uint64_t f5:2;
		uint64_t unused:2;
		uint64_t clmsk:4;
		uint64_t dptr:40;
#else
		uint64_t dptr:40;
		uint64_t clmsk:4;
		uint64_t unused:2;
	    uint64_t f5:2;
		uint64_t dlen:16;
#endif
	} walk;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t dlen:16;
		uint64_t unused:4;
		uint64_t clmsk:4;
		uint64_t dptr:40;
#else
		uint64_t dptr:40;
		uint64_t clmsk:4;
		uint64_t unused:4;
		uint64_t dlen:16;
#endif
	} cload;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t dlen:16;
        uint64_t f5:2;
		uint64_t unused:2;
		uint64_t clmsk:4;
		uint64_t dptr:40;
#else
		uint64_t dptr:40;
		uint64_t clmsk:4;
		uint64_t unused:2;
        uint64_t f5:2;
		uint64_t dlen:16;
#endif
	} mload;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t unused1:20;
		uint64_t clmsk:4;
		uint64_t unused0:40;
#else
		uint64_t unused0:40;
		uint64_t clmsk:4;
		uint64_t unused1:20;
#endif
	} free;
} cvmx_hfa_word2_t;

typedef union {
    uint64_t u64;
    struct {
#ifdef __BIG_ENDIAN_BITFIELD
        uint64_t varies0:24;
        uint64_t wqptr:40;
#else
        uint64_t wqptr:40;
        uint64_t varies0:24;
#endif
    };
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t unused1:2;
		uint64_t vgid:8;
		uint64_t unused0:5;
		uint64_t f3:9;
		uint64_t wqptr:40;
#else
		uint64_t wqptr:40;
		uint64_t f3:9;
		uint64_t unused0:5;
		uint64_t vgid:8;
		uint64_t unused1:2;
#endif
	} walk;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t unused1:2;
		uint64_t vgid:8;
		uint64_t unused0:7;
		uint64_t f4:7;
		uint64_t wqptr:40;
#else
		uint64_t wqptr:40;
		uint64_t f4:7;
		uint64_t unused0:7;
		uint64_t vgid:8;
		uint64_t unused1:2;
#endif
	} cload;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t unused1:2;
		uint64_t vgid:8;
		uint64_t unused0:7;
		uint64_t f4:7;
		uint64_t wqptr:40;
#else
		uint64_t wqptr:40;
		uint64_t f4:7;
		uint64_t unused0:7;
		uint64_t vgid:8;
		uint64_t unused1:2;
#endif
	} mload;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		uint64_t unused1:2;
		uint64_t vgid:8;
		uint64_t unused0:14;
		uint64_t wqptr:40;
#else
		uint64_t wqptr:40;
		uint64_t unused0:14;
		uint64_t vgid:8;
		uint64_t unused1:2;
#endif
	} free;
} cvmx_hfa_word3_t;

typedef union {
	uint64_t u64[4];
	struct {
		cvmx_hfa_word0_t word0;
		cvmx_hfa_word1_t word1;
		cvmx_hfa_word2_t word2;
		cvmx_hfa_word3_t word3;
	};
} cvmx_hfa_command_t;

typedef struct
{
	cvmx_fpa_pool_config_t dfa_pool;
}cvmx_dfa_app_config_t;

extern CVMX_SHARED cvmx_dfa_app_config_t dfa_config;

static inline int64_t cvmx_fpa_get_dfa_pool(void)
{
	return (dfa_config.dfa_pool.pool_num);	
} 

static inline uint64_t cvmx_fpa_get_dfa_pool_block_size(void)
{
	return (dfa_config.dfa_pool.buffer_size);	
}


#ifdef CVMX_ENABLE_DFA_FUNCTIONS
/**
 * Initialize the DFA/HFA hardware before use
 * Returns 0 on success, -1 on failure
 */
int cvmx_hfa_initialize(void);

/**
 * Shutdown and cleanup resources used by the DFA/HFA
 */
int cvmx_hfa_shutdown(void);

/**
 * Submit a command to the HFA block
 *
 * @param command HFA command to submit
 *
 * @return Zero on success, negative on failure
 */
int cvmx_hfa_submit(cvmx_hfa_command_t * command);

/**
 * Allocate a block of memory from the free list that was passed
 * to the application by the bootloader.
 * 
 * @param size      Size in bytes of block to allocate
 * @param alignment Alignment required - must be power of 2
 *
 *  @return pointer to block of memory, NULL on error 
 */

void *hfa_bootmem_alloc(unsigned long int size, uint64_t alignment);

/**
 * Frees a block to the bootmem allocator list.  
 *
 * @param ptr  	   address of block  (memory pointer (void*))
 * @param size     size of block in bytes.
 *
 * @return 1 on success,
 *         0 on failure
 *
 */

int hfa_bootmem_free(void *ptr, unsigned long int size);
/**
 * Finds a named bootmem block by name.
 *
 * @param name   name of block to free
 *
 * @return pointer to named block descriptor on success
 *         0 on failure
 */

const cvmx_bootmem_named_block_desc_t *hfa_bootmem_find_named_block(const char *name);

/**
 * Create a named bootmem block by name.
 *
 * @param name   create named block with this name
 *
 * @return pointer to named block on success
 *         NULL on failure
 */

void *hfa_bootmem_alloc_named( uint64_t size, uint64_t alignment, const char *name);

/**
 * Frees a named bootmem block by name.
 *
 * @param name   name of block to free
 *
 * @return 1 on success
 *         0 on failure
 */
int  hfa_bootmem_free_named(const char *name);


/**
 * Flushes (and unlocks) the entire L2 cache.
 * IMPORTANT: Must only be run by one core at a time due to use
 * of L2C debug features.
 */
void hfa_l2c_flush(void);

/**
 * Given the chip processor ID from COP0, this function returns a
 * string representing the chip model number. The string is of the
 * form CNXXXXpX.X-FREQ-SUFFIX.
 * - XXXX = The chip model number
 * - X.X = Chip pass number
 * - FREQ = Current frequency in Mhz
 * - SUFFIX = NSP, EXP, SCP, SSP, or CP
 *
 * @param   chip_id     Chip ID
 *
 * @return Model string
 */
const char *hfa_octeon_model_get_string(uint32_t);
#endif

#ifdef	__cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif
#endif /* __CVMX_HFA_H__ */
