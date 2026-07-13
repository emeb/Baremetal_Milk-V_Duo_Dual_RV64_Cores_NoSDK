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
	CLKGEN->clk_sel_0 |= (1<<31);
	__asm(""::: "memory");
	
	/* clk ena for all I2C */
	CLKGEN->clk_en_1 |= (1<<6);
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
	/* set target address, start */
	i2c->IC_TAR = (addr & 0x7f) | IC_TAR_GC_OR_START | IC_TAR_SPECIAL;
	__asm(""::: "memory");
	
	/* enable I2C */
	i2c->IC_ENABLE = 1;
	__asm(""::: "memory");

	/* begin data */
	while(len--)
	{
		/* send data and stop */
		i2c->IC_DATA_CMD = *data++ | (len==0 ? IC_DATA_CMD_STOP : 0);
		__asm(""::: "memory");
		
		while
	}
}

