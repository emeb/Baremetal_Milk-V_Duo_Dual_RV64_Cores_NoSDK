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
#include "aiao.h"
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
	/* bypass ethernet PHY */
	i2s_io_bypass();
	
#if 1
	/* set up ETH IO pins for I2S */
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_TXP->bits.func_sel = IO_PAD_ETH_TXP_IIS2_LRCK;
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_TXM->bits.func_sel = IO_PAD_ETH_TXM_IIS2_BCLK;
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_RXP->bits.func_sel = IO_PAD_ETH_RXP_IIS2_DO;
	FMUX_GPIO_REG_IOCTRL_PAD_ETH_RXM->bits.func_sel = IO_PAD_ETH_RXM_IIS2_DI;
	FMUX_GPIO_REG_IOCTRL_AUX0->bits.func_sel = IO_AUX0_IIS1_MCLK;
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

	/* Set AIAO muxes for external I2S on ETH pins */
	AIAO->i2s_tdm_sclk_in_sel = 0x7124;
	AIAO->i2s_tdm_fs_in_sel = 0x7124;
	AIAO->i2s_tdm_sdi_in_sel = 0x7664;
	AIAO->i2s_tdm_sdo_out_sel = 0x7664;
	AIAO->i2s_tdm_multi_sync = 0x0;
	AIAO->i2s_bclk_oen_sel = 0x0;
	
	/* I2S2 as master TX */
	I2S_TDM_2->BLK_MODE_SETTING = I2S_TDM_BLK_MODE_SETTING_TX_MODE |
		I2S_TDM_BLK_MODE_SETTING_MASTER_MODE;
	// FRAME_SETTING defaults good for 16-bit stereo I2S
	// SLOT_SETTING1,2 defaults good for 16-bit stereo I2S
	uint32_t clk_ctrl0 = I2S_TDM_2->I2S_CLK_CTRL0;
	I2S_TDM_2->I2S_CLK_CTRL0 = clk_ctrl0 | 0x1c0; // aud_ena, mclk ena, bclk_out_force_ena
	
	/* I2S1 as slave RX */
	I2S_TDM_1->BLK_MODE_SETTING = I2S_TDM_BLK_MODE_SETTING_EXT_FS;
	// FRAME_SETTING defaults good for 16-bit stereo I2S
	// SLOT_SETTING1,2 defaults good for 16-bit stereo I2S
	clk_ctrl0 = I2S_TDM_1->I2S_CLK_CTRL0;
	I2S_TDM_1->I2S_CLK_CTRL0 = 0x100;	// aud_ena
	
	/* reset */
	I2S_TDM_2->I2S_RESET = I2S_TDM_I2S_RESET_TX;
	I2S_TDM_1->I2S_RESET = I2S_TDM_I2S_RESET_RX;
	delayus(10);
	I2S_TDM_2->I2S_RESET = 0;
	I2S_TDM_1->I2S_RESET = 0;
	
	/* enable slave first to keep in sync */
	I2S_TDM_1->I2S_ENABLE = 1;
	I2S_TDM_2->I2S_ENABLE = 1;


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

