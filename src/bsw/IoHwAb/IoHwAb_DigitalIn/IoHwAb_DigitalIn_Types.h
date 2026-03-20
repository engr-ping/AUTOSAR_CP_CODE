/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: IoHwAb_DigitalIn                                                                                             
*  Content:   DigitalIn module of IoHwAb
*  Category: IoHwAb DigitalIn
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */
#ifndef _IOHWAB_DIGITALIN_TYPES_H_
#define _IOHWAB_DIGITALIN_TYPES_H_

#include "Std_Types.h"

typedef struct
{
    uint8 channelId;
    uint8 invert;
    uint8 debounceTime;
    uint8* debounceBuf;
} IoHwAb_DigitalIn_ChannelConfig_t;

typedef struct 
{
    uint16 diChannelId;
    uint8* wkSaveValue;
} IoHwAb_DigitalIn_WakeUpConfig_t;

typedef struct
{
    uint8 channelId;
    uint8 invert;
    uint8 debounceTime;
    uint8* debounceBuf;
} IoHwAb_DigitalIn_ChannelType;

#endif /* _IOHWAB_DIGITALIN_TYPES_H_ */
