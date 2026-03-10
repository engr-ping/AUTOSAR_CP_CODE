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
#include "PwmIf.h"
#include "PwmIf_Cfg.h"


Std_ReturnType PwmIf_SetDutyCycle(uint16 ChannelId, uint16 DutyCycle)
{
    Std_ReturnType returnValue = E_OK;

    if(ChannelId < PWMIF_PWMO_CHANNEL_MAX)
    {
      PwmIf_SetDutyCycleCfgType* pSetDutyCycleCfg = &gPwmIf_atSetDutyCycleCfg[ChannelId];
        /* Call the set duty cycle function to set the duty cycle */
        returnValue = pSetDutyCycleCfg->SetDutyCycleFunc(pSetDutyCycleCfg->PwmChnId, DutyCycle);
    }
    else
    {
        /* Invalid ChannelId, return 0 or handle error as needed */
        returnValue = E_NOT_OK;
    }

    return returnValue;
}

void PwmIf_GetDutyPeriodValue(uint16 ChannelId, uint16* Duty, uint16* Period)
{
    if(ChannelId < PWMIF_PWMI_CHANNEL_MAX)
    {
      PwmIf_GetDutyPeriodValueCfgType* pGetDutyPeriodValueCfg = &gPwmIf_atGetDutyPeriodValueCfg[ChannelId];
        /* Call the get duty period value function to get the duty and period */
        pGetDutyPeriodValueCfg->GetDutyPeriodValueFunc(pGetDutyPeriodValueCfg->PwmChnId, Duty, Period);
    }
    else
    {
        /* Invalid ChannelId, set Duty and Period to 0 or handle error as needed */
        *Duty = 0u;
        *Period = 0u;
    }
}