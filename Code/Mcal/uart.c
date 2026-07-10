/******************************************************************************************
  Filename    : uart.c

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.07.2026
  
  Description : UART peripheral header file
  
******************************************************************************************/

#include "uart.h"
#include "pinmux.h"
#include "clkgen.h"
#include "rstcfg.h"
#include "printf.h"

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t uart_init(UART_TypeDef *uart)
{
#if 1
	/* configure pinmux and clk source for 25MHz xtal */
    switch((unsigned long long)uart)
    {
        case UART0_BASE:
			/* note that this is on JTAG TMS and may not work */
	        FMUX_GPIO_REG_IOCTRL_UART0_TX->bits.func_sel = IO_UART0_TX_UART0_TX;
 	        CLKGEN->clk_sel_0 |= (1<<9);
           break;

        case UART1_BASE:
			/* Note that this is on JTAG TDI and may not work */
	        FMUX_GPIO_REG_IOCTRL_IIC0_SCL->bits.func_sel = IO_IIC0_SCL_UART1_TX;
	        CLKGEN->clk_sel_0 |= (1<<10);
            break;
        
        case UART2_BASE:
 	        FMUX_GPIO_REG_IOCTRL_SD1_D2->bits.func_sel = IO_SD1_D2_UART2_TX;
	        CLKGEN->clk_sel_0 |= (1<<11);
            break;

        case UART3_BASE:
 	        FMUX_GPIO_REG_IOCTRL_SD1_D2->bits.func_sel = IO_SD1_D2_UART3_TX;
	        CLKGEN->clk_sel_0 |= (1<<12);
            break;
        
        case UART4_BASE:
            FMUX_GPIO_REG_IOCTRL_SD1_GPIO1->bits.func_sel = IO_SD1_GPIO1_UART4_TX;
	        CLKGEN->clk_sel_0 |= (1<<13);
            break;

        default:
            return 1;
    }

	/* LCR[7] = 1 to access DRH/DRL */
	uart->LCR = 0x80;
	
	/* Baud rate div = 25MHz / BR => 14 for 115200 from 25MHz */
	uart->RBR_THR_DLL = 14;
	uart->IER_DLH = 0;
	
	/* LCR[7] = 0 to access RBR/THR, 8N1 */
	uart->LCR = UART_LCR_DLEN_8;
	
	/* Disable FIFOs */
	//uart->FCR_IIR = 0;

    return 0;
#endif
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t uart_tx(UART_TypeDef *uart, uint8_t data)
{
	/* send character */
	uart->RBR_THR_DLL = (uint32_t)data;
	
	/* wait for THR empty */
	uint32_t timeout = 1000;
	while((uart->FCR_IIR & 0xf) != 0b0010)			// thr empty in iir reg - per datasheet
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
uint32_t uart_rx(UART_TypeDef *uart, uint8_t *data)
{
    /* wait for RX */
 	uint32_t timeout = 1000;
    while((uart->LSR & 0x1) == 0)
    {
 		if(timeout-- == 0)
			return 1;
    }

    /* get data */
	*data = (uint8_t)uart->RBR_THR_DLL;
    return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t uart_dump(UART_TypeDef *uart)
{
	char *uart_name;
	
    switch((unsigned long long)uart)
    {
        case UART0_BASE:
			printf("UART0_TX pinmux = 0x%08X\n\r", FMUX_GPIO_REG_IOCTRL_UART0_TX->bits.func_sel);
 	        uart_name = "UART0";
           break;

        case UART1_BASE:
			/* Note that this is on JTAG TDI and may not work */
			printf("IIC0_SCL pinmux = 0x%08X\n\r", FMUX_GPIO_REG_IOCTRL_IIC0_SCL->bits.func_sel);
 	        uart_name = "UART1";
            break;
        
        case UART2_BASE:
			printf("SD1_D2 pinmux = 0x%08X\n\r", FMUX_GPIO_REG_IOCTRL_SD1_D2->bits.func_sel);
 	        uart_name = "UART2";
            break;

        case UART3_BASE:
			printf("SD1_D2 pinmux = 0x%08X\n\r", FMUX_GPIO_REG_IOCTRL_SD1_D2->bits.func_sel);
 	        uart_name = "UART3";
            break;
        
        case UART4_BASE:
			printf("SD1_GPIO1 pinmux = 0x%08X\n\r", FMUX_GPIO_REG_IOCTRL_SD1_GPIO1->bits.func_sel);
 	        uart_name = "UART4";
            break;

        default:
            return 1;
    }

	printf("CLKGEN->CLK_EN_1 = 0x%08X\n\r", CLKGEN->clk_en_1);
	printf("CLKGEN->CLK_SEL_0 = 0x%08X\n\r", CLKGEN->clk_sel_0);
	printf("RSTCFG->SOFT_RSTN_0 = 0x%08X\n\r", RSTCFG->SOFT_RSTN_0);
	printf("%s->LCR = 0x%08X\n\r", uart_name, uart->LCR);
	printf("%s->RBR_THR_DLL = 0x%08X\n\r", uart_name, uart->RBR_THR_DLL);
	printf("%s->IER_DLH = 0x%08X\n\r", uart_name, uart->IER_DLH);
	printf("setting %s->LCR[7] for baudrate access...\n\r", uart_name);
	uart->LCR |= 0x80;	// access baud rate regs
	printf("%s->LCR = 0x%08X\n\r", uart_name, uart->LCR);
	printf("%s->RBR_THR_DLL = 0x%08X\n\r", uart_name, uart->RBR_THR_DLL);
	printf("%s->IER_DLH = 0x%08X\n\r", uart_name, uart->IER_DLH);
	printf("restoring %s->LCR[7] for data access...\n\r", uart_name);
	uart->LCR &= ~(uint32_t)0x80;	// access data regs
	printf("%s->LCR = 0x%08X\n\r", uart_name, uart->LCR);
	printf("%s->RBR_THR_DLL = 0x%08X\n\r", uart_name, uart->RBR_THR_DLL);
	printf("%s->IER_DLH = 0x%08X\n\r", uart_name, uart->IER_DLH);
	
	return 0;
}
