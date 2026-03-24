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
#include "HbIf_Cfg.h"


extern void Pwm_SetDutyCycle(uint16 ChannelId, uint16 DutyCycle);
extern void Pwm_GetDutyPeriodValue(uint16 ChannelId, uint16* Duty, uint16* Period);

const PwmIf_SetDutyCycleCfgType gPwmIf_atSetDutyCycleCfg[PWMIF_PWMO_CHANNEL_MAX] =
{
    {Pwm_SetDutyCycle, 0},
    {Pwm_SetDutyCycle, 1},
    {Pwm_SetDutyCycle, 2},

};

const PwmIf_GetDutyPeriodValueCfgType gPwmIf_atGetDutyPeriodValueCfg[PWMIF_PWMI_CHANNEL_MAX] =
{
    {Pwm_GetDutyPeriodValue, 0},
    {Pwm_GetDutyPeriodValue, 1},
    {Pwm_GetDutyPeriodValue, 2},

};