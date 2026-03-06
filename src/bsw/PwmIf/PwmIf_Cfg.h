#ifndef _PWMIF_CFG_H_
#define _PWMIF_CFG_H_

#include "PwmIf_Types.h"

#define PWMIF_PWMO_CHANNEL_MAX 3u
#define PWMIF_PWMI_CHANNEL_MAX 3u

extern const PwmIf_SetDutyCycleCfgType gPwmIf_atSetDutyCycleCfg[PWMIF_PWMO_CHANNEL_MAX];
extern const PwmIf_GetDutyPeriodValueCfgType gPwmIf_atGetDutyPeriodValueCfg[PWMIF_PWMI_CHANNEL_MAX];

#endif /* _PWMIF_CFG_H_ */