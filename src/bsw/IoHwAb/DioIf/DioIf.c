
#include "DioIf.h"
#include "DioIf_Cfg.h"


boolean DioIf_ReadChannel(uint16 ChannelId)
{
    boolean DioVal = FALSE;

    if(ChannelId < DIOIF_DI_CHANNEL_MAX)
    {
      DioIf_ReadChannelCfgType* pConvCfg = &DioIf_ReadChannelCfg[ChannelId];
        /* Call the conversion function to get the converted value */
        DioVal = pConvCfg->ReadChannelFunc(pConvCfg->DioChnId);
    }
    else
    {
        /* Invalid ChannelId, return FALSE or handle error as needed */
        DioVal = FALSE;
    }

    return DioVal;
}


Std_ReturnType DioIf_WriteChannel(uint16 ChannelId, boolean Value)
{
    Std_ReturnType returnValue = E_OK;

    if(ChannelId < DIOIF_DO_CHANNEL_MAX)
    {
      DioIf_WriteChannelCfgType* pConvCfg = &DioIf_WriteChannelCfg[ChannelId];
        /* Call the conversion function to set the value */
        returnValue = pConvCfg->WriteChannelFunc(pConvCfg->DioChnId, Value);
    }
    else
    {
        /* Invalid ChannelId, return error code */
        returnValue = E_NOT_OK;
    }

    return returnValue;
}