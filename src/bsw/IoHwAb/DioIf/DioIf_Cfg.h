#ifndef _DIOIF_CFG_H_
#define _DIOIF_CFG_H_

#include "DioIf_Types.h"

#define DIOIF_DI_CHANNEL_MAX 3u
#define DIOIF_DO_CHANNEL_MAX 3u

/* Digital Input Channel IDs */
#define DIO_CHN_IDL01 0u
#define DIO_CHN_IDL02 1u
#define DIO_CHN_IDL03 2u
#define DIO_CHN_IDL04 3u
#define DIO_CHN_IDL05 4u
#define DIO_CHN_IDL06 5u
#define DIO_CHN_IDL07 6u
#define DIO_CHN_IDL08 7u
#define DIO_CHN_IDL09 8u
#define DIO_CHN_IDL10 9u
#define DIO_CHN_IDL11 10u
#define DIO_CHN_IDL12 11u
#define DIO_CHN_IDL13 12u
#define DIO_CHN_IDL14 13u
#define DIO_CHN_IDL15 14u
#define DIO_CHN_IDL16 15u
#define DIO_CHN_IDL17 16u

extern DioIf_ReadChannelCfgType DioIf_ReadChannelCfg[DIOIF_DI_CHANNEL_MAX];
extern DioIf_WriteChannelCfgType DioIf_WriteChannelCfg[DIOIF_DO_CHANNEL_MAX];

#endif /* _DIOIF_CFG_H_ */
