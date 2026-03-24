/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Pmm_Smc                                                                                             
*  Content:  Power Mode Management for High power mode
*  Category: Ecu init and shutdown management
******************************************************************************************************************
*  Revision Management                                                                                            
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */

#include "Pmm_Lpm.h" 
#include "Pmm_Hpm.h"
#include "DioIf.h"
#include "IoHwAb_DigitalIn_Cfg.h"
#include "IoHwAb_AnalogIn_Cfg.h"
#include "Gpt.h"
#include "Mcu.h"
#include "IoHwAb_DigitalIn.h" 
#include "IoHwAb_AnalogIn.h" 

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Pmm_Hpm.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */ /* PRQA S 1599 */

/* PRQA S 0303,0305,0306,0315,1006,1281,2987,3006,3408,3426,3432 EOF*/

/*************************************************************************
*    Local Macros -- Macros used in this file only
*************************************************************************/


/*************************************************************************
*    Local Enums -- Enums used in this file only
*************************************************************************/

/*************************************************************************
*    Local Typedefs -- Typedefs used in this file only
*************************************************************************/

/*************************************************************************
*    Local Static Variables Definition -- Variables used in this file only
*************************************************************************/

/*************************************************************************
*  Local Static Functions Declaration -- Functions used in this file only
**************************************************************************/

/*************************************************************************
*  Global Variables Definition -- Create global variables here
*************************************************************************/


extern uint32 *LPM_IN_RAM_SRC;
extern uint32 *LPM_IN_RAM_DEST;
extern uint32 *LPM_IN_RAM_SIZE;
uint32 gPmm_Hpm_u32SacInRamSrc  = (uint32)(&LPM_IN_RAM_SRC);
uint32 gPmm_Hpm_u32SacInRamDest = (uint32)(&LPM_IN_RAM_DEST);
uint32 gPmm_Hpm_u32SacInRamSize = (uint32)(&LPM_IN_RAM_SIZE);

/*************************************************************************
*  Others -- Variables, Functions, etc. created in other C files
*************************************************************************/
static void Pmm_Hpm_CopySacCodeToRAM(void);
static boolean Pmm_Hpm_EnterSleepCheckIcuWakeup(void);
static void Pmm_Hpm_EnterSleepSetWakeupEvents(Pmm_Lpm_WakeResourceType_e WakeupSource);
static void Pmm_Hpm_EnterSleepEnableWakeupSource(void);
static void Pmm_Hpm_DisableAllInt(void);
static void Pmm_Hpm_ResetAllPeripheralStatus(void);
/*************************************************************************
*    Const Variables Definition -- this would be configured according to different project
*************************************************************************/

/*********************************************************************************
*
*    Global Variables In RAM
*
***********************************************************************************/



/***********************************************************************************************************************
 *  Pmm_Hpm_Init
 **********************************************************************************************************************/
/*! \brief
 *  \details
 *  \param[in]
 *  \param[in]
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
void Pmm_Hpm_Init(void)
{
    uint32 tmp_u32DES;


    Pmm_Hpm_CopySacCodeToRAM();
   /* Clear Power OnRegister Flag*/

}

/***********************************************************************************************************************
 *  Pmm_Hpm_CopySacCodeToRAM
 **********************************************************************************************************************/
/*! \brief
 *  \details
 *  \param[in]
 *  \param[in]
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/

static void Pmm_Hpm_CopySacCodeToRAM(void)
{
    /****** Copy code From Flash to RAM******/
    uint32 i;
    uint8 *pu8RamCodeBuffer;       // destination pointer
    uint32 tmp_u32CopyLength;    // size of the RAMBootCode() in 32bit words

    pu8RamCodeBuffer  = (uint8 *)gPmm_Hpm_u32SacInRamDest;  // SRAM start addr = 0x40000000
    tmp_u32CopyLength = gPmm_Hpm_u32SacInRamSize;

    for (i = 0U; i < (uint32)(tmp_u32CopyLength + 1U); ++i)
    {
        pu8RamCodeBuffer[i] = ((uint8 *)gPmm_Hpm_u32SacInRamSrc)[i];
    }

    /************************Copy const value to RAM***************************************************/
    (void)memcpy(gPmm_Lpm_atIcuWKCfg_RAM,             cPmm_Lpm_atIcuWKCfg,          sizeof(cPmm_Lpm_atIcuWKCfg));
    (void)memcpy(gPmm_Lpm_atPortCfg_RAM,              cPmm_Lpm_atPortCfg,           sizeof(cPmm_Lpm_atPortCfg));
    (void)memcpy(gPmm_Lpm_atAiChanCfg_RAM,            cPmm_Lpm_atAiChanCfg,         sizeof(cPmm_Lpm_atAiChanCfg));
    (void)memcpy(gPmm_Lpm_atDiChanWkCfg_RAM,          cPmm_Lpm_atDiChanWkCfg,       sizeof(cPmm_Lpm_atDiChanWkCfg));
    (void)memcpy(gPmm_Lpm_atAdWkupSrcPrjCfg_RAM,      cPmm_Lpm_atAdWkupSrcPrjCfg,   sizeof(cPmm_Lpm_atAdWkupSrcPrjCfg));
    (void)memcpy(gPmm_Lpm_abDiWkpSrcEnable_RAM,       cPmm_Lpm_abDiWkupSrcEnable,   sizeof(cPmm_Lpm_abDiWkupSrcEnable));

}


/***********************************************************************************************************************
 *  Pmm_Hpm_EnterSleepEnableWakeupSource
 **********************************************************************************************************************/
/*! \brief
 *  \details
 *  \param[in]
 *  \param[in]
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static void Pmm_Hpm_EnterSleepEnableWakeupSource(void)
{
    uint8    index;
    uint32 u32REMask = 0x0U;
    uint32 u32FEMask = 0x0U;
    uint32 u32EnableMask = 0x0U;

    for(index = 0x0U; index < PMM_LPM_ICU_WK_SRC_NUM; index++)
    {
        if((boolean)TRUE == cPmm_Lpm_atIcuWKCfg[index].IsEnable)
        {
            if(PMM_LPM_WKPU_RISING_EDGE == cPmm_Lpm_atIcuWKCfg[index].WKPU_EDGE)
            {
                u32REMask |= (uint32)((uint32)1U << cPmm_Lpm_atIcuWKCfg[index].WKPU_Channel);
            }
            else if(PMM_LPM_WKPU_FALLING_EDGE == cPmm_Lpm_atIcuWKCfg[index].WKPU_EDGE)
            {
                u32FEMask |= (uint32)((uint32)1U << cPmm_Lpm_atIcuWKCfg[index].WKPU_Channel);
            }
            else if(PMM_LPM_WKPU_BOTH_EDGES == cPmm_Lpm_atIcuWKCfg[index].WKPU_EDGE)
            {
                u32REMask |= (uint32)((uint32)1U << cPmm_Lpm_atIcuWKCfg[index].WKPU_Channel);
                u32FEMask |= (uint32)((uint32)1U << cPmm_Lpm_atIcuWKCfg[index].WKPU_Channel);
            }
            else
            {
                /**********It's empt,Nothing to do*****************/
            }
            u32EnableMask |= (uint32)((uint32)1U << cPmm_Lpm_atIcuWKCfg[index].WKPU_Channel);
        }
        else
        {
            /**********It's empt,Nothing to do*****************/
        }
    }

}


/***********************************************************************************************************************
 *  Pmm_Hpm_EnterSleepSetWakeupEvents
 **********************************************************************************************************************/
/*! \brief      Store the latest Wakeup source in control ram
 *  \details     Store the latest wakeup source in control ram, and the max num of wakeup source could be
 *                  saved is LPM_RECORD_MORNITER_DATA_SIZE
 *  \param[in]
 *  \param[in]
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static void Pmm_Hpm_EnterSleepSetWakeupEvents(Pmm_Lpm_WakeResourceType_e WakeupSource)
{
    uint8 index;
    gPmm_Lpm_bWakeFlag_RAM = TRUE;
    /* Record raw wakeup reason for moniter */
    for(index = (uint8)(LPM_RECORD_MORNITER_DATA_SIZE - 1U); index > 0U; index--)
    {
        gPmm_Lpm_aeWakeupEvents_RAM[index] = gPmm_Lpm_aeWakeupEvents_RAM[index - 1U];
    }

    gPmm_Lpm_aeWakeupEvents_RAM[0U] = WakeupSource;
}

/***********************************************************************************************************************
 *  Pmm_Hpm_EnterSleepCheckIcuWakeup
 **********************************************************************************************************************/
/*! \brief    check whether ICU wakeup happen
 *  \details   load WKPU_WISR and check ICU wakeup source according to cfg
 *  \param[in]  N/A
 *  \param[in]  N/A
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static boolean Pmm_Hpm_EnterSleepCheckIcuWakeup(void)
{
    uint8 i;
    boolean tmp_bRtn = FALSE;
    uint32 tmp_u32WisrReg;

    tmp_u32WisrReg = WKPU.WISR.R;

    for(i = 0x0U; i < PMM_LPM_ICU_WK_SRC_NUM; i++)
    {
        if((uint8)TRUE == cPmm_Lpm_atIcuWKCfg[i].IsEnable)
        {
            if(LPM_WKPU_01 != cPmm_Lpm_atIcuWKCfg[i].WKPU_Channel)
            {
                if((tmp_u32WisrReg & ((uint32)0x1U << cPmm_Lpm_atIcuWKCfg[i].WKPU_Channel)) != 0u)
                {
                    tmp_bRtn = TRUE;
                    Pmm_Hpm_EnterSleepSetWakeupEvents((Pmm_Lpm_WakeResourceType_e)cPmm_Lpm_atIcuWKCfg[i].Index);
                }
                else
                {}
            }
            else
            {}
        }
        else
        {}
    }

    return tmp_bRtn;
}



/***********************************************************************************************************************
 *  Pmm_Hpm_PreEnterSleep
 **********************************************************************************************************************/
/*! \brief
 *  \details
 *  \param[in]
 *  \param[in]
 *
 *  \pre         
 *  \return
 *  \return
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
extern boolean gPmm_Hpm_bShutdownSyncCore0;
extern boolean gPmm_Hpm_bShutdownSyncCore1;

void Pmm_Hpm_PreEnterSleep(void)
{
    uint8 i;

    Pmm_Hpm_CopySacCodeToRAM();
    
    gPmm_Lpm_u32DiWakeupSrc_RAM = 0u;
    gPmm_Lpm_u16AiWakeupSrc_RAM = 0u;
    for(i=0u;i <= (uint8)IOHWAB_AI_WD_MAX;i++)
    {
        gPmm_Lpm_au16AdcValue_RAM[i] = 0u;
    }
    Pmm_Lpm_ClearSleepTime();


/*******************Don't change the code order for all platform********************/
    Pmm_Hpm_DisableAllInt();    
    //First Set ICU wake up src, then set sbc CAN wakeup mode
    Pmm_Hpm_EnterSleepEnableWakeupSource();  

    Pmm_Hpm_ResetAllPeripheralStatus();


    //enter to Low power
    while(1U)
    {
        if((gPmm_Hpm_bShutdownSyncCore0 == 1U)&&(gPmm_Hpm_bShutdownSyncCore1 == 1U))
        {
        	Pmm_Hpm_CheckModeTransition();
        }
    }
}

/***********************************************************************************************************************
 *  Pmm_Hpm_CheckModeTransition
 **********************************************************************************************************************/
/*! \brief
 *  \details
 *  \param[in]
 *  \param[in]
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
void Pmm_Hpm_CheckModeTransition(void)
{
    uint32 tmp_u32WISR;
    uint32 tmp_u32WRER;
    while (1U)
    {
        tmp_u32WISR = WKPU.WISR.R;
        tmp_u32WRER = WKPU.WRER.R;
        if(( tmp_u32WISR & tmp_u32WRER ) != 0U) //wake up source is enabled and flag
        {
            //First save wakeup events
            (void)Pmm_Hpm_EnterSleepCheckIcuWakeup();
            /*Perform MCU_FUNC_RESET*/
            /*Or mode change and jump to your wakeup function*/
        }
    }
}



/***********************************************************************************************************************
 *  Pmm_Hpm_GetWakeupEvents
 **********************************************************************************************************************/
/*! \brief    Get wakeup source of corresponding index
 *  \details   Get wakeup source of corresponding index
 *  \param[in]
 *  \param[in]
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
Pmm_Lpm_WakeResourceType_e Pmm_Hpm_GetWakeupEvents(uint8 u8Index)
{
    return gPmm_Lpm_aeWakeupEvents_RAM[u8Index];
}

/***********************************************************************************************************************
 *  Pmm_Hpm_vDisableINT
 **********************************************************************************************************************/
/*! \brief
 *  \details
 *  \param[in]
 *  \param[in]
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static void Pmm_Hpm_DisableAllInt(void)
{
    uint8 i;
/********************  ADC  *********************************/
    // disable ADC interrupt

    //clear ADC interrupt Pending flag

/********************  GPT  *********************************/
  
}

/***********************************************************************************************************************
 *  Pmm_Hpm_ResetAllPeripheralStatus
 **********************************************************************************************************************/
/*! \brief
 *  \details
 *  \param[in]
 *  \param[in]
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/

static void Pmm_Hpm_ResetAllPeripheralStatus(void)
{
    ASM_KEYWORD(" wrteei 0");
    //Reset All Peripheral
    ASM_KEYWORD(" wrteei 1");
}


/***********************************************************************************************************************
 *  Pmm_Hpm_PreEnterReset
 **********************************************************************************************************************/
/*! \brief
 *  \details
 *  \param[in]
 *  \param[in]
 *
 *  \pre         -
 *  \return
 *  \return
 *  \context
 *  \reentrant
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
void Pmm_Hpm_PreEnterReset(void)
{
    Pmm_Hpm_DisableAllInt();
    Pmm_Hpm_ResetAllPeripheralStatus();

    (void)Mcu_InitClock(McuConf_McuClockSettingConfig_McuClockSettingConfig_PreStb);
    (void)Mcu_SetMode(McuConf_McuModeSettingConf_McuMode_PreStb);

}
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#define Pmm_Hpm_START_SEC_CODE
#include "Pmm_Hpm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Pmm_Hpm_CODE) Pmm_Hpm_McuSleepTime_Operation(P2VAR(uint32, AUTOMATIC, RTE_PMM_HPM_APPL_VAR) sleepTime) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Pmm_Hpm_vMcuSleepTime
 *********************************************************************************************************************/
    *sleepTime = gPmm_Lpm_u32SleepTime_RAM;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Pmm_Hpm_PowOnResetFlag_Operation
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Operation> of PortPrototype <PowOnResetFlag>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void Pmm_Hpm_PowOnResetFlag_Operation(boolean *pbPowOnRstSts)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Pmm_Hpm_vPowOnResetFlag_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Runnable Entity Name: Pmm_Hpm_vWakeUpSource
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Operation> of PortPrototype <WakeupSource>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void Pmm_Hpm_vWakeUpSource(uint8 *pu8WkSrcEvent, uint16 *pu16AdcWkSrcChn, uint32 *pu32DiWkSrcChn)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Pmm_Hpm_vWakeUpSource_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Pmm_Hpm_CODE) Pmm_Hpm_WakeUpSource_Operation(P2VAR(uint8, AUTOMATIC, RTE_PMM_HPM_APPL_VAR) pu8WkSrcEvent, P2VAR(uint16, AUTOMATIC, RTE_PMM_HPM_APPL_VAR) pu16AdcWkSrcChn, P2VAR(uint32, AUTOMATIC, RTE_PMM_HPM_APPL_VAR) pu32DiWkSrcChn) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Pmm_Hpm_vWakeUpSource
 *********************************************************************************************************************/
    *pu16AdcWkSrcChn = gPmm_Lpm_u16AiWakeupSrc_RAM;
    *pu32DiWkSrcChn  = gPmm_Lpm_u32DiWakeupSrc_RAM;
    *pu8WkSrcEvent   = (uint8)gPmm_Lpm_aeWakeupEvents_RAM[0U];
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Pmm_Hpm_vMcuSleepTime
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Operation> of PortPrototype <McuSleepTime>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void Pmm_Hpm_vMcuSleepTime(uint32 *sleepTime)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Pmm_Hpm_vMcuSleepTime_doc
 *********************************************************************************************************************/


FUNC(void, Pmm_Hpm_CODE) Pmm_Hpm_FastSleep_Operation(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Pmm_Hpm_vMcuSleepTime
 *********************************************************************************************************************/
    Rte_Write_Request_ESH_FastSleepFlg_requestedMode(1);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define Pmm_Hpm_STOP_SEC_CODE
#include "Pmm_Hpm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


