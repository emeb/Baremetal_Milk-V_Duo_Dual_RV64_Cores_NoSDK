/******************************************************************************************
  Filename    : i2s_tdm.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.18.2026
  
  Description : I2S_TDM peripheral header file
  
******************************************************************************************/

#ifndef I2S_TDM_H
#define I2S_TDM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct  I2S_TDM_TypeDef
 * @brief   I2S_TDM Register Layout
 */
typedef struct {
    volatile uint32_t BLK_MODE_SETTING;	/* 0x000: TX/RX module operation control */
	volatile uint32_t FRAME_SETTING;	/* 0x004: Audio frame timing control */
	volatile uint32_t SLOT_SETTING1;	/* 0x008: Channel and data control */
	volatile uint32_t SLOT_SETTING2;	/* 0x00c: Channel enable */
	volatile uint32_t DATA_FORMAT;		/* 0x010: The output control of BCLK IO. */
	volatile uint32_t BLK_CFG;			/* 0x014: Enable PDM mode. */
	volatile uint32_t I2S_ENABLE;		/* 0x018: TX/RX block enable */
	volatile uint32_t I2S_RESET;		/* 0x01c: TX/RX block reset*/
	volatile uint32_t I2S_INT_EN;		/* 0x020: Interrupt enable */
	volatile uint32_t I2S_INT;			/* 0x024: Interrupt status */
	volatile uint32_t FIFO_THRESHOLD;	/* 0x028: FIFO threshold */
	volatile uint32_t I2S_LRCK_MASTER;	/* 0x02c: BCLK/LRCK master generator mode */
	volatile uint32_t FIFO_RESET;		/* 0x030: FIFO reset */
	uint32_t RESERVED_0[3];				/* 0x034 - 0x03c */
	volatile uint32_t RX_STATUS;		/* 0x040: RX block internal status */
	uint32_t RESERVED_1;				/* 0x044 */
	volatile uint32_t TX_STATUS;		/* 0x048: TX block internal status */
	uint32_t RESERVED_2[8];				/* 0x04c - 0x05c */
	volatile uint32_t I2S_CLK_CTRL0;	/* 0x060: Clock control */
	volatile uint32_t I2S_CLK_CTRL1;	/* 0x064: Clock divider */
	volatile uint32_t I2S_PCM_SYNTH;	/* 0x068: PCM FS synthesis mode*/
	uint32_t RESERVED_3[8];				/* 0x06c - 0x07c */
	volatile uint32_t RX_RD_PORT;		/* 0x080: RX FIFO read port */
	uint32_t RESERVED_4[15];			/* 0x084 - 0x0bc */
	volatile uint32_t TX_WR_PORT;		/* 0x0c0: TX FIFO write port */
} I2S_TDM_TypeDef;

/* Peripheral Base Definitions */
#define I2S_TDM_0_BASE    (0x0x04100000ull)
#define I2S_TDM_1_BASE    (0x0x04110000ull)
#define I2S_TDM_2_BASE    (0x0x04120000ull)
#define I2S_TDM_3_BASE    (0x0x04130000ull)

/* Instance Pointers */
#define I2S_TDM_0    ((I2S_TDM_TypeDef *)I2S_TDM_0_BASE)
#define I2S_TDM_1    ((I2S_TDM_TypeDef *)I2S_TDM_1_BASE)
#define I2S_TDM_2    ((I2S_TDM_TypeDef *)I2S_TDM_2_BASE)
#define I2S_TDM_3    ((I2S_TDM_TypeDef *)I2S_TDM_3_BASE)

/* Register fields */
#define I2S_TDM_BLK_MODE_SETTING_TX_MODE			(1)
#define I2S_TDM_BLK_MODE_SETTING_MASTER_MODE		(1<<1)
#define I2S_TDM_BLK_MODE_SETTING_RX_SAMPLE_EDGE_POS	(1<<2)
#define I2S_TDM_BLK_MODE_SETTING_TX_SAMPLE_EDGE_POS	(1<<3)
#define I2S_TDM_BLK_MODE_SETTING_DMA_MODE			(1<<7)
#define I2S_TDM_BLK_MODE_SETTING_MULTIBIT			(1<<8)
#define I2S_TDM_BLK_MODE_SETTING_EXT_FS				(1<<10)
#define I2S_TDM_BLK_MODE_SETTING_PCM_SYNTH			(1<<12)
#define I2S_TDM_FRAME_SETTING_FRAME_LENGTH_POS 		(0)
#define I2S_TDM_FRAME_SETTING_FRAME_LENGTH_MASK		(0x1ff)
#define I2S_TDM_FRAME_SETTING_FS_POLARITY_HIGH		(1<<12)
#define I2S_TDM_FRAME_SETTING_FS_OFFSET_I2S			(1<<13)
#define I2S_TDM_FRAME_SETTING_FS_IDEF_LRCK			(1<<14)
#define I2S_TDM_FRAME_SETTING_FRAME_ACT_LENGTH_POS 	(16)
#define I2S_TDM_FRAME_SETTING_FRAME_ACT_LENGTH_MASK	(0xff<<I2S_TDM_FRAME_SETTING_FRAME_ACT_LENGTH_POS)
/* more to come... */

#ifdef __cplusplus
}
#endif

#endif /* I2S_TDM_H */