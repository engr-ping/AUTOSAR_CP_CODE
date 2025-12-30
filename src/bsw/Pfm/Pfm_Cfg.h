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

#include "Platform_Types.h"


/***********************    Global Type Definition    ************************/
typedef enum
{
    PFM_DDS_ING,
    PFM_DDS_POS,
    PFM_DDS_NEG,
    PFM_DDS_SET,
    PFM_DDS_CLR,

    PFM_DDS_SIZE
} PFM_DefectDetectState_e;

typedef enum
{
    PFM_DDT_VCC,
    PFM_DDT_GND,
    PFM_DDT_OL,

    PFM_DDT_SIZE
} PFM_DefectDetectType_e;

typedef enum
{
    PFM_DFC_SET,
    PFM_DFC_CLR,

    PFM_DFC_SIZE
} PFM_DefectFilterCount_e;

typedef struct
{
    PFM_DefectDetectState_e eShort2Vcc;
    PFM_DefectDetectState_e eShort2Gnd;
    PFM_DefectDetectState_e eOpenLoad;
} PFM_DefectReportState_t;

typedef struct
{
    PFM_DefectReportState_t tDRS;
    boolean bInterceptEnable;
} PFM_FaultState_t;

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


#define PFM_DEM_ERROR_ENABLE_FLG    1   //gDEM_bDiagErrorEnableFlg


/**************************  Macro Definitions    **************************/

#define PFM_FID_OPHxx    (PFM_PID_DUMMTY)    // S3003   OPHxx

#define PFM_FID_OR01    (PFM_PID_DUMMTY)

#define PFM_FID_VREF01    (PFM_PID_DUMMTY)
#define PFM_FID_VREF02    (PFM_PID_DUMMTY)
#define PFM_FID_VREF03    (PFM_PID_DUMMTY)

extern const uint8  cPFM_au8DefectFilterTime[PFM_PID_SIZE][PFM_DDT_SIZE][PFM_DFC_SIZE];
extern const uint16  cPFM_au16DefectDtcId[PFM_PID_SIZE][PFM_DDT_SIZE];
extern const uint8  cPFM_au8InterceptEnableMask[PFM_PID_SIZE];
extern const boolean  cPFM_abInterceptState[PFM_PID_SIZE];

#endif // _PFM_CFG_H


