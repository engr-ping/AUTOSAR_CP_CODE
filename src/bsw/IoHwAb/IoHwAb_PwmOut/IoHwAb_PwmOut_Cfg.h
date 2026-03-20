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
#ifndef _IOHWAB_PWMOUT_CFG_H_
#define _IOHWAB_PWMOUT_CFG_H_

#include "IoHwAb_PwmOut_Types.h"
#include "PwmIf.h"

#define IOHWAB_PWMO_CHN_MAX 10U
#define IOHWAB_PO_CHN_MAX IOHWAB_PWMO_CHN_MAX

/* External variable declarations */
extern const IoHwAb_PwmOut_ChannelConfig_t IoHwAb_PwmOut_ChannelConfig[];

#endif /* _IOHWAB_PWMOUT_CFG_H_ */
