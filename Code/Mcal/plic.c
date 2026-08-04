/******************************************************************************************
  Filename    : plic.c

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 03.08.2026
  
  Description : PLIC header file
  
******************************************************************************************/
#include "plic.h"

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t plic_get_priority(uint32_t irqnum)
{
	if((irqnum < 1) || (irqnum > 1023))
		return 0;
	
	return *(uint32_t *)(PLIC_BASE + 4 * irqnum);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void plic_set_priority(uint32_t irqnum, uint32_t priority)
{
	if((irqnum < 1) || (irqnum > 1023))
		return;
	
	*(uint32_t *)(PLIC_BASE + 4 * irqnum) = priority & 0x1f;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t plic_get_pending(uint32_t irqnum)
{
	if((irqnum < 1) || (irqnum > 1023))
		return 0;
	
	uint32_t reg = irqnum >> 5;
	uint32_t shift = irqnum & 0x1f;
	
	return (*(uint32_t *)(PLIC_BASE + PLIC_IP_OFFSET + 4 * reg) >> shift) & 1;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void plic_set_pending(uint32_t irqnum, uint32_t enable)
{
	if((irqnum < 1) || (irqnum > 1023))
		return;
	
	uint32_t reg = irqnum >> 5;
	uint32_t shift = irqnum & 0x1f;
	
	*(uint32_t *)(PLIC_BASE + PLIC_IP_OFFSET + 4 * reg) = (enable & 1) << shift;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t plic_get_enable(uint32_t irqnum, uint32_t supervisor)
{
	if((irqnum < 1) || (irqnum > 1023))
		return 0;
	
	uint32_t reg = (irqnum >> 5) + (0x20 * (supervisor & 1));
	uint32_t shift = irqnum & 0x1f;
	
	return (*(uint32_t *)(PLIC_BASE + PLIC_IE_OFFSET + 4 * reg) >> shift) & 1;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void plic_set_enable(uint32_t irqnum, uint32_t supervisor, uint32_t enable)
{
	if((irqnum < 1) || (irqnum > 1023))
		return;
	
	uint32_t reg = (irqnum >> 5) + (0x20 * (supervisor & 1));
	uint32_t shift = irqnum & 0x1f;
	
	*(uint32_t *)(PLIC_BASE + PLIC_IE_OFFSET + 4 * reg) = (enable & 1) << shift;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t plic_get_thresh(uint32_t supervisor)
{
	uint32_t reg = (supervisor & 1) ? PLIC_STH_OFFSET : PLIC_MTH_OFFSET;
	
	return *(uint32_t *)(PLIC_BASE + reg);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void plic_set_thresh(uint32_t supervisor, uint32_t thresh)
{
	uint32_t reg = (supervisor & 1) ? PLIC_STH_OFFSET : PLIC_MTH_OFFSET;
	
	*(uint32_t *)(PLIC_BASE + reg) = thresh;
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t plic_get_claim(uint32_t supervisor)
{
	uint32_t reg = (supervisor & 1) ? PLIC_STH_OFFSET : PLIC_MTH_OFFSET;
	
	return *(uint32_t *)(PLIC_BASE + reg + 0x4);
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void plic_set_claim(uint32_t supervisor, uint32_t claim)
{
	uint32_t reg = (supervisor & 1) ? PLIC_STH_OFFSET : PLIC_MTH_OFFSET;
	
	*(uint32_t *)(PLIC_BASE + reg + 0x4) = claim;
}


