#ifndef _DIOIF_CFG_H_
#define _DIOIF_CFG_H_

#include "DioIf_Types.h"

#define DIOIF_DI_CHANNEL_MAX 3u
#define DIOIF_DO_CHANNEL_MAX 3u

extern DioIf_ReadChannelCfgType DioIf_ReadChannelCfg[DIOIF_DI_CHANNEL_MAX];
extern DioIf_WriteChannelCfgType DioIf_WriteChannelCfg[DIOIF_DO_CHANNEL_MAX];

#endif /* _DIOIF_CFG_H_ */