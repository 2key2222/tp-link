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
 * cvmx-lmcx-defs.h
 *
 * Configuration and status register (CSR) type definitions for
 * Octeon lmcx.
 *
 * This file is auto generated. Do not edit.
 *
 * <hr>$Revision$<hr>
 *
 */
#ifndef __CVMX_LMCX_DEFS_H__
#define __CVMX_LMCX_DEFS_H__

#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_BIST_CTL(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
			if ((block_id == 0))
				return CVMX_ADD_IO_SEG(0x0001180088000100ull) + ((block_id) & 0) * 0x60000000ull;
			break;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 3))
				return CVMX_ADD_IO_SEG(0x0001180088000100ull) + ((block_id) & 3) * 0x1000000ull;
			break;
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 1))
				return CVMX_ADD_IO_SEG(0x00011800880000F0ull) + ((block_id) & 1) * 0x60000000ull;
			break;
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN50XX & OCTEON_FAMILY_MASK:
			if ((block_id == 0))
				return CVMX_ADD_IO_SEG(0x00011800880000F0ull);
			break;
	}
	cvmx_warn("CVMX_LMCX_BIST_CTL (block_id = %lu) not supported on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000100ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
static inline uint64_t CVMX_LMCX_BIST_CTL(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000100ull) + (block_id) * 0x60000000ull;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000100ull) + (block_id) * 0x1000000ull;
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880000F0ull) + (block_id) * 0x60000000ull;
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN50XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880000F0ull);
	}
	return CVMX_ADD_IO_SEG(0x0001180088000100ull) + (block_id) * 0x1000000ull;
}
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_BIST_RESULT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1)))))
		cvmx_warn("CVMX_LMCX_BIST_RESULT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880000F8ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_BIST_RESULT(block_id) (CVMX_ADD_IO_SEG(0x00011800880000F8ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CHAR_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CHAR_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000220ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_CHAR_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000220ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CHAR_DQ_ERR_COUNT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_CHAR_DQ_ERR_COUNT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000040ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_CHAR_DQ_ERR_COUNT(block_id) (CVMX_ADD_IO_SEG(0x0001180088000040ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CHAR_MASK0(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CHAR_MASK0(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000228ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_CHAR_MASK0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000228ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CHAR_MASK1(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CHAR_MASK1(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000230ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_CHAR_MASK1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000230ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CHAR_MASK2(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CHAR_MASK2(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000238ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_CHAR_MASK2(block_id) (CVMX_ADD_IO_SEG(0x0001180088000238ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CHAR_MASK3(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CHAR_MASK3(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000240ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_CHAR_MASK3(block_id) (CVMX_ADD_IO_SEG(0x0001180088000240ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CHAR_MASK4(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CHAR_MASK4(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000318ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_CHAR_MASK4(block_id) (CVMX_ADD_IO_SEG(0x0001180088000318ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_COMP_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_COMP_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000028ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_COMP_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000028ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_COMP_CTL2(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_COMP_CTL2(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001B8ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_COMP_CTL2(block_id) (CVMX_ADD_IO_SEG(0x00011800880001B8ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CONFIG(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CONFIG(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000188ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_CONFIG(block_id) (CVMX_ADD_IO_SEG(0x0001180088000188ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CONTROL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CONTROL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000190ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_CONTROL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000190ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000010ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000010ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_CTL1(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_CTL1(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000090ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_CTL1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000090ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DCLK_CNT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_DCLK_CNT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001E0ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_DCLK_CNT(block_id) (CVMX_ADD_IO_SEG(0x00011800880001E0ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DCLK_CNT_HI(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_DCLK_CNT_HI(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000070ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_DCLK_CNT_HI(block_id) (CVMX_ADD_IO_SEG(0x0001180088000070ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DCLK_CNT_LO(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_DCLK_CNT_LO(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000068ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_DCLK_CNT_LO(block_id) (CVMX_ADD_IO_SEG(0x0001180088000068ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DCLK_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1)))))
		cvmx_warn("CVMX_LMCX_DCLK_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880000B8ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_DCLK_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880000B8ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DDR2_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_DDR2_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000018ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_DDR2_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000018ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DDR4_DIMM_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_DDR4_DIMM_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880003F0ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_DDR4_DIMM_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880003F0ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DDR_PLL_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_DDR_PLL_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000258ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_DDR_PLL_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000258ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DELAY_CFG(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_DELAY_CFG(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000088ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_DELAY_CFG(block_id) (CVMX_ADD_IO_SEG(0x0001180088000088ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DIMMX_DDR4_PARAMS0(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 1)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 1)) && ((block_id <= 3))))))
		cvmx_warn("CVMX_LMCX_DIMMX_DDR4_PARAMS0(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800880000D0ull) + (((offset) & 1) + ((block_id) & 3) * 0x200000ull) * 8;
}
#else
#define CVMX_LMCX_DIMMX_DDR4_PARAMS0(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800880000D0ull) + (((offset) & 1) + ((block_id) & 3) * 0x200000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DIMMX_DDR4_PARAMS1(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 1)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 1)) && ((block_id <= 3))))))
		cvmx_warn("CVMX_LMCX_DIMMX_DDR4_PARAMS1(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000140ull) + (((offset) & 1) + ((block_id) & 3) * 0x200000ull) * 8;
}
#else
#define CVMX_LMCX_DIMMX_DDR4_PARAMS1(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180088000140ull) + (((offset) & 1) + ((block_id) & 3) * 0x200000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DIMMX_PARAMS(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && (((offset <= 1)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && (((offset <= 1)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && (((offset <= 1)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && (((offset <= 1)) && ((block_id <= 3)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 1)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 1)) && ((block_id <= 3)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && (((offset <= 1)) && ((block_id == 0))))))
		cvmx_warn("CVMX_LMCX_DIMMX_PARAMS(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000270ull) + (((offset) & 1) + ((block_id) & 3) * 0x200000ull) * 8;
}
#else
#define CVMX_LMCX_DIMMX_PARAMS(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180088000270ull) + (((offset) & 1) + ((block_id) & 3) * 0x200000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DIMM_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_DIMM_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000310ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_DIMM_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000310ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DLL_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1)))))
		cvmx_warn("CVMX_LMCX_DLL_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880000C0ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_DLL_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880000C0ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DLL_CTL2(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_DLL_CTL2(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001C8ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_DLL_CTL2(block_id) (CVMX_ADD_IO_SEG(0x00011800880001C8ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DLL_CTL3(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_DLL_CTL3(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000218ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_DLL_CTL3(block_id) (CVMX_ADD_IO_SEG(0x0001180088000218ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_DUAL_MEMCFG(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 1))
				return CVMX_ADD_IO_SEG(0x0001180088000098ull) + ((block_id) & 1) * 0x60000000ull;
			break;
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN50XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN58XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			if ((block_id == 0))
				return CVMX_ADD_IO_SEG(0x0001180088000098ull) + ((block_id) & 0) * 0x60000000ull;
			break;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 3))
				return CVMX_ADD_IO_SEG(0x0001180088000098ull) + ((block_id) & 3) * 0x1000000ull;
			break;
	}
	cvmx_warn("CVMX_LMCX_DUAL_MEMCFG (block_id = %lu) not supported on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000098ull) + ((block_id) & 0) * 0x60000000ull;
}
#else
static inline uint64_t CVMX_LMCX_DUAL_MEMCFG(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000098ull) + (block_id) * 0x60000000ull;
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN50XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN58XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000098ull) + (block_id) * 0x60000000ull;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000098ull) + (block_id) * 0x1000000ull;
	}
	return CVMX_ADD_IO_SEG(0x0001180088000098ull) + (block_id) * 0x60000000ull;
}
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_ECC_PARITY_TEST(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_ECC_PARITY_TEST(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000108ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_ECC_PARITY_TEST(block_id) (CVMX_ADD_IO_SEG(0x0001180088000108ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_ECC_SYND(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN30XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN50XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN38XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN58XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			if ((block_id == 0))
				return CVMX_ADD_IO_SEG(0x0001180088000038ull) + ((block_id) & 0) * 0x60000000ull;
			break;
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 1))
				return CVMX_ADD_IO_SEG(0x0001180088000038ull) + ((block_id) & 1) * 0x60000000ull;
			break;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 3))
				return CVMX_ADD_IO_SEG(0x0001180088000038ull) + ((block_id) & 3) * 0x1000000ull;
			break;
	}
	cvmx_warn("CVMX_LMCX_ECC_SYND (block_id = %lu) not supported on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000038ull) + ((block_id) & 0) * 0x60000000ull;
}
#else
static inline uint64_t CVMX_LMCX_ECC_SYND(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN30XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN50XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN38XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN58XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000038ull) + (block_id) * 0x60000000ull;
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000038ull) + (block_id) * 0x60000000ull;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000038ull) + (block_id) * 0x1000000ull;
	}
	return CVMX_ADD_IO_SEG(0x0001180088000038ull) + (block_id) * 0x60000000ull;
}
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_EXT_CONFIG(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_EXT_CONFIG(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000030ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_EXT_CONFIG(block_id) (CVMX_ADD_IO_SEG(0x0001180088000030ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_FADR(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN30XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN50XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN38XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN58XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			if ((block_id == 0))
				return CVMX_ADD_IO_SEG(0x0001180088000020ull) + ((block_id) & 0) * 0x60000000ull;
			break;
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 1))
				return CVMX_ADD_IO_SEG(0x0001180088000020ull) + ((block_id) & 1) * 0x60000000ull;
			break;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 3))
				return CVMX_ADD_IO_SEG(0x0001180088000020ull) + ((block_id) & 3) * 0x1000000ull;
			break;
	}
	cvmx_warn("CVMX_LMCX_FADR (block_id = %lu) not supported on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000020ull) + ((block_id) & 0) * 0x60000000ull;
}
#else
static inline uint64_t CVMX_LMCX_FADR(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN30XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN50XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN38XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN31XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN58XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000020ull) + (block_id) * 0x60000000ull;
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000020ull) + (block_id) * 0x60000000ull;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x0001180088000020ull) + (block_id) * 0x1000000ull;
	}
	return CVMX_ADD_IO_SEG(0x0001180088000020ull) + (block_id) * 0x60000000ull;
}
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_IFB_CNT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_IFB_CNT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001D0ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_IFB_CNT(block_id) (CVMX_ADD_IO_SEG(0x00011800880001D0ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_IFB_CNT_HI(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_IFB_CNT_HI(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000050ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_IFB_CNT_HI(block_id) (CVMX_ADD_IO_SEG(0x0001180088000050ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_IFB_CNT_LO(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_IFB_CNT_LO(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000048ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_IFB_CNT_LO(block_id) (CVMX_ADD_IO_SEG(0x0001180088000048ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_INT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_INT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001F0ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_INT(block_id) (CVMX_ADD_IO_SEG(0x00011800880001F0ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_INT_EN(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_INT_EN(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001E8ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_INT_EN(block_id) (CVMX_ADD_IO_SEG(0x00011800880001E8ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_LANEX_CRC_SWIZ(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 8)) && ((block_id <= 3))))))
		cvmx_warn("CVMX_LMCX_LANEX_CRC_SWIZ(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000380ull) + (((offset) & 15) + ((block_id) & 3) * 0x200000ull) * 8;
}
#else
#define CVMX_LMCX_LANEX_CRC_SWIZ(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180088000380ull) + (((offset) & 15) + ((block_id) & 3) * 0x200000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MEM_CFG0(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_MEM_CFG0(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000000ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_MEM_CFG0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000000ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MEM_CFG1(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_MEM_CFG1(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000008ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_MEM_CFG1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000008ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MODEREG_PARAMS0(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_MODEREG_PARAMS0(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001A8ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_MODEREG_PARAMS0(block_id) (CVMX_ADD_IO_SEG(0x00011800880001A8ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MODEREG_PARAMS1(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_MODEREG_PARAMS1(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000260ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_MODEREG_PARAMS1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000260ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MODEREG_PARAMS2(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_MODEREG_PARAMS2(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000050ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_MODEREG_PARAMS2(block_id) (CVMX_ADD_IO_SEG(0x0001180088000050ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MODEREG_PARAMS3(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_MODEREG_PARAMS3(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000058ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_MODEREG_PARAMS3(block_id) (CVMX_ADD_IO_SEG(0x0001180088000058ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MPR_DATA0(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_MPR_DATA0(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000070ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_MPR_DATA0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000070ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MPR_DATA1(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_MPR_DATA1(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000078ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_MPR_DATA1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000078ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MPR_DATA2(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_MPR_DATA2(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000080ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_MPR_DATA2(block_id) (CVMX_ADD_IO_SEG(0x0001180088000080ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_MR_MPR_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_MR_MPR_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000068ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_MR_MPR_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000068ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_NXM(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 1))
				return CVMX_ADD_IO_SEG(0x00011800880000C8ull) + ((block_id) & 1) * 0x60000000ull;
			break;
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN58XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			if ((block_id == 0))
				return CVMX_ADD_IO_SEG(0x00011800880000C8ull) + ((block_id) & 0) * 0x60000000ull;
			break;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			if ((block_id <= 3))
				return CVMX_ADD_IO_SEG(0x00011800880000C8ull) + ((block_id) & 3) * 0x1000000ull;
			break;
	}
	cvmx_warn("CVMX_LMCX_NXM (block_id = %lu) not supported on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880000C8ull) + ((block_id) & 0) * 0x60000000ull;
}
#else
static inline uint64_t CVMX_LMCX_NXM(unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN56XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880000C8ull) + (block_id) * 0x60000000ull;
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN52XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN58XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880000C8ull) + (block_id) * 0x60000000ull;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880000C8ull) + (block_id) * 0x1000000ull;
	}
	return CVMX_ADD_IO_SEG(0x00011800880000C8ull) + (block_id) * 0x60000000ull;
}
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_NXM_FADR(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_NXM_FADR(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000028ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_NXM_FADR(block_id) (CVMX_ADD_IO_SEG(0x0001180088000028ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_OPS_CNT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_OPS_CNT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001D8ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_OPS_CNT(block_id) (CVMX_ADD_IO_SEG(0x00011800880001D8ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_OPS_CNT_HI(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_OPS_CNT_HI(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000060ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_OPS_CNT_HI(block_id) (CVMX_ADD_IO_SEG(0x0001180088000060ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_OPS_CNT_LO(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_OPS_CNT_LO(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000058ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_OPS_CNT_LO(block_id) (CVMX_ADD_IO_SEG(0x0001180088000058ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_PHY_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_PHY_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000210ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_PHY_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000210ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_PLL_BWCTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_PLL_BWCTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000040ull);
}
#else
#define CVMX_LMCX_PLL_BWCTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000040ull))
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_PLL_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_PLL_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880000A8ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_PLL_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880000A8ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_PLL_STATUS(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_PLL_STATUS(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880000B0ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_PLL_STATUS(block_id) (CVMX_ADD_IO_SEG(0x00011800880000B0ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_READ_LEVEL_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1)))))
		cvmx_warn("CVMX_LMCX_READ_LEVEL_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000140ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_READ_LEVEL_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000140ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_READ_LEVEL_DBG(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1)))))
		cvmx_warn("CVMX_LMCX_READ_LEVEL_DBG(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000148ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_READ_LEVEL_DBG(block_id) (CVMX_ADD_IO_SEG(0x0001180088000148ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_READ_LEVEL_RANKX(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && (((offset <= 3)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && (((offset <= 3)) && ((block_id <= 1))))))
		cvmx_warn("CVMX_LMCX_READ_LEVEL_RANKX(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000100ull) + (((offset) & 3) + ((block_id) & 1) * 0xC000000ull) * 8;
}
#else
#define CVMX_LMCX_READ_LEVEL_RANKX(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180088000100ull) + (((offset) & 3) + ((block_id) & 1) * 0xC000000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_RESET_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_RESET_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000180ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_RESET_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000180ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_RLEVEL_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_RLEVEL_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880002A0ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_RLEVEL_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880002A0ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_RLEVEL_DBG(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_RLEVEL_DBG(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880002A8ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_RLEVEL_DBG(block_id) (CVMX_ADD_IO_SEG(0x00011800880002A8ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_RLEVEL_RANKX(unsigned long offset, unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && (((offset <= 3)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && (((offset <= 3)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && (((offset <= 3)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && (((offset <= 3)) && ((block_id <= 3)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && (((offset <= 3)) && ((block_id == 0)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && (((offset <= 3)) && ((block_id <= 3)))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && (((offset <= 3)) && ((block_id == 0))))))
		cvmx_warn("CVMX_LMCX_RLEVEL_RANKX(%lu,%lu) is invalid on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000280ull) + (((offset) & 3) + ((block_id) & 3) * 0x200000ull) * 8;
}
#else
#define CVMX_LMCX_RLEVEL_RANKX(offset, block_id) (CVMX_ADD_IO_SEG(0x0001180088000280ull) + (((offset) & 3) + ((block_id) & 3) * 0x200000ull) * 8)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_RODT_COMP_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_RODT_COMP_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880000A0ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_RODT_COMP_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800880000A0ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_RODT_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_RODT_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000078ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_RODT_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000078ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_RODT_MASK(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_RODT_MASK(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000268ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_RODT_MASK(block_id) (CVMX_ADD_IO_SEG(0x0001180088000268ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_SCRAMBLED_FADR(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_SCRAMBLED_FADR(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000330ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_SCRAMBLED_FADR(block_id) (CVMX_ADD_IO_SEG(0x0001180088000330ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_SCRAMBLE_CFG0(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_SCRAMBLE_CFG0(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000320ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_SCRAMBLE_CFG0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000320ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_SCRAMBLE_CFG1(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_SCRAMBLE_CFG1(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000328ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_SCRAMBLE_CFG1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000328ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_SEQ_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_SEQ_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000048ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_SEQ_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000048ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_SLOT_CTL0(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_SLOT_CTL0(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001F8ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_SLOT_CTL0(block_id) (CVMX_ADD_IO_SEG(0x00011800880001F8ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_SLOT_CTL1(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_SLOT_CTL1(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000200ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_SLOT_CTL1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000200ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_SLOT_CTL2(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_SLOT_CTL2(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000208ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_SLOT_CTL2(block_id) (CVMX_ADD_IO_SEG(0x0001180088000208ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_TIMING_PARAMS0(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_TIMING_PARAMS0(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000198ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_TIMING_PARAMS0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000198ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_TIMING_PARAMS1(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_TIMING_PARAMS1(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001A0ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_TIMING_PARAMS1(block_id) (CVMX_ADD_IO_SEG(0x00011800880001A0ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_TIMING_PARAMS2(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3)))))
		cvmx_warn("CVMX_LMCX_TIMING_PARAMS2(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000060ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_TIMING_PARAMS2(block_id) (CVMX_ADD_IO_SEG(0x0001180088000060ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_TRO_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_TRO_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000248ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_TRO_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000248ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_TRO_STAT(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_TRO_STAT(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000250ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_TRO_STAT(block_id) (CVMX_ADD_IO_SEG(0x0001180088000250ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_WLEVEL_CTL(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_WLEVEL_CTL(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000300ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_WLEVEL_CTL(block_id) (CVMX_ADD_IO_SEG(0x0001180088000300ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_WLEVEL_DBG(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_WLEVEL_DBG(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000308ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_WLEVEL_DBG(block_id) (CVMX_ADD_IO_SEG(0x0001180088000308ull) + ((block_id) & 3) * 0x1000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_WLEVEL_RANKX(unsigned long offset, unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			if (((offset <= 3)) && ((block_id == 0)))
				return CVMX_ADD_IO_SEG(0x00011800880002B0ull) + (((offset) & 3) + ((block_id) & 0) * 0x0ull) * 8;
			break;
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
			if (((offset <= 3)) && ((block_id == 0)))
				return CVMX_ADD_IO_SEG(0x00011800880002B0ull) + (((offset) & 3) + ((block_id) & 0) * 0x200000ull) * 8;
			break;
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			if (((offset <= 3)) && ((block_id <= 3)))
				return CVMX_ADD_IO_SEG(0x00011800880002B0ull) + (((offset) & 3) + ((block_id) & 3) * 0x200000ull) * 8;
			break;
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
			if (((offset <= 3)) && ((block_id == 0)))
				return CVMX_ADD_IO_SEG(0x00011800880002C0ull) + (((offset) & 3) + ((block_id) & 0) * 0x200000ull) * 8;
			break;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
			if (((offset <= 3)) && ((block_id <= 3)))
				return CVMX_ADD_IO_SEG(0x00011800880002C0ull) + (((offset) & 3) + ((block_id) & 3) * 0x200000ull) * 8;
			break;
	}
	cvmx_warn("CVMX_LMCX_WLEVEL_RANKX (%lu, %lu) not supported on this chip\n", offset, block_id);
	return CVMX_ADD_IO_SEG(0x00011800880002B0ull) + (((offset) & 3) + ((block_id) & 0) * 0x200000ull) * 8;
}
#else
static inline uint64_t CVMX_LMCX_WLEVEL_RANKX(unsigned long offset, unsigned long block_id)
{
	switch(cvmx_get_octeon_family()) {
		case OCTEON_CN66XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN63XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880002B0ull) + ((offset) + (block_id) * 0x0ull) * 8;
		case OCTEON_CNF71XX & OCTEON_FAMILY_MASK:
		case OCTEON_CN61XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880002B0ull) + ((offset) + (block_id) * 0x200000ull) * 8;
		case OCTEON_CN68XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880002B0ull) + ((offset) + (block_id) * 0x200000ull) * 8;
		case OCTEON_CN70XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880002C0ull) + ((offset) + (block_id) * 0x200000ull) * 8;
		case OCTEON_CN78XX & OCTEON_FAMILY_MASK:
			return CVMX_ADD_IO_SEG(0x00011800880002C0ull) + ((offset) + (block_id) * 0x200000ull) * 8;
	}
	return CVMX_ADD_IO_SEG(0x00011800880002B0ull) + ((offset) + (block_id) * 0x200000ull) * 8;
}
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_WODT_CTL0(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN38XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN50XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN58XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_WODT_CTL0(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000030ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_WODT_CTL0(block_id) (CVMX_ADD_IO_SEG(0x0001180088000030ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_WODT_CTL1(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN30XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN31XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN52XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN56XX) && ((block_id <= 1)))))
		cvmx_warn("CVMX_LMCX_WODT_CTL1(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x0001180088000080ull) + ((block_id) & 1) * 0x60000000ull;
}
#else
#define CVMX_LMCX_WODT_CTL1(block_id) (CVMX_ADD_IO_SEG(0x0001180088000080ull) + ((block_id) & 1) * 0x60000000ull)
#endif
#if CVMX_ENABLE_CSR_ADDRESS_CHECKING
static inline uint64_t CVMX_LMCX_WODT_MASK(unsigned long block_id)
{
	if (!(
	      (OCTEON_IS_MODEL(OCTEON_CN61XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN63XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN66XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN68XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN70XX) && ((block_id == 0))) ||
	      (OCTEON_IS_MODEL(OCTEON_CN78XX) && ((block_id <= 3))) ||
	      (OCTEON_IS_MODEL(OCTEON_CNF71XX) && ((block_id == 0)))))
		cvmx_warn("CVMX_LMCX_WODT_MASK(%lu) is invalid on this chip\n", block_id);
	return CVMX_ADD_IO_SEG(0x00011800880001B0ull) + ((block_id) & 3) * 0x1000000ull;
}
#else
#define CVMX_LMCX_WODT_MASK(block_id) (CVMX_ADD_IO_SEG(0x00011800880001B0ull) + ((block_id) & 3) * 0x1000000ull)
#endif

/**
 * cvmx_lmc#_bist_ctl
 *
 * This register has fields to control BIST operation.
 *
 */
union cvmx_lmcx_bist_ctl {
	uint64_t u64;
	struct cvmx_lmcx_bist_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_4_63                : 60;
	uint64_t dlcram_bist_status           : 1;  /**< DLC RAM BIST status; 1 means fail. */
	uint64_t dlcram_bist_done             : 1;  /**< DLC RAM BIST complete indication; 1 means complete. */
	uint64_t start_bist                   : 1;  /**< Start BIST on DLC memory. */
	uint64_t reserved_0_0                 : 1;
#else
	uint64_t reserved_0_0                 : 1;
	uint64_t start_bist                   : 1;
	uint64_t dlcram_bist_done             : 1;
	uint64_t dlcram_bist_status           : 1;
	uint64_t reserved_4_63                : 60;
#endif
	} s;
	struct cvmx_lmcx_bist_ctl_cn50xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_1_63                : 63;
	uint64_t start                        : 1;  /**< A 0->1 transition causes BiST to run. */
#else
	uint64_t start                        : 1;
	uint64_t reserved_1_63                : 63;
#endif
	} cn50xx;
	struct cvmx_lmcx_bist_ctl_cn50xx      cn52xx;
	struct cvmx_lmcx_bist_ctl_cn50xx      cn52xxp1;
	struct cvmx_lmcx_bist_ctl_cn50xx      cn56xx;
	struct cvmx_lmcx_bist_ctl_cn50xx      cn56xxp1;
	struct cvmx_lmcx_bist_ctl_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_4_63                : 60;
	uint64_t dlcram_bist_status           : 1;  /**< Reserved. */
	uint64_t dlcram_bist_done             : 1;  /**< Reserved. */
	uint64_t start_bist                   : 1;  /**< Reserved. */
	uint64_t clear_bist                   : 1;  /**< Reserved. */
#else
	uint64_t clear_bist                   : 1;
	uint64_t start_bist                   : 1;
	uint64_t dlcram_bist_done             : 1;
	uint64_t dlcram_bist_status           : 1;
	uint64_t reserved_4_63                : 60;
#endif
	} cn70xx;
	struct cvmx_lmcx_bist_ctl_cn70xx      cn78xx;
};
typedef union cvmx_lmcx_bist_ctl cvmx_lmcx_bist_ctl_t;

/**
 * cvmx_lmc#_bist_result
 *
 * Notes:
 * Access to the internal BiST results
 * Each bit is the BiST result of an individual memory (per bit, 0=pass and 1=fail).
 */
union cvmx_lmcx_bist_result {
	uint64_t u64;
	struct cvmx_lmcx_bist_result_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_11_63               : 53;
	uint64_t csrd2e                       : 1;  /**< BiST result of CSRD2E memory (0=pass, !0=fail) */
	uint64_t csre2d                       : 1;  /**< BiST result of CSRE2D memory (0=pass, !0=fail) */
	uint64_t mwf                          : 1;  /**< BiST result of MWF memories (0=pass, !0=fail) */
	uint64_t mwd                          : 3;  /**< BiST result of MWD memories (0=pass, !0=fail) */
	uint64_t mwc                          : 1;  /**< BiST result of MWC memories (0=pass, !0=fail) */
	uint64_t mrf                          : 1;  /**< BiST result of MRF memories (0=pass, !0=fail) */
	uint64_t mrd                          : 3;  /**< BiST result of MRD memories (0=pass, !0=fail) */
#else
	uint64_t mrd                          : 3;
	uint64_t mrf                          : 1;
	uint64_t mwc                          : 1;
	uint64_t mwd                          : 3;
	uint64_t mwf                          : 1;
	uint64_t csre2d                       : 1;
	uint64_t csrd2e                       : 1;
	uint64_t reserved_11_63               : 53;
#endif
	} s;
	struct cvmx_lmcx_bist_result_cn50xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_9_63                : 55;
	uint64_t mwf                          : 1;  /**< BiST result of MWF memories (0=pass, !0=fail) */
	uint64_t mwd                          : 3;  /**< BiST result of MWD memories (0=pass, !0=fail) */
	uint64_t mwc                          : 1;  /**< BiST result of MWC memories (0=pass, !0=fail) */
	uint64_t mrf                          : 1;  /**< BiST result of MRF memories (0=pass, !0=fail) */
	uint64_t mrd                          : 3;  /**< BiST result of MRD memories (0=pass, !0=fail) */
#else
	uint64_t mrd                          : 3;
	uint64_t mrf                          : 1;
	uint64_t mwc                          : 1;
	uint64_t mwd                          : 3;
	uint64_t mwf                          : 1;
	uint64_t reserved_9_63                : 55;
#endif
	} cn50xx;
	struct cvmx_lmcx_bist_result_s        cn52xx;
	struct cvmx_lmcx_bist_result_s        cn52xxp1;
	struct cvmx_lmcx_bist_result_s        cn56xx;
	struct cvmx_lmcx_bist_result_s        cn56xxp1;
};
typedef union cvmx_lmcx_bist_result cvmx_lmcx_bist_result_t;

/**
 * cvmx_lmc#_char_ctl
 *
 * This register provides an assortment of various control fields needed to characterize the DDR3
 * interface.
 */
union cvmx_lmcx_char_ctl {
	uint64_t u64;
	struct cvmx_lmcx_char_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_53_63               : 11;
	uint64_t dq_char_check_lock           : 1;  /**< Indicates if a lock has been achieved. Is set to 1 only if a lock is achieved during the
                                                         LFSR priming period after DQ_CHAR_CHECK_ENABLE is set to 1, and is forced back to 0 when
                                                         DQ_CHAR_CHECK_ENABLE is set to 0. */
	uint64_t dq_char_check_enable         : 1;  /**< Enable DQ pattern check. The transition from disabled to enabled clears
                                                         LMC(0..3)_CHAR_DQ_ERR_COUNT. */
	uint64_t dq_char_bit_sel              : 3;  /**< Select a bit within the byte for DQ characterization pattern check. */
	uint64_t dq_char_byte_sel             : 4;  /**< Select a byte of data for DQ characterization pattern check. */
	uint64_t dr                           : 1;  /**< Pattern at Data Rate (not Clock Rate) */
	uint64_t skew_on                      : 1;  /**< Skew adjacent bits */
	uint64_t en                           : 1;  /**< Enable characterization */
	uint64_t sel                          : 1;  /**< Pattern select
                                                         0 = PRBS
                                                         1 = Programmable pattern */
	uint64_t prog                         : 8;  /**< Programmable pattern */
	uint64_t prbs                         : 32; /**< PRBS Polynomial */
#else
	uint64_t prbs                         : 32;
	uint64_t prog                         : 8;
	uint64_t sel                          : 1;
	uint64_t en                           : 1;
	uint64_t skew_on                      : 1;
	uint64_t dr                           : 1;
	uint64_t dq_char_byte_sel             : 4;
	uint64_t dq_char_bit_sel              : 3;
	uint64_t dq_char_check_enable         : 1;
	uint64_t dq_char_check_lock           : 1;
	uint64_t reserved_53_63               : 11;
#endif
	} s;
	struct cvmx_lmcx_char_ctl_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_44_63               : 20;
	uint64_t dr                           : 1;  /**< Pattern at Data Rate (not Clock Rate) */
	uint64_t skew_on                      : 1;  /**< Skew adjacent bits */
	uint64_t en                           : 1;  /**< Enable characterization */
	uint64_t sel                          : 1;  /**< Pattern select
                                                         0 = PRBS
                                                         1 = Programmable pattern */
	uint64_t prog                         : 8;  /**< Programmable pattern */
	uint64_t prbs                         : 32; /**< PRBS Polynomial */
#else
	uint64_t prbs                         : 32;
	uint64_t prog                         : 8;
	uint64_t sel                          : 1;
	uint64_t en                           : 1;
	uint64_t skew_on                      : 1;
	uint64_t dr                           : 1;
	uint64_t reserved_44_63               : 20;
#endif
	} cn61xx;
	struct cvmx_lmcx_char_ctl_cn63xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_42_63               : 22;
	uint64_t en                           : 1;  /**< Enable characterization */
	uint64_t sel                          : 1;  /**< Pattern select
                                                         0 = PRBS
                                                         1 = Programmable pattern */
	uint64_t prog                         : 8;  /**< Programmable pattern */
	uint64_t prbs                         : 32; /**< PRBS Polynomial */
#else
	uint64_t prbs                         : 32;
	uint64_t prog                         : 8;
	uint64_t sel                          : 1;
	uint64_t en                           : 1;
	uint64_t reserved_42_63               : 22;
#endif
	} cn63xx;
	struct cvmx_lmcx_char_ctl_cn63xx      cn63xxp1;
	struct cvmx_lmcx_char_ctl_cn61xx      cn66xx;
	struct cvmx_lmcx_char_ctl_cn61xx      cn68xx;
	struct cvmx_lmcx_char_ctl_cn63xx      cn68xxp1;
	struct cvmx_lmcx_char_ctl_s           cn70xx;
	struct cvmx_lmcx_char_ctl_s           cn78xx;
	struct cvmx_lmcx_char_ctl_cn61xx      cnf71xx;
};
typedef union cvmx_lmcx_char_ctl cvmx_lmcx_char_ctl_t;

/**
 * cvmx_lmc#_char_dq_err_count
 *
 * This register is used to initiate the various control sequences in the LMC.
 *
 */
union cvmx_lmcx_char_dq_err_count {
	uint64_t u64;
	struct cvmx_lmcx_char_dq_err_count_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_40_63               : 24;
	uint64_t dq_err_count                 : 40; /**< DQ error count. */
#else
	uint64_t dq_err_count                 : 40;
	uint64_t reserved_40_63               : 24;
#endif
	} s;
	struct cvmx_lmcx_char_dq_err_count_s  cn70xx;
	struct cvmx_lmcx_char_dq_err_count_s  cn78xx;
};
typedef union cvmx_lmcx_char_dq_err_count cvmx_lmcx_char_dq_err_count_t;

/**
 * cvmx_lmc#_char_mask0
 *
 * This register provides an assortment of various control fields needed to characterize the DDR3
 * interface.
 */
union cvmx_lmcx_char_mask0 {
	uint64_t u64;
	struct cvmx_lmcx_char_mask0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t mask                         : 64; /**< Mask for DQ0[63:0] */
#else
	uint64_t mask                         : 64;
#endif
	} s;
	struct cvmx_lmcx_char_mask0_s         cn61xx;
	struct cvmx_lmcx_char_mask0_s         cn63xx;
	struct cvmx_lmcx_char_mask0_s         cn63xxp1;
	struct cvmx_lmcx_char_mask0_s         cn66xx;
	struct cvmx_lmcx_char_mask0_s         cn68xx;
	struct cvmx_lmcx_char_mask0_s         cn68xxp1;
	struct cvmx_lmcx_char_mask0_s         cn70xx;
	struct cvmx_lmcx_char_mask0_s         cn78xx;
	struct cvmx_lmcx_char_mask0_s         cnf71xx;
};
typedef union cvmx_lmcx_char_mask0 cvmx_lmcx_char_mask0_t;

/**
 * cvmx_lmc#_char_mask1
 *
 * This register provides an assortment of various control fields needed to characterize the DDR3
 * interface.
 */
union cvmx_lmcx_char_mask1 {
	uint64_t u64;
	struct cvmx_lmcx_char_mask1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_8_63                : 56;
	uint64_t mask                         : 8;  /**< Mask for DQ0[71:64] */
#else
	uint64_t mask                         : 8;
	uint64_t reserved_8_63                : 56;
#endif
	} s;
	struct cvmx_lmcx_char_mask1_s         cn61xx;
	struct cvmx_lmcx_char_mask1_s         cn63xx;
	struct cvmx_lmcx_char_mask1_s         cn63xxp1;
	struct cvmx_lmcx_char_mask1_s         cn66xx;
	struct cvmx_lmcx_char_mask1_s         cn68xx;
	struct cvmx_lmcx_char_mask1_s         cn68xxp1;
	struct cvmx_lmcx_char_mask1_s         cn70xx;
	struct cvmx_lmcx_char_mask1_s         cn78xx;
	struct cvmx_lmcx_char_mask1_s         cnf71xx;
};
typedef union cvmx_lmcx_char_mask1 cvmx_lmcx_char_mask1_t;

/**
 * cvmx_lmc#_char_mask2
 *
 * This register provides an assortment of various control fields needed to characterize the DDR3
 * interface.
 */
union cvmx_lmcx_char_mask2 {
	uint64_t u64;
	struct cvmx_lmcx_char_mask2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t mask                         : 64; /**< Mask for DQ1[63:0] */
#else
	uint64_t mask                         : 64;
#endif
	} s;
	struct cvmx_lmcx_char_mask2_s         cn61xx;
	struct cvmx_lmcx_char_mask2_s         cn63xx;
	struct cvmx_lmcx_char_mask2_s         cn63xxp1;
	struct cvmx_lmcx_char_mask2_s         cn66xx;
	struct cvmx_lmcx_char_mask2_s         cn68xx;
	struct cvmx_lmcx_char_mask2_s         cn68xxp1;
	struct cvmx_lmcx_char_mask2_s         cn70xx;
	struct cvmx_lmcx_char_mask2_s         cn78xx;
	struct cvmx_lmcx_char_mask2_s         cnf71xx;
};
typedef union cvmx_lmcx_char_mask2 cvmx_lmcx_char_mask2_t;

/**
 * cvmx_lmc#_char_mask3
 *
 * This register provides an assortment of various control fields needed to characterize the DDR3
 * interface.
 */
union cvmx_lmcx_char_mask3 {
	uint64_t u64;
	struct cvmx_lmcx_char_mask3_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_8_63                : 56;
	uint64_t mask                         : 8;  /**< Mask for DQ1[71:64] */
#else
	uint64_t mask                         : 8;
	uint64_t reserved_8_63                : 56;
#endif
	} s;
	struct cvmx_lmcx_char_mask3_s         cn61xx;
	struct cvmx_lmcx_char_mask3_s         cn63xx;
	struct cvmx_lmcx_char_mask3_s         cn63xxp1;
	struct cvmx_lmcx_char_mask3_s         cn66xx;
	struct cvmx_lmcx_char_mask3_s         cn68xx;
	struct cvmx_lmcx_char_mask3_s         cn68xxp1;
	struct cvmx_lmcx_char_mask3_s         cn70xx;
	struct cvmx_lmcx_char_mask3_s         cn78xx;
	struct cvmx_lmcx_char_mask3_s         cnf71xx;
};
typedef union cvmx_lmcx_char_mask3 cvmx_lmcx_char_mask3_t;

/**
 * cvmx_lmc#_char_mask4
 *
 * This register is an assortment of various control fields needed to characterize the DDR3 interface.
 *
 */
union cvmx_lmcx_char_mask4 {
	uint64_t u64;
	struct cvmx_lmcx_char_mask4_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t ref_pin_on_mask              : 9;  /**< INTERNAL: This mask is applied to the REF_PIN_ON signals that go to
                                                         the PHY, so that each byte lane can selectively turn off or on the signals
                                                         once the master signals is enabled.  Using the symbol R, the mask looks
                                                         like this:
                                                         RRRRRRRRR
                                                         876543210 */
	uint64_t dac_on_mask                  : 9;  /**< INTERNAL: This mask is applied to the DAC_ON signals that go to
                                                         the PHY, so that each byte lane can selectively turn off or on the signals
                                                         once the master signals are enabled.  Using the symbols D  for DAC_ON,
                                                         the mask looks like this:
                                                         DDDDDDDDD
                                                         876543210 */
	uint64_t reserved_45_45               : 1;
	uint64_t dbi_mask                     : 9;  /**< Mask for DBI/DQS<1>. */
	uint64_t par_mask                     : 1;  /**< Mask for PAR. */
	uint64_t act_n_mask                   : 1;  /**< Mask for ACT_N. */
	uint64_t a17_mask                     : 1;  /**< Mask for A17. */
	uint64_t reset_n_mask                 : 1;  /**< Mask for RESET_L */
	uint64_t a_mask                       : 16; /**< Mask for A[15:0] */
	uint64_t ba_mask                      : 3;  /**< Mask for BA[2:0] */
	uint64_t we_n_mask                    : 1;  /**< Mask for WE_N */
	uint64_t cas_n_mask                   : 1;  /**< Mask for CAS_N */
	uint64_t ras_n_mask                   : 1;  /**< Mask for RAS_N */
	uint64_t odt1_mask                    : 2;  /**< Mask for ODT1 */
	uint64_t odt0_mask                    : 2;  /**< Mask for ODT0 */
	uint64_t cs1_n_mask                   : 2;  /**< Mask for CS1_N */
	uint64_t cs0_n_mask                   : 2;  /**< Mask for CS0_N */
	uint64_t cke_mask                     : 2;  /**< Mask for CKE* */
#else
	uint64_t cke_mask                     : 2;
	uint64_t cs0_n_mask                   : 2;
	uint64_t cs1_n_mask                   : 2;
	uint64_t odt0_mask                    : 2;
	uint64_t odt1_mask                    : 2;
	uint64_t ras_n_mask                   : 1;
	uint64_t cas_n_mask                   : 1;
	uint64_t we_n_mask                    : 1;
	uint64_t ba_mask                      : 3;
	uint64_t a_mask                       : 16;
	uint64_t reset_n_mask                 : 1;
	uint64_t a17_mask                     : 1;
	uint64_t act_n_mask                   : 1;
	uint64_t par_mask                     : 1;
	uint64_t dbi_mask                     : 9;
	uint64_t reserved_45_45               : 1;
	uint64_t dac_on_mask                  : 9;
	uint64_t ref_pin_on_mask              : 9;
#endif
	} s;
	struct cvmx_lmcx_char_mask4_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_33_63               : 31;
	uint64_t reset_n_mask                 : 1;  /**< Mask for RESET_L */
	uint64_t a_mask                       : 16; /**< Mask for A[15:0] */
	uint64_t ba_mask                      : 3;  /**< Mask for BA[2:0] */
	uint64_t we_n_mask                    : 1;  /**< Mask for WE_N */
	uint64_t cas_n_mask                   : 1;  /**< Mask for CAS_N */
	uint64_t ras_n_mask                   : 1;  /**< Mask for RAS_N */
	uint64_t odt1_mask                    : 2;  /**< Mask for ODT1 */
	uint64_t odt0_mask                    : 2;  /**< Mask for ODT0 */
	uint64_t cs1_n_mask                   : 2;  /**< Mask for CS1_N */
	uint64_t cs0_n_mask                   : 2;  /**< Mask for CS0_N */
	uint64_t cke_mask                     : 2;  /**< Mask for CKE* */
#else
	uint64_t cke_mask                     : 2;
	uint64_t cs0_n_mask                   : 2;
	uint64_t cs1_n_mask                   : 2;
	uint64_t odt0_mask                    : 2;
	uint64_t odt1_mask                    : 2;
	uint64_t ras_n_mask                   : 1;
	uint64_t cas_n_mask                   : 1;
	uint64_t we_n_mask                    : 1;
	uint64_t ba_mask                      : 3;
	uint64_t a_mask                       : 16;
	uint64_t reset_n_mask                 : 1;
	uint64_t reserved_33_63               : 31;
#endif
	} cn61xx;
	struct cvmx_lmcx_char_mask4_cn61xx    cn63xx;
	struct cvmx_lmcx_char_mask4_cn61xx    cn63xxp1;
	struct cvmx_lmcx_char_mask4_cn61xx    cn66xx;
	struct cvmx_lmcx_char_mask4_cn61xx    cn68xx;
	struct cvmx_lmcx_char_mask4_cn61xx    cn68xxp1;
	struct cvmx_lmcx_char_mask4_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_45_63               : 19;
	uint64_t dbi_mask                     : 9;  /**< Mask for DBI/DQS<1>. */
	uint64_t par_mask                     : 1;  /**< Mask for PAR. */
	uint64_t act_n_mask                   : 1;  /**< Mask for ACT_N. */
	uint64_t a17_mask                     : 1;  /**< Mask for A17. */
	uint64_t reset_n_mask                 : 1;  /**< Mask for RESET_L. */
	uint64_t a_mask                       : 16; /**< Mask for A<15:0>. */
	uint64_t ba_mask                      : 3;  /**< Mask for BA<2:0>. */
	uint64_t we_n_mask                    : 1;  /**< Mask for WE_N. */
	uint64_t cas_n_mask                   : 1;  /**< Mask for CAS_N. */
	uint64_t ras_n_mask                   : 1;  /**< Mask for RAS_N. */
	uint64_t odt1_mask                    : 2;  /**< Mask for ODT1. */
	uint64_t odt0_mask                    : 2;  /**< Mask for ODT0. */
	uint64_t cs1_n_mask                   : 2;  /**< Mask for CS1_N. */
	uint64_t cs0_n_mask                   : 2;  /**< Mask for CS0_N. */
	uint64_t cke_mask                     : 2;  /**< Mask for CKE*. */
#else
	uint64_t cke_mask                     : 2;
	uint64_t cs0_n_mask                   : 2;
	uint64_t cs1_n_mask                   : 2;
	uint64_t odt0_mask                    : 2;
	uint64_t odt1_mask                    : 2;
	uint64_t ras_n_mask                   : 1;
	uint64_t cas_n_mask                   : 1;
	uint64_t we_n_mask                    : 1;
	uint64_t ba_mask                      : 3;
	uint64_t a_mask                       : 16;
	uint64_t reset_n_mask                 : 1;
	uint64_t a17_mask                     : 1;
	uint64_t act_n_mask                   : 1;
	uint64_t par_mask                     : 1;
	uint64_t dbi_mask                     : 9;
	uint64_t reserved_45_63               : 19;
#endif
	} cn70xx;
	struct cvmx_lmcx_char_mask4_s         cn78xx;
	struct cvmx_lmcx_char_mask4_cn61xx    cnf71xx;
};
typedef union cvmx_lmcx_char_mask4 cvmx_lmcx_char_mask4_t;

/**
 * cvmx_lmc#_comp_ctl
 *
 * LMC_COMP_CTL = LMC Compensation control
 *
 */
union cvmx_lmcx_comp_ctl {
	uint64_t u64;
	struct cvmx_lmcx_comp_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t nctl_csr                     : 4;  /**< Compensation control bits */
	uint64_t nctl_clk                     : 4;  /**< Compensation control bits */
	uint64_t nctl_cmd                     : 4;  /**< Compensation control bits */
	uint64_t nctl_dat                     : 4;  /**< Compensation control bits */
	uint64_t pctl_csr                     : 4;  /**< Compensation control bits */
	uint64_t pctl_clk                     : 4;  /**< Compensation control bits */
	uint64_t reserved_0_7                 : 8;
#else
	uint64_t reserved_0_7                 : 8;
	uint64_t pctl_clk                     : 4;
	uint64_t pctl_csr                     : 4;
	uint64_t nctl_dat                     : 4;
	uint64_t nctl_cmd                     : 4;
	uint64_t nctl_clk                     : 4;
	uint64_t nctl_csr                     : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_comp_ctl_cn30xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t nctl_csr                     : 4;  /**< Compensation control bits */
	uint64_t nctl_clk                     : 4;  /**< Compensation control bits */
	uint64_t nctl_cmd                     : 4;  /**< Compensation control bits */
	uint64_t nctl_dat                     : 4;  /**< Compensation control bits */
	uint64_t pctl_csr                     : 4;  /**< Compensation control bits */
	uint64_t pctl_clk                     : 4;  /**< Compensation control bits */
	uint64_t pctl_cmd                     : 4;  /**< Compensation control bits */
	uint64_t pctl_dat                     : 4;  /**< Compensation control bits */
#else
	uint64_t pctl_dat                     : 4;
	uint64_t pctl_cmd                     : 4;
	uint64_t pctl_clk                     : 4;
	uint64_t pctl_csr                     : 4;
	uint64_t nctl_dat                     : 4;
	uint64_t nctl_cmd                     : 4;
	uint64_t nctl_clk                     : 4;
	uint64_t nctl_csr                     : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} cn30xx;
	struct cvmx_lmcx_comp_ctl_cn30xx      cn31xx;
	struct cvmx_lmcx_comp_ctl_cn30xx      cn38xx;
	struct cvmx_lmcx_comp_ctl_cn30xx      cn38xxp2;
	struct cvmx_lmcx_comp_ctl_cn50xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t nctl_csr                     : 4;  /**< Compensation control bits */
	uint64_t reserved_20_27               : 8;
	uint64_t nctl_dat                     : 4;  /**< Compensation control bits */
	uint64_t pctl_csr                     : 4;  /**< Compensation control bits */
	uint64_t reserved_5_11                : 7;
	uint64_t pctl_dat                     : 5;  /**< Compensation control bits */
#else
	uint64_t pctl_dat                     : 5;
	uint64_t reserved_5_11                : 7;
	uint64_t pctl_csr                     : 4;
	uint64_t nctl_dat                     : 4;
	uint64_t reserved_20_27               : 8;
	uint64_t nctl_csr                     : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} cn50xx;
	struct cvmx_lmcx_comp_ctl_cn50xx      cn52xx;
	struct cvmx_lmcx_comp_ctl_cn50xx      cn52xxp1;
	struct cvmx_lmcx_comp_ctl_cn50xx      cn56xx;
	struct cvmx_lmcx_comp_ctl_cn50xx      cn56xxp1;
	struct cvmx_lmcx_comp_ctl_cn50xx      cn58xx;
	struct cvmx_lmcx_comp_ctl_cn58xxp1 {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t nctl_csr                     : 4;  /**< Compensation control bits */
	uint64_t reserved_20_27               : 8;
	uint64_t nctl_dat                     : 4;  /**< Compensation control bits */
	uint64_t pctl_csr                     : 4;  /**< Compensation control bits */
	uint64_t reserved_4_11                : 8;
	uint64_t pctl_dat                     : 4;  /**< Compensation control bits */
#else
	uint64_t pctl_dat                     : 4;
	uint64_t reserved_4_11                : 8;
	uint64_t pctl_csr                     : 4;
	uint64_t nctl_dat                     : 4;
	uint64_t reserved_20_27               : 8;
	uint64_t nctl_csr                     : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} cn58xxp1;
};
typedef union cvmx_lmcx_comp_ctl cvmx_lmcx_comp_ctl_t;

/**
 * cvmx_lmc#_comp_ctl2
 *
 * LMC_COMP_CTL2 = LMC Compensation control
 *
 */
union cvmx_lmcx_comp_ctl2 {
	uint64_t u64;
	struct cvmx_lmcx_comp_ctl2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_51_63               : 13;
	uint64_t rclk_char_mode               : 1;  /**< Reserved. INTERNAL: Select RCLK characterization mode. */
	uint64_t reserved_40_49               : 10;
	uint64_t ptune_offset                 : 4;  /**< Ptune offset value. */
	uint64_t reserved_12_35               : 24;
	uint64_t cmd_ctl                      : 4;  /**< Drive strength control for CMD/A/RESET_L drivers
                                                         0001 = 24 ohm
                                                         0010 = 26.67 ohm
                                                         0011 = 30 ohm
                                                         0100 = 34.3 ohm
                                                         0101 = 40 ohm
                                                         0110 = 48 ohm
                                                         0111 = 60 ohm
                                                         0000,1000-1111 = Reserved */
	uint64_t ck_ctl                       : 4;  /**< Drive strength control for CK/CS*_L/ODT/CKE* drivers
                                                         0001 = 24 ohm
                                                         0010 = 26.67 ohm
                                                         0011 = 30 ohm
                                                         0100 = 34.3 ohm
                                                         0101 = 40 ohm
                                                         0110 = 48 ohm
                                                         0111 = 60 ohm
                                                         0000,1000-1111 = Reserved */
	uint64_t dqx_ctl                      : 4;  /**< Drive strength control for DQ/DQS drivers
                                                         0001 = 24 ohm
                                                         0010 = 26.67 ohm
                                                         0011 = 30 ohm
                                                         0100 = 34.3 ohm
                                                         0101 = 40 ohm
                                                         0110 = 48 ohm
                                                         0111 = 60 ohm
                                                         0000,1000-1111 = Reserved */
#else
	uint64_t dqx_ctl                      : 4;
	uint64_t ck_ctl                       : 4;
	uint64_t cmd_ctl                      : 4;
	uint64_t reserved_12_35               : 24;
	uint64_t ptune_offset                 : 4;
	uint64_t reserved_40_49               : 10;
	uint64_t rclk_char_mode               : 1;
	uint64_t reserved_51_63               : 13;
#endif
	} s;
	struct cvmx_lmcx_comp_ctl2_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_34_63               : 30;
	uint64_t ddr__ptune                   : 4;  /**< DDR PCTL from compensation circuit
                                                         The encoded value provides debug information for the
                                                         compensation impedance on P-pullup */
	uint64_t ddr__ntune                   : 4;  /**< DDR NCTL from compensation circuit
                                                         The encoded value provides debug information for the
                                                         compensation impedance on N-pulldown */
	uint64_t m180                         : 1;  /**< Cap impedance at 180 Ohm (instead of 240 Ohm) */
	uint64_t byp                          : 1;  /**< Bypass mode
                                                         When set, PTUNE,NTUNE are the compensation setting.
                                                         When clear, DDR_PTUNE,DDR_NTUNE are the compensation setting. */
	uint64_t ptune                        : 4;  /**< PCTL impedance control in bypass mode */
	uint64_t ntune                        : 4;  /**< NCTL impedance control in bypass mode */
	uint64_t rodt_ctl                     : 4;  /**< NCTL RODT impedance control bits
                                                         This field controls ODT values during a memory read
                                                         on the Octeon side
                                                         0000 = No ODT
                                                         0001 = 20 ohm
                                                         0010 = 30 ohm
                                                         0011 = 40 ohm
                                                         0100 = 60 ohm
                                                         0101 = 120 ohm
                                                         0110-1111 = Reserved */
	uint64_t cmd_ctl                      : 4;  /**< Drive strength control for CMD/A/RESET_L drivers
                                                         0001 = 24 ohm
                                                         0010 = 26.67 ohm
                                                         0011 = 30 ohm
                                                         0100 = 34.3 ohm
                                                         0101 = 40 ohm
                                                         0110 = 48 ohm
                                                         0111 = 60 ohm
                                                         0000,1000-1111 = Reserved */
	uint64_t ck_ctl                       : 4;  /**< Drive strength control for CK/CS*_L/ODT/CKE* drivers
                                                         0001 = 24 ohm
                                                         0010 = 26.67 ohm
                                                         0011 = 30 ohm
                                                         0100 = 34.3 ohm
                                                         0101 = 40 ohm
                                                         0110 = 48 ohm
                                                         0111 = 60 ohm
                                                         0000,1000-1111 = Reserved */
	uint64_t dqx_ctl                      : 4;  /**< Drive strength control for DQ/DQS drivers
                                                         0001 = 24 ohm
                                                         0010 = 26.67 ohm
                                                         0011 = 30 ohm
                                                         0100 = 34.3 ohm
                                                         0101 = 40 ohm
                                                         0110 = 48 ohm
                                                         0111 = 60 ohm
                                                         0000,1000-1111 = Reserved */
#else
	uint64_t dqx_ctl                      : 4;
	uint64_t ck_ctl                       : 4;
	uint64_t cmd_ctl                      : 4;
	uint64_t rodt_ctl                     : 4;
	uint64_t ntune                        : 4;
	uint64_t ptune                        : 4;
	uint64_t byp                          : 1;
	uint64_t m180                         : 1;
	uint64_t ddr__ntune                   : 4;
	uint64_t ddr__ptune                   : 4;
	uint64_t reserved_34_63               : 30;
#endif
	} cn61xx;
	struct cvmx_lmcx_comp_ctl2_cn61xx     cn63xx;
	struct cvmx_lmcx_comp_ctl2_cn61xx     cn63xxp1;
	struct cvmx_lmcx_comp_ctl2_cn61xx     cn66xx;
	struct cvmx_lmcx_comp_ctl2_cn61xx     cn68xx;
	struct cvmx_lmcx_comp_ctl2_cn61xx     cn68xxp1;
	struct cvmx_lmcx_comp_ctl2_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_51_63               : 13;
	uint64_t rclk_char_mode               : 1;  /**< Reserved. INTERNAL: Select RCLK characterization mode. */
	uint64_t ddr__ptune                   : 5;  /**< DDR PCTL from compensation circuit. The encoded value provides debug information for the
                                                         compensation impedance on P-pullup. */
	uint64_t ddr__ntune                   : 5;  /**< DDR NCTL from compensation circuit. The encoded value provides debug information for the
                                                         compensation impedance on N-pulldown. */
	uint64_t ptune_offset                 : 4;  /**< Ptune offset value. This is a signed value where the MSB is a sign bit, with zero
                                                         indicating addition and one indicating subtraction. */
	uint64_t ntune_offset                 : 4;  /**< Ntune offset value. This is a signed value where the MSB is a sign bit, with zero
                                                         indicating addition and one indicating subtraction. */
	uint64_t m180                         : 1;  /**< Reserved; must be zero. INTERNAL: Cap impedance at 180 ohm, instead of 240 ohm. */
	uint64_t byp                          : 1;  /**< Bypass mode. When set, PTUNE,NTUNE are the compensation setting. When clear,
                                                         DDR__PTUNE,DDR__NTUNE are the compensation setting. */
	uint64_t ptune                        : 5;  /**< PCTL impedance control in bypass mode. */
	uint64_t ntune                        : 5;  /**< NCTL impedance control in bypass mode. */
	uint64_t rodt_ctl                     : 4;  /**< RODT NCTL impedance control bits. This field controls ODT values during a memory read.
                                                         0x0 = No ODT. 0x3 = 40 ohm.
                                                         0x1 = 20 ohm. 0x4 = 60 ohm.
                                                         0x2 = 30 ohm. 0x5 = 120 ohm.
                                                         0x6-0xF = Reserved
                                                         In DDR4 mode:
                                                         0x0 = No ODT. 0x4 = 120 ohm.
                                                         0x1 = 40 ohm. 0x5 = 240 ohm.
                                                         0x2 = 60 ohm. 0x6 = 34 ohm.
                                                         0x3 = 80 ohm. 0x7 = 48 ohm.
                                                         0x8-0xF = Reserved */
	uint64_t control_ctl                  : 4;  /**< Drive strength control for ODT, etc. drivers.
                                                         In DDR3 mode:
                                                         0x1 = 24 ohm. 0x5 = 40 ohm.
                                                         0x2 = 26.67 ohm. 0x6 = 48 ohm.
                                                         0x3 = 30 ohm. 0x7 = 60 ohm.
                                                         0x4 = 34.3 ohm. 0x0, 0x8-0xF = Reserved.
                                                         In DDR4 mode:
                                                         0x0 = Reserved. 0x4 = 34 ohm.
                                                         0x1 = Reserved. 0x5 = 40 ohm.
                                                         0x2 = 26 ohm. 0x6 = 48 ohm.
                                                         0x3 = 30 ohm. 0x7 = 68 ohm.
                                                         0x8-0xF = Reserved. */
	uint64_t cmd_ctl                      : 4;  /**< Drive strength control for CMD/A/RESET_L drivers.
                                                         In DDR3 mode:
                                                         0x1 = 24 ohm. 0x5 = 40 ohm.
                                                         0x2 = 26.67 ohm. 0x6 = 48 ohm.
                                                         0x3 = 30 ohm. 0x7 = 60 ohm.
                                                         0x4 = 34.3 ohm. 0x0,0x8-0xF = Reserved.
                                                         In DDR4 mode:
                                                         0x0 = Reserved. 0x4 = 34 ohm.
                                                         0x1 = Reserved. 0x5 = 40 ohm.
                                                         0x2 = 26 ohm. 0x6 = 48 ohm.
                                                         0x3 = 30 ohm. 0x7 = 68 ohm.
                                                         0x8-0xF = Reserved. */
	uint64_t ck_ctl                       : 4;  /**< "Drive strength control for DDR_CK_*_P/DDRCS*_L/DDR_ODT_* /DDR_CKE*
                                                         drivers.
                                                         In DDR3 mode:
                                                         0x1 = 24 ohm. 0x5 = 40 ohm.
                                                         0x2 = 26.67 ohm. 0x6 = 48 ohm.
                                                         0x3 = 30 ohm. 0x7 = 60 ohm.
                                                         0x4 = 34.3 ohm. 0x0,0x8-0xF = Reserved.
                                                         In DDR4 mode:
                                                         0x0 = Reserved. 0x4 = 34 ohm.
                                                         0x1 = Reserved. 0x5 = 40 ohm.
                                                         0x2 = 26 ohm. 0x6 = 48 ohm.
                                                         0x3 = 30 ohm. 0x7 = 68 ohm.
                                                         0x8-0xF = Reserved." */
	uint64_t dqx_ctl                      : 4;  /**< Drive strength control for DDR_DQ* /DDR_DQS_*_P/N drivers.
                                                         0x1 = 24 ohm. 0x5 = 40 ohm.
                                                         0x2 = 26.67 ohm. 0x6 = 48 ohm.
                                                         0x3 = 30 ohm. 0x7 = 60 ohm.
                                                         0x4 = 34.3 ohm. 0x0,0x8-0xF = Reserved. */
#else
	uint64_t dqx_ctl                      : 4;
	uint64_t ck_ctl                       : 4;
	uint64_t cmd_ctl                      : 4;
	uint64_t control_ctl                  : 4;
	uint64_t rodt_ctl                     : 4;
	uint64_t ntune                        : 5;
	uint64_t ptune                        : 5;
	uint64_t byp                          : 1;
	uint64_t m180                         : 1;
	uint64_t ntune_offset                 : 4;
	uint64_t ptune_offset                 : 4;
	uint64_t ddr__ntune                   : 5;
	uint64_t ddr__ptune                   : 5;
	uint64_t rclk_char_mode               : 1;
	uint64_t reserved_51_63               : 13;
#endif
	} cn70xx;
	struct cvmx_lmcx_comp_ctl2_cn70xx     cn78xx;
	struct cvmx_lmcx_comp_ctl2_cn61xx     cnf71xx;
};
typedef union cvmx_lmcx_comp_ctl2 cvmx_lmcx_comp_ctl2_t;

/**
 * cvmx_lmc#_config
 *
 * This register controls certain parameters required for memory configuration. Note the
 * following:
 * Priority order for hardware write operations to
 * LMC(0..3)_CONFIG/LMC(0..3)_FADR/LMC(0..3)_ECC_SYND: DED error > SEC error.
 * The self-refresh entry sequence(s) power the DLL up/down (depending on
 * LMC(0..3)_MODEREG_PARAMS0[DLL]) when LMC(0..3)_CONFIG[SREF_WITH_DLL] is set.
 * Prior to the self-refresh exit sequence, LMC(0..3)_MODEREG_PARAMS0 should be reprogrammed (if
 * needed) to the appropriate values.
 * See LMC Initialization Sequence for the LMC bring-up sequence.
 */
union cvmx_lmcx_config {
	uint64_t u64;
	struct cvmx_lmcx_config_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_63_63               : 1;
	uint64_t bg2_enable                   : 1;  /**< BG2 pin is active for DDR4 mode. Only has an effect when LMC(0..3)_CONFIG[MODEDDR4] = 1.
                                                         Typically only cleared for DDR4 *16 devices, where there is no BG2 pin on the device. */
	uint64_t mode_x4dev                   : 1;  /**< DDR *4 device mode. */
	uint64_t mode32b                      : 1;  /**< 32b Datapath Mode                                          NS
                                                         Set to 1 if we use only 32 DQ pins
                                                         0 for 64b DQ mode. */
	uint64_t scrz                         : 1;  /**< Hide LMC*_SCRAMBLE_CFG0 and LMC*_SCRAMBLE_CFG1 when set */
	uint64_t early_unload_d1_r1           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 3
                                                         reads
                                                         The recommended EARLY_UNLOAD_D1_R1 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK3[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 3 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK3[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D1_R1
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D1_R1 = (maxset<1:0>!=3)). */
	uint64_t early_unload_d1_r0           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 2
                                                         reads
                                                         The recommended EARLY_UNLOAD_D1_RO value can be calculated
                                                         after the final LMC*_RLEVEL_RANK2[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 2 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK2[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D1_RO
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D1_RO = (maxset<1:0>!=3)). */
	uint64_t early_unload_d0_r1           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 1
                                                         reads
                                                         The recommended EARLY_UNLOAD_D0_R1 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK1[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 1 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK1[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D0_R1
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D0_R1 = (maxset<1:0>!=3)). */
	uint64_t early_unload_d0_r0           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 0
                                                         reads.
                                                         The recommended EARLY_UNLOAD_D0_R0 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK0[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 0 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK0[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D0_R0
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D0_R0 = (maxset<1:0>!=3)). */
	uint64_t init_status                  : 4;  /**< Indicates status of initialization
                                                         INIT_STATUS[n] = 1 implies rank n has been initialized
                                                         SW must set necessary INIT_STATUS bits with the
                                                         same LMC*_CONFIG write that initiates
                                                         power-up/init and self-refresh exit sequences
                                                         (if the required INIT_STATUS bits are not already
                                                         set before LMC initiates the sequence).
                                                         INIT_STATUS determines the chip-selects that assert
                                                         during refresh, ZQCS, and precharge power-down and
                                                         self-refresh entry/exit SEQUENCE's. */
	uint64_t mirrmask                     : 4;  /**< Mask determining which ranks are address-mirrored.
                                                         MIRRMASK<n> = 1 means Rank n addresses are mirrored
                                                         for 0 <= n <= 3
                                                         A mirrored read/write has these differences:
                                                          - DDR_BA<1> is swapped with DDR_BA<0>
                                                          - DDR_A<8> is swapped with DDR_A<7>
                                                          - DDR_A<6> is swapped with DDR_A<5>
                                                          - DDR_A<4> is swapped with DDR_A<3>
                                                         When RANK_ENA=0, MIRRMASK<1> and MIRRMASK<3> MBZ */
	uint64_t rankmask                     : 4;  /**< Mask to select rank to be leveled/initialized.
                                                         To write-level/read-level/initialize rank i, set RANKMASK<i>
                                                                         RANK_ENA=1               RANK_ENA=0
                                                           RANKMASK<0> = DIMM0_CS0                DIMM0_CS0
                                                           RANKMASK<1> = DIMM0_CS1                  MBZ
                                                           RANKMASK<2> = DIMM1_CS0                DIMM1_CS0
                                                           RANKMASK<3> = DIMM1_CS1                  MBZ
                                                         For read/write leveling, each rank has to be leveled separately,
                                                         so RANKMASK should only have one bit set.
                                                         RANKMASK is not used during self-refresh entry/exit and
                                                         precharge power-down entry/exit instruction sequences.
                                                         When RANK_ENA=0, RANKMASK<1> and RANKMASK<3> MBZ */
	uint64_t rank_ena                     : 1;  /**< RANK ena (for use with dual-rank DIMMs)
                                                         For dual-rank DIMMs, the rank_ena bit will enable
                                                         the drive of the CS*_L[1:0] and ODT_<1:0> pins differently based on the
                                                         (pbank_lsb-1) address bit.
                                                         Write 0 for SINGLE ranked DIMM's. */
	uint64_t sref_with_dll                : 1;  /**< Self-refresh entry/exit write MR1 and MR2
                                                         When set, self-refresh entry and exit instruction sequences
                                                         write MR1 and MR2 (in all ranks). (The writes occur before
                                                         self-refresh entry, and after self-refresh exit.)
                                                         When clear, self-refresh entry and exit instruction sequences
                                                         do not write any registers in the DDR3 parts. */
	uint64_t early_dqx                    : 1;  /**< Send DQx signals one CK cycle earlier for the case when
                                                         the shortest DQx lines have a larger delay than the CK line */
	uint64_t reserved_18_39               : 22;
	uint64_t reset                        : 1;  /**< Reset oneshot pulse for refresh counter,
                                                         and LMC*_OPS_CNT, LMC*_IFB_CNT, and LMC*_DCLK_CNT
                                                         CSR's. SW should write this to a one, then re-write
                                                         it to a zero to cause the reset. */
	uint64_t ecc_adr                      : 1;  /**< Include memory reference address in the ECC calculation
                                                         0=disabled, 1=enabled */
	uint64_t forcewrite                   : 4;  /**< Force the oldest outstanding write to complete after
                                                         having waited for 2^FORCEWRITE CK cycles.  0=disabled. */
	uint64_t idlepower                    : 3;  /**< Enter precharge power-down mode after the memory
                                                         controller has been idle for 2^(2+IDLEPOWER) CK cycles.
                                                         0=disabled.
                                                         This field should only be programmed after initialization.
                                                         LMC*_MODEREG_PARAMS0[PPD] determines whether the DRAM DLL
                                                         is disabled during the precharge power-down. */
	uint64_t pbank_lsb                    : 4;  /**< DIMM address bit select
                                                         Reverting to the explanation for ROW_LSB,
                                                         PBank_LSB would be Row_LSB bit + \#rowbits + \#rankbits
                                                         In the 512MB DIMM Example, assuming no rank bits:
                                                         pbank_lsb=mem_addr[15+13] for 64b mode
                                                                  =mem_addr[14+13] for 32b mode
                                                         Decoding for pbank_lsb
                                                              - 0000:DIMM = mem_adr[28]    / rank = mem_adr[27] (if RANK_ENA)
                                                              - 0001:DIMM = mem_adr[29]    / rank = mem_adr[28]      "
                                                              - 0010:DIMM = mem_adr[30]    / rank = mem_adr[29]      "
                                                              - 0011:DIMM = mem_adr[31]    / rank = mem_adr[30]      "
                                                              - 0100:DIMM = mem_adr[32]    / rank = mem_adr[31]      "
                                                              - 0101:DIMM = mem_adr[33]    / rank = mem_adr[32]      "
                                                              - 0110:DIMM = mem_adr[34]    / rank = mem_adr[33]      "
                                                              - 0111:DIMM = 0              / rank = mem_adr[34]      "
                                                              - 1000-1111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16]
                                                         With rank_ena = 0, pbank_lsb = 2
                                                         With rank_ena = 1, pbank_lsb = 3 */
	uint64_t row_lsb                      : 3;  /**< Row Address bit select
                                                         Encoding used to determine which memory address
                                                         bit position represents the low order DDR ROW address.
                                                         The processor's memory address[34:7] needs to be
                                                         translated to DRAM addresses (bnk,row,col,rank and DIMM)
                                                         and that is a function of the following:
                                                         1. Datapath Width (64 or 32)
                                                         2. \# Banks (8)
                                                         3. \# Column Bits of the memory part - spec'd indirectly
                                                         by this register.
                                                         4. \# Row Bits of the memory part - spec'd indirectly
                                                         5. \# Ranks in a DIMM - spec'd by RANK_ENA
                                                         6. \# DIMM's in the system by the register below (PBANK_LSB).
                                                         Col Address starts from mem_addr[2] for 32b (4Bytes)
                                                         dq width or from mem_addr[3] for 64b (8Bytes) dq width
                                                         \# col + \# bank = 12. Hence row_lsb is mem_adr[15] for
                                                         64bmode or mem_adr[14] for 32b mode. Hence row_lsb
                                                         parameter should be set to 001 (64b) or 000 (32b).
                                                         Decoding for row_lsb
                                                              - 000: row_lsb = mem_adr[14]
                                                              - 001: row_lsb = mem_adr[15]
                                                              - 010: row_lsb = mem_adr[16]
                                                              - 011: row_lsb = mem_adr[17]
                                                              - 100: row_lsb = mem_adr[18]
                                                              - 101: row_lsb = mem_adr[19]
                                                              - 110: row_lsb = mem_adr[20]
                                                              - 111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16] */
	uint64_t ecc_ena                      : 1;  /**< ECC Enable: When set will enable the 8b ECC
                                                         check/correct logic. Should be 1 when used with DIMMs
                                                         with ECC. 0, otherwise.
                                                         When this mode is turned on, DQ[71:64]
                                                         on writes, will contain the ECC code generated for
                                                         the 64 bits of data which will
                                                         written in the memory and then later on reads, used
                                                         to check for Single bit error (which will be auto-
                                                         corrected) and Double Bit error (which will be
                                                         reported). When not turned on, DQ[71:64]
                                                         are driven to 0.  Please refer to SEC_ERR, DED_ERR,
                                                         LMC*_FADR, LMC*_SCRAMBLED_FADR and LMC*_ECC_SYND registers
                                                         for diagnostics information when there is an error. */
	uint64_t init_start                   : 1;  /**< A 0->1 transition starts the DDR memory sequence that is
                                                         selected by LMC*_CONFIG[SEQUENCE].  This register is a
                                                         oneshot and clears itself each time it is set. */
#else
	uint64_t init_start                   : 1;
	uint64_t ecc_ena                      : 1;
	uint64_t row_lsb                      : 3;
	uint64_t pbank_lsb                    : 4;
	uint64_t idlepower                    : 3;
	uint64_t forcewrite                   : 4;
	uint64_t ecc_adr                      : 1;
	uint64_t reset                        : 1;
	uint64_t reserved_18_39               : 22;
	uint64_t early_dqx                    : 1;
	uint64_t sref_with_dll                : 1;
	uint64_t rank_ena                     : 1;
	uint64_t rankmask                     : 4;
	uint64_t mirrmask                     : 4;
	uint64_t init_status                  : 4;
	uint64_t early_unload_d0_r0           : 1;
	uint64_t early_unload_d0_r1           : 1;
	uint64_t early_unload_d1_r0           : 1;
	uint64_t early_unload_d1_r1           : 1;
	uint64_t scrz                         : 1;
	uint64_t mode32b                      : 1;
	uint64_t mode_x4dev                   : 1;
	uint64_t bg2_enable                   : 1;
	uint64_t reserved_63_63               : 1;
#endif
	} s;
	struct cvmx_lmcx_config_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_61_63               : 3;
	uint64_t mode32b                      : 1;  /**< 32b Datapath Mode                                          NS
                                                         Set to 1 if we use only 32 DQ pins
                                                         0 for 64b DQ mode. */
	uint64_t scrz                         : 1;  /**< Hide LMC*_SCRAMBLE_CFG0 and LMC*_SCRAMBLE_CFG1 when set */
	uint64_t early_unload_d1_r1           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 3
                                                         reads
                                                         The recommended EARLY_UNLOAD_D1_R1 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK3[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 3 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK3[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D1_R1
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D1_R1 = (maxset<1:0>!=3)). */
	uint64_t early_unload_d1_r0           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 2
                                                         reads
                                                         The recommended EARLY_UNLOAD_D1_RO value can be calculated
                                                         after the final LMC*_RLEVEL_RANK2[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 2 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK2[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D1_RO
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D1_RO = (maxset<1:0>!=3)). */
	uint64_t early_unload_d0_r1           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 1
                                                         reads
                                                         The recommended EARLY_UNLOAD_D0_R1 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK1[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 1 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK1[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D0_R1
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D0_R1 = (maxset<1:0>!=3)). */
	uint64_t early_unload_d0_r0           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 0
                                                         reads.
                                                         The recommended EARLY_UNLOAD_D0_R0 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK0[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 0 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK0[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D0_R0
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D0_R0 = (maxset<1:0>!=3)). */
	uint64_t init_status                  : 4;  /**< Indicates status of initialization
                                                         INIT_STATUS[n] = 1 implies rank n has been initialized
                                                         SW must set necessary INIT_STATUS bits with the
                                                         same LMC*_CONFIG write that initiates
                                                         power-up/init and self-refresh exit sequences
                                                         (if the required INIT_STATUS bits are not already
                                                         set before LMC initiates the sequence).
                                                         INIT_STATUS determines the chip-selects that assert
                                                         during refresh, ZQCS, and precharge power-down and
                                                         self-refresh entry/exit SEQUENCE's. */
	uint64_t mirrmask                     : 4;  /**< Mask determining which ranks are address-mirrored.
                                                         MIRRMASK<n> = 1 means Rank n addresses are mirrored
                                                         for 0 <= n <= 3
                                                         A mirrored read/write has these differences:
                                                          - DDR_BA<1> is swapped with DDR_BA<0>
                                                          - DDR_A<8> is swapped with DDR_A<7>
                                                          - DDR_A<6> is swapped with DDR_A<5>
                                                          - DDR_A<4> is swapped with DDR_A<3>
                                                         When RANK_ENA=0, MIRRMASK<1> and MIRRMASK<3> MBZ */
	uint64_t rankmask                     : 4;  /**< Mask to select rank to be leveled/initialized.
                                                         To write-level/read-level/initialize rank i, set RANKMASK<i>
                                                                         RANK_ENA=1               RANK_ENA=0
                                                           RANKMASK<0> = DIMM0_CS0                DIMM0_CS0
                                                           RANKMASK<1> = DIMM0_CS1                  MBZ
                                                           RANKMASK<2> = DIMM1_CS0                DIMM1_CS0
                                                           RANKMASK<3> = DIMM1_CS1                  MBZ
                                                         For read/write leveling, each rank has to be leveled separately,
                                                         so RANKMASK should only have one bit set.
                                                         RANKMASK is not used during self-refresh entry/exit and
                                                         precharge power-down entry/exit instruction sequences.
                                                         When RANK_ENA=0, RANKMASK<1> and RANKMASK<3> MBZ */
	uint64_t rank_ena                     : 1;  /**< RANK ena (for use with dual-rank DIMMs)
                                                         For dual-rank DIMMs, the rank_ena bit will enable
                                                         the drive of the CS*_L[1:0] and ODT_<1:0> pins differently based on the
                                                         (pbank_lsb-1) address bit.
                                                         Write 0 for SINGLE ranked DIMM's. */
	uint64_t sref_with_dll                : 1;  /**< Self-refresh entry/exit write MR1 and MR2
                                                         When set, self-refresh entry and exit instruction sequences
                                                         write MR1 and MR2 (in all ranks). (The writes occur before
                                                         self-refresh entry, and after self-refresh exit.)
                                                         When clear, self-refresh entry and exit instruction sequences
                                                         do not write any registers in the DDR3 parts. */
	uint64_t early_dqx                    : 1;  /**< Send DQx signals one CK cycle earlier for the case when
                                                         the shortest DQx lines have a larger delay than the CK line */
	uint64_t sequence                     : 3;  /**< Selects the sequence that LMC runs after a 0->1
                                                         transition on LMC*_CONFIG[INIT_START].
                                                         SEQUENCE=0=power-up/init:
                                                           - RANKMASK selects participating ranks (should be all ranks with attached DRAM)
                                                           - INIT_STATUS must equal RANKMASK
                                                           - DDR_DIMM*_CKE signals activated (if they weren't already active)
                                                           - RDIMM register control words 0-15 will be written to RANKMASK-selected
                                                               RDIMM's when LMC(0)_CONTROL[RDIMM_ENA]=1 and corresponding
                                                               LMC*_DIMM_CTL[DIMM*_WMASK] bits are set. (Refer to LMC*_DIMM*_PARAMS and
                                                               LMC*_DIMM_CTL descriptions below for more details.)
                                                           - MR0, MR1, MR2, and MR3 will be written to selected ranks
                                                         SEQUENCE=1=read-leveling:
                                                           - RANKMASK selects the rank to be read-leveled
                                                           - MR3 written to selected rank
                                                         SEQUENCE=2=self-refresh entry:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - MR1 and MR2 will be written to selected ranks if SREF_WITH_DLL=1
                                                           - DDR_DIMM*_CKE signals de-activated
                                                         SEQUENCE=3=self-refresh exit:
                                                           - INIT_STATUS must be set to indicate participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_DIMM*_CKE signals activated
                                                           - MR0, MR1, MR2, and MR3 will be written to participating ranks if SREF_WITH_DLL=1
                                                         SEQUENCE=4=precharge power-down entry:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_DIMM*_CKE signals de-activated
                                                         SEQUENCE=5=precharge power-down exit:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_DIMM*_CKE signals activated
                                                         SEQUENCE=6=write-leveling:
                                                           - RANKMASK selects the rank to be write-leveled
                                                           - INIT_STATUS must indicate all ranks with attached DRAM
                                                           - MR1 and MR2 written to INIT_STATUS-selected ranks
                                                         SEQUENCE=7=illegal
                                                         Precharge power-down entry and exit SEQUENCE's may also
                                                         be automatically generated by the HW when IDLEPOWER!=0.
                                                         Self-refresh entry SEQUENCE's may also be automatically
                                                         generated by hardware upon a chip warm or soft reset
                                                         sequence when LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT] are set.
                                                         LMC writes the LMC*_MODEREG_PARAMS0 and LMC*_MODEREG_PARAMS1 CSR field values
                                                         to the Mode registers in the DRAM parts (i.e. MR0, MR1, MR2, and MR3) as part of some of these sequences.
                                                         Refer to the LMC*_MODEREG_PARAMS0 and LMC*_MODEREG_PARAMS1 descriptions for more details.
                                                         If there are two consecutive power-up/init's without
                                                         a DRESET assertion between them, LMC asserts DDR_DIMM*_CKE as part of
                                                         the first power-up/init, and continues to assert DDR_DIMM*_CKE
                                                         through the remainder of the first and the second power-up/init.
                                                         If DDR_DIMM*_CKE deactivation and reactivation is needed for
                                                         a second power-up/init, a DRESET assertion is required
                                                         between the first and the second. */
	uint64_t ref_zqcs_int                 : 19; /**< Refresh & ZQCS interval represented in \#of 512 CK cycle
                                                         increments. A Refresh sequence is triggered when bits
                                                         [24:18] are equal to 0, and a ZQCS sequence is triggered
                                                         when [36:18] are equal to 0.
                                                         Program [24:18] to RND-DN(tREFI/clkPeriod/512)
                                                         Program [36:25] to RND-DN(ZQCS_Interval/clkPeriod/(512*128)). Note
                                                         that this value should always be greater than 32, to account for
                                                         resistor calibration delays.
                                                         000_00000000_00000000: RESERVED
                                                         Max Refresh interval = 127 * 512           = 65024 CKs
                                                         Max ZQCS interval    = (8*256*256-1) * 512 = 268434944 CKs ~ 335ms for a 800 MHz CK
                                                         LMC*_CONFIG[INIT_STATUS] determines which ranks receive
                                                         the REF / ZQCS. LMC does not send any refreshes / ZQCS's
                                                         when LMC*_CONFIG[INIT_STATUS]=0. */
	uint64_t reset                        : 1;  /**< Reset oneshot pulse for refresh counter,
                                                         and LMC*_OPS_CNT, LMC*_IFB_CNT, and LMC*_DCLK_CNT
                                                         CSR's. SW should write this to a one, then re-write
                                                         it to a zero to cause the reset. */
	uint64_t ecc_adr                      : 1;  /**< Include memory reference address in the ECC calculation
                                                         0=disabled, 1=enabled */
	uint64_t forcewrite                   : 4;  /**< Force the oldest outstanding write to complete after
                                                         having waited for 2^FORCEWRITE CK cycles.  0=disabled. */
	uint64_t idlepower                    : 3;  /**< Enter precharge power-down mode after the memory
                                                         controller has been idle for 2^(2+IDLEPOWER) CK cycles.
                                                         0=disabled.
                                                         This field should only be programmed after initialization.
                                                         LMC*_MODEREG_PARAMS0[PPD] determines whether the DRAM DLL
                                                         is disabled during the precharge power-down. */
	uint64_t pbank_lsb                    : 4;  /**< DIMM address bit select
                                                         Reverting to the explanation for ROW_LSB,
                                                         PBank_LSB would be Row_LSB bit + \#rowbits + \#rankbits
                                                         In the 512MB DIMM Example, assuming no rank bits:
                                                         pbank_lsb=mem_addr[15+13] for 64b mode
                                                                  =mem_addr[14+13] for 32b mode
                                                         Decoding for pbank_lsb
                                                              - 0000:DIMM = mem_adr[28]    / rank = mem_adr[27] (if RANK_ENA)
                                                              - 0001:DIMM = mem_adr[29]    / rank = mem_adr[28]      "
                                                              - 0010:DIMM = mem_adr[30]    / rank = mem_adr[29]      "
                                                              - 0011:DIMM = mem_adr[31]    / rank = mem_adr[30]      "
                                                              - 0100:DIMM = mem_adr[32]    / rank = mem_adr[31]      "
                                                              - 0101:DIMM = mem_adr[33]    / rank = mem_adr[32]      "
                                                              - 0110:DIMM = mem_adr[34]    / rank = mem_adr[33]      "
                                                              - 0111:DIMM = 0              / rank = mem_adr[34]      "
                                                              - 1000-1111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16]
                                                         With rank_ena = 0, pbank_lsb = 2
                                                         With rank_ena = 1, pbank_lsb = 3 */
	uint64_t row_lsb                      : 3;  /**< Row Address bit select
                                                         Encoding used to determine which memory address
                                                         bit position represents the low order DDR ROW address.
                                                         The processor's memory address[34:7] needs to be
                                                         translated to DRAM addresses (bnk,row,col,rank and DIMM)
                                                         and that is a function of the following:
                                                         1. Datapath Width (64 or 32)
                                                         2. \# Banks (8)
                                                         3. \# Column Bits of the memory part - spec'd indirectly
                                                         by this register.
                                                         4. \# Row Bits of the memory part - spec'd indirectly
                                                         5. \# Ranks in a DIMM - spec'd by RANK_ENA
                                                         6. \# DIMM's in the system by the register below (PBANK_LSB).
                                                         Col Address starts from mem_addr[2] for 32b (4Bytes)
                                                         dq width or from mem_addr[3] for 64b (8Bytes) dq width
                                                         \# col + \# bank = 12. Hence row_lsb is mem_adr[15] for
                                                         64bmode or mem_adr[14] for 32b mode. Hence row_lsb
                                                         parameter should be set to 001 (64b) or 000 (32b).
                                                         Decoding for row_lsb
                                                              - 000: row_lsb = mem_adr[14]
                                                              - 001: row_lsb = mem_adr[15]
                                                              - 010: row_lsb = mem_adr[16]
                                                              - 011: row_lsb = mem_adr[17]
                                                              - 100: row_lsb = mem_adr[18]
                                                              - 101: row_lsb = mem_adr[19]
                                                              - 110: row_lsb = mem_adr[20]
                                                              - 111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16] */
	uint64_t ecc_ena                      : 1;  /**< ECC Enable: When set will enable the 8b ECC
                                                         check/correct logic. Should be 1 when used with DIMMs
                                                         with ECC. 0, otherwise.
                                                         When this mode is turned on, DQ[71:64]
                                                         on writes, will contain the ECC code generated for
                                                         the 64 bits of data which will
                                                         written in the memory and then later on reads, used
                                                         to check for Single bit error (which will be auto-
                                                         corrected) and Double Bit error (which will be
                                                         reported). When not turned on, DQ[71:64]
                                                         are driven to 0.  Please refer to SEC_ERR, DED_ERR,
                                                         LMC*_FADR, LMC*_SCRAMBLED_FADR and LMC*_ECC_SYND registers
                                                         for diagnostics information when there is an error. */
	uint64_t init_start                   : 1;  /**< A 0->1 transition starts the DDR memory sequence that is
                                                         selected by LMC*_CONFIG[SEQUENCE].  This register is a
                                                         oneshot and clears itself each time it is set. */
#else
	uint64_t init_start                   : 1;
	uint64_t ecc_ena                      : 1;
	uint64_t row_lsb                      : 3;
	uint64_t pbank_lsb                    : 4;
	uint64_t idlepower                    : 3;
	uint64_t forcewrite                   : 4;
	uint64_t ecc_adr                      : 1;
	uint64_t reset                        : 1;
	uint64_t ref_zqcs_int                 : 19;
	uint64_t sequence                     : 3;
	uint64_t early_dqx                    : 1;
	uint64_t sref_with_dll                : 1;
	uint64_t rank_ena                     : 1;
	uint64_t rankmask                     : 4;
	uint64_t mirrmask                     : 4;
	uint64_t init_status                  : 4;
	uint64_t early_unload_d0_r0           : 1;
	uint64_t early_unload_d0_r1           : 1;
	uint64_t early_unload_d1_r0           : 1;
	uint64_t early_unload_d1_r1           : 1;
	uint64_t scrz                         : 1;
	uint64_t mode32b                      : 1;
	uint64_t reserved_61_63               : 3;
#endif
	} cn61xx;
	struct cvmx_lmcx_config_cn63xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_59_63               : 5;
	uint64_t early_unload_d1_r1           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 3
                                                         reads
                                                         The recommended EARLY_UNLOAD_D1_R1 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK3[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 3 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK3[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D1_R1
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D1_R1 = (maxset<1:0>!=3)). */
	uint64_t early_unload_d1_r0           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 2
                                                         reads
                                                         The recommended EARLY_UNLOAD_D1_RO value can be calculated
                                                         after the final LMC*_RLEVEL_RANK2[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 2 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK2[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D1_RO
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D1_RO = (maxset<1:0>!=3)). */
	uint64_t early_unload_d0_r1           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 1
                                                         reads
                                                         The recommended EARLY_UNLOAD_D0_R1 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK1[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 1 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK1[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D0_R1
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D0_R1 = (maxset<1:0>!=3)). */
	uint64_t early_unload_d0_r0           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 0
                                                         reads.
                                                         The recommended EARLY_UNLOAD_D0_R0 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK0[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 0 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK0[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D0_R0
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D0_R0 = (maxset<1:0>!=3)). */
	uint64_t init_status                  : 4;  /**< Indicates status of initialization
                                                         INIT_STATUS[n] = 1 implies rank n has been initialized
                                                         SW must set necessary INIT_STATUS bits with the
                                                         same LMC*_CONFIG write that initiates
                                                         power-up/init and self-refresh exit sequences
                                                         (if the required INIT_STATUS bits are not already
                                                         set before LMC initiates the sequence).
                                                         INIT_STATUS determines the chip-selects that assert
                                                         during refresh, ZQCS, and precharge power-down and
                                                         self-refresh entry/exit SEQUENCE's. */
	uint64_t mirrmask                     : 4;  /**< Mask determining which ranks are address-mirrored.
                                                         MIRRMASK<n> = 1 means Rank n addresses are mirrored
                                                         for 0 <= n <= 3
                                                         A mirrored read/write has these differences:
                                                          - DDR_BA<1> is swapped with DDR_BA<0>
                                                          - DDR_A<8> is swapped with DDR_A<7>
                                                          - DDR_A<6> is swapped with DDR_A<5>
                                                          - DDR_A<4> is swapped with DDR_A<3>
                                                         When RANK_ENA=0, MIRRMASK<1> and MIRRMASK<3> MBZ */
	uint64_t rankmask                     : 4;  /**< Mask to select rank to be leveled/initialized.
                                                         To write-level/read-level/initialize rank i, set RANKMASK<i>
                                                                         RANK_ENA=1               RANK_ENA=0
                                                           RANKMASK<0> = DIMM0_CS0                DIMM0_CS0
                                                           RANKMASK<1> = DIMM0_CS1                  MBZ
                                                           RANKMASK<2> = DIMM1_CS0                DIMM1_CS0
                                                           RANKMASK<3> = DIMM1_CS1                  MBZ
                                                         For read/write leveling, each rank has to be leveled separately,
                                                         so RANKMASK should only have one bit set.
                                                         RANKMASK is not used during self-refresh entry/exit and
                                                         precharge power-down entry/exit instruction sequences.
                                                         When RANK_ENA=0, RANKMASK<1> and RANKMASK<3> MBZ */
	uint64_t rank_ena                     : 1;  /**< RANK ena (for use with dual-rank DIMMs)
                                                         For dual-rank DIMMs, the rank_ena bit will enable
                                                         the drive of the CS*_L[1:0] and ODT_<1:0> pins differently based on the
                                                         (pbank_lsb-1) address bit.
                                                         Write 0 for SINGLE ranked DIMM's. */
	uint64_t sref_with_dll                : 1;  /**< Self-refresh entry/exit write MR1 and MR2
                                                         When set, self-refresh entry and exit instruction sequences
                                                         write MR1 and MR2 (in all ranks). (The writes occur before
                                                         self-refresh entry, and after self-refresh exit.)
                                                         When clear, self-refresh entry and exit instruction sequences
                                                         do not write any registers in the DDR3 parts. */
	uint64_t early_dqx                    : 1;  /**< Send DQx signals one CK cycle earlier for the case when
                                                         the shortest DQx lines have a larger delay than the CK line */
	uint64_t sequence                     : 3;  /**< Selects the sequence that LMC runs after a 0->1
                                                         transition on LMC*_CONFIG[INIT_START].
                                                         SEQUENCE=0=power-up/init:
                                                           - RANKMASK selects participating ranks (should be all ranks with attached DRAM)
                                                           - INIT_STATUS must equal RANKMASK
                                                           - DDR_CKE* signals activated (if they weren't already active)
                                                           - RDIMM register control words 0-15 will be written to RANKMASK-selected
                                                               RDIMM's when LMC(0)_CONTROL[RDIMM_ENA]=1 and corresponding
                                                               LMC*_DIMM_CTL[DIMM*_WMASK] bits are set. (Refer to LMC*_DIMM*_PARAMS and
                                                               LMC*_DIMM_CTL descriptions below for more details.)
                                                           - MR0, MR1, MR2, and MR3 will be written to selected ranks
                                                         SEQUENCE=1=read-leveling:
                                                           - RANKMASK selects the rank to be read-leveled
                                                           - MR3 written to selected rank
                                                         SEQUENCE=2=self-refresh entry:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - MR1 and MR2 will be written to selected ranks if SREF_WITH_DLL=1
                                                           - DDR_CKE* signals de-activated
                                                         SEQUENCE=3=self-refresh exit:
                                                           - INIT_STATUS must be set to indicate participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_CKE* signals activated
                                                           - MR0, MR1, MR2, and MR3 will be written to participating ranks if SREF_WITH_DLL=1
                                                         SEQUENCE=4=precharge power-down entry:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_CKE* signals de-activated
                                                         SEQUENCE=5=precharge power-down exit:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_CKE* signals activated
                                                         SEQUENCE=6=write-leveling:
                                                           - RANKMASK selects the rank to be write-leveled
                                                           - INIT_STATUS must indicate all ranks with attached DRAM
                                                           - MR1 and MR2 written to INIT_STATUS-selected ranks
                                                         SEQUENCE=7=illegal
                                                         Precharge power-down entry and exit SEQUENCE's may also
                                                         be automatically generated by the HW when IDLEPOWER!=0.
                                                         Self-refresh entry SEQUENCE's may also be automatically
                                                         generated by hardware upon a chip warm or soft reset
                                                         sequence when LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT] are set.
                                                         LMC writes the LMC*_MODEREG_PARAMS0 and LMC*_MODEREG_PARAMS1 CSR field values
                                                         to the Mode registers in the DRAM parts (i.e. MR0, MR1, MR2, and MR3) as part of some of these sequences.
                                                         Refer to the LMC*_MODEREG_PARAMS0 and LMC*_MODEREG_PARAMS1 descriptions for more details.
                                                         If there are two consecutive power-up/init's without
                                                         a DRESET assertion between them, LMC asserts DDR_CKE* as part of
                                                         the first power-up/init, and continues to assert DDR_CKE*
                                                         through the remainder of the first and the second power-up/init.
                                                         If DDR_CKE* deactivation and reactivation is needed for
                                                         a second power-up/init, a DRESET assertion is required
                                                         between the first and the second. */
	uint64_t ref_zqcs_int                 : 19; /**< Refresh & ZQCS interval represented in \#of 512 CK cycle
                                                         increments. A Refresh sequence is triggered when bits
                                                         [24:18] are equal to 0, and a ZQCS sequence is triggered
                                                         when [36:18] are equal to 0.
                                                         Program [24:18] to RND-DN(tREFI/clkPeriod/512)
                                                         Program [36:25] to RND-DN(ZQCS_Interval/clkPeriod/(512*128)). Note
                                                         that this value should always be greater than 32, to account for
                                                         resistor calibration delays.
                                                         000_00000000_00000000: RESERVED
                                                         Max Refresh interval = 127 * 512           = 65024 CKs
                                                         Max ZQCS interval    = (8*256*256-1) * 512 = 268434944 CKs ~ 335ms for a 800 MHz CK
                                                         LMC*_CONFIG[INIT_STATUS] determines which ranks receive
                                                         the REF / ZQCS. LMC does not send any refreshes / ZQCS's
                                                         when LMC*_CONFIG[INIT_STATUS]=0. */
	uint64_t reset                        : 1;  /**< Reset oneshot pulse for refresh counter,
                                                         and LMC*_OPS_CNT, LMC*_IFB_CNT, and LMC*_DCLK_CNT
                                                         CSR's. SW should write this to a one, then re-write
                                                         it to a zero to cause the reset. */
	uint64_t ecc_adr                      : 1;  /**< Include memory reference address in the ECC calculation
                                                         0=disabled, 1=enabled */
	uint64_t forcewrite                   : 4;  /**< Force the oldest outstanding write to complete after
                                                         having waited for 2^FORCEWRITE CK cycles.  0=disabled. */
	uint64_t idlepower                    : 3;  /**< Enter precharge power-down mode after the memory
                                                         controller has been idle for 2^(2+IDLEPOWER) CK cycles.
                                                         0=disabled.
                                                         This field should only be programmed after initialization.
                                                         LMC*_MODEREG_PARAMS0[PPD] determines whether the DRAM DLL
                                                         is disabled during the precharge power-down. */
	uint64_t pbank_lsb                    : 4;  /**< DIMM address bit select
                                                         Reverting to the explanation for ROW_LSB,
                                                         PBank_LSB would be Row_LSB bit + \#rowbits + \#rankbits
                                                         Decoding for pbank_lsb
                                                              - 0000:DIMM = mem_adr[28]    / rank = mem_adr[27] (if RANK_ENA)
                                                              - 0001:DIMM = mem_adr[29]    / rank = mem_adr[28]      "
                                                              - 0010:DIMM = mem_adr[30]    / rank = mem_adr[29]      "
                                                              - 0011:DIMM = mem_adr[31]    / rank = mem_adr[30]      "
                                                              - 0100:DIMM = mem_adr[32]    / rank = mem_adr[31]      "
                                                              - 0101:DIMM = mem_adr[33]    / rank = mem_adr[32]      "
                                                              - 0110:DIMM = mem_adr[34]    / rank = mem_adr[33]      "
                                                              - 0111:DIMM = 0              / rank = mem_adr[34]      "
                                                              - 1000-1111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16]
                                                         With rank_ena = 0, pbank_lsb = 2
                                                         With rank_ena = 1, pbank_lsb = 3 */
	uint64_t row_lsb                      : 3;  /**< Row Address bit select
                                                         Encoding used to determine which memory address
                                                         bit position represents the low order DDR ROW address.
                                                         The processor's memory address[34:7] needs to be
                                                         translated to DRAM addresses (bnk,row,col,rank and DIMM)
                                                         and that is a function of the following:
                                                         1. Datapath Width (64)
                                                         2. \# Banks (8)
                                                         3. \# Column Bits of the memory part - spec'd indirectly
                                                         by this register.
                                                         4. \# Row Bits of the memory part - spec'd indirectly
                                                         5. \# Ranks in a DIMM - spec'd by RANK_ENA
                                                         6. \# DIMM's in the system by the register below (PBANK_LSB).
                                                         Decoding for row_lsb
                                                              - 000: row_lsb = mem_adr[14]
                                                              - 001: row_lsb = mem_adr[15]
                                                              - 010: row_lsb = mem_adr[16]
                                                              - 011: row_lsb = mem_adr[17]
                                                              - 100: row_lsb = mem_adr[18]
                                                              - 101: row_lsb = mem_adr[19]
                                                              - 110: row_lsb = mem_adr[20]
                                                              - 111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16] */
	uint64_t ecc_ena                      : 1;  /**< ECC Enable: When set will enable the 8b ECC
                                                         check/correct logic. Should be 1 when used with DIMMs
                                                         with ECC. 0, otherwise.
                                                         When this mode is turned on, DQ[71:64]
                                                         on writes, will contain the ECC code generated for
                                                         the 64 bits of data which will
                                                         written in the memory and then later on reads, used
                                                         to check for Single bit error (which will be auto-
                                                         corrected) and Double Bit error (which will be
                                                         reported). When not turned on, DQ[71:64]
                                                         are driven to 0.  Please refer to SEC_ERR, DED_ERR,
                                                         LMC*_FADR, and LMC*_ECC_SYND registers
                                                         for diagnostics information when there is an error. */
	uint64_t init_start                   : 1;  /**< A 0->1 transition starts the DDR memory sequence that is
                                                         selected by LMC*_CONFIG[SEQUENCE].  This register is a
                                                         oneshot and clears itself each time it is set. */
#else
	uint64_t init_start                   : 1;
	uint64_t ecc_ena                      : 1;
	uint64_t row_lsb                      : 3;
	uint64_t pbank_lsb                    : 4;
	uint64_t idlepower                    : 3;
	uint64_t forcewrite                   : 4;
	uint64_t ecc_adr                      : 1;
	uint64_t reset                        : 1;
	uint64_t ref_zqcs_int                 : 19;
	uint64_t sequence                     : 3;
	uint64_t early_dqx                    : 1;
	uint64_t sref_with_dll                : 1;
	uint64_t rank_ena                     : 1;
	uint64_t rankmask                     : 4;
	uint64_t mirrmask                     : 4;
	uint64_t init_status                  : 4;
	uint64_t early_unload_d0_r0           : 1;
	uint64_t early_unload_d0_r1           : 1;
	uint64_t early_unload_d1_r0           : 1;
	uint64_t early_unload_d1_r1           : 1;
	uint64_t reserved_59_63               : 5;
#endif
	} cn63xx;
	struct cvmx_lmcx_config_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_55_63               : 9;
	uint64_t init_status                  : 4;  /**< Indicates status of initialization
                                                         INIT_STATUS[n] = 1 implies rank n has been initialized
                                                         SW must set necessary INIT_STATUS bits with the
                                                         same LMC*_CONFIG write that initiates
                                                         power-up/init and self-refresh exit sequences
                                                         (if the required INIT_STATUS bits are not already
                                                         set before LMC initiates the sequence).
                                                         INIT_STATUS determines the chip-selects that assert
                                                         during refresh, ZQCS, and precharge power-down and
                                                         self-refresh entry/exit SEQUENCE's. */
	uint64_t mirrmask                     : 4;  /**< Mask determining which ranks are address-mirrored.
                                                         MIRRMASK<n> = 1 means Rank n addresses are mirrored
                                                         for 0 <= n <= 3
                                                         A mirrored read/write has these differences:
                                                          - DDR_BA<1> is swapped with DDR_BA<0>
                                                          - DDR_A<8> is swapped with DDR_A<7>
                                                          - DDR_A<6> is swapped with DDR_A<5>
                                                          - DDR_A<4> is swapped with DDR_A<3>
                                                         When RANK_ENA=0, MIRRMASK<1> and MIRRMASK<3> MBZ */
	uint64_t rankmask                     : 4;  /**< Mask to select rank to be leveled/initialized.
                                                         To write-level/read-level/initialize rank i, set RANKMASK<i>
                                                                         RANK_ENA=1               RANK_ENA=0
                                                           RANKMASK<0> = DIMM0_CS0                DIMM0_CS0
                                                           RANKMASK<1> = DIMM0_CS1                  MBZ
                                                           RANKMASK<2> = DIMM1_CS0                DIMM1_CS0
                                                           RANKMASK<3> = DIMM1_CS1                  MBZ
                                                         For read/write leveling, each rank has to be leveled separately,
                                                         so RANKMASK should only have one bit set.
                                                         RANKMASK is not used during self-refresh entry/exit and
                                                         precharge power-down entry/exit instruction sequences.
                                                         When RANK_ENA=0, RANKMASK<1> and RANKMASK<3> MBZ */
	uint64_t rank_ena                     : 1;  /**< RANK ena (for use with dual-rank DIMMs)
                                                         For dual-rank DIMMs, the rank_ena bit will enable
                                                         the drive of the CS*_L[1:0] and ODT_<1:0> pins differently based on the
                                                         (pbank_lsb-1) address bit.
                                                         Write 0 for SINGLE ranked DIMM's. */
	uint64_t sref_with_dll                : 1;  /**< Self-refresh entry/exit write MR1 and MR2
                                                         When set, self-refresh entry and exit instruction sequences
                                                         write MR1 and MR2 (in all ranks). (The writes occur before
                                                         self-refresh entry, and after self-refresh exit.)
                                                         When clear, self-refresh entry and exit instruction sequences
                                                         do not write any registers in the DDR3 parts. */
	uint64_t early_dqx                    : 1;  /**< Send DQx signals one CK cycle earlier for the case when
                                                         the shortest DQx lines have a larger delay than the CK line */
	uint64_t sequence                     : 3;  /**< Selects the sequence that LMC runs after a 0->1
                                                         transition on LMC*_CONFIG[INIT_START].
                                                         SEQUENCE=0=power-up/init:
                                                           - RANKMASK selects participating ranks (should be all ranks with attached DRAM)
                                                           - INIT_STATUS must equal RANKMASK
                                                           - DDR_CKE* signals activated (if they weren't already active)
                                                           - RDIMM register control words 0-15 will be written to RANKMASK-selected
                                                               RDIMM's when LMC(0)_CONTROL[RDIMM_ENA]=1 and corresponding
                                                               LMC*_DIMM_CTL[DIMM*_WMASK] bits are set. (Refer to LMC*_DIMM*_PARAMS and
                                                               LMC*_DIMM_CTL descriptions below for more details.)
                                                           - MR0, MR1, MR2, and MR3 will be written to selected ranks
                                                         SEQUENCE=1=read-leveling:
                                                           - RANKMASK selects the rank to be read-leveled
                                                           - MR3 written to selected rank
                                                         SEQUENCE=2=self-refresh entry:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - MR1 and MR2 will be written to selected ranks if SREF_WITH_DLL=1
                                                           - DDR_CKE* signals de-activated
                                                         SEQUENCE=3=self-refresh exit:
                                                           - INIT_STATUS must be set to indicate participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_CKE* signals activated
                                                           - MR0, MR1, MR2, and MR3 will be written to participating ranks if SREF_WITH_DLL=1
                                                         SEQUENCE=4=precharge power-down entry:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_CKE* signals de-activated
                                                         SEQUENCE=5=precharge power-down exit:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_CKE* signals activated
                                                         SEQUENCE=6=write-leveling:
                                                           - RANKMASK selects the rank to be write-leveled
                                                           - INIT_STATUS must indicate all ranks with attached DRAM
                                                           - MR1 and MR2 written to INIT_STATUS-selected ranks
                                                         SEQUENCE=7=illegal
                                                         Precharge power-down entry and exit SEQUENCE's may also
                                                         be automatically generated by the HW when IDLEPOWER!=0.
                                                         Self-refresh entry SEQUENCE's may also be automatically
                                                         generated by hardware upon a chip warm or soft reset
                                                         sequence when LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT] are set.
                                                         LMC writes the LMC*_MODEREG_PARAMS0 and LMC*_MODEREG_PARAMS1 CSR field values
                                                         to the Mode registers in the DRAM parts (i.e. MR0, MR1, MR2, and MR3) as part of some of these sequences.
                                                         Refer to the LMC*_MODEREG_PARAMS0 and LMC*_MODEREG_PARAMS1 descriptions for more details.
                                                         If there are two consecutive power-up/init's without
                                                         a DRESET assertion between them, LMC asserts DDR_CKE* as part of
                                                         the first power-up/init, and continues to assert DDR_CKE*
                                                         through the remainder of the first and the second power-up/init.
                                                         If DDR_CKE* deactivation and reactivation is needed for
                                                         a second power-up/init, a DRESET assertion is required
                                                         between the first and the second. */
	uint64_t ref_zqcs_int                 : 19; /**< Refresh & ZQCS interval represented in \#of 512 CK cycle
                                                         increments. A Refresh sequence is triggered when bits
                                                         [24:18] are equal to 0, and a ZQCS sequence is triggered
                                                         when [36:18] are equal to 0.
                                                         Program [24:18] to RND-DN(tREFI/clkPeriod/512)
                                                         Program [36:25] to RND-DN(ZQCS_Interval/clkPeriod/(512*128)). Note
                                                         that this value should always be greater than 32, to account for
                                                         resistor calibration delays.
                                                         000_00000000_00000000: RESERVED
                                                         Max Refresh interval = 127 * 512           = 65024 CKs
                                                         Max ZQCS interval    = (8*256*256-1) * 512 = 268434944 CKs ~ 335ms for a 800 MHz CK
                                                         LMC*_CONFIG[INIT_STATUS] determines which ranks receive
                                                         the REF / ZQCS. LMC does not send any refreshes / ZQCS's
                                                         when LMC*_CONFIG[INIT_STATUS]=0. */
	uint64_t reset                        : 1;  /**< Reset oneshot pulse for refresh counter,
                                                         and LMC*_OPS_CNT, LMC*_IFB_CNT, and LMC*_DCLK_CNT
                                                         CSR's. SW should write this to a one, then re-write
                                                         it to a zero to cause the reset. */
	uint64_t ecc_adr                      : 1;  /**< Include memory reference address in the ECC calculation
                                                         0=disabled, 1=enabled */
	uint64_t forcewrite                   : 4;  /**< Force the oldest outstanding write to complete after
                                                         having waited for 2^FORCEWRITE CK cycles.  0=disabled. */
	uint64_t idlepower                    : 3;  /**< Enter precharge power-down mode after the memory
                                                         controller has been idle for 2^(2+IDLEPOWER) CK cycles.
                                                         0=disabled.
                                                         This field should only be programmed after initialization.
                                                         LMC*_MODEREG_PARAMS0[PPD] determines whether the DRAM DLL
                                                         is disabled during the precharge power-down. */
	uint64_t pbank_lsb                    : 4;  /**< DIMM address bit select
                                                         Reverting to the explanation for ROW_LSB,
                                                         PBank_LSB would be Row_LSB bit + \#rowbits + \#rankbits
                                                         Decoding for pbank_lsb
                                                              - 0000:DIMM = mem_adr[28]    / rank = mem_adr[27] (if RANK_ENA)
                                                              - 0001:DIMM = mem_adr[29]    / rank = mem_adr[28]      "
                                                              - 0010:DIMM = mem_adr[30]    / rank = mem_adr[29]      "
                                                              - 0011:DIMM = mem_adr[31]    / rank = mem_adr[30]      "
                                                              - 0100:DIMM = mem_adr[32]    / rank = mem_adr[31]      "
                                                              - 0101:DIMM = mem_adr[33]    / rank = mem_adr[32]      "
                                                              - 0110:DIMM = mem_adr[34]    / rank = mem_adr[33]      "
                                                              - 0111:DIMM = 0              / rank = mem_adr[34]      "
                                                              - 1000-1111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16]
                                                         With rank_ena = 0, pbank_lsb = 2
                                                         With rank_ena = 1, pbank_lsb = 3 */
	uint64_t row_lsb                      : 3;  /**< Row Address bit select
                                                         Encoding used to determine which memory address
                                                         bit position represents the low order DDR ROW address.
                                                         The processor's memory address[34:7] needs to be
                                                         translated to DRAM addresses (bnk,row,col,rank and DIMM)
                                                         and that is a function of the following:
                                                         1. Datapath Width (64)
                                                         2. \# Banks (8)
                                                         3. \# Column Bits of the memory part - spec'd indirectly
                                                         by this register.
                                                         4. \# Row Bits of the memory part - spec'd indirectly
                                                         5. \# Ranks in a DIMM - spec'd by RANK_ENA
                                                         6. \# DIMM's in the system by the register below (PBANK_LSB).
                                                         Decoding for row_lsb
                                                              - 000: row_lsb = mem_adr[14]
                                                              - 001: row_lsb = mem_adr[15]
                                                              - 010: row_lsb = mem_adr[16]
                                                              - 011: row_lsb = mem_adr[17]
                                                              - 100: row_lsb = mem_adr[18]
                                                              - 101: row_lsb = mem_adr[19]
                                                              - 110: row_lsb = mem_adr[20]
                                                              - 111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16] */
	uint64_t ecc_ena                      : 1;  /**< ECC Enable: When set will enable the 8b ECC
                                                         check/correct logic. Should be 1 when used with DIMMs
                                                         with ECC. 0, otherwise.
                                                         When this mode is turned on, DQ[71:64]
                                                         on writes, will contain the ECC code generated for
                                                         the 64 bits of data which will
                                                         written in the memory and then later on reads, used
                                                         to check for Single bit error (which will be auto-
                                                         corrected) and Double Bit error (which will be
                                                         reported). When not turned on, DQ[71:64]
                                                         are driven to 0.  Please refer to SEC_ERR, DED_ERR,
                                                         LMC*_FADR, and LMC*_ECC_SYND registers
                                                         for diagnostics information when there is an error. */
	uint64_t init_start                   : 1;  /**< A 0->1 transition starts the DDR memory sequence that is
                                                         selected by LMC*_CONFIG[SEQUENCE].  This register is a
                                                         oneshot and clears itself each time it is set. */
#else
	uint64_t init_start                   : 1;
	uint64_t ecc_ena                      : 1;
	uint64_t row_lsb                      : 3;
	uint64_t pbank_lsb                    : 4;
	uint64_t idlepower                    : 3;
	uint64_t forcewrite                   : 4;
	uint64_t ecc_adr                      : 1;
	uint64_t reset                        : 1;
	uint64_t ref_zqcs_int                 : 19;
	uint64_t sequence                     : 3;
	uint64_t early_dqx                    : 1;
	uint64_t sref_with_dll                : 1;
	uint64_t rank_ena                     : 1;
	uint64_t rankmask                     : 4;
	uint64_t mirrmask                     : 4;
	uint64_t init_status                  : 4;
	uint64_t reserved_55_63               : 9;
#endif
	} cn63xxp1;
	struct cvmx_lmcx_config_cn66xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_60_63               : 4;
	uint64_t scrz                         : 1;  /**< Hide LMC*_SCRAMBLE_CFG0 and LMC*_SCRAMBLE_CFG1 when set */
	uint64_t early_unload_d1_r1           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 3
                                                         reads
                                                         The recommended EARLY_UNLOAD_D1_R1 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK3[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 3 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK3[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D1_R1
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D1_R1 = (maxset<1:0>!=3)). */
	uint64_t early_unload_d1_r0           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 2
                                                         reads
                                                         The recommended EARLY_UNLOAD_D1_RO value can be calculated
                                                         after the final LMC*_RLEVEL_RANK2[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 2 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK2[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D1_RO
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D1_RO = (maxset<1:0>!=3)). */
	uint64_t early_unload_d0_r1           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 1
                                                         reads
                                                         The recommended EARLY_UNLOAD_D0_R1 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK1[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 1 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK1[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D0_R1
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D0_R1 = (maxset<1:0>!=3)). */
	uint64_t early_unload_d0_r0           : 1;  /**< When set, unload the PHY silo one cycle early for Rank 0
                                                         reads.
                                                         The recommended EARLY_UNLOAD_D0_R0 value can be calculated
                                                         after the final LMC*_RLEVEL_RANK0[BYTE*] values are
                                                         selected (as part of read-leveling initialization).
                                                         Then, determine the largest read-leveling setting
                                                         for rank 0 (i.e. calculate maxset=MAX(LMC*_RLEVEL_RANK0[BYTEi])
                                                         across all i), then set EARLY_UNLOAD_D0_R0
                                                         when the low two bits of this largest setting is not
                                                         3 (i.e. EARLY_UNLOAD_D0_R0 = (maxset<1:0>!=3)). */
	uint64_t init_status                  : 4;  /**< Indicates status of initialization
                                                         INIT_STATUS[n] = 1 implies rank n has been initialized
                                                         SW must set necessary INIT_STATUS bits with the
                                                         same LMC*_CONFIG write that initiates
                                                         power-up/init and self-refresh exit sequences
                                                         (if the required INIT_STATUS bits are not already
                                                         set before LMC initiates the sequence).
                                                         INIT_STATUS determines the chip-selects that assert
                                                         during refresh, ZQCS, and precharge power-down and
                                                         self-refresh entry/exit SEQUENCE's. */
	uint64_t mirrmask                     : 4;  /**< Mask determining which ranks are address-mirrored.
                                                         MIRRMASK<n> = 1 means Rank n addresses are mirrored
                                                         for 0 <= n <= 3
                                                         A mirrored read/write has these differences:
                                                          - DDR_BA<1> is swapped with DDR_BA<0>
                                                          - DDR_A<8> is swapped with DDR_A<7>
                                                          - DDR_A<6> is swapped with DDR_A<5>
                                                          - DDR_A<4> is swapped with DDR_A<3>
                                                         When RANK_ENA=0, MIRRMASK<1> and MIRRMASK<3> MBZ */
	uint64_t rankmask                     : 4;  /**< Mask to select rank to be leveled/initialized.
                                                         To write-level/read-level/initialize rank i, set RANKMASK<i>
                                                                         RANK_ENA=1               RANK_ENA=0
                                                           RANKMASK<0> = DIMM0_CS0                DIMM0_CS0
                                                           RANKMASK<1> = DIMM0_CS1                  MBZ
                                                           RANKMASK<2> = DIMM1_CS0                DIMM1_CS0
                                                           RANKMASK<3> = DIMM1_CS1                  MBZ
                                                         For read/write leveling, each rank has to be leveled separately,
                                                         so RANKMASK should only have one bit set.
                                                         RANKMASK is not used during self-refresh entry/exit and
                                                         precharge power-down entry/exit instruction sequences.
                                                         When RANK_ENA=0, RANKMASK<1> and RANKMASK<3> MBZ */
	uint64_t rank_ena                     : 1;  /**< RANK ena (for use with dual-rank DIMMs)
                                                         For dual-rank DIMMs, the rank_ena bit will enable
                                                         the drive of the CS*_L[1:0] and ODT_<1:0> pins differently based on the
                                                         (pbank_lsb-1) address bit.
                                                         Write 0 for SINGLE ranked DIMM's. */
	uint64_t sref_with_dll                : 1;  /**< Self-refresh entry/exit write MR1 and MR2
                                                         When set, self-refresh entry and exit instruction sequences
                                                         write MR1 and MR2 (in all ranks). (The writes occur before
                                                         self-refresh entry, and after self-refresh exit.)
                                                         When clear, self-refresh entry and exit instruction sequences
                                                         do not write any registers in the DDR3 parts. */
	uint64_t early_dqx                    : 1;  /**< Send DQx signals one CK cycle earlier for the case when
                                                         the shortest DQx lines have a larger delay than the CK line */
	uint64_t sequence                     : 3;  /**< Selects the sequence that LMC runs after a 0->1
                                                         transition on LMC*_CONFIG[INIT_START].
                                                         SEQUENCE=0=power-up/init:
                                                           - RANKMASK selects participating ranks (should be all ranks with attached DRAM)
                                                           - INIT_STATUS must equal RANKMASK
                                                           - DDR_CKE* signals activated (if they weren't already active)
                                                           - RDIMM register control words 0-15 will be written to RANKMASK-selected
                                                               RDIMM's when LMC(0)_CONTROL[RDIMM_ENA]=1 and corresponding
                                                               LMC*_DIMM_CTL[DIMM*_WMASK] bits are set. (Refer to LMC*_DIMM*_PARAMS and
                                                               LMC*_DIMM_CTL descriptions below for more details.)
                                                           - MR0, MR1, MR2, and MR3 will be written to selected ranks
                                                         SEQUENCE=1=read-leveling:
                                                           - RANKMASK selects the rank to be read-leveled
                                                           - MR3 written to selected rank
                                                         SEQUENCE=2=self-refresh entry:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - MR1 and MR2 will be written to selected ranks if SREF_WITH_DLL=1
                                                           - DDR_CKE* signals de-activated
                                                         SEQUENCE=3=self-refresh exit:
                                                           - INIT_STATUS must be set to indicate participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_CKE* signals activated
                                                           - MR0, MR1, MR2, and MR3 will be written to participating ranks if SREF_WITH_DLL=1
                                                         SEQUENCE=4=precharge power-down entry:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_CKE* signals de-activated
                                                         SEQUENCE=5=precharge power-down exit:
                                                           - INIT_STATUS selects participating ranks (should be all ranks with attached DRAM)
                                                           - DDR_CKE* signals activated
                                                         SEQUENCE=6=write-leveling:
                                                           - RANKMASK selects the rank to be write-leveled
                                                           - INIT_STATUS must indicate all ranks with attached DRAM
                                                           - MR1 and MR2 written to INIT_STATUS-selected ranks
                                                         SEQUENCE=7=illegal
                                                         Precharge power-down entry and exit SEQUENCE's may also
                                                         be automatically generated by the HW when IDLEPOWER!=0.
                                                         Self-refresh entry SEQUENCE's may also be automatically
                                                         generated by hardware upon a chip warm or soft reset
                                                         sequence when LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT] are set.
                                                         LMC writes the LMC*_MODEREG_PARAMS0 and LMC*_MODEREG_PARAMS1 CSR field values
                                                         to the Mode registers in the DRAM parts (i.e. MR0, MR1, MR2, and MR3) as part of some of these sequences.
                                                         Refer to the LMC*_MODEREG_PARAMS0 and LMC*_MODEREG_PARAMS1 descriptions for more details.
                                                         If there are two consecutive power-up/init's without
                                                         a DRESET assertion between them, LMC asserts DDR_CKE* as part of
                                                         the first power-up/init, and continues to assert DDR_CKE*
                                                         through the remainder of the first and the second power-up/init.
                                                         If DDR_CKE* deactivation and reactivation is needed for
                                                         a second power-up/init, a DRESET assertion is required
                                                         between the first and the second. */
	uint64_t ref_zqcs_int                 : 19; /**< Refresh & ZQCS interval represented in \#of 512 CK cycle
                                                         increments. A Refresh sequence is triggered when bits
                                                         [24:18] are equal to 0, and a ZQCS sequence is triggered
                                                         when [36:18] are equal to 0.
                                                         Program [24:18] to RND-DN(tREFI/clkPeriod/512)
                                                         Program [36:25] to RND-DN(ZQCS_Interval/clkPeriod/(512*128)). Note
                                                         that this value should always be greater than 32, to account for
                                                         resistor calibration delays.
                                                         000_00000000_00000000: RESERVED
                                                         Max Refresh interval = 127 * 512           = 65024 CKs
                                                         Max ZQCS interval    = (8*256*256-1) * 512 = 268434944 CKs ~ 335ms for a 800 MHz CK
                                                         LMC*_CONFIG[INIT_STATUS] determines which ranks receive
                                                         the REF / ZQCS. LMC does not send any refreshes / ZQCS's
                                                         when LMC*_CONFIG[INIT_STATUS]=0. */
	uint64_t reset                        : 1;  /**< Reset oneshot pulse for refresh counter,
                                                         and LMC*_OPS_CNT, LMC*_IFB_CNT, and LMC*_DCLK_CNT
                                                         CSR's. SW should write this to a one, then re-write
                                                         it to a zero to cause the reset. */
	uint64_t ecc_adr                      : 1;  /**< Include memory reference address in the ECC calculation
                                                         0=disabled, 1=enabled */
	uint64_t forcewrite                   : 4;  /**< Force the oldest outstanding write to complete after
                                                         having waited for 2^FORCEWRITE CK cycles.  0=disabled. */
	uint64_t idlepower                    : 3;  /**< Enter precharge power-down mode after the memory
                                                         controller has been idle for 2^(2+IDLEPOWER) CK cycles.
                                                         0=disabled.
                                                         This field should only be programmed after initialization.
                                                         LMC*_MODEREG_PARAMS0[PPD] determines whether the DRAM DLL
                                                         is disabled during the precharge power-down. */
	uint64_t pbank_lsb                    : 4;  /**< DIMM address bit select
                                                         Reverting to the explanation for ROW_LSB,
                                                         PBank_LSB would be Row_LSB bit + \#rowbits + \#rankbits
                                                         Decoding for pbank_lsb
                                                              - 0000:DIMM = mem_adr[28]    / rank = mem_adr[27] (if RANK_ENA)
                                                              - 0001:DIMM = mem_adr[29]    / rank = mem_adr[28]      "
                                                              - 0010:DIMM = mem_adr[30]    / rank = mem_adr[29]      "
                                                              - 0011:DIMM = mem_adr[31]    / rank = mem_adr[30]      "
                                                              - 0100:DIMM = mem_adr[32]    / rank = mem_adr[31]      "
                                                              - 0101:DIMM = mem_adr[33]    / rank = mem_adr[32]      "
                                                              - 0110:DIMM = mem_adr[34]    / rank = mem_adr[33]      "
                                                              - 0111:DIMM = 0              / rank = mem_adr[34]      "
                                                              - 1000-1111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16]
                                                         With rank_ena = 0, pbank_lsb = 2
                                                         With rank_ena = 1, pbank_lsb = 3 */
	uint64_t row_lsb                      : 3;  /**< Row Address bit select
                                                         Encoding used to determine which memory address
                                                         bit position represents the low order DDR ROW address.
                                                         The processor's memory address[34:7] needs to be
                                                         translated to DRAM addresses (bnk,row,col,rank and DIMM)
                                                         and that is a function of the following:
                                                         1. Datapath Width (64)
                                                         2. \# Banks (8)
                                                         3. \# Column Bits of the memory part - spec'd indirectly
                                                         by this register.
                                                         4. \# Row Bits of the memory part - spec'd indirectly
                                                         5. \# Ranks in a DIMM - spec'd by RANK_ENA
                                                         6. \# DIMM's in the system by the register below (PBANK_LSB).
                                                         Decoding for row_lsb
                                                              - 000: row_lsb = mem_adr[14]
                                                              - 001: row_lsb = mem_adr[15]
                                                              - 010: row_lsb = mem_adr[16]
                                                              - 011: row_lsb = mem_adr[17]
                                                              - 100: row_lsb = mem_adr[18]
                                                              - 101: row_lsb = mem_adr[19]
                                                              - 110: row_lsb = mem_adr[20]
                                                              - 111: RESERVED
                                                         For example, for a DIMM made of Samsung's k4b1g0846c-f7 1Gb (16M x 8 bit x 8 bank)
                                                         DDR3 parts, the column address width = 10, so with
                                                         10b of col, 3b of bus, 3b of bank, row_lsb = 16. So, row = mem_adr[29:16] */
	uint64_t ecc_ena                      : 1;  /**< ECC Enable: When set will enable the 8b ECC
                                                         check/correct logic. Should be 1 when used with DIMMs
                                                         with ECC. 0, otherwise.
                                                         When this mode is turned on, DQ[71:64]
                                                         on writes, will contain the ECC code generated for
                                                         the 64 bits of data which will
                                                         written in the memory and then later on reads, used
                                                         to check for Single bit error (which will be auto-
                                                         corrected) and Double Bit error (which will be
                                                         reported). When not turned on, DQ[71:64]
                                                         are driven to 0.  Please refer to SEC_ERR, DED_ERR,
                                                         LMC*_FADR, LMC*_SCRAMBLED_FADR and LMC*_ECC_SYND registers
                                                         for diagnostics information when there is an error. */
	uint64_t init_start                   : 1;  /**< A 0->1 transition starts the DDR memory sequence that is
                                                         selected by LMC*_CONFIG[SEQUENCE].  This register is a
                                                         oneshot and clears itself each time it is set. */
#else
	uint64_t init_start                   : 1;
	uint64_t ecc_ena                      : 1;
	uint64_t row_lsb                      : 3;
	uint64_t pbank_lsb                    : 4;
	uint64_t idlepower                    : 3;
	uint64_t forcewrite                   : 4;
	uint64_t ecc_adr                      : 1;
	uint64_t reset                        : 1;
	uint64_t ref_zqcs_int                 : 19;
	uint64_t sequence                     : 3;
	uint64_t early_dqx                    : 1;
	uint64_t sref_with_dll                : 1;
	uint64_t rank_ena                     : 1;
	uint64_t rankmask                     : 4;
	uint64_t mirrmask                     : 4;
	uint64_t init_status                  : 4;
	uint64_t early_unload_d0_r0           : 1;
	uint64_t early_unload_d0_r1           : 1;
	uint64_t early_unload_d1_r0           : 1;
	uint64_t early_unload_d1_r1           : 1;
	uint64_t scrz                         : 1;
	uint64_t reserved_60_63               : 4;
#endif
	} cn66xx;
	struct cvmx_lmcx_config_cn63xx        cn68xx;
	struct cvmx_lmcx_config_cn63xx        cn68xxp1;
	struct cvmx_lmcx_config_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_63_63               : 1;
	uint64_t bg2_enable                   : 1;  /**< BG2 pin is active for DDR4 mode. Only has an effect when LMC(0..0)_CONFIG[MODEDDR4] = 1.
                                                         Typically only cleared for DDR4 *16 devices, where there is no BG2 pin on the device. */
	uint64_t mode_x4dev                   : 1;  /**< Always reads as 0 for CN70XX devices, there is no x4 device support. */
	uint64_t mode32b                      : 1;  /**< Always reads as 1 for CN70XX devices, only 32b mode is supported. */
	uint64_t scrz                         : 1;  /**< Hide LMC(0..0)_SCRAMBLE_CFG0 and LMC(0..0)_SCRAMBLE_CFG1 when set. */
	uint64_t early_unload_d1_r1           : 1;  /**< Reserved, MBZ.  INTERNAL:  When set, unload the PHY silo one cycle early for
                                                         Rank 3 reads. The recommended EARLY_UNLOAD_D1_R1 value is 0.  Not used in
                                                         CN70XX/CN71XX. */
	uint64_t early_unload_d1_r0           : 1;  /**< Reserved, MBZ.  INTERNAL:  When set, unload the PHY silo one cycle early for
                                                         Rank 2 reads.  The recommended EARLY_UNLOAD_D1_RO value is 0.  Not used in
                                                         CN70XX/CN71XX. */
	uint64_t early_unload_d0_r1           : 1;  /**< Reserved, MBZ.  INTERNAL:  When set, unload the PHY silo one cycle early for
                                                         Rank 1 reads.  The recommended EARLY_UNLOAD_D0_R1 value is 0. */
	uint64_t early_unload_d0_r0           : 1;  /**< Reserved, MBZ.  INTERNAL:  When set, unload the PHY silo one cycle early for
                                                         Rank 0 reads.  The recommended EARLY_UNLOAD_D0_R0 value is 0. */
	uint64_t init_status                  : 4;  /**< Indicates status of initialization. INIT_STATUS[n] = 1 implies rank n has been
                                                         initialized.
                                                         Software must set necessary RANKMASK bits before executing the initialization sequence
                                                         using LMC(0..0)_SEQ_CTL. If the rank has been selected for init with the RANKMASK bits,
                                                         the INIT_STATUS bits will be set after successful initialization and after self-refresh
                                                         exit. INIT_STATUS determines the chip-selects that assert during refresh, ZQCS, precharge
                                                         power-down entry/exit, and self-refresh entry SEQ_SEL's.  For CN70XX/CN71XX, only bits
                                                         <1:0>
                                                         corresponding to 2 ranks should ever be set. */
	uint64_t mirrmask                     : 4;  /**< "Mask determining which ranks are address-mirrored.
                                                         MIRRMASK<n> = 1 means Rank n addresses are mirrored for
                                                         0 <= n <= 3.
                                                         In DDR3, a mirrored read/write operation has the following differences:
                                                         DDR#_BA<1> is swapped with DDR#_BA<0>;
                                                         DDR#_A<8> is swapped with DDR#_A<7>;
                                                         DDR#_A<6> is swapped with DDR#_A<5>;
                                                         DDR#_A<4> is swapped with DDR#_A<3>.
                                                         For CN70XX/CN71XX, MIRRMASK<3:2> MBZ.
                                                         When RANK_ENA = 0, MIRRMASK<1> MBZ."
                                                         INTERNAL:
                                                         In DDR4, a mirrored read/write operation has the following differences:
                                                         DDR#_BG<1> is swapped with DDR#_BG<0>;
                                                         DDR#_BA<1> is swapped with DDR#_BA<0>;
                                                         DDR#_A<13> is swapped with DDR#_A<11>;
                                                         DDR#_A<8> is swapped with DDR#_A<7>;
                                                         DDR#_A<6> is swapped with DDR#_A<5>;
                                                         DDR#_A<4> is swapped with DDR#_A<3>.
                                                         For CN70XX, MIRRMASK<3:2> MBZ.
                                                         When RANK_ENA = 0, MIRRMASK<1> MBZ." */
	uint64_t rankmask                     : 4;  /**< Mask to select rank to be leveled/initialized. To write-level/read-level/initialize rank
                                                         i, set RANKMASK< i>
                                                                       RANK_ENA = 1 RANK_ENA = 0
                                                         RANKMASK<0> = DIMM0_CS0    DIMM0_CS0
                                                         RANKMASK<1> = DIMM0_CS1    MBZ
                                                         RANKMASK<2> = MBZ          MBZ
                                                         RANKMASK<3> = MBZ          MBZ
                                                         For read/write leveling, each rank has to be leveled separately, so RANKMASK should only
                                                         have one bit set. RANKMASK is not used during self-refresh entry/exit and precharge power-
                                                         down entry/exit instruction sequences. For CN70XX/CN71XX, RANKMASK<3:2> MBZ.  When
                                                         RANK_ENA = 0,
                                                         RANKMASK<1> MBZ. */
	uint64_t rank_ena                     : 1;  /**< "RANK enable (for use with dual-rank DIMMs).
                                                         * For dual-rank DIMMs, the RANK_ENA bit will enable the drive of the DDR_CS*_L and
                                                         ODT_<1:0> pins differently based on the (PBANK_LSB - 1) address bit.
                                                         * Write 0 for SINGLE ranked DIMMs." */
	uint64_t sref_with_dll                : 1;  /**< Self-refresh entry/exit write mode registers. When set, self-refresh entry sequence writes
                                                         MR2 and MR1 (in this order, in all ranks), and self-refresh exit sequence writes MR1, MR0,
                                                         MR2, and MR3 (in this order, for all ranks). The write operations occur before self-
                                                         refresh entry, and after self-refresh exit. When clear, self-refresh entry and exit
                                                         instruction sequences do not write any mode registers in the DDR3/4 parts. */
	uint64_t early_dqx                    : 1;  /**< Set this bit to send DQx signals one CK cycle earlier for the case when the shortest DQx
                                                         lines have a larger delay than the CK line. */
	uint64_t ref_zqcs_int                 : 22; /**< Refresh interval is represented in number of 512 CK cycle increments. ZQCS interval is
                                                         represented in a number of refresh intervals. A refresh sequence is triggered when bits
                                                         <24:18> are equal to 0x0, and a ZQCS sequence is triggered when <39:18> are equal to 0x0.
                                                         The ZQCS timer only decrements when the refresh timer is 0.
                                                         Program <24:18> to RND-DN(TREFI/clkPeriod/512).
                                                         A value of 0 in bits <24:18> will effectively turn off refresh.
                                                         Program <36:25> to (RND-DN(ZQCS_Period / Refresh_Period) - 1), where Refresh_Period is the
                                                         effective period programmed in bits <24:18>. Note that this value should always be greater
                                                         than 32, to account for resistor calibration delays.
                                                         000_00000000_0000000: Reserved
                                                         Max Refresh interval = 127 * 512= 65024 CK cycles
                                                         Max ZQCS interval = 32768 * 127 * 512 = 2130706432 CK cycles
                                                         If refresh interval is programmed to ~8us, max ZQCS interval is ~262ms, or ~4 ZQCS
                                                         operations per second.
                                                         LMC(0..0)_CONFIG[INIT_STATUS] determines which ranks receive the REF / ZQCS. LMC does not
                                                         send any refreshes / ZQCS's when LMC(0..0)_CONFIG[INIT_STATUS]=0. */
	uint64_t reset                        : 1;  /**< Reset one-shot pulse for LMC(0..0)_OPS_CNT, LMC(0..0)_IFB_CNT, and LMC(0..0)_DCLK_CNT
                                                         CSRs.
                                                         To cause the reset, software writes this to a 1, then rewrites it to a 0. */
	uint64_t ecc_adr                      : 1;  /**< Include memory reference address in the ECC calculation.
                                                         0 = disabled, 1 = enabled. */
	uint64_t forcewrite                   : 4;  /**< Force the oldest outstanding write to complete after having waited for 2^FORCEWRITE CK
                                                         cycles. 0 = disabled. */
	uint64_t idlepower                    : 3;  /**< Enter precharge power-down mode after the memory controller has been idle for
                                                         2^(2+IDLEPOWER) CK cycles. 0 = disabled.
                                                         This field should only be programmed after initialization.
                                                         LMC(0..0)_MODEREG_PARAMS0[PPD] determines whether the DRAM DLL is disabled during the
                                                         precharge power-down. */
	uint64_t pbank_lsb                    : 4;  /**< "DIMM address bit select. Reverting to the explanation for ROW_LSB, PBANK_LSB would be:
                                                         ROW_LSB bit + \#rowbits + \#rankbits
                                                         Decoding for PBANK_LSB:
                                                         0x0: DIMM = mem_adr<28>; if RANK_ENA=1, rank = mem_adr<27>
                                                         0x1: DIMM = mem_adr<29>; if RANK_ENA=1, rank = mem_adr<28>
                                                         0x2: DIMM = mem_adr<30>; if RANK_ENA=1, rank = mem_adr<29>
                                                         0x3: DIMM = mem_adr<31>; if RANK_ENA=1, rank = mem_adr<30>
                                                         0x4: DIMM = mem_adr<32>; if RANK_ENA=1, rank = mem_adr<31>
                                                         0x5: DIMM = mem_adr<33>; if RANK_ENA=1, rank = mem_adr<32>
                                                         0x6: DIMM = mem_adr<34>; if RANK_ENA=1, rank = mem_adr<33>
                                                         0x7: DIMM = mem_adr<35>; if RANK_ENA=1, rank = mem_adr<34>
                                                         0x8: DIMM = mem_adr<36>; if RANK_ENA=1, rank = mem_adr<35>
                                                         0x9: DIMM = 0; if RANK_ENA=1, rank = mem_adr<36>
                                                         0xA-0xF: reserved
                                                         For example, for a DIMM made of Samsung's K4B1G0846C-F7 1Gb (16M * 8 bit * 8 bank) DDR3
                                                         parts, the column address width = 10, so with 10b of col, 3b of bus, 3b of bank, ROW_LSB =
                                                         16. So, row = mem_adr<29:16>.
                                                         With RANK_ENA = 0, PBANK_LSB = 2.
                                                         With RANK_ENA = 1, PBANK_LSB = 3." */
	uint64_t row_lsb                      : 3;  /**< "Row address bit select.
                                                         Encoding used to determine which memory address bit position represents the low order DDR
                                                         ROW address. The processor's memory address<34:7> needs to be translated to DRAM addresses
                                                         (bnk,row,col,rank and DIMM) and that is a function of the following:
                                                         Datapath width (32)
                                                         * Datapath width (64).
                                                         * Number of banks (8).
                                                         * Number of  column bits of the memory part--specified indirectly by this register.
                                                         * Number of row bits of the memory part--specified indirectly by PBANK_LSB.
                                                         * Number of ranks in a DIMM--specified by RANK_ENA.
                                                         * Number of DIMMs in the system by the register below (PBANK_LSB).
                                                         Col Address starts from mem_addr[2] for 32b (4Bytes) DQ width. ROW_LSB is mem_adr[14] for
                                                         32b mode. Therefore, the ROW_LSB parameter should be set to 000 (32b).
                                                         Decoding for row_lsb:
                                                         Mem address  Mem address
                                                         Value and corresponding bit that is LSB:
                                                         000 <14>. 100 <18>.
                                                         001 <15>. 101 <19>.
                                                         010 <16>. 110 <20>.
                                                         011 <17>. 111 Reserved.
                                                         For example, for a DIMM made of Samsung's K4B1G0846C-F7 1GB (16M * 8 bit * 8 bank) DDR3
                                                         parts, the column address width = 10, so with 10b of col, 2b of bus, 3b of bank, ROW_LSB =
                                                         15. So, row = mem_adr<28:15>, and ROW_LSB parameter should be set to 001.
                                                         Refer to Cache-block Read Transaction Example." */
	uint64_t ecc_ena                      : 1;  /**< ECC enable. When set, enables the 8b ECC check/correct logic. Should be 1 when used with
                                                         DIMMs with ECC; 0, otherwise.
                                                         When this mode is turned on, DQ<35:32> on write operations contains the ECC code generated
                                                         for the 64 bits of data which will be written in the memory. Later on read operations,
                                                         will be used to check for single-bit error (which will be auto-corrected) and double-bit
                                                         error (which will be reported).
                                                         When not turned on, DQ<35:32> are driven to 0. Please refer to SEC_ERR, DED_ERR,
                                                         LMC(0..0)_FADR, and LMC(0..0)_ECC_SYND registers for diagnostics information when there is
                                                         an error. */
	uint64_t reserved_0_0                 : 1;
#else
	uint64_t reserved_0_0                 : 1;
	uint64_t ecc_ena                      : 1;
	uint64_t row_lsb                      : 3;
	uint64_t pbank_lsb                    : 4;
	uint64_t idlepower                    : 3;
	uint64_t forcewrite                   : 4;
	uint64_t ecc_adr                      : 1;
	uint64_t reset                        : 1;
	uint64_t ref_zqcs_int                 : 22;
	uint64_t early_dqx                    : 1;
	uint64_t sref_with_dll                : 1;
	uint64_t rank_ena                     : 1;
	uint64_t rankmask                     : 4;
	uint64_t mirrmask                     : 4;
	uint64_t init_status                  : 4;
	uint64_t early_unload_d0_r0           : 1;
	uint64_t early_unload_d0_r1           : 1;
	uint64_t early_unload_d1_r0           : 1;
	uint64_t early_unload_d1_r1           : 1;
	uint64_t scrz                         : 1;
	uint64_t mode32b                      : 1;
	uint64_t mode_x4dev                   : 1;
	uint64_t bg2_enable                   : 1;
	uint64_t reserved_63_63               : 1;
#endif
	} cn70xx;
	struct cvmx_lmcx_config_cn70xx        cn78xx;
	struct cvmx_lmcx_config_cn61xx        cnf71xx;
};
typedef union cvmx_lmcx_config cvmx_lmcx_config_t;

/**
 * cvmx_lmc#_control
 *
 * LMC_CONTROL = LMC Control
 * This register is an assortment of various control fields needed by the memory controller
 */
union cvmx_lmcx_control {
	uint64_t u64;
	struct cvmx_lmcx_control_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t scramble_ena                 : 1;  /**< When set, will enable the scramble/descramble logic */
	uint64_t thrcnt                       : 12; /**< Fine count. */
	uint64_t persub                       : 8;  /**< Offset for DFA rate-matching. */
	uint64_t thrmax                       : 4;  /**< Fine rate matching max bucket size. In conjunction with the coarse rate matching logic,
                                                         the fine rate matching logic gives software the ability to prioritize DFA reads over L2C
                                                         writes. Higher PERSUB values result in a lower DFA read bandwidth.
                                                         0x0 = Reserved */
	uint64_t crm_cnt                      : 5;  /**< Coarse count. */
	uint64_t crm_thr                      : 5;  /**< Coarse rate matching threshold. */
	uint64_t crm_max                      : 5;  /**< Coarse rate matching max bucket size. The coarse rate matching logic is used to control
                                                         the bandwidth allocated to DFA reads. CRM_MAX is subdivided into two regions with DFA
                                                         reads being preferred over LMC reads/writes when CRM_CNT < CRM_THR. CRM_CNT increments by
                                                         1 when a DFA read is slotted and by 2 when a LMC read/write is slotted, and rolls over
                                                         when CRM_MAX is reached.
                                                         0x0 = Reserved */
	uint64_t rodt_bprch                   : 1;  /**< When set, the turn-off time for the ODT pin during a
                                                         RD cmd is delayed an additional CK cycle. */
	uint64_t wodt_bprch                   : 1;  /**< When set, the turn-off time for the ODT pin during a
                                                         WR cmd is delayed an additional CK cycle. */
	uint64_t bprch                        : 2;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the default DDR_DQ/DQS drivers is delayed an additional BPRCH
                                                         CK cycles.
                                                         00 = 0 CKs
                                                         01 = 1 CKs
                                                         10 = 2 CKs
                                                         11 = 3 CKs */
	uint64_t ext_zqcs_dis                 : 1;  /**< Disable (external) auto-zqcs calibration
                                                         When clear, LMC runs external ZQ calibration
                                                         every LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t int_zqcs_dis                 : 1;  /**< Disable (internal) auto-zqcs calibration
                                                         When clear, LMC runs internal ZQ calibration
                                                         every LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t auto_dclkdis                 : 1;  /**< When 1, LMC will automatically shut off its internal
                                                         clock to conserve power when there is no traffic. Note
                                                         that this has no effect on the DDR3 PHY and pads clocks. */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                          bank[2:0]=address[9:7] ^ address[14:12]
                                                         else
                                                          bank[2:0]=address[9:7] */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         forcing reads to interrupt. */
	uint64_t nxm_write_en                 : 1;  /**< NXM Write mode
                                                         When clear, LMC discards writes to addresses that don't
                                                         exist in the DRAM (as defined by LMC*_NXM configuration).
                                                         When set, LMC completes writes to addresses that don't
                                                         exist in the DRAM at an aliased address. */
	uint64_t elev_prio_dis                : 1;  /**< Disable elevate priority logic.
                                                         When set, writes are sent in
                                                         regardless of priority information from L2C. */
	uint64_t inorder_wr                   : 1;  /**< Send writes in order(regardless of priority) */
	uint64_t inorder_rd                   : 1;  /**< Send reads in order (regardless of priority) */
	uint64_t throttle_wr                  : 1;  /**< When set, use at most one IFB for writes */
	uint64_t throttle_rd                  : 1;  /**< When set, use at most one IFB for reads */
	uint64_t fprch2                       : 2;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the default DDR_DQ/DQS drivers is FPRCH2 CKs earlier.
                                                         00 = 0 CKs
                                                         01 = 1 CKs
                                                         10 = 2 CKs
                                                         11 = RESERVED */
	uint64_t pocas                        : 1;  /**< Enable the Posted CAS feature of DDR3.
                                                         This bit must be set whenever LMC*_MODEREG_PARAMS0[AL]!=0,
                                                         and clear otherwise. */
	uint64_t ddr2t                        : 1;  /**< Turn on the DDR 2T mode. 2 CK cycle window for CMD and
                                                         address. This mode helps relieve setup time pressure
                                                         on the Address and command bus which nominally have
                                                         a very large fanout. Please refer to Micron's tech
                                                         note tn_47_01 titled "DDR2-533 Memory Design Guide
                                                         for Two Dimm Unbuffered Systems" for physical details. */
	uint64_t bwcnt                        : 1;  /**< Bus utilization counter Clear.
                                                         Clears the LMC*_OPS_CNT, LMC*_IFB_CNT, and
                                                         LMC*_DCLK_CNT registers. SW should first write this
                                                         field to a one, then write this field to a zero to
                                                         clear the CSR's. */
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require address and
                                                         control bits to be registered in the controller. */
#else
	uint64_t rdimm_ena                    : 1;
	uint64_t bwcnt                        : 1;
	uint64_t ddr2t                        : 1;
	uint64_t pocas                        : 1;
	uint64_t fprch2                       : 2;
	uint64_t throttle_rd                  : 1;
	uint64_t throttle_wr                  : 1;
	uint64_t inorder_rd                   : 1;
	uint64_t inorder_wr                   : 1;
	uint64_t elev_prio_dis                : 1;
	uint64_t nxm_write_en                 : 1;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t auto_dclkdis                 : 1;
	uint64_t int_zqcs_dis                 : 1;
	uint64_t ext_zqcs_dis                 : 1;
	uint64_t bprch                        : 2;
	uint64_t wodt_bprch                   : 1;
	uint64_t rodt_bprch                   : 1;
	uint64_t crm_max                      : 5;
	uint64_t crm_thr                      : 5;
	uint64_t crm_cnt                      : 5;
	uint64_t thrmax                       : 4;
	uint64_t persub                       : 8;
	uint64_t thrcnt                       : 12;
	uint64_t scramble_ena                 : 1;
#endif
	} s;
	struct cvmx_lmcx_control_s            cn61xx;
	struct cvmx_lmcx_control_cn63xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_24_63               : 40;
	uint64_t rodt_bprch                   : 1;  /**< When set, the turn-off time for the ODT pin during a
                                                         RD cmd is delayed an additional CK cycle. */
	uint64_t wodt_bprch                   : 1;  /**< When set, the turn-off time for the ODT pin during a
                                                         WR cmd is delayed an additional CK cycle. */
	uint64_t bprch                        : 2;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the default DDR_DQ/DQS drivers is delayed an additional BPRCH
                                                         CK cycles.
                                                         00 = 0 CKs
                                                         01 = 1 CKs
                                                         10 = 2 CKs
                                                         11 = 3 CKs */
	uint64_t ext_zqcs_dis                 : 1;  /**< Disable (external) auto-zqcs calibration
                                                         When clear, LMC runs external ZQ calibration
                                                         every LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t int_zqcs_dis                 : 1;  /**< Disable (internal) auto-zqcs calibration
                                                         When clear, LMC runs internal ZQ calibration
                                                         every LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t auto_dclkdis                 : 1;  /**< When 1, LMC will automatically shut off its internal
                                                         clock to conserve power when there is no traffic. Note
                                                         that this has no effect on the DDR3 PHY and pads clocks. */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                          bank[2:0]=address[9:7] ^ address[14:12]
                                                         else
                                                          bank[2:0]=address[9:7] */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         forcing reads to interrupt. */
	uint64_t nxm_write_en                 : 1;  /**< NXM Write mode
                                                         When clear, LMC discards writes to addresses that don't
                                                         exist in the DRAM (as defined by LMC*_NXM configuration).
                                                         When set, LMC completes writes to addresses that don't
                                                         exist in the DRAM at an aliased address. */
	uint64_t elev_prio_dis                : 1;  /**< Disable elevate priority logic.
                                                         When set, writes are sent in
                                                         regardless of priority information from L2C. */
	uint64_t inorder_wr                   : 1;  /**< Send writes in order(regardless of priority) */
	uint64_t inorder_rd                   : 1;  /**< Send reads in order (regardless of priority) */
	uint64_t throttle_wr                  : 1;  /**< When set, use at most one IFB for writes */
	uint64_t throttle_rd                  : 1;  /**< When set, use at most one IFB for reads */
	uint64_t fprch2                       : 2;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the default DDR_DQ/DQS drivers is FPRCH2 CKs earlier.
                                                         00 = 0 CKs
                                                         01 = 1 CKs
                                                         10 = 2 CKs
                                                         11 = RESERVED */
	uint64_t pocas                        : 1;  /**< Enable the Posted CAS feature of DDR3.
                                                         This bit must be set whenever LMC*_MODEREG_PARAMS0[AL]!=0,
                                                         and clear otherwise. */
	uint64_t ddr2t                        : 1;  /**< Turn on the DDR 2T mode. 2 CK cycle window for CMD and
                                                         address. This mode helps relieve setup time pressure
                                                         on the Address and command bus which nominally have
                                                         a very large fanout. Please refer to Micron's tech
                                                         note tn_47_01 titled "DDR2-533 Memory Design Guide
                                                         for Two Dimm Unbuffered Systems" for physical details. */
	uint64_t bwcnt                        : 1;  /**< Bus utilization counter Clear.
                                                         Clears the LMC*_OPS_CNT, LMC*_IFB_CNT, and
                                                         LMC*_DCLK_CNT registers. SW should first write this
                                                         field to a one, then write this field to a zero to
                                                         clear the CSR's. */
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require address and
                                                         control bits to be registered in the controller. */
#else
	uint64_t rdimm_ena                    : 1;
	uint64_t bwcnt                        : 1;
	uint64_t ddr2t                        : 1;
	uint64_t pocas                        : 1;
	uint64_t fprch2                       : 2;
	uint64_t throttle_rd                  : 1;
	uint64_t throttle_wr                  : 1;
	uint64_t inorder_rd                   : 1;
	uint64_t inorder_wr                   : 1;
	uint64_t elev_prio_dis                : 1;
	uint64_t nxm_write_en                 : 1;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t auto_dclkdis                 : 1;
	uint64_t int_zqcs_dis                 : 1;
	uint64_t ext_zqcs_dis                 : 1;
	uint64_t bprch                        : 2;
	uint64_t wodt_bprch                   : 1;
	uint64_t rodt_bprch                   : 1;
	uint64_t reserved_24_63               : 40;
#endif
	} cn63xx;
	struct cvmx_lmcx_control_cn63xx       cn63xxp1;
	struct cvmx_lmcx_control_cn66xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t scramble_ena                 : 1;  /**< When set, will enable the scramble/descramble logic */
	uint64_t reserved_24_62               : 39;
	uint64_t rodt_bprch                   : 1;  /**< When set, the turn-off time for the ODT pin during a
                                                         RD cmd is delayed an additional CK cycle. */
	uint64_t wodt_bprch                   : 1;  /**< When set, the turn-off time for the ODT pin during a
                                                         WR cmd is delayed an additional CK cycle. */
	uint64_t bprch                        : 2;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the default DDR_DQ/DQS drivers is delayed an additional BPRCH
                                                         CK cycles.
                                                         00 = 0 CKs
                                                         01 = 1 CKs
                                                         10 = 2 CKs
                                                         11 = 3 CKs */
	uint64_t ext_zqcs_dis                 : 1;  /**< Disable (external) auto-zqcs calibration
                                                         When clear, LMC runs external ZQ calibration
                                                         every LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t int_zqcs_dis                 : 1;  /**< Disable (internal) auto-zqcs calibration
                                                         When clear, LMC runs internal ZQ calibration
                                                         every LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t auto_dclkdis                 : 1;  /**< When 1, LMC will automatically shut off its internal
                                                         clock to conserve power when there is no traffic. Note
                                                         that this has no effect on the DDR3 PHY and pads clocks. */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                          bank[2:0]=address[9:7] ^ address[14:12]
                                                         else
                                                          bank[2:0]=address[9:7] */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         forcing reads to interrupt. */
	uint64_t nxm_write_en                 : 1;  /**< NXM Write mode
                                                         When clear, LMC discards writes to addresses that don't
                                                         exist in the DRAM (as defined by LMC*_NXM configuration).
                                                         When set, LMC completes writes to addresses that don't
                                                         exist in the DRAM at an aliased address. */
	uint64_t elev_prio_dis                : 1;  /**< Disable elevate priority logic.
                                                         When set, writes are sent in
                                                         regardless of priority information from L2C. */
	uint64_t inorder_wr                   : 1;  /**< Send writes in order(regardless of priority) */
	uint64_t inorder_rd                   : 1;  /**< Send reads in order (regardless of priority) */
	uint64_t throttle_wr                  : 1;  /**< When set, use at most one IFB for writes */
	uint64_t throttle_rd                  : 1;  /**< When set, use at most one IFB for reads */
	uint64_t fprch2                       : 2;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the default DDR_DQ/DQS drivers is FPRCH2 CKs earlier.
                                                         00 = 0 CKs
                                                         01 = 1 CKs
                                                         10 = 2 CKs
                                                         11 = RESERVED */
	uint64_t pocas                        : 1;  /**< Enable the Posted CAS feature of DDR3.
                                                         This bit must be set whenever LMC*_MODEREG_PARAMS0[AL]!=0,
                                                         and clear otherwise. */
	uint64_t ddr2t                        : 1;  /**< Turn on the DDR 2T mode. 2 CK cycle window for CMD and
                                                         address. This mode helps relieve setup time pressure
                                                         on the Address and command bus which nominally have
                                                         a very large fanout. Please refer to Micron's tech
                                                         note tn_47_01 titled "DDR2-533 Memory Design Guide
                                                         for Two Dimm Unbuffered Systems" for physical details. */
	uint64_t bwcnt                        : 1;  /**< Bus utilization counter Clear.
                                                         Clears the LMC*_OPS_CNT, LMC*_IFB_CNT, and
                                                         LMC*_DCLK_CNT registers. SW should first write this
                                                         field to a one, then write this field to a zero to
                                                         clear the CSR's. */
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require address and
                                                         control bits to be registered in the controller. */
#else
	uint64_t rdimm_ena                    : 1;
	uint64_t bwcnt                        : 1;
	uint64_t ddr2t                        : 1;
	uint64_t pocas                        : 1;
	uint64_t fprch2                       : 2;
	uint64_t throttle_rd                  : 1;
	uint64_t throttle_wr                  : 1;
	uint64_t inorder_rd                   : 1;
	uint64_t inorder_wr                   : 1;
	uint64_t elev_prio_dis                : 1;
	uint64_t nxm_write_en                 : 1;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t auto_dclkdis                 : 1;
	uint64_t int_zqcs_dis                 : 1;
	uint64_t ext_zqcs_dis                 : 1;
	uint64_t bprch                        : 2;
	uint64_t wodt_bprch                   : 1;
	uint64_t rodt_bprch                   : 1;
	uint64_t reserved_24_62               : 39;
	uint64_t scramble_ena                 : 1;
#endif
	} cn66xx;
	struct cvmx_lmcx_control_cn68xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_63_63               : 1;
	uint64_t thrcnt                       : 12; /**< Fine Count */
	uint64_t persub                       : 8;  /**< Offset for DFA rate-matching */
	uint64_t thrmax                       : 4;  /**< Fine Rate Matching Max Bucket Size
                                                         0 = Reserved
                                                         In conjunction with the Coarse Rate Matching Logic, the Fine Rate
                                                         Matching Logic gives SW the ability to prioritize DFA Rds over
                                                         L2C Writes. Higher PERSUB values result in a lower DFA Rd
                                                         bandwidth. */
	uint64_t crm_cnt                      : 5;  /**< Coarse Count */
	uint64_t crm_thr                      : 5;  /**< Coarse Rate Matching Threshold */
	uint64_t crm_max                      : 5;  /**< Coarse Rate Matching Max Bucket Size
                                                         0 = Reserved
                                                         The Coarse Rate Matching Logic is used to control the bandwidth
                                                         allocated to DFA Rds. CRM_MAX is subdivided into two regions
                                                         with DFA Rds being preferred over LMC Rd/Wrs when
                                                         CRM_CNT < CRM_THR. CRM_CNT increments by 1 when a DFA Rd is
                                                         slotted and by 2 when a LMC Rd/Wr is slotted, and rolls over
                                                         when CRM_MAX is reached. */
	uint64_t rodt_bprch                   : 1;  /**< When set, the turn-off time for the ODT pin during a
                                                         RD cmd is delayed an additional CK cycle. */
	uint64_t wodt_bprch                   : 1;  /**< When set, the turn-off time for the ODT pin during a
                                                         WR cmd is delayed an additional CK cycle. */
	uint64_t bprch                        : 2;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the default DDR_DQ/DQS drivers is delayed an additional BPRCH
                                                         CK cycles.
                                                         00 = 0 CKs
                                                         01 = 1 CKs
                                                         10 = 2 CKs
                                                         11 = 3 CKs */
	uint64_t ext_zqcs_dis                 : 1;  /**< Disable (external) auto-zqcs calibration
                                                         When clear, LMC runs external ZQ calibration
                                                         every LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t int_zqcs_dis                 : 1;  /**< Disable (internal) auto-zqcs calibration
                                                         When clear, LMC runs internal ZQ calibration
                                                         every LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t auto_dclkdis                 : 1;  /**< When 1, LMC will automatically shut off its internal
                                                         clock to conserve power when there is no traffic. Note
                                                         that this has no effect on the DDR3 PHY and pads clocks. */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                          bank[2:0]=address[9:7] ^ address[14:12]
                                                         else
                                                          bank[2:0]=address[9:7] */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         forcing reads to interrupt. */
	uint64_t nxm_write_en                 : 1;  /**< NXM Write mode
                                                         When clear, LMC discards writes to addresses that don't
                                                         exist in the DRAM (as defined by LMC*_NXM configuration).
                                                         When set, LMC completes writes to addresses that don't
                                                         exist in the DRAM at an aliased address. */
	uint64_t elev_prio_dis                : 1;  /**< Disable elevate priority logic.
                                                         When set, writes are sent in
                                                         regardless of priority information from L2C. */
	uint64_t inorder_wr                   : 1;  /**< Send writes in order(regardless of priority) */
	uint64_t inorder_rd                   : 1;  /**< Send reads in order (regardless of priority) */
	uint64_t throttle_wr                  : 1;  /**< When set, use at most one IFB for writes */
	uint64_t throttle_rd                  : 1;  /**< When set, use at most one IFB for reads */
	uint64_t fprch2                       : 2;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the default DDR_DQ/DQS drivers is FPRCH2 CKs earlier.
                                                         00 = 0 CKs
                                                         01 = 1 CKs
                                                         10 = 2 CKs
                                                         11 = RESERVED */
	uint64_t pocas                        : 1;  /**< Enable the Posted CAS feature of DDR3.
                                                         This bit must be set whenever LMC*_MODEREG_PARAMS0[AL]!=0,
                                                         and clear otherwise. */
	uint64_t ddr2t                        : 1;  /**< Turn on the DDR 2T mode. 2 CK cycle window for CMD and
                                                         address. This mode helps relieve setup time pressure
                                                         on the Address and command bus which nominally have
                                                         a very large fanout. Please refer to Micron's tech
                                                         note tn_47_01 titled "DDR2-533 Memory Design Guide
                                                         for Two Dimm Unbuffered Systems" for physical details. */
	uint64_t bwcnt                        : 1;  /**< Bus utilization counter Clear.
                                                         Clears the LMC*_OPS_CNT, LMC*_IFB_CNT, and
                                                         LMC*_DCLK_CNT registers. SW should first write this
                                                         field to a one, then write this field to a zero to
                                                         clear the CSR's. */
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require address and
                                                         control bits to be registered in the controller. */
#else
	uint64_t rdimm_ena                    : 1;
	uint64_t bwcnt                        : 1;
	uint64_t ddr2t                        : 1;
	uint64_t pocas                        : 1;
	uint64_t fprch2                       : 2;
	uint64_t throttle_rd                  : 1;
	uint64_t throttle_wr                  : 1;
	uint64_t inorder_rd                   : 1;
	uint64_t inorder_wr                   : 1;
	uint64_t elev_prio_dis                : 1;
	uint64_t nxm_write_en                 : 1;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t auto_dclkdis                 : 1;
	uint64_t int_zqcs_dis                 : 1;
	uint64_t ext_zqcs_dis                 : 1;
	uint64_t bprch                        : 2;
	uint64_t wodt_bprch                   : 1;
	uint64_t rodt_bprch                   : 1;
	uint64_t crm_max                      : 5;
	uint64_t crm_thr                      : 5;
	uint64_t crm_cnt                      : 5;
	uint64_t thrmax                       : 4;
	uint64_t persub                       : 8;
	uint64_t thrcnt                       : 12;
	uint64_t reserved_63_63               : 1;
#endif
	} cn68xx;
	struct cvmx_lmcx_control_cn68xx       cn68xxp1;
	struct cvmx_lmcx_control_s            cn70xx;
	struct cvmx_lmcx_control_s            cn78xx;
	struct cvmx_lmcx_control_cn66xx       cnf71xx;
};
typedef union cvmx_lmcx_control cvmx_lmcx_control_t;

/**
 * cvmx_lmc#_ctl
 *
 * LMC_CTL = LMC Control
 * This register is an assortment of various control fields needed by the memory controller
 */
union cvmx_lmcx_ctl {
	uint64_t u64;
	struct cvmx_lmcx_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ddr__nctl                    : 4;  /**< DDR nctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pulldns. */
	uint64_t ddr__pctl                    : 4;  /**< DDR pctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pullup. */
	uint64_t slow_scf                     : 1;  /**< Should be cleared to zero */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                           bank[n:0]=address[n+7:7] ^ address[n+7+5:7+5]
                                                         else
                                                           bank[n:0]=address[n+7:7]
                                                         where n=1 for a 4 bank part and n=2 for an 8 bank part */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         allowing reads to interrupt. */
	uint64_t pll_div2                     : 1;  /**< PLL Div2. */
	uint64_t pll_bypass                   : 1;  /**< PLL Bypass. */
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require Write
                                                         data to be registered in the controller. */
	uint64_t r2r_slot                     : 1;  /**< R2R Slot Enable: When set, all read-to-read trans
                                                         will slot an additional 1 cycle data bus bubble to
                                                         avoid DQ/DQS bus contention. This is only a CYA bit,
                                                         in case the "built-in" DIMM and RANK crossing logic
                                                         which should auto-detect and perfectly slot
                                                         read-to-reads to the same DIMM/RANK. */
	uint64_t inorder_mwf                  : 1;  /**< Reads as zero */
	uint64_t inorder_mrf                  : 1;  /**< Always clear to zero */
	uint64_t reserved_10_11               : 2;
	uint64_t fprch2                       : 1;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the DDR_DQ/DQS drivers is 1 dclk earlier.
                                                         This bit should typically be set. */
	uint64_t bprch                        : 1;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the DDR_DQ/DQS drivers is delayed an additional DCLK
                                                         cycle. This should be set to one whenever both SILO_HC
                                                         and SILO_QC are set. */
	uint64_t sil_lat                      : 2;  /**< SILO Latency: On reads, determines how many additional
                                                         dclks to wait (on top of TCL+1+TSKW) before pulling
                                                         data out of the pad silos.
                                                             - 00: illegal
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: illegal
                                                         This should always be set to 1. */
	uint64_t tskw                         : 2;  /**< This component is a representation of total BOARD
                                                         DELAY on DQ (used in the controller to determine the
                                                         R->W spacing to avoid DQS/DQ bus conflicts). Enter
                                                         the largest of the per byte Board delay
                                                             - 00: 0 dclk
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: 3 dclks */
	uint64_t qs_dic                       : 2;  /**< DDR2 Termination Resistor Setting
                                                         A non Zero value in this register
                                                         enables the On Die Termination (ODT) in DDR parts.
                                                         These two bits are loaded into the RTT
                                                         portion of the EMRS register bits A6 & A2. If DDR2's
                                                         termination (for the memory's DQ/DQS/DM pads) is not
                                                         desired, set it to 00. If it is, chose between
                                                         01 for 75 ohm and 10 for 150 ohm termination.
                                                             00 = ODT Disabled
                                                             01 = 75 ohm Termination
                                                             10 = 150 ohm Termination
                                                             11 = 50 ohm Termination
                                                         Octeon, on writes, by default, drives the 4/8 ODT
                                                         pins (64/128b mode) based on what the masks
                                                         (LMC_WODT_CTL) are programmed to.
                                                         LMC_DDR2_CTL->ODT_ENA enables Octeon to drive ODT pins
                                                         for READS. LMC_RODT_CTL needs to be programmed based
                                                         on the system's needs for ODT. */
	uint64_t dic                          : 2;  /**< Drive Strength Control:
                                                         DIC[0] is
                                                         loaded into the Extended Mode Register (EMRS) A1 bit
                                                         during initialization.
                                                             0 = Normal
                                                             1 = Reduced
                                                         DIC[1] is used to load into EMRS
                                                         bit 10 - DQSN Enable/Disable field. By default, we
                                                         program the DDR's to drive the DQSN also. Set it to
                                                         1 if DQSN should be Hi-Z.
                                                             0 - DQSN Enable
                                                             1 - DQSN Disable */
#else
	uint64_t dic                          : 2;
	uint64_t qs_dic                       : 2;
	uint64_t tskw                         : 2;
	uint64_t sil_lat                      : 2;
	uint64_t bprch                        : 1;
	uint64_t fprch2                       : 1;
	uint64_t reserved_10_11               : 2;
	uint64_t inorder_mrf                  : 1;
	uint64_t inorder_mwf                  : 1;
	uint64_t r2r_slot                     : 1;
	uint64_t rdimm_ena                    : 1;
	uint64_t pll_bypass                   : 1;
	uint64_t pll_div2                     : 1;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t slow_scf                     : 1;
	uint64_t ddr__pctl                    : 4;
	uint64_t ddr__nctl                    : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_ctl_cn30xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ddr__nctl                    : 4;  /**< DDR nctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pulldns. */
	uint64_t ddr__pctl                    : 4;  /**< DDR pctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pullup. */
	uint64_t slow_scf                     : 1;  /**< 1=SCF has pass1 latency, 0=SCF has 1 cycle lower latency
                                                         when compared to pass1 */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                           bank[n:0]=address[n+7:7] ^ address[n+7+5:7+5]
                                                         else
                                                           bank[n:0]=address[n+7:7]
                                                         where n=1 for a 4 bank part and n=2 for an 8 bank part */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         allowing reads to interrupt. */
	uint64_t pll_div2                     : 1;  /**< PLL Div2. */
	uint64_t pll_bypass                   : 1;  /**< PLL Bypass. */
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require Write
                                                         data to be registered in the controller. */
	uint64_t r2r_slot                     : 1;  /**< R2R Slot Enable: When set, all read-to-read trans
                                                         will slot an additional 1 cycle data bus bubble to
                                                         avoid DQ/DQS bus contention. This is only a CYA bit,
                                                         in case the "built-in" DIMM and RANK crossing logic
                                                         which should auto-detect and perfectly slot
                                                         read-to-reads to the same DIMM/RANK. */
	uint64_t inorder_mwf                  : 1;  /**< Reads as zero */
	uint64_t inorder_mrf                  : 1;  /**< Always set to zero */
	uint64_t dreset                       : 1;  /**< Dclk domain reset.  The reset signal that is used by the
                                                         Dclk domain is (DRESET || ECLK_RESET). */
	uint64_t mode32b                      : 1;  /**< 32b data Path Mode
                                                         Set to 1 if we use only 32 DQ pins
                                                         0 for 16b DQ mode. */
	uint64_t fprch2                       : 1;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the DDR_DQ/DQS drivers is 1 dclk earlier.
                                                         This bit should typically be set. */
	uint64_t bprch                        : 1;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the DDR_DQ/DQS drivers is delayed an additional DCLK
                                                         cycle. This should be set to one whenever both SILO_HC
                                                         and SILO_QC are set. */
	uint64_t sil_lat                      : 2;  /**< SILO Latency: On reads, determines how many additional
                                                         dclks to wait (on top of TCL+1+TSKW) before pulling
                                                         data out of the pad silos.
                                                             - 00: illegal
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: illegal
                                                         This should always be set to 1. */
	uint64_t tskw                         : 2;  /**< This component is a representation of total BOARD
                                                         DELAY on DQ (used in the controller to determine the
                                                         R->W spacing to avoid DQS/DQ bus conflicts). Enter
                                                         the largest of the per byte Board delay
                                                             - 00: 0 dclk
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: 3 dclks */
	uint64_t qs_dic                       : 2;  /**< QS Drive Strength Control (DDR1):
                                                         & DDR2 Termination Resistor Setting
                                                         When in DDR2, a non Zero value in this register
                                                         enables the On Die Termination (ODT) in DDR parts.
                                                         These two bits are loaded into the RTT
                                                         portion of the EMRS register bits A6 & A2. If DDR2's
                                                         termination (for the memory's DQ/DQS/DM pads) is not
                                                         desired, set it to 00. If it is, chose between
                                                         01 for 75 ohm and 10 for 150 ohm termination.
                                                             00 = ODT Disabled
                                                             01 = 75 ohm Termination
                                                             10 = 150 ohm Termination
                                                             11 = 50 ohm Termination
                                                         Octeon, on writes, by default, drives the 8 ODT
                                                         pins based on what the masks (LMC_WODT_CTL1 & 2)
                                                         are programmed to. LMC_DDR2_CTL->ODT_ENA
                                                         enables Octeon to drive ODT pins for READS.
                                                         LMC_RODT_CTL needs to be programmed based on
                                                         the system's needs for ODT. */
	uint64_t dic                          : 2;  /**< Drive Strength Control:
                                                         For DDR-I/II Mode, DIC[0] is
                                                         loaded into the Extended Mode Register (EMRS) A1 bit
                                                         during initialization. (see DDR-I data sheet EMRS
                                                         description)
                                                             0 = Normal
                                                             1 = Reduced
                                                         For DDR-II Mode, DIC[1] is used to load into EMRS
                                                         bit 10 - DQSN Enable/Disable field. By default, we
                                                         program the DDR's to drive the DQSN also. Set it to
                                                         1 if DQSN should be Hi-Z.
                                                             0 - DQSN Enable
                                                             1 - DQSN Disable */
#else
	uint64_t dic                          : 2;
	uint64_t qs_dic                       : 2;
	uint64_t tskw                         : 2;
	uint64_t sil_lat                      : 2;
	uint64_t bprch                        : 1;
	uint64_t fprch2                       : 1;
	uint64_t mode32b                      : 1;
	uint64_t dreset                       : 1;
	uint64_t inorder_mrf                  : 1;
	uint64_t inorder_mwf                  : 1;
	uint64_t r2r_slot                     : 1;
	uint64_t rdimm_ena                    : 1;
	uint64_t pll_bypass                   : 1;
	uint64_t pll_div2                     : 1;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t slow_scf                     : 1;
	uint64_t ddr__pctl                    : 4;
	uint64_t ddr__nctl                    : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} cn30xx;
	struct cvmx_lmcx_ctl_cn30xx           cn31xx;
	struct cvmx_lmcx_ctl_cn38xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ddr__nctl                    : 4;  /**< DDR nctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pulldns. */
	uint64_t ddr__pctl                    : 4;  /**< DDR pctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pullup. */
	uint64_t slow_scf                     : 1;  /**< 1=SCF has pass1 latency, 0=SCF has 1 cycle lower latency
                                                         when compared to pass1
                                                         NOTE - This bit has NO effect in PASS1 */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                           bank[n:0]=address[n+7:7] ^ address[n+7+5:7+5]
                                                         else
                                                           bank[n:0]=address[n+7:7]
                                                         where n=1 for a 4 bank part and n=2 for an 8 bank part */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         allowing reads to interrupt. */
	uint64_t reserved_16_17               : 2;
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require Write
                                                         data to be registered in the controller. */
	uint64_t r2r_slot                     : 1;  /**< R2R Slot Enable: When set, all read-to-read trans
                                                         will slot an additional 1 cycle data bus bubble to
                                                         avoid DQ/DQS bus contention. This is only a CYA bit,
                                                         in case the "built-in" DIMM and RANK crossing logic
                                                         which should auto-detect and perfectly slot
                                                         read-to-reads to the same DIMM/RANK. */
	uint64_t inorder_mwf                  : 1;  /**< When set, forces LMC_MWF (writes) into strict, in-order
                                                         mode.  When clear, writes may be serviced out of order
                                                         (optimized to keep multiple banks active).
                                                         This bit is ONLY to be set at power-on and
                                                         should not be set for normal use.
                                                         NOTE: For PASS1, set as follows:
                                                             DDR-I -> 1
                                                             DDR-II -> 0
                                                         For Pass2, this bit is RA0, write ignore (this feature
                                                         is permanently disabled) */
	uint64_t inorder_mrf                  : 1;  /**< When set, forces LMC_MRF (reads) into strict, in-order
                                                         mode.  When clear, reads may be serviced out of order
                                                         (optimized to keep multiple banks active).
                                                         This bit is ONLY to be set at power-on and
                                                         should not be set for normal use.
                                                         NOTE: For PASS1, set as follows:
                                                             DDR-I -> 1
                                                             DDR-II -> 0
                                                         For Pass2, this bit should be written ZERO for
                                                         DDR I & II */
	uint64_t set_zero                     : 1;  /**< Reserved. Always Set this Bit to Zero */
	uint64_t mode128b                     : 1;  /**< 128b data Path Mode
                                                         Set to 1 if we use all 128 DQ pins
                                                         0 for 64b DQ mode. */
	uint64_t fprch2                       : 1;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the DDR_DQ/DQS drivers is 1 dclk earlier.
                                                         This bit should typically be set. */
	uint64_t bprch                        : 1;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the DDR_DQ/DQS drivers is delayed an additional DCLK
                                                         cycle. This should be set to one whenever both SILO_HC
                                                         and SILO_QC are set. */
	uint64_t sil_lat                      : 2;  /**< SILO Latency: On reads, determines how many additional
                                                         dclks to wait (on top of TCL+1+TSKW) before pulling
                                                         data out of the pad silos.
                                                             - 00: illegal
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: illegal
                                                         This should always be set to 1. */
	uint64_t tskw                         : 2;  /**< This component is a representation of total BOARD
                                                         DELAY on DQ (used in the controller to determine the
                                                         R->W spacing to avoid DQS/DQ bus conflicts). Enter
                                                         the largest of the per byte Board delay
                                                             - 00: 0 dclk
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: 3 dclks */
	uint64_t qs_dic                       : 2;  /**< QS Drive Strength Control (DDR1):
                                                         & DDR2 Termination Resistor Setting
                                                         When in DDR2, a non Zero value in this register
                                                         enables the On Die Termination (ODT) in DDR parts.
                                                         These two bits are loaded into the RTT
                                                         portion of the EMRS register bits A6 & A2. If DDR2's
                                                         termination (for the memory's DQ/DQS/DM pads) is not
                                                         desired, set it to 00. If it is, chose between
                                                         01 for 75 ohm and 10 for 150 ohm termination.
                                                             00 = ODT Disabled
                                                             01 = 75 ohm Termination
                                                             10 = 150 ohm Termination
                                                             11 = 50 ohm Termination
                                                         Octeon, on writes, by default, drives the 4/8 ODT
                                                         pins (64/128b mode) based on what the masks
                                                         (LMC_WODT_CTL) are programmed to.
                                                         LMC_DDR2_CTL->ODT_ENA enables Octeon to drive ODT pins
                                                         for READS. LMC_RODT_CTL needs to be programmed based
                                                         on the system's needs for ODT. */
	uint64_t dic                          : 2;  /**< Drive Strength Control:
                                                         For DDR-I/II Mode, DIC[0] is
                                                         loaded into the Extended Mode Register (EMRS) A1 bit
                                                         during initialization. (see DDR-I data sheet EMRS
                                                         description)
                                                             0 = Normal
                                                             1 = Reduced
                                                         For DDR-II Mode, DIC[1] is used to load into EMRS
                                                         bit 10 - DQSN Enable/Disable field. By default, we
                                                         program the DDR's to drive the DQSN also. Set it to
                                                         1 if DQSN should be Hi-Z.
                                                             0 - DQSN Enable
                                                             1 - DQSN Disable */
#else
	uint64_t dic                          : 2;
	uint64_t qs_dic                       : 2;
	uint64_t tskw                         : 2;
	uint64_t sil_lat                      : 2;
	uint64_t bprch                        : 1;
	uint64_t fprch2                       : 1;
	uint64_t mode128b                     : 1;
	uint64_t set_zero                     : 1;
	uint64_t inorder_mrf                  : 1;
	uint64_t inorder_mwf                  : 1;
	uint64_t r2r_slot                     : 1;
	uint64_t rdimm_ena                    : 1;
	uint64_t reserved_16_17               : 2;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t slow_scf                     : 1;
	uint64_t ddr__pctl                    : 4;
	uint64_t ddr__nctl                    : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} cn38xx;
	struct cvmx_lmcx_ctl_cn38xx           cn38xxp2;
	struct cvmx_lmcx_ctl_cn50xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ddr__nctl                    : 4;  /**< DDR nctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pulldns. */
	uint64_t ddr__pctl                    : 4;  /**< DDR pctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pullup. */
	uint64_t slow_scf                     : 1;  /**< Should be cleared to zero */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                           bank[n:0]=address[n+7:7] ^ address[n+7+5:7+5]
                                                         else
                                                           bank[n:0]=address[n+7:7]
                                                         where n=1 for a 4 bank part and n=2 for an 8 bank part */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         allowing reads to interrupt. */
	uint64_t reserved_17_17               : 1;
	uint64_t pll_bypass                   : 1;  /**< PLL Bypass. */
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require Write
                                                         data to be registered in the controller. */
	uint64_t r2r_slot                     : 1;  /**< R2R Slot Enable: When set, all read-to-read trans
                                                         will slot an additional 1 cycle data bus bubble to
                                                         avoid DQ/DQS bus contention. This is only a CYA bit,
                                                         in case the "built-in" DIMM and RANK crossing logic
                                                         which should auto-detect and perfectly slot
                                                         read-to-reads to the same DIMM/RANK. */
	uint64_t inorder_mwf                  : 1;  /**< Reads as zero */
	uint64_t inorder_mrf                  : 1;  /**< Always clear to zero */
	uint64_t dreset                       : 1;  /**< Dclk domain reset.  The reset signal that is used by the
                                                         Dclk domain is (DRESET || ECLK_RESET). */
	uint64_t mode32b                      : 1;  /**< 32b data Path Mode
                                                         Set to 1 if we use 32 DQ pins
                                                         0 for 16b DQ mode. */
	uint64_t fprch2                       : 1;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the DDR_DQ/DQS drivers is 1 dclk earlier.
                                                         This bit should typically be set. */
	uint64_t bprch                        : 1;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the DDR_DQ/DQS drivers is delayed an additional DCLK
                                                         cycle. This should be set to one whenever both SILO_HC
                                                         and SILO_QC are set. */
	uint64_t sil_lat                      : 2;  /**< SILO Latency: On reads, determines how many additional
                                                         dclks to wait (on top of TCL+1+TSKW) before pulling
                                                         data out of the pad silos.
                                                             - 00: illegal
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: illegal
                                                         This should always be set to 1. */
	uint64_t tskw                         : 2;  /**< This component is a representation of total BOARD
                                                         DELAY on DQ (used in the controller to determine the
                                                         R->W spacing to avoid DQS/DQ bus conflicts). Enter
                                                         the largest of the per byte Board delay
                                                             - 00: 0 dclk
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: 3 dclks */
	uint64_t qs_dic                       : 2;  /**< DDR2 Termination Resistor Setting
                                                         When in DDR2, a non Zero value in this register
                                                         enables the On Die Termination (ODT) in DDR parts.
                                                         These two bits are loaded into the RTT
                                                         portion of the EMRS register bits A6 & A2. If DDR2's
                                                         termination (for the memory's DQ/DQS/DM pads) is not
                                                         desired, set it to 00. If it is, chose between
                                                         01 for 75 ohm and 10 for 150 ohm termination.
                                                             00 = ODT Disabled
                                                             01 = 75 ohm Termination
                                                             10 = 150 ohm Termination
                                                             11 = 50 ohm Termination
                                                         Octeon, on writes, by default, drives the ODT
                                                         pins based on what the masks
                                                         (LMC_WODT_CTL) are programmed to.
                                                         LMC_DDR2_CTL->ODT_ENA enables Octeon to drive ODT pins
                                                         for READS. LMC_RODT_CTL needs to be programmed based
                                                         on the system's needs for ODT. */
	uint64_t dic                          : 2;  /**< Drive Strength Control:
                                                         DIC[0] is
                                                         loaded into the Extended Mode Register (EMRS) A1 bit
                                                         during initialization.
                                                             0 = Normal
                                                             1 = Reduced
                                                         DIC[1] is used to load into EMRS
                                                         bit 10 - DQSN Enable/Disable field. By default, we
                                                         program the DDR's to drive the DQSN also. Set it to
                                                         1 if DQSN should be Hi-Z.
                                                             0 - DQSN Enable
                                                             1 - DQSN Disable */
#else
	uint64_t dic                          : 2;
	uint64_t qs_dic                       : 2;
	uint64_t tskw                         : 2;
	uint64_t sil_lat                      : 2;
	uint64_t bprch                        : 1;
	uint64_t fprch2                       : 1;
	uint64_t mode32b                      : 1;
	uint64_t dreset                       : 1;
	uint64_t inorder_mrf                  : 1;
	uint64_t inorder_mwf                  : 1;
	uint64_t r2r_slot                     : 1;
	uint64_t rdimm_ena                    : 1;
	uint64_t pll_bypass                   : 1;
	uint64_t reserved_17_17               : 1;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t slow_scf                     : 1;
	uint64_t ddr__pctl                    : 4;
	uint64_t ddr__nctl                    : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} cn50xx;
	struct cvmx_lmcx_ctl_cn52xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ddr__nctl                    : 4;  /**< DDR nctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pulldns. */
	uint64_t ddr__pctl                    : 4;  /**< DDR pctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pullup. */
	uint64_t slow_scf                     : 1;  /**< Always clear to zero */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                           bank[n:0]=address[n+7:7] ^ address[n+7+5:7+5]
                                                         else
                                                           bank[n:0]=address[n+7:7]
                                                         where n=1 for a 4 bank part and n=2 for an 8 bank part */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         allowing reads to interrupt. */
	uint64_t reserved_16_17               : 2;
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require Write
                                                         data to be registered in the controller. */
	uint64_t r2r_slot                     : 1;  /**< R2R Slot Enable: When set, all read-to-read trans
                                                         will slot an additional 1 cycle data bus bubble to
                                                         avoid DQ/DQS bus contention. This is only a CYA bit,
                                                         in case the "built-in" DIMM and RANK crossing logic
                                                         which should auto-detect and perfectly slot
                                                         read-to-reads to the same DIMM/RANK. */
	uint64_t inorder_mwf                  : 1;  /**< Reads as zero */
	uint64_t inorder_mrf                  : 1;  /**< Always set to zero */
	uint64_t dreset                       : 1;  /**< MBZ
                                                         THIS IS OBSOLETE.  Use LMC_DLL_CTL[DRESET] instead. */
	uint64_t mode32b                      : 1;  /**< 32b data Path Mode
                                                         Set to 1 if we use only 32 DQ pins
                                                         0 for 64b DQ mode. */
	uint64_t fprch2                       : 1;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the DDR_DQ/DQS drivers is 1 dclk earlier.
                                                         This bit should typically be set. */
	uint64_t bprch                        : 1;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the DDR_DQ/DQS drivers is delayed an additional DCLK
                                                         cycle. This should be set to one whenever both SILO_HC
                                                         and SILO_QC are set. */
	uint64_t sil_lat                      : 2;  /**< SILO Latency: On reads, determines how many additional
                                                         dclks to wait (on top of TCL+1+TSKW) before pulling
                                                         data out of the pad silos.
                                                             - 00: illegal
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: illegal
                                                         This should always be set to 1.
                                                         THIS IS OBSOLETE.  Use READ_LEVEL_RANK instead. */
	uint64_t tskw                         : 2;  /**< This component is a representation of total BOARD
                                                         DELAY on DQ (used in the controller to determine the
                                                         R->W spacing to avoid DQS/DQ bus conflicts). Enter
                                                         the largest of the per byte Board delay
                                                             - 00: 0 dclk
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: 3 dclks
                                                         THIS IS OBSOLETE.  Use READ_LEVEL_RANK instead. */
	uint64_t qs_dic                       : 2;  /**< DDR2 Termination Resistor Setting
                                                         When in DDR2, a non Zero value in this register
                                                         enables the On Die Termination (ODT) in DDR parts.
                                                         These two bits are loaded into the RTT
                                                         portion of the EMRS register bits A6 & A2. If DDR2's
                                                         termination (for the memory's DQ/DQS/DM pads) is not
                                                         desired, set it to 00. If it is, chose between
                                                         01 for 75 ohm and 10 for 150 ohm termination.
                                                             00 = ODT Disabled
                                                             01 = 75 ohm Termination
                                                             10 = 150 ohm Termination
                                                             11 = 50 ohm Termination
                                                         Octeon, on writes, by default, drives the 4/8 ODT
                                                         pins (64/128b mode) based on what the masks
                                                         (LMC_WODT_CTL0 & 1) are programmed to.
                                                         LMC_DDR2_CTL->ODT_ENA enables Octeon to drive ODT pins
                                                         for READS. LMC_RODT_CTL needs to be programmed based
                                                         on the system's needs for ODT. */
	uint64_t dic                          : 2;  /**< Drive Strength Control:
                                                         DIC[0] is
                                                         loaded into the Extended Mode Register (EMRS) A1 bit
                                                         during initialization.
                                                             0 = Normal
                                                             1 = Reduced
                                                         DIC[1] is used to load into EMRS
                                                         bit 10 - DQSN Enable/Disable field. By default, we
                                                         program the DDR's to drive the DQSN also. Set it to
                                                         1 if DQSN should be Hi-Z.
                                                             0 - DQSN Enable
                                                             1 - DQSN Disable */
#else
	uint64_t dic                          : 2;
	uint64_t qs_dic                       : 2;
	uint64_t tskw                         : 2;
	uint64_t sil_lat                      : 2;
	uint64_t bprch                        : 1;
	uint64_t fprch2                       : 1;
	uint64_t mode32b                      : 1;
	uint64_t dreset                       : 1;
	uint64_t inorder_mrf                  : 1;
	uint64_t inorder_mwf                  : 1;
	uint64_t r2r_slot                     : 1;
	uint64_t rdimm_ena                    : 1;
	uint64_t reserved_16_17               : 2;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t slow_scf                     : 1;
	uint64_t ddr__pctl                    : 4;
	uint64_t ddr__nctl                    : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} cn52xx;
	struct cvmx_lmcx_ctl_cn52xx           cn52xxp1;
	struct cvmx_lmcx_ctl_cn52xx           cn56xx;
	struct cvmx_lmcx_ctl_cn52xx           cn56xxp1;
	struct cvmx_lmcx_ctl_cn58xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ddr__nctl                    : 4;  /**< DDR nctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pulldns. */
	uint64_t ddr__pctl                    : 4;  /**< DDR pctl from compensation circuit
                                                         The encoded value on this will adjust the drive strength
                                                         of the DDR DQ pullup. */
	uint64_t slow_scf                     : 1;  /**< Should be cleared to zero */
	uint64_t xor_bank                     : 1;  /**< If (XOR_BANK == 1), then
                                                           bank[n:0]=address[n+7:7] ^ address[n+7+5:7+5]
                                                         else
                                                           bank[n:0]=address[n+7:7]
                                                         where n=1 for a 4 bank part and n=2 for an 8 bank part */
	uint64_t max_write_batch              : 4;  /**< Maximum number of consecutive writes to service before
                                                         allowing reads to interrupt. */
	uint64_t reserved_16_17               : 2;
	uint64_t rdimm_ena                    : 1;  /**< Registered DIMM Enable - When set allows the use
                                                         of JEDEC Registered DIMMs which require Write
                                                         data to be registered in the controller. */
	uint64_t r2r_slot                     : 1;  /**< R2R Slot Enable: When set, all read-to-read trans
                                                         will slot an additional 1 cycle data bus bubble to
                                                         avoid DQ/DQS bus contention. This is only a CYA bit,
                                                         in case the "built-in" DIMM and RANK crossing logic
                                                         which should auto-detect and perfectly slot
                                                         read-to-reads to the same DIMM/RANK. */
	uint64_t inorder_mwf                  : 1;  /**< Reads as zero */
	uint64_t inorder_mrf                  : 1;  /**< Always clear to zero */
	uint64_t dreset                       : 1;  /**< Dclk domain reset.  The reset signal that is used by the
                                                         Dclk domain is (DRESET || ECLK_RESET). */
	uint64_t mode128b                     : 1;  /**< 128b data Path Mode
                                                         Set to 1 if we use all 128 DQ pins
                                                         0 for 64b DQ mode. */
	uint64_t fprch2                       : 1;  /**< Front Porch Enable: When set, the turn-off
                                                         time for the DDR_DQ/DQS drivers is 1 dclk earlier.
                                                         This bit should typically be set. */
	uint64_t bprch                        : 1;  /**< Back Porch Enable: When set, the turn-on time for
                                                         the DDR_DQ/DQS drivers is delayed an additional DCLK
                                                         cycle. This should be set to one whenever both SILO_HC
                                                         and SILO_QC are set. */
	uint64_t sil_lat                      : 2;  /**< SILO Latency: On reads, determines how many additional
                                                         dclks to wait (on top of TCL+1+TSKW) before pulling
                                                         data out of the pad silos.
                                                             - 00: illegal
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: illegal
                                                         This should always be set to 1. */
	uint64_t tskw                         : 2;  /**< This component is a representation of total BOARD
                                                         DELAY on DQ (used in the controller to determine the
                                                         R->W spacing to avoid DQS/DQ bus conflicts). Enter
                                                         the largest of the per byte Board delay
                                                             - 00: 0 dclk
                                                             - 01: 1 dclks
                                                             - 10: 2 dclks
                                                             - 11: 3 dclks */
	uint64_t qs_dic                       : 2;  /**< DDR2 Termination Resistor Setting
                                                         A non Zero value in this register
                                                         enables the On Die Termination (ODT) in DDR parts.
                                                         These two bits are loaded into the RTT
                                                         portion of the EMRS register bits A6 & A2. If DDR2's
                                                         termination (for the memory's DQ/DQS/DM pads) is not
                                                         desired, set it to 00. If it is, chose between
                                                         01 for 75 ohm and 10 for 150 ohm termination.
                                                             00 = ODT Disabled
                                                             01 = 75 ohm Termination
                                                             10 = 150 ohm Termination
                                                             11 = 50 ohm Termination
                                                         Octeon, on writes, by default, drives the 4/8 ODT
                                                         pins (64/128b mode) based on what the masks
                                                         (LMC_WODT_CTL) are programmed to.
                                                         LMC_DDR2_CTL->ODT_ENA enables Octeon to drive ODT pins
                                                         for READS. LMC_RODT_CTL needs to be programmed based
                                                         on the system's needs for ODT. */
	uint64_t dic                          : 2;  /**< Drive Strength Control:
                                                         DIC[0] is
                                                         loaded into the Extended Mode Register (EMRS) A1 bit
                                                         during initialization.
                                                             0 = Normal
                                                             1 = Reduced
                                                         DIC[1] is used to load into EMRS
                                                         bit 10 - DQSN Enable/Disable field. By default, we
                                                         program the DDR's to drive the DQSN also. Set it to
                                                         1 if DQSN should be Hi-Z.
                                                             0 - DQSN Enable
                                                             1 - DQSN Disable */
#else
	uint64_t dic                          : 2;
	uint64_t qs_dic                       : 2;
	uint64_t tskw                         : 2;
	uint64_t sil_lat                      : 2;
	uint64_t bprch                        : 1;
	uint64_t fprch2                       : 1;
	uint64_t mode128b                     : 1;
	uint64_t dreset                       : 1;
	uint64_t inorder_mrf                  : 1;
	uint64_t inorder_mwf                  : 1;
	uint64_t r2r_slot                     : 1;
	uint64_t rdimm_ena                    : 1;
	uint64_t reserved_16_17               : 2;
	uint64_t max_write_batch              : 4;
	uint64_t xor_bank                     : 1;
	uint64_t slow_scf                     : 1;
	uint64_t ddr__pctl                    : 4;
	uint64_t ddr__nctl                    : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} cn58xx;
	struct cvmx_lmcx_ctl_cn58xx           cn58xxp1;
};
typedef union cvmx_lmcx_ctl cvmx_lmcx_ctl_t;

/**
 * cvmx_lmc#_ctl1
 *
 * LMC_CTL1 = LMC Control1
 * This register is an assortment of various control fields needed by the memory controller
 */
union cvmx_lmcx_ctl1 {
	uint64_t u64;
	struct cvmx_lmcx_ctl1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_21_63               : 43;
	uint64_t ecc_adr                      : 1;  /**< Include memory reference address in the ECC calculation
                                                         0=disabled, 1=enabled */
	uint64_t forcewrite                   : 4;  /**< Force the oldest outstanding write to complete after
                                                         having waited for 2^FORCEWRITE cycles.  0=disabled. */
	uint64_t idlepower                    : 3;  /**< Enter power-down mode after the memory controller has
                                                         been idle for 2^(2+IDLEPOWER) cycles.  0=disabled. */
	uint64_t sequence                     : 3;  /**< Instruction sequence that is run after a 0->1 transition
                                                         on LMC_MEM_CFG0[INIT_START].
                                                         0=DDR2 power-up/init, 1=read-leveling
                                                         2=self-refresh entry, 3=self-refresh exit,
                                                         4=power-down entry, 5=power-down exit, 6=7=illegal */
	uint64_t sil_mode                     : 1;  /**< Read Silo mode.  0=envelope, 1=self-timed. */
	uint64_t dcc_enable                   : 1;  /**< Duty Cycle Corrector Enable.
                                                         0=disable, 1=enable
                                                         If the memory part does not support DCC, then this bit
                                                         must be set to 0. */
	uint64_t reserved_2_7                 : 6;
	uint64_t data_layout                  : 2;  /**< Logical data layout per DQ byte lane:
                                                         In 32b mode, this setting has no effect and the data
                                                         layout DQ[35:0] is the following:
                                                             [E[3:0], D[31:24], D[23:16], D[15:8], D[7:0]]
                                                         In 16b mode, the DQ[35:0] layouts are the following:
                                                         0 - [0[3:0], 0[7:0], [0[7:2], E[1:0]], D[15:8], D[7:0]]
                                                         1 - [0[3:0], [0[7:2], E[1:0]], D[15:8], D[7:0], 0[7:0]]
                                                         2 - [[0[1:0], E[1:0]], D[15:8], D[7:0], 0[7:0], 0[7:0]]
                                                         where E means ecc, D means data, and 0 means unused
                                                         (ignored on reads and written as 0 on writes) */
#else
	uint64_t data_layout                  : 2;
	uint64_t reserved_2_7                 : 6;
	uint64_t dcc_enable                   : 1;
	uint64_t sil_mode                     : 1;
	uint64_t sequence                     : 3;
	uint64_t idlepower                    : 3;
	uint64_t forcewrite                   : 4;
	uint64_t ecc_adr                      : 1;
	uint64_t reserved_21_63               : 43;
#endif
	} s;
	struct cvmx_lmcx_ctl1_cn30xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_2_63                : 62;
	uint64_t data_layout                  : 2;  /**< Logical data layout per DQ byte lane:
                                                         In 32b mode, this setting has no effect and the data
                                                         layout DQ[35:0] is the following:
                                                             [E[3:0], D[31:24], D[23:16], D[15:8], D[7:0]]
                                                         In 16b mode, the DQ[35:0] layouts are the following:
                                                         0 - [0[3:0], 0[7:0], [0[7:2], E[1:0]], D[15:8], D[7:0]]
                                                         1 - [0[3:0], [0[7:2], E[1:0]], D[15:8], D[7:0], 0[7:0]]
                                                         2 - [[0[1:0], E[1:0]], D[15:8], D[7:0], 0[7:0], 0[7:0]]
                                                         where E means ecc, D means data, and 0 means unused
                                                         (ignored on reads and written as 0 on writes) */
#else
	uint64_t data_layout                  : 2;
	uint64_t reserved_2_63                : 62;
#endif
	} cn30xx;
	struct cvmx_lmcx_ctl1_cn50xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_10_63               : 54;
	uint64_t sil_mode                     : 1;  /**< Read Silo mode.  0=envelope, 1=self-timed. */
	uint64_t dcc_enable                   : 1;  /**< Duty Cycle Corrector Enable.
                                                         0=disable, 1=enable
                                                         If the memory part does not support DCC, then this bit
                                                         must be set to 0. */
	uint64_t reserved_2_7                 : 6;
	uint64_t data_layout                  : 2;  /**< Logical data layout per DQ byte lane:
                                                         In 32b mode, this setting has no effect and the data
                                                         layout DQ[35:0] is the following:
                                                             [E[3:0], D[31:24], D[23:16], D[15:8], D[7:0]]
                                                         In 16b mode, the DQ[35:0] layouts are the following:
                                                         0 - [0[3:0], 0[7:0], [0[7:2], E[1:0]], D[15:8], D[7:0]]
                                                         1 - [0[3:0], [0[7:2], E[1:0]], D[15:8], D[7:0], 0[7:0]]
                                                         2 - [[0[1:0], E[1:0]], D[15:8], D[7:0], 0[7:0], 0[7:0]]
                                                         where E means ecc, D means data, and 0 means unused
                                                         (ignored on reads and written as 0 on writes) */
#else
	uint64_t data_layout                  : 2;
	uint64_t reserved_2_7                 : 6;
	uint64_t dcc_enable                   : 1;
	uint64_t sil_mode                     : 1;
	uint64_t reserved_10_63               : 54;
#endif
	} cn50xx;
	struct cvmx_lmcx_ctl1_cn52xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_21_63               : 43;
	uint64_t ecc_adr                      : 1;  /**< Include memory reference address in the ECC calculation
                                                         0=disabled, 1=enabled */
	uint64_t forcewrite                   : 4;  /**< Force the oldest outstanding write to complete after
                                                         having waited for 2^FORCEWRITE cycles.  0=disabled. */
	uint64_t idlepower                    : 3;  /**< Enter power-down mode after the memory controller has
                                                         been idle for 2^(2+IDLEPOWER) cycles.  0=disabled. */
	uint64_t sequence                     : 3;  /**< Instruction sequence that is run after a 0->1 transition
                                                         on LMC_MEM_CFG0[INIT_START].
                                                         0=DDR2 power-up/init, 1=read-leveling
                                                         2=self-refresh entry, 3=self-refresh exit,
                                                         4=power-down entry, 5=power-down exit, 6=7=illegal */
	uint64_t sil_mode                     : 1;  /**< Read Silo mode.  0=envelope, 1=self-timed. */
	uint64_t dcc_enable                   : 1;  /**< Duty Cycle Corrector Enable.
                                                         0=disable, 1=enable
                                                         If the memory part does not support DCC, then this bit
                                                         must be set to 0. */
	uint64_t reserved_0_7                 : 8;
#else
	uint64_t reserved_0_7                 : 8;
	uint64_t dcc_enable                   : 1;
	uint64_t sil_mode                     : 1;
	uint64_t sequence                     : 3;
	uint64_t idlepower                    : 3;
	uint64_t forcewrite                   : 4;
	uint64_t ecc_adr                      : 1;
	uint64_t reserved_21_63               : 43;
#endif
	} cn52xx;
	struct cvmx_lmcx_ctl1_cn52xx          cn52xxp1;
	struct cvmx_lmcx_ctl1_cn52xx          cn56xx;
	struct cvmx_lmcx_ctl1_cn52xx          cn56xxp1;
	struct cvmx_lmcx_ctl1_cn58xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_10_63               : 54;
	uint64_t sil_mode                     : 1;  /**< Read Silo mode.  0=envelope, 1=self-timed. */
	uint64_t dcc_enable                   : 1;  /**< Duty Cycle Corrector Enable.
                                                         0=disable, 1=enable
                                                         If the memory part does not support DCC, then this bit
                                                         must be set to 0. */
	uint64_t reserved_0_7                 : 8;
#else
	uint64_t reserved_0_7                 : 8;
	uint64_t dcc_enable                   : 1;
	uint64_t sil_mode                     : 1;
	uint64_t reserved_10_63               : 54;
#endif
	} cn58xx;
	struct cvmx_lmcx_ctl1_cn58xx          cn58xxp1;
};
typedef union cvmx_lmcx_ctl1 cvmx_lmcx_ctl1_t;

/**
 * cvmx_lmc#_dclk_cnt
 *
 * LMC_DCLK_CNT  = Performance Counters
 *
 */
union cvmx_lmcx_dclk_cnt {
	uint64_t u64;
	struct cvmx_lmcx_dclk_cnt_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t dclkcnt                      : 64; /**< Performance Counter
                                                         64-bit counter that increments every CK cycle */
#else
	uint64_t dclkcnt                      : 64;
#endif
	} s;
	struct cvmx_lmcx_dclk_cnt_s           cn61xx;
	struct cvmx_lmcx_dclk_cnt_s           cn63xx;
	struct cvmx_lmcx_dclk_cnt_s           cn63xxp1;
	struct cvmx_lmcx_dclk_cnt_s           cn66xx;
	struct cvmx_lmcx_dclk_cnt_s           cn68xx;
	struct cvmx_lmcx_dclk_cnt_s           cn68xxp1;
	struct cvmx_lmcx_dclk_cnt_s           cn70xx;
	struct cvmx_lmcx_dclk_cnt_s           cn78xx;
	struct cvmx_lmcx_dclk_cnt_s           cnf71xx;
};
typedef union cvmx_lmcx_dclk_cnt cvmx_lmcx_dclk_cnt_t;

/**
 * cvmx_lmc#_dclk_cnt_hi
 *
 * LMC_DCLK_CNT_HI  = Performance Counters
 *
 */
union cvmx_lmcx_dclk_cnt_hi {
	uint64_t u64;
	struct cvmx_lmcx_dclk_cnt_hi_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t dclkcnt_hi                   : 32; /**< Performance Counter that counts dclks
                                                         Upper 32-bits of a 64-bit counter. */
#else
	uint64_t dclkcnt_hi                   : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn30xx;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn31xx;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn38xx;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn38xxp2;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn50xx;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn52xx;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn52xxp1;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn56xx;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn56xxp1;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn58xx;
	struct cvmx_lmcx_dclk_cnt_hi_s        cn58xxp1;
};
typedef union cvmx_lmcx_dclk_cnt_hi cvmx_lmcx_dclk_cnt_hi_t;

/**
 * cvmx_lmc#_dclk_cnt_lo
 *
 * LMC_DCLK_CNT_LO  = Performance Counters
 *
 */
union cvmx_lmcx_dclk_cnt_lo {
	uint64_t u64;
	struct cvmx_lmcx_dclk_cnt_lo_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t dclkcnt_lo                   : 32; /**< Performance Counter that counts dclks
                                                         Lower 32-bits of a 64-bit counter. */
#else
	uint64_t dclkcnt_lo                   : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn30xx;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn31xx;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn38xx;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn38xxp2;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn50xx;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn52xx;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn52xxp1;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn56xx;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn56xxp1;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn58xx;
	struct cvmx_lmcx_dclk_cnt_lo_s        cn58xxp1;
};
typedef union cvmx_lmcx_dclk_cnt_lo cvmx_lmcx_dclk_cnt_lo_t;

/**
 * cvmx_lmc#_dclk_ctl
 *
 * LMC_DCLK_CTL = LMC DCLK generation control
 *
 *
 * Notes:
 * This CSR is only relevant for LMC1. LMC0_DCLK_CTL is not used.
 *
 */
union cvmx_lmcx_dclk_ctl {
	uint64_t u64;
	struct cvmx_lmcx_dclk_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_8_63                : 56;
	uint64_t off90_ena                    : 1;  /**< 0=use global DCLK (i.e. the PLL) directly for LMC1
                                                         1=use the 90 degree DCLK DLL to offset LMC1 DCLK */
	uint64_t dclk90_byp                   : 1;  /**< 0=90 degree DCLK DLL uses sampled delay from LMC0
                                                         1=90 degree DCLK DLL uses DCLK90_VLU
                                                         See DCLK90_VLU. */
	uint64_t dclk90_ld                    : 1;  /**< The 90 degree DCLK DLL samples the delay setting
                                                         from LMC0's DLL when this field transitions 0->1 */
	uint64_t dclk90_vlu                   : 5;  /**< Manual open-loop delay setting.
                                                         The LMC1 90 degree DCLK DLL uses DCLK90_VLU rather
                                                         than the delay setting sampled from LMC0 when
                                                         DCLK90_BYP=1. */
#else
	uint64_t dclk90_vlu                   : 5;
	uint64_t dclk90_ld                    : 1;
	uint64_t dclk90_byp                   : 1;
	uint64_t off90_ena                    : 1;
	uint64_t reserved_8_63                : 56;
#endif
	} s;
	struct cvmx_lmcx_dclk_ctl_s           cn56xx;
	struct cvmx_lmcx_dclk_ctl_s           cn56xxp1;
};
typedef union cvmx_lmcx_dclk_ctl cvmx_lmcx_dclk_ctl_t;

/**
 * cvmx_lmc#_ddr2_ctl
 *
 * LMC_DDR2_CTL = LMC DDR2 & DLL Control Register
 *
 */
union cvmx_lmcx_ddr2_ctl {
	uint64_t u64;
	struct cvmx_lmcx_ddr2_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t bank8                        : 1;  /**< For 8 bank DDR2 parts
                                                         1 - DDR2 parts have 8 internal banks (BA is 3 bits
                                                         wide).
                                                         0 - DDR2 parts have 4 internal banks (BA is 2 bits
                                                         wide). */
	uint64_t burst8                       : 1;  /**< 8-burst mode.
                                                         1 - DDR data transfer happens in burst of 8
                                                         0 - DDR data transfer happens in burst of 4
                                                         BURST8 should be set when DDR2T is set
                                                         to minimize the command bandwidth loss. */
	uint64_t addlat                       : 3;  /**< Additional Latency for posted CAS
                                                         When Posted CAS is on, this configures the additional
                                                         latency. This should be set to
                                                                1 .. LMC_MEM_CFG1[TRCD]-2
                                                         (Note the implication that posted CAS should not
                                                         be used when tRCD is two.) */
	uint64_t pocas                        : 1;  /**< Enable the Posted CAS feature of DDR2. */
	uint64_t bwcnt                        : 1;  /**< Bus utilization counter Clear.
                                                         Clears the LMC_OPS_CNT_*, LMC_IFB_CNT_*, and
                                                         LMC_DCLK_CNT_* registers. SW should first write this
                                                         field to a one, then write this field to a zero to
                                                         clear the CSR's. */
	uint64_t twr                          : 3;  /**< DDR Write Recovery time (tWR). Last Wr Brst to Pre delay
                                                         This is not a direct encoding of the value. Its
                                                         programmed as below per DDR2 spec. The decimal number
                                                         on the right is RNDUP(tWR(ns) / tCYC(ns))
                                                          TYP=15ns
                                                             - 000: RESERVED
                                                             - 001: 2
                                                             - 010: 3
                                                             - 011: 4
                                                             - 100: 5
                                                             - 101: 6
                                                             - 110: 7
                                                             - 111: 8 */
	uint64_t silo_hc                      : 1;  /**< Delays the read sample window by a Half Cycle. */
	uint64_t ddr_eof                      : 4;  /**< Early Fill Counter Init.
                                                         L2 needs to know a few cycle before a fill completes so
                                                         it can get its Control pipe started (for better overall
                                                         performance). This counter contains  an init value which
                                                         is a function of Eclk/Dclk ratio to account for the
                                                         asynchronous boundary between L2 cache and the DRAM
                                                         controller. This init value will
                                                         determine when to safely let the L2 know that a fill
                                                         termination is coming up.
                                                         Set DDR_EOF according to the following rule:
                                                         eclkFreq/dclkFreq = dclkPeriod/eclkPeriod = RATIO
                                                                RATIO < 6/6  -> illegal
                                                         6/6 <= RATIO < 6/5  -> DDR_EOF=3
                                                         6/5 <= RATIO < 6/4  -> DDR_EOF=3
                                                         6/4 <= RATIO < 6/3  -> DDR_EOF=2
                                                         6/3 <= RATIO < 6/2  -> DDR_EOF=1
                                                         6/2 <= RATIO < 6/1  -> DDR_EOF=0
                                                         6/1 <= RATIO        -> DDR_EOF=0 */
	uint64_t tfaw                         : 5;  /**< tFAW - Cycles = RNDUP[tFAW(ns)/tcyc(ns)] - 1
                                                         Four Access Window time. Relevant only in DDR2 AND in
                                                         8-bank parts.
                                                             tFAW = 5'b0 in DDR2-4bank
                                                             tFAW = RNDUP[tFAW(ns)/tcyc(ns)] - 1
                                                                      in DDR2-8bank */
	uint64_t crip_mode                    : 1;  /**< Cripple Mode - When set, the LMC allows only
                                                         1 inflight transaction (.vs. 8 in normal mode).
                                                         This bit is ONLY to be set at power-on and
                                                         should not be set for normal use. */
	uint64_t ddr2t                        : 1;  /**< Turn on the DDR 2T mode. 2 cycle window for CMD and
                                                         address. This mode helps relieve setup time pressure
                                                         on the Address and command bus which nominally have
                                                         a very large fanout. Please refer to Micron's tech
                                                         note tn_47_01 titled "DDR2-533 Memory Design Guide
                                                         for Two Dimm Unbuffered Systems" for physical details.
                                                         BURST8 should be set when DDR2T is set to minimize
                                                         add/cmd loss. */
	uint64_t odt_ena                      : 1;  /**< Enable Obsolete ODT on Reads
                                                         Obsolete Read ODT wiggles DDR_ODT_* pins on reads.
                                                         Should normally be cleared to zero.
                                                         When this is on, the following fields must also be
                                                         programmed:
                                                             LMC_CTL->QS_DIC - programs the termination value
                                                             LMC_RODT_CTL - programs the ODT I/O mask for Reads */
	uint64_t qdll_ena                     : 1;  /**< DDR Quad DLL Enable: A 0->1 transition on this bit after
                                                         DCLK init sequence will reset the DDR 90 DLL. Should
                                                         happen at startup before any activity in DDR.
                                                         DRESET should be asserted before and for 10 usec
                                                         following the 0->1 transition on QDLL_ENA. */
	uint64_t dll90_vlu                    : 5;  /**< Contains the open loop setting value for the DDR90 delay
                                                         line. */
	uint64_t dll90_byp                    : 1;  /**< DDR DLL90 Bypass: When set, the DDR90 DLL is to be
                                                         bypassed and the setting is defined by DLL90_VLU */
	uint64_t rdqs                         : 1;  /**< DDR2 RDQS mode. When set, configures memory subsystem to
                                                         use unidirectional DQS pins. RDQS/DM - Rcv & DQS - Xmit */
	uint64_t ddr2                         : 1;  /**< Should be set */
#else
	uint64_t ddr2                         : 1;
	uint64_t rdqs                         : 1;
	uint64_t dll90_byp                    : 1;
	uint64_t dll90_vlu                    : 5;
	uint64_t qdll_ena                     : 1;
	uint64_t odt_ena                      : 1;
	uint64_t ddr2t                        : 1;
	uint64_t crip_mode                    : 1;
	uint64_t tfaw                         : 5;
	uint64_t ddr_eof                      : 4;
	uint64_t silo_hc                      : 1;
	uint64_t twr                          : 3;
	uint64_t bwcnt                        : 1;
	uint64_t pocas                        : 1;
	uint64_t addlat                       : 3;
	uint64_t burst8                       : 1;
	uint64_t bank8                        : 1;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_ddr2_ctl_cn30xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t bank8                        : 1;  /**< For 8 bank DDR2 parts
                                                         1 - DDR2 parts have 8 internal banks (BA is 3 bits
                                                         wide).
                                                         0 - DDR2 parts have 4 internal banks (BA is 2 bits
                                                         wide). */
	uint64_t burst8                       : 1;  /**< 8-burst mode.
                                                         1 - DDR data transfer happens in burst of 8
                                                         0 - DDR data transfer happens in burst of 4
                                                         BURST8 should be set when DDR2T is set to minimize
                                                         add/cmd bandwidth loss. */
	uint64_t addlat                       : 3;  /**< Additional Latency for posted CAS
                                                         When Posted CAS is on, this configures the additional
                                                         latency. This should be set to
                                                                1 .. LMC_MEM_CFG1[TRCD]-2
                                                         (Note the implication that posted CAS should not
                                                         be used when tRCD is two.) */
	uint64_t pocas                        : 1;  /**< Enable the Posted CAS feature of DDR2. */
	uint64_t bwcnt                        : 1;  /**< Bus utilization counter Clear.
                                                         Clears the LMC_OPS_CNT_*, LMC_IFB_CNT_*, and
                                                         LMC_DCLK_CNT_* registers. SW should first write this
                                                         field to a one, then write this field to a zero to
                                                         clear the CSR's. */
	uint64_t twr                          : 3;  /**< DDR Write Recovery time (tWR). Last Wr Brst to Pre delay
                                                         This is not a direct encoding of the value. Its
                                                         programmed as below per DDR2 spec. The decimal number
                                                         on the right is RNDUP(tWR(ns) / tCYC(ns))
                                                          TYP=15ns
                                                             - 000: RESERVED
                                                             - 001: 2
                                                             - 010: 3
                                                             - 011: 4
                                                             - 100: 5
                                                             - 101: 6
                                                             - 110-111: RESERVED */
	uint64_t silo_hc                      : 1;  /**< Delays the read sample window by a Half Cycle. */
	uint64_t ddr_eof                      : 4;  /**< Early Fill Counter Init.
                                                         L2 needs to know a few cycle before a fill completes so
                                                         it can get its Control pipe started (for better overall
                                                         performance). This counter contains  an init value which
                                                         is a function of Eclk/Dclk ratio to account for the
                                                         asynchronous boundary between L2 cache and the DRAM
                                                         controller. This init value will
                                                         determine when to safely let the L2 know that a fill
                                                         termination is coming up.
                                                         DDR_EOF = RNDUP (DCLK period/Eclk Period). If the ratio
                                                         is above 3, set DDR_EOF to 3.
                                                             DCLK/ECLK period         DDR_EOF
                                                                Less than 1            1
                                                                Less than 2            2
                                                                More than 2            3 */
	uint64_t tfaw                         : 5;  /**< tFAW - Cycles = RNDUP[tFAW(ns)/tcyc(ns)] - 1
                                                         Four Access Window time. Relevant only in
                                                         8-bank parts.
                                                             TFAW = 5'b0 for DDR2-4bank
                                                             TFAW = RNDUP[tFAW(ns)/tcyc(ns)] - 1 in DDR2-8bank */
	uint64_t crip_mode                    : 1;  /**< Cripple Mode - When set, the LMC allows only
                                                         1 inflight transaction (.vs. 8 in normal mode).
                                                         This bit is ONLY to be set at power-on and
                                                         should not be set for normal use. */
	uint64_t ddr2t                        : 1;  /**< Turn on the DDR 2T mode. 2 cycle window for CMD and
                                                         address. This mode helps relieve setup time pressure
                                                         on the Address and command bus which nominally have
                                                         a very large fanout. Please refer to Micron's tech
                                                         note tn_47_01 titled "DDR2-533 Memory Design Guide
                                                         for Two Dimm Unbuffered Systems" for physical details.
                                                         BURST8 should be used when DDR2T is set to minimize
                                                         add/cmd bandwidth loss. */
	uint64_t odt_ena                      : 1;  /**< Enable ODT for DDR2 on Reads
                                                         When this is on, the following fields must also be
                                                         programmed:
                                                             LMC_CTL->QS_DIC - programs the termination value
                                                             LMC_RODT_CTL - programs the ODT I/O mask for writes
                                                         Program as 0 for DDR1 mode and ODT needs to be off
                                                         on Octeon Reads */
	uint64_t qdll_ena                     : 1;  /**< DDR Quad DLL Enable: A 0->1 transition on this bit after
                                                         erst deassertion will reset the DDR 90 DLL. Should
                                                         happen at startup before any activity in DDR. */
	uint64_t dll90_vlu                    : 5;  /**< Contains the open loop setting value for the DDR90 delay
                                                         line. */
	uint64_t dll90_byp                    : 1;  /**< DDR DLL90 Bypass: When set, the DDR90 DLL is to be
                                                         bypassed and the setting is defined by DLL90_VLU */
	uint64_t reserved_1_1                 : 1;
	uint64_t ddr2                         : 1;  /**< DDR2 Enable: When set, configures memory subsystem for
                                                         DDR-II SDRAMs. */
#else
	uint64_t ddr2                         : 1;
	uint64_t reserved_1_1                 : 1;
	uint64_t dll90_byp                    : 1;
	uint64_t dll90_vlu                    : 5;
	uint64_t qdll_ena                     : 1;
	uint64_t odt_ena                      : 1;
	uint64_t ddr2t                        : 1;
	uint64_t crip_mode                    : 1;
	uint64_t tfaw                         : 5;
	uint64_t ddr_eof                      : 4;
	uint64_t silo_hc                      : 1;
	uint64_t twr                          : 3;
	uint64_t bwcnt                        : 1;
	uint64_t pocas                        : 1;
	uint64_t addlat                       : 3;
	uint64_t burst8                       : 1;
	uint64_t bank8                        : 1;
	uint64_t reserved_32_63               : 32;
#endif
	} cn30xx;
	struct cvmx_lmcx_ddr2_ctl_cn30xx      cn31xx;
	struct cvmx_lmcx_ddr2_ctl_s           cn38xx;
	struct cvmx_lmcx_ddr2_ctl_s           cn38xxp2;
	struct cvmx_lmcx_ddr2_ctl_s           cn50xx;
	struct cvmx_lmcx_ddr2_ctl_s           cn52xx;
	struct cvmx_lmcx_ddr2_ctl_s           cn52xxp1;
	struct cvmx_lmcx_ddr2_ctl_s           cn56xx;
	struct cvmx_lmcx_ddr2_ctl_s           cn56xxp1;
	struct cvmx_lmcx_ddr2_ctl_s           cn58xx;
	struct cvmx_lmcx_ddr2_ctl_s           cn58xxp1;
};
typedef union cvmx_lmcx_ddr2_ctl cvmx_lmcx_ddr2_ctl_t;

/**
 * cvmx_lmc#_ddr4_dimm_ctl
 *
 * This register is used only when LMC(0..3)_CONTROL[RDIMM_ENA] = 1. During an RCW initialization
 * sequence, this register controls LMC's write operations to the extended DDR4 control words in
 * the JEDEC standard registering clock driver on an RDIMM.
 */
union cvmx_lmcx_ddr4_dimm_ctl {
	uint64_t u64;
	struct cvmx_lmcx_ddr4_dimm_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_22_63               : 42;
	uint64_t ddr4_dimm1_wmask             : 11; /**< DIMM1 write mask. If (DIMM1_WMASK[n] = 1), write DIMM1.RCn. */
	uint64_t ddr4_dimm0_wmask             : 11; /**< DIMM0 write mask. If (DIMM0_WMASK[n] = 1), write DIMM0.RCn. */
#else
	uint64_t ddr4_dimm0_wmask             : 11;
	uint64_t ddr4_dimm1_wmask             : 11;
	uint64_t reserved_22_63               : 42;
#endif
	} s;
	struct cvmx_lmcx_ddr4_dimm_ctl_s      cn70xx;
	struct cvmx_lmcx_ddr4_dimm_ctl_s      cn78xx;
};
typedef union cvmx_lmcx_ddr4_dimm_ctl cvmx_lmcx_ddr4_dimm_ctl_t;

/**
 * cvmx_lmc#_ddr_pll_ctl
 *
 * This register controls the DDR_CK frequency. For details, refer to CK Speed Programming. See
 * LMC Initialization Sequence for the initialization sequence.
 * DDR PLL Bringup sequence:
 * 1. Write CLKF, DDR_PS_EN, DFM_PS_EN, DIFFAMP, CPS, CPB. If test mode is going to be activated,
 * then also write jtg__ddr_pll_tm_en1, jtg__ddr_pll_tm_en2, jtg__ddr_pll_tm_en3,
 * jtg__ddr_pll_tm_en4, jtg__dfa_pll_tm_en1, jtg__dfa_pll_tm_en2, jtg__dfa_pll_tm_en3,
 * jtg__dfa_pll_tm_en4, JTAG_TEST_MODE
 * 2. Wait 128 ref clock cycles (7680 rclk cycles)
 * 3. Write 1 to RESET_N
 * 4. Wait 1152 ref clocks (1152*16 rclk cycles)
 * 5. Write 0 to DDR_DIV_RESET and DFM_DIV_RESET
 * 6. Wait 10 ref clock cycles (160 rclk cycles) before bringing up the DDR interface
 * If test mode is going to be activated, wait an additional 8191 ref clocks (8191*16 rclk+
 * cycles) to allow PLL clock alignment.
 */
union cvmx_lmcx_ddr_pll_ctl {
	uint64_t u64;
	struct cvmx_lmcx_ddr_pll_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t dclk_invert                  : 1;  /**< Invert dclk that feeds LMC/DDR at the south side of the chip. */
	uint64_t phy_dcok                     : 1;  /**< Set to power up PHY logic after setting LMC(0..3)_DDR_PLL_CTL[DDR4_MODE]. */
	uint64_t ddr4_mode                    : 1;  /**< DDR4 mode select: 1 = DDR4, 0 = DDR3. */
	uint64_t pll_fbslip                   : 1;  /**< PLL FBSLIP indication. */
	uint64_t pll_lock                     : 1;  /**< PLL LOCK indication. */
	uint64_t reserved_18_26               : 9;
	uint64_t diffamp                      : 4;  /**< PLL diffamp input transconductance */
	uint64_t cps                          : 3;  /**< PLL charge-pump current */
	uint64_t reserved_8_10                : 3;
	uint64_t reset_n                      : 1;  /**< PLL reset */
	uint64_t clkf                         : 7;  /**< Multiply reference by CLKF
                                                         32 <= CLKF <= 64
                                                         LMC+DFM PLL frequency = 50 * CLKF
                                                         min = 1.6 GHz, max = 3.2 GHz */
#else
	uint64_t clkf                         : 7;
	uint64_t reset_n                      : 1;
	uint64_t reserved_8_10                : 3;
	uint64_t cps                          : 3;
	uint64_t diffamp                      : 4;
	uint64_t reserved_18_26               : 9;
	uint64_t pll_lock                     : 1;
	uint64_t pll_fbslip                   : 1;
	uint64_t ddr4_mode                    : 1;
	uint64_t phy_dcok                     : 1;
	uint64_t dclk_invert                  : 1;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_ddr_pll_ctl_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_27_63               : 37;
	uint64_t jtg_test_mode                : 1;  /**< JTAG Test Mode
                                                         Clock alignment between DCLK & REFCLK as well as FCLK &
                                                         REFCLK can only be performed after the ddr_pll_divider_reset
                                                         is deasserted. SW need to wait atleast 10 reference clock
                                                         cycles after deasserting pll_divider_reset before asserting
                                                         LMC(0)_DDR_PLL_CTL[JTG_TEST_MODE]. During alignment (which can
                                                         take upto 160 microseconds) DCLK and FCLK can exhibit some
                                                         high frequency pulses. Therefore, all bring up activities in
                                                         that clock domain need to be delayed (when the chip operates
                                                         in jtg_test_mode) by about 160 microseconds to ensure that
                                                         lock is achieved. */
	uint64_t dfm_div_reset                : 1;  /**< DFM postscalar divider reset */
	uint64_t dfm_ps_en                    : 3;  /**< DFM postscalar divide ratio
                                                         Determines the DFM CK speed.
                                                         0x0 : Divide LMC+DFM PLL output by 1
                                                         0x1 : Divide LMC+DFM PLL output by 2
                                                         0x2 : Divide LMC+DFM PLL output by 3
                                                         0x3 : Divide LMC+DFM PLL output by 4
                                                         0x4 : Divide LMC+DFM PLL output by 6
                                                         0x5 : Divide LMC+DFM PLL output by 8
                                                         0x6 : Divide LMC+DFM PLL output by 12
                                                         0x7 : Divide LMC+DFM PLL output by 12
                                                         DFM_PS_EN is not used when DFM_DIV_RESET = 1 */
	uint64_t ddr_div_reset                : 1;  /**< DDR postscalar divider reset */
	uint64_t ddr_ps_en                    : 3;  /**< DDR postscalar divide ratio
                                                         Determines the LMC CK speed.
                                                         0x0 : Divide LMC+DFM PLL output by 1
                                                         0x1 : Divide LMC+DFM PLL output by 2
                                                         0x2 : Divide LMC+DFM PLL output by 3
                                                         0x3 : Divide LMC+DFM PLL output by 4
                                                         0x4 : Divide LMC+DFM PLL output by 6
                                                         0x5 : Divide LMC+DFM PLL output by 8
                                                         0x6 : Divide LMC+DFM PLL output by 12
                                                         0x7 : Divide LMC+DFM PLL output by 12
                                                         DDR_PS_EN is not used when DDR_DIV_RESET = 1 */
	uint64_t diffamp                      : 4;  /**< PLL diffamp input transconductance */
	uint64_t cps                          : 3;  /**< PLL charge-pump current */
	uint64_t cpb                          : 3;  /**< PLL charge-pump current */
	uint64_t reset_n                      : 1;  /**< PLL reset */
	uint64_t clkf                         : 7;  /**< Multiply reference by CLKF
                                                         32 <= CLKF <= 64
                                                         LMC+DFM PLL frequency = 50 * CLKF
                                                         min = 1.6 GHz, max = 3.2 GHz */
#else
	uint64_t clkf                         : 7;
	uint64_t reset_n                      : 1;
	uint64_t cpb                          : 3;
	uint64_t cps                          : 3;
	uint64_t diffamp                      : 4;
	uint64_t ddr_ps_en                    : 3;
	uint64_t ddr_div_reset                : 1;
	uint64_t dfm_ps_en                    : 3;
	uint64_t dfm_div_reset                : 1;
	uint64_t jtg_test_mode                : 1;
	uint64_t reserved_27_63               : 37;
#endif
	} cn61xx;
	struct cvmx_lmcx_ddr_pll_ctl_cn61xx   cn63xx;
	struct cvmx_lmcx_ddr_pll_ctl_cn61xx   cn63xxp1;
	struct cvmx_lmcx_ddr_pll_ctl_cn61xx   cn66xx;
	struct cvmx_lmcx_ddr_pll_ctl_cn61xx   cn68xx;
	struct cvmx_lmcx_ddr_pll_ctl_cn61xx   cn68xxp1;
	struct cvmx_lmcx_ddr_pll_ctl_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_31_63               : 33;
	uint64_t phy_dcok                     : 1;  /**< Set to power up PHY logic after setting LMC(0..0)_DDR_PLL_CTL[DDR4_MODE]. */
	uint64_t ddr4_mode                    : 1;  /**< DDR4 mode select (0 for DDR3). */
	uint64_t pll_fbslip                   : 1;  /**< PLL FBSLIP indication. */
	uint64_t pll_lock                     : 1;  /**< PLL LOCK indication. */
	uint64_t pll_rfslip                   : 1;  /**< PLL RFSLIP indication. */
	uint64_t clkr                         : 2;  /**< PLL post-divider control. */
	uint64_t jtg_test_mode                : 1;  /**< Reserved; must be zero. INTERNAL: JTAG test mode. Clock alignment between DCLK & REFCLK as
                                                         well as FCLK & REFCLK can only be performed after the ddr_pll_divider_reset is deasserted.
                                                         SW need to wait at least 10 reference clock cycles after deasserting pll_divider_reset
                                                         before asserting LMC(0..0)_DDR_PLL_CTL[JTG_TEST_MODE]. During alignment (which can take up
                                                         to 160 microseconds) DCLK and FCLK can exhibit some high-frequency pulses. Therefore, all
                                                         bring up activities in that clock domain need to be delayed (when the chip operates in
                                                         jtg_test_mode) by about 160 microseconds to ensure that lock is achieved. */
	uint64_t ddr_div_reset                : 1;  /**< DDR postscalar divider reset. */
	uint64_t ddr_ps_en                    : 4;  /**< DDR postscalar divide ratio. Determines the LMC CK speed.
                                                         0x0 = Divide LMC PLL by 1.
                                                         0x1 = Divide LMC PLL by 2.
                                                         0x2 = Divide LMC PLL by 3.
                                                         0x3 = Divide LMC PLL by 4.
                                                         0x4 = Divide LMC PLL by 5.
                                                         0x5 = Divide LMC PLL by 6.
                                                         0x6 = Divide LMC PLL by 7.
                                                         0x7 = Divide LMC PLL by 8.
                                                         0x8 = Divide LMC PLL by 10.
                                                         0x9 = Divide LMC PLL by 12.
                                                         0xA-0xF = Reserved.
                                                         DDR_PS_EN is not used when DDR_DIV_RESET = 1 */
	uint64_t reserved_8_17                : 10;
	uint64_t reset_n                      : 1;  /**< PLL reset */
	uint64_t clkf                         : 7;  /**< Multiply reference by CLKF. 32 <= CLKF <= 64. LMC PLL frequency = 50 * CLKF. min = 1.6
                                                         GHz, max = 3.2 GHz. */
#else
	uint64_t clkf                         : 7;
	uint64_t reset_n                      : 1;
	uint64_t reserved_8_17                : 10;
	uint64_t ddr_ps_en                    : 4;
	uint64_t ddr_div_reset                : 1;
	uint64_t jtg_test_mode                : 1;
	uint64_t clkr                         : 2;
	uint64_t pll_rfslip                   : 1;
	uint64_t pll_lock                     : 1;
	uint64_t pll_fbslip                   : 1;
	uint64_t ddr4_mode                    : 1;
	uint64_t phy_dcok                     : 1;
	uint64_t reserved_31_63               : 33;
#endif
	} cn70xx;
	struct cvmx_lmcx_ddr_pll_ctl_cn78xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t dclk_invert                  : 1;  /**< Invert dclk that feeds LMC/DDR at the south side of the chip. */
	uint64_t phy_dcok                     : 1;  /**< Set to power up PHY logic after setting LMC(0..3)_DDR_PLL_CTL[DDR4_MODE]. */
	uint64_t ddr4_mode                    : 1;  /**< DDR4 mode select: 1 = DDR4, 0 = DDR3. */
	uint64_t pll_fbslip                   : 1;  /**< PLL FBSLIP indication. */
	uint64_t pll_lock                     : 1;  /**< PLL LOCK indication. */
	uint64_t pll_rfslip                   : 1;  /**< PLL RFSLIP indication. */
	uint64_t clkr                         : 2;  /**< PLL post-divider control. */
	uint64_t jtg_test_mode                : 1;  /**< Reserved; must be zero. INTERNAL: JTAG test mode. Clock alignment between DCLK & REFCLK as
                                                         well as FCLK & REFCLK can only be performed after the ddr_pll_divider_reset is deasserted.
                                                         SW need to wait at least 10 reference clock cycles after deasserting pll_divider_reset
                                                         before asserting LMC(0..3)_DDR_PLL_CTL[JTG_TEST_MODE]. During alignment (which can take up
                                                         to 160 microseconds) DCLK and FCLK can exhibit some high-frequency pulses. Therefore, all
                                                         bring up activities in that clock domain need to be delayed (when the chip operates in
                                                         jtg_test_mode) by about 160 microseconds to ensure that lock is achieved. */
	uint64_t ddr_div_reset                : 1;  /**< DDR postscalar divider reset. */
	uint64_t ddr_ps_en                    : 4;  /**< DDR postscalar divide ratio. Determines the LMC CK speed.
                                                         0x0 = divide LMC PLL by TBD.
                                                         0x1 = divide LMC PLL by TBD.
                                                         0x2 = divide LMC PLL by TBD.
                                                         0x3 = divide LMC PLL by TBD.
                                                         0x4 = divide LMC PLL by TBD.
                                                         0x5 = divide LMC PLL by TBD.
                                                         0x6 = divide LMC PLL by TBD.
                                                         0x7 = divide LMC PLL by TBD.
                                                         0x8 = divide LMC PLL by TBD.
                                                         0x9 = divide LMC PLL by TBD.
                                                         0xA = divide LMC PLL by TBD.
                                                         0xB = divide LMC PLL by TBD.
                                                         0xC = divide LMC PLL by TBD.
                                                         0xD = divide LMC PLL by TBD.
                                                         0xE = divide LMC PLL by TBD.
                                                         0xF = divide LMC PLL by TBD.
                                                         DDR_PS_EN is not used when DDR_DIV_RESET = 1 */
	uint64_t reserved_9_17                : 9;
	uint64_t clkf_ext                     : 1;  /**< A 1-bit extension to the CLKF register to support for DDR4-2666. */
	uint64_t reset_n                      : 1;  /**< PLL reset */
	uint64_t clkf                         : 7;  /**< Multiply reference by CLKF. 32 <= CLKF <= 64. LMC PLL frequency = 50 * CLKF. min = 1.6
                                                         GHz, max = 3.2 GHz. */
#else
	uint64_t clkf                         : 7;
	uint64_t reset_n                      : 1;
	uint64_t clkf_ext                     : 1;
	uint64_t reserved_9_17                : 9;
	uint64_t ddr_ps_en                    : 4;
	uint64_t ddr_div_reset                : 1;
	uint64_t jtg_test_mode                : 1;
	uint64_t clkr                         : 2;
	uint64_t pll_rfslip                   : 1;
	uint64_t pll_lock                     : 1;
	uint64_t pll_fbslip                   : 1;
	uint64_t ddr4_mode                    : 1;
	uint64_t phy_dcok                     : 1;
	uint64_t dclk_invert                  : 1;
	uint64_t reserved_32_63               : 32;
#endif
	} cn78xx;
	struct cvmx_lmcx_ddr_pll_ctl_cn61xx   cnf71xx;
};
typedef union cvmx_lmcx_ddr_pll_ctl cvmx_lmcx_ddr_pll_ctl_t;

/**
 * cvmx_lmc#_delay_cfg
 *
 * LMC_DELAY_CFG = Open-loop delay line settings
 *
 *
 * Notes:
 * The DQ bits add OUTGOING delay only to dq, dqs_[p,n], cb, cbs_[p,n], dqm.  Delay is approximately
 * 50-80ps per setting depending on process/voltage.  There is no need to add incoming delay since by
 * default all strobe bits are delayed internally by 90 degrees (as was always the case in previous
 * passes and past chips.
 *
 * The CMD add delay to all command bits DDR_RAS, DDR_CAS, DDR_A<15:0>, DDR_BA<2:0>, DDR_n_CS<1:0>_L,
 * DDR_WE, DDR_CKE and DDR_ODT_<7:0>. Again, delay is 50-80ps per tap.
 *
 * The CLK bits add delay to all clock signals DDR_CK_<5:0>_P and DDR_CK_<5:0>_N.  Again, delay is
 * 50-80ps per tap.
 *
 * The usage scenario is the following: There is too much delay on command signals and setup on command
 * is not met. The user can then delay the clock until setup is met.
 *
 * At the same time though, dq/dqs should be delayed because there is also a DDR spec tying dqs with
 * clock. If clock is too much delayed with respect to dqs, writes will start to fail.
 *
 * This scheme should eliminate the board need of adding routing delay to clock signals to make high
 * frequencies work.
 */
union cvmx_lmcx_delay_cfg {
	uint64_t u64;
	struct cvmx_lmcx_delay_cfg_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_15_63               : 49;
	uint64_t dq                           : 5;  /**< Setting for DQ  delay line */
	uint64_t cmd                          : 5;  /**< Setting for CMD delay line */
	uint64_t clk                          : 5;  /**< Setting for CLK delay line */
#else
	uint64_t clk                          : 5;
	uint64_t cmd                          : 5;
	uint64_t dq                           : 5;
	uint64_t reserved_15_63               : 49;
#endif
	} s;
	struct cvmx_lmcx_delay_cfg_s          cn30xx;
	struct cvmx_lmcx_delay_cfg_cn38xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_14_63               : 50;
	uint64_t dq                           : 4;  /**< Setting for DQ  delay line */
	uint64_t reserved_9_9                 : 1;
	uint64_t cmd                          : 4;  /**< Setting for CMD delay line */
	uint64_t reserved_4_4                 : 1;
	uint64_t clk                          : 4;  /**< Setting for CLK delay line */
#else
	uint64_t clk                          : 4;
	uint64_t reserved_4_4                 : 1;
	uint64_t cmd                          : 4;
	uint64_t reserved_9_9                 : 1;
	uint64_t dq                           : 4;
	uint64_t reserved_14_63               : 50;
#endif
	} cn38xx;
	struct cvmx_lmcx_delay_cfg_cn38xx     cn50xx;
	struct cvmx_lmcx_delay_cfg_cn38xx     cn52xx;
	struct cvmx_lmcx_delay_cfg_cn38xx     cn52xxp1;
	struct cvmx_lmcx_delay_cfg_cn38xx     cn56xx;
	struct cvmx_lmcx_delay_cfg_cn38xx     cn56xxp1;
	struct cvmx_lmcx_delay_cfg_cn38xx     cn58xx;
	struct cvmx_lmcx_delay_cfg_cn38xx     cn58xxp1;
};
typedef union cvmx_lmcx_delay_cfg cvmx_lmcx_delay_cfg_t;

/**
 * cvmx_lmc#_dimm#_ddr4_params0
 *
 * This register contains values to be programmed into the extra DDR4 control words in the
 * corresponding (registered) DIMM. These are control words RC1x through RC8x.
 */
union cvmx_lmcx_dimmx_ddr4_params0 {
	uint64_t u64;
	struct cvmx_lmcx_dimmx_ddr4_params0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t rc8x                         : 8;  /**< RC8x. */
	uint64_t rc7x                         : 8;  /**< RC7x. */
	uint64_t rc6x                         : 8;  /**< RC6x. */
	uint64_t rc5x                         : 8;  /**< RC5x. */
	uint64_t rc4x                         : 8;  /**< RC4x. */
	uint64_t rc3x                         : 8;  /**< RC3x. */
	uint64_t rc2x                         : 8;  /**< RC2x. */
	uint64_t rc1x                         : 8;  /**< RC1x. */
#else
	uint64_t rc1x                         : 8;
	uint64_t rc2x                         : 8;
	uint64_t rc3x                         : 8;
	uint64_t rc4x                         : 8;
	uint64_t rc5x                         : 8;
	uint64_t rc6x                         : 8;
	uint64_t rc7x                         : 8;
	uint64_t rc8x                         : 8;
#endif
	} s;
	struct cvmx_lmcx_dimmx_ddr4_params0_s cn70xx;
	struct cvmx_lmcx_dimmx_ddr4_params0_s cn78xx;
};
typedef union cvmx_lmcx_dimmx_ddr4_params0 cvmx_lmcx_dimmx_ddr4_params0_t;

/**
 * cvmx_lmc#_dimm#_ddr4_params1
 *
 * This register contains values to be programmed into the extra DDR4 control words in the
 * corresponding (registered) DIMM. These are control words RC9x through RCBx.
 */
union cvmx_lmcx_dimmx_ddr4_params1 {
	uint64_t u64;
	struct cvmx_lmcx_dimmx_ddr4_params1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_24_63               : 40;
	uint64_t rcbx                         : 8;  /**< RCBx. */
	uint64_t rcax                         : 8;  /**< RCAx. */
	uint64_t rc9x                         : 8;  /**< RC9x. */
#else
	uint64_t rc9x                         : 8;
	uint64_t rcax                         : 8;
	uint64_t rcbx                         : 8;
	uint64_t reserved_24_63               : 40;
#endif
	} s;
	struct cvmx_lmcx_dimmx_ddr4_params1_s cn70xx;
	struct cvmx_lmcx_dimmx_ddr4_params1_s cn78xx;
};
typedef union cvmx_lmcx_dimmx_ddr4_params1 cvmx_lmcx_dimmx_ddr4_params1_t;

/**
 * cvmx_lmc#_dimm#_params
 *
 * This register contains values to be programmed into each control word in the corresponding
 * (registered) DIMM. The control words allow optimization of the device properties for different
 * raw card designs. Note that LMC only uses this CSR when LMC(0..3)_CONTROL[RDIMM_ENA]=1. During
 * a power-up/init sequence, LMC writes these fields into the control words in the JEDEC standard
 * SSTE32882 registering clock driver on an RDIMM when corresponding
 * LMC(0..3)_DIMM_CTL[DIMM*_WMASK] bits are set.
 */
union cvmx_lmcx_dimmx_params {
	uint64_t u64;
	struct cvmx_lmcx_dimmx_params_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t rc15                         : 4;  /**< RC15, Reserved */
	uint64_t rc14                         : 4;  /**< RC14, Reserved */
	uint64_t rc13                         : 4;  /**< RC13, Reserved */
	uint64_t rc12                         : 4;  /**< RC12, Reserved */
	uint64_t rc11                         : 4;  /**< RC11, Encoding for RDIMM Operating VDD */
	uint64_t rc10                         : 4;  /**< RC10, Encoding for RDIMM Operating Speed */
	uint64_t rc9                          : 4;  /**< RC9 , Power Savings Settings Control Word */
	uint64_t rc8                          : 4;  /**< RC8 , Additional IBT Settings Control Word */
	uint64_t rc7                          : 4;  /**< RC7 , Reserved */
	uint64_t rc6                          : 4;  /**< RC6 , Reserved */
	uint64_t rc5                          : 4;  /**< RC5 , CK Driver Characterstics Control Word */
	uint64_t rc4                          : 4;  /**< RC4 , Control Signals Driver Characteristics Control Word */
	uint64_t rc3                          : 4;  /**< RC3 , CA Signals Driver Characterstics Control Word */
	uint64_t rc2                          : 4;  /**< RC2 , Timing Control Word */
	uint64_t rc1                          : 4;  /**< RC1 , Clock Driver Enable Control Word */
	uint64_t rc0                          : 4;  /**< RC0 , Global Features Control Word */
#else
	uint64_t rc0                          : 4;
	uint64_t rc1                          : 4;
	uint64_t rc2                          : 4;
	uint64_t rc3                          : 4;
	uint64_t rc4                          : 4;
	uint64_t rc5                          : 4;
	uint64_t rc6                          : 4;
	uint64_t rc7                          : 4;
	uint64_t rc8                          : 4;
	uint64_t rc9                          : 4;
	uint64_t rc10                         : 4;
	uint64_t rc11                         : 4;
	uint64_t rc12                         : 4;
	uint64_t rc13                         : 4;
	uint64_t rc14                         : 4;
	uint64_t rc15                         : 4;
#endif
	} s;
	struct cvmx_lmcx_dimmx_params_s       cn61xx;
	struct cvmx_lmcx_dimmx_params_s       cn63xx;
	struct cvmx_lmcx_dimmx_params_s       cn63xxp1;
	struct cvmx_lmcx_dimmx_params_s       cn66xx;
	struct cvmx_lmcx_dimmx_params_s       cn68xx;
	struct cvmx_lmcx_dimmx_params_s       cn68xxp1;
	struct cvmx_lmcx_dimmx_params_s       cn70xx;
	struct cvmx_lmcx_dimmx_params_s       cn78xx;
	struct cvmx_lmcx_dimmx_params_s       cnf71xx;
};
typedef union cvmx_lmcx_dimmx_params cvmx_lmcx_dimmx_params_t;

/**
 * cvmx_lmc#_dimm_ctl
 *
 * Note that this CSR is only used when LMC(0..3)_CONTROL[RDIMM_ENA] = 1. During a power-up/init
 * sequence, this CSR controls LMC's write operations to the control words in the JEDEC standard
 * SSTE32882 registering clock driver on an RDIMM.
 */
union cvmx_lmcx_dimm_ctl {
	uint64_t u64;
	struct cvmx_lmcx_dimm_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_46_63               : 18;
	uint64_t parity                       : 1;  /**< Parity
                                                         The PAR_IN input of a registered DIMM should be
                                                         tied off. LMC adjusts the value of the DDR_WE_L (DWE#)
                                                         pin during DDR3 register part control word writes to
                                                         ensure the parity is observed correctly by the receiving
                                                         SSTE32882 register part.
                                                         When PAR_IN is grounded, PARITY should be cleared to 0. */
	uint64_t tcws                         : 13; /**< LMC waits for this time period before and after a RDIMM
                                                         Control Word Access during a power-up/init SEQUENCE.
                                                         TCWS is in multiples of 8 CK cycles.
                                                         Set TCWS (CSR field) = RNDUP[tcws(ns)/(8*tCYC(ns))],
                                                         where tCWS is the desired time (ns), and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=0x4e0 (equivalent to 15us) when changing
                                                         clock timing (RC2.DBA1, RC6.DA4, RC10.DA3, RC10.DA4,
                                                         RC11.DA3, and RC11.DA4)
                                                         TYP=0x8, otherwise
                                                         0x0 = Reserved */
	uint64_t dimm1_wmask                  : 16; /**< DIMM1 Write Mask
                                                         if (DIMM1_WMASK[n] = 1)
                                                             Write DIMM1.RCn */
	uint64_t dimm0_wmask                  : 16; /**< DIMM0 Write Mask
                                                         if (DIMM0_WMASK[n] = 1)
                                                             Write DIMM0.RCn */
#else
	uint64_t dimm0_wmask                  : 16;
	uint64_t dimm1_wmask                  : 16;
	uint64_t tcws                         : 13;
	uint64_t parity                       : 1;
	uint64_t reserved_46_63               : 18;
#endif
	} s;
	struct cvmx_lmcx_dimm_ctl_s           cn61xx;
	struct cvmx_lmcx_dimm_ctl_s           cn63xx;
	struct cvmx_lmcx_dimm_ctl_s           cn63xxp1;
	struct cvmx_lmcx_dimm_ctl_s           cn66xx;
	struct cvmx_lmcx_dimm_ctl_s           cn68xx;
	struct cvmx_lmcx_dimm_ctl_s           cn68xxp1;
	struct cvmx_lmcx_dimm_ctl_s           cn70xx;
	struct cvmx_lmcx_dimm_ctl_s           cn78xx;
	struct cvmx_lmcx_dimm_ctl_s           cnf71xx;
};
typedef union cvmx_lmcx_dimm_ctl cvmx_lmcx_dimm_ctl_t;

/**
 * cvmx_lmc#_dll_ctl
 *
 * LMC_DLL_CTL = LMC DLL control and DCLK reset
 *
 */
union cvmx_lmcx_dll_ctl {
	uint64_t u64;
	struct cvmx_lmcx_dll_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_8_63                : 56;
	uint64_t dreset                       : 1;  /**< Dclk domain reset.  The reset signal that is used by the
                                                         Dclk domain is (DRESET || ECLK_RESET). */
	uint64_t dll90_byp                    : 1;  /**< DDR DLL90 Bypass: When set, the DDR90 DLL is to be
                                                         bypassed and the setting is defined by DLL90_VLU */
	uint64_t dll90_ena                    : 1;  /**< DDR Quad DLL Enable: A 0->1 transition on this bit after
                                                         DCLK init sequence resets the DDR 90 DLL. Should
                                                         happen at startup before any activity in DDR. QDLL_ENA
                                                         must not transition 1->0 outside of a DRESET sequence
                                                         (i.e. it must remain 1 until the next DRESET).
                                                         DRESET should be asserted before and for 10 usec
                                                         following the 0->1 transition on QDLL_ENA. */
	uint64_t dll90_vlu                    : 5;  /**< Contains the open loop setting value for the DDR90 delay
                                                         line. */
#else
	uint64_t dll90_vlu                    : 5;
	uint64_t dll90_ena                    : 1;
	uint64_t dll90_byp                    : 1;
	uint64_t dreset                       : 1;
	uint64_t reserved_8_63                : 56;
#endif
	} s;
	struct cvmx_lmcx_dll_ctl_s            cn52xx;
	struct cvmx_lmcx_dll_ctl_s            cn52xxp1;
	struct cvmx_lmcx_dll_ctl_s            cn56xx;
	struct cvmx_lmcx_dll_ctl_s            cn56xxp1;
};
typedef union cvmx_lmcx_dll_ctl cvmx_lmcx_dll_ctl_t;

/**
 * cvmx_lmc#_dll_ctl2
 *
 * See LMC Initialization Sequence for the initialization sequence.
 *
 */
union cvmx_lmcx_dll_ctl2 {
	uint64_t u64;
	struct cvmx_lmcx_dll_ctl2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_0_63                : 64;
#else
	uint64_t reserved_0_63                : 64;
#endif
	} s;
	struct cvmx_lmcx_dll_ctl2_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_16_63               : 48;
	uint64_t intf_en                      : 1;  /**< Interface Enable */
	uint64_t dll_bringup                  : 1;  /**< DLL Bringup */
	uint64_t dreset                       : 1;  /**< Dclk domain reset.  The reset signal that is used by the
                                                         Dclk domain is (DRESET || ECLK_RESET). */
	uint64_t quad_dll_ena                 : 1;  /**< DLL Enable */
	uint64_t byp_sel                      : 4;  /**< Bypass select
                                                         0000 : no byte
                                                         0001 : byte 0
                                                         - ...
                                                         1001 : byte 8
                                                         1010 : all bytes
                                                         1011-1111 : Reserved */
	uint64_t byp_setting                  : 8;  /**< Bypass setting
                                                         DDR3-1600: 00100010
                                                         DDR3-1333: 00110010
                                                         DDR3-1066: 01001011
                                                         DDR3-800 : 01110101
                                                         DDR3-667 : 10010110
                                                         DDR3-600 : 10101100 */
#else
	uint64_t byp_setting                  : 8;
	uint64_t byp_sel                      : 4;
	uint64_t quad_dll_ena                 : 1;
	uint64_t dreset                       : 1;
	uint64_t dll_bringup                  : 1;
	uint64_t intf_en                      : 1;
	uint64_t reserved_16_63               : 48;
#endif
	} cn61xx;
	struct cvmx_lmcx_dll_ctl2_cn63xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_15_63               : 49;
	uint64_t dll_bringup                  : 1;  /**< DLL Bringup */
	uint64_t dreset                       : 1;  /**< Dclk domain reset.  The reset signal that is used by the
                                                         Dclk domain is (DRESET || ECLK_RESET). */
	uint64_t quad_dll_ena                 : 1;  /**< DLL Enable */
	uint64_t byp_sel                      : 4;  /**< Bypass select
                                                         0000 : no byte
                                                         0001 : byte 0
                                                         - ...
                                                         1001 : byte 8
                                                         1010 : all bytes
                                                         1011-1111 : Reserved */
	uint64_t byp_setting                  : 8;  /**< Bypass setting
                                                         DDR3-1600: 00100010
                                                         DDR3-1333: 00110010
                                                         DDR3-1066: 01001011
                                                         DDR3-800 : 01110101
                                                         DDR3-667 : 10010110
                                                         DDR3-600 : 10101100 */
#else
	uint64_t byp_setting                  : 8;
	uint64_t byp_sel                      : 4;
	uint64_t quad_dll_ena                 : 1;
	uint64_t dreset                       : 1;
	uint64_t dll_bringup                  : 1;
	uint64_t reserved_15_63               : 49;
#endif
	} cn63xx;
	struct cvmx_lmcx_dll_ctl2_cn63xx      cn63xxp1;
	struct cvmx_lmcx_dll_ctl2_cn63xx      cn66xx;
	struct cvmx_lmcx_dll_ctl2_cn61xx      cn68xx;
	struct cvmx_lmcx_dll_ctl2_cn61xx      cn68xxp1;
	struct cvmx_lmcx_dll_ctl2_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_17_63               : 47;
	uint64_t intf_en                      : 1;  /**< Interface enable. */
	uint64_t dll_bringup                  : 1;  /**< DLL bring up. */
	uint64_t dreset                       : 1;  /**< System-memory-clock domain reset. The reset signal that is used by the system-memory-clock
                                                         domain is
                                                         (DRESET -OR- core-clock reset). */
	uint64_t quad_dll_ena                 : 1;  /**< DLL enable. */
	uint64_t byp_sel                      : 4;  /**< Reserved; must be zero. INTERNAL: Bypass select.
                                                         0x0 = no byte.
                                                         0x1 = byte 0.
                                                         - ...
                                                         0x9 = byte 8.
                                                         0xA = all bytes.
                                                         0xB-0xF = Reserved. */
	uint64_t byp_setting                  : 9;  /**< Reserved; must be zero. INTERNAL: Bypass setting.
                                                         DDR3-1600: 0x22.
                                                         DDR3-1333: 0x32.
                                                         DDR3-1066: 0x4B.
                                                         DDR3-800  : 0x75.
                                                         DDR3-667  : 0x96.
                                                         DDR3-600  : 0xAC. */
#else
	uint64_t byp_setting                  : 9;
	uint64_t byp_sel                      : 4;
	uint64_t quad_dll_ena                 : 1;
	uint64_t dreset                       : 1;
	uint64_t dll_bringup                  : 1;
	uint64_t intf_en                      : 1;
	uint64_t reserved_17_63               : 47;
#endif
	} cn70xx;
	struct cvmx_lmcx_dll_ctl2_cn70xx      cn78xx;
	struct cvmx_lmcx_dll_ctl2_cn61xx      cnf71xx;
};
typedef union cvmx_lmcx_dll_ctl2 cvmx_lmcx_dll_ctl2_t;

/**
 * cvmx_lmc#_dll_ctl3
 *
 * LMC_DLL_CTL3 = LMC DLL control and DCLK reset
 *
 */
union cvmx_lmcx_dll_ctl3 {
	uint64_t u64;
	struct cvmx_lmcx_dll_ctl3_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_0_63                : 64;
#else
	uint64_t reserved_0_63                : 64;
#endif
	} s;
	struct cvmx_lmcx_dll_ctl3_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_41_63               : 23;
	uint64_t dclk90_fwd                   : 1;  /**< Forward setting
                                                         0 : disable
                                                         1 : forward (generates a 1 cycle pulse to forward setting)
                                                         This register is oneshot and clears itself each time
                                                         it is set */
	uint64_t ddr_90_dly_byp               : 1;  /**< Bypass DDR90_DLY in Clock Tree */
	uint64_t dclk90_recal_dis             : 1;  /**< Disable periodic recalibration of DDR90 Delay Line in */
	uint64_t dclk90_byp_sel               : 1;  /**< Bypass Setting Select for DDR90 Delay Line */
	uint64_t dclk90_byp_setting           : 8;  /**< Bypass Setting for DDR90 Delay Line */
	uint64_t dll_fast                     : 1;  /**< DLL lock
                                                         0 = DLL locked */
	uint64_t dll90_setting                : 8;  /**< Encoded DLL settings. Works in conjuction with
                                                         DLL90_BYTE_SEL */
	uint64_t fine_tune_mode               : 1;  /**< DLL Fine Tune Mode
                                                         0 = disabled
                                                         1 = enable.
                                                         When enabled, calibrate internal PHY DLL every
                                                         LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t dll_mode                     : 1;  /**< DLL Mode */
	uint64_t dll90_byte_sel               : 4;  /**< Observe DLL settings for selected byte
                                                         0001 : byte 0
                                                         - ...
                                                         1001 : byte 8
                                                         0000,1010-1111 : Reserved */
	uint64_t offset_ena                   : 1;  /**< Offset enable
                                                         0 = disable
                                                         1 = enable */
	uint64_t load_offset                  : 1;  /**< Load offset
                                                         0 : disable
                                                         1 : load (generates a 1 cycle pulse to the PHY)
                                                         This register is oneshot and clears itself each time
                                                         it is set */
	uint64_t mode_sel                     : 2;  /**< Mode select
                                                         00 : reset
                                                         01 : write
                                                         10 : read
                                                         11 : write & read */
	uint64_t byte_sel                     : 4;  /**< Byte select
                                                         0000 : no byte
                                                         0001 : byte 0
                                                         - ...
                                                         1001 : byte 8
                                                         1010 : all bytes
                                                         1011-1111 : Reserved */
	uint64_t offset                       : 6;  /**< Write/read offset setting
                                                         [4:0] : offset
                                                         [5]   : 0 = increment, 1 = decrement
                                                         Not a 2's complement value */
#else
	uint64_t offset                       : 6;
	uint64_t byte_sel                     : 4;
	uint64_t mode_sel                     : 2;
	uint64_t load_offset                  : 1;
	uint64_t offset_ena                   : 1;
	uint64_t dll90_byte_sel               : 4;
	uint64_t dll_mode                     : 1;
	uint64_t fine_tune_mode               : 1;
	uint64_t dll90_setting                : 8;
	uint64_t dll_fast                     : 1;
	uint64_t dclk90_byp_setting           : 8;
	uint64_t dclk90_byp_sel               : 1;
	uint64_t dclk90_recal_dis             : 1;
	uint64_t ddr_90_dly_byp               : 1;
	uint64_t dclk90_fwd                   : 1;
	uint64_t reserved_41_63               : 23;
#endif
	} cn61xx;
	struct cvmx_lmcx_dll_ctl3_cn63xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_29_63               : 35;
	uint64_t dll_fast                     : 1;  /**< DLL lock
                                                         0 = DLL locked */
	uint64_t dll90_setting                : 8;  /**< Encoded DLL settings. Works in conjuction with
                                                         DLL90_BYTE_SEL */
	uint64_t fine_tune_mode               : 1;  /**< DLL Fine Tune Mode
                                                         0 = disabled
                                                         1 = enable.
                                                         When enabled, calibrate internal PHY DLL every
                                                         LMC*_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t dll_mode                     : 1;  /**< DLL Mode */
	uint64_t dll90_byte_sel               : 4;  /**< Observe DLL settings for selected byte
                                                         0001 : byte 0
                                                         - ...
                                                         1001 : byte 8
                                                         0000,1010-1111 : Reserved */
	uint64_t offset_ena                   : 1;  /**< Offset enable
                                                         0 = disable
                                                         1 = enable */
	uint64_t load_offset                  : 1;  /**< Load offset
                                                         0 : disable
                                                         1 : load (generates a 1 cycle pulse to the PHY)
                                                         This register is oneshot and clears itself each time
                                                         it is set */
	uint64_t mode_sel                     : 2;  /**< Mode select
                                                         00 : reset
                                                         01 : write
                                                         10 : read
                                                         11 : write & read */
	uint64_t byte_sel                     : 4;  /**< Byte select
                                                         0000 : no byte
                                                         0001 : byte 0
                                                         - ...
                                                         1001 : byte 8
                                                         1010 : all bytes
                                                         1011-1111 : Reserved */
	uint64_t offset                       : 6;  /**< Write/read offset setting
                                                         [4:0] : offset
                                                         [5]   : 0 = increment, 1 = decrement
                                                         Not a 2's complement value */
#else
	uint64_t offset                       : 6;
	uint64_t byte_sel                     : 4;
	uint64_t mode_sel                     : 2;
	uint64_t load_offset                  : 1;
	uint64_t offset_ena                   : 1;
	uint64_t dll90_byte_sel               : 4;
	uint64_t dll_mode                     : 1;
	uint64_t fine_tune_mode               : 1;
	uint64_t dll90_setting                : 8;
	uint64_t dll_fast                     : 1;
	uint64_t reserved_29_63               : 35;
#endif
	} cn63xx;
	struct cvmx_lmcx_dll_ctl3_cn63xx      cn63xxp1;
	struct cvmx_lmcx_dll_ctl3_cn63xx      cn66xx;
	struct cvmx_lmcx_dll_ctl3_cn61xx      cn68xx;
	struct cvmx_lmcx_dll_ctl3_cn61xx      cn68xxp1;
	struct cvmx_lmcx_dll_ctl3_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_44_63               : 20;
	uint64_t dclk90_fwd                   : 1;  /**< Reserved; must be zero. INTERNAL: Generate a one cycle pulse to forward setting. This is a
                                                         oneshot and clears itself each time it is set. */
	uint64_t ddr_90_dly_byp               : 1;  /**< Reserved; must be zero. INTERNAL: Bypass DDR90_DLY in clock tree. */
	uint64_t dclk90_recal_dis             : 1;  /**< Disable periodic recalibration of DDR90 delay line in. */
	uint64_t dclk90_byp_sel               : 1;  /**< Bypass setting select for DDR90 delay line. */
	uint64_t dclk90_byp_setting           : 9;  /**< Bypass setting for DDR90 delay line. */
	uint64_t dll_fast                     : 1;  /**< Reserved; must be zero. INTERNAL: DLL lock, 0=DLL locked. */
	uint64_t dll90_setting                : 9;  /**< Reserved; must be zero. INTERNAL: Encoded DLL settings. Works in conjunction with
                                                         DLL90_BYTE_SEL. */
	uint64_t fine_tune_mode               : 1;  /**< DLL fine tune mode. 0 = disabled; 1 = enable. When enabled, calibrate internal PHY DLL
                                                         every LMC(0..0)_CONFIG[REF_ZQCS_INT] CK cycles. */
	uint64_t dll_mode                     : 1;  /**< Reserved; must be zero. INTERNAL: DLL mode. */
	uint64_t dll90_byte_sel               : 4;  /**< Observe DLL settings for selected byte.
                                                         - 0011: byte 4
                                                         - 0100: byte 3
                                                         - 0101: byte 2
                                                         - 0110: byte 1
                                                         - 0111: byte 0
                                                         0000-0010,1000-1111: Reserved */
	uint64_t offset_ena                   : 1;  /**< Reserved; must be zero. INTERNAL: Offset enable. 1=enable. */
	uint64_t load_offset                  : 1;  /**< Reserved; must be zero. INTERNAL: Load offset. 0=disable, 1=generate a one cycle pulse to
                                                         the PHY. This field is a oneshot and clears itself each time it is set. */
	uint64_t mode_sel                     : 2;  /**< Reserved; must be zero. INTERNAL: Mode select. 0x0 = reset, 0x1 = write, 0x2 = read, 0x3 =
                                                         write and read. */
	uint64_t byte_sel                     : 4;  /**< Reserved; must be zero. INTERNAL: Byte select. 0x0 = no byte, 0x1 = byte 0, ..., 0x9 =
                                                         byte 8, 0xA = all bytes, 0xB-0xF = Reserved. */
	uint64_t offset                       : 7;  /**< Reserved; must be zero. INTERNAL: Write/read offset setting. <5:0>: offset (not
                                                         two's-complement), <5>: 0 = increment, 1 = decrement. */
#else
	uint64_t offset                       : 7;
	uint64_t byte_sel                     : 4;
	uint64_t mode_sel                     : 2;
	uint64_t load_offset                  : 1;
	uint64_t offset_ena                   : 1;
	uint64_t dll90_byte_sel               : 4;
	uint64_t dll_mode                     : 1;
	uint64_t fine_tune_mode               : 1;
	uint64_t dll90_setting                : 9;
	uint64_t dll_fast                     : 1;
	uint64_t dclk90_byp_setting           : 9;
	uint64_t dclk90_byp_sel               : 1;
	uint64_t dclk90_recal_dis             : 1;
	uint64_t ddr_90_dly_byp               : 1;
	uint64_t dclk90_fwd                   : 1;
	uint64_t reserved_44_63               : 20;
#endif
	} cn70xx;
	struct cvmx_lmcx_dll_ctl3_cn70xx      cn78xx;
	struct cvmx_lmcx_dll_ctl3_cn61xx      cnf71xx;
};
typedef union cvmx_lmcx_dll_ctl3 cvmx_lmcx_dll_ctl3_t;

/**
 * cvmx_lmc#_dual_memcfg
 *
 * This register controls certain parameters of dual-memory configuration.
 * This register enables the design to have two separate memory configurations, selected
 * dynamically by the reference address. Note however, that both configurations share
 * LMC(0..3)_CONTROL[XOR_BANK], LMC(0..3)_CONFIG [PBANK_LSB], LMC(0..3)_CONFIG[RANK_ENA], and all
 * timing parameters.
 * In this description:
 * config0 refers to the normal memory configuration that is defined by the
 * LMC*_CONFIG[ROW_LSB] parameter
 * config1 refers to the dual (or second) memory configuration that is defined by this register.
 * Enable-mask to chip-select mapping is shown below:
 */
union cvmx_lmcx_dual_memcfg {
	uint64_t u64;
	struct cvmx_lmcx_dual_memcfg_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_20_63               : 44;
	uint64_t bank8                        : 1;  /**< See LMC_DDR2_CTL[BANK8] */
	uint64_t row_lsb                      : 3;  /**< See LMC*_CONFIG[ROW_LSB] */
	uint64_t reserved_8_15                : 8;
	uint64_t cs_mask                      : 8;  /**< Chip select mask.
                                                         This mask corresponds to the 8 chip selects for a memory
                                                         configuration.  Each reference address will assert one of
                                                         the chip selects.  If that chip select has its
                                                         corresponding CS_MASK bit set, then the "config1"
                                                         parameters are used, otherwise the "config0" parameters
                                                         are used.  See additional notes below.
                                                         [7:4] *UNUSED IN 6xxx* */
#else
	uint64_t cs_mask                      : 8;
	uint64_t reserved_8_15                : 8;
	uint64_t row_lsb                      : 3;
	uint64_t bank8                        : 1;
	uint64_t reserved_20_63               : 44;
#endif
	} s;
	struct cvmx_lmcx_dual_memcfg_s        cn50xx;
	struct cvmx_lmcx_dual_memcfg_s        cn52xx;
	struct cvmx_lmcx_dual_memcfg_s        cn52xxp1;
	struct cvmx_lmcx_dual_memcfg_s        cn56xx;
	struct cvmx_lmcx_dual_memcfg_s        cn56xxp1;
	struct cvmx_lmcx_dual_memcfg_s        cn58xx;
	struct cvmx_lmcx_dual_memcfg_s        cn58xxp1;
	struct cvmx_lmcx_dual_memcfg_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_19_63               : 45;
	uint64_t row_lsb                      : 3;  /**< See LMC*_CONFIG[ROW_LSB] */
	uint64_t reserved_8_15                : 8;
	uint64_t cs_mask                      : 8;  /**< Chip select mask.
                                                         This mask corresponds to the 8 chip selects for a memory
                                                         configuration.  Each reference address will assert one of
                                                         the chip selects.  If that chip select has its
                                                         corresponding CS_MASK bit set, then the "config1"
                                                         parameters are used, otherwise the "config0" parameters
                                                         are used.  See additional notes below.
                                                         [7:4] *UNUSED IN 6xxx* */
#else
	uint64_t cs_mask                      : 8;
	uint64_t reserved_8_15                : 8;
	uint64_t row_lsb                      : 3;
	uint64_t reserved_19_63               : 45;
#endif
	} cn61xx;
	struct cvmx_lmcx_dual_memcfg_cn61xx   cn63xx;
	struct cvmx_lmcx_dual_memcfg_cn61xx   cn63xxp1;
	struct cvmx_lmcx_dual_memcfg_cn61xx   cn66xx;
	struct cvmx_lmcx_dual_memcfg_cn61xx   cn68xx;
	struct cvmx_lmcx_dual_memcfg_cn61xx   cn68xxp1;
	struct cvmx_lmcx_dual_memcfg_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_19_63               : 45;
	uint64_t row_lsb                      : 3;  /**< Encoding used to determine which memory address bit position represents the low order DDR
                                                         ROW address. Refer to
                                                         LMC(0..0)_CONFIG[ROW_LSB].
                                                         Refer to Cache-block Read Transaction Example. */
	uint64_t reserved_4_15                : 12;
	uint64_t cs_mask                      : 4;  /**< Chip-select mask. This mask corresponds to the four chip-select signals for a memory
                                                         configuration. Each reference address asserts one of the chip-select signals. If that
                                                         chip-select signal has its corresponding CS_MASK bit set, then the config1 parameters are
                                                         used, otherwise the config0 parameters are used. */
#else
	uint64_t cs_mask                      : 4;
	uint64_t reserved_4_15                : 12;
	uint64_t row_lsb                      : 3;
	uint64_t reserved_19_63               : 45;
#endif
	} cn70xx;
	struct cvmx_lmcx_dual_memcfg_cn70xx   cn78xx;
	struct cvmx_lmcx_dual_memcfg_cn61xx   cnf71xx;
};
typedef union cvmx_lmcx_dual_memcfg cvmx_lmcx_dual_memcfg_t;

/**
 * cvmx_lmc#_ecc_parity_test
 *
 * This register has bits to control the ECC and CA Parity errors creation during test modes.
 * ECC error is generated by enabling the CA_PARITY_CORRUPT_ENA bit of this register and
 * selecting any ECC_CORRUPT_IDX index of the dataword from the cacheline to be
 * corrupted. User can select which bit of the 128-bits dataword to corrupt by asserting
 * any of the CHAR_MASK0 and CHAR_MASK2 bits. (CHAR_MASK0 and CHAR_MASK2 corresponds to the
 * lower and upper 64-bit signal that can corrupt any individual bit of the data).
 *
 * CA Parity error is generated by enabling CA_PARITY_CORRUPT_ENA bit of this register and
 * selecting the DDR command that the parity is to be corrupted with through CA_PARITY_SEL.
 */
union cvmx_lmcx_ecc_parity_test {
	uint64_t u64;
	struct cvmx_lmcx_ecc_parity_test_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_12_63               : 52;
	uint64_t ecc_corrupt_ena              : 1;  /**< enables the ECC data corruption. */
	uint64_t ecc_corrupt_idx              : 3;  /**< selects the cacheline index that the dataword is to be corrupted with */
	uint64_t reserved_6_7                 : 2;
	uint64_t ca_parity_corrupt_ena        : 1;  /**< enables the CA Parity bit corruption. */
	uint64_t ca_parity_sel                : 5;  /**< selects the type of DDR command to corrupt the parity bit. */
#else
	uint64_t ca_parity_sel                : 5;
	uint64_t ca_parity_corrupt_ena        : 1;
	uint64_t reserved_6_7                 : 2;
	uint64_t ecc_corrupt_idx              : 3;
	uint64_t ecc_corrupt_ena              : 1;
	uint64_t reserved_12_63               : 52;
#endif
	} s;
	struct cvmx_lmcx_ecc_parity_test_s    cn78xx;
};
typedef union cvmx_lmcx_ecc_parity_test cvmx_lmcx_ecc_parity_test_t;

/**
 * cvmx_lmc#_ecc_synd
 *
 * LMC_ECC_SYND = MRD ECC Syndromes
 *
 */
union cvmx_lmcx_ecc_synd {
	uint64_t u64;
	struct cvmx_lmcx_ecc_synd_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t mrdsyn3                      : 8;  /**< MRD ECC Syndrome Quad3
                                                         MRDSYN3 corresponds to DQ[63:0]_c1_p1
                                                         In 32b mode, ecc is calculated on 4 cycle worth of data
                                                         MRDSYN3 corresponds to [DQ[31:0]_c3_p1, DQ[31:0]_c3_p0]
                                                           where _cC_pP denotes cycle C and phase P */
	uint64_t mrdsyn2                      : 8;  /**< MRD ECC Syndrome Quad2
                                                         MRDSYN2 corresponds to DQ[63:0]_c1_p0
                                                         In 32b mode, ecc is calculated on 4 cycle worth of data
                                                         MRDSYN2 corresponds to [DQ[31:0]_c2_p1, DQ[31:0]_c2_p0]
                                                           where _cC_pP denotes cycle C and phase P */
	uint64_t mrdsyn1                      : 8;  /**< MRD ECC Syndrome Quad1
                                                         MRDSYN1 corresponds to DQ[63:0]_c0_p1
                                                         In 32b mode, ecc is calculated on 4 cycle worth of data
                                                         MRDSYN1 corresponds to [DQ[31:0]_c1_p1, DQ[31:0]_c1_p0]
                                                           where _cC_pP denotes cycle C and phase P */
	uint64_t mrdsyn0                      : 8;  /**< MRD ECC Syndrome Quad0
                                                         MRDSYN0 corresponds to DQ[63:0]_c0_p0
                                                         In 32b mode, ecc is calculated on 4 cycle worth of data
                                                         MRDSYN0 corresponds to [DQ[31:0]_c0_p1, DQ[31:0]_c0_p0]
                                                           where _cC_pP denotes cycle C and phase P */
#else
	uint64_t mrdsyn0                      : 8;
	uint64_t mrdsyn1                      : 8;
	uint64_t mrdsyn2                      : 8;
	uint64_t mrdsyn3                      : 8;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_ecc_synd_s           cn30xx;
	struct cvmx_lmcx_ecc_synd_s           cn31xx;
	struct cvmx_lmcx_ecc_synd_s           cn38xx;
	struct cvmx_lmcx_ecc_synd_s           cn38xxp2;
	struct cvmx_lmcx_ecc_synd_s           cn50xx;
	struct cvmx_lmcx_ecc_synd_s           cn52xx;
	struct cvmx_lmcx_ecc_synd_s           cn52xxp1;
	struct cvmx_lmcx_ecc_synd_s           cn56xx;
	struct cvmx_lmcx_ecc_synd_s           cn56xxp1;
	struct cvmx_lmcx_ecc_synd_s           cn58xx;
	struct cvmx_lmcx_ecc_synd_s           cn58xxp1;
	struct cvmx_lmcx_ecc_synd_s           cn61xx;
	struct cvmx_lmcx_ecc_synd_s           cn63xx;
	struct cvmx_lmcx_ecc_synd_s           cn63xxp1;
	struct cvmx_lmcx_ecc_synd_s           cn66xx;
	struct cvmx_lmcx_ecc_synd_s           cn68xx;
	struct cvmx_lmcx_ecc_synd_s           cn68xxp1;
	struct cvmx_lmcx_ecc_synd_s           cn70xx;
	struct cvmx_lmcx_ecc_synd_s           cn78xx;
	struct cvmx_lmcx_ecc_synd_s           cnf71xx;
};
typedef union cvmx_lmcx_ecc_synd cvmx_lmcx_ecc_synd_t;

/**
 * cvmx_lmc#_ext_config
 *
 * This register has additional configuration and control bits for the LMC.
 *
 */
union cvmx_lmcx_ext_config {
	uint64_t u64;
	struct cvmx_lmcx_ext_config_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_46_63               : 18;
	uint64_t error_alert_n_sample         : 1;  /**< Read to get a sample of the DRAM error_alert_n pin. */
	uint64_t ea_int_polarity              : 1;  /**< Set to invert error_alert_n interrupt polarity.  When clear, interrupt will be signaled
                                                         on the rising edge of error_alert_n.  When set, interrupt will be signeld on the falling
                                                         edge of error_alert_n. */
	uint64_t reserved_43_43               : 1;
	uint64_t par_addr_mask                : 3;  /**< Mask applied to parity for address bits 14, 13, and 12.  Clear to exclude these
                                                         address bits from the parity calculation, necessary if the DRAM device does not
                                                         have these pins. */
	uint64_t reserved_38_39               : 2;
	uint64_t mrs_cmd_override             : 1;  /**< Set to override behavior of MRS and RCS DRAM operations. */
	uint64_t mrs_cmd_select               : 1;  /**< When LMC(0..3)_EXT_CONFIG[MRS_CMD_OVERRIDE] is set, use this bit to select which
                                                         style of operation for MRS and RCW commands.  If clear, select operation where
                                                         signals other than CS are active before and after the CS_N active cycle.  When set,
                                                         select operation where the other command signals (RAS_N,CAS_N,WE_n,ADDR,etc) all are
                                                         active only during the cycle where the CS_N is also active. */
	uint64_t reserved_33_35               : 3;
	uint64_t invert_data                  : 1;  /**< Set this bit to cause all data to be inverted before writing or reading to/from
                                                         DRAM - this effectively uses the scramble logic to instead invert all the data,
                                                         so this bit must not be set if data scrambling is enabled.  May be useful if
                                                         data inversion will result in lower power. */
	uint64_t reserved_30_31               : 2;
	uint64_t cmd_rti                      : 1;  /**< Set this bit to change the behavior of the LMC to return to a completely
                                                         idle command (no CS active, no command pins active, and address/ba/bg all low)
                                                         on the interface after an active command, rather than only forcing the CS
                                                         inactive between commands. */
	uint64_t cal_ena                      : 1;  /**< Set to cause LMC to operate in CAL mode.  DRAM mode registers must first be
                                                         programmed into CAL mode, then set CAL_ENABLE. */
	uint64_t reserved_27_27               : 1;
	uint64_t par_include_a17              : 1;  /**< If set, include A17 in parity calculations in DDR4 mode. */
	uint64_t par_include_bg1              : 1;  /**< If set, include BG1 in parity calculations in DDR4 mode. */
	uint64_t gen_par                      : 1;  /**< Enable parity generation in the DRAM commands, must be set prior to enabling
                                                         parity in register or DRAM devices */
	uint64_t reserved_21_23               : 3;
	uint64_t vrefint_seq_deskew           : 1;  /**< Personality bit to change the operation of what is normally the internal
                                                         vref training sequence into the deskew training sequence. */
	uint64_t read_ena_bprch               : 1;  /**< Enable pad receiver one cycle longer than normal during read operations. */
	uint64_t read_ena_fprch               : 1;  /**< Enable pad receiver starting one cycle earlier than normal during read operations. */
	uint64_t slot_ctl_reset_force         : 1;  /**< Write 1 to reset the slot-control override for all slot-control registers. After writing a
                                                         1 to this bit, slot-control registers will update with changes made to other timing-
                                                         control registers. This is a one-shot operation; it automatically returns to 0 after a
                                                         write to 1. */
	uint64_t ref_int_lsbs                 : 9;  /**< Refresh-interval value least-significant bits. The default is 0x0; but it can be set to a
                                                         non-zero value to get a more precise refresh interval. */
	uint64_t drive_ena_bprch              : 1;  /**< Drive DQx for one cycle longer than normal during write operations. */
	uint64_t drive_ena_fprch              : 1;  /**< Drive DQX starting one cycle earlier than normal during write operations. */
	uint64_t dlcram_flip_synd             : 2;  /**< Reserved. INTERNAL: DLC RAM flip syndrome control bits. */
	uint64_t dlcram_cor_dis               : 1;  /**< Reserved. INTERNAL: DLC RAM correction disable control. */
	uint64_t dlc_nxm_rd                   : 1;  /**< When set, enable NXM events for HFA read operations. INTERNAL: Default is disabled, but
                                                         could be useful for debug of DLC/DFA accesses. */
	uint64_t l2c_nxm_rd                   : 1;  /**< When set, enable NXM events for L2C read operations. INTERNAL: Default is disabled as L2C
                                                         NXM read operations are possible and expected during normal operation. */
	uint64_t l2c_nxm_wr                   : 1;  /**< When set, enable NXM events for L2C write operations. */
#else
	uint64_t l2c_nxm_wr                   : 1;
	uint64_t l2c_nxm_rd                   : 1;
	uint64_t dlc_nxm_rd                   : 1;
	uint64_t dlcram_cor_dis               : 1;
	uint64_t dlcram_flip_synd             : 2;
	uint64_t drive_ena_fprch              : 1;
	uint64_t drive_ena_bprch              : 1;
	uint64_t ref_int_lsbs                 : 9;
	uint64_t slot_ctl_reset_force         : 1;
	uint64_t read_ena_fprch               : 1;
	uint64_t read_ena_bprch               : 1;
	uint64_t vrefint_seq_deskew           : 1;
	uint64_t reserved_21_23               : 3;
	uint64_t gen_par                      : 1;
	uint64_t par_include_bg1              : 1;
	uint64_t par_include_a17              : 1;
	uint64_t reserved_27_27               : 1;
	uint64_t cal_ena                      : 1;
	uint64_t cmd_rti                      : 1;
	uint64_t reserved_30_31               : 2;
	uint64_t invert_data                  : 1;
	uint64_t reserved_33_35               : 3;
	uint64_t mrs_cmd_select               : 1;
	uint64_t mrs_cmd_override             : 1;
	uint64_t reserved_38_39               : 2;
	uint64_t par_addr_mask                : 3;
	uint64_t reserved_43_43               : 1;
	uint64_t ea_int_polarity              : 1;
	uint64_t error_alert_n_sample         : 1;
	uint64_t reserved_46_63               : 18;
#endif
	} s;
	struct cvmx_lmcx_ext_config_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_21_63               : 43;
	uint64_t vrefint_seq_deskew           : 1;  /**< Personality bit to change the operation of what is normally the internal Vref training
                                                         sequence into the deskew training sequence. */
	uint64_t read_ena_bprch               : 1;  /**< Enable pad receiver one cycle longer than normal during read operations. */
	uint64_t read_ena_fprch               : 1;  /**< Enable pad receiver starting one cycle earlier than normal during read operations. */
	uint64_t slot_ctl_reset_force         : 1;  /**< Write 1 to reset the slot-control override for all slot-control registers. After writing a
                                                         1 to this bit, slot-control registers will update with changes made to other timing-
                                                         control registers. This is a one-shot operation; it automatically returns to 0 after a
                                                         write to 1. */
	uint64_t ref_int_lsbs                 : 9;  /**< Refresh-interval value least-significant bits. The default is 0x0; but it can be set to a
                                                         non-zero value to get a more precise refresh interval. */
	uint64_t drive_ena_bprch              : 1;  /**< Drive DQx for one cycle longer than normal during write operations. */
	uint64_t drive_ena_fprch              : 1;  /**< Drive DQX starting one cycle earlier than normal during write operations. */
	uint64_t dlcram_flip_synd             : 2;  /**< Reserved. INTERNAL: DLC RAM flip syndrome control bits. */
	uint64_t dlcram_cor_dis               : 1;  /**< Reserved. INTERNAL: DLC RAM correction disable control. */
	uint64_t dlc_nxm_rd                   : 1;  /**< When set, enable NXM events for HFA read operations. INTERNAL: Default is disabled, but
                                                         could be useful for debug of DLC/DFA accesses. */
	uint64_t l2c_nxm_rd                   : 1;  /**< When set, enable NXM events for L2C read operations. INTERNAL: Default is disabled as L2C
                                                         NXM read operations are possible and expected during normal operation. */
	uint64_t l2c_nxm_wr                   : 1;  /**< When set, enable NXM events for L2C write operations. */
#else
	uint64_t l2c_nxm_wr                   : 1;
	uint64_t l2c_nxm_rd                   : 1;
	uint64_t dlc_nxm_rd                   : 1;
	uint64_t dlcram_cor_dis               : 1;
	uint64_t dlcram_flip_synd             : 2;
	uint64_t drive_ena_fprch              : 1;
	uint64_t drive_ena_bprch              : 1;
	uint64_t ref_int_lsbs                 : 9;
	uint64_t slot_ctl_reset_force         : 1;
	uint64_t read_ena_fprch               : 1;
	uint64_t read_ena_bprch               : 1;
	uint64_t vrefint_seq_deskew           : 1;
	uint64_t reserved_21_63               : 43;
#endif
	} cn70xx;
	struct cvmx_lmcx_ext_config_s         cn78xx;
};
typedef union cvmx_lmcx_ext_config cvmx_lmcx_ext_config_t;

/**
 * cvmx_lmc#_fadr
 *
 * This register only captures the first transaction with ECC errors. A DED error can over-write
 * this register with its failing addresses if the first error was a SEC. If you write
 * LMC(0..3)_INT -> SEC_ERR/DED_ERR, it clears the error bits and captures the next failing
 * address. If FDIMM is 1, that means the error is in the high DIMM.
 * LMC(0..3)_FADR captures the failing pre-scrambled address location (split into DIMM, bunk,
 * bank, etc). If scrambling is off, then LMC(0..3)_FADR will also capture the failing physical
 * location in the DRAM parts. LMC(0..3)_SCRAMBLED_FADR captures the actual failing address
 * location in the physical DRAM parts, i.e.,
 * If scrambling is on, LMC(0..3)_SCRAMBLED_FADR contains the failing physical location in the
 * DRAM parts (split into DIMM, bunk, bank, etc.)
 * If scrambling is off, the pre-scramble and post-scramble addresses are the same; and so the
 * contents of LMC(0..3)_SCRAMBLED_FADR match the contents of LMC(0..3)_FADR.
 */
union cvmx_lmcx_fadr {
	uint64_t u64;
	struct cvmx_lmcx_fadr_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_40_63               : 24;
	uint64_t fill_order                   : 2;  /**< Fill order for failing transaction. */
	uint64_t reserved_0_37                : 38;
#else
	uint64_t reserved_0_37                : 38;
	uint64_t fill_order                   : 2;
	uint64_t reserved_40_63               : 24;
#endif
	} s;
	struct cvmx_lmcx_fadr_cn30xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t fdimm                        : 2;  /**< Failing DIMM# */
	uint64_t fbunk                        : 1;  /**< Failing Rank */
	uint64_t fbank                        : 3;  /**< Failing Bank[2:0] */
	uint64_t frow                         : 14; /**< Failing Row Address[13:0] */
	uint64_t fcol                         : 12; /**< Failing Column Start Address[11:0]
                                                         Represents the Failing read's starting column address
                                                         (and not the exact column address in which the SEC/DED
                                                         was detected) */
#else
	uint64_t fcol                         : 12;
	uint64_t frow                         : 14;
	uint64_t fbank                        : 3;
	uint64_t fbunk                        : 1;
	uint64_t fdimm                        : 2;
	uint64_t reserved_32_63               : 32;
#endif
	} cn30xx;
	struct cvmx_lmcx_fadr_cn30xx          cn31xx;
	struct cvmx_lmcx_fadr_cn30xx          cn38xx;
	struct cvmx_lmcx_fadr_cn30xx          cn38xxp2;
	struct cvmx_lmcx_fadr_cn30xx          cn50xx;
	struct cvmx_lmcx_fadr_cn30xx          cn52xx;
	struct cvmx_lmcx_fadr_cn30xx          cn52xxp1;
	struct cvmx_lmcx_fadr_cn30xx          cn56xx;
	struct cvmx_lmcx_fadr_cn30xx          cn56xxp1;
	struct cvmx_lmcx_fadr_cn30xx          cn58xx;
	struct cvmx_lmcx_fadr_cn30xx          cn58xxp1;
	struct cvmx_lmcx_fadr_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_36_63               : 28;
	uint64_t fdimm                        : 2;  /**< Failing DIMM# */
	uint64_t fbunk                        : 1;  /**< Failing Rank */
	uint64_t fbank                        : 3;  /**< Failing Bank[2:0] */
	uint64_t frow                         : 16; /**< Failing Row Address[15:0] */
	uint64_t fcol                         : 14; /**< Failing Column Address[13:0]
                                                         Technically, represents the address of the 128b data
                                                         that had an ecc error, i.e., fcol[0] is always 0. Can
                                                         be used in conjuction with LMC*_CONFIG[DED_ERR] to
                                                         isolate the 64b chunk of data in error */
#else
	uint64_t fcol                         : 14;
	uint64_t frow                         : 16;
	uint64_t fbank                        : 3;
	uint64_t fbunk                        : 1;
	uint64_t fdimm                        : 2;
	uint64_t reserved_36_63               : 28;
#endif
	} cn61xx;
	struct cvmx_lmcx_fadr_cn61xx          cn63xx;
	struct cvmx_lmcx_fadr_cn61xx          cn63xxp1;
	struct cvmx_lmcx_fadr_cn61xx          cn66xx;
	struct cvmx_lmcx_fadr_cn61xx          cn68xx;
	struct cvmx_lmcx_fadr_cn61xx          cn68xxp1;
	struct cvmx_lmcx_fadr_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_40_63               : 24;
	uint64_t fill_order                   : 2;  /**< Fill order for failing transaction. */
	uint64_t fdimm                        : 1;  /**< Failing DIMM number. CN70XX/CN71XX only supports one DIMM, so this bit will always
                                                         return a 0. */
	uint64_t fbunk                        : 1;  /**< Failing rank number. */
	uint64_t fbank                        : 4;  /**< Failing bank number. Bits <3:0>. */
	uint64_t frow                         : 18; /**< Failing row address. Bits <17:0>. */
	uint64_t fcol                         : 14; /**< Failing column address <13:0>. Technically, represents the address of the 64b data that
                                                         had an ECC error, i.e., FCOL[0] is always 0. Can be used in conjunction with
                                                         LMC(0..0)_INT[DED_ERR] to isolate the 64b chunk of data in error. */
#else
	uint64_t fcol                         : 14;
	uint64_t frow                         : 18;
	uint64_t fbank                        : 4;
	uint64_t fbunk                        : 1;
	uint64_t fdimm                        : 1;
	uint64_t fill_order                   : 2;
	uint64_t reserved_40_63               : 24;
#endif
	} cn70xx;
	struct cvmx_lmcx_fadr_cn70xx          cn78xx;
	struct cvmx_lmcx_fadr_cn61xx          cnf71xx;
};
typedef union cvmx_lmcx_fadr cvmx_lmcx_fadr_t;

/**
 * cvmx_lmc#_ifb_cnt
 *
 * LMC_IFB_CNT  = Performance Counters
 *
 */
union cvmx_lmcx_ifb_cnt {
	uint64_t u64;
	struct cvmx_lmcx_ifb_cnt_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t ifbcnt                       : 64; /**< Performance Counter
                                                         64-bit counter that increments every
                                                         CK cycle there is something in the in-flight buffer. */
#else
	uint64_t ifbcnt                       : 64;
#endif
	} s;
	struct cvmx_lmcx_ifb_cnt_s            cn61xx;
	struct cvmx_lmcx_ifb_cnt_s            cn63xx;
	struct cvmx_lmcx_ifb_cnt_s            cn63xxp1;
	struct cvmx_lmcx_ifb_cnt_s            cn66xx;
	struct cvmx_lmcx_ifb_cnt_s            cn68xx;
	struct cvmx_lmcx_ifb_cnt_s            cn68xxp1;
	struct cvmx_lmcx_ifb_cnt_s            cn70xx;
	struct cvmx_lmcx_ifb_cnt_s            cn78xx;
	struct cvmx_lmcx_ifb_cnt_s            cnf71xx;
};
typedef union cvmx_lmcx_ifb_cnt cvmx_lmcx_ifb_cnt_t;

/**
 * cvmx_lmc#_ifb_cnt_hi
 *
 * LMC_IFB_CNT_HI  = Performance Counters
 *
 */
union cvmx_lmcx_ifb_cnt_hi {
	uint64_t u64;
	struct cvmx_lmcx_ifb_cnt_hi_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ifbcnt_hi                    : 32; /**< Performance Counter to measure Bus Utilization
                                                         Upper 32-bits of 64-bit counter that increments every
                                                         cycle there is something in the in-flight buffer. */
#else
	uint64_t ifbcnt_hi                    : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn30xx;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn31xx;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn38xx;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn38xxp2;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn50xx;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn52xx;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn52xxp1;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn56xx;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn56xxp1;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn58xx;
	struct cvmx_lmcx_ifb_cnt_hi_s         cn58xxp1;
};
typedef union cvmx_lmcx_ifb_cnt_hi cvmx_lmcx_ifb_cnt_hi_t;

/**
 * cvmx_lmc#_ifb_cnt_lo
 *
 * LMC_IFB_CNT_LO  = Performance Counters
 *
 */
union cvmx_lmcx_ifb_cnt_lo {
	uint64_t u64;
	struct cvmx_lmcx_ifb_cnt_lo_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ifbcnt_lo                    : 32; /**< Performance Counter
                                                         Low 32-bits of 64-bit counter that increments every
                                                         cycle there is something in the in-flight buffer. */
#else
	uint64_t ifbcnt_lo                    : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn30xx;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn31xx;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn38xx;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn38xxp2;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn50xx;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn52xx;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn52xxp1;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn56xx;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn56xxp1;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn58xx;
	struct cvmx_lmcx_ifb_cnt_lo_s         cn58xxp1;
};
typedef union cvmx_lmcx_ifb_cnt_lo cvmx_lmcx_ifb_cnt_lo_t;

/**
 * cvmx_lmc#_int
 *
 * LMC_INT = LMC Interrupt Register
 *
 */
union cvmx_lmcx_int {
	uint64_t u64;
	struct cvmx_lmcx_int_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_12_63               : 52;
	uint64_t ddr_err                      : 1;  /**< DDR RAM error alert interrupt. */
	uint64_t dlcram_ded_err               : 1;  /**< DLC RAM ECC double error detect (DED). */
	uint64_t dlcram_sec_err               : 1;  /**< DLC RAM ECC single error correct (SEC). */
	uint64_t ded_err                      : 4;  /**< Double Error detected (DED) of Rd Data
                                                         [0] corresponds to DQ[63:0]_c0_p0
                                                         [1] corresponds to DQ[63:0]_c0_p1
                                                         [2] corresponds to DQ[63:0]_c1_p0
                                                         [3] corresponds to DQ[63:0]_c1_p1
                                                         In 32b mode, ecc is calculated on 4 cycle worth of data
                                                         [0] corresponds to [DQ[31:0]_c0_p1, DQ[31:0]_c0_p0]
                                                         [1] corresponds to [DQ[31:0]_c1_p1, DQ[31:0]_c1_p0]
                                                         [2] corresponds to [DQ[31:0]_c2_p1, DQ[31:0]_c2_p0]
                                                         [3] corresponds to [DQ[31:0]_c3_p1, DQ[31:0]_c3_p0]
                                                          where _cC_pP denotes cycle C and phase P
                                                          Write of 1 will clear the corresponding error bit */
	uint64_t sec_err                      : 4;  /**< Single Error (corrected) of Rd Data
                                                         [0] corresponds to DQ[63:0]_c0_p0
                                                         [1] corresponds to DQ[63:0]_c0_p1
                                                         [2] corresponds to DQ[63:0]_c1_p0
                                                         [3] corresponds to DQ[63:0]_c1_p1
                                                         In 32b mode, ecc is calculated on 4 cycle worth of data
                                                         [0] corresponds to [DQ[31:0]_c0_p1, DQ[31:0]_c0_p0]
                                                         [1] corresponds to [DQ[31:0]_c1_p1, DQ[31:0]_c1_p0]
                                                         [2] corresponds to [DQ[31:0]_c2_p1, DQ[31:0]_c2_p0]
                                                         [3] corresponds to [DQ[31:0]_c3_p1, DQ[31:0]_c3_p0]
                                                          where _cC_pP denotes cycle C and phase P
                                                          Write of 1 will clear the corresponding error bit */
	uint64_t nxm_wr_err                   : 1;  /**< Write to non-existent memory
                                                         Write of 1 will clear the corresponding error bit */
#else
	uint64_t nxm_wr_err                   : 1;
	uint64_t sec_err                      : 4;
	uint64_t ded_err                      : 4;
	uint64_t dlcram_sec_err               : 1;
	uint64_t dlcram_ded_err               : 1;
	uint64_t ddr_err                      : 1;
	uint64_t reserved_12_63               : 52;
#endif
	} s;
	struct cvmx_lmcx_int_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_9_63                : 55;
	uint64_t ded_err                      : 4;  /**< Double Error detected (DED) of Rd Data
                                                         [0] corresponds to DQ[63:0]_c0_p0
                                                         [1] corresponds to DQ[63:0]_c0_p1
                                                         [2] corresponds to DQ[63:0]_c1_p0
                                                         [3] corresponds to DQ[63:0]_c1_p1
                                                         In 32b mode, ecc is calculated on 4 cycle worth of data
                                                         [0] corresponds to [DQ[31:0]_c0_p1, DQ[31:0]_c0_p0]
                                                         [1] corresponds to [DQ[31:0]_c1_p1, DQ[31:0]_c1_p0]
                                                         [2] corresponds to [DQ[31:0]_c2_p1, DQ[31:0]_c2_p0]
                                                         [3] corresponds to [DQ[31:0]_c3_p1, DQ[31:0]_c3_p0]
                                                          where _cC_pP denotes cycle C and phase P
                                                          Write of 1 will clear the corresponding error bit */
	uint64_t sec_err                      : 4;  /**< Single Error (corrected) of Rd Data
                                                         [0] corresponds to DQ[63:0]_c0_p0
                                                         [1] corresponds to DQ[63:0]_c0_p1
                                                         [2] corresponds to DQ[63:0]_c1_p0
                                                         [3] corresponds to DQ[63:0]_c1_p1
                                                         In 32b mode, ecc is calculated on 4 cycle worth of data
                                                         [0] corresponds to [DQ[31:0]_c0_p1, DQ[31:0]_c0_p0]
                                                         [1] corresponds to [DQ[31:0]_c1_p1, DQ[31:0]_c1_p0]
                                                         [2] corresponds to [DQ[31:0]_c2_p1, DQ[31:0]_c2_p0]
                                                         [3] corresponds to [DQ[31:0]_c3_p1, DQ[31:0]_c3_p0]
                                                          where _cC_pP denotes cycle C and phase P
                                                          Write of 1 will clear the corresponding error bit */
	uint64_t nxm_wr_err                   : 1;  /**< Write to non-existent memory
                                                         Write of 1 will clear the corresponding error bit */
#else
	uint64_t nxm_wr_err                   : 1;
	uint64_t sec_err                      : 4;
	uint64_t ded_err                      : 4;
	uint64_t reserved_9_63                : 55;
#endif
	} cn61xx;
	struct cvmx_lmcx_int_cn61xx           cn63xx;
	struct cvmx_lmcx_int_cn61xx           cn63xxp1;
	struct cvmx_lmcx_int_cn61xx           cn66xx;
	struct cvmx_lmcx_int_cn61xx           cn68xx;
	struct cvmx_lmcx_int_cn61xx           cn68xxp1;
	struct cvmx_lmcx_int_s                cn70xx;
	struct cvmx_lmcx_int_s                cn78xx;
	struct cvmx_lmcx_int_cn61xx           cnf71xx;
};
typedef union cvmx_lmcx_int cvmx_lmcx_int_t;

/**
 * cvmx_lmc#_int_en
 *
 * LMC_INT_EN = LMC Interrupt Enable Register
 *
 */
union cvmx_lmcx_int_en {
	uint64_t u64;
	struct cvmx_lmcx_int_en_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_6_63                : 58;
	uint64_t ddr_error_alert_ena          : 1;  /**< DDR4 error alert interrupt enable bit. */
	uint64_t dlcram_ded_ena               : 1;  /**< DLC RAM ECC double error detect (DED) interrupt enable bit. */
	uint64_t dlcram_sec_ena               : 1;  /**< DLC RAM ECC single error correct (SEC) interrupt enable bit. */
	uint64_t intr_ded_ena                 : 1;  /**< ECC Double Error Detect(DED) Interrupt Enable bit
                                                         When set, the memory controller raises a processor
                                                         interrupt on detecting an uncorrectable Dbl Bit ECC
                                                         error. */
	uint64_t intr_sec_ena                 : 1;  /**< ECC Single Error Correct(SEC) Interrupt Enable bit
                                                         When set, the memory controller raises a processor
                                                         interrupt on detecting a correctable Single Bit ECC
                                                         error. */
	uint64_t intr_nxm_wr_ena              : 1;  /**< Non Write Error Interrupt Enable bit
                                                         When set, the memory controller raises a processor
                                                         interrupt on detecting an non-existent memory write */
#else
	uint64_t intr_nxm_wr_ena              : 1;
	uint64_t intr_sec_ena                 : 1;
	uint64_t intr_ded_ena                 : 1;
	uint64_t dlcram_sec_ena               : 1;
	uint64_t dlcram_ded_ena               : 1;
	uint64_t ddr_error_alert_ena          : 1;
	uint64_t reserved_6_63                : 58;
#endif
	} s;
	struct cvmx_lmcx_int_en_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_3_63                : 61;
	uint64_t intr_ded_ena                 : 1;  /**< ECC Double Error Detect(DED) Interrupt Enable bit
                                                         When set, the memory controller raises a processor
                                                         interrupt on detecting an uncorrectable Dbl Bit ECC
                                                         error. */
	uint64_t intr_sec_ena                 : 1;  /**< ECC Single Error Correct(SEC) Interrupt Enable bit
                                                         When set, the memory controller raises a processor
                                                         interrupt on detecting a correctable Single Bit ECC
                                                         error. */
	uint64_t intr_nxm_wr_ena              : 1;  /**< Non Write Error Interrupt Enable bit
                                                         When set, the memory controller raises a processor
                                                         interrupt on detecting an non-existent memory write */
#else
	uint64_t intr_nxm_wr_ena              : 1;
	uint64_t intr_sec_ena                 : 1;
	uint64_t intr_ded_ena                 : 1;
	uint64_t reserved_3_63                : 61;
#endif
	} cn61xx;
	struct cvmx_lmcx_int_en_cn61xx        cn63xx;
	struct cvmx_lmcx_int_en_cn61xx        cn63xxp1;
	struct cvmx_lmcx_int_en_cn61xx        cn66xx;
	struct cvmx_lmcx_int_en_cn61xx        cn68xx;
	struct cvmx_lmcx_int_en_cn61xx        cn68xxp1;
	struct cvmx_lmcx_int_en_s             cn70xx;
	struct cvmx_lmcx_int_en_s             cn78xx;
	struct cvmx_lmcx_int_en_cn61xx        cnf71xx;
};
typedef union cvmx_lmcx_int_en cvmx_lmcx_int_en_t;

/**
 * cvmx_lmc#_lane#_crc_swiz
 *
 * This register contains the CRC bit swizzle for even and odd ranks.
 *
 */
union cvmx_lmcx_lanex_crc_swiz {
	uint64_t u64;
	struct cvmx_lmcx_lanex_crc_swiz_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_56_63               : 8;
	uint64_t r1_swiz7                     : 3;  /**< Bit select for odd rank, bit 7. */
	uint64_t r1_swiz6                     : 3;  /**< Bit select for odd rank, bit 6. */
	uint64_t r1_swiz5                     : 3;  /**< Bit select for odd rank, bit 5. */
	uint64_t r1_swiz4                     : 3;  /**< Bit select for odd rank, bit 4. */
	uint64_t r1_swiz3                     : 3;  /**< Bit select for odd rank, bit 3. */
	uint64_t r1_swiz2                     : 3;  /**< Bit select for odd rank, bit 2. */
	uint64_t r1_swiz1                     : 3;  /**< Bit select for odd rank, bit 1. */
	uint64_t r1_swiz0                     : 3;  /**< Bit select for odd rank, bit 0. */
	uint64_t reserved_24_31               : 8;
	uint64_t r0_swiz7                     : 3;  /**< Bit select for even rank, bit 7. */
	uint64_t r0_swiz6                     : 3;  /**< Bit select for even rank, bit 6. */
	uint64_t r0_swiz5                     : 3;  /**< Bit select for even rank, bit 5. */
	uint64_t r0_swiz4                     : 3;  /**< Bit select for even rank, bit 4. */
	uint64_t r0_swiz3                     : 3;  /**< Bit select for even rank, bit 3. */
	uint64_t r0_swiz2                     : 3;  /**< Bit select for even rank, bit 2. */
	uint64_t r0_swiz1                     : 3;  /**< Bit select for even rank, bit 1. */
	uint64_t r0_swiz0                     : 3;  /**< Bit select for even rank, bit 0. */
#else
	uint64_t r0_swiz0                     : 3;
	uint64_t r0_swiz1                     : 3;
	uint64_t r0_swiz2                     : 3;
	uint64_t r0_swiz3                     : 3;
	uint64_t r0_swiz4                     : 3;
	uint64_t r0_swiz5                     : 3;
	uint64_t r0_swiz6                     : 3;
	uint64_t r0_swiz7                     : 3;
	uint64_t reserved_24_31               : 8;
	uint64_t r1_swiz0                     : 3;
	uint64_t r1_swiz1                     : 3;
	uint64_t r1_swiz2                     : 3;
	uint64_t r1_swiz3                     : 3;
	uint64_t r1_swiz4                     : 3;
	uint64_t r1_swiz5                     : 3;
	uint64_t r1_swiz6                     : 3;
	uint64_t r1_swiz7                     : 3;
	uint64_t reserved_56_63               : 8;
#endif
	} s;
	struct cvmx_lmcx_lanex_crc_swiz_s     cn78xx;
};
typedef union cvmx_lmcx_lanex_crc_swiz cvmx_lmcx_lanex_crc_swiz_t;

/**
 * cvmx_lmc#_mem_cfg0
 *
 * Specify the RSL base addresses for the block
 *
 *                  LMC_MEM_CFG0 = LMC Memory Configuration Register0
 *
 * This register controls certain parameters of  Memory Configuration
 */
union cvmx_lmcx_mem_cfg0 {
	uint64_t u64;
	struct cvmx_lmcx_mem_cfg0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t reset                        : 1;  /**< Reset oneshot pulse for refresh counter,
                                                         and LMC_OPS_CNT_*, LMC_IFB_CNT_*, and LMC_DCLK_CNT_*
                                                         CSR's. SW should write this to a one, then re-write
                                                         it to a zero to cause the reset. */
	uint64_t silo_qc                      : 1;  /**< Adds a Quarter Cycle granularity to generate
                                                         dqs pulse generation for silo.
                                                         Combination of Silo_HC and Silo_QC gives the
                                                         ability to position the read enable with quarter
                                                         cycle resolution. This is applied on all the bytes
                                                         uniformly. */
	uint64_t bunk_ena                     : 1;  /**< Bunk Enable aka RANK ena (for use with dual-rank DIMMs)
                                                         For dual-rank DIMMs, the bunk_ena bit will enable
                                                         the drive of the CS_N[1:0] pins based on the
                                                         (pbank_lsb-1) address bit.
                                                         Write 0 for SINGLE ranked DIMM's. */
	uint64_t ded_err                      : 4;  /**< Double Error detected (DED) of Rd Data
                                                         In 128b mode, ecc is calulated on 1 cycle worth of data
                                                         [25] corresponds to DQ[63:0], Phase0
                                                         [26] corresponds to DQ[127:64], Phase0
                                                         [27] corresponds to DQ[63:0], Phase1
                                                         [28] corresponds to DQ[127:64], Phase1
                                                         In 64b mode, ecc is calculated on 2 cycle worth of data
                                                         [25] corresponds to DQ[63:0], Phase0, cycle0
                                                         [26] corresponds to DQ[63:0], Phase0, cycle1
                                                         [27] corresponds to DQ[63:0], Phase1, cycle0
                                                         [28] corresponds to DQ[63:0], Phase1, cycle1
                                                         Write of 1 will clear the corresponding error bit */
	uint64_t sec_err                      : 4;  /**< Single Error (corrected) of Rd Data
                                                         In 128b mode, ecc is calulated on 1 cycle worth of data
                                                         [21] corresponds to DQ[63:0], Phase0
                                                         [22] corresponds to DQ[127:64], Phase0
                                                         [23] corresponds to DQ[63:0], Phase1
                                                         [24] corresponds to DQ[127:64], Phase1
                                                         In 64b mode, ecc is calculated on 2 cycle worth of data
                                                         [21] corresponds to DQ[63:0], Phase0, cycle0
                                                         [22] corresponds to DQ[63:0], Phase0, cycle1
                                                         [23] corresponds to DQ[63:0], Phase1, cycle0
                                                         [24] corresponds to DQ[63:0], Phase1, cycle1
                                                         Write of 1 will clear the corresponding error bit */
	uint64_t intr_ded_ena                 : 1;  /**< ECC Double Error Detect(DED) Interrupt Enable bit
                                                         When set, the memory controller raises a processor
                                                         interrupt on detecting an uncorrectable Dbl Bit ECC
                                                         error. */
	uint64_t intr_sec_ena                 : 1;  /**< ECC Single Error Correct(SEC) Interrupt Enable bit
                                                         When set, the memory controller raises a processor
                                                         interrupt on detecting a correctable Single Bit ECC
                                                         error. */
	uint64_t tcl                          : 4;  /**< This register is not used */
	uint64_t ref_int                      : 6;  /**< Refresh interval represented in \#of 512 dclk increments.
                                                         Program this to RND-DN(tREFI/clkPeriod/512)
                                                            - 000000: RESERVED
                                                            - 000001: 1 * 512  = 512 dclks
                                                             - ...
                                                            - 111111: 63 * 512 = 32256 dclks */
	uint64_t pbank_lsb                    : 4;  /**< Physical Bank address select
                                                                                 Reverting to the explanation for ROW_LSB,
                                                                                 PBank_LSB would be Row_LSB bit + \#rowbits
                                                                                 + \#rankbits
                                                                                 In the 512MB DIMM Example, assuming no rank bits:
                                                                                 pbank_lsb=mem_addr[15+13] for 64 b mode
                                                                                          =mem_addr[16+13] for 128b mode
                                                                                 Hence the parameter
                                                         0000:pbank[1:0] = mem_adr[28:27]    / rank = mem_adr[26] (if bunk_ena)
                                                         0001:pbank[1:0] = mem_adr[29:28]    / rank = mem_adr[27]      "
                                                         0010:pbank[1:0] = mem_adr[30:29]    / rank = mem_adr[28]      "
                                                         0011:pbank[1:0] = mem_adr[31:30]    / rank = mem_adr[29]      "
                                                         0100:pbank[1:0] = mem_adr[32:31]    / rank = mem_adr[30]      "
                                                         0101:pbank[1:0] = mem_adr[33:32]    / rank = mem_adr[31]      "
                                                         0110:pbank[1:0] =[1'b0,mem_adr[33]] / rank = mem_adr[32]      "
                                                         0111:pbank[1:0] =[2'b0]             / rank = mem_adr[33]      "
                                                         1000-1111: RESERVED */
	uint64_t row_lsb                      : 3;  /**< Encoding used to determine which memory address
                                                         bit position represents the low order DDR ROW address.
                                                         The processor's memory address[33:7] needs to be
                                                         translated to DRAM addresses (bnk,row,col,rank and dimm)
                                                         and that is a function of the following:
                                                         1. \# Banks (4 or 8) - spec'd by BANK8
                                                         2. Datapath Width(64 or 128) - MODE128b
                                                         3. \# Ranks in a DIMM - spec'd by BUNK_ENA
                                                         4. \# DIMM's in the system
                                                         5. \# Column Bits of the memory part - spec'd indirectly
                                                         by this register.
                                                         6. \# Row Bits of the memory part - spec'd indirectly
                                                         by the register below (PBANK_LSB).
                                                         Illustration: For Micron's MT18HTF6472A,512MB DDR2
                                                         Unbuffered DIMM which uses 256Mb parts (8M x 8 x 4),
                                                         \# Banks = 4 -> 2 bits of BA
                                                         \# Columns = 1K -> 10 bits of Col
                                                         \# Rows = 8K -> 13 bits of Row
                                                         Assuming that the total Data width is 128, this is how
                                                         we arrive at row_lsb:
                                                         Col Address starts from mem_addr[4] for 128b (16Bytes)
                                                         dq width or from mem_addr[3] for 64b (8Bytes) dq width
                                                         \# col + \# bank = 12. Hence row_lsb is mem_adr[15] for
                                                         64bmode or mem_adr[16] for 128b mode. Hence row_lsb
                                                         parameter should be set to 001 (64b) or 010 (128b).
                                                              - 000: row_lsb = mem_adr[14]
                                                              - 001: row_lsb = mem_adr[15]
                                                              - 010: row_lsb = mem_adr[16]
                                                              - 011: row_lsb = mem_adr[17]
                                                              - 100: row_lsb = mem_adr[18]
                                                              - 101-111:row_lsb = RESERVED */
	uint64_t ecc_ena                      : 1;  /**< ECC Enable: When set will enable the 8b ECC
                                                         check/correct logic. Should be 1 when used with DIMMs
                                                         with ECC. 0, otherwise.
                                                         When this mode is turned on, DQ[71:64] and DQ[143:137]
                                                         on writes, will contain the ECC code generated for
                                                         the lower 64 and upper 64 bits of data which will
                                                         written in the memory and then later on reads, used
                                                         to check for Single bit error (which will be auto-
                                                         corrected) and Double Bit error (which will be
                                                         reported). When not turned on, DQ[71:64] and DQ[143:137]
                                                         are driven to 0.  Please refer to SEC_ERR, DED_ERR,
                                                         LMC_FADR, and LMC_ECC_SYND registers
                                                         for diagnostics information when there is an error. */
	uint64_t init_start                   : 1;  /**< A 0->1 transition starts the DDR memory initialization
                                                         sequence. */
#else
	uint64_t init_start                   : 1;
	uint64_t ecc_ena                      : 1;
	uint64_t row_lsb                      : 3;
	uint64_t pbank_lsb                    : 4;
	uint64_t ref_int                      : 6;
	uint64_t tcl                          : 4;
	uint64_t intr_sec_ena                 : 1;
	uint64_t intr_ded_ena                 : 1;
	uint64_t sec_err                      : 4;
	uint64_t ded_err                      : 4;
	uint64_t bunk_ena                     : 1;
	uint64_t silo_qc                      : 1;
	uint64_t reset                        : 1;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_mem_cfg0_s           cn30xx;
	struct cvmx_lmcx_mem_cfg0_s           cn31xx;
	struct cvmx_lmcx_mem_cfg0_s           cn38xx;
	struct cvmx_lmcx_mem_cfg0_s           cn38xxp2;
	struct cvmx_lmcx_mem_cfg0_s           cn50xx;
	struct cvmx_lmcx_mem_cfg0_s           cn52xx;
	struct cvmx_lmcx_mem_cfg0_s           cn52xxp1;
	struct cvmx_lmcx_mem_cfg0_s           cn56xx;
	struct cvmx_lmcx_mem_cfg0_s           cn56xxp1;
	struct cvmx_lmcx_mem_cfg0_s           cn58xx;
	struct cvmx_lmcx_mem_cfg0_s           cn58xxp1;
};
typedef union cvmx_lmcx_mem_cfg0 cvmx_lmcx_mem_cfg0_t;

/**
 * cvmx_lmc#_mem_cfg1
 *
 * LMC_MEM_CFG1 = LMC Memory Configuration Register1
 *
 * This register controls the External Memory Configuration Timing Parameters. Please refer to the
 * appropriate DDR part spec from your memory vendor for the various values in this CSR.
 * The details of each of these timing parameters can be found in the JEDEC spec or the vendor
 * spec of the memory parts.
 */
union cvmx_lmcx_mem_cfg1 {
	uint64_t u64;
	struct cvmx_lmcx_mem_cfg1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t comp_bypass                  : 1;  /**< Compensation bypass. */
	uint64_t trrd                         : 3;  /**< tRRD cycles: ACT-ACT timing parameter for different
                                                         banks. (Represented in tCYC cycles == 1dclks)
                                                         TYP=15ns (66MHz=1,167MHz=3,200MHz=3)
                                                         For DDR2, TYP=7.5ns
                                                            - 000: RESERVED
                                                            - 001: 1 tCYC
                                                            - 010: 2 tCYC
                                                            - 011: 3 tCYC
                                                            - 100: 4 tCYC
                                                            - 101: 5 tCYC
                                                            - 110: 6 tCYC
                                                            - 111: 7 tCYC */
	uint64_t caslat                       : 3;  /**< CAS Latency Encoding which is loaded into each DDR
                                                         SDRAM device (MRS[6:4]) upon power-up (INIT_START=1).
                                                         (Represented in tCYC cycles == 1 dclks)
                                                            000 RESERVED
                                                            001 RESERVED
                                                            010 2.0 tCYC
                                                            011 3.0 tCYC
                                                            100 4.0 tCYC
                                                            101 5.0 tCYC
                                                            110 6.0 tCYC
                                                            111 RESERVED
                                                         eg). The parameters TSKW, SILO_HC, and SILO_QC can
                                                         account for 1/4 cycle granularity in board/etch delays. */
	uint64_t tmrd                         : 3;  /**< tMRD Cycles
                                                         (Represented in dclk tCYC)
                                                         For DDR2, its TYP 2*tCYC)
                                                             - 000: RESERVED
                                                             - 001: 1
                                                             - 010: 2
                                                             - 011: 3
                                                             - 100: 4
                                                             - 101-111: RESERVED */
	uint64_t trfc                         : 5;  /**< Indicates tRFC constraints.
                                                         Set TRFC (CSR field) = RNDUP[tRFC(ns)/4*tcyc(ns)],
                                                         where tRFC is from the DDR2 spec, and tcyc(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         For example, with 2Gb, DDR2-667 parts,
                                                         typ tRFC=195ns, so TRFC (CSR field) = 0x11.
                                                             TRFC (binary): Corresponding tRFC Cycles
                                                             ----------------------------------------
                                                             - 00000-00001: RESERVED
                                                             - 00010: 0-8
                                                             - 00011: 9-12
                                                             - 00100: 13-16
                                                             - ...
                                                             - 11110: 117-120
                                                             - 11111: 121-124 */
	uint64_t trp                          : 4;  /**< tRP Cycles = RNDUP[tRP(ns)/tcyc(ns)]
                                                         (Represented in tCYC cycles == 1dclk)
                                                         TYP=15ns (66MHz=1,167MHz=3,400MHz=6 for TYP)
                                                             - 0000: RESERVED
                                                             - 0001: 1
                                                             - ...
                                                             - 1001: 9
                                                             - 1010-1111: RESERVED
                                                         When using parts with 8 banks (LMC_DDR2_CTL->BANK8
                                                         is 1), load tRP cycles + 1 into this register. */
	uint64_t twtr                         : 4;  /**< tWTR Cycles = RNDUP[tWTR(ns)/tcyc(ns)]
                                                         Last Wr Data to Rd Command time.
                                                         (Represented in tCYC cycles == 1dclks)
                                                         TYP=15ns (66MHz=1,167MHz=3,400MHz=6, for TYP)
                                                             - 0000: RESERVED
                                                             - 0001: 1
                                                             - ...
                                                             - 0111: 7
                                                             - 1000-1111: RESERVED */
	uint64_t trcd                         : 4;  /**< tRCD Cycles = RNDUP[tRCD(ns)/tcyc(ns)]
                                                         (Represented in tCYC cycles == 1dclk)
                                                         TYP=15ns (66MHz=1,167MHz=3,400MHz=6 for TYP)
                                                             - 0000: RESERVED
                                                             - 0001: 2 (2 is the smallest value allowed)
                                                             - 0002: 2
                                                             - ...
                                                             - 1001: 9
                                                             - 1010-1111: RESERVED
                                                         In 2T mode, make this register TRCD-1, not going
                                                         below 2. */
	uint64_t tras                         : 5;  /**< tRAS Cycles = RNDUP[tRAS(ns)/tcyc(ns)]
                                                         (Represented in tCYC cycles == 1 dclk)
                                                             - 00000-0001: RESERVED
                                                             - 00010: 2
                                                             - ...
                                                             - 11111: 31 */
#else
	uint64_t tras                         : 5;
	uint64_t trcd                         : 4;
	uint64_t twtr                         : 4;
	uint64_t trp                          : 4;
	uint64_t trfc                         : 5;
	uint64_t tmrd                         : 3;
	uint64_t caslat                       : 3;
	uint64_t trrd                         : 3;
	uint64_t comp_bypass                  : 1;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_mem_cfg1_s           cn30xx;
	struct cvmx_lmcx_mem_cfg1_s           cn31xx;
	struct cvmx_lmcx_mem_cfg1_cn38xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_31_63               : 33;
	uint64_t trrd                         : 3;  /**< tRRD cycles: ACT-ACT timing parameter for different
                                                         banks. (Represented in tCYC cycles == 1dclks)
                                                         TYP=15ns (66MHz=1,167MHz=3,200MHz=3)
                                                         For DDR2, TYP=7.5ns
                                                            - 000: RESERVED
                                                            - 001: 1 tCYC
                                                            - 010: 2 tCYC
                                                            - 011: 3 tCYC
                                                            - 100: 4 tCYC
                                                            - 101: 5 tCYC
                                                            - 110-111: RESERVED */
	uint64_t caslat                       : 3;  /**< CAS Latency Encoding which is loaded into each DDR
                                                         SDRAM device (MRS[6:4]) upon power-up (INIT_START=1).
                                                         (Represented in tCYC cycles == 1 dclks)
                                                            000 RESERVED
                                                            001 RESERVED
                                                            010 2.0 tCYC
                                                            011 3.0 tCYC
                                                            100 4.0 tCYC
                                                            101 5.0 tCYC
                                                            110 6.0 tCYC (DDR2)
                                                                2.5 tCYC (DDR1)
                                                            111 RESERVED
                                                         eg). The parameters TSKW, SILO_HC, and SILO_QC can
                                                         account for 1/4 cycle granularity in board/etch delays. */
	uint64_t tmrd                         : 3;  /**< tMRD Cycles
                                                         (Represented in dclk tCYC)
                                                         For DDR2, its TYP 2*tCYC)
                                                             - 000: RESERVED
                                                             - 001: 1
                                                             - 010: 2
                                                             - 011: 3
                                                             - 100: 4
                                                             - 101-111: RESERVED */
	uint64_t trfc                         : 5;  /**< Indicates tRFC constraints.
                                                         Set TRFC (CSR field) = RNDUP[tRFC(ns)/4*tcyc(ns)],
                                                         where tRFC is from the DDR2 spec, and tcyc(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         For example, with 2Gb, DDR2-667 parts,
                                                         typ tRFC=195ns, so TRFC (CSR field) = 0x11.
                                                             TRFC (binary): Corresponding tRFC Cycles
                                                             ----------------------------------------
                                                             - 00000-00001: RESERVED
                                                             - 00010: 0-8
                                                             - 00011: 9-12
                                                             - 00100: 13-16
                                                             - ...
                                                             - 11110: 117-120
                                                             - 11111: 121-124 */
	uint64_t trp                          : 4;  /**< tRP Cycles = RNDUP[tRP(ns)/tcyc(ns)]
                                                         (Represented in tCYC cycles == 1dclk)
                                                         TYP=15ns (66MHz=1,167MHz=3,400MHz=6 for TYP)
                                                             - 0000: RESERVED
                                                             - 0001: 1
                                                             - ...
                                                             - 0111: 7
                                                             - 1000-1111: RESERVED
                                                         When using parts with 8 banks (LMC_DDR2_CTL->BANK8
                                                         is 1), load tRP cycles + 1 into this register. */
	uint64_t twtr                         : 4;  /**< tWTR Cycles = RNDUP[tWTR(ns)/tcyc(ns)]
                                                         Last Wr Data to Rd Command time.
                                                         (Represented in tCYC cycles == 1dclks)
                                                         TYP=15ns (66MHz=1,167MHz=3,400MHz=6, for TYP)
                                                             - 0000: RESERVED
                                                             - 0001: 1
                                                             - ...
                                                             - 0111: 7
                                                             - 1000-1111: RESERVED */
	uint64_t trcd                         : 4;  /**< tRCD Cycles = RNDUP[tRCD(ns)/tcyc(ns)]
                                                         (Represented in tCYC cycles == 1dclk)
                                                         TYP=15ns (66MHz=1,167MHz=3,400MHz=6 for TYP)
                                                             - 0000: RESERVED
                                                             - 0001: 2 (2 is the smallest value allowed)
                                                             - 0002: 2
                                                             - ...
                                                             - 0111: 7
                                                             - 1110-1111: RESERVED
                                                         In 2T mode, make this register TRCD-1, not going
                                                         below 2. */
	uint64_t tras                         : 5;  /**< tRAS Cycles = RNDUP[tRAS(ns)/tcyc(ns)]
                                                         (Represented in tCYC cycles == 1 dclk)
                                                         For DDR-I mode:
                                                         TYP=45ns (66MHz=3,167MHz=8,400MHz=18
                                                             - 00000-0001: RESERVED
                                                             - 00010: 2
                                                             - ...
                                                             - 10100: 20
                                                             - 10101-11111: RESERVED */
#else
	uint64_t tras                         : 5;
	uint64_t trcd                         : 4;
	uint64_t twtr                         : 4;
	uint64_t trp                          : 4;
	uint64_t trfc                         : 5;
	uint64_t tmrd                         : 3;
	uint64_t caslat                       : 3;
	uint64_t trrd                         : 3;
	uint64_t reserved_31_63               : 33;
#endif
	} cn38xx;
	struct cvmx_lmcx_mem_cfg1_cn38xx      cn38xxp2;
	struct cvmx_lmcx_mem_cfg1_s           cn50xx;
	struct cvmx_lmcx_mem_cfg1_cn38xx      cn52xx;
	struct cvmx_lmcx_mem_cfg1_cn38xx      cn52xxp1;
	struct cvmx_lmcx_mem_cfg1_cn38xx      cn56xx;
	struct cvmx_lmcx_mem_cfg1_cn38xx      cn56xxp1;
	struct cvmx_lmcx_mem_cfg1_cn38xx      cn58xx;
	struct cvmx_lmcx_mem_cfg1_cn38xx      cn58xxp1;
};
typedef union cvmx_lmcx_mem_cfg1 cvmx_lmcx_mem_cfg1_t;

/**
 * cvmx_lmc#_modereg_params0
 *
 * These parameters are written into the DDR3 MR0, MR1, MR2 and MR3 registers.
 *
 */
union cvmx_lmcx_modereg_params0 {
	uint64_t u64;
	struct cvmx_lmcx_modereg_params0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_25_63               : 39;
	uint64_t ppd                          : 1;  /**< DLL Control for precharge powerdown
                                                         0 = Slow exit (DLL off)
                                                         1 = Fast exit (DLL on)
                                                         LMC writes this value to MR0[PPD] in the selected DDR3 parts
                                                         during power-up/init and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK].
                                                         This value must equal the MR0[PPD] value in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t wrp                          : 3;  /**< Write recovery for auto precharge
                                                         Should be programmed to be equal to or greater than
                                                         RNDUP[tWR(ns)/tCYC(ns)]
                                                         000 = 5
                                                         001 = 5
                                                         010 = 6
                                                         011 = 7
                                                         100 = 8
                                                         101 = 10
                                                         110 = 12
                                                         111 = 14
                                                         LMC writes this value to MR0[WR] in the selected DDR3 parts
                                                         during power-up/init and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK].
                                                         This value must equal the MR0[WR] value in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t dllr                         : 1;  /**< DLL Reset
                                                         LMC writes this value to MR0[DLL] in the selected DDR3 parts
                                                         during power-up/init and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK].
                                                         The MR0[DLL] value must be 0 in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t tm                           : 1;  /**< Test Mode
                                                         LMC writes this value to MR0[TM] in the selected DDR3 parts
                                                         during power-up/init and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK].
                                                         The MR0[TM] value must be 0 in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t rbt                          : 1;  /**< Read Burst Type
                                                         1 = interleaved (fixed)
                                                         LMC writes this value to MR0[RBT] in the selected DDR3 parts
                                                         during power-up/init and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK].
                                                         The MR0[RBT] value must be 1 in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t cl                           : 4;  /**< CAS Latency
                                                         0010 = 5
                                                         0100 = 6
                                                         0110 = 7
                                                         1000 = 8
                                                         1010 = 9
                                                         1100 = 10
                                                         1110 = 11
                                                         0001 = 12
                                                         0011 = 13
                                                         0101 = 14
                                                         0111 = 15
                                                         1001 = 16
                                                         0000, 1011, 1101, 1111 = Reserved
                                                         LMC writes this value to MR0[CAS Latency / CL] in the selected DDR3 parts
                                                         during power-up/init and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK].
                                                         This value must equal the MR0[CAS Latency / CL] value in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t bl                           : 2;  /**< Burst Length
                                                         0 = 8 (fixed)
                                                         LMC writes this value to MR0[BL] in the selected DDR3 parts
                                                         during power-up/init and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK].
                                                         The MR0[BL] value must be 0 in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t qoff                         : 1;  /**< Qoff Enable
                                                         0 = enable
                                                         1 = disable
                                                         LMC writes this value to MR1[Qoff] in the DDR3 parts in the selected ranks
                                                         during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK,INIT_STATUS] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT].
                                                         The MR1[Qoff] value must be 0 in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t tdqs                         : 1;  /**< TDQS Enable
                                                         0 = disable
                                                         LMC writes this value to MR1[TDQS] in the DDR3 parts in the selected ranks
                                                         during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK,INIT_STATUS] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t wlev                         : 1;  /**< Write Leveling Enable
                                                         0 = disable
                                                         LMC writes MR1[Level]=0 in the DDR3 parts in the selected ranks
                                                         during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         (Write-leveling can only be initiated via the
                                                         write-leveling instruction sequence.)
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK,INIT_STATUS] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t al                           : 2;  /**< Additive Latency
                                                         00 = 0
                                                         01 = CL-1
                                                         10 = CL-2
                                                         11 = Reserved
                                                         LMC writes this value to MR1[AL] in the selected DDR3 parts
                                                         during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT].
                                                         This value must equal the MR1[AL] value in all the DDR3
                                                         parts attached to all ranks during normal operation.
                                                         See also LMC*_CONTROL[POCAS]. */
	uint64_t dll                          : 1;  /**< DLL Enable
                                                         0 = enable
                                                         1 = disable.
                                                         LMC writes this value to MR1[DLL] in the selected DDR3 parts
                                                         during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT].
                                                         This value must equal the MR1[DLL] value in all the DDR3
                                                         parts attached to all ranks during normal operation.
                                                         In dll-off mode, CL/CWL must be programmed
                                                         equal to 6/6, respectively, as per the DDR3 specifications. */
	uint64_t mpr                          : 1;  /**< MPR
                                                         LMC writes this value to MR3[MPR] in the selected DDR3 parts
                                                         during power-up/init, read-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh exit instruction sequences.
                                                         (LMC also writes MR3[MPR]=1 at the beginning of the
                                                         read-leveling instruction sequence. Read-leveling should only be initiated via the
                                                         read-leveling instruction sequence.)
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK].
                                                         The MR3[MPR] value must be 0 in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t mprloc                       : 2;  /**< MPR Location
                                                         LMC writes this value to MR3[MPRLoc] in the selected DDR3 parts
                                                         during power-up/init, read-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh exit instruction sequences.
                                                         (LMC also writes MR3[MPRLoc]=0 at the beginning of the
                                                         read-leveling instruction sequence.)
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK].
                                                         The MR3[MPRLoc] value must be 0 in all the DDR3
                                                         parts attached to all ranks during normal operation. */
	uint64_t cwl                          : 3;  /**< CAS Write Latency
                                                         - 000: 5
                                                         - 001: 6
                                                         - 010: 7
                                                         - 011: 8
                                                         - 100: 9
                                                         - 101: 10
                                                         - 110: 11
                                                         - 111: 12
                                                         LMC writes this value to MR2[CWL] in the selected DDR3 parts
                                                         during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT].
                                                         This value must equal the MR2[CWL] value in all the DDR3
                                                         parts attached to all ranks during normal operation. */
#else
	uint64_t cwl                          : 3;
	uint64_t mprloc                       : 2;
	uint64_t mpr                          : 1;
	uint64_t dll                          : 1;
	uint64_t al                           : 2;
	uint64_t wlev                         : 1;
	uint64_t tdqs                         : 1;
	uint64_t qoff                         : 1;
	uint64_t bl                           : 2;
	uint64_t cl                           : 4;
	uint64_t rbt                          : 1;
	uint64_t tm                           : 1;
	uint64_t dllr                         : 1;
	uint64_t wrp                          : 3;
	uint64_t ppd                          : 1;
	uint64_t reserved_25_63               : 39;
#endif
	} s;
	struct cvmx_lmcx_modereg_params0_s    cn61xx;
	struct cvmx_lmcx_modereg_params0_s    cn63xx;
	struct cvmx_lmcx_modereg_params0_s    cn63xxp1;
	struct cvmx_lmcx_modereg_params0_s    cn66xx;
	struct cvmx_lmcx_modereg_params0_s    cn68xx;
	struct cvmx_lmcx_modereg_params0_s    cn68xxp1;
	struct cvmx_lmcx_modereg_params0_s    cn70xx;
	struct cvmx_lmcx_modereg_params0_s    cn78xx;
	struct cvmx_lmcx_modereg_params0_s    cnf71xx;
};
typedef union cvmx_lmcx_modereg_params0 cvmx_lmcx_modereg_params0_t;

/**
 * cvmx_lmc#_modereg_params1
 *
 * These parameters are written into the DDR3 MR0, MR1, MR2 and MR3 registers.
 *
 */
union cvmx_lmcx_modereg_params1 {
	uint64_t u64;
	struct cvmx_lmcx_modereg_params1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_48_63               : 16;
	uint64_t rtt_nom_11                   : 3;  /**< RTT_NOM Rank 3
                                                         LMC writes this value to MR1[Rtt_Nom] in the rank 3 (i.e. DIMM1_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT].
                                                         Per JEDEC DDR3 specifications, if RTT_Nom is used during writes,
                                                         only values MR1[Rtt_Nom] = 1 (RQZ/4), 2 (RQZ/2), or 3 (RQZ/6) are allowed.
                                                         Otherwise, values MR1[Rtt_Nom] = 4 (RQZ/12) and 5 (RQZ/8) are also allowed. */
	uint64_t dic_11                       : 2;  /**< Output Driver Impedance Control Rank 3
                                                         LMC writes this value to MR1[D.I.C.] in the rank 3 (i.e. DIMM1_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t rtt_wr_11                    : 2;  /**< RTT_WR Rank 3
                                                         LMC writes this value to MR2[Rtt_WR] in the rank 3 (i.e. DIMM1_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t srt_11                       : 1;  /**< Self-refresh temperature range Rank 3
                                                         LMC writes this value to MR2[SRT] in the rank 3 (i.e. DIMM1_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t asr_11                       : 1;  /**< Auto self-refresh Rank 3
                                                         LMC writes this value to MR2[ASR] in the rank 3 (i.e. DIMM1_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t pasr_11                      : 3;  /**< Partial array self-refresh Rank 3
                                                         LMC writes this value to MR2[PASR] in the rank 3 (i.e. DIMM1_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t rtt_nom_10                   : 3;  /**< RTT_NOM Rank 2
                                                         LMC writes this value to MR1[Rtt_Nom] in the rank 2 (i.e. DIMM1_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT].
                                                         Per JEDEC DDR3 specifications, if RTT_Nom is used during writes,
                                                         only values MR1[Rtt_Nom] = 1 (RQZ/4), 2 (RQZ/2), or 3 (RQZ/6) are allowed.
                                                         Otherwise, values MR1[Rtt_Nom] = 4 (RQZ/12) and 5 (RQZ/8) are also allowed. */
	uint64_t dic_10                       : 2;  /**< Output Driver Impedance Control Rank 2
                                                         LMC writes this value to MR1[D.I.C.] in the rank 2 (i.e. DIMM1_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t rtt_wr_10                    : 2;  /**< RTT_WR Rank 2
                                                         LMC writes this value to MR2[Rtt_WR] in the rank 2 (i.e. DIMM1_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t srt_10                       : 1;  /**< Self-refresh temperature range Rank 2
                                                         LMC writes this value to MR2[SRT] in the rank 2 (i.e. DIMM1_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t asr_10                       : 1;  /**< Auto self-refresh Rank 2
                                                         LMC writes this value to MR2[ASR] in the rank 2 (i.e. DIMM1_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t pasr_10                      : 3;  /**< Partial array self-refresh Rank 2
                                                         LMC writes this value to MR2[PASR] in the rank 2 (i.e. DIMM1_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t rtt_nom_01                   : 3;  /**< RTT_NOM Rank 1
                                                         LMC writes this value to MR1[Rtt_Nom] in the rank 1 (i.e. DIMM0_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT].
                                                         Per JEDEC DDR3 specifications, if RTT_Nom is used during writes,
                                                         only values MR1[Rtt_Nom] = 1 (RQZ/4), 2 (RQZ/2), or 3 (RQZ/6) are allowed.
                                                         Otherwise, values MR1[Rtt_Nom] = 4 (RQZ/12) and 5 (RQZ/8) are also allowed. */
	uint64_t dic_01                       : 2;  /**< Output Driver Impedance Control Rank 1
                                                         LMC writes this value to MR1[D.I.C.] in the rank 1 (i.e. DIMM0_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t rtt_wr_01                    : 2;  /**< RTT_WR Rank 1
                                                         LMC writes this value to MR2[Rtt_WR] in the rank 1 (i.e. DIMM0_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t srt_01                       : 1;  /**< Self-refresh temperature range Rank 1
                                                         LMC writes this value to MR2[SRT] in the rank 1 (i.e. DIMM0_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t asr_01                       : 1;  /**< Auto self-refresh Rank 1
                                                         LMC writes this value to MR2[ASR] in the rank 1 (i.e. DIMM0_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t pasr_01                      : 3;  /**< Partial array self-refresh Rank 1
                                                         LMC writes this value to MR2[PASR] in the rank 1 (i.e. DIMM0_CS1) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t rtt_nom_00                   : 3;  /**< RTT_NOM Rank 0
                                                         LMC writes this value to MR1[Rtt_Nom] in the rank 0 (i.e. DIMM0_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT].
                                                         Per JEDEC DDR3 specifications, if RTT_Nom is used during writes,
                                                         only values MR1[Rtt_Nom] = 1 (RQZ/4), 2 (RQZ/2), or 3 (RQZ/6) are allowed.
                                                         Otherwise, values MR1[Rtt_Nom] = 4 (RQZ/12) and 5 (RQZ/8) are also allowed. */
	uint64_t dic_00                       : 2;  /**< Output Driver Impedance Control Rank 0
                                                         LMC writes this value to MR1[D.I.C.] in the rank 0 (i.e. DIMM0_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t rtt_wr_00                    : 2;  /**< RTT_WR Rank 0
                                                         LMC writes this value to MR2[Rtt_WR] in the rank 0 (i.e. DIMM0_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t srt_00                       : 1;  /**< Self-refresh temperature range Rank 0
                                                         LMC writes this value to MR2[SRT] in the rank 0 (i.e. DIMM0_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t asr_00                       : 1;  /**< Auto self-refresh Rank 0
                                                         LMC writes this value to MR2[ASR] in the rank 0 (i.e. DIMM0_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
	uint64_t pasr_00                      : 3;  /**< Partial array self-refresh Rank 0
                                                         LMC writes this value to MR2[PASR] in the rank 0 (i.e. DIMM0_CS0) DDR3 parts
                                                         when selected during power-up/init, write-leveling, and, if LMC*_CONFIG[SREF_WITH_DLL] is set,
                                                         self-refresh entry and exit instruction sequences.
                                                         See LMC*_CONFIG[SEQUENCE,INIT_START,RANKMASK] and
                                                         LMC*_RESET_CTL[DDR3PWARM,DDR3PSOFT]. */
#else
	uint64_t pasr_00                      : 3;
	uint64_t asr_00                       : 1;
	uint64_t srt_00                       : 1;
	uint64_t rtt_wr_00                    : 2;
	uint64_t dic_00                       : 2;
	uint64_t rtt_nom_00                   : 3;
	uint64_t pasr_01                      : 3;
	uint64_t asr_01                       : 1;
	uint64_t srt_01                       : 1;
	uint64_t rtt_wr_01                    : 2;
	uint64_t dic_01                       : 2;
	uint64_t rtt_nom_01                   : 3;
	uint64_t pasr_10                      : 3;
	uint64_t asr_10                       : 1;
	uint64_t srt_10                       : 1;
	uint64_t rtt_wr_10                    : 2;
	uint64_t dic_10                       : 2;
	uint64_t rtt_nom_10                   : 3;
	uint64_t pasr_11                      : 3;
	uint64_t asr_11                       : 1;
	uint64_t srt_11                       : 1;
	uint64_t rtt_wr_11                    : 2;
	uint64_t dic_11                       : 2;
	uint64_t rtt_nom_11                   : 3;
	uint64_t reserved_48_63               : 16;
#endif
	} s;
	struct cvmx_lmcx_modereg_params1_s    cn61xx;
	struct cvmx_lmcx_modereg_params1_s    cn63xx;
	struct cvmx_lmcx_modereg_params1_s    cn63xxp1;
	struct cvmx_lmcx_modereg_params1_s    cn66xx;
	struct cvmx_lmcx_modereg_params1_s    cn68xx;
	struct cvmx_lmcx_modereg_params1_s    cn68xxp1;
	struct cvmx_lmcx_modereg_params1_s    cn70xx;
	struct cvmx_lmcx_modereg_params1_s    cn78xx;
	struct cvmx_lmcx_modereg_params1_s    cnf71xx;
};
typedef union cvmx_lmcx_modereg_params1 cvmx_lmcx_modereg_params1_t;

/**
 * cvmx_lmc#_modereg_params2
 *
 * These parameters are written into the DDR4 mode registers.
 *
 */
union cvmx_lmcx_modereg_params2 {
	uint64_t u64;
	struct cvmx_lmcx_modereg_params2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_40_63               : 24;
	uint64_t vref_range_11                : 1;  /**< VREF range for rank 3. */
	uint64_t vref_value_11                : 6;  /**< VREF value for rank 3. */
	uint64_t rtt_park_11                  : 3;  /**< RTT park value for rank 3. */
	uint64_t vref_range_10                : 1;  /**< VREF range for rank 2. */
	uint64_t vref_value_10                : 6;  /**< VREF value for rank 2. */
	uint64_t rtt_park_10                  : 3;  /**< RTT park value for rank 2. */
	uint64_t vref_range_01                : 1;  /**< VREF range for rank 1. */
	uint64_t vref_value_01                : 6;  /**< VREF value for rank 1. */
	uint64_t rtt_park_01                  : 3;  /**< RTT park value for rank 1. */
	uint64_t vref_range_00                : 1;  /**< VREF range for rank 0. */
	uint64_t vref_value_00                : 6;  /**< VREF value for rank 0. */
	uint64_t rtt_park_00                  : 3;  /**< RTT park value for rank 0. */
#else
	uint64_t rtt_park_00                  : 3;
	uint64_t vref_value_00                : 6;
	uint64_t vref_range_00                : 1;
	uint64_t rtt_park_01                  : 3;
	uint64_t vref_value_01                : 6;
	uint64_t vref_range_01                : 1;
	uint64_t rtt_park_10                  : 3;
	uint64_t vref_value_10                : 6;
	uint64_t vref_range_10                : 1;
	uint64_t rtt_park_11                  : 3;
	uint64_t vref_value_11                : 6;
	uint64_t vref_range_11                : 1;
	uint64_t reserved_40_63               : 24;
#endif
	} s;
	struct cvmx_lmcx_modereg_params2_s    cn70xx;
	struct cvmx_lmcx_modereg_params2_s    cn78xx;
};
typedef union cvmx_lmcx_modereg_params2 cvmx_lmcx_modereg_params2_t;

/**
 * cvmx_lmc#_modereg_params3
 *
 * These parameters are written into the DDR4 mode registers.
 *
 */
union cvmx_lmcx_modereg_params3 {
	uint64_t u64;
	struct cvmx_lmcx_modereg_params3_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_33_63               : 31;
	uint64_t mpr_fmt                      : 2;  /**< MPR format. */
	uint64_t wr_cmd_lat                   : 2;  /**< Write command latency when CRC and DM are both enabled. */
	uint64_t fgrm                         : 3;  /**< Fine granularity refresh mode. */
	uint64_t temp_sense                   : 1;  /**< Temperature sensor readout enable. */
	uint64_t pda                          : 1;  /**< Per DRAM addressability. */
	uint64_t gd                           : 1;  /**< Gear-down mode. */
	uint64_t crc                          : 1;  /**< CRC mode. */
	uint64_t lpasr                        : 2;  /**< LP auto self refresh. */
	uint64_t tccd_l                       : 3;  /**< TCCD_L timing parameter:
                                                         0x0 = 4. 0x3 = 7.
                                                         0x1 = 5. 0x4 = 8.
                                                         0x2 = 6. 0x5-0x7 = reserved. */
	uint64_t rd_dbi                       : 1;  /**< Read DBI. */
	uint64_t wr_dbi                       : 1;  /**< Write DBI. */
	uint64_t dm                           : 1;  /**< Data mask enable. */
	uint64_t ca_par_pers                  : 1;  /**< Command/address persistent parity error mode. */
	uint64_t odt_pd                       : 1;  /**< ODT in PD mode. */
	uint64_t par_lat_mode                 : 3;  /**< Parity latency mode. */
	uint64_t wr_preamble                  : 1;  /**< Write preamble, 0 = one nCK, 1 = two nCK. */
	uint64_t rd_preamble                  : 1;  /**< Write preamble, 0 = one nCK, 1 = two nCK. */
	uint64_t sre_abort                    : 1;  /**< Self refresh abort. */
	uint64_t cal                          : 3;  /**< CS-to-CMD/ADDR latency mode (cycles). */
	uint64_t vref_mon                     : 1;  /**< Internal VREF monitor: 0 = disable, 1 = enable. */
	uint64_t tc_ref                       : 1;  /**< Temperature controlled refresh range: 0 = normal, 1 = extended. */
	uint64_t max_pd                       : 1;  /**< Maximum power-down mode: 0 = disable, 1 = enable. */
#else
	uint64_t max_pd                       : 1;
	uint64_t tc_ref                       : 1;
	uint64_t vref_mon                     : 1;
	uint64_t cal                          : 3;
	uint64_t sre_abort                    : 1;
	uint64_t rd_preamble                  : 1;
	uint64_t wr_preamble                  : 1;
	uint64_t par_lat_mode                 : 3;
	uint64_t odt_pd                       : 1;
	uint64_t ca_par_pers                  : 1;
	uint64_t dm                           : 1;
	uint64_t wr_dbi                       : 1;
	uint64_t rd_dbi                       : 1;
	uint64_t tccd_l                       : 3;
	uint64_t lpasr                        : 2;
	uint64_t crc                          : 1;
	uint64_t gd                           : 1;
	uint64_t pda                          : 1;
	uint64_t temp_sense                   : 1;
	uint64_t fgrm                         : 3;
	uint64_t wr_cmd_lat                   : 2;
	uint64_t mpr_fmt                      : 2;
	uint64_t reserved_33_63               : 31;
#endif
	} s;
	struct cvmx_lmcx_modereg_params3_s    cn70xx;
	struct cvmx_lmcx_modereg_params3_s    cn78xx;
};
typedef union cvmx_lmcx_modereg_params3 cvmx_lmcx_modereg_params3_t;

/**
 * cvmx_lmc#_mpr_data0
 *
 * This register provides bits <63:0> of MPR data register.
 *
 */
union cvmx_lmcx_mpr_data0 {
	uint64_t u64;
	struct cvmx_lmcx_mpr_data0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t mpr_data                     : 64; /**< MPR data bits<63:0>. Bits<7:0> represent the MPR data for the lowest-order *4 device (*4
                                                         device 0); bits<15:8> represent *4 device 1; ..., bits<63:56> are for *4 device 7. */
#else
	uint64_t mpr_data                     : 64;
#endif
	} s;
	struct cvmx_lmcx_mpr_data0_s          cn70xx;
	struct cvmx_lmcx_mpr_data0_s          cn78xx;
};
typedef union cvmx_lmcx_mpr_data0 cvmx_lmcx_mpr_data0_t;

/**
 * cvmx_lmc#_mpr_data1
 *
 * This register provides bits <127:64> of MPR data register.
 *
 */
union cvmx_lmcx_mpr_data1 {
	uint64_t u64;
	struct cvmx_lmcx_mpr_data1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t mpr_data                     : 64; /**< MPR data bits<127:64>. Bits<7:0> represent the MPR data for *4 device 8; bits<15:8>
                                                         represent *4 device 9; ...; bits<63:56> are for *4 device 15. */
#else
	uint64_t mpr_data                     : 64;
#endif
	} s;
	struct cvmx_lmcx_mpr_data1_s          cn70xx;
	struct cvmx_lmcx_mpr_data1_s          cn78xx;
};
typedef union cvmx_lmcx_mpr_data1 cvmx_lmcx_mpr_data1_t;

/**
 * cvmx_lmc#_mpr_data2
 *
 * This register provides bits <143:128> of MPR data register.
 *
 */
union cvmx_lmcx_mpr_data2 {
	uint64_t u64;
	struct cvmx_lmcx_mpr_data2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_16_63               : 48;
	uint64_t mpr_data                     : 16; /**< MPR data bits<143:128>. Bits<7:0> represent the MPR data for *4 device 16; bits<15:8>
                                                         represent *4 device 17. */
#else
	uint64_t mpr_data                     : 16;
	uint64_t reserved_16_63               : 48;
#endif
	} s;
	struct cvmx_lmcx_mpr_data2_s          cn70xx;
	struct cvmx_lmcx_mpr_data2_s          cn78xx;
};
typedef union cvmx_lmcx_mpr_data2 cvmx_lmcx_mpr_data2_t;

/**
 * cvmx_lmc#_mr_mpr_ctl
 *
 * This register sets timing parameters for DDR4.
 *
 */
union cvmx_lmcx_mr_mpr_ctl {
	uint64_t u64;
	struct cvmx_lmcx_mr_mpr_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_57_63               : 7;
	uint64_t mr_wr_bg1                    : 1;  /**< BG1 part of address select for MRS in DDR4 mode. */
	uint64_t reserved_53_55               : 3;
	uint64_t mr_wr_use_default_value      : 1;  /**< When set, write the value to the MR that is computed from the value set in various CSR
                                                         fields that would be used during initialization, rather that using the value in the
                                                         LMC(0..3)_MR_MPR_CTL[MR_WR_ADDR] CSR field.  Useful to re-write the same value or
                                                         to change single bits without having to compute a whole new value for the MR. */
	uint64_t mpr_whole_byte_enable        : 1;  /**< Reserved. INTERNAL: Select a whole byte of DRAM data to read when whole-byte mode enabled. */
	uint64_t mpr_byte_select              : 4;  /**< Reserved. INTERNAL: Select a whole byte of DRAM data to read when whole-byte mode enabled. */
	uint64_t mpr_bit_select               : 2;  /**< Select which of four bits to read for each nibble of DRAM data. Typically all four bits
                                                         from a *4 device, or all eight bits from a *8 device, or all 16 bits from a *16 device
                                                         carry the same data, but this field allows selection of which device bit will be used to
                                                         read the MPR data. */
	uint64_t mpr_wr                       : 1;  /**< MPR sequence will perform a write operation when set. */
	uint64_t mpr_loc                      : 2;  /**< MPR location select for MPR sequence. Only makes a difference for DDR4. */
	uint64_t mr_wr_pda_enable             : 1;  /**< PDA write enable. When set, MRW operations use PDA, enabled by MR_WR_PDA_MASK per device.
                                                         Only available for DDR4 devices. */
	uint64_t mr_wr_pda_mask               : 18; /**< PDA mask. If MR_WR_PDA_ENABLE = 1 and there is a 1 in the bit for this mask value, then
                                                         the corresponding DRAM device is enabled for the PDA MR write operation.
                                                         Bit<23> corresponds to the lowest order, *4 device, and bit<40> corresponds to the highest
                                                         order *4 device, for a total of up to 18 devices. */
	uint64_t mr_wr_rank                   : 2;  /**< Selects the DRAM rank for either MRW or MPR sequences. */
	uint64_t mr_wr_sel                    : 3;  /**< Selects which MR to write with the MR write sequence.
                                                         Which pins to drive and how to drive them is automatically controlled through the DDR3/4
                                                         mode setting. Bits<19:18> are also used to select the MPR page for an MPR sequence.
                                                         A value of 0x7 selects an RCW write for both DDR4 and DDR3 MRW operations. */
	uint64_t mr_wr_addr                   : 18; /**< Sets a value for A<17:0> for MR write operations. Note that many of these bits must be 0
                                                         for various MRs. Bits<7:0> are also used for write data on an MPR sequence write
                                                         operation. */
#else
	uint64_t mr_wr_addr                   : 18;
	uint64_t mr_wr_sel                    : 3;
	uint64_t mr_wr_rank                   : 2;
	uint64_t mr_wr_pda_mask               : 18;
	uint64_t mr_wr_pda_enable             : 1;
	uint64_t mpr_loc                      : 2;
	uint64_t mpr_wr                       : 1;
	uint64_t mpr_bit_select               : 2;
	uint64_t mpr_byte_select              : 4;
	uint64_t mpr_whole_byte_enable        : 1;
	uint64_t mr_wr_use_default_value      : 1;
	uint64_t reserved_53_55               : 3;
	uint64_t mr_wr_bg1                    : 1;
	uint64_t reserved_57_63               : 7;
#endif
	} s;
	struct cvmx_lmcx_mr_mpr_ctl_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_52_63               : 12;
	uint64_t mpr_whole_byte_enable        : 1;  /**< Reserved. INTERNAL: Select a whole byte of DRAM data to read when whole-byte mode enabled. */
	uint64_t mpr_byte_select              : 4;  /**< Reserved. INTERNAL: Select a whole byte of DRAM data to read when whole-byte mode enabled. */
	uint64_t mpr_bit_select               : 2;  /**< Select which of four bits to read for each nibble of DRAM data. Typically all four bits
                                                         from a *4 device, or all eight bits from a *8 device, or all 16 bits from a *16 device
                                                         carry the same data, but this field allows selection of which device bit will be used to
                                                         read the MPR data. */
	uint64_t mpr_wr                       : 1;  /**< MPR sequence will perform a write operation when set. */
	uint64_t mpr_loc                      : 2;  /**< MPR location select for MPR sequence. Only makes a difference for DDR4. */
	uint64_t mr_wr_pda_enable             : 1;  /**< PDA write enable. When set, MRW operations use PDA, enabled by MR_WR_PDA_MASK per device.
                                                         Only available for DDR4 devices. */
	uint64_t mr_wr_pda_mask               : 18; /**< PDA mask. If MR_WR_PDA_ENABLE = 1 and there is a 1 in the bit for this mask value, then
                                                         the corresponding DRAM device is enabled for the PDA MR write operation.
                                                         Bit<23> corresponds to the lowest order, *4 device, and bit<40> corresponds to the highest
                                                         order *4 device, for a total of up to 18 devices. */
	uint64_t mr_wr_rank                   : 2;  /**< Selects the DRAM rank for either MRW or MPR sequences.  For CN70XX/CN71XX, this must be
                                                         set
                                                         to either 0 or 1. */
	uint64_t mr_wr_sel                    : 3;  /**< Selects which MR to write with the MR write sequence.
                                                         Which pins to drive and how to drive them is automatically controlled through the DDR3/4
                                                         mode setting. Bits<19:18> are also used to select the MPR page for an MPR sequence.
                                                         A value of 0x7 selects an RCW write for both DDR4 and DDR3 MRW operations. */
	uint64_t mr_wr_addr                   : 18; /**< Sets a value for A<17:0> for MR write operations. Note that many of these bits must be 0
                                                         for various MRs. Bits<7:0> are also used for write data on an MPR sequence write
                                                         operation. */
#else
	uint64_t mr_wr_addr                   : 18;
	uint64_t mr_wr_sel                    : 3;
	uint64_t mr_wr_rank                   : 2;
	uint64_t mr_wr_pda_mask               : 18;
	uint64_t mr_wr_pda_enable             : 1;
	uint64_t mpr_loc                      : 2;
	uint64_t mpr_wr                       : 1;
	uint64_t mpr_bit_select               : 2;
	uint64_t mpr_byte_select              : 4;
	uint64_t mpr_whole_byte_enable        : 1;
	uint64_t reserved_52_63               : 12;
#endif
	} cn70xx;
	struct cvmx_lmcx_mr_mpr_ctl_s         cn78xx;
};
typedef union cvmx_lmcx_mr_mpr_ctl cvmx_lmcx_mr_mpr_ctl_t;

/**
 * cvmx_lmc#_nxm
 *
 * Following is the decoding for mem_msb/rank:
 *
 */
union cvmx_lmcx_nxm {
	uint64_t u64;
	struct cvmx_lmcx_nxm_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_40_63               : 24;
	uint64_t mem_msb_d3_r1                : 4;  /**< Max Row MSB for DIMM3, RANK1/DIMM3 in Single Ranked
                                                         *UNUSED IN 6xxx* */
	uint64_t mem_msb_d3_r0                : 4;  /**< Max Row MSB for DIMM3, RANK0
                                                         *UNUSED IN 6xxx* */
	uint64_t mem_msb_d2_r1                : 4;  /**< Max Row MSB for DIMM2, RANK1/DIMM2 in Single Ranked
                                                         *UNUSED IN 6xxx* */
	uint64_t mem_msb_d2_r0                : 4;  /**< Max Row MSB for DIMM2, RANK0
                                                         *UNUSED IN 6xxx* */
	uint64_t mem_msb_d1_r1                : 4;  /**< Max Row MSB for DIMM1, RANK1/DIMM1 in Single Ranked */
	uint64_t mem_msb_d1_r0                : 4;  /**< Max Row MSB for DIMM1, RANK0 */
	uint64_t mem_msb_d0_r1                : 4;  /**< Max Row MSB for DIMM0, RANK1/DIMM0 in Single Ranked */
	uint64_t mem_msb_d0_r0                : 4;  /**< Max Row MSB for DIMM0, RANK0 */
	uint64_t cs_mask                      : 8;  /**< Chip select mask.
                                                         CS_MASK[3:0] corresponds to the 4 chip selects for a memory
                                                         configuration.  If the memory configuration does not populate
                                                         a rank of memory for a chip select, the corresponding bit in
                                                         the CS_MASK field must be set, and for 6xxx devices bits
                                                         CS_MASK[7:4] must always all be set.  LMC will alias a NXM
                                                         read reference to use the lowest, legal chip select and
                                                         return 0s for data.  LMC normally discards NXM writes, but
                                                         will also alias them when LMC*_CONTROL[NXM_WRITE_EN]=1. */
#else
	uint64_t cs_mask                      : 8;
	uint64_t mem_msb_d0_r0                : 4;
	uint64_t mem_msb_d0_r1                : 4;
	uint64_t mem_msb_d1_r0                : 4;
	uint64_t mem_msb_d1_r1                : 4;
	uint64_t mem_msb_d2_r0                : 4;
	uint64_t mem_msb_d2_r1                : 4;
	uint64_t mem_msb_d3_r0                : 4;
	uint64_t mem_msb_d3_r1                : 4;
	uint64_t reserved_40_63               : 24;
#endif
	} s;
	struct cvmx_lmcx_nxm_cn52xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_8_63                : 56;
	uint64_t cs_mask                      : 8;  /**< Chip select mask.
                                                         This mask corresponds to the 8 chip selects for a memory
                                                         configuration.  If LMC_MEM_CFG0[BUNK_ENA]==0 then this
                                                         mask must be set in pairs because each reference address
                                                         will assert a pair of chip selects.  If the chip
                                                         select(s) have a corresponding CS_MASK bit set, then the
                                                         reference is to non-existent memory.  LMC will alias the
                                                         reference to use the lowest, legal chip select(s) in
                                                         that case. */
#else
	uint64_t cs_mask                      : 8;
	uint64_t reserved_8_63                : 56;
#endif
	} cn52xx;
	struct cvmx_lmcx_nxm_cn52xx           cn56xx;
	struct cvmx_lmcx_nxm_cn52xx           cn58xx;
	struct cvmx_lmcx_nxm_s                cn61xx;
	struct cvmx_lmcx_nxm_s                cn63xx;
	struct cvmx_lmcx_nxm_s                cn63xxp1;
	struct cvmx_lmcx_nxm_s                cn66xx;
	struct cvmx_lmcx_nxm_s                cn68xx;
	struct cvmx_lmcx_nxm_s                cn68xxp1;
	struct cvmx_lmcx_nxm_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_24_63               : 40;
	uint64_t mem_msb_d1_r1                : 4;  /**< Reserved.  INTERNAL: Max row MSB for DIMM1, RANK1/DIMM1 in single ranked. */
	uint64_t mem_msb_d1_r0                : 4;  /**< Reserved.  INTERNAL: Max row MSB for DIMM1, RANK0. */
	uint64_t mem_msb_d0_r1                : 4;  /**< Max row MSB for DIMM0, RANK1/DIMM0 in single ranked. */
	uint64_t mem_msb_d0_r0                : 4;  /**< Max row MSB for DIMM0, RANK0. */
	uint64_t reserved_4_7                 : 4;
	uint64_t cs_mask                      : 4;  /**< Chip select mask. This mask corresponds to the four chip selects for a memory
                                                         configuration. If LMC(0..0)_CONFIG[RANK_ENA]=0 then this mask must be set in pairs because
                                                         each reference address will assert a pair of chip selects. If the chip select(s) have a
                                                         corresponding CS_MASK bit set, then the reference is to nonexistent memory (NXM). LMC will
                                                         alias a NXM read reference to use the lowest, legal chip select(s) and return zeros. LMC
                                                         normally discards NXM write operations, but will also alias them when LMC(0..0)_CONTROL
                                                         [NXM_WRITE_EN]=1. */
#else
	uint64_t cs_mask                      : 4;
	uint64_t reserved_4_7                 : 4;
	uint64_t mem_msb_d0_r0                : 4;
	uint64_t mem_msb_d0_r1                : 4;
	uint64_t mem_msb_d1_r0                : 4;
	uint64_t mem_msb_d1_r1                : 4;
	uint64_t reserved_24_63               : 40;
#endif
	} cn70xx;
	struct cvmx_lmcx_nxm_cn70xx           cn78xx;
	struct cvmx_lmcx_nxm_s                cnf71xx;
};
typedef union cvmx_lmcx_nxm cvmx_lmcx_nxm_t;

/**
 * cvmx_lmc#_nxm_fadr
 *
 * This register captures only the first transaction with a NXM error while an interrupt is
 * pending, and only captures a subsequent event once the interrupt is cleared by writing a 1 to
 * LMC(0..3)_INT[NXM_ERR]. It captures the actual L2C-LMC address provided to the LMC that caused
 * the NXM error. A read or write NXM error is captured only if enabled using the NXM event
 * enables.
 */
union cvmx_lmcx_nxm_fadr {
	uint64_t u64;
	struct cvmx_lmcx_nxm_fadr_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_39_63               : 25;
	uint64_t nxm_src                      : 1;  /**< Indicates the source of the operation that caused a NXM error:
                                                         0 = L2C, 1 = HFA */
	uint64_t nxm_type                     : 1;  /**< Indicates the type of operation that caused NXM error:
                                                         0 = Read, 1 = Write */
	uint64_t nxm_faddr                    : 37; /**< Failing L2C-LMC address. Bits<3:0> are always 0s for an HFA access, and bits<4:0> are
                                                         always 0s for an L2C access. Bits<5:4> represent the fill order for an L2C read operation,
                                                         and the start point within a cache line for a write operation. */
#else
	uint64_t nxm_faddr                    : 37;
	uint64_t nxm_type                     : 1;
	uint64_t nxm_src                      : 1;
	uint64_t reserved_39_63               : 25;
#endif
	} s;
	struct cvmx_lmcx_nxm_fadr_s           cn70xx;
	struct cvmx_lmcx_nxm_fadr_s           cn78xx;
};
typedef union cvmx_lmcx_nxm_fadr cvmx_lmcx_nxm_fadr_t;

/**
 * cvmx_lmc#_ops_cnt
 *
 * LMC_OPS_CNT  = Performance Counters
 *
 */
union cvmx_lmcx_ops_cnt {
	uint64_t u64;
	struct cvmx_lmcx_ops_cnt_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t opscnt                       : 64; /**< Performance Counter
                                                         64-bit counter that increments when the DDR3 data bus
                                                         is being used
                                                         DRAM bus utilization = LMC*_OPS_CNT/LMC*_DCLK_CNT */
#else
	uint64_t opscnt                       : 64;
#endif
	} s;
	struct cvmx_lmcx_ops_cnt_s            cn61xx;
	struct cvmx_lmcx_ops_cnt_s            cn63xx;
	struct cvmx_lmcx_ops_cnt_s            cn63xxp1;
	struct cvmx_lmcx_ops_cnt_s            cn66xx;
	struct cvmx_lmcx_ops_cnt_s            cn68xx;
	struct cvmx_lmcx_ops_cnt_s            cn68xxp1;
	struct cvmx_lmcx_ops_cnt_s            cn70xx;
	struct cvmx_lmcx_ops_cnt_s            cn78xx;
	struct cvmx_lmcx_ops_cnt_s            cnf71xx;
};
typedef union cvmx_lmcx_ops_cnt cvmx_lmcx_ops_cnt_t;

/**
 * cvmx_lmc#_ops_cnt_hi
 *
 * LMC_OPS_CNT_HI  = Performance Counters
 *
 */
union cvmx_lmcx_ops_cnt_hi {
	uint64_t u64;
	struct cvmx_lmcx_ops_cnt_hi_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t opscnt_hi                    : 32; /**< Performance Counter to measure Bus Utilization
                                                         Upper 32-bits of 64-bit counter
                                                           DRAM bus utilization = LMC_OPS_CNT_* /LMC_DCLK_CNT_* */
#else
	uint64_t opscnt_hi                    : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_ops_cnt_hi_s         cn30xx;
	struct cvmx_lmcx_ops_cnt_hi_s         cn31xx;
	struct cvmx_lmcx_ops_cnt_hi_s         cn38xx;
	struct cvmx_lmcx_ops_cnt_hi_s         cn38xxp2;
	struct cvmx_lmcx_ops_cnt_hi_s         cn50xx;
	struct cvmx_lmcx_ops_cnt_hi_s         cn52xx;
	struct cvmx_lmcx_ops_cnt_hi_s         cn52xxp1;
	struct cvmx_lmcx_ops_cnt_hi_s         cn56xx;
	struct cvmx_lmcx_ops_cnt_hi_s         cn56xxp1;
	struct cvmx_lmcx_ops_cnt_hi_s         cn58xx;
	struct cvmx_lmcx_ops_cnt_hi_s         cn58xxp1;
};
typedef union cvmx_lmcx_ops_cnt_hi cvmx_lmcx_ops_cnt_hi_t;

/**
 * cvmx_lmc#_ops_cnt_lo
 *
 * LMC_OPS_CNT_LO  = Performance Counters
 *
 */
union cvmx_lmcx_ops_cnt_lo {
	uint64_t u64;
	struct cvmx_lmcx_ops_cnt_lo_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t opscnt_lo                    : 32; /**< Performance Counter
                                                         Low 32-bits of 64-bit counter
                                                           DRAM bus utilization = LMC_OPS_CNT_* /LMC_DCLK_CNT_* */
#else
	uint64_t opscnt_lo                    : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_ops_cnt_lo_s         cn30xx;
	struct cvmx_lmcx_ops_cnt_lo_s         cn31xx;
	struct cvmx_lmcx_ops_cnt_lo_s         cn38xx;
	struct cvmx_lmcx_ops_cnt_lo_s         cn38xxp2;
	struct cvmx_lmcx_ops_cnt_lo_s         cn50xx;
	struct cvmx_lmcx_ops_cnt_lo_s         cn52xx;
	struct cvmx_lmcx_ops_cnt_lo_s         cn52xxp1;
	struct cvmx_lmcx_ops_cnt_lo_s         cn56xx;
	struct cvmx_lmcx_ops_cnt_lo_s         cn56xxp1;
	struct cvmx_lmcx_ops_cnt_lo_s         cn58xx;
	struct cvmx_lmcx_ops_cnt_lo_s         cn58xxp1;
};
typedef union cvmx_lmcx_ops_cnt_lo cvmx_lmcx_ops_cnt_lo_t;

/**
 * cvmx_lmc#_phy_ctl
 *
 * LMC_PHY_CTL = LMC PHY Control
 *
 */
union cvmx_lmcx_phy_ctl {
	uint64_t u64;
	struct cvmx_lmcx_phy_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_51_63               : 13;
	uint64_t phy_reset                    : 1;  /**< Reserved. INTERNAL: Write to 1 to reset the PHY, one-shot operation, will automatically
                                                         clear to value of 0. */
	uint64_t dsk_dbg_rd_complete          : 1;  /**< Reserved. INTERNAL: Indicates completion of a read operation, will clear to 0 when a read
                                                         operation is started, then set to 1 when operation is complete. */
	uint64_t dsk_dbg_rd_data              : 10; /**< Reserved. INTERNAL: Data from a deskew read operation. Only valid when the
                                                         LMCX_PHY_CTL[DSK_DBG_RD_COMPLETE] bit is set. */
	uint64_t dsk_dbg_rd_start             : 1;  /**< Reserved. INTERNAL: Write 1 to start deskew data read operation, will automatically clear
                                                         to 0. Write to 1 will also clear the complete bit. */
	uint64_t dsk_dbg_clk_scaler           : 2;  /**< Reserved. INTERNAL: Adjust clock toggle rate for reading deskew debug information:
                                                         0 = Deskew read clock toggles every 4 DCLK
                                                         1 = Deskew read clock toggles every 8 DCLKs
                                                         2 = Deskew read clock toggles every 12 DCLKs
                                                         3 = Deskew read clock toggles every 16 DCLKs */
	uint64_t dsk_dbg_offset               : 2;  /**< Reserved. INTERNAL: Offset to change delay of deskew debug data return time to LMC from
                                                         DDR PHY. */
	uint64_t dsk_dbg_num_bits_sel         : 1;  /**< Reserved. INTERNAL: Deskew debug, select number of bits per byte lane.
                                                         0 = 8 bits per byte lane, no DBI
                                                         1 = 9 bits ber byte lane, including DBI */
	uint64_t dsk_dbg_byte_sel             : 4;  /**< Reserved. INTERNAL: Deskew debug byte select for read operation.  Values 0-3 correspond to
                                                         byte lanes 0-3, 4 is for ECC, 5-8 are byte lanes 4-7. */
	uint64_t dsk_dbg_bit_sel              : 4;  /**< Reserved. INTERNAL: Deskew debug bit select for dsk read operation. */
	uint64_t dbi_mode_ena                 : 1;  /**< Enable DBI mode for PHY. */
	uint64_t ddr_error_n_ena              : 1;  /**< Enable error_alert_n signal for PHY. */
	uint64_t ref_pin_on                   : 1;  /**< Reserved. INTERNAL: Voltage reference pin enabled. */
	uint64_t dac_on                       : 1;  /**< Reserved. INTERNAL: PHY DAC on. */
	uint64_t int_pad_loopback_ena         : 1;  /**< DDR pad loopback enable. */
	uint64_t int_phy_loopback_ena         : 1;  /**< Internal PHY loopback enable. */
	uint64_t phy_dsk_reset                : 1;  /**< PHY deskew reset. When set, the deskew reset signal goes active if the vrefint/deskew
                                                         training sequence is in the idle state. */
	uint64_t phy_dsk_byp                  : 1;  /**< PHY deskew bypass. */
	uint64_t phy_pwr_save_disable         : 1;  /**< DDR PHY power save disable. */
	uint64_t ten                          : 1;  /**< DDR PHY test enable pin. */
	uint64_t rx_always_on                 : 1;  /**< Disable dynamic DDR3 IO Rx power gating */
	uint64_t lv_mode                      : 1;  /**< Low Voltage Mode (1.35V) */
	uint64_t ck_tune1                     : 1;  /**< Clock Tune */
	uint64_t ck_dlyout1                   : 4;  /**< Clock delay out setting */
	uint64_t ck_tune0                     : 1;  /**< Clock Tune */
	uint64_t ck_dlyout0                   : 4;  /**< Clock delay out setting */
	uint64_t loopback                     : 1;  /**< Loopback enable */
	uint64_t loopback_pos                 : 1;  /**< Loopback pos mode */
	uint64_t ts_stagger                   : 1;  /**< TS Staggermode
                                                         This mode configures output drivers with 2-stage drive
                                                         strength to avoid undershoot issues on the bus when strong
                                                         drivers are suddenly turned on. When this mode is asserted,
                                                         Octeon will configure output drivers to be weak drivers
                                                         (60 ohm output impedance) at the first CK cycle, and
                                                         change drivers to the designated drive strengths specified
                                                         in $LMC(0)_COMP_CTL2 [CMD_CTL/CK_CTL/DQX_CTL] starting
                                                         at the following cycle */
#else
	uint64_t ts_stagger                   : 1;
	uint64_t loopback_pos                 : 1;
	uint64_t loopback                     : 1;
	uint64_t ck_dlyout0                   : 4;
	uint64_t ck_tune0                     : 1;
	uint64_t ck_dlyout1                   : 4;
	uint64_t ck_tune1                     : 1;
	uint64_t lv_mode                      : 1;
	uint64_t rx_always_on                 : 1;
	uint64_t ten                          : 1;
	uint64_t phy_pwr_save_disable         : 1;
	uint64_t phy_dsk_byp                  : 1;
	uint64_t phy_dsk_reset                : 1;
	uint64_t int_phy_loopback_ena         : 1;
	uint64_t int_pad_loopback_ena         : 1;
	uint64_t dac_on                       : 1;
	uint64_t ref_pin_on                   : 1;
	uint64_t ddr_error_n_ena              : 1;
	uint64_t dbi_mode_ena                 : 1;
	uint64_t dsk_dbg_bit_sel              : 4;
	uint64_t dsk_dbg_byte_sel             : 4;
	uint64_t dsk_dbg_num_bits_sel         : 1;
	uint64_t dsk_dbg_offset               : 2;
	uint64_t dsk_dbg_clk_scaler           : 2;
	uint64_t dsk_dbg_rd_start             : 1;
	uint64_t dsk_dbg_rd_data              : 10;
	uint64_t dsk_dbg_rd_complete          : 1;
	uint64_t phy_reset                    : 1;
	uint64_t reserved_51_63               : 13;
#endif
	} s;
	struct cvmx_lmcx_phy_ctl_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_15_63               : 49;
	uint64_t rx_always_on                 : 1;  /**< Disable dynamic DDR3 IO Rx power gating */
	uint64_t lv_mode                      : 1;  /**< Low Voltage Mode (1.35V) */
	uint64_t ck_tune1                     : 1;  /**< Clock Tune */
	uint64_t ck_dlyout1                   : 4;  /**< Clock delay out setting */
	uint64_t ck_tune0                     : 1;  /**< Clock Tune */
	uint64_t ck_dlyout0                   : 4;  /**< Clock delay out setting */
	uint64_t loopback                     : 1;  /**< Loopback enable */
	uint64_t loopback_pos                 : 1;  /**< Loopback pos mode */
	uint64_t ts_stagger                   : 1;  /**< TS Staggermode
                                                         This mode configures output drivers with 2-stage drive
                                                         strength to avoid undershoot issues on the bus when strong
                                                         drivers are suddenly turned on. When this mode is asserted,
                                                         Octeon will configure output drivers to be weak drivers
                                                         (60 ohm output impedance) at the first CK cycle, and
                                                         change drivers to the designated drive strengths specified
                                                         in $LMC(0)_COMP_CTL2 [CMD_CTL/CK_CTL/DQX_CTL] starting
                                                         at the following cycle */
#else
	uint64_t ts_stagger                   : 1;
	uint64_t loopback_pos                 : 1;
	uint64_t loopback                     : 1;
	uint64_t ck_dlyout0                   : 4;
	uint64_t ck_tune0                     : 1;
	uint64_t ck_dlyout1                   : 4;
	uint64_t ck_tune1                     : 1;
	uint64_t lv_mode                      : 1;
	uint64_t rx_always_on                 : 1;
	uint64_t reserved_15_63               : 49;
#endif
	} cn61xx;
	struct cvmx_lmcx_phy_ctl_cn61xx       cn63xx;
	struct cvmx_lmcx_phy_ctl_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_14_63               : 50;
	uint64_t lv_mode                      : 1;  /**< Low Voltage Mode (1.35V) */
	uint64_t ck_tune1                     : 1;  /**< Clock Tune */
	uint64_t ck_dlyout1                   : 4;  /**< Clock delay out setting */
	uint64_t ck_tune0                     : 1;  /**< Clock Tune */
	uint64_t ck_dlyout0                   : 4;  /**< Clock delay out setting */
	uint64_t loopback                     : 1;  /**< Loopback enable */
	uint64_t loopback_pos                 : 1;  /**< Loopback pos mode */
	uint64_t ts_stagger                   : 1;  /**< TS Staggermode
                                                         This mode configures output drivers with 2-stage drive
                                                         strength to avoid undershoot issues on the bus when strong
                                                         drivers are suddenly turned on. When this mode is asserted,
                                                         Octeon will configure output drivers to be weak drivers
                                                         (60 ohm output impedance) at the first CK cycle, and
                                                         change drivers to the designated drive strengths specified
                                                         in $LMC(0)_COMP_CTL2 [CMD_CTL/CK_CTL/DQX_CTL] starting
                                                         at the following cycle */
#else
	uint64_t ts_stagger                   : 1;
	uint64_t loopback_pos                 : 1;
	uint64_t loopback                     : 1;
	uint64_t ck_dlyout0                   : 4;
	uint64_t ck_tune0                     : 1;
	uint64_t ck_dlyout1                   : 4;
	uint64_t ck_tune1                     : 1;
	uint64_t lv_mode                      : 1;
	uint64_t reserved_14_63               : 50;
#endif
	} cn63xxp1;
	struct cvmx_lmcx_phy_ctl_cn61xx       cn66xx;
	struct cvmx_lmcx_phy_ctl_cn61xx       cn68xx;
	struct cvmx_lmcx_phy_ctl_cn61xx       cn68xxp1;
	struct cvmx_lmcx_phy_ctl_s            cn70xx;
	struct cvmx_lmcx_phy_ctl_s            cn78xx;
	struct cvmx_lmcx_phy_ctl_cn61xx       cnf71xx;
};
typedef union cvmx_lmcx_phy_ctl cvmx_lmcx_phy_ctl_t;

/**
 * cvmx_lmc#_pll_bwctl
 *
 * LMC_PLL_BWCTL  = DDR PLL Bandwidth Control Register
 *
 */
union cvmx_lmcx_pll_bwctl {
	uint64_t u64;
	struct cvmx_lmcx_pll_bwctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_5_63                : 59;
	uint64_t bwupd                        : 1;  /**< Load this Bandwidth Register value into the PLL */
	uint64_t bwctl                        : 4;  /**< Bandwidth Control Register for DDR PLL */
#else
	uint64_t bwctl                        : 4;
	uint64_t bwupd                        : 1;
	uint64_t reserved_5_63                : 59;
#endif
	} s;
	struct cvmx_lmcx_pll_bwctl_s          cn30xx;
	struct cvmx_lmcx_pll_bwctl_s          cn31xx;
	struct cvmx_lmcx_pll_bwctl_s          cn38xx;
	struct cvmx_lmcx_pll_bwctl_s          cn38xxp2;
};
typedef union cvmx_lmcx_pll_bwctl cvmx_lmcx_pll_bwctl_t;

/**
 * cvmx_lmc#_pll_ctl
 *
 * LMC_PLL_CTL = LMC pll control
 *
 *
 * Notes:
 * This CSR is only relevant for LMC0. LMC1_PLL_CTL is not used.
 *
 * Exactly one of EN2, EN4, EN6, EN8, EN12, EN16 must be set.
 *
 * The resultant DDR_CK frequency is the DDR2_REF_CLK
 * frequency multiplied by:
 *
 *     (CLKF + 1) / ((CLKR + 1) * EN(2,4,6,8,12,16))
 *
 * The PLL frequency, which is:
 *
 *     (DDR2_REF_CLK freq) * ((CLKF + 1) / (CLKR + 1))
 *
 * must reside between 1.2 and 2.5 GHz. A faster PLL frequency is desirable if there is a choice.
 */
union cvmx_lmcx_pll_ctl {
	uint64_t u64;
	struct cvmx_lmcx_pll_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_30_63               : 34;
	uint64_t bypass                       : 1;  /**< PLL Bypass */
	uint64_t fasten_n                     : 1;  /**< Should be set, especially when CLKF > ~80 */
	uint64_t div_reset                    : 1;  /**< Analog pll divider reset
                                                         De-assert at least 500*(CLKR+1) reference clock
                                                         cycles following RESET_N de-assertion. */
	uint64_t reset_n                      : 1;  /**< Analog pll reset
                                                         De-assert at least 5 usec after CLKF, CLKR,
                                                         and EN* are set up. */
	uint64_t clkf                         : 12; /**< Multiply reference by CLKF + 1
                                                         CLKF must be <= 128 */
	uint64_t clkr                         : 6;  /**< Divide reference by CLKR + 1 */
	uint64_t reserved_6_7                 : 2;
	uint64_t en16                         : 1;  /**< Divide output by 16 */
	uint64_t en12                         : 1;  /**< Divide output by 12 */
	uint64_t en8                          : 1;  /**< Divide output by 8 */
	uint64_t en6                          : 1;  /**< Divide output by 6 */
	uint64_t en4                          : 1;  /**< Divide output by 4 */
	uint64_t en2                          : 1;  /**< Divide output by 2 */
#else
	uint64_t en2                          : 1;
	uint64_t en4                          : 1;
	uint64_t en6                          : 1;
	uint64_t en8                          : 1;
	uint64_t en12                         : 1;
	uint64_t en16                         : 1;
	uint64_t reserved_6_7                 : 2;
	uint64_t clkr                         : 6;
	uint64_t clkf                         : 12;
	uint64_t reset_n                      : 1;
	uint64_t div_reset                    : 1;
	uint64_t fasten_n                     : 1;
	uint64_t bypass                       : 1;
	uint64_t reserved_30_63               : 34;
#endif
	} s;
	struct cvmx_lmcx_pll_ctl_cn50xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_29_63               : 35;
	uint64_t fasten_n                     : 1;  /**< Should be set, especially when CLKF > ~80 */
	uint64_t div_reset                    : 1;  /**< Analog pll divider reset
                                                         De-assert at least 500*(CLKR+1) reference clock
                                                         cycles following RESET_N de-assertion. */
	uint64_t reset_n                      : 1;  /**< Analog pll reset
                                                         De-assert at least 5 usec after CLKF, CLKR,
                                                         and EN* are set up. */
	uint64_t clkf                         : 12; /**< Multiply reference by CLKF + 1
                                                         CLKF must be <= 256 */
	uint64_t clkr                         : 6;  /**< Divide reference by CLKR + 1 */
	uint64_t reserved_6_7                 : 2;
	uint64_t en16                         : 1;  /**< Divide output by 16 */
	uint64_t en12                         : 1;  /**< Divide output by 12 */
	uint64_t en8                          : 1;  /**< Divide output by 8 */
	uint64_t en6                          : 1;  /**< Divide output by 6 */
	uint64_t en4                          : 1;  /**< Divide output by 4 */
	uint64_t en2                          : 1;  /**< Divide output by 2 */
#else
	uint64_t en2                          : 1;
	uint64_t en4                          : 1;
	uint64_t en6                          : 1;
	uint64_t en8                          : 1;
	uint64_t en12                         : 1;
	uint64_t en16                         : 1;
	uint64_t reserved_6_7                 : 2;
	uint64_t clkr                         : 6;
	uint64_t clkf                         : 12;
	uint64_t reset_n                      : 1;
	uint64_t div_reset                    : 1;
	uint64_t fasten_n                     : 1;
	uint64_t reserved_29_63               : 35;
#endif
	} cn50xx;
	struct cvmx_lmcx_pll_ctl_s            cn52xx;
	struct cvmx_lmcx_pll_ctl_s            cn52xxp1;
	struct cvmx_lmcx_pll_ctl_cn50xx       cn56xx;
	struct cvmx_lmcx_pll_ctl_cn56xxp1 {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_28_63               : 36;
	uint64_t div_reset                    : 1;  /**< Analog pll divider reset
                                                         De-assert at least 500*(CLKR+1) reference clock
                                                         cycles following RESET_N de-assertion. */
	uint64_t reset_n                      : 1;  /**< Analog pll reset
                                                         De-assert at least 5 usec after CLKF, CLKR,
                                                         and EN* are set up. */
	uint64_t clkf                         : 12; /**< Multiply reference by CLKF + 1
                                                         CLKF must be <= 128 */
	uint64_t clkr                         : 6;  /**< Divide reference by CLKR + 1 */
	uint64_t reserved_6_7                 : 2;
	uint64_t en16                         : 1;  /**< Divide output by 16 */
	uint64_t en12                         : 1;  /**< Divide output by 12 */
	uint64_t en8                          : 1;  /**< Divide output by 8 */
	uint64_t en6                          : 1;  /**< Divide output by 6 */
	uint64_t en4                          : 1;  /**< Divide output by 4 */
	uint64_t en2                          : 1;  /**< Divide output by 2 */
#else
	uint64_t en2                          : 1;
	uint64_t en4                          : 1;
	uint64_t en6                          : 1;
	uint64_t en8                          : 1;
	uint64_t en12                         : 1;
	uint64_t en16                         : 1;
	uint64_t reserved_6_7                 : 2;
	uint64_t clkr                         : 6;
	uint64_t clkf                         : 12;
	uint64_t reset_n                      : 1;
	uint64_t div_reset                    : 1;
	uint64_t reserved_28_63               : 36;
#endif
	} cn56xxp1;
	struct cvmx_lmcx_pll_ctl_cn56xxp1     cn58xx;
	struct cvmx_lmcx_pll_ctl_cn56xxp1     cn58xxp1;
};
typedef union cvmx_lmcx_pll_ctl cvmx_lmcx_pll_ctl_t;

/**
 * cvmx_lmc#_pll_status
 *
 * LMC_PLL_STATUS = LMC pll status
 *
 */
union cvmx_lmcx_pll_status {
	uint64_t u64;
	struct cvmx_lmcx_pll_status_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ddr__nctl                    : 5;  /**< DDR nctl from compensation circuit */
	uint64_t ddr__pctl                    : 5;  /**< DDR pctl from compensation circuit */
	uint64_t reserved_2_21                : 20;
	uint64_t rfslip                       : 1;  /**< Reference clock slip */
	uint64_t fbslip                       : 1;  /**< Feedback clock slip */
#else
	uint64_t fbslip                       : 1;
	uint64_t rfslip                       : 1;
	uint64_t reserved_2_21                : 20;
	uint64_t ddr__pctl                    : 5;
	uint64_t ddr__nctl                    : 5;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_pll_status_s         cn50xx;
	struct cvmx_lmcx_pll_status_s         cn52xx;
	struct cvmx_lmcx_pll_status_s         cn52xxp1;
	struct cvmx_lmcx_pll_status_s         cn56xx;
	struct cvmx_lmcx_pll_status_s         cn56xxp1;
	struct cvmx_lmcx_pll_status_s         cn58xx;
	struct cvmx_lmcx_pll_status_cn58xxp1 {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_2_63                : 62;
	uint64_t rfslip                       : 1;  /**< Reference clock slip */
	uint64_t fbslip                       : 1;  /**< Feedback clock slip */
#else
	uint64_t fbslip                       : 1;
	uint64_t rfslip                       : 1;
	uint64_t reserved_2_63                : 62;
#endif
	} cn58xxp1;
};
typedef union cvmx_lmcx_pll_status cvmx_lmcx_pll_status_t;

/**
 * cvmx_lmc#_read_level_ctl
 *
 * Notes:
 * The HW writes and reads the cache block selected by ROW, COL, BNK and the rank as part of a read-leveling sequence for a rank.
 * A cache block write is 16 72-bit words. PATTERN selects the write value. For the first 8
 * words, the write value is the bit PATTERN<i> duplicated into a 72-bit vector. The write value of
 * the last 8 words is the inverse of the write value of the first 8 words.
 * See LMC*_READ_LEVEL_RANK*.
 */
union cvmx_lmcx_read_level_ctl {
	uint64_t u64;
	struct cvmx_lmcx_read_level_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_44_63               : 20;
	uint64_t rankmask                     : 4;  /**< Selects ranks to be leveled
                                                         to read-level rank i, set RANKMASK<i> */
	uint64_t pattern                      : 8;  /**< All DQ driven to PATTERN[burst], 0 <= burst <= 7
                                                         All DQ driven to ~PATTERN[burst-8], 8 <= burst <= 15 */
	uint64_t row                          : 16; /**< Row    address used to write/read data pattern */
	uint64_t col                          : 12; /**< Column address used to write/read data pattern */
	uint64_t reserved_3_3                 : 1;
	uint64_t bnk                          : 3;  /**< Bank   address used to write/read data pattern */
#else
	uint64_t bnk                          : 3;
	uint64_t reserved_3_3                 : 1;
	uint64_t col                          : 12;
	uint64_t row                          : 16;
	uint64_t pattern                      : 8;
	uint64_t rankmask                     : 4;
	uint64_t reserved_44_63               : 20;
#endif
	} s;
	struct cvmx_lmcx_read_level_ctl_s     cn52xx;
	struct cvmx_lmcx_read_level_ctl_s     cn52xxp1;
	struct cvmx_lmcx_read_level_ctl_s     cn56xx;
	struct cvmx_lmcx_read_level_ctl_s     cn56xxp1;
};
typedef union cvmx_lmcx_read_level_ctl cvmx_lmcx_read_level_ctl_t;

/**
 * cvmx_lmc#_read_level_dbg
 *
 * Notes:
 * A given read of LMC*_READ_LEVEL_DBG returns the read-leveling pass/fail results for all possible
 * delay settings (i.e. the BITMASK) for only one byte in the last rank that the HW read-leveled.
 * LMC*_READ_LEVEL_DBG[BYTE] selects the particular byte.
 * To get these pass/fail results for another different rank, you must run the hardware read-leveling
 * again. For example, it is possible to get the BITMASK results for every byte of every rank
 * if you run read-leveling separately for each rank, probing LMC*_READ_LEVEL_DBG between each
 * read-leveling.
 */
union cvmx_lmcx_read_level_dbg {
	uint64_t u64;
	struct cvmx_lmcx_read_level_dbg_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t bitmask                      : 16; /**< Bitmask generated during deskew settings sweep
                                                         BITMASK[n]=0 means deskew setting n failed
                                                         BITMASK[n]=1 means deskew setting n passed
                                                         for 0 <= n <= 15 */
	uint64_t reserved_4_15                : 12;
	uint64_t byte                         : 4;  /**< 0 <= BYTE <= 8 */
#else
	uint64_t byte                         : 4;
	uint64_t reserved_4_15                : 12;
	uint64_t bitmask                      : 16;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_read_level_dbg_s     cn52xx;
	struct cvmx_lmcx_read_level_dbg_s     cn52xxp1;
	struct cvmx_lmcx_read_level_dbg_s     cn56xx;
	struct cvmx_lmcx_read_level_dbg_s     cn56xxp1;
};
typedef union cvmx_lmcx_read_level_dbg cvmx_lmcx_read_level_dbg_t;

/**
 * cvmx_lmc#_read_level_rank#
 *
 * Notes:
 * This is four CSRs per LMC, one per each rank.
 * Each CSR is written by HW during a read-leveling sequence for the rank. (HW sets STATUS==3 after HW read-leveling completes for the rank.)
 * Each CSR may also be written by SW, but not while a read-leveling sequence is in progress. (HW sets STATUS==1 after a CSR write.)
 * Deskew setting is measured in units of 1/4 DCLK, so the above BYTE* values can range over 4 DCLKs.
 * SW initiates a HW read-leveling sequence by programming LMC*_READ_LEVEL_CTL and writing INIT_START=1 with SEQUENCE=1.
 * See LMC*_READ_LEVEL_CTL.
 */
union cvmx_lmcx_read_level_rankx {
	uint64_t u64;
	struct cvmx_lmcx_read_level_rankx_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_38_63               : 26;
	uint64_t status                       : 2;  /**< Indicates status of the read-levelling and where
                                                         the BYTE* programmings in <35:0> came from:
                                                         0 = BYTE* values are their reset value
                                                         1 = BYTE* values were set via a CSR write to this register
                                                         2 = read-leveling sequence currently in progress (BYTE* values are unpredictable)
                                                         3 = BYTE* values came from a complete read-leveling sequence */
	uint64_t byte8                        : 4;  /**< Deskew setting */
	uint64_t byte7                        : 4;  /**< Deskew setting */
	uint64_t byte6                        : 4;  /**< Deskew setting */
	uint64_t byte5                        : 4;  /**< Deskew setting */
	uint64_t byte4                        : 4;  /**< Deskew setting */
	uint64_t byte3                        : 4;  /**< Deskew setting */
	uint64_t byte2                        : 4;  /**< Deskew setting */
	uint64_t byte1                        : 4;  /**< Deskew setting */
	uint64_t byte0                        : 4;  /**< Deskew setting */
#else
	uint64_t byte0                        : 4;
	uint64_t byte1                        : 4;
	uint64_t byte2                        : 4;
	uint64_t byte3                        : 4;
	uint64_t byte4                        : 4;
	uint64_t byte5                        : 4;
	uint64_t byte6                        : 4;
	uint64_t byte7                        : 4;
	uint64_t byte8                        : 4;
	uint64_t status                       : 2;
	uint64_t reserved_38_63               : 26;
#endif
	} s;
	struct cvmx_lmcx_read_level_rankx_s   cn52xx;
	struct cvmx_lmcx_read_level_rankx_s   cn52xxp1;
	struct cvmx_lmcx_read_level_rankx_s   cn56xx;
	struct cvmx_lmcx_read_level_rankx_s   cn56xxp1;
};
typedef union cvmx_lmcx_read_level_rankx cvmx_lmcx_read_level_rankx_t;

/**
 * cvmx_lmc#_reset_ctl
 *
 * "Specify the RSL base addresses for the block.
 * INTERNAL: DDR3RST DDR3 DRAM parts have a RESET# pin that wasn't present in DDR2 parts. The
 * DDR3RST CSR field controls the assertion of the 7xxx pin that attaches to RESET#. When DDR3RST
 * is set, 6xxx asserts RESET#. When DDR3RST is clear, 6xxx de-asserts RESET#. DDR3RST is set on
 * a cold reset. Warm and soft chip resets do not affect the DDR3RST value. Outside of cold
 * reset, only software CSR writes change the DDR3RST value. DDR3PWARM Enables preserve mode
 * during a warm reset. When set, the DDR3 controller hardware automatically puts the attached
 * DDR3 DRAM parts into self refresh (see LMC*CONFIG[SEQ_SEL] below) at the beginning of a warm
 * reset sequence, provided that the DDR3 controller is up. When clear, the DDR3 controller
 * hardware does not put the attached DDR3 DRAM parts into self-refresh during a warm reset
 * sequence. DDR3PWARM is cleared on a cold reset. Warm and soft chip resets do not affect the
 * DDR3PWARM value. Outside of cold reset, only software CSR writes change the DDR3PWARM value.
 * Note that if a warm reset follows a soft reset, DDR3PWARM has no effect, as the DDR3
 * controller is no longer up after any cold/warm/soft reset sequence. DDR3PSOFT Enables preserve
 * mode during a soft reset. When set, the DDR3 controller hardware automatically puts the
 * attached DDR3 DRAM parts into self refresh (see LMC*CONFIG[SEQ_SEL] below) at the beginning of
 * a soft reset sequence, provided that the DDR3 controller is up. When clear, the DDR3
 * controller hardware does not put the attached DDR3 DRAM parts into self-refresh during a soft
 * reset sequence. DDR3PSOFT is cleared on a cold reset. Warm and soft chip resets do not affect
 * the DDR3PSOFT value. Outside of cold reset, only software CSR writes change the DDR3PSOFT
 * value. DDR3PSV May be useful for system software to determine when the DDR3 contents have been
 * preserved. Cleared by hardware during a cold reset. Never cleared by hardware during a
 * warm/soft reset. Set by hardware during a warm/soft reset if the hardware automatically put
 * the DDR3 DRAM into self-refresh during the reset sequence. Can also be written by software (to
 * any value)."
 */
union cvmx_lmcx_reset_ctl {
	uint64_t u64;
	struct cvmx_lmcx_reset_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_4_63                : 60;
	uint64_t ddr3psv                      : 1;  /**< Memory Reset
                                                         1 = DDR contents preserved */
	uint64_t ddr3psoft                    : 1;  /**< Memory Reset
                                                         1 = Enable Preserve mode during soft reset */
	uint64_t ddr3pwarm                    : 1;  /**< Memory Reset
                                                         1 = Enable Preserve mode during warm reset */
	uint64_t ddr3rst                      : 1;  /**< Memory Reset
                                                         0 = Reset asserted
                                                         1 = Reset de-asserted */
#else
	uint64_t ddr3rst                      : 1;
	uint64_t ddr3pwarm                    : 1;
	uint64_t ddr3psoft                    : 1;
	uint64_t ddr3psv                      : 1;
	uint64_t reserved_4_63                : 60;
#endif
	} s;
	struct cvmx_lmcx_reset_ctl_s          cn61xx;
	struct cvmx_lmcx_reset_ctl_s          cn63xx;
	struct cvmx_lmcx_reset_ctl_s          cn63xxp1;
	struct cvmx_lmcx_reset_ctl_s          cn66xx;
	struct cvmx_lmcx_reset_ctl_s          cn68xx;
	struct cvmx_lmcx_reset_ctl_s          cn68xxp1;
	struct cvmx_lmcx_reset_ctl_s          cn70xx;
	struct cvmx_lmcx_reset_ctl_s          cn78xx;
	struct cvmx_lmcx_reset_ctl_s          cnf71xx;
};
typedef union cvmx_lmcx_reset_ctl cvmx_lmcx_reset_ctl_t;

/**
 * cvmx_lmc#_rlevel_ctl
 */
union cvmx_lmcx_rlevel_ctl {
	uint64_t u64;
	struct cvmx_lmcx_rlevel_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t pattern                      : 8;  /**< Sets the data pattern used to match in read-leveling operations. */
	uint64_t reserved_22_23               : 2;
	uint64_t delay_unload_3               : 1;  /**< When set, unload the PHY silo one cycle later
                                                         during read-leveling if LMC*_RLEVEL_RANKi[BYTE*<1:0>] = 3
                                                         DELAY_UNLOAD_3 should normally be set. */
	uint64_t delay_unload_2               : 1;  /**< When set, unload the PHY silo one cycle later
                                                         during read-leveling if LMC*_RLEVEL_RANKi[BYTE*<1:0>] = 2
                                                         DELAY_UNLOAD_2 should normally be set. */
	uint64_t delay_unload_1               : 1;  /**< When set, unload the PHY silo one cycle later
                                                         during read-leveling if LMC*_RLEVEL_RANKi[BYTE*<1:0>] = 1
                                                         DELAY_UNLOAD_1 should normally be set. */
	uint64_t delay_unload_0               : 1;  /**< When set, unload the PHY silo one cycle later
                                                         during read-leveling if LMC*_RLEVEL_RANKi[BYTE*<1:0>] = 0
                                                         DELAY_UNLOAD_0 should normally be set. */
	uint64_t bitmask                      : 8;  /**< Mask to select bit lanes on which read-leveling
                                                         feedback is returned when OR_DIS is set to 1 */
	uint64_t or_dis                       : 1;  /**< Disable or'ing of bits in a byte lane when computing
                                                         the read-leveling bitmask
                                                         OR_DIS should normally not be set. */
	uint64_t offset_en                    : 1;  /**< When set, LMC attempts to select the read-leveling
                                                         setting that is LMC*RLEVEL_CTL[OFFSET] settings earlier than the
                                                         last passing read-leveling setting in the largest
                                                         contiguous sequence of passing settings.
                                                         When clear, or if the setting selected by LMC*RLEVEL_CTL[OFFSET]
                                                         did not pass, LMC selects the middle setting in the
                                                         largest contiguous sequence of passing settings,
                                                         rounding earlier when necessary. */
	uint64_t offset                       : 4;  /**< The offset used when LMC*RLEVEL_CTL[OFFSET] is set */
	uint64_t byte                         : 4;  /**< 0 <= BYTE <= 8
                                                         Byte index for which bitmask results are saved
                                                         in LMC*_RLEVEL_DBG */
#else
	uint64_t byte                         : 4;
	uint64_t offset                       : 4;
	uint64_t offset_en                    : 1;
	uint64_t or_dis                       : 1;
	uint64_t bitmask                      : 8;
	uint64_t delay_unload_0               : 1;
	uint64_t delay_unload_1               : 1;
	uint64_t delay_unload_2               : 1;
	uint64_t delay_unload_3               : 1;
	uint64_t reserved_22_23               : 2;
	uint64_t pattern                      : 8;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_rlevel_ctl_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_22_63               : 42;
	uint64_t delay_unload_3               : 1;  /**< When set, unload the PHY silo one cycle later
                                                         during read-leveling if LMC*_RLEVEL_RANKi[BYTE*<1:0>] = 3
                                                         DELAY_UNLOAD_3 should normally be set. */
	uint64_t delay_unload_2               : 1;  /**< When set, unload the PHY silo one cycle later
                                                         during read-leveling if LMC*_RLEVEL_RANKi[BYTE*<1:0>] = 2
                                                         DELAY_UNLOAD_2 should normally be set. */
	uint64_t delay_unload_1               : 1;  /**< When set, unload the PHY silo one cycle later
                                                         during read-leveling if LMC*_RLEVEL_RANKi[BYTE*<1:0>] = 1
                                                         DELAY_UNLOAD_1 should normally be set. */
	uint64_t delay_unload_0               : 1;  /**< When set, unload the PHY silo one cycle later
                                                         during read-leveling if LMC*_RLEVEL_RANKi[BYTE*<1:0>] = 0
                                                         DELAY_UNLOAD_0 should normally be set. */
	uint64_t bitmask                      : 8;  /**< Mask to select bit lanes on which read-leveling
                                                         feedback is returned when OR_DIS is set to 1 */
	uint64_t or_dis                       : 1;  /**< Disable or'ing of bits in a byte lane when computing
                                                         the read-leveling bitmask
                                                         OR_DIS should normally not be set. */
	uint64_t offset_en                    : 1;  /**< When set, LMC attempts to select the read-leveling
                                                         setting that is LMC*RLEVEL_CTL[OFFSET] settings earlier than the
                                                         last passing read-leveling setting in the largest
                                                         contiguous sequence of passing settings.
                                                         When clear, or if the setting selected by LMC*RLEVEL_CTL[OFFSET]
                                                         did not pass, LMC selects the middle setting in the
                                                         largest contiguous sequence of passing settings,
                                                         rounding earlier when necessary. */
	uint64_t offset                       : 4;  /**< The offset used when LMC*RLEVEL_CTL[OFFSET] is set */
	uint64_t byte                         : 4;  /**< 0 <= BYTE <= 8
                                                         Byte index for which bitmask results are saved
                                                         in LMC*_RLEVEL_DBG */
#else
	uint64_t byte                         : 4;
	uint64_t offset                       : 4;
	uint64_t offset_en                    : 1;
	uint64_t or_dis                       : 1;
	uint64_t bitmask                      : 8;
	uint64_t delay_unload_0               : 1;
	uint64_t delay_unload_1               : 1;
	uint64_t delay_unload_2               : 1;
	uint64_t delay_unload_3               : 1;
	uint64_t reserved_22_63               : 42;
#endif
	} cn61xx;
	struct cvmx_lmcx_rlevel_ctl_cn61xx    cn63xx;
	struct cvmx_lmcx_rlevel_ctl_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_9_63                : 55;
	uint64_t offset_en                    : 1;  /**< When set, LMC attempts to select the read-leveling
                                                         setting that is LMC*RLEVEL_CTL[OFFSET] settings earlier than the
                                                         last passing read-leveling setting in the largest
                                                         contiguous sequence of passing settings.
                                                         When clear, or if the setting selected by LMC*RLEVEL_CTL[OFFSET]
                                                         did not pass, LMC selects the middle setting in the
                                                         largest contiguous sequence of passing settings,
                                                         rounding earlier when necessary. */
	uint64_t offset                       : 4;  /**< The offset used when LMC*RLEVEL_CTL[OFFSET] is set */
	uint64_t byte                         : 4;  /**< 0 <= BYTE <= 8
                                                         Byte index for which bitmask results are saved
                                                         in LMC*_RLEVEL_DBG */
#else
	uint64_t byte                         : 4;
	uint64_t offset                       : 4;
	uint64_t offset_en                    : 1;
	uint64_t reserved_9_63                : 55;
#endif
	} cn63xxp1;
	struct cvmx_lmcx_rlevel_ctl_cn61xx    cn66xx;
	struct cvmx_lmcx_rlevel_ctl_cn61xx    cn68xx;
	struct cvmx_lmcx_rlevel_ctl_cn61xx    cn68xxp1;
	struct cvmx_lmcx_rlevel_ctl_s         cn70xx;
	struct cvmx_lmcx_rlevel_ctl_s         cn78xx;
	struct cvmx_lmcx_rlevel_ctl_cn61xx    cnf71xx;
};
typedef union cvmx_lmcx_rlevel_ctl cvmx_lmcx_rlevel_ctl_t;

/**
 * cvmx_lmc#_rlevel_dbg
 *
 * A given read of LMC(0..3)_RLEVEL_DBG returns the read-leveling pass/fail results for all
 * possible delay settings (i.e. the BITMASK) for only one byte in the last rank that the
 * hardware ran read-leveling on. LMC(0..3)_RLEVEL_CTL[BYTE] selects the particular byte. To get
 * these pass/fail results for a different rank, you must run the hardware read-leveling again.
 * For example, it is possible to get the BITMASK results for every byte of every rank if you run
 * read-leveling separately for each rank, probing LMC(0..3)_RLEVEL_DBG between each read-
 * leveling.
 */
union cvmx_lmcx_rlevel_dbg {
	uint64_t u64;
	struct cvmx_lmcx_rlevel_dbg_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t bitmask                      : 64; /**< Bitmask generated during deskew settings sweep
                                                         BITMASK[n]=0 means deskew setting n failed
                                                         BITMASK[n]=1 means deskew setting n passed
                                                         for 0 <= n <= 63 */
#else
	uint64_t bitmask                      : 64;
#endif
	} s;
	struct cvmx_lmcx_rlevel_dbg_s         cn61xx;
	struct cvmx_lmcx_rlevel_dbg_s         cn63xx;
	struct cvmx_lmcx_rlevel_dbg_s         cn63xxp1;
	struct cvmx_lmcx_rlevel_dbg_s         cn66xx;
	struct cvmx_lmcx_rlevel_dbg_s         cn68xx;
	struct cvmx_lmcx_rlevel_dbg_s         cn68xxp1;
	struct cvmx_lmcx_rlevel_dbg_s         cn70xx;
	struct cvmx_lmcx_rlevel_dbg_s         cn78xx;
	struct cvmx_lmcx_rlevel_dbg_s         cnf71xx;
};
typedef union cvmx_lmcx_rlevel_dbg cvmx_lmcx_rlevel_dbg_t;

/**
 * cvmx_lmc#_rlevel_rank#
 *
 * Four of these CSRs exist per LMC, one for each rank. Deskew setting is measured in units of
 * 1/2 CK, so the BYTEn values can range over 16 CK cycles. Each CSR is written by hardware
 * during a read-leveling sequence for the rank. (Hardware sets STATUS to 3 after hardware read-
 * leveling completes for the rank.)
 * If hardware is unable to find a match per LMC(0..3)_RLEVEL_CTL[OFFSET_EN] and
 * LMC(0..3)_RLEVEL_CTL[OFFSET], then hardware sets LMC(0..3)_RLEVEL_RANK(0..3)[BYTEn<5:0>] to
 * 0x0.
 * Each CSR may also be written by software, but not while a read-leveling sequence is in
 * progress. (Hardware sets STATUS to 1 after a CSR write.) Software initiates a hardware read-
 * leveling sequence by programming LMC(0..3)_RLEVEL_CTL and writing INIT_START = 1 with
 * SEQ_SEL=1. See LMC*_RLEVEL_CTL.
 * LMC*_RLEVEL_RANKi values for ranks i without attached DRAM should be set such that they do not
 * increase the range of possible BYTE values for any byte lane. The easiest way to do this is to
 * set LMC*_RLEVEL_RANKi = LMC*_RLEVEL_RANKj, where j is some rank with attached DRAM whose
 * LMC*_RLEVEL_RANKj is already fully initialized.
 */
union cvmx_lmcx_rlevel_rankx {
	uint64_t u64;
	struct cvmx_lmcx_rlevel_rankx_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_56_63               : 8;
	uint64_t status                       : 2;  /**< Indicates status of the read-levelling and where
                                                         the BYTE* programmings in <35:0> came from:
                                                         0 = BYTE* values are their reset value
                                                         1 = BYTE* values were set via a CSR write to this register
                                                         2 = read-leveling sequence currently in progress (BYTE* values are unpredictable)
                                                         3 = BYTE* values came from a complete read-leveling sequence */
	uint64_t byte8                        : 6;  /**< Deskew setting
                                                         When ECC DRAM is not present (i.e. when DRAM is not
                                                         attached to chip signals DDR_CBS_0_* and DDR_CB[7:0]),
                                                         SW should write BYTE8 to a value that does
                                                         not increase the range of possible BYTE* values. The
                                                         easiest way to do this is to set
                                                         LMC*_RLEVEL_RANK*[BYTE8] = LMC*_RLEVEL_RANK*[BYTE0]
                                                         when there is no ECC DRAM, using the final BYTE0 value. */
	uint64_t byte7                        : 6;  /**< Deskew setting */
	uint64_t byte6                        : 6;  /**< Deskew setting */
	uint64_t byte5                        : 6;  /**< Deskew setting */
	uint64_t byte4                        : 6;  /**< Deskew setting */
	uint64_t byte3                        : 6;  /**< Deskew setting */
	uint64_t byte2                        : 6;  /**< Deskew setting */
	uint64_t byte1                        : 6;  /**< Deskew setting */
	uint64_t byte0                        : 6;  /**< Deskew setting */
#else
	uint64_t byte0                        : 6;
	uint64_t byte1                        : 6;
	uint64_t byte2                        : 6;
	uint64_t byte3                        : 6;
	uint64_t byte4                        : 6;
	uint64_t byte5                        : 6;
	uint64_t byte6                        : 6;
	uint64_t byte7                        : 6;
	uint64_t byte8                        : 6;
	uint64_t status                       : 2;
	uint64_t reserved_56_63               : 8;
#endif
	} s;
	struct cvmx_lmcx_rlevel_rankx_s       cn61xx;
	struct cvmx_lmcx_rlevel_rankx_s       cn63xx;
	struct cvmx_lmcx_rlevel_rankx_s       cn63xxp1;
	struct cvmx_lmcx_rlevel_rankx_s       cn66xx;
	struct cvmx_lmcx_rlevel_rankx_s       cn68xx;
	struct cvmx_lmcx_rlevel_rankx_s       cn68xxp1;
	struct cvmx_lmcx_rlevel_rankx_s       cn70xx;
	struct cvmx_lmcx_rlevel_rankx_s       cn78xx;
	struct cvmx_lmcx_rlevel_rankx_s       cnf71xx;
};
typedef union cvmx_lmcx_rlevel_rankx cvmx_lmcx_rlevel_rankx_t;

/**
 * cvmx_lmc#_rodt_comp_ctl
 *
 * LMC_RODT_COMP_CTL = LMC Compensation control
 *
 */
union cvmx_lmcx_rodt_comp_ctl {
	uint64_t u64;
	struct cvmx_lmcx_rodt_comp_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_17_63               : 47;
	uint64_t enable                       : 1;  /**< 0=not enabled, 1=enable */
	uint64_t reserved_12_15               : 4;
	uint64_t nctl                         : 4;  /**< Compensation control bits */
	uint64_t reserved_5_7                 : 3;
	uint64_t pctl                         : 5;  /**< Compensation control bits */
#else
	uint64_t pctl                         : 5;
	uint64_t reserved_5_7                 : 3;
	uint64_t nctl                         : 4;
	uint64_t reserved_12_15               : 4;
	uint64_t enable                       : 1;
	uint64_t reserved_17_63               : 47;
#endif
	} s;
	struct cvmx_lmcx_rodt_comp_ctl_s      cn50xx;
	struct cvmx_lmcx_rodt_comp_ctl_s      cn52xx;
	struct cvmx_lmcx_rodt_comp_ctl_s      cn52xxp1;
	struct cvmx_lmcx_rodt_comp_ctl_s      cn56xx;
	struct cvmx_lmcx_rodt_comp_ctl_s      cn56xxp1;
	struct cvmx_lmcx_rodt_comp_ctl_s      cn58xx;
	struct cvmx_lmcx_rodt_comp_ctl_s      cn58xxp1;
};
typedef union cvmx_lmcx_rodt_comp_ctl cvmx_lmcx_rodt_comp_ctl_t;

/**
 * cvmx_lmc#_rodt_ctl
 *
 * LMC_RODT_CTL = Obsolete LMC Read OnDieTermination control
 * See the description in LMC_WODT_CTL1. On Reads, Octeon only supports turning on ODT's in
 * the lower 2 DIMM's with the masks as below.
 *
 * Notes:
 * When a given RANK in position N is selected, the RODT _HI and _LO masks for that position are used.
 * Mask[3:0] is used for RODT control of the RANKs in positions 3, 2, 1, and 0, respectively.
 * In  64b mode, DIMMs are assumed to be ordered in the following order:
 *  position 3: [unused        , DIMM1_RANK1_LO]
 *  position 2: [unused        , DIMM1_RANK0_LO]
 *  position 1: [unused        , DIMM0_RANK1_LO]
 *  position 0: [unused        , DIMM0_RANK0_LO]
 * In 128b mode, DIMMs are assumed to be ordered in the following order:
 *  position 3: [DIMM3_RANK1_HI, DIMM1_RANK1_LO]
 *  position 2: [DIMM3_RANK0_HI, DIMM1_RANK0_LO]
 *  position 1: [DIMM2_RANK1_HI, DIMM0_RANK1_LO]
 *  position 0: [DIMM2_RANK0_HI, DIMM0_RANK0_LO]
 */
union cvmx_lmcx_rodt_ctl {
	uint64_t u64;
	struct cvmx_lmcx_rodt_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t rodt_hi3                     : 4;  /**< Read ODT mask for position 3, data[127:64] */
	uint64_t rodt_hi2                     : 4;  /**< Read ODT mask for position 2, data[127:64] */
	uint64_t rodt_hi1                     : 4;  /**< Read ODT mask for position 1, data[127:64] */
	uint64_t rodt_hi0                     : 4;  /**< Read ODT mask for position 0, data[127:64] */
	uint64_t rodt_lo3                     : 4;  /**< Read ODT mask for position 3, data[ 63: 0] */
	uint64_t rodt_lo2                     : 4;  /**< Read ODT mask for position 2, data[ 63: 0] */
	uint64_t rodt_lo1                     : 4;  /**< Read ODT mask for position 1, data[ 63: 0] */
	uint64_t rodt_lo0                     : 4;  /**< Read ODT mask for position 0, data[ 63: 0] */
#else
	uint64_t rodt_lo0                     : 4;
	uint64_t rodt_lo1                     : 4;
	uint64_t rodt_lo2                     : 4;
	uint64_t rodt_lo3                     : 4;
	uint64_t rodt_hi0                     : 4;
	uint64_t rodt_hi1                     : 4;
	uint64_t rodt_hi2                     : 4;
	uint64_t rodt_hi3                     : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_rodt_ctl_s           cn30xx;
	struct cvmx_lmcx_rodt_ctl_s           cn31xx;
	struct cvmx_lmcx_rodt_ctl_s           cn38xx;
	struct cvmx_lmcx_rodt_ctl_s           cn38xxp2;
	struct cvmx_lmcx_rodt_ctl_s           cn50xx;
	struct cvmx_lmcx_rodt_ctl_s           cn52xx;
	struct cvmx_lmcx_rodt_ctl_s           cn52xxp1;
	struct cvmx_lmcx_rodt_ctl_s           cn56xx;
	struct cvmx_lmcx_rodt_ctl_s           cn56xxp1;
	struct cvmx_lmcx_rodt_ctl_s           cn58xx;
	struct cvmx_lmcx_rodt_ctl_s           cn58xxp1;
};
typedef union cvmx_lmcx_rodt_ctl cvmx_lmcx_rodt_ctl_t;

/**
 * cvmx_lmc#_rodt_mask
 *
 * System designers may desire to terminate DQ/DQS lines for higher frequency DDR operations,
 * especially on a multirank system. DDR3 DQ/DQS I/Os have built-in termination resistors that
 * can be turned on or off by the controller, after meeting TAOND and TAOF timing requirements.
 * Each rank has its own ODT pin that fans out to all the memory parts in that DIMM. System
 * designers may prefer different combinations of ODT ONs for read operations into different
 * ranks. CN78XX supports full programmability by way of the mask register below. Each rank
 * position has its own 4-bit programmable field. When the controller does a read to that rank,
 * it sets the 4 ODT pins to the MASK pins below. For example, when doing a read from Rank0, a
 * system designer may desire to terminate the lines with the resistor on DIMM0/Rank1. The mask
 * RODT_D0_R0 would then be [0010].
 * CN78XX drives the appropriate mask values on the ODT pins by default. If this feature is not
 * required, write 0x0 in this register. Note that, as per the JEDEC DDR3 specifications, the ODT
 * pin for the rank that is being read should always be 0x0.
 * When a given RANK is selected, the RODT mask for that rank is used. The resulting RODT mask is
 * driven to the DIMMs in the following manner:
 */
union cvmx_lmcx_rodt_mask {
	uint64_t u64;
	struct cvmx_lmcx_rodt_mask_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t rodt_d3_r1                   : 8;  /**< Read ODT mask DIMM3, RANK1/DIMM3 in SingleRanked
                                                         *UNUSED IN 6xxx, and MBZ* */
	uint64_t rodt_d3_r0                   : 8;  /**< Read ODT mask DIMM3, RANK0
                                                         *UNUSED IN 6xxx, and MBZ* */
	uint64_t rodt_d2_r1                   : 8;  /**< Read ODT mask DIMM2, RANK1/DIMM2 in SingleRanked
                                                         *UNUSED IN 6xxx, and MBZ* */
	uint64_t rodt_d2_r0                   : 8;  /**< Read ODT mask DIMM2, RANK0
                                                         *UNUSED IN 6xxx, and MBZ* */
	uint64_t rodt_d1_r1                   : 8;  /**< Read ODT mask DIMM1, RANK1/DIMM1 in SingleRanked
                                                         if (RANK_ENA) then
                                                             RODT_D1_R1[3] must be 0
                                                         else
                                                             RODT_D1_R1[3:0] is not used and MBZ
                                                         *Upper 4 bits UNUSED IN 6xxx, and MBZ* */
	uint64_t rodt_d1_r0                   : 8;  /**< Read ODT mask DIMM1, RANK0
                                                         if (RANK_ENA) then
                                                             RODT_D1_RO[2] must be 0
                                                         else
                                                             RODT_D1_RO[3:2,1] must be 0
                                                         *Upper 4 bits UNUSED IN 6xxx, and MBZ* */
	uint64_t rodt_d0_r1                   : 8;  /**< Read ODT mask DIMM0, RANK1/DIMM0 in SingleRanked
                                                         if (RANK_ENA) then
                                                             RODT_D0_R1[1] must be 0
                                                         else
                                                             RODT_D0_R1[3:0] is not used and MBZ
                                                         *Upper 4 bits UNUSED IN 6xxx, and MBZ* */
	uint64_t rodt_d0_r0                   : 8;  /**< Read ODT mask DIMM0, RANK0
                                                         if (RANK_ENA) then
                                                             RODT_D0_RO[0] must be 0
                                                         else
                                                             RODT_D0_RO[1:0,3] must be 0
                                                         *Upper 4 bits UNUSED IN 6xxx, and MBZ* */
#else
	uint64_t rodt_d0_r0                   : 8;
	uint64_t rodt_d0_r1                   : 8;
	uint64_t rodt_d1_r0                   : 8;
	uint64_t rodt_d1_r1                   : 8;
	uint64_t rodt_d2_r0                   : 8;
	uint64_t rodt_d2_r1                   : 8;
	uint64_t rodt_d3_r0                   : 8;
	uint64_t rodt_d3_r1                   : 8;
#endif
	} s;
	struct cvmx_lmcx_rodt_mask_s          cn61xx;
	struct cvmx_lmcx_rodt_mask_s          cn63xx;
	struct cvmx_lmcx_rodt_mask_s          cn63xxp1;
	struct cvmx_lmcx_rodt_mask_s          cn66xx;
	struct cvmx_lmcx_rodt_mask_s          cn68xx;
	struct cvmx_lmcx_rodt_mask_s          cn68xxp1;
	struct cvmx_lmcx_rodt_mask_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_28_63               : 36;
	uint64_t rodt_d1_r1                   : 4;  /**< Reserved. */
	uint64_t reserved_20_23               : 4;
	uint64_t rodt_d1_r0                   : 4;  /**< Reserved. */
	uint64_t reserved_12_15               : 4;
	uint64_t rodt_d0_r1                   : 4;  /**< Read ODT mask DIMM0, RANK1/DIMM0 in SingleRanked. If RANK_ENA=1, RODT_D0_R1<1> must be
                                                         zero. Otherwise, RODT_D0_R1<3:0> is not used and must be zero. */
	uint64_t reserved_4_7                 : 4;
	uint64_t rodt_d0_r0                   : 4;  /**< Read ODT mask DIMM0, RANK0. If RANK_ENA=1, RODT_D0_RO<0> must be zero. Otherwise,
                                                         RODT_D0_RO<1:0,3> must be zero. */
#else
	uint64_t rodt_d0_r0                   : 4;
	uint64_t reserved_4_7                 : 4;
	uint64_t rodt_d0_r1                   : 4;
	uint64_t reserved_12_15               : 4;
	uint64_t rodt_d1_r0                   : 4;
	uint64_t reserved_20_23               : 4;
	uint64_t rodt_d1_r1                   : 4;
	uint64_t reserved_28_63               : 36;
#endif
	} cn70xx;
	struct cvmx_lmcx_rodt_mask_cn70xx     cn78xx;
	struct cvmx_lmcx_rodt_mask_s          cnf71xx;
};
typedef union cvmx_lmcx_rodt_mask cvmx_lmcx_rodt_mask_t;

/**
 * cvmx_lmc#_scramble_cfg0
 *
 * LMC_SCRAMBLE_CFG0 = LMC Scramble Config0
 *
 */
union cvmx_lmcx_scramble_cfg0 {
	uint64_t u64;
	struct cvmx_lmcx_scramble_cfg0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t key                          : 64; /**< Scramble Key for Data */
#else
	uint64_t key                          : 64;
#endif
	} s;
	struct cvmx_lmcx_scramble_cfg0_s      cn61xx;
	struct cvmx_lmcx_scramble_cfg0_s      cn66xx;
	struct cvmx_lmcx_scramble_cfg0_s      cn70xx;
	struct cvmx_lmcx_scramble_cfg0_s      cn78xx;
	struct cvmx_lmcx_scramble_cfg0_s      cnf71xx;
};
typedef union cvmx_lmcx_scramble_cfg0 cvmx_lmcx_scramble_cfg0_t;

/**
 * cvmx_lmc#_scramble_cfg1
 *
 * These registers set the aliasing that uses the lowest, legal chip select(s).
 *
 */
union cvmx_lmcx_scramble_cfg1 {
	uint64_t u64;
	struct cvmx_lmcx_scramble_cfg1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t key                          : 64; /**< Scramble Key for Addresses */
#else
	uint64_t key                          : 64;
#endif
	} s;
	struct cvmx_lmcx_scramble_cfg1_s      cn61xx;
	struct cvmx_lmcx_scramble_cfg1_s      cn66xx;
	struct cvmx_lmcx_scramble_cfg1_s      cn70xx;
	struct cvmx_lmcx_scramble_cfg1_s      cn78xx;
	struct cvmx_lmcx_scramble_cfg1_s      cnf71xx;
};
typedef union cvmx_lmcx_scramble_cfg1 cvmx_lmcx_scramble_cfg1_t;

/**
 * cvmx_lmc#_scrambled_fadr
 *
 * LMC(0..3)_FADR captures the failing pre-scrambled address location (split into DIMM, bunk,
 * bank, etc). If scrambling is off, LMC(0..3)_FADR also captures the failing physical location
 * in the DRAM parts. LMC(0..3)_SCRAMBLED_FADR captures the actual failing address location in
 * the physical DRAM parts, i.e.:
 * If scrambling is on, LMC(0..3)_SCRAMBLED_FADR contains the failing physical location in the
 * DRAM parts (split into DIMM, bunk, bank, etc);
 * If scrambling is off, the pre-scramble and post-scramble addresses are the same, and so the
 * contents of LMC(0..3)_SCRAMBLED_FADR match the contents of LMC(0..3)_FADR.
 * This register only captures the first transaction with ECC errors. A DED error can over-write
 * this register with its failing addresses if the first error was a SEC. If you write
 * LMC(0..3)_CONFIG -> SEC_ERR/DED_ERR, it clears the error bits and captures the next failing
 * address. If FDIMM is 1, that means the error is in the higher DIMM.
 */
union cvmx_lmcx_scrambled_fadr {
	uint64_t u64;
	struct cvmx_lmcx_scrambled_fadr_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_40_63               : 24;
	uint64_t fill_order                   : 2;  /**< Fill order for failing transaction. */
	uint64_t reserved_14_37               : 24;
	uint64_t fcol                         : 14; /**< Failing Column Address[13:0]
                                                         Technically, represents the address of the 128b data
                                                         that had an ecc error, i.e., fcol[0] is always 0. Can
                                                         be used in conjuction with LMC*_CONFIG[DED_ERR] to
                                                         isolate the 64b chunk of data in error */
#else
	uint64_t fcol                         : 14;
	uint64_t reserved_14_37               : 24;
	uint64_t fill_order                   : 2;
	uint64_t reserved_40_63               : 24;
#endif
	} s;
	struct cvmx_lmcx_scrambled_fadr_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_36_63               : 28;
	uint64_t fdimm                        : 2;  /**< Failing DIMM# */
	uint64_t fbunk                        : 1;  /**< Failing Rank */
	uint64_t fbank                        : 3;  /**< Failing Bank[2:0] */
	uint64_t frow                         : 16; /**< Failing Row Address[15:0] */
	uint64_t fcol                         : 14; /**< Failing Column Address[13:0]
                                                         Technically, represents the address of the 128b data
                                                         that had an ecc error, i.e., fcol[0] is always 0. Can
                                                         be used in conjuction with LMC*_CONFIG[DED_ERR] to
                                                         isolate the 64b chunk of data in error */
#else
	uint64_t fcol                         : 14;
	uint64_t frow                         : 16;
	uint64_t fbank                        : 3;
	uint64_t fbunk                        : 1;
	uint64_t fdimm                        : 2;
	uint64_t reserved_36_63               : 28;
#endif
	} cn61xx;
	struct cvmx_lmcx_scrambled_fadr_cn61xx cn66xx;
	struct cvmx_lmcx_scrambled_fadr_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_40_63               : 24;
	uint64_t fill_order                   : 2;  /**< Fill order for failing transaction. */
	uint64_t fdimm                        : 1;  /**< Failing DIMM number. */
	uint64_t fbunk                        : 1;  /**< Failing rank number. */
	uint64_t fbank                        : 4;  /**< Failing bank number. Bits <3:0>. */
	uint64_t frow                         : 18; /**< Failing row address. Bits <17:0>. */
	uint64_t fcol                         : 14; /**< Failing column address <13:0>. Technically, represents the address of the 128b data that
                                                         had an ECC error, i.e., FCOL<0> is always 0. Can be used in conjunction with
                                                         LMC(0..0)_CONFIG[DED_ERR] to isolate the 64b chunk of data in error. */
#else
	uint64_t fcol                         : 14;
	uint64_t frow                         : 18;
	uint64_t fbank                        : 4;
	uint64_t fbunk                        : 1;
	uint64_t fdimm                        : 1;
	uint64_t fill_order                   : 2;
	uint64_t reserved_40_63               : 24;
#endif
	} cn70xx;
	struct cvmx_lmcx_scrambled_fadr_cn70xx cn78xx;
	struct cvmx_lmcx_scrambled_fadr_cn61xx cnf71xx;
};
typedef union cvmx_lmcx_scrambled_fadr cvmx_lmcx_scrambled_fadr_t;

/**
 * cvmx_lmc#_seq_ctl
 *
 * This register is used to initiate the various control sequences in the LMC.
 *
 */
union cvmx_lmcx_seq_ctl {
	uint64_t u64;
	struct cvmx_lmcx_seq_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_6_63                : 58;
	uint64_t seq_complete                 : 1;  /**< Sequence complete. This bit is cleared when INIT_START is set to a 1 and then is set to 1
                                                         when the sequence is completed. */
	uint64_t seq_sel                      : 4;  /**< Selects the sequence that LMC runs after a 0->1 transition on INIT_START.
                                                         0x0 = Power-up/initialization:
                                                         LMC(0..3)_CONFIG[RANKMASK] selects participating ranks (should be all ranks with attached
                                                         DRAM). DDR*_DIMM*_CKE* signals are activated (if not already active). RDIMM register
                                                         control words 0-15 are written to LMC(0..3)_CONFIG[RANKMASK]-selected RDIMMs when
                                                         LMC(0..3)_CONTROL[RDIMM_ENA] = 1 and corresponding LMC(0..3)_DIMM_CTL[DIMM*_WMASK] bits
                                                         are set. (Refer to LMC(0..3)_DIMM(0..1)_PARAMS and LMC(0..3)_DIMM_CTL descriptions for
                                                         more
                                                         details.)
                                                         The DRAM registers MR0, MR1, MR2, and MR3 are written in the selected ranks.
                                                         0x1 = Read-leveling:
                                                         LMC(0..3)_CONFIG[RANKMASK] selects the rank to be read-leveled. MR3 written in the
                                                         selected rank.
                                                         0x2 = Self-refresh entry:
                                                         LMC(0..3)_CONFIG[INIT_STATUS] selects the participating ranks (should be all ranks with
                                                         attached DRAM). MR1 and MR2 are written in the selected ranks if
                                                         LMC(0..3)_CONFIG[SREF_WITH_DLL] = 1. DDR*_DIMM*_CKE* signals de-activated.
                                                         0x3 = Self-refresh exit:
                                                         LMC(0..3)_CONFIG[RANKMASK] must be set to indicate participating ranks (should be all
                                                         ranks with attached DRAM). DDR*_DIMM*_CKE* signals activated. MR0, MR1, MR2, and MR3 are
                                                         written in the participating ranks if LMC(0..3)_CONFIG[SREF_WITH_DLL] = 1.
                                                         LMC(0..3)_CONFIG[INIT_STATUS] is updated for ranks that are selected.
                                                         0x6 = Write-leveling:
                                                         LMC(0..3)_CONFIG[RANKMASK] selects the rank to be write-leveled.
                                                         LMC(0..3)_CONFIG[INIT_STATUS] must indicate all ranks with attached DRAM. MR1 and MR2
                                                         written in the LMC(0..3)_CONFIG[INIT_STATUS]-selected ranks.
                                                         0x7 = Initialize RCW:
                                                         LMC(0..3)_CONFIG[RANKMASK] selects participating ranks (should be all ranks with attached
                                                         DRAM). In DDR3 mode, RDIMM register control words 0-15 are written to
                                                         LMC(0..3)_CONFIG[RANKMASK]-selected RDIMMs when LMC(0..3)_CONTROL[RDIMM_ENA] = 1 and
                                                         corresponding LMC(0..3)_DIMM_CTL[DIMM*_WMASK] bits are set. (Refer to
                                                         LMC(0..3)_DIMM(0..1)_PARAMS and LMC(0..3)_DIMM_CTL descriptions for more details.) */
	uint64_t init_start                   : 1;  /**< A 0->1 transition starts the DDR memory sequence that is selected by SEQ_SEL. This
                                                         register is a one-shot and clears itself each time it is set. */
#else
	uint64_t init_start                   : 1;
	uint64_t seq_sel                      : 4;
	uint64_t seq_complete                 : 1;
	uint64_t reserved_6_63                : 58;
#endif
	} s;
	struct cvmx_lmcx_seq_ctl_s            cn70xx;
	struct cvmx_lmcx_seq_ctl_s            cn78xx;
};
typedef union cvmx_lmcx_seq_ctl cvmx_lmcx_seq_ctl_t;

/**
 * cvmx_lmc#_slot_ctl0
 *
 * This register is an assortment of control fields needed by the memory controller. If software
 * has not previously written to this register (since the last DRESET), hardware updates the
 * fields in this register to the minimum allowed value when any of LMC(0..3)_RLEVEL_RANK(0..3),
 * LMC(0..3)_WLEVEL_RANK(0..3), LMC(0..3)_CONTROL, and LMC(0..3)_MODEREG_PARAMS0 registers
 * change. Ideally, only read this register after LMC has been initialized and
 * LMC(0..3)_RLEVEL_RANK(0..3), LMC(0..3)_WLEVEL_RANK(0..3) have valid data.
 * The interpretation of the fields in this register depends on LMC(0)_CONFIG[DDR2T]:
 * If LMC(0..3)_CONFIG[DDR2T]=1, (FieldValue + 4) is the minimum CK cycles between when the DRAM
 * part registers CAS commands of the 1
 * st and 2
 * nd types from different cache blocks.
 * If LMC(0..3)_CONFIG[DDR2T]=0, (FieldValue + 3) is the minimum CK cycles between when the DRAM
 * part registers CAS commands of the 1
 * st and 2
 * nd types from different cache blocks. FieldValue = 0 is always illegal in this case.
 * The hardware-calculated minimums for these fields are shown in LMC(0)_SLOT_CTL0 Hardware-
 * Calculated Minimums.
 */
union cvmx_lmcx_slot_ctl0 {
	uint64_t u64;
	struct cvmx_lmcx_slot_ctl0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_48_63               : 16;
	uint64_t w2w_l_init                   : 6;  /**< Write-to-write spacing control for back-to-back write followed by write cache block
                                                         accesses to the same rank and DIMM, and same BG for DDR4. */
	uint64_t w2r_l_init                   : 6;  /**< Write-to-read spacing control for back-to-back write followed by read cache block accesses
                                                         to the same rank and DIMM, and same BG for DDR4. */
	uint64_t r2w_l_init                   : 6;  /**< Read-to-write spacing control for back-to-back read followed by write cache block accesses
                                                         to the same rank and DIMM, and same BG for DDR4. */
	uint64_t r2r_l_init                   : 6;  /**< Read-to-read spacing control for back-to-back read followed by read cache block accesses
                                                         to the same rank and DIMM, and same BG for DDR4. */
	uint64_t w2w_init                     : 6;  /**< Write-to-write spacing control
                                                         for back to back write followed by write cache block
                                                         accesses to the same rank and DIMM */
	uint64_t w2r_init                     : 6;  /**< Write-to-read spacing control
                                                         for back to back write followed by read cache block
                                                         accesses to the same rank and DIMM */
	uint64_t r2w_init                     : 6;  /**< Read-to-write spacing control
                                                         for back to back read followed by write cache block
                                                         accesses to the same rank and DIMM */
	uint64_t r2r_init                     : 6;  /**< Read-to-read spacing control
                                                         for back to back read followed by read cache block
                                                         accesses to the same rank and DIMM */
#else
	uint64_t r2r_init                     : 6;
	uint64_t r2w_init                     : 6;
	uint64_t w2r_init                     : 6;
	uint64_t w2w_init                     : 6;
	uint64_t r2r_l_init                   : 6;
	uint64_t r2w_l_init                   : 6;
	uint64_t w2r_l_init                   : 6;
	uint64_t w2w_l_init                   : 6;
	uint64_t reserved_48_63               : 16;
#endif
	} s;
	struct cvmx_lmcx_slot_ctl0_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_24_63               : 40;
	uint64_t w2w_init                     : 6;  /**< Write-to-write spacing control
                                                         for back to back write followed by write cache block
                                                         accesses to the same rank and DIMM */
	uint64_t w2r_init                     : 6;  /**< Write-to-read spacing control
                                                         for back to back write followed by read cache block
                                                         accesses to the same rank and DIMM */
	uint64_t r2w_init                     : 6;  /**< Read-to-write spacing control
                                                         for back to back read followed by write cache block
                                                         accesses to the same rank and DIMM */
	uint64_t r2r_init                     : 6;  /**< Read-to-read spacing control
                                                         for back to back read followed by read cache block
                                                         accesses to the same rank and DIMM */
#else
	uint64_t r2r_init                     : 6;
	uint64_t r2w_init                     : 6;
	uint64_t w2r_init                     : 6;
	uint64_t w2w_init                     : 6;
	uint64_t reserved_24_63               : 40;
#endif
	} cn61xx;
	struct cvmx_lmcx_slot_ctl0_cn61xx     cn63xx;
	struct cvmx_lmcx_slot_ctl0_cn61xx     cn63xxp1;
	struct cvmx_lmcx_slot_ctl0_cn61xx     cn66xx;
	struct cvmx_lmcx_slot_ctl0_cn61xx     cn68xx;
	struct cvmx_lmcx_slot_ctl0_cn61xx     cn68xxp1;
	struct cvmx_lmcx_slot_ctl0_s          cn70xx;
	struct cvmx_lmcx_slot_ctl0_s          cn78xx;
	struct cvmx_lmcx_slot_ctl0_cn61xx     cnf71xx;
};
typedef union cvmx_lmcx_slot_ctl0 cvmx_lmcx_slot_ctl0_t;

/**
 * cvmx_lmc#_slot_ctl1
 *
 * This register is an assortment of control fields needed by the memory controller. If software
 * has not previously written to this register (since the last DRESET), hardware updates the
 * fields in this register to the minimum allowed value when any of LMC(0..3)_RLEVEL_RANK(0..3),
 * LMC(0..3)_WLEVEL_RANK(0..3), LMC(0..3)_CONTROL and LMC(0..3)_MODEREG_PARAMS0 CSRs change.
 * Ideally, only read this register after LMC has been initialized and
 * LMC(0..3)_RLEVEL_RANK(0..3), LMC(0..3)_WLEVEL_RANK(0..3) have valid data.
 * The interpretation of the fields in this CSR depends on LMC(0)_CONFIG[DDR2T]:
 * If LMC(0..3)_CONFIG[DDR2T]=1, (FieldValue + 4) is the minimum CK cycles between when the DRAM
 * part registers CAS commands of the 1
 * st and 2
 * nd types from different cache blocks.
 * If LMC(0..3)_CONFIG[DDR2T]=0, (FieldValue + 3) is the minimum CK cycles between when the DRAM
 * part registers CAS commands of the 1
 * st and 2
 * nd types from different cache blocks. FieldValue = 0 is always illegal in this case.
 * The hardware-calculated minimums for these fields are shown in LMC(0)_SLOT_CTL1 Hardware-
 * Calculated Minimums.
 */
union cvmx_lmcx_slot_ctl1 {
	uint64_t u64;
	struct cvmx_lmcx_slot_ctl1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_24_63               : 40;
	uint64_t w2w_xrank_init               : 6;  /**< Write-to-write spacing control
                                                         for back to back write followed by write cache block
                                                         accesses across ranks of the same DIMM */
	uint64_t w2r_xrank_init               : 6;  /**< Write-to-read spacing control
                                                         for back to back write followed by read cache block
                                                         accesses across ranks of the same DIMM */
	uint64_t r2w_xrank_init               : 6;  /**< Read-to-write spacing control
                                                         for back to back read followed by write cache block
                                                         accesses across ranks of the same DIMM */
	uint64_t r2r_xrank_init               : 6;  /**< Read-to-read spacing control
                                                         for back to back read followed by read cache block
                                                         accesses across ranks of the same DIMM */
#else
	uint64_t r2r_xrank_init               : 6;
	uint64_t r2w_xrank_init               : 6;
	uint64_t w2r_xrank_init               : 6;
	uint64_t w2w_xrank_init               : 6;
	uint64_t reserved_24_63               : 40;
#endif
	} s;
	struct cvmx_lmcx_slot_ctl1_s          cn61xx;
	struct cvmx_lmcx_slot_ctl1_s          cn63xx;
	struct cvmx_lmcx_slot_ctl1_s          cn63xxp1;
	struct cvmx_lmcx_slot_ctl1_s          cn66xx;
	struct cvmx_lmcx_slot_ctl1_s          cn68xx;
	struct cvmx_lmcx_slot_ctl1_s          cn68xxp1;
	struct cvmx_lmcx_slot_ctl1_s          cn70xx;
	struct cvmx_lmcx_slot_ctl1_s          cn78xx;
	struct cvmx_lmcx_slot_ctl1_s          cnf71xx;
};
typedef union cvmx_lmcx_slot_ctl1 cvmx_lmcx_slot_ctl1_t;

/**
 * cvmx_lmc#_slot_ctl2
 *
 * This register is an assortment of control fields needed by the memory controller. If software
 * has not previously written to this register (since the last DRESET), hardware updates the
 * fields in this register to the minimum allowed value when any of LMC(0..3)_RLEVEL_RANK(0..3),
 * LMC(0..3)_WLEVEL_RANK(0..3), LMC(0..3)_CONTROL and LMC(0..3)_MODEREG_PARAMS0 CSRs change.
 * Ideally, only read this register after LMC has been initialized and
 * LMC(0..3)_RLEVEL_RANK(0..3), LMC(0..3)_WLEVEL_RANK(0..3) have valid data.
 * The interpretation of the fields in this CSR depends on LMC(0)_CONFIG[DDR2T]:
 * If LMC(0..3)_CONFIG[DDR2T] = 1, (FieldValue + 4) is the minimum CK cycles between when the
 * DRAM part registers CAS commands of the 1
 * st and 2
 * nd types from different cache blocks.
 * If LMC(0..3)_CONFIG[DDR2T] = 0, (FieldValue + 3) is the minimum CK cycles between when the
 * DRAM part registers CAS commands of the 1
 * st and 2
 * nd types from different cache blocks. FieldValue = 0 is always illegal in this case.
 * The hardware-calculated minimums for these fields are shown in LMC Registers.
 */
union cvmx_lmcx_slot_ctl2 {
	uint64_t u64;
	struct cvmx_lmcx_slot_ctl2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_24_63               : 40;
	uint64_t w2w_xdimm_init               : 6;  /**< Write-to-write spacing control
                                                         for back to back write followed by write cache block
                                                         accesses across DIMMs */
	uint64_t w2r_xdimm_init               : 6;  /**< Write-to-read spacing control
                                                         for back to back write followed by read cache block
                                                         accesses across DIMMs */
	uint64_t r2w_xdimm_init               : 6;  /**< Read-to-write spacing control
                                                         for back to back read followed by write cache block
                                                         accesses across DIMMs */
	uint64_t r2r_xdimm_init               : 6;  /**< Read-to-read spacing control
                                                         for back to back read followed by read cache block
                                                         accesses across DIMMs */
#else
	uint64_t r2r_xdimm_init               : 6;
	uint64_t r2w_xdimm_init               : 6;
	uint64_t w2r_xdimm_init               : 6;
	uint64_t w2w_xdimm_init               : 6;
	uint64_t reserved_24_63               : 40;
#endif
	} s;
	struct cvmx_lmcx_slot_ctl2_s          cn61xx;
	struct cvmx_lmcx_slot_ctl2_s          cn63xx;
	struct cvmx_lmcx_slot_ctl2_s          cn63xxp1;
	struct cvmx_lmcx_slot_ctl2_s          cn66xx;
	struct cvmx_lmcx_slot_ctl2_s          cn68xx;
	struct cvmx_lmcx_slot_ctl2_s          cn68xxp1;
	struct cvmx_lmcx_slot_ctl2_s          cn70xx;
	struct cvmx_lmcx_slot_ctl2_s          cn78xx;
	struct cvmx_lmcx_slot_ctl2_s          cnf71xx;
};
typedef union cvmx_lmcx_slot_ctl2 cvmx_lmcx_slot_ctl2_t;

/**
 * cvmx_lmc#_timing_params0
 */
union cvmx_lmcx_timing_params0 {
	uint64_t u64;
	struct cvmx_lmcx_timing_params0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_26_63               : 38;
	uint64_t tmrd                         : 4;  /**< Indicates tMRD constraints.
                                                         Set TMRD (CSR field) = RNDUP[tMRD(ns)/tCYC(ns)]-1,
                                                         where tMRD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=4nCK */
	uint64_t reserved_8_21                : 14;
	uint64_t tckeon                       : 8;  /**< Reserved. Should be written to zero. */
#else
	uint64_t tckeon                       : 8;
	uint64_t reserved_8_21                : 14;
	uint64_t tmrd                         : 4;
	uint64_t reserved_26_63               : 38;
#endif
	} s;
	struct cvmx_lmcx_timing_params0_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_47_63               : 17;
	uint64_t trp_ext                      : 1;  /**< Indicates tRP constraints.
                                                         Set [TRP_EXT[0:0], TRP[3:0]] (CSR field) = RNDUP[tRP(ns)/tCYC(ns)]
                                                         + (RNDUP[tRTP(ns)/tCYC(ns)]-4)-1,
                                                         where tRP, tRTP are from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP tRP=10-15ns
                                                         TYP tRTP=max(4nCK, 7.5ns) */
	uint64_t tcksre                       : 4;  /**< Indicates tCKSRE constraints.
                                                         Set TCKSRE (CSR field) = RNDUP[tCKSRE(ns)/tCYC(ns)]-1,
                                                         where tCKSRE is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(5nCK, 10ns) */
	uint64_t trp                          : 4;  /**< Indicates tRP constraints.
                                                         Set [TRP_EXT[0:0], TRP[3:0]] (CSR field) = RNDUP[tRP(ns)/tCYC(ns)]
                                                         + (RNDUP[tRTP(ns)/tCYC(ns)])-4)-1,
                                                         where tRP, tRTP are from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP tRP=10-15ns
                                                         TYP tRTP=max(4nCK, 7.5ns) */
	uint64_t tzqinit                      : 4;  /**< Indicates tZQINIT constraints.
                                                         Set TZQINIT (CSR field) = RNDUP[tZQINIT(ns)/(256*tCYC(ns))],
                                                         where tZQINIT is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=2 (equivalent to 512) */
	uint64_t tdllk                        : 4;  /**< Indicates tDLLK constraints.
                                                         Set TDLLK (CSR field) = RNDUP[tDLLK(ns)/(256*tCYC(ns))],
                                                         where tDLLK is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=2 (equivalent to 512)
                                                         This parameter is used in self-refresh exit
                                                         and assumed to be greater than tRFC */
	uint64_t tmod                         : 4;  /**< Indicates tMOD constraints.
                                                         Set TMOD (CSR field) = RNDUP[tMOD(ns)/tCYC(ns)]-1,
                                                         where tMOD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(12nCK, 15ns) */
	uint64_t tmrd                         : 4;  /**< Indicates tMRD constraints.
                                                         Set TMRD (CSR field) = RNDUP[tMRD(ns)/tCYC(ns)]-1,
                                                         where tMRD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=4nCK */
	uint64_t txpr                         : 4;  /**< Indicates tXPR constraints.
                                                         Set TXPR (CSR field) = RNDUP[tXPR(ns)/(16*tCYC(ns))],
                                                         where tXPR is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(5nCK, tRFC+10ns) */
	uint64_t tcke                         : 4;  /**< Indicates tCKE constraints.
                                                         Set TCKE (CSR field) = RNDUP[tCKE(ns)/tCYC(ns)]-1,
                                                         where tCKE is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(3nCK, 7.5/5.625/5.625/5ns) */
	uint64_t tzqcs                        : 4;  /**< Indicates tZQCS constraints.
                                                         Set TZQCS (CSR field) = RNDUP[tZQCS(ns)/(16*tCYC(ns))],
                                                         where tZQCS is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=4 (equivalent to 64) */
	uint64_t reserved_0_9                 : 10;
#else
	uint64_t reserved_0_9                 : 10;
	uint64_t tzqcs                        : 4;
	uint64_t tcke                         : 4;
	uint64_t txpr                         : 4;
	uint64_t tmrd                         : 4;
	uint64_t tmod                         : 4;
	uint64_t tdllk                        : 4;
	uint64_t tzqinit                      : 4;
	uint64_t trp                          : 4;
	uint64_t tcksre                       : 4;
	uint64_t trp_ext                      : 1;
	uint64_t reserved_47_63               : 17;
#endif
	} cn61xx;
	struct cvmx_lmcx_timing_params0_cn61xx cn63xx;
	struct cvmx_lmcx_timing_params0_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_46_63               : 18;
	uint64_t tcksre                       : 4;  /**< Indicates tCKSRE constraints.
                                                         Set TCKSRE (CSR field) = RNDUP[tCKSRE(ns)/tCYC(ns)]-1,
                                                         where tCKSRE is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(5nCK, 10ns) */
	uint64_t trp                          : 4;  /**< Indicates tRP constraints.
                                                         Set TRP (CSR field) = RNDUP[tRP(ns)/tCYC(ns)]
                                                         + (RNDUP[tRTP(ns)/tCYC(ns)])-4)-1,
                                                         where tRP, tRTP are from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP tRP=10-15ns
                                                         TYP tRTP=max(4nCK, 7.5ns) */
	uint64_t tzqinit                      : 4;  /**< Indicates tZQINIT constraints.
                                                         Set TZQINIT (CSR field) = RNDUP[tZQINIT(ns)/(256*tCYC(ns))],
                                                         where tZQINIT is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=2 (equivalent to 512) */
	uint64_t tdllk                        : 4;  /**< Indicates tDLLK constraints.
                                                         Set TDLLK (CSR field) = RNDUP[tDLLK(ns)/(256*tCYC(ns))],
                                                         where tDLLK is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=2 (equivalent to 512)
                                                         This parameter is used in self-refresh exit
                                                         and assumed to be greater than tRFC */
	uint64_t tmod                         : 4;  /**< Indicates tMOD constraints.
                                                         Set TMOD (CSR field) = RNDUP[tMOD(ns)/tCYC(ns)]-1,
                                                         where tMOD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(12nCK, 15ns) */
	uint64_t tmrd                         : 4;  /**< Indicates tMRD constraints.
                                                         Set TMRD (CSR field) = RNDUP[tMRD(ns)/tCYC(ns)]-1,
                                                         where tMRD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=4nCK */
	uint64_t txpr                         : 4;  /**< Indicates tXPR constraints.
                                                         Set TXPR (CSR field) = RNDUP[tXPR(ns)/(16*tCYC(ns))],
                                                         where tXPR is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(5nCK, tRFC+10ns) */
	uint64_t tcke                         : 4;  /**< Indicates tCKE constraints.
                                                         Set TCKE (CSR field) = RNDUP[tCKE(ns)/tCYC(ns)]-1,
                                                         where tCKE is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(3nCK, 7.5/5.625/5.625/5ns) */
	uint64_t tzqcs                        : 4;  /**< Indicates tZQCS constraints.
                                                         Set TZQCS (CSR field) = RNDUP[tZQCS(ns)/(16*tCYC(ns))],
                                                         where tZQCS is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=4 (equivalent to 64) */
	uint64_t tckeon                       : 10; /**< Reserved. Should be written to zero. */
#else
	uint64_t tckeon                       : 10;
	uint64_t tzqcs                        : 4;
	uint64_t tcke                         : 4;
	uint64_t txpr                         : 4;
	uint64_t tmrd                         : 4;
	uint64_t tmod                         : 4;
	uint64_t tdllk                        : 4;
	uint64_t tzqinit                      : 4;
	uint64_t trp                          : 4;
	uint64_t tcksre                       : 4;
	uint64_t reserved_46_63               : 18;
#endif
	} cn63xxp1;
	struct cvmx_lmcx_timing_params0_cn61xx cn66xx;
	struct cvmx_lmcx_timing_params0_cn61xx cn68xx;
	struct cvmx_lmcx_timing_params0_cn61xx cn68xxp1;
	struct cvmx_lmcx_timing_params0_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_48_63               : 16;
	uint64_t tcksre                       : 4;  /**< Indicates TCKSRE constraints. Set this field as follows:
                                                         RNDUP[TCKSRE(ns) / TCYC(ns)] - 1
                                                         where TCKSRE is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not
                                                         data rate).
                                                         TYP = max(5nCK, 10 ns). */
	uint64_t trp                          : 5;  /**< Indicates TRP constraints. Set TRP as follows:
                                                         RNDUP[TRP(ns) / TCYC(ns)] - 1
                                                         where TRP and TRTP are from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency
                                                         (not data rate).
                                                         TYP TRP = 10-15ns.
                                                         TYP TRTP = max(4nCK, 7.5 ns). */
	uint64_t tzqinit                      : 4;  /**< Indicates TZQINIT constraints. Set this field as follows:
                                                         RNDUP[TZQINIT(ns) / (256 * TCYC(ns))]
                                                         where TZQINIT is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not
                                                         data rate).
                                                         TYP = 2 (equivalent to 512). */
	uint64_t tdllk                        : 4;  /**< Indicates TDLLK constraints. Set this field as follows:
                                                         RNDUP[TDLLK(ns) / (256 * TCYC(ns))]
                                                         where TDLLK is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = 2 (equivalent to 512).
                                                         This parameter is used in self-refresh exit and assumed to be greater than TRFC. */
	uint64_t tmod                         : 5;  /**< Indicates tMOD constraints. Set this field as follows:
                                                         RNDUP[TMOD(ns) / TCYC(ns)] - 1
                                                         where TMOD is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = max(12nCK, 15 ns). */
	uint64_t tmrd                         : 4;  /**< Indicates TMRD constraints. Set this field as follows:
                                                         RNDUP[TMRD(ns) / TCYC(ns)] - 1
                                                         where TMRD is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = 4nCK. */
	uint64_t txpr                         : 6;  /**< Indicates TXPR constraints. Set this field as follows:
                                                         RNDUP[TXPR(ns) / (16 * TCYC(ns))]
                                                         where TXPR is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = max(5nCK, TRFC+10 ns). */
	uint64_t tcke                         : 4;  /**< Indicates TCKE constraints. Set this field as follows:
                                                         RNDUP[TCKE(ns) / TCYC(ns)] - 1
                                                         where TCKE is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = max(3nCK, 7.5/5.625/5.625/5 ns). */
	uint64_t tzqcs                        : 4;  /**< Indicates TZQCS constraints. Set this field as follows:
                                                         RNDUP[TZQCS(ns) / (16 * TCYC(ns))]
                                                         where TZQCS is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = 4 (equivalent to 64). */
	uint64_t reserved_0_7                 : 8;
#else
	uint64_t reserved_0_7                 : 8;
	uint64_t tzqcs                        : 4;
	uint64_t tcke                         : 4;
	uint64_t txpr                         : 6;
	uint64_t tmrd                         : 4;
	uint64_t tmod                         : 5;
	uint64_t tdllk                        : 4;
	uint64_t tzqinit                      : 4;
	uint64_t trp                          : 5;
	uint64_t tcksre                       : 4;
	uint64_t reserved_48_63               : 16;
#endif
	} cn70xx;
	struct cvmx_lmcx_timing_params0_cn70xx cn78xx;
	struct cvmx_lmcx_timing_params0_cn61xx cnf71xx;
};
typedef union cvmx_lmcx_timing_params0 cvmx_lmcx_timing_params0_t;

/**
 * cvmx_lmc#_timing_params1
 */
union cvmx_lmcx_timing_params1 {
	uint64_t u64;
	struct cvmx_lmcx_timing_params1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_4_63                : 60;
	uint64_t tmprr                        : 4;  /**< Indicates tMPRR constraints.
                                                         Set TMPRR (CSR field) = RNDUP[tMPRR(ns)/tCYC(ns)]-1,
                                                         where tMPRR is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=1nCK */
#else
	uint64_t tmprr                        : 4;
	uint64_t reserved_4_63                : 60;
#endif
	} s;
	struct cvmx_lmcx_timing_params1_cn61xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_47_63               : 17;
	uint64_t tras_ext                     : 1;  /**< Indicates tRAS constraints.
                                                         Set [TRAS_EXT[0:0], TRAS[4:0]] (CSR field) = RNDUP[tRAS(ns)/tCYC(ns)]-1,
                                                         where tRAS is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=35ns-9*tREFI
                                                             - 000000: RESERVED
                                                             - 000001: 2 tCYC
                                                             - 000010: 3 tCYC
                                                             - ...
                                                             - 111111: 64 tCYC */
	uint64_t txpdll                       : 5;  /**< Indicates tXPDLL constraints.
                                                         Set TXPDLL (CSR field) = RNDUP[tXPDLL(ns)/tCYC(ns)]-1,
                                                         where tXPDLL is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(10nCK, 24ns) */
	uint64_t tfaw                         : 5;  /**< Indicates tFAW constraints.
                                                         Set TFAW (CSR field) = RNDUP[tFAW(ns)/(4*tCYC(ns))],
                                                         where tFAW is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=30-40ns */
	uint64_t twldqsen                     : 4;  /**< Indicates tWLDQSEN constraints.
                                                         Set TWLDQSEN (CSR field) = RNDUP[tWLDQSEN(ns)/(4*tCYC(ns))],
                                                         where tWLDQSEN is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(25nCK) */
	uint64_t twlmrd                       : 4;  /**< Indicates tWLMRD constraints.
                                                         Set TWLMRD (CSR field) = RNDUP[tWLMRD(ns)/(4*tCYC(ns))],
                                                         where tWLMRD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(40nCK) */
	uint64_t txp                          : 3;  /**< Indicates tXP constraints.
                                                         Set TXP (CSR field) = RNDUP[tXP(ns)/tCYC(ns)]-1,
                                                         where tXP is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(3nCK, 7.5ns) */
	uint64_t trrd                         : 3;  /**< Indicates tRRD constraints.
                                                         Set TRRD (CSR field) = RNDUP[tRRD(ns)/tCYC(ns)]-2,
                                                         where tRRD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(4nCK, 10ns)
                                                            - 000: RESERVED
                                                            - 001: 3 tCYC
                                                            - ...
                                                            - 110: 8 tCYC
                                                            - 111: 9 tCYC */
	uint64_t trfc                         : 5;  /**< Indicates tRFC constraints.
                                                         Set TRFC (CSR field) = RNDUP[tRFC(ns)/(8*tCYC(ns))],
                                                         where tRFC is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=90-350ns
                                                              - 00000: RESERVED
                                                              - 00001: 8 tCYC
                                                              - 00010: 16 tCYC
                                                              - 00011: 24 tCYC
                                                              - 00100: 32 tCYC
                                                              - ...
                                                              - 11110: 240 tCYC
                                                              - 11111: 248 tCYC */
	uint64_t twtr                         : 4;  /**< Indicates tWTR constraints.
                                                         Set TWTR (CSR field) = RNDUP[tWTR(ns)/tCYC(ns)]-1,
                                                         where tWTR is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(4nCK, 7.5ns)
                                                             - 0000: RESERVED
                                                             - 0001: 2
                                                             - ...
                                                             - 0111: 8
                                                             - 1000-1111: RESERVED */
	uint64_t trcd                         : 4;  /**< Indicates tRCD constraints.
                                                         Set TRCD (CSR field) = RNDUP[tRCD(ns)/tCYC(ns)],
                                                         where tRCD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=10-15ns
                                                             - 0000: RESERVED
                                                             - 0001: 2 (2 is the smallest value allowed)
                                                             - 0002: 2
                                                             - ...
                                                             - 1110: 14
                                                             - 1111: RESERVED
                                                         In 2T mode, make this register TRCD-1, not going
                                                         below 2. */
	uint64_t tras                         : 5;  /**< Indicates tRAS constraints.
                                                         Set [TRAS_EXT[0:0], TRAS[4:0]] (CSR field) = RNDUP[tRAS(ns)/tCYC(ns)]-1,
                                                         where tRAS is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=35ns-9*tREFI
                                                             - 000000: RESERVED
                                                             - 000001: 2 tCYC
                                                             - 000010: 3 tCYC
                                                             - ...
                                                             - 111111: 64 tCYC */
	uint64_t tmprr                        : 4;  /**< Indicates tMPRR constraints.
                                                         Set TMPRR (CSR field) = RNDUP[tMPRR(ns)/tCYC(ns)]-1,
                                                         where tMPRR is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=1nCK */
#else
	uint64_t tmprr                        : 4;
	uint64_t tras                         : 5;
	uint64_t trcd                         : 4;
	uint64_t twtr                         : 4;
	uint64_t trfc                         : 5;
	uint64_t trrd                         : 3;
	uint64_t txp                          : 3;
	uint64_t twlmrd                       : 4;
	uint64_t twldqsen                     : 4;
	uint64_t tfaw                         : 5;
	uint64_t txpdll                       : 5;
	uint64_t tras_ext                     : 1;
	uint64_t reserved_47_63               : 17;
#endif
	} cn61xx;
	struct cvmx_lmcx_timing_params1_cn61xx cn63xx;
	struct cvmx_lmcx_timing_params1_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_46_63               : 18;
	uint64_t txpdll                       : 5;  /**< Indicates tXPDLL constraints.
                                                         Set TXPDLL (CSR field) = RNDUP[tXPDLL(ns)/tCYC(ns)]-1,
                                                         where tXPDLL is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(10nCK, 24ns) */
	uint64_t tfaw                         : 5;  /**< Indicates tFAW constraints.
                                                         Set TFAW (CSR field) = RNDUP[tFAW(ns)/(4*tCYC(ns))],
                                                         where tFAW is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=30-40ns */
	uint64_t twldqsen                     : 4;  /**< Indicates tWLDQSEN constraints.
                                                         Set TWLDQSEN (CSR field) = RNDUP[tWLDQSEN(ns)/(4*tCYC(ns))],
                                                         where tWLDQSEN is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(25nCK) */
	uint64_t twlmrd                       : 4;  /**< Indicates tWLMRD constraints.
                                                         Set TWLMRD (CSR field) = RNDUP[tWLMRD(ns)/(4*tCYC(ns))],
                                                         where tWLMRD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(40nCK) */
	uint64_t txp                          : 3;  /**< Indicates tXP constraints.
                                                         Set TXP (CSR field) = RNDUP[tXP(ns)/tCYC(ns)]-1,
                                                         where tXP is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(3nCK, 7.5ns) */
	uint64_t trrd                         : 3;  /**< Indicates tRRD constraints.
                                                         Set TRRD (CSR field) = RNDUP[tRRD(ns)/tCYC(ns)]-2,
                                                         where tRRD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(4nCK, 10ns)
                                                            - 000: RESERVED
                                                            - 001: 3 tCYC
                                                            - ...
                                                            - 110: 8 tCYC
                                                            - 111: 9 tCYC */
	uint64_t trfc                         : 5;  /**< Indicates tRFC constraints.
                                                         Set TRFC (CSR field) = RNDUP[tRFC(ns)/(8*tCYC(ns))],
                                                         where tRFC is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=90-350ns
                                                              - 00000: RESERVED
                                                              - 00001: 8 tCYC
                                                              - 00010: 16 tCYC
                                                              - 00011: 24 tCYC
                                                              - 00100: 32 tCYC
                                                              - ...
                                                              - 11110: 240 tCYC
                                                              - 11111: 248 tCYC */
	uint64_t twtr                         : 4;  /**< Indicates tWTR constraints.
                                                         Set TWTR (CSR field) = RNDUP[tWTR(ns)/tCYC(ns)]-1,
                                                         where tWTR is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=max(4nCK, 7.5ns)
                                                             - 0000: RESERVED
                                                             - 0001: 2
                                                             - ...
                                                             - 0111: 8
                                                             - 1000-1111: RESERVED */
	uint64_t trcd                         : 4;  /**< Indicates tRCD constraints.
                                                         Set TRCD (CSR field) = RNDUP[tRCD(ns)/tCYC(ns)],
                                                         where tRCD is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=10-15ns
                                                             - 0000: RESERVED
                                                             - 0001: 2 (2 is the smallest value allowed)
                                                             - 0002: 2
                                                             - ...
                                                             - 1001: 9
                                                             - 1010-1111: RESERVED
                                                         In 2T mode, make this register TRCD-1, not going
                                                         below 2. */
	uint64_t tras                         : 5;  /**< Indicates tRAS constraints.
                                                         Set TRAS (CSR field) = RNDUP[tRAS(ns)/tCYC(ns)]-1,
                                                         where tRAS is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=35ns-9*tREFI
                                                             - 00000: RESERVED
                                                             - 00001: 2 tCYC
                                                             - 00010: 3 tCYC
                                                             - ...
                                                             - 11111: 32 tCYC */
	uint64_t tmprr                        : 4;  /**< Indicates tMPRR constraints.
                                                         Set TMPRR (CSR field) = RNDUP[tMPRR(ns)/tCYC(ns)]-1,
                                                         where tMPRR is from the DDR3 spec, and tCYC(ns)
                                                         is the DDR clock frequency (not data rate).
                                                         TYP=1nCK */
#else
	uint64_t tmprr                        : 4;
	uint64_t tras                         : 5;
	uint64_t trcd                         : 4;
	uint64_t twtr                         : 4;
	uint64_t trfc                         : 5;
	uint64_t trrd                         : 3;
	uint64_t txp                          : 3;
	uint64_t twlmrd                       : 4;
	uint64_t twldqsen                     : 4;
	uint64_t tfaw                         : 5;
	uint64_t txpdll                       : 5;
	uint64_t reserved_46_63               : 18;
#endif
	} cn63xxp1;
	struct cvmx_lmcx_timing_params1_cn61xx cn66xx;
	struct cvmx_lmcx_timing_params1_cn61xx cn68xx;
	struct cvmx_lmcx_timing_params1_cn61xx cn68xxp1;
	struct cvmx_lmcx_timing_params1_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_49_63               : 15;
	uint64_t txpdll                       : 5;  /**< Indicates TXPDLL constraints. Set this field as follows:
                                                         RNDUP[TXPDLL(ns) / TCYC(ns)] - 1
                                                         where TXPDLL is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not
                                                         data rate).
                                                         TYP=max(10nCK, 24 ns) */
	uint64_t tfaw                         : 5;  /**< Indicates TFAW constraints. Set this field as follows:
                                                         RNDUP[TFAW(ns) / (4 * TCYC(ns))]
                                                         where TFAW is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = 30-40 ns */
	uint64_t twldqsen                     : 4;  /**< Indicates TWLDQSEN constraints. Set this field as follows:
                                                         RNDUP[TWLDQSEN(ns) / (4 * TCYC(ns))]
                                                         where TWLDQSEN is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not
                                                         data rate).
                                                         TYP = max(25nCK) */
	uint64_t twlmrd                       : 4;  /**< Indicates TWLMRD constraints. Set this field as follows:
                                                         RNDUP[TWLMRD(ns) / (4 * TCYC(ns))]
                                                         where TWLMRD is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not
                                                         data rate).
                                                         TYP = max(40nCK) */
	uint64_t txp                          : 3;  /**< Indicates TXP constraints. Set this field as follows:
                                                         RNDUP[TXP(ns) / TCYC(ns)] - 1
                                                         where TXP is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP=max(3nCK, 7.5 ns) */
	uint64_t trrd                         : 3;  /**< Indicates TRRD constraints. Set this field as follows:
                                                         RNDUP[TRRD(ns) / TCYC(ns)] - 1,
                                                         where TRRD is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = max(4nCK, 10 ns)
                                                         0x0 = reserved
                                                         0x1 = 2 TCYC
                                                         - ...
                                                         0x6 = 7 TCYC
                                                         0x7 = 8 TCYC
                                                         For DDR4, this is the TRRD_S parameter. */
	uint64_t trfc                         : 7;  /**< Indicates TRFC constraints. Set this field as follows:
                                                         RNDUP[TRFC(ns) / (8 * TCYC(ns))]
                                                         where TRFC is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = 90-350 ns
                                                         0x0 = reserved.
                                                         0x1 = 8 TCYC.
                                                         0x2 = 16 TCYC.
                                                         0x3 = 24 TCYC.
                                                         0x4 = 32 TCYC.
                                                         - ...
                                                         0x7E = 1008 TCYC.
                                                         0x7F = 1016 TCYC. */
	uint64_t twtr                         : 4;  /**< Indicates TWTR constraints. Set this field as follows:
                                                         RNDUP[TWTR(ns) / TCYC(ns)] - 1
                                                         where TWTR is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = max(4nCK, 7.5 ns)
                                                         For DDR4, this CSR field represents TWTR_S.
                                                         0x0 = reserved.
                                                         0x1 = 2.
                                                         - ...
                                                         0x7 = 8.
                                                         0x8-0xF = reserved. */
	uint64_t trcd                         : 4;  /**< Indicates TRCD constraints. Set this field as follows:
                                                         RNDUP[TRCD(ns) / TCYC(ns)]
                                                         where TRCD is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = 10-15 ns
                                                         0x0 = reserved.
                                                         0x1 = 2 (2 is the smallest value allowed).
                                                         0x2 = 2.
                                                         - ...
                                                         0xE = 14.
                                                         0xA-0xF = reserved.
                                                         In 2T mode, make this register TRCD - 1, not going below 2. */
	uint64_t tras                         : 6;  /**< Indicates TRAS constraints. Set TRAS (CSR field) as follows:
                                                         RNDUP[TRAS(ns)/TCYC(ns)] - 1,
                                                         where TRAS is from the DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data rate).
                                                         TYP = 35ns - 9 * TREFI
                                                         - 000000: reserved
                                                         - 000001: 2 TCYC
                                                         - 000010: 3 TCYC
                                                         - ...
                                                         - 111111: 64 TCYC */
	uint64_t tmprr                        : 4;  /**< Indicates TMPRR constraints. Set this field as follows:
                                                         RNDUP[TMPRR(ns) / TCYC(ns)] - 1
                                                         where TMPRR is from the JEDEC DDR3 spec, and TCYC(ns) is the DDR clock frequency (not data
                                                         rate).
                                                         TYP = 1 nCK */
#else
	uint64_t tmprr                        : 4;
	uint64_t tras                         : 6;
	uint64_t trcd                         : 4;
	uint64_t twtr                         : 4;
	uint64_t trfc                         : 7;
	uint64_t trrd                         : 3;
	uint64_t txp                          : 3;
	uint64_t twlmrd                       : 4;
	uint64_t twldqsen                     : 4;
	uint64_t tfaw                         : 5;
	uint64_t txpdll                       : 5;
	uint64_t reserved_49_63               : 15;
#endif
	} cn70xx;
	struct cvmx_lmcx_timing_params1_cn70xx cn78xx;
	struct cvmx_lmcx_timing_params1_cn61xx cnf71xx;
};
typedef union cvmx_lmcx_timing_params1 cvmx_lmcx_timing_params1_t;

/**
 * cvmx_lmc#_timing_params2
 *
 * This register sets timing parameters for DDR4.
 *
 */
union cvmx_lmcx_timing_params2 {
	uint64_t u64;
	struct cvmx_lmcx_timing_params2_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_15_63               : 49;
	uint64_t trtp                         : 4;  /**< Specifies the TRTP parameter, in cycles. Set this field as follows:
                                                         RNDUP[TRTP(ns) / TCYC(ns)] - 1,
                                                         For DDR3, typical = max(4 nCK, 7.5ns).
                                                         For DDR4 the TRTP parameter is dictated by the TWR MR bits. */
	uint64_t t_rw_op_max                  : 4;  /**< Specifies the maximum delay for a read or write operation to complete, used to set the
                                                         timing of MRW and MPR operations. Set this field as follows:
                                                         RNDUP[Maximum operation delay (cycles) / 8]
                                                         Typical = 0x7. */
	uint64_t twtr_l                       : 4;  /**< Specifies TWTR_L constraints. Set this field as follows:
                                                         RNDUP[TWTR_L(ns) / TCYC(ns)] - 1
                                                         where TWTR_L is from the JEDEC DDR4 spec, and TCYC(ns) is the DDR clock frequency (not the
                                                         data rate).
                                                         Typical = MAX(4 nCK, 7.5 ns)
                                                         INTERNAL: Seems the '- 1' is because we add 1 back into slot timing equation */
	uint64_t trrd_l                       : 3;  /**< Specifies TRRD_L constraints. Set this field as follows:
                                                         RNDUP[TRRD_L(ns) / TCYC(ns)] - 1,
                                                         where TRRD_L is from the JEDEC DDR4 spec, and TCYC(ns) is the DDR clock frequency (not the
                                                         data rate).
                                                         Typical = MAX(4 nCK, 7.5 ns)
                                                         0x0 = reserved. 0x4 = five TCYC.
                                                         0x1 = two TCYC. 0x5 = six TCYC.
                                                         0x2 = three TCYC. 0x6 = seven TCYC.
                                                         0x3 = four TCYC. 0x7 = eight TCYC. */
#else
	uint64_t trrd_l                       : 3;
	uint64_t twtr_l                       : 4;
	uint64_t t_rw_op_max                  : 4;
	uint64_t trtp                         : 4;
	uint64_t reserved_15_63               : 49;
#endif
	} s;
	struct cvmx_lmcx_timing_params2_s     cn70xx;
	struct cvmx_lmcx_timing_params2_s     cn78xx;
};
typedef union cvmx_lmcx_timing_params2 cvmx_lmcx_timing_params2_t;

/**
 * cvmx_lmc#_tro_ctl
 *
 * LMC_TRO_CTL = LMC Temperature Ring Osc Control
 * This register is an assortment of various control fields needed to control the temperature ring oscillator
 *
 * Notes:
 * To bring up the temperature ring oscillator, write TRESET to 0, and follow by initializing RCLK_CNT to desired
 * value
 */
union cvmx_lmcx_tro_ctl {
	uint64_t u64;
	struct cvmx_lmcx_tro_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_33_63               : 31;
	uint64_t rclk_cnt                     : 32; /**< rclk counter */
	uint64_t treset                       : 1;  /**< Reset ring oscillator */
#else
	uint64_t treset                       : 1;
	uint64_t rclk_cnt                     : 32;
	uint64_t reserved_33_63               : 31;
#endif
	} s;
	struct cvmx_lmcx_tro_ctl_s            cn61xx;
	struct cvmx_lmcx_tro_ctl_s            cn63xx;
	struct cvmx_lmcx_tro_ctl_s            cn63xxp1;
	struct cvmx_lmcx_tro_ctl_s            cn66xx;
	struct cvmx_lmcx_tro_ctl_s            cn68xx;
	struct cvmx_lmcx_tro_ctl_s            cn68xxp1;
	struct cvmx_lmcx_tro_ctl_s            cnf71xx;
};
typedef union cvmx_lmcx_tro_ctl cvmx_lmcx_tro_ctl_t;

/**
 * cvmx_lmc#_tro_stat
 *
 * LMC_TRO_STAT = LMC Temperature Ring Osc Status
 * This register is an assortment of various control fields needed to control the temperature ring oscillator
 */
union cvmx_lmcx_tro_stat {
	uint64_t u64;
	struct cvmx_lmcx_tro_stat_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t ring_cnt                     : 32; /**< ring counter */
#else
	uint64_t ring_cnt                     : 32;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_tro_stat_s           cn61xx;
	struct cvmx_lmcx_tro_stat_s           cn63xx;
	struct cvmx_lmcx_tro_stat_s           cn63xxp1;
	struct cvmx_lmcx_tro_stat_s           cn66xx;
	struct cvmx_lmcx_tro_stat_s           cn68xx;
	struct cvmx_lmcx_tro_stat_s           cn68xxp1;
	struct cvmx_lmcx_tro_stat_s           cnf71xx;
};
typedef union cvmx_lmcx_tro_stat cvmx_lmcx_tro_stat_t;

/**
 * cvmx_lmc#_wlevel_ctl
 */
union cvmx_lmcx_wlevel_ctl {
	uint64_t u64;
	struct cvmx_lmcx_wlevel_ctl_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_22_63               : 42;
	uint64_t rtt_nom                      : 3;  /**< RTT_NOM
                                                         LMC writes a decoded value to MR1[Rtt_Nom] of the rank during
                                                         write leveling. Per JEDEC DDR3 specifications,
                                                         only values MR1[Rtt_Nom] = 1 (RQZ/4), 2 (RQZ/2), or 3 (RQZ/6)
                                                         are allowed during write leveling with output buffer enabled.
                                                         000 : LMC writes 001 (RZQ/4)   to MR1[Rtt_Nom]
                                                         001 : LMC writes 010 (RZQ/2)   to MR1[Rtt_Nom]
                                                         010 : LMC writes 011 (RZQ/6)   to MR1[Rtt_Nom]
                                                         011 : LMC writes 100 (RZQ/12)  to MR1[Rtt_Nom]
                                                         100 : LMC writes 101 (RZQ/8)   to MR1[Rtt_Nom]
                                                         101 : LMC writes 110 (Rsvd)    to MR1[Rtt_Nom]
                                                         110 : LMC writes 111 (Rsvd)    to  MR1[Rtt_Nom]
                                                         111 : LMC writes 000 (Disabled) to MR1[Rtt_Nom] */
	uint64_t bitmask                      : 8;  /**< Mask to select bit lanes on which write-leveling
                                                         feedback is returned when OR_DIS is set to 1 */
	uint64_t or_dis                       : 1;  /**< Disable or'ing of bits in a byte lane when computing
                                                         the write-leveling bitmask */
	uint64_t sset                         : 1;  /**< Run write-leveling on the current setting only. */
	uint64_t lanemask                     : 9;  /**< One-hot mask to select byte lane to be leveled by
                                                         the write-leveling sequence
                                                         Used with x16 parts where the upper and lower byte
                                                         lanes need to be leveled independently */
#else
	uint64_t lanemask                     : 9;
	uint64_t sset                         : 1;
	uint64_t or_dis                       : 1;
	uint64_t bitmask                      : 8;
	uint64_t rtt_nom                      : 3;
	uint64_t reserved_22_63               : 42;
#endif
	} s;
	struct cvmx_lmcx_wlevel_ctl_s         cn61xx;
	struct cvmx_lmcx_wlevel_ctl_s         cn63xx;
	struct cvmx_lmcx_wlevel_ctl_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_10_63               : 54;
	uint64_t sset                         : 1;  /**< Run write-leveling on the current setting only. */
	uint64_t lanemask                     : 9;  /**< One-hot mask to select byte lane to be leveled by
                                                         the write-leveling sequence
                                                         Used with x16 parts where the upper and lower byte
                                                         lanes need to be leveled independently */
#else
	uint64_t lanemask                     : 9;
	uint64_t sset                         : 1;
	uint64_t reserved_10_63               : 54;
#endif
	} cn63xxp1;
	struct cvmx_lmcx_wlevel_ctl_s         cn66xx;
	struct cvmx_lmcx_wlevel_ctl_s         cn68xx;
	struct cvmx_lmcx_wlevel_ctl_s         cn68xxp1;
	struct cvmx_lmcx_wlevel_ctl_s         cn70xx;
	struct cvmx_lmcx_wlevel_ctl_s         cn78xx;
	struct cvmx_lmcx_wlevel_ctl_s         cnf71xx;
};
typedef union cvmx_lmcx_wlevel_ctl cvmx_lmcx_wlevel_ctl_t;

/**
 * cvmx_lmc#_wlevel_dbg
 *
 * A given write of LMC(0..3)_WLEVEL_DBG returns the write-leveling pass/fail results for all
 * possible delay settings (i.e. the BITMASK) for only one byte in the last rank that the
 * hardware write-leveled. LMC(0..3)_WLEVEL_DBG[BYTE] selects the particular byte. To get these
 * pass/fail results for a different rank, you must run the hardware write-leveling again. For
 * example, it is possible to get the BITMASK results for every byte of every rank if you run
 * write-leveling separately for each rank, probing LMC(0..3)_WLEVEL_DBG between each write-
 * leveling.
 */
union cvmx_lmcx_wlevel_dbg {
	uint64_t u64;
	struct cvmx_lmcx_wlevel_dbg_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_12_63               : 52;
	uint64_t bitmask                      : 8;  /**< Bitmask generated during deskew settings sweep
                                                         if LMCX_WLEVEL_CTL[SSET]=0
                                                           BITMASK[n]=0 means deskew setting n failed
                                                           BITMASK[n]=1 means deskew setting n passed
                                                           for 0 <= n <= 7
                                                           BITMASK contains the first 8 results of the total 16
                                                           collected by LMC during the write-leveling sequence
                                                         else if LMCX_WLEVEL_CTL[SSET]=1
                                                           BITMASK[0]=0 means curr deskew setting failed
                                                           BITMASK[0]=1 means curr deskew setting passed */
	uint64_t byte                         : 4;  /**< 0 <= BYTE <= 8 */
#else
	uint64_t byte                         : 4;
	uint64_t bitmask                      : 8;
	uint64_t reserved_12_63               : 52;
#endif
	} s;
	struct cvmx_lmcx_wlevel_dbg_s         cn61xx;
	struct cvmx_lmcx_wlevel_dbg_s         cn63xx;
	struct cvmx_lmcx_wlevel_dbg_s         cn63xxp1;
	struct cvmx_lmcx_wlevel_dbg_s         cn66xx;
	struct cvmx_lmcx_wlevel_dbg_s         cn68xx;
	struct cvmx_lmcx_wlevel_dbg_s         cn68xxp1;
	struct cvmx_lmcx_wlevel_dbg_s         cn70xx;
	struct cvmx_lmcx_wlevel_dbg_s         cn78xx;
	struct cvmx_lmcx_wlevel_dbg_s         cnf71xx;
};
typedef union cvmx_lmcx_wlevel_dbg cvmx_lmcx_wlevel_dbg_t;

/**
 * cvmx_lmc#_wlevel_rank#
 *
 * Four of these CSRs exist per LMC, one for each rank. Deskew setting is measured in units of
 * 1/8 CK, so the below BYTEn values can range over 4 CK cycles. Assuming
 * LMC(0..3)_WLEVEL_CTL[SSET]=0, the BYTEn<2:0> values are not used during write-leveling, and
 * they are overwritten by the hardware as part of the write-leveling sequence. (Hardware sets
 * STATUS to 3 after hardware write-leveling completes for the rank). Software needs to set
 * BYTEn<4:3> bits.
 * Each CSR may also be written by software, but not while a write-leveling sequence is in
 * progress. (Hardware sets STATUS to 1 after a CSR write.) Software initiates a hardware write-
 * leveling sequence by programming LMC*_WLEVEL_CTL and writing RANKMASK and INIT_START=1 with
 * SEQ_SEL=6 in LMC*0_CONFIG.
 * LMC will then step through and accumulate write leveling results for 8 unique delay settings
 * (twice), starting at a delay of LMC(0..3)_WLEVEL_RANK(0..3) [BYTEn<4:3>]* 8 CK increasing by
 * 1/8 CK each setting. Hardware will then set LMC(0..3)_WLEVEL_RANK(0..3)[BYTEn<2:0>] to
 * indicate the first write leveling result of '1' that followed a result of '0' during the
 * sequence by searching for a '1100' pattern in the generated bitmask, except that LMC will
 * always write LMC(0..3)_WLEVEL_RANK(0..3)[BYTEn<0>]=0. If hardware is unable to find a match
 * for a '1100' pattern, then hardware sets LMC(0..3)_WLEVEL_RANK(0..3) [BYTEn<2:0>] to 0x4. See
 * LMC*_WLEVEL_CTL.
 * LMC*_WLEVEL_RANKi values for ranks i without attached DRAM should be set such that they do not
 * increase the range of possible BYTE values for any byte lane. The easiest way to do this is to
 * set LMC*_WLEVEL_RANKi = LMC*_WLEVEL_RANKj, where j is some rank with attached DRAM whose
 * LMC*_WLEVEL_RANKj is already fully initialized.
 */
union cvmx_lmcx_wlevel_rankx {
	uint64_t u64;
	struct cvmx_lmcx_wlevel_rankx_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_47_63               : 17;
	uint64_t status                       : 2;  /**< Indicates status of the write-leveling and where
                                                         the BYTE* programmings in <44:0> came from:
                                                         0 = BYTE* values are their reset value
                                                         1 = BYTE* values were set via a CSR write to this register
                                                         2 = write-leveling sequence currently in progress (BYTE* values are unpredictable)
                                                         3 = BYTE* values came from a complete write-leveling sequence, irrespective of
                                                             which lanes are masked via LMC*WLEVEL_CTL[LANEMASK] */
	uint64_t byte8                        : 5;  /**< Deskew setting
                                                         Bit 0 of BYTE8 must be zero during normal operation.
                                                         When ECC DRAM is not present (i.e. when DRAM is not
                                                         attached to chip signals DDR_CBS_0_* and DDR_CB[7:0]),
                                                         SW should write BYTE8 with a value that does
                                                         not increase the range of possible BYTE* values. The
                                                         easiest way to do this is to set
                                                         LMC*_WLEVEL_RANK*[BYTE8] = LMC*_WLEVEL_RANK*[BYTE0]
                                                         when there is no ECC DRAM, using the final BYTE0 value. */
	uint64_t byte7                        : 5;  /**< Deskew setting
                                                         Bit 0 of BYTE7 must be zero during normal operation */
	uint64_t byte6                        : 5;  /**< Deskew setting
                                                         Bit 0 of BYTE6 must be zero during normal operation */
	uint64_t byte5                        : 5;  /**< Deskew setting
                                                         Bit 0 of BYTE5 must be zero during normal operation */
	uint64_t byte4                        : 5;  /**< Deskew setting
                                                         Bit 0 of BYTE4 must be zero during normal operation */
	uint64_t byte3                        : 5;  /**< Deskew setting
                                                         Bit 0 of BYTE3 must be zero during normal operation */
	uint64_t byte2                        : 5;  /**< Deskew setting
                                                         Bit 0 of BYTE2 must be zero during normal operation */
	uint64_t byte1                        : 5;  /**< Deskew setting
                                                         Bit 0 of BYTE1 must be zero during normal operation */
	uint64_t byte0                        : 5;  /**< Deskew setting
                                                         Bit 0 of BYTE0 must be zero during normal operation */
#else
	uint64_t byte0                        : 5;
	uint64_t byte1                        : 5;
	uint64_t byte2                        : 5;
	uint64_t byte3                        : 5;
	uint64_t byte4                        : 5;
	uint64_t byte5                        : 5;
	uint64_t byte6                        : 5;
	uint64_t byte7                        : 5;
	uint64_t byte8                        : 5;
	uint64_t status                       : 2;
	uint64_t reserved_47_63               : 17;
#endif
	} s;
	struct cvmx_lmcx_wlevel_rankx_s       cn61xx;
	struct cvmx_lmcx_wlevel_rankx_s       cn63xx;
	struct cvmx_lmcx_wlevel_rankx_s       cn63xxp1;
	struct cvmx_lmcx_wlevel_rankx_s       cn66xx;
	struct cvmx_lmcx_wlevel_rankx_s       cn68xx;
	struct cvmx_lmcx_wlevel_rankx_s       cn68xxp1;
	struct cvmx_lmcx_wlevel_rankx_s       cn70xx;
	struct cvmx_lmcx_wlevel_rankx_s       cn78xx;
	struct cvmx_lmcx_wlevel_rankx_s       cnf71xx;
};
typedef union cvmx_lmcx_wlevel_rankx cvmx_lmcx_wlevel_rankx_t;

/**
 * cvmx_lmc#_wodt_ctl0
 *
 * LMC_WODT_CTL0 = LMC Write OnDieTermination control
 * See the description in LMC_WODT_CTL1.
 *
 * Notes:
 * Together, the LMC_WODT_CTL1 and LMC_WODT_CTL0 CSRs control the write ODT mask.  See LMC_WODT_CTL1.
 *
 */
union cvmx_lmcx_wodt_ctl0 {
	uint64_t u64;
	struct cvmx_lmcx_wodt_ctl0_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_0_63                : 64;
#else
	uint64_t reserved_0_63                : 64;
#endif
	} s;
	struct cvmx_lmcx_wodt_ctl0_cn30xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t wodt_d1_r1                   : 8;  /**< Write ODT mask DIMM1, RANK1 */
	uint64_t wodt_d1_r0                   : 8;  /**< Write ODT mask DIMM1, RANK0 */
	uint64_t wodt_d0_r1                   : 8;  /**< Write ODT mask DIMM0, RANK1 */
	uint64_t wodt_d0_r0                   : 8;  /**< Write ODT mask DIMM0, RANK0 */
#else
	uint64_t wodt_d0_r0                   : 8;
	uint64_t wodt_d0_r1                   : 8;
	uint64_t wodt_d1_r0                   : 8;
	uint64_t wodt_d1_r1                   : 8;
	uint64_t reserved_32_63               : 32;
#endif
	} cn30xx;
	struct cvmx_lmcx_wodt_ctl0_cn30xx     cn31xx;
	struct cvmx_lmcx_wodt_ctl0_cn38xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t wodt_hi3                     : 4;  /**< Write ODT mask for position 3, data[127:64] */
	uint64_t wodt_hi2                     : 4;  /**< Write ODT mask for position 2, data[127:64] */
	uint64_t wodt_hi1                     : 4;  /**< Write ODT mask for position 1, data[127:64] */
	uint64_t wodt_hi0                     : 4;  /**< Write ODT mask for position 0, data[127:64] */
	uint64_t wodt_lo3                     : 4;  /**< Write ODT mask for position 3, data[ 63: 0] */
	uint64_t wodt_lo2                     : 4;  /**< Write ODT mask for position 2, data[ 63: 0] */
	uint64_t wodt_lo1                     : 4;  /**< Write ODT mask for position 1, data[ 63: 0] */
	uint64_t wodt_lo0                     : 4;  /**< Write ODT mask for position 0, data[ 63: 0] */
#else
	uint64_t wodt_lo0                     : 4;
	uint64_t wodt_lo1                     : 4;
	uint64_t wodt_lo2                     : 4;
	uint64_t wodt_lo3                     : 4;
	uint64_t wodt_hi0                     : 4;
	uint64_t wodt_hi1                     : 4;
	uint64_t wodt_hi2                     : 4;
	uint64_t wodt_hi3                     : 4;
	uint64_t reserved_32_63               : 32;
#endif
	} cn38xx;
	struct cvmx_lmcx_wodt_ctl0_cn38xx     cn38xxp2;
	struct cvmx_lmcx_wodt_ctl0_cn38xx     cn50xx;
	struct cvmx_lmcx_wodt_ctl0_cn30xx     cn52xx;
	struct cvmx_lmcx_wodt_ctl0_cn30xx     cn52xxp1;
	struct cvmx_lmcx_wodt_ctl0_cn30xx     cn56xx;
	struct cvmx_lmcx_wodt_ctl0_cn30xx     cn56xxp1;
	struct cvmx_lmcx_wodt_ctl0_cn38xx     cn58xx;
	struct cvmx_lmcx_wodt_ctl0_cn38xx     cn58xxp1;
};
typedef union cvmx_lmcx_wodt_ctl0 cvmx_lmcx_wodt_ctl0_t;

/**
 * cvmx_lmc#_wodt_ctl1
 *
 * LMC_WODT_CTL1 = LMC Write OnDieTermination control
 * System designers may desire to terminate DQ/DQS/DM lines for higher frequency DDR operations
 * (667MHz and faster), especially on a multi-rank system. DDR2 DQ/DM/DQS I/O's have built in
 * Termination resistor that can be turned on or off by the controller, after meeting tAOND and tAOF
 * timing requirements. Each Rank has its own ODT pin that fans out to all the memory parts
 * in that DIMM. System designers may prefer different combinations of ODT ON's for read and write
 * into different ranks. Octeon supports full programmability by way of the mask register below.
 * Each Rank position has its own 8-bit programmable field.
 * When the controller does a write to that rank, it sets the 8 ODT pins to the MASK pins below.
 * For eg., When doing a write into Rank0, a system designer may desire to terminate the lines
 * with the resistor on Dimm0/Rank1. The mask WODT_D0_R0 would then be [00000010].
 * If ODT feature is not desired, the DDR parts can be programmed to not look at these pins by
 * writing 0 in QS_DIC. Octeon drives the appropriate mask values on the ODT pins by default.
 * If this feature is not required, write 0 in this register.
 *
 * Notes:
 * Together, the LMC_WODT_CTL1 and LMC_WODT_CTL0 CSRs control the write ODT mask.
 * When a given RANK is selected, the WODT mask for that RANK is used.  The resulting WODT mask is
 * driven to the DIMMs in the following manner:
 *            BUNK_ENA=1     BUNK_ENA=0
 * Mask[7] -> DIMM3, RANK1    DIMM3
 * Mask[6] -> DIMM3, RANK0
 * Mask[5] -> DIMM2, RANK1    DIMM2
 * Mask[4] -> DIMM2, RANK0
 * Mask[3] -> DIMM1, RANK1    DIMM1
 * Mask[2] -> DIMM1, RANK0
 * Mask[1] -> DIMM0, RANK1    DIMM0
 * Mask[0] -> DIMM0, RANK0
 */
union cvmx_lmcx_wodt_ctl1 {
	uint64_t u64;
	struct cvmx_lmcx_wodt_ctl1_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_32_63               : 32;
	uint64_t wodt_d3_r1                   : 8;  /**< Write ODT mask DIMM3, RANK1/DIMM3 in SingleRanked */
	uint64_t wodt_d3_r0                   : 8;  /**< Write ODT mask DIMM3, RANK0 */
	uint64_t wodt_d2_r1                   : 8;  /**< Write ODT mask DIMM2, RANK1/DIMM2 in SingleRanked */
	uint64_t wodt_d2_r0                   : 8;  /**< Write ODT mask DIMM2, RANK0 */
#else
	uint64_t wodt_d2_r0                   : 8;
	uint64_t wodt_d2_r1                   : 8;
	uint64_t wodt_d3_r0                   : 8;
	uint64_t wodt_d3_r1                   : 8;
	uint64_t reserved_32_63               : 32;
#endif
	} s;
	struct cvmx_lmcx_wodt_ctl1_s          cn30xx;
	struct cvmx_lmcx_wodt_ctl1_s          cn31xx;
	struct cvmx_lmcx_wodt_ctl1_s          cn52xx;
	struct cvmx_lmcx_wodt_ctl1_s          cn52xxp1;
	struct cvmx_lmcx_wodt_ctl1_s          cn56xx;
	struct cvmx_lmcx_wodt_ctl1_s          cn56xxp1;
};
typedef union cvmx_lmcx_wodt_ctl1 cvmx_lmcx_wodt_ctl1_t;

/**
 * cvmx_lmc#_wodt_mask
 *
 * System designers may desire to terminate DQ/DQS lines for higher-frequency DDR operations,
 * especially on a multirank system. DDR3 DQ/DQS I/Os have built-in termination resistors that
 * can be turned on or off by the controller, after meeting TAOND and TAOF timing requirements.
 * Each rank has its own ODT pin that fans out to all of the memory parts in that DIMM. System
 * designers may prefer different combinations of ODT ONs for write operations into different
 * ranks. CN78XX supports full programmability by way of the mask register below. Each rank
 * position has its own 8-bit programmable field. When the controller does a write to that rank,
 * it sets the 4 ODT pins to the mask pins below. For example, when doing a write into Rank0, a
 * system designer may desire to terminate the lines with the resistor on DIMM0/Rank1. The mask
 * WODT_D0_R0 would then be [00000010].
 * CN78XX drives the appropriate mask values on the ODT pins by default. If this feature is not
 * required, write 0x0 in this register. When a given RANK is selected, the WODT mask for that
 * RANK is used. The resulting WODT mask is driven to the DIMMs in the following manner:
 */
union cvmx_lmcx_wodt_mask {
	uint64_t u64;
	struct cvmx_lmcx_wodt_mask_s {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t wodt_d3_r1                   : 8;  /**< Write ODT mask DIMM3, RANK1/DIMM3 in SingleRanked
                                                         *UNUSED IN 6xxx, and MBZ* */
	uint64_t wodt_d3_r0                   : 8;  /**< Write ODT mask DIMM3, RANK0
                                                         *UNUSED IN 6xxx, and MBZ* */
	uint64_t wodt_d2_r1                   : 8;  /**< Write ODT mask DIMM2, RANK1/DIMM2 in SingleRanked
                                                         *UNUSED IN 6xxx, and MBZ* */
	uint64_t wodt_d2_r0                   : 8;  /**< Write ODT mask DIMM2, RANK0
                                                         *UNUSED IN 6xxx, and MBZ* */
	uint64_t wodt_d1_r1                   : 8;  /**< Write ODT mask DIMM1, RANK1/DIMM1 in SingleRanked
                                                         if (!RANK_ENA) then WODT_D1_R1[3:0] MBZ
                                                         *Upper 4 bits UNUSED IN 6xxx, and MBZ* */
	uint64_t wodt_d1_r0                   : 8;  /**< Write ODT mask DIMM1, RANK0
                                                         if (!RANK_ENA) then WODT_D1_R0[3,1] MBZ
                                                         *Upper 4 bits UNUSED IN 6xxx, and MBZ* */
	uint64_t wodt_d0_r1                   : 8;  /**< Write ODT mask DIMM0, RANK1/DIMM0 in SingleRanked
                                                         if (!RANK_ENA) then WODT_D0_R1[3:0] MBZ
                                                         *Upper 4 bits UNUSED IN 6xxx, and MBZ* */
	uint64_t wodt_d0_r0                   : 8;  /**< Write ODT mask DIMM0, RANK0
                                                         if (!RANK_ENA) then WODT_D0_R0[3,1] MBZ
                                                         *Upper 4 bits UNUSED IN 6xxx, and MBZ* */
#else
	uint64_t wodt_d0_r0                   : 8;
	uint64_t wodt_d0_r1                   : 8;
	uint64_t wodt_d1_r0                   : 8;
	uint64_t wodt_d1_r1                   : 8;
	uint64_t wodt_d2_r0                   : 8;
	uint64_t wodt_d2_r1                   : 8;
	uint64_t wodt_d3_r0                   : 8;
	uint64_t wodt_d3_r1                   : 8;
#endif
	} s;
	struct cvmx_lmcx_wodt_mask_s          cn61xx;
	struct cvmx_lmcx_wodt_mask_s          cn63xx;
	struct cvmx_lmcx_wodt_mask_s          cn63xxp1;
	struct cvmx_lmcx_wodt_mask_s          cn66xx;
	struct cvmx_lmcx_wodt_mask_s          cn68xx;
	struct cvmx_lmcx_wodt_mask_s          cn68xxp1;
	struct cvmx_lmcx_wodt_mask_cn70xx {
#ifdef __BIG_ENDIAN_BITFIELD
	uint64_t reserved_28_63               : 36;
	uint64_t wodt_d1_r1                   : 4;  /**< Reserved. */
	uint64_t reserved_20_23               : 4;
	uint64_t wodt_d1_r0                   : 4;  /**< Reserved. */
	uint64_t reserved_12_15               : 4;
	uint64_t wodt_d0_r1                   : 4;  /**< Write ODT mask DIMM0, RANK1/DIMM0 in SingleRanked. If RANK_ENA=0, WODT_D0_R1<3:0> must be
                                                         zero. */
	uint64_t reserved_4_7                 : 4;
	uint64_t wodt_d0_r0                   : 4;  /**< Write ODT mask DIMM0, RANK0. If RANK_ENA=0, WODT_D0_R0<3,1> must be zero. */
#else
	uint64_t wodt_d0_r0                   : 4;
	uint64_t reserved_4_7                 : 4;
	uint64_t wodt_d0_r1                   : 4;
	uint64_t reserved_12_15               : 4;
	uint64_t wodt_d1_r0                   : 4;
	uint64_t reserved_20_23               : 4;
	uint64_t wodt_d1_r1                   : 4;
	uint64_t reserved_28_63               : 36;
#endif
	} cn70xx;
	struct cvmx_lmcx_wodt_mask_cn70xx     cn78xx;
	struct cvmx_lmcx_wodt_mask_s          cnf71xx;
};
typedef union cvmx_lmcx_wodt_mask cvmx_lmcx_wodt_mask_t;

#endif
