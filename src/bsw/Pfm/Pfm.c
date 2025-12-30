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
#include "ind_startup.h"
#include "Platform_Types.h"
#include "Pfm.h"
#include "Pfm_Cfg.h"
#include "dem.h"

/* Macros Local To This Module                                          */
/* ===========================                                          */
#define b_MASK                      (uint8)0xFFu

#define SETBIT_U8(basis,bitpos)     ((basis) |= ((uint8)1 << (bitpos)))
#define CLRBIT_U8(basis,bitpos)     ((basis) &= (uint8)b_MASK - ((uint8)1 << (bitpos)))
#define GETBIT_U8(basis,bitpos)     (((basis) & ((uint8)1 << (bitpos))) != 0u)


/* Local Module RAM-Definitions (attribute static)                      */
/* Definition of variables only local to this module. That is, not to   */
/* be exported to other modules.                                        */
/* ===========================================                          */
static boolean sPfm_abFaultUpdateEnable[PFM_PID_SIZE];
static boolean sPFM_bFaultUpdateEnableGlobal;
static uint8 sPFM_au8DefectFilterCount[PFM_PID_SIZE][PFM_DDT_SIZE][PFM_DFC_SIZE];
static uint8 sPFM_au8FaultState[PFM_PID_SIZE];
static PFM_DefectDetectState_e sPFM_aeDefectDetectState[PFM_PID_SIZE][PFM_DDT_SIZE];

/* Exported Variables Definitions */
/* ============================================================         */
boolean gPFM_abInterceptEnable[PFM_PID_SIZE];
/*****************    Local Functions Declaration    ******************/

static void PFM_u8ReportError2DEM(const uint16 u16DTC_ID);
static void PFM_u8ClearError2DEM(const uint16 u16DTC_ID);
/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/
void Pfm_Init(void)
{
    uint8 i;

    for( i = 1u; i < (uint8)PFM_PID_SIZE; i++ )
    {
        gPFM_abInterceptEnable[i]   = FALSE;
        sPFM_abFaultUpdateEnable[i] = TRUE;
    }

    sPFM_bFaultUpdateEnableGlobal   = TRUE;
}

/****************************************************************
 process: PFM_v10ms
 purpose: 
 ****************************************************************/
void PFM_v10ms(void)
{
    uint8 iPid;
    uint8 jDdt;
    uint8* pu8Tmp;

    if( sPFM_bFaultUpdateEnableGlobal != (boolean)FALSE )
    {
        for( iPid = 1u; iPid < (uint8)PFM_PID_SIZE; iPid++ )
        {
            if( sPFM_abFaultUpdateEnable[iPid] != (boolean)FALSE )
            {
                for( jDdt = 0u; jDdt < (uint8)PFM_DDT_SIZE; jDdt++ )
                {
                    switch(sPFM_aeDefectDetectState[iPid][jDdt])
                    {
                        case PFM_DDS_POS:
                        {
                            pu8Tmp = &sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_SET];
                            if( (*pu8Tmp) < cPFM_au8DefectFilterTime[iPid][jDdt][PFM_DFC_SET] )
                            {
                                (*pu8Tmp) = (*pu8Tmp) + 1u;
                            }
                            else
                            {
                                sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_SET] = 0u;
                                sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_CLR] = 0u;
                                SETBIT_U8(sPFM_au8FaultState[iPid], jDdt);
                                PFM_u8ReportError2DEM(cPFM_au16DefectDtcId[iPid][jDdt]);
                            }
                        }
                        break;

                        case PFM_DDS_NEG:
                        {
                            pu8Tmp = &sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_CLR];
                            if( (*pu8Tmp) < cPFM_au8DefectFilterTime[iPid][jDdt][PFM_DFC_CLR] )
                            {
                                (*pu8Tmp) = (*pu8Tmp) + 1u;
                            }
                            else
                            {
                                sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_SET] = 0u;
                                sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_CLR] = 0u;
                                CLRBIT_U8(sPFM_au8FaultState[iPid], jDdt);
                                PFM_u8ClearError2DEM(cPFM_au16DefectDtcId[iPid][jDdt]);
                            }
                        }
                        break;

                        case PFM_DDS_SET:
                        {
                            sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_SET] = 0u;
                            sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_CLR] = 0u;
                            (void)SETBIT_U8(sPFM_au8FaultState[iPid], jDdt);
                            PFM_u8ReportError2DEM(cPFM_au16DefectDtcId[iPid][jDdt]);
                        }
                        break;

                        case PFM_DDS_CLR:
                        {
                            sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_SET] = 0u;
                            sPFM_au8DefectFilterCount[iPid][jDdt][PFM_DFC_CLR] = 0u;
                            CLRBIT_U8(sPFM_au8FaultState[iPid], jDdt);
                            PFM_u8ClearError2DEM(cPFM_au16DefectDtcId[iPid][jDdt]);
                        }
                        break;

                        default:
                        {
                            /* nothing to do */
                        }
                        break;
                    }
                 }
                
                if ((sPFM_au8FaultState[iPid] & cPFM_au8InterceptEnableMask[iPid]) != 0u)
                {
                    gPFM_abInterceptEnable[iPid] = TRUE;
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
 process: PFM_vEnableDiagnosic
 purpose: 
 ****************************************************************/
void PFM_vEnableDiagnosic(uint8 u8Id, boolean bEnable)
{
    if(u8Id < (uint8)PFM_PID_SIZE)
    {
        sPFM_abFaultUpdateEnable[u8Id] = bEnable;
    }
}

/****************************************************************
 process: PFM_vClearFault
 purpose: 
 ****************************************************************/
void PFM_vClearFault(uint8 u8Id)
{
    uint8 jDdt; 
    for( jDdt = 0u; jDdt < (uint8)PFM_DDT_SIZE; jDdt++ )
    {
        sPFM_au8DefectFilterCount[u8Id][jDdt][PFM_DFC_SET] = 0u;
        sPFM_au8DefectFilterCount[u8Id][jDdt][PFM_DFC_CLR] = 0u;
    }
    gPFM_abInterceptEnable[u8Id] = FALSE;
    sPFM_au8FaultState[u8Id] = 0u;
}

/****************************************************************
 process: PFM_vClearFaultAll
 purpose: 
 ****************************************************************/
void PFM_vClearFaultAll(void)
{
    uint8 iPid;
    (void)memset((void *)sPFM_au8DefectFilterCount, 0, (uint16)PFM_PID_SIZE*(uint16)PFM_DDT_SIZE*(uint16)PFM_DFC_SIZE);   /* PRQA S 0314*/
    
    for (iPid = 0; iPid < (uint8)PFM_PID_SIZE; iPid++)
    {
        gPFM_abInterceptEnable[iPid] = FALSE;
        sPFM_au8FaultState[iPid] = 0u;
        sPFM_aeDefectDetectState[iPid][PFM_DDT_VCC] = PFM_DDS_CLR;
        sPFM_aeDefectDetectState[iPid][PFM_DDT_GND] = PFM_DDS_CLR;
        sPFM_aeDefectDetectState[iPid][PFM_DDT_OL]  = PFM_DDS_CLR;
    }
}

/****************************************************************
 process: PFM_vDefectReport
 purpose: 
 ****************************************************************/
void PFM_vDefectReport( PFM_PhysicalId_e        ePid, 
                        PFM_DefectDetectState_e eOpenLoad, 
                        PFM_DefectDetectState_e eShort2Vcc, 
                        PFM_DefectDetectState_e eShort2Gnd )
{
    if( ePid < PFM_PID_SIZE )
    {
        sPFM_aeDefectDetectState[ePid][PFM_DDT_VCC] = eShort2Vcc;
        sPFM_aeDefectDetectState[ePid][PFM_DDT_GND] = eShort2Gnd;
        sPFM_aeDefectDetectState[ePid][PFM_DDT_OL]  = eOpenLoad;
    }
}

/****************************************************************
 process: PFM_bGetFaultState
 purpose: Acquire the channel fault state 
 ****************************************************************/
boolean PFM_bGetFaultState( PFM_PhysicalId_e ePid,  uint8 u8Ddt)
{
    boolean bRet;
    if((ePid < PFM_PID_SIZE) && (u8Ddt < (uint8)PFM_DDT_SIZE))
    {
        if(GETBIT_U8(sPFM_au8FaultState[ePid], u8Ddt))
        {
            bRet = TRUE;
        }
        else
        {
            bRet = FALSE;
        }
    }
    else
    {
        bRet = FALSE;
    }
    return bRet;
}

static void PFM_u8ReportError2DEM(const uint16 u16DTC_ID)
{
#if (PFM_DEM_ERROR_ENABLE_FLG == TRUE)
    if(u16DTC_ID >= (uint16)DTC_MAX)
    {
        /* nothing to do */
    }
    else
    {
        (void)Dem_SetEventStatus(u16DTC_ID, DEM_EVENT_STATUS_FAILED); 
    }
#endif
}

static void PFM_u8ClearError2DEM(const uint16 u16DTC_ID)
{
#if (PFM_DEM_ERROR_ENABLE_FLG == TRUE)
    if(u16DTC_ID >= (uint16)DTC_MAX)
    {
        /* nothing to do */
    }
    else
    {
        (void)Dem_SetEventStatus(u16DTC_ID, DEM_EVENT_STATUS_PASSED); 
    }
#endif
}
