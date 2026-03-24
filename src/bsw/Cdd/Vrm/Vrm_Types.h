/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Vrm                                                                                             
*  Content:  Voltage Range Management for TTypes define
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */

#ifndef VRM_TYPES_H
#define VRM_TYPES_H

#include "Std_Types.h"

/* ============================================================
   Type Definitions - Voltage Status
   ============================================================ */

typedef enum {
    VRM_STATUS_NORMAL   = 0,               /* Default value */
    VRM_STATUS_LOW      = 1,
    VRM_STATUS_HIGH     = 2,
    VRM_STATUS_OVER     = 3,
    VRM_STATUS_UNDER    = 4,
    VRM_STATUS_NOR2LOW  = 5,
    VRM_STATUS_LOW2NOR  = 6,
    VRM_STATUS_UND2NOR  = 7,
    VRM_STATUS_OVR2NOR  = 8,
    VRM_STATUS_HIGH2NOR = 9,
    VRM_STATUS_NOR2HIGH = 10
} Vrm_VoltageStatus_e;


/* ============================================================
   Type Definitions - Voltage Compensation
   ============================================================ */

#define VRM_COMPENSATE_NONE                     (0u)
#define VRM_COMPENSATE_TYPE_PUP1                (1u)
#define VRM_COMPENSATE_TYPE_PUP2                (2u)
#define VRM_COMPENSATE_TYPE_PUP3                (3u)
#define VRM_COMPENSATE_PRECISION                1024u

/* ============================================================
   Type Definitions - State Machine Types
   ============================================================ */


/* ============================================================
   Type Definitions - Main Status Structure
   ============================================================ */



typedef struct
{
    uint32 kParameter;
    uint16 AdcIfChannel;
    uint16 offset;
    uint8 DebounceCnt;
} Vrm_VoltageChannel_t;



#endif /* VRM_TYPES_H */
