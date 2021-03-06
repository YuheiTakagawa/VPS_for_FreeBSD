/*-
 * Copyright (c) 2004 Mark R V Murray
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: projects/vps/sys/dev/random/probe.c 257008 2013-10-23 19:02:26Z will $");

#if defined(__amd64__) || defined(__i386__)
#include "opt_cpu.h"
#endif

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/selinfo.h>

#include <dev/random/random_adaptors.h>
#include <dev/random/randomdev.h>

void
random_ident_hardware(struct random_adaptor **adaptor)
{
	struct random_adaptor *tmp;
	int enable;

	/* Set default to software (yarrow) */
	*adaptor = random_adaptor_get("yarrow");

	/* Then go looking for hardware */
	enable = 1;
	TUNABLE_INT_FETCH("hw.nehemiah_rng_enable", &enable);
	if (enable && (tmp = random_adaptor_get("nehemiah")))
		*adaptor = tmp;

	enable = 1;
	TUNABLE_INT_FETCH("hw.ivy_rng_enable", &enable);
	if (enable && (tmp = random_adaptor_get("rdrand")))
		*adaptor = tmp;
}
