/******************************************************************************************
  Filename    : saradc.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.16.2026
  
  Description : SARADC peripheral header file
  
******************************************************************************************/

#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HW_SARADC SARADC

/**
 * @struct  SARADC_TypeDef
 * @brief   SARADC Register Layout
 */
typedef struct {
    uint32_t RESERVED_0;				/* 0x000 */
	volatile uint32_t saradc_ctrl;		/* 0x004: control register */
	volatile uint32_t saradc_status;	/* 0x008: staus register */
	volatile uint32_t saradc_cyc_set;	/* 0x00c: saradc waveform setting register */
	uint32_t RESERVED_1;				/* 0x010 */
	volatile uint32_t saradc_ch1_result;/* 0x014: channel 1 result register */
	volatile uint32_t saradc_ch2_result;/* 0x018: channel 2 result register */
	volatile uint32_t saradc_ch3_result;/* 0x01c: channel 3 result register */
	volatile uint32_t saradc_intr_en;	/* 0x020: interrupt enable register */
	volatile uint32_t saradc_intr_clr;	/* 0x024: interrupt clear register */
	volatile uint32_t saradc_intr_sta;	/* 0x028: interrupt status register */
	volatile uint32_t saradc_intr_raw;	/* 0x02c: interrupt raw status register */
	volatile uint32_t saradc_test;		/* 0x030: undocumented Enable self-test mode, active high*/
	volatile uint32_t saradc_trim;		/* 0x034: undocumented trim register */
	volatile uint32_t saradc_period_cycle;	/* 0x038: undocumented bit[0]-bit[23] auto measure in a period */
	uint32_t RESERVED_2;				/* 0x03c */
	volatile uint32_t saradc_test_force;/* 0x040: undocumented */
} SARADC_TypeDef;

/* Peripheral Base Definitions */
#define SARADC_BASE    (0x030F0000ull)

/* Instance Pointers */
#define SARADC    ((SARADC_TypeDef *)SARADC_BASE)

/* channels */
#define SARADC_CHL1 1
#define SARADC_CHL2 (1<<1)
#define SARADC_CHL3 (1<<2)

/* Register fields */
#define SARADC_CTRL_EN 1
#define SARADC_CTRL_SEL1 (1<<4)
#define SARADC_CTRL_SEL2 (1<<5)
#define SARADC_CTRL_SEL3 (1<<6)
#define SARADC_STATUS_BUSY 1
#define SARADC_STATUS_CH0_BUSY (1<<4)
#define SARADC_STATUS_CH1_BUSY (1<<5)
#define SARADC_STATUS_CH2_BUSY (1<<6)
#define SARADC_CYC_SETTLING 0x1f
#define SARADC_CYC_SAMP (0x7<<8)
#define SARADC_CYC_CLKDIV (0xf<<12)
#define SARADC_CYC_COMP (0xf<<16)

/* Functions */
uint32_t saradc_init(SARADC_TypeDef *saradc, uint8_t chls);
uint32_t saradc_getchl(SARADC_TypeDef *saradc, uint8_t chl, uint16_t *result);

#ifdef __cplusplus
}
#endif

#endif /* SARADC_H */