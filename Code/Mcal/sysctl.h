/******************************************************************************************
  Filename    : sysctl.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 06.08.2026
  
  Description : System Control header file
  
******************************************************************************************/

#ifndef SYSCTL_H
#define SYSCTL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct  SYSCTL_TypeDef
 * @brief   System Control Register Layout
 */
typedef struct {
	uint32_t RESERVED_0;					/* 0x000 */
	volatile uint32_t conf_info;			/* 0x004: conf_info */
	volatile uint32_t sys_ctrl_reg;			/* 0x008: sys_ctrl_reg */
	uint32_t RESERVED_1[14];				/* 0x00c - 0x040 */
	volatile uint32_t usb_phy_ctrl_reg;		/* 0x048: usb_phy_ctrl_reg */
	uint32_t RESERVED_2[66];				/* 0x04c - 0x150 */
	volatile uint32_t sdma_dma_ch_remap[2];	/* 0x154 - 0x158 : sdma_dma_ch_remap0,1 */
	uint32_t RESERVED_3[17];				/* 0x15c - 0x19c */
	volatile uint32_t top_timer_clk_sel;	/* 0x1a0: top_timer_clk_sel */
	uint32_t RESERVED_4;					/* 0x1a4 */
	volatile uint32_t top_wdt_ctrl;			/* 0x1a8: top_timer_clk_sel */
	uint32_t RESERVED_5[3];					/* 0x1ac - 0x1b4 */
	volatile uint32_t ddr_axi_urgent_ow;	/* 0x1b8: ddr_axi_urgent_ow */
	volatile uint32_t ddr_axi_urgent;		/* 0x1bc: ddr_axi_urgent */
	uint32_t RESERVED_6[6];					/* 0x1c0 - 0x1d4 */
	volatile uint32_t ddr_axi_qos_0;		/* 0x1d8: ddr_axi_qos_0 */
	volatile uint32_t ddr_axi_qos_1;		/* 0x1dc: ddr_axi_qos_1 */
	uint32_t RESERVED_7[5];					/* 0x1e0 - 0x1f0 */
	volatile uint32_t sd_pwrsw_ctrl;		/* 0x1f4: sd_pwrsw_ctrl */
	volatile uint32_t sd_pwrsw_time;		/* 0x1f8: sd_pwrsw_time */
	uint32_t RESERVED_8[16];				/* 0x1fc - 0x238 */
	volatile uint32_t ddr_axi_qos_ow;		/* 0x23c: ddr_axi_qos_ow */
	uint32_t RESERVED_9[21];				/* 0x240 - 0x290 */
	volatile uint32_t sd_ctrl_opt;			/* 0x294: sd_ctrl_opt */
	volatile uint32_t sdma_dma_int_mux;		/* 0x298: sdma_dma_int_mux */
} SYSCTL_TypeDef;

/* Peripheral Base Definitions */
#define SYSCTL_BASE (0x03000000ull)

/* Instance Pointers */
#define SYSCTL    ((SYSCTL_TypeDef *)SYSCTL_BASE)

/* register definitions */
#define CONF_INFO_BOOT_SEL_POS					(0)
#define CONF_INFO_BOOT_SEL_MASK 				(0xFF)
#define CONF_INFO_IO_STA_USBID_POS				(9)
#define CONF_INFO_IO_STA_USBID_MASK				(1)
#define CONF_INFO_IO_STA_USBVBUS_POS			(10)
#define CONF_INFO_IO_STA_USBVBUS_MASK			(1)
#define CONF_INFO_IO_STA_TRAP_POS				(24)
#define CONF_INFO_IO_STA_TRAP_MASK				(0xFF)
#define SYS_CTRL_REG_REG_SW_ROOT_RESET_EN_POS	(2)
#define SYS_CTRL_REG_REG_SW_ROOT_RESET_EN_MASK	(0xF)

/* dma source enumeration */
enum {
	SYSCTL_SDMA_RX_REQ_I2S0,		// 0
	SYSCTL_SDMA_TX_REQ_I2S0,	
	SYSCTL_SDMA_RX_REQ_I2S1,
	SYSCTL_SDMA_TX_REQ_I2S1,
	SYSCTL_SDMA_RX_REQ_I2S2,
	SYSCTL_SDMA_TX_REQ_I2S2,		// 5
	SYSCTL_SDMA_RX_REQ_I2S3,
	SYSCTL_SDMA_TX_REQ_I2S3,
	SYSCTL_DMA_RX_REQ_N_UART0,
	SYSCTL_DMA_TX_REQ_N_UART0,
	SYSCTL_DMA_RX_REQ_N_UART1,		// 10
	SYSCTL_DMA_TX_REQ_N_UART1,
	SYSCTL_DMA_RX_REQ_N_UART2,
	SYSCTL_DMA_TX_REQ_N_UART2,
	SYSCTL_DMA_RX_REQ_N_UART3,
	SYSCTL_DMA_TX_REQ_N_UART3,		// 15
	SYSCTL_DMA_RX_REQ_SPI0,
	SYSCTL_DMA_TX_REQ_SPI0,
	SYSCTL_DMA_RX_REQ_SPI1,
	SYSCTL_DMA_TX_REQ_SPI1,
	SYSCTL_DMA_RX_REQ_SPI2,			// 20
	SYSCTL_DMA_TX_REQ_SPI2,
	SYSCTL_DMA_RX_REQ_SPI3,
	SYSCTL_DMA_TX_REQ_SPI3,
	SYSCTL_DMA_RX_REQ_I2C0,
	SYSCTL_DMA_TX_REQ_I2C0,			// 25
	SYSCTL_DMA_RX_REQ_I2C1,
	SYSCTL_DMA_TX_REQ_I2C1,
	SYSCTL_DMA_RX_REQ_I2C2,
	SYSCTL_DMA_TX_REQ_I2C2,
	SYSCTL_DMA_RX_REQ_I2C3,			// 30
	SYSCTL_DMA_TX_REQ_I2C3,
	SYSCTL_DMA_RX_REQ_I2C4,
	SYSCTL_DMA_TX_REQ_I2C4,
	SYSCTL_DMA_RX_REQ_TDM0,
	SYSCTL_DMA_TX_REQ_TDM0,			// 35
	SYSCTL_DMA_RX_REQ_TDM1,
	SYSCTL_DMA_REQ_AUDSRC,
	SYSCTL_DMA_REQ_SPI_NAND,
	SYSCTL_DMA_REQ_SPI_NOR,
	SYSCTL_DMA_RX_REQ_N_UART4,		// 40
	SYSCTL_DMA_TX_REQ_N_UART4,
	SYSCTL_DMA_REQ_SPI_NOR1,
};

/* functions */
void sysctl_sdma_ch_remap_set(uint32_t chl, uint32_t source);
uint32_t sysctl_sdma_ch_remap_get(uint32_t chl);

#ifdef __cplusplus
}
#endif

#endif /* SYSCTL_H */