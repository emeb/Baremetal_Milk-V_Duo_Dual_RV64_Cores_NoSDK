/******************************************************************************************
  Filename    : spi.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.10.2026
  
  Description : SPI peripheral header file
  
******************************************************************************************/

#ifndef SPI_H
#define SPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HW_SPI SPI2

/**
 * @struct  SPI_TypeDef
 * @brief   SPI Register Layout
 */
typedef struct {
	volatile uint32_t CTRLR0;	/* 0x000: Control Register 0 */
	volatile uint32_t CTRLR1;	/* 0x004: Control Register 1 */
	volatile uint32_t SPIENR;	/* 0x008: SPI Enable Register */
	volatile uint32_t MWCR;		/* 0x00c: Microwire Control Register */
	volatile uint32_t SER;		/* 0x010: Slave Enable Register */
	volatile uint32_t BAUDR;	/* 0x014: Baud Rate Select */
	volatile uint32_t TXFTLR;	/* 0x018: Transmit FIFO Threshold Level */
	volatile uint32_t RXFTLR;	/* 0x01c: Receive FIFO Threshold Level */
	volatile uint32_t TXFLR;	/* 0x020: Transmit FIFO Level Register */
	volatile uint32_t RXFLR;	/* 0x024: Receive FIFO Level Register */
	volatile uint32_t SR;		/* 0x028: Status Register */
	volatile uint32_t IMR;		/* 0x02c: Interrupt Mask Register */
	volatile uint32_t ISR;		/* 0x030: Interrupt Status Register */
	volatile uint32_t RISR;		/* 0x034: Raw Interrupt Status Register */
	volatile uint32_t TXOICR;	/* 0x038: Transmit FIFO Overflow Interrupt Clear Register */
	volatile uint32_t RXOICR;	/* 0x03c: Receive FIFO Overflow Interrupt Clear Register */
	volatile uint32_t RXUICR;	/* 0x040: Receive FIFO Underflow Interrupt Clear Register */
	volatile uint32_t MSTICR;	/* 0x044: Multi-Master Interrupt Clear Register */
	volatile uint32_t ICR;		/* 0x048: Interrupt Clear Register */
	volatile uint32_t DMACR;	/* 0x04c: DMA Control Register */
	volatile uint32_t DMATDLR;	/* 0x050: DMA Transmit Data Level */
	volatile uint32_t DMARDLR;	/* 0x054: DMA Receive Data Level */
    uint32_t RESERVED_0[2];		/* 0x058 - 0x05C */
	volatile uint32_t DR;		/* 0x060: Data Register */
    uint32_t RESERVED_1[35];	/* 0x064 - 0x0ec */
	volatile uint32_t RX_SAMPLE_DLY;/* 0x0f0: Rx Sample Delay Register */
} SPI_TypeDef;

/* Peripheral Base Definitions */
#define SPI0_BASE    (0x04180000ull)
#define SPI1_BASE    (0x04190000ull)
#define SPI2_BASE    (0x041A0000ull)
#define SPI3_BASE    (0x041B0000ull)

/* Instance Pointers */
#define SPI0    ((SPI_TypeDef *)SPI0_BASE)
#define SPI1    ((SPI_TypeDef *)SPI1_BASE)
#define SPI2    ((SPI_TypeDef *)SPI2_BASE)
#define SPI3    ((SPI_TypeDef *)SPI3_BASE)

/* Register fields */
#define SPI_CTRLR0_MWCTLFSZ_1BIT 0
#define SPI_CTRLR0_MWCTLFSZ_2BIT (0x1<<12)
#define SPI_CTRLR0_MWCTLFSZ_3BIT (0x2<<12)
#define SPI_CTRLR0_MWCTLFSZ_4BIT (0x3<<12)
#define SPI_CTRLR0_MWCTLFSZ_5BIT (0x4<<12)
#define SPI_CTRLR0_MWCTLFSZ_6BIT (0x5<<12)
#define SPI_CTRLR0_MWCTLFSZ_7BIT (0x6<<12)
#define SPI_CTRLR0_MWCTLFSZ_8BIT (0x7<<12)
#define SPI_CTRLR0_MWCTLFSZ_9BIT (0x8<<12)
#define SPI_CTRLR0_MWCTLFSZ_10BIT (0x9<<12)
#define SPI_CTRLR0_MWCTLFSZ_11BIT (0xa<<12)
#define SPI_CTRLR0_MWCTLFSZ_12BIT (0xb<<12)
#define SPI_CTRLR0_MWCTLFSZ_13BIT (0xc<<12)
#define SPI_CTRLR0_MWCTLFSZ_14BIT (0xd<<12)
#define SPI_CTRLR0_MWCTLFSZ_15BIT (0xe<<12)
#define SPI_CTRLR0_MWCTLFSZ_16BIT (0xf<<12)
#define SPI_CTRLR0_SHFR_LOOP (1<<11)
#define SPI_CTRLR0_XFR_MODE_TXRX 0
#define SPI_CTRLR0_XFR_MODE_TX (1<<8)
#define SPI_CTRLR0_XFR_MODE_RX (2<<8)
#define SPI_CTRLR0_XFR_MODE_EEPROM (3<<8)
#define SPI_CTRLR0_CLK_POL_LOW 0
#define SPI_CTRLR0_CLK_POL_HIGH (1<<7)
#define SPI_CTRLR0_CLK_PHS_MID 0
#define SPI_CTRLR0_CLK_PHS_START (1<<6)
#define SPI_CTRLR0_FORMAT_MOT 0
#define SPI_CTRLR0_FORMAT_TI (1<<4)
#define SPI_CTRLR0_FORMAT_NS (2<<4)
#define SPI_CTRLR0_DATASZ_4BIT 0x3
#define SPI_CTRLR0_DATASZ_5BIT 0x4
#define SPI_CTRLR0_DATASZ_6BIT 0x5
#define SPI_CTRLR0_DATASZ_7BIT 0x6
#define SPI_CTRLR0_DATASZ_8BIT 0x7
#define SPI_CTRLR0_DATASZ_9BIT 0x8
#define SPI_CTRLR0_DATASZ_10BIT 0x9
#define SPI_CTRLR0_DATASZ_11BIT 0xa
#define SPI_CTRLR0_DATASZ_12BIT 0xb
#define SPI_CTRLR0_DATASZ_13BIT 0xc
#define SPI_CTRLR0_DATASZ_14BIT 0xd
#define SPI_CTRLR0_DATASZ_15BIT 0xe
#define SPI_CTRLR0_DATASZ_16BIT 0xf
#define SPI_SR_DCERR (1<<6)
#define SPI_SR_TXERR (1<<5)
#define SPI_SR_RXERR (1<<4)
#define SPI_SR_RXNE (1<<3)
#define SPI_SR_TXE (1<<2)
#define SPI_SR_TXNF (1<<1)
#define SPI_SR_BUSY (1)


/* Functions */
uint32_t spi_init(SPI_TypeDef *spi);
void spi_tx(SPI_TypeDef *spi, uint8_t *data, uint32_t len);
void spi_txrx(SPI_TypeDef *spi, uint8_t *tx_data, uint8_t *rx_data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* SPI_H */