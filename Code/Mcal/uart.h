/******************************************************************************************
  Filename    : uart.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.07.2026
  
  Description : UART peripheral header file
  
******************************************************************************************/

#ifndef UART_H
#define UART_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HW_UART UART2

/**
 * @struct  UART_TypeDef
 * @brief   UART Register Layout
 */
typedef struct {
	volatile uint32_t RBR_THR_DLL;	/* 0x000: Receive Buffer,Transmit Holding or Divisor Latch Low byte Register */
	volatile uint32_t IER_DLH;		/* 0x004: Interrupt Enable or Divisor Latch high byte Register */
	volatile uint32_t FCR_IIR;		/* 0x008: FIFO Control or Interrupt Identification Register */
	volatile uint32_t LCR;			/* 0x00c: Line Control Register */
	volatile uint32_t MCR;			/* 0x010: Modem Control Register */
	volatile uint32_t LSR;			/* 0x014: Line Status Register */
	volatile uint32_t MSR;			/* 0x018: Modem Status Register */
    uint32_t RESERVED_0;			/* 0x01c */
	volatile uint32_t LPDLL;		/* 0x020: Low Power Divisor Latch (Low) Register */
	volatile uint32_t LPDLH;		/* 0x024: Low Power Divisor Latch (High) Register */
    uint32_t RESERVED_1[2];			/* 0x028 - 0x02c */
	volatile uint32_t SRBR_STHR;	/* 0x030: Shadow Receive/Trasnmit Buffer Register */
    uint32_t RESERVED_2[11];		/* 0x034 - 0x06c */
	volatile uint32_t FAR;			/* 0x070: FIFO Access Register */
	volatile uint32_t TFR;			/* 0x074: Transmit FIFO Read */
	volatile uint32_t RFW;			/* 0x078: Receive FIFO Write */
	volatile uint32_t USR;			/* 0x07c: UART Status Register */
	volatile uint32_t TFL;			/* 0x080: Transmit FIFO Level */
	volatile uint32_t RFL;			/* 0x084: Receive FIFO Level */
	volatile uint32_t SRR;			/* 0x088: Software Reset Register */
	volatile uint32_t SRTS;			/* 0x08c: Shadow Request to Send */
	volatile uint32_t SBCR;			/* 0x090: Shadow Break Control Register */
	volatile uint32_t SDMAM;		/* 0x094: Shadow DMA Mode */
	volatile uint32_t SFE;			/* 0x098: Shadow FIFO Enable */
	volatile uint32_t SRT;			/* 0x09c: Shadow RCVR Trigger */
	volatile uint32_t STET;			/* 0x0a0: Shadow TX Empty Trigger */
	volatile uint32_t HTX;			/* 0x0a4: Halt TX */
	volatile uint32_t DMASA;		/* 0x0a8: DMA Software Acknowledge */
} UART_TypeDef;

/* Peripheral Base Definitions */
#define UART0_BASE    (0x04140000ull)
#define UART1_BASE    (0x04150000ull)
#define UART2_BASE    (0x04160000ull)
#define UART3_BASE    (0x04170000ull)
#define UART4_BASE    (0x041c0000ull)

/* Instance Pointers */
#define UART0    ((UART_TypeDef *)UART0_BASE)
#define UART1    ((UART_TypeDef *)UART1_BASE)
#define UART2    ((UART_TypeDef *)UART2_BASE)
#define UART3    ((UART_TypeDef *)UART3_BASE)
#define UART4    ((UART_TypeDef *)UART4_BASE)

/* Register fields */
#define UART_LCR_DLEN_5	0
#define UART_LCR_DLEN_6	1
#define UART_LCR_DLEN_7	2
#define UART_LCR_DLEN_8	3
#define UART_LCR_STOPBITS_1	0
#define UART_LCR_STOPBITS_2	4
#define UART_LCR_PARITY_ENA	8
#define UART_LCR_PARITY_EVEN	16
#define UART_LCR_PARITY_STICK	32
#define UART_LCR_BREAK	64
#define UART_LCR_DIV_ACCESS	128

uint32_t uart_init(UART_TypeDef *uart);
uint32_t uart_tx(UART_TypeDef *uart, uint8_t data);
uint32_t uart_rx(UART_TypeDef *uart, uint8_t *data);
uint32_t uart_dump(UART_TypeDef *uart);

#ifdef __cplusplus
}
#endif

#endif /* UART_H */