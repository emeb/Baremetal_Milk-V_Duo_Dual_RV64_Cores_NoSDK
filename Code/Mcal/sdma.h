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
	volatile uint64_t LLP;					/* 0x028: Configuration */
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

#ifdef __cplusplus
}
#endif

#endif /* SDMA_H */