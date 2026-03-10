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

#ifndef VRM_H
#define VRM_H

#include "Vrm_Types.h"
#include "Vrm_Cfg.h"
#include "Vrm_VoltSts.h"
#include "Vrm_PupCtrl.h"
#include "Vrm_VoltageCompensate.h"

/* ============================================================
   Exported MACRO Definitions                                       
   ============================================================ */

#define Vrm_CLR_INTERCEPT(Id)                            \
do                                                       \
{                                                        \
    Vrm_InterceptEnableArray[Id] = FALSE;                \
}while(0);

#define Vrm_SET_INTERCEPT(Id)                            \
do                                                       \
{                                                        \
    Vrm_InterceptEnableArray[Id] = TRUE;                 \
}while(0);

/* ============================================================
   Exported Variables Definitions                                       
   ============================================================ */

extern uint8 Vrm_InterceptEnableArray[VRM_PID_SIZE];

/* ============================================================
   Exported Function Definitions                                       
   ============================================================ */

extern void Vrm_Init(void);
extern void Vrm_MainFunction10ms(void);
extern void Vrm_MainFunction10msWakeup(void);
extern void Vrm_Enable(void);
extern void Vrm_Disable(void);
    
#endif /* VRM_H */

