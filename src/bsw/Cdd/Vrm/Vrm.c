/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Vrm                                                                                             
*  Content:  Voltage Range Management
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */                                          

#include "Vrm.h"
#include "Std_Types.h"

/* Local Module RAM-Definitions (attribute static)                      */
/* ===========================================                          */
/* Definition of variables only local to this module. That is, not to   */
/* be exported to other modules.                                        */

/* Exported Variables Definitions */
/* ============================================================         */

uint8 Vrm_InterceptEnableArray[VRM_PID_SIZE];

/****************************************************************
 process: Vrm_Init
 purpose: VRM internal status init
 ****************************************************************/
void Vrm_Init(void)
{
    uint8 Index;
    Vrm_StatusInit();

    for (Index = 0U; Index < (uint8)VRM_PID_SIZE; Index++) 
    {
        Vrm_CLR_INTERCEPT(Index);
    }
}


/****************************************************************
 process: Vrm_MainFunction10ms
 purpose: called by 10ms task
 ****************************************************************/
void Vrm_MainFunction10ms(void)
{ 
    /* update CompensateFactor */
    VRM_CompensateFactorUpdatePup(0);
    VRM_CompensateFactorUpdatePup(1);
    VRM_CompensateFactorUpdatePup(2);
    Vrm_SystemVoltageCalculation();
    Vrm_StatusStep(); /*must after Vrm_SystemVoltageCalculation*/
}


/****************************************************************
 process: Vrm_MainFunction10msWakeup
 purpose: called by 10ms wake pending task
 ****************************************************************/
void Vrm_MainFunction10msWakeup(void)
{ 
    /* update CompensateFactor */
    VRM_CompensateFactorUpdatePup(0);
}

