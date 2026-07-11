/******************************************************************************************
  Filename    : spi.c

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.11.2026
  
  Description : SPI peripheral header file
  
******************************************************************************************/

#include "spi.h"
#include "pinmux.h"
#include "clkgen.h"
#include "printf.h"

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t spi_init(SPI_TypeDef *spi)
{
	switch((unsigned long long)spi)
	{
		case SPI2_BASE:
			FMUX_GPIO_REG_IOCTRL_SD1_CLK->bits.func_sel = IO_SD1_CLK_SPI2_SCK;
			FMUX_GPIO_REG_IOCTRL_SD1_CMD->bits.func_sel = IO_SD1_CMD_SPI2_SDO;
			FMUX_GPIO_REG_IOCTRL_SD1_D0->bits.func_sel = IO_SD1_D0_SPI2_SDI;
			FMUX_GPIO_REG_IOCTRL_SD1_D3->bits.func_sel = IO_SD1_D3_SPI2_CS_X;
 	        CLKGEN->clk_en_1 |= (1<<11);	// SPI2 clk ena
			break;
		
		default:
			return 1;
	}
	__asm(""::: "memory");
	
	/* disable SPI */
	spi->SPIENR = 0;
	__asm(""::: "memory");

	/* clock prescaler to 1/8 = ~25MHz */
	spi->BAUDR = 8;
	__asm(""::: "memory");

	/* format */
	spi->CTRLR0 = SPI_CTRLR0_DATASZ_8BIT | SPI_CTRLR0_FORMAT_MOT | SPI_CTRLR0_CLK_PHS_MID |
		SPI_CTRLR0_CLK_POL_LOW;
	__asm(""::: "memory");
	
	/* fifo threshold */
	spi->TXFTLR = 4;
	__asm(""::: "memory");

	/* slave enable is required and drops the CS line for every byte */
	spi->SER = 1;
	
	return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void spi_tx(SPI_TypeDef *spi, uint8_t *data, uint32_t len)
{
	/* set TX only mode */
	spi->CTRLR0 |= SPI_CTRLR0_XFR_MODE_TX;
	
	/* enable SPI */
	spi->SPIENR = 1;
	__asm(""::: "memory");
	
	/* send data */
	while(len--)
	{
		/* write data to FIFO */
		spi->DR = *data++;
		__asm(""::: "memory");
		
		/* wait if FIFO is full */
		while(!(spi->SR & SPI_SR_TXNF))
		{
			__asm(""::: "memory");
		}
	}
	
	/* wait for not busy */
	while((spi->SR & SPI_SR_BUSY))
	{
		__asm(""::: "memory");
	}
	
	/* disable SPI */
	spi->SPIENR = 0;
}

/* uncomment for uncoupled TX/RX */
#define TXRX_UNCOUPLE

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void spi_txrx(SPI_TypeDef *spi, uint8_t *tx_data, uint8_t *rx_data, uint32_t len)
{
	uint32_t rx_cnt = len;
	
	/* set TXRX mode (default) */
	spi->CTRLR0 &= ~(uint32_t)SPI_CTRLR0_XFR_MODE_EEPROM;
	
	/* enable SPI */
	spi->SPIENR = 1;
	__asm(""::: "memory");
	
	/* send data */
	while(len--)
	{
		/* write data to TX FIFO */
		spi->DR = *tx_data++;
		__asm(""::: "memory");
		
		/* wait if TX FIFO is full */
		while(!(spi->SR & SPI_SR_TXNF))
		{
			__asm(""::: "memory");
		}
		
#ifndef TXRX_UNCOUPLE
		/* wait for RX FIFO to have data */
		while(!(spi->SR & SPI_SR_RXNE))
		{
			__asm(""::: "memory");
		}
		
		/* read RX data */
		*rx_data++ = (uint8_t)spi->DR;
		__asm(""::: "memory");
#else
		/* get RX if avail, else skip & handle later */
		if(spi->SR & SPI_SR_RXNE)
		{
			__asm(""::: "memory");
			*rx_data++ = (uint8_t)spi->DR;
			__asm(""::: "memory");
			rx_cnt--;
		}
#endif
	}
	
#ifdef TXRX_UNCOUPLE
	/* get remaining RX */
	while(rx_cnt)
	{
		/* wait for FIFO */
		while(!(spi->SR & SPI_SR_RXNE))
		{
			__asm(""::: "memory");
		}
		
		/* get data */
		*rx_data++ = (uint8_t)spi->DR;
		__asm(""::: "memory");
		rx_cnt--;
	}
#endif
	
	/* wait for not busy */
	while((spi->SR & SPI_SR_BUSY))
	{
		__asm(""::: "memory");
	}
	
	/* disable SPI */
	spi->SPIENR = 0;

}

