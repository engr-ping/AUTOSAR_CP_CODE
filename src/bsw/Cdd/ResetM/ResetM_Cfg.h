#ifndef _RESETM_CFG_H_
#define _RESETM_CFG_H_


typedef void (*ResetM_FuncType)(void);

typedef struct 
{
  ResetM_FuncType Function;
  uint8 ResetType;
}ResetM_CfgType;



#endif /*_RESETM_CFG_H_*/