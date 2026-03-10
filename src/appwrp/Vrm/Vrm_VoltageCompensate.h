/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Pfm                                                                                             
*  Content:  Power device fault management module source file.
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2025.12.30    clipping            v0001        Frist edit                                                        
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
#define Vrm_GetCompensatedVoltagePup1(Voltage)   (Vrm_CompensateVoltage(Voltage, Vrm_KVPup1CompensationFactor))
#define Vrm_GetCompensatedVoltagePup2(Voltage)   (Vrm_CompensateVoltage(Voltage, Vrm_KVPup2CompensationFactor))
#define Vrm_GetCompensatedVoltagePup3(Voltage)   (Vrm_CompensateVoltage(Voltage, Vrm_KVPup3CompensationFactor))

#define VRM_COMPENSATE_PRECISION                 1024u  //have nothing to do with ADC bit

/* Exported Variables Definitions                                       */
/* ============================================================         */
extern uint16 Vrm_KVPup1CompensationFactor;             /* P1=0, P2=12288, P3=1, P4=0 */
extern uint16 Vrm_KVPup2CompensationFactor;             /* P1=0, P2=12288, P3=1, P4=0 */
extern uint16 Vrm_KVPup3CompensationFactor;             /* P1=0, P2=12288, P3=1, P4=0 */
 

/*****************    Local Functions Declaration    ******************/
extern void Vrm_CompensateFactorUpdatePup1(void);
extern uint16 Vrm_GetPup1CompensationFactor(uint16 Voltage);

extern void Vrm_CompensateFactorUpdatePup2(void);
extern uint16 Vrm_GetPup2CompensationFactor(uint16 Voltage);

extern void Vrm_CompensateFactorUpdatePup3(void);
extern uint16 Vrm_GetPup3CompensationFactor(uint16 Voltage);

extern uint16 Vrm_CompensateVoltage(uint16 AdValue, uint16 Factor);
extern uint16 Vrm_GetVoltageCompensation(uint16 AdValue, uint8 CompensateType);


#endif
