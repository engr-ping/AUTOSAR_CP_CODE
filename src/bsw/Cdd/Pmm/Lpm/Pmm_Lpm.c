/*****************************************************************************************************************
******************************************************************************************************************
*  Copyright (C) .                                                                            
*  All rights reserved.                                                                                           
******************************************************************************************************************
*  FileName: Pmm_Sac                                                                                             
*  Content:  Power Mode Management for Sleep Awake Control
*  Category: Sleep Awake Control Management
******************************************************************************************************************
*  Revision Management                                                                                       
*  yyyy.mm.dd    name              version      description                                                       
*  ----------    --------          -------      -----------------------------------                               
*  2026.03.23    clipping            v0001        Frist edit                                                        
******************************************************************************************************************
******************************************************************************************************************/

/* Include Headerfiles  */
/* PRQA S 0286,0303,0305,0662,1006,1281,2983,2987,3006,3387,3432,4391,4399 EOF*/
#include "Pmm_Lpm.h"
#include "Pmm_Lpm_LCfg.h"
#include "VRM.h"
#include "Reg_eSys_WKPU.h"
#include "Mcu_MagicCarpet_LLD.h"
#include "Reg_eSys_SIUL.h"
#include "Reg_eSys_MagicCarpet.h"
#include "Reg_eSys_DSPI.h"
#include "IoHwAb_DigitalInput_Cfg.h"
#include "IoHwAb_AnalogInput_Cfg.h"
#include "spc58xg.h"
#include "IoHwAb_DigitalInput.h"
#include "IoHwAb_AnalogInput.h"
#include "VRM_Cfg.h"

/*************************************************************************
*    Local Macros -- Macros used in this file only
*************************************************************************/
#define SELCTL_16MHz_IRC 0x0U   /* Internal RC Osc */
#define DIVIDEBY1 0x0U

/*---------ADC MACROS---------*/
/*     ADC MCR register definitions    */

#define ADC_MCR_OWREN (1UL << 31U)

/*     ADC IMR register definitions    */
#define ADC_IMR_MSKEOC (1U << 1U)
#define ADC_IMR_MSKECH (1U << 0U)
/*     ADC ISR register definitions    */
#define ADC_B0_CH(n) (1u << (n % 32U))

#define PMM_LPM_READ_DI(sn) (*gPmm_Lpm_atDiChanWkCfg_RAM[IOHWAB_DI_WD_##sn].pVaribleType = \
(boolean)(SIUL2.GPDI[gPmm_Lpm_atDiChanWkCfg_RAM[IOHWAB_DI_WD_##sn].DiChannel].B.PDI  ^  gPmm_Lpm_atDiChanWkCfg_RAM[IOHWAB_DI_WD_##sn].InvertType))


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
void Pmm_Lpm_MainFunction(void);

static void    Pmm_Lpm_McuInit(void);
static void    Pmm_Lpm_PortInit(void);
static void    Pmm_Lpm_AdcInit(void);
static void    Pmm_Lpm_DelayUS(uint16 u16time);
static void    Pmm_Lpm_EnterStandby(void );
static void    Pmm_Lpm_ExitStandby(void );
static void    Pmm_Lpm_EnableRTC(void);
static uint32  Pmm_Lpm_ScanDiWakeupSrc(void);
static uint32  Pmm_Lpm_ScanAiWakeupSrc(void);
static boolean Pmm_Lpm_CheckIcuWakeup(void);
static void    Pmm_Lpm_SetWakeupEvents(Pmm_Lpm_WakeResourceType_e WakeupSource);
static uint16  Pmm_Lpm_GetPup1CompensateFactor(uint16 u16PupFvAd);
static uint16  Pmm_Lpm_VoltageCompensate( uint16 u16AdValue, uint16 u16Factor );
static boolean Pmm_Lpm_AdcWkCompare(uint16 u16AdcLastValue,uint16 u16AdcValue,uint8 adWkChannel);

static void    Pmm_Lpm_AppTimer(void);
static void    Pmm_Lpm_SbcEnterToStopMode(void);
static void    Pmm_Lpm_ExtWdTrigger(void);

static void Pmm_Lpm_LFSrcSpiDeinit(void);
static void Pmm_Lpm_LFSrcSpiInit(void);
static void Pmm_Lpm_LFCSLow(void);
static void Pmm_Lpm_LFCSHigh(void);
static void Pmm_Lpm_LFSrcSpiTransmit(uint8 *DataSendBuf,uint8 *DataReceiveBuf, uint8 u8DataLength);
static void Pmm_Lpm_LFLowPowerMode(void);

/*************************************************************************
*  Global Variables Definition -- Create global variables here
*************************************************************************/
/* Store the confirmed wakeup reason */

/*************************************************************************
*  Others -- Variables, Functions, etc. created in other C files
*************************************************************************/
extern uint32 __SP_INIT;

/*************************************************************************
*    Const Variables Definition -- this would be configured according to different project
*************************************************************************/
extern void _start_CyclicWakeUp(void);

/*********************************************************************************
*
*    Global Variables In RAM
*
***********************************************************************************/


#define LPM_START_PROTECTED_RAM
#include "MemMap.h"

/* Record Raw wakeup resource for moniter */
Pmm_Lpm_WakeResourceType_e gPmm_Lpm_aeWakeupEvents_RAM[LPM_RECORD_MORNITER_DATA_SIZE];
uint16 gPmm_Lpm_au16AdcValue_RAM[(uint8)((uint8)IOHWAB_AI_WD_MAX + 1U)];
uint32 gPmm_Lpm_u32DiWakeupSrc_RAM;
uint16  gPmm_Lpm_u16AiWakeupSrc_RAM;
Pmm_Lpm_IcuWakeupSrc_t gPmm_Lpm_atIcuWKCfg_RAM[PMM_LPM_ICU_WK_SRC_NUM];
Pmm_Lpm_AiChannelInfo_t gPmm_Lpm_atAiChanCfg_RAM[(uint8)((uint8)IOHWAB_AI_WD_MAX + 1U)];
Pmm_Lpm_DiChannelInfo_t gPmm_Lpm_atDiChanWkCfg_RAM[IOHWAB_DI_WD_MAX];
Pmm_Lpm_PortType_t gPmm_Lpm_atPortCfg_RAM[PMM_LPM_PORT_MAXNUM];
Pmm_Lpm_AiCfgType_t gPmm_Lpm_atAdWkupSrcPrjCfg_RAM[IOHWAB_AI_WD_MAX];
boolean gPmm_Lpm_abDiWkpSrcEnable_RAM[IOHWAB_DI_WD_MAX];

IoHwAb_DI_WakeUp_e gPmm_Lpm_aeWakeupParam_RAM[ENUM_INPUT_CHANNEL_ALL_NUM];
IoHwAb_u8GetADFuncPtr gPmm_Lpm_apu8GetWakeUpADFuncTab_RAM[IOHWAB_AI_WD_MAX];
boolean gPmm_Lpm_bWakeFlag_RAM;
uint32 gPmm_Lpm_u32SleepTime_RAM;

uint8  gPmm_Lpm_u8OpcChnEn_RAM;

uint32 gPmm_Lpm_u32WelcomeLightSleepTime_RAM;
uint32 gPmm_Lpm_u32WelcomeLightPollingTime_RAM;
boolean gPmm_Lpm_bWDLRunOnce_RAM;

uint8 gPmm_Lpm_u8lFSrvTx1_RAM;
uint8 gPmm_Lpm_au8LFSrvTx2_RAM[3];
uint8 gPmm_Lpm_au8LFSrvTx3_RAM[4];
uint8 gPmm_Lpm_au8LFSrvRX_RAM[4];


#define LPM_STOP_PROTECTED_RAM
#include "MemMap.h"


/*********************************************************************************
*
*    LPM Work to RAM
*
***********************************************************************************/
#define LPM_START_SEC_CODE_RAM
#include "MemMap.h"

/***********************************************************************************************************************
 *  Pmm_Lpm_SleepActivity
 **********************************************************************************************************************/
/*! \brief       Prepare the stack pointer for cyclic wakeup
 *  \details      Prepare the SP for C function
 *  \param[in]  N/A
 *  \param[in]  N/A
 *
 *  \pre         - CADRR0 is set to Pmm_Lpm_SleepActivity before enter standby
 *  \return     - N/A
 *  \return     - N/A
 *  \context   -
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
__attribute__((aligned(4))) void Pmm_Lpm_SleepActivity(void)
{
    ASM_KEYWORD(".globl _start_CyclicWakeUp");
    ASM_KEYWORD("_start_CyclicWakeUp:");
    ASM_KEYWORD("e_lis       r1,__SP_INIT@h");      /* Initialize stack pointer r1 to value in the linker command file.*/
    ASM_KEYWORD("e_or2i      r1,__SP_INIT@l");
    ASM_KEYWORD("e_stwu      r1, -64(r1)");         /* Terminate stack.*/
    ASM_KEYWORD("e_bl Pmm_Lpm_MainFunction");
}

/***********************************************************************************************************************
 *  Pmm_Lpm_MainFunction
 **********************************************************************************************************************/
/*! \brief       MainFunction when cyclic wakeup
 *  \details      Init MCU/ADC/Port -->check wakeup source->wakeup/continue to sleep
 *  \param[in]  N/A
 *  \param[in]  N/A
 *
 *  \pre         - called by Pmm_Lpm_SleepActivity
 *  \return     - Never Return
 *  \return     - N/A
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
void Pmm_Lpm_MainFunction(void)
{
    boolean tmp_bICUWPFlag = FALSE;
    uint32 tmp_u32DiWakeupSrc = 0x0U;
    uint32 tmp_u32AiWakeupSrc = 0x0U;

    Pmm_Lpm_McuInit();
    Pmm_Lpm_PortInit();

    Pmm_Lpm_AppTimer();
    
    Pmm_Lpm_EnablePup1();
    Pmm_Lpm_ExtWdTrigger();

    gPmm_Lpm_u32WelcomeLightSleepTime_RAM +=10u;
    
    if((gPmm_Lpm_bWDLRunOnce_RAM == TRUE)&&(gPmm_Lpm_u32WelcomeLightSleepTime_RAM >= gPmm_Lpm_u32WelcomeLightPollingTime_RAM))
    {
        Pmm_Lpm_LFSrcSpiInit();
        Pmm_Lpm_LFLowPowerMode();
        Pmm_Lpm_ExtWdTrigger(); 
        gPmm_Lpm_bWDLRunOnce_RAM = FALSE;
    }

    tmp_bICUWPFlag = Pmm_Lpm_CheckIcuWakeup();

    /*Whether ICU wakeup event detected
    *  FALSE: check di/ai wakeup event
    *  TRUE : Exit standby
    */
    if((boolean)FALSE == tmp_bICUWPFlag)
    {
        Pmm_Lpm_AdcInit();

        /*16M-delay for 1300 us*/
        Pmm_Lpm_DelayUS(1300U);

        tmp_u32DiWakeupSrc = Pmm_Lpm_ScanDiWakeupSrc();
        gPmm_Lpm_u32DiWakeupSrc_RAM = tmp_u32DiWakeupSrc;

        tmp_u32AiWakeupSrc = Pmm_Lpm_ScanAiWakeupSrc();
        gPmm_Lpm_u16AiWakeupSrc_RAM = (uint16)tmp_u32AiWakeupSrc;

		Pmm_Lpm_DisablePup1();

        tmp_bICUWPFlag = Pmm_Lpm_CheckIcuWakeup();
        if((0x0U != tmp_u32DiWakeupSrc) || (0x0U != tmp_u32AiWakeupSrc) || ((boolean)FALSE != tmp_bICUWPFlag))
        {
            Pmm_Lpm_ExitStandby();
        }
        else
        {
            Pmm_Lpm_EnableRTC();
            // clear CTU and RTC Interrupt Flag
            Pmm_Lpm_EnterStandby();
        }
    }
    else
    {
        Pmm_Lpm_ExitStandby();
    }
}
/***********************************************************************************************************************
 *  Pmm_Lpm_McuInit
 **********************************************************************************************************************/
/*! \brief     Init MCU when cyclic wakeup
 *  \details    Open the power of SIUL/DSPI4(Ext Watchdog)/ADC
 *  \param[in]  N/A
 *  \param[in]  N/A
 *
 *  \pre         - SP OK
 *  \return     - N/A
 *  \return     - N/A
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static void Pmm_Lpm_McuInit(void)
{
    //mcu init - mode/clock
    // init driver
}

/***********************************************************************************************************************
 *  Pmm_Lpm_CheckIcuWakeup
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
static boolean Pmm_Lpm_CheckIcuWakeup(void)
{
    uint8 i;
    boolean tmp_bRtn = FALSE;
    uint32 tmp_u32WisrReg;

    tmp_u32WisrReg = 0; //IcuWakeup check

    for(i = 0x0U; i < PMM_LPM_ICU_WK_SRC_NUM; i++)
    {
        if(TRUE == gPmm_Lpm_atIcuWKCfg_RAM[i].IsEnable)
        {
            if((LPM_WKPU_00 != gPmm_Lpm_atIcuWKCfg_RAM[i].WKPU_Channel)&&(LPM_WKPU_01 != gPmm_Lpm_atIcuWKCfg_RAM[i].WKPU_Channel))
            {
                if((tmp_u32WisrReg & ((uint32)0x1U << gPmm_Lpm_atIcuWKCfg_RAM[i].WKPU_Channel)) != 0u)
                {
                    tmp_bRtn = TRUE;
                    Pmm_Lpm_SetWakeupEvents((Pmm_Lpm_WakeResourceType_e)gPmm_Lpm_atIcuWKCfg_RAM[i].Index);
                }
                else
                {
                     /*****Nothing to do*****/
                }
            }
            else
            {
                /*****Nothing to do*****/
            }
        }
        else
        {
            /*****Nothing to do*****/
        }
    }

    return tmp_bRtn;
}

/***********************************************************************************************************************
 *  Pmm_Lpm_LFSrcSpiInit
 **********************************************************************************************************************/
/*! \brief     Digital input scan chip spi init
 *  \details
 *  \param[in] N/A
 *  \param[in] N/A
 *
 *  \pre        - N/A
 *  \return     - N/A
 *  \return     - N/A
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static void Pmm_Lpm_LFSrcSpiInit(void)
{

    Pmm_Lpm_LFCSHigh();

    //Spi Init
}

/***********************************************************************************************************************
 *  Pmm_Lpm_LFSrcSpiDeinit
 **********************************************************************************************************************/
/*! \brief     Digital input scan chip spi deinit
 *  \details
 *  \param[in] N/A
 *  \param[in] N/A
 *
 *  \pre        - N/A
 *  \return     - N/A
 *  \return     - N/A
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static void Pmm_Lpm_LFSrcSpiDeinit(void)
{
    /* Stop DSPI transfers */
}

/***********************************************************************************************************************
 *  Pmm_Lpm_LFCSHigh
 **********************************************************************************************************************/
/*! \brief     Digital input scan chip spi init
 *  \details
 *  \param[in] N/A
 *  \param[in] N/A
 *
 *  \pre        - N/A
 *  \return     - N/A
 *  \return     - N/A
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static void Pmm_Lpm_LFCSHigh(void)
{ 
    /* Output the high level */
    /* change CS to GPIO mode */
}

/***********************************************************************************************************************
 *  Pmm_Lpm_LFCSHigh
 **********************************************************************************************************************/
/*! \brief     Digital input scan chip spi init
 *  \details
 *  \param[in] N/A
 *  \param[in] N/A
 *
 *  \pre        - N/A
 *  \return     - N/A
 *  \return     - N/A
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static void Pmm_Lpm_LFCSLow(void)
{
    /* Output the low level*/
    /* change CS to GPIO mode */
}

/***********************************************************************************************************************
 *  Pmm_Lpm_LFSrcSpiTransmit
 **********************************************************************************************************************/
/*! \brief     Send/Recv MC33978 SPI
 *  \details
 *  \param[in] send spi data
 *  \param[in] N/A
 *
 *  \pre         - spi init done
 *  \return     - Recv spi data
 *  \return     - N/A
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static void Pmm_Lpm_LFSrcSpiTransmit(uint8 *DataSendBuf,uint8 *DataReceiveBuf, uint8 u8DataLength)
{
    uint8 tmp_u8LFDataLength;
    
    Pmm_Lpm_LFCSLow();
    
    /*set lf*/
    
    Pmm_Lpm_LFCSHigh();  /* Change CS to high*/
}


/***********************************************************************************************************************
 *  Pmm_Lpm_PortInit
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
static void Pmm_Lpm_PortInit(void)
{
    uint8 index;

    for(index = 0U;index <(uint8)PMM_LPM_PORT_MAXNUM; index++)
    {

    }
}


/***********************************************************************************************************************
 *  Pmm_Lpm_AdcInit
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
static void Pmm_Lpm_AdcInit(void)
{
    uint8 i;
    uint32 u32R0Mask = 0x0u;
    uint32 u32R1Mask = 0x0u;
    /*
      Main Configuration Register (MCR)
      Main Status Register (MSR) - R
      Interrupt Status Register (ISR)
      Internal Channel Interrupt Pending Register n (ICIPRn)
      Interrupt Mask Register (IMR)
      Internal Channel Interrupt Mask Register n (ICIMRn)
      Conversion Timing Register n (CTRn)
      Internal Channel Normal Conversion Mask Register n (ICNCMRn)
      Power Down Exit Delay Register (PDEDR)
      Internal Channel Data Register n (ICDRn)*/

    for (i = 0; i < ((uint8)IOHWAB_AI_WD_MAX + 1U); i++)
    {
        if(gPmm_Lpm_atAiChanCfg_RAM[i].AiChannel < 32U)
        {
            u32R0Mask |= (uint32)ADC_B0_CH(gPmm_Lpm_atAiChanCfg_RAM[i].AiChannel);
        }
        else
        {
            u32R1Mask |= (uint32)ADC_B0_CH(gPmm_Lpm_atAiChanCfg_RAM[i].AiChannel);
        }
    }

}



static void Pmm_Lpm_vReadDiValue(void)
{


}

/***********************************************************************************************************************
 *  Pmm_Lpm_ScanDiWakeupSrc
 **********************************************************************************************************************/
/*! \brief     Read Digital input status  and return digital input wakeup src
 *  \details
 *  \param[in] N/A
 *  \param[in] N/A
 *
 *  \pre         - Port init done
 *  \return     - N/A
 *  \return     - N/A
 *  \context
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace
 **********************************************************************************************************************/
static uint32 Pmm_Lpm_ScanDiWakeupSrc(void)
{
    volatile uint8 i = 0u;
    uint32 tmp_u32DiWakeupSrc;
    uint32 tmp_u32DiWakeupEnble = 0x0u;


    Pmm_Lpm_vReadDiValue();

    tmp_u32DiWakeupSrc = IoHwAb_u32DigitalInputWakeUpCompare();

    for(i = (uint8)0; i < (uint8)IOHWAB_DI_WD_MAX ; i++)
    {
        if(gPmm_Lpm_abDiWkpSrcEnable_RAM[i] == (boolean)TRUE)
        {
        tmp_u32DiWakeupEnble |= ((uint32)1u << i);
        }
    }

    tmp_u32DiWakeupSrc &= tmp_u32DiWakeupEnble;

    if(tmp_u32DiWakeupSrc != 0u)
    {
        Pmm_Lpm_SetWakeupEvents(LPM_CW_DI);
    }
    else
    {}

    return tmp_u32DiWakeupSrc;
}

/***********************************************************************************************************************
 *  Pmm_Lpm_ScanAiWakeupSrc
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
static uint32 Pmm_Lpm_ScanAiWakeupSrc(void)
{
    uint8 i;
    uint16 tmp_u16AiValue;
    uint16 tmp_u16KVPup1;
    uint32 tmp_u32WakeupSig = 0x0u;


    gPmm_Lpm_au16AdcValue_RAM[PMM_LPM_AI_PUP1_FV] = SAR_ADC_12BIT_B0.ICDR[gPmm_Lpm_atAiChanCfg_RAM[PMM_LPM_AI_PUP1_FV].AiChannel].B.CDATA;

    tmp_u16KVPup1 = Pmm_Lpm_GetPup1CompensateFactor(gPmm_Lpm_au16AdcValue_RAM[PMM_LPM_AI_PUP1_FV]);

    for (i = 0U; i < (uint8)IOHWAB_AI_WD_MAX; i++)
    {
        if(TRUE == gPmm_Lpm_atAdWkupSrcPrjCfg_RAM[i].bAiChnEn)
        {
            gPmm_Lpm_au16AdcValue_RAM[i] = SAR_ADC_12BIT_B0.ICDR[gPmm_Lpm_atAiChanCfg_RAM[i].AiChannel].B.CDATA;

            if(VRM_COMPENSATE_TYPE_PUP1 == gPmm_Lpm_atAiChanCfg_RAM[i].u8PupCompType)
            {
                tmp_u16AiValue = (Pmm_Lpm_VoltageCompensate(gPmm_Lpm_au16AdcValue_RAM[i], tmp_u16KVPup1));
            }
            else
            {
                tmp_u16AiValue = gPmm_Lpm_au16AdcValue_RAM[i];
            }
            if(Pmm_Lpm_AdcWkCompare(gIoHwAb_au16AISignalWakeUpSaved[i], tmp_u16AiValue, i) == TRUE)
            {
                tmp_u32WakeupSig |= ((uint32)1u) << i;
            }
            else
            {
                  /*****Nothing to do*****/
            }
        }
        else
        {
            /*****Nothing to do*****/
        }
    }

    if(tmp_u32WakeupSig != 0U)
    {
        Pmm_Lpm_SetWakeupEvents(LPM_CW_AI);
    }
    else
    { 
        /*****Nothing to do*****/
    }

    return tmp_u32WakeupSig;
}

static uint16 Pmm_Lpm_GetPup1CompensateFactor(uint16 u16PupFvAd)
{
    uint16 tmp_u16KVPup1;
    uint32 tmp_u32AdcCalVal;
    uint32 tmp_u32Value;

    tmp_u32Value =  (uint32)(VRM_BASIC_VOLTAGE / 1000u * VRM_PUP1_R2 * VRM_MAX_AD_HEX / 5u * VRM_COMPENSATE_PRECISION / (VRM_PUP1_R1 + VRM_PUP1_R2));

	if (u16PupFvAd == 0U)
	{
		/* saturated to the max value */
		tmp_u16KVPup1 = 0xffffu;
	}
	else
	{
		/* temp variable to hold intermediate result */
		tmp_u32AdcCalVal = tmp_u32Value/u16PupFvAd;
		/* handle overflow */
		if (tmp_u32AdcCalVal > 0xffffu)
		{
			tmp_u16KVPup1 = 0xffffu;
		}
		/* otherwise just get the result */
		else
		{
			tmp_u16KVPup1 = (uint16)tmp_u32AdcCalVal;
		}
	}

	return tmp_u16KVPup1;
}

static uint16 Pmm_Lpm_VoltageCompensate( uint16 u16AdValue, uint16 u16Factor )
{
    uint32 tmp_u32AdcCalVal;
    uint16 tmp_u16Rtn;

    tmp_u32AdcCalVal = (uint32)(((uint32)u16AdValue * u16Factor) / 1024u);

    if( tmp_u32AdcCalVal > 4095u)
    {
        tmp_u16Rtn = 4095u;
    }
    else
    {
        tmp_u16Rtn = (uint16)tmp_u32AdcCalVal;
    }

    return(tmp_u16Rtn);
}


static boolean Pmm_Lpm_AdcWkCompare(uint16 u16AdcLastValue,uint16 u16AdcValue,uint8 adWkChannel)
{
    uint8 tmp_u8lastShift;
    uint8 tmp_u8curShift;
    uint16 tmp_u16Dvalue;
    uint8 tmp_bRtnVal;
    if(PMM_LPM_ADC_WKP_BY_SHIFT == gPmm_Lpm_atAdWkupSrcPrjCfg_RAM[adWkChannel].eAdcWkType)
    {
        tmp_u8lastShift = (*(gPmm_Lpm_apu8GetWakeUpADFuncTab_RAM[adWkChannel]))(u16AdcLastValue);
        tmp_u8curShift = (*(gPmm_Lpm_apu8GetWakeUpADFuncTab_RAM[adWkChannel]))(u16AdcValue);
        if(tmp_u8lastShift != tmp_u8curShift)
        {
            tmp_bRtnVal = 1U;
        }
        else
        {
            tmp_bRtnVal = 0U;
        }
    }
    else
    {
        if(u16AdcLastValue >= u16AdcValue)
        {
             tmp_u16Dvalue = u16AdcLastValue - u16AdcValue;
        }
        else
        {
            tmp_u16Dvalue = u16AdcValue - u16AdcLastValue;
        }
        if(tmp_u16Dvalue > gPmm_Lpm_atAdWkupSrcPrjCfg_RAM[adWkChannel].u16Tolerance)
        {
            tmp_bRtnVal = 1U;
        }
        else
        {
            tmp_bRtnVal = 0U;
        }
    }

    return tmp_bRtnVal;
}

/***********************************************************************************************************************
 *  Pmm_Lpm_ExitStandby
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
static void Pmm_Lpm_ExitStandby(void)
{

}

/***********************************************************************************************************************
 *  Pmm_Lpm_EnterStandby
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
static void Pmm_Lpm_EnterStandby(void)
{
    uint32 tmp_u32WISR;
    uint32 tmp_u32WRER;

	Pmm_Lpm_SbcEnterToStopMode();

}

/***********************************************************************************************************************
 *  Pmm_Lpm_EnableRTC
 **********************************************************************************************************************/
/*! \brief      Enable RTC to cyclical wake up MCU
 *  \details     RTC(LP timer) use LPRC div 8 as clock in Standby domain - 128KHz
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
static void Pmm_Lpm_EnableRTC(void)
{

}

/***********************************************************************************************************************
 *  Pmm_Lpm_ExtWdTrigger
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
static void Pmm_Lpm_ExtWdTrigger(void)
{

}

/***********************************************************************************************************************
 *  Pmm_Lpm_SbcEnterToStopMode
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
static void Pmm_Lpm_SbcEnterToStopMode(void)
{

}

/***********************************************************************************************************************
 *  Pmm_Lpm_SetWakeupEvents
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
static void Pmm_Lpm_SetWakeupEvents(Pmm_Lpm_WakeResourceType_e WakeupSource)
{
    uint8 index;
    gPmm_Lpm_bWakeFlag_RAM = TRUE;
    /* Record raw wakeup reason for moniter */
    for(index = (uint8)(LPM_RECORD_MORNITER_DATA_SIZE - 1U); index > 0U; index--)
    {
        gPmm_Lpm_aeWakeupEvents_RAM[index] = gPmm_Lpm_aeWakeupEvents_RAM[(uint8)(index - 1U)];
    }

    gPmm_Lpm_aeWakeupEvents_RAM[0U] = WakeupSource;
}

/***********************************************************************************************************************
 *  Pmm_Lpm_DelayUS
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
static void Pmm_Lpm_DelayUS(uint16 u16time)
{
    uint16 index = 0x0U;
    uint16 tmp_u16Cnt = 8U * u16time;

    /*16M-delay for Time us
    * while(index ++ < Time) would be optimized
    */
    while(index < tmp_u16Cnt)
    {
         index++;
    }
}


static void Pmm_Lpm_AppTimer(void)
{
    gPmm_Lpm_u32SleepTime_RAM += 10u;
}


static void Pmm_Lpm_LFLowPowerMode(void)
{
    uint8 i;

    for(i = 0u;i < 4u;i++)
    {
        gPmm_Lpm_au8LFSrvRX_RAM[i] = 0;
    }

    //stop polling mode.

    gPmm_Lpm_u8lFSrvTx1_RAM = 0;
    Pmm_Lpm_LFSrcSpiTransmit(&gPmm_Lpm_u8lFSrvTx1_RAM,gPmm_Lpm_au8LFSrvRX_RAM,1u);

    //delay time 1ms.
    Pmm_Lpm_DelayUS(1000u);

    //transfer to sleep mode.
    gPmm_Lpm_au8LFSrvTx2_RAM[0] = 0x02u;
    gPmm_Lpm_au8LFSrvTx2_RAM[1] = 0x4Fu;
    gPmm_Lpm_au8LFSrvTx2_RAM[2] = 0x8Bu;
    Pmm_Lpm_LFSrcSpiTransmit(gPmm_Lpm_au8LFSrvTx2_RAM,gPmm_Lpm_au8LFSrvRX_RAM,3u);

    //delay time 1ms.
    Pmm_Lpm_DelayUS(1000u);

    //get response.
    for(i = 0u;i < 4u;i++)
    {
        gPmm_Lpm_au8LFSrvTx3_RAM[i] = 0;
    }
    Pmm_Lpm_LFSrcSpiTransmit(gPmm_Lpm_au8LFSrvTx3_RAM,gPmm_Lpm_au8LFSrvRX_RAM,4u);

}



#define LPM_STOP_SEC_CODE_RAM
#include "MemMap.h"
/*********************************************************************************
*
*    LPM Work to RAM  END
*
***********************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


