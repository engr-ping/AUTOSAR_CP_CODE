

#ifndef _ADCIF_TYPES_H_
#define _ADCIF_TYPES_H_
#include "Std_Types.h"

typedef uint16 (*AdcIf_ConvFuncType)(uint16);

typedef struct
{
    AdcIf_ConvFuncType ConvFunc;
    uint16 AdcChnId;
}AdcIf_ConvCfgType;
  

#endif /* _ADCIF_TYPES_H_ */