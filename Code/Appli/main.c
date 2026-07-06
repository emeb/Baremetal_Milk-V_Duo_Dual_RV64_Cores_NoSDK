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
#include "clkgen.h"
#include "rstcfg.h"

//-----------------------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------------------
int main_core1(void);
void isr_timer(void);
void delayms(uint32_t ms);

void uart_init(void);
uint32_t uart_tx(uint8_t data);
uint8_t uart_rx(void);

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
  
  /* configure XGPIOA[25] as output high (Pin 25/GP19/Green LED) */
  GPIOA->SWPORTA_DDR.bits.P25 = 1;
  GPIOA->SWPORTA_DR.bits.P25 = 1;
	
  /* configure pinmux for XGPIOA[26] */
  FMUX_GPIO_REG_IOCTRL_SPINOR_HOLD_->bits.func_sel = IO_SPINOR_HOLD_X_XGPIOA_26;
  
  /* configure XGPIOA[26] as output high (serial diag) */
  GPIOA->SWPORTA_DDR.bits.P26 = 1;
  GPIOA->SWPORTA_DR.bits.P26 = 1;

#if 0
	/* configure pinmux for XGPIOA[16] */
  FMUX_GPIO_REG_IOCTRL_UART0_TX->bits.func_sel = IO_UART0_TX_XGPIOA_16;
  
  /* configure XGPIOA[16] as output high (Pin16/GP12/UART0/1_TX) */
  GPIOA->SWPORTA_DDR.bits.P16 = 1;
  GPIOA->SWPORTA_DR.bits.P16 = 1;
#endif

#if 0
  /* configure pinmux for PWRGPIO[26] */
  //FMUX_GPIO_REG_IOCTRL_SD1_GPIO1->bits.func_sel = IO_SD1_GPIO1_PWR_GPIO_26;
  /* configure pinmux for PWRGPIO[19] */
  FMUX_GPIO_REG_IOCTRL_SD1_D2->bits.func_sel = IO_SD1_D2_PWR_GPIO_19;
  
  /* configure XGPIOA[26] as output high (Pin 4/GP2/diag) */
  //GPIOE->SWPORTA_DDR.bits.P26 = 1;
  //GPIOE->SWPORTA_DR.bits.P26 = 1;
  /* configure XGPIOA[19] as output high (Pin 4/GP2/diag) */
  GPIOE->SWPORTA_DDR.bits.P19 = 1;
  GPIOE->SWPORTA_DR.bits.P19 = 1;
#endif

  /* configure UART */
  uart_init();
  soft_uart_init();
  printf("\n\n\r-----------------------------\n\r");
  printf("Bare metal CV1800B + soft UART - starting up\n\r");
  printf("Version: %s\n\r", fwVersionStr);
  printf("Build Date: %s\n\r", bdate);
  printf("Build Time: %s\n\r", btime);
  printf("-----------------------------\n\r");
  
#if 0
  /* dump UART0 settings */
  printf("UART_TX pinmux = 0x%08X [2:0 = 0]\n\r", FMUX_GPIO_REG_IOCTRL_UART0_TX->bits.func_sel);
  printf("CLKGEN->CLK_EN_1 = 0x%08X [14 = 1]\n\r", CLKGEN->clk_en_1);
  printf("CLKGEN->CLK_SEL_0 = 0x%08X [13:9] = 1]\n\r", CLKGEN->clk_sel_0);
  printf("RSTCFG->SOFT_RSTN_0 = 0x%08X [23 = 1]\n\r", RSTCFG->SOFT_RSTN_0);
  printf("UART0->LCR = 0x%08X\n\r", UART0->LCR);
  printf("UART0->RBR_THR_DLL = 0x%08X\n\r", UART0->RBR_THR_DLL);
  printf("UART0->IER_DLH = 0x%08X\n\r", UART0->IER_DLH);
  printf("setting UART0->LCR[7] for baudrate access...\n\r");
  UART0->LCR |= 0x80;	// access baud rate regs
  printf("UART0->LCR = 0x%08X\n\r", UART0->LCR);
  printf("UART0->RBR_THR_DLL = 0x%08X\n\r", UART0->RBR_THR_DLL);
  printf("UART0->IER_DLH = 0x%08X\n\r", UART0->IER_DLH);
  printf("restoring UART0->LCR[7] for data access...\n\r");
  UART0->LCR &= ~(uint32_t)0x80;	// access data regs
  printf("UART0->LCR = 0x%08X\n\r", UART0->LCR);
  printf("UART0->RBR_THR_DLL = 0x%08X\n\r", UART0->RBR_THR_DLL);
  printf("UART0->IER_DLH = 0x%08X\n\r", UART0->IER_DLH);
#endif
	
#if 0
  /* dump UART4 settings */
  printf("SD1_GPIO1 pinmux = 0x%08X [2:0 = 0]\n\r", FMUX_GPIO_REG_IOCTRL_SD1_GPIO1->bits.func_sel);
  printf("CLKGEN->CLK_EN_1 = 0x%08X [14 = 1]\n\r", CLKGEN->clk_en_1);
  printf("CLKGEN->CLK_SEL_0 = 0x%08X [13:9] = 1]\n\r", CLKGEN->clk_sel_0);
  printf("RSTCFG->SOFT_RSTN_0 = 0x%08X [23 = 1]\n\r", RSTCFG->SOFT_RSTN_0);
  printf("UART4->LCR = 0x%08X\n\r", UART4->LCR);
  printf("UART4->RBR_THR_DLL = 0x%08X\n\r", UART4->RBR_THR_DLL);
  printf("UART4->IER_DLH = 0x%08X\n\r", UART4->IER_DLH);
  printf("setting UART4->LCR[7] for baudrate access...\n\r");
  UART4->LCR |= 0x80;	// access baud rate regs
  printf("UART4->LCR = 0x%08X\n\r", UART4->LCR);
  printf("UART4->RBR_THR_DLL = 0x%08X\n\r", UART4->RBR_THR_DLL);
  printf("UART4->IER_DLH = 0x%08X\n\r", UART4->IER_DLH);
  printf("restoring UART4->LCR[7] for data access...\n\r");
  UART4->LCR &= ~(uint32_t)0x80;	// access data regs
  printf("UART4->LCR = 0x%08X\n\r", UART4->LCR);
  printf("UART4->RBR_THR_DLL = 0x%08X\n\r", UART4->RBR_THR_DLL);
  printf("UART4->IER_DLH = 0x%08X\n\r", UART4->IER_DLH);
#endif
	
#if 1
  /* dump UART2 settings */
  printf("SD1_GPIO1 pinmux = 0x%08X [2:0 = 0]\n\r", FMUX_GPIO_REG_IOCTRL_SD1_D2->bits.func_sel);
  printf("CLKGEN->CLK_EN_1 = 0x%08X [14 = 1]\n\r", CLKGEN->clk_en_1);
  printf("CLKGEN->CLK_SEL_0 = 0x%08X [13:9] = 1]\n\r", CLKGEN->clk_sel_0);
  printf("RSTCFG->SOFT_RSTN_0 = 0x%08X [23 = 1]\n\r", RSTCFG->SOFT_RSTN_0);
  printf("UART2->LCR = 0x%08X\n\r", UART2->LCR);
  printf("UART2->RBR_THR_DLL = 0x%08X\n\r", UART2->RBR_THR_DLL);
  printf("UART2->IER_DLH = 0x%08X\n\r", UART2->IER_DLH);
  printf("setting UART2->LCR[7] for baudrate access...\n\r");
  UART2->LCR |= 0x80;	// access baud rate regs
  printf("UART2->LCR = 0x%08X\n\r", UART2->LCR);
  printf("UART2->RBR_THR_DLL = 0x%08X\n\r", UART2->RBR_THR_DLL);
  printf("UART2->IER_DLH = 0x%08X\n\r", UART2->IER_DLH);
  printf("restoring UART2->LCR[7] for data access...\n\r");
  UART2->LCR &= ~(uint32_t)0x80;	// access data regs
  printf("UART2->LCR = 0x%08X\n\r", UART2->LCR);
  printf("UART2->RBR_THR_DLL = 0x%08X\n\r", UART2->RBR_THR_DLL);
  printf("UART2->IER_DLH = 0x%08X\n\r", UART2->IER_DLH);
#endif
	
  /* start the second core*/
  core_start_core1();

  /* configure the timer */
  core_set_timer_timeout(TIMEOUT_250MS);

  //printf("Later UART_TX pinmux = 0x%08X [2:0 = 0]\n\r", FMUX_GPIO_REG_IOCTRL_UART0_TX->bits.func_sel);

  /* endless loop */
  while(1)
  {
		// send char
#if 0
		if(uart_tx('.'))
			delayms(10);	// 10ms delay means it timed out
		else
	  		delayms(1);		// 1ms delay means it was OK
#else
		soft_uart_tx('.');
		uart_tx('+');
	  GPIOE->SWPORTA_DR.bits.P19 ^= 1;
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

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void uart_init(void)
{
	/* configure pinmux for UART0_TX (usually comes up as 6/JTAG_TMS)*/
	//FMUX_GPIO_REG_IOCTRL_UART0_TX->bits.func_sel = IO_UART0_TX_UART0_TX;
	//FMUX_GPIO_REG_IOCTRL_IIC0_SCL->bits.func_sel = IO_IIC0_SCL_UART1_TX;
	//FMUX_GPIO_REG_IOCTRL_SD1_GPIO1->bits.func_sel = IO_SD1_GPIO1_UART4_TX;
	FMUX_GPIO_REG_IOCTRL_SD1_D2->bits.func_sel = IO_SD1_D2_UART2_TX;

#if 1
	/* set clock source to use 25MHz XTAL */
	//CLKGEN->clk_sel_0 |= (1<<9);
	//CLKGEN->clk_sel_0 |= (1<<10);
	//CLKGEN->clk_sel_0 |= (1<<11);
	
	/* LCR[7] = 1 to access DRH/DRL */
	UART2->LCR = 0x80;
	
	/* Baud rate div = 25MHz / BR => 14 for 115200 from 25MHz */
	UART2->RBR_THR_DLL = 14;
	UART2->IER_DLH = 0;
	
	/* LCR[7] = 0 to access RBR/THR, 8N1 */
	UART2->LCR = UART_LCR_DLEN_8;
	
	/* Disable FIFOs */
	UART2->FCR_IIR = 0;
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
	UART2->RBR_THR_DLL = data;
	
	/* wait for THR empty */
	uint32_t timeout = 1000;
	//while((UART2->FCR_IIR & 0xf) != 0x2);	// thr empty in int id reg
	while((UART2->LSR & 0x20) == 0)			// thr empty in line status reg
	//while((UART2->LSR & 0x40) == 0)			// tx empty in line status reg
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
