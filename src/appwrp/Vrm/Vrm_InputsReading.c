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

#include "Rte_Vrm_InputsReading.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Vrm_Cfg.h"
static uint16 Vrm_InputDebounce( uint16 InputValue, uint16 * DebounceBuffer, uint8 DebounceTime );
#define DEBOUNCE_VRM_TIME_MAX  (8u)
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * IOHWAB_UINT16: Integer in interval [0...65535]
 * UInt16: Integer in interval [0...65535]
 * uint16: Integer in interval [0...65535] (standard type)
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Indirect API:
 * =============
 *   Rte_PortHandle_ADPOW_If_R Rte_Ports_ADPOW_If_R(void)
 *
 *   uint8 Rte_NPorts_ADPOW_If_R(void)
 *   Rte_PortHandle_ADPOW_If_R Rte_Port_ADPOW(void)
 *********************************************************************************************************************/


#define VRM_InputsReading_START_SEC_CODE
#include "Vrm_InputsReading_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Vrm_InputsReading_vInit
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * This runnable is never executed by the RTE.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Vrm_InputsReading_vInit_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Vrm_InputsReading_CODE) Vrm_InputsReading_vInit(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Vrm_InputsReading_vInit
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: Vrm_InputsReading_vMainFunction
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_ADPOW_AD_KL30_1_FV(IOHWAB_UINT16 *data)
 *   Std_ReturnType Rte_Read_ADPOW_AD_KL30_2_FV(IOHWAB_UINT16 *data)
 *   Std_ReturnType Rte_Read_ADPOW_AD_SLC_POWER_FV(IOHWAB_UINT16 *data)
 *   Std_ReturnType Rte_Read_ADPOW_AD_VPUP1_FV(IOHWAB_UINT16 *data)
 *   Std_ReturnType Rte_Read_ADPOW_AD_VPUP2_FV(IOHWAB_UINT16 *data)
 *   Std_ReturnType Rte_Read_ADPOW_AD_VPUP3_FV(IOHWAB_UINT16 *data)
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_gASI_u16BatteryVolt_mv_Val(UInt16 data)
 *   Std_ReturnType Rte_Write_gASI_u16KL30_1Volt_mv_Val(UInt16 data)
 *   Std_ReturnType Rte_Write_gASI_u16KL30_2Volt_mv_Val(UInt16 data)
 *   Std_ReturnType Rte_Write_gVrm_u16VBatADValue_Val(UInt16 data)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: Vrm_InputsReading_vMainFunction_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, Vrm_InputsReading_CODE) Vrm_InputsReading_vMainFunction(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: Vrm_InputsReading_vMainFunction
 *********************************************************************************************************************/
    uint16 ext1AdValueFiltered, ext2AdValueFiltered, batAdValueFiltered;
    static uint16 sVrm_rawExt1AdValue[VRM_EXT1_DEBOUNCE_COUNT], sVrm_rawExt2AdValue[VRM_EXT2_DEBOUNCE_COUNT],    \
                   sVrm_rawBatAdValue[VRM_BAT_DEBOUNCE_COUNT];
    uint16 ext1Ad, ext2Ad, batAd, ext1Value, ext2Value, batValue;
    static uint8 ext1DebounceCnt = 0, ext2DebounceCnt = 0, batDebounceCnt = 0;

    /* Read the KL30_1 and KL30_2's AD value from Rte */
    Rte_Read_ADPOW_AD_KL30_1_FV(&ext1Ad);
    Rte_Read_ADPOW_AD_KL30_2_FV(&ext2Ad);

    /* Priority Ext1 highest, Ext2 second*/
    if(ext1Ad > VRM_DETA1)
    {
        if(ext2Ad < (ext1Ad - VRM_DETA1))  //Subtraction of Two Unsigned Variables may cause overflow, to be a bigger number
        {
            batAd = ext1Ad;
        }
        else
        {
            batAd = ext2Ad;
        }
    }
    else
    {
        batAd = ext2Ad;
    }

    /* Write Bat AD value to Rte */
    (void)Rte_Write_gVrm_u16VBatADValue_Val(batAd);          /* PRQA S 3426 */
    
    /* Do debounce in vrm module */
    ext1AdValueFiltered = Vrm_InputDebounce(ext1Ad, sVrm_rawExt1AdValue, VRM_EXT1_DEBOUNCE_COUNT);
    ext2AdValueFiltered = Vrm_InputDebounce(ext2Ad, sVrm_rawExt2AdValue, VRM_EXT2_DEBOUNCE_COUNT);
    batAdValueFiltered = Vrm_InputDebounce(batAd, sVrm_rawBatAdValue, VRM_BAT_DEBOUNCE_COUNT);

    /* Ext1: Volt physical value and Write to Rte, uint/mV */
    if(ext1DebounceCnt >= VRM_EXT1_DEBOUNCE_COUNT)
    {
        ext1Value = VRM_CONVERT_AD2VOL_POW(ext1AdValueFiltered);        /* PRQA S 2983 */
        (void)Rte_Write_gASI_u16KL30_1Volt_mv_Val(ext1Value);                /* PRQA S 3112 */
    }
    else
    { 
        /* Init 5 times, the volt value is defualt value: 12000mV */
        ext1DebounceCnt++;
        (void)Rte_Write_gASI_u16KL30_1Volt_mv_Val(VRM_EXT1_AD2VOL_DEFAULT_VAL);      /* PRQA S 3112 */
    }

    /* Ext2: Volt physical value and Write to Rte, uint/mV */
    if(ext2DebounceCnt >= VRM_EXT2_DEBOUNCE_COUNT)
    {
        ext2Value = VRM_CONVERT_AD2VOL_POW(ext2AdValueFiltered);        /* PRQA S 2983 */
        (void)Rte_Write_gASI_u16KL30_2Volt_mv_Val(ext2Value);                /* PRQA S 3112 */
    }
    else
    { 
        /* Init 5 times, the volt value is defualt value: 12000mV */
        ext2DebounceCnt++;
        (void)Rte_Write_gASI_u16KL30_2Volt_mv_Val(VRM_EXT2_AD2VOL_DEFAULT_VAL);      /* PRQA S 3112 */
    }

    /*Bat: Volt physical value and Write to Rte, uint/mV */
    if(batDebounceCnt >= VRM_BAT_DEBOUNCE_COUNT)
    {
        batValue = VRM_CONVERT_AD2VOL_POW(batAdValueFiltered);
        (void)Rte_Write_gASI_u16BatteryVolt_mv_Val(batValue);                 /* PRQA S 3426,3417 */
    }
    else
    {
        /* Init 5 times, the volt value is defualt value: 12000mV */
        batDebounceCnt++;
        (void)Rte_Write_gASI_u16BatteryVolt_mv_Val(VRM_BAT_AD2VOL_DEFAULT_VAL);      /* PRQA S 3426, 3417 */
    }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define VRM_InputsReading_STOP_SEC_CODE
#include "Vrm_InputsReading_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
static uint16 Vrm_InputDebounce( uint16 inputValue, uint16 * debounceBuffer, uint8 debounceTime )
{
    uint32  sum;
    uint16* tmpPtr;
    uint16  ret;
    uint16  max;
    uint16  min;
    uint8   i;

    if(debounceTime == 0u)
    {
        /* if debounce time is 0 or 1, output is input everytime.  */
        ret = inputValue;
    }
    else 
    {
        if(debounceTime == 1u)
        {
            /* if debounce time is 2, output is average value of current input and last time input.  */
            sum              = (uint32)(*debounceBuffer) + (uint32)inputValue;
            ret              = (uint16)(sum >> 1);
        }
        else
        {
            /* The maximum of debounce time is DEBOUNCE_VRM_TIME_MAX */
            if(debounceTime > DEBOUNCE_VRM_TIME_MAX)
            {
                debounceTime  = DEBOUNCE_VRM_TIME_MAX;                        /* PRQA S 1338 */
            }

            /* if debounce time is 2 or up 2. */
            debounceTime      = debounceTime - 1u;                          /* PRQA S 1338 */
            tmpPtr             = debounceBuffer + debounceTime;             /* PRQA S 0488 */

            /* First remove maximum and minimum value. Then get the average value.  */
            if( inputValue > *tmpPtr )
            {
                max          = inputValue;
                min          = *tmpPtr;
            }
            else
            {
                max          = *tmpPtr;
                min          = inputValue;
            }

            /* Sum of the latest series inputs, except maximum and minimum. */
            sum              = 0;
            for( i = 0; i < debounceTime; i++ )
            {
                *tmpPtr        = *(tmpPtr - 1);
                tmpPtr         = tmpPtr - 1;

                if( *tmpPtr > max )
                {
                    sum     += max;
                    max      = *tmpPtr;
                }
                else if( *tmpPtr < min )
                {
                    sum     += min;
                    min      = *tmpPtr;
                }
                else
                {
                    sum     += *tmpPtr;
                }
            }

            /* Get the average value  */
            sum             /= debounceTime;

            if( sum > 0xFFFFu)
            {
                ret          = 0xFFFFu;
            }
            else
            {
                ret          = (uint16)sum;
            }
        }

        /* save current input unitl next time calculation. */
        *debounceBuffer        = inputValue; 
    }

    return(ret);
}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
