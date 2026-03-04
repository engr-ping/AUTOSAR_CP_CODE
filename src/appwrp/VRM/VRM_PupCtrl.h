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
#include "Platform_Types.h"

#ifndef _VRM_PUPCTRL_H
#define _VRM_PUPCTRL_H
/* Exported Macros Definitions                                          */



/* Exported Function Definitions                                       */

extern void VRM_SetAndKeepPowerOutput(uint8 PupSt);
extern void VRM_SetAndKeepPup1Output(uint8 PupSt);
extern void VRM_SetAndKeepPup2Output(uint8 PupSt);
extern void VRM_SetAndKeepPup3Output(uint8 PupSt);


extern void VRM_SetPowerOutput(uint8 PupSt);
extern void VRM_SetPup1Output(uint8 PupSt);
extern void VRM_SetPup2Output(uint8 PupSt);
extern void VRM_SetPup3Output(uint8 PupSt);


extern void VRM_ReleasePowerOutput(void);
extern void VRM_ReleasePup1Output(void);
extern void VRM_ReleasePup2Output(void);
extern void VRM_ReleasePup3Output(void);


#endif

