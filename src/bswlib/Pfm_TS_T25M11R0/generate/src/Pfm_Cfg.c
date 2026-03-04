[!/**
 * \file Pfm_Cfg.c.m
 *
 * \brief AUTOSAR Pfm Configuration Source Template
 *
 * This file contains the Freemarker template for generating 
 * the Pfm configuration source file.
 *
 * \author SWP
 *
 */!][!//

[!/* 
 * PFM Configuration Source File Generation Template
 */!][!//

/* Include Headerfiles  */
#include "Pfm.h"
#include "Pfm_Cfg.h"

/* Module: Pfm Configuration
   Abbreviations used:
   PID: Physical ID - identifies the physical fault detection device
   DDT: Defect Detect Type - type of defect (VCC, GND, OL)
   DFC: Defect Filter Count - counter for fault filtering
*/

/* Defect filter time configuration based on XDM settings */
const uint8 Pfm_DefectFilterTime[PFM_PID_SIZE][PFM_DDT_SIZE][PFM_DFC_SIZE] = 
{
  /* VCC *//* GND *//* OL  */
[!LOOP "as:modconf('Pfm')[1]/PfmChannel/*"!][!//
[!VAR "Shot2VCCDefectDetection" = "node:value(./Shot2VCCDefectDetection)"!][!//
[!VAR "Shot2GNDCDefectDetection" = "node:value(./Shot2GNDCDefectDetection)"!][!//
[!VAR "OpenLoadDefectDetection" = "node:value(./OpenLoadDefectDetection)"!][!//
  {{[!"$Shot2VCCDefectDetection"!], [!"$Shot2VCCDefectDetection"!]},[!//
{[!"$Shot2GNDCDefectDetection"!], [!"$Shot2GNDCDefectDetection"!]},[!//
{[!"OpenLoadDefectDetection"!], [!"$OpenLoadDefectDetection"!]}},  /* PID_[!"name(.)"!] */
[!ENDLOOP!]
};

/* DTC ID mapping configuration */
const uint16 Pfm_DefectDtcId[PFM_PID_SIZE][PFM_DDT_SIZE] =
{    
[!LOOP "as:modconf('Pfm')[1]/PfmChannel/*"!][!//
  {[!//
[!IF "node:exists(./PfmChannelDemEventParameterRefs/PFM_E_SHORT_2_VCC_FAILED)"!][!//
[!"concat('DemConf_DemEventParameter_',as:name(node:ref(./PfmChannelDemEventParameterRefs/PFM_E_SHORT_2_VCC_FAILED)))"!][!//
[!ELSE!][!//
DTC_MAX[!//
[!ENDIF!],[!//
[!IF "node:exists(./PfmChannelDemEventParameterRefs/PFM_E_SHORT_2GND_FAILED)"!][!//
[!"concat('DemConf_DemEventParameter_',as:name(node:ref(./PfmChannelDemEventParameterRefs/PFM_E_SHORT_2GND_FAILED)))"!][!//
[!ELSE!][!//
DTC_MAX[!//
[!ENDIF!],[!//
[!IF "node:exists(./PfmChannelDemEventParameterRefs/PFM_E_OPEN_LOAD_FAILED)"!][!//
[!"concat('DemConf_DemEventParameter_',as:name(node:ref(./PfmChannelDemEventParameterRefs/PFM_E_OPEN_LOAD_FAILED)))"!][!//
[!ELSE!][!//
DTC_MAX[!//
[!ENDIF!]},  /* DTC ID for PID_[!"name(.)"!] */
[!ENDLOOP!]
};

/* Intercept enable mask based on EnableInterception setting */
const uint8 Pfm_InterceptEnableMask[PFM_PID_SIZE] = 
{
[!LOOP "as:modconf('Pfm')[1]/PfmChannel/*"!][!//
[!VAR "EnableInterception" = "node:value(./EnableInterception)"!][!//
[!IF "$EnableInterception = 'SHORT_TO_GND'"!][!//
  0U,  /* PID_[!"name(.)"!] - Interception enabled for GND */
[!ELSE!][!IF "$EnableInterception = 'SHORT_TO_VCC'"!][!//
  1U,  /* PID_[!"name(.)"!] - Interception enabled for VCC */
[!ELSE!][!IF "$EnableInterception = 'OPEN_LOAD'"!][!//
  2U,  /* PID_[!"name(.)"!] - Interception enabled for OPEN_LOAD */
[!ELSE!][!//
  0U,/* PID_[!"name(.)"!] - Interception enabled for GND */
[!ENDIF!][!ENDIF!][!ENDIF!][!//
[!ENDLOOP!]
};

/* Initial intercept state configuration */
const boolean Pfm_InterceptState[PFM_PID_SIZE] = 
{
[!LOOP "as:modconf('Pfm')[1]/PfmChannel/*"!][!//
[!VAR "EnableInterception" = "node:value(./EnableInterception)"!][!//
[!IF "$EnableInterception = 'true'"!][!//
  TRUE,     /* PID_[!"name(.)"!] - Intercept state enabled */[!//
[!ELSE!][!//
  FALSE,    /* PID_[!"name(.)"!] - Intercept state disabled */[!//
[!ENDIF!][!//   
[!ENDLOOP!]
};