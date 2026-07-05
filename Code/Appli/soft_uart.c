/*
 * soft_uart.c - GPIO-based UART
 * 04-07-2026 E. Brombaugh
 */

#include "soft_uart.h"
#include "pinmux.h"
#include "gpio.h"

/*
 * init the soft uart on a GPIO
 */
void soft_uart_init(void)
{
	/* configure pinmux for XGPIOA[27] */
	FMUX_GPIO_REG_IOCTRL_SPINOR_WP_->bits.func_sel = IO_SPINOR_WP_X_XGPIOA_27;

	/* configure XGPIOA[26] as output high */
	GPIOA->SWPORTA_DDR.bits.P27 = 1;
	GPIOA->SWPORTA_DR.bits.P27 = 1;
}

/*
 * busywait delay for 115200bps bit period
 */
static void bit_delay(void)
{
	for(int i=0;i<2460;i++)
	{
	  __asm("nop");
	}
}

/*
 * send a char with 8/N/1 formatting
 */
void soft_uart_tx(uint8_t data)
{
	/* start bit */
	GPIOA->SWPORTA_DR.bits.P27 = 0;
	bit_delay();
	
	for(int i=0;i<8;i++)
	{
		GPIOA->SWPORTA_DR.bits.P27 = (unsigned char)(data & 1);
		bit_delay();
		data >>= 1;
	}
	
	/* stop bit */
	GPIOA->SWPORTA_DR.bits.P27 = 1;
	bit_delay();
}
