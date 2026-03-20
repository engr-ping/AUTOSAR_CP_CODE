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
#ifndef _IOHWAB_PWMCAP_CFG_H_
#define _IOHWAB_PWMCAP_CFG_H_

#include "IoHwAb_PwmCap_Types.h"
#include "PwmIf.h"

#define IOHWAB_PC_DEBOUNCE_TIME_MAX     (8u)
#define IOHWAB_PC_CHN_MAX               5u

extern const IoHwAb_PwmCap_ChannelConfig_t IoHwAb_Pc_ChannelConfig[IOHWAB_PC_CHN_MAX];

#endif /* _IOHWAB_PWMCAP_CFG_H_ */
