/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: IoHwAb_PwmOut                                                                                             
*  Content:   PwmOut module of IoHwAb
*  Category: IoHwAb PwmOut
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */
#include "IoHwAb_PwmOut.h"
#include "IoHwAb_PwmOut_Cfg.h"
#include "VRM.h"
#include "Pfm.h"

/* Exported Variables Definitions */
boolean IoHwAb_PwmOut_poDiagIntEn[IOHWAB_PO_CHN_MAX];
uint16  IoHwAb_PwmOut_poDiagIntSt[IOHWAB_PO_CHN_MAX];
uint16  IoHwAb_PwmOut_poOld[IOHWAB_PO_CHN_MAX];
static uint16 IoHwAb_PwmOut_signalSts[IOHWAB_PO_CHN_MAX];


/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/

/****************************************************************
 process: IoHwAb_PwmOut_SignalProcess
 purpose: Write PWM output channel with signal processing
 ****************************************************************/
uint16 IoHwAb_PwmOut_SignalProcess(uint16 channelId, uint16 dutyCycle)
{
     uint16 ret;
     static uint8 sPwmOutInrushCount[IOHWAB_PWMO_CHN_MAX];
     uint16 tmpEnDiagDuty;
     IoHwAb_PwmOut_ChannelConfig_t* channelConfigPtr = &IoHwAb_PwmOut_ChannelConfig[channelId];
     uint8 pfmFid = channelConfigPtr->pfmFid;
     uint8 vrmFid = channelConfigPtr->vrmFid;
     uint8 diagSrvId = channelConfigPtr->dsid;
     uint8 inrushId = channelConfigPtr->irid;
     uint8 inrushDelayTime = channelConfigPtr->inrushDelayTime;
     uint16 enDiagDuty = channelConfigPtr->enDiagDuty;

    tmpEnDiagDuty = (uint16)(enDiagDuty * 256u / 100u);

    if(gPFM_abInterceptEnable[pfmFid] != (boolean)FALSE)
    {
        ret = cPFM_abInterceptState[pfmFid];
    }
    else if(gVRM_abInterceptEnable[vrmFid] != (boolean)FALSE)
    {
        ret = Vrm_abInterceptState[vrmFid];
    }
    else if(IoHwAb_PwmOut_poDiagIntEn[diagSrvId] != (boolean)FALSE)
    {
        ret = IoHwAb_PwmOut_poDiagIntSt[diagSrvId];
    }
    else
    {
        ret = dutyCycle;
    }

    if(ret == 0u)//pwm output duty is 0
    {
        //Pfm_EnableDiagnosic(pfmFid, (boolean)FALSE);
        sPwmOutInrushCount[inrushId] = 0u;
    }
    else if(inrushDelayTime != 0u)
    {
        if( (ret >= tmpEnDiagDuty) && (IoHwAb_PwmOut_poOld[inrushId] < tmpEnDiagDuty) )
        {
            Pfm_EnableDiagnosic(pfmFid, (boolean)FALSE);
            sPwmOutInrushCount[inrushId] = 0u;
        }
        else if((ret >= tmpEnDiagDuty))
        {
            if( sPwmOutInrushCount[inrushId] < inrushDelayTime )
            {
                sPwmOutInrushCount[inrushId]++;
            }
            else
            {
                Pfm_EnableDiagnosic(pfmFid, (boolean)TRUE);
            }
        }
        else
        {
            Pfm_EnableDiagnosic(pfmFid, (boolean)FALSE);
            sPwmOutInrushCount[inrushId] = 0u;
        }
    }
    else
    {
        Pfm_EnableDiagnosic(pfmFid, (boolean)TRUE);
        sPwmOutInrushCount[inrushId] = 0u;
    }

    IoHwAb_PwmOut_poOld[inrushId] = ret;
    
    return ret;
}


void IoHwAb_PwmOut_SetDutyCycle(uint16 channelId, uint16 dutyCycle)
{
    uint16 tmp;

    IoHwAb_PwmOut_ChannelConfig_t* channelConfigPtr = &IoHwAb_PwmOut_ChannelConfig[channelId];
    tmp = IoHwAb_PwmOut_SignalProcess(channelId, dutyCycle);
    PwmIf_SetDutyCycle(channelConfigPtr->pwmIfChannelId, tmp);
    IoHwAb_PwmOut_signalSts[channelId] = tmp;             
}

/****************************************************************
 process: IoHwAb_PwmOut_SetChannelDiagInt
 purpose: Set diagnostic intervention for PWM output channel
 ****************************************************************/
void IoHwAb_PwmOut_SetChannelDiagInt(uint16 channelId, uint16 duty)
{
    IoHwAb_PwmOut_poDiagIntEn[channelId] = (boolean)TRUE;
    IoHwAb_PwmOut_poDiagIntSt[channelId] = duty;
}

/****************************************************************
 process: IoHwAb_PwmOut_ClearChannelDiagInt
 purpose: Clear diagnostic intervention for PWM output channel
 ****************************************************************/
void IoHwAb_PwmOut_ClearChannelDiagInt(uint16 channelId)
{
    IoHwAb_PwmOut_poDiagIntEn[channelId] = (boolean)FALSE;
}

/****************************************************************
 process: IoHwAb_PwmOut_Init
 purpose: Initialize PWM output module
 ****************************************************************/
void IoHwAb_PwmOut_Init(void)
{
    uint8 i;
    (void)memset(IoHwAb_PwmOut_poDiagIntEn, 0u, sizeof(IoHwAb_PwmOut_poDiagIntEn));
    (void)memset(IoHwAb_PwmOut_poDiagIntSt, 0u, sizeof(IoHwAb_PwmOut_poDiagIntSt));
    (void)memset(IoHwAb_PwmOut_poOld, 0u, sizeof(IoHwAb_PwmOut_poOld));
}