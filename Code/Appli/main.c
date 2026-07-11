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
#include "printf.h"
#include "spi.h"
#include "clkgen.h"

//-----------------------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------------------
int main_core1(void);
void isr_timer(void);
void delayms(uint32_t ms);

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
    /* diagnostic software UART via GPIO */
    if(!uart_init(HW_UART))
    {
		printf("\n\n\r-----------------------------\n\r");
		printf("Bare metal CV1800B + HW UART - starting up\n\r");
		printf("Version: %s\n\r", fwVersionStr);
		printf("Build Date: %s\n\r", bdate);
		printf("Build Time: %s\n\r", btime);
		printf("-----------------------------\n\r");
	}
  
	/* configure pinmux for XGPIOA[25] */
	FMUX_GPIO_REG_IOCTRL_SPINOR_MOSI->bits.func_sel = IO_SPINOR_MOSI_XGPIOA_25;

	/* configure XGPIOA[25] as output high (Pin 25/GP19/Green LED) */
	GPIOA->SWPORTA_DDR.bits.P25 = 1;
	GPIOA->SWPORTA_DR.bits.P25 = 1;

	/* configure pinmux for XGPIOA[26] */
	FMUX_GPIO_REG_IOCTRL_SPINOR_HOLD_->bits.func_sel = IO_SPINOR_HOLD_X_XGPIOA_26;

	/* configure XGPIOA[26] as output low (HW diag) */
	GPIOA->SWPORTA_DDR.bits.P26 = 1;
	GPIOA->SWPORTA_DR.bits.P26 = 0;
	
	printf("CLKGEN->clk_en_1 = 0x%08X\n\r", CLKGEN->clk_en_1);
	printf("SPI2->CTRLR0 = 0x%08X\n\r", SPI2->CTRLR0);
	printf("SPI2->BAUDR = 0x%08X\n\r", SPI2->BAUDR);
	printf("SPI2->SPIENR = 0x%08X\n\r", SPI2->SPIENR);
	printf("&SPI2->DR = 0x%08X, 0x%08X\n\r", &(SPI2->DR), SPI2_BASE); 
	/* start SPI */
	if(spi_init(HW_SPI))
	{
		printf("SPI init failed\n\r");
	}
	else
	{
		printf("SPI initialized\n\r");
	}
	uint8_t spi_tx[13] = "Hello World!";
	uint8_t spi_rx[16];
	printf("CLKGEN->clk_en_1 = 0x%08X\n\r", CLKGEN->clk_en_1);
	printf("SPI2->CTRLR0 = 0x%08X\n\r", SPI2->CTRLR0);
	printf("SPI2->BAUDR = 0x%08X\n\r", SPI2->BAUDR);
	printf("SPI2->SPIENR = 0x%08X\n\r", SPI2->SPIENR);

	/* start the second core*/
	core_start_core1();

	/* configure the timer */
	core_set_timer_timeout(TIMEOUT_250MS);

	/* endless loop */
	while(1)
	{
		// send char
		uart_tx(HW_UART, '+');
		
		// send SPI data w/ GPIO bracket
		GPIOA->SWPORTA_DR.bits.P26 = 1;
		//spi_tx(HW_SPI, spi_tx, sizeof(spi_tx));
		spi_txrx(HW_SPI, spi_tx, spi_rx, sizeof(spi_tx));
		GPIOA->SWPORTA_DR.bits.P26 = 0;
		
		/* dump rx */
		printf("rx: ");
		for(int i=0;i<16;i++)
		{
			printf("%02X ", spi_rx[i]);
		}
		printf("\n\r");
		
		delayms(100);
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

