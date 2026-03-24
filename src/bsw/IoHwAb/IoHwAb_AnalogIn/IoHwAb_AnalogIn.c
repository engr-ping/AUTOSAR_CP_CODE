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


#include "IoHwAb_AnalogIn.h"
#include "IoHwAb_AnalogIn_Cfg.h"
#include "IoHwAb_AnalogIn_Api.h"

uint16 IoHwAb_AnalogIn_aiDiagIntSt[IOHWAB_AI_CHN_MAX];
boolean IoHwAb_AnalogIn_aiDiagIntEn[IOHWAB_AI_CHN_MAX];


extern uint16 Vrm_GetVoltageCompensation(uint16 AdValue, uint8 CompensateType);


static uint16 IoHwAb_AnalogIn_DebounceAnalog( uint16 input, uint16 * debounceBuf, uint8 debounceTime )
{
    uint32  sum;
    uint16* tmpPtr;
    uint16  ret;
    uint16  max;
    uint16  min;
    uint8   i;

    if(debounceTime == 0)
    {
        /* if debounce time is 0 or 1, output is input everytime.  */
        ret = input;
    }
    else 
    {
        if(debounceTime == 1)
        {
            /* if debounce time is 2, output is average value of current input and last time input.  */
            sum              = *debounceBuf + input;
            ret              = (uint16)(sum >> 1);
        }
        else
        {
            /* The maximum of debounce time is IOHWAB_AI_DEBOUNCE_AN_TIME_MAX */
            if(debounceTime > IOHWAB_AI_DEBOUNCE_AN_TIME_MAX)
            {
                debounceTime  = IOHWAB_AI_DEBOUNCE_AN_TIME_MAX;
            }

            /* if debounce time is 2 or up 2. */
            debounceTime      = debounceTime - 1;
            tmpPtr             = debounceBuf + debounceTime;

            /* First remove maximum and minimum value. Then get the average value.  */
            if( input > *tmpPtr )
            {
                max          = input;
                min          = *tmpPtr;
            }
            else
            {
                max          = *tmpPtr;
                min          = input;
            }

            /* Sum of the latest series inputs, except maximum and minimum. */
            sum              = 0;
            for( i = 0; i < debounceTime; i++ )
            {
                *tmpPtr        = *(tmpPtr - 1);
                tmpPtr         = tmpPtr - 1;

                if( *tmpPtr > max )
                {
                    sum     += max;
                    max      = *tmpPtr;
                }
                else if( *tmpPtr < min )
                {
                    sum     += min;
                    min      = *tmpPtr;
                }
                else
                {
                    sum     += *tmpPtr;
                }
            }

            /* Get the average value  */
            sum             /= debounceTime;
            ret          = (uint16)sum;
        }

        /* save current input unitl next time calculation. */
        *debounceBuf        = input; 
    }

    return(ret);
}


uint16 IoHwAb_AnalogIn_SignalProcess(uint16 channelId)
{
    uint16 tmp;
    uint16 retVal;
    const IoHwAb_AnalogIn_ChannelConfig_t* channelCfg = &IoHwAb_AnalogIn_ChannelCfg[channelId];
    uint16 adValue = AdcIf_ReadChannel(channelId);

    tmp = Vrm_GetVoltageCompensation(adValue, channelCfg->vrmCompenstate);
    retVal = IoHwAb_AnalogIn_DebounceAnalog(tmp, channelCfg->debounceBuff, channelCfg->debounceCnt);
    return retVal;
}


uint16 IoHwAb_AnalogIn_ReadChannel(uint16 channelId)
{
    uint16 adValue = 0u;
    if(IoHwAb_AnalogIn_aiDiagIntEn[channelId] != (boolean)FALSE) 
    {
        adValue = IoHwAb_AnalogIn_aiDiagIntSt[channelId]; 
    }
    else
    {
        adValue = IoHwAb_AnalogIn_SignalProcess(channelId);
    }
    return adValue;
}

void IoHwAb_AnalogIn_SetChannelDiagInt(uint16 channelId, uint16 st)
{
  IoHwAb_AnalogIn_aiDiagIntEn[channelId] = (boolean)TRUE;
  IoHwAb_AnalogIn_aiDiagIntSt[channelId] = st;
}

void IoHwAb_AnalogIn_ClearChannelDiagInt(uint16 channelId)
{
  IoHwAb_AnalogIn_aiDiagIntEn[channelId] = (boolean)FALSE;
}

void IoHwAb_AnalogIn_Init(void)
{
    uint8 i;
    (void)memset(IoHwAb_AnalogIn_aiDiagIntEn, 0u, sizeof(IoHwAb_AnalogIn_aiDiagIntEn));
    (void)memset(IoHwAb_AnalogIn_aiDiagIntSt, 0u, sizeof(IoHwAb_AnalogIn_aiDiagIntSt));
}

void IoHwAb_AnalogIn_EnterSleep(void)
{
    uint8 i;
    const IoHwAb_AnalogIn_WakeUpConfig_t* wakeUpCfg = NULL;
    const IoHwAb_AnalogIn_ChannelConfig_t* channelCfg = NULL;
    for(i = 0u; i < IOHWAB_AI_WD_MAX; i++)
    {
        wakeUpCfg = &IoHwAb_AnalogIn_WakeUpSignal[i];
        channelCfg = &IoHwAb_AnalogIn_ChannelCfg[wakeUpCfg->aiChannelId];
        IoHwAb_AnalogIn_SignalWakeUpSaved[i] = IoHwAb_AnalogIn_SignalVal[wakeUpCfg->aiChannelId];
    }
}

#define LPM_START_SEC_CODE_RAM
#include "MemMap.h"


/****************************************************************
 process: IoHwAb_AnalogIn_SignalConfirmProcess
 purpose: according to raw ad value, copy to debounce buffer
 ****************************************************************/
void IoHwAb_AnalogIn_SignalConfirmProcess( uint16 wkChannelId)
{
    uint8 ii;
    const IoHwAb_AnalogIn_WakeUpConfig_t* wakeUpCfgPtr = &IoHwAb_AnalogIn_WakeUpSignal[wkChannelId];
    const IoHwAb_AnalogIn_ChannelConfig_t* channelCfg = &IoHwAb_AnalogIn_ChannelCfg[wakeUpCfgPtr->aiChannelId];
    uint16 adValue = IoHwAb_AnalogIn_SignalVal[wakeUpCfgPtr->aiChannelId];

    if(channelCfg->debounceCnt > 0u)
    {
        for(ii = 0u; ii < channelCfg->debounceCnt; ii++)
        {
            channelCfg->debounceBuff[ii] = adValue;
        }
    }
}

/****************************************************************
 process: IoHwAb_AnalogIn_SignalWakeUpJudge
 purpose: WakeUp judge according to Shift Position
 ****************************************************************/
uint8 IoHwAb_AnalogIn_SignalWakeUpJudge(uint8 judgeA, uint8 judgeB)
{
    boolean result;
    
    if(judgeA != judgeB)
    {
        result = (boolean)TRUE;
    }
    else
    {
        result = (boolean)FALSE;
    }

    return result;
}


void IoHwAb_AnalogIn_WakeUpConfirm(void)
{
    uint8 i;
    for(i = 0u; i < IOHWAB_AI_WD_MAX; i++)
    {
        IoHwAb_AnalogIn_SignalConfirmProcess((uint16)i);
    }

}
#define LPM_STOP_SEC_CODE_RAM
#include "MemMap.h"