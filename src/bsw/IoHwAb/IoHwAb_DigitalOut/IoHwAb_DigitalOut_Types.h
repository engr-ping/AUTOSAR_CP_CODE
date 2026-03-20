/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: IoHwAb_DigitalOut                                                                                             
*  Content:   DigitalOut module of IoHwAb
*  Category: IoHwAb DigitalOut
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */
#ifndef _IOHWAB_DIGITALOUT_TYPES_H_
#define _IOHWAB_DIGITALOUT_TYPES_H_

#include "Std_Types.h"

typedef struct
{
    uint8 dioIfChannelId;
    uint8 invert;
    uint8 pfmFid;
    uint8 vrmFid;
    uint8 dsid;
    uint8 irid;
    uint8 inrushDelay;
} IoHwAb_DigitalOut_ChannelConfig_t;

/* External variable declarations */
extern const IoHwAb_DigitalOut_ChannelConfig_t IoHwAb_Do_ChannelConfig[];
extern boolean gPFM_abInterceptEnable[];
extern boolean cPFM_abInterceptState[];
extern boolean gVRM_abInterceptEnable[];
extern boolean Vrm_abInterceptState[];

#endif /* _IOHWAB_DIGITALOUT_TYPES_H_ */
