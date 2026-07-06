/******************************************************************************************
  Filename    : clkgen.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.07.2026
  
  Description : Clock Generator peripheral header file
  
******************************************************************************************/

#ifndef CLKGEN_H
#define CLKGEN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct  CLKGEN_TypeDef
 * @brief   CLKGEN Register Layout
 */
typedef struct {
	uint32_t clk_en_0;			/* 0x000: clock enable register 0 */
	uint32_t clk_en_1;			/* 0x004: clock enable register 1 */
	uint32_t clk_en_2;			/* 0x008: clock enable register 2 */
	uint32_t clk_en_3;			/* 0x00c: clock enable register 3 */
	uint32_t clk_en_4;			/* 0x010: clock enable register 4 */
	uint32_t RESERVED_0[3];
	uint32_t clk_sel_0;			/* 0x020: clock source selection register 0 */
	uint32_t RESERVED_1[3];
	uint32_t clk_byp_0;			/* 0x030: clock bypass to xtal register 0 */
	uint32_t clk_byp_1;			/* 0x034: clock bypass to xtal register 1 */
	uint32_t RESERVED_2[4];
	uint32_t div_clk_cpu_axi0;	/* 0x048: divider register of clk_cpu_axi0 */
	uint32_t RESERVED_3[2];
	uint32_t div_clk_tpu;		/* 0x054: divider register of clk_tpu */
	uint32_t RESERVED_4[6];
	uint32_t div_clk_sd0;		/* 0x070: divider register of clk_sd0 */
	uint32_t RESERVED_5;
	uint32_t div_clk_100k_sd0;	/* 0x078: divider register of clk_100k_sd0 */
	uint32_t div_clk_sd1;		/* 0x07c: divider register of clk_sd1 */
	uint32_t RESERVED_6;
	uint32_t div_clk_100k_sd1;	/* 0x084: divider register of clk_100k_sd1 */
	uint32_t div_clk_spi_nand;	/* 0x088: divider register of clk_spi_nand */
	uint32_t div_clk_500m_eth0;	/* 0x08c: divider register of clk_500m_eth0 */
	uint32_t RESERVED_7;
	uint32_t div_clk_gpio_db;	/* 0x094: divider register of clk_gpio_db */
	uint32_t div_clk_sdma_aud0;	/* 0x098: divider register of clk_sdma_aud0 */
	uint32_t div_clk_sdma_aud1;	/* 0x09c: divider register of clk_sdma_aud1 */
	uint32_t div_clk_sdma_aud2;	/* 0x0a0: divider register of clk_sdma_aud2 */
	uint32_t div_clk_sdma_aud3;	/* 0x0a4: divider register of clk_sdma_aud3 */
	uint32_t div_clk_cam0_200;	/* 0x0a8: divider register of clk_cam0_200 */
	uint32_t RESERVED_8[3];
	uint32_t div_clk_axi4;		/* 0x0b8: divider register of clk_axi4 */
	uint32_t div_clk_axi6;		/* 0x0bc: divider register of clk_axi6 */
	uint32_t RESERVED_9;
	uint32_t div_clk_dsi_esc;	/* 0x0c4: divider register of clk_dsi_esc */
	uint32_t div_clk_axi_vip;	/* 0x0c8: divider register of clk_axi_vip */
	uint32_t div_clk_src_vip_sys_0;	/* 0x0d0: divider register of clk_src_vip_sys_0 */
	uint32_t RESERVED_10;
	uint32_t div_clk_src_vip_sys_1;	/* 0x0d8: divider register of clk_src_vip_sys_1 */
	uint32_t RESERVED_11;
	uint32_t div_clk_disp_src_vip;	/* 0x0e0: divider register of clk_disp_src_vip */
	/* there are more but I don't need them ATM */
} CLKGEN_TypeDef;

/* Peripheral Base Definitions */
#define CLKGEN_BASE    (0x03002000ull)

/* Instance Pointers */
#define CLKGEN    ((CLKGEN_TypeDef *)CLKGEN_BASE)

#ifdef __cplusplus
}
#endif

#endif /* CLKGEN_H */
