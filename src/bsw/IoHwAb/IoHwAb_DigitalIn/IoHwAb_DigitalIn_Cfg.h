/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: IoHwAb_DigitalIn                                                                                             
*  Content:   DigitalIn module of IoHwAb
*  Category: IoHwAb DigitalIn
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */

#ifndef _IOHWAB_DIGITALIN_CFG_H_
#define _IOHWAB_DIGITALIN_CFG_H_

#include "IoHwAb_DigitalIn_Types.h"
#include "DioIf.h"

/* Macros Local To This Module                                          */
/* ===========================                                          */
#define IOHWAB_DI_DEBOUNCE_DI_TIME_MAX     (8u)
#define IOHWAB_DI_CHN_MAX                  52u
#define IOHWAB_DI_MAX_DEBOUNCE_TIME        (7u)

/* Invert Configuration Constants */
#define INVERT_LOW_ACTIVE                  (1u)
#define INVERT_HIGH_ACTIVE                 (0u)
#define INVERT_MC33978_DEFAULT             (0u)

/* Digital Input Channel IDs */
typedef enum
{
    IOHWAB_DI_CHN_IDL01 = 0,
    IOHWAB_DI_CHN_IDL02,
    IOHWAB_DI_CHN_IDL03,
    IOHWAB_DI_CHN_IDL04,
    IOHWAB_DI_CHN_IDL05,
    IOHWAB_DI_CHN_IDL06,
    IOHWAB_DI_CHN_IDL07,
    IOHWAB_DI_CHN_IDL08,
    IOHWAB_DI_CHN_IDL09,
    IOHWAB_DI_CHN_IDL10,
    IOHWAB_DI_CHN_IDL11,
    IOHWAB_DI_CHN_IDL12,
    IOHWAB_DI_CHN_IDL13,
    IOHWAB_DI_CHN_IDL14,
    IOHWAB_DI_CHN_IDL15,
    IOHWAB_DI_CHN_IDL16,
    IOHWAB_DI_CHN_IDL17,
    IOHWAB_DI_CHN_IDL18,
    IOHWAB_DI_CHN_IDL19,
    IOHWAB_DI_CHN_IDL20,
    IOHWAB_DI_CHN_IDL21,
    IOHWAB_DI_CHN_IDL22,
    IOHWAB_DI_CHN_IDL23,
    IOHWAB_DI_CHN_IDL24,
    IOHWAB_DI_CHN_IDL25,
    IOHWAB_DI_CHN_IDL26,
    IOHWAB_DI_CHN_IDL27,
    IOHWAB_DI_CHN_IDL28,
    IOHWAB_DI_CHN_IDL29,
    IOHWAB_DI_CHN_IDL30,
    IOHWAB_DI_CHN_IDL31,
    IOHWAB_DI_CHN_IDL32,
    IOHWAB_DI_CHN_IDL33,
    IOHWAB_DI_CHN_IDL34,
    IOHWAB_DI_CHN_IDH01,
    IOHWAB_DI_CHN_IDH02,
    IOHWAB_DI_CHN_IDH03,
    IOHWAB_DI_CHN_IDH04,
    IOHWAB_DI_CHN_IDX01,
    IOHWAB_DI_CHN_IDX02,
    IOHWAB_DI_CHN_IDX03,
    IOHWAB_DI_CHN_IDX04,
    IOHWAB_DI_CHN_IDX05,
    IOHWAB_DI_CHN_IPL01,
    IOHWAB_DI_CHN_IPL02,
    IOHWAB_DI_CHN_IPL03,
    IOHWAB_DI_CHN_IPL04,
    IOHWAB_DI_CHN_IPL05,
    IOHWAB_DI_CHN_IPL06,
    IOHWAB_DI_CHN_IPL07,
    IOHWAB_DI_CHN_MAX
} IoHwAb_DiChannelId_e;

/* Wake-Up Channel IDs */
typedef enum
{
    IOHWAB_DI_WD_IDL09 = 0,
    IOHWAB_DI_WD_IDL11,
    IOHWAB_DI_WD_IDL10,
    IOHWAB_DI_WD_IDL08,
    IOHWAB_DI_WD_IDL05,
    IOHWAB_DI_WD_IDL15,
    IOHWAB_DI_WD_IDL07,
    IOHWAB_DI_WD_IDL06,
    IOHWAB_DI_WD_IDL03,
    IOHWAB_DI_WD_IDL01,
    IOHWAB_DI_WD_IDL04,
    IOHWAB_DI_WD_IDL28,
    IOHWAB_DI_WD_IDL02,
    IOHWAB_DI_WD_IDL14,
    IOHWAB_DI_WD_IDL16,
    IOHWAB_DI_WD_IDX02,
    IOHWAB_DI_WD_IDX03,
    IOHWAB_DI_WD_IDX01,
    IOHWAB_DI_WD_IDL27,
    IOHWAB_DI_WD_IDH01,
    IOHWAB_DI_WD_IDH02,
    IOHWAB_DI_WD_IDH03,
    IOHWAB_DI_WD_IDH04,
    IOHWAB_DI_WD_IPL03,
    IOHWAB_DI_WD_IPL04,
    IOHWAB_DI_WD_IPL05,
    IOHWAB_DI_WD_IPL06,
    IOHWAB_DI_WD_MAX
} IoHwAb_DiWakeUpId_e;

/* Exported Variables Definitions                                       */
/* ===========================                                          */
#define  SAC_START_PROTECTED_RAM
#include "MemMap.h"


#define DEBOUNCE_DI_TIME_MAX    (8u)

#define IOHWAB_DI_GET_POWER_ON_FLAG 

extern boolean IoHwAb_Di_SignalValue[IOHWAB_DI_CHN_MAX];
extern boolean gIoHwAb_abDiDiagIntSt[IOHWAB_DI_CHN_MAX];
extern boolean gIoHwAb_abDiDiagIntEn[IOHWAB_DI_CHN_MAX];
extern boolean IoHwAb_Di_SignalWakeUpSaved[IOHWAB_DI_WD_MAX];

#define  SAC_STOP_PROTECTED_RAM
#include "MemMap.h"

/* Channel Configuration */
extern const IoHwAb_DigitalIn_ChannelType gIoHwAb_DiChannelCfg[IOHWAB_DI_CHN_MAX];

/* Exported Function Definitions                                       */
/* ===========================                                         */
extern void IoHwAb_vDigitalInputHandle(void);
extern void IoHwAb_vDigitalInputWakeUpSaved(void);
extern uint32 IoHwAb_u32DigitalInputWakeUpCompare(void);
extern void IoHwAb_vDigitalInputEnterSleep(void);

#endif /* _IOHWAB_DIGITALIN_CFG_H_ */
