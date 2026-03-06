#include "DioIf_Cfg.h"

DioIf_ReadChannelCfgType gDioIf_aReadChannelCfg[DIOIF_DI_CHANNEL_MAX] =
{
    {DioIf_ReadChannelFunc_Ch0, DIOIF_CHANNEL_0},
    {DioIf_ReadChannelFunc_Ch1, DIOIF_CHANNEL_1},
    {DioIf_ReadChannelFunc_Ch2, DIOIF_CHANNEL_2},
};

DioIf_WriteChannelCfgType gDioIf_aWriteChannelCfg[DIOIF_DO_CHANNEL_MAX] =
{
    {DioIf_WriteChannelFunc_Ch0, DIOIF_CHANNEL_0},
    {DioIf_WriteChannelFunc_Ch1, DIOIF_CHANNEL_1},
    {DioIf_WriteChannelFunc_Ch2, DIOIF_CHANNEL_2},
};