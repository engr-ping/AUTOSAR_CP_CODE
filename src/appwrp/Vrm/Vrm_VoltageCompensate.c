/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Pfm                                                                                             
*  Content:  Power device fault management module source file.
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2025.12.30    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */
#include "VRM_VoltageCompensate.h"
#include "Lib_Srv.h"

/* Macros Local To This Module                                          */
/* ===========================                                          */

/* Local Module RAM-Definitions (attribute static)                      */
/* ===========================================                          */
/* Definition of variables only local to this module. That is, not to   */
/* be exported to other modules.                                        */

/* Exported Variables Definitions */
/* ============================================================         */
uint16 VRM_kvPup1CompensationFactor;              /* P1=0, P2=12288, P3=1, P4=0 */
uint16 VRM_kvPup2CompensationFactor;              /* P1=0, P2=12288, P3=1, P4=0 */
uint16 VRM_kvPup3CompensationFactor;              /* P1=0, P2=12288, P3=1, P4=0 */



/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/


/*****************    Local Functions Declaration    ******************/


/****************************************************************
 process: VRM_vCompensateFactorUpdate
 purpose: cal K value according to VPUP1 voltage 
 ****************************************************************/
void VRM_CompensateFactorUpdatePup1(void)
{
    VRM_kvPup1CompensationFactor = div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP1_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP1_R1 + VRM_PUP1_R2),(uint16)VRM_GET_AD_PUP1);
}

/****************************************************************
 process: VRM_GetPup1CompensationFactor
 purpose: Get K value according to VPUP1 voltage 
 ****************************************************************/
uint16 VRM_GetPup1CompensationFactor(uint16 pupFvAd)
{
    uint16 kvPup1;

    kvPup1 =  div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP1_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP1_R1 + VRM_PUP1_R2), pupFvAd);
	return kvPup1;
}


/****************************************************************
 process: VRM_vCompensateFactorUpdate
 purpose: cal K value according to VPUP2 voltage 
 ****************************************************************/
void VRM_CompensateFactorUpdatePup2(void)
{
    VRM_kvPup2CompensationFactor = div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP2_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP2_R1 + VRM_PUP2_R2), (uint16)VRM_GET_AD_PUP2);
}

/****************************************************************
 process: VRM_GetPup2CompensationFactor
 purpose: Get K value according to VPUP2 voltage 
 ****************************************************************/
uint16 VRM_GetPup2CompensationFactor(uint16 pupFvAd)
{
    uint16 kvPup2;

    kvPup2 =  div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP2_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP2_R1 + VRM_PUP2_R2), pupFvAd);
	return kvPup2;
}


/****************************************************************
 process: VRM_vCompensateFactorUpdate
 purpose: cal K value according to VPUP3 voltage 
 ****************************************************************/
void VRM_CompensateFactorUpdatePup3(void)
{
    VRM_kvPup3CompensationFactor = div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP3_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP3_R1 + VRM_PUP3_R2), (uint16)VRM_GET_AD_PUP3);
}

/****************************************************************
 process: VRM_GetPup3CompensationFactor
 purpose: Get K value according to VPUP3 voltage 
 ****************************************************************/
uint16 VRM_GetPup3CompensationFactor(uint16 pupFvAd)
{
    uint16 kvPup3;

    kvPup3 =  div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP3_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP3_R1 + VRM_PUP3_R2), pupFvAd);
	return kvPup3;
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
uint16 VRM_GetVoltageCompensation( uint16 adValue, uint8 compensateType )
{
    uint16 ret;

    if( compensateType == VRM_COMPENSATE_TYPE_PUP1 )
    {
        ret = VRM_u16GetVoltCompPup1(adValue);
    }
    else if( compensateType == VRM_COMPENSATE_TYPE_PUP2 )
    {
        ret = VRM_u16GetVoltCompPup2(adValue);
    }
	else if( compensateType == VRM_COMPENSATE_TYPE_PUP3 )
    {
        ret = VRM_u16GetVoltCompPup3(adValue);
    }
    else
    {
        ret = adValue;
    }
    
    return ret;
}

