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
typedef enum
{
  RESETM_REASON_NONE = 0u,
  RESETM_REASON_SW = 1u,
  RESETM_REASON_SYSTEM = 2u,
  RESETM_REASON_EXT_WATCHDOG = 3u,
  RESETM_REASON_POWER_ON = 4u,
  RESETM_REASON_WAKEUP = 5u,
}ResetM_ReasonType;

#define RESETM_HISTORY_SIZE 10U  /*must >= 2*/

ResetM_ReasonType ResetM_GetResetReason(void);

Std_ReturnType ResetM_SetResetExcutionType(uint8 Type);
