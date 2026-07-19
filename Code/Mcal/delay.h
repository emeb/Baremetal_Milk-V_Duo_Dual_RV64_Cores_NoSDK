/******************************************************************************************
  Filename    : delay.h

  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : emeb
 
  Owner       : emeb
  
  Date        : 19.07.2026
  
  Description : busywait delay header file
  
******************************************************************************************/
#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void delayus(uint32_t us);
void delayms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* DELAY_H */
