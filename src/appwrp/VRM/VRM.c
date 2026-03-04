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

/* Include Headerfiles  */                                             */

#include "VRM.h"
#include "Platform_Types.h"

/* Local Module RAM-Definitions (attribute static)                      */
/* ===========================================                          */
/* Definition of variables only local to this module. That is, not to   */
/* be exported to other modules.                                        */

/* Exported Variables Definitions */
/* ============================================================         */

uint8 VRM_InterceptEnableArray[VRM_PID_SIZE];

/****************************************************************
 process: VRM_Init
 purpose: VRM internal status init
 ****************************************************************/
void VRM_Init(void)
{
    uint8 Index;

    for (Index = 0U; Index < (uint8)VRM_PID_SIZE; Index++) 
    {
        VRM_CLR_INTERCEPT(Index)
    }
}


/****************************************************************
 process: VRM_MainFunction10ms
 purpose: called by 10ms task
 ****************************************************************/
void VRM_MainFunction10ms(void)
{ 
    /* update CompensateFactor */
    VRM_CompensateFactorUpdatePup1();
    VRM_CompensateFactorUpdatePup2();
    VRM_CompensateFactorUpdatePup3();
}


/****************************************************************
 process: VRM_MainFunction10msWakeup
 purpose: called by 10ms wake pending task
 ****************************************************************/
void VRM_MainFunction10msWakeup(void)
{ 
    /* update CompensateFactor */
    VRM_CompensateFactorUpdatePup1();
}

