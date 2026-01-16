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

#ifndef _PFM_CFG_H
#define _PFM_CFG_H
#include "Pfm_Types.h"

/***********************    Global Type Definition    ************************/

/* Abbreviations used throughout this module:
   DDS: Defect Detect State (ING: In-progress, POS: Positive, NEG: Negative, SET: Set, CLR: Clear)
   DDT: Defect Detect Type (VCC: Short to VCC, GND: Short to GND, OL: Open Load)
   DFC: Defect Filter Count (SET: Set counter, CLR: Clear counter)
   DRS: Defect Report State, PID: Physical ID, FID: Function ID (alias for PID)
*/


/***********************    Global Type Definition    ************************/

/*chip of group list order: from left to right, from top to dowm */
typedef enum
{
    PFM_PID_DUMMTY,

    PFM_PID_SIZE
} PFM_PhysicalId_e;


/* Match with the index of Dem_Cfg_DtcTable[] in Dem_Lcfg.c*/
enum
{
    /* Index    UdsDtc */
    /*     0 */ DtcClass_DTC_DUMMY = 0,

    DTC_MAX
};


#define PFM_DEM_ERROR_ENABLE_FLG    1U   //gDEM_bDiagErrorEnableFlg


/**************************  Macro Definitions    **************************/

/* Abbreviations used in macro names:
   FID: Function ID mapping (aliases for PID), 
   PID: Physical ID, DDT: Defect Detect Type, DFC: Defect Filter Count
*/

#define PFM_FID_OPHXX    (PFM_PID_DUMMTY)    

#define PFM_FID_SLC_PWM    (PFM_PID_DUMMTY)
#define PFM_FID_VREF01    (PFM_PID_DUMMTY)
#define PFM_FID_VREF02    (PFM_PID_DUMMTY)
#define PFM_FID_VREF03    (PFM_PID_DUMMTY)

extern const uint8 Pfm_DefectFilterTime[PFM_PID_SIZE][PFM_DDT_SIZE][PFM_DFC_SIZE];
extern const uint16 Pfm_DefectDtcId[PFM_PID_SIZE][PFM_DDT_SIZE];
extern const uint8 Pfm_InterceptEnableMask[PFM_PID_SIZE];
extern const boolean Pfm_InterceptState[PFM_PID_SIZE];

#endif // _PFM_CFG_H


