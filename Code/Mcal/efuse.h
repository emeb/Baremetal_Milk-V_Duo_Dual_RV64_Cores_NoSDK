/******************************************************************************************
  Filename    : efuse.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.16.2026
  
  Description : EFUSE peripheral header file
  
******************************************************************************************/

#ifndef EFUSE_H
#define EFUSE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct  EFUSE_TypeDef
 * @brief   EFUSE Register Layout
 */
typedef struct {
    volatile uint32_t EFUSE_MODE;		/* 0x000: */
	volatile uint32_t EFUSE_ADR;		/* 0x004: */
	volatile uint32_t EFUSE_DIR_CMD;	/* 0x008: */
	volatile uint32_t EFUSE_RD_DATA;	/* 0x00c: */
	volatile uint32_t EFUSE_STATUS;		/* 0x010: */
	volatile uint32_t EFUSE_ONE_WAY;	/* 0x014: */
	volatile uint32_t PGM_PLUSE_WIDTH;	/* 0x018: */
	volatile uint32_t A_READ_WIDTH;		/* 0x01c: */
	volatile uint32_t M_READ_WIDTH;		/* 0x020: */
	uint32_t RESERVED_0[55];			/* 0x024 - 0x100 */
	volatile uint32_t FTSN0;			/* 0x100: Efuse Register contents */
	volatile uint32_t FTSN1;			/* 0x104: Efuse Register contents */
	volatile uint32_t FTSN2;			/* 0x108: Efuse Register contents */
	volatile uint32_t FTSN3;			/* 0x10c: Efuse Register contents */
	volatile uint32_t FTSN4;			/* 0x110: Efuse Register contents */
	volatile uint32_t eFuse_FT_Debug;	/* 0x114: Efuse Register contents */
	volatile uint32_t Analog0;			/* 0x118: Efuse Register contents */
	volatile uint32_t Analog1;			/* 0x11c: Efuse Register contents */
	volatile uint32_t Analog2;			/* 0x120: Efuse Register contents */
	volatile uint32_t Analog3;			/* 0x124: Efuse Register contents */
	volatile uint32_t Bonding0;			/* 0x128: Efuse Register contents */
	volatile uint32_t SW_info;			/* 0x12c: Efuse Register contents */
	volatile uint32_t SW_reserved30;	/* 0x130: Efuse Register contents */
	volatile uint32_t SW_reserved34;	/* 0x134: Efuse Register contents */
	volatile uint32_t SW_reserved38;	/* 0x138: Efuse Register contents */
	volatile uint32_t SW_reserved3c;	/* 0x13c: Efuse Register contents */
	/* lots more not included - up to 0x1c4 */
} EFUSE_TypeDef;

/* Peripheral Base Definitions */
#define EFUSE_BASE    (0x03050000ull)

/* Instance Pointers */
#define EFUSE    ((EFUSE_TypeDef *)EFUSE_BASE)

/* Register fields */

#ifdef __cplusplus
}
#endif

#endif /* EFUSE_H */