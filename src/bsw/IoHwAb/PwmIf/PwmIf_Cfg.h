/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: PwmIf                                                                                             
*  Content:   PwmIf module                                                                                             
*  Category: PwmIf
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */
#ifndef _PWMIF_CFG_H_
#define _PWMIF_CFG_H_

#include "PwmIf_Types.h"

#define PWMIF_PWMO_CHANNEL_MAX 3u
#define PWMIF_PWMI_CHANNEL_MAX 3u

extern const PwmIf_SetDutyCycleCfgType gPwmIf_atSetDutyCycleCfg[PWMIF_PWMO_CHANNEL_MAX];
extern const PwmIf_GetDutyPeriodValueCfgType gPwmIf_atGetDutyPeriodValueCfg[PWMIF_PWMI_CHANNEL_MAX];

#endif /* _PWMIF_CFG_H_ */