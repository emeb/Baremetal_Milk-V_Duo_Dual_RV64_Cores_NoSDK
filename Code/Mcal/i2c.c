/******************************************************************************************
  Filename    : i2c.c

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.12.2026
  
  Description : I2C peripheral header file
  
******************************************************************************************/

#include "i2c.h"
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
uint32_t i2c_init(I2C_TypeDef *i2c)
{
	switch((unsigned long long)i2c)
	{
		case I2C0_BASE:
			FMUX_GPIO_REG_IOCTRL_IIC0_SCL->bits.func_sel = IO_IIC0_SCL_IIC0_SCL;
			FMUX_GPIO_REG_IOCTRL_IIC0_SDA->bits.func_sel = IO_IIC0_SDA_IIC0_SDA;
			break;
		
		default:
			return 1;
	}
	__asm(""::: "memory");
	
	/* clk src selection 25MHz or 100MHz */
	//CLKGEN->clk_sel_0 |= (uint32_t)(1<<31);
	CLKGEN->clk_sel_0 &= (uint32_t)~(1<<31);
	__asm(""::: "memory");
	
	/* clk ena for all I2C */
	CLKGEN->clk_en_1 |= (uint32_t)(1<<6);
	__asm(""::: "memory");
	
	/* disable I2C */
	i2c->IC_ENABLE = 0;
	__asm(""::: "memory");

	/* timing for 25MHz */
	i2c->IC_SS_SCL_HCNT = IC_SS_SCL_HCNT_25M;
	__asm(""::: "memory");
	i2c->IC_SS_SCL_LCNT = IC_SS_SCL_LCNT_25M;
	__asm(""::: "memory");
	i2c->IC_FS_SCL_HCNT = IC_FS_SCL_HCNT_25M;
	__asm(""::: "memory");
	i2c->IC_FS_SCL_LCNT = IC_FS_SCL_LCNT_25M;
	__asm(""::: "memory");
	i2c->IC_SDA_HOLD = IC_SDA_HOLD_25M;
	__asm(""::: "memory");
	i2c->IC_SDA_SETUP = IC_SDA_SETUP_25M;
	__asm(""::: "memory");
	i2c->IC_FS_SPKLEN = IC_FS_SPKLEN_25M;
	__asm(""::: "memory");

	/* control */
	i2c->IC_CON = IC_CON_MASTER_MODE | IC_CON_SPEED_100K | IC_CON_RESTART_EN | 
		IC_CON_SLAVE_DISABLE;
	__asm(""::: "memory");
		
	return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void i2c_tx(I2C_TypeDef *i2c, uint8_t addr, uint8_t *data, uint32_t len)
{
	uint32_t dummy __attribute__((unused));
	
	/* set target address, start */
	i2c->IC_TAR = (addr & 0x7f);
	__asm(""::: "memory");
	
	/* enable I2C */
	i2c->IC_ENABLE = 1;
	__asm(""::: "memory");
	
	/* clear IRQs */
	dummy = i2c->IC_CLR_INTR;

	/* begin data */
	while(len--)
	{
		/* send data and stop */
		i2c->IC_DATA_CMD = *data++ | (len==0 ? IC_DATA_CMD_STOP : 0);
		__asm(""::: "memory");
		
		/* wait if full */
		while(!(i2c->IC_STATUS & IC_STATUS_ST_TFNF))
		{
			__asm(""::: "memory");
		}
	}
	
	/* wait for not busy */
	while(i2c->IC_STATUS & IC_STATUS_ST_MST_ACTIVITY)
	{
		__asm(""::: "memory");
	}

	/* disable I2C */
	i2c->IC_ENABLE = 0;
	__asm(""::: "memory");
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void i2c_txrx(I2C_TypeDef *i2c, uint8_t addr, uint8_t *tx_data, uint32_t tx_len,
	uint8_t *rx_data, uint32_t rx_len)
{
	uint32_t dummy __attribute__((unused));
	
	/* set target address, start */
	i2c->IC_TAR = (addr & 0x7f);
	__asm(""::: "memory");
	
	/* enable I2C */
	i2c->IC_ENABLE = 1;
	__asm(""::: "memory");
	
	/* clear IRQs */
	dummy = i2c->IC_CLR_INTR;

	/* send tx data */
	while(tx_len--)
	{
		/* send data */
		i2c->IC_DATA_CMD = *tx_data++;
		__asm(""::: "memory");
		
		/* wait if full */
		while(!(i2c->IC_STATUS & IC_STATUS_ST_TFNF))
		{
			__asm(""::: "memory");
		}
	}
	
	/* tell it to restart and read */
	i2c->IC_DATA_CMD = IC_DATA_CMD_READ | IC_DATA_CMD_RESTART;
	__asm(""::: "memory");
	
	/* get rx data */
	while(rx_len--)
	{
		/* wait for data */
		while(!(i2c->IC_STATUS & IC_STATUS_ST_RFNE))
		{
			__asm(""::: "memory");
		}
		
		/* get data */
		*rx_data++ = (uint8_t)i2c->IC_DATA_CMD;
		__asm(""::: "memory");
	}
		
	/* All done - generate read + stop */
	i2c->IC_DATA_CMD = IC_DATA_CMD_READ | IC_DATA_CMD_STOP;
	__asm(""::: "memory");
	
	/* wait for not busy */
	while(i2c->IC_STATUS & IC_STATUS_ST_MST_ACTIVITY)
	{
		__asm(""::: "memory");
	}

	/* disable I2C */
	i2c->IC_ENABLE = 0;
	__asm(""::: "memory");
}
