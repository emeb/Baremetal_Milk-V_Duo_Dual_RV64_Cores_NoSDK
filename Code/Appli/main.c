/******************************************************************************************
  Filename    : main.c
  
  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 16.03.2026
  
  Description : Application main function
  
******************************************************************************************/

//-----------------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------------
#include <stdint.h>
#include "riscv-csr.h"
#include "pinmux.h"
#include "gpio.h"
#include "core.h"
#include "uart.h"
#include "soft_uart.h"
#include "printf.h"

/* uncomment this to use a soft UART when HW UART isn't working */
#define SOFT_UART

//-----------------------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------------------
int main_core1(void);
void isr_timer(void);
void delayms(uint32_t ms);

#ifndef SOFT_UART
void uart_init(void);
uint32_t uart_tx(uint8_t data);
uint8_t uart_rx(void);
#endif


//-----------------------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------------------
volatile uint64_t  __attribute__((section(".non_cacheable_data"))) sync_non_cacheable = 0x12345678;
volatile uint64_t sync = 0x0102030405060708;

/* build time */
const char *bdate = __DATE__;
const char *btime = __TIME__;
const char *fwVersionStr = "V0.1";

//-----------------------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------------------
#define TIMEOUT_500MS  (uint64_t)12500000 // timer freq is 25MHz
#define TIMEOUT_250MS  (uint64_t)6250000 // timer freq is 25MHz

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
int main(void)
{
  /* configure pinmux for XGPIOA[25] */
  FMUX_GPIO_REG_IOCTRL_SPINOR_MOSI->bits.func_sel = IO_SPINOR_MOSI_XGPIOA_25;
  
  /* configure XGPIOA[25] as output high (Green LED) */
  GPIOA->SWPORTA_DDR.bits.P25 = 1;
  GPIOA->SWPORTA_DR.bits.P25 = 1;
	
  /* configure pinmux for XGPIOA[26] */
  FMUX_GPIO_REG_IOCTRL_SPINOR_HOLD_->bits.func_sel = IO_SPINOR_HOLD_X_XGPIOA_26;
  
  /* configure XGPIOA[26] as output high (serial diag) */
  GPIOA->SWPORTA_DDR.bits.P26 = 1;
  GPIOA->SWPORTA_DR.bits.P26 = 1;
	
  /* configure UART */
#ifndef SOFT_UART
  uart_init();
#else
  soft_uart_init();
  printf("\n\n\r-----------------------------\n\r");
  printf("Bare metal CV1800B + soft UART - starting up\n\r");
  printf("Version: %s\n\r", fwVersionStr);
  printf("Build Date: %s\n\r", bdate);
  printf("Build Time: %s\n\r", btime);
  printf("-----------------------------\n\r");
	
#endif
	
  /* start the second core*/
  core_start_core1();

  /* configure the timer */
  core_set_timer_timeout(TIMEOUT_250MS);

  /* endless loop */
  while(1)
  {
		// send char
#ifndef SOFT_UART
		if(uart_tx('.'))
			delayms(10);	// 10ms delay means it timed out
		else
	  		delayms(1);		// 1ms delay means it was OK
#else
		soft_uart_tx('.');
		delayms(100);
#endif
	  
	  // toggle GPIO
	  GPIOA->SWPORTA_DR.bits.P26 ^= 1;
  }

  return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
int main_core1(void)
{
  /* sanity check for MMU and cache configuration */
  if((sync == 0x0102030405060708) && (sync_non_cacheable == 0x12345678))
  {
    /* configure pinmux for XGPIOC[24] */
    FMUX_GPIO_REG_IOCTRL_PAD_AUD_AOUTR->bits.func_sel = IO_PAD_AUD_AOUTR_XGPIOC_24;

    /* set XGPIOC[24] as output high (Blue LED) */
    GPIOC->SWPORTA_DDR.bits.P24 = 1;
    GPIOC->SWPORTA_DR.bits.P24 = 1;
  }
  else
  {
    /* sanity check failed: possible mmu mapping error, cache incoherency, or global pointer (gp) misalignment */
    __asm("j .");
  }

  /* configure the timer */
  core_set_timer_timeout(TIMEOUT_500MS);

  /* endless loop */
  for(;;);

  return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void isr_timer(void)
{
  uint32_t ActiveCore = osGetActiveCore();

  if(CORE0_ID == ActiveCore)
  {
    GPIOA->SWPORTA_DR.bits.P25 ^= 1;
  
    /* configure the timer */
    core_set_timer_timeout(TIMEOUT_250MS);
  }
  else if(CORE1_ID == ActiveCore)
  {
    GPIOC->SWPORTA_DR.bits.P24 ^= 1;
  
    /* configure the timer */
    core_set_timer_timeout(TIMEOUT_500MS);
  }
  else
  {
    /* error identifying the active core */
    __asm("j .");
  }
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void delayms(uint32_t ms)
{
	while(ms--)
	{
		/* 1 ms busywait delay */
		for(int i=0;i<283360;i++)
		{
		  __asm("nop");
		}
	}
}

#ifndef SOFT_UART
//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void uart_init(void)
{
	/* configure pinmux for UART0_TX */
	FMUX_GPIO_REG_IOCTRL_UART0_TX->bits.func_sel = IO_UART0_TX_UART0_TX;

#if 0
	/* LCR[7] = 1 to access DRH/DRL */
	UART0->LCR = 0x80;
	
	/* Baud rate div = 25MHz / BR => 14 for 115200 */
	UART0->RBR_THR_DLL = 14;
	UART0->IER_DLH = 0;
	
	/* LCR[7] = 0 to access RBR/THR, 8N1 */
	UART0->LCR = UART_LCR_DLEN_8;
	
	/* Disable FIFOs */
	UART0->FCR_IIR = 0;
#endif
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t uart_tx(uint8_t data)
{
	/* send character */
	UART0->RBR_THR_DLL = data;
	
	/* wait for THR empty */
	//while((UART0->FCR_IIR & 0xf) != 0x2);
	uint32_t timeout = 1000;
	while((UART0->LSR & 0x40) == 0)
	{
		if(timeout-- == 0)
			return 1;
	}
	
	return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint8_t uart_rx(void)
{
	return 0;
}
#endif
