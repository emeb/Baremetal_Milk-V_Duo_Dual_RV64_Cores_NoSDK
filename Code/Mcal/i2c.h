/******************************************************************************************
  Filename    : i2c.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 04.12.2026
  
  Description : I2C peripheral header file
  
******************************************************************************************/

#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HW_I2C I2C0

/**
 * @struct  I2C_TypeDef
 * @brief   I2C Register Layout
 */
typedef struct {
	volatile uint32_t IC_CON;			/* 0x000: I2C Control */
	volatile uint32_t IC_TAR;			/* 0x004: I2C Target Address */
	volatile uint32_t IC_SAR;			/* 0x008: I2C Slave Address */
    uint32_t RESERVED_0;				/* 0x00c */
	volatile uint32_t IC_DATA_CMD;		/* 0x010: I2C Rx/Tx Data Buffer and Command */
	volatile uint32_t IC_SS_SCL_HCNT;	/* 0x014: Standard speed I2C Clock SCL High Count */
	volatile uint32_t IC_SS_SCL_LCNT;	/* 0x018: Standard speed I2C Clock SCL Low Count */
	volatile uint32_t IC_FS_SCL_HCNT;	/* 0x01c: Fast speed I2C Clock SCL High Count */
	volatile uint32_t IC_FS_SCL_LCNT;	/* 0x020: Fast speed I2C Clock SCL Low Count */
    uint32_t RESERVED_1[2];				/* 0x024 - 0x028 */
	volatile uint32_t IC_INTR_STAT;		/* 0x02c: I2C Interrupt Status */
	volatile uint32_t IC_INTR_MASK;		/* 0x030: I2C Interrupt Mask */
	volatile uint32_t IC_RAW_INTR_STAT;	/* 0x034: I2C Raw Interrupt Status */
	volatile uint32_t IC_RX_TL;			/* 0x038: I2C Receive FIFO Threshold */
	volatile uint32_t IC_TX_TL;			/* 0x03c: I2C Transmit FIFO Threshold */
	volatile uint32_t IC_CLR_INTR;		/* 0x040: Clear Combined and Individual Interrupts */
	volatile uint32_t IC_CLR_RX_UNDER;	/* 0x044: Clear RX_UNDER Interrupt */
	volatile uint32_t IC_CLR_RX_OVER;	/* 0x048: Clear RX_OVER Interrupt */
	volatile uint32_t IC_CLR_TX_OVER;	/* 0x04c: Clear TX_OVER Interrupt */
	volatile uint32_t IC_CLR_RD_REQ;	/* 0x050: Clear RD_REQ Interrupt */
	volatile uint32_t IC_CLR_TX_ABRT;	/* 0x054: Clear TX_ABRT Interrupt */
	volatile uint32_t IC_CLR_RX_DONE;	/* 0x058: Clear RX_DONE Interrupt */
	volatile uint32_t IC_CLR_ACTIVITY;	/* 0x05c: Clear ACTIVITY Interrupt */
	volatile uint32_t IC_CLR_STOP_DET;	/* 0x060: Clear STOP_DET Interrupt */
	volatile uint32_t IC_CLR_START_DET;	/* 0x064: Clear START_DET Interrupt */
	volatile uint32_t IC_CLR_GEN_CALL;	/* 0x068: Clear GEN_CALL Interrupt */
	volatile uint32_t IC_ENABLE;		/* 0x06c: I2C Enable */
	volatile uint32_t IC_STATUS;		/* 0x070: I2C Status register */
	volatile uint32_t IC_TXFLR;			/* 0x074: Transmit FIFO Level Register */
	volatile uint32_t IC_RXFLR;			/* 0x078: Receive FIFO Level Register */
	volatile uint32_t IC_SDA_HOLD;		/* 0x07c: SDA hold time length register */
	volatile uint32_t IC_TX_ABRT_SOURCE;/* 0x080: I2C Transmit Abort Status Register */
	volatile uint32_t IC_SLV_DATA_NACK_ONLY;/* 0x084: Generate SLV_DATA_NACK Register */
	volatile uint32_t IC_DMA_CR;		/* 0x088: DMA Control Register */
	volatile uint32_t IC_DMA_TDLR;		/* 0x08c: DMA Transmit Data Level */
	volatile uint32_t IC_DMA_RDLR;		/* 0x090: DMA Receive Data Level */
	volatile uint32_t IC_SDA_SETUP;		/* 0x094: I2C SDA Setup Register */
	volatile uint32_t IC_ACK_GENERAL_CALL;	/* 0x098: I2C ACK General Call Register */
	volatile uint32_t IC_ENABLE_STATUS;	/* 0x09c: I2C Enable Status Register */
	volatile uint32_t IC_FS_SPKLEN;		/* 0x0a0: ISS and FS spike suppression limit */
	volatile uint32_t IC_HS_SPKLEN;		/* 0x0a4: HS spike suppression limit */
} I2C_TypeDef;

/* Peripheral Base Definitions */
#define I2C0_BASE    (0x04000000ull)
#define I2C1_BASE    (0x04010000ull)
#define I2C2_BASE    (0x04020000ull)
#define I2C3_BASE    (0x04030000ull)
#define I2C4_BASE    (0x04040000ull)

/* Instance Pointers */
#define I2C0    ((I2C_TypeDef *)I2C0_BASE)
#define I2C1    ((I2C_TypeDef *)I2C1_BASE)
#define I2C2    ((I2C_TypeDef *)I2C2_BASE)
#define I2C3    ((I2C_TypeDef *)I2C3_BASE)
#define I2C4    ((I2C_TypeDef *)I2C4_BASE)

/* timing values */
#define IC_SS_SCL_HCNT_25M	115
#define IC_SS_SCL_LCNT_25M	135
#define IC_FS_SCL_HCNT_25M	21
#define IC_FS_SCL_LCNT_25M	42
#define IC_SDA_HOLD_25M 1
#define IC_SDA_SETUP_25M 6
#define IC_FS_SPKLEN_25M 2
#define IC_SS_SCL_HCNT_100M	460
#define IC_SS_SCL_LCNT_100M	540
#define IC_FS_SCL_HCNT_100M	90
#define IC_FS_SCL_LCNT_100M	160
#define IC_SDA_HOLD_100M 1
#define IC_SDA_SETUP_100M 25
#define IC_FS_SPKLEN_100M 5

/* Register fields */
#define IC_CON_MASTER_MODE 1
#define IC_CON_SPEED_100K (1<<1)
#define IC_CON_SPEED_400K (2<<1)
#define IC_CON_10BIT_SLAVE (1<<3)
#define IC_CON_10BIT_MASTER (1<<4)
#define IC_CON_RESTART_EN (1<<5)
#define IC_CON_SLAVE_DISABLE (1<<6)
#define IC_TAR_IC_TAR_MASK (0x3FF)
#define IC_TAR_GC_OR_START (1<<10)
#define IC_TAR_SPECIAL (1<<11)
#define IC_SAR_IC_SAR_MASK (0x3FF)
#define IC_DATA_CMD_READ (1<<8)
#define IC_DATA_CMD_STOP (1<<9)
#define IC_DATA_CMD_RESTART (1<<10)
#define IC_STATUS_ST_ACTIVITY 1
#define IC_STATUS_ST_TFNF (1<<1)
#define IC_STATUS_ST_TFE (1<<2)
#define IC_STATUS_ST_RFNE (1<<3)
#define IC_STATUS_ST_RFF (1<<4)
#define IC_STATUS_ST_MST_ACTIVITY (1<<5)
#define IC_STATUS_ST_SLV_ACTIVITY (1<<6)

/* Functions */
uint32_t i2c_init(I2C_TypeDef *i2c);
void i2c_tx(I2C_TypeDef *i2c, uint8_t addr, uint8_t *data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* I2C_H */