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
#include "Pfm.h"
#include "Pfm_Cfg.h"

const uint8  cPFM_au8DefectFilterTime[PFM_PID_SIZE][PFM_DDT_SIZE][PFM_DFC_SIZE] = 
{
    {{0,0},{0,0},{0,0}},        /* PFM_PID_DUMMTY*/

};


/* bit0: short to VCC, bit 1: short to GND, bit 2: Open load */
const uint8 cPFM_au8InterceptEnableMask[PFM_PID_SIZE] = 
{
    0,        /* PFM_PID_DUMMTY */
};


/* configuatre the DTC-ID, need mapping to DEM module and DTC description */
const uint16 cPFM_au16DefectDtcId[PFM_PID_SIZE][PFM_DDT_SIZE] =
{
    /* short to battery */    /* short to ground */     /* open load */
    {DTC_MAX,                 DTC_MAX,                  DTC_MAX},                 /* DUMMY */

};


