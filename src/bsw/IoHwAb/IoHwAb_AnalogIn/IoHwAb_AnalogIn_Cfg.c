/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: IoHwAb_AnalogIn                                                                                             
*  Content:   AnalogIn module of IoHwAb
*  Category: IoHwAb AnalogIn
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */
#include "IoHwAb_AnalogIn_Cfg.h"
#include "Rte_IoHwAb_AnalogIn.h"

uint16 IoHwAb_AnalogIn_SignalVal[IOHWAB_AI_CHN_MAX];
uint16 IoHwAb_AnalogIn_SignalWakeUpSaved[IOHWAB_AI_WD_MAX];

const IoHwAb_AnalogIn_WakeUpConfig_t IoHwAb_AnalogIn_WakeUpSignal[IOHWAB_AI_WD_MAX] =
{
    /*WakeUp Signal ,GetAdShiftFunc*/
    {IOHWAB_AI_CHN_0, NULL},  /*WakeUp Signal for Channel 0*/
    {IOHWAB_AI_CHN_1, NULL},  /*WakeUp Signal for Channel 1*/
    {IOHWAB_AI_CHN_2, NULL},  /*WakeUp Signal for Channel 2*/
    {IOHWAB_AI_CHN_3, NULL},  /*WakeUp Signal for Channel 3*/
    {IOHWAB_AI_CHN_4, NULL},  /*WakeUp Signal for Channel 4*/
};

const IoHwAb_AnalogIn_ChannelConfig_t IoHwAb_AnalogIn_ChannelCfg[IOHWAB_AI_CHN_MAX] =
{
    /* Voltage Compensation Type, Debounce Count, Debounce Buffer */
    {VRM_COMPENSATE_TYPE_PUP1, 0, NULL},  /*Channel 0*/
    {VRM_COMPENSATE_TYPE_PUP2, 0, NULL},  /*Channel 1*/
    {VRM_COMPENSATE_TYPE_NONE, 0, NULL},  /*Channel 2*/
};



void IoHwAb_AnalogIn_MainFunction_C0(void)
{
    /* This function is called periodically to process the analog input signals. */
    /* The implementation of this function should read the raw ADC values, apply voltage compensation, and perform debouncing as needed. */
    IoHwAb_AnalogIn_SignalVal[IOHWAB_AI_CHN_0] = IoHwAb_AnalogIn_ReadChannel(IOHWAB_AI_CHN_0);
    Rte_Write_xxx_xxx(IoHwAb_AnalogIn_SignalVal[IOHWAB_AI_CHN_0]);
}