/* Define the machine-dependent type `jmp_buf'.  Ubicom32 version.
   Copyright (C) 1992,93,95,97,2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _BITS_SETJMP_H
#define _BITS_SETJMP_H	1

#if !defined _SETJMP_H && !defined _PTHREAD_H
# error "Never include <bits/setjmp.h> directly; use <setjmp.h> instead."
#endif

#ifndef	_ASM
/*
 * This is the structure where we are going to save D10-D13, A0, A1, A2, A5, A6 and SP(A7).
 * A5 is the return address. Call to setjmp will save these. Call to longjmp will return
 * Control to the address in A5.
 */
typedef struct setjmp_save_struct {
	unsigned long  d10;		/* D10 */
	unsigned long  d11;		/* D11 */
	unsigned long  d12;		/* D12 */
	unsigned long  d13;		/* D13 */
	unsigned long  a1;		/* A1  */
	unsigned long  a2;		/* A2  */
	unsigned long  a5;		/* A5 return address. */
	unsigned long  a6;		/* A6 */
	unsigned long  sp;		/* A7 stack pointer. */
} __jmp_buf[1];

#endif

/* Test if longjmp to JMPBUF would unwind the frame
   containing a local variable at ADDRESS.  */
#define _JMPBUF_UNWINDS(jmpbuf, address) \
  ((void *) (address) < (void*)(jmpbuf)->sp)

#endif	/* bits/setjmp.h */
