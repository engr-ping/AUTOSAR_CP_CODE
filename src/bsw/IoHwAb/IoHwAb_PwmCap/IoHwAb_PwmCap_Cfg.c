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
#include "IoHwAb_PwmCap_Cfg.h"


const IoHwAb_PwmCap_ChannelConfig_t IoHwAb_Pc_ChannelConfig[IOHWAB_PC_CHN_MAX] =
{
    {0u, (boolean)TRUE},
    {1u, (boolean)TRUE},
    {2u, (boolean)TRUE},
    {3u, (boolean)TRUE}
};



void IoHwAb_PwmCap_MainFunction_C0(void)
{
    /* No periodic task is required for PWM capture module, as the capture value is updated in interrupt context. */
    IoHwAb_PwmCap_CaptureValue_t pwmCapValue;
    
    IoHwAb_PwmCap_GetDutyPeriodValue(0u, &pwmCapValue.period, &pwmCapValue.duty);
    Rte_Write_xxx(&pwmCapValue);
}