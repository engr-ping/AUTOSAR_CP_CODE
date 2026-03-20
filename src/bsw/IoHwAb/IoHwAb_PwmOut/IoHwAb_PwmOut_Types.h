/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: IoHwAb_PwmOut                                                                                             
*  Content:   PwmOut module of IoHwAb
*  Category: IoHwAb PwmOut
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */
#ifndef _IOHWAB_PWMOUT_TYPES_H_
#define _IOHWAB_PWMOUT_TYPES_H_

#include "Std_Types.h"

typedef struct
{
    uint16 pwmIfChannelId;
    uint8 pfmFid;
    uint8 vrmFid;
    uint8 dsid;
    uint8 irid;
    uint8 inrushDelayTime;
    uint16 enDiagDuty;
} IoHwAb_PwmOut_ChannelConfig_t;

typedef struct
{
    uint16 pwmIfChannelId;
    uint8 pfmFid;
    uint8 vrmFid;
    uint8 dsid;
    uint8 irid;
    uint8 inrushDelayTime;
    uint16 enDiagDuty;
} IoHwAb_PwmOut_ChannelType;

#endif /* _IOHWAB_PWMOUT_TYPES_H_ */
