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

#ifndef _PFM_H
#define _PFM_H

#include "Pfm_Cfg.h"

extern boolean gPFM_abInterceptEnable[PFM_PID_SIZE];

extern void PFM_vInit(void);
extern void PFM_v10ms(void);
extern void PFM_vEnableDiagnosic(uint8 u8Id, boolean bEnable);

extern void PFM_vDefectReport(  PFM_PhysicalId_e        ePid, 
                                PFM_DefectDetectState_e eOpenLoad, 
                                PFM_DefectDetectState_e eShort2Vcc, 
                                PFM_DefectDetectState_e eShort2Gnd );

extern void PFM_vClearFault(uint8 u8Id);
extern void PFM_vClearFaultAll(void);
extern boolean PFM_bGetFaultState( PFM_PhysicalId_e ePid,  uint8 u8Ddt);

#endif


