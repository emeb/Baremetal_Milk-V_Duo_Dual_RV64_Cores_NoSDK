/******************************************************************************************
  Filename    : saradc.c

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.16.2026
  
  Description : SARADC peripheral header file
  
******************************************************************************************/

#include "saradc.h"
#include "gpio.h"
#include "pinmux.h"
#include "clkgen.h"
#include "printf.h"
#include "efuse.h"

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t saradc_init(SARADC_TypeDef *saradc, uint8_t chls)
{
	/* set GPIO to input */
	if(chls & SARADC_CHL1)
	{
		FMUX_GPIO_REG_IOCTRL_ADC1->bits.func_sel = IO_ADC1_XGPIOB_3;
		GPIOB->SWPORTA_DDR.bits.P3 = 0;
	}
	else if(chls & SARADC_CHL2)
	{
		FMUX_GPIO_REG_IOCTRL_USB_VBUS_DET->bits.func_sel = IO_USB_VBUS_DET_XGPIOB_6;
		GPIOB->SWPORTA_DDR.bits.P6 = 0;
	}
	else if(chls & SARADC_CHL3)
	{
		FMUX_GPIO_REG_IOCTRL_PWR_VBAT_DET->bits.func_sel = IO_PWR_VBAT_DET_PWR_VBAT_DET;
	}
	else
		return 1;
	
	/* enable clock */
	CLKGEN->clk_en_0 |= (uint32_t)(1<<10);
	printf("clken_0 = 0x%08X\n\r", CLKGEN->clk_en_0);
	
	/* set trim value to top 4 bits of efuse adc trim reg 0x118 */
	printf("trim = 0x%08X\n\r", saradc->saradc_trim);
	uint32_t trim_value = (EFUSE->Analog0 >> 28) & 0xf;
	saradc->saradc_trim = trim_value;
	printf("trim = 0x%08X\n\r", saradc->saradc_trim);

	/* configure timing */
	saradc->saradc_cyc_set = SARADC_CYC_SETTLING | SARADC_CYC_SAMP | 
		SARADC_CYC_CLKDIV | (0xb<<16);

	return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t saradc_getchl(SARADC_TypeDef *saradc, uint8_t chl, uint16_t *result)
{
	/* check for valid channel */
	if((chl < 1) || (chl > 3))
		return 1;
	
	/* set channel */
	uint32_t ctrl = saradc->saradc_ctrl;
	__asm(""::: "memory");
	ctrl &= ~(0xfu<<4);
	ctrl |= (1<<(chl+4));
	saradc->saradc_ctrl = ctrl;
	__asm(""::: "memory");
	
	/* enable */
	saradc->saradc_ctrl |= SARADC_CTRL_EN;
	__asm(""::: "memory");

	/* wait for results */
	uint32_t timeout = 10000;
	while(saradc->saradc_status & SARADC_STATUS_BUSY)
	{
		__asm(""::: "memory");
		if(timeout-- == 0)
			return 2;
	}
	
	/* get result */
	switch(chl)
	{
		case 1:
			*result = (uint16_t)saradc->saradc_ch1_result;
			break;
		
		case 2:
			*result = (uint16_t)saradc->saradc_ch2_result;
			break;
		
		case 3:
			*result = (uint16_t)saradc->saradc_ch3_result;
			break;
		
		default:
			*result = 4096;
			return 3;
	}
	
	return 0;
}
