
#include "AdcIf.h"
#include "AdcIf_Cfg.h"


uint16 AdcIf_ReadChannel(uint16 ChannelId)
{
    uint16 u16AdcVal = 0u;

    if(ChannelId < ADCIF_CHANNEL_MAX)
    {
      AdcIf_ConvCfgType* pConvCfg = &gAdcIf_atConvCfg[ChannelId];
        /* Call the conversion function to get the converted value */
        u16AdcVal = pConvCfg->ConvFunc(pConvCfg->AdcChnId);
    }
    else
    {
        /* Invalid ChannelId, return 0 or handle error as needed */
        u16AdcVal = 0u;
    }

    return u16AdcVal;
}