#ifndef _IOHWAB_PWMOUT_API_H_
#define _IOHWAB_PWMOUT_API_H_
#include "IoHwAb_PwmOut_Types.h"
/***************extern module shared******************** */
extern void Pfm_EnableDiagnostic(uint8 Id, boolean Enable);
extern Std_ReturnType PwmIf_SetDutyCycle(uint16 ChannelId, uint16 DutyCycle);

extern void *memset(void *s, int c, uint32 n);



/***************interal module shared******************** */

#endif /*_IOHWAB_PWMOUT_API_H_*/