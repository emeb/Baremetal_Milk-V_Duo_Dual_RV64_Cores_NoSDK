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
	uint32_t RESERVED_2[5];				/* 0x04c - 0x05c */
	volatile uint32_t I2S_CLK_CTRL0;	/* 0x060: Clock control */
	volatile uint32_t I2S_CLK_CTRL1;	/* 0x064: Clock divider */
	volatile uint32_t I2S_PCM_SYNTH;	/* 0x068: PCM FS synthesis mode*/
	uint32_t RESERVED_3[5];				/* 0x06c - 0x07c */
	volatile uint32_t RX_RD_PORT;		/* 0x080: RX FIFO read port 0 */
	volatile uint32_t RX_RD_PORT_1;		/* 0x080: RX FIFO read port 1 */
	uint32_t RESERVED_4[14];			/* 0x084 - 0x0bc */
	volatile uint32_t TX_WR_PORT;		/* 0x0c0: TX FIFO write port 0 */
	volatile uint32_t TX_WR_PORT_1;		/* 0x0c4: TX FIFO write port 1 */
} I2S_TDM_TypeDef;

/* Peripheral Base Definitions */
#define I2S_TDM_0_BASE    (0x04100000ull)
#define I2S_TDM_1_BASE    (0x04110000ull)
#define I2S_TDM_2_BASE    (0x04120000ull)
#define I2S_TDM_3_BASE    (0x04130000ull)

/* Instance Pointers */
#define I2S_TDM_0    ((I2S_TDM_TypeDef *)I2S_TDM_0_BASE)
#define I2S_TDM_1    ((I2S_TDM_TypeDef *)I2S_TDM_1_BASE)
#define I2S_TDM_2    ((I2S_TDM_TypeDef *)I2S_TDM_2_BASE)
#define I2S_TDM_3    ((I2S_TDM_TypeDef *)I2S_TDM_3_BASE)

/* Register fields */
#define I2S_TDM_BLK_MODE_SETTING_TX_MODE			(1u)
#define I2S_TDM_BLK_MODE_SETTING_MASTER_MODE		(1<<1)
#define I2S_TDM_BLK_MODE_SETTING_RX_SAMPLE_EDGE_POS	(1u<<2)
#define I2S_TDM_BLK_MODE_SETTING_TX_SAMPLE_EDGE_POS	(1u<<3)
#define I2S_TDM_BLK_MODE_SETTING_DMA_MODE			(1u<<7)
#define I2S_TDM_BLK_MODE_SETTING_MULTIBIT			(1u<<8)
#define I2S_TDM_BLK_MODE_SETTING_EXT_FS				(1u<<10)
#define I2S_TDM_BLK_MODE_SETTING_PCM_SYNTH			(1u<<12)
#define I2S_TDM_FRAME_SETTING_FRAME_LENGTH_POS 		(0)
#define I2S_TDM_FRAME_SETTING_FRAME_LENGTH_MASK		(0x1ffu)
#define I2S_TDM_FRAME_SETTING_FS_POLARITY_HIGH		(1u<<12)
#define I2S_TDM_FRAME_SETTING_FS_OFFSET_I2S			(1u<<13)
#define I2S_TDM_FRAME_SETTING_FS_IDEF_LRCK			(1u<<14)
#define I2S_TDM_FRAME_SETTING_FRAME_ACT_LENGTH_POS 	(16)
#define I2S_TDM_FRAME_SETTING_FRAME_ACT_LENGTH_MASK	(0xffu<<I2S_TDM_FRAME_SETTING_FRAME_ACT_LENGTH_POS)
#define I2S_TDM_SLOT_SETTING1_SLOT_NUM_POS			(0)
#define I2S_TDM_SLOT_SETTING1_SLOT_NUM_MASK			(0xfu)
#define I2S_TDM_SLOT_SETTING1_SLOT_SIZE_POS			(8)
#define I2S_TDM_SLOT_SETTING1_SLOT_SIZE_MASK		(0x3fu<<I2S_TDM_SLOT_SETTING1_SLOT_SIZE_POS)
#define I2S_TDM_SLOT_SETTING1_DATA_SIZE_POS			(16)
#define I2S_TDM_SLOT_SETTING1_DATA_NUM_MASK			(0x1fu<<I2S_TDM_SLOT_SETTING1_DATA_SIZE_POS)
#define I2S_TDM_SLOT_SETTING1_FB_OFFSET_POS			(24)
#define I2S_TDM_SLOT_SETTING1_FB_OFFSET_MASK		(0x1fu<<I2S_TDM_SLOT_SETTING1_FB_OFFSET_POS)
#define I2S_TDM_DATA_FORMAT_DATA_FORMAT_RESERVED	(1u)
#define I2S_TDM_DATA_FORMAT_WORD_LENGTH_POS			(1u)
#define I2S_TDM_DATA_FORMAT_WORD_LENGTH_MASK		(3<<I2S_TDM_DATA_FORMAT_WORD_LENGTH_POS)
#define I2S_TDM_DATA_FORMAT_PAD_SLOT_NO_4BIT		(1u<<3)
#define I2S_TDM_DATA_FORMAT_SKIP_RX_INACTIVE_SLOT	(1u<<4)
#define I2S_TDM_DATA_FORMAT_SKIP_TX_INACTIVE_SLOT	(1u<<5)
#define I2S_TDM_DATA_FORMAT_SKIP_TX_SOURCE_LEFT_ALIGN	(1<<6)
#define I2S_TDM_BLK_CFG_FORCE_COMPLETE				(1u)
#define I2S_TDM_BLK_CFG_DMA_REQ_FORCE_STOP			(1u<<1)
#define I2S_TDM_BLK_CFG_AUTO_DISABLE_WITH_CH_EN		(1u<<4)
#define I2S_TDM_BLK_CFG_RX_START_WAIT_DMA_EN		(1u<<6)
#define I2S_TDM_BLK_RX_BLK_CLK_FORCE_EN				(1u<<8)
#define I2S_TDM_BLK_RX_FIFO_DMA_CLK_FORCE_EN		(1u<<9)
#define I2S_TDM_BLK_TX_BLK_CLK_FORCE_EN				(1u<<16)
#define I2S_TDM_BLK_TX_FIFO_DMA_CLK_FORCE_EN		(1u<<17)
#define I2S_TDM_I2S_RESET_RX						(1u)
#define I2S_TDM_I2S_RESET_TX						(1u<<1)
#define I2S_TDM_I2S_INT_TX_FIFO_AVAIL_INT			(1u<<4)
#define I2S_TDM_I2S_INT_TX_FIFO_AVAIL_INT_RAW		(1u<<12)
/* more to come... */

void i2s_io_bypass(void);
uint32_t i2s_ext_init(void);
uint32_t i2s_ext_tx(uint32_t data);


#ifdef __cplusplus
}
#endif

#endif /* I2S_TDM_H */