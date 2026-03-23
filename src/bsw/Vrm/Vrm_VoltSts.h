/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Vrm                                                                                             
*  Content:  Voltage Range Management Voltage status
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */

#ifndef _VRM_VOLTSTS_H
#define _VRM_VOLTSTS_H

#include "Vrm_Types.h"
#include "Vrm_Cfg.h"

typedef struct
{
#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
    uint32 TempCounterTypeA[VRM_STATEFLOW_TYPE_A_NUM];
#endif

#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
    uint32 TempCounterTypeB[VRM_STATEFLOW_TYPE_B_NUM];
#endif

#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
    uint32 TempCounterTypeC[VRM_STATEFLOW_TYPE_C_NUM];
#endif

#if (VRM_DTC_TYPE_D_NUM != 0)
    uint32 TempCounterTypeD[VRM_DTC_TYPE_D_NUM];
    uint16 DtcVoltage[VRM_DTC_TYPE_D_NUM];
#endif
    uint16 Voltage;
#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
    Vrm_VoltageStatus_e IsVoltageStatusTypeA[VRM_STATEFLOW_TYPE_A_NUM];
#endif
#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
    Vrm_VoltageStatus_e IsVoltageStatusTypeB[VRM_STATEFLOW_TYPE_B_NUM];
#endif
#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
    Vrm_VoltageStatus_e IsVoltageStatusTypeC[VRM_STATEFLOW_TYPE_C_NUM];
#endif
#if (VRM_DTC_TYPE_D_NUM != 0)
    Vrm_VoltageStatus_e IsVoltageStatusTypeD[VRM_DTC_TYPE_D_NUM];
#endif
} Vrm_Status_t;

extern void Vrm_DtcStep(void);
extern void Vrm_StatusFlowTypeCWakeup(void);
extern void Vrm_StatusStep(void);
extern void Vrm_StatusInit(void);



#endif


