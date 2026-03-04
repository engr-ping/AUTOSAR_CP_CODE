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
#include "Platform_Types.h"
#include "VRM_PupCtrl.h"

/* Macros Local To This Module                                          */
/* ===========================                                          */

/* Local Module RAM-Definitions (attribute static)                      */
/* ===========================================                          */
/* Definition of variables only local to this module. That is, not to   */
/* be exported to other modules.                                        */
static uint8 VRM_PowerLockStatus = 0;
static uint8 VRM_Pup1LockStatus = 0;
static uint8 VRM_Pup2LockStatus = 0;
static uint8 VRM_Pup3LockStatus = 0;



/* Exported Variables Definitions                                       */
/* ============================================================         */



/************************************************************************/
/*                 Global Definitions                                   */
/************************************************************************/


/*****************    Local Functions Declaration    ******************/


/****************************************************************
 process: VRM_vPutAndKeepVcc1Sw
 purpose: set Vcc1_SW in EOL mode 
 ****************************************************************/
void VRM_SetAndKeepPowerOutput(uint8 PowerState)
{
    VRM_PowerLockStatus = TRUE;

    if(PowerState != (boolean)FALSE)
    {
        VRM_SET_V_POWER;
    }
    else
    {
        VRM_CLR_V_POWER;
    }
}

/****************************************************************
 process: VRM_SetAndKeepPup1Output
 purpose: set PUP1 in EOL mode 
 ****************************************************************/
void VRM_SetAndKeepPup1Output(uint8 PowerState)
{

    VRM_Pup1LockStatus = TRUE;

    if(PowerState != (boolean)FALSE)
    {
        VRM_SET_V_PUP1;
    }
    else
    {
        VRM_CLR_V_PUP1;
    }
}

/****************************************************************
 process: VRM_SetAndKeepPup2Output
 purpose: set PUP2 in EOL mode 
 ****************************************************************/
void VRM_SetAndKeepPup2Output(uint8 PowerState)
{
    VRM_Pup2LockStatus = TRUE;

    if(PowerState != (boolean)FALSE)
    {
        VRM_SET_V_PUP2;
    }
    else
    {
        VRM_CLR_V_PUP2;
    }
}

/****************************************************************
 process: VRM_SetAndKeepPup3Output
 purpose: set PUP3 in EOL mode 
 ****************************************************************/
void VRM_SetAndKeepPup3Output(uint8 PowerState)
{
    VRM_Pup3LockStatus = TRUE;

    if(PowerState != (boolean)FALSE)
    {
        VRM_SET_V_PUP3;
    }
    else
    {
        VRM_CLR_V_PUP3;
    }
}


/****************************************************************
 process: VRM_SetPowerOutput
 purpose: set Power in normal mode 
 ****************************************************************/
void VRM_SetPowerOutput(uint8 PowerState)
{
    if(VRM_PowerLockStatus == (boolean)FALSE)
    {
        if(PowerState != (boolean)FALSE)
        {
            VRM_SET_V_POWER;
        }
        else
        {
            VRM_CLR_V_POWER;
        }
    }
}


/****************************************************************
 process: VRM_SetPup1Output
 purpose: set PUP1 in normal mode 
 ****************************************************************/
void VRM_SetPup1Output(uint8 PowerState)
{
	
    if(VRM_Pup1LockStatus == (boolean)FALSE)
    {
        if(PowerState != (boolean)FALSE)
        {
            VRM_SET_V_PUP1;
        }
        else
        {
            VRM_CLR_V_PUP1;
        }
    }
}


/****************************************************************
 process: VRM_SetPup2Output
 purpose: set PUP2 in normal mode 
 ****************************************************************/
void VRM_SetPup2Output(uint8 PowerState)
{
    if( VRM_Pup2LockStatus == (boolean)FALSE)
    {
        if(PowerState != (boolean)FALSE)
        {
            VRM_SET_V_PUP2;
        }
        else
        {
            VRM_CLR_V_PUP2;
        }
    }
}


/****************************************************************
 process: VRM_SetPup3Output
 purpose: set PUP3 in normal mode 
 ****************************************************************/
void VRM_SetPup3Output(uint8 PowerState)
{
    if(VRM_Pup3LockStatus == (boolean)FALSE)
    {
        if(PowerState != (boolean)FALSE)
        {
            VRM_SET_V_PUP3;
        }
        else
        {
            VRM_CLR_V_PUP3;
        }
    }
}


/****************************************************************
 process: VRM_vReleaseVcc1Sw
 purpose: release Vcc1_SW diag control 
 ****************************************************************/
void VRM_ReleasePowerOutput(void)
{
    VRM_PowerLockStatus = FALSE;
}

/****************************************************************
 process: VRM_ReleasePup1Output
 purpose: release PUP1 diag control 
 ****************************************************************/
void VRM_ReleasePup1Output(void)
{
    VRM_Pup1LockStatus = FALSE;
}

/****************************************************************
 process: VRM_ReleasePup2Output
 purpose: release PUP2 diag control 
 ****************************************************************/
void VRM_ReleasePup2Output(void)
{
    VRM_Pup2LockStatus = FALSE;
}

/****************************************************************
 process: VRM_ReleasePup3Output
 purpose: release PUP3 diag control 
 ****************************************************************/
void VRM_ReleasePup3Output(void)
{
    VRM_Pup3LockStatus = FALSE;
}

