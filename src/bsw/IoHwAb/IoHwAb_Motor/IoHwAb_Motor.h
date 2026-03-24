#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "Std_Types.h"

/* 初始化电机驱动 */
extern void Motor_Init(void);

/* 统一电机控制接口 */
extern Std_ReturnType Motor_WriteChannel(uint16_t channelId,uint16_t speed,uint8_t direction);

/* 获取电机状态 */
extern uint8_t Motor_GetStatus(uint16_t channelId);

#endif /* MOTOR_DRIVER_H */