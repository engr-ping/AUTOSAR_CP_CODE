#ifndef MOTOR_CHANNEL_CFG_H
#define MOTOR_CHANNEL_CFG_H

#include "Std_Types.h"
#include "HbIf.h"

/* 电机类型枚举 */
typedef enum {
    MOTOR_TYPE_DC_BRUSHED_SINGLE = 0,   /* 有刷直流-单向（1个半桥） */
    MOTOR_TYPE_DC_BRUSHED_BI = 1,       /* 有刷直流-双向（1个H桥=2个半桥） */
    MOTOR_TYPE_DC_BRUSHLESS = 2,        /* 无刷直流（3个半桥） */
    MOTOR_TYPE_STEPPER = 3,             /* 步进电机（2个H桥=4个半桥） */
    MOTOR_TYPE_PMSM = 4                 /* 永磁同步电机（3个半桥） */
} Motor_Type;

/* PWM映射配置（每个电机通道关联的PWM通道） */
typedef struct {
    uint8_t pwmChannelCount;            /* PWM通道数量（1-6） */
    uint8_t pwmChannelIds[6];           /* PWM通道ID数组 */
    uint16_t minDutyPercent[6];         /* 各通道最小占空比 */
    uint16_t maxDutyPercent[6];         /* 各通道最大占空比 */
} Motor_PwmMappingType;

/* 半桥映射配置（每个电机通道关联的半桥通道） */
typedef struct {
    uint8_t hboChannelCount;            /* 半桥通道数量（1-4） */
    uint8_t hboChannelIds[4];           /* 半桥通道ID数组（最多4个） */
    uint8_t directionMapping[4];        /* 方向映射关系（哪个半桥控制哪个方向） */
} Motor_HbMappingType;

/* 电机通道配置结构体 */
typedef struct {
    uint16_t channelId;                  /* 逻辑通道ID (0-3) */
    Motor_Type motorType;               /* 电机类型 */
    
    /* PWM映射 */
    Motor_PwmMappingType pwmMapping;
    
    /* 半桥映射 */
    Motor_HbMappingType hboMapping;
    
    /* 速度范围配置 */
    uint16_t minSpeed;                  /* 最小速度（0-1000） */
    uint16_t maxSpeed;                  /* 最大速度（0-1000） */
    
    /* 运行状态（运行时更新） */
    uint16_t currentSpeed;              /* 当前速度 */
    uint8_t currentDirection;           /* 当前方向 */
    uint8_t enableState;                /* 使能状态 */
    uint8_t faultState;                 /* 故障状态 */
} Motor_ChannelConfigType;

/* 外部声明配置表 */
extern Motor_ChannelConfigType Motor_ChannelConfig[MOTOR_CHANNEL_MAX];

#endif /* MOTOR_CHANNEL_CFG_H */