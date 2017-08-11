/*	$NetBSD: imx51_ipuv3reg.h,v 1.1 2012/04/17 10:19:57 bsh Exp $	*/
/*
 * Copyright (c) 2011, 2012  Genetec Corporation.  All rights reserved.
 * Written by Hashimoto Kenichi for Genetec Corporation.
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
 * THIS SOFTWARE IS PROVIDED BY GENETEC CORPORATION ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL GENETEC CORPORATION
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*-
 * Copyright (c) 2012, 2013 The FreeBSD Foundation
 * All rights reserved.
 *
 * Portions of this software were developed by Oleksandr Rybalko
 * under sponsorship from the FreeBSD Foundation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.	Redistributions of source code must retain the above copyright
 *	notice, this list of conditions and the following disclaimer.
 * 2.	Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: projects/vps/sys/arm/freescale/imx/imx51_ipuv3reg.h 250357 2013-05-08 09:42:50Z ray $
 */

#ifndef _ARM_IMX_IMX51_IPUV3REG_H
#define _ARM_IMX_IMX51_IPUV3REG_H

/* register offset address */

/*
 * CM
 * Control Module
 */
#define IPU_CM_CONF			0x00000000
#define  CM_CONF_CSI_SEL		0x80000000
#define  CM_CONF_IC_INPUT		0x40000000
#define  CM_CONF_CSI1_DATA_SOURCE	0x20000000
#define  CM_CONF_CSI0_DATA_SOURCE	0x10000000
#define  CM_CONF_VDI_DMFC_SYNC		0x08000000
#define  CM_CONF_IC_DMFC_SYNC		0x04000000
#define  CM_CONF_IC_DMFC_SEL		0x02000000
#define  CM_CONF_ISP_DOUBLE_FLOW	0x01000000
#define  CM_CONF_IDMAC_DISABLE		0x00400000
#define  CM_CONF_IPU_DIAGBUS_ON		0x00200000
#define  CM_CONF_IPU_DIAGBUS_MODE	0x001f0000
#define  CM_CONF_VDI_EN			0x00001000
#define  CM_CONF_SISG_EN		0x00000800
#define  CM_CONF_DMFC_EN		0x00000400
#define  CM_CONF_DC_EN			0x00000200
#define  CM_CONF_SMFC_EN		0x00000100
#define  CM_CONF_DI1_EN			0x00000080
#define  CM_CONF_DI0_EN			0x00000040
#define  CM_CONF_DP_EN			0x00000020
#define  CM_CONF_ISP_EN			0x00000010
#define  CM_CONF_IRT_EN			0x00000008
#define  CM_CONF_IC_EN			0x00000004
#define  CM_CONF_CSI1_EN		0x00000002
#define  CM_CONF_CSI0_EN		0x00000001
#define IPU_SISG_CTRL0			0x00000004
#define IPU_SISG_CTRL1			0x00000008
#define IPU_CM_INT_CTRL_1		0x0000003c
#define IPU_CM_INT_CTRL_2		0x00000040
#define IPU_CM_INT_CTRL_3		0x00000044
#define IPU_CM_INT_CTRL_4		0x00000048
#define IPU_CM_INT_CTRL_5		0x0000004c
#define IPU_CM_INT_CTRL_6		0x00000050
#define IPU_CM_INT_CTRL_7		0x00000054
#define IPU_CM_INT_CTRL_8		0x00000058
#define IPU_CM_INT_CTRL_9		0x0000005c
#define IPU_CM_INT_CTRL_10		0x00000060
#define IPU_CM_INT_CTRL_11		0x00000064
#define IPU_CM_INT_CTRL_12		0x00000068
#define IPU_CM_INT_CTRL_13		0x0000006c
#define IPU_CM_INT_CTRL_14		0x00000070
#define IPU_CM_INT_CTRL_15		0x00000074
#define IPU_CM_SDMA_EVENT_1		0x00000078
#define IPU_CM_SDMA_EVENT_2		0x0000007c
#define IPU_CM_SDMA_EVENT_3		0x00000080
#define IPU_CM_SDMA_EVENT_4		0x00000084
#define IPU_CM_SDMA_EVENT_7		0x00000088
#define IPU_CM_SDMA_EVENT_8		0x0000008c
#define IPU_CM_SDMA_EVENT_11		0x00000090
#define IPU_CM_SDMA_EVENT_12		0x00000094
#define IPU_CM_SDMA_EVENT_13		0x00000098
#define IPU_CM_SDMA_EVENT_14		0x0000009c
#define IPU_CM_SRM_PRI1			0x000000a0
#define IPU_CM_SRM_PRI2			0x000000a4
#define IPU_CM_FS_PROC_FLOW1		0x000000a8
#define IPU_CM_FS_PROC_FLOW2		0x000000ac
#define IPU_CM_FS_PROC_FLOW3		0x000000b0
#define IPU_CM_FS_DISP_FLOW1		0x000000b4
#define IPU_CM_FS_DISP_FLOW2		0x000000b8
#define IPU_CM_SKIP			0x000000bc
#define IPU_CM_DISP_ALT_CONF		0x000000c0
#define IPU_CM_DISP_GEN			0x000000c4
#define  CM_DISP_GEN_DI0_COUNTER_RELEASE	0x01000000
#define  CM_DISP_GEN_DI1_COUNTER_RELEASE	0x00800000
#define  CM_DISP_GEN_MCU_MAX_BURST_STOP		0x00400000
#define  CM_DISP_GEN_MCU_T_SHIFT		18
#define  CM_DISP_GEN_MCU_T(n)		((n) << CM_DISP_GEN_MCU_T_SHIFT)
#define IPU_CM_DISP_ALT1		0x000000c8
#define IPU_CM_DISP_ALT2		0x000000cc
#define IPU_CM_DISP_ALT3		0x000000d0
#define IPU_CM_DISP_ALT4		0x000000d4
#define IPU_CM_SNOOP			0x000000d8
#define IPU_CM_MEM_RST			0x000000dc
#define  CM_MEM_START			0x80000000
#define  CM_MEM_EN			0x007fffff
#define IPU_CM_PM			0x000000e0
#define IPU_CM_GPR			0x000000e4
#define  CM_GPR_IPU_CH_BUF1_RDY1_CLR		0x80000000
#define  CM_GPR_IPU_CH_BUF1_RDY0_CLR		0x40000000
#define  CM_GPR_IPU_CH_BUF0_RDY1_CLR		0x20000000
#define  CM_GPR_IPU_CH_BUF0_RDY0_CLR		0x10000000
#define  CM_GPR_IPU_ALT_CH_BUF1_RDY1_CLR	0x08000000
#define  CM_GPR_IPU_ALT_CH_BUF1_RDY0_CLR	0x04000000
#define  CM_GPR_IPU_ALT_CH_BUF0_RDY1_CLR	0x02000000
#define  CM_GPR_IPU_ALT_CH_BUF0_RDY0_CLR	0x01000000
#define  CM_GPR_IPU_DI1_CLK_CHANGE_ACK_DIS	0x00800000
#define  CM_GPR_IPU_DI0_CLK_CHANGE_ACK_DIS	0x00400000
#define  CM_GPR_IPU_CH_BUF2_RDY1_CLR		0x00200000
#define  CM_GPR_IPU_CH_BUF2_RDY0_CLR		0x00100000
#define  CM_GPR_IPU_GP(n)			__BIT((n))
#define IPU_CM_CH_DB_MODE_SEL_0		0x00000150
#define IPU_CM_CH_DB_MODE_SEL_1		0x00000154
#define IPU_CM_ALT_CH_DB_MODE_SEL_0	0x00000168
#define IPU_CM_ALT_CH_DB_MODE_SEL_1	0x0000016c
#define IPU_CM_CH_TRB_MODE_SEL_0	0x00000178
#define IPU_CM_CH_TRB_MODE_SEL_1	0x0000017c
#define IPU_CM_INT_STAT_1		0x00000200
#define IPU_CM_INT_STAT_2		0x00000204
#define IPU_CM_INT_STAT_3		0x00000208
#define IPU_CM_INT_STAT_4		0x0000020c
#define IPU_CM_INT_STAT_5		0x00000210
#define IPU_CM_INT_STAT_6		0x00000214
#define IPU_CM_INT_STAT_7		0x00000218
#define IPU_CM_INT_STAT_8		0x0000021c
#define IPU_CM_INT_STAT_9		0x00000220
#define IPU_CM_INT_STAT_10		0x00000224
#define IPU_CM_INT_STAT_11		0x00000228
#define IPU_CM_INT_STAT_12		0x0000022c
#define IPU_CM_INT_STAT_13		0x00000230
#define IPU_CM_INT_STAT_14		0x00000234
#define IPU_CM_INT_STAT_15		0x00000238
#define IPU_CM_CUR_BUF_0		0x0000023c
#define IPU_CM_CUR_BUF_1		0x00000240
#define IPU_CM_ALT_CUR_BUF_0		0x00000244
#define IPU_CM_ALT_CUR_BUF_1		0x00000248
#define IPU_CM_SRM_STAT			0x0000024c
#define IPU_CM_PROC_TASKS_STAT		0x00000250
#define IPU_CM_DISP_TASKS_STAT		0x00000254
#define IPU_CM_TRIPLE_CUR_BUF_0		0x00000258
#define IPU_CM_TRIPLE_CUR_BUF_1		0x0000025c
#define IPU_CM_TRIPLE_CUR_BUF_2		0x00000260
#define IPU_CM_TRIPLE_CUR_BUF_3		0x00000264
#define IPU_CM_CH_BUF0_RDY0		0x00000268
#define IPU_CM_CH_BUF0_RDY1		0x0000026c
#define IPU_CM_CH_BUF1_RDY0		0x00000270
#define IPU_CM_CH_BUF1_RDY1		0x00000274
#define IPU_CM_ALT_CH_BUF0_RDY0		0x00000278
#define IPU_CM_ALT_CH_BUF0_RDY1		0x0000027c
#define IPU_CM_ALT_CH_BUF1_RDY0		0x00000280
#define IPU_CM_ALT_CH_BUF1_RDY1		0x00000284
#define IPU_CM_CH_BUF2_RDY0		0x00000288
#define IPU_CM_CH_BUF2_RDY1		0x0000028c

/*
 * IDMAC
 * Image DMA Controller
 */
#define IPU_IDMAC_CONF		0x00000000
#define IPU_IDMAC_CH_EN_1	0x00000004
#define IPU_IDMAC_CH_EN_2	0x00000008
#define IPU_IDMAC_SEP_ALPHA	0x0000000c
#define IPU_IDMAC_ALT_SEP_ALPHA	0x00000010
#define IPU_IDMAC_CH_PRI_1	0x00000014
#define IPU_IDMAC_CH_PRI_2	0x00000018
#define IPU_IDMAC_WM_EN_1	0x0000001c
#define IPU_IDMAC_WM_EN_2	0x00000020
#define IPU_IDMAC_LOCK_EN_1	0x00000024
#define IPU_IDMAC_LOCK_EN_2	0x00000028
#define IPU_IDMAC_SUB_ADDR_0	0x0000002c
#define IPU_IDMAC_SUB_ADDR_1	0x00000030
#define IPU_IDMAC_SUB_ADDR_2	0x00000034
#define IPU_IDMAC_SUB_ADDR_3	0x00000038
#define IPU_IDMAC_SUB_ADDR_4	0x0000003c
#define IPU_IDMAC_BNDM_EN_1	0x00000040
#define IPU_IDMAC_BNDM_EN_2	0x00000044
#define IPU_IDMAC_SC_CORD	0x00000048
#define IPU_IDMAC_SC_CORD1	0x0000004c
#define IPU_IDMAC_CH_BUSY_1	0x00000100
#define IPU_IDMAC_CH_BUSY_2	0x00000104

#define CH_PANNEL_BG	23
#define CH_PANNEL_FG	27

/*
 * DP
 * Display Port
 */
#define IPU_DP_DEBUG_CNT	0x000000bc
#define IPU_DP_DEBUG_STAT	0x000000c0

/*
 * IC
 * Image Converter
 */
#define IPU_IC_CONF		0x00000000
#define IPU_IC_PRP_ENC_RSC	0x00000004
#define IPU_IC_PRP_VF_RSC	0x00000008
#define IPU_IC_PP_RSC		0x0000000c
#define IPU_IC_CMBP_1		0x00000010
#define IPU_IC_CMBP_2		0x00000014
#define IPU_IC_IDMAC_1		0x00000018
#define IPU_IC_IDMAC_2		0x0000001c
#define IPU_IC_IDMAC_3		0x00000020
#define IPU_IC_IDMAC_4		0x00000024

/*
 * CSI
 * Camera Sensor Interface
 */
#define IPU_CSI0_SENS_CONF	0x00000000
#define IPU_CSI0_SENS_FRM_SIZE	0x00000004
#define IPU_CSI0_ACT_FRM_SIZE	0x00000008
#define IPU_CSI0_OUT_FRM_CTRL	0x0000000c
#define IPU_CSI0_TST_CTRL	0x00000010
#define IPU_CSI0_CCIR_CODE_1	0x00000014
#define IPU_CSI0_CCIR_CODE_2	0x00000018
#define IPU_CSI0_CCIR_CODE_3	0x0000001c
#define IPU_CSI0_DI		0x00000020
#define IPU_CSI0_SKIP		0x00000024
#define IPU_CSI0_CPD_CTRL	0x00000028
#define IPU_CSI0_CPD_OFFSET1	0x000000ec
#define IPU_CSI0_CPD_OFFSET2	0x000000f0

#define IPU_CSI1_SENS_CONF	0x00000000
#define IPU_CSI1_SENS_FRM_SIZE	0x00000004
#define IPU_CSI1_ACT_FRM_SIZE	0x00000008
#define IPU_CSI1_OUT_FRM_CTRL	0x0000000c
#define IPU_CSI1_TST_CTRL	0x00000010
#define IPU_CSI1_CCIR_CODE_1	0x00000014
#define IPU_CSI1_CCIR_CODE_2	0x00000018
#define IPU_CSI1_CCIR_CODE_3	0x0000001c
#define IPU_CSI1_DI		0x00000020
#define IPU_CSI1_SKIP		0x00000024
#define IPU_CSI1_CPD_CTRL	0x00000028
#define IPU_CSI1_CPD_OFFSET1	0x000000ec
#define IPU_CSI1_CPD_OFFSET2	0x000000f0

/*
 * DI
 * Display Interface
 */
#define IPU_DI_GENERAL			0x00000000
#define  DI_GENERAL_DISP_Y_SEL		0x70000000
#define  DI_GENERAL_CLOCK_STOP_MODE	0x0f000000
#define  DI_GENERAL_DISP_CLOCK_INIT	0x00800000
#define  DI_GENERAL_MASK_SEL		0x00400000
#define  DI_GENERAL_VSYNC_EXT		0x00200000
#define  DI_GENERAL_CLK_EXT		0x00100000
#define  DI_GENERAL_WATCHDOG_MODE	0x000c0000
#define  DI_GENERAL_POLARITY_DISP_CLK	0x00020000
#define  DI_GENERAL_SYNC_COUNT_SEL	0x0000f000
#define  DI_GENERAL_ERR_TREATMENT	0x00000800
#define  DI_GENERAL_ERM_VSYNC_SEL	0x00000400
#define  DI_GENERAL_POLARITY_CS(n)	(1 << ((n) + 8))
#define  DI_GENERAL_POLARITY(n)		(1 << ((n) - 1))

#define IPU_DI_BS_CLKGEN0		0x00000004
#define  DI_BS_CLKGEN0_OFFSET_SHIFT	16
#define IPU_DI_BS_CLKGEN1		0x00000008
#define  DI_BS_CLKGEN1_DOWN_SHIFT	16
#define  DI_BS_CLKGEN1_UP_SHIFT		0
#define IPU_DI_SW_GEN0(n)		(0x0000000c + ((n) - 1) * 4)
#define  DI_SW_GEN0_RUN_VAL		0x7ff80000
#define  DI_SW_GEN0_RUN_RESOL		0x00070000
#define  DI_SW_GEN0_OFFSET_VAL		0x00007ff8
#define  DI_SW_GEN0_OFFSET_RESOL	0x00000007
#define  __DI_SW_GEN0(run_val, run_resol, offset_val, offset_resol)	\
	(((run_val) << 19) | ((run_resol) << 16) | 			\
	 ((offset_val) << 3) | (offset_resol))
#define IPU_DI_SW_GEN1(n)		(0x00000030 + ((n) - 1) * 4)
#define  DI_SW_GEN1_CNT_POL_GEN_EN	0x60000000
#define  DI_SW_GEN1_CNT_AUTO_RELOAD	0x10000000
#define  DI_SW_GEN1_CNT_CLR_SEL		0x0e000000
#define  DI_SW_GEN1_CNT_DOWN		0x01ff0000
#define  DI_SW_GEN1_CNT_POL_TRIG_SEL	0x00007000
#define  DI_SW_GEN1_CNT_POL_CLR_SEL	0x00000e00
#define  DI_SW_GEN1_CNT_UP		0x000001ff
#define  __DI_SW_GEN1(pol_gen_en, auto_reload, clr_sel, down, pol_trig_sel, pol_clr_sel, up) \
	(((pol_gen_en) << 29) | ((auto_reload) << 28) | \
	 ((clr_sel) << 25) |				\
	    ((down) << 16) | ((pol_trig_sel) << 12) |	\
	 ((pol_clr_sel) << 9) | (up))
#define IPU_DI_SYNC_AS_GEN		0x00000054
#define  DI_SYNC_AS_GEN_SYNC_START_EN	0x10000000
#define  DI_SYNC_AS_GEN_VSYNC_SEL	0x0000e000
#define  DI_SYNC_AS_GEN_VSYNC_SEL_SHIFT	13
#define  DI_SYNC_AS_GEN_SYNC_STAR	0x00000fff
#define IPU_DI_DW_GEN(n)		(0x00000058 + (n) * 4)
#define  DI_DW_GEN_ACCESS_SIZE_SHIFT		24
#define  DI_DW_GEN_COMPONNENT_SIZE_SHIFT	16
#define  DI_DW_GEN_PIN_SHIFT(n)			(((n) - 11) * 2)
#define  DI_DW_GEN_PIN(n)		__BITS(DI_DW_GEN_PIN_SHIFT(n) + 1, \
					       DI_DW_GEN_PIN_SHIFT(n))
#define IPU_DI_DW_SET(n, m)	(0x00000088 + (n) * 4 + (m) * 0x30)
#define  DI_DW_SET_DOWN_SHIFT	16
#define  DI_DW_SET_UP_SHIFT	0
#define IPU_DI_STP_REP(n)	(0x00000148 + ((n - 1) / 2) * 4)
#define  DI_STP_REP_SHIFT(n)	(((n - 1) % 2) * 16)
#define  DI_STP_REP_MASK(n)	(0x00000fff << DI_STP_REP_SHIFT((n)))
#define IPU_DI_SER_CONF			0x0000015c
#define IPU_DI_SSC			0x00000160
#define IPU_DI_POL			0x00000164
#define  DI_POL_DRDY_POLARITY_17 	0x00000040
#define  DI_POL_DRDY_POLARITY_16 	0x00000020
#define  DI_POL_DRDY_POLARITY_15 	0x00000010
#define  DI_POL_DRDY_POLARITY_14 	0x00000008
#define  DI_POL_DRDY_POLARITY_13 	0x00000004
#define  DI_POL_DRDY_POLARITY_12 	0x00000002
#define  DI_POL_DRDY_POLARITY_11 	0x00000001
#define IPU_DI_AW0			0x00000168
#define IPU_DI_AW1			0x0000016c
#define IPU_DI_SCR_CONF			0x00000170
#define IPU_DI_STAT			0x00000174

/*
 * SMFC
 * Sensor Multi FIFO Controller
 */
#define IPU_SMFC_MAP	0x00000000
#define IPU_SMFC_WMC	0x00000004
#define IPU_SMFC_BS	0x00000008

/*
 * DC
 * Display Controller
 */
#define IPU_DC_READ_CH_CONF	0x00000000
#define IPU_DC_READ_CH_ADDR	0x00000004

#define IPU_DC_RL0_CH_0		0x00000008
#define IPU_DC_RL1_CH_0		0x0000000c
#define IPU_DC_RL2_CH_0		0x00000010
#define IPU_DC_RL3_CH_0		0x00000014
#define IPU_DC_RL4_CH_0		0x00000018
#define IPU_DC_WR_CH_CONF_1	0x0000001c
#define IPU_DC_WR_CH_ADDR_1	0x00000020
#define IPU_DC_RL0_CH_1		0x00000024
#define IPU_DC_RL1_CH_1		0x00000028
#define IPU_DC_RL2_CH_1		0x0000002c
#define IPU_DC_RL3_CH_1		0x00000030
#define IPU_DC_RL4_CH_1		0x00000034
#define IPU_DC_WR_CH_CONF_2	0x00000038
#define IPU_DC_WR_CH_ADDR_2	0x0000003c
#define IPU_DC_RL0_CH_2		0x00000040
#define IPU_DC_RL1_CH_2		0x00000044
#define IPU_DC_RL2_CH_2		0x00000048
#define IPU_DC_RL3_CH_2		0x0000004c
#define IPU_DC_RL4_CH_2		0x00000050
#define IPU_DC_CMD_CH_CONF_3	0x00000054
#define IPU_DC_CMD_CH_CONF_4	0x00000058
#define IPU_DC_WR_CH_CONF_5	0x0000005c
#define IPU_DC_WR_CH_ADDR_5	0x00000060
#define IPU_DC_RL0_CH_5		0x00000064
#define IPU_DC_RL1_CH_5		0x00000068
#define IPU_DC_RL2_CH_5		0x0000006c
#define IPU_DC_RL3_CH_5		0x00000070
#define IPU_DC_RL4_CH_5		0x00000074
#define IPU_DC_WR_CH_CONF_6	0x00000078
#define IPU_DC_WR_CH_ADDR_6	0x0000007c
#define IPU_DC_RL0_CH_6		0x00000080
#define IPU_DC_RL1_CH_6		0x00000084
#define IPU_DC_RL2_CH_6		0x00000088
#define IPU_DC_RL3_CH_6		0x0000008c
#define IPU_DC_RL4_CH_6		0x00000090
#define IPU_DC_WR_CH_CONF1_8	0x00000094
#define IPU_DC_WR_CH_CONF2_8	0x00000098
#define IPU_DC_RL1_CH_8		0x0000009c
#define IPU_DC_RL2_CH_8		0x000000a0
#define IPU_DC_RL3_CH_8		0x000000a4
#define IPU_DC_RL4_CH_8		0x000000a8
#define IPU_DC_RL5_CH_8		0x000000ac
#define IPU_DC_RL6_CH_8		0x000000b0
#define IPU_DC_WR_CH_CONF1_9	0x000000b4
#define IPU_DC_WR_CH_CONF2_9	0x000000b8
#define IPU_DC_RL1_CH_9		0x000000bc
#define IPU_DC_RL2_CH_9		0x000000c0
#define IPU_DC_RL3_CH_9		0x000000c4
#define IPU_DC_RL4_CH_9		0x000000c8
#define IPU_DC_RL5_CH_9		0x000000cc
#define IPU_DC_RL6_CH_9		0x000000d0

#define IPU_DC_RL(chan_base, evt)	((chan_base) + (evt / 2) *0x4)
#define  DC_RL_CH_0		IPU_DC_RL0_CH_0
#define  DC_RL_CH_1		IPU_DC_RL0_CH_1
#define  DC_RL_CH_2		IPU_DC_RL0_CH_2
#define  DC_RL_CH_5		IPU_DC_RL0_CH_5
#define  DC_RL_CH_6		IPU_DC_RL0_CH_6
#define  DC_RL_CH_8		IPU_DC_RL0_CH_8

#define  DC_RL_EVT_NF		0
#define  DC_RL_EVT_NL		1
#define  DC_RL_EVT_EOF		2
#define  DC_RL_EVT_NFIELD	3
#define  DC_RL_EVT_EOL		4
#define  DC_RL_EVT_EOFIELD	5
#define  DC_RL_EVT_NEW_ADDR	6
#define  DC_RL_EVT_NEW_CHAN	7
#define  DC_RL_EVT_NEW_DATA	8

#define IPU_DC_GEN		0x000000d4
#define IPU_DC_DISP_CONF1_0	0x000000d8
#define IPU_DC_DISP_CONF1_1	0x000000dc
#define IPU_DC_DISP_CONF1_2	0x000000e0
#define IPU_DC_DISP_CONF1_3	0x000000e4
#define IPU_DC_DISP_CONF2_0	0x000000e8
#define IPU_DC_DISP_CONF2_1	0x000000ec
#define IPU_DC_DISP_CONF2_2	0x000000f0
#define IPU_DC_DISP_CONF2_3	0x000000f4
#define IPU_DC_DI0_CONF_1	0x000000f8
#define IPU_DC_DI0_CONF_2	0x000000fc
#define IPU_DC_DI1_CONF_1	0x00000100
#define IPU_DC_DI1_CONF_2	0x00000104

#define IPU_DC_MAP_CONF_PNTR(n)	(0x00000108 + (n) * 4)
#define IPU_DC_MAP_CONF_0	0x00000108
#define IPU_DC_MAP_CONF_1	0x0000010c
#define IPU_DC_MAP_CONF_2	0x00000110
#define IPU_DC_MAP_CONF_3	0x00000114
#define IPU_DC_MAP_CONF_4	0x00000118
#define IPU_DC_MAP_CONF_5	0x0000011c
#define IPU_DC_MAP_CONF_6	0x00000120
#define IPU_DC_MAP_CONF_7	0x00000124
#define IPU_DC_MAP_CONF_8	0x00000128
#define IPU_DC_MAP_CONF_9	0x0000012c
#define IPU_DC_MAP_CONF_10	0x00000130
#define IPU_DC_MAP_CONF_11	0x00000134
#define IPU_DC_MAP_CONF_12	0x00000138
#define IPU_DC_MAP_CONF_13	0x0000013c
#define IPU_DC_MAP_CONF_14	0x00000140

#define IPU_DC_MAP_CONF_MASK(n)	(0x00000144 + (n) * 4)
#define IPU_DC_MAP_CONF_15	0x00000144
#define IPU_DC_MAP_CONF_16	0x00000148
#define IPU_DC_MAP_CONF_17	0x0000014c
#define IPU_DC_MAP_CONF_18	0x00000150
#define IPU_DC_MAP_CONF_19	0x00000154
#define IPU_DC_MAP_CONF_20	0x00000158
#define IPU_DC_MAP_CONF_21	0x0000015c
#define IPU_DC_MAP_CONF_22	0x00000160
#define IPU_DC_MAP_CONF_23	0x00000164
#define IPU_DC_MAP_CONF_24	0x00000168
#define IPU_DC_MAP_CONF_25	0x0000016c
#define IPU_DC_MAP_CONF_26	0x00000170

#define IPU_DC_UGDE(m, n)	(0x00000174 + (m) * 0x10 + (n) +4)
#define IPU_DC_UGDE0_0		0x00000174
#define IPU_DC_UGDE0_1		0x00000178
#define IPU_DC_UGDE0_2		0x0000017c
#define IPU_DC_UGDE0_3		0x00000180
#define IPU_DC_UGDE1_0		0x00000184
#define IPU_DC_UGDE1_1		0x00000188
#define IPU_DC_UGDE1_2		0x0000018c
#define IPU_DC_UGDE1_3		0x00000190
#define IPU_DC_UGDE2_0		0x00000194
#define IPU_DC_UGDE2_1		0x00000198
#define IPU_DC_UGDE2_2		0x0000019c
#define IPU_DC_UGDE2_3		0x000001a0
#define IPU_DC_UGDE3_0		0x000001a4
#define IPU_DC_UGDE3_1		0x000001a8
#define IPU_DC_UGDE3_2		0x000001ac
#define IPU_DC_UGDE3_3		0x000001b0
#define IPU_DC_LLA0		0x000001b4
#define IPU_DC_LLA1		0x000001b8
#define IPU_DC_R_LLA0		0x000001bc
#define IPU_DC_R_LLA1		0x000001c0
#define IPU_DC_WR_CH_ADDR_5_ALT	0x000001c4
#define IPU_DC_STAT		0x000001c8

/*
 * DMFC
 * Display Multi FIFO Controller
 */
#define IPU_DMFC_RD_CHAN		0x00000000
#define  DMFC_RD_CHAN_PPW_C		0x03000000
#define  DMFC_RD_CHAN_WM_DR_0		0x00e00000
#define  DMFC_RD_CHAN_WM_SET_0		0x001c0000
#define  DMFC_RD_CHAN_WM_EN_0		0x00020000
#define  DMFC_RD_CHAN_BURST_SIZE_0	0x000000c0
#define IPU_DMFC_WR_CHAN		0x00000004
#define  DMFC_WR_CHAN_BUSRT_SIZE_2C	0xc0000000
#define  DMFC_WR_CHAN_FIFO_SIZE_2C	0x38000000
#define  DMFC_WR_CHAN_ST_ADDR_2C	0x07000000
#define  DMFC_WR_CHAN_BURST_SIZE_1C	0x00c00000
#define  DMFC_WR_CHAN_FIFO_SIZE_1C	0x00380000
#define  DMFC_WR_CHAN_ST_ADDR_1C	0x00070000
#define  DMFC_WR_CHAN_BURST_SIZE_2	0x0000c000
#define  DMFC_WR_CHAN_FIFO_SIZE_2	0x00003800
#define  DMFC_WR_CHAN_ST_ADDR_2		0x00000700
#define  DMFC_WR_CHAN_BURST_SIZE_1	0x000000c0
#define  DMFC_WR_CHAN_FIFO_SIZE_1	0x00000038
#define  DMFC_WR_CHAN_ST_ADDR_1		0x00000007
#define IPU_DMFC_WR_CHAN_DEF		0x00000008
#define  DMFC_WR_CHAN_DEF_WM_CLR_2C	0xe0000000
#define  DMFC_WR_CHAN_DEF_WM_SET_2C	0x1c000000
#define  DMFC_WR_CHAN_DEF_WM_EN_2C	0x02000000
#define  DMFC_WR_CHAN_DEF_WM_CLR_1C	0x00e00000
#define  DMFC_WR_CHAN_DEF_WM_SET_1C	0x001c0000
#define  DMFC_WR_CHAN_DEF_WM_EN_1C	0x00020000
#define  DMFC_WR_CHAN_DEF_WM_CLR_2	0x0000e000
#define  DMFC_WR_CHAN_DEF_WM_SET_2	0x00001c00
#define  DMFC_WR_CHAN_DEF_WM_EN_2	0x00000200
#define  DMFC_WR_CHAN_DEF_WM_CLR_1	0x000000e0
#define  DMFC_WR_CHAN_DEF_WM_SET_1	0x0000000c
#define  DMFC_WR_CHAN_DEF_WM_EN_1	0x00000002
#define IPU_DMFC_DP_CHAN		0x0000000c
#define  DMFC_DP_CHAN_BUSRT_SIZE_6F	0xc0000000
#define  DMFC_DP_CHAN_FIFO_SIZE_6F	0x38000000
#define  DMFC_DP_CHAN_ST_ADDR_6F	0x07000000
#define  DMFC_DP_CHAN_BURST_SIZE_6B	0x00c00000
#define  DMFC_DP_CHAN_FIFO_SIZE_6B	0x00380000
#define  DMFC_DP_CHAN_ST_ADDR_6B	0x00070000
#define  DMFC_DP_CHAN_BURST_SIZE_5F	0x0000c000
#define  DMFC_DP_CHAN_FIFO_SIZE_5F	0x00003800
#define  DMFC_DP_CHAN_ST_ADDR_5F	0x00000700
#define  DMFC_DP_CHAN_BURST_SIZE_5B	0x000000c0
#define  DMFC_DP_CHAN_FIFO_SIZE_5B	0x00000038
#define  DMFC_DP_CHAN_ST_ADDR_5B	0x00000007
#define IPU_DMFC_DP_CHAN_DEF		0x00000010
#define  DMFC_DP_CHAN_DEF_WM_CLR_6F	0xe0000000
#define  DMFC_DP_CHAN_DEF_WM_SET_6F	0x1c000000
#define  DMFC_DP_CHAN_DEF_WM_EN_6F	0x02000000
#define  DMFC_DP_CHAN_DEF_WM_CLR_6B	0x00e00000
#define  DMFC_DP_CHAN_DEF_WM_SET_6B	0x001c0000
#define  DMFC_DP_CHAN_DEF_WM_EN_6B	0x00020000
#define  DMFC_DP_CHAN_DEF_WM_CLR_5F	0x0000e000
#define  DMFC_DP_CHAN_DEF_WM_SET_5F	0x00001c00
#define  DMFC_DP_CHAN_DEF_WM_EN_5F	0x00000200
#define  DMFC_DP_CHAN_DEF_WM_CLR_5B	0x000000e0
#define  DMFC_DP_CHAN_DEF_WM_SET_5B	0x0000001c
#define  DMFC_DP_CHAN_DEF_WM_EN_5B	0x00000002
#define IPU_DMFC_GENERAL1		0x00000014
#define  DMFC_GENERAL1_WAIT4EOT_9	0x01000000
#define  DMFC_GENERAL1_WAIT4EOT_6F	0x00800000
#define  DMFC_GENERAL1_WAIT4EOT_6B	0x00400000
#define  DMFC_GENERAL1_WAIT4EOT_5F	0x00200000
#define  DMFC_GENERAL1_WAIT4EOT_5B	0x00100000
#define  DMFC_GENERAL1_WAIT4EOT_4	0x00080000
#define  DMFC_GENERAL1_WAIT4EOT_3	0x00040000
#define  DMFC_GENERAL1_WAIT4EOT_2	0x00020000
#define  DMFC_GENERAL1_WAIT4EOT_1	0x00010000
#define  DMFC_GENERAL1_WM_CLR_9		0x0000e000
#define  DMFC_GENERAL1_WM_SET_9		0x00001c00
#define  DMFC_GENERAL1_BURST_SIZE_9	0x00000060
#define  DMFC_GENERAL1_DCDP_SYNC_PR	0x00000003
#define   DCDP_SYNC_PR_FORBIDDEN	0
#define   DCDP_SYNC_PR_DC_DP		1
#define   DCDP_SYNC_PR_DP_DC		2
#define   DCDP_SYNC_PR_ROUNDROBIN	3
#define IPU_DMFC_GENERAL2		0x00000018
#define  DMFC_GENERAL2_FRAME_HEIGHT_RD	0x1fff0000
#define  DMFC_GENERAL2_FRAME_WIDTH_RD	0x00001fff
#define IPU_DMFC_IC_CTRL		0x0000001c
#define  DMFC_IC_CTRL_IC_FRAME_HEIGHT_RD	0xfff80000
#define  DMFC_IC_CTRL_IC_FRAME_WIDTH_RD		0x0007ffc0
#define  DMFC_IC_CTRL_IC_PPW_C			0x00000030
#define  DMFC_IC_CTRL_IC_IN_PORT		0x00000007
#define   IC_IN_PORT_CH28		0
#define   IC_IN_PORT_CH41		1
#define   IC_IN_PORT_DISABLE		2
#define   IC_IN_PORT_CH23		4
#define   IC_IN_PORT_CH27		5
#define   IC_IN_PORT_CH24		6
#define   IC_IN_PORT_CH29		7
#define IPU_DMFC_WR_CHAN_ALT		0x00000020
#define IPU_DMFC_WR_CHAN_DEF_ALT	0x00000024
#define IPU_DMFC_DP_CHAN_ALT		0x00000028
#define IPU_DMFC_DP_CHAN_DEF_ALT	0x0000002c
#define  DMFC_DP_CHAN_DEF_ALT_WM_CLR_6F_ALT	0xe0000000
#define  DMFC_DP_CHAN_DEF_ALT_WM_SET_6F_ALT	0x1c000000
#define  DMFC_DP_CHAN_DEF_ALT_WM_EN_6F_ALT	0x02000000
#define  DMFC_DP_CHAN_DEF_ALT_WM_CLR_6B_ALT	0x00e00000
#define  DMFC_DP_CHAN_DEF_ALT_WM_SET_6B_ALT	0x001c0000
#define  DMFC_DP_CHAN_DEF_ALT_WM_EN_6B_ALT	0x00020000
#define  DMFC_DP_CHAN_DEF_ALT_WM_CLR_5B_ALT	0x000000e0
#define  DMFC_DP_CHAN_DEF_ALT_WM_SET_5B_ALT	0x0000001c
#define  DMFC_DP_CHAN_DEF_ALT_WM_EN_5B_ALT	0x00000002
#define IPU_DMFC_GENERAL1_ALT		0x00000030
#define  DMFC_GENERAL1_ALT_WAIT4EOT_6F_ALT	0x00800000
#define  DMFC_GENERAL1_ALT_WAIT4EOT_6B_ALT	0x00400000
#define  DMFC_GENERAL1_ALT_WAIT4EOT_5B_ALT	0x00100000
#define  DMFC_GENERAL1_ALT_WAIT4EOT_2_ALT	0x00020000
#define IPU_DMFC_STAT			0x00000034
#define  DMFC_STAT_IC_BUFFER_EMPTY	0x02000000
#define  DMFC_STAT_IC_BUFFER_FULL	0x01000000
#define  DMFC_STAT_FIFO_EMPTY(n)	__BIT(12 + (n))
#define  DMFC_STAT_FIFO_FULL(n)		__BIT((n))

/*
 * VCI
 * Video De Interkacing Module
 */
#define IPU_VDI_FSIZE	0x00000000
#define IPU_VDI_C	0x00000004

/*
 * DP
 * Display Processor
 */
#define IPU_DP_COM_CONF_SYNC		0x00000000
#define  DP_FG_EN_SYNC			0x00000001
#define  DP_DP_GWAM_SYNC		0x00000004
#define IPU_DP_GRAPH_WIND_CTRL_SYNC	0x00000004
#define IPU_DP_FG_POS_SYNC		0x00000008
#define IPU_DP_CUR_POS_SYNC		0x0000000c
#define IPU_DP_CUR_MAP_SYNC		0x00000010
#define IPU_DP_CSC_SYNC_0		0x00000054
#define IPU_DP_CSC_SYNC_1		0x00000058
#define IPU_DP_CUR_POS_ALT		0x0000005c
#define IPU_DP_COM_CONF_ASYNC0		0x00000060
#define IPU_DP_GRAPH_WIND_CTRL_ASYNC0	0x00000064
#define IPU_DP_FG_POS_ASYNC0		0x00000068
#define IPU_DP_CUR_POS_ASYNC0		0x0000006c
#define IPU_DP_CUR_MAP_ASYNC0		0x00000070
#define IPU_DP_CSC_ASYNC0_0		0x000000b4
#define IPU_DP_CSC_ASYNC0_1		0x000000b8
#define IPU_DP_COM_CONF_ASYNC1		0x000000bc
#define IPU_DP_GRAPH_WIND_CTRL_ASYNC1	0x000000c0
#define IPU_DP_FG_POS_ASYNC1		0x000000c4
#define IPU_DP_CUR_POS_ASYNC1		0x000000c8
#define IPU_DP_CUR_MAP_ASYNC1		0x000000cc
#define IPU_DP_CSC_ASYNC1_0		0x00000110
#define IPU_DP_CSC_ASYNC1_1		0x00000114

/* IDMA parameter */
	/*
	 * non-Interleaved parameter
	 *
	 * param 0: XV W0[ 9: 0]
	 *          YV W0[18:10]
	 *          XB W0[31:19]
	 * param 1: YB W0[43:32]
	 *          NSB W0[44]
	 *          CF W0[45]
	 *          UBO W0[61:46]
	 * param 2: UBO W0[67:62]
	 *          VBO W0[89:68]
	 *          IOX W0[93:90]
	 *          RDRW W0[94]
	 *          Reserved W0[95]
	 * param 3: Reserved W0[112:96]
	 *          S0 W0[113]
	 *          BNDM W0[116:114]
	 *          BM W0[118:117]
	 *          ROT W0[119]
	 *          HF W0[120]
	 *          VF W0[121]
	 *          THF W0[122]
	 *          CAP W0[123]
	 *          CAE W0[124]
	 *          FW W0[127:125]
	 * param 4: FW W0[137:128]
	 *          FH W0[149:138]
	 * param 5: EBA0 W1[28:0]
	 *          EBA1 W1[31:29]
	 * param 6: EBA1 W1[57:32]
	 *          ILO W1[63:58]
	 * param 7: ILO W1[77:64]
	 *          NPB W1[84:78]
	 *          PFS W1[88:85]
	 *          ALU W1[89]
	 *          ALBM W1[92:90]
	 *          ID W1[94:93]
	 *          TH W1[95]
	 * param 8: TH W1[101:96]
	 *          SLY W1[115:102]
	 *          WID3 W1[127:125]
	 * param 9: SLUV W1[141:128]
	 *          CRE W1[149]
	 *
	 * Interleaved parameter
	 *
	 * param 0: XV W0[ 9: 0]
	 *          YV W0[18:10]
	 *          XB W0[31:19]
	 * param 1: YB W0[43:32]
	 *          NSB W0[44]
	 *          CF W0[45]
	 *          SX W0[57:46]
	 *          SY W0[61:58]
	 * param 2: SY W0[68:62]
	 *          NS W0[78:69]
	 *          SDX W0[85:79]
	 *          SM W0[95:86]
	 * param 3: SCC W0[96]
	 *          SCE W0[97]
	 *          SDY W0[104:98]
	 *          SDRX W0[105]
	 *          SDRY W0[106]
	 *          BPP W0[109:107]
	 *	    DEC_SEL W0[111:110]
	 *          DIM W0[112]
	 *          SO W0[113]
	 *          BNDM W0[116:114]
	 *          BM W0[118:117]
	 *          ROT W0[119]
	 *          HF W0[120]
	 *          VF W0[121]
	 *          THF W0[122]
	 *          CAP W0[123]
	 *          CAE W0[124]
	 *          FW W0[127:125]
	 * param 4: FW W0[137:128]
	 *          FH W0[149:138]
	 * param 5: EBA0 W1[28:0]
	 *          EBA1 W1[31:29]
	 * param 6: EBA1 W1[57:32]
	 *          ILO W1[63:58]
	 * param 7: ILO W1[77:64]
	 *          NPB W1[84:78]
	 *          PFS W1[88:85]
	 *          ALU W1[89]
	 *          ALBM W1[92:90]
	 *          ID W1[94:93]
	 *          TH W1[95]
	 * param 8: TH W1[101:96]
	 *          SL W1[115:102]
	 *          WID0 W1[118:116]
	 *          WID1 W1[121:119]
	 *          WID2 W1[124:122]
	 *          WID3 W1[127:125]
	 * param 9: OFS0 W1[132:128]
	 *          OFS1 W1[137:133]
	 *          OFS2 W1[142:138]
	 *          OFS3 W1[147:143]
	 *          SXYS W1[148]
	 *          CRE W1[149]
	 *          DEC_SEL2 W1[150]
	 */

#define __IDMA_PARAM(word, shift, size) \
	((((word) & 0xff) << 16) | (((shift) & 0xff) << 8) | ((size) & 0xff))

/* non-Interleaved parameter */
/* W0 */
#define IDMAC_Ch_PARAM_XV	__IDMA_PARAM(0,  0, 10)
#define IDMAC_Ch_PARAM_YV	__IDMA_PARAM(0, 10,  9)
#define IDMAC_Ch_PARAM_XB	__IDMA_PARAM(0, 19, 13)
#define IDMAC_Ch_PARAM_YB	__IDMA_PARAM(0, 32, 12)
#define IDMAC_Ch_PARAM_NSB	__IDMA_PARAM(0, 44,  1)
#define IDMAC_Ch_PARAM_CF	__IDMA_PARAM(0, 45,  1)
#define IDMAC_Ch_PARAM_UBO	__IDMA_PARAM(0, 46, 22)
#define IDMAC_Ch_PARAM_VBO	__IDMA_PARAM(0, 68, 22)
#define IDMAC_Ch_PARAM_IOX	__IDMA_PARAM(0, 90,  4)
#define IDMAC_Ch_PARAM_RDRW	__IDMA_PARAM(0, 94,  1)
#define IDMAC_Ch_PARAM_S0	__IDMA_PARAM(0,113,  1)
#define IDMAC_Ch_PARAM_BNDM	__IDMA_PARAM(0,114,  3)
#define IDMAC_Ch_PARAM_BM	__IDMA_PARAM(0,117,  2)
#define IDMAC_Ch_PARAM_ROT	__IDMA_PARAM(0,119,  1)
#define IDMAC_Ch_PARAM_HF	__IDMA_PARAM(0,120,  1)
#define IDMAC_Ch_PARAM_VF	__IDMA_PARAM(0,121,  1)
#define IDMAC_Ch_PARAM_THF	__IDMA_PARAM(0,122,  1)
#define IDMAC_Ch_PARAM_CAP	__IDMA_PARAM(0,123,  1)
#define IDMAC_Ch_PARAM_CAE	__IDMA_PARAM(0,124,  1)
#define IDMAC_Ch_PARAM_FW	__IDMA_PARAM(0,125, 13)
#define IDMAC_Ch_PARAM_FH	__IDMA_PARAM(0,138, 12)
/* W1 */
#define IDMAC_Ch_PARAM_EBA0	__IDMA_PARAM(1,  0, 29)
#define IDMAC_Ch_PARAM_EBA1	__IDMA_PARAM(1, 29, 29)
#define IDMAC_Ch_PARAM_ILO	__IDMA_PARAM(1, 58, 20)
#define IDMAC_Ch_PARAM_NPB	__IDMA_PARAM(1, 78,  7)
#define IDMAC_Ch_PARAM_PFS	__IDMA_PARAM(1, 85,  4)
#define IDMAC_Ch_PARAM_ALU	__IDMA_PARAM(1, 89,  1)
#define IDMAC_Ch_PARAM_ALBM	__IDMA_PARAM(1, 90,  3)
#define IDMAC_Ch_PARAM_ID	__IDMA_PARAM(1, 93,  2)
#define IDMAC_Ch_PARAM_TH	__IDMA_PARAM(1, 95,  7)
#define IDMAC_Ch_PARAM_SL	__IDMA_PARAM(1,102, 14)
#define IDMAC_Ch_PARAM_WID3	__IDMA_PARAM(1,125,  3)
#define IDMAC_Ch_PARAM_SLUV	__IDMA_PARAM(1,128, 14)
#define IDMAC_Ch_PARAM_CRE	__IDMA_PARAM(1,149,  1)

/* Interleaved parameter */
/* W0 */
#define IDMAC_Ch_PARAM_XV	__IDMA_PARAM(0,  0, 10)
#define IDMAC_Ch_PARAM_YV	__IDMA_PARAM(0, 10,  9)
#define IDMAC_Ch_PARAM_XB	__IDMA_PARAM(0, 19, 13)
#define IDMAC_Ch_PARAM_YB	__IDMA_PARAM(0, 32, 12)
#define IDMAC_Ch_PARAM_NSB	__IDMA_PARAM(0, 44,  1)
#define IDMAC_Ch_PARAM_CF	__IDMA_PARAM(0, 45,  1)
#define IDMAC_Ch_PARAM_SX	__IDMA_PARAM(0, 46, 12)
#define IDMAC_Ch_PARAM_SY	__IDMA_PARAM(0, 58, 11)
#define IDMAC_Ch_PARAM_NS	__IDMA_PARAM(0, 69, 10)
#define IDMAC_Ch_PARAM_SDX	__IDMA_PARAM(0, 79,  7)
#define IDMAC_Ch_PARAM_SM	__IDMA_PARAM(0, 86, 10)
#define IDMAC_Ch_PARAM_SCC	__IDMA_PARAM(0, 96,  1)
#define IDMAC_Ch_PARAM_SCE	__IDMA_PARAM(0, 97,  1)
#define IDMAC_Ch_PARAM_SDY	__IDMA_PARAM(0, 98,  7)
#define IDMAC_Ch_PARAM_SDRX	__IDMA_PARAM(0,105,  1)
#define IDMAC_Ch_PARAM_SDRY	__IDMA_PARAM(0,106,  1)
#define IDMAC_Ch_PARAM_BPP	__IDMA_PARAM(0,107,  3)
#define IDMAC_Ch_PARAM_DEC_SEL	__IDMA_PARAM(0,110,  2)
#define IDMAC_Ch_PARAM_DIM	__IDMA_PARAM(0,112,  1)
#define IDMAC_Ch_PARAM_SO	__IDMA_PARAM(0,113,  1)
#define IDMAC_Ch_PARAM_BNDM	__IDMA_PARAM(0,114,  3)
#define IDMAC_Ch_PARAM_BM	__IDMA_PARAM(0,117,  2)
#define IDMAC_Ch_PARAM_ROT	__IDMA_PARAM(0,119,  1)
#define IDMAC_Ch_PARAM_HF	__IDMA_PARAM(0,120,  1)
#define IDMAC_Ch_PARAM_VF	__IDMA_PARAM(0,121,  1)
#define IDMAC_Ch_PARAM_THF	__IDMA_PARAM(0,122,  1)
#define IDMAC_Ch_PARAM_CAP	__IDMA_PARAM(0,123,  1)
#define IDMAC_Ch_PARAM_CAE	__IDMA_PARAM(0,124,  1)
#define IDMAC_Ch_PARAM_FW	__IDMA_PARAM(0,125, 13)
#define IDMAC_Ch_PARAM_FH	__IDMA_PARAM(0,138, 12)
/* W1 */
#define IDMAC_Ch_PARAM_EBA0	__IDMA_PARAM(1,  0, 29)
#define IDMAC_Ch_PARAM_EBA1	__IDMA_PARAM(1, 29, 29)
#define IDMAC_Ch_PARAM_ILO	__IDMA_PARAM(1, 58, 20)
#define IDMAC_Ch_PARAM_NPB	__IDMA_PARAM(1, 78,  7)
#define IDMAC_Ch_PARAM_PFS	__IDMA_PARAM(1, 85,  4)
#define IDMAC_Ch_PARAM_ALU	__IDMA_PARAM(1, 89,  1)
#define IDMAC_Ch_PARAM_ALBM	__IDMA_PARAM(1, 90,  3)
#define IDMAC_Ch_PARAM_ID	__IDMA_PARAM(1, 93,  2)
#define IDMAC_Ch_PARAM_TH	__IDMA_PARAM(1, 95,  7)
#define IDMAC_Ch_PARAM_SL	__IDMA_PARAM(1,102, 14)
#define IDMAC_Ch_PARAM_WID0	__IDMA_PARAM(1,116,  3)
#define IDMAC_Ch_PARAM_WID1	__IDMA_PARAM(1,119,  3)
#define IDMAC_Ch_PARAM_WID2	__IDMA_PARAM(1,122,  3)
#define IDMAC_Ch_PARAM_WID3	__IDMA_PARAM(1,125,  3)
#define IDMAC_Ch_PARAM_OFS0	__IDMA_PARAM(1,128,  5)
#define IDMAC_Ch_PARAM_OFS1	__IDMA_PARAM(1,133,  5)
#define IDMAC_Ch_PARAM_OFS2	__IDMA_PARAM(1,138,  5)
#define IDMAC_Ch_PARAM_OFS3	__IDMA_PARAM(1,143,  5)
#define IDMAC_Ch_PARAM_SXYS	__IDMA_PARAM(1,148,  1)
#define IDMAC_Ch_PARAM_CRE	__IDMA_PARAM(1,149,  1)
#define IDMAC_Ch_PARAM_DEC_SEL2 __IDMA_PARAM(1,150,  1)

/* XXX Temp */
#define	GPUMEM_BASE	0x20000000
#define	GPUMEM_SIZE	0x20000

#define	GPU_BASE	0x30000000
#define	GPU_SIZE	0x10000000

/* Image Prossasing Unit */
#define	IPU_BASE	0x40000000
#define	IPU_CM_BASE	(IPU_BASE + 0x1e000000)
#define	IPU_CM_SIZE	0x8000
#define	IPU_IDMAC_BASE	(IPU_BASE + 0x1e008000)
#define	IPU_IDMAC_SIZE	0x8000
#define	IPU_DP_BASE	(IPU_BASE + 0x1e018000)
#define	IPU_DP_SIZE	0x8000
#define	IPU_IC_BASE	(IPU_BASE + 0x1e020000)
#define	IPU_IC_SIZE	0x8000
#define	IPU_IRT_BASE	(IPU_BASE + 0x1e028000)
#define	IPU_IRT_SIZE	0x8000
#define	IPU_CSI0_BASE	(IPU_BASE + 0x1e030000)
#define	IPU_CSI0_SIZE	0x8000
#define	IPU_CSI1_BASE	(IPU_BASE + 0x1e038000)
#define	IPU_CSI1_SIZE	0x8000
#define	IPU_DI0_BASE	(IPU_BASE + 0x1e040000)
#define	IPU_DI0_SIZE	0x8000
#define	IPU_DI1_BASE	(IPU_BASE + 0x1e048000)
#define	IPU_DI1_SIZE	0x8000
#define	IPU_SMFC_BASE	(IPU_BASE + 0x1e050000)
#define	IPU_SMFC_SIZE	0x8000
#define	IPU_DC_BASE	(IPU_BASE + 0x1e058000)
#define	IPU_DC_SIZE	0x8000
#define	IPU_DMFC_BASE	(IPU_BASE + 0x1e060000)
#define	IPU_DMFC_SIZE	0x8000
#define	IPU_VDI_BASE	(IPU_BASE + 0x1e068000)
#define	IPU_VDI_SIZE	0x8000
#define	IPU_CPMEM_BASE	(IPU_BASE + 0x1f000000)
#define	IPU_CPMEM_SIZE	0x20000
#define	IPU_LUT_BASE	(IPU_BASE + 0x1f020000)
#define	IPU_LUT_SIZE	0x20000
#define	IPU_SRM_BASE	(IPU_BASE + 0x1f040000)
#define	IPU_SRM_SIZE	0x20000
#define	IPU_TPM_BASE	(IPU_BASE + 0x1f060000)
#define	IPU_TPM_SIZE	0x20000
#define	IPU_DCTMPL_BASE	(IPU_BASE + 0x1f080000)
#define	IPU_DCTMPL_SIZE	0x20000

#endif /* _ARM_IMX_IMX51_IPUV3REG_H */
