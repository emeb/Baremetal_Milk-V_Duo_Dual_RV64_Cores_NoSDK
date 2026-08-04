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

#ifdef __cplusplus
extern "C" {
#endif

#define PLIC_BASE    		(0x70000000ull)
#define PLIC_IP_OFFSET		(0x0001000ull)
#define PLIC_IE_OFFSET		(0x0002000ull)
#define PLIC_MTH_OFFSET		(0x0200000ull)
#define PLIC_STH_OFFSET		(0x0201000ull)

enum {
	PLIC_IRQ_TEMPSENS = 16,
	PLIC_IRQ_RTC_ALARM,
	PLIC_IRQ_RTC_LONGPRESS,
	PLIC_IRQ_VBAT_DET,
	PLIC_IRQ_JPEG,			// 20
	PLIC_IRQ_H264,
	PLIC_IRQ_H265,
	PLIC_IRQ_VCSBM,
	PLIC_IRQ_ISP,
	PLIC_IRQ_SC_TOP,		// 25
	PLIC_IRQ_CSI_MAC0,
	PLIC_IRQ_CSI_MAC1,
	PLIC_IRQ_LDC,
	PLIC_IRQ_SYS_DMA,
	PLIC_IRQ_USB,			// 30
	PLIC_IRQ_ETH0_SBD,
	PLIC_IRQ_ETH0_LPI,
	PLIC_IRQ_EMMC_WKUP,
	PLIC_IRQ_EMMC,
	PLIC_IRQ_SD0_WKUP,		// 35
	PLIC_IRQ_SD0,
	PLIC_IRQ_SD1_WKUP,
	PLIC_IRQ_SD1,
	PLIC_IRQ_SPI_NAND,
	PLIC_IRQ_I2S0,			// 40
	PLIC_IRQ_I2S1,
	PLIC_IRQ_I2S2,
	PLIC_IRQ_I2S3,
	PLIC_IRQ_UART0,
	PLIC_IRQ_UART1,			// 45
	PLIC_IRQ_UART2,
	PLIC_IRQ_UART3,
	PLIC_IRQ_UART4,
	PLIC_IRQ_I2C0,
	PLIC_IRQ_I2C1,			// 50
	PLIC_IRQ_I2C2,
	PLIC_IRQ_I2C3,
	PLIC_IRQ_I2C4,
	PLIC_IRQ_SPI0_SSI,
	PLIC_IRQ_SPI1_SSI,		// 55
	PLIC_IRQ_SPI2_SSI,
	PLIC_IRQ_SPI3_SSI,
	PLIC_IRQ_WDT,
	PLIC_IRQ_KEYSCAN,
	PLIC_IRQ_GPIO0,			// 60
	PLIC_IRQ_GPIO1,
	PLIC_IRQ_GPIO2,
	PLIC_IRQ_GPIO3,
	PLIC_IRQ_WGN0,
	PLIC_IRQ_WGN1,			// 65
	PLIC_IRQ_WGN2,
	PLIC_IRQ_RTC_MBOX,
	PLIC_IRQ_RTC_IRRX = 69,
	PLIC_IRQ_RTC_GPIO,		// 70
	PLIC_IRQ_RTC_UART,
	PLIC_IRQ_RTC_SPI_NOR,
	PLIC_IRQ_RTC_I2C,
	PLIC_IRQ_RTC_WDT,
	PLIC_IRQ_TPU,			// 75
	PLIC_IRQ_TDMA,
	PLIC_IRQ_SWI0,
	PLIC_IRQ_SWI1,
	PLIC_IRQ_TIM0,
	PLIC_IRQ_TIM1,			// 80
	PLIC_IRQ_TIM2,
	PLIC_IRQ_TIM3,
	PLIC_IRQ_TIM4,
	PLIC_IRQ_TIM5,
	PLIC_IRQ_TIM6,			// 85
	PLIC_IRQ_TIM7,
	PLIC_IRQ_PERI_FW,
	PLIC_IRQ_HSPERI_FW,
	PLIC_IRQ_DDR_FW,
	PLIC_IRQ_ROM_FW,		// 90
	PLIC_IRQ_SPACC,
	PLIC_IRQ_TRNG,
	PLIC_IRQ_DDR_AXI_MON,
	PLIC_IRQ_DDR_PI_PHY,
	PLIC_IRQ_SPI_NOR,		// 95
	PLIC_IRQ_EPHY,
	PLIC_IRQ_IVE,
	PLIC_IRQ_DBGSYS = 99,
	PLIC_IRQ_SARADC,		// 100
	PLIC_IRQ_MBOX,
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