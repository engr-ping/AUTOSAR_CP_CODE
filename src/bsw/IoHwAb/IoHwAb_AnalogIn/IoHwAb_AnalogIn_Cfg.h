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
#ifndef _IOHWAB_ANALOGIN_CFG_H_
#define _IOHWAB_ANALOGIN_CFG_H_

#include "IoHwAb_AnalogIn_Types.h"
#include "AdcIf.h"
/* #include "Vrm.h" */

#define IOHWAB_AI_DEBOUNCE_AN_TIME_MAX    (8u)

#define IOHWAB_AI_CHN_0 0
#define IOHWAB_AI_CHN_1 1
#define IOHWAB_AI_CHN_2 2
#define IOHWAB_AI_CHN_3 3
#define IOHWAB_AI_CHN_4 4
#define IOHWAB_AI_CHN_5 5
#define IOHWAB_AI_CHN_6 6
#define IOHWAB_AI_CHN_7 7
#define IOHWAB_AI_CHN_8 8
#define IOHWAB_AI_CHN_9 9

#define IOHWAB_AI_CHN_MAX 10u
#define IOHWAB_AI_WD_MAX 5u

/* VRM compensation type definitions */
#define VRM_COMPENSATE_TYPE_NONE    0u
#define VRM_COMPENSATE_TYPE_PUP1    1u
#define VRM_COMPENSATE_TYPE_PUP2    2u

extern const IoHwAb_AnalogIn_WakeUpConfig_t IoHwAb_AnalogIn_WakeUpSignal[IOHWAB_AI_WD_MAX];
extern const IoHwAb_AnalogIn_ChannelConfig_t IoHwAb_AnalogIn_ChannelCfg[IOHWAB_AI_CHN_MAX];


extern uint16 IoHwAb_AnalogIn_SignalVal[IOHWAB_AI_CHN_MAX];
extern uint16 IoHwAb_AnalogIn_SignalWakeUpSaved[IOHWAB_AI_WD_MAX];

#endif /* _IOHWAB_ANALOGIN_CFG_H_ */
