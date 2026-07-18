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
uint32_t saradc_init(SARADC_TypeDef *saradc, uint8_t chls)
{
	/* set GPIO to input */
	if(chls & SARADC_CHL0)
	{
		FMUX_GPIO_REG_IOCTRL_ADC1->bits.func_sel = IO_ADC1_XGPIOB_3;
		GPIOB->SWPORTA_DDR.bits.P3 = 0;
	}
	else if(chls & SARADC_CHL1)
	{
		FMUX_GPIO_REG_IOCTRL_USB_VBUS_DET->bits.func_sel = IO_USB_VBUS_DET_XGPIOB_6;
		GPIOB->SWPORTA_DDR.bits.P6 = 0;
	}
	else if(chls & SARADC_CHL2)
	{
		FMUX_GPIO_REG_IOCTRL_PWR_VBAT_DET->bits.func_sel = IO_PWR_VBAT_DET_PWR_VBAT_DET;
	}
	else
		return 1;
	
	/* enable clock */
	CLKGEN->clk_en_0 |= (uint32_t)(1<<10);
	
	/* set trim value to top 4 bits of efuse adc trim reg */
#define TRIM_VALUE 0 	// dummy for now
	saradc->saradc_trim = TRIM_VALUE << 28;
	
	/* configure timing */
	saradc->saradc_cyc_set = SARADC_CYC_SETTLING | SARADC_CYC_SAMP | SARADC_CYC_CLKDIV;
	
	return 0;
}

\//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t saradc_getchl(SARADC_TypeDef *saradc, uint8_t chl, uint16_t *result);
{
	if(chl > 0xf)
		return 1;
	
	/* set channel */
	uint32_t ctrl = saradc->saradc_ctrl;
	__asm(""::: "memory");
	ctrl &= ~(0xf<<4);
	ctrl |= ((chl & 0xf) << 4;
	saradc->saradc_ctrl = ctrl;
	__asm(""::: "memory");
	
	/* enable */
	saradc->saradc_ctrl |= SARADC_CTRL_EN;
	__asm(""::: "memory");

	/* wait for results */
	while(saradc->saradc_status & SARADC_STATUS_BUSY)
	{
		__asm(""::: "memory");
	}
	
	/* get result */
	switch(chl)
	{
		case 1:
			*result = saradc->saradc_ch1_result;
			break;
		
		case 2:
			*result = saradc->saradc_ch1_result;
			break;
		
		case 3:
			*result = saradc->saradc_ch1_result;
			break;
		
		default:
			*result = 4096;
	}
	
	return 0;
}
