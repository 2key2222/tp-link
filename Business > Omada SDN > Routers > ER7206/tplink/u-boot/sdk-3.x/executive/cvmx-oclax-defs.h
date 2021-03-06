/***********************license start***************
 * Copyright (c) 2003-2013  Cavium Inc. (support@cavium.com). All rights
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
 * cvmx-oclax-defs.h
 *
 * Configuration and status register (CSR) type definitions for
 * Octeon oclax.
 *
 * This file is auto generated. Do not edit.
 *
 * <hr>$Revision$<hr>
 *
 */
#ifndef __CVMX_OCLAX_DEFS_H__
#define __CVMX_OCLAX_DEFS_H__

#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_BIST_RESULT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_BIST_RESULT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000040ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_BIST_RESULT(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000040ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_CDHX_CTL(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 1)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 1)) && ((block_id <= 4))))))
		cvmx_warn("CVMX_OCLAX_CDHX_CTL(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000600ull) + (((offset) & 1) + ((block_id) & 7) * 0x200000ull) * 8;
}
#else
#define CVMX_OCLAX_CDHX_CTL(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800A8000600ull) + (((offset) & 1) + ((block_id) & 7) * 0x200000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_CONST(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_CONST(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000000ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_CONST(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000000ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_DATX(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 8191)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 8191)) && ((block_id <= 4))))))
		cvmx_warn("CVMX_OCLAX_DATX(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8400000ull) + (((offset) & 8191) + ((block_id) & 7) * 0x200000ull) * 8;
}
#else
#define CVMX_OCLAX_DATX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800A8400000ull) + (((offset) & 8191) + ((block_id) & 7) * 0x200000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_DAT_POP(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_DAT_POP(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000800ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_DAT_POP(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000800ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_FIFO_DEPTH(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_FIFO_DEPTH(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000200ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_FIFO_DEPTH(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000200ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_FIFO_LIMIT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_FIFO_LIMIT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000240ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_FIFO_LIMIT(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000240ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_FIFO_TAIL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_FIFO_TAIL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000260ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_FIFO_TAIL(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000260ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_FIFO_TRIG(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_FIFO_TRIG(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A80002A0ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_FIFO_TRIG(block_id) (CVMX_ADD_IO_SEG(0x00011800A80002A0ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_FIFO_WRAP(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_FIFO_WRAP(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000280ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_FIFO_WRAP(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000280ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_FSMX_ANDX_IX(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((a == 0)) && ((b <= 1)) && ((c <= 15)) && ((d <= 1)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((a <= 4)) && ((b <= 1)) && ((c <= 15)) && ((d <= 1))))))
		cvmx_warn("CVMX_OCLAX_FSMX_ANDX_IX(%lu,%lu,%lu,%lu) is invalid on this chip\n", a, b, c, d);
	return CVMX_ADD_IO_SEG(0x00011800A8300000ull) + ((a) << 24) + ((b) << 12) + ((c) << 4) + ((d) << 3);
}
#else
#define CVMX_OCLAX_FSMX_ANDX_IX(a, b, c, d) (CVMX_ADD_IO_SEG(0x00011800A8300000ull) + ((a) << 24) + ((b) << 12) + ((c) << 4) + ((d) << 3))
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_FSMX_ORX(unsigned long a, unsigned long b, unsigned long c)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((a == 0)) && ((b <= 1)) && ((c <= 15)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((a <= 4)) && ((b <= 1)) && ((c <= 15))))))
		cvmx_warn("CVMX_OCLAX_FSMX_ORX(%lu,%lu,%lu) is invalid on this chip\n", a, b, c);
	return CVMX_ADD_IO_SEG(0x00011800A8310000ull) + ((a) << 24) + ((b) << 12) + ((c) << 3);
}
#else
#define CVMX_OCLAX_FSMX_ORX(a, b, c) (CVMX_ADD_IO_SEG(0x00011800A8310000ull) + ((a) << 24) + ((b) << 12) + ((c) << 3))
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_FSMX_STATEX(unsigned long a, unsigned long b, unsigned long c)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((a == 0)) && ((b <= 1)) && ((c <= 15)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((a <= 4)) && ((b <= 1)) && ((c <= 15))))))
		cvmx_warn("CVMX_OCLAX_FSMX_STATEX(%lu,%lu,%lu) is invalid on this chip\n", a, b, c);
	return CVMX_ADD_IO_SEG(0x00011800A8320000ull) + ((a) << 24) + ((b) << 12) + ((c) << 3);
}
#else
#define CVMX_OCLAX_FSMX_STATEX(a, b, c) (CVMX_ADD_IO_SEG(0x00011800A8320000ull) + ((a) << 24) + ((b) << 12) + ((c) << 3))
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_GEN_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_GEN_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000060ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_GEN_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000060ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_MATX_COUNT(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 3)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 3)) && ((block_id <= 4))))))
		cvmx_warn("CVMX_OCLAX_MATX_COUNT(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8230000ull) + (((offset) & 3) + ((block_id) & 7) * 0x1000ull) * 4096;
}
#else
#define CVMX_OCLAX_MATX_COUNT(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800A8230000ull) + (((offset) & 3) + ((block_id) & 7) * 0x1000ull) * 4096)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_MATX_CTL(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 3)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 3)) && ((block_id <= 4))))))
		cvmx_warn("CVMX_OCLAX_MATX_CTL(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8200000ull) + (((offset) & 3) + ((block_id) & 7) * 0x1000ull) * 4096;
}
#else
#define CVMX_OCLAX_MATX_CTL(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800A8200000ull) + (((offset) & 3) + ((block_id) & 7) * 0x1000ull) * 4096)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_MATX_MASKX(unsigned long a, unsigned long b, unsigned long c)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((a == 0)) && ((b <= 3)) && ((c <= 1)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((a <= 4)) && ((b <= 3)) && ((c <= 1))))))
		cvmx_warn("CVMX_OCLAX_MATX_MASKX(%lu,%lu,%lu) is invalid on this chip\n", a, b, c);
	return CVMX_ADD_IO_SEG(0x00011800A8220000ull) + ((a) << 24) + ((b) << 12) + ((c) << 3);
}
#else
#define CVMX_OCLAX_MATX_MASKX(a, b, c) (CVMX_ADD_IO_SEG(0x00011800A8220000ull) + ((a) << 24) + ((b) << 12) + ((c) << 3))
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_MATX_THRESH(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 3)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 3)) && ((block_id <= 4))))))
		cvmx_warn("CVMX_OCLAX_MATX_THRESH(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8240000ull) + (((offset) & 3) + ((block_id) & 7) * 0x1000ull) * 4096;
}
#else
#define CVMX_OCLAX_MATX_THRESH(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800A8240000ull) + (((offset) & 3) + ((block_id) & 7) * 0x1000ull) * 4096)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_MATX_VALUEX(unsigned long a, unsigned long b, unsigned long c)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((a == 0)) && ((b <= 3)) && ((c <= 1)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((a <= 4)) && ((b <= 3)) && ((c <= 1))))))
		cvmx_warn("CVMX_OCLAX_MATX_VALUEX(%lu,%lu,%lu) is invalid on this chip\n", a, b, c);
	return CVMX_ADD_IO_SEG(0x00011800A8210000ull) + ((a) << 24) + ((b) << 12) + ((c) << 3);
}
#else
#define CVMX_OCLAX_MATX_VALUEX(a, b, c) (CVMX_ADD_IO_SEG(0x00011800A8210000ull) + ((a) << 24) + ((b) << 12) + ((c) << 3))
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_RAWX(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 1)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 1)) && ((block_id <= 4))))))
		cvmx_warn("CVMX_OCLAX_RAWX(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000100ull) + (((offset) & 1) + ((block_id) & 7) * 0x200000ull) * 8;
}
#else
#define CVMX_OCLAX_RAWX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800A8000100ull) + (((offset) & 1) + ((block_id) & 7) * 0x200000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_SFT_RST(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_SFT_RST(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000020ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_SFT_RST(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000020ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_STACK_BASE(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_STACK_BASE(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000400ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_STACK_BASE(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000400ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_STACK_CUR(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_STACK_CUR(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000480ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_STACK_CUR(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000480ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_STACK_STORE_CNT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_STACK_STORE_CNT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000460ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_STACK_STORE_CNT(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000460ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_STACK_TOP(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_STACK_TOP(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000420ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_STACK_TOP(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000420ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_STACK_WRAP(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_STACK_WRAP(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000440ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_STACK_WRAP(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000440ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_STAGEX(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 71)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 71)) && ((block_id <= 4))))))
		cvmx_warn("CVMX_OCLAX_STAGEX(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8100000ull) + (((offset) & 127) + ((block_id) & 7) * 0x200000ull) * 8;
}
#else
#define CVMX_OCLAX_STAGEX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800A8100000ull) + (((offset) & 127) + ((block_id) & 7) * 0x200000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_STATE_INT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_STATE_INT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A8000080ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_STATE_INT(block_id) (CVMX_ADD_IO_SEG(0x00011800A8000080ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_STATE_SET(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_STATE_SET(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A80000A0ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_STATE_SET(block_id) (CVMX_ADD_IO_SEG(0x00011800A80000A0ull) + ((block_id) & 7) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_OCLAX_TIME(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 4)))))
		cvmx_warn("CVMX_OCLAX_TIME(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800A80000C0ull) + ((block_id) & 7) * 0x1000000ull;
}
#else
#define CVMX_OCLAX_TIME(block_id) (CVMX_ADD_IO_SEG(0x00011800A80000C0ull) + ((block_id) & 7) * 0x1000000ull)
#endif

/**
 * cvmx_ocla#_bist_result
 *
 * This register provides access to the internal BIST results. Each bit is the BIST result of an
 * individual memory (per bit, 0 = pass and 1 = fail).
 */
union cvmx_oclax_bist_result {
	uint64_t u64;
	struct cvmx_oclax_bist_result_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_1_63                : 63;
	uint64_t dat                          : 1;  /**< BIST result of the DAT memory. */
#else
	uint64_t dat                          : 1;
	uint64_t reserved_1_63                : 63;
#endif
	} s;
	struct cvmx_oclax_bist_result_s       cn70xx;
	struct cvmx_oclax_bist_result_s       cn78xx;
};
typedef union cvmx_oclax_bist_result cvmx_oclax_bist_result_t;

/**
 * cvmx_ocla#_cdh#_ctl
 */
union cvmx_oclax_cdhx_ctl {
	uint64_t u64;
	struct cvmx_oclax_cdhx_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_6_63                : 58;
	uint64_t dup                          : 1;  /**< Retain duplicates in the data stream. */
	uint64_t dis_stamp                    : 1;  /**< Remove time stamps from data stream. */
	uint64_t cap_ctl                      : 4;  /**< Minterms that will cause data to be captured. These minterms are the four inputs to a 4-1
                                                         mux selected by PLA1 and 0. The output is thus calulated from the equation:
                                                         fsmcap0 = OCLA(0..4)_FSM(0)_STATE[state0][CAP]
                                                         fsmcap1 = OCLA(0..4)_FSM(1)_STATE[state1][CAP]
                                                         out = (    (<3> & fsmcap0 & fsmcap0)
                                                         || (<2> & fsmcap1 & !fsmcap0)
                                                         || (<1> & !fsmcap1 & fsmcap0)
                                                         || (<0> & !fsmcap1 & !fsmcap0))
                                                         Common examples:
                                                         0x0 = No capture
                                                         0x2 = Capture when fsmcap0 requests capture
                                                         0x4 = Capture when fsmcap1 requests capture
                                                         0x6 = Capture on fsmcap0 | fsmcap1
                                                         0x8 = Capture on fsmcap0 & fsmcap1
                                                         0xF = Always capture. */
#else
	uint64_t cap_ctl                      : 4;
	uint64_t dis_stamp                    : 1;
	uint64_t dup                          : 1;
	uint64_t reserved_6_63                : 58;
#endif
	} s;
	struct cvmx_oclax_cdhx_ctl_s          cn70xx;
	struct cvmx_oclax_cdhx_ctl_s          cn78xx;
};
typedef union cvmx_oclax_cdhx_ctl cvmx_oclax_cdhx_ctl_t;

/**
 * cvmx_ocla#_const
 */
union cvmx_oclax_const {
	uint64_t u64;
	struct cvmx_oclax_const_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_16_63               : 48;
	uint64_t dat_size                     : 16; /**< Size of data RAM in units of 36-bit entries. This value is subject to change between chip
                                                         passes, and software should thus use this value rather than a hard coded constant.
                                                         OCLA(0..3) size is 4096, OCLA(4) size is 8192. */
#else
	uint64_t dat_size                     : 16;
	uint64_t reserved_16_63               : 48;
#endif
	} s;
	struct cvmx_oclax_const_s             cn70xx;
	struct cvmx_oclax_const_s             cn78xx;
};
typedef union cvmx_oclax_const cvmx_oclax_const_t;

/**
 * cvmx_ocla#_dat#
 */
union cvmx_oclax_datx {
	uint64_t u64;
	struct cvmx_oclax_datx_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_38_63               : 26;
	uint64_t entry                        : 38; /**< Captured entry. Data is in the format described by OCLA_CAP_DAT_S or OCLA_CAP_CTL_S. */
#else
	uint64_t entry                        : 38;
	uint64_t reserved_38_63               : 26;
#endif
	} s;
	struct cvmx_oclax_datx_s              cn70xx;
	struct cvmx_oclax_datx_s              cn78xx;
};
typedef union cvmx_oclax_datx cvmx_oclax_datx_t;

/**
 * cvmx_ocla#_dat_pop
 */
union cvmx_oclax_dat_pop {
	uint64_t u64;
	struct cvmx_oclax_dat_pop_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t valid                        : 1;  /**< Valid entry. Indicates the FIFO contains data, and equivalent to OCLA(0..4)_FIFO_DEPTH[DEPTH] != 0. */
	uint64_t trig                         : 1;  /**< Internal trigger set. Equivalent to OCLA(0..4)_STATE_INT[TRIG]. */
	uint64_t wmark                        : 1;  /**< Internal buffer watermark reached. Equivalent to OCLA(0..4)_STATE_INT[WMARK]. */
	uint64_t reserved_38_60               : 23;
	uint64_t entry                        : 38; /**< Captured entry. If VALID is set, has read side effect of unloading data by decrementing
                                                         OCLA(0..4)_FIFO_DEPTH[DEPTH]. Data is in the format described by OCLA_CAP_DAT_S or
                                                         OCLA_CAP_CTL_S.
                                                         Note that unloading data will cause that data not to be sent to memory, therefore
                                                         OCLA(0..4)_DAT_POP should not be read when OCLA(0..4)_FIFO_LIMIT[DDR] != all-ones. */
#else
	uint64_t entry                        : 38;
	uint64_t reserved_38_60               : 23;
	uint64_t wmark                        : 1;
	uint64_t trig                         : 1;
	uint64_t valid                        : 1;
#endif
	} s;
	struct cvmx_oclax_dat_pop_s           cn70xx;
	struct cvmx_oclax_dat_pop_s           cn78xx;
};
typedef union cvmx_oclax_dat_pop cvmx_oclax_dat_pop_t;

/**
 * cvmx_ocla#_fifo_depth
 */
union cvmx_oclax_fifo_depth {
	uint64_t u64;
	struct cvmx_oclax_fifo_depth_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_16_63               : 48;
	uint64_t depth                        : 16; /**< Current capture FIFO depth in 36-bit words. */
#else
	uint64_t depth                        : 16;
	uint64_t reserved_16_63               : 48;
#endif
	} s;
	struct cvmx_oclax_fifo_depth_s        cn70xx;
	struct cvmx_oclax_fifo_depth_s        cn78xx;
};
typedef union cvmx_oclax_fifo_depth cvmx_oclax_fifo_depth_t;

/**
 * cvmx_ocla#_fifo_limit
 */
union cvmx_oclax_fifo_limit {
	uint64_t u64;
	struct cvmx_oclax_fifo_limit_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t overfull                     : 16; /**< Stop level. When OCLA(0..4)_FIFO_DEPTH > OVERFULL, stop capturing and set
                                                         OCLA(0..4)_STATE_INT[OVERFULL]. This should be set to no more than
                                                         OCLA(0..4)_CONST[DAT_SIZE] minus 26 when using DDR capture to insure that overflow can be
                                                         detected. */
	uint64_t ddr                          : 16; /**< DDR level. When OCLA(0..4)_FIFO_DEPTH > DDR, FIFO entries will be removed, packed into a
                                                         cache line, and overflowed to DDR/L2. All-ones disables overflow to DDR/L2. If non-zero
                                                         must be at least 28. */
	uint64_t bp                           : 16; /**< Backpressure level. When OCLA(0..4)_FIFO_DEPTH > BP, OCLA will signal backpressure to
                                                         coprocessors. All-ones disables indicating backpressure. */
	uint64_t wmark                        : 16; /**< Interrupt watermark level. When OCLA(0..4)_FIFO_DEPTH > WMARK OCLA will set
                                                         OCLA(0..4)_STATE_INT[WMARK] interrupt. All-ones disables setting the interrupt. */
#else
	uint64_t wmark                        : 16;
	uint64_t bp                           : 16;
	uint64_t ddr                          : 16;
	uint64_t overfull                     : 16;
#endif
	} s;
	struct cvmx_oclax_fifo_limit_s        cn70xx;
	struct cvmx_oclax_fifo_limit_s        cn78xx;
};
typedef union cvmx_oclax_fifo_limit cvmx_oclax_fifo_limit_t;

/**
 * cvmx_ocla#_fifo_tail
 */
union cvmx_oclax_fifo_tail {
	uint64_t u64;
	struct cvmx_oclax_fifo_tail_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_16_63               : 48;
	uint64_t tail                         : 16; /**< Address last written into entry FIFO. */
#else
	uint64_t tail                         : 16;
	uint64_t reserved_16_63               : 48;
#endif
	} s;
	struct cvmx_oclax_fifo_tail_s         cn70xx;
	struct cvmx_oclax_fifo_tail_s         cn78xx;
};
typedef union cvmx_oclax_fifo_tail cvmx_oclax_fifo_tail_t;

/**
 * cvmx_ocla#_fifo_trig
 */
union cvmx_oclax_fifo_trig {
	uint64_t u64;
	struct cvmx_oclax_fifo_trig_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t limit                        : 16; /**< Post-trigger number of entries to collect before stopping collection. If zero, collection
                                                         will never stop, which may be desirable when overflowing to DDR/L2. Must be <
                                                         OCLA(0..4)_CONST[DAT_SIZE] - 5. */
	uint64_t cnt                          : 16; /**< Number of entries collected since trigger. Cleared when OCLA(0..4)_STATE_INT[TRIG] clear. */
#else
	uint64_t cnt                          : 16;
	uint64_t limit                        : 16;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_oclax_fifo_trig_s         cn70xx;
	struct cvmx_oclax_fifo_trig_s         cn78xx;
};
typedef union cvmx_oclax_fifo_trig cvmx_oclax_fifo_trig_t;

/**
 * cvmx_ocla#_fifo_wrap
 */
union cvmx_oclax_fifo_wrap {
	uint64_t u64;
	struct cvmx_oclax_fifo_wrap_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t wraps                        : 32; /**< Number of times FIFO has wrapped since trigger. Cleared when OCLA(0..4)_STATE_INT[TRIG] clear. */
#else
	uint64_t wraps                        : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_oclax_fifo_wrap_s         cn70xx;
	struct cvmx_oclax_fifo_wrap_s         cn78xx;
};
typedef union cvmx_oclax_fifo_wrap cvmx_oclax_fifo_wrap_t;

/**
 * cvmx_ocla#_fsm#_and#_i#
 *
 * Values for PLA-AND plane. AND(0..15) represents the 15 allowed AND terms. I(0..1) for I=0
 * indicates the term non-inverted, for I=1 indicates the term inverted. Any AND tree may be
 * disabled by setting the same bit in both _I(0) and _I(1), as '((1) & !(1))' is always false.
 */
union cvmx_oclax_fsmx_andx_ix {
	uint64_t u64;
	struct cvmx_oclax_fsmx_andx_ix_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_15_63               : 49;
	uint64_t mcd                          : 3;  /**< Multichip Debug (MCD) 0..2 inputs. */
	uint64_t match                        : 4;  /**< Matcher 0..3 input. */
	uint64_t fsm1_state                   : 4;  /**< FSM 1 last state. */
	uint64_t fsm0_state                   : 4;  /**< FSM 0 last state. */
#else
	uint64_t fsm0_state                   : 4;
	uint64_t fsm1_state                   : 4;
	uint64_t match                        : 4;
	uint64_t mcd                          : 3;
	uint64_t reserved_15_63               : 49;
#endif
	} s;
	struct cvmx_oclax_fsmx_andx_ix_s      cn70xx;
	struct cvmx_oclax_fsmx_andx_ix_s      cn78xx;
};
typedef union cvmx_oclax_fsmx_andx_ix cvmx_oclax_fsmx_andx_ix_t;

/**
 * cvmx_ocla#_fsm#_or#
 */
union cvmx_oclax_fsmx_orx {
	uint64_t u64;
	struct cvmx_oclax_fsmx_orx_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_4_63                : 60;
	uint64_t or_state                     : 4;  /**< Column to drive on PLA OR-plane. */
#else
	uint64_t or_state                     : 4;
	uint64_t reserved_4_63                : 60;
#endif
	} s;
	struct cvmx_oclax_fsmx_orx_s          cn70xx;
	struct cvmx_oclax_fsmx_orx_s          cn78xx;
};
typedef union cvmx_oclax_fsmx_orx cvmx_oclax_fsmx_orx_t;

/**
 * cvmx_ocla#_fsm#_state#
 *
 * See State Outputs for more details on each of these actions.
 *
 */
union cvmx_oclax_fsmx_statex {
	uint64_t u64;
	struct cvmx_oclax_fsmx_statex_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_30_63               : 34;
	uint64_t set_int                      : 1;  /**< In this state set interrupt. */
	uint64_t cap                          : 1;  /**< In this state request capture this cycle. */
	uint64_t set_mcd                      : 3;  /**< In this state set MCD. */
	uint64_t set_trig                     : 1;  /**< In this state set internal trigger indication. */
	uint64_t reserved_20_23               : 4;
	uint64_t set_val                      : 4;  /**< In this state store match value into matcher 0..3. */
	uint64_t reserved_12_15               : 4;
	uint64_t clr_cnt                      : 4;  /**< In this state clear match counter. */
	uint64_t reserved_4_7                 : 4;
	uint64_t inc_cnt                      : 4;  /**< In this state increment match counter. See State Outputs for more information on this or
                                                         any of the bits above. */
#else
	uint64_t inc_cnt                      : 4;
	uint64_t reserved_4_7                 : 4;
	uint64_t clr_cnt                      : 4;
	uint64_t reserved_12_15               : 4;
	uint64_t set_val                      : 4;
	uint64_t reserved_20_23               : 4;
	uint64_t set_trig                     : 1;
	uint64_t set_mcd                      : 3;
	uint64_t cap                          : 1;
	uint64_t set_int                      : 1;
	uint64_t reserved_30_63               : 34;
#endif
	} s;
	struct cvmx_oclax_fsmx_statex_s       cn70xx;
	struct cvmx_oclax_fsmx_statex_s       cn78xx;
};
typedef union cvmx_oclax_fsmx_statex cvmx_oclax_fsmx_statex_t;

/**
 * cvmx_ocla#_gen_ctl
 */
union cvmx_oclax_gen_ctl {
	uint64_t u64;
	struct cvmx_oclax_gen_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_4_63                : 60;
	uint64_t exten                        : 1;  /**< Enable external triggering.
                                                         0 = External triggering ignored.
                                                         1 = When the external trigger pin selected with GPIO_OCLA_EXTEN_TRIG is high it will cause
                                                         triggerring and set OCLA(0..4)_STATE_SET[TRIG]. The external device must de-assert the
                                                         signal to release the trigger (it is not edge sensitive.) */
	uint64_t den                          : 1;  /**< Enable data bus and counter clocking. When set, the OCLA inbound data bus may be used and
                                                         counters may increment. When clear, the bus is always zero and internal flops may be clock
                                                         gated off to save power. Must be set for normal operation. */
	uint64_t stt                          : 1;  /**< Store to DDR directly, bypassing L2 cache. */
	uint64_t reserved_0_0                 : 1;
#else
	uint64_t reserved_0_0                 : 1;
	uint64_t stt                          : 1;
	uint64_t den                          : 1;
	uint64_t exten                        : 1;
	uint64_t reserved_4_63                : 60;
#endif
	} s;
	struct cvmx_oclax_gen_ctl_s           cn70xx;
	struct cvmx_oclax_gen_ctl_s           cn78xx;
};
typedef union cvmx_oclax_gen_ctl cvmx_oclax_gen_ctl_t;

/**
 * cvmx_ocla#_mat#_count
 */
union cvmx_oclax_matx_count {
	uint64_t u64;
	struct cvmx_oclax_matx_count_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t count                        : 32; /**< Current counter value. Note software must reset this to zero (or the appropriate count)
                                                         before starting capture. */
#else
	uint64_t count                        : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_oclax_matx_count_s        cn70xx;
	struct cvmx_oclax_matx_count_s        cn78xx;
};
typedef union cvmx_oclax_matx_count cvmx_oclax_matx_count_t;

/**
 * cvmx_ocla#_mat#_ctl
 */
union cvmx_oclax_matx_ctl {
	uint64_t u64;
	struct cvmx_oclax_matx_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_8_63                : 56;
	uint64_t fsm_ctr                      : 1;  /**< What output matcher provides to FSM:
                                                         0 = FSM receives raw match signal, asserting only in those cycles with matches.
                                                         1 = FSM receives OCLA(0..4)_MAT(0..3)_COUNT >= OCLA(0..4)_MAT(0..3)_THRESH. */
	uint64_t inc_match                    : 1;  /**< Increment OCLA(0..4)_MAT(0..3)_COUNT counter automatically on each match. */
	uint64_t shift                        : 6;  /**< Right rotation amount to apply to data loaded into OCLA(0..4)_MAT(0..3)_VALUE(0..1)
                                                         register when FSM requests a value load. */
#else
	uint64_t shift                        : 6;
	uint64_t inc_match                    : 1;
	uint64_t fsm_ctr                      : 1;
	uint64_t reserved_8_63                : 56;
#endif
	} s;
	struct cvmx_oclax_matx_ctl_s          cn70xx;
	struct cvmx_oclax_matx_ctl_s          cn78xx;
};
typedef union cvmx_oclax_matx_ctl cvmx_oclax_matx_ctl_t;

/**
 * cvmx_ocla#_mat#_mask#
 */
union cvmx_oclax_matx_maskx {
	uint64_t u64;
	struct cvmx_oclax_matx_maskx_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_36_63               : 28;
	uint64_t mask                         : 36; /**< Bitmask of which bits in OCLA(0..4)_MAT(0..3)_VALUE(0..1) are to be compared.
                                                         0 = Do not compare bit.
                                                         1 = Compare bit. */
#else
	uint64_t mask                         : 36;
	uint64_t reserved_36_63               : 28;
#endif
	} s;
	struct cvmx_oclax_matx_maskx_s        cn70xx;
	struct cvmx_oclax_matx_maskx_s        cn78xx;
};
typedef union cvmx_oclax_matx_maskx cvmx_oclax_matx_maskx_t;

/**
 * cvmx_ocla#_mat#_thresh
 */
union cvmx_oclax_matx_thresh {
	uint64_t u64;
	struct cvmx_oclax_matx_thresh_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t thresh                       : 32; /**< Counter threshold value. Compared against OCLA(0..4)_MAT(0..3)_COUNT to assert matcher
                                                         output, and set OCLA(0..4)_STATE_INT[OVFL]. */
#else
	uint64_t thresh                       : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_oclax_matx_thresh_s       cn70xx;
	struct cvmx_oclax_matx_thresh_s       cn78xx;
};
typedef union cvmx_oclax_matx_thresh cvmx_oclax_matx_thresh_t;

/**
 * cvmx_ocla#_mat#_value#
 */
union cvmx_oclax_matx_valuex {
	uint64_t u64;
	struct cvmx_oclax_matx_valuex_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_36_63               : 28;
	uint64_t mask                         : 36; /**< Data value to compare against when corresponding bits of OCLA(0..4)_MAT(0..3)_MASK(0..1) are set. */
#else
	uint64_t mask                         : 36;
	uint64_t reserved_36_63               : 28;
#endif
	} s;
	struct cvmx_oclax_matx_valuex_s       cn70xx;
	struct cvmx_oclax_matx_valuex_s       cn78xx;
};
typedef union cvmx_oclax_matx_valuex cvmx_oclax_matx_valuex_t;

/**
 * cvmx_ocla#_raw#
 */
union cvmx_oclax_rawx {
	uint64_t u64;
	struct cvmx_oclax_rawx_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_36_63               : 28;
	uint64_t raw                          : 36; /**< Raw value of debug bus input signals into OCLA. */
#else
	uint64_t raw                          : 36;
	uint64_t reserved_36_63               : 28;
#endif
	} s;
	struct cvmx_oclax_rawx_s              cn70xx;
	struct cvmx_oclax_rawx_s              cn78xx;
};
typedef union cvmx_oclax_rawx cvmx_oclax_rawx_t;

/**
 * cvmx_ocla#_sft_rst
 */
union cvmx_oclax_sft_rst {
	uint64_t u64;
	struct cvmx_oclax_sft_rst_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_1_63                : 63;
	uint64_t reset                        : 1;  /**< Reset. When set, causes a block reset, except RSL. */
#else
	uint64_t reset                        : 1;
	uint64_t reserved_1_63                : 63;
#endif
	} s;
	struct cvmx_oclax_sft_rst_s           cn70xx;
	struct cvmx_oclax_sft_rst_s           cn78xx;
};
typedef union cvmx_oclax_sft_rst cvmx_oclax_sft_rst_t;

/**
 * cvmx_ocla#_stack_base
 */
union cvmx_oclax_stack_base {
	uint64_t u64;
	struct cvmx_oclax_stack_base_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_42_63               : 22;
	uint64_t ptr                          : 35; /**< Memory address for base of overflow stack. This address must be on the local node in a OCI system. */
	uint64_t reserved_0_6                 : 7;
#else
	uint64_t reserved_0_6                 : 7;
	uint64_t ptr                          : 35;
	uint64_t reserved_42_63               : 22;
#endif
	} s;
	struct cvmx_oclax_stack_base_s        cn70xx;
	struct cvmx_oclax_stack_base_s        cn78xx;
};
typedef union cvmx_oclax_stack_base cvmx_oclax_stack_base_t;

/**
 * cvmx_ocla#_stack_cur
 */
union cvmx_oclax_stack_cur {
	uint64_t u64;
	struct cvmx_oclax_stack_cur_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_42_63               : 22;
	uint64_t ptr                          : 35; /**< Next address to write for overflow stack. This address must be on the local node in a OCI
                                                         system. During initialization this must be between OCLA(0..4)_STACK_BASE and
                                                         OCLA(0..4)_STACK_TOP. */
	uint64_t reserved_0_6                 : 7;
#else
	uint64_t reserved_0_6                 : 7;
	uint64_t ptr                          : 35;
	uint64_t reserved_42_63               : 22;
#endif
	} s;
	struct cvmx_oclax_stack_cur_s         cn70xx;
	struct cvmx_oclax_stack_cur_s         cn78xx;
};
typedef union cvmx_oclax_stack_cur cvmx_oclax_stack_cur_t;

/**
 * cvmx_ocla#_stack_store_cnt
 */
union cvmx_oclax_stack_store_cnt {
	uint64_t u64;
	struct cvmx_oclax_stack_store_cnt_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t stores                       : 32; /**< Number of cache line stores sent to memory subsystem. Not cleared by hardware. */
#else
	uint64_t stores                       : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_oclax_stack_store_cnt_s   cn70xx;
	struct cvmx_oclax_stack_store_cnt_s   cn78xx;
};
typedef union cvmx_oclax_stack_store_cnt cvmx_oclax_stack_store_cnt_t;

/**
 * cvmx_ocla#_stack_top
 */
union cvmx_oclax_stack_top {
	uint64_t u64;
	struct cvmx_oclax_stack_top_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_42_63               : 22;
	uint64_t ptr                          : 35; /**< Memory address for top of overflow stack plus one. This address must be on the local node
                                                         in a OCI system. */
	uint64_t reserved_0_6                 : 7;
#else
	uint64_t reserved_0_6                 : 7;
	uint64_t ptr                          : 35;
	uint64_t reserved_42_63               : 22;
#endif
	} s;
	struct cvmx_oclax_stack_top_s         cn70xx;
	struct cvmx_oclax_stack_top_s         cn78xx;
};
typedef union cvmx_oclax_stack_top cvmx_oclax_stack_top_t;

/**
 * cvmx_ocla#_stack_wrap
 */
union cvmx_oclax_stack_wrap {
	uint64_t u64;
	struct cvmx_oclax_stack_wrap_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t wraps                        : 32; /**< Number of times stack has been reset to OCLA(0..4)_STACK_BASE since trigger. Cleared when
                                                         OCLA(0..4)_STATE_INT[TRIG] clear. */
#else
	uint64_t wraps                        : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_oclax_stack_wrap_s        cn70xx;
	struct cvmx_oclax_stack_wrap_s        cn78xx;
};
typedef union cvmx_oclax_stack_wrap cvmx_oclax_stack_wrap_t;

/**
 * cvmx_ocla#_stage#
 */
union cvmx_oclax_stagex {
	uint64_t u64;
	struct cvmx_oclax_stagex_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_3_63                : 61;
	uint64_t dly                          : 3;  /**< Cycles of delay staging to apply to corresponding input bit. */
#else
	uint64_t dly                          : 3;
	uint64_t reserved_3_63                : 61;
#endif
	} s;
	struct cvmx_oclax_stagex_s            cn70xx;
	struct cvmx_oclax_stagex_s            cn78xx;
};
typedef union cvmx_oclax_stagex cvmx_oclax_stagex_t;

/**
 * cvmx_ocla#_state_int
 */
union cvmx_oclax_state_int {
	uint64_t u64;
	struct cvmx_oclax_state_int_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t fsm1_state                   : 4;  /**< FSM1 current state. */
	uint64_t fsm0_state                   : 4;  /**< FSM0 current state. */
	uint64_t reserved_36_55               : 20;
	uint64_t fsm1_rst                     : 1;  /**< FSM1 hold in state zero. Writing one to OCLA(0..4)_STATE_SET[FSM1_RST] sets this bit and
                                                         holds FSM1 in state zero, writing one to OCLA(0..4)_STATE_INT[FSM1_RST] removes the hold. */
	uint64_t fsm0_rst                     : 1;  /**< FSM0 hold in state zero. Writing one to OCLA(0..4)_STATE_SET[FSM0_RST] sets this bit and
                                                         holds FSM0 in state zero, writing one to OCLA(0..4)_STATE_INT[FSM0_RST] removes the hold. */
	uint64_t fsm1_ena                     : 1;  /**< FSM1 sequencing enabled. */
	uint64_t fsm0_ena                     : 1;  /**< FSM0 sequencing enabled. */
	uint64_t reserved_19_31               : 13;
	uint64_t ddrfull                      : 1;  /**< DDR buffer wrapped. Asserted when OCLA(0..4)_STACK_CUR has wrapped and been re-initialized
                                                         to OCLA(0..4)_STACK_BASE. */
	uint64_t wmark                        : 1;  /**< Internal buffer watermark reached. Asserted when OCLA(0..4)_FIFO_DEPTH >
                                                         OCLA(0..4)_FIFO_LIMIT[WMARK]. */
	uint64_t overfull                     : 1;  /**< Capture ended due to FIFO overflow. Asserted when OCLA(0..4)_FIFO_DEPTH >
                                                         OCLA(0..4)_FIFO_LIMIT[OVERFULL]. */
	uint64_t trigfull                     : 1;  /**< Capture ended due to buffer full. Asserted when OCLA(0..4)_FIFO_TRIG[LIMIT] >=
                                                         OCLA(0..4)_FIFO_TRIG[COUNT]. */
	uint64_t captured                     : 1;  /**< Capture started. Asserted when the first capture is made. Informational only; often masked. */
	uint64_t fsm1_int                     : 1;  /**< FSM1 interrupt requested. */
	uint64_t fsm0_int                     : 1;  /**< FSM0 interrupt requested. */
	uint64_t mcd                          : 3;  /**< Multichip Debug (MCD0..2) set. Asserted on MCD received from another coprocessor or code,
                                                         or FSM MCD request or W1S to OCLA(0..4)_STATE_SET[MCD]. */
	uint64_t trig                         : 1;  /**< Internal trigger set. Asserted on FSM internal trigger request or W1S to OCLA(0..4)_STATE_SET[TRIG] */
	uint64_t reserved_4_7                 : 4;
	uint64_t ovfl                         : 4;  /**< Match counter has overflowed. Asserted when OCLA(0..4)_MAT(0..3)_COUNT >=
                                                         OCLA(0..4)_MAT(0..3)_THRESH. Informational only; often masked. Writing 1 clears the
                                                         counter, not just the interrupt. */
#else
	uint64_t ovfl                         : 4;
	uint64_t reserved_4_7                 : 4;
	uint64_t trig                         : 1;
	uint64_t mcd                          : 3;
	uint64_t fsm0_int                     : 1;
	uint64_t fsm1_int                     : 1;
	uint64_t captured                     : 1;
	uint64_t trigfull                     : 1;
	uint64_t overfull                     : 1;
	uint64_t wmark                        : 1;
	uint64_t ddrfull                      : 1;
	uint64_t reserved_19_31               : 13;
	uint64_t fsm0_ena                     : 1;
	uint64_t fsm1_ena                     : 1;
	uint64_t fsm0_rst                     : 1;
	uint64_t fsm1_rst                     : 1;
	uint64_t reserved_36_55               : 20;
	uint64_t fsm0_state                   : 4;
	uint64_t fsm1_state                   : 4;
#endif
	} s;
	struct cvmx_oclax_state_int_s         cn70xx;
	struct cvmx_oclax_state_int_s         cn78xx;
};
typedef union cvmx_oclax_state_int cvmx_oclax_state_int_t;

/**
 * cvmx_ocla#_state_set
 *
 * This register reads identically to OCLA(0..4)_STATE_INT, but allows R/W1S instead of R/W1C access.
 *
 */
union cvmx_oclax_state_set {
	uint64_t u64;
	struct cvmx_oclax_state_set_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t fsm1_state                   : 4;  /**< See OCLA(0..4)_STATE_INT[FSM1_STATE]. */
	uint64_t fsm0_state                   : 4;  /**< See OCLA(0..4)_STATE_INT[FSM0_STATE]. */
	uint64_t reserved_36_55               : 20;
	uint64_t fsm1_rst                     : 1;  /**< See OCLA(0..4)_STATE_INT[FSM1_RST]. */
	uint64_t fsm0_rst                     : 1;  /**< See OCLA(0..4)_STATE_INT[FSM0_RST]. */
	uint64_t fsm1_ena                     : 1;  /**< See OCLA(0..4)_STATE_INT[FSM1_ENA]. */
	uint64_t fsm0_ena                     : 1;  /**< See OCLA(0..4)_STATE_INT[FSM0_ENA]. */
	uint64_t reserved_19_31               : 13;
	uint64_t ddrfull                      : 1;  /**< See OCLA(0..4)_STATE_INT[DDRFULL]. */
	uint64_t wmark                        : 1;  /**< See OCLA(0..4)_STATE_INT[WMARK]. */
	uint64_t overfull                     : 1;  /**< See OCLA(0..4)_STATE_INT[OVERFULL]. */
	uint64_t trigfull                     : 1;  /**< See OCLA(0..4)_STATE_INT[TRIGFULL]. */
	uint64_t captured                     : 1;  /**< See OCLA(0..4)_STATE_INT[CAPTURED]. */
	uint64_t fsm1_int                     : 1;  /**< See OCLA(0..4)_STATE_INT[FSM1_INT]. */
	uint64_t fsm0_int                     : 1;  /**< See OCLA(0..4)_STATE_INT[FSM0_INT]. */
	uint64_t mcd                          : 3;  /**< See OCLA(0..4)_STATE_INT[MCD]. */
	uint64_t trig                         : 1;  /**< See OCLA(0..4)_STATE_INT[TRIG]. */
	uint64_t reserved_4_7                 : 4;
	uint64_t ovfl                         : 4;  /**< See OCLA(0..4)_STATE_INT[OVFL]. */
#else
	uint64_t ovfl                         : 4;
	uint64_t reserved_4_7                 : 4;
	uint64_t trig                         : 1;
	uint64_t mcd                          : 3;
	uint64_t fsm0_int                     : 1;
	uint64_t fsm1_int                     : 1;
	uint64_t captured                     : 1;
	uint64_t trigfull                     : 1;
	uint64_t overfull                     : 1;
	uint64_t wmark                        : 1;
	uint64_t ddrfull                      : 1;
	uint64_t reserved_19_31               : 13;
	uint64_t fsm0_ena                     : 1;
	uint64_t fsm1_ena                     : 1;
	uint64_t fsm0_rst                     : 1;
	uint64_t fsm1_rst                     : 1;
	uint64_t reserved_36_55               : 20;
	uint64_t fsm0_state                   : 4;
	uint64_t fsm1_state                   : 4;
#endif
	} s;
	struct cvmx_oclax_state_set_s         cn70xx;
	struct cvmx_oclax_state_set_s         cn78xx;
};
typedef union cvmx_oclax_state_set cvmx_oclax_state_set_t;

/**
 * cvmx_ocla#_time
 */
union cvmx_oclax_time {
	uint64_t u64;
	struct cvmx_oclax_time_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t cycle                        : 32; /**< Current time as free running counter. Loaded into captured control packets. */
#else
	uint64_t cycle                        : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_oclax_time_s              cn70xx;
	struct cvmx_oclax_time_s              cn78xx;
};
typedef union cvmx_oclax_time cvmx_oclax_time_t;

#endif
