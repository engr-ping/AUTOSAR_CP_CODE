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
#include "VRM_Cfg.h"
#include "VRM_VoltSts.h"
 
static Vrm_Status_t sVRM_tStatus_DWork;
static uint8 sVRM_bTypeCReinit = FALSE;

#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
static void VRM_vStatusFlowTypeA(uint8 num);
#endif
#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
static void VRM_vStatusFlowTypeB(uint8 num);
#endif
#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
static void VRM_vStatusFlowTypeC(uint8 num);
#endif
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * IOHWAB_BOOL: Boolean
 * IOHWAB_UINT8: Integer in interval [0...255]
 * UInt16: Integer in interval [0...65535]
 * boolean: Boolean (standard type)
 * uint8: Integer in interval [0...255] (standard type)
 *
 *********************************************************************************************************************/


#define VRM_VoltSts_START_SEC_CODE
#include "VRM_VoltSts_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: GetVoltSts
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Operation> of PortPrototype <GetVoltStatus>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void GetVoltSts(uint8 statusType, uint8 *voltageStatus)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: GetVoltSts_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

void GetVoltSts(uint8 statusType, uint8* voltageStatus) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: GetVoltSts
 *********************************************************************************************************************/

    if(statusType == (uint8)VRM_STATE_TYPE_NO_MONITOR)
    {
        *voltageStatus = (uint8)VRM_STATUS_NORMAL ;
    }
#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
    else if(statusType < VRM_STATEFLOW_TYPE_A_NUM)
    { 
        *voltageStatus = (uint8)(sVRM_tStatus_DWork.IsVoltageStatusTypeA[(uint8)(statusType)]);
    }
#endif
#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
    else if(statusType < (VRM_STATEFLOW_TYPE_A_NUM + VRM_STATEFLOW_TYPE_B_NUM))
    {
        *voltageStatus = (uint8)(sVRM_tStatus_DWork.IsVoltageStatusTypeB[(uint8)statusType - VRM_STATEFLOW_TYPE_A_NUM]);
    }
#endif
#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
    else if(statusType < (VRM_STATEFLOW_TYPE_A_NUM + VRM_STATEFLOW_TYPE_B_NUM + VRM_STATEFLOW_TYPE_C_NUM))
    {
        *voltageStatus = (uint8)(sVRM_tStatus_DWork.IsVoltageStatusTypeC[(uint8)statusType - VRM_STATEFLOW_TYPE_A_NUM - VRM_STATEFLOW_TYPE_B_NUM]);
    }
#endif
    else
    {
        *voltageStatus = (uint8)VRM_STATUS_NORMAL ;
    }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}





/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/****************************************************************
 process: VRM_vStatusStep
 purpose: called by VRM_VoltSts_vMainFunction ,run status machine
 ****************************************************************/
void Vrm_StatusStep(void)
{
    uint8 i;
    uint16 tmp_u16BatAdValue;

    //fetch the non-filtered BatADValue to tmp_u16BatAdValue
    (void)Rte_Read_gVRM_u16VBatADValue_Val(&tmp_u16BatAdValue);             /* PRQA S 3426 */
    
    tmp_u16BatAdValue = Vrm_GetSystemVoltage();
    sVRM_tStatus_DWork.Voltage = VRM_CONVERT_AD2VOL_POW(tmp_u16BatAdValue);

#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
    for (i=0 ; i< VRM_STATEFLOW_TYPE_A_NUM; i++)
    {
        sVRM_tStatus_DWork.TempCounterTypeA[i]++; 
        VRM_vStatusFlowTypeA(i);
    }
#endif
    
#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
    for (i=0 ; i< VRM_STATEFLOW_TYPE_B_NUM; i++)
    {
        sVRM_tStatus_DWork.TempCounterTypeB[i]++; 
        VRM_vStatusFlowTypeB(i);
    }
#endif


#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
    /*  be given a init state already ,run state machine*/
    if((boolean)TRUE == sVRM_bTypeCReinit)
    {
        for (i=0 ; i< VRM_STATEFLOW_TYPE_C_NUM; i++)         /* PRQA S 2877 */
        {
            sVRM_tStatus_DWork.TempCounterTypeC[i]++; 
            VRM_vStatusFlowTypeC(i);
        }
    }
    else
    {
        /* Need be given a init state, then run state machine */
        sVRM_bTypeCReinit = TRUE;
        for (i=0 ; i< VRM_STATEFLOW_TYPE_C_NUM; i++)         /* PRQA S 2877 */
        {
            /* clear the time cnt */
            sVRM_tStatus_DWork.TempCounterTypeC[i] = 0;
            if (sVRM_tStatus_DWork.Voltage < cVRM_au16LowThresholdFlowTypeC[i]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[i] = VRM_STATUS_UNDER;
            }
            else if (sVRM_tStatus_DWork.Voltage > cVRM_au16HighThresholdFlowTypeC[i]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[i] = VRM_STATUS_OVER;
            }
            else 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[i] = VRM_STATUS_NORMAL;
            }
        }
    }
#endif
}

/****************************************************************
 process: VRM_vStatusInit
 purpose: init status variable
 ****************************************************************/
void Vrm_StatusInit(void)
{
    (void)memset(&sVRM_tStatus_DWork, 0, sizeof(Vrm_Status_t));                 /* PRQA S 0315 */
}


/****************************************************************
 process: VRM_vStatusFlowTypeA
 purpose: at [under]and[OVER] do vrm output intercept
 status machine as following
 
          N2LTime              <LowThreshold          >HighThreshold             N2HTime 
       <--------             <------------           ------------->            --------->
[LOW]             [NOR2LOW]                 [NORMAL]                [NOR2HIGH]            [HIGH]
 ||A                         ------------>    A  A   <-------------                        A||
 |||                         >=LowThreshold   |  |   <=HighThreshold                       |||
 |||                                          |  |                                         |||
 |||                                          |  |                                         |||
 |||<LowThreshold                             |  |                          >HighThreshold |||
 |||------------                L2NTime       |  |                            -------------|||
 ||               [LOW2NOR]  -----------------|  |----------------- [HIGH2NOR]              ||
 ||------------>                              |  |                             <------------||
 |  >=LowThreshold                            |  |                          <=HighThreshold  |
 |                                            |  |                                           |
 |L2UTime                                     |  |                                   H2OTime |
 |                                            |  |                                           |
 |  >=LowThreshold+LOW_HYST                   |  |                 <=HIGHThreshold-HIGH_HYST |
 V      -------->                U2NTIME      |  |                           <-----------    V
 [UNDER]          [UND2NOR]  -----------------|  |----------------  [OVR2NOR]             [OVER]
        <--------                                                            ------------>
    <LowThreshold+LOW_HYST                                          >HIGHThreshold-HIGH_HYST
 ****************************************************************/
#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
static void VRM_vStatusFlowTypeA(uint8 num)
{
    switch (sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]) 
    {
/********************************************************************************************/
/*********** VRM_STATUS_HIGH *************************************************************/
/********************************************************************************************/
        case VRM_STATUS_HIGH:
            if (sVRM_tStatus_DWork.TempCounterTypeA[num] >= (uint32)cVRM_au16H2OTimeFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num] = VRM_STATUS_OVER;
                (void)Rte_Call_VRM_GetInterceptFlag_Operation(((uint8)VRM_STATE_TYPE_A_1 + num), TRUE);    /* PRQA S 2986 */
            }
            else 
            {
                if (sVRM_tStatus_DWork.Voltage <= cVRM_au16HighThresholdFlowTypeA[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeA[num] = VRM_STATUS_HIGH2NOR;
                    sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_HIGH2NOR *********************************************************/
/********************************************************************************************/
        case VRM_STATUS_HIGH2NOR:
            if (sVRM_tStatus_DWork.Voltage > cVRM_au16HighThresholdFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num] = VRM_STATUS_HIGH;
                sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.TempCounterTypeA[num] >= (uint32)cVRM_au16H2NTimeFlowTypeA[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeA[num] = VRM_STATUS_NORMAL;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_LOW **************************************************************/
/********************************************************************************************/
        case VRM_STATUS_LOW:
            if (sVRM_tStatus_DWork.TempCounterTypeA[num] >= (uint32)cVRM_au16L2UTimeFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num] = VRM_STATUS_UNDER;
                (void)Rte_Call_VRM_GetInterceptFlag_Operation(((uint8)VRM_STATE_TYPE_A_1 + num), TRUE);      /* PRQA S 2986 */
            }
            else 
            {
                if (sVRM_tStatus_DWork.Voltage >= cVRM_au16LowThresholdFlowTypeA[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeA[num] = VRM_STATUS_LOW2NOR;
                    sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_LOW2NOR **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_LOW2NOR:
            if (sVRM_tStatus_DWork.Voltage < cVRM_au16LowThresholdFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_LOW;
                sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.TempCounterTypeA[num] >= (uint32)cVRM_au16L2NTimeFlowTypeA[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_NORMAL;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_NOR2HIGH *********************************************************/
/********************************************************************************************/
        case VRM_STATUS_NOR2HIGH:
            if (sVRM_tStatus_DWork.Voltage <= cVRM_au16HighThresholdFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_NORMAL;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.TempCounterTypeA[num] >= (uint32)cVRM_au16N2HTimeFlowTypeA[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_HIGH;
                    sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_NOR2LOW **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_NOR2LOW:
            if (sVRM_tStatus_DWork.Voltage >= cVRM_au16LowThresholdFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_NORMAL;
            } 
            else
            {
                if (sVRM_tStatus_DWork.TempCounterTypeA[num] >= (uint32)cVRM_au16N2LTimeFlowTypeA[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_LOW;
                    sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_NORMAL ***********************************************************/
/********************************************************************************************/
        case VRM_STATUS_NORMAL:
            if (sVRM_tStatus_DWork.Voltage < cVRM_au16LowThresholdFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_NOR2LOW;
                sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
            } 
            else if (sVRM_tStatus_DWork.Voltage > cVRM_au16HighThresholdFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_NOR2HIGH;
                sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
            }
            else 
            {
                /* nothing to do */
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_OVER *************************************************************/
/********************************************************************************************/
        case VRM_STATUS_OVER:
            if (sVRM_tStatus_DWork.Voltage <= (cVRM_au16HighThresholdFlowTypeA[num]-cVRM_au16HighHystFlowTypeA[num])) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_OVR2NOR;
                sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_OVR2NOR **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_OVR2NOR:
            if (sVRM_tStatus_DWork.TempCounterTypeA[num] >= (uint32)cVRM_au16O2NTimeFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_NORMAL;
                (void)Rte_Call_VRM_GetInterceptFlag_Operation(((uint8)VRM_STATE_TYPE_A_1 + num), FALSE);         /* PRQA S 2986 */
            }
            else if (sVRM_tStatus_DWork.Voltage > (cVRM_au16HighThresholdFlowTypeA[num] - cVRM_au16HighHystFlowTypeA[num])) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_OVER;
            } 
            else 
            {
                /* nothing to do */
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_OVR2NOR **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_UND2NOR:
            if (sVRM_tStatus_DWork.TempCounterTypeA[num] >= (uint32)cVRM_au16U2NTimeFlowTypeA[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_NORMAL;
                (void)Rte_Call_VRM_GetInterceptFlag_Operation(((uint8)VRM_STATE_TYPE_A_1 + num), FALSE);         /* PRQA S 2986 */
            }
            else if (sVRM_tStatus_DWork.Voltage < (cVRM_au16LowThresholdFlowTypeA[num] + cVRM_au16LowHystFlowTypeA[num])) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_UNDER;
            } 
            else 
            {
                /* nothing to do */
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_UNDER ************************************************************/
/********************************************************************************************/
        case VRM_STATUS_UNDER:
            if (sVRM_tStatus_DWork.Voltage >= (cVRM_au16LowThresholdFlowTypeA[num] + cVRM_au16LowHystFlowTypeA[num]))
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeA[num]  = VRM_STATUS_UND2NOR;
                sVRM_tStatus_DWork.TempCounterTypeA[num] = 0U;
            } 
        break;
/********************************************************************************************/
/*********** VRM_default ********************************************************************/
/********************************************************************************************/
   default:  break;
   }
}
#endif

/****************************************************************
 process: VRM_vStatusFlowTypeB
 purpose: different from VRM_vStatusFlowTypeA
 1: no hyst 
 status machine as following
                 <UnderThreshold                                  >OverThreshold                  
 <------------------------------------------[NORMAL]  --------------------------------------->               
 |                                            A  A                                           |
 |                                            |  |                                           |
 |                                            |  |                                           |
 |                                            |  |                                           |
 |  >=LowThreshold+LOW_HYST                   |  |                 <=HIGHThreshold-HIGH_HYST |
 V      -------->                U2NTIME      |  |       O2NTIME             <-----------    V
 [UNDER]          [UND2NOR]-------------------|  |------------------[OVR2NOR]             [OVER]
        <--------                                                            ------------>    
     <LowThreshold                                                          >OverThreshold

 ****************************************************************/
#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
static void VRM_vStatusFlowTypeB(uint8 num)
{
    switch (sVRM_tStatus_DWork.IsVoltageStatusTypeB[num]) 
    {
        case VRM_STATUS_NORMAL:
            if (sVRM_tStatus_DWork.Voltage < cVRM_au16UnderThresholdFlowTypeB[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeB[num] = VRM_STATUS_UNDER;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.Voltage > cVRM_au16OverThresholdFlowTypeB[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeB[num] = VRM_STATUS_OVER;
                }
            }
        break;
    
        case VRM_STATUS_OVR2NOR:
            if (sVRM_tStatus_DWork.TempCounterTypeB[num] >= (uint32)cVRM_au16O2NTimeFlowTypeB[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeB[num] = VRM_STATUS_NORMAL;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.Voltage > cVRM_au16OverThresholdFlowTypeB[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeB[num]= VRM_STATUS_OVER;
                }
            }
        break;
    
        case VRM_STATUS_OVER:
            if (sVRM_tStatus_DWork.Voltage <= (cVRM_au16OverThresholdFlowTypeB[num]-cVRM_au16HighHystFlowTypeB[num])) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeB[num] = VRM_STATUS_OVR2NOR;
                sVRM_tStatus_DWork.TempCounterTypeB[num] = 0U;
            }
        break;
    
        case VRM_STATUS_UND2NOR:
            if (sVRM_tStatus_DWork.TempCounterTypeB[num] >= (uint32)cVRM_au16U2NTimeFlowTypeB[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeB[num] = VRM_STATUS_NORMAL;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.Voltage < cVRM_au16UnderThresholdFlowTypeB[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeB[num] = VRM_STATUS_UNDER;
                }
            }
        break;
        case VRM_STATUS_UNDER:
            if (sVRM_tStatus_DWork.Voltage >= (cVRM_au16UnderThresholdFlowTypeB[num]+cVRM_au16LowHystFlowTypeB[num])) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeB[num]= VRM_STATUS_UND2NOR;
                sVRM_tStatus_DWork.TempCounterTypeB[num] = 0U;
            }
        break;
        default:
        break;
    }
}
#endif
/****************************************************************
 process: VRM_vStatusFlowTypeC
 purpose: different from VRM_vStatusFlowTypeA
 1: donot intercept output, only offer status
 2: init status need judge from voltage,not normal like TypeA
 status machine as following
 
          N2LTime              <LowThreshold          >HighThreshold             N2HTime 
       <--------             <------------           ------------->            --------->
[LOW]             [NOR2LOW]                 [NORMAL]                [NOR2HIGH]            [HIGH]
 ||A                         ------------>    A  A   <-------------                        A||
 |||                         >=LowThreshold   |  |   <=HighThreshold                       |||
 |||                                          |  |                                         |||
 |||                                          |  |                                         |||
 |||<LowThreshold                             |  |                          >HighThreshold |||
 |||------------                L2NTime       |  |                            -------------|||
 ||               [LOW2NOR]  -----------------|  |----------------- [HIGH2NOR]              ||
 ||------------>                              |  |                             <------------||
 |  >=LowThreshold                            |  |                          <=HighThreshold  |
 |                                            |  |                                           |
 |L2UTime                                     |  |                                   H2OTime |
 |                                            |  |                                           |
 |  >=LowThreshold+LOW_HYST                   |  |                 <=HIGHThreshold-HIGH_HYST |
 V      -------->                U2NTIME      |  |                           <-----------    V
 [UNDER]          [UND2NOR]  -----------------|  |----------------  [OVR2NOR]             [OVER]
        <--------                                                            ------------>
    <LowThreshold+LOW_HYST                                          >HIGHThreshold-HIGH_HYST
 ****************************************************************/
#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
static void VRM_vStatusFlowTypeC(uint8 num)
{
    switch (sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]) 
    {
/********************************************************************************************/
/*********** VRM_STATUS_HIGH *************************************************************/
/********************************************************************************************/
        case VRM_STATUS_HIGH:
            if (sVRM_tStatus_DWork.TempCounterTypeC[num] >= (uint32)cVRM_au16H2OTimeFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_OVER;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.Voltage <= cVRM_au16HighThresholdFlowTypeC[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_HIGH2NOR;
                    sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_HIGH2NOR *********************************************************/
/********************************************************************************************/
        case VRM_STATUS_HIGH2NOR:
            if (sVRM_tStatus_DWork.Voltage > cVRM_au16HighThresholdFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_HIGH;
                sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.TempCounterTypeC[num] >= (uint32)cVRM_au16H2NTimeFlowTypeC[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_NORMAL;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_LOW **************************************************************/
/********************************************************************************************/
        case VRM_STATUS_LOW:
            if (sVRM_tStatus_DWork.TempCounterTypeC[num] >= (uint32)cVRM_au16L2UTimeFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_UNDER;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.Voltage >= cVRM_au16LowThresholdFlowTypeC[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_LOW2NOR;
                    sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_LOW2NOR **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_LOW2NOR:
            if (sVRM_tStatus_DWork.Voltage < cVRM_au16LowThresholdFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]  = VRM_STATUS_LOW;
                sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.TempCounterTypeC[num] >= (uint32)cVRM_au16L2NTimeFlowTypeC[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]  = VRM_STATUS_NORMAL;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_NOR2HIGH *********************************************************/
/********************************************************************************************/
        case VRM_STATUS_NOR2HIGH:
            if (sVRM_tStatus_DWork.Voltage <= cVRM_au16HighThresholdFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]  = VRM_STATUS_NORMAL;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.TempCounterTypeC[num] >= (uint32)cVRM_au16N2HTimeFlowTypeC[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]  = VRM_STATUS_HIGH;
                    sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_NOR2LOW **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_NOR2LOW:
            if (sVRM_tStatus_DWork.Voltage >= cVRM_au16LowThresholdFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]  = VRM_STATUS_NORMAL;
            } 
            else
            {
                if (sVRM_tStatus_DWork.TempCounterTypeC[num] >= (uint32)cVRM_au16N2LTimeFlowTypeC[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]  = VRM_STATUS_LOW;
                    sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
                    
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_NORMAL ***********************************************************/
/********************************************************************************************/
        case VRM_STATUS_NORMAL:
            if (sVRM_tStatus_DWork.Voltage < cVRM_au16LowThresholdFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]  = VRM_STATUS_NOR2LOW;
                sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
            } 
            else if (sVRM_tStatus_DWork.Voltage > cVRM_au16HighThresholdFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]  = VRM_STATUS_NOR2HIGH;
                sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
            }
            else 
            {
                /* nothing to do */
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_OVER *************************************************************/
/********************************************************************************************/
        case VRM_STATUS_OVER:
            if (sVRM_tStatus_DWork.Voltage <= (cVRM_au16HighThresholdFlowTypeC[num]-cVRM_au16HighHystFlowTypeC[num])) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num]  = VRM_STATUS_OVR2NOR;
                sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_OVR2NOR *************************************************************/
/********************************************************************************************/
        case VRM_STATUS_OVR2NOR:
            if (sVRM_tStatus_DWork.TempCounterTypeC[num] >= (uint32)cVRM_au16O2NTimeFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_NORMAL;  
            }
            else if (sVRM_tStatus_DWork.Voltage > (cVRM_au16HighThresholdFlowTypeC[num] - cVRM_au16HighHystFlowTypeC[num])) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_OVER;
            } 
            else 
            {
                /* nothing to do */
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_OVR2NOR **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_UND2NOR:
            if (sVRM_tStatus_DWork.TempCounterTypeC[num] >= (uint32)cVRM_au16U2NTimeFlowTypeC[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_NORMAL;
            }
            else if (sVRM_tStatus_DWork.Voltage < (cVRM_au16LowThresholdFlowTypeC[num] + cVRM_au16LowHystFlowTypeC[num])) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_UNDER;
            } 
            else 
            {
                /* nothing to do */
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_UNDER ************************************************************/
/********************************************************************************************/
        case VRM_STATUS_UNDER:
            if (sVRM_tStatus_DWork.Voltage >= (cVRM_au16LowThresholdFlowTypeC[num] + cVRM_au16LowHystFlowTypeC[num])) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeC[num] = VRM_STATUS_UND2NOR;
                sVRM_tStatus_DWork.TempCounterTypeC[num] = 0U;
            } 
        break;
/********************************************************************************************/
/*********** VRM_default ********************************************************************/
/********************************************************************************************/
   default:  break;
   }
}
#endif
/****************************************************************
 process: VRM_Dtc_FlowTypeD
 purpose: different from VRM_vStatusFlowTypeA
 at [under]and[OVER] set DTC
 enter [normal] clr DTC
 1: donot intercept output, only offer status
 status machine as following
 
          N2LTime              <LowThreshold          >HighThreshold             N2HTime 
       <--------             <------------           ------------->            --------->
[LOW]             [NOR2LOW]                 [NORMAL]                [NOR2HIGH]            [HIGH]
 ||A                         ------------>    A  A   <-------------                        A||
 |||                         >=LowThreshold   |  |   <=HighThreshold                       |||
 |||                                          |  |                                         |||
 |||                                          |  |                                         |||
 |||<LowThreshold                             |  |                          >HighThreshold |||
 |||------------                L2NTime       |  |                            -------------|||
 ||               [LOW2NOR]  -----------------|  |----------------- [HIGH2NOR]              ||
 ||------------>                              |  |                             <------------||
 |  >=LowThreshold                            |  |                          <=HighThreshold  |
 |                                            |  |                                           |
 |L2UTime                                     |  |                                   H2OTime |
 |                                            |  |                                           |
 |  >=LowThreshold+LOW_HYST                   |  |                 <=HIGHThreshold-HIGH_HYST |
 V      -------->                U2NTIME      |  |                           <-----------    V
 [UNDER]          [UND2NOR]  -----------------|  |----------------  [OVR2NOR]             [OVER]
        <--------                                                            ------------>
    <LowThreshold+LOW_HYST                                          >HIGHThreshold-HIGH_HYST
 ****************************************************************/
#if 0
static void VRM_Dtc_FlowTypeD(uint8 num , uint32 u32LowDtc, uint32 u32HighDtc)
{
    switch (sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]) 
    {
/********************************************************************************************/
/*********** VRM_STATUS_HIGH *************************************************************/
/********************************************************************************************/
        case VRM_STATUS_HIGH:
            if (sVRM_tStatus_DWork.TempCounterTypeD[num] >= (uint32)cVRM_au16H2OTimeFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num] = VRM_STATUS_OVER;
                DEM_u8ReportError((uint8)u32HighDtc);
            } 
            else 
            {
                if (sVRM_tStatus_DWork.u16DtcVoltage[num] <= cVRM_au16HighThresholdFlowDtcTypeD[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeD[num] = VRM_STATUS_HIGH2NOR;
                    sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_HIGH2NOR *********************************************************/
/********************************************************************************************/
        case VRM_STATUS_HIGH2NOR:
            if (sVRM_tStatus_DWork.u16DtcVoltage[num] > cVRM_au16HighThresholdFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num] = VRM_STATUS_HIGH;
                sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.TempCounterTypeD[num] >= (uint32)cVRM_au16H2NTimeFlowDtcTypeD[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeD[num] = VRM_STATUS_NORMAL;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_LOW **************************************************************/
/********************************************************************************************/
        case VRM_STATUS_LOW:
            if (sVRM_tStatus_DWork.TempCounterTypeD[num] >= (uint32)cVRM_au16L2UTimeFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num] = VRM_STATUS_UNDER;
                DEM_u8ReportError((uint8)u32LowDtc);
                
            } 
            else 
            {
                if (sVRM_tStatus_DWork.u16DtcVoltage[num] >= cVRM_au16LowThresholdFlowDtcTypeD[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeD[num] = VRM_STATUS_LOW2NOR;
                    sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_LOW2NOR **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_LOW2NOR:
            if (sVRM_tStatus_DWork.u16DtcVoltage[num] < cVRM_au16LowThresholdFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_LOW;
                sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.TempCounterTypeD[num] >= (uint32)cVRM_au16L2NTimeFlowDtcTypeD[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_NORMAL;              
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_NOR2HIGH *********************************************************/
/********************************************************************************************/
        case VRM_STATUS_NOR2HIGH:
            if (sVRM_tStatus_DWork.u16DtcVoltage[num] <= cVRM_au16HighThresholdFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_NORMAL;
            } 
            else 
            {
                if (sVRM_tStatus_DWork.TempCounterTypeD[num] >= (uint32)cVRM_au16N2HTimeFlowDtcTypeD[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_HIGH;
                    sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U;
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_NOR2LOW **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_NOR2LOW:
            if (sVRM_tStatus_DWork.u16DtcVoltage[num] >= cVRM_au16LowThresholdFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_NORMAL;
            } 
            else
            {
                if (sVRM_tStatus_DWork.TempCounterTypeD[num] >= (uint32)cVRM_au16N2LTimeFlowDtcTypeD[num]) 
                {
                    sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_LOW;
                    sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U;
                    
                }
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_NORMAL ***********************************************************/
/********************************************************************************************/
        case VRM_STATUS_NORMAL:
            if (sVRM_tStatus_DWork.u16DtcVoltage[num] < cVRM_au16LowThresholdFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_NOR2LOW;
                sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U;
            } 
            else if (sVRM_tStatus_DWork.u16DtcVoltage[num] > cVRM_au16HighThresholdFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_NOR2HIGH;
                sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U;
            }
            else 
            {
                DEM_u8ClearError((uint8)u32HighDtc);
                DEM_u8ClearError((uint8)u32LowDtc);
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_OVER *************************************************************/
/********************************************************************************************/
        case VRM_STATUS_OVER:
            DEM_u8ReportError((uint8)u32HighDtc);
            if (sVRM_tStatus_DWork.u16DtcVoltage[num] <= cVRM_au16HighThresholdFlowDtcTypeD[num]-cVRM_au16HighHystFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_OVR2NOR;
                sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U; 
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_OVR2NOR **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_OVR2NOR:
            if (sVRM_tStatus_DWork.TempCounterTypeD[num] >= (uint32)cVRM_au16O2NTimeFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_NORMAL;
                DEM_u8ClearError((uint8)u32HighDtc);
            }
            else if (sVRM_tStatus_DWork.u16DtcVoltage[num] > cVRM_au16HighThresholdFlowDtcTypeD[num] -cVRM_au16HighHystFlowDtcTypeD[num]) 
            {
    
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_OVER;
            } 
            else 
            {
                /* nothing to do */
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_UND2NOR **********************************************************/
/********************************************************************************************/
        case VRM_STATUS_UND2NOR:
            if (sVRM_tStatus_DWork.TempCounterTypeD[num] >= (uint32)cVRM_au16U2NTimeFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_NORMAL;
                DEM_u8ClearError((uint8)u32LowDtc);
            }
            else if (sVRM_tStatus_DWork.u16DtcVoltage[num] < cVRM_au16LowThresholdFlowDtcTypeD[num] +cVRM_au16LowHystFlowDtcTypeD[num]) 
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_UNDER;
            } 
            else 
            {
                /* nothing to do */
            }
        break;
/********************************************************************************************/
/*********** VRM_STATUS_UNDER ************************************************************/
/********************************************************************************************/
        case VRM_STATUS_UNDER:
            DEM_u8ReportError((uint8)u32LowDtc);
            if (sVRM_tStatus_DWork.u16DtcVoltage[num] >= cVRM_au16LowThresholdFlowTypeA[num] + cVRM_au16LowHystFlowDtcTypeD[num])
            {
                sVRM_tStatus_DWork.IsVoltageStatusTypeD[num]  = VRM_STATUS_UND2NOR;
                sVRM_tStatus_DWork.TempCounterTypeD[num] = 0U;
            } 
        break;
/********************************************************************************************/
/*********** VRM_default ********************************************************************/
/********************************************************************************************/
   default:  break;
   }
}
#endif

/****************************************************************
 process: VRM_vStatusFlowTypeCWakeUp
 purpose: set TypeC state rejudge from battery voltage flag
 ****************************************************************/
void VRM_vStatusFlowTypeCWakeUp(void)
{
    sVRM_bTypeCReinit = FALSE;
}

/****************************************************************
 process: VRM_vDtcStep
 purpose: call by 10ms run DTC status machine
 ****************************************************************/
void VRM_vDtcStep(void)
{
    //Dtc related, it is empty now
}
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
