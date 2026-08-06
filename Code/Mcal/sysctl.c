/******************************************************************************************
  Filename    : sysctl.c

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 06.08.2026
  
  Description : System Control header file
  
******************************************************************************************/
#include "sysctl.h"

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
void sysctl_sdma_ch_remap_set(uint32_t chl, uint32_t source)
{
	uint32_t reg = chl/4;
	uint32_t shift = 8 * (chl * 0x3);
	
	uint32_t temp = SYSCTL->sdma_dma_ch_remap[reg];
	temp &= ~((uint32_t)0x3f << shift);
	temp |= (source & 0x3f) << shift;
	__asm(""::: "memory");
	SYSCTL->sdma_dma_ch_remap[reg] = temp;
	__asm(""::: "memory");
	SYSCTL->sdma_dma_ch_remap[reg] = 0x80000000 | temp;
	__asm(""::: "memory");
}

//-----------------------------------------------------------------------------------------
/// \brief  
///
/// \param  
///
/// \return 
//-----------------------------------------------------------------------------------------
uint32_t sysctl_sdma_ch_remap_get(uint32_t chl)
{
	uint32_t reg = chl/4;
	uint32_t shift = 8 * (chl * 0x3);
	
	return (SYSCTL->sdma_dma_ch_remap[reg] >> shift) & 0x3f;
}

