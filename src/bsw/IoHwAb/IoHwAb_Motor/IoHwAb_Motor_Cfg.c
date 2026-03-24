#include "Motor_Channel_Cfg.h"

#define MOTOR_CHANNEL_MAX    4u

/* 电机通道配置表 */
Motor_ChannelConfigType Motor_ChannelConfig[MOTOR_CHANNEL_MAX] = {
    /* ========== 通道0：有刷直流电机-双向（1个H桥 = 2个半桥） ========== */
    {
        .channelId = 0,
        .motorType = MOTOR_TYPE_DC_BRUSHED_BI,
        
        /* PWM映射：1个PWM通道控制速度 */
        .pwmMapping = {
            .pwmChannelCount = 1,
            .pwmChannelIds = {0, 0, 0, 0, 0, 0},
            .minDutyPercent = {0, 0, 0, 0, 0, 0},
            .maxDutyPercent = {100, 0, 0, 0, 0, 0}
        },
        
        /* 半桥映射：2个半桥组成H桥 */
        .hboMapping = {
            .hboChannelCount = 2,
            .hboChannelIds = {0, 1, 0, 0},      /* 半桥通道0和1 */
            .directionMapping = {0, 1, 0, 0}     /* 半桥0控制正向，半桥1控制反向 */
        },
        
        .minSpeed = 0,
        .maxSpeed = 1000,
        .currentSpeed = 0,
        .currentDirection = HBIF_DIR_FREE,
        .enableState = 1,
        .faultState = 0
    },
    
    /* ========== 通道1：无刷直流电机（3个半桥） ========== */
    {
        .channelId = 1,
        .motorType = MOTOR_TYPE_DC_BRUSHLESS,
        
        /* PWM映射：3个PWM通道控制三相 */
        .pwmMapping = {
            .pwmChannelCount = 3,
            .pwmChannelIds = {2, 3, 4, 0, 0, 0},   /* PWM通道2,3,4 */
            .minDutyPercent = {10, 10, 10, 0, 0, 0},
            .maxDutyPercent = {90, 90, 90, 0, 0, 0}
        },
        
        /* 半桥映射：3个半桥组成三相逆变桥 */
        .hboMapping = {
            .hboChannelCount = 3,
            .hboChannelIds = {2, 3, 4, 0},         /* 半桥通道2,3,4 */
            .directionMapping = {0, 1, 2, 0}        /* 分别对应U,V,W相 */
        },
        
        .minSpeed = 100,
        .maxSpeed = 900,
        .currentSpeed = 0,
        .currentDirection = HBIF_DIR_FREE,
        .enableState = 1,
        .faultState = 0
    },
    
    /* ========== 通道2：步进电机（2个H桥 = 4个半桥） ========== */
    {
        .channelId = 2,
        .motorType = MOTOR_TYPE_STEPPER,
        
        /* PWM映射：4个PWM通道控制步进时序 */
        .pwmMapping = {
            .pwmChannelCount = 4,
            .pwmChannelIds = {5, 6, 7, 8, 0, 0},    /* PWM通道5,6,7,8 */
            .minDutyPercent = {0, 0, 0, 0, 0, 0},
            .maxDutyPercent = {100, 100, 100, 100, 0, 0}
        },
        
        /* 半桥映射：4个半桥组成两个H桥 */
        .hboMapping = {
            .hboChannelCount = 4,
            .hboChannelIds = {5, 6, 7, 8},          /* 半桥通道5,6,7,8 */
            .directionMapping = {0, 1, 2, 3}         /* 分别对应A+,A-,B+,B-相 */
        },
        
        .minSpeed = 0,
        .maxSpeed = 1000,
        .currentSpeed = 0,
        .currentDirection = HBIF_DIR_FREE,
        .enableState = 1,
        .faultState = 0
    },
    
    /* ========== 通道3：有刷直流电机-单向（1个半桥） ========== */
    {
        .channelId = 3,
        .motorType = MOTOR_TYPE_DC_BRUSHED_SINGLE,
        
        /* PWM映射：1个PWM通道控制速度 */
        .pwmMapping = {
            .pwmChannelCount = 1,
            .pwmChannelIds = {9, 0, 0, 0, 0, 0},
            .minDutyPercent = {0, 0, 0, 0, 0, 0},
            .maxDutyPercent = {100, 0, 0, 0, 0, 0}
        },
        
        /* 半桥映射：1个半桥控制方向 */
        .hboMapping = {
            .hboChannelCount = 1,
            .hboChannelIds = {9, 0, 0, 0},          /* 半桥通道9 */
            .directionMapping = {0, 0, 0, 0}
        },
        
        .minSpeed = 0,
        .maxSpeed = 1000,
        .currentSpeed = 0,
        .currentDirection = HBIF_DIR_FREE,
        .enableState = 1,
        .faultState = 0
    }
};