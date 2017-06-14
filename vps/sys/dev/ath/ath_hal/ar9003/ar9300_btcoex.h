/*
 * Copyright (c) 2011 Atheros Communications, Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $FreeBSD: projects/vps/sys/dev/ath/ath_hal/ar9003/ar9300_btcoex.h 237611 2012-06-26 22:16:53Z adrian $
 */

#ifndef	__ATH_AR9300_BTCOEX_H__
#define	__ATH_AR9300_BTCOEX_H__
/*
 * Weight table configurations.
 */
#define	AR9300_BT_WGHT				0xcccc4444
#define	AR9300_STOMP_ALL_WLAN_WGHT0		0xfffffff0
#define	AR9300_STOMP_ALL_WLAN_WGHT1		0xfffffff0
#define	AR9300_STOMP_LOW_WLAN_WGHT0		0x88888880
#define	AR9300_STOMP_LOW_WLAN_WGHT1		0x88888880
#define	AR9300_STOMP_NONE_WLAN_WGHT0		0x00000000
#define	AR9300_STOMP_NONE_WLAN_WGHT1		0x00000000
/* Stomp BT even when WLAN is idle */
#define	AR9300_STOMP_ALL_FORCE_WLAN_WGHT0	0xffffffff
#define	AR9300_STOMP_ALL_FORCE_WLAN_WGHT1	0xffffffff
/* Stomp BT even when WLAN is idle */
#define	AR9300_STOMP_LOW_FORCE_WLAN_WGHT0	0x88888888
#define	AR9300_STOMP_LOW_FORCE_WLAN_WGHT1	0x88888888

#define	JUPITER_STOMP_ALL_WLAN_WGHT0		0x00007d00
#define	JUPITER_STOMP_ALL_WLAN_WGHT1		0x7d7d7d00
#define	JUPITER_STOMP_ALL_WLAN_WGHT2		0x7d7d7d00
#define	JUPITER_STOMP_ALL_WLAN_WGHT3		0x7d7d7d7d
#define	JUPITER_STOMP_LOW_WLAN_WGHT0		0x00007d00
#define	JUPITER_STOMP_LOW_WLAN_WGHT1		0x7d3b3b00
#define	JUPITER_STOMP_LOW_WLAN_WGHT2		0x3b3b3b00
#define	JUPITER_STOMP_LOW_WLAN_WGHT3		0x3b3b3b3b
#define	JUPITER_STOMP_NONE_WLAN_WGHT0		0x00007d00
#define	JUPITER_STOMP_NONE_WLAN_WGHT1		0x7d000000
#define	JUPITER_STOMP_NONE_WLAN_WGHT2		0x00000000
#define	JUPITER_STOMP_NONE_WLAN_WGHT3		0x00000000
#define	JUPITER_STOMP_ALL_FORCE_WLAN_WGHT0	0x00007d7d
#define	JUPITER_STOMP_ALL_FORCE_WLAN_WGHT1	0x7d7d7d00
#define	JUPITER_STOMP_ALL_FORCE_WLAN_WGHT2	0x7d7d7d7d
#define	JUPITER_STOMP_ALL_FORCE_WLAN_WGHT3	0x7d7d7d7d
#define	JUPITER_STOMP_LOW_FORCE_WLAN_WGHT0	0x00003b3b
#define	JUPITER_STOMP_LOW_FORCE_WLAN_WGHT1	0x3b3b3b00
#define	JUPITER_STOMP_LOW_FORCE_WLAN_WGHT2	0x3b3b3b3b
#define	JUPITER_STOMP_LOW_FORCE_WLAN_WGHT3	0x3b3b3b3b

#endif	/* __ATH_AR9300_BTCOEX_H__ */