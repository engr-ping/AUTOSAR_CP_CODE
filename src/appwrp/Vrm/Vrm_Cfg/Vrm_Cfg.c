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
#include "IoHwAb_DigitalOutput.h"
#include "IoHwAb_PwmOutput.h"


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
const uint8 * VRM_OutputStatePointerArray[VRM_PID_SIZE] = 
{
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_DUMMY]),       /* VRM_PID_DUMMY */
   
};

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
const VRM_StateType VRM_InterceptStateTypeArray[VRM_PID_SIZE] =
{
    VRM_STATE_TYPE_NO_MONITOR, 


    VRM_STATE_TYPE_NO_MONITOR     /*ODL31*/
};


//----------------------------------------------------------------------------
/* flow type_A Parameter */ 
//----------------------------------------------------------------------------
#if (VRM_STATEFLOW_TYPE_A_NUM == 3)
const uint16 VRM_LowThresholdTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_LOW_THRESHOLD_TYPE_A_1,   
    VRM_LOW_THRESHOLD_TYPE_A_2, 
    VRM_LOW_THRESHOLD_TYPE_A_3
};

const uint16 VRM_HighThresholdTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_HIGH_THRESHOLD_TYPE_A_1, 
    VRM_HIGH_THRESHOLD_TYPE_A_2, 
    VRM_HIGH_THRESHOLD_TYPE_A_3
};

const uint16 VRM_LowHystTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_LOW_HYST_TYPE_A_1, 
    VRM_LOW_HYST_TYPE_A_2,      
    VRM_LOW_HYST_TYPE_A_3
};

const uint16 VRM_HighHystTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_HIGH_HYST_TYPE_A_1, 
    VRM_HIGH_HYST_TYPE_A_2,     
    VRM_HIGH_HYST_TYPE_A_3
};

const uint16 VRM_N2LTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_N2LTIME_TYPE_A_1, 
    VRM_N2LTIME_TYPE_A_2,       
    VRM_N2LTIME_TYPE_A_3
};

const uint16 VRM_L2UTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_L2UTIME_TYPE_A_1,  
    VRM_L2UTIME_TYPE_A_2,        
    VRM_L2UTIME_TYPE_A_3
};

const uint16 VRM_L2NTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_L2NTIME_TYPE_A_1,      
    VRM_L2NTIME_TYPE_A_2, 
    VRM_L2NTIME_TYPE_A_3
};

const uint16 VRM_H2OTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_H2OTIME_TYPE_A_1, 
    VRM_H2OTIME_TYPE_A_2, 
    VRM_H2OTIME_TYPE_A_3
};

const uint16 VRM_N2HTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_N2HTIME_TYPE_A_1,
    VRM_N2HTIME_TYPE_A_2,        
    VRM_N2HTIME_TYPE_A_3
};

const uint16 VRM_H2NTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_H2NTIME_TYPE_A_1,
    VRM_H2NTIME_TYPE_A_2,
    VRM_H2NTIME_TYPE_A_3
};

const uint16 VRM_U2NTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_U2NTIME_TYPE_A_1,
    VRM_U2NTIME_TYPE_A_2,        
    VRM_U2NTIME_TYPE_A_3
};

const uint16 VRM_O2NTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
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
const uint16 VRM_UnderThresholdTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_UNDER_THRESHOLD_TYPE_B_1,   
    VRM_UNDER_THRESHOLD_TYPE_B_2
};

const uint16 VRM_OverThresholdTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_OVER_THRESHOLD_TYPE_B_1, 
    VRM_OVER_THRESHOLD_TYPE_B_2
};

const uint16 VRM_LowHystTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_LOW_HYST_TYPE_B_1,      
    VRM_LOW_HYST_TYPE_B_2
};

const uint16 VRM_HighHystTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_HIGH_HYST_TYPE_B_1,   
    VRM_HIGH_HYST_TYPE_B_2
};

const uint16 VRM_U2NTimeTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_U2NTIME_TYPE_B_1,     
    VRM_U2NTIME_TYPE_B_2
};

const uint16 VRM_O2NTimeTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_O2NTIME_TYPE_B_1,
    VRM_O2NTIME_TYPE_B_2
};
#endif

//----------------------------------------------------------------------------
/* flow type_C Parameter */ 
//---------------------------------------------------------------------------- 
#if (VRM_STATEFLOW_TYPE_C_NUM == 1)
const uint16 VRM_LowThresholdTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_LOW_THRESHOLD_TYPE_C_1
};

const uint16 VRM_HighThresholdTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{    
    VRM_HIGH_THRESHOLD_TYPE_C_1
};

const uint16 VRM_LowHystTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_LOW_HYST_TYPE_C_1
};

const uint16 VRM_HighHystTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_HIGH_HYST_TYPE_C_1
};

const uint16 VRM_N2LTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_N2LTIME_TYPE_C_1
};

const uint16 VRM_L2UTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{   
    VRM_L2UTIME_TYPE_C_1
};

const uint16 VRM_L2NTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_L2NTIME_TYPE_C_1
};

const uint16 VRM_H2OTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_H2OTIME_TYPE_C_1
};

const uint16 VRM_N2HTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_N2HTIME_TYPE_C_1
};

const uint16 VRM_H2NTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_H2NTIME_TYPE_C_1
};

const uint16 VRM_U2NTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_U2NTIME_TYPE_C_1
};

const uint16 VRM_O2NTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_O2NTIME_TYPE_C_1
};
#endif

//----------------------------------------------------------------------------
/* flow type_D DTC  Parameter */ 
//---------------------------------------------------------------------------- 
#if (VRM_DTC_TYPE_D_NUM == 3)
const uint16 VRM_LowThresholdTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_LOW_THRESHOLD_DTC_TYPE1,  
    VRM_LOW_THRESHOLD_DTC_TYPE2,  
    VRM_LOW_THRESHOLD_DTC_TYPE3
};

const uint16 VRM_HighThresholdTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_HIGH_THRESHOLD_DTC_TYPE1, 
    VRM_HIGH_THRESHOLD_DTC_TYPE2, 
    VRM_HIGH_THRESHOLD_DTC_TYPE3
};

const uint16 VRM_LowHystTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_LOW_HYST_DTC_TYPE1, 
    VRM_LOW_HYST_DTC_TYPE2,       
    VRM_LOW_HYST_DTC_TYPE3
};
const uint16 VRM_HighHystTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_HIGH_HYST_DTC_TYPE1, 
    VRM_HIGH_HYST_DTC_TYPE2,     
    VRM_HIGH_HYST_DTC_TYPE3
};

const uint16 VRM_N2LTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_N2LTIME_DTC_TYPE1, 
    VRM_N2LTIME_DTC_TYPE2,       
    VRM_N2LTIME_DTC_TYPE3
};

const uint16 VRM_L2UTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_L2UTIME_DTC_TYPE1,  
    VRM_L2UTIME_DTC_TYPE2,        
    VRM_L2UTIME_DTC_TYPE3
};

const uint16 VRM_L2NTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_L2NTIME_DTC_TYPE1,      
    VRM_L2NTIME_DTC_TYPE2, 
    VRM_L2NTIME_DTC_TYPE3
};

const uint16 VRM_H2OTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_H2OTIME_DTC_TYPE1, 
    VRM_H2OTIME_DTC_TYPE2, 
    VRM_H2OTIME_DTC_TYPE3
};

const uint16 VRM_N2HTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_N2HTIME_DTC_TYPE1,
    VRM_N2HTIME_DTC_TYPE2,        
    VRM_N2HTIME_DTC_TYPE3
};

const uint16 VRM_H2NTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_H2NTIME_DTC_TYPE1,
    VRM_H2NTIME_DTC_TYPE2,
    VRM_H2NTIME_DTC_TYPE3
};

const uint16 VRM_U2NTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_U2NTIME_DTC_TYPE1,
    VRM_U2NTIME_DTC_TYPE2,        
    VRM_U2NTIME_DTC_TYPE3
};

const uint16 VRM_O2NTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_O2NTIME_DTC_TYPE1,
    VRM_O2NTIME_DTC_TYPE2,
    VRM_O2NTIME_DTC_TYPE3
};
#endif

