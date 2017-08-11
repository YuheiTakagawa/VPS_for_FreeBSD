/*-
 * Copyright 2001 by Thomas Moestl <tmm@FreeBSD.org>.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: projects/vps/sys/sparc64/include/tstate.h 88631 2001-12-29 07:11:00Z jake $
 */

#ifndef	_MACHINE_TSTATE_H_
#define	_MACHINE_TSTATE_H_

#include <machine/pstate.h>
#include <machine/ccr.h>

#define	TSTATE_CWP_SHIFT	0
#define	TSTATE_CWP_BITS		5
#define	TSTATE_CWP_MASK \
	(((1 << TSTATE_CWP_BITS) - 1) << TSTATE_CWP_SHIFT)
#define	TSTATE_CWP(x)		((x & TSTATE_CWP_MASK) >> TSTATE_CWP_SHIFT)

#define	TSTATE_PSTATE_SHIFT	8
#define	TSTATE_PSTATE_BITS	12
#define	TSTATE_PSTATE_MASK \
	(((1 << TSTATE_PSTATE_BITS) - 1) << TSTATE_PSTATE_SHIFT)
#define	TSTATE_PSTATE(x)	((x) << TSTATE_PSTATE_SHIFT)
#define	TSTATE_AG		TSTATE_PSTATE(PSTATE_AG)
#define	TSTATE_IE		TSTATE_PSTATE(PSTATE_IE)
#define	TSTATE_PRIV		TSTATE_PSTATE(PSTATE_PRIV)
#define	TSTATE_AM		TSTATE_PSTATE(PSTATE_AM)
#define	TSTATE_PEF		TSTATE_PSTATE(PSTATE_PEF)
#define	TSTATE_RED		TSTATE_PSTATE(PSTATE_RED)
#define	TSTATE_MM_TSO		TSTATE_PSTATE(PSTATE_MM_TSO)
#define	TSTATE_MM_PSO		TSTATE_PSTATE(PSTATE_MM_PSO)
#define	TSTATE_MM_RMO		TSTATE_PSTATE(PSTATE_MM_RMO)
#define	TSTATE_TLE		TSTATE_PSTATE(PSTATE_TLE)
#define	TSTATE_CLE		TSTATE_PSTATE(PSTATE_CLE)
#define	TSTATE_MG		TSTATE_PSTATE(PSTATE_MG)
#define	TSTATE_IG		TSTATE_PSTATE(PSTATE_IG)

#define	TSTATE_ASI_SHIFT	24
#define	TSTATE_ASI_BITS		8
#define	TSTATE_ASI_MASK	\
	(((1 << TSTATE_ASI_BITS) - 1) << TSTATE_ASI_SHIFT)
#define	TSTATE_ASI(x)		((x & TSTATE_ASI_MASK) >> TSTATE_ASI_SHIFT)

#define	TSTATE_CCR_SHIFT	32
#define	TSTATE_ICC_SHIFT	(TSTATE_CCR_SHIFT + ICC_SHIFT)
#define	TSTATE_ICC_MASK		(ICC_MASK << TSTATE_CCR_SHIFT)
#define	TSTATE_XCC_SHIFT	(TSTATE_CCR_SHIFT + XCC_SHIFT)
#define	TSTATE_XCC_MASK		(XCC_MASK << TSTATE_CCR_SHIFT)
#define	TSTATE_CCR(x)		((x) << TSTATE_CCR_SHIFT)
#define	TSTATE_ICC_C		TSTATE_CCR(ICC_C)
#define	TSTATE_ICC_V		TSTATE_CCR(ICC_V)
#define	TSTATE_ICC_Z		TSTATE_CCR(ICC_Z)
#define	TSTATE_ICC_N		TSTATE_CCR(ICC_N)
#define	TSTATE_XCC_C		TSTATE_CCR(XCC_C)
#define	TSTATE_XCC_V		TSTATE_CCR(XCC_V)
#define	TSTATE_XCC_Z		TSTATE_CCR(XCC_Z)
#define	TSTATE_XCC_N		TSTATE_CCR(XCC_N)

#define	TSTATE_SECURE(tstate) \
	PSTATE_SECURE(((tstate) >> TSTATE_PSTATE_SHIFT) & ((1 << TSTATE_PSTATE_BITS) - 1))

#endif /* !_MACHINE_TSTATE_H_ */
