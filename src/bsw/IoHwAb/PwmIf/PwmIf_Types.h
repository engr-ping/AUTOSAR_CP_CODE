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

#ifndef _PWMIF_TYPES_H_
#define _PWMIF_TYPES_H_
#include "Std_Types.h"

typedef Std_ReturnType (*PwmIf_SetDutyCycleFuncType)(uint16,uint16);
typedef void (*PwmIf_GetDutyPeriodValueFuncType)(uint16,uint16*,uint16*);

typedef struct
{
    PwmIf_SetDutyCycleFuncType SetDutyCycleFunc;
    uint16 PwmChnId;
}PwmIf_SetDutyCycleCfgType;


typedef struct
{
    PwmIf_GetDutyPeriodValueFuncType GetDutyPeriodValueFunc;
    uint16 PwmChnId;
}PwmIf_GetDutyPeriodValueCfgType;

#endif /* _PWMIF_TYPES_H_ */