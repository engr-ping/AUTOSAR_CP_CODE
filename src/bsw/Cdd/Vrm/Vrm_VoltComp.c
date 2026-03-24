/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Vrm                                                                                             
*  Content:  Voltage Range Management for Voltage Compensate
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */
#include "Vrm_VoltComp.h"

/* Macros Local To This Module                                          */
/* ===========================                                          */

/* Local Module RAM-Definitions (attribute static)                      */
/* ===========================================                          */
/* Definition of variables only local to this module. That is, not to   */
/* be exported to other modules.                                        */

/* Exported Variables Definitions */
/* ============================================================         */


static uint16 Vrm_PupVoltage[VRM_PUP_CHANNEL_SIZE];
extern uint16 AdcIf_ReadChannel(uint16 ChannelId);
/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/
#define MAXUINT16       (0xffff)

/*****************    Local Functions Declaration    ******************/

uint16 Vrm_Div_u32u32_u16(uint32 x_u32,uint32 y_u32)
{
/* Note: This C Code is generated (Cz = Ax / Ax) */
    uint16 res;
    uint32 temp;
    if (y_u32 == 0)
    {
        /* saturated to the max value */
        res = MAXUINT16;
    }
    else
    {
        /* temp variable to hold intermediate result */
        temp = x_u32/y_u32;
        /* handle overflow */
        if (temp > MAXUINT16)
        {
            res = MAXUINT16;
        }
        /* otherwise just get the result */
        else
        {
            res = (uint16)temp;
        }
    }
    return res;

}



/****************************************************************
 process: VRM_vCompensateFactorUpdate
 purpose: cal K value according to VPUP1 voltage 
 ****************************************************************/
uint16 VRM_CompensateFactorUpdatePup(uint8 PupChannel)
{

    const Vrm_VoltageChannel_t * PupChnPrt = &Vrm_PupChannelCfg[PupChannel];
    Vrm_PupVoltage[PupChannel] = Vrm_Div_u32u32_u16(PupChnPrt->kParameter,(uint16)AdcIf_ReadChannel(PupChnPrt->AdcIfChannel))+PupChnPrt->offset;

    return Vrm_PupVoltage[PupChannel];
}

/****************************************************************
 process: VRM_GetPup1CompensationFactor
 purpose: Get K value according to VPUP1 voltage 
 ****************************************************************/
uint16 VRM_GetPupCompensationFactor(uint8 PupChannel,uint16 pupFvAd)
{
    uint16 kvPup1;
    Vrm_VoltageChannel_t * PupChnPrt = &Vrm_PupChannelCfg[PupChannel];
    kvPup1 =  Vrm_Div_u32u32_u16(PupChnPrt->kParameter, pupFvAd);
	return kvPup1;
}


/****************************************************************
 process: VRM_CompensateVoltage
 purpose: according to advalue and Compensate factor, cal new advalue 
 ****************************************************************/
uint16 VRM_CompensateVoltage( uint16 adValue, uint16 factor )
{
    uint32 tmp;
    uint16 rtn;

    tmp = (((uint32)adValue * factor)) / VRM_COMPENSATE_PRECISION;

    if( tmp > VRM_MAX_AD_HEX)
    {
        rtn = VRM_MAX_AD_HEX;
    }
    else
    {
        rtn = (uint16)tmp;
    }

    return(rtn);
}


/****************************************************************
 process: VRM_GetVoltageCompensation
 purpose: for different CompensateType,cal Compensate value
 ****************************************************************/
uint16 Vrm_GetVoltageCompensation( uint16 adValue, uint8 compensateType )
{
    uint16 ret;

    ret = VRM_CompensateVoltage(adValue,Vrm_PupVoltage[compensateType - 1]);   // type = channel + 1

    return ret;
}

