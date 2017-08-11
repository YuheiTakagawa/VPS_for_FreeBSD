/*-
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY BROADCOM ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BROADCOM OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: projects/vps/sys/mips/nlm/dev/net/ucore/ucore_app.c 233657 2012-03-29 11:46:29Z jchandra $
 */

#include "ucore.h"

int main(void)
{
#if 0
	volatile unsigned int *pkt = 
	    (volatile unsigned int *) (PACKET_MEMORY + PACKET_DATA_OFFSET);
	int intf, hw_parser_error, context;
#endif
	unsigned int pktrdy;
	int num_cachelines = 1518 / 64 ; /* pktsize / L3 cacheline size */


	/* Spray packets to using distribution vector */
	while (1) {
		pktrdy = nlm_read_ucore_rxpktrdy();
#if 0
		intf = pktrdy & 0x1f;
		context = (pktrdy >> 13) & 0x3ff;
		hw_parser_error = (pktrdy >> 23) & 0x1;
#endif
		nlm_ucore_setup_poepktdistr(FWD_DIST_VEC, 0, 0, 0, 0);
		nlm_ucore_pkt_done(num_cachelines, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		    0, 0);
	}

	return (0);
}
