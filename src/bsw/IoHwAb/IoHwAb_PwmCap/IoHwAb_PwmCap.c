/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: IoHwAb_PwmCap                                                                                             
*  Content:   PwmCap module of IoHwAb
*  Category: IoHwAb PwmCap
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */
#include "IoHwAb_PwmCap.h"
#include "IoHwAb_PwmCap_Cfg.h"

/* Exported Variables Definitions */
IoHwAb_PwmCap_CaptureValue_t IoHwAb_PwmCap_pcDiagInt[IOHWAB_PC_CHN_MAX];
boolean IoHwAb_PwmCap_pcDiagIntEn[IOHWAB_PC_CHN_MAX];

/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/

/****************************************************************
 process: IoHwAb_PwmCap_GetDutyPeriodValue
 purpose: Read PWM capture channel period and duty
 ****************************************************************/
Std_ReturnType IoHwAb_PwmCap_GetDutyPeriodValue(uint16 channelId, uint16* period, uint16* duty)
{
    Std_ReturnType ret = E_NOT_OK;
    IoHwAb_PwmCap_ChannelConfig_t* channelConfigPtr = &IoHwAb_Pc_ChannelConfig[channelId];
    if(channelConfigPtr->captureEnable == !(boolean)FALSE)
    {
        if(IoHwAb_PwmCap_pcDiagIntEn[channelId] != (boolean)FALSE)
        {
            *period = IoHwAb_PwmCap_pcDiagInt[channelId].period;
            *duty = IoHwAb_PwmCap_pcDiagInt[channelId].duty;
        }
        else
        {
            // Read from PWM interface
            PwmIf_GetDutyPeriodValue(channelConfigPtr->pwmIfChannelId, duty, period);
        }
        ret = E_OK;
    }
    else
    {
        ret = E_NOT_OK;
    }
    return ret;

}

/****************************************************************
 process: IoHwAb_PwmCap_SetChannelDiagInt
 purpose: Set diagnostic intervention for PWM capture channel
 ****************************************************************/
void IoHwAb_PwmCap_SetChannelDiagInt(uint16 channelId, uint16 period, uint16 duty)
{
    IoHwAb_PwmCap_pcDiagIntEn[channelId] = (boolean)TRUE;
    IoHwAb_PwmCap_pcDiagInt[channelId].period = period;
    IoHwAb_PwmCap_pcDiagInt[channelId].duty = duty;
}

/****************************************************************
 process: IoHwAb_PwmCap_ClearChannelDiagInt
 purpose: Clear diagnostic intervention for PWM capture channel
 ****************************************************************/
void IoHwAb_PwmCap_ClearChannelDiagInt(uint16 channelId)
{
    IoHwAb_PwmCap_pcDiagIntEn[channelId] = (boolean)FALSE;
}

/****************************************************************
 process: IoHwAb_PwmCap_Init
 purpose: Initialize PWM capture module
 ****************************************************************/
void IoHwAb_PwmCap_Init(void)
{
    uint8 i;
    (void)memset(IoHwAb_PwmCap_pcDiagInt, 0u, sizeof(IoHwAb_PwmCap_pcDiagInt));
    (void)memset(IoHwAb_PwmCap_pcDiagIntEn, 0u, sizeof(IoHwAb_PwmCap_pcDiagIntEn));
}