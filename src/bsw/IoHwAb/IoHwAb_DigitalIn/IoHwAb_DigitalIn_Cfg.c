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
    {DIO_CHN_IDL01,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[0]},  /* IDL01 */
    {DIO_CHN_IDL02,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[1]},  /* IDL02 */
    {DIO_CHN_IDL03,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[2]},  /* IDL03 */
    {DIO_CHN_IDL04,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[3]},  /* IDL04 */
    {DIO_CHN_IDL05,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[4]},  /* IDL05 */
    {DIO_CHN_IDL06,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[5]},  /* IDL06 */
    {DIO_CHN_IDL07,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[6]},  /* IDL07 */
    {DIO_CHN_IDL08,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[7]},  /* IDL08 */
    {DIO_CHN_IDL09,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[8]},  /* IDL09 */
    {DIO_CHN_IDL10,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[9]},  /* IDL10 */
    {DIO_CHN_IDL11,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[10]}, /* IDL11 */
    {DIO_CHN_IDL12,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[11]}, /* IDL12 */
    {DIO_CHN_IDL13,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[12]}, /* IDL13 */
    {DIO_CHN_IDL14,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[13]}, /* IDL14 */
    {DIO_CHN_IDL15,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[14]}, /* IDL15 */
    {DIO_CHN_IDL16,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[15]}, /* IDL16 */
    {DIO_CHN_IDL17,  5u, INVERT_LOW_ACTIVE,IoHwAb_Di_DebBuf[16]}, /* IDL17 */


};

IoHwAb_DigitalIn_WakeUpConfig_t IoHwAb_DigitalIn_WakeUpSignal[IOHWAB_DI_WD_MAX] = {
    /* WakeUpId, DiChnnelId, Threshold, Condition */
    {IOHWAB_DI_CHN_IDL09, &IoHwAb_Di_SignalWakeUpSaved[IOHWAB_DI_CHN_IDL09]},
    {IOHWAB_DI_CHN_IDL10, &IoHwAb_Di_SignalWakeUpSaved[IOHWAB_DI_CHN_IDL10]},
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
    IoHwAb_Di_SignalValue[IOHWAB_DI_CHN_0] = IoHwAb_DigitalIn_ReadChannel(IOHWAB_DI_CHN_0);
    Rte_Write_xxx_xxx(IoHwAb_Di_SignalValue[IOHWAB_DI_CHN_0]);
}