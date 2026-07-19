/******************************************************************************************
  Filename    : i2s_tdm.c

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.19.2026
  
  Description : I2S_TDM peripheral driver
  
******************************************************************************************/
#include "i2s_tdm.h"
#include "gpio.h"
#include "pinmux.h"
#include "printf.h"
#include "delay.h"

/*
 * disable ethernet on ETH pins to allow I2S or GPIO 
 * uses undocumented regs per pinout spreadsheet pg 6:
 * 0x03009804[0] = 1'b1 (rg_ephy_apb_rw_sel=1, use apb interface)
 * 0x03009808[4:0] = 5'b00001 (rg_ephy_pll_stable_cnt[4:0] = 5'd1 (10us)
 * 0x03009800[2] = 0x0905 (rg_ephy_dig_rst_n=1, reset release, other keep default)
 * wait 10us
 * 0x0300907C[12:8]= 5'b00101 (page_sel_mode0 = page 5)
 * 0x03009078[11:0] = 0xF00 (set to gpio from top)
 * 0x03009074[10:9 2:1]= 0x606 (set ephy rxp&rxm input&output enable)
 * 0x03009070[10:9 2:1]= 0x606 (set ephy rxp&rxm input&output enable)
 */
void i2s_io_bypass(void)
{
	*(uint32_t *)0x03009804 = 1;
	__asm(""::: "memory");
	*(uint32_t *)0x03009808 = 1;
	__asm(""::: "memory");
	*(uint32_t *)0x03009800 = 0x905;
	__asm(""::: "memory");
	
	delayus(10);
	
	*(uint32_t *)0x0300907C = 0x500;
	__asm(""::: "memory");
	*(uint32_t *)0x03009078 = 0xf00;
	__asm(""::: "memory");
	*(uint32_t *)0x03009074 = 0x606;
	__asm(""::: "memory");
	*(uint32_t *)0x03009070 = 0x606;
	__asm(""::: "memory");
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t i2s_ext_init(void)
{
	i2s_io_bypass();
	
#if 0
	/* set up IO pins for I2S */
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_TXP->bits.func_sel = IO_PAD_ETH_TXP_IIS2_LRCK;
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_TXM->bits.func_sel = IO_PAD_ETH_TXM_IIS2_BCLK;
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_RXP->bits.func_sel = IO_PAD_ETH_RXP_IIS2_DO;
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_RXM->bits.func_sel = IO_PAD_ETH_RXM_IIS2_DI;
#else
	/* set up IO pins for GPIO to test */
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_TXP->bits.func_sel = IO_PAD_ETH_TXP_XGPIOB_25;
	GPIOB->SWPORTA_DDR.bits.P25 = 1;
	GPIOB->SWPORTA_DR.bits.P25 = 1;
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_TXM->bits.func_sel = IO_PAD_ETH_TXM_XGPIOB_24;
	GPIOB->SWPORTA_DDR.bits.P24 = 1;
	GPIOB->SWPORTA_DR.bits.P24 = 1;
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_RXP->bits.func_sel = IO_PAD_ETH_RXP_XGPIOB_27;
	GPIOB->SWPORTA_DDR.bits.P27 = 1;
	GPIOB->SWPORTA_DR.bits.P27 = 1;
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_RXM->bits.func_sel = IO_PAD_ETH_RXM_XGPIOB_26;
	GPIOB->SWPORTA_DDR.bits.P26 = 1;
	GPIOB->SWPORTA_DR.bits.P26 = 1;
#endif

	return 0;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void i2s_ext_tx(void)
{
#if 1
	/* GPIO test */
	static uint32_t count = 0;
	
	GPIOB->SWPORTA_DR.bits.P25 = (count >> 0) & 1;
	GPIOB->SWPORTA_DR.bits.P24 = (count >> 1) & 1;
	GPIOB->SWPORTA_DR.bits.P27 = (count >> 2) & 1;
	GPIOB->SWPORTA_DR.bits.P26 = (count >> 3) & 1;
	
	count++;
#endif
}

