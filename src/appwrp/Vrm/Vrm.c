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

#include "Vrm.h"
#include "Std_Types.h"

/* Local Module RAM-Definitions (attribute static)                      */
/* ===========================================                          */
/* Definition of variables only local to this module. That is, not to   */
/* be exported to other modules.                                        */

/* Exported Variables Definitions */
/* ============================================================         */

uint8 Vrm_InterceptEnableArray[Vrm_PID_SIZE];

/****************************************************************
 process: Vrm_Init
 purpose: VRM internal status init
 ****************************************************************/
void Vrm_Init(void)
{
    uint8 Index;

    for (Index = 0U; Index < (uint8)Vrm_PID_SIZE; Index++) 
    {
        Vrm_CLR_INTERCEPT(Index)
    }
}


/****************************************************************
 process: Vrm_MainFunction10ms
 purpose: called by 10ms task
 ****************************************************************/
void Vrm_MainFunction10ms(void)
{ 
    /* update CompensateFactor */
    Vrm_CompensateFactorUpdatePup1();
    Vrm_CompensateFactorUpdatePup2();
    Vrm_CompensateFactorUpdatePup3();
}


/****************************************************************
 process: Vrm_MainFunction10msWakeup
 purpose: called by 10ms wake pending task
 ****************************************************************/
void Vrm_MainFunction10msWakeup(void)
{ 
    /* update CompensateFactor */
    Vrm_CompensateFactorUpdatePup1();
}

