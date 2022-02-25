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
 * Support library for CN6XXX and CN70/71XX hardware HFA engine.
 *
 */
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
#include <linux/export.h>
#include <asm/octeon/cvmx.h>
#include <asm/octeon/cvmx-pko.h>
#include <asm/octeon/cvmx-helper.h>
#include <asm/octeon/cvmx-clock.h>
#include <asm/octeon/cvmx-dfa-defs.h>
#include <asm/octeon/cvmx-l2c.h>
#include <asm/octeon/cvmx-hfa.h>
#else
#ifndef CVMX_DONT_INCLUDE_CONFIG
#include "executive-config.h"
#include "cvmx-config.h"
#endif
#include "cvmx.h"
#include "cvmx-fau.h"
#include "cvmx-cmd-queue.h"
#include "cvmx-helper.h"
#include "cvmx-l2c.h"
#include "cvmx-hfa.h"
#ifdef CVMX_BUILD_FOR_LINUX_USER
#include <sys/sysmips.h>
#include <asm/sysmips.h>

extern int errno;
#endif
#endif
#ifdef CVMX_ENABLE_DFA_FUNCTIONS

/**
 * Initialize the DFA block
 *
 * @return Zero on success, negative on failure
 */
int cvmx_hfa_initialize(void)
{
	cvmx_dfa_difctl_t control;
	cvmx_cmd_queue_result_t result;
	void *initial_base_address;
	int cmdsize;

	cmdsize = ((CVMX_FPA_DFA_POOL_SIZE - 8) / sizeof(cvmx_hfa_command_t)) * 
        sizeof(cvmx_hfa_command_t);
	result = cvmx_cmd_queue_initialize(CVMX_CMD_QUEUE_DFA, 0, 
                                       CVMX_FPA_DFA_POOL, cmdsize + 8);
    switch(result){
        case CVMX_CMD_QUEUE_SUCCESS:
            /*Do nothing*/
        break;
        case CVMX_CMD_QUEUE_ALREADY_SETUP:
            return 0;
        break;
        default:
            return (-1);
        break;
    }

	control.u64 = 0;
	control.cn31xx.dwbcnt = CVMX_FPA_DFA_POOL_SIZE / 128;
	control.s.pool = CVMX_FPA_DFA_POOL;
	control.s.size = cmdsize / sizeof(cvmx_hfa_command_t);
	CVMX_SYNCWS;
	cvmx_write_csr(CVMX_DFA_DIFCTL, control.u64);
	initial_base_address = cvmx_cmd_queue_buffer(CVMX_CMD_QUEUE_DFA);
	CVMX_SYNCWS;
	cvmx_write_csr(CVMX_DFA_DIFRDPTR, cvmx_ptr_to_phys(initial_base_address));
	cvmx_read_csr(CVMX_DFA_DIFRDPTR);	/* Read to make sure setup is complete */
	return 0;
}
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(cvmx_hfa_initialize);
#endif

/**
 * Shutdown the DFA block. DFA must be idle when
 * this function is called.
 *
 * @return Zero on success, negative on failure
 */
int cvmx_hfa_shutdown(void)
{
	if (cvmx_cmd_queue_length(CVMX_CMD_QUEUE_DFA)) {
		cvmx_dprintf("ERROR: cvmx_hfa_shutdown: DFA not idle.\n");
		return -1;
	}
	cvmx_cmd_queue_shutdown(CVMX_CMD_QUEUE_DFA);
	return 0;
}
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(cvmx_hfa_shutdown);
#endif

/**
 * Submit a command to the DFA block
 *
 * @param command DFA command to submit
 *
 * @return Zero on success, negative on failure
 */
int cvmx_hfa_submit(cvmx_hfa_command_t * command)
{
	cvmx_cmd_queue_result_t result = cvmx_cmd_queue_write(CVMX_CMD_QUEUE_DFA, 1, 4, command->u64);
	if (result == CVMX_CMD_QUEUE_SUCCESS)
		cvmx_write_csr(CVMX_DFA_DBELL, 1);
	return result;
}
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(cvmx_hfa_submit);
#endif

void *hfa_bootmem_alloc(long unsigned int size, uint64_t alignment)
{
#ifndef CVMX_BOOTMEM_CORRUPT_CHECK
    void *addr = NULL;
    addr = cvmx_bootmem_alloc_range(size, alignment, 0, 0);
#ifdef DEBUG
    cvmx_dprintf("BOOTMEM ALLOC: ptr %p size %lu\n", addr, size); 
#endif
    return (addr);
#else 
    uint64_t alloc_size = size+(2*CHECK_SIZE);
    void *addr = NULL;
    addr = cvmx_bootmem_alloc_range(alloc_size, alignment, 0, 0);
   
    cvmx_dprintf("ALLOC: addr: %p size %lu\n", addr, size);
    if(addr){ 
        memset((uint8_t *)addr, 0xA, CHECK_SIZE);
        memset((uint8_t *)addr+size+CHECK_SIZE, 0xB, CHECK_SIZE);
        return ((uint8_t*)addr+CHECK_SIZE);
    }
    return addr;
#endif
}
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(hfa_bootmem_alloc);
#endif

int hfa_bootmem_free(void *ptr, long unsigned int size)
{
	uint64_t address;

#ifdef CVMX_BOOTMEM_CORRUPT_CHECK
    uint8_t buf1[CHECK_SIZE];
    uint8_t buf2[CHECK_SIZE];
   
    memset(buf1, 0xA, CHECK_SIZE);
    memset(buf2, 0xB, CHECK_SIZE);
 
    if(memcmp((uint8_t *)(ptr-CHECK_SIZE), buf1, CHECK_SIZE)){
        cvmx_dprintf("Buffer %p Accessed extra memory\n", 
                                    ((uint8_t *)ptr-CHECK_SIZE));
    }
    if(memcmp((uint8_t *)ptr+size, buf2, CHECK_SIZE)){
        cvmx_dprintf("Buffer(end) %p Accessed extra memory\n", 
                                    ((uint8_t *)ptr-CHECK_SIZE));
    }
    memset((uint8_t *)(ptr-CHECK_SIZE), 0x0, CHECK_SIZE);
    memset((uint8_t *)ptr+size, 0x0, CHECK_SIZE);
    
    size = (size+(2*CHECK_SIZE) + (CVMX_BOOTMEM_ALIGNMENT_SIZE -1)) & 
                   ~(CVMX_BOOTMEM_ALIGNMENT_SIZE -1);
	address = cvmx_ptr_to_phys((uint8_t *)ptr-CHECK_SIZE);
	return __cvmx_bootmem_phy_free(address, size, 0);
#else
#ifdef DEBUG
    cvmx_dprintf("\t\t\t\tBOOTMEM FREE: ptr %p size %lu\n", ptr, size); 
#endif    
    /*Round size up of mult of minimum alignment bytes*/
    size = (size + (CVMX_BOOTMEM_ALIGNMENT_SIZE -1)) & 
                   ~(CVMX_BOOTMEM_ALIGNMENT_SIZE -1);
	address = cvmx_ptr_to_phys(ptr);
	return __cvmx_bootmem_phy_free(address, size, 0);
#endif
}
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(hfa_bootmem_free);
#endif

const cvmx_bootmem_named_block_desc_t *
hfa_bootmem_find_named_block(const char *name)
{
      return cvmx_bootmem_find_named_block(name);
}
   
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(hfa_bootmem_find_named_block);
#endif

void *hfa_bootmem_alloc_named(uint64_t size, uint64_t alignment, const char *name)
{
      return cvmx_bootmem_alloc_named(size, alignment, name);
}
   
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(hfa_bootmem_alloc_named);
#endif

int hfa_bootmem_free_named(const char *name)
{
      return cvmx_bootmem_free_named(name);
}
   
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(hfa_bootmem_free_named);
#endif

void hfa_l2c_flush(void)
{
#ifdef CVMX_BUILD_FOR_LINUX_USER
    sysmips(HFA_MIPS_CAVIUM_L2C_FLUSH);
#else    
        cvmx_l2c_flush();
#endif
}
     
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(hfa_l2c_flush);
#endif

const char *hfa_octeon_model_get_string(uint32_t chip_id)
{
      return octeon_model_get_string(chip_id);
}
   
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
EXPORT_SYMBOL(hfa_octeon_model_get_string);
#endif

#endif
