/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Pmm_Sac  
*  Content:  Power Mode Management for Sleep Awake Control
*  Category: Sleep Awake Control Management
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */

#ifndef _PMM_LPM_H_
#define _PMM_LPM_H_

/* Include Headerfiles  */
#include "Platform_Types.h"
#include "Pmm_Lpm_LCfg.h"
#include "Pmm_Lpm_ProjectCfg.h"
/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/
/**
* @{
* @brief WKPU External Interrupt Channels defines
*/



/* AUTOSAR Software specification version information */
#define PMM_LPM_RELEASE_MAJOR_VERSION            (3u)
#define PMM_LPM_RELEASE_MINOR_VERSION            (0u)
#define PMM_LPM_RELEASE_REVISION_VERSION         (0u)

#define LPM_WKPU_00    ((uint8) 0U)
#define LPM_WKPU_01    ((uint8) 1U)
#define LPM_WKPU_02    ((uint8) 2U)
#define LPM_WKPU_03    ((uint8) 3U)
#define LPM_WKPU_04    ((uint8) 4U)
#define LPM_WKPU_05    ((uint8) 5U)
#define LPM_WKPU_06    ((uint8) 6U)
#define LPM_WKPU_07    ((uint8) 7U)
#define LPM_WKPU_08    ((uint8) 8U)
#define LPM_WKPU_09    ((uint8) 9U)
#define LPM_WKPU_10   ((uint8)10U)
#define LPM_WKPU_11   ((uint8)11U)
#define LPM_WKPU_12   ((uint8)12U)
#define LPM_WKPU_13   ((uint8)13U)
#define LPM_WKPU_14   ((uint8)14U)
#define LPM_WKPU_15   ((uint8)15U)
#define LPM_WKPU_16   ((uint8)16U)
#define LPM_WKPU_17   ((uint8)17U)
#define LPM_WKPU_18   ((uint8)18U)
#define LPM_WKPU_19   ((uint8)19U)
#define LPM_WKPU_20   ((uint8)20U)
#define LPM_WKPU_21   ((uint8)21U)
#define LPM_WKPU_22   ((uint8)22U)
#define LPM_WKPU_23   ((uint8)23U)
#define LPM_WKPU_24   ((uint8)24U)
#define LPM_WKPU_25   ((uint8)25U)
#define LPM_WKPU_26   ((uint8)26U)
#define LPM_WKPU_27   ((uint8)27U)
#define LPM_WKPU_28   ((uint8)28U)
#define LPM_WKPU_29   ((uint8)29U)
#define LPM_WKPU_30   ((uint8)30U)
#define LPM_WKPU_31   ((uint8)31U)

#define SLEEP_AWAKE_CYCLE   100U          //Cycle Awake Time ms

#define Pmm_Lpm_ClearSleepTime()           (gPmm_Lpm_u32SleepTime_RAM = 0u)
#define PMM_LPM_AI_PUP1_FV IOHWAB_AI_WD_MAX



#define Pmm_Lpm_EnablePup1()   
#define Pmm_Lpm_DisablePup1()   




/* After double check, confirmed wakeup reason */
typedef enum
{

    LPM_CW_RTC          = 0U,            /*Confirmed wakeup RTC                   */
    LPM_CW_CTU          = 1U,            /*Confirmed wakeup SSWU                  */
    LPM_CW_RKE          = 2U,            /*Confirmed wakeup reason from RKE       */
    LPM_CW_LF           = 3U,           /*Confirmed wakeup reason from LF        */
    LPM_CW_SBC_CANRX    = 4U,            /*Confirmed wakeup reason from SBC_CANRX */
    LPM_CW_CAN2RX       = 5U,            /*Confirmed wakeup reason from CAN2_RX  */
    LPM_CW_LIN01        = 6U,            /*Confirmed wakeup reason from LIN1      */
    LPM_CW_AI           = 23U,           /*Confirmed wakeup reason from Analog input     */
    LPM_CW_DI           = 24U,           /*Confirmed wakeup reason from Digital input     */
    LPM_CW_NOWAKE                       /*Confirmed wakeup reason    */
}Pmm_Lpm_WakeResourceType_e;

typedef enum
{
    /** WKPU_FALLING_EDGE = An appropriate action shall be executed when a falling edge
        occurs on the WKPU input signal. */
    PMM_LPM_WKPU_FALLING_EDGE = 0x0U,
    /** WKPU_RISING_EDGE = An appropriate action shall be executed when a rising edge
        occurs on the WKPU input signal. */
    PMM_LPM_WKPU_RISING_EDGE  = 0x1U,
    /** WKPU_BOTH_EDGES = An appropriate action shall be executed when a falling edge or
        rising edge occurs on the WKPU input signal. */
    PMM_LPM_WKPU_BOTH_EDGES   = 0x2U
} Pmm_Lpm_WKPU_ActivationType;

typedef struct
{
    Pmm_Lpm_WakeResourceType_e                        Index;
    uint8                                          WKPU_Channel;
    Pmm_Lpm_WKPU_ActivationType                       WKPU_EDGE;
    boolean                                        IsEnable;
} Pmm_Lpm_IcuWakeupSrc_t;


typedef struct
{
    uint8                                            Index;
    uint8                                            AiChannel;
    uint8                                            u8PupCompType;
}Pmm_Lpm_AiChannelInfo_t;
typedef enum
{
    PMM_LPM_ADC_WKP_BY_SHIFT,
    PMM_LPM_ADC_WKP_BY_THRESHOLD
}Pmm_Lpm_AiWkType_e;

typedef struct
{
    uint16          u16Tolerance;
    Pmm_Lpm_AiWkType_e eAdcWkType;
    boolean         bAiChnEn;
}Pmm_Lpm_AiCfgType_t;

typedef struct
{
    uint8                                          Index;
    uint8                                          DiChannel;
    uint8                                          InvertType;
    boolean                                        *pVaribleType;
}Pmm_Lpm_DiChannelInfo_t;

typedef struct
{
    volatile uint16                                   PortChannel;
    volatile uint32                                   RegValue;
}Pmm_Lpm_PortType_t;

typedef struct
{
    volatile uint8                                   PortChannel;
    volatile uint32                                  RegValue;

}Pmm_Lpm_OPCPortType_t;

typedef struct
{
    uint8                                   OpcPeriod;
    uint8                                   OpcActive;
    boolean*                                IsEnableOPC;
}Pmm_Lpm_OpcCntType_t;


/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/
extern const Pmm_Lpm_IcuWakeupSrc_t cPmm_Lpm_atIcuWKCfg[PMM_LPM_ICU_WK_SRC_NUM];
extern const Pmm_Lpm_AiChannelInfo_t cPmm_Lpm_atAiChanCfg[IOHWAB_AI_WD_MAX + 1];
extern const Pmm_Lpm_DiChannelInfo_t cPmm_Lpm_atDiChanWkCfg[IOHWAB_DI_WD_MAX];
extern const Pmm_Lpm_PortType_t cPmm_Lpm_atPortCfg[PMM_LPM_PORT_MAXNUM];
extern const Pmm_Lpm_AiCfgType_t  cPmm_Lpm_atAdWkupSrcPrjCfg[IOHWAB_AI_WD_MAX];
extern const boolean cPmm_Lpm_abDiWkupSrcEnable[IOHWAB_DI_WD_MAX];


#define LPM_START_PROTECTED_RAM
#include "MemMap.h"

/* Record Raw wakeup resource for moniter */
extern Pmm_Lpm_WakeResourceType_e gPmm_Lpm_aeWakeupEvents_RAM[LPM_RECORD_MORNITER_DATA_SIZE];
extern uint16 gPmm_Lpm_au16AdcValue_RAM[IOHWAB_AI_WD_MAX + 1];
extern uint32 gPmm_Lpm_u32DiWakeupSrc_RAM;
extern uint16 gPmm_Lpm_u16AiWakeupSrc_RAM;
extern Pmm_Lpm_IcuWakeupSrc_t gPmm_Lpm_atIcuWKCfg_RAM[PMM_LPM_ICU_WK_SRC_NUM];
extern Pmm_Lpm_AiChannelInfo_t gPmm_Lpm_atAiChanCfg_RAM[IOHWAB_AI_WD_MAX + 1];
extern Pmm_Lpm_DiChannelInfo_t gPmm_Lpm_atDiChanWkCfg_RAM[IOHWAB_DI_WD_MAX];
extern Pmm_Lpm_PortType_t gPmm_Lpm_atPortCfg_RAM[PMM_LPM_PORT_MAXNUM];
extern Pmm_Lpm_AiCfgType_t gPmm_Lpm_atAdWkupSrcPrjCfg_RAM[IOHWAB_AI_WD_MAX];
extern boolean gPmm_Lpm_abDiWkpSrcEnable_RAM[IOHWAB_DI_WD_MAX];
extern IoHwAb_DI_WakeUp_e gPmm_Lpm_aeWakeupParam_RAM[ENUM_INPUT_CHANNEL_ALL_NUM];
extern IoHwAb_u8GetADFuncPtr gPmm_Lpm_apu8GetWakeUpADFuncTab_RAM[IOHWAB_AI_WD_MAX];
extern boolean gPmm_Lpm_bWakeFlag_RAM;

extern uint32  gPmm_Lpm_u32SleepTime_RAM;

extern uint8  gPmm_Lpm_u8OpcChnEn_RAM;

extern uint32 gPmm_Lpm_u32WelcomeLightSleepTime_RAM;
extern uint32 gPmm_Lpm_u32WelcomeLightPollingTime_RAM;
extern boolean gPmm_Lpm_bWDLRunOnce_RAM;

#define LPM_STOP_PROTECTED_RAM
#include "MemMap.h"




/* Record Raw wakeup resource for moniter */
extern void Pmm_Lpm_CheckWakeupEvents(void);
extern void Pmm_Lpm_SleepActivity();

#endif
