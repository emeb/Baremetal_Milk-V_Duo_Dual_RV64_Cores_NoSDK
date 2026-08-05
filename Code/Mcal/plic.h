/******************************************************************************************
  Filename    : plic.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 03.08.2026
  
  Description : PLIC header file
  
******************************************************************************************/

#ifndef PLIC_H
#define PLIC_H

#include <stdint.h>
#include "core.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PLIC_IP_OFFSET		(0x0001000ull)
#define PLIC_IE_OFFSET		(0x0002000ull)
#define PLIC_MTH_OFFSET		(0x0200000ull)
#define PLIC_STH_OFFSET		(0x0201000ull)

enum {
	PLIC0_IRQ_TEMPSENS = 16,
	PLIC0_IRQ_RTC_ALARM,
	PLIC0_IRQ_RTC_LONGPRESS,
	PLIC0_IRQ_VBAT_DET,
	PLIC0_IRQ_JPEG,			// 20
	PLIC0_IRQ_H264,
	PLIC0_IRQ_H265,
	PLIC0_IRQ_VCSBM,
	PLIC0_IRQ_ISP,
	PLIC0_IRQ_SC_TOP,		// 25
	PLIC0_IRQ_CSI_MAC0,
	PLIC0_IRQ_CSI_MAC1,
	PLIC0_IRQ_LDC,
	PLIC0_IRQ_SYS_DMA,
	PLIC0_IRQ_USB,			// 30
	PLIC0_IRQ_ETH0_SBD,
	PLIC0_IRQ_ETH0_LPI,
	PLIC0_IRQ_EMMC_WKUP,
	PLIC0_IRQ_EMMC,
	PLIC0_IRQ_SD0_WKUP,		// 35
	PLIC0_IRQ_SD0,
	PLIC0_IRQ_SD1_WKUP,
	PLIC0_IRQ_SD1,
	PLIC0_IRQ_SPI_NAND,
	PLIC0_IRQ_I2S0,			// 40
	PLIC0_IRQ_I2S1,
	PLIC0_IRQ_I2S2,
	PLIC0_IRQ_I2S3,
	PLIC0_IRQ_UART0,
	PLIC0_IRQ_UART1,		// 45
	PLIC0_IRQ_UART2,
	PLIC0_IRQ_UART3,
	PLIC0_IRQ_UART4,
	PLIC0_IRQ_I2C0,
	PLIC0_IRQ_I2C1,			// 50
	PLIC0_IRQ_I2C2,
	PLIC0_IRQ_I2C3,
	PLIC0_IRQ_I2C4,
	PLIC0_IRQ_SPI0_SSI,
	PLIC0_IRQ_SPI1_SSI,		// 55
	PLIC0_IRQ_SPI2_SSI,
	PLIC0_IRQ_SPI3_SSI,
	PLIC0_IRQ_WDT,
	PLIC0_IRQ_KEYSCAN,
	PLIC0_IRQ_GPIO0,		// 60
	PLIC0_IRQ_GPIO1,
	PLIC0_IRQ_GPIO2,
	PLIC0_IRQ_GPIO3,
	PLIC0_IRQ_WGN0,
	PLIC0_IRQ_WGN1,			// 65
	PLIC0_IRQ_WGN2,
	PLIC0_IRQ_RTC_MBOX,
	PLIC0_IRQ_RTC_IRRX = 69,
	PLIC0_IRQ_RTC_GPIO,		// 70
	PLIC0_IRQ_RTC_UART,
	PLIC0_IRQ_RTC_SPI_NOR,
	PLIC0_IRQ_RTC_I2C,
	PLIC0_IRQ_RTC_WDT,
	PLIC0_IRQ_TPU,			// 75
	PLIC0_IRQ_TDMA,
	PLIC0_IRQ_SWI0,
	PLIC0_IRQ_SWI1,
	PLIC0_IRQ_TIM0,
	PLIC0_IRQ_TIM1,			// 80
	PLIC0_IRQ_TIM2,
	PLIC0_IRQ_TIM3,
	PLIC0_IRQ_TIM4,
	PLIC0_IRQ_TIM5,
	PLIC0_IRQ_TIM6,			// 85
	PLIC0_IRQ_TIM7,
	PLIC0_IRQ_PERI_FW,
	PLIC0_IRQ_HSPERI_FW,
	PLIC0_IRQ_DDR_FW,
	PLIC0_IRQ_ROM_FW,		// 90
	PLIC0_IRQ_SPACC,
	PLIC0_IRQ_TRNG,
	PLIC0_IRQ_DDR_AXI_MON,
	PLIC0_IRQ_DDR_PI_PHY,
	PLIC0_IRQ_SPI_NOR,		// 95
	PLIC0_IRQ_EPHY,
	PLIC0_IRQ_IVE,
	PLIC0_IRQ_DBGSYS = 99,
	PLIC0_IRQ_SARADC,		// 100
	PLIC0_IRQ_MBOX,
};

enum {
	PLIC1_IRQ_JPEG = 16,
	PLIC1_IRQ_H264,
	PLIC1_IRQ_H265,
	PLIC1_IRQ_VCSBM,
	PLIC1_IRQ_ISP,			// 20
	PLIC1_IRQ_SC_TOP,
	PLIC1_IRQ_CSI_MAC0,
	PLIC1_IRQ_CSI_MAC1,
	PLIC1_IRQ_LDC,
	PLIC1_IRQ_SYS_DMA,		// 25
	PLIC1_IRQ_I2S0,
	PLIC1_IRQ_I2S1,
	PLIC1_IRQ_I2S2,
	PLIC1_IRQ_I2S3,
	PLIC1_IRQ_UART0,		// 30
	PLIC1_IRQ_UART1,
	PLIC1_IRQ_I2C0,
	PLIC1_IRQ_I2C1,
	PLIC1_IRQ_I2C2,
	PLIC1_IRQ_I2C3,			// 35
	PLIC1_IRQ_I2C4,
	PLIC1_IRQ_SPI0_SSI,
	PLIC1_IRQ_SPI1_SSI,
	PLIC1_IRQ_WDT,
	PLIC1_IRQ_KEYSCAN,		// 40
	PLIC1_IRQ_GPIO0,
	PLIC1_IRQ_GPIO1,
	PLIC1_IRQ_GPIO2,
	PLIC1_IRQ_GPIO3,
	PLIC1_IRQ_WGN0,			// 45
	PLIC1_IRQ_RTC_MBOX,
	PLIC1_IRQ_RTC_IRRX,
	PLIC1_IRQ_RTC_GPIO,
	PLIC1_IRQ_RTC_UART,
	PLIC1_IRQ_RTC_I2C,		// 50
	PLIC1_IRQ_RTC_WDT,
	PLIC1_IRQ_TDMA,
	PLIC1_IRQ_SWI0,
	PLIC1_IRQ_SWI1,
	PLIC1_IRQ_TIM4,			// 55
	PLIC1_IRQ_TIM5,
	PLIC1_IRQ_TIM6,
	PLIC1_IRQ_TIM7,
	PLIC1_IRQ_SPACC,
	PLIC1_IRQ_EPHY,			// 60
	PLIC1_IRQ_MBOX,
};

uint32_t plic_get_priority(uint32_t irqnum);
void plic_set_priority(uint32_t irqnum, uint32_t priority);
uint32_t plic_get_pending(uint32_t irqnum);
void plic_set_pending(uint32_t irqnum, uint32_t enable);
uint32_t plic_get_enable(uint32_t irqnum, uint32_t supervisor);
void plic_set_enable(uint32_t irqnum, uint32_t supervisor, uint32_t enable);
uint32_t plic_get_thresh(uint32_t supervisor);
void plic_set_thresh(uint32_t supervisor, uint32_t thresh);
uint32_t plic_get_claim(uint32_t supervisor);
void plic_set_claim(uint32_t supervisor, uint32_t claim);

#ifdef __cplusplus
}
#endif

#endif /* PLIC_H */