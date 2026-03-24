#ifndef _DIOIF_H_
#define _DIOIF_H_

#include "DioIf_Types.h"

extern boolean DioIf_ReadChannel(uint16 ChannelId);
extern Std_ReturnType DioIf_WriteChannel(uint16 ChannelId, boolean Value);

#endif /* _DIOIF_H_ */ 