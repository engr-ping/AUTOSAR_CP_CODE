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
#ifndef VRM_CFG_H
#define VRM_CFG_H

/* Include Headerfiles  */
/* ===================                                                  */
#include "IoHwAb_DigitalOutput_Cfg.h"
#include "AdcIf.h"
#include "PORT.h"
#include "DioIf.h"

/*
Type A : can control output channel status
config the num
*/
#define VRM_STATEFLOW_TYPE_A_NUM     (3U)
/*
Type A : output channel can be vrm intercept, whether query output has been on or off,
1: query output has been on or off
0: no query output has been on or off
*/
#define VRM_INTERCEPT_OUTPUT_QUERY   (1U)
/*
Type B : communication use this type
config the num
*/
#define VRM_STATEFLOW_TYPE_B_NUM     (2U)
/*
Type C : init state need be given by battery voltage,not like type A,and type B is normal
config the num
*/
#define VRM_STATEFLOW_TYPE_C_NUM     (1U)
/*
Type D : be used for BCM power DTC
config the num
*/
#define VRM_DTC_TYPE_D_NUM           (0U)

/* the following enum need be amended according to the types num */
typedef enum
{
   VRM_STATE_TYPE_A_1,
   VRM_STATE_TYPE_A_2,
   VRM_STATE_TYPE_A_3,
   VRM_STATE_TYPE_B_1,
   VRM_STATE_TYPE_B_2,
   VRM_STATE_TYPE_C_1,
   VRM_STATE_TYPE_NO_MONITOR
}Vrm_StateType;

/***********************    Global Type Definition    ************************/
typedef enum
{
    VRM_PID_DUMMY,

    VRM_PID_OPH01,
    VRM_PID_SIZE
} Vrm_PhysicalId_e;

/**************************    Macro Definitions    **************************/
#define VRM_FID_OPH01       (VRM_PID_OPH01)


#define VRM_FID_VREF03      (VRM_PID_DUMMY)

/***************************************************************************************************/
/************************** Battery Voltage Detect channel configuration  **************************/
/***************************************************************************************************/
/* INL, EXL, Harzard light power input feedback circuit cfg */
#define VRM_AD2VOL_R1_POW_CFG          (1000U)
#define VRM_AD2VOL_R2_POW_CFG          (215U)

#define VRM_AD2VOL_R1_POW              (5u*(VRM_AD2VOL_R1_POW_CFG+VRM_AD2VOL_R2_POW_CFG)*125u )
#define VRM_AD2VOL_R2_POW              (512u*VRM_AD2VOL_R2_POW_CFG)

#define VRM_DETA1                      (30u)     /* unit: AD */

#define VRM_BAT_DEBOUNCE_COUNT         (5u)      /* Bat voltage debounce cnt */
#define VRM_EXT1_DEBOUNCE_COUNT        (5u)      /* Ext1 voltage debounce cnt */
#define VRM_EXT2_DEBOUNCE_COUNT        (5u)      /* Ext2 voltage debounce cnt */

/* compensate transistor voltage drop, Compensate voltage: 100mV */
#define VRM_AD2VOL_COMPENSATE_POW      (100u)

/* Bat default voltage: 12000mV, during the inital debounce time, transfer the default voltage to RTE */
#define VRM_BAT_AD2VOL_DEFAULT_VAL     (12000u)
/* Ext1 default voltage: 12000mV, during the inital debounce time, transfer the default voltage to RTE */
#define VRM_EXT1_AD2VOL_DEFAULT_VAL    (12000u)
/* Ext2 default voltage: 12000mV, during the inital debounce time, transfer the default voltage to RTE */
#define VRM_EXT2_AD2VOL_DEFAULT_VAL    (12000u)


/* convert ad value to voltage, Uint mV, Accuracy：6mV */
#define VRM_CONVERT_AD2VOL_POW(AD)     (uint16)(((uint32)(AD) * VRM_AD2VOL_R1_POW / VRM_AD2VOL_R2_POW) + VRM_AD2VOL_COMPENSATE_POW)

/***************************************************************************************************/
/************************** VPUP related  ****************************************************/
/***************************************************************************************************/
#define VRM_BASIC_VOLTAGE              (12000u)    /* the basic voltage of compensation is 12,000 mV */
#define VRM_MAX_AD_HEX                 (4095u)     /* 12 bits AD convertor */

#define VRM_GET_AD_PUP1                ADCIF_GETRAW_V_PUP1_FV
#define VRM_PUP1_R1                    (1000u)
#define VRM_PUP1_R2                    (215u)

#define VRM_GET_AD_PUP2                ADCIF_GETRAW_V_PUP2_FV
#define VRM_PUP2_R1                    (1000u)
#define VRM_PUP2_R2                    (215u)

#define VRM_GET_AD_PUP3                ADCIF_GETRAW_V_PUP3_FV
#define VRM_PUP3_R1                    (1000u)
#define VRM_PUP3_R2                    (215u)

#define VRM_SET_V_PUP1                 Dio_WriteChannel(DioConf_DioChannel_MCU_VPUP1_CTL, STD_HIGH)
#define VRM_CLR_V_PUP1                 Dio_WriteChannel(DioConf_DioChannel_MCU_VPUP1_CTL, STD_LOW)

#define VRM_SET_V_PUP2                 Dio_WriteChannel(DioConf_DioChannel_MCU_VPUP2_CTL, STD_HIGH)
#define VRM_CLR_V_PUP2                 Dio_WriteChannel(DioConf_DioChannel_MCU_VPUP2_CTL, STD_LOW)

#define VRM_SET_V_PUP3                 Dio_WriteChannel(DioConf_DioChannel_MCU_VPUP3_CTL, STD_HIGH)
#define VRM_CLR_V_PUP3                 Dio_WriteChannel(DioConf_DioChannel_MCU_VPUP3_CTL, STD_LOW)

#define VRM_SET_V_POWER                Dio_WriteChannel(DioConf_DioChannel_MCU_POWER_CTL, STD_HIGH)
#define VRM_CLR_V_POWER                Dio_WriteChannel(DioConf_DioChannel_MCU_POWER_CTL, STD_LOW)

/****************************************************************************************************/
/************************** Input power status machina configuration ********************************/
/****************************************************************************************************/
//--------------------------------------------
/*  state type_A_1 is used by AppIO */
//--------------------------------------------
#define   VRM_LOW_THRESHOLD_TYPE_A_1     (8500U)  //!<low threshold of the type voltage monitor,  mv
#define   VRM_HIGH_THRESHOLD_TYPE_A_1    (16500U) //!<high threshold of the type voltage moniotr, mv
#define   VRM_LOW_HYST_TYPE_A_1          (500U)   //!<the hyst from the under voltage to the normal voltage,mv
#define   VRM_HIGH_HYST_TYPE_A_1         (500U)   //!<the hyst from the over voltage to the normal voltage,mv
#define   VRM_N2LTIME_TYPE_A_1           (2U)     //!<normal to low voltage time delay,tick
#define   VRM_L2UTIME_TYPE_A_1           (2U)     //!<low to under voltage time delay,tick
#define   VRM_L2NTIME_TYPE_A_1           (2U)     //!<low to normal voltage time delay,tick
#define   VRM_H2OTIME_TYPE_A_1           (2U)     //!<high to over voltage time delay,tick
#define   VRM_N2HTIME_TYPE_A_1           (2U)     //!<normal to high voltage time delay,tick
#define   VRM_H2NTIME_TYPE_A_1           (2U)     //!<high to normal voltage time delay,tick
#define   VRM_U2NTIME_TYPE_A_1           (100U)   //!<under to normal voltage time delay,tick
#define   VRM_O2NTIME_TYPE_A_1           (100U)   //!<over to normal voltage time delay,tick
//--------------------------------------------
/*  state type_A_2 is is used by AppNvM */
//--------------------------------------------
#define   VRM_LOW_THRESHOLD_TYPE_A_2     (8000U)  //!<low threshold of the type voltage monitor,  mv
#define   VRM_HIGH_THRESHOLD_TYPE_A_2    (28000U) //!<high threshold of the type voltage moniotr, mv
#define   VRM_LOW_HYST_TYPE_A_2          (500U)   //!<the hyst from the under voltage to the normal voltage,mv
#define   VRM_HIGH_HYST_TYPE_A_2         (500U)   //!<the hyst from the over voltage to the normal voltage,mv
#define   VRM_N2LTIME_TYPE_A_2           (2U)     //!<normal to low voltage time delay,tick
#define   VRM_L2UTIME_TYPE_A_2           (2U)     //!<low to under voltage time delay,tick
#define   VRM_L2NTIME_TYPE_A_2           (2U)     //!<low to normal voltage time delay,tick
#define   VRM_H2OTIME_TYPE_A_2           (2U)     //!<high to over voltage time delay,tick
#define   VRM_N2HTIME_TYPE_A_2           (2U)     //!<normal to high voltage time delay,tick
#define   VRM_H2NTIME_TYPE_A_2           (2U)     //!<high to normal voltage time delay,tick
#define   VRM_U2NTIME_TYPE_A_2           (20U)    //!<under to normal voltage time delay,tick
#define   VRM_O2NTIME_TYPE_A_2           (20U)    //!<over to normal voltage time delay,tick
//--------------------------------------------
/*  state type_A_3 is used by AppIO */  
//--------------------------------------------
#define   VRM_LOW_THRESHOLD_TYPE_A_3     (6000U)  //!<low threshold of the type voltage monitor,  mv
#define   VRM_HIGH_THRESHOLD_TYPE_A_3    (28000U) //!<high threshold of the type voltage moniotr, mv   
#define   VRM_LOW_HYST_TYPE_A_3          (500U)   //!<the hyst from the under voltage to the normal voltage,mv
#define   VRM_HIGH_HYST_TYPE_A_3         (500U)   //!<the hyst from the over voltage to the normal voltage,mv
#define   VRM_N2LTIME_TYPE_A_3           (2U)     //!<normal to low voltage time delay,tick
#define   VRM_L2UTIME_TYPE_A_3           (2U)     //!<low to under voltage time delay,tick
#define   VRM_L2NTIME_TYPE_A_3           (2U)     //!<low to normal voltage time delay,tick
#define   VRM_H2OTIME_TYPE_A_3           (2U)     //!<high to over voltage time delay,tick
#define   VRM_N2HTIME_TYPE_A_3           (2U)     //!<normal to high voltage time delay,tick
#define   VRM_H2NTIME_TYPE_A_3           (2U)     //!<high to normal voltage time delay,tick
#define   VRM_U2NTIME_TYPE_A_3           (100U)   //!<under to normal voltage time delay,tick
#define   VRM_O2NTIME_TYPE_A_3           (100U)   //!<over to normal voltage time delay,tick

//--------------------------------------------
/*  state type_B_1 */
//--------------------------------------------
#define   VRM_UNDER_THRESHOLD_TYPE_B_1   (6000U)  //!<low threshold of the type voltage monitor,  mv
#define   VRM_OVER_THRESHOLD_TYPE_B_1    (28000U) //!<high threshold of the type voltage moniotr, mv
#define   VRM_LOW_HYST_TYPE_B_1          (500U)   //!<the hyst from the under voltage to the normal voltage,mv, Not available now
#define   VRM_HIGH_HYST_TYPE_B_1         (500U)   //!<the hyst from the over voltage to the normal voltage,mv, Not available now
#define   VRM_U2NTIME_TYPE_B_1           (100U)   //!<under to normal voltage time delay,tick
#define   VRM_O2NTIME_TYPE_B_1           (100U)   //!<over to normal voltage time delay,tick
//--------------------------------------------
/*  state type_B_2 */
//--------------------------------------------
#define   VRM_UNDER_THRESHOLD_TYPE_B_2   (8000U)  //!<low threshold of the type voltage monitor,  mv
#define   VRM_OVER_THRESHOLD_TYPE_B_2    (16000U) //!<high threshold of the type voltage moniotr, mv
#define   VRM_LOW_HYST_TYPE_B_2          (0U)     //!<the hyst from the under voltage to the normal voltage,mv, Not available now
#define   VRM_HIGH_HYST_TYPE_B_2         (0U)     //!<the hyst from the over voltage to the normal voltage,mv Not available now
#define   VRM_U2NTIME_TYPE_B_2           (20U)    //!<under to normal voltage time delay,tick
#define   VRM_O2NTIME_TYPE_B_2           (20U)    //!<over to normal voltage time delay,tick


/*
 state type_C_1
*/
#define   VRM_LOW_THRESHOLD_TYPE_C_1     (6500U)  //!<low threshold of the type voltage monitor,  mv
#define   VRM_HIGH_THRESHOLD_TYPE_C_1    (16000U) //!<high threshold of the type voltage moniotr, mv
#define   VRM_LOW_HYST_TYPE_C_1          (300U)   //!<the hyst from the under voltage to the normal voltage,mv
#define   VRM_HIGH_HYST_TYPE_C_1         (300U)   //!<the hyst from the over voltage to the normal voltage,mv
#define   VRM_N2LTIME_TYPE_C_1           (4U)     //!<normal to low voltage time delay,tick
#define   VRM_L2UTIME_TYPE_C_1           (4U)     //!<low to under voltage time delay,tick
#define   VRM_L2NTIME_TYPE_C_1           (4U)     //!<low to normal voltage time delay,tick
#define   VRM_H2OTIME_TYPE_C_1           (4U)     //!<high to over voltage time delay,tick
#define   VRM_N2HTIME_TYPE_C_1           (4U)     //!<normal to high voltage time delay,tick
#define   VRM_H2NTIME_TYPE_C_1           (4U)     //!<high to normal voltage time delay,tick
#define   VRM_U2NTIME_TYPE_C_1           (20U)    //!<under to normal voltage time delay,tick
#define   VRM_O2NTIME_TYPE_C_1           (20U)    //!<over to normal voltage time delay,tick


//--------------------------------------------
/* INL Power DTC Related Configuration*/
//--------------------------------------------

#define VRM_INL_POWER_ON                           (1)         //!<1:INL power input ON  0:INL power input OFF
//#define VRM_INL_POWER_INPUT_LOWPOWER_DTC_INDEX     (DTC_MAX)   //!<Related DTC index, insert"DTC_MAX" if there's no.
//#define VRM_INL_POWER_INPUT_HIGHPOWER_DTC_INDEX    (DTC_MAX)   //!<Related DTC index, insert"DTC_MAX" if there's no.
#define VRM_LOW_THRESHOLD_DTC_TYPE1                (8000U)     //!<low threshold of the type voltage monitor, mv
#define VRM_HIGH_THRESHOLD_DTC_TYPE1               (16000U)    //!<high threshold of the type voltage moniotr, mv
#define VRM_LOW_HYST_DTC_TYPE1                     (500U)      //!<the hyst from the under voltage to the normal voltage,mv
#define VRM_HIGH_HYST_DTC_TYPE1                    (500U)      //!<the hyst from the over voltage to the normal voltage,mv
#define VRM_N2LTIME_DTC_TYPE1                      (4U)        //!<normal to low voltage time delay,tick
#define VRM_L2UTIME_DTC_TYPE1                      (4U)        //!<low to under voltage time delay,tick
#define VRM_L2NTIME_DTC_TYPE1                      (4U)        //!<low to normal voltage time delay,tick
#define VRM_H2OTIME_DTC_TYPE1                      (4U)        //!<high to over voltage time delay,tick
#define VRM_N2HTIME_DTC_TYPE1                      (4U)        //!<normal to high voltage time delay,tick
#define VRM_H2NTIME_DTC_TYPE1                      (4U)        //!<high to normal voltage time delay,tick
#define VRM_U2NTIME_DTC_TYPE1                      (200U)      //!<under to normal voltage time delay,tick
#define VRM_O2NTIME_DTC_TYPE1                      (200U)      //!<over to normal voltage time delay,tick

//--------------------------------------------
/* EXL Power DTC Related Configuration*/
//--------------------------------------------
#define VRM_EXL_POWER_ON                           (1)         //!<1:EXL power input ON  0:EXL power input OFF
//#define VRM_EXL_POWER_INPUT_LOWPOWER_DTC_INDEX     (DTC_MAX)   //!<Related DTC index, insert"DTC_MAX" if there's no.
//#define VRM_EXL_POWER_INPUT_HIGHPOWER_DTC_INDEX    (DTC_MAX)   //!<Related DTC index, insert"DTC_MAX" if there's no.
#define VRM_LOW_THRESHOLD_DTC_TYPE2                (8000U)     //!<low threshold of the type voltage monitor,  mv
#define VRM_HIGH_THRESHOLD_DTC_TYPE2               (16000U)    //!<high threshold of the type voltage moniotr, mv
#define VRM_LOW_HYST_DTC_TYPE2                     (500U)      //!<the hyst from the under voltage to the normal voltage,mv
#define VRM_HIGH_HYST_DTC_TYPE2                    (500U)      //!<the hyst from the over voltage to the normal voltage,mv
#define VRM_N2LTIME_DTC_TYPE2                      (4U)        //!<normal to low voltage time delay,tick
#define VRM_L2UTIME_DTC_TYPE2                      (4U)        //!<low to under voltage time delay,tick
#define VRM_L2NTIME_DTC_TYPE2                      (4U)        //!<low to normal voltage time delay,tick
#define VRM_H2OTIME_DTC_TYPE2                      (4U)        //!<high to over voltage time delay,tick
#define VRM_N2HTIME_DTC_TYPE2                      (4U)        //!<normal to high voltage time delay,tick
#define VRM_H2NTIME_DTC_TYPE2                      (4U)        //!<high to normal voltage time delay,tick
#define VRM_U2NTIME_DTC_TYPE2                      (200U)      //!<under to normal voltage time delay,tick
#define VRM_O2NTIME_DTC_TYPE2                      (200U)      //!<over to normal voltage time delay,tick

//--------------------------------------------
/* HAZARD Power DTC Related Configuration*/
//--------------------------------------------
#define VRM_HAZARD_POWER_ON                        (0)         //!<1:INL power input ON  0:INL power input OFF
//#define VRM_HAZARD_POWER_INPUT_LOWPOWER_DTC_INDEX  (DTC_MAX)   //!<Related DTC index, insert"DTC_MAX" if there's no.
//#define VRM_HAZARD_POWER_INPUT_HIGHPOWER_DTC_INDEX (DTC_MAX)   //!<Related DTC index, insert"DTC_MAX" if there's no.
#define VRM_LOW_THRESHOLD_DTC_TYPE3                (8000U)     //!<low threshold of the type voltage monitor,  mv
#define VRM_HIGH_THRESHOLD_DTC_TYPE3               (16000U)    //!<high threshold of the type voltage moniotr, mv
#define VRM_LOW_HYST_DTC_TYPE3                     (500U)      //!<the hyst from the under voltage to the normal voltage,mv
#define VRM_HIGH_HYST_DTC_TYPE3                    (500U)      //!<the hyst from the over voltage to the normal voltage,mv
#define VRM_N2LTIME_DTC_TYPE3                      (4U)        //!<normal to low voltage time delay,tick
#define VRM_L2UTIME_DTC_TYPE3                      (4U)     //!<low to under voltage time delay,tick
#define VRM_L2NTIME_DTC_TYPE3                      (4U)     //!<low to normal voltage time delay,tick
#define VRM_H2OTIME_DTC_TYPE3                      (4U)     //!<high to over voltage time delay,tick
#define VRM_N2HTIME_DTC_TYPE3                      (4U)     //!<normal to high voltage time delay,tick
#define VRM_H2NTIME_DTC_TYPE3                      (4U)     //!<high to normal voltage time delay,tick
#define VRM_U2NTIME_DTC_TYPE3                      (200U)   //!<under to normal voltage time delay,tick
#define VRM_O2NTIME_DTC_TYPE3                      (200U)   //!<over to normal voltage time delay,tick

/****************************************************************************************************/
/************************** Exported Constant Variables Definitions *********************************/
/****************************************************************************************************/
extern const boolean Vrm_interceptControlOnClose[VRM_PID_SIZE];
extern const uint8 * Vrm_outputState[VRM_PID_SIZE];
extern const boolean Vrm_interceptState[VRM_PID_SIZE];
extern const Vrm_StateTypes_e Vrm_interceptStateType[VRM_PID_SIZE];
extern const IOHWAB_DoInrushTimerId_e gVrm_channelStateIndex[VRM_PID_SIZE];

//----------------------------------------------------------------------------
/* flow type_A  Parameter */
//----------------------------------------------------------------------------
#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
extern const uint16 Vrm_au16LowThresholdFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16HighThresholdFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16LowHystFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16HighHystFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16N2LTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16L2UTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16L2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16H2OTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16N2HTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16H2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16U2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 Vrm_au16O2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
#endif
//----------------------------------------------------------------------------
/* flow type_B  Parameter */
//----------------------------------------------------------------------------
#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
extern const uint16 Vrm_au16UnderThresholdFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 Vrm_au16OverThresholdFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 Vrm_au16LowHystFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 Vrm_au16HighHystFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 Vrm_au16U2NTimeFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 Vrm_au16O2NTimeFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
#endif
//----------------------------------------------------------------------------
/* flow type_C  Parameter */
//----------------------------------------------------------------------------
#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
extern const uint16 Vrm_au16LowThresholdFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16HighThresholdFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16LowHystFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16HighHystFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16N2LTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16L2UTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16L2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16H2OTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16N2HTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16H2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16U2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 Vrm_au16O2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
#endif
//----------------------------------------------------------------------------
/* flow type_D DTC  Parameter */
//----------------------------------------------------------------------------
#if (VRM_DTC_TYPE_D_NUM != 0)
extern const uint16 Vrm_au16LowThresholdFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16HighThresholdFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16LowHystFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16HighHystFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16N2LTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16L2UTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16L2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16H2OTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16N2HTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16H2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16U2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 Vrm_au16O2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
#endif

#endif

