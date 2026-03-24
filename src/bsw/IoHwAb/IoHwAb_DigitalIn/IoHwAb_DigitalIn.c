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

#define	b_MASK						(uint8)0xFFu

/* uint8 macros */
#define SETBIT_U8(basis,bitpos)     ((basis) |= ((uint8)1 << (bitpos)), TRUE)
#define CLRBIT_U8(basis,bitpos)     ((basis) &= b_MASK - ((uint8)1 << (bitpos)), FALSE)
#define GETBIT_U8(basis,bitpos)     (((basis) & ((uint8)1 << (bitpos))) != 0)
#define	PUTBIT_U8(basis,bitpos,val) ((val) ? SETBIT_U8(basis,bitpos) : CLRBIT_U8(basis,bitpos))
/****************************************************************
 process: IoHwAb_DigitalIn_DebounceDigital
 purpose: Debounce processing for digital signals
 ****************************************************************/
void IoHwAb_DigitalIn_DebounceDigital( uint8 input, uint8 debounceTime, uint8 * const debounceBuf, uint8 * const output )
{
    uint8 mask;

    if( debounceTime == 0u )
    {
        *output = input;
    }
    else
    {
        if( debounceTime == 1u )
        {
            if( (input != FALSE ) == GETBIT_U8(*debounceBuf, 0) )
            /* input is the same with the last input.  */
            {
                *output       = input;
            }

        }
        else
        {
            if( debounceTime > DEBOUNCE_DI_TIME_MAX )
            {
                debounceTime  = DEBOUNCE_DI_TIME_MAX;
            }

            mask              = (uint8)(b_MASK << debounceTime);

            if(input != FALSE)
            /*=== Report true =========================================
                               |.<--Debounce time-->|
                            +--+--+--+--+--+--+--+--+
                            |b7|b6|b5|b4|b3|b2|b1|b0|
                            +--+--+--+--+--+--+--+--+
                              X  1  1  1  1  1  1  1
            ===========================================================*/
            {
                if((*debounceBuf | mask) == b_MASK)    /* 11...1000... */
                {
                    *output   = TRUE;
                }
            }
            else
            /*=== Report false =========================================
                           |.<--Debounce time-->|
                        +--+--+--+--+--+--+--+--+
                        |b7|b6|b5|b4|b3|b2|b1|b0|
                        +--+--+--+--+--+--+--+--+
                          X  0  0  0  0  0  0  0
            ===========================================================*/
            {
                if((*debounceBuf & (~mask)) == 0)      /* 00...0111... */
                {
                    *output   = FALSE;
                }
            }

            /*=== Update debounce buffer for input ====================
                        +--+--+--+--+--+--+--+--+
                        |b7|b6|b5|b4|b3|b2|b1|b0| <== input(bI)
                        +--+--+--+--+--+--+--+--+  
                                    ||
                                    \/    
                        +--+--+--+--+--+--+--+--+
                        |b6|b5|b4|b3|b2|b1|b0|bI|
                        +--+--+--+--+--+--+--+--+
            ===========================================================*/
            *debounceBuf     <<= 1;
        }

        PUTBIT_U8(*debounceBuf, 0, input);
    }
}



/****************************************************************
 process: IoHwAb_vDigitalInput_10ms
 purpose: Digital input signal handle in 10ms grid
 ****************************************************************/
boolean IoHwAb_DigitalIn_firstDebounceFinishFlag = FALSE;

/****************************************************************
 process: IoHwAb_vFirstDebounceFinishProcess
 purpose: wait first debounce finish
 ****************************************************************/
static void IoHwAb_vFirstDebounceFinishProcess(void)
{
    static uint8 sFdfpCount = 0u;

    sFdfpCount++;

    if((sFdfpCount >= (uint8)IOHWAB_DI_MAX_DEBOUNCE_TIME) || (IOHWAB_DI_GET_POWER_ON_FLAG == (boolean)FALSE))
    {
        sFdfpCount = (uint8)IOHWAB_DI_MAX_DEBOUNCE_TIME;
        IoHwAb_DigitalIn_firstDebounceFinishFlag = TRUE;
    }
}

/****************************************************************
 process: IoHwAb_DigitalIn_SignalProcess
 purpose: Process digital input signal with inversion and debouncing
 ****************************************************************/
boolean IoHwAb_DigitalIn_SignalProcess(uint8 channelId, boolean input, boolean * const output)
{
    boolean tempDiSignalInput;
    const IoHwAb_DigitalIn_ChannelConfig_t* channelCfg = &IoHwAb_DiChannelCfg[channelId];
    /* Apply inversion if configured */
    tempDiSignalInput = input ^ channelCfg->invert;

    /* Apply debouncing */
    IoHwAb_DigitalIn_DebounceDigital(tempDiSignalInput, channelCfg->debounceTime, channelCfg->debounceBuf, output);
}

/****************************************************************
 process: IoHwAb_DigitalIn_Init
 purpose: Initialize digital input module
 ****************************************************************/
void IoHwAb_DigitalIn_Init(void)
{
    uint8 i;
    (void)memset(IoHwAb_DigitalIn_diDiagIntEn, 0u, sizeof(IoHwAb_DigitalIn_diDiagIntEn));
    (void)memset(IoHwAb_DigitalIn_diDiagIntSt, 0u, sizeof(IoHwAb_DigitalIn_diDiagIntSt));
}


/****************************************************************
 process: IoHwAb_DigitalIn_EnterSleep
 purpose: Save digital input signals before entering sleep
 ****************************************************************/
void IoHwAb_DigitalIn_EnterSleep(void)
{
    IoHwAb_vDigitalInputWakeUpSaved();
}

/****************************************************************
 process: IoHwAb_DigitalIn_ReadChannel
 purpose: Read digital input channel value
 ****************************************************************/
boolean IoHwAb_DigitalIn_ReadChannel(uint8 channelId)
{
    boolean channelValue = FALSE;
    if(IoHwAb_DigitalIn_diDiagIntEn[channelId] != FALSE)
    {
        /* Use diagnostic interrupt value if enabled */
        IoHwAb_Di_SignalValue[channelId] = IoHwAb_DigitalIn_diDiagIntSt[channelId];
    }
    else
    {
        /* Normal processing: read channel and update signal */
        boolean rawInput = DioIf_ReadChannel(IoHwAb_DiChannelCfg[channelId].channelId);
        
        IoHwAb_DigitalIn_SignalProcess(channelId, rawInput, &IoHwAb_Di_SignalValue[channelId]);
    }
    
    return channelValue;
}

/****************************************************************
 process: IoHwAb_DigitalIn_SetChannelDiagInt
 purpose: Set diagnostic interrupt for digital input channel
 ****************************************************************/
void IoHwAb_DigitalIn_SetChannelDiagInt(uint8 channelId, boolean value)
{
    if(channelId < IOHWAB_DI_CHN_MAX)
    {
        IoHwAb_DigitalIn_diDiagIntEn[channelId] = TRUE;
        IoHwAb_DigitalIn_diDiagIntSt[channelId] = value;
    }
}

/****************************************************************
 process: IoHwAb_DigitalIn_ClearChannelDiagInt
 purpose: Clear diagnostic interrupt for digital input channel
 ****************************************************************/
void IoHwAb_DigitalIn_ClearChannelDiagInt(uint8 channelId)
{
    if(channelId < IOHWAB_DI_CHN_MAX)
    {
        IoHwAb_DigitalIn_diDiagIntEn[channelId] = FALSE;
    }
}

#define LPM_START_SEC_CODE_RAM
#include "MemMap.h"

/****************************************************************
 process: IoHwAb_DigitalIn_SignalWakeUpJudge
 purpose: Judge wake-up based on digital input signal change
 ****************************************************************/
boolean IoHwAb_DigitalIn_SignalWakeUpJudge(boolean currentState, boolean savedState)
{
    if(currentState != savedState)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/****************************************************************
 process: IoHwAb_DigitalIn_SignalConfirmProcess
 purpose: Confirm digital input signal for wake-up detection
 ****************************************************************/
void IoHwAb_DigitalIn_SignalConfirmProcess(boolean input, uint8 debounceTime, uint8 * debounceBuf)
{
    uint8 ii;

    if(debounceTime > 0u)
    {
        for(ii = 0u; ii < debounceTime; ii++)
        {
            debounceBuf[ii] = (input ? 0xFFu : 0x00u);
        }
    }
}

#define LPM_STOP_SEC_CODE_RAM
#include "MemMap.h"