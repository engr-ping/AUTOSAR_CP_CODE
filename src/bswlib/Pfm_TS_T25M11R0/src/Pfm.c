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
/* ===================                                                  */
#include "Pfm.h"
#include "Pfm_Cfg.h"
#include "dem.h"

/* Module: Pfm - Power/Fault Management
   Abbreviations used:
   PID: Physical ID - identifies the physical fault detection device
   DDT: Defect Detect Type - type of defect (VCC, GND, OL)
   DFC: Defect Filter Count - counter for fault filtering
   DDS: Defect Detect State - current state of defect detection
   DEM: Diagnostic Event Manager
*/

/* Macros Local To This Module                                          */
/* ===========================                                          */
#define PFM_BIT_MASK_ALL            (uint8)0xFFu

#define PFM_SETBIT(basis, bitpos)   ((basis) |= ((uint8)1u << (bitpos)))
#define PFM_CLRBIT(basis, bitpos)   ((basis) &= (uint8)PFM_BIT_MASK_ALL - ((uint8)1u << (bitpos)))
#define PFM_GETBIT(basis, bitpos)   (((basis) & ((uint8)1u << (bitpos))) != 0u)


/* Local Module RAM-Definitions (attribute static)                      */
/* Definition of variables only local to this module. That is, not to   */
/* be exported to other modules.                                        */
/* ===========================================                          */
static boolean Pfm_FaultUpdateEnable[PFM_PID_SIZE];
static boolean Pfm_FaultUpdateEnableGlobal;
static uint8 Pfm_DefectFilterCount[PFM_PID_SIZE][PFM_DDT_SIZE][PFM_DFC_SIZE];
static uint8 Pfm_FaultState[PFM_PID_SIZE];
static PFM_DefectDetectState_e Pfm_DefectDetectState[PFM_PID_SIZE][PFM_DDT_SIZE];

/* Exported Variables Definitions */
/* ============================================================         */
boolean Pfm_InterceptEnable[PFM_PID_SIZE];
/*****************    Local Functions Declaration    ******************/

static void Pfm_ReportError2DEM(const uint16 dtcId);
static void Pfm_ClearError2DEM(const uint16 dtcId);
/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/
void Pfm_Init(void)
{
    uint8 i;

    for( i = 1u; i < (uint8)PFM_PID_SIZE; i++ )
    {
        Pfm_InterceptEnable[i]   = FALSE;
        Pfm_FaultUpdateEnable[i] = TRUE;
    }

    Pfm_FaultUpdateEnableGlobal = TRUE;
}

/****************************************************************
 process: Pfm_10ms
 purpose: 10ms periodic fault detection and filtering handler
 ****************************************************************/
void Pfm_10ms(void)
{
    uint8 pid;  /* Physical ID - local variable */
    uint8 ddt;  /* Defect Detect Type - local variable */
    uint8* filterCountPtr;

    if( Pfm_FaultUpdateEnableGlobal != (boolean)FALSE )
    {
        for( pid = 1u; pid < (uint8)PFM_PID_SIZE; pid++ )
        {
            if( Pfm_FaultUpdateEnable[pid] != (boolean)FALSE )
            {
                for( ddt = 0u; ddt < (uint8)PFM_DDT_SIZE; ddt++ )
                {
                    switch(Pfm_DefectDetectState[pid][ddt])
                    {
                        case PFM_DDS_POS:
                        {
                            filterCountPtr = &Pfm_DefectFilterCount[pid][ddt][PFM_DFC_SET];
                            if( (*filterCountPtr) < Pfm_DefectFilterTime[pid][ddt][PFM_DFC_SET] )
                            {
                                (*filterCountPtr) = (*filterCountPtr) + 1u;
                            }
                            else
                            {
                                Pfm_DefectFilterCount[pid][ddt][PFM_DFC_SET] = 0u;
                                Pfm_DefectFilterCount[pid][ddt][PFM_DFC_CLR] = 0u;
                                PFM_SETBIT(Pfm_FaultState[pid], ddt);
                                Pfm_ReportError2DEM(Pfm_DefectDtcId[pid][ddt]);
                            }
                        }
                        break;

                        case PFM_DDS_NEG:
                        {
                            filterCountPtr = &Pfm_DefectFilterCount[pid][ddt][PFM_DFC_CLR];
                            if( (*filterCountPtr) < Pfm_DefectFilterTime[pid][ddt][PFM_DFC_CLR] )
                            {
                                (*filterCountPtr) = (*filterCountPtr) + 1u;
                            }
                            else
                            {
                                Pfm_DefectFilterCount[pid][ddt][PFM_DFC_SET] = 0u;
                                Pfm_DefectFilterCount[pid][ddt][PFM_DFC_CLR] = 0u;
                                PFM_CLRBIT(Pfm_FaultState[pid], ddt);
                                Pfm_ClearError2DEM(Pfm_DefectDtcId[pid][ddt]);
                            }
                        }
                        break;

                        case PFM_DDS_SET:
                        {
                            Pfm_DefectFilterCount[pid][ddt][PFM_DFC_SET] = 0u;
                            Pfm_DefectFilterCount[pid][ddt][PFM_DFC_CLR] = 0u;
                            (void)PFM_SETBIT(Pfm_FaultState[pid], ddt);
                            Pfm_ReportError2DEM(Pfm_DefectDtcId[pid][ddt]);
                        }
                        break;

                        case PFM_DDS_CLR:
                        {
                            Pfm_DefectFilterCount[pid][ddt][PFM_DFC_SET] = 0u;
                            Pfm_DefectFilterCount[pid][ddt][PFM_DFC_CLR] = 0u;
                            PFM_CLRBIT(Pfm_FaultState[pid], ddt);
                            Pfm_ClearError2DEM(Pfm_DefectDtcId[pid][ddt]);
                        }
                        break;

                        default:
                        {
                            /* nothing to do */
                        }
                        break;
                    }
                 }
                
                if ((Pfm_FaultState[pid] & Pfm_InterceptEnableMask[pid]) != 0u)
                {
                    Pfm_InterceptEnable[pid] = TRUE;
                }
                else
                {
                    /* nothing to do */
                }
            }
            else
            {
                /* nothing to do */
            }
        }
    }
    else
    {
        /* nothing to do */
    }
}
/****************************************************************
 process: Pfm_EnableDiagnostic
 purpose: Enable/Disable diagnostic for a specific fault device
 ****************************************************************/
void Pfm_EnableDiagnostic(uint8 Id, boolean Enable)
{
    if(Id < (uint8)PFM_PID_SIZE)
    {
        Pfm_FaultUpdateEnable[Id] = Enable;
    }
}

/****************************************************************
 process: Pfm_ClearFault
 purpose: Clear fault state for a specific device
 ****************************************************************/
void Pfm_ClearFault(uint8 Id)
{
    uint8 ddt;  /* Defect Detect Type - local variable */
    for( ddt = 0u; ddt < (uint8)PFM_DDT_SIZE; ddt++ )
    {
        Pfm_DefectFilterCount[Id][ddt][PFM_DFC_SET] = 0u;
        Pfm_DefectFilterCount[Id][ddt][PFM_DFC_CLR] = 0u;
    }
    Pfm_InterceptEnable[Id] = FALSE;
    Pfm_FaultState[Id] = 0u;
}

/****************************************************************
 process: Pfm_ClearFaultAll
 purpose: Clear fault state for all devices
 ****************************************************************/
void Pfm_ClearFaultAll(void)
{
    uint8 pid;  /* Physical ID */
    (void)memset((void *)Pfm_DefectFilterCount, 0, (uint16)PFM_PID_SIZE*(uint16)PFM_DDT_SIZE*(uint16)PFM_DFC_SIZE);   /* PRQA S 0314*/
    
    for (pid = 0; pid < (uint8)PFM_PID_SIZE; pid++)
    {
        Pfm_InterceptEnable[pid] = FALSE;
        Pfm_FaultState[pid] = 0u;
        Pfm_DefectDetectState[pid][PFM_DDT_VCC] = PFM_DDS_CLR;
        Pfm_DefectDetectState[pid][PFM_DDT_GND] = PFM_DDS_CLR;
        Pfm_DefectDetectState[pid][PFM_DDT_OL]  = PFM_DDS_CLR;
    }
}

/****************************************************************
 process: Pfm_DefectReport
 purpose: Report defect state change from diagnostic driver
 ****************************************************************/
void Pfm_DefectReport( PFM_PhysicalId_e Pid, 
                       PFM_DefectDetectState_e OpenLoad, 
                       PFM_DefectDetectState_e Short2Vcc, 
                       PFM_DefectDetectState_e Short2Gnd )
{
    if( Pid < PFM_PID_SIZE )
    {
        Pfm_DefectDetectState[Pid][PFM_DDT_VCC] = Short2Vcc;
        Pfm_DefectDetectState[Pid][PFM_DDT_GND] = Short2Gnd;
        Pfm_DefectDetectState[Pid][PFM_DDT_OL]  = OpenLoad;
    }
}

/****************************************************************
 process: Pfm_GetFaultState
 purpose: Acquire the channel fault state 
 ****************************************************************/
boolean Pfm_GetFaultState( PFM_PhysicalId_e Pid, uint8 Ddt)
{
    boolean retval;
    if((Pid < PFM_PID_SIZE) && (Ddt < (uint8)PFM_DDT_SIZE))
    {
        if(PFM_GETBIT(Pfm_FaultState[Pid], Ddt))
        {
            retval = TRUE;
        }
        else
        {
            retval = FALSE;
        }
    }
    else
    {
        retval = FALSE;
    }
    return retval;
}

static void Pfm_ReportError2DEM(const uint16 dtcId)
{
#if (PFM_DEM_ERROR_ENABLE_FLG == TRUE)
    if(dtcId >= (uint16)DTC_MAX)
    {
        /* nothing to do */
    }
    else
    {
        (void)Dem_SetEventStatus(dtcId, DEM_EVENT_STATUS_FAILED); 
    }
#endif
}

static void Pfm_ClearError2DEM(const uint16 dtcId)
{
#if (PFM_DEM_ERROR_ENABLE_FLG == TRUE)
    if(dtcId >= (uint16)DTC_MAX)
    {
        /* nothing to do */
    }
    else
    {
        (void)Dem_SetEventStatus(dtcId, DEM_EVENT_STATUS_PASSED); 
    }
#endif
}
