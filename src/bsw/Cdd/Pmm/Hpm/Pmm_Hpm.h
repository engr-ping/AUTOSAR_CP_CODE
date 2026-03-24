/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Pmm_Smc                                                                                             
*  Content:  Power Mode Management for High Power Mode
*  Category: Ecu init and shutdown management
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */


#ifndef _PMM_HPM_H_
#define _PMM_HPM_H_

/* Include Headerfiles  */
#include "Platform_Types.h"
#include "Pmm_Lpm.h"
/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/
extern void _start_CyclicWakeUp(void);

/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/
extern void Pmm_Hpm_Init(void);
extern Pmm_Lpm_WakeResourceType_e Pmm_Hpm_GetWakeupEvents(uint8 u8Index);
extern void Pmm_Hpm_CheckModeTransition(void);
extern void Pmm_Hpm_PreEnterSleep(void);
extern void Pmm_Hpm_PreEnterReset(void);


#endif
