/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Pmm_Sac                                                                                             
*  Content:  Power Mode Management for Sleep Awake Control
*  Category: 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */

#ifndef _LPM_LCFG_H_
#define _LPM_LCFG_H_

/******************************************************************************
*    Include files
******************************************************************************/

#include "IoHwAb_DigitalInput_Cfg.h"
#include "IoHwAb_AnalogInput_Cfg.h"
#include "pk.h"
/******************************************************************************
*    Local Macros -- Macros used in this file only
******************************************************************************/
#define ICU_WK_MAX_NUM         32U
#define PMM_LPM_ICU_WK_SRC_NUM         23U
#define SBC_SPI_BASEADDR       DSPI1_BASEADDR
#define PMM_LPM_IPL_DI_MASK       0x03C00000UL



/*************************************************************************
*
*           OPC Function Configure
*
*           Only Cfg STD_ON or STD_OFF
**************************************************************************/


#define PMM_LPM_ENABLE_OPC0 STD_OFF
#define PMM_LPM_ENABLE_OPC1 STD_OFF
#define PMM_LPM_ENABLE_OPC2 STD_OFF
#define PMM_LPM_ENABLE_OPC3 STD_OFF
#define PMM_LPM_ENABLE_OPC4 STD_OFF
#define PMM_LPM_ENABLE_OPC5 STD_ON
#define PMM_LPM_ENABLE_OPC6 STD_OFF
#define PMM_LPM_ENABLE_OPC7 STD_OFF


/******************Do not change this code*********************************/




enum
{
    PMM_LPM_PORT_PUP1,
    PMM_LPM_PORT_SBC_SPIDI1,
    PMM_LPM_PORT_SBC_SPIDI2,
    PMM_LPM_PORT_SBC_SPIDO,
    PMM_LPM_PORT_SBC_SPICLK,
    PMM_LPM_PORT_SBC_SPICLK1,
    PMM_LPM_PORT_SBC_SPICS,
    PMM_LPM_PORT_IDH01,
    PMM_LPM_PORT_IDH02,
    PMM_LPM_PORT_IDH03,
    PMM_LPM_PORT_IDH04,
    PMM_LPM_PORT_MAXNUM          //exception ADC and DI Wakeup
};


enum
{
#if(PMM_LPM_ENABLE_OPC0 == STD_ON)
    PMM_LPM_OPC_CHN0,
#endif
#if(PMM_LPM_ENABLE_OPC1 == STD_ON)
    PMM_LPM_OPC_CHN1,
#endif
#if(PMM_LPM_ENABLE_OPC2 == STD_ON)
    PMM_LPM_OPC_CHN2,
#endif
#if(PMM_LPM_ENABLE_OPC3 == STD_ON)
    PMM_LPM_OPC_CHN3,
#endif
#if(PMM_LPM_ENABLE_OPC4 == STD_ON)
    PMM_LPM_OPC_CHN4,
#endif
#if(PMM_LPM_ENABLE_OPC5 == STD_ON)
    PMM_LPM_OPC_CHN5,
#endif
#if(PMM_LPM_ENABLE_OPC6 == STD_ON)
    PMM_LPM_OPC_CHN6,
#endif
#if(PMM_LPM_ENABLE_OPC7 == STD_ON)
    PMM_LPM_OPC_CHN7,
#endif
    PMM_LPM_OPC_MAX
};

/******************************************************************************
*    Local Macros -- Macros used in this file only
******************************************************************************/
#define LPM_RECORD_MORNITER_DATA_SIZE 10U

/******************************************************************************
*    Local Macros -- Macros used in Pmm_Lpm module only
******************************************************************************/
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG0  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL09]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG1  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL11]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG2  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL10]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG3  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL08]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG4  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL05]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG5  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL15]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG6  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL07]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG7  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL06]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG8  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL03]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG9  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL26]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG10 gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL01]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG11 gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL04]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG12 gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL28]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SG13 gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL02]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SP0  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDX05]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SP1  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDX04]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SP2  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL14]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SP3  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL16]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SP4  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDX02]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SP5  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDX03]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SP6  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDX01]
#define PMM_LPM_MC33978_CHANNEL_HISTORY_SP7  gDioIf_abDigitalSampleValue[DIOIF_DIRECT_IDL27]




/******************************************************************************
*    Local Enums -- Enums used in this file only
******************************************************************************/


/******************************************************************************
*    Local Typedefs -- Typedefs used in this file only
******************************************************************************/
/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/


extern uint8 Pmm_Lpm_u8GetIA02Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA05Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA06Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA07Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA09Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA10Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA11Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA28Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA29Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA30Shift(uint16 ChanAD);
extern uint8 Pmm_Lpm_u8GetIA31Shift(uint16 ChanAD);

#endif

