/******************************************************************************************
  Filename    : sdma.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 06.08.2026
  
  Description : System DMA header file
  
******************************************************************************************/

#ifndef SDMA_H
#define SDMA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct  DMAC_TypeDef
 * @brief   DMAC Register Layout
 */
typedef struct {
	volatile uint64_t ID;								/* 0x000: */
	volatile uint32_t COMPVERREG;						/* 0x008: */
	volatile uint32_t CFGREG;							/* 0x010: */
	volatile uint64_t CHENREG;							/* 0x018: */
	uint32_t RESERVED_0[4];								/* 0x020 - 0x02c */
	volatile uint32_t INTSTATUSREG;						/* 0x030: */
	uint32_t RESERVED_1;								/* 0x034 */
	volatile uint32_t INTCLEARREG;						/* 0x038: */
	uint32_t RESERVED_2;								/* 0x03c */
	volatile uint32_t COMMONREG_INTSTATUS_ENABLERREG;	/* 0x040: */
	uint32_t RESERVED_3;								/* 0x044 */
	volatile uint32_t COMMONREG_INTSIGNAL_ENABLERREG;	/* 0x048: */
	uint32_t RESERVED_4;								/* 0x04c */
	volatile uint32_t COMMONREG_INTSTATUSREG;			/* 0x050: */
	uint32_t RESERVED_5;								/* 0x054 */
	volatile uint32_t RESETREG;							/* 0x058: */
} DMAC_TypeDef;

/**
 * @struct  DMAC_CHx_TypeDef
 * @brief   DMAC Register Layout
 */
typedef struct {
	volatile uint64_t SAR;					/* 0x000: Source addr */
	volatile uint64_t DAR;					/* 0x008: Dest addr */
	volatile uint32_t BLOCK_TS;				/* 0x010: Transfer Size */
	uint32_t RESERVED_0;					/* 0x014 */
	volatile uint64_t CTL;					/* 0x018: Control */
	volatile uint64_t CFG;					/* 0x020: Configuration */
	volatile uint64_t LLP;					/* 0x028: AXI Layer */
	volatile uint64_t STATUSREG;			/* 0x030: Status */
	volatile uint32_t SWHSSRCREG;			/* 0x038: Software Handshake Src */
	uint32_t RESERVED_1;					/* 0x03c */
	volatile uint32_t SWHSDSTREG;			/* 0x040: Software Handshake Dst */
	uint32_t RESERVED_2;					/* 0x044 */
	volatile uint32_t BLK_TFR_RESUMEREQREG;	/* 0x048: Block Transfer Resume Request */
	uint32_t RESERVED_3;					/* 0x04c */
	volatile uint32_t AXI_IDREG;			/* 0x050: Block Transfer Resume Request */
	uint32_t RESERVED_4;					/* 0x054 */
	volatile uint32_t AXI_QOSREG;			/* 0x058: Block Transfer Resume Request */
	uint32_t RESERVED_5;					/* 0x05c */
	volatile uint32_t SSTAT;				/* 0x060: Source Status */
	uint32_t RESERVED_6;					/* 0x064 */
	volatile uint32_t DSTAT;				/* 0x068: Destination Status */
	uint32_t RESERVED_7;					/* 0x06c */
	volatile uint32_t SSTATAR;				/* 0x070: Source Status Addr */
	uint32_t RESERVED_8;					/* 0x074 */
	volatile uint32_t DSTATAR;				/* 0x078: Destination Status Addr */
	uint32_t RESERVED_9;					/* 0x07c */
	volatile uint32_t INTSTATUS_ENABLEREG;	/* 0x080: Interrupt Status Enable */
	uint32_t RESERVED_10;					/* 0x084 */
	volatile uint32_t INTSTATUS;			/* 0x088: Interrupt Status */
	uint32_t RESERVED_11;					/* 0x08c */
	volatile uint32_t INTSIGNAL_ENABLEREG;	/* 0x090: Interrupt Signal Enable */
	uint32_t RESERVED_12;					/* 0x094 */
	volatile uint32_t INTCLEARREG;			/* 0x098: Interrupt Clear */
} DMAC_CHx_TypeDef;

/* Peripheral Base Definitions */
#define DMAC_BASE		(0x04330000ull)
#define DMAC_CH1_BASE	(DMAC_BASE+0x100ull)
#define DMAC_CH2_BASE	(DMAC_BASE+0x200ull)
#define DMAC_CH3_BASE	(DMAC_BASE+0x300ull)
#define DMAC_CH4_BASE	(DMAC_BASE+0x400ull)
#define DMAC_CH5_BASE	(DMAC_BASE+0x500ull)
#define DMAC_CH6_BASE	(DMAC_BASE+0x600ull)
#define DMAC_CH7_BASE	(DMAC_BASE+0x700ull)
#define DMAC_CH8_BASE	(DMAC_BASE+0x800ull)

/* Instance Pointers */
#define DMAC		((DMAC_TypeDef *)DMAC_BASE)
#define DMAC_CH1	((DMAC_CHx_TypeDef *)DMAC_CH1_BASE)
#define DMAC_CH2	((DMAC_CHx_TypeDef *)DMAC_CH2_BASE)
#define DMAC_CH3	((DMAC_CHx_TypeDef *)DMAC_CH3_BASE)
#define DMAC_CH4	((DMAC_CHx_TypeDef *)DMAC_CH4_BASE)
#define DMAC_CH5	((DMAC_CHx_TypeDef *)DMAC_CH5_BASE)
#define DMAC_CH6	((DMAC_CHx_TypeDef *)DMAC_CH6_BASE)
#define DMAC_CH7	((DMAC_CHx_TypeDef *)DMAC_CH7_BASE)
#define DMAC_CH8	((DMAC_CHx_TypeDef *)DMAC_CH8_BASE)

/* Register fields */
#define DMAC_CFGREG_DMAC_EN		(1ull<<0)
#define DMAC_CFGREG_INT_EN		(1ull<<1)
#define DMAC_CHENREG_CH1_EN			(1ull<<0)
#define DMAC_CHENREG_CH2_EN			(1ull<<1)
#define DMAC_CHENREG_CH3_EN			(1ull<<2)
#define DMAC_CHENREG_CH4_EN			(1ull<<3)
#define DMAC_CHENREG_CH5_EN			(1ull<<4)
#define DMAC_CHENREG_CH6_EN			(1ull<<5)
#define DMAC_CHENREG_CH7_EN			(1ull<<6)
#define DMAC_CHENREG_CH8_EN			(1ull<<7)
#define DMAC_CHENREG_CH1_EN_WE		(1ull<<8)
#define DMAC_CHENREG_CH2_EN_WE		(1ull<<9)
#define DMAC_CHENREG_CH3_EN_WE		(1ull<<10)
#define DMAC_CHENREG_CH4_EN_WE		(1ull<<11)
#define DMAC_CHENREG_CH5_EN_WE		(1ull<<12)
#define DMAC_CHENREG_CH6_EN_WE		(1ull<<13)
#define DMAC_CHENREG_CH7_EN_WE		(1ull<<14)
#define DMAC_CHENREG_CH8_EN_WE		(1ull<<15)
#define DMAC_CHENREG_CH1_SUSP		(1ull<<16)
#define DMAC_CHENREG_CH2_SUSP		(1ull<<17)
#define DMAC_CHENREG_CH3_SUSP		(1ull<<18)
#define DMAC_CHENREG_CH4_SUSP		(1ull<<19)
#define DMAC_CHENREG_CH5_SUSP		(1ull<<20)
#define DMAC_CHENREG_CH6_SUSP		(1ull<<21)
#define DMAC_CHENREG_CH7_SUSP		(1ull<<22)
#define DMAC_CHENREG_CH8_SUSP		(1ull<<23)
#define DMAC_CHENREG_CH1_SUSP_WE	(1ull<<24)
#define DMAC_CHENREG_CH2_SUSP_WE	(1ull<<25)
#define DMAC_CHENREG_CH3_SUSP_WE	(1ull<<26)
#define DMAC_CHENREG_CH4_SUSP_WE	(1ull<<27)
#define DMAC_CHENREG_CH5_SUSP_WE	(1ull<<28)
#define DMAC_CHENREG_CH6_SUSP_WE	(1ull<<29)
#define DMAC_CHENREG_CH7_SUSP_WE	(1ull<<30)
#define DMAC_CHENREG_CH8_SUSP_WE	(1ull<<31)
#define DMAC_CHENREG_CH1_ABORT		(1ull<<32)
#define DMAC_CHENREG_CH2_ABORT		(1ull<<33)
#define DMAC_CHENREG_CH3_ABORT		(1ull<<34)
#define DMAC_CHENREG_CH4_ABORT		(1ull<<35)
#define DMAC_CHENREG_CH5_ABORT		(1ull<<36)
#define DMAC_CHENREG_CH6_ABORT		(1ull<<37)
#define DMAC_CHENREG_CH7_ABORT		(1ull<<38)
#define DMAC_CHENREG_CH8_ABORT		(1ull<<39)
#define DMAC_CHENREG_CH1_ABORT_WE	(1ull<<40)
#define DMAC_CHENREG_CH2_ABORT_WE	(1ull<<41)
#define DMAC_CHENREG_CH3_ABORT_WE	(1ull<<42)
#define DMAC_CHENREG_CH4_ABORT_WE	(1ull<<43)
#define DMAC_CHENREG_CH5_ABORT_WE	(1ull<<44)
#define DMAC_CHENREG_CH6_ABORT_WE	(1ull<<45)
#define DMAC_CHENREG_CH7_ABORT_WE	(1ull<<46)
#define DMAC_CHENREG_CH8_ABORT_WE	(1ull<<47)
#define DMAC_INTSTATUSREG_CH1_INTSTAT	(1ull<<0)
#define DMAC_INTSTATUSREG_CH2_INTSTAT	(1ull<<1)
#define DMAC_INTSTATUSREG_CH3_INTSTAT	(1ull<<2)
#define DMAC_INTSTATUSREG_CH4_INTSTAT	(1ull<<3)
#define DMAC_INTSTATUSREG_CH5_INTSTAT	(1ull<<4)
#define DMAC_INTSTATUSREG_CH6_INTSTAT	(1ull<<5)
#define DMAC_INTSTATUSREG_CH7_INTSTAT	(1ull<<6)
#define DMAC_INTSTATUSREG_CH8_INTSTAT	(1ull<<7)
#define DMAC_INTSTATUSREG_COMMONREG_INTSTAT	(1ull<<16)
#define DMAC_CHX_CTL_SMS	(1ull<<0)
#define DMAC_CHX_CTL_DMS	(1ull<<2)
#define DMAC_CHX_CTL_SINC	(1ull<<4)
#define DMAC_CHX_CTL_DINC	(1ull<<6)
#define DMAC_CHX_CTL_SRC_TR_WIDTH_POS	(8)
#define DMAC_CHX_CTL_SRC_TR_WIDTH_MASK	(0x7ull)
#define DMAC_CHX_CTL_SRC_TR_WIDTH		(DMAC_CHX_CTL_SRC_TR_WIDTH_MASK<<DMAC_CHX_CTL_SRC_TR_WIDTH_POS)
#define DMAC_CHX_CTL_DST_TR_WIDTH_POS	(11)
#define DMAC_CHX_CTL_DST_TR_WIDTH_MASK	(0x7ull)
#define DMAC_CHX_CTL_DST_TR_WIDTH		(DMAC_CHX_CTL_SRC_TR_WIDTH_MASK<<DMAC_CHX_CTL_SRC_TR_WIDTH_POS)
#define DMAC_CHX_CTL_SRC_MSZ_POS	(14)
#define DMAC_CHX_CTL_SRC_MSZ_MASK	(0xfull)
#define DMAC_CHX_CTL_SRC_MSZ		(DMAC_CHX_CTL_SRC_MSZ_MASK<<DMAC_CHX_CTL_SRC_MSZ_POS)
#define DMAC_CHX_CTL_DST_MSZ_POS	(18)
#define DMAC_CHX_CTL_DST_MSZ_MASK	(0xfull)
#define DMAC_CHX_CTL_DST_MSZ		(DMAC_CHX_CTL_SRC_MSZ_MASK<<DMAC_CHX_CTL_SRC_MSZ_POS)
#define DMAC_CHX_CTL_AR_CACHE_POS	(22)
#define DMAC_CHX_CTL_AR_CACHE_MASK	(0xfull)
#define DMAC_CHX_CTL_AR_CACHE		(DMAC_CHX_CTL_AR_CACHE_MASK<<DMAC_CHX_CTL_AR_CACHE_POS)
#define DMAC_CHX_CTL_AW_CACHE_POS	(26)
#define DMAC_CHX_CTL_AW_CACHE_MASK	(0xfull)
#define DMAC_CHX_CTL_AW_CACHE		(DMAC_CHX_CTL_SRC_AR_CACHE_MASK<<DMAC_CHX_CTL_SRC_AR_CACHE_POS)
#define DMAC_CHX_CTL_DST_NONPOSTED_LASTWRITE_EN		(1ull<<30)
#define DMAC_CHX_CTL_AR_PROT_POS	(32)
#define DMAC_CHX_CTL_AR_PROT_MASK	(0x7ull)
#define DMAC_CHX_CTL_AR_PROT		(DMAC_CHX_CTL_AR_PROT_MASK<<DMAC_CHX_CTL_AR_PROT_POS)
#define DMAC_CHX_CTL_AW_PROT_POS	(35)
#define DMAC_CHX_CTL_AW_PROT_MASK	(0x7ull)
#define DMAC_CHX_CTL_AW_PROT		(DMAC_CHX_CTL_SRC_AR_PROT_MASK<<DMAC_CHX_CTL_SRC_AR_PROT_POS)
#define DMAC_CHX_CTL_ARLEN_EN		(1ull<<38)
#define DMAC_CHX_CTL_ARLEN_POS		(39)
#define DMAC_CHX_CTL_ARLEN_MASK		(0xffull)
#define DMAC_CHX_CTL_ARLEN			(DMAC_CHX_CTL_ARLEN_MASK<<DMAC_CHX_CTL_ARLEN_POS)
#define DMAC_CHX_CTL_AWLEN_EN		(1ull<<47)
#define DMAC_CHX_CTL_AWLEN_POS		(48)
#define DMAC_CHX_CTL_AWLEN_MASK		(0xffull)
#define DMAC_CHX_CTL_AWLEN			(DMAC_CHX_CTL_AWLEN_MASK<<DMAC_CHX_CTL_AWLEN_POS)
#define DMAC_CHX_CTL_SRC_STAT_EN	(1ull<<56)
#define DMAC_CHX_CTL_DST_STAT_EN	(1ull<<57)
#define DMAC_CHX_CTL_IOC_BLKTFR		(1ull<<58)
#define DMAC_CHX_CTL_SHADOWREG_OR_LLI_LAST		(1ull<<62)
#define DMAC_CHX_CTL_SHADOWREG_OR_LLI_VALID		(1ull<<63)
#define DMAC_CHX_CFG_SRC_MULTBLK_TYPE_POS	(0)
#define DMAC_CHX_CFG_SRC_MULTBLK_TYPE_MASK	(0x3ull)
#define DMAC_CHX_CFG_SRC_MULTBLK_TYPE		(DMAC_CHX_CFG_SRC_MULTBLK_TYPE_MASK<<DMAC_CHX_CFG_SRC_MULTBLK_TYPE_POS)
#define DMAC_CHX_CFG_DST_MULTBLK_TYPE_POS	(2)
#define DMAC_CHX_CFG_DST_MULTBLK_TYPE_MASK	(0x3ull)
#define DMAC_CHX_CFG_DST_MULTBLK_TYPE		(DMAC_CHX_CFG_DST_MULTBLK_TYPE_MASK<<DMAC_CHX_CFG_DST_MULTBLK_TYPE_POS)
#define DMAC_CHX_CFG_TT_FC_POS	(32)
#define DMAC_CHX_CFG_TT_FC_MASK	(0x3ull)
#define DMAC_CHX_CFG_TT_FC		(DMAC_CHX_CFG_TT_FC_MASK<<DMAC_CHX_CFG_TT_FC_POS)
#define DMAC_CHX_CFG_HS_SEL_SRC	(1ull<<35)
#define DMAC_CHX_CFG_HS_SEL_DST	(1ull<<36)
#define DMAC_CHX_CFG_SRC_HW_HSPOL	(1ull<<37)
#define DMAC_CHX_CFG_DST_HW_HSPOL	(1ull<<38)
#define DMAC_CHX_CFG_SRC_PER	(1ull<<39)
#define DMAC_CHX_CFG_DST_PER	(1ull<<44)
#define DMAC_CHX_CFG_CH_PRIOR_POS	(49)
#define DMAC_CHX_CFG_CH_PRIOR_MASK	(0x7ull)
#define DMAC_CHX_CFG_CH_PRIOR		(DMAC_CHX_CFG_CH_PRIOR_MASK<<DMAC_CHX_CFG_CH_PRIOR_POS)
#define DMAC_CHX_CFG_LOCK_CH	(1ull<<52)
#define DMAC_CHX_CFG_LOCK_CH_L_POS	(53)
#define DMAC_CHX_CFG_LOCK_CH_L_MASK	(0x3ull)
#define DMAC_CHX_CFG_LOCK_CH_L		(DMAC_CHX_CFG_LOCK_CH_L_MASK<<DMAC_CHX_CFG_LOCK_CH_L_POS)
#define DMAC_CHX_CFG_SRC_OSR_LMT_POS	(55)
#define DMAC_CHX_CFG_SRC_OSR_LMT_MASK	(0xfull)
#define DMAC_CHX_CFG_SRC_OSR_LMT		(DMAC_CHX_CFG_SRC_OSR_LMT_MASK<<DMAC_CHX_CFG_SRC_OSR_LMT_POS)
#define DMAC_CHX_CFG_DST_OSR_LMT_POS	(59)
#define DMAC_CHX_CFG_DST_OSR_LMT_MASK	(0xfull)
#define DMAC_CHX_CFG_DST_OSR_LMT		(DMAC_CHX_CFG_DST_OSR_LMT_MASK<<DMAC_CHX_CFG_DST_OSR_LMT_POS)
#define DMAC_CHX_LLP_LMS	(1ull<<0)
#define DMAC_CHX_LLP_LOC_POS	(6)
#define DMAC_CHX_LLP_LOC_MASK	(0x3fffffffffffffffull)
#define DMAC_CHX_LLP_LOC		(DMAC_CHX_LLP_LOC_MASK<<DMAC_CHX_LLP_LOC_POS)
#define DMAC_CHX_STATUSREG_POS	(6)
#define DMAC_CHX_STATUSREG_MASK	(0x3fffffffffffffffull)
#define DMAC_CHX_STATUSREG		(DMAC_CHX_STATUSREG_MASK<<DMAC_CHX_STATUSREG_POS)
#define DMAC_CHX_STATUSREG_CMPLTD_BLK_TFR_SIZE_POS	(0)
#define DMAC_CHX_STATUSREG_CMPLTD_BLK_TFR_SIZE_MASK	(0x3fffffull)
#define DMAC_CHX_STATUSREG_CMPLTD_BLK_TFR_SIZE		(DMAC_CHX_STATUSREG_CMPLTD_BLK_TFR_SIZE_MASK<<DMAC_CHX_STATUSREG_CMPLTD_BLK_TFR_SIZE_POS)
#define DMAC_CHX_STATUSREG_DATA_LEFT_IN_FIFO_POS	(32)
#define DMAC_CHX_STATUSREG_DATA_LEFT_IN_FIFO_MASK	(0x3fffull)
#define DMAC_CHX_STATUSREG_DATA_LEFT_IN_FIFO		(DMAC_CHX_STATUSREG_DATA_LEFT_IN_FIFO_MASK<<DMAC_CHX_STATUSREG_DATA_LEFT_IN_FIFO_POS)

#ifdef __cplusplus
}
#endif

#endif /* SDMA_H */