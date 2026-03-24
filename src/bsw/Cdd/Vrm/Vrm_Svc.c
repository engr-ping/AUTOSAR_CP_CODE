/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Vrm                                                                                             
*  Content:  Voltage Range Management for System Voltage Calculation
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */

#include "Vrm_Types.h"
#include "Vrm_Cfg.h"


#define DEBOUNCE_VRM_TIME_MAX  (8u)

static uint16 Vrm_SysVoltVal;
static uint16 Vrm_RawBatAdValue[VRM_INPUT_BATTRAY_CHANNEL_NUM][VRM_BAT_DEBOUNCE_COUNT];
static uint16 Vrm_BattVoltVal[VRM_INPUT_BATTRAY_CHANNEL_NUM];

static uint16 Vrm_InputDebounce( uint16 inputValue, uint16 * debounceBuffer, uint8 debounceTime );

void Vrm_SystemVoltageCalculation(void)
{
    uint16 MiniVolt;
    uint16 MaxVolt;
    uint16 CutAdc;
    uint16 CutVolt;
    uint8 index;
    Vrm_VoltageChannel_t* BattCfgPrt = &Vrm_BattChannelCfg[0];
    CutAdc = Vrm_InputDebounce(AdcIf_ReadChannel(BattCfgPrt->AdcIfChannel),&Vrm_RawBatAdValue[0][0],BattCfgPrt->DebounceCnt);
    CutVolt = CutAdc * BattCfgPrt->kParameter + BattCfgPrt->offset;
    MiniVolt = CutVolt;
    MaxVolt = CutVolt;
    Vrm_BattVoltVal[0] = CutVolt;
    BattCfgPrt++;
    for(index =1;index < VRM_INPUT_BATTRAY_CHANNEL_NUM;index++ )
    {

        CutAdc = Vrm_InputDebounce(AdcIf_ReadChannel(BattCfgPrt->AdcIfChannel),&Vrm_RawBatAdValue[index][0],BattCfgPrt->DebounceCnt);
        CutVolt = CutAdc * BattCfgPrt->kParameter + BattCfgPrt->offset;
        Vrm_BattVoltVal[index] = CutVolt;

        if(MiniVolt > CutVolt)
        {
            MiniVolt = CutVolt;
        }

        if(MaxVolt < CutVolt)
        {
            MaxVolt = CutVolt;
        }

        BattCfgPrt++;
    }


    if((MaxVolt - MiniVolt) <= 1500u)
    {
        Vrm_SysVoltVal = (MaxVolt + MiniVolt)/2;
    }
    else
    {
        Vrm_SysVoltVal = MaxVolt;
    }
}
uint16 Vrm_GetSystemVoltage(void)
{
    return Vrm_SysVoltVal;
}

uint16 Vrm_GetBattVoltage(uint8 BattChannelId)
{
    uint16 Voltage;
    if(BattChannelId < VRM_INPUT_BATTRAY_CHANNEL_NUM)
    {
        Voltage = Vrm_BattVoltVal[BattChannelId];
    }
    else 
    {
        Voltage = 0u;
    }

    return Voltage;
}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
static uint16 Vrm_InputDebounce( uint16 inputValue, uint16 * debounceBuffer, uint8 debounceTime )
{
    uint32  sum;
    uint16* tmpPtr;
    uint16  ret;
    uint16  max;
    uint16  min;
    uint8   i;

    if(debounceTime == 0u)
    {
        /* if debounce time is 0 or 1, output is input everytime.  */
        ret = inputValue;
    }
    else 
    {
        if(debounceTime == 1u)
        {
            /* if debounce time is 2, output is average value of current input and last time input.  */
            sum              = (uint32)(*debounceBuffer) + (uint32)inputValue;
            ret              = (uint16)(sum >> 1);
        }
        else
        {
            /* The maximum of debounce time is DEBOUNCE_VRM_TIME_MAX */
            if(debounceTime > DEBOUNCE_VRM_TIME_MAX)
            {
                debounceTime  = DEBOUNCE_VRM_TIME_MAX;                        /* PRQA S 1338 */
            }

            /* if debounce time is 2 or up 2. */
            debounceTime      = debounceTime - 1u;                          /* PRQA S 1338 */
            tmpPtr             = debounceBuffer + debounceTime;             /* PRQA S 0488 */

            /* First remove maximum and minimum value. Then get the average value.  */
            if( inputValue > *tmpPtr )
            {
                max          = inputValue;
                min          = *tmpPtr;
            }
            else
            {
                max          = *tmpPtr;
                min          = inputValue;
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

            if( sum > 0xFFFFu)
            {
                ret          = 0xFFFFu;
            }
            else
            {
                ret          = (uint16)sum;
            }
        }

        /* save current input unitl next time calculation. */
        *debounceBuffer        = inputValue; 
    }

    return(ret);
}

