/*
 * Copyright (c) 2008-2010 Atheros Communications Inc.
 * Copyright (c) 2010-2011 Adrian Chadd, Xenion Pty Ltd.
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
 * $FreeBSD: projects/vps/sys/dev/ath/ath_hal/ar9002/ar9285phy.h 219481 2011-03-11 11:58:54Z adrian $
 */
#ifndef	__ATH_AR9285PHY_H__
#define	__ATH_AR9285PHY_H__

#define AR9285_AN_RF2G1              0x7820
#define AR9285_AN_RF2G1_ENPACAL      0x00000800
#define AR9285_AN_RF2G1_ENPACAL_S    11
#define AR9285_AN_RF2G1_PDPADRV1     0x02000000
#define AR9285_AN_RF2G1_PDPADRV1_S   25
#define AR9285_AN_RF2G1_PDPADRV2     0x01000000
#define AR9285_AN_RF2G1_PDPADRV2_S   24
#define AR9285_AN_RF2G1_PDPAOUT      0x00800000
#define AR9285_AN_RF2G1_PDPAOUT_S    23

#define AR9285_AN_RF2G2              0x7824
#define AR9285_AN_RF2G2_OFFCAL       0x00001000
#define AR9285_AN_RF2G2_OFFCAL_S     12

#define AR9285_AN_RF2G3             0x7828
#define AR9285_AN_RF2G3_PDVCCOMP    0x02000000
#define AR9285_AN_RF2G3_PDVCCOMP_S  25
#define AR9285_AN_RF2G3_OB_0    0x00E00000
#define AR9285_AN_RF2G3_OB_0_S    21
#define AR9285_AN_RF2G3_OB_1    0x001C0000
#define AR9285_AN_RF2G3_OB_1_S    18
#define AR9285_AN_RF2G3_OB_2    0x00038000
#define AR9285_AN_RF2G3_OB_2_S    15
#define AR9285_AN_RF2G3_OB_3    0x00007000
#define AR9285_AN_RF2G3_OB_3_S    12
#define AR9285_AN_RF2G3_OB_4    0x00000E00
#define AR9285_AN_RF2G3_OB_4_S    9

#define AR9285_AN_RF2G3_DB1_0    0x000001C0
#define AR9285_AN_RF2G3_DB1_0_S    6
#define AR9285_AN_RF2G3_DB1_1    0x00000038
#define AR9285_AN_RF2G3_DB1_1_S    3
#define AR9285_AN_RF2G3_DB1_2    0x00000007
#define AR9285_AN_RF2G3_DB1_2_S    0

#define AR9285_AN_RF2G4         0x782C
#define AR9285_AN_RF2G4_DB1_3    0xE0000000
#define AR9285_AN_RF2G4_DB1_3_S    29
#define AR9285_AN_RF2G4_DB1_4    0x1C000000
#define AR9285_AN_RF2G4_DB1_4_S    26

#define AR9285_AN_RF2G4_DB2_0    0x03800000
#define AR9285_AN_RF2G4_DB2_0_S    23
#define AR9285_AN_RF2G4_DB2_1    0x00700000
#define AR9285_AN_RF2G4_DB2_1_S    20
#define AR9285_AN_RF2G4_DB2_2    0x000E0000
#define AR9285_AN_RF2G4_DB2_2_S    17
#define AR9285_AN_RF2G4_DB2_3    0x0001C000
#define AR9285_AN_RF2G4_DB2_3_S    14
#define AR9285_AN_RF2G4_DB2_4    0x00003800
#define AR9285_AN_RF2G4_DB2_4_S    11

#define AR9285_RF2G5                    0x7830
#define AR9285_RF2G5_IC50TX             0xfffff8ff
#define AR9285_RF2G5_IC50TX_SET         0x00000400
#define AR9285_RF2G5_IC50TX_XE_SET      0x00000500
#define AR9285_RF2G5_IC50TX_CLEAR       0x00000700
#define AR9285_RF2G5_IC50TX_CLEAR_S     8

#define AR_PHY_TX_PWRCTRL_TX_GAIN_TAB_MAX   0x0007E000
#define AR_PHY_TX_PWRCTRL_TX_GAIN_TAB_MAX_S 13
#define AR_PHY_TX_GAIN_CLC       0x0000001E
#define AR_PHY_TX_GAIN_CLC_S     1
#define AR_PHY_TX_GAIN           0x0007F000
#define AR_PHY_TX_GAIN_S         12

#define AR_PHY_CLC_TBL1      0xa35c
#define AR_PHY_CLC_I0        0x07ff0000
#define AR_PHY_CLC_I0_S      16
#define AR_PHY_CLC_Q0        0x0000ffd0
#define AR_PHY_CLC_Q0_S      5

#define AR_PHY_MULTICHAIN_GAIN_CTL          0x99ac
#define AR_PHY_9285_FAST_DIV_BIAS           0x00007E00
#define AR_PHY_9285_FAST_DIV_BIAS_S         9
#define AR_PHY_9285_ANT_DIV_CTL_ALL         0x7f000000
#define AR_PHY_9285_ANT_DIV_CTL             0x01000000
#define AR_PHY_9285_ANT_DIV_CTL_S           24
#define AR_PHY_9285_ANT_DIV_ALT_LNACONF     0x06000000
#define AR_PHY_9285_ANT_DIV_ALT_LNACONF_S   25
#define AR_PHY_9285_ANT_DIV_MAIN_LNACONF    0x18000000
#define AR_PHY_9285_ANT_DIV_MAIN_LNACONF_S  27
#define AR_PHY_9285_ANT_DIV_ALT_GAINTB      0x20000000
#define AR_PHY_9285_ANT_DIV_ALT_GAINTB_S    29
#define AR_PHY_9285_ANT_DIV_MAIN_GAINTB     0x40000000
#define AR_PHY_9285_ANT_DIV_MAIN_GAINTB_S   30
#define AR_PHY_9285_ANT_DIV_LNA1            2
#define AR_PHY_9285_ANT_DIV_LNA2            1
#define AR_PHY_9285_ANT_DIV_LNA1_PLUS_LNA2  3
#define AR_PHY_9285_ANT_DIV_LNA1_MINUS_LNA2 0
#define AR_PHY_9285_ANT_DIV_GAINTB_0        0
#define AR_PHY_9285_ANT_DIV_GAINTB_1        1

/* for AR_PHY_CCK_DETECT */
#define AR_PHY_CCK_DETECT_ANT_SWITCH_TIME           0x00001FC0
#define AR_PHY_CCK_DETECT_ANT_SWITCH_TIME_S         6
#define AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV    0x2000
#define AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV_S  13

#endif
