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
 * @struct  PLL_G2_TypeDef
 * @brief   PLL_G2 Register Layout
 */
typedef struct {
	volatile uint32_t pll_g2_ctrl;			/* 0x000: Group2 PLL Ctrl register */
	volatile uint32_t pll_g2_status;		/* 0x004: Group2 PLL Status register */
	volatile uint32_t mipimpll_csr;			/* 0x008: MIPIMPLL Ctrl register */
	volatile uint32_t apll0_csr;			/* 0x00c: APLL0 Ctrl register */
	volatile uint32_t disppll_csr;			/* 0x010: DISPPLL Ctrl register */
	volatile uint32_t cam0pll_csr;			/* 0x014: CAM0PLL Ctrl register */
	volatile uint32_t cam1pll_csr;			/* 0x018: CAM1PLL Ctrl register */
	uint32_t RESERVED_0[8];					/* 0x01c - 0x03c */
	volatile uint32_t pll_g2_ssc_syn_ctrl;	/* 0x040: Group2 PLL Synthesizer ctrl register */
	uint32_t RESERVED_1[3];					/* 0x044 - 0x04c */
	volatile uint32_t apll_ssc_syn_ctrl;	/* 0x050: APLL synthesizer ctrl register */
	volatile uint32_t apll_ssc_syn_set;		/* 0x054: APLL synthesizer set register */
	uint32_t RESERVED_2[2];					/* 0x058 - 0x05c */
	volatile uint32_t disppll_ssc_syn_ctrl;	/* 0x060: DISPPLL synthesizer ctrl register */
	volatile uint32_t disppll_ssc_syn_set;	/* 0x064: DISPPLL synthesizer set register */
	uint32_t RESERVED_3[2];					/* 0x068 - 0x06c */
	volatile uint32_t cam0pll_ssc_syn_ctrl;	/* 0x070: CAM0PLL synthesizer ctrl register */
	volatile uint32_t cam0pll_ssc_syn_set;	/* 0x074: CAM0PLL synthesizer set register */
	uint32_t RESERVED_4[2];					/* 0x078 - 0x07c */
	volatile uint32_t cam1pll_ssc_syn_ctrl;	/* 0x080: CAM1PLL synthesizer ctrl register */
	volatile uint32_t cam1pll_ssc_syn_set;	/* 0x084: CAM1PLL synthesizer set register */
	uint32_t RESERVED_5[2];					/* 0x088 - 0x08c */
	volatile uint32_t apll_frac_div_ctrl;	/* 0x090: APLL frac divider ctrl register */
	volatile uint32_t apll_frac_div_m;		/* 0x094: APLL frac divider M parameter */
	volatile uint32_t apll_frac_div_n;		/* 0x098: APLL frac divider N parameter */
	uint32_t RESERVED_6;					/* 0x09c */
	volatile uint32_t mipimpll_clk_csr;		/* 0x0a0: MIPIMPLL clock Ctrl register */
	volatile uint32_t a0pll_clk_csr;		/* 0x0a4: a0pll clock Ctrl register */
	volatile uint32_t disppll_clk_csr;		/* 0x0a8: disppll clock Ctrl register */
	volatile uint32_t cam0pll_clk_csr;		/* 0x0ac: cam0pll clock Ctrl register */
	volatile uint32_t cam1pll_clk_csr;		/* 0x0b0: cam1pll clock Ctrl register */
	uint32_t RESERVED_7[3];					/* 0x0b4 - 0x0bc */
	volatile uint32_t clk_cam0_src_div;		/* 0x0c0: clk_cam0_src_div */
	volatile uint32_t clk_cam1_src_div;		/* 0x0c4: clk_cam1_src_div */
} PLL_G2_TypeDef;

/* Peripheral Base Definitions */
#define PLL_G2_BASE    (0x03002800ull)

/* Instance Pointers */
#define PLL_G2    ((PLL_G2_TypeDef *)PLL_G2_BASE)

/**
 * @struct  PLL_G6_TypeDef
 * @brief   PLL_G6 Register Layout
 */
typedef struct {
	volatile uint32_t pll_g6_ctrl;			/* 0x000: Group6 PLL Ctrl register */
	volatile uint32_t pll_g6_status;		/* 0x004: Group6 PLL Status register */
	volatile uint32_t mpll_csr;				/* 0x008: MPLL Ctrl register */
	volatile uint32_t tpll_csr;				/* 0x00c: TPLL Ctrl register */
	volatile uint32_t fpll_csr;				/* 0x010: FPLL Ctrl register */
	uint32_t RESERVED_0[10];				/* 0x014 - 0x03c */
	volatile uint32_t pll_g6_ssc_syn_ctrl;	/* 0x040: Group6 PLL Synthesizer ctrl register */
	uint32_t RESERVED_1[3];					/* 0x044 - 0x04c */
	volatile uint32_t dpll_ssc_syn_ctrl;	/* 0x050: DPLL synthesizer ctrl register */
	volatile uint32_t dpll_ssc_syn_set;		/* 0x054: DPLL synthesizer set register */
	volatile uint32_t dpll_ssc_syn_span;	/* 0x058: DPLL synthesizer span register */
	volatile uint32_t dpll_ssc_syn_step;	/* 0x05c: DPLL synthesizer step register */
	volatile uint32_t mpll_ssc_syn_ctrl;	/* 0x060: MPLL synthesizer ctrl register */
	volatile uint32_t mpll_ssc_syn_set;		/* 0x064: MPLL synthesizer set register */
	volatile uint32_t mpll_ssc_syn_span;	/* 0x068: MPLL synthesizer span register */
	volatile uint32_t mpll_ssc_syn_step;	/* 0x06c: MPLL synthesizer step register */
	volatile uint32_t tpll_ssc_syn_ctrl;	/* 0x070: TPLL synthesizer ctrl register */
	volatile uint32_t tpll_ssc_syn_set;		/* 0x074: TPLL synthesizer set register */
	volatile uint32_t tpll_ssc_syn_span;	/* 0x078: TPLL synthesizer span register */
	volatile uint32_t tpll_ssc_syn_step;	/* 0x07c: TPLL synthesizer step register */
} PLL_G6_TypeDef;

/* Peripheral Base Definitions */
#define PLL_G6_BASE    (0x03002900ull)

/* Instance Pointers */
#define PLL_G6    ((PLL_G5_TypeDef *)PLL_G6_BASE)

/**
 * @struct  CLKGEN_TypeDef
 * @brief   CLKGEN Register Layout
 */
typedef struct {
	volatile uint32_t clk_en_0;					/* 0x000: clock enable register 0 */
	volatile uint32_t clk_en_1;					/* 0x004: clock enable register 1 */
	volatile uint32_t clk_en_2;					/* 0x008: clock enable register 2 */
	volatile uint32_t clk_en_3;					/* 0x00c: clock enable register 3 */
	volatile uint32_t clk_en_4;					/* 0x010: clock enable register 4 */
	uint32_t RESERVED_0[3];						/* 0x014 - 0x01c */
	volatile uint32_t clk_sel_0;				/* 0x020: clock source selection register 0 */
	uint32_t RESERVED_1[3];						/* 0x024 - 0x03c */
	volatile uint32_t clk_byp_0;				/* 0x030: clock bypass to xtal register 0 */
	volatile uint32_t clk_byp_1;				/* 0x034: clock bypass to xtal register 1 */
	uint32_t RESERVED_2[4];						/* 0x038 - 0x044 */
	volatile uint32_t div_clk_cpu_axi0;			/* 0x048: divider register of clk_cpu_axi0 */
	uint32_t RESERVED_3[2];						/* 0x04c - 0x050 */
	volatile uint32_t div_clk_tpu;				/* 0x054: divider register of clk_tpu */
	uint32_t RESERVED_4[6];						/* 0x058 - 0x06c */
	volatile uint32_t div_clk_sd0;				/* 0x070: divider register of clk_sd0 */
	uint32_t RESERVED_5;						/* 0x073 */
	volatile uint32_t div_clk_100k_sd0;			/* 0x078: divider register of clk_100k_sd0 */
	volatile uint32_t div_clk_sd1;				/* 0x07c: divider register of clk_sd1 */
	uint32_t RESERVED_6;						/* 0x080 */
	volatile uint32_t div_clk_100k_sd1;			/* 0x084: divider register of clk_100k_sd1 */
	volatile uint32_t div_clk_spi_nand;			/* 0x088: divider register of clk_spi_nand */
	volatile uint32_t div_clk_500m_eth0;		/* 0x08c: divider register of clk_500m_eth0 */
	uint32_t RESERVED_7;						/* 0x090 */
	volatile uint32_t div_clk_gpio_db;			/* 0x094: divider register of clk_gpio_db */
	volatile uint32_t div_clk_sdma_aud0;		/* 0x098: divider register of clk_sdma_aud0 */
	volatile uint32_t div_clk_sdma_aud1;		/* 0x09c: divider register of clk_sdma_aud1 */
	volatile uint32_t div_clk_sdma_aud2;		/* 0x0a0: divider register of clk_sdma_aud2 */
	volatile uint32_t div_clk_sdma_aud3;		/* 0x0a4: divider register of clk_sdma_aud3 */
	volatile uint32_t div_clk_cam0_200;			/* 0x0a8: divider register of clk_cam0_200 */
	uint32_t RESERVED_8[3];						/* 0x0ac - 0x0b4 */
	volatile uint32_t div_clk_axi4;				/* 0x0b8: divider register of clk_axi4 */
	volatile uint32_t div_clk_axi6;				/* 0x0bc: divider register of clk_axi6 */
	uint32_t RESERVED_9;						/* 0x0c0 */
	volatile uint32_t div_clk_dsi_esc;			/* 0x0c4: divider register of clk_dsi_esc */
	volatile uint32_t div_clk_axi_vip;			/* 0x0c8: divider register of clk_axi_vip */
	volatile uint32_t div_clk_src_vip_sys_0;	/* 0x0d0: divider register of clk_src_vip_sys_0 */
	uint32_t RESERVED_10;						/* 0x0d4 */
	volatile uint32_t div_clk_src_vip_sys_1;	/* 0x0d8: divider register of clk_src_vip_sys_1 */
	uint32_t RESERVED_11;						/* 0x0dc */
	volatile uint32_t div_clk_disp_src_vip;		/* 0x0e0: divider register of clk_disp_src_vip */
	volatile uint32_t div_clk_axi_video_codec;	/* 0x0e4: divider register of clk_axi_video_codec */
	volatile uint32_t div_clk_vc_src0;			/* 0x0ec: divider register of clk_vc_src0 */
	uint32_t RESERVED_12[3];					/* 0x0f0 - 0x0f8 */
	volatile uint32_t div_clk_lm;				/* 0x0fc: divider register of clk_1m */
	volatile uint32_t div_clk_spi;				/* 0x100: divider register of clk_spi */
	volatile uint32_t div_clk_i2c;				/* 0x104: divider register of clk_i2c */
	uint32_t RESERVED_13[2];					/* 0x108 - 0x10c */
	volatile uint32_t div_clk_src_vip_sys_2;	/* 0x110: divider register of clk_src_vip_sys_2 */
	uint32_t RESERVED_14;						/* 0x114 */
	volatile uint32_t div_clk_audsrc;			/* 0x118: divider register of clk_audsrc */
	uint32_t RESERVED_15;						/* 0x11c */
	volatile uint32_t div_clk_pwm_src_0;		/* 0x120: divider register of clk_pwm_src_0 */
	uint32_t RESERVED_16;						/* 0x024 */
	volatile uint32_t div_clk_ap_debug;			/* 0x128: divider register of clk_ap_debug */
	volatile uint32_t div_clk_rtcsys_src_0;		/* 0x12c: divider register of clk_rtcsys_src_0 */
	volatile uint32_t div_clk_c906_0_0;			/* 0x130: divider register of clk_c906_0_0 */
	volatile uint32_t div_clk_c906_0_1;			/* 0x134: divider register of clk_c906_0_1 */
	volatile uint32_t div_clk_c906_1_0;			/* 0x138: divider register of clk_c906_1_0 */
	volatile uint32_t div_clk_c906_1_1;			/* 0x13c: divider register of clk_c906_1_1 */
	volatile uint32_t div_clk_src_vip_sys_3;	/* 0x140: divider register of clk_src_vip_sys_3 */
	volatile uint32_t div_clk_src_vip_sys_4;	/* 0x144: divider register of clk_src_vip_sys_4 */
} CLKGEN_TypeDef;

/* Peripheral Base Definitions */
#define CLKGEN_BASE    (0x03002000ull)

/* Instance Pointers */
#define CLKGEN    ((CLKGEN_TypeDef *)CLKGEN_BASE)

#ifdef __cplusplus
}
#endif

#endif /* CLKGEN_H */
