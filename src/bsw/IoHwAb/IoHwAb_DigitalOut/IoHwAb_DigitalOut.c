/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: IoHwAb_DigitalOut                                                                                             
*  Content:   DigitalOut module of IoHwAb
*  Category: IoHwAb DigitalOut
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.09    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/
/* Include Headerfiles  */
#include "IoHwAb_DigitalOut.h"
#include "IoHwAb_DigitalOut_Cfg.h"
#include "VRM.h"
#include "Pfm.h"

/* Exported Variables Definitions */
boolean IoHwAb_DigitalOut_doSignalOld[IOHWAB_DO_CHN_MAX];
boolean IoHwAb_DigitalOut_doDiagIntEn[IOHWAB_DO_CHN_MAX];
boolean IoHwAb_DigitalOut_doDiagIntSt[IOHWAB_DO_CHN_MAX];
static boolean IoHwAb_DigitalOut_signalSts[IOHWAB_DO_CHN_MAX];
/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/

/****************************************************************
 process: IoHwAb_DigitalOut_SignalProcess
 purpose: Write digital output channel with signal processing
 ****************************************************************/
boolean IoHwAb_DigitalOut_SignalProcess(uint16 channelId, boolean outputRequest)
{
    boolean ret;
    static uint8 sDoInrushCount[IOHWAB_DO_CHN_MAX];
    IoHwAb_DigitalOut_ChannelConfig_t* channelConfigPtr = &IoHwAb_Do_ChannelConfig[channelId];
    boolean lowActive = channelConfigPtr->invert;
    uint8 pfmFid = channelConfigPtr->pfmFid;    
    uint8 vrmFid = channelConfigPtr->vrmFid;    
    uint8 diagSrvId = channelConfigPtr->dsid;    
    uint8 inrushId = channelConfigPtr->irid;    
    uint8 inrushDelayTime = channelConfigPtr->inrushDelay;


    /*judge whether pfm need to take over the output*/
    if(gPFM_abInterceptEnable[pfmFid] != (boolean)FALSE)
    {
        ret = cPFM_abInterceptState[pfmFid];
    }
    else if(gVRM_abInterceptEnable[vrmFid] != (boolean)FALSE)
    {
        ret = Vrm_abInterceptState[vrmFid];
    } 
    else if(IoHwAb_DigitalOut_doDiagIntEn[diagSrvId] != (boolean)FALSE)
    {
        /*judge whether diagnostic want to take over the output*/
        ret = IoHwAb_DigitalOut_doDiagIntSt[diagSrvId];
    }
    else
    {
        ret = outputRequest;
    }

    /*Whether this output need to do in rush current delay*/
    if(inrushDelayTime != 0u)
    {
        /*if the channel output is change from close to open, we should disable
          the pfm diagnostic*/
        if((ret != (boolean)FALSE) && (IoHwAb_DigitalOut_doSignalOld[inrushId] == (boolean)FALSE) )
        {
            Pfm_EnableDiagnosic(pfmFid, (boolean)FALSE);
            sDoInrushCount[inrushId] = 0U;
        }
        else
        {
            if(sDoInrushCount[inrushId] < inrushDelayTime )
            {
                sDoInrushCount[inrushId]++;
            }
            else
            {    /*In crash count is done, we shall Reenable the PFM diagnostic*/
                Pfm_EnableDiagnosic(pfmFid, (boolean)TRUE);
            }
        }
    }

    IoHwAb_DigitalOut_doSignalOld[inrushId] = ret;

    ret = ret ^ lowActive;
    
    
    return ret;
}

/****************************************************************
 process: IoHwAb_DigitalOut_WriteChannel
 purpose: Write digital output channel status
 ****************************************************************/
Std_ReturnType IoHwAb_DigitalOut_WriteChannel(uint16 channelId, boolean ret)
{
    boolean tmp;
    IoHwAb_DigitalOut_ChannelConfig_t* channelConfigPtr = &IoHwAb_Do_ChannelConfig[channelId];
    tmp = IoHwAb_DigitalOut_SignalProcess(channelId, ret);
    IoHwAb_DigitalOut_signalSts[channelId] = tmp; 
    
    return DioIf_WriteChannel(channelConfigPtr->dioIfChannelId, tmp);
}

/****************************************************************
 process: IoHwAb_DigitalOut_SetChannelDiagInt
 purpose: Set diagnostic intervention for channel
 ****************************************************************/
void IoHwAb_DigitalOut_SetChannelDiagInt(uint16 channelId, boolean st)
{
    IoHwAb_DigitalOut_doDiagIntEn[channelId] = (boolean)TRUE;
    IoHwAb_DigitalOut_doDiagIntSt[channelId] = st;
}

/****************************************************************
 process: IoHwAb_DigitalOut_ClearChannelDiagInt
 purpose: Clear diagnostic intervention for channel
 ****************************************************************/
void IoHwAb_DigitalOut_ClearChannelDiagInt(uint16 channelId)
{
    IoHwAb_DigitalOut_doDiagIntEn[channelId] = (boolean)FALSE;
}

/****************************************************************
 process: IoHwAb_DigitalOut_Init
 purpose: Initialize digital output module
 ****************************************************************/
void IoHwAb_DigitalOut_Init(void)
{
    uint8 i;
    (void)memset(IoHwAb_DigitalOut_doSignalOld, 0u, sizeof(IoHwAb_DigitalOut_doSignalOld));
    (void)memset(IoHwAb_DigitalOut_doDiagIntEn, 0u, sizeof(IoHwAb_DigitalOut_doDiagIntEn));
    (void)memset(IoHwAb_DigitalOut_doDiagIntSt, 0u, sizeof(IoHwAb_DigitalOut_doDiagIntSt));
}