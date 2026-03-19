#include "AdcIf_Cfg.h"

extern uint16 Adc_ReadChannel(uint16 ChannelId);


AdcIf_ConvCfgType gAdcIf_atConvCfg[ADCIF_CHANNEL_MAX] =
{
    {Adc_ReadChannel, 0},
    {Adc_ReadChannel, 1},
    {Adc_ReadChannel, 2},
};