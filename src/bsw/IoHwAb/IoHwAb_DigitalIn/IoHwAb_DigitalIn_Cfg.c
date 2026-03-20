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
#include "IoHwAb_DigitalIn.h"
#include "IoHwAb_DigitalIn_Cfg.h"

/* Macros Local To This Module                                          */
/* ===========================                                          */

/* Local Module RAM-Definitions (attribute static)                      */
/* ===========================================                          */

/* Exported Variables Definitions */
/* ============================================================         */
#define  SAC_START_PROTECTED_RAM
#include "MemMap.h"

/* Digital input signal debounce buffers */
static uint8  IoHwAb_Di_DebBuf[IOHWAB_DI_CHN_MAX];

/* Digital input signal storage */
boolean IoHwAb_Di_SignalValue[IOHWAB_DI_CHN_MAX];
boolean IoHwAb_DigitalIn_diDiagIntSt[IOHWAB_DI_CHN_MAX];
boolean IoHwAb_DigitalIn_diDiagIntEn[IOHWAB_DI_CHN_MAX];
boolean IoHwAb_Di_SignalWakeUpSaved[IOHWAB_DI_WD_MAX];

#define  SAC_STOP_PROTECTED_RAM
#include "MemMap.h"

/* Digital Input Channel Configuration */
const IoHwAb_DigitalIn_ChannelConfig_t IoHwAb_DiChannelCfg[IOHWAB_DI_CHN_MAX] = {
    /*ChannelID,Invert,DebounceTime,DebounceBuffer*/
    {DIO_CHN_IDL01,  5u, INVERT_LOW_ACTIVE,&IoHwAb_Di_DebBuf[0]},  /* IDL01 */
    {DIO_CHN_IDL02,  5u, INVERT_LOW_ACTIVE,&IoHwAb_Di_DebBuf[1]},  /* IDL02 */
};

IoHwAb_DigitalIn_WakeUpConfig_t IoHwAb_DigitalIn_WakeUpSignal[IOHWAB_DI_WD_MAX] = {
    /* WakeUpId, DiChnnelId, Threshold, Condition */
    {DIO_CHN_IDL09, &IoHwAb_Di_SignalWakeUpSaved[DIO_CHN_IDL09]},
    {DIO_CHN_IDL09, &IoHwAb_Di_SignalWakeUpSaved[DIO_CHN_IDL09]},
};

#define SAC_START_SEC_CODE_RAM
#include "MemMap.h"

/****************************************************************
 process: IoHwAb_vDigitalInputHandle
 purpose: Digital input signal handle in 10ms grid
 ****************************************************************/
void IoHwAb_vDigitalInputHandle(void)
{
    /* Process all configured digital input channels */
    uint8 i;
    
    for(i = 0u; i < IOHWAB_DI_CHN_MAX; i++)
    {

    }
}

/****************************************************************
 process: IoHwAb_vDigitalInputWakeUpSaved
 purpose: Save digital input signals before sleep
 ****************************************************************/
void IoHwAb_vDigitalInputWakeUpSaved(void)
{
    uint8 i;
    for(i = 0u; i < IOHWAB_DI_WD_MAX; i++)
    {
        IoHwAb_Di_SignalWakeUpSaved[i] = IoHwAb_Di_SignalValue[IoHwAb_DigitalIn_WakeUpSignal[i].diChannelId];
    }


}

/****************************************************************
 process: IoHwAb_u32DigitalInputWakeUpCompare
 purpose: Compare digital input signals with saved wake-up states
 ****************************************************************/
uint32 IoHwAb_u32DigitalInputWakeUpCompare(void)
{
    uint32 temp_u32DigitalInputWDSignal = 0u;
    uint8 i;
    for(i = 0u; i < IOHWAB_DI_WD_MAX; i++)
    {
      temp_u32DigitalInputWDSignal |= (IoHwAb_DIWakeUpCompare(i)<<i);
    }
    return temp_u32DigitalInputWDSignal;
}



/****************************************************************
process: IoHwAb_vDigitalInputWakeUpConfirm
purpose: 
****************************************************************/
void IoHwAb_DigitalIn_WakeUpConfirm(void)
{
    uint8 i;
    for(i = 0u; i < IOHWAB_DI_WD_MAX; i++)
    {   
        IoHwAb_Di_SignalValue[IoHwAb_DigitalIn_WakeUpSignal[i].diChannelId] = IoHwAb_Di_SignalWakeUpSaved[i]; 
    }
}

#define SAC_STOP_SEC_CODE_RAM
#include "MemMap.h"



void IoHwAb_DigitalIn_MainFunction_C0(void)
{
    /* This function is called periodically to process the digital input signals. */
    /* The implementation of this function should read the raw digital input values and perform debouncing as needed. */
    IoHwAb_Di_SignalValue[0] = IoHwAb_DigitalIn_ReadChannel(0);
    Rte_Write_xxx_xxx(IoHwAb_Di_SignalValue[0]);
}