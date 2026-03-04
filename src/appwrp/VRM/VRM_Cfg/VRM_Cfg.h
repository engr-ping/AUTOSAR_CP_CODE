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
#include "AdcIf_LCfg.h"
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
}VRM_StateType;

/***********************    Global Type Definition    ************************/
typedef enum
{
    VRM_PID_DUMMY,

    VRM_PID_OPH01,
    VRM_PID_OPH02,
    VRM_PID_OPH03,
    VRM_PID_OPH04,
    VRM_PID_OPH05,
    VRM_PID_OPH06,
    VRM_PID_OPH07,
    VRM_PID_OPH08,
    VRM_PID_OPH09,
    VRM_PID_OPH10,
    VRM_PID_OPH11,
    VRM_PID_OPH12,
    VRM_PID_OPH13,
    VRM_PID_OPH14,
    VRM_PID_OPH15,
    VRM_PID_OPH16,
    VRM_PID_OPH17,
    VRM_PID_OPH18,
    VRM_PID_OPH19,
    VRM_PID_OPH20,
    VRM_PID_OPH21,
    VRM_PID_OPH22,
    VRM_PID_OPH23,
    VRM_PID_OPH24,
    VRM_PID_OPH25,
    VRM_PID_OPH26,
    VRM_PID_OPH27,
    VRM_PID_OPH28,
    VRM_PID_OPH29,
    VRM_PID_OPH30,
    VRM_PID_OPH31,
    VRM_PID_OPH32,
    VRM_PID_OPH33,
    VRM_PID_OPH34,
    VRM_PID_OPH35,
    VRM_PID_OPH36,
    VRM_PID_OPH37,
    VRM_PID_OPH38,
    VRM_PID_OPH39,
    VRM_PID_OPH40,
    VRM_PID_OPH41,
    VRM_PID_OPH42,
    VRM_PID_OPH43,
    VRM_PID_OPH44,
    VRM_PID_OPH45,
    
    VRM_PID_OPL01,
    
    VRM_PID_OR01,
    VRM_PID_OR02,
    VRM_PID_OR03,
    VRM_PID_OR04,
    VRM_PID_OR05,
    VRM_PID_OR06,
    VRM_PID_OR07,
    VRM_PID_OR08,
    VRM_PID_OR09,
    VRM_PID_OR10,
    VRM_PID_OR11,
    VRM_PID_OR12,
    VRM_PID_OR13,
    VRM_PID_OR14,
    
    VRM_PID_ODH01,
    VRM_PID_ODH02,
    VRM_PID_ODH03,
    VRM_PID_ODH04,
    VRM_PID_ODH05,
    VRM_PID_ODH06,
    VRM_PID_ODH07,
    VRM_PID_ODH08,
    
    VRM_PID_ODL01,
    VRM_PID_ODL02,
    VRM_PID_ODL03,
    VRM_PID_ODL04,
    VRM_PID_ODL05,
    VRM_PID_ODL06,
    VRM_PID_ODL07,
    VRM_PID_ODL08,
    VRM_PID_ODL09,
    VRM_PID_ODL10,
    VRM_PID_ODL11,
    VRM_PID_ODL12,
    VRM_PID_ODL13,
    VRM_PID_ODL14,
    VRM_PID_ODL15,
    VRM_PID_ODL16,
    VRM_PID_ODL17,
    VRM_PID_ODL18,
    VRM_PID_ODL19,
    VRM_PID_ODL20,
    VRM_PID_ODL21,
    VRM_PID_ODL22,
    VRM_PID_ODL23,
    VRM_PID_ODL24,
    VRM_PID_ODL25,
    VRM_PID_ODL26,
    VRM_PID_ODL27,
    VRM_PID_ODL28,
    VRM_PID_ODL29,
    VRM_PID_ODL30,
    VRM_PID_ODL31,

    VRM_PID_SIZE
} VRM_PhysicalId_e;

/**************************    Macro Definitions    **************************/
#define VRM_FID_OPH01       (VRM_PID_OPH01)
#define VRM_FID_OPH02       (VRM_PID_OPH02)
#define VRM_FID_OPH03       (VRM_PID_OPH03)
#define VRM_FID_OPH04       (VRM_PID_OPH04)
#define VRM_FID_OPH05       (VRM_PID_OPH05)
#define VRM_FID_OPH06       (VRM_PID_OPH06)
#define VRM_FID_OPH07       (VRM_PID_OPH07)
#define VRM_FID_OPH08       (VRM_PID_OPH08)
#define VRM_FID_OPH09       (VRM_PID_OPH09)
#define VRM_FID_OPH10       (VRM_PID_OPH10)


#define VRM_FID_OPH11       (VRM_PID_OPH11)
#define VRM_FID_OPH12       (VRM_PID_OPH12)
#define VRM_FID_OPH13       (VRM_PID_OPH13)
#define VRM_FID_OPH14       (VRM_PID_OPH14)
#define VRM_FID_OPH15       (VRM_PID_OPH15) 
#define VRM_FID_OPH16       (VRM_PID_OPH16)
#define VRM_FID_OPH17       (VRM_PID_OPH17)
#define VRM_FID_OPH18       (VRM_PID_OPH18) 
#define VRM_FID_OPH19       (VRM_PID_OPH19) 
#define VRM_FID_OPH20       (VRM_PID_OPH20) 

#define VRM_FID_OPH21       (VRM_PID_OPH21) 
#define VRM_FID_OPH22       (VRM_PID_OPH22) 
#define VRM_FID_OPH23       (VRM_PID_OPH23) 
#define VRM_FID_OPH24       (VRM_PID_OPH24) 
#define VRM_FID_OPH25       (VRM_PID_OPH25) 
#define VRM_FID_OPH26       (VRM_PID_OPH26) 
#define VRM_FID_OPH27       (VRM_PID_OPH27) 
#define VRM_FID_OPH28       (VRM_PID_OPH28) 
#define VRM_FID_OPH29       (VRM_PID_OPH29) 
#define VRM_FID_OPH30       (VRM_PID_OPH30) 

#define VRM_FID_OPH31       (VRM_PID_OPH31) 
#define VRM_FID_OPH32       (VRM_PID_OPH32) 
#define VRM_FID_OPH33       (VRM_PID_OPH33) 
#define VRM_FID_OPH34       (VRM_PID_OPH34) 
#define VRM_FID_OPH35       (VRM_PID_OPH35) 
#define VRM_FID_OPH36       (VRM_PID_OPH36) 
#define VRM_FID_OPH37       (VRM_PID_OPH37) 
#define VRM_FID_OPH38       (VRM_PID_OPH38) 
#define VRM_FID_OPH39       (VRM_PID_OPH39) 
#define VRM_FID_OPH40       (VRM_PID_OPH40) 

#define VRM_FID_OPH41       (VRM_PID_OPH41) 
#define VRM_FID_OPH42       (VRM_PID_OPH42) 
#define VRM_FID_OPH43       (VRM_PID_OPH43) 
#define VRM_FID_OPH44       (VRM_PID_OPH44) 
#define VRM_FID_OPH45       (VRM_PID_OPH45) 

#define VRM_FID_OPL01       (VRM_PID_OPL01) 

#define VRM_FID_OR01       (VRM_PID_OR01) 
#define VRM_FID_OR02       (VRM_PID_OR02) 
#define VRM_FID_OR03       (VRM_PID_OR03) 
#define VRM_FID_OR04       (VRM_PID_OR04) 
#define VRM_FID_OR05       (VRM_PID_OR05) 
#define VRM_FID_OR06       (VRM_PID_OR06) 
#define VRM_FID_OR07       (VRM_PID_OR07) 
#define VRM_FID_OR08       (VRM_PID_OR08) 
#define VRM_FID_OR09       (VRM_PID_OR09) 
#define VRM_FID_OR10       (VRM_PID_OR10) 
#define VRM_FID_OR11       (VRM_PID_OR11) 
#define VRM_FID_OR12       (VRM_PID_OR12) 
#define VRM_FID_OR13       (VRM_PID_OR13) 
#define VRM_FID_OR14       (VRM_PID_OR14) 

#define VRM_FID_ODH01       (VRM_PID_ODH01) 
#define VRM_FID_ODH02       (VRM_PID_ODH02) 
#define VRM_FID_ODH03       (VRM_PID_ODH03) 
#define VRM_FID_ODH04       (VRM_PID_ODH04) 
//add
#define VRM_FID_ODH05       (VRM_PID_ODH05) 
#define VRM_FID_ODH06       (VRM_PID_ODH06) 
#define VRM_FID_ODH07       (VRM_PID_ODH07) 
#define VRM_FID_ODH08       (VRM_PID_ODH08) 


#define VRM_FID_ODL01       (VRM_PID_ODL01) 
#define VRM_FID_ODL02       (VRM_PID_ODL02) 
#define VRM_FID_ODL03       (VRM_PID_ODL03) 
#define VRM_FID_ODL04       (VRM_PID_ODL04) 
#define VRM_FID_ODL05       (VRM_PID_ODL05) 
#define VRM_FID_ODL06       (VRM_PID_ODL06) 
#define VRM_FID_ODL07       (VRM_PID_ODL07) 
#define VRM_FID_ODL08       (VRM_PID_ODL08) 
#define VRM_FID_ODL09       (VRM_PID_ODL09) 
#define VRM_FID_ODL10       (VRM_PID_ODL10) 

#define VRM_FID_ODL11       (VRM_PID_ODL11) 
#define VRM_FID_ODL12       (VRM_PID_ODL12) 
#define VRM_FID_ODL13       (VRM_PID_ODL13) 
#define VRM_FID_ODL14       (VRM_PID_ODL14) 
#define VRM_FID_ODL15       (VRM_PID_ODL15) 
#define VRM_FID_ODL16       (VRM_PID_ODL16) 
#define VRM_FID_ODL17       (VRM_PID_ODL17) 
#define VRM_FID_ODL18       (VRM_PID_ODL18) 
#define VRM_FID_ODL19       (VRM_PID_ODL19) 
#define VRM_FID_ODL20       (VRM_PID_ODL20) 

#define VRM_FID_ODL21       (VRM_PID_ODL21) 
#define VRM_FID_ODL22       (VRM_PID_ODL22) 
#define VRM_FID_ODL23       (VRM_PID_ODL23) 
#define VRM_FID_ODL24       (VRM_PID_ODL24) 
#define VRM_FID_ODL25       (VRM_PID_ODL25) 
#define VRM_FID_ODL26       (VRM_PID_ODL26) 
#define VRM_FID_ODL27       (VRM_PID_ODL27) 
#define VRM_FID_ODL28       (VRM_PID_ODL28) 
#define VRM_FID_ODL29       (VRM_PID_ODL29) 
#define VRM_FID_ODL30       (VRM_PID_ODL30)

#define VRM_FID_ODL31       (VRM_PID_ODL31) 

#define VRM_FID_SLC_PWM     (VRM_PID_DUMMY)
#define VRM_FID_VREF01      (VRM_PID_DUMMY)
#define VRM_FID_VREF02      (VRM_PID_DUMMY)
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
extern const boolean cVRM_abInterceptControlOnClose[VRM_PID_SIZE];
extern const uint8 * cVRM_apu8OutPutState[VRM_PID_SIZE];
extern const boolean cVRM_abInterceptState[VRM_PID_SIZE];
extern const VRM_StateTypes_e cVRM_aeInterceptStateType[VRM_PID_SIZE];
extern const IOHWAB_DoInrushTimerId_e gVRM_eChannelStateIndex[VRM_PID_SIZE];

//----------------------------------------------------------------------------
/* flow type_A  Parameter */
//----------------------------------------------------------------------------
#if (VRM_STATEFLOW_TYPE_A_NUM != 0)
extern const uint16 cVRM_au16LowThresholdFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16HighThresholdFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16LowHystFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16HighHystFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16N2LTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16L2UTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16L2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16H2OTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16N2HTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16H2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16U2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
extern const uint16 cVRM_au16O2NTimeFlowTypeA[VRM_STATEFLOW_TYPE_A_NUM];
#endif
//----------------------------------------------------------------------------
/* flow type_B  Parameter */
//----------------------------------------------------------------------------
#if (VRM_STATEFLOW_TYPE_B_NUM != 0)
extern const uint16 cVRM_au16UnderThresholdFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 cVRM_au16OverThresholdFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 cVRM_au16LowHystFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 cVRM_au16HighHystFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 cVRM_au16U2NTimeFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
extern const uint16 cVRM_au16O2NTimeFlowTypeB[VRM_STATEFLOW_TYPE_B_NUM];
#endif
//----------------------------------------------------------------------------
/* flow type_C  Parameter */
//----------------------------------------------------------------------------
#if (VRM_STATEFLOW_TYPE_C_NUM != 0)
extern const uint16 cVRM_au16LowThresholdFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16HighThresholdFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16LowHystFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16HighHystFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16N2LTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16L2UTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16L2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16H2OTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16N2HTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16H2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16U2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
extern const uint16 cVRM_au16O2NTimeFlowTypeC[VRM_STATEFLOW_TYPE_C_NUM];
#endif
//----------------------------------------------------------------------------
/* flow type_D DTC  Parameter */
//----------------------------------------------------------------------------
#if (VRM_DTC_TYPE_D_NUM != 0)
extern const uint16 cVRM_au16LowThresholdFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16HighThresholdFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16LowHystFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16HighHystFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16N2LTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16L2UTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16L2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16H2OTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16N2HTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16H2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16U2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
extern const uint16 cVRM_au16O2NTimeFlowDtcTypeD[VRM_DTC_TYPE_D_NUM];
#endif

#endif

