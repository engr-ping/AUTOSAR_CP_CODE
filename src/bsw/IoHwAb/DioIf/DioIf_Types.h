

#ifndef _DIOIF_TYPES_H_
#define _DIOIF_TYPES_H_
#include "Std_Types.h"

typedef boolean (*DioIf_ReadChannelFuncType)(uint16);
typedef Std_ReturnType (*DioIf_WriteChannelFuncType)(uint16, boolean);

typedef struct
{
    DioIf_ReadChannelFuncType ReadChannelFunc;
    uint16 DioChnId;
}DioIf_ReadChannelCfgType;
  

typedef struct
{
    DioIf_WriteChannelFuncType WriteChannelFunc;
    uint16 DioChnId;
}DioIf_WriteChannelCfgType;


#endif /* _DIOIF_TYPES_H_ */