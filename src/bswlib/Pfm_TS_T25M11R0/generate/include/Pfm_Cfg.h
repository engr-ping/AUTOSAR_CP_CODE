[!/**
 * \file Pfm_Cfg.h.m
 *
 * \brief AUTOSAR Pfm Configuration Header Template
 *
 * This file contains the Freemarker template for generating 
 * the Pfm configuration header file.
 *
 * \author SWP
 *
 */!][!//

[!/* 
 * PFM Configuration Header File Generation Template
 */!][!//

#ifndef _PFM_CFG_H
#define _PFM_CFG_H
#include "Pfm_Types.h"

/***********************    Global Type Definition    ************************/

/* Abbreviations used throughout this module:
   DDS: Defect Detect State (ING: In-progress, POS: Positive, NEG: Negative, SET: Set, CLR: Clear)
   DDT: Defect Detect Type (VCC: Short to VCC, GND: Short to GND, OL: Open Load)
   DFC: Defect Filter Count (SET: Set counter, CLR: Clear counter)
   DRS: Defect Report State, PID: Physical ID, FID: Function ID (alias for PID)
*/

/***********************    Global Type Definition    ************************/

/* Chip of group list order: from left to right, from top to down */

/* Define the physical ID enumeration based on MaxPhysicalDevices from XDM config */
[!VAR "i" = "0"!]
typedef enum
{
[!LOOP "as:modconf('Pfm')[1]/PfmChannel/*"!][!//
  PFM_PID_[!"name(.)"!] = [!"num:i($i)"!]u,[!//\N
[!VAR "i" = "num:i($i) + 1"!][!//
[!ENDLOOP!]
  PFM_PID_SIZE
} PFM_PhysicalId_e;

/***********************    Global Constant Definition    ************************/

#define DTC_MAX ((uint16)0xFFFFu)

/* DEM Error Enable Flag based on XDM configuration */
//#define PFM_DEM_ERROR_ENABLE_FLG   

/**************************  Macro Definitions    **************************/

/* Abbreviations used in macro names:
   FID: Function ID mapping (aliases for PID), 
   PID: Physical ID, DDT: Defect Detect Type, DFC: Defect Filter Count
*/

[!LOOP "as:modconf('Pfm')[1]/PfmChannel/*"!][!//
[!IF "node:value(./Shot2VCCDefectDetection) != 0"!]
#define PFM_FID_PID_[!"name(.)"!]_VCC    (0)
[!ENDIF!][!//
[!IF "node:value(./Shot2GNDCDefectDetection) != 0"!]
#define PFM_FID_PID_[!"name(.)"!]_GND    (0)
[!ENDIF!][!//
[!IF "node:value(./OpenLoadDefectDetection) != 0"!]
#define PFM_FID_PID_[!"name(.)"!]_OL    (0)
[!ENDIF!][!//
[!ENDLOOP!]

extern const uint8 Pfm_DefectFilterTime[PFM_PID_SIZE][PFM_DDT_SIZE][PFM_DFC_SIZE];
extern const uint16 Pfm_DefectDtcId[PFM_PID_SIZE][PFM_DDT_SIZE];
extern const uint8 Pfm_InterceptEnableMask[PFM_PID_SIZE];
extern const boolean Pfm_InterceptState[PFM_PID_SIZE];

#endif // _PFM_CFG_H