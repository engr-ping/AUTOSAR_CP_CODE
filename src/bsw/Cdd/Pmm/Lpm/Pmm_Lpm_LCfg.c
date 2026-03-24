/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Pmm_Lpm                                                                                             
*  Content:  Power Mode Management for Low power mode
*  Category: Sleep Awake Control 
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */
#include "Pmm_Lpm.h"
#include "Pmm_Lpm_LCfg.h"

/*PRQA S 4424,4521 EOF*/
/*************************************************************************
*    Const Variables Definition -- this would be configured according to different project
*************************************************************************/
const Pmm_Lpm_IcuWakeupSrc_t cPmm_Lpm_atIcuWKCfg[PMM_LPM_ICU_WK_SRC_NUM] =
{
    {LPM_CW_RTC,              LPM_WKPU_01,     PMM_LPM_WKPU_RISING_EDGE,   TRUE },                        /*RTC*/
    {LPM_CW_CTU,              LPM_WKPU_00,     PMM_LPM_WKPU_RISING_EDGE,   PMM_LPM_ICU_WAKEUP_IS_EN_CTU},                          /*CTU*/
    {LPM_CW_RKE,              LPM_WKPU_26,     PMM_LPM_WKPU_FALLING_EDGE,  PMM_LPM_ICU_WAKEUP_IS_EN_RKE},                          /*RKE_INT*/
    {LPM_CW_LF,               LPM_WKPU_30,     PMM_LPM_WKPU_RISING_EDGE,   PMM_LPM_ICU_WAKEUP_IS_EN_LF },                          /*LF_INT*/
    {LPM_CW_SBC_CANRX,        LPM_WKPU_24,     PMM_LPM_WKPU_FALLING_EDGE,  PMM_LPM_ICU_WAKEUP_IS_EN_SBC_CANRX},                    /*SBC_CANRX*/
    {LPM_CW_CAN2RX,           LPM_WKPU_31,     PMM_LPM_WKPU_FALLING_EDGE,  PMM_LPM_ICU_WAKEUP_IS_EN_CAN2RX},                       /*TJA CANRX*/
    {LPM_CW_LIN01,            LPM_WKPU_25,     PMM_LPM_WKPU_FALLING_EDGE,  PMM_LPM_ICU_WAKEUP_IS_EN_LIN01},                        /*LIN01_RXD*/
};

const Pmm_Lpm_AiChannelInfo_t cPmm_Lpm_atAiChanCfg[IOHWAB_AI_WD_MAX + 1] =
{
    {IOHWAB_AI_WD_IAN02, 35U,    IOHWAB_AI_COMPENSATE_TYPE_IAN02 },                         /*IAN02*/
    {PMM_LPM_AI_PUP1_FV,  2U,    IOHWAB_AI_COMPENSATE_TYPE_V_PUP1_FV }                      /*PUP1_FV*/
};


const Pmm_Lpm_DiChannelInfo_t cPmm_Lpm_atDiChanWkCfg[IOHWAB_DI_WD_MAX] =
{
/************index****DiChannel**Invert**Status************/
    {IOHWAB_DI_WD_IDL09,  0, IOHWAB_DI_INVERT_IDL09,&IOHWAB_DI_VARIABLE_IDL09},

};

const Pmm_Lpm_PortType_t cPmm_Lpm_atPortCfg[PMM_LPM_PORT_MAXNUM] =
{
/*index**PortChannel****RegValue*****/
/*00*/  {144u, 0x02000000u},  /*PJ11 - PUP1*/
//SBC SPI
/*01*/  {119u, 0x00380004u},  /* DI - PH7  */

};




