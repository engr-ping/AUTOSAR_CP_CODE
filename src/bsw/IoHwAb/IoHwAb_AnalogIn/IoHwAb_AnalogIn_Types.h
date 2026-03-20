/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: IoHwAb_AnalogIn                                                                                             
*  Content:   AnalogIn module of IoHwAb
*  Category: IoHwAb AnalogIn
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */
#ifndef _IOHWAB_ANALOGIN_TYPES_H_
#define _IOHWAB_ANALOGIN_TYPES_H_

#include "Std_Types.h"

typedef uint8 (*IoHwAb_AnalogIn_GetAdShiftFunc_t)(uint16);

typedef struct
{
    uint8 vrmCompenstate;
    uint8 debounceCnt;
    uint16* debounceBuff;
} IoHwAb_AnalogIn_ChannelConfig_t;

typedef struct 
{
    uint16 aiChannelId;
    IoHwAb_AnalogIn_GetAdShiftFunc_t* getAdShiftFunc;
} IoHwAb_AnalogIn_WakeUpConfig_t;

#define NULL (void*)0

#endif /* _IOHWAB_ANALOGIN_TYPES_H_ */