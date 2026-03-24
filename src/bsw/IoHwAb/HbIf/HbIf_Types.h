/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: PwmIf                                                                                             
*  Content:   PwmIf module                                                                                             
*  Category: PwmIf
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */

#ifndef _HBIF_TYPES_H_
#define _HBIF_TYPES_H_
#include "Std_Types.h"


#define HBIF_DIR_HIGH  2u   
#define HBIF_DIR_LOW   1u   
#define HBIF_DIR_STOP  0u   



/* 半桥类型枚举 */
typedef enum {
    HBIF_TYPE_HALF_BRIDGE = 0,     
    HBIF_TYPE_H_BRIDGE_DIR = 1,    
    HBIF_TYPE_H_BRIDGE_DUAL = 2     
} HbIf_BridgeType;


typedef Std_ReturnType (*SetFuncType)(uint16,uint16);

typedef struct {       
    SetFuncType HbFunction;  
    uint16 channelId;

} HbIf_ChannelConfigType;



#endif /* _HBIF_TYPES_H_ */