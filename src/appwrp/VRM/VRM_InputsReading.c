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

#include "Rte_VRM_InputsReading.h" /* PRQA S 0857 */ /* MD_MSR_1.1_857 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "VRM_Cfg.h"
static uint16 VRM_InputDebounce( uint16 InputValue, uint16 * DebounceBuffer, uint8 DebounceTime );
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
#include "VRM_InputsReading_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VRM_InputsReading_vInit
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * This runnable is never executed by the RTE.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: VRM_InputsReading_vInit_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, VRM_InputsReading_CODE) VRM_InputsReading_vInit(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VRM_InputsReading_vInit
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: VRM_InputsReading_vMainFunction
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
 *   Std_ReturnType Rte_Write_gVRM_u16VBatADValue_Val(UInt16 data)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: VRM_InputsReading_vMainFunction_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, VRM_InputsReading_CODE) VRM_InputsReading_vMainFunction(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: VRM_InputsReading_vMainFunction
 *********************************************************************************************************************/
    uint16 tmp_u16Ext1AdValueFilted,tmp_u16Ext2AdValueFilted,tmp_u16BatAdValueFilted;
    static uint16 sVRM_u16RawExt1AdValue[VRM_EXT1_DEBOUNCE_COUNT],sVRM_u16RawExt2AdValue[VRM_EXT2_DEBOUNCE_COUNT],    \
                   sVRM_u16RawBatAdValue[VRM_BAT_DEBOUNCE_COUNT];
    uint16 tmp_u16Ext1Ad,tmp_u16Ext2Ad,tmp_u16BatAd,tmp_u16Ext1Value,tmp_u16Ext2Value,tmp_u16BatValue;
    static uint8 tmp_Ext1DebounceCnt = 0,tmp_Ext2DebounceCnt = 0,tmp_BatDebounceCnt = 0;

    /* Read the KL30_1 and KL30_2's AD value from Rte */
    Rte_Read_ADPOW_AD_KL30_1_FV(&tmp_u16Ext1Ad);
    Rte_Read_ADPOW_AD_KL30_2_FV(&tmp_u16Ext2Ad);

    /* Priority Ext1 highest, Ext2 second*/
    if(tmp_u16Ext1Ad > VRM_DETA1)
    {
        if(tmp_u16Ext2Ad < (tmp_u16Ext1Ad - VRM_DETA1))  //Subtraction of Two Unsigned Variables may cause overflow, to be a bigger number
        {
            tmp_u16BatAd = tmp_u16Ext1Ad;
        }
        else
        {
            tmp_u16BatAd = tmp_u16Ext2Ad;
        }
    }
    else
    {
        tmp_u16BatAd = tmp_u16Ext2Ad;
    }

    /* Write Bat AD value to Rte */
    (void)Rte_Write_gVRM_u16VBatADValue_Val(tmp_u16BatAd);          /* PRQA S 3426 */
    
    /* Do debounce in vrm module */
    tmp_u16Ext1AdValueFilted = VRM_InputDebounce(tmp_u16Ext1Ad, sVRM_u16RawExt1AdValue, VRM_EXT1_DEBOUNCE_COUNT);
    tmp_u16Ext2AdValueFilted = VRM_InputDebounce(tmp_u16Ext2Ad, sVRM_u16RawExt2AdValue, VRM_EXT2_DEBOUNCE_COUNT);
    tmp_u16BatAdValueFilted = VRM_InputDebounce(tmp_u16BatAd, sVRM_u16RawBatAdValue, VRM_BAT_DEBOUNCE_COUNT);

    /* Ext1: Volt physical value and Write to Rte, uint/mV */
    if(tmp_Ext1DebounceCnt >= VRM_EXT1_DEBOUNCE_COUNT)
    {
        tmp_u16Ext1Value = VRM_CONVERT_AD2VOL_POW(tmp_u16Ext1AdValueFilted);        /* PRQA S 2983 */
        (void)Rte_Write_gASI_u16KL30_1Volt_mv_Val(tmp_u16Ext1Value);                /* PRQA S 3112 */
    }
    else
    { 
        /* Init 5 times, the volt value is defualt value: 12000mV */
        tmp_Ext1DebounceCnt++;
        (void)Rte_Write_gASI_u16KL30_1Volt_mv_Val(VRM_EXT1_AD2VOL_DEFAULT_VAL);      /* PRQA S 3112 */
    }

    /* Ext2: Volt physical value and Write to Rte, uint/mV */
    if(tmp_Ext2DebounceCnt >= VRM_EXT2_DEBOUNCE_COUNT)
    {
        tmp_u16Ext2Value = VRM_CONVERT_AD2VOL_POW(tmp_u16Ext2AdValueFilted);        /* PRQA S 2983 */
        (void)Rte_Write_gASI_u16KL30_2Volt_mv_Val(tmp_u16Ext2Value);                /* PRQA S 3112 */
    }
    else
    { 
        /* Init 5 times, the volt value is defualt value: 12000mV */
        tmp_Ext2DebounceCnt++;
        (void)Rte_Write_gASI_u16KL30_2Volt_mv_Val(VRM_EXT2_AD2VOL_DEFAULT_VAL);      /* PRQA S 3112 */
    }

    /*Bat: Volt physical value and Write to Rte, uint/mV */
    if(tmp_BatDebounceCnt >= VRM_BAT_DEBOUNCE_COUNT)
    {
        tmp_u16BatValue = VRM_CONVERT_AD2VOL_POW(tmp_u16BatAdValueFilted);
        (void)Rte_Write_gASI_u16BatteryVolt_mv_Val(tmp_u16BatValue);                 /* PRQA S 3426,3417 */
    }
    else
    {
        /* Init 5 times, the volt value is defualt value: 12000mV */
        tmp_BatDebounceCnt++;
        (void)Rte_Write_gASI_u16BatteryVolt_mv_Val(VRM_BAT_AD2VOL_DEFAULT_VAL);      /* PRQA S 3426, 3417 */
    }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define VRM_InputsReading_STOP_SEC_CODE
#include "VRM_InputsReading_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
static uint16 VRM_InputDebounce( uint16 InputValue, uint16 * DebounceBuffer, uint8 DebounceTime )
{
    uint32  u32Sum;
    uint16* pu16Tmp;
    uint16  u16Ret;
    uint16  u16Max;
    uint16  u16Min;
    uint8   i;

    if(DebounceTime == 0u)
    {
        /* if debounce time is 0 or 1, output is input everytime.  */
        u16Ret = InputValue;
    }
    else 
    {
        if(DebounceTime == 1u)
        {
            /* if debounce time is 2, output is average value of current input and last time input.  */
            u32Sum              = (uint32)(*DebounceBuffer) + (uint32)InputValue;
            u16Ret              = (uint16)(u32Sum >> 1);
        }
        else
        {
            /* The maximum of debounce time is DEBOUNCE_VRM_TIME_MAX */
            if(DebounceTime > DEBOUNCE_VRM_TIME_MAX)
            {
                DebounceTime  = DEBOUNCE_VRM_TIME_MAX;                        /* PRQA S 1338 */
            }

            /* if debounce time is 2 or up 2. */
            DebounceTime      = DebounceTime - 1u;                          /* PRQA S 1338 */
            pu16Tmp             = DebounceBuffer + DebounceTime;             /* PRQA S 0488 */

            /* First remove maximum and minimum value. Then get the average value.  */
            if( InputValue > *pu16Tmp )
            {
                u16Max          = InputValue;
                u16Min          = *pu16Tmp;
            }
            else
            {
                u16Max          = *pu16Tmp;
                u16Min          = InputValue;
            }

            /* Sum of the latest series inputs, except maximum and minimum. */
            u32Sum              = 0;
            for( i = 0; i < DebounceTime; i++ )
            {
                *pu16Tmp        = *(pu16Tmp - 1);
                pu16Tmp         = pu16Tmp - 1;

                if( *pu16Tmp > u16Max )
                {
                    u32Sum     += u16Max;
                    u16Max      = *pu16Tmp;
                }
                else if( *pu16Tmp < u16Min )
                {
                    u32Sum     += u16Min;
                    u16Min      = *pu16Tmp;
                }
                else
                {
                    u32Sum     += *pu16Tmp;
                }
            }

            /* Get the average value  */
            u32Sum             /= DebounceTime;

            if( u32Sum > 0xFFFFu)
            {
                u16Ret          = 0xFFFFu;
            }
            else
            {
                u16Ret          = (uint16)u32Sum;
            }
        }

        /* save current input unitl next time calculation. */
        *DebounceBuffer        = InputValue; 
    }

    return(u16Ret);
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
