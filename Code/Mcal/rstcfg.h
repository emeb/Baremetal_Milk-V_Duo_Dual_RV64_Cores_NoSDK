/******************************************************************************************
  Filename    : rstcfg.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.07.2026
  
  Description : Reset Configuration peripheral header file
  
******************************************************************************************/

#ifndef RSTCFG_H
#define RSTCFG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct  RSTCFG_TypeDef
 * @brief   RSTCFG Register Layout
 */
typedef struct {
	volatile uint32_t SOFT_RSTN_0;			/* 0x000: clock enable register 0 */
	volatile uint32_t SOFT_RSTN_1;			/* 0x004: clock enable register 1 */
	volatile uint32_t SOFT_RSTN_2;			/* 0x008: clock enable register 2 */
	volatile uint32_t SOFT_RSTN_3;			/* 0x00c: clock enable register 3 */
	uint32_t RESERVED_0[4];
	volatile uint32_t SOFT_CPUAC_RSTN;		/* 0x020: clock source selection register 0 */
	volatile uint32_t SOFT_CPU_RSTN;		/* 0x024: clock source selection register 0 */
} RSTCFG_TypeDef;

/* Peripheral Base Definitions */
#define RSTCFG_BASE    (0x03003000ull)

/* Instance Pointers */
#define RSTCFG    ((RSTCFG_TypeDef *)RSTCFG_BASE)

#ifdef __cplusplus
}
#endif

#endif /* RSTCFG_H */
