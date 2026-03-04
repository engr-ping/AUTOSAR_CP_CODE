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

#include "VRM_Types.h"
#include "VRM_Cfg.h"
#include "VRM_VoltSts.h"
#include "VRM_PupCtrl.h"
#include "VRM_VoltageCompensate.h"

/* ============================================================
   Exported MACRO Definitions                                       
   ============================================================ */

#define VRM_CLR_INTERCEPT(Id)                            \
do                                                       \
{                                                        \
    VRM_InterceptEnableArray[Id] = FALSE;                \
}while(0);

#define VRM_SET_INTERCEPT(Id)                            \
do                                                       \
{                                                        \
    VRM_InterceptEnableArray[Id] = TRUE;                 \
}while(0);

/* ============================================================
   Exported Variables Definitions                                       
   ============================================================ */

extern uint8 VRM_InterceptEnableArray[VRM_PID_SIZE];

/* ============================================================
   Exported Function Definitions                                       
   ============================================================ */

extern void VRM_Init(void);
extern void VRM_MainFunction10ms(void);
extern void VRM_MainFunction10msWakeup(void);
extern void VRM_Enable(void);
extern void VRM_Disable(void);
    
#endif /* VRM_H */

