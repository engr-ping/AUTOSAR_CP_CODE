#include "PwmIf_Cfg.h"

const PwmIf_SetDutyCycleCfgType gPwmIf_atSetDutyCycleCfg[PWMIF_PWMO_CHANNEL_MAX] =
{
    {PwmIf_SetDutyCycleFunc_Ch0, PwmConf_PwmChannel_0},
    {PwmIf_SetDutyCycleFunc_Ch0, PwmConf_PwmChannel_1},
    {PwmIf_SetDutyCycleFunc_Ch0, PwmConf_PwmChannel_2},

};

const PwmIf_GetDutyPeriodValueCfgType gPwmIf_atGetDutyPeriodValueCfg[PWMIF_PWMI_CHANNEL_MAX] =
{
    {PwmIf_GetDutyPeriodValueFunc_Ch0, PwmConf_PwmChannel_0},
    {PwmIf_GetDutyPeriodValueFunc_Ch0, PwmConf_PwmChannel_1},
    {PwmIf_GetDutyPeriodValueFunc_Ch0, PwmConf_PwmChannel_2},

};