/*-
 * Copyright (c) 2011 Aleksandr Rybalko.
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: projects/vps/sys/dev/etherswitch/arswitch/arswitchreg.h 257008 2013-10-23 19:02:26Z will $
 */

#ifndef __AR8X16_SWITCHREG_H__
#define	__AR8X16_SWITCHREG_H__

/* XXX doesn't belong here; stolen shamelessly from ath_hal/ah_internal.h */
/*
 * Register manipulation macros that expect bit field defines
 * to follow the convention that an _S suffix is appended for
 * a shift count, while the field mask has no suffix.
 */
#define	SM(_v, _f)	(((_v) << _f##_S) & (_f))
#define	MS(_v, _f)	(((_v) & (_f)) >> _f##_S)

/* Atheros specific MII registers */
#define	MII_ATH_DBG_ADDR		0x1d
#define	MII_ATH_DBG_DATA		0x1e

#define	AR8X16_REG_MASK_CTRL		0x0000
#define		AR8X16_MASK_CTRL_REV_MASK	0x000000ff
#define		AR8X16_MASK_CTRL_VER_MASK	0x0000ff00
#define		AR8X16_MASK_CTRL_VER_SHIFT	8
#define		AR8X16_MASK_CTRL_SOFT_RESET	(1 << 31)

#define	AR8X16_REG_MODE			0x0008
/* DIR-615 E4 U-Boot */
#define		AR8X16_MODE_DIR_615_UBOOT	0x8d1003e0
/* From Ubiquiti RSPRO */
#define		AR8X16_MODE_RGMII_PORT4_ISO	0x81461bea
#define		AR8X16_MODE_RGMII_PORT4_SWITCH	0x01261be2
/* AVM Fritz!Box 7390 */
#define		AR8X16_MODE_GMII		0x010e5b71
/* from avm_cpmac/linux_ar_reg.h */
#define		AR8X16_MODE_RESERVED		0x000e1b20
#define		AR8X16_MODE_MAC0_GMII_EN	(1u <<  0)
#define		AR8X16_MODE_MAC0_RGMII_EN	(1u <<  1)
#define		AR8X16_MODE_PHY4_GMII_EN	(1u <<  2)
#define		AR8X16_MODE_PHY4_RGMII_EN	(1u <<  3)
#define		AR8X16_MODE_MAC0_MAC_MODE	(1u <<  4)
#define		AR8X16_MODE_RGMII_RXCLK_DELAY_EN (1u <<  6)
#define		AR8X16_MODE_RGMII_TXCLK_DELAY_EN (1u <<  7)
#define		AR8X16_MODE_MAC5_MAC_MODE	(1u << 14)
#define		AR8X16_MODE_MAC5_PHY_MODE	(1u << 15)
#define		AR8X16_MODE_TXDELAY_S0		(1u << 21)
#define		AR8X16_MODE_TXDELAY_S1		(1u << 22)
#define		AR8X16_MODE_RXDELAY_S0		(1u << 23)
#define		AR8X16_MODE_LED_OPEN_EN		(1u << 24)
#define		AR8X16_MODE_SPI_EN		(1u << 25)
#define		AR8X16_MODE_RXDELAY_S1		(1u << 26)
#define		AR8X16_MODE_POWER_ON_SEL	(1u << 31)

#define	AR8X16_REG_ISR			0x0010
#define	AR8X16_REG_IMR			0x0014

#define	AR8X16_REG_SW_MAC_ADDR0		0x0020
#define	AR8X16_REG_SW_MAC_ADDR1		0x0024

#define	AR8X16_REG_FLOOD_MASK		0x002c
#define		AR8X16_FLOOD_MASK_BCAST_TO_CPU	(1 << 26)

#define	AR8X16_REG_GLOBAL_CTRL		0x0030
#define		AR8216_GLOBAL_CTRL_MTU_MASK	0x00000fff
#define		AR8216_GLOBAL_CTRL_MTU_MASK_S	0
#define		AR8316_GLOBAL_CTRL_MTU_MASK	0x00007fff
#define		AR8316_GLOBAL_CTRL_MTU_MASK_S	0
#define		AR8236_GLOBAL_CTRL_MTU_MASK	0x00007fff
#define		AR8236_GLOBAL_CTRL_MTU_MASK_S	0
#define		AR7240_GLOBAL_CTRL_MTU_MASK	0x00003fff
#define		AR7240_GLOBAL_CTRL_MTU_MASK_S	0

#define	AR8X16_REG_VLAN_CTRL			0x0040
#define		AR8X16_VLAN_OP			0x00000007
#define		AR8X16_VLAN_OP_NOOP		0x0
#define		AR8X16_VLAN_OP_FLUSH		0x1
#define		AR8X16_VLAN_OP_LOAD		0x2
#define		AR8X16_VLAN_OP_PURGE		0x3
#define		AR8X16_VLAN_OP_REMOVE_PORT	0x4
#define		AR8X16_VLAN_OP_GET_NEXT		0x5
#define		AR8X16_VLAN_OP_GET		0x6
#define		AR8X16_VLAN_ACTIVE		(1 << 3)
#define		AR8X16_VLAN_FULL		(1 << 4)
#define		AR8X16_VLAN_PORT		0x00000f00
#define		AR8X16_VLAN_PORT_SHIFT		8
#define		AR8X16_VLAN_VID			0x0fff0000
#define		AR8X16_VLAN_VID_SHIFT		16
#define		AR8X16_VLAN_PRIO		0x70000000
#define		AR8X16_VLAN_PRIO_SHIFT		28
#define		AR8X16_VLAN_PRIO_EN		(1 << 31)

#define	AR8X16_REG_VLAN_DATA		0x0044
#define		AR8X16_VLAN_MEMBER		0x0000003f
#define		AR8X16_VLAN_VALID		(1 << 11)

#define	AR8X16_REG_ARL_CTRL0		0x0050
#define	AR8X16_REG_ARL_CTRL1		0x0054
#define	AR8X16_REG_ARL_CTRL2		0x0058

#define	AR8X16_REG_AT_CTRL		0x005c
#define		AR8X16_AT_CTRL_ARP_EN		(1 << 20)

#define	AR8X16_REG_IP_PRIORITY_1     	0x0060
#define	AR8X16_REG_IP_PRIORITY_2     	0x0064
#define	AR8X16_REG_IP_PRIORITY_3     	0x0068
#define	AR8X16_REG_IP_PRIORITY_4     	0x006C

#define	AR8X16_REG_TAG_PRIO		0x0070

#define	AR8X16_REG_SERVICE_TAG		0x0074
#define		AR8X16_SERVICE_TAG_MASK		0x0000ffff

#define	AR8X16_REG_CPU_PORT		0x0078
#define		AR8X16_MIRROR_PORT_SHIFT	4
#define		AR8X16_MIRROR_PORT_MASK		(0xf << AR8X16_MIRROR_PORT_SHIFT)
#define		AR8X16_CPU_MIRROR_PORT(_p)	((_p) << AR8X16_MIRROR_PORT_SHIFT)
#define		AR8X16_CPU_MIRROR_DIS		AR8X16_CPU_MIRROR_PORT(0xf)
#define		AR8X16_CPU_PORT_EN		(1 << 8)

#define	AR8X16_REG_MIB_FUNC0		0x0080
#define		AR8X16_MIB_TIMER_MASK		0x0000ffff
#define		AR8X16_MIB_AT_HALF_EN		(1 << 16)
#define		AR8X16_MIB_BUSY			(1 << 17)
#define		AR8X16_MIB_FUNC_SHIFT		24
#define		AR8X16_MIB_FUNC_NO_OP		0x0
#define		AR8X16_MIB_FUNC_FLUSH		0x1
#define		AR8X16_MIB_FUNC_CAPTURE		0x3
#define		AR8X16_MIB_FUNC_XXX		(1 << 30) /* 0x40000000 */

#define	AR8X16_REG_MDIO_HIGH_ADDR	0x0094

#define	AR8X16_REG_MDIO_CTRL		0x0098
#define		AR8X16_MDIO_CTRL_DATA_MASK	0x0000ffff
#define		AR8X16_MDIO_CTRL_REG_ADDR_SHIFT	16
#define		AR8X16_MDIO_CTRL_PHY_ADDR_SHIFT	21
#define		AR8X16_MDIO_CTRL_CMD_WRITE	0
#define		AR8X16_MDIO_CTRL_CMD_READ	(1 << 27)
#define		AR8X16_MDIO_CTRL_MASTER_EN	(1 << 30)
#define		AR8X16_MDIO_CTRL_BUSY		(1 << 31)

#define	AR8X16_REG_PORT_BASE(_p)	(0x0100 + (_p) * 0x0100)

#define	AR8X16_REG_PORT_STS(_p)		(AR8X16_REG_PORT_BASE((_p)) + 0x0000)
#define		AR8X16_PORT_STS_SPEED_MASK	0x00000003
#define		AR8X16_PORT_STS_SPEED_10	0
#define		AR8X16_PORT_STS_SPEED_100	1
#define		AR8X16_PORT_STS_SPEED_1000	2
#define		AR8X16_PORT_STS_TXMAC		(1 << 2)
#define		AR8X16_PORT_STS_RXMAC		(1 << 3)
#define		AR8X16_PORT_STS_TXFLOW		(1 << 4)
#define		AR8X16_PORT_STS_RXFLOW		(1 << 5)
#define		AR8X16_PORT_STS_DUPLEX		(1 << 6)
#define		AR8X16_PORT_STS_LINK_UP		(1 << 8)
#define		AR8X16_PORT_STS_LINK_AUTO	(1 << 9)
#define		AR8X16_PORT_STS_LINK_PAUSE	(1 << 10)

#define	AR8X16_REG_PORT_CTRL(_p)	(AR8X16_REG_PORT_BASE((_p)) + 0x0004)
#define		AR8X16_PORT_CTRL_STATE_MASK	0x00000007
#define		AR8X16_PORT_CTRL_STATE_DISABLED	0
#define		AR8X16_PORT_CTRL_STATE_BLOCK	1
#define		AR8X16_PORT_CTRL_STATE_LISTEN	2
#define		AR8X16_PORT_CTRL_STATE_LEARN	3
#define		AR8X16_PORT_CTRL_STATE_FORWARD	4
#define		AR8X16_PORT_CTRL_LEARN_LOCK	(1 << 7)
#define		AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_SHIFT 8
#define		AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_KEEP	0
#define		AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_STRIP 1
#define		AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_ADD 2
#define		AR8X16_PORT_CTRL_EGRESS_VLAN_MODE_DOUBLE_TAG 3
#define		AR8X16_PORT_CTRL_IGMP_SNOOP	(1 << 10)
#define		AR8X16_PORT_CTRL_HEADER		(1 << 11)
#define		AR8X16_PORT_CTRL_MAC_LOOP	(1 << 12)
#define		AR8X16_PORT_CTRL_SINGLE_VLAN	(1 << 13)
#define		AR8X16_PORT_CTRL_LEARN		(1 << 14)
#define		AR8X16_PORT_CTRL_DOUBLE_TAG	(1 << 15)
#define		AR8X16_PORT_CTRL_MIRROR_TX	(1 << 16)
#define		AR8X16_PORT_CTRL_MIRROR_RX	(1 << 17)

#define	AR8X16_REG_PORT_VLAN(_p)	(AR8X16_REG_PORT_BASE((_p)) + 0x0008)

#define		AR8X16_PORT_VLAN_DEFAULT_ID_SHIFT	0
#define		AR8X16_PORT_VLAN_DEST_PORTS_SHIFT	16
#define		AR8X16_PORT_VLAN_MODE_MASK		0xc0000000
#define		AR8X16_PORT_VLAN_MODE_SHIFT		30
#define		AR8X16_PORT_VLAN_MODE_PORT_ONLY		0
#define		AR8X16_PORT_VLAN_MODE_PORT_FALLBACK	1
#define		AR8X16_PORT_VLAN_MODE_VLAN_ONLY		2
#define		AR8X16_PORT_VLAN_MODE_SECURE		3

#define	AR8X16_REG_PORT_RATE_LIM(_p)	(AR8X16_REG_PORT_BASE((_p)) + 0x000c)
#define		AR8X16_PORT_RATE_LIM_128KB	0
#define		AR8X16_PORT_RATE_LIM_256KB	1
#define		AR8X16_PORT_RATE_LIM_512KB	2
#define		AR8X16_PORT_RATE_LIM_1MB	3
#define		AR8X16_PORT_RATE_LIM_2MB	4
#define		AR8X16_PORT_RATE_LIM_4MB	5
#define		AR8X16_PORT_RATE_LIM_8MB	6
#define		AR8X16_PORT_RATE_LIM_16MB	7
#define		AR8X16_PORT_RATE_LIM_32MB	8
#define		AR8X16_PORT_RATE_LIM_64MB	9
#define		AR8X16_PORT_RATE_LIM_IN_EN	(1 << 24)
#define		AR8X16_PORT_RATE_LIM_OUT_EN	(1 << 23)
#define		AR8X16_PORT_RATE_LIM_IN_MASK	0x000f0000
#define		AR8X16_PORT_RATE_LIM_IN_SHIFT	16
#define		AR8X16_PORT_RATE_LIM_OUT_MASK	0x0000000f
#define		AR8X16_PORT_RATE_LIM_OUT_SHIFT	0

#define	AR8X16_REG_PORT_PRIORITY(_p)	(AR8X16_REG_PORT_BASE((_p)) + 0x0010)

#define	AR8X16_REG_STATS_BASE(_p)	(0x20000 + (_p) * 0x100)

#define	AR8X16_STATS_RXBROAD		0x0000
#define	AR8X16_STATS_RXPAUSE		0x0004
#define	AR8X16_STATS_RXMULTI		0x0008
#define	AR8X16_STATS_RXFCSERR		0x000c
#define	AR8X16_STATS_RXALIGNERR		0x0010
#define	AR8X16_STATS_RXRUNT		0x0014
#define	AR8X16_STATS_RXFRAGMENT		0x0018
#define	AR8X16_STATS_RX64BYTE		0x001c
#define	AR8X16_STATS_RX128BYTE		0x0020
#define	AR8X16_STATS_RX256BYTE		0x0024
#define	AR8X16_STATS_RX512BYTE		0x0028
#define	AR8X16_STATS_RX1024BYTE		0x002c
#define	AR8X16_STATS_RX1518BYTE		0x0030
#define	AR8X16_STATS_RXMAXBYTE		0x0034
#define	AR8X16_STATS_RXTOOLONG		0x0038
#define	AR8X16_STATS_RXGOODBYTE		0x003c
#define	AR8X16_STATS_RXBADBYTE		0x0044
#define	AR8X16_STATS_RXOVERFLOW		0x004c
#define	AR8X16_STATS_FILTERED		0x0050
#define	AR8X16_STATS_TXBROAD		0x0054
#define	AR8X16_STATS_TXPAUSE		0x0058
#define	AR8X16_STATS_TXMULTI		0x005c
#define	AR8X16_STATS_TXUNDERRUN		0x0060
#define	AR8X16_STATS_TX64BYTE		0x0064
#define	AR8X16_STATS_TX128BYTE		0x0068
#define	AR8X16_STATS_TX256BYTE		0x006c
#define	AR8X16_STATS_TX512BYTE		0x0070
#define	AR8X16_STATS_TX1024BYTE		0x0074
#define	AR8X16_STATS_TX1518BYTE		0x0078
#define	AR8X16_STATS_TXMAXBYTE		0x007c
#define	AR8X16_STATS_TXOVERSIZE		0x0080
#define	AR8X16_STATS_TXBYTE		0x0084
#define	AR8X16_STATS_TXCOLLISION	0x008c
#define	AR8X16_STATS_TXABORTCOL		0x0090
#define	AR8X16_STATS_TXMULTICOL		0x0094
#define	AR8X16_STATS_TXSINGLECOL	0x0098
#define	AR8X16_STATS_TXEXCDEFER		0x009c
#define	AR8X16_STATS_TXDEFER		0x00a0
#define	AR8X16_STATS_TXLATECOL		0x00a4

#define	AR8X16_PORT_CPU			0
#define	AR8X16_NUM_PORTS		6
#define	AR8X16_NUM_PHYS			5
#define	AR8X16_MAGIC			0xc000050e

#define	AR8X16_PHY_ID1			0x004d
#define	AR8X16_PHY_ID2			0xd041

#define	AR8X16_PORT_MASK(_port)		(1 << (_port))
#define	AR8X16_PORT_MASK_ALL		((1<<AR8X16_NUM_PORTS)-1)
#define	AR8X16_PORT_MASK_BUT(_port)	(AR8X16_PORT_MASK_ALL & ~(1 << (_port)))

#define	AR8X16_MAX_VLANS		16

#endif /* __AR8X16_SWITCHREG_H__ */

