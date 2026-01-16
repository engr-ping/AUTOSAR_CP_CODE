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

#ifndef _PFM_TYPES_H
#define _PFM_TYPES_H

#include "Platform_Types.h"

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
    PFM_DefectDetectState_e Short2Vcc;
    PFM_DefectDetectState_e Short2Gnd;
    PFM_DefectDetectState_e OpenLoad;
} PFM_DefectReportState_t;

typedef struct
{
    PFM_DefectReportState_t DefectReportState;
    boolean InterceptEnable;
} PFM_FaultState_t;



#endif /**< _PFM_TYPES_H */
