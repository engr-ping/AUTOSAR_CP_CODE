#include "DioIf_Cfg.h"

extern uint8 Dio_ReadChannel(const uint8 ChannelId);
extern void Dio_WriteChannel(const uint8 ChannelId, uint8 Level);
DioIf_ReadChannelCfgType DioIf_ReadChannelCfg[DIOIF_DI_CHANNEL_MAX] =
{
    {Dio_ReadChannel, 0},
    {Dio_ReadChannel, 1},
    {Dio_ReadChannel, 2},
};

DioIf_WriteChannelCfgType DioIf_WriteChannelCfg[DIOIF_DO_CHANNEL_MAX] =
{
    {Dio_WriteChannel, 3},
    {Dio_WriteChannel, 4},
    {Dio_WriteChannel, 5},
};