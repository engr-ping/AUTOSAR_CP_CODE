[!/**
 * \file Pfm.m
 *
 * \brief AUTOSAR Pfm (Power/Fault Management)
 *
 * This file contains the template macros for code generation
 * of the Pfm module - device fault detection and filtering.
 *
 * \author SWP
 *
 */!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Main Initialization Macro for Pfm Module                             */!][!//
[!/* ===================================================================== */!][!//
[!MACRO "Init_Variables_for_Generation_Pfm"!][!//
[!VAR "swcName_Pfm" = "'Pfm'"!][!//
[!VAR "Pfm_ModuleIdValue" = "''"!][!//
[!VAR "Pfm_MaxPhysicalDevices" = "num:i(1)"!][!//
[!VAR "Pfm_DetectTypes" = "num:i(3)"!][!//
[!VAR "Pfm_FilterStates" = "num:i(2)"!][!//
[!VAR "Pfm_DetectStates" = "num:i(5)"!][!//
[!VAR "Pfm_DemIntegrationEnabled" = "true()"!][!//
[!VAR "Pfm_FilterCountForSet" = "num:i(3)"!][!//
[!VAR "Pfm_FilterCountForClear" = "num:i(5)"!][!//
[!//
[!/* Determine module ID */!][!//
[!IF "exists(as:modconf('Pfm')[1])"!][!//
[!VAR "Pfm_ModuleIdValue" = "num:i(0xAB)"!][!//
[!ENDIF!][!//
[!//
[!/* Read configuration parameters from General section */!][!//
[!IF "exists(as:modconf('Pfm')[1]/General)"!][!//
[!VAR "Pfm_MaxPhysicalDevices" = "node:value(as:modconf('Pfm')[1]/General/MaxPhysicalDevices)"!][!//
[!VAR "Pfm_FilterCountForSet" = "node:value(as:modconf('Pfm')[1]/General/FilterCountForSet)"!][!//
[!VAR "Pfm_FilterCountForClear" = "node:value(as:modconf('Pfm')[1]/General/FilterCountForClear)"!][!//
[!VAR "Pfm_DemIntegrationEnabled" = "node:value(as:modconf('Pfm')[1]/General/DemErrorEnableFlag) = '1'"!][!//
[!ENDIF!][!//
[!//
[!/* Count physical devices from PfmChannel list */!][!//
[!IF "exists(as:modconf('Pfm')[1]/PfmChannel)"!][!//
[!VAR "Pfm_MaxPhysicalDevices" = "count(as:modconf('Pfm')[1]/PfmChannel/*)"!][!//
[!ENDIF!][!//
[!//
[!ENDMACRO!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Module ID Calculation Macro                                          */!][!//
[!/* ===================================================================== */!][!//
[!MACRO "Pfm_ModuleID_calculations"!][!//
[!VAR "Pfm_ModuleIdValue" = "num:i(0xAB)"!][!//
[!ENDMACRO!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Configuration Parameter Validation Macro                             */!][!//
[!/* ===================================================================== */!][!//
[!MACRO "Pfm_Configuration_Validation"!][!//
[!/* Validate filter count values */!][!//
[!IF "$Pfm_FilterCountForSet < 1 or $Pfm_FilterCountForSet > 255"!][!//
[!ERROR "Pfm: FilterCountForSet must be between 1 and 255"!][!//
[!ENDIF!][!//
[!IF "$Pfm_FilterCountForClear < 1 or $Pfm_FilterCountForClear > 255"!][!//
[!ERROR "Pfm: FilterCountForClear must be between 1 and 255"!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Abbreviation Definitions                                             */!][!//
[!/* ===================================================================== */!][!//
[!/* 
   PID: Physical ID - unique identifier for physical fault detection devices (1 to PFM_PID_SIZE)
   DDT: Defect Detect Type - type of defect detected
         PFM_DDT_VCC (0): Short to Power Supply
         PFM_DDT_GND (1): Short to Ground
         PFM_DDT_OL  (2): Open Load
   DFC: Defect Filter Count - counter for fault filtering
         PFM_DFC_SET (0): Counter for confirming fault detection
         PFM_DFC_CLR (1): Counter for clearing fault detection
   DDS: Defect Detect State - current state of defect detection
         PFM_DDS_ING (0): In-progress
         PFM_DDS_POS (1): Positive
         PFM_DDS_NEG (2): Negative
         PFM_DDS_SET (3): Set
         PFM_DDS_CLR (4): Clear
   DRS: Defect Report State - fault state information structure
   DEM: Diagnostic Event Manager - module for diagnostic event management
   FID: Function ID mapping (alias for PID in some contexts)
*/!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Generate Service Entry Points                                        */!][!//
[!/* ===================================================================== */!][!//
[!MACRO "Pfm_Generate_ServiceEntryPoints"!][!//
[!/* Service IDs and Timing */!][!//
[!VAR "Pfm_Init_ServiceID" = "num:i(0x01)"!][!//
[!VAR "Pfm_10ms_ServiceID" = "num:i(0x02)"!][!//
[!VAR "Pfm_10ms_Period" = "num:i(10)"!][!//
[!VAR "Pfm_EnableDiagnostic_ServiceID" = "num:i(0x03)"!][!//
[!VAR "Pfm_DefectReport_ServiceID" = "num:i(0x04)"!][!//
[!VAR "Pfm_ClearFault_ServiceID" = "num:i(0x05)"!][!//
[!VAR "Pfm_ClearFaultAll_ServiceID" = "num:i(0x06)"!][!//
[!VAR "Pfm_GetFaultState_ServiceID" = "num:i(0x07)"!][!//
[!ENDMACRO!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Generate Extern Configuration Constants                              */!][!//
[!/* ===================================================================== */!][!//
[!MACRO "Pfm_Generate_Config_Constants"!][!//
[!/* 
   extern const uint8 Pfm_DefectFilterTime[PFM_PID_SIZE][PFM_DDT_SIZE][PFM_DFC_SIZE];
   extern const uint16 Pfm_DefectDtcId[PFM_PID_SIZE][PFM_DDT_SIZE];
   extern const uint8 Pfm_InterceptEnableMask[PFM_PID_SIZE];
   extern const boolean Pfm_InterceptState[PFM_PID_SIZE];
*/!][!//
[!ENDMACRO!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Type Definitions and Enumerations                                    */!][!//
[!/* ===================================================================== */!][!//
[!MACRO "Pfm_Generate_Types"!][!//
[!/* 
   typedef enum
   {
       PFM_DDS_ING,   // In-progress
       PFM_DDS_POS,   // Positive state
       PFM_DDS_NEG,   // Negative state
       PFM_DDS_SET,   // Set state
       PFM_DDS_CLR,   // Clear state
       PFM_DDS_SIZE
   } PFM_DefectDetectState_e;

   typedef enum
   {
       PFM_DDT_VCC,   // Short to VCC
       PFM_DDT_GND,   // Short to GND
       PFM_DDT_OL,    // Open Load
       PFM_DDT_SIZE
   } PFM_DefectDetectType_e;

   typedef enum
   {
       PFM_DFC_SET,   // Set counter for fault confirmation
       PFM_DFC_CLR,   // Clear counter for fault clearing
       PFM_DFC_SIZE
   } PFM_DefectFilterCount_e;
*/!][!//
[!ENDMACRO!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Global Variables Declaration Macro                                   */!][!//
[!/* ===================================================================== */!][!//
[!MACRO "Pfm_Generate_Global_Variables"!][!//
[!/* 
   Exported:
   - boolean Pfm_InterceptEnable[PFM_PID_SIZE];
   
   Static (local to PFM.c):
   - static boolean Pfm_FaultUpdateEnable[PFM_PID_SIZE];
   - static boolean Pfm_FaultUpdateEnableGlobal;
   - static uint8 Pfm_DefectFilterCount[PFM_PID_SIZE][PFM_DDT_SIZE][PFM_DFC_SIZE];
   - static uint8 Pfm_FaultState[PFM_PID_SIZE];
   - static PFM_DefectDetectState_e Pfm_DefectDetectState[PFM_PID_SIZE][PFM_DDT_SIZE];
*/!][!//
[!ENDMACRO!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Function Declarations Macro                                          */!][!//
[!/* ===================================================================== */!][!//
[!MACRO "Pfm_Generate_Functions"!][!//
[!/* 
   extern void Pfm_Init(void);
   extern void Pfm_10ms(void);
   extern void Pfm_EnableDiagnostic(uint8 Id, boolean Enable);
   extern void Pfm_DefectReport(PFM_PhysicalId_e Pid, 
                                PFM_DefectDetectState_e OpenLoad,
                                PFM_DefectDetectState_e Short2Vcc,
                                PFM_DefectDetectState_e Short2Gnd);
   extern void Pfm_ClearFault(uint8 Id);
   extern void Pfm_ClearFaultAll(void);
   extern boolean Pfm_GetFaultState(PFM_PhysicalId_e Pid, uint8 Ddt);
   
   Static (internal):
   - static void Pfm_ReportError2DEM(const uint16 dtcId);
   - static void Pfm_ClearError2DEM(const uint16 dtcId);
*/!][!//
[!ENDMACRO!][!//
[!//
[!/* ===================================================================== */!][!//
[!/* Call initialization macro at module load                             */!][!//
[!/* ===================================================================== */!][!//
[!CALL "Init_Variables_for_Generation_Pfm"!][!//
[!CALL "Pfm_ModuleID_calculations"!][!//
[!CALL "Pfm_Configuration_Validation"!][!//
[!CALL "Pfm_Generate_ServiceEntryPoints"!][!//
