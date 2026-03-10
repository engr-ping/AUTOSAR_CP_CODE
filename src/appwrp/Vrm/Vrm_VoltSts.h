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

#ifndef _VRM_VOLTSTS_H
#define _VRM_VOLTSTS_H

#include "Vrm_Cfg.h"

typedef enum {
    VRM_VOLTAGE_STATUS_NORMAL   = 0,               /* Default value */
    VRM_VOLTAGE_STATUS_LOW      = 1,
    VRM_VOLTAGE_STATUS_HIGH     = 2,
    VRM_VOLTAGE_STATUS_OVER     = 3,
    VRM_VOLTAGE_STATUS_UNDER    = 4,
    VRM_VOLTAGE_STATUS_NOR2LOW  = 5,
    VRM_VOLTAGE_STATUS_LOW2NOR  = 6,
    VRM_VOLTAGE_STATUS_UND2NOR  = 7,
    VRM_VOLTAGE_STATUS_OVR2NOR  = 8,
    VRM_VOLTAGE_STATUS_HIGH2NOR = 9,
    VRM_VOLTAGE_STATUS_NOR2HIGH = 10
} Vrm_VoltageStatus_e;

typedef struct {
#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
    uint32 tempCounterTypeA[VRM_STATEFLOW_TYPE_A_NUM];
#endif

#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
    uint32 tempCounterTypeB[VRM_STATEFLOW_TYPE_B_NUM];
#endif

#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
    uint32 tempCounterTypeC[VRM_STATEFLOW_TYPE_C_NUM];
#endif

#if (VRM_DTC_TYPE_D_NUM != 0)
    uint32 tempCounterTypeD[VRM_DTC_TYPE_D_NUM];
    uint16 dtcVoltage[VRM_DTC_TYPE_D_NUM];
#endif
    uint16 voltage;
#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
    Vrm_VoltageStatus_e  voltageStatusTypeA[VRM_STATEFLOW_TYPE_A_NUM];
#endif
#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
    Vrm_VoltageStatus_e  voltageStatusTypeB[VRM_STATEFLOW_TYPE_B_NUM];
#endif
#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
    Vrm_VoltageStatus_e  voltageStatusTypeC[VRM_STATEFLOW_TYPE_C_NUM];
#endif
#if (VRM_DTC_TYPE_D_NUM != 0)
    Vrm_VoltageStatus_e  voltageStatusTypeD[VRM_DTC_TYPE_D_NUM];
#endif
} Vrm_Status_t;

extern void Vrm_DtcStep(void);
extern void Vrm_StatusFlowTypeCWakeup(void);
extern void Vrm_StatusStep(void);
extern void Vrm_StatusInit(void);
#endif


