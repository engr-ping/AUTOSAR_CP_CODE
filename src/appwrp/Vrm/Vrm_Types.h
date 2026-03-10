/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: VRM_Types
*  Content:  Voltage/Power Resource Management module type definitions
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2025.12.30    clipping            v0001        Frist edit                                                        
*  2026.01.19    refactor            v0002        Rename to AUTOSAR CP naming convention
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */

#ifndef VRM_TYPES_H
#define VRM_TYPES_H

#include "Std_Types.h"

/* ============================================================
   Type Definitions - Voltage Status
   ============================================================ */

typedef enum
{
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
} Vrm_VoltageStatus_t;

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

typedef enum
{
    VRM_STATE_TYPE_NO_MONITOR = 0,
    VRM_STATE_TYPE_A = 1,
    VRM_STATE_TYPE_B = 2,
    VRM_STATE_TYPE_C = 3,
    VRM_STATE_TYPE_D = 4
} Vrm_StateTypeDefinition_e;

/* ============================================================
   Type Definitions - Main Status Structure
   ============================================================ */

typedef struct
{
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
    Vrm_VoltageStatus_t voltageStatusTypeA[VRM_STATEFLOW_TYPE_A_NUM];
#endif
#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
    Vrm_VoltageStatus_t voltageStatusTypeB[VRM_STATEFLOW_TYPE_B_NUM];
#endif
#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
    Vrm_VoltageStatus_t voltageStatusTypeC[VRM_STATEFLOW_TYPE_C_NUM];
#endif
#if (VRM_DTC_TYPE_D_NUM != 0)
    Vrm_VoltageStatus_t voltageStatusTypeD[VRM_DTC_TYPE_D_NUM];
#endif
} Vrm_VoltageStatusData_t;

#endif /* VRM_TYPES_H */
