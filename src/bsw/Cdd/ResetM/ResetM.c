/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: ResetM                                                                                        
*  Content:  Reset Manager
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */
#include "ResetM.h"


static ResetM_ReasonType ResetM_HistoryResetReason[RESETM_HISTORY_SIZE];


void ResetM_ResetReasonMonitor(void)
{
  uint8 i;
  ResetM_ReasonType CurrentResetReason;
  CurrentResetReason = Reset_ResetReasonUpdata();
  for(i = (RESETM_HISTORY_SIZE-1);i > 0u;i--)
  {
    ResetM_HistoryResetReason[i] = ResetM_HistoryResetReason[i - 1u];
  }
  ResetM_HistoryResetReason[0] = CurrentResetReason;

}


ResetM_ReasonType ResetM_GetResetReason(void)
{
  return ResetM_HistoryResetReason[0];
}

Std_ReturnType ResetM_SetResetExcutionType(uint8 Type)
{
    ResetM_CfgType* ResetPrt = &ResetM_Cfg[Type];

    ResetM_Cfg->Function();
}