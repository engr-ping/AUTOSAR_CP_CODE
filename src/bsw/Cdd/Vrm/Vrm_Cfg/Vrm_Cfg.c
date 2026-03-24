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
#include "VRM_Cfg.h"

#if (VRM_INTERCEPT_OUTPUT_QUERY != 0U)
//----------------------------------------------------------------------------
/* 
FALSE:  output channel can be vrm intercept,no matter output has been on or off, default  
TRUE:   output channel can't be vrm intercept,when output has been enabled 
*/ 
//----------------------------------------------------------------------------
const boolean VRM_InterceptControlOnCloseArray[VRM_PID_SIZE] = 
{
    FALSE,    /*DUMMY*/
    FALSE,    /*OPH01*/


};

//----------------------------------------------------------------------------
/* 
detail all VRM intercept output status index
*/ 
//----------------------------------------------------------------------------

#endif
//----------------------------------------------------------------------------
/* 
FALSE:  channel be closed ,when  vrm intercept, default
TRUE:   channel be opened ,when  vrm intercept 
*/ 
//----------------------------------------------------------------------------
const boolean VRM_InterceptStateArray[VRM_PID_SIZE] = 
{
    FALSE,    /*DUMMY*/


    FALSE     /*ODL31*/
};
    
//----------------------------------------------------------------------------
/* 
chose channel intercept type ,VRM_STATE_TYPE_A_1....VRM_STATETYPES_A_n
note: only choose type A
*/ 
//----------------------------------------------------------------------------
const Vrm_StateType_e VRM_InterceptStateTypeArray[VRM_PID_SIZE] =
{
    VRM_STATE_TYPE_NO_MONITOR, 


    VRM_STATE_TYPE_NO_MONITOR     /*ODL31*/
};



const Vrm_VoltageChannel_t Vrm_PupChannelCfg[VRM_PUP_CHANNEL_SIZE] =
{
    /* kParameter,AdcIfChannel,battery*/
    {VRM_PUP1_COV2VOL_PARA,VRM_GET_AD_PUP1,0,0},  /*PUP1*/
    {VRM_PUP2_COV2VOL_PARA,VRM_GET_AD_PUP2,0,0},  /*PUP2*/
    {VRM_PUP3_COV2VOL_PARA,VRM_GET_AD_PUP3,0,0}   /*PUP3*/
};


const Vrm_VoltageChannel_t Vrm_BattChannelCfg[VRM_INPUT_BATTRAY_CHANNEL_NUM] =
{
    /* kParameter,AdcIfChannel,battery*/
    {VRM_PUP1_COV2VOL_PARA,VRM_GET_AD_PUP1,0,VRM_BAT_DEBOUNCE_COUNT},  /*PUP1*/
    {VRM_PUP2_COV2VOL_PARA,VRM_GET_AD_PUP2,0,VRM_BAT_DEBOUNCE_COUNT},  /*PUP2*/
    {VRM_PUP3_COV2VOL_PARA,VRM_GET_AD_PUP3,0,VRM_BAT_DEBOUNCE_COUNT}   /*PUP3*/
};

//----------------------------------------------------------------------------
/* flow type_A Parameter */ 
//----------------------------------------------------------------------------
#if (VRM_STATEFLOW_TYPE_A_NUM == 3)
const uint16 cVRM_au16LowThresholdFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_LOW_THRESHOLD_TYPE_A_1,   
    VRM_LOW_THRESHOLD_TYPE_A_2, 
    VRM_LOW_THRESHOLD_TYPE_A_3
};

const uint16 cVRM_au16HighThresholdFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_HIGH_THRESHOLD_TYPE_A_1, 
    VRM_HIGH_THRESHOLD_TYPE_A_2, 
    VRM_HIGH_THRESHOLD_TYPE_A_3
};

const uint16 cVRM_au16LowHystFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_LOW_HYST_TYPE_A_1, 
    VRM_LOW_HYST_TYPE_A_2,      
    VRM_LOW_HYST_TYPE_A_3
};

const uint16 cVRM_au16HighHystFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_HIGH_HYST_TYPE_A_1, 
    VRM_HIGH_HYST_TYPE_A_2,     
    VRM_HIGH_HYST_TYPE_A_3
};

const uint16 cVRM_au16N2LTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_N2LTIME_TYPE_A_1, 
    VRM_N2LTIME_TYPE_A_2,       
    VRM_N2LTIME_TYPE_A_3
};

const uint16 cVRM_au16L2UTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_L2UTIME_TYPE_A_1,  
    VRM_L2UTIME_TYPE_A_2,        
    VRM_L2UTIME_TYPE_A_3
};

const uint16 cVRM_au16L2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_L2NTIME_TYPE_A_1,      
    VRM_L2NTIME_TYPE_A_2, 
    VRM_L2NTIME_TYPE_A_3
};

const uint16 cVRM_au16H2OTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_H2OTIME_TYPE_A_1, 
    VRM_H2OTIME_TYPE_A_2, 
    VRM_H2OTIME_TYPE_A_3
};

const uint16 cVRM_au16N2HTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_N2HTIME_TYPE_A_1,
    VRM_N2HTIME_TYPE_A_2,        
    VRM_N2HTIME_TYPE_A_3
};

const uint16 cVRM_au16H2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_H2NTIME_TYPE_A_1,
    VRM_H2NTIME_TYPE_A_2,
    VRM_H2NTIME_TYPE_A_3
};

const uint16 cVRM_au16U2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_U2NTIME_TYPE_A_1,
    VRM_U2NTIME_TYPE_A_2,        
    VRM_U2NTIME_TYPE_A_3
};

const uint16 cVRM_au16O2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_O2NTIME_TYPE_A_1,
    VRM_O2NTIME_TYPE_A_2,
    VRM_O2NTIME_TYPE_A_3
};
#endif

//----------------------------------------------------------------------------
/* flow type_B Parameter */ 
//---------------------------------------------------------------------------- 
#if (VRM_STATEFLOW_TYPE_B_NUM == 2)
const uint16 cVRM_au16UnderThresholdFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_UNDER_THRESHOLD_TYPE_B_1,   
    VRM_UNDER_THRESHOLD_TYPE_B_2
};

const uint16 cVRM_au16OverThresholdFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_OVER_THRESHOLD_TYPE_B_1, 
    VRM_OVER_THRESHOLD_TYPE_B_2
};

const uint16 cVRM_au16LowHystFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_LOW_HYST_TYPE_B_1,      
    VRM_LOW_HYST_TYPE_B_2
};

const uint16 cVRM_au16HighHystFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_HIGH_HYST_TYPE_B_1,   
    VRM_HIGH_HYST_TYPE_B_2
};

const uint16 cVRM_au16U2NTimeFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_U2NTIME_TYPE_B_1,     
    VRM_U2NTIME_TYPE_B_2
};

const uint16 cVRM_au16O2NTimeFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_O2NTIME_TYPE_B_1,
    VRM_O2NTIME_TYPE_B_2
};
#endif

//----------------------------------------------------------------------------
/* flow type_C Parameter */ 
//---------------------------------------------------------------------------- 
#if (VRM_STATEFLOW_TYPE_C_NUM == 1)
const uint16 cVRM_au16LowThresholdFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_LOW_THRESHOLD_TYPE_C_1
};

const uint16 cVRM_au16HighThresholdFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{    
    VRM_HIGH_THRESHOLD_TYPE_C_1
};

const uint16 cVRM_au16LowHystFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_LOW_HYST_TYPE_C_1
};

const uint16 cVRM_au16HighHystFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_HIGH_HYST_TYPE_C_1
};

const uint16 cVRM_au16N2LTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_N2LTIME_TYPE_C_1
};

const uint16 cVRM_au16L2UTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{   
    VRM_L2UTIME_TYPE_C_1
};

const uint16 cVRM_au16L2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_L2NTIME_TYPE_C_1
};

const uint16 cVRM_au16H2OTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_H2OTIME_TYPE_C_1
};

const uint16 cVRM_au16N2HTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_N2HTIME_TYPE_C_1
};

const uint16 cVRM_au16H2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_H2NTIME_TYPE_C_1
};

const uint16 cVRM_au16U2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_U2NTIME_TYPE_C_1
};

const uint16 cVRM_au16O2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_O2NTIME_TYPE_C_1
};
#endif

//----------------------------------------------------------------------------
/* flow type_D DTC  Parameter */ 
//---------------------------------------------------------------------------- 
#if (VRM_DTC_TYPE_D_NUM == 3)
const uint16 cVRM_au16LowThresholdFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_LOW_THRESHOLD_DTC_TYPE1,  
    VRM_LOW_THRESHOLD_DTC_TYPE2,  
    VRM_LOW_THRESHOLD_DTC_TYPE3
};

const uint16 cVRM_au16HighThresholdFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_HIGH_THRESHOLD_DTC_TYPE1, 
    VRM_HIGH_THRESHOLD_DTC_TYPE2, 
    VRM_HIGH_THRESHOLD_DTC_TYPE3
};

const uint16 cVRM_au16LowHystFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_LOW_HYST_DTC_TYPE1, 
    VRM_LOW_HYST_DTC_TYPE2,       
    VRM_LOW_HYST_DTC_TYPE3
};
const uint16 cVRM_au16HighHystFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_HIGH_HYST_DTC_TYPE1, 
    VRM_HIGH_HYST_DTC_TYPE2,     
    VRM_HIGH_HYST_DTC_TYPE3
};

const uint16 cVRM_au16N2LTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_N2LTIME_DTC_TYPE1, 
    VRM_N2LTIME_DTC_TYPE2,       
    VRM_N2LTIME_DTC_TYPE3
};

const uint16 cVRM_au16L2UTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_L2UTIME_DTC_TYPE1,  
    VRM_L2UTIME_DTC_TYPE2,        
    VRM_L2UTIME_DTC_TYPE3
};

const uint16 cVRM_au16L2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_L2NTIME_DTC_TYPE1,      
    VRM_L2NTIME_DTC_TYPE2, 
    VRM_L2NTIME_DTC_TYPE3
};

const uint16 cVRM_au16H2OTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_H2OTIME_DTC_TYPE1, 
    VRM_H2OTIME_DTC_TYPE2, 
    VRM_H2OTIME_DTC_TYPE3
};

const uint16 cVRM_au16N2HTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_N2HTIME_DTC_TYPE1,
    VRM_N2HTIME_DTC_TYPE2,        
    VRM_N2HTIME_DTC_TYPE3
};

const uint16 cVRM_au16H2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_H2NTIME_DTC_TYPE1,
    VRM_H2NTIME_DTC_TYPE2,
    VRM_H2NTIME_DTC_TYPE3
};

const uint16 cVRM_au16U2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_U2NTIME_DTC_TYPE1,
    VRM_U2NTIME_DTC_TYPE2,        
    VRM_U2NTIME_DTC_TYPE3
};

const uint16 cVRM_au16O2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_O2NTIME_DTC_TYPE1,
    VRM_O2NTIME_DTC_TYPE2,
    VRM_O2NTIME_DTC_TYPE3
};
#endif

