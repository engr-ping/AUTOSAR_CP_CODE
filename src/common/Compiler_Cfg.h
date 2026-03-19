/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007 - 2013 by Vector Informatik GmbH.                                           All rights reserved.
 *
 *                Please note, that this file contains example configuration used by the 
 *                MICROSAR BSW. This code may influence the behaviour of the MICROSAR BSW
 *                in principle. Therefore, great care must be taken to verify
 *                the correctness of the implementation.
 *
 *                The contents of the originally delivered files are only examples respectively 
 *                implementation proposals. With regard to the fact that these functions
 *                are meant for demonstration purposes only, the liability of Vector Informatik
 *                shall be expressly excluded in cases of ordinary negligence, 
 *                to the extent admissible by law or statute.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  _Compiler_Cfg.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This File is a template for the Compiler_Cfg.h
 *                This file has to be extended with the memory and pointer classes for all BSW modules
 *                which where used.
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  MISRA VIOLATIONS
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Joachim Kalmbach              Jk            Vector Informatik GmbH
 *  Heike Honert                  Ht            Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-01  Jk                    Initial creation
 *  01.01.00  2007-12-14  Jk                    Component specific defines filtering added
 *  01.01.01  2008-12-17  Ht                    Improve list of components  (Tp_AsrTpCan,Tp_AsrTpFr,DrvMcu,DrvIcu added)
 *  01.01.02  2009-04-27  Ht                    support OEM specific _compiler_cfg.inc file, improve list of components 
 *                                              (Cp_XcpOnCanAsr, Il_AsrIpduM, If_VxFblDcm, If_VxFblVpm_Volvo_ab, DrvFls added)
 *  01.01.03  2009-04-24  Msr                   Renamed J1939_AsrBase as TpJ1939_AsrBase
 *  01.01.04  2009-06-03  Ht                    Improve list of components (Adc, Dio, Gpt, Pwm, Spi, Wdg, Fls, Port, Fim)
 *  01.02.00  2009-08-01  Ht                    Improve list of components (Fee_30_Inst2, Can, ...Sub)
 *                                              Support filtering for RTE
 *  01.02.01  2009-09-02  Lo                    add external Flash driver support
 *  01.02.02  2009-09-21  Lo                    add DrvFls_Mcs12xFslftm01ExtVx
 *                        Ht                    Improve list of components (CanTrcv_30_Tja1040dio,
 *                                                Eth, EthTrcv, EthIf, SoAd, TcpIp, EthSM)
 *  01.03.00  2009-10-30  Ht                    support R8: change EthTrcv to EthTrcv_30_Canoeemu
 *                                              support EthTrcv_30_Dp83848
 *                                              change CanTrcv_30_Xdio to CanTrcv_30___Your_Trcv__
 *                                              change CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1041
 *                                              change name FrTrcv to FrTrcv_30_Tja1080dio
 *                        Lo                    add Cp_AsrXcp
 *                        Ht                    add Cp_XcpOnFrAsr
 *  01.03.01  2010-01-13  Ht                    support SysService_AsrCal
 *  01.03.02  2010-02-15  Ht                   support SysService_SswRcs_Daimler, SysService_Tls, Tp_Http, 
 *                                                      SysService_Dns, SysService_Json, DrvTrans_GenericLindioAsr
 *                        Lo                    add Diag_AsrDem for all OEMs
 *                                              rename internal variables and filter methods
 *  01.04.00  2010-03-04  Ht                    change name FrTrcv_30_Tja1080dio to FrTrcv_30_Tja1080
 *  01.04.01  2010-03-10  Ht                    support DrvTrans_GenericFrAsr, DrvTrans_As8223FrspiAsr, DrvEep and If_AsrIfEa
 *  01.04.02  2010-04-07  Lo                    change IfFee to real components and add If_AsrIfWdV85xNec01Sub
 *  01.04.03  2010-06-11  Ht                    add CanTrcv_30_Tja1043
 *                        Lo                    add Il_AsrIpduMEbBmwSub
 *  01.04.04  2010-08-24  Ht                    add CanTrcv_30_Tle62512G, DrvEep_XAt25128EAsr, Tp_AsrTpFrEbBmwSub
 *  01.05.00  2010-08-24  Ht                    support R10:
 *                                              change LinTrcv_30_Tle7259dio to LinTrcv_30_Tle7259
 *  01.05.01  2010-10-14  Ht                    add VStdLib, SysService_SswScc, SysService_IpBase, SysService_Crypto
 *  01.05.02  2010-10-20  Ht                    support comments for Package Merge Tool
 *  01.05.03  2010-11-03  Ht                    add SysService_E2eLibTttechSub, SysService_E2ePwTttechSub
 *  01.05.04  2010-11-16  Ht                    add SysService_Exi, DrvTrans_Int6400EthAsr, Cdd_AsrCdd_Fiat, Diag_AsrDem_Fiat,
 *  01.05.05  2010-12-17  Ht                    add SysService_AsrSchM, DrvEep_XXStubAsr, DrvIcu_Tms570Tinhet01ExtVx
 *                                                  DrvWd_XTle4278gEAsr, DrvWd_XXStubAsr
 *  01.05.06  2011-02-17  Ht                    add DrvEed, SysService_AsrBswM
 *  01.05.07  2011-03-04  Ht                    add DrvTrans_Tja1055CandioAsr
 *                                              rename CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1040
 *                                              add SysService_XmlEngine
 *  01.06.00  2011-03-04  Ht                    support ASR4.0
 *                                              add Ccl_Asr4ComM, Ccl_Asr4SmCan, Nm_Asr4NmIf, Nm_AsrNmDirOsek
 *  01.06.01  2011-04-15  Ht                    add Diag_AsrDcm_<OEM>
 *  01.06.02  2011-06-17  Ht                    correct Diag_AsrDcm_<OEM>
 *                                              add Monitoring_AsrDlt and Monitoring_GenericMeasurement
 *  01.06.03  2011-09-01  Ht                    add DrvTrans_Tja1145CanSpiAsr, DrvTrans_E52013CanspiAsr, DrvFls_XXStubAsr,
 *                                              If_AsrIfFeeV85xNec05Sub, If_AsrIfFeeV85xNec06Sub, If_AsrIfFeeV85xNec07Sub
 *                                              SysService_AsrWdMTttechSub and If_AsrIfWdTttechSub
 *  01.06.04  2011-10-20  Ht                    ESCAN00054334: add If_AsrIfFeeTiSub
 *                                              ESCAN00054719: add Cdd_AsrCdd
 *  01.06.05  2011-12-09  Ht                    add Tp_IpV4, Tp_IpV6
 *  01.06.06  2011-12-14  Ht                    add Monitoring_RuntimeMeasurement
 *  01.06.07  2012-01-03  Ht                    add DrvI2c, SysService_Asr4BswM
 *  01.06.08  2012-01-31  Ht                    add DrvTrans_Ar7000EthAsr, DrvTrans_GenericEthmiiAsr
 *  01.06.09  2012-03-06  Ht                    add If_AsrIfFeeMb9df126Fuji01Sub, 
 *                                              Infineon_Tc1767Inf01Sub, Infineon_Tc178xInf01Sub, Infineon_Tc1797Inf01Sub, Infineon_Tc1797Inf02Sub
 *  01.06.10  2012-03-13  Ht                    add Gw_AsrPduRCfg5, Il_AsrComCfg5, Il_AsrIpduMCfg5, Cdd_AsrCddCfg5,
 *                                              Tp_Asr4TpCan, Diag_Asr4Dcm, Diag_Asr4Dem
 *  01.06.11  2012-03-20  Ht                    add Cp_AsrCcp, Cp_XcpOnTcpIpAsr
 *  01.07.00  2012-07-26  Ht                    add Nm_Asr4NmCan, Nm_Asr4NmFr, Infineon_Xc2000Inf01Sub, Ccl_Asr4ComMCfg5, SysService_Asr4BswMCfg5, SysService_Asr4EcuM, SysService_AsrRamTst,
 *                                                  Ccl_Asr4SmLin
 *                                              add define REGSPACE - add support for ASR specification 4.0 R3
 *  01.07.01  2012-10-23  Seu                   add SysService_XmlSecurity
 *  01.07.02  2013-12-16  Seu                   MISRA compliance: usage of character "'" removed, typos corrected
 *********************************************************************************************************************/
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/* Package Merger: Start Section CompilerCfgIncludes */


/* Package Merger: Stop Section CompilerCfgIncludes */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define AUTOSAR_COMSTACKDATA

#define MSR_REGSPACE  REGSPACE

/* Configurable memory class for pointers to registers (e.g. static volatile CONSTP2VAR(uint16, PWM_CONST, REGSPACE)). */
#define REGSPACE


/* due to compatibility to ASR 2.1 */
#define _STATIC_   STATIC
#define _INLINE_   INLINE

/* Package Merger: Start Section CompilerCfgModuleList */


/* include Rte Compiler_Cfg because the Rte sections are configuration dependent*/

/**********************************************************************************************************************
 *  CAN_30_CORE START
 *********************************************************************************************************************/

#define CAN_30_CORE_CODE        /* units public code */
#define CAN_30_CORE_STATIC_CODE /* units private code */

#define CAN_30_CORE_CONST
#define CAN_30_CORE_PBCFG

#define CAN_30_CORE_VAR_INIT
#define CAN_30_CORE_VAR_NO_INIT
#define CAN_30_CORE_VAR_CLEARED

#define CAN_30_CORE_APPL_CODE
#define CAN_30_CORE_APPL_VAR
#define CAN_30_CORE_VAR_PBCFG

/**********************************************************************************************************************
 *  CAN_30_CORE END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  VCAN_30_MCAN START 
 *********************************************************************************************************************/

#define VCAN_30_MCAN_CODE  /* should be same as CAN_30_CORE_CODE */
#define VCAN_30_MCAN_CODE_ISR
#define VCAN_30_MCAN_REGSPACE
#define VCAN_30_MCAN_CONST
#define VCAN_30_MCAN_PBCFG

#define VCAN_30_MCAN_APPL_CODE

#define VCAN_30_MCAN_VAR_INIT
#define VCAN_30_MCAN_VAR_NO_INIT
#define VCAN_30_MCAN_VAR_ZERO_INIT
#define VCAN_30_MCAN_VAR_PBCFG

#define VCAN_30_MCAN_MESSAGERAM

/*-------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************
 *  VCAN_30_MCAN END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CRYPTO_30_HWA START
 *********************************************************************************************************************/

#define CRYPTO_30_HWA_CODE
#define CRYPTO_30_HWA_APPL_DATA
#define CRYPTO_30_HWA_APPL_VAR
#define CRYPTO_30_HWA_VAR_ZERO_INIT
#define CRYPTO_30_HWA_CONST
#define CRYPTO_30_HWA_VAR_NOINIT

/**********************************************************************************************************************
 *  CRYPTO_30_HWA END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  ETH_30_TC4XXGETH START 
 *********************************************************************************************************************/

#define ETH_30_TC4XXGETH_CODE
#define ETH_30_TC4XXGETH_CODE_ISR

#define ETH_30_TC4XXGETH_CONST
#define ETH_30_TC4XXGETH_APPL_CONST
#define ETH_30_TC4XXGETH_PBCFG
#define ETH_30_TC4XXGETH_APPL_DATA
#define ETH_30_TC4XXGETH_APPL_VAR

#define ETH_30_TC4XXGETH_APPL_CODE

#define ETH_30_TC4XXGETH_VAR_NOINIT
#define ETH_30_TC4XXGETH_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  ETH_30_TC4XXGETH END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  FR START 
 *********************************************************************************************************************/

#define FR_CODE                                                       /* FR modules code qualifier */
#define FR_CODE_ISR                                                   /* module interrupt service routines */

#define FR_CONST                                                      /* FR constant memory */
#define FR_APPL_CONST                                                 /* Application constant memory, coming from outside of the module */
#define FR_PBCFG                                                      /* postbuild generated constant/flash */
#define FR_APPL_DATA                                                  /* memory class for pointers to application data (expected to be in RAM or ROM) passed via API */
#define FR_VAR_FRM_DATA                                               /* memory class for pointers to Flexray memory data in RAM */
#define FR_APPL_CODE                                                  /* memory class for pointers to application functions (e.g. call back function pointers) */

#define FR_VAR_NOINIT                                                 /* none initialized variables. To be used for all global or static variables that are never initialized */
#define FR_VAR_NOINIT_FAST                                            /* like FR_VAR_NOINIT, optimized access */
#define FR_VAR_ZERO_INIT




/**********************************************************************************************************************
 *  FR END
 *********************************************************************************************************************/





/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2023 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**        \file  Lin_Compiler_Cfg.inc
 *        \brief  AUTOSAR LIN Driver
 *
 *      \details  AUTOSAR LIN Driver for all target systems
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  LIN DRIVER START
 **********************************************************************************************************************/

#define LIN_CODE
#define LIN_CODE_FAST
#define LIN_CODE_ISR
#define LIN_APPL_CODE

#define LIN_CONST
#define LIN_CONST_FAST
#define LIN_PBCFG

#define LIN_VAR_PBCFG
#define LIN_VAR_INIT
#define LIN_VAR_NOINIT
#define LIN_VAR_ZERO_INIT
#define LIN_VAR_INIT_FAST
#define LIN_VAR_NOINIT_FAST
#define LIN_VAR_ZERO_INIT_FAST

#define LIN_VAR_INIT_NOCACHE
#define LIN_VAR_NOINIT_NOCACHE
#define LIN_VAR_ZERO_INIT_NOCACHE

#define LIN_APPL_VAR
#define LIN_VAR_REGS

/***********************************************************************************************************************
 *  LIN DRIVER END
 **********************************************************************************************************************/




 /**********************************************************************************************************************
 *  CAN_17_MCMCAN START
 *********************************************************************************************************************/

#define CAN_17_MCMCAN_CODE
#define CAN_17_MCMCAN_VAR_NOINIT
#define CAN_17_MCMCAN_VAR_POWER_ON_INIT
#define CAN_17_MCMCAN_VAR_FAST
#define CAN_17_MCMCAN_VAR
#define CAN_17_MCMCAN_CONST
#define CAN_17_MCMCAN_APPL_DATA
#define CAN_17_MCMCAN_APPL_CONST
#define CAN_17_MCMCAN_APPL_CODE
#define CAN_17_MCMCAN_CALLOUT_CODE

/**********************************************************************************************************************
 *  CAN_17_MCMCAN END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  ADC START
 *********************************************************************************************************************/

#define ADC_CODE
#define ADC_VAR_NOINIT
#define ADC_VAR_POWER_ON_INIT
#define ADC_VAR_FAST
#define ADC_VAR
#define ADC_CONST
#define ADC_APPL_DATA
#define ADC_APPL_CONST
#define ADC_APPL_CODE
#define ADC_CALLOUT_CODE

/**********************************************************************************************************************
 *  ADC END
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  DIO START
 *********************************************************************************************************************/

#define DIO_CODE
#define DIO_VAR_NOINIT
#define DIO_VAR_POWER_ON_INIT
#define DIO_VAR_FAST
#define DIO_VAR
#define DIO_CONST
#define DIO_APPL_DATA
#define DIO_APPL_CONST
#define DIO_APPL_CODE
#define DIO_CALLOUT_CODE

/**********************************************************************************************************************
 *  DIO END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  DMA START
 *********************************************************************************************************************/

#define DMA_CODE
#define DMA_VAR_NOINIT
#define DMA_VAR_POWER_ON_INIT
#define DMA_VAR_FAST
#define DMA_VAR
#define DMA_CONST
#define DMA_APPL_DATA
#define DMA_APPL_CONST
#define DMA_APPL_CODE
#define DMA_CALLOUT_CODE
#define DMA_PBCFG

/**********************************************************************************************************************
 *  DMA END
 *********************************************************************************************************************/
 

 /**********************************************************************************************************************
 *  FEE START
 *********************************************************************************************************************/

#define FEE_CODE
#define FEE_VAR_NOINIT
#define FEE_VAR_POWER_ON_INIT
#define FEE_VAR_FAST
#define FEE_VAR
#define FEE_CONST
#define FEE_APPL_DATA
#define FEE_APPL_CONST
#define FEE_APPL_CODE
#define FEE_CALLOUT_CODE
#define FEE_PBCFG
 
/**********************************************************************************************************************
 *  FEE END
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *  GPT START
 *********************************************************************************************************************/

#define GPT_CODE
#define GPT_VAR_NOINIT
#define GPT_VAR_POWER_ON_INIT
#define GPT_VAR_FAST
#define GPT_VAR
#define GPT_CONST
#define GPT_APPL_DATA
#define GPT_APPL_CONST
#define GPT_APPL_CODE
#define GPT_CALLOUT_CODE

/**********************************************************************************************************************
 *  GPT END
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  GTM START
 *********************************************************************************************************************/

#define GTM_CODE
#define GTM_VAR_NOINIT
#define GTM_VAR_POWER_ON_INIT
#define GTM_VAR_FAST
#define GTM_VAR
#define GTM_CONST
#define GTM_APPL_DATA
#define GTM_APPL_CONST
#define GTM_APPL_CODE
#define GTM_CALLOUT_CODE

/**********************************************************************************************************************
 *  GTM END
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *  ICU START
 *********************************************************************************************************************/

#define ICU_CODE
#define ICU_VAR_NOINIT
#define ICU_VAR_POWER_ON_INIT
#define ICU_VAR_FAST
#define ICU_VAR
#define ICU_CONST
#define ICU_APPL_DATA
#define ICU_APPL_CONST
#define ICU_APPL_CODE
#define ICU_CALLOUT_CODE

/**********************************************************************************************************************
 *  ICU END
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  IRQ START
 *********************************************************************************************************************/

#define IRQ_CODE
#define IRQ_VAR_NOINIT
#define IRQ_VAR_POWER_ON_INIT
#define IRQ_VAR_FAST
#define IRQ_VAR
#define IRQ_CONST
#define IRQ_APPL_DATA
#define IRQ_APPL_CONST
#define IRQ_APPL_CODE
#define IRQ_CALLOUT_CODE

/**********************************************************************************************************************
 *  IRQ END
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  MCU START
 *********************************************************************************************************************/

#define MCU_CODE
#define MCU_VAR_NOINIT
#define MCU_VAR_POWER_ON_INIT
#define MCU_VAR_FAST
#define MCU_VAR
#define MCU_CONST
#define MCU_APPL_DATA
#define MCU_APPL_CONST
#define MCU_APPL_CODE
#define MCU_CALLOUT_CODE

/**********************************************************************************************************************
 *  MCU END
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  MEM START
 *********************************************************************************************************************/

#define MEM_17_NVM_CODE
#define MEM_17_NVM_VAR_NOINIT
#define MEM_17_NVM_VAR_POWER_ON_INIT
#define MEM_17_NVM_VAR_FAST
#define MEM_17_NVM_VAR
#define MEM_17_NVM_CONST
#define MEM_17_NVM_APPL_DATA
#define MEM_17_NVM_APPL_CONST
#define MEM_17_NVM_APPL_CODE
#define MEM_17_NVM_CALLOUT_CODE

/**********************************************************************************************************************
 *  MEM END
 *********************************************************************************************************************/
 
  /**********************************************************************************************************************
 *  MEMACC START
 *********************************************************************************************************************/

#define MEMACC_CODE
#define MEMACC_VAR_NOINIT
#define MEMACC_VAR_POWER_ON_INIT
#define MEMACC_VAR_FAST
#define MEMACC_VAR
#define MEMACC_CONST
#define MEMACC_APPL_DATA
#define MEMACC_APPL_CONST
#define MEMACC_APPL_CODE
#define MEMACC_CALLOUT_CODE

/**********************************************************************************************************************
 *  MEMACC END
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  PORT START
 *********************************************************************************************************************/

#define PORT_CODE
#define PORT_VAR_NOINIT
#define PORT_VAR_POWER_ON_INIT
#define PORT_VAR_FAST
#define PORT_VAR
#define PORT_CONST
#define PORT_APPL_DATA
#define PORT_APPL_CONST
#define PORT_APPL_CODE
#define PORT_CALLOUT_CODE

/**********************************************************************************************************************
 *  PORT END
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  PWM START
 *********************************************************************************************************************/

#define PWM_17_TIMERIP_CODE
#define PWM_17_TIMERIP_VAR_NOINIT
#define PWM_17_TIMERIP_VAR_POWER_ON_INIT
#define PWM_17_TIMERIP_VAR_FAST
#define PWM_17_TIMERIP_VAR
#define PWM_17_TIMERIP_CONST
#define PWM_17_TIMERIP_APPL_DATA
#define PWM_17_TIMERIP_APPL_CONST
#define PWM_17_TIMERIP_APPL_CODE
#define PWM_17_TIMERIP_CALLOUT_CODE

/**********************************************************************************************************************
 *  PWM END
 *********************************************************************************************************************/

   /**********************************************************************************************************************
 *  SMU START
 *********************************************************************************************************************/

#define SMU_CODE
#define SMU_VAR_NOINIT
#define SMU_VAR_POWER_ON_INIT
#define SMU_VAR_FAST
#define SMU_VAR
#define SMU_CONST
#define SMU_APPL_DATA
#define SMU_APPL_CONST
#define SMU_APPL_CODE
#define SMU_CALLOUT_CODE

/**********************************************************************************************************************
 *  SMU END
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *  SPI START
 *********************************************************************************************************************/

#define SPI_CODE
#define SPI_VAR_NOINIT
#define SPI_VAR_POWER_ON_INIT
#define SPI_VAR_FAST
#define SPI_VAR
#define SPI_CONST
#define SPI_APPL_DATA
#define SPI_APPL_CONST
#define SPI_APPL_CODE
#define SPI_CALLOUT_CODE

/**********************************************************************************************************************
 *  SPI END
 *********************************************************************************************************************/
 
 /**********************************************************************************************************************
 *  WDG START
 *********************************************************************************************************************/

#define WDG_17_WTU_CODE
#define WDG_17_WTU_VAR_NOINIT
#define WDG_17_WTU_VAR_POWER_ON_INIT
#define WDG_17_WTU_VAR_FAST
#define WDG_17_WTU_VAR
#define WDG_17_WTU_CONST
#define WDG_17_WTU_APPL_DATA
#define WDG_17_WTU_APPL_CONST
#define WDG_17_WTU_APPL_CODE
#define WDG_17_WTU_CALLOUT_CODE

/**********************************************************************************************************************
 *  WDG END
 *********************************************************************************************************************/




/**********************************************************************************************************************
 *  OS START
 *********************************************************************************************************************/

#define OS_CODE                         /* Regular OS code. */
#define OS_CODE_FAST                    /* Time critical OS code. (currently not used) */
#define OS_CODE_SLOW                    /* Not time critical OS code. (currently not used) */
#define OS_CODE_ISR                     /* OS ISRs. (currently not used) */

#define OS_PANICHOOK_CODE               /* Panic Hook */
#define OS_PRETASKHOOK_CODE             /* PreTask Hook */
#define OS_POSTTASKHOOK_CODE            /* PostTask Hook */
#define OS_STARTUPHOOK_CODE             /* Startup Hook */
#define OS_ERRORHOOK_CODE               /* Error Hook */
#define OS_PROTECTIONHOOK_CODE          /* Protection Hook */
#define OS_SHUTDOWNHOOK_CODE            /* Shutdown Hook */

#define OS_CONST                        /* Constant data. */
#define OS_CONST_FAST                   /* Constant data with fast access. (currently not used) */

#define OS_VAR_INIT                     /* Initialized dynamic data. (Not used by the OS) */
#define OS_VAR_NOINIT                   /* Not initialized dynamic data. */
#define OS_VAR_ZERO_INIT                /* Zero initialized dynamic data. */
#define OS_VAR_INIT_FAST                /* Initialized dynamic data with fast access. (Not used by the OS) */
#define OS_VAR_NOINIT_FAST              /* Not initialized dynamic data with fast access. */
#define OS_VAR_ZERO_INIT_FAST           /* Zero initialized dynamic data with fast access. */

#define OS_VAR_INIT_NOCACHE             /* Initialized dynamic data not cached. (Not used by the OS) */
#define OS_VAR_NOINIT_NOCACHE           /* Not initialized dynamic data not cached. */
#define OS_VAR_ZERO_INIT_NOCACHE        /* Zero initialized dynamic data not cached. */

#define OS_APPL_VAR                     /* Dynamic data from user space (always in RAM). */
#define OS_APPL_DATA                    /* Data from user space (maybe in RAM or ROM). */

#define Os_OsCore0_swc_CODE



/**********************************************************************************************************************
 *  OS END
 *********************************************************************************************************************/




#define _TASKING_C_TRICORE_ 1

#define _TASKING_C_ARM_ 1U




/**********************************************************************************************************************
 *  vHyp START
 *********************************************************************************************************************/

#define VHYP_CODE
#define VHYP_SERVICE_CODE
#define VHYP_CONST
#define VHYP_VAR_INIT


/**********************************************************************************************************************
 *  vHyp END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  COMM START 
 *********************************************************************************************************************/

#define COMM_CODE

#define COMM_CONST
#define COMM_PBCFG

#define COMM_VAR_NO_INIT
#define COMM_VAR_PBCFG
#define COMM_VAR_CLEARED

#define COMM_APPL_VAR
#define COMM_NVM_DATA
#define COMM_NVM_DATA_NO_INIT

/**********************************************************************************************************************
 *  COMM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CanSM START
 *********************************************************************************************************************/

#define CANSM_CODE

#define CANSM_CONST


#define CANSM_APPL_CODE

#define CANSM_VAR_NOINIT
#define CANSM_VAR_ZERO_INIT

#define CANSM_APPL_VAR


/*******  FAST sections **********************************************************************************************/

#define CANSM_CONST_FAST

#define CANSM_VAR_NOINIT_FAST
#define CANSM_VAR_ZERO_INIT_FAST


/**********************************************************************************************************************
 *  CanSM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  FrSM START
 *********************************************************************************************************************/

#define FRSM_CODE
#define FRSM_APPL_CODE

#define FRSM_CONST
#define FRSM_PBCFG

#define FRSM_VAR_NOINIT
#define FRSM_VAR_ZERO_INIT

#define FRSM_APPL_VAR


/**********************************************************************************************************************
 *  FrSM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LINSM START
 *********************************************************************************************************************/

#define LINSM_CODE
#define LINSM_CONST
#define LINSM_PBCFG
#define LINSM_VAR_NOINIT
#define LINSM_VAR_ZERO_INIT
#define LINSM_APPL_DATA


/**********************************************************************************************************************
 *  LINSM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  ETHSM START 
 *********************************************************************************************************************/

#define ETHSM_CODE

#define ETHSM_CONST
#define ETHSM_APPL_CONST
#define ETHSM_PBCFG
#define ETHSM_APPL_DATA

#define ETHSM_VAR_NOINIT
#define ETHSM_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  ETHSM END
 *********************************************************************************************************************/


/*==== CDDDES ==================================================================*/
#define CDDDES_CODE                /* code */
#define CDDDES_VAR_INIT            /* initialized global/static variables */
#define CDDDES_VAR                 /* uninitialized global/static variables */
#define CDDDES_CONST               /* global/static constants */
#define CDDDES_CONST_ROOT          /* global/static constants */
#define CDDDES_PBCFG               /* global/static constants for PostBuild */
#define CDDDES_PBCFG_ROOT          /* global/static constants for PostBuild */
#define CDDDES_NVM_DATA            /* variables/buffers managed by NvM */
#define CDDDES_APPL_CODE           /* callback functions outside of CDDDES */
#define CDDDES_APPL_VAR            /* variables/buffers outside of CDDDES */
#define CDDDES_APPL_CONST          /* constants outside CDDDES */
#define CDDDES_APPL_DATA           /* data variables/buffers outside of CDDDES */
#define CDDDES_SHARED_DATA         /* variables/buffers shared by all */
#define CDDDES_NVM_DATA_NOINIT     CDDDES_NVM_DATA
#define CDDDES_CONST_PBCFG
/*===========================================================================*/


/*==== DRM ==================================================================*/
#define CDDDRM_CODE                                                   /* code */
#define CDDDRM_VAR_INIT                                               /* initialized global/static variables */
#define CDDDRM_VAR_NOINIT                                             /* uninitialized global/static variables */
#define CDDDRM_VAR_ZERO_INIT                                          /* zero initialized global/static variables */
#define CDDDRM_CONST                                                  /* global/static constants */
#define CDDDRM_CONST_ROOT                                             /* global/static constants */
#define CDDDRM_PBCFG                                                  /* global/static constants for PostBuild */
#define CDDDRM_PBCFG_ROOT                                             /* global/static constants for PostBuild */
#define CDDDRM_NVM_DATA                                               /* variables/buffers managed by NvM */
#define CDDDRM_APPL_CODE                                              /* callback functions outside of DRM */
#define CDDDRM_APPL_DATA                                              /* variables/buffers outside of DRM */
#define CDDDRM_APPL_CONST                                             /* constants outside DRM */
#define CDDDRM_SHARED_DATA                                            /* variables/buffers shared by all */
#define CDDDRM_NVM_DATA_NOINIT                                        CDDDRM_NVM_DATA
#define CDDDRM_CONST_PBCFG
/*===========================================================================*/



/**********************************************************************************************************************
 *  Cdd_AsrCdd START 
 *********************************************************************************************************************/

/* Copy the compiler abstraction defines for each of your configured CDDs and replace the prefix _CDD with the MSN of your configured CDD as higher case. */

#define _CDD_CODE
#define _CDD_APPL_DATA

/* Add additional compiler abstraction defines for each of you configured CDDs here. */

/**********************************************************************************************************************
 *  Cdd_AsrCdd END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  VX1000HOOKIF START 
 *********************************************************************************************************************/

#define VX1000HOOKIF_CODE

#define VX1000HOOKIF_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  VX1000HOOKIF END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  VX1000IF START 
 *********************************************************************************************************************/

#define VX1000IF_CODE
#define VX1000IF_CONST
#define VX1000IF_VAR_NOINIT
#define VX1000IF_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  VX1000IF END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  VX1000TLIF START 
 *********************************************************************************************************************/

#define VX1000TLIF_CODE
#define VX1000TLIF_CONST
#define VX1000TLIF_VAR_NOINIT
#define VX1000TLIF_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  VX1000TLIF END
 *********************************************************************************************************************/



/***********************************************************************************************************************
 *  VFSMLIB START 
 **********************************************************************************************************************/

#define VFSMLIB_CODE
#define VFSMLIB_CODE_FAST
#define VFSMLIB_CODE_ISR

#define VFSMLIB_CONST
#define VFSMLIB_CONST_FAST
#define VFSMLIB_PBCFG
#define VFSMLIB_VAR_PBCFG

#define VFSMLIB_VAR_INIT
#define VFSMLIB_VAR_NO_INIT
#define VFSMLIB_VAR_CLEARED

#define VFSMLIB_VAR_INIT_FAST
#define VFSMLIB_VAR_NO_INIT_FAST
#define VFSMLIB_VAR_CLEARED_FAST

#define VFSMLIB_VAR_INIT_NOCACHE
#define VFSMLIB_VAR_NO_INIT_NOCACHE
#define VFSMLIB_VAR_CLEARED_NOCACHE

#define VFSMLIB_APPL_CODE
#define VFSMLIB_APPL_CONST
#define VFSMLIB_APPL_VAR
#define VFSMLIB_APPL_DATA

#define VFSMLIB_INTERNAL_DATA

/***********************************************************************************************************************
 *  VFSMLIB END
 **********************************************************************************************************************/



/**********************************************************************************************************************
 *  CCP START 
 *********************************************************************************************************************/

#define CCP_CONST
#define CCP_CODE
#define CCP_APPL_DATA
#define CCP_APPL_VAR
#define CCP_MTA_DATA
#define CCP_DAQ_DATA
#define CCP_VAR_NOINIT
#define CCP_VAR_INIT
#define CCP_VAR_ZERO_INIT
#define CCP_PBCFG


/**********************************************************************************************************************
 *  CCP END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  XCP START 
 *********************************************************************************************************************/

#define XCP_CODE
#define XCP_CONST
#define XCP_PBCFG

#define XCP_VAR_INIT
#define XCP_VAR_NOINIT
#define XCP_VAR_ZERO_INIT
#define XCP_VAR_NOINIT_NOCACHE
#define XCP_APPL_DATA
#define XCP_APPL_VAR



/**********************************************************************************************************************
 *  XCP END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CANXCP START 
 *********************************************************************************************************************/

#define CANXCP_VAR_INIT
#define CANXCP_VAR_NOINIT
#define CANXCP_CONST
#define CANXCP_PBCFG
#define CANXCP_CODE
#define CANXCP_APPL_VAR

/*-------------------------------------------------------------------------------------------------------------------*/
/* CANXCP END                                                                                                        */
/*-------------------------------------------------------------------------------------------------------------------*/




/**********************************************************************************************************************
 *  FRXCP START 
 *********************************************************************************************************************/

#define FRXCP_PBCFG
#define FRXCP_CONST
#define FRXCP_CODE
#define FRXCP_APPL_DATA
#define FRXCP_VAR_INIT
#define FRXCP_VAR_NOINIT
#define FRXCP_VAR_PBCFG

/**********************************************************************************************************************
 *  FRXCP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  TCPIPXCP START 
 *********************************************************************************************************************/

#define TCPIPXCP_VAR_NOINIT
#define TCPIPXCP_VAR_INIT
#define TCPIPXCP_CONST
#define TCPIPXCP_PBCFG
#define TCPIPXCP_CODE
#define TCPIPXCP_APPL_VAR
#define TCPIPXCP_APPL_DATA

/**********************************************************************************************************************
 *  TCPIPXCP END 
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  VLINAA START
 *********************************************************************************************************************/

#define VLINAA_CODE
#define VLINAA_CODE_FAST
#define VLINAA_CODE_ISR
#define VLINAA_CODE_RTE

#define VLINAA_CONST
#define VLINAA_CONST_FAST
#define VLINAA_PBCFG
#define VLINAA_VAR_PBCFG

#define VLINAA_VAR_INIT
#define VLINAA_VAR_NOINIT
#define VLINAA_VAR_CLEARED

#define VLINAA_VAR_INIT_FAST
#define VLINAA_VAR_NOINIT_FAST
#define VLINAA_VAR_CLEARED_FAST

#define VLINAA_VAR_INIT_NOCACHE
#define VLINAA_VAR_NOINIT_NOCACHE
#define VLINAA_VAR_CLEARED_NOCACHE

#define VLINAA_APPL_VAR
#define VLINAA_PDUR_VAR

/**********************************************************************************************************************
 *  VLINAA END
 *********************************************************************************************************************/


#define DCM_CODE                /* code */
#define DCM_CONST               /* global/static constants */
#define DCM_CAL_PRM             /* calibrateable constants */
#define DCM_APPL_CODE           /* callback functions outside of Dcm */
#define DCM_APPL_CONST          /* constants outside Dcm */ 
#define DCM_APPL_DATA           /* variables/buffers outside of Dcm */
#define DCM_CALLOUT_CODE        /* callback functions outside of Dcm but part of Dcm (callouts) */
#define DCM_VAR_INIT            /* initialized global/static variables */
#define DCM_VAR_NOINIT          /* uninitialized global/static variables */
#define DCM_VAR_PBCFG           /* global/static variable for PostBuildLoadable */
#define DCM_PBCFG               /* global/static constants for PostBuildLoadable */



/*==== DEM ==================================================================*/
#define DEM_CODE                /* code */
#define DEM_VAR_INIT            /* initialized global/static variables */
#define DEM_VAR_CLEARED         /* initialized global/static variables with initialization value 0 */
#define DEM_VAR_NO_INIT         /* uninitialized global/static variables */
#define DEM_VAR_UNCACHED        /* uninitialized global/static un-cached variables */
#define DEM_CONST               /* global/static constants */
#define DEM_CONST_ROOT          /* global/static constants */
#define DEM_PBCFG               /* global/static constants for PostBuild */
#define DEM_PBCFG_ROOT          /* global/static constants for PostBuild */
#define DEM_VAR_PBCFG           /* post-buildable RAM */
#define DEM_DCM_DATA            /* variables/buffers passed by Dcm to Dem */
#define DEM_J1939DCM_DATA       /* variables/buffers passed by J1939Dcm to Dem */
#define DEM_DLT_DATA            /* variables/buffers passed by Dlt to Dem */
#define DEM_NVM_DATA            /* variables/buffers managed by NvM */
#define DEM_APPL_CODE           /* callback functions outside of Dem */
#define DEM_APPL_DATA           /* variables/buffers outside of Dem */
#define DEM_APPL_CONST          /* constants outside Dem */
#define DEM_SHARED_DATA         /* variables/buffers shared by all */
#define DEM_CAL_PRM             /* calibrateable constants */
#define DEM_NVM_DATA_NO_INIT    DEM_NVM_DATA
#define DEM_VAR_SATELLITE       /* variables/buffers of Dem satellites */
/*===========================================================================*/



/**********************************************************************************************************************
 *  J1939DCM START
 *********************************************************************************************************************/
#define J1939DCM_CODE
#define J1939DCM_APLL_CODE

#define J1939DCM_CONST
#define J1939DCM_PBCFG
#define J1939DCM_PBCFG_ROOT

#define J1939DCM_VAR_INIT
#define J1939DCM_VAR_NOINIT

#define J1939DCM_APPL_DATA
#define J1939DCM_INTERNAL_DATA


/**********************************************************************************************************************
 *  J1939DCM END
 *********************************************************************************************************************/


/*==== VDEM42 ================================================================*/
#define VDEM42_CODE             /* code */
#define VDEM42_APPL_DATA        /* data variables/buffers outside of VDEM42 */
#define VDEM42_APPL_VAR         /* variables/buffers outside of VDEM42 */
/*============================================================================*/


/**********************************************************************************************************************
 *  CRYPTO_30_LIBCV START
 *********************************************************************************************************************/

#define CRYPTO_30_LIBCV_CODE
#define CRYPTO_30_LIBCV_APPL_CODE

#define CRYPTO_30_LIBCV_CONST

#define CRYPTO_30_LIBCV_VAR_NOINIT
#define CRYPTO_30_LIBCV_VAR_ZERO_INIT
#define CRYPTO_30_LIBCV_APPL_VAR
#define CRYPTO_30_LIBCV_APPL_DATA

#define CRYPTO_30_LIBCV_CRYPTOCV_APPL_VAR

/**********************************************************************************************************************
 *  CRYPTO_30_LIBCV END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CRYPTO_30_VHSM START
 *********************************************************************************************************************/

#define CRYPTO_30_VHSM_CODE
#define CRYPTO_30_VHSM_APPL_CODE
#define CRYPTO_30_VHSM_CONST

#define CRYPTO_30_VHSM_VAR_NOINIT
#define CRYPTO_30_VHSM_VAR_INIT
#define CRYPTO_30_VHSM_VAR_ZERO_INIT
#define CRYPTO_30_VHSM_APPL_VAR
#define CRYPTO_30_VHSM_APPL_DATA

/**********************************************************************************************************************
 *  CRYPTO_30_VHSM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  EEP_30_VMEMACCM START
 *********************************************************************************************************************/

#define EEP_30_VMEMACCM_CODE
#define EEP_30_VMEMACCM_APPL_VAR
#define EEP_30_VMEMACCM_VAR_INIT

/**********************************************************************************************************************
 *  EEP_30_VMEMACCM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  FLS_30_VMEMACCM START
 *********************************************************************************************************************/

#define FLS_30_VMEMACCM_CODE
#define FLS_30_VMEMACCM_CONST
#define FLS_30_VMEMACCM_VAR


#define FLS_30_VMEMACCM_APPL_VAR /* use for user data buffers located in RAM */



/**********************************************************************************************************************
 *  FLS_30_VMEMACCM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Lin_Compiler_Cfg.inc
 *        \brief  AUTOSAR LIN Driver
 *
 *      \details  AUTOSAR LIN Driver for all target systems
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  LIN DRIVER START
 *********************************************************************************************************************/

#define LIN_30_GENERIC_CODE
#define LIN_30_GENERIC_CODE_FAST
#define LIN_30_GENERIC_CODE_ISR
#define LIN_30_GENERIC_APPL_CODE

#define LIN_30_GENERIC_CONST
#define LIN_30_GENERIC_CONST_FAST
#define LIN_30_GENERIC_PBCFG

#define LIN_30_GENERIC_VAR_PBCFG
#define LIN_30_GENERIC_VAR_INIT
#define LIN_30_GENERIC_VAR_NOINIT
#define LIN_30_GENERIC_VAR_ZERO_INIT
#define LIN_30_GENERIC_VAR_INIT_FAST
#define LIN_30_GENERIC_VAR_NOINIT_FAST
#define LIN_30_GENERIC_VAR_ZERO_INIT_FAST

#define LIN_30_GENERIC_VAR_INIT_NOCACHE
#define LIN_30_GENERIC_VAR_NOINIT_NOCACHE
#define LIN_30_GENERIC_VAR_ZERO_INIT_NOCACHE

#define LIN_30_GENERIC_APPL_VAR
#define LIN_30_GENERIC_VAR_REGS

/**********************************************************************************************************************
 *  LIN DRIVER END
 *********************************************************************************************************************/




/***********************************************************************************************************************
 *  VMEM START
 **********************************************************************************************************************/

#define VMEM_30_BLOCKING_CODE
#define VMEM_30_BLOCKING_CONST
#define VMEM_30_BLOCKING_VAR
#define VMEM_30_BLOCKING_APPL_VAR
#define VMEM_30_BLOCKING_APPL_CONST
#define VMEM_30_BLOCKING_APPL_CODE

/***********************************************************************************************************************
 *  VMEM END
 **********************************************************************************************************************/



/***********************************************************************************************************************
 *  VMEM_30_EEP START
 **********************************************************************************************************************/

#define VMEM_30_EEP_CODE
#define VMEM_30_EEP_CONST
#define VMEM_30_EEP_APPL_VAR
#define VMEM_30_EEP_VAR_ZERO_INIT
#define VMEM_30_EEP_PBCFG
#define VMEM_30_EEP_VAR

/***********************************************************************************************************************
 *  VMEM_30_EEP END
 **********************************************************************************************************************/


#if !defined ( VMEM_30_FLS_COMPILER_CFG_INC )
#define VMEM_30_FLS_COMPILER_CFG_INC


/***********************************************************************************************************************
 *  VMEM_30_FLS START
 **********************************************************************************************************************/

#define VMEM_30_FLS_CODE
#define VMEM_30_FLS_CONST
#define VMEM_30_FLS_APPL_VAR
#define VMEM_30_FLS_VAR_ZERO_INIT

/***********************************************************************************************************************
 *  VMEM_30_FLS END
 **********************************************************************************************************************/
#endif /* VMEM_30_FLS_COMPILER_CFG_INC */



/***********************************************************************************************************************
 *  VMEM_30_MMFLASHRO START
 **********************************************************************************************************************/

#define VMEM_30_MMFLASHRO_CODE
#define VMEM_30_MMFLASHRO_CONST
#define VMEM_30_MMFLASHRO_APPL_VAR
#define VMEM_30_MMFLASHRO_VAR_ZERO_INIT
#define VMEM_30_MMFLASHRO_VAR_NOINIT
#define VMEM_30_MMFLASHRO_PBCFG

/***********************************************************************************************************************
 *  VMEM_30_MMFLASHRO END
 **********************************************************************************************************************/



/***********************************************************************************************************************
 *  VMEM_30_XXRAM START
 **********************************************************************************************************************/

#define VMEM_30_XXRAM_CODE
#define VMEM_30_XXRAM_CONST
#define VMEM_30_XXRAM_APPL_VAR
#define VMEM_30_XXRAM_VAR_ZERO_INIT
#define VMEM_30_XXRAM_VAR_INIT
#define VMEM_30_XXRAM_PBCFG
#define VMEM_30_XXRAM_VAR
/***********************************************************************************************************************
 *  VMEM_30_XXRAM END
 **********************************************************************************************************************/



/***********************************************************************************************************************
 *  VMEM_30_VRPCPROXY START
 **********************************************************************************************************************/

#define VMEM_30_VRPCPROXY_CODE
#define VMEM_30_VRPCPROXY_CONST
#define VMEM_30_VRPCPROXY_APPL_VAR
#define VMEM_30_VRPCPROXY_VAR_ZERO_INIT
#define VMEM_30_VRPCPROXY_VAR_NOINIT

/***********************************************************************************************************************
 *  VMEM_30_VRPCPROXY END
 **********************************************************************************************************************/



/**********************************************************************************************************************
 *  EcuAb_AsrIoHwAb START
 *********************************************************************************************************************/

#define IOHWAB_CODE

#define IOHWAB_VAR

#define IOHWAB_APPL_DATA
#define IOHWAB_APPL_CODE

#define IOHWAB_CONST

/**********************************************************************************************************************
 *  EcuAb_AsrIoHwAb END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  PDUR START
 *********************************************************************************************************************/

#define PDUR_CODE
#define PDUR_VAR_NO_INIT
#define PDUR_VAR_CLEARED
#define PDUR_VAR
#define PDUR_CONST
#define PDUR_PBCFG
#define PDUR_VAR_PBCFG
#define PDUR_APPL_DATA
#define PDUR_APPL_CODE

/**********************************************************************************************************************
 *  PDUR END
 *********************************************************************************************************************/



/***********************************************************************************************************************
 *  MIRROR START 
 **********************************************************************************************************************/

#define MIRROR_CODE

#define MIRROR_CONST
#define MIRROR_APPL_VAR

#define MIRROR_APPL_DATA
#define MIRROR_APPL_CODE
#define MIRROR_VAR_ZERO_INIT
#define MIRROR_VAR_NOINIT
#define MIRROR_VAR_PBCFG
#define MIRROR_PBCFG

/***********************************************************************************************************************
 *  MIRROR END
 **********************************************************************************************************************/



/**********************************************************************************************************************
 *  LINIF START
 *********************************************************************************************************************/

#define LINIF_CODE
#define LINIF_CONST
#define LINIF_VAR_NOINIT
#define LINIF_VAR_ZERO_INIT
#define LINIF_VAR_PBCFG
#define LINIF_APPL_DATA
#define LINIF_APPL_VAR
#define LINIF_PBCFG
#define LINIF_APPL_PBCFG
#define LINIF_CBK_TRCV_CODE

/**********************************************************************************************************************
 *  LINIF END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LIN TP START
 *********************************************************************************************************************/

#define LINTP_CODE
#define LINTP_CONST
#define LINTP_VAR_NOINIT
#define LINTP_VAR_ZERO_INIT
#define LINTP_VAR_PBCFG
#define LINTP_APPL_DATA
#define LINTP_APPL_VAR
#define LINTP_PBCFG
#define LINTP_APPL_PBCFG

/**********************************************************************************************************************
 *  LIN TP END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  If_Asr4IfWd START
 *********************************************************************************************************************/

#define WDGIF_CODE
#define WDGIF_CONST
#define WDGIF_VAR
#define WDGIF_APPL_DATA
#define WDGIF_APPL_CONST

/**********************************************************************************************************************
 *  If_Asr4IfWd END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CANIF START 
 *********************************************************************************************************************/

#define CANIF_CODE
#define CANIF_CODE_FAST
#define CANIF_CODE_ISR


#define CANIF_CONST
#define CANIF_CONST_FAST
#define CANIF_PBCFG

#define CANIF_VAR_PBCFG /* ESCAN00065502 */

#define CANIF_VAR_INIT
#define CANIF_VAR_NOINIT
#define CANIF_VAR_ZERO_INIT

#define CANIF_VAR_INIT_FAST
#define CANIF_VAR_NOINIT_FAST
#define CANIF_VAR_ZERO_INIT_FAST

#define CANIF_VAR_INIT_NOCACHE
#define CANIF_VAR_NOINIT_NOCACHE
#define CANIF_VAR_ZERO_INIT_NOCACHE


#define CANIF_APPL_CODE
#define CANIF_APPL_VAR
#define CANIF_APPL_PBCFG


/*-------------------------------------------------------------------------------------------------------------------*/

/* Has to be kept in default section -> Default access */
#define CANIF_VAR_STACK


/* VAR section of higher layers (TP / NM / PduR / CanSM / EcuM) automatically mapped to APPL_VAR */
#define CANIF_APPL_STATE_VAR   CANIF_APPL_VAR
#define CANIF_APPL_MSG_VAR     CANIF_APPL_VAR

/* VAR section of lower layers (CAN Driver / Transceiver Driver) automatically mapped to APPL_VAR */
#define CANIF_CBK_VAR          CANIF_APPL_VAR

/* #define CANIF_CBK_TRCV_VAR     CANIF_CBK_VAR    not used yet */
#define CANIF_CBK_DRV_VAR      CANIF_CBK_VAR

/* Code sections - DO NOT MODIFY */
#define CANIF_CBK_TRCV_CODE     CANIF_APPL_CODE
#define CANIF_CBK_CANDRV_CODE   CANIF_APPL_CODE
#define CANIF_APPL_STATE_CODE   CANIF_APPL_CODE
#define CANIF_APPL_MSG_CODE     CANIF_APPL_CODE


/* Upper layer data pointer */
#define CANIF_UL_STANDARD_VAR    CANIF_APPL_VAR
#define CANIF_UL_ADVANCED_VAR    CANIF_APPL_VAR
#define CANIF_UL_OSEKNM_VAR      CANIF_APPL_VAR

/**********************************************************************************************************************
 *  CANIF END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CRYIF START
 *********************************************************************************************************************/

#define CRYIF_CODE
#define CRYIF_CONST

#define CRYIF_VAR_ZERO_INIT
#define CRYIF_APPL_VAR
#define CRYIF_APPL_DATA

/**********************************************************************************************************************
 *  CRYIF END
 *********************************************************************************************************************/




/**********************************************************************************************************************
 *  If_AsrIfEa START 
 *********************************************************************************************************************/

#define EA_PUBLIC_CODE
#define EA_PRIVATE_CODE

#define EA_APPL_DATA
#define EA_FAST_DATA

#define EA_PRIVATE_CONST
#define EA_PUBLIC_CONST

#define EA_NVM_CODE

/* In ASR4 SchM/RTE declares Ea_MainFunction, using EA_CODE *
 * It MUST be defined to EA_PUBLIC_CODE!                     */
#define EA_CODE EA_PUBLIC_CODE

/**********************************************************************************************************************
 *  If_AsrIfEa END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  ETHIF START
 *********************************************************************************************************************/

#define ETHIF_CODE
#define ETHIF_CODE_ISR
#define ETHIF_ETHCTRL_INLINE_CODE
#define ETHIF_ETHTRCV_INLINE_CODE
#define ETHIF_ETHSWT_INLINE_CODE
#define ETHIF_GW_INLINE_CODE
#define ETHIF_LINK_INLINE_CODE
#define ETHIF_MACSEC_INLINE_CODE
#define ETHIF_MIRROR_INLINE_CODE
#define ETHIF_MODE_INLINE_CODE
#define ETHIF_RX_INLINE_CODE
#define ETHIF_STATS_INLINE_CODE
#define ETHIF_TX_INLINE_CODE
#define ETHIF_UTILS_INLINE_CODE
#define ETHIF_ZEROCOPY_INLINE_CODE

#define ETHIF_CONST

#define ETHIF_APPL_VAR
#define ETHIF_APPL_DATA
#define ETHIF_APPL_CODE

#define ETHIF_VAR_NO_INIT
#define ETHIF_VAR_NO_INIT_FAST

#define ETHIF_VAR_INIT

/**********************************************************************************************************************
 *  ETHIF END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  FEE START 
 *********************************************************************************************************************/

#define FEE_API_CODE
#define FEE_APPL_CODE
#define FEE_APPL_CONFIG
#define FEE_APPL_DATA
#define FEE_CONST
#define FEE_PRIVATE_CODE
#define FEE_PRIVATE_CONST
#define FEE_PRIVATE_DATA
#define FEE_VAR
#define FEE_VAR_NOINIT

/* In ASR4 SchM/RTE declares NvM_MainFunction, using FEE_CODE */
#define FEE_CODE

/**********************************************************************************************************************
 *  FEE END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  If_AsrIfFeeSmallSector START
 *********************************************************************************************************************/

#define FEE_30_SMALLSECTOR_PUBLIC_CODE
#define FEE_30_SMALLSECTOR_PRIVATE_CODE

#define FEE_30_SMALLSECTOR_APPL_DATA
#define FEE_30_SMALLSECTOR_FAST_DATA

#define FEE_30_SMALLSECTOR_PRIVATE_CONST
#define FEE_30_SMALLSECTOR_PUBLIC_CONST

#define FEE_30_SMALLSECTOR_NVM_CODE

/* In ASR4 SchM/RTE declares Fee_MainFunction, using FEE_30_SMALLSECTOR_CODE *
 * It MUST be defined to FEE_30_SMALLSECTOR_PUBLIC_CODE!                     */
#define FEE_30_SMALLSECTOR_CODE FEE_30_SMALLSECTOR_PUBLIC_CODE

/**********************************************************************************************************************
 *  If_AsrIfFeeSmallSector END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  FRIF START 
 *********************************************************************************************************************/

#define FRIF_CODE
#define FRIF_CODE_FAST
#define FRIF_CODE_ISR

#define FRIF_CONST
#define FRIF_CONST_FAST
#define FRIF_PBCFG
#define FRIF_PBCFG_GLOBALROOT

#define FRIF_VAR_INIT
#define FRIF_VAR_NOINIT
#define FRIF_VAR_ZERO_INIT
#define FRIF_VAR_INIT_FAST
#define FRIF_VAR_NOINIT_FAST
#define FRIF_VAR_PBCFG
#define FRIF_VAR_ZERO_INIT_FAST

#define FRIF_APPL_DATA
#define FRIF_APPL_CODE

/**********************************************************************************************************************
 *  FRIF END
 *********************************************************************************************************************/


#define MEMIF_CODE
#define MEMIF_PRIVATE_CODE
#define MEMIF_CONST
#define MEMIF_APPL_DATA


/**********************************************************************************************************************
 *  SOAD START 
 *********************************************************************************************************************/

#define SOAD_CODE

#define SOAD_APPL_DATA
#define SOAD_APPL_VAR

#define SOAD_CONST
#define SOAD_PBCFG

#define SOAD_VAR_NO_INIT
#define SOAD_VAR_CLEARED
#define SOAD_VAR_PBCFG

/**********************************************************************************************************************
 *  SOAD END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  FEE_30_FLEXNOR START 
 *********************************************************************************************************************/

#define FEE_30_FLEXNOR_CODE

#define FEE_30_FLEXNOR_VAR

#define FEE_30_FLEXNOR_CONST
#define FEE_30_FLEXNOR_PBCFG
#define FEE_30_FLEXNOR_VAR_PBCFG

#define FEE_30_FLEXNOR_VAR_INIT
#define FEE_30_FLEXNOR_VAR_NOINIT
#define FEE_30_FLEXNOR_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  FEE_30_FLEXNOR END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  FEE_30_FLEXNOR START 
 *********************************************************************************************************************/

#define FEE_30_FLEXNOR_CODE

#define FEE_30_FLEXNOR_VAR

#define FEE_30_FLEXNOR_CONST
#define FEE_30_FLEXNOR_PBCFG
#define FEE_30_FLEXNOR_VAR_PBCFG

#define FEE_30_FLEXNOR_VAR_INIT
#define FEE_30_FLEXNOR_VAR_NOINIT
#define FEE_30_FLEXNOR_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  FEE_30_FLEXNOR END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  VFEEACC START 
 *********************************************************************************************************************/

#define VFEEACC_CODE
#define VFEEACC_APPL_CODE
#define VFEEACC_APPL_DATA
#define VFEEACC_CONST
#define VFEEACC_PRIVATE_CODE
#define VFEEACC_PRIVATE_CONST
#define VFEEACC_PRIVATE_DATA

/**********************************************************************************************************************
 *  VFEEACC END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  VMEMACCM START
 *********************************************************************************************************************/

#define VMEMACCM_CODE

#define VMEMACCM_CONST

#define VMEMACCM_VMEM_CODE
#define VMEMACCM_VMEM_CONST

#define VMEMACCM_APPL_VAR /* use for user data buffers located in RAM */

#define VMEMACCM_VAR_INIT
#define VMEMACCM_VAR_NOINIT
#define VMEMACCM_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  VMEMACCM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  VSYNCMEM START 
 *********************************************************************************************************************/

#define VSYNCMEM_CODE

#define VSYNCMEM_APPL_VAR /* use for user data buffers located in RAM */

#define VSYNCMEM_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  VSYNCMEM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  Com START
 *********************************************************************************************************************/

/* Module Constant Data */
#define COM_CONST
/* Module Constant Data of the Postbuild Configuration */
#define COM_PBCFG
/* Module Var Data of the Postbuild Configuration */
#define COM_VAR_PBCFG


/* Module Implementation */
#define COM_CODE

/* Module Variables which are initialized by the startup code or by the call of Com_InitMemory() */
#define COM_VAR_NO_INIT
/* Module Variables which are initialized by call of Com_Init() */
#define COM_VAR_CLEARED
/* Module Variables which are initialized by call of Com_Init() */
#define COM_VAR_INIT

/* Application Code Implementation (e.g. Callbacks) */
#define COM_APPL_CODE
/* Application Buffer which is located in RAM */
#define COM_APPL_VAR
/* Application Buffer which is located in ROM or RAM */
#define COM_APPL_DATA

/**********************************************************************************************************************
 *  Com END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  IpduM START 
 *********************************************************************************************************************/

#define IPDUM_CODE
#define IPDUM_CONST
#define IPDUM_PBCFG
#define IPDUM_VAR_PBCFG
#define IPDUM_VAR_INIT
#define IPDUM_VAR_CLEARED
#define IPDUM_VAR_NO_INIT
#define IPDUM_APPL_DATA

/**********************************************************************************************************************
 *  IpduM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  LDCOM START
 *********************************************************************************************************************/
/* Module Implementation */
#define LDCOM_CODE

/* Module Constant Data */
#define LDCOM_CONST
/* Module Constant Data of the Postbuild Configuration */
#define LDCOM_PBCFG
/* Module Var Data of the Postbuild Configuration */
#define LDCOM_VAR_PBCFG

/* Module Variables which are initialized by call of LdCom_Init() */
#define LDCOM_VAR_INIT
/* Module Variables which are initialized by the startup code or by the call of LdCom_InitMemory() */
#define LDCOM_VAR_NO_INIT
/* Module Variables which are initialized by call of LdCom_Init() */
#define LDCOM_VAR_CLEARED

/* Application Code Implementation (e.g. Callbacks) */
#define LDCOM_APPL_CODE
/* Application Buffer which is located in RAM */
#define LDCOM_APPL_VAR
/* Application Buffer which is located in ROM or RAM */
#define LDCOM_APPL_DATA

/**********************************************************************************************************************
 *  LDCOM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  SECOC START 
 *********************************************************************************************************************/
/* Module Implementation */
#define SECOC_CODE

/* Module Constant Data */
#define SECOC_CONST
/* Module Constant Data of the Postbuild Configuration */
#define SECOC_PBCFG
/* Module Var Data of the Postbuild Configuration */
#define SECOC_VAR_PBCFG


/* Module Variables which are initialized by call of SecOC_Init() */
#define SECOC_VAR_INIT
/* Module Variables which are initialized by the startup code or by the call of SecOC_InitMemory() */
#define SECOC_VAR_NO_INIT
/* Module Variables which are initialized by call of SecOC_Init() */
#define SECOC_VAR_CLEARED

/* Application Code Implementation (e.g. Callbacks) */
#define SECOC_APPL_CODE
/* Application Buffer which is located in RAM */
#define SECOC_APPL_VAR
/* Application Buffer which is located in ROM or RAM */
#define SECOC_APPL_DATA

/**********************************************************************************************************************
 *  SECOC END
 *********************************************************************************************************************/



/***********************************************************************************************************************
 *  VIPC START
 **********************************************************************************************************************/

#define VIPC_CODE
#define VIPC_CONST
#define VIPC_APPL_VAR
#define VIPC_APPL_CONST
#define VIPC_APPL_DATA
#define VIPC_APPL_CODE
#define VIPC_VAR_ZERO_INIT
#define VIPC_VAR_NOINIT
#define VIPC_VAR_PBCFG
#define VIPC_PBCFG
#define VIPC_PBCFG_ROOT

/***********************************************************************************************************************
 *  VIPC END
 **********************************************************************************************************************/



/**********************************************************************************************************************
 *  VIPCMEMCP START
 *********************************************************************************************************************/

#define VIPCMEMCP_CODE
#define VIPCMEMCP_CONST
#define VIPCMEMCP_VAR_NOINIT
#define VIPCMEMCP_VAR_ZERO_INIT
#define VIPCMEMCP_PBCFG

/**********************************************************************************************************************
 *  VIPCMEMCP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  VIPCMEMIF START
 *********************************************************************************************************************/

#define VIPCMEMIF_CODE

#define VIPCMEMIF_CONST
#define VIPCMEMIF_PBCFG
#define VIPCMEMIF_VAR_PBCFG

#define VIPCMEMIF_VAR_NOINIT
#define VIPCMEMIF_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  VIPCMEMIF END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  VIPCMEMIFLINUX START
 *********************************************************************************************************************/

#define VIPCMEMIFLINUX_CODE
#define VIPCMEMIFLINUX_CONST
#define VIPCMEMIFLINUX_VAR_NOINIT
#define VIPCMEMIFLINUX_VAR_ZERO_INIT
#define VIPCMEMIFLINUX_VAR_PBCFG
#define VIPCMEMIFLINUX_PBCFG

/**********************************************************************************************************************
 *  VIPCMEMIFLINUX END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  VIPCMEMLINUX START
 *********************************************************************************************************************/

#define VIPCMEMLINUX_CODE
#define VIPCMEMLINUX_CONST
#define VIPCMEMLINUX_VAR_NOINIT
#define VIPCMEMLINUX_VAR_ZERO_INIT
#define VIPCMEMLINUX_PBCFG

/**********************************************************************************************************************
 *  VIPCMEMLINUX END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  vRpcProxy START 
 *********************************************************************************************************************/
/* Module Implementation */
#define VRPCPROXY_CODE
#define VRPCPROXY_PBCFG

/* Module Constant Data */
#define VRPCPROXY_CONST

/* Module Variables which are initialized by call of vRpcProxy_Init() */
#define VRPCPROXY_VAR_INIT
#define VRPCPROXY_VAR_NO_INIT
#define VRPCPROXY_VAR_CLEARED

/* Application Code Implementation (e.g. Callbacks) */
#define VRPCPROXY_APPL_CODE
/* Application Buffer which is located in RAM */
#define VRPCPROXY_APPL_VAR
/* Application Buffer which is located in ROM or RAM */
#define VRPCPROXY_APPL_DATA
/**********************************************************************************************************************
 *  vRpcProxy END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  J1939RM START
 *********************************************************************************************************************/

#define J1939RM_CODE
#define J1939RM_APPL_CODE

#define J1939RM_CONST
#define J1939RM_PBCFG
#define J1939RM_APPL_DATA

#define J1939RM_VAR_NO_INIT
#define J1939RM_VAR_CLEARED
#define J1939RM_VAR_PBCFG

/**********************************************************************************************************************
 *  J1939RM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  NvM START 
 *********************************************************************************************************************/

#define NVM_APPL_DATA
#define NVM_APPL_CODE
#define NVM_APPL_CONST

#define NVM_CONFIG_DATA
#define NVM_CONFIG_CONST

#define NVM_FAST_DATA

#define NVM_PRIVATE_CODE
#define NVM_PRIVATE_CONST
#define NVM_PRIVATE_DATA

#define NVM_PUBLIC_CODE
#define NVM_PUBLIC_CONST

/* SchM/RTE declares NvM_MainFunction, using NVM_CODE *
 * It MUST be defined to NVM_PUBLIC_CODE!             */
#define NVM_CODE NVM_PUBLIC_CODE

/**********************************************************************************************************************
 *  NvM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  DBG START 
 *********************************************************************************************************************/


#define DBG_CODE

#define DBG_CONST

#define DBG_VAR_INIT
#define DBG_VAR_NOINIT
#define DBG_VAR_ZERO_INIT

#define DBG_APPL_VAR
#define DBG_PBCFG


/**********************************************************************************************************************
 *  DBG END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  RTM START 
 *********************************************************************************************************************/

#define RTM_CONST
#define RTM_CODE
#define RTM_VAR_INIT
#define RTM_VAR_NO_INIT
#define RTM_VAR_CLEARED
#define RTM_APPL_VAR
#define RTM_APPL_DATA

/**********************************************************************************************************************
 *  RTM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  DLT START 
 *********************************************************************************************************************/

#define DLT_CODE
#define DLT_VAR_INIT
#define DLT_VAR_NO_INIT
#define DLT_VAR_CLEARED
#define DLT_VAR
#define DLT_CONST
#define DLT_PBCFG
#define DLT_VAR_PBCFG
#define DLT_APPL_VAR
#define DLT_APPL_CODE

/**********************************************************************************************************************
 *  DLT END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  J1939NM START
 *********************************************************************************************************************/

#define J1939NM_CODE
#define J1939NM_APPL_CODE

#define J1939NM_CONST
#define J1939NM_PBCFG
#define J1939NM_APPL_VAR
#define J1939NM_APPL_DATA

#define J1939NM_VAR_NO_INIT
#define J1939NM_VAR_CLEARED
#define J1939NM_VAR_PBCFG

/**********************************************************************************************************************
 *  J1939NM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CANNM START 
 *********************************************************************************************************************/

#define CANNM_CODE

#define CANNM_CONST
#define CANNM_PBCFG

#define CANNM_VAR_NOINIT
#define CANNM_VAR_INIT
#define CANNM_VAR_ZERO_INIT
#define CANNM_VAR_PBCFG
#define CANNM_APPL_VAR

/**********************************************************************************************************************
 *  CANNM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  FRNM START
 *********************************************************************************************************************/

#define FRNM_CODE

#define FRNM_CONST
#define FRNM_PBCFG

#define FRNM_VAR_NOINIT
#define FRNM_VAR_INIT
#define FRNM_VAR_ZERO_INIT
#define FRNM_VAR_PBCFG
#define FRNM_APPL_VAR

/**********************************************************************************************************************
 *  FRNM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  NM START 
 *********************************************************************************************************************/
 
#define NM_CODE
#define NM_APPL_CODE

#define NM_CONST

#define NM_VAR_NO_INIT
#define NM_VAR_INIT
#define NM_APPL_VAR
#define NM_VAR_CLEARED

/**********************************************************************************************************************
 *  NM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  NMOSEK START 
 *********************************************************************************************************************/

#define NMOSEK_CODE
#define NMOSEK_APPL_CODE

#define NMOSEK_CONST
#define NMOSEK_PBCFG
#define NMOSEK_APPL_CONST

#define NMOSEK_VAR_NO_INIT
#define NMOSEK_VAR_ZERO_INIT
#define NMOSEK_VAR_PBCFG
#define NMOSEK_APPL_VAR

/**********************************************************************************************************************
 *  NMOSEK END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  UDPNM START 
 *********************************************************************************************************************/

#define UDPNM_CODE

#define UDPNM_CONST
#define UDPNM_APPL_VAR
#define UDPNM_PBCFG

#define UDPNM_VAR_NOINIT
#define UDPNM_VAR_INIT
#define UDPNM_VAR_ZERO_INIT
#define UDPNM_VAR_PBCFG

/**********************************************************************************************************************
 *  UDPNM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CSM START
 *********************************************************************************************************************/

#define CSM_CODE
#define CSM_APPL_CODE
#define CSM_RTE_CODE

#define CSM_CONST

#define CSM_VAR_NOINIT
#define CSM_VAR_ZERO_INIT
#define CSM_APPL_VAR
#define CSM_APPL_CONST

/**********************************************************************************************************************
 *  CSM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  KEYM START
 *********************************************************************************************************************/

#define KEYM_CODE
#define KEYM_APPL_CODE
#define KEYM_RTE_CODE

#define KEYM_CONST
#define KEYM_PBCFG

#define KEYM_VAR_INIT
#define KEYM_VAR_NO_INIT
#define KEYM_VAR_ZERO_INIT
#define KEYM_APPL_VAR
#define KEYM_APPL_DATA

/**********************************************************************************************************************
 *  KEYM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  FVM START 
 *********************************************************************************************************************/

#define FVM_CODE
#define FVM_CODE_FAST
#define FVM_CODE_ISR

#define FVM_CONST
#define FVM_CONST_FAST
#define FVM_PBCFG

#define FVM_VAR_PBCFG   /* ESCAN00065502 */

#define FVM_VAR_INIT
#define FVM_VAR_NOINIT
#define FVM_VAR_ZERO_INIT
#define FVM_VAR_INIT_FAST
#define FVM_VAR_NOINIT_FAST
#define FVM_VAR_ZERO_INIT_FAST

#define FVM_VAR_INIT_NOCACHE
#define FVM_VAR_NOINIT_NOCACHE
#define FVM_VAR_ZERO_INIT_NOCACHE

#define FVM_APPL_CODE
#define FVM_APPL_VAR
#define FVM_APPL_DATA

/**********************************************************************************************************************
 *  FVM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  IDSM START 
 *********************************************************************************************************************/

#define IDSM_CONST
#define IDSM_APPL_DATA
#define IDSM_VAR_INIT
#define IDSM_CODE
#define IDSM_NVM_DATA
#define IDSM_VAR_NO_INIT
#define IDSM_VAR_ZERO_INIT
#define IDSM_VAR_CLEARED

/**********************************************************************************************************************
 *  IDSM END
 *********************************************************************************************************************/


/***********************************************************************************************************************
 *  MKA START
 **********************************************************************************************************************/

#define MKA_CODE

#define MKA_CONST
#define MKA_CONFIG_DATA
#define MKA_PBCFG

#define MKA_VAR_INIT
#define MKA_VAR_NO_INIT
#define MKA_VAR_CLEARED

#define MKA_APPL_CODE
#define MKA_APPL_CONST
#define MKA_APPL_VAR
#define MKA_APPL_DATA

/***********************************************************************************************************************
 *  MKA END
 **********************************************************************************************************************/


/**********************************************************************************************************************
 *  VIKE START
 *********************************************************************************************************************/

#define VIKE_CODE
#define VIKE_CONST

#define VIKE_VAR_NO_INIT
#define VIKE_VAR_CLEARED

#define VIKE_APPL_VAR
#define VIKE_APPL_DATA
#define VIKE_APPL_CODE

/**********************************************************************************************************************
 *  VIKE END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  VSECPRIM START
 *********************************************************************************************************************/

#define VSECPRIM_CODE
#define VSECPRIM_CONST
#define VSECPRIM_APPL_CONST
#define VSECPRIM_APPL_VAR
#define VSECPRIM_APPL_DATA


/**********************************************************************************************************************
 *  VSECPRIM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  BSWM START
 *********************************************************************************************************************/

#define BSWM_CODE
#define BSWM_CONST
#define BSWM_PBCFG
#define BSWM_APPL_DATA
#define BSWM_VAR_NO_INIT
#define BSWM_VAR_PBCFG
#define BswM_CODE

/**********************************************************************************************************************
 *  BSWM END
 *********************************************************************************************************************/




/**********************************************************************************************************************
 *  SYSSERVICE_ASR4ECUM START 
 *********************************************************************************************************************/
#define ECUM_APPL_DATA 
#define ECUM_CODE
#define ECUM_CONST
#define ECUM_PBCFG
#define ECUM_VAR_NO_INIT
#define EcuM_CODE

/**********************************************************************************************************************
 *  SYSSERVICE_ASR4ECUM END
 *********************************************************************************************************************/


/* ----------------------------------- FiM Compiler Abstraction ----------------------------------- */
#define FIM_CODE                /* code                                                             */
#define FIM_CONST               /* global/static constants                                          */
#define FIM_PBCFG               /* global/static constants for PostBuild                            */
#define FIM_PBCFG_ROOT          /* global/static constants for PostBuild                            */
#define FIM_VAR_NO_INIT         /* uninitialized global/static variables                            */
#define FIM_VAR_UNCACHED        /* uninitialized global/static un-cached variables                  */
#define FIM_VAR_INIT            /* initialized global/static variables                              */
#define FIM_VAR_CLEARED         /* initialized global/static variables with initialization value 0  */
#define FIM_APPL_DATA           /* variables/buffers outside of FiM                                 */
#define FIM_DEM_DATA            /* variables/buffers of DEM                                         */



/**********************************************************************************************************************
 *  SysService_Asr4WdM START 
 *********************************************************************************************************************/

#define WDGM_CODE
#define WDGM_APPL_CODE
#define WDGM_CONST
#define WDGM_VAR_INIT
#define WDGM_VAR_NOINIT
#define WDGM_VAR_ZERO_INIT
#define WDGM_APPL_DATA
#define WDGM_APPL_CONST

/**********************************************************************************************************************
 *  SysService_Asr4WdM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  SYSSERVICE_ASRCRC START 
 *********************************************************************************************************************/

#define CRC_APPL_DATA
#define CRC_PRIVATE_CODE
#define CRC_CODE
#define CRC_CONST

/**********************************************************************************************************************
 *  SYSSERVICE_ASRCRC END
 *********************************************************************************************************************/


# define DET_CODE
# define DET_VAR
# define DET_APPL_DATA
# define DET_CONST


/**********************************************************************************************************************
 *  ETM START 
 *********************************************************************************************************************/

/* use for functions */
#define ETM_CODE

/* use for function parameters */
#define ETM_APPL_VAR
#define ETM_APPL_DATA
#define ETM_APPL_CONST

/* use for static data */
#define ETM_CONST

/* use for dynamic data */
#define ETM_VAR_NO_INIT
#define ETM_VAR_CLEARED

/**********************************************************************************************************************
 *  ETM END
 *********************************************************************************************************************/




/**********************************************************************************************************************
 *  SysService_AsrRamTst START
 *********************************************************************************************************************/

#define RAMTST_APPL_DATA
#define RAMTST_CODE
#define RAMTST_VAR
#define RAMTST_CONST
#define RAMTST_PBCFG

/**********************************************************************************************************************
 *  SysService_AsrRamTst END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  SD START
 *********************************************************************************************************************/

#define SD_CODE

#define SD_APPL_DATA
#define SD_APPL_VAR

#define SD_CONST
#define SD_PBCFG

#define SD_VAR_NO_INIT
#define SD_VAR_INIT
#define SD_VAR_CLEARED
#define SD_VAR_PBCFG

/**********************************************************************************************************************
 *  SD END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  STBM START
 *********************************************************************************************************************/

/* Module Constant Data */
#define STBM_CONST
#define STBM_PBCFG

/* Module Implementation */
#define STBM_CODE

/* Module Variables which are initialized by the startup code */
#define STBM_VAR_CLEARED
/* Module Variables which are initialized by call of StbM_Init() */
#define STBM_VAR_NO_INIT

#define STBM_VAR_PBCFG

/* Application Code Implementation (e.g. Callbacks) */
#define STBM_APPL_CODE
/* Application Buffer which is located in RAM */
#define STBM_APPL_VAR
/* Application Buffer which is located in ROM or RAM */
#define STBM_APPL_DATA

/**********************************************************************************************************************
 *  STBM END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  CANTSYN START
 *********************************************************************************************************************/

/* Module Constant Data */
#define CANTSYN_CONST

/* Module Implementation */
#define CANTSYN_CODE

/* Module Variables which are initialized by the startup code */
#define CANTSYN_VAR_CLEARED
/* Module Variables which are initialized by call of CanTSyn_Init() */
#define CANTSYN_VAR_NO_INIT

#define CANTSYN_VAR_INIT

#define CANTSYN_PBCFG

/* Application Buffer which is located in RAM */
#define CANTSYN_APPL_VAR
/* Application Buffer which is located in ROM or RAM */
#define CANTSYN_APPL_DATA

/**********************************************************************************************************************
 *  CANTSYN END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  ETHTSYN START
 *********************************************************************************************************************/

#define ETHTSYN_CODE

#define ETHTSYN_CONST
#define ETHTSYN_PBCFG

#define ETHTSYN_APPL_VAR
#define ETHTSYN_APPL_DATA

#define ETHTSYN_VAR_NO_INIT
#define ETHTSYN_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  ETHTSYN END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  FRTSYN START 
 *********************************************************************************************************************/

/* Module Constant Data */
#define FRTSYN_CONST

/* Module Implementation */
#define FRTSYN_CODE

/* Module Variables which are initialized by the startup code */
#define FRTSYN_VAR_CLEARED
/* Module Variables which are initialized by call of FrTSyn_Init() */
#define FRTSYN_VAR_NO_INIT

/* Application Buffer which is located in RAM */
#define FRTSYN_APPL_VAR
/* Application Buffer which is located in ROM or RAM */
#define FRTSYN_APPL_DATA

/**********************************************************************************************************************
 *  FRTSYN END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  DNS START
 *********************************************************************************************************************/

#define DNS_CODE

#define DNS_CONST
#define DNS_PBCFG
#define DNS_PBCFG_ROOT

#define DNS_VAR_NOINIT
#define DNS_VAR_ZERO_INIT

#define DNS_APPL_DATA
#define DNS_APPL_CODE

/**********************************************************************************************************************
 *  DNS END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  SysService_E2eLib START 
 *********************************************************************************************************************/

#define E2E_CODE
#define E2E_VAR_FAST
#define E2E_VAR
#define E2E_CONST
#define E2E_DATA
#define E2E_APPL_DATA
#define E2E_APPL_CONST
#define E2E_APPL_CODE

/**********************************************************************************************************************
 *  SysService_E2eLib END
 *********************************************************************************************************************/





/**********************************************************************************************************************
 *  E2E START 
 *********************************************************************************************************************/


#define E2EPW_CODE
#define E2EPW_VAR_NOINIT
#define E2EPW_VAR_INIT
#define E2EPW_VAR_POWER_ON_INIT
#define E2EPW_VAR_FAST
#define E2EPW_VAR
#define E2EPW_CONST
#define E2EPW_APPL_DATA
#define E2EPW_APPL_CONST
#define E2EPW_APPL_CODE
#define E2EPW_APPL_VAR


/**********************************************************************************************************************
 *  E2E END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  EXI START
 *********************************************************************************************************************/

#define EXI_CODE

#define EXI_CONST

#define EXI_APPL_DATA
#define EXI_APPL_VAR

/**********************************************************************************************************************
 *  EXI END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  ETHFW START 
 *********************************************************************************************************************/

#define ETHFW_CODE

#define ETHFW_APPL_DATA
#define ETHFW_APPL_CONST
#define ETHFW_APPL_CODE

#define ETHFW_CONST
#define ETHFW_PBCFG

#define ETHFW_VAR
#define ETHFW_VAR_NOINIT
#define ETHFW_VAR_INIT
#define ETHFW_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  ETHFW END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  JSON START
 *********************************************************************************************************************/

#define JSON_CODE

#define JSON_CONST
#define JSON_PBCFG
#define JSON_PBCFG_ROOT

#define JSON_VAR_NOINIT
#define JSON_VAR_ZERO_INIT

#define JSON_APPL_DATA
#define JSON_APPL_CODE

/**********************************************************************************************************************
 *  JSON END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  SLAC START 
 *********************************************************************************************************************/

#define SLAC_CODE
#define SLAC_CODE_FAST
#define SLAC_CODE_ISR

#define SLAC_CONST
#define SLAC_CONST_FAST
#define SLAC_PBCFG
#define SLAC_VAR_PBCFG

#define SLAC_VAR_INIT
#define SLAC_VAR_NOINIT
#define SLAC_VAR_ZERO_INIT

#define SLAC_VAR_INIT_FAST
#define SLAC_VAR_NOINIT_FAST
#define SLAC_VAR_ZERO_INIT_FAST

#define SLAC_VAR_INIT_NOCACHE
#define SLAC_VAR_NOINIT_NOCACHE
#define SLAC_VAR_ZERO_INIT_NOCACHE

#define SLAC_APPL_DATA
#define SLAC_APPL_VAR

/**********************************************************************************************************************
 *  SLAC END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  SRP START
 *********************************************************************************************************************/

#define SRP_CODE

#define SRP_CONST
#define SRP_VAR

#define SRP_VAR_CLEARED
#define SRP_VAR_NO_INIT

/**********************************************************************************************************************
 *  SRP END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  SCC START
 *********************************************************************************************************************/

#define SCC_CODE
#define SCC_STATIC_CODE
#define SCC_RTE_CODE

#define SCC_CONST

#define SCC_APPL_DATA
#define SCC_RTE_DATA

#define SCC_VAR_INIT
#define SCC_VAR_NOINIT
#define SCC_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  SCC END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  XMLSECURITY START
 *********************************************************************************************************************/

#define XMLSECURITY_CODE
#define XMLSECURITY_CBK_CODE

#define XMLSECURITY_CONST

#define XMLSECURITY_VAR_NOINIT
#define XMLSECURITY_VAR_ZERO_INIT

#define XMLSECURITY_APPL_DATA
#define XMLSECURITY_APPL_VAR

/**********************************************************************************************************************
 *  XMLSECURITY END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  VCANCCCDM START
 *********************************************************************************************************************/

#define VCANCCCDM_CODE
#define VCANCCCDM_CONST
#define VCANCCCDM_VAR
#define VCANCCCDM_VAR_NOINIT
#define VCANCCCDM_VAR_ZERO_INIT
#define VCANCCCDM_APPL_CODE
#define VCANCCCDM_CANIF_VAR

/**********************************************************************************************************************
 *  VCANCCCDM END
 *********************************************************************************************************************/
 



/**********************************************************************************************************************
 *  vCanCcGbt START
 *********************************************************************************************************************/

#define VCANCCGBT_CODE
#define VCANCCGBT_APPL_CODE

#define VCANCCGBT_CONST
#define VCANCCGBT_PBCFG
#define VCANCCGBT_APPL_DATA

#define VCANCCGBT_VAR_NOINIT
#define VCANCCGBT_VAR_ZERO_INIT
#define VCANCCGBT_VAR_PBCFG

/**********************************************************************************************************************
 *  vCanCcGbt END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  J1939TP START
 *********************************************************************************************************************/

#define J1939TP_CODE

#define J1939TP_CONST
#define J1939TP_PBCFG
#define J1939TP_APPL_DATA

#define J1939TP_VAR_NO_INIT
#define J1939TP_VAR_CLEARED
#define J1939TP_VAR_PBCFG

/**********************************************************************************************************************
 *  J1939TP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANTP START 
 *********************************************************************************************************************/

#define CANTP_CODE
#define CANTP_CONST

#define CANTP_PBCFG
#define CANTP_VAR_PBCFG

#define CANTP_VAR_CLEARED
#define CANTP_VAR_NO_INIT

#define CANTP_APPL_CODE
#define CANTP_APPL_DATA

/**********************************************************************************************************************
 *  CANTP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  DOIP START
 *********************************************************************************************************************/

#define DOIP_CODE

#define DOIP_APPL_CONST
#define DOIP_APPL_DATA
#define DOIP_APPL_VAR
#define DOIP_CONST
#define DOIP_PBCFG

#define DOIP_VAR_NO_INIT
#define DOIP_VAR_CLEARED
#define DOIP_VAR_PBCFG

/**********************************************************************************************************************
 *  DOIP END
 *********************************************************************************************************************/



/***********************************************************************************************************************
 *  SOMEIPTP START 
 **********************************************************************************************************************/

#define SOMEIPTP_CODE

#define SOMEIPTP_CONST

#define SOMEIPTP_APPL_VAR
#define SOMEIPTP_APPL_DATA
#define SOMEIPTP_APPL_CODE

#define SOMEIPTP_VAR_CLEARED
#define SOMEIPTP_VAR_NO_INIT

#define SOMEIPTP_PBCFG
#define SOMEIPTP_VAR_PBCFG

/***********************************************************************************************************************
 *  SOMEIPTP END
 **********************************************************************************************************************/


/**********************************************************************************************************************
 *  TCPIP START
 *********************************************************************************************************************/

#define TCPIP_CODE
#define TCPIP_CODE_ISR

#define TCPIP_CONST
#define TCPIP_PBCFG

#define TCPIP_APPL_CODE
#define TCPIP_APPL_CONST
#define TCPIP_APPL_DATA
#define TCPIP_APPL_VAR

#define TCPIP_VAR_INIT
#define TCPIP_VAR_CLEARED
#define TCPIP_VAR_NO_INIT

/**********************************************************************************************************************
 *  TCPIP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  DOIPINT START
 *********************************************************************************************************************/

#define DOIPINT_CODE

#define DOIPINT_CONST
#define DOIPINT_VAR
#define DOIPINT_PBCFG

#define DOIPINT_VAR_INIT
#define DOIPINT_VAR_NO_INIT
#define DOIPINT_VAR_CLEARED

/**********************************************************************************************************************
 *  DOIPINT END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  HTTP START 
 *********************************************************************************************************************/

/* Module implementation code */
#define HTTP_CODE

/* Module constants */
#define HTTP_CONST
/* Module post-build constants or root constant of the post-build configuration (root table) */
#define HTTP_PBCFG
#define HTTP_PBCFG_ROOT

/* Qualifier for addressen callbacks called APIs of external modules (must match with <MSN>_CODE of external module) */
#define HTTP_APPL_CODE
/* Qualifier to address configuration structures of external modules (must match with qualifier of external module)*/
#define HTTP_APPL_PBCFG

/* Qualifier for databuffer pointers comming from external (called APIs of this module) */
/* Buffers in RAM or ROM (P2CONST value is read only) */
#define HTTP_APPL_DATA
/* Buffer in RAM (P2VAR) */
#define HTTP_APPL_VAR
/* Qualifier for constants comming from external using pointers (called APIs of this module) */
/* Constants (CONST value is read only */
#define HTTP_APPL_CONST

/* Variables */
/* Module variables initialized by startup code or by call of <MSN>_InitMemory() */
#define HTTP_VAR_INIT
/* Module variables initialized by startup code or by call of <MSN>_InitMemory() with value 0 */
#define HTTP_VAR_ZERO_INIT
/* Module variables initialized by call of <MSN>_Init() or in code before use */
#define HTTP_VAR_NOINIT

/**********************************************************************************************************************
 *  HTTP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  AVTP START 
 *********************************************************************************************************************/

#define AVTP_CODE

#define AVTP_APPL_DATA
#define AVTP_APPL_VAR
#define AVTP_CONST

#define AVTP_VAR_NO_INIT
#define AVTP_VAR_CLEARED

/**********************************************************************************************************************
 *  AVTP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2023 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *        \file   FrTp_Compiler_Cfg.inc
 *        \brief  Header file of the FrTp sub-module Compiler_Cfg.
 *
 *      \details  Declares and defines the memory sections of the FrTp.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  TP_ISO10681 START
 *********************************************************************************************************************/

#define FRTP_CODE

#define FRTP_CODE
#define FRTP_CONST

#define FRTP_APPL_DATA
#define FRTP_APPL_CODE

#define FRTP_VAR_NO_INIT
#define FRTP_VAR_CLEARED

#define FRTP_PBCFG
#define FRTP_PBCFG_ROOT
#define FRTP_VAR_PBCFG

/**********************************************************************************************************************
 *  TP_ISO10681 END
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  RTP START 
 *********************************************************************************************************************/

#define RTP_CODE

#define RTP_APPL_DATA
#define RTP_APPL_CONST
#define RTP_APPL_CODE

#define RTP_CONST

#define RTP_VAR
#define RTP_VAR_NOINIT
#define RTP_VAR_INIT
#define RTP_VAR_ZERO_INIT

/**********************************************************************************************************************
 *  RTP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  VBSDAD START 
 *********************************************************************************************************************/

#define VBSDAD_CODE

#define VBSDAD_APPL_DATA
#define VBSDAD_APPL_VAR

#define VBSDAD_CONST
#define VBSDAD_PBCFG

#define VBSDAD_VAR_NOINIT
#define VBSDAD_VAR_ZERO_INIT
#define VBSDAD_VAR_INIT
#define VBSDAD_VAR_PBCFG

/* Package Merger: Stop Section CompilerCfgModuleList */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define RTE_CODE
#define RTE_CONST
#define RTE_VAR_ZERO_INIT
#define RTE_ECUM_APPL_VAR
#define RTE_OS_OSCORE0_SWC_APPL_VAR

#define VSTDLIB_CODE
#define VSTDLIB_CONST
#define VSTDLIB_VAR_FAR
#define VSTDLIB_APPL_VAR


#endif  /* COMPILER_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Compiler_Cfg.h
 *********************************************************************************************************************/
