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
#include "VRM_Cfg.h"
#include "IoHwAb_DigitalOutput.h"
#include "IoHwAb_PwmOutput.h"


#if (VRM_INTERCEPT_OUTPUT_QUERY != 0U)
//----------------------------------------------------------------------------
/* 
FALSE:  output channel can be vrm intercept,no matter output has been on or off, default  
TRUE:   output channel can't be vrm intercept,when output has been enabled 
*/ 
//----------------------------------------------------------------------------
const boolean VRM_InterceptControlOnCloseArray[VRM_PID_SIZE] = 
{
    FALSE,    /*DUMMY*/
    FALSE,    /*OPH01*/
    FALSE,    /*OPH02*/
    FALSE,    /*OPH03*/
    FALSE,    /*OPH04*/
    FALSE,    /*OPH05*/
    FALSE,    /*OPH06*/
    FALSE,    /*OPH07*/
    FALSE,    /*OPH08*/
    FALSE,    /*OPH09*/
    FALSE,    /*OPH10*/
   
    FALSE,    /*OPH11*/
    FALSE,    /*OPH12*/
    FALSE,    /*OPH13*/
    FALSE,    /*OPH14*/
    FALSE,    /*OPH15*/
    FALSE,    /*OPH16*/
    FALSE,    /*OPH17*/
    FALSE,    /*OPH18*/
    FALSE,    /*OPH19*/
    FALSE,    /*OPH20*/
  
    FALSE,    /*OPH21*/
    FALSE,    /*OPH22*/
    FALSE,    /*OPH23*/
    FALSE,    /*OPH24*/
    FALSE,    /*OPH25*/
    FALSE,    /*OPH26*/
    FALSE,    /*OPH27*/
    FALSE,    /*OPH28*/
    FALSE,    /*OPH29*/
    FALSE,    /*OPH30*/
  
    FALSE,    /*OPH31*/
    FALSE,    /*OPH32*/
    FALSE,    /*OPH33*/
    FALSE,    /*OPH34*/
    FALSE,    /*OPH35*/
    FALSE,    /*OPH36*/
    FALSE,    /*OPH37*/
    FALSE,    /*OPH38*/
    FALSE,    /*OPH39*/
    FALSE,    /*OPH40*/
  
    FALSE,    /*OPH41*/
    FALSE,    /*OPH42*/
    FALSE,    /*OPH43*/
    FALSE,    /*OPH44*/
    FALSE,    /*OPH45*/
    
    FALSE,    /*OPL01*/
    
    FALSE,    /*OR01*/
    FALSE,    /*OR02*/
    FALSE,    /*OR03*/
    FALSE,    /*OR04*/
    FALSE,    /*OR05*/
    FALSE,    /*OR06*/
    FALSE,    /*OR07*/
    FALSE,    /*OR08*/
    FALSE,    /*OR09*/
    FALSE,    /*OR10*/
    
    FALSE,    /*OR11*/
    FALSE,    /*OR12*/
    FALSE,    /*OR13*/
    FALSE,    /*OR14*/

    FALSE,    /*ODH01*/
    FALSE,    /*ODH02*/
    FALSE,    /*ODH03*/
    FALSE,    /*ODH04*/
    FALSE,    /*ODH05*/
    FALSE,    /*ODH06*/
    FALSE,    /*ODH07*/
    FALSE,    /*ODH08*/

    FALSE,    /*ODL01*/
    FALSE,    /*ODL02*/
    FALSE,    /*ODL03*/
    FALSE,    /*ODL04*/
    FALSE,    /*ODL05*/
    FALSE,    /*ODL06*/
    FALSE,    /*ODL07*/
    FALSE,    /*ODL08*/
    FALSE,    /*ODL09*/
    FALSE,    /*ODL10*/

    FALSE,    /*ODL11*/
    FALSE,    /*ODL12*/
    FALSE,    /*ODL13*/
    FALSE,    /*ODL14*/
    FALSE,    /*ODL15*/
    FALSE,    /*ODL16*/
    FALSE,    /*ODL17*/
    FALSE,    /*ODL18*/
    FALSE,    /*ODL19*/
    FALSE,    /*ODL20*/
    
    FALSE,    /*ODL21*/
    FALSE,    /*ODL22*/
    FALSE,    /*ODL23*/
    FALSE,    /*ODL24*/
    FALSE,    /*ODL25*/
    FALSE,    /*ODL26*/
    FALSE,    /*ODL27*/
    FALSE,    /*ODL28*/
    FALSE,    /*ODL29*/
    FALSE,    /*ODL30*/

    FALSE     /*ODL31*/
};

//----------------------------------------------------------------------------
/* 
detail all VRM intercept output status index
*/ 
//----------------------------------------------------------------------------
const uint8 * VRM_OutputStatePointerArray[VRM_PID_SIZE] = 
{
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_DUMMY]),       /* VRM_PID_DUMMY */
        
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH01]),     /* VRM_PID_OPH01 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH02]),     /* VRM_PID_OPH02 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH03]),     /* VRM_PID_OPH03 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH04]),     /* VRM_PID_OPH04 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH05]),     /* VRM_PID_OPH05 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH06]),     /* VRM_PID_OPH06 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH07]),     /* VRM_PID_OPH07 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH08]),     /* VRM_PID_OPH08 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH09]),     /* VRM_PID_OPH09 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH10]),     /* VRM_PID_OPH10 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH11]),     /* VRM_PID_OPH11 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH12]),     /* VRM_PID_OPH12 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH13]),     /* VRM_PID_OPH13 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH14]),     /* VRM_PID_OPH14 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH15]),     /* VRM_PID_OPH15 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH16]),     /* VRM_PID_OPH16 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH17]),     /* VRM_PID_OPH17 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH18]),     /* VRM_PID_OPH18 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH19]),     /* VRM_PID_OPH19 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH20]),     /* VRM_PID_OPH20 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH21]),     /* VRM_PID_OPH21 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH22]),     /* VRM_PID_OPH22 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH23]),     /* VRM_PID_OPH23 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH24]),     /* VRM_PID_OPH24 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH25]),     /* VRM_PID_OPH25 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH26]),     /* VRM_PID_OPH26 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH27]),     /* VRM_PID_OPH27 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH28]),     /* VRM_PID_OPH28 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH29]),     /* VRM_PID_OPH29 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH30]),     /* VRM_PID_OPH30 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH31]),     /* VRM_PID_OPH31 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH32]),     /* VRM_PID_OPH32 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH33]),     /* VRM_PID_OPH33 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH34]),     /* VRM_PID_OPH34 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH35]),     /* VRM_PID_OPH35 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH36]),     /* VRM_PID_OPH36 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH37]),     /* VRM_PID_OPH37 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH38]),     /* VRM_PID_OPH38 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH39]),     /* VRM_PID_OPH39 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH40]),     /* VRM_PID_OPH40 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH41]),     /* VRM_PID_OPH41 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH42]),     /* VRM_PID_OPH42 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH43]),     /* VRM_PID_OPH43 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH44]),     /* VRM_PID_OPH44 */
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPH45]),     /* VRM_PID_OPH45 */
    
    (uint8*)(&gIoHwAb_au16PwmOutOld[IOHWAB_PWMO_IRID_OPL01]),     /* VRM_PID_OPL01 */

    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR01]),        /* VRM_PID_OR01 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR02]),        /* VRM_PID_OR02 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR03]),        /* VRM_PID_OR03 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR04]),        /* VRM_PID_OR04 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR05]),        /* VRM_PID_OR05 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR06]),        /* VRM_PID_OR06 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR07]),        /* VRM_PID_OR07 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR08]),        /* VRM_PID_OR08 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR09]),        /* VRM_PID_OR09 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR10]),        /* VRM_PID_OR10 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR11]),        /* VRM_PID_OR11 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR12]),        /* VRM_PID_OR12 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR13]),        /* VRM_PID_OR13 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_OR14]),        /* VRM_PID_OR14 */

    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODH01]),       /* VRM_PID_ODH01 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODH02]),       /* VRM_PID_ODH02 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODH03]),       /* VRM_PID_ODH03 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODH04]),       /* VRM_PID_ODH04 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODH05]),       /* VRM_PID_ODH05 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODH06]),       /* VRM_PID_ODH06 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODH07]),       /* VRM_PID_ODH07 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODH08]),       /* VRM_PID_ODH08 */
    
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL01]),       /* VRM_PID_ODL01 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL02]),       /* VRM_PID_ODL02 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL03]),       /* VRM_PID_ODL03 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL04]),       /* VRM_PID_ODL04 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL05]),       /* VRM_PID_ODL05 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL06]),       /* VRM_PID_ODL06 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL07]),       /* VRM_PID_ODL07 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL08]),       /* VRM_PID_ODL08 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL09]),       /* VRM_PID_ODL09 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL10]),       /* VRM_PID_ODL10 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL11]),       /* VRM_PID_ODL11 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL12]),       /* VRM_PID_ODL12 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL13]),       /* VRM_PID_ODL13 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL14]),       /* VRM_PID_ODL14 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL15]),       /* VRM_PID_ODL15 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL16]),       /* VRM_PID_ODL16 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL17]),       /* VRM_PID_ODL17 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL18]),       /* VRM_PID_ODL18 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL19]),       /* VRM_PID_ODL19 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL20]),       /* VRM_PID_ODL20 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL21]),       /* VRM_PID_ODL21 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL22]),       /* VRM_PID_ODL22 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL23]),       /* VRM_PID_ODL23 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL24]),       /* VRM_PID_ODL24 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL25]),       /* VRM_PID_ODL25 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL26]),       /* VRM_PID_ODL26 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL27]),       /* VRM_PID_ODL27 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL28]),       /* VRM_PID_ODL28 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL29]),       /* VRM_PID_ODL29 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL30]),       /* VRM_PID_ODL30 */
    (uint8*)(&gIoHwAb_abDoSignalOld[IOHWAB_DO_IRID_ODL31])        /* VRM_PID_ODL31 */

};

#endif
//----------------------------------------------------------------------------
/* 
FALSE:  channel be closed ,when  vrm intercept, default
TRUE:   channel be opened ,when  vrm intercept 
*/ 
//----------------------------------------------------------------------------
const boolean VRM_InterceptStateArray[VRM_PID_SIZE] = 
{
    FALSE,    /*DUMMY*/
    FALSE,    /*OPH01*/
    FALSE,    /*OPH02*/
    FALSE,    /*OPH03*/
    FALSE,    /*OPH04*/
    FALSE,    /*OPH05*/
    FALSE,    /*OPH06*/
    FALSE,    /*OPH07*/
    FALSE,    /*OPH08*/
    FALSE,    /*OPH09*/
    FALSE,    /*OPH10*/
   
    FALSE,    /*OPH11*/
    FALSE,    /*OPH12*/
    FALSE,    /*OPH13*/
    FALSE,    /*OPH14*/
    FALSE,    /*OPH15*/
    FALSE,    /*OPH16*/
    FALSE,    /*OPH17*/
    FALSE,    /*OPH18*/
    FALSE,    /*OPH19*/
    FALSE,    /*OPH20*/
  
    FALSE,    /*OPH21*/
    FALSE,    /*OPH22*/
    FALSE,    /*OPH23*/
    FALSE,    /*OPH24*/
    FALSE,    /*OPH25*/
    FALSE,    /*OPH26*/
    FALSE,    /*OPH27*/
    FALSE,    /*OPH28*/
    FALSE,    /*OPH29*/
    FALSE,    /*OPH30*/
  
    FALSE,    /*OPH31*/
    FALSE,    /*OPH32*/
    FALSE,    /*OPH33*/
    FALSE,    /*OPH34*/
    FALSE,    /*OPH35*/
    FALSE,    /*OPH36*/
    FALSE,    /*OPH37*/
    FALSE,    /*OPH38*/
    FALSE,    /*OPH39*/
    FALSE,    /*OPH40*/
  
    FALSE,    /*OPH41*/
    FALSE,    /*OPH42*/
    FALSE,    /*OPH43*/
    FALSE,    /*OPH44*/
    FALSE,    /*OPH45*/
    
    FALSE,    /*OPL01*/
    
    FALSE,    /*OR01*/
    FALSE,    /*OR02*/
    FALSE,    /*OR03*/
    FALSE,    /*OR04*/
    FALSE,    /*OR05*/
    FALSE,    /*OR06*/
    FALSE,    /*OR07*/
    FALSE,    /*OR08*/
    FALSE,    /*OR09*/
    FALSE,    /*OR10*/
    
    FALSE,    /*OR11*/
    FALSE,    /*OR12*/
    FALSE,    /*OR13*/
    FALSE,    /*OR14*/

    FALSE,    /*ODH01*/
    FALSE,    /*ODH02*/
    FALSE,    /*ODH03*/
    FALSE,    /*ODH04*/
    FALSE,    /*ODH05*/
    FALSE,    /*ODH06*/
    FALSE,    /*ODH07*/
    FALSE,    /*ODH08*/

    FALSE,    /*ODL01*/
    FALSE,    /*ODL02*/
    FALSE,    /*ODL03*/
    FALSE,    /*ODL04*/
    FALSE,    /*ODL05*/
    FALSE,    /*ODL06*/
    FALSE,    /*ODL07*/
    FALSE,    /*ODL08*/
    FALSE,    /*ODL09*/
    FALSE,    /*ODL10*/

    FALSE,    /*ODL11*/
    FALSE,    /*ODL12*/
    FALSE,    /*ODL13*/
    FALSE,    /*ODL14*/
    FALSE,    /*ODL15*/
    FALSE,    /*ODL16*/
    FALSE,    /*ODL17*/
    FALSE,    /*ODL18*/
    FALSE,    /*ODL19*/
    FALSE,    /*ODL20*/
    
    FALSE,    /*ODL21*/
    FALSE,    /*ODL22*/
    FALSE,    /*ODL23*/
    FALSE,    /*ODL24*/
    FALSE,    /*ODL25*/
    FALSE,    /*ODL26*/
    FALSE,    /*ODL27*/
    FALSE,    /*ODL28*/
    FALSE,    /*ODL29*/
    FALSE,    /*ODL30*/

    FALSE     /*ODL31*/
};
    
//----------------------------------------------------------------------------
/* 
chose channel intercept type ,VRM_STATE_TYPE_A_1....VRM_STATETYPES_A_n
note: only choose type A
*/ 
//----------------------------------------------------------------------------
const VRM_StateType VRM_InterceptStateTypeArray[VRM_PID_SIZE] =
{
    VRM_STATE_TYPE_NO_MONITOR, 
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH01*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH02*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH03*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH04*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH05*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH06*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH07*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH08*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH09*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH10*/
   
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH11*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH12*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH13*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH14*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH15*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH16*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH17*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH18*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH19*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH20*/
  
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH21*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH22*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH23*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH24*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH25*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH26*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH27*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH28*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH29*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH30*/
  
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH31*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH32*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH33*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH34*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH35*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH36*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH37*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH38*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH39*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH40*/
  
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH41*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH42*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH43*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH44*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OPH45*/
    
    VRM_STATE_TYPE_NO_MONITOR,    /*OPL01*/
    
    VRM_STATE_TYPE_NO_MONITOR,    /*OR01*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR02*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR03*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR04*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR05*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR06*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR07*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR08*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR09*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR10*/
    
    VRM_STATE_TYPE_NO_MONITOR,    /*OR11*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR12*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR13*/
    VRM_STATE_TYPE_NO_MONITOR,    /*OR14*/

    VRM_STATE_TYPE_NO_MONITOR,    /*ODH01*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODH02*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODH03*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODH04*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODH05*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODH06*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODH07*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODH08*/

    VRM_STATE_TYPE_NO_MONITOR,    /*ODL01*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL02*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL03*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL04*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL05*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL06*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL07*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL08*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL09*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL10*/

    VRM_STATE_TYPE_NO_MONITOR,    /*ODL11*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL12*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL13*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL14*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL15*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL16*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL17*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL18*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL19*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL20*/
    
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL21*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL22*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL23*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL24*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL25*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL26*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL27*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL28*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL29*/
    VRM_STATE_TYPE_NO_MONITOR,    /*ODL30*/

    VRM_STATE_TYPE_NO_MONITOR     /*ODL31*/
};


//----------------------------------------------------------------------------
/* flow type_A Parameter */ 
//----------------------------------------------------------------------------
#if (VRM_STATEFLOW_TYPE_A_NUM == 3)
const uint16 VRM_LowThresholdTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_LOW_THRESHOLD_TYPE_A_1,   
    VRM_LOW_THRESHOLD_TYPE_A_2, 
    VRM_LOW_THRESHOLD_TYPE_A_3
};

const uint16 VRM_HighThresholdTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_HIGH_THRESHOLD_TYPE_A_1, 
    VRM_HIGH_THRESHOLD_TYPE_A_2, 
    VRM_HIGH_THRESHOLD_TYPE_A_3
};

const uint16 VRM_LowHystTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_LOW_HYST_TYPE_A_1, 
    VRM_LOW_HYST_TYPE_A_2,      
    VRM_LOW_HYST_TYPE_A_3
};

const uint16 VRM_HighHystTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_HIGH_HYST_TYPE_A_1, 
    VRM_HIGH_HYST_TYPE_A_2,     
    VRM_HIGH_HYST_TYPE_A_3
};

const uint16 VRM_N2LTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_N2LTIME_TYPE_A_1, 
    VRM_N2LTIME_TYPE_A_2,       
    VRM_N2LTIME_TYPE_A_3
};

const uint16 VRM_L2UTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_L2UTIME_TYPE_A_1,  
    VRM_L2UTIME_TYPE_A_2,        
    VRM_L2UTIME_TYPE_A_3
};

const uint16 VRM_L2NTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_L2NTIME_TYPE_A_1,      
    VRM_L2NTIME_TYPE_A_2, 
    VRM_L2NTIME_TYPE_A_3
};

const uint16 VRM_H2OTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_H2OTIME_TYPE_A_1, 
    VRM_H2OTIME_TYPE_A_2, 
    VRM_H2OTIME_TYPE_A_3
};

const uint16 VRM_N2HTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_N2HTIME_TYPE_A_1,
    VRM_N2HTIME_TYPE_A_2,        
    VRM_N2HTIME_TYPE_A_3
};

const uint16 VRM_H2NTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_H2NTIME_TYPE_A_1,
    VRM_H2NTIME_TYPE_A_2,
    VRM_H2NTIME_TYPE_A_3
};

const uint16 VRM_U2NTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_U2NTIME_TYPE_A_1,
    VRM_U2NTIME_TYPE_A_2,        
    VRM_U2NTIME_TYPE_A_3
};

const uint16 VRM_O2NTimeTypeAArray[VRM_STATEFLOW_TYPE_A_NUM] = 
{
    VRM_O2NTIME_TYPE_A_1,
    VRM_O2NTIME_TYPE_A_2,
    VRM_O2NTIME_TYPE_A_3
};
#endif

//----------------------------------------------------------------------------
/* flow type_B Parameter */ 
//---------------------------------------------------------------------------- 
#if (VRM_STATEFLOW_TYPE_B_NUM == 2)
const uint16 VRM_UnderThresholdTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_UNDER_THRESHOLD_TYPE_B_1,   
    VRM_UNDER_THRESHOLD_TYPE_B_2
};

const uint16 VRM_OverThresholdTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_OVER_THRESHOLD_TYPE_B_1, 
    VRM_OVER_THRESHOLD_TYPE_B_2
};

const uint16 VRM_LowHystTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_LOW_HYST_TYPE_B_1,      
    VRM_LOW_HYST_TYPE_B_2
};

const uint16 VRM_HighHystTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_HIGH_HYST_TYPE_B_1,   
    VRM_HIGH_HYST_TYPE_B_2
};

const uint16 VRM_U2NTimeTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_U2NTIME_TYPE_B_1,     
    VRM_U2NTIME_TYPE_B_2
};

const uint16 VRM_O2NTimeTypeBArray[VRM_STATEFLOW_TYPE_B_NUM] = 
{
    VRM_O2NTIME_TYPE_B_1,
    VRM_O2NTIME_TYPE_B_2
};
#endif

//----------------------------------------------------------------------------
/* flow type_C Parameter */ 
//---------------------------------------------------------------------------- 
#if (VRM_STATEFLOW_TYPE_C_NUM == 1)
const uint16 VRM_LowThresholdTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_LOW_THRESHOLD_TYPE_C_1
};

const uint16 VRM_HighThresholdTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{    
    VRM_HIGH_THRESHOLD_TYPE_C_1
};

const uint16 VRM_LowHystTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_LOW_HYST_TYPE_C_1
};

const uint16 VRM_HighHystTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_HIGH_HYST_TYPE_C_1
};

const uint16 VRM_N2LTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_N2LTIME_TYPE_C_1
};

const uint16 VRM_L2UTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{   
    VRM_L2UTIME_TYPE_C_1
};

const uint16 VRM_L2NTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_L2NTIME_TYPE_C_1
};

const uint16 VRM_H2OTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_H2OTIME_TYPE_C_1
};

const uint16 VRM_N2HTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_N2HTIME_TYPE_C_1
};

const uint16 VRM_H2NTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_H2NTIME_TYPE_C_1
};

const uint16 VRM_U2NTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_U2NTIME_TYPE_C_1
};

const uint16 VRM_O2NTimeTypeCArray[VRM_STATEFLOW_TYPE_C_NUM] = 
{
    VRM_O2NTIME_TYPE_C_1
};
#endif

//----------------------------------------------------------------------------
/* flow type_D DTC  Parameter */ 
//---------------------------------------------------------------------------- 
#if (VRM_DTC_TYPE_D_NUM == 3)
const uint16 VRM_LowThresholdTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_LOW_THRESHOLD_DTC_TYPE1,  
    VRM_LOW_THRESHOLD_DTC_TYPE2,  
    VRM_LOW_THRESHOLD_DTC_TYPE3
};

const uint16 VRM_HighThresholdTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_HIGH_THRESHOLD_DTC_TYPE1, 
    VRM_HIGH_THRESHOLD_DTC_TYPE2, 
    VRM_HIGH_THRESHOLD_DTC_TYPE3
};

const uint16 VRM_LowHystTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_LOW_HYST_DTC_TYPE1, 
    VRM_LOW_HYST_DTC_TYPE2,       
    VRM_LOW_HYST_DTC_TYPE3
};
const uint16 VRM_HighHystTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_HIGH_HYST_DTC_TYPE1, 
    VRM_HIGH_HYST_DTC_TYPE2,     
    VRM_HIGH_HYST_DTC_TYPE3
};

const uint16 VRM_N2LTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_N2LTIME_DTC_TYPE1, 
    VRM_N2LTIME_DTC_TYPE2,       
    VRM_N2LTIME_DTC_TYPE3
};

const uint16 VRM_L2UTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_L2UTIME_DTC_TYPE1,  
    VRM_L2UTIME_DTC_TYPE2,        
    VRM_L2UTIME_DTC_TYPE3
};

const uint16 VRM_L2NTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_L2NTIME_DTC_TYPE1,      
    VRM_L2NTIME_DTC_TYPE2, 
    VRM_L2NTIME_DTC_TYPE3
};

const uint16 VRM_H2OTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_H2OTIME_DTC_TYPE1, 
    VRM_H2OTIME_DTC_TYPE2, 
    VRM_H2OTIME_DTC_TYPE3
};

const uint16 VRM_N2HTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_N2HTIME_DTC_TYPE1,
    VRM_N2HTIME_DTC_TYPE2,        
    VRM_N2HTIME_DTC_TYPE3
};

const uint16 VRM_H2NTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_H2NTIME_DTC_TYPE1,
    VRM_H2NTIME_DTC_TYPE2,
    VRM_H2NTIME_DTC_TYPE3
};

const uint16 VRM_U2NTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_U2NTIME_DTC_TYPE1,
    VRM_U2NTIME_DTC_TYPE2,        
    VRM_U2NTIME_DTC_TYPE3
};

const uint16 VRM_O2NTimeTypeDArray[VRM_DTC_TYPE_D_NUM] = 
{
    VRM_O2NTIME_DTC_TYPE1,
    VRM_O2NTIME_DTC_TYPE2,
    VRM_O2NTIME_DTC_TYPE3
};
#endif

