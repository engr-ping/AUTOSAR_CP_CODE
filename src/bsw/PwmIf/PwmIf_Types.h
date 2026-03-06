

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