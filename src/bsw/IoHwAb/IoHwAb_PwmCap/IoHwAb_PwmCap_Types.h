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
#ifndef _IOHWAB_PWMCAP_TYPES_H_
#define _IOHWAB_PWMCAP_TYPES_H_

#include "Std_Types.h"

typedef struct
{
    uint8 pwmIfChannelId;
    boolean captureEnable;
} IoHwAb_PwmCap_ChannelConfig_t;


typedef struct
{
    uint16 duty;
    uint16 period;
} IoHwAb_PwmCap_CaptureValue_t;

#endif /* _IOHWAB_PWMCAP_TYPES_H_ */
