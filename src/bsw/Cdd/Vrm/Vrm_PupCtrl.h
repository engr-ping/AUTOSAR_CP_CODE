/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Vrm_PupCtrl                                                                                             
*  Content:  Pull-up power supply control module source file.
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2025.12.30    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */
#include "Std_Types.h"

#ifndef _VRM_PUPCTRL_H
#define _VRM_PUPCTRL_H
/* Exported Macros Definitions                                          */



/* Exported Function Definitions                                       */

extern void Vrm_SetAndKeepPowerOutput(uint8 PupSt);
extern void Vrm_SetAndKeepPup1Output(uint8 PupSt);
extern void Vrm_SetAndKeepPup2Output(uint8 PupSt);
extern void Vrm_SetAndKeepPup3Output(uint8 PupSt);


extern void Vrm_SetPowerOutput(uint8 PupSt);
extern void Vrm_SetPup1Output(uint8 PupSt);
extern void Vrm_SetPup2Output(uint8 PupSt);
extern void Vrm_SetPup3Output(uint8 PupSt);


extern void Vrm_ReleasePowerOutput(void);
extern void Vrm_ReleasePup1Output(void);
extern void Vrm_ReleasePup2Output(void);
extern void Vrm_ReleasePup3Output(void);


#endif

