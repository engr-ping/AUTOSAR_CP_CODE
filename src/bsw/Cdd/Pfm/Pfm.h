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

#ifndef _PFM_H
#define _PFM_H
#include "Pfm_Types.h"
#include "Pfm_Cfg.h"

/* Module: Pfm - Power/Fault Management
   Abbreviations used:
   PID: Physical ID - identifies the physical fault detection device
   DDT: Defect Detect Type - type of defect (short to Vcc, short to Gnd, open load)
   DFC: Defect Filter Count - counter for fault filtering
   DDS: Defect Detect State - current state of defect detection
*/

extern boolean Pfm_InterceptEnable[PFM_PID_SIZE];

extern void Pfm_Init(void);
extern void Pfm_10ms(void);
extern void Pfm_EnableDiagnostic(uint8 Id, boolean Enable);

extern void Pfm_DefectReport(  PFM_PhysicalId_e Pid, 
                              PFM_DefectDetectState_e OpenLoad, 
                              PFM_DefectDetectState_e Short2Vcc, 
                              PFM_DefectDetectState_e Short2Gnd );

extern void Pfm_ClearFault(uint8 Id);
extern void Pfm_ClearFaultAll(void);
extern boolean Pfm_GetFaultState( PFM_PhysicalId_e Pid, uint8 Ddt);

#endif


