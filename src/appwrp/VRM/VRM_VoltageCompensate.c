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
uint16 VRM_KVPup1CompensationFactor;              /* P1=0, P2=12288, P3=1, P4=0 */
uint16 VRM_KVPup2CompensationFactor;              /* P1=0, P2=12288, P3=1, P4=0 */
uint16 VRM_KVPup3CompensationFactor;              /* P1=0, P2=12288, P3=1, P4=0 */



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
    VRM_KVPup1CompensationFactor = div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP1_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP1_R1 + VRM_PUP1_R2),(uint16)VRM_GET_AD_PUP1);
}

/****************************************************************
 process: VRM_GetPup1CompensationFactor
 purpose: Get K value according to VPUP1 voltage 
 ****************************************************************/
uint16 VRM_GetPup1CompensationFactor(uint16 u16PupFvAd)
{
    uint16 u16KVPup1;

    u16KVPup1 =  div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP1_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP1_R1 + VRM_PUP1_R2), u16PupFvAd);
	return u16KVPup1;
}


/****************************************************************
 process: VRM_vCompensateFactorUpdate
 purpose: cal K value according to VPUP2 voltage 
 ****************************************************************/
void VRM_CompensateFactorUpdatePup2(void)
{
    VRM_KVPup2CompensationFactor = div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP2_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP2_R1 + VRM_PUP2_R2), (uint16)VRM_GET_AD_PUP2);
}

/****************************************************************
 process: VRM_GetPup2CompensationFactor
 purpose: Get K value according to VPUP2 voltage 
 ****************************************************************/
uint16 VRM_GetPup2CompensationFactor(uint16 u16PupFvAd)
{
    uint16 u16KVPup2;

    u16KVPup2 =  div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP2_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP2_R1 + VRM_PUP2_R2), u16PupFvAd);
	return u16KVPup2;
}


/****************************************************************
 process: VRM_vCompensateFactorUpdate
 purpose: cal K value according to VPUP3 voltage 
 ****************************************************************/
void VRM_CompensateFactorUpdatePup3(void)
{
    VRM_KVPup3CompensationFactor = div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP3_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP3_R1 + VRM_PUP3_R2), (uint16)VRM_GET_AD_PUP3);
}

/****************************************************************
 process: VRM_GetPup3CompensationFactor
 purpose: Get K value according to VPUP3 voltage 
 ****************************************************************/
uint16 VRM_GetPup3CompensationFactor(uint16 u16PupFvAd)
{
    uint16 u16KVPup3;

    u16KVPup3 =  div_U32U16_U16(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP3_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP3_R1 + VRM_PUP3_R2), u16PupFvAd);
	return u16KVPup3;
}


/****************************************************************
 process: VRM_CompensateVoltage
 purpose: according to advalue and Compensate factor, cal new advalue 
 ****************************************************************/
uint16 VRM_CompensateVoltage( uint16 AdValue, uint16 Factor )
{
    uint32 u32Tmp;
    uint16 u16Rtn;

    u32Tmp = (((uint32)AdValue * Factor)) / VRM_COMPENSATE_PRECISION;

    if( u32Tmp > VRM_MAX_AD_HEX)
    {
        u16Rtn = VRM_MAX_AD_HEX;
    }
    else
    {
        u16Rtn = (uint16)u32Tmp;
    }

    return(u16Rtn);
}


/****************************************************************
 process: VRM_GetVoltageCompensation
 purpose: for different CompensateType,cal Compensate value
 ****************************************************************/
uint16 VRM_GetVoltageCompensation( uint16 AdValue, uint8 CompensateType )
{
    uint16 u16Ret;

    if( CompensateType == VRM_COMPENSATE_TYPE_PUP1 )
    {
        u16Ret = VRM_u16GetVoltCompPup1(AdValue);
    }
    else if( CompensateType == VRM_COMPENSATE_TYPE_PUP2 )
    {
        u16Ret = VRM_u16GetVoltCompPup2(AdValue);
    }
	else if( CompensateType == VRM_COMPENSATE_TYPE_PUP3 )
    {
        u16Ret = VRM_u16GetVoltCompPup3(AdValue);
    }
    else
    {
        u16Ret = AdValue;
    }
    
    return u16Ret;
}

