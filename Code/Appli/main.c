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
#include <math.h>
#include "riscv-csr.h"
#include "pinmux.h"
#include "gpio.h"
#include "core.h"
#include "uart.h"
#include "printf.h"
#include "spi.h"
#include "clkgen.h"
#include "i2c.h"
#include "saradc.h"
#include "aiao.h"
#include "i2s_tdm.h"
#include "delay.h"
#include "plic.h"

//-----------------------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------------------
int main_core1(void);
void isr_timer(void);
void isr_ext(void);

//-----------------------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------------------
volatile uint64_t  __attribute__((section(".non_cacheable_data"))) sync_non_cacheable = 0x12345678;
volatile uint64_t sync = 0x0102030405060708;

/* build time */
const char *bdate = __DATE__;
const char *btime = __TIME__;
const char *fwVersionStr = "V0.1";

/* I2S testing */
volatile uint32_t i2s_buffer[128], i2s_tx_ptr = 0, i2s_tx = 0, i2s_tx_err = 0,
	i2s_rx = 0, i2s_rx_err = 0, i2s_rx_data, i2s_cnt = 0, isr_ext_cnt = 0;
	
//#define I2S_IRQ
#define I2S_DMA

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
	
#if 0
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
#endif

#if 0
	/* start I2C */
	if(i2c_init(HW_I2C))
	{
		printf("I2C init failed\n\r");
	}
	else
	{
		printf("I2C initialized\n\r");
	}
	//uint8_t i2c_txbuf[] = "Hello World!";
	uint8_t i2c_txbuf[2] = {0x0c, 0x0};	// should be a read from reg 6 = 0x140
	uint8_t i2c_rxbuf[2];
	uint8_t target_addr = 0x1A;
#endif

#if 0
	/* start ADC */
	if(saradc_init(HW_SARADC, SARADC_CHL1 | SARADC_CHL2 | SARADC_CHL3))
	{
		printf("SARADC init failed\n\r");
	}
	else
	{
		printf("SARADC initialized\n\r");
	}
#endif

	/* start the second core*/
	core_start_core1();

	/* configure the timer */
	core_set_timer_timeout(TIMEOUT_250MS);

#if 1
	/* generate some audio data */
	for(uint32_t i=0;i<128;i++)
	{
		i2s_buffer[i] = ((i<<9)&0xFFFF) | ((((128-i)<<9)&0xFFFF)<<16);
	}

	/* start I2S external */
#ifdef I2S_DMA
	if(i2s_ext_dma_init((uint32_t *)i2s_buffer, sizeof(i2s_buffer)/sizeof(uint32_t)))
#else
#ifndef I2S_IRQ
	if(i2s_ext_pio_init())
#else
	if(i2s_ext_irq_init())
#endif
#endif
	{
		printf("I2S Ext init failed\n\r");
	}
	else
	{
		printf("I2S Ext initialized\n\r");
	}
	
#if 0
	/* check clocking for I2S */
	printf("PLL G2 ------------------------------------------\n\r");
	printf("g2_ctrl = 0x%08X\n\r", PLL_G2->pll_g2_ctrl);
	printf("g2_stat = 0x%08X\n\r", PLL_G2->pll_g2_status);
	printf("apll0_csr = 0x%08X\n\r", PLL_G2->apll0_csr);
	printf("apll_ssc_syn_ctrl = 0x%08X\n\r", PLL_G2->apll_ssc_syn_ctrl);
	printf("apll_ssc_syn_set = 0x%08X\n\r", PLL_G2->apll_ssc_syn_set);
	printf("apll_frac_div_ctrl = 0x%08X\n\r", PLL_G2->apll_frac_div_ctrl);
	printf("apll_frac_div_m = 0x%08X\n\r", PLL_G2->apll_frac_div_m);
	printf("apll_frac_div_n = 0x%08X\n\r", PLL_G2->apll_frac_div_n);
	printf("a0pll_clk_csr = 0x%08X\n\r", PLL_G2->a0pll_clk_csr);
	
	printf("CLKGEN ------------------------------------------\n\r");
	printf("clk_en_1 = 0x%08X\n\r", CLKGEN->clk_en_1);
	printf("clk_byp_0 = 0x%08X\n\r", CLKGEN->clk_byp_0);
	printf("div_clk_sdma_aud0 = 0x%08X\n\r", CLKGEN->div_clk_sdma_aud0);
	printf("div_clk_sdma_aud1 = 0x%08X\n\r", CLKGEN->div_clk_sdma_aud1);
	printf("div_clk_sdma_aud2 = 0x%08X\n\r", CLKGEN->div_clk_sdma_aud2);
	printf("div_clk_sdma_aud3 = 0x%08X\n\r", CLKGEN->div_clk_sdma_aud3);

	printf("AIAO --------------------------------------------\n\r");
	printf("i2s_tdm_sclk_in_sel = 0x%08X\n\r", AIAO->i2s_tdm_sclk_in_sel);
	printf("i2s_tdm_fs_in_sel = 0x%08X\n\r", AIAO->i2s_tdm_fs_in_sel);
	printf("i2s_tdm_sdi_in_sel = 0x%08X\n\r", AIAO->i2s_tdm_sdi_in_sel);
	printf("i2s_tdm_sdo_out_sel = 0x%08X\n\r", AIAO->i2s_tdm_sdo_out_sel);
	printf("i2s_tdm_multi_sync = 0x%08X\n\r", AIAO->i2s_tdm_multi_sync);
	printf("i2s_bclk_oen_sel = 0x%08X\n\r", AIAO->i2s_bclk_oen_sel);
	printf("i2s_bclk_out_ctrl = 0x%08X\n\r", AIAO->i2s_bclk_out_ctrl);
	printf("sys_clk_ctrl = 0x%08X\n\r", AIAO->sys_clk_ctrl);
	printf("i2s0_master_clk_ctrl0 = 0x%08X\n\r", AIAO->i2s0_master_clk_ctrl0);
	printf("i2s0_master_clk_ctrl1 = 0x%08X\n\r", AIAO->i2s0_master_clk_ctrl1);
	printf("i2s1_master_clk_ctrl0 = 0x%08X\n\r", AIAO->i2s1_master_clk_ctrl0);
	printf("i2s1_master_clk_ctrl1 = 0x%08X\n\r", AIAO->i2s1_master_clk_ctrl1);
	printf("i2s2_master_clk_ctrl0 = 0x%08X\n\r", AIAO->i2s2_master_clk_ctrl0);
	printf("i2s2_master_clk_ctrl1 = 0x%08X\n\r", AIAO->i2s2_master_clk_ctrl1);
	printf("i2s3_master_clk_ctrl0 = 0x%08X\n\r", AIAO->i2s3_master_clk_ctrl0);
	printf("i2s3_master_clk_ctrl1 = 0x%08X\n\r", AIAO->i2s3_master_clk_ctrl1);
	printf("sys_lrck_ctrl = 0x%08X\n\r", AIAO->sys_lrck_ctrl);

	printf("I2S_TDM_2 ---------------------------------------\n\r");
	printf("BLK_MODE_SETTING = 0x%08X\n\r", I2S_TDM_2->BLK_MODE_SETTING);
	printf("FRAME_SETTING = 0x%08X\n\r", I2S_TDM_2->FRAME_SETTING);
	printf("SLOT_SETTING1 = 0x%08X\n\r", I2S_TDM_2->SLOT_SETTING1);
	printf("SLOT_SETTING2 = 0x%08X\n\r", I2S_TDM_2->SLOT_SETTING2);
	printf("DATA_FORMAT = 0x%08X\n\r", I2S_TDM_2->DATA_FORMAT);
	printf("BLK_CFG = 0x%08X\n\r", I2S_TDM_2->BLK_CFG);
	printf("I2S_ENABLE = 0x%08X\n\r", I2S_TDM_2->I2S_ENABLE);
	printf("I2S_RESET = 0x%08X\n\r", I2S_TDM_2->I2S_RESET);
	printf("I2S_INT_EN = 0x%08X\n\r", I2S_TDM_2->I2S_INT_EN);
	printf("I2S_INT = 0x%08X\n\r", I2S_TDM_2->I2S_INT);
	printf("FIFO_THRESHOLD = 0x%08X\n\r", I2S_TDM_2->FIFO_THRESHOLD);
	printf("I2S_LRCK_MASTER = 0x%08X\n\r", I2S_TDM_2->I2S_LRCK_MASTER);
	printf("FIFO_RESET = 0x%08X\n\r", I2S_TDM_2->FIFO_RESET);
	printf("RX_STATUS = 0x%08X\n\r", I2S_TDM_2->RX_STATUS);
	printf("TX_STATUS = 0x%08X\n\r", I2S_TDM_2->TX_STATUS);
	printf("I2S_CLK_CTRL0 = 0x%08X\n\r", I2S_TDM_2->I2S_CLK_CTRL0);
	printf("I2S_CLK_CTRL1 = 0x%08X\n\r", I2S_TDM_2->I2S_CLK_CTRL1);
	printf("I2S_PCM_SYNTH = 0x%08X\n\r", I2S_TDM_2->I2S_PCM_SYNTH);
	
	printf("I2S_TDM_1 ---------------------------------------\n\r");
	printf("BLK_MODE_SETTING = 0x%08X\n\r", I2S_TDM_1->BLK_MODE_SETTING);
	printf("FRAME_SETTING = 0x%08X\n\r", I2S_TDM_1->FRAME_SETTING);
	printf("SLOT_SETTING1 = 0x%08X\n\r", I2S_TDM_1->SLOT_SETTING1);
	printf("SLOT_SETTING2 = 0x%08X\n\r", I2S_TDM_1->SLOT_SETTING2);
	printf("DATA_FORMAT = 0x%08X\n\r", I2S_TDM_1->DATA_FORMAT);
	printf("BLK_CFG = 0x%08X\n\r", I2S_TDM_1->BLK_CFG);
	printf("I2S_ENABLE = 0x%08X\n\r", I2S_TDM_1->I2S_ENABLE);
	printf("I2S_RESET = 0x%08X\n\r", I2S_TDM_1->I2S_RESET);
	printf("I2S_INT_EN = 0x%08X\n\r", I2S_TDM_1->I2S_INT_EN);
	printf("I2S_INT = 0x%08X\n\r", I2S_TDM_1->I2S_INT);
	printf("FIFO_THRESHOLD = 0x%08X\n\r", I2S_TDM_1->FIFO_THRESHOLD);
	printf("I2S_LRCK_MASTER = 0x%08X\n\r", I2S_TDM_1->I2S_LRCK_MASTER);
	printf("FIFO_RESET = 0x%08X\n\r", I2S_TDM_1->FIFO_RESET);
	printf("RX_STATUS = 0x%08X\n\r", I2S_TDM_1->RX_STATUS);
	printf("TX_STATUS = 0x%08X\n\r", I2S_TDM_1->TX_STATUS);
	printf("I2S_CLK_CTRL0 = 0x%08X\n\r", I2S_TDM_1->I2S_CLK_CTRL0);
	printf("I2S_CLK_CTRL1 = 0x%08X\n\r", I2S_TDM_1->I2S_CLK_CTRL1);
	printf("I2S_PCM_SYNTH = 0x%08X\n\r", I2S_TDM_1->I2S_PCM_SYNTH);
	
	printf("Check offsets:    I2S_TDM_2 = 0x%08X\n\r", I2S_TDM_2);
	printf("I2S_TDM_2->BLK_MODE_SETTING = 0x%08X\n\r", &(I2S_TDM_2->BLK_MODE_SETTING));
	printf("      I2S_TDM_2->FIFO_RESET = 0x%08X\n\r", &(I2S_TDM_2->FIFO_RESET));
	printf("       I2S_TDM_2->RX_STATUS = 0x%08X\n\r", &(I2S_TDM_2->RX_STATUS));
	printf("       I2S_TDM_2->TX_STATUS = 0x%08X\n\r", &(I2S_TDM_2->TX_STATUS));
	printf("   I2S_TDM_2->I2S_CLK_CTRL0 = 0x%08X\n\r", &(I2S_TDM_2->I2S_CLK_CTRL0));
	printf("      I2S_TDM_2->RX_RD_PORT = 0x%08X\n\r", &(I2S_TDM_2->RX_RD_PORT));
	printf("    I2S_TDM_2->RX_RD_PORT_1 = 0x%08X\n\r", &(I2S_TDM_2->RX_RD_PORT_1));
	printf("      I2S_TDM_2->TX_WR_PORT = 0x%08X\n\r", &(I2S_TDM_2->TX_WR_PORT));
	printf("    I2S_TDM_2->TX_WR_PORT_1 = 0x%08X\n\r", &(I2S_TDM_2->TX_WR_PORT_1));
#endif
#if 0
	printf("\n\nCheck IRQ settings & status after startup:\n\r");
	printf("PLIC0_IRQ_I2S2 = %d\n\r", PLIC0_IRQ_I2S2);
	printf("PLIC0_IRQ_I2S1 = %d\n\r", PLIC0_IRQ_I2S1);
	printf("AIAO->i2s_sys_int_en = 0x%08X\n\r", AIAO->i2s_sys_int_en);
	printf("AIAO->i2s_sys_ints = 0x%08X\n\r", AIAO->i2s_sys_ints);
	printf("I2S_TDM_2->I2S_INT_EN = 0x%08X\n\r", I2S_TDM_2->I2S_INT_EN);
	printf("I2S_TDM_2->I2S_INT = 0x%08X\n\r", I2S_TDM_2->I2S_INT);
	printf("I2S_TDM_1->I2S_INT_EN = 0x%08X\n\r", I2S_TDM_1->I2S_INT_EN);
	printf("I2S_TDM_1->I2S_INT = 0x%08X\n\r", I2S_TDM_1->I2S_INT);
	printf("plic_get_priority(PLIC0_IRQ_I2S2) = 0x%08X\n\r", plic_get_priority(PLIC0_IRQ_I2S2));
	printf("plic_get_priority(PLIC0_IRQ_I2S1) = 0x%08X\n\r", plic_get_priority(PLIC0_IRQ_I2S1));
	printf("plic_get_enable(PLIC0_IRQ_I2S2) = 0x%08X\n\r", plic_get_enable(PLIC0_IRQ_I2S2, 1));
	printf("plic_get_enable(PLIC0_IRQ_I2S1) = 0x%08X\n\r", plic_get_enable(PLIC0_IRQ_I2S1, 1));
	printf("plic_get_pending(PLIC0_IRQ_I2S2) = 0x%08X\n\r", plic_get_pending(PLIC0_IRQ_I2S2));
	printf("plic_get_pending(PLIC0_IRQ_I2S1) = 0x%08X\n\n\r", plic_get_pending(PLIC0_IRQ_I2S1));
#endif
#endif

	/* endless loop */
	while(1)
	{
		// send char
		//uart_tx(HW_UART, '+');
		
#if 0
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
#endif

#if 0
		// I2C transaction
		GPIOA->SWPORTA_DR.bits.P26 = 1;
		//i2c_tx(HW_I2C, target_addr, i2c_txbuf, 2);
		uint32_t errstat = i2c_txrx(HW_I2C, target_addr, i2c_txbuf, 1,
			i2c_rxbuf, 2);
		GPIOA->SWPORTA_DR.bits.P26 = 0;
		if(errstat)
			printf("Error %1d\n\r", errstat);
		else
			printf("RX Data = %02X %02X\n\r", i2c_rxbuf[0], i2c_rxbuf[1]);
#endif

#if 0
		// SARADC tests
		for(uint8_t i=1;i<4;i++)
		{
			uint16_t adc_val;
			uint32_t adc_stat;
			if((adc_stat = saradc_getchl(HW_SARADC, i, &adc_val)))
				printf("XXX%1d ", adc_stat);
			else
				printf("%4d ", adc_val & 0xfff);
		}
		printf("\n\r");
#endif

#if 1
#ifndef I2S_IRQ
		/* PIO mode - transmit - wrapped with GPIO toggle for diag */
		GPIOA->SWPORTA_DR.bits.P26 = 1;
		__asm(""::: "memory");
		if(i2s_ext_pio_tx(i2s_buffer[i2s_tx_ptr]))
			i2s_tx_err++;
		else
			i2s_tx++;
		i2s_tx_ptr = (i2s_tx_ptr + 1) & 0x7f;
		GPIOA->SWPORTA_DR.bits.P26 = 0;
		__asm(""::: "memory");
		
		/* receive - not actually using data yet */
		if(i2s_ext_pio_rx((uint32_t *)&i2s_rx_data))
			i2s_rx++;
#else
		/* DMA & IRQ mode I/O handled in ISR so just delay a bit */
		delayus(21);	// roughly 1/48k
#endif

		/* status */
		if(i2s_cnt++ > 48000)
		{
			i2s_cnt = 0;
			printf("%8d %8d %8d %8d %8d %8d\n\r", i2s_tx, i2s_tx_err, i2s_rx, i2s_rx_err, i2s_tx-i2s_rx, isr_ext_cnt);
		}
#endif
		//delayms(100);
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
void isr_ext(void)
{
	uint32_t ActiveCore = osGetActiveCore();

	isr_ext_cnt++;
	
	if(CORE0_ID == ActiveCore)
	{
		/* which IRQ was it? */
		uint32_t id = plic_get_claim(1);

		/* do stuff */
#ifdef I2S_IRQ
		if(id == PLIC0_IRQ_I2S2)
		{
			/* master tx */
			GPIOA->SWPORTA_DR.bits.P26 = 1;
			__asm(""::: "memory");
			
			if(i2s_ext_irq_tx(i2s_buffer[i2s_tx_ptr]))
			{
				i2s_tx++;
				i2s_tx_ptr = (i2s_tx_ptr + 1) & 0x7f;
			}
			else
				i2s_tx_err++;

			GPIOA->SWPORTA_DR.bits.P26 = 0;
			__asm(""::: "memory");
		}
		else if(id == PLIC0_IRQ_I2S1)
		{
			/* slave rx */
			if(i2s_ext_irq_rx((uint32_t *)&i2s_rx_data))
				i2s_rx++;
			else
				i2s_rx_err++;
		}
#endif

#ifdef I2S_DMA
		if(id == PLIC0_IRQ_SYS_DMA)
		{
			/* handle SDMA IRQ */
		}
#endif

		/* clear the IRQ */
		plic_set_claim(1, id);
	}
	else if(CORE1_ID == ActiveCore)
	{
		/* which IRQ was it? */
		uint32_t id = plic_get_claim(1);

		/* do stuff */

		/* clear the IRQ */
		plic_set_claim(1, id);
	}
	else
	{
		/* error identifying the active core */
		__asm("j .");
	}
}

