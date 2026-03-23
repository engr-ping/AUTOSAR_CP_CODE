/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Vrm                                                                                             
*  Content:  Voltage Range Management for Voltage Compensate
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */
#ifndef _VRM_VOLTAGECOMPENSATE_H
#define _VRM_VOLTAGECOMPENSATE_H

#include "Vrm_Cfg.h"

#define VRM_COMPENSATE_NONE                     (0u)
#define VRM_COMPENSATE_TYPE_PUP1                (1u)
#define VRM_COMPENSATE_TYPE_PUP2                (2u)
#define VRM_COMPENSATE_TYPE_PUP3                (3u)


/* Exported Macros Definitions                                          */
/* ===========================                                          */

#define VRM_COMPENSATE_PRECISION                 1024u  //have nothing to do with ADC bit

/* Exported Variables Definitions                                       */
/* ============================================================         */

 

/*****************    Local Functions Declaration    ******************/
extern uint16 VRM_CompensateFactorUpdatePup(uint8 PupChannel);
extern uint16 VRM_GetPupCompensationFactor(uint8 PupChannel,uint16 pupFvAd);

extern uint16 Vrm_GetVoltageCompensation(uint16 AdValue, uint8 CompensateType);


#endif
