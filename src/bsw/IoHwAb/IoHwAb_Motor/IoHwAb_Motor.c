#include "MotorDriver.h"
#include "Motor_Channel_Cfg.h"
#include "PwmIf.h"
#include "HbIf.h"

/* 获取通道配置 */
static Motor_ChannelConfigType* Motor_GetConfig(uint16_t channelId)
{
    uint8_t i;
    
    for (i = 0; i < MOTOR_CHANNEL_MAX; i++) {
        if (Motor_ChannelConfig[i].channelId == channelId) {
            return &Motor_ChannelConfig[i];
        }
    }
    return NULL;
}

/* 将速度（0-1000）转换为占空比百分比（0-100） */
static uint16_t Motor_SpeedToDutyPercent(uint16_t speed, 
                                          uint16_t minSpeed, 
                                          uint16_t maxSpeed)
{
    uint16_t dutyPercent;
    
    /* 速度限幅 */
    if (speed > maxSpeed) {
        speed = maxSpeed;
    }
    if (speed < minSpeed) {
        speed = minSpeed;
    }
    
    /* 线性转换：minSpeed-maxSpeed -> 0-100 */
    if (maxSpeed > minSpeed) {
        dutyPercent = ((speed - minSpeed) * 100) / (maxSpeed - minSpeed);
    } else {
        dutyPercent = 0;
    }
    
    return dutyPercent;
}

/* ========== 有刷直流-单向电机控制（1个半桥） ========== */
static Std_ReturnType Motor_SetBrushedSingle(Motor_ChannelConfigType* config,
                                              uint16_t speed,
                                              uint8_t direction)
{
    uint16_t dutyPercent;
    uint8_t i;
    Std_ReturnType ret = E_OK;
    
    /* 速度转占空比 */
    dutyPercent = Motor_SpeedToDutyPercent(speed, config->minSpeed, config->maxSpeed);
    
    /* 1. 设置半桥方向（1个半桥） */
    if (speed > 0) {
        /* 有速度时才使能半桥 */
        for (i = 0; i < config->hboMapping.hboChannelCount; i++) {
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[i], 
                                       (direction == 0) ? HBIF_DIR_FORWARD : HBIF_DIR_FORWARD);
        }
    } else {
        /* 速度为0时，所有半桥自由停止 */
        for (i = 0; i < config->hboMapping.hboChannelCount; i++) {
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[i], HBIF_DIR_FREE);
        }
    }
    
    /* 2. 设置PWM占空比 */
    if (speed == 0) {
        for (i = 0; i < config->pwmMapping.pwmChannelCount; i++) {
            ret |= PwmIf_Disable(config->pwmMapping.pwmChannelIds[i]);
        }
    } else {
        for (i = 0; i < config->pwmMapping.pwmChannelCount; i++) {
            ret |= PwmIf_SetDuty(config->pwmMapping.pwmChannelIds[i], dutyPercent);
            ret |= PwmIf_Enable(config->pwmMapping.pwmChannelIds[i]);
        }
    }
    
    return ret;
}

/* ========== 有刷直流-双向电机控制（2个半桥组成H桥） ========== */
static Std_ReturnType Motor_SetBrushedBi(Motor_ChannelConfigType* config,
                                          uint16_t speed,
                                          uint8_t direction)
{
    uint16_t dutyPercent;
    uint8_t i;
    Std_ReturnType ret = E_OK;
    
    /* 速度转占空比 */
    dutyPercent = Motor_SpeedToDutyPercent(speed, config->minSpeed, config->maxSpeed);
    
    /* 1. 设置H桥方向（2个半桥） */
    if (speed > 0) {
        /* 根据方向设置两个半桥的状态 */
        if (direction == HBIF_DIR_FORWARD) {
            /* 正向：半桥0导通，半桥1关断 */
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[0], HBIF_DIR_FORWARD);
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[1], HBIF_DIR_FREE);
        } else if (direction == HBIF_DIR_REVERSE) {
            /* 反向：半桥0关断，半桥1导通 */
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[0], HBIF_DIR_FREE);
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[1], HBIF_DIR_FORWARD);
        } else if (direction == HBIF_DIR_BRAKE) {
            /* 刹车：两个半桥都刹车 */
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[0], HBIF_DIR_BRAKE);
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[1], HBIF_DIR_BRAKE);
        }
    } else {
        /* 速度为0时，所有半桥自由停止 */
        for (i = 0; i < config->hboMapping.hboChannelCount; i++) {
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[i], HBIF_DIR_FREE);
        }
    }
    
    /* 2. 设置PWM占空比（通常只用一个PWM控制H桥总速度） */
    if (speed == 0) {
        for (i = 0; i < config->pwmMapping.pwmChannelCount; i++) {
            ret |= PwmIf_Disable(config->pwmMapping.pwmChannelIds[i]);
        }
    } else {
        for (i = 0; i < config->pwmMapping.pwmChannelCount; i++) {
            ret |= PwmIf_SetDuty(config->pwmMapping.pwmChannelIds[i], dutyPercent);
            ret |= PwmIf_Enable(config->pwmMapping.pwmChannelIds[i]);
        }
    }
    
    return ret;
}

/* ========== 无刷直流电机控制（3个半桥） ========== */
static Std_ReturnType Motor_SetBrushlessDC(Motor_ChannelConfigType* config,
                                            uint16_t speed,
                                            uint8_t direction)
{
    uint16_t dutyPercent;
    uint8_t i;
    Std_ReturnType ret = E_OK;
    
    /* 速度转占空比 */
    dutyPercent = Motor_SpeedToDutyPercent(speed, config->minSpeed, config->maxSpeed);
    
    /* 1. 设置三相半桥方向（实际需要根据霍尔传感器进行换相） */
    /* 这里简化处理：正向时顺序导通，反向时逆序导通 */
    if (speed > 0) {
        if (direction == HBIF_DIR_FORWARD) {
            /* 正向换相逻辑（简化：全部设置为正向） */
            for (i = 0; i < config->hboMapping.hboChannelCount; i++) {
                ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[i], HBIF_DIR_FORWARD);
            }
        } else {
            /* 反向换相逻辑 */
            for (i = 0; i < config->hboMapping.hboChannelCount; i++) {
                ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[i], HBIF_DIR_REVERSE);
            }
        }
    } else {
        /* 速度为0时，所有半桥自由停止 */
        for (i = 0; i < config->hboMapping.hboChannelCount; i++) {
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[i], HBIF_DIR_FREE);
        }
    }
    
    /* 2. 设置三相PWM占空比 */
    if (speed == 0) {
        for (i = 0; i < config->pwmMapping.pwmChannelCount; i++) {
            ret |= PwmIf_Disable(config->pwmMapping.pwmChannelIds[i]);
        }
    } else {
        for (i = 0; i < config->pwmMapping.pwmChannelCount; i++) {
            ret |= PwmIf_SetDuty(config->pwmMapping.pwmChannelIds[i], dutyPercent);
            ret |= PwmIf_Enable(config->pwmMapping.pwmChannelIds[i]);
        }
    }
    
    return ret;
}

/* ========== 步进电机控制（4个半桥 = 2个H桥） ========== */
static Std_ReturnType Motor_SetStepper(Motor_ChannelConfigType* config,
                                        uint16_t speed,
                                        uint8_t direction)
{
    uint16_t dutyPercent;
    uint8_t i;
    Std_ReturnType ret = E_OK;
    
    /* 步进电机的速度控制通常通过步进频率实现，这里简化处理 */
    dutyPercent = Motor_SpeedToDutyPercent(speed, config->minSpeed, config->maxSpeed);
    
    /* 1. 设置步进电机方向（4个半桥组合成步进序列） */
    /* 这里简化：正向时按顺序导通A+->A->B+->B-，反向时逆序 */
    if (speed > 0) {
        /* 简化：正向时全部正向，反向时全部反向 */
        uint8_t stepDirection = (direction == HBIF_DIR_FORWARD) ? HBIF_DIR_FORWARD : HBIF_DIR_REVERSE;
        for (i = 0; i < config->hboMapping.hboChannelCount; i++) {
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[i], stepDirection);
        }
    } else {
        /* 速度为0时，所有半桥自由停止 */
        for (i = 0; i < config->hboMapping.hboChannelCount; i++) {
            ret |= HbIf_SetDirection(config->hboMapping.hboChannelIds[i], HBIF_DIR_FREE);
        }
    }
    
    /* 2. 设置PWM占空比（步进电机可能需要多路PWM） */
    if (speed == 0) {
        for (i = 0; i < config->pwmMapping.pwmChannelCount; i++) {
            ret |= PwmIf_Disable(config->pwmMapping.pwmChannelIds[i]);
        }
    } else {
        for (i = 0; i < config->pwmMapping.pwmChannelCount; i++) {
            ret |= PwmIf_SetDuty(config->pwmMapping.pwmChannelIds[i], dutyPercent);
            ret |= PwmIf_Enable(config->pwmMapping.pwmChannelIds[i]);
        }
    }
    
    return ret;
}

/* ========== 永磁同步电机控制（3个半桥） ========== */
static Std_ReturnType Motor_SetPMSM(Motor_ChannelConfigType* config,
                                     uint16_t speed,
                                     uint8_t direction)
{
    /* PMSM控制与无刷直流类似，但需要更复杂的FOC算法 */
    /* 这里复用无刷电机控制 */
    return Motor_SetBrushlessDC(config, speed, direction);
}

/* ========== 统一的电机控制接口 ========== */
Std_ReturnType Motor_WriteChannel(uint16_t channelId,uint16_t speed,uint8_t direction)
{
    Motor_ChannelConfigType* config;
    Std_ReturnType ret = E_NOT_OK;
    
    /* 参数检查 */
    if (direction > HBIF_DIR_FREE) {
        return E_NOT_OK;
    }
    
    /* 获取配置 */
    config = Motor_GetConfig(channelId);
    if (config == NULL) {
        return E_NOT_OK;
    }
    
    /* 检查使能状态 */
    if (config->enableState == 0) {
        return E_NOT_OK;
    }
    
    /* 根据电机类型调用相应控制函数 */
    switch (config->motorType) {
        case MOTOR_TYPE_DC_BRUSHED_SINGLE:
            ret = Motor_SetBrushedSingle(config, speed, direction);
            break;
            
        case MOTOR_TYPE_DC_BRUSHED_BI:
            ret = Motor_SetBrushedBi(config, speed, direction);
            break;
            
        case MOTOR_TYPE_DC_BRUSHLESS:
            ret = Motor_SetBrushlessDC(config, speed, direction);
            break;
            
        case MOTOR_TYPE_STEPPER:
            ret = Motor_SetStepper(config, speed, direction);
            break;
            
        case MOTOR_TYPE_PMSM:
            ret = Motor_SetPMSM(config, speed, direction);
            break;
            
        default:
            ret = E_NOT_OK;
            break;
    }
    
    /* 更新状态 */
    if (ret == E_OK) {
        config->currentSpeed = speed;
        config->currentDirection = direction;
    }
    
    return ret;
}

/* 初始化电机驱动 */
void Motor_Init(void)
{
    uint8_t i;
    
    /* 初始化PWM接口层 */
    PwmIf_Init();
    
    /* 初始化半桥接口层 */
    HbIf_Init();
    
    /* 初始化电机通道状态 */
    for (i = 0; i < MOTOR_CHANNEL_MAX; i++) {
        Motor_ChannelConfig[i].currentSpeed = 0;
        Motor_ChannelConfig[i].currentDirection = HBIF_DIR_FREE;
        Motor_ChannelConfig[i].enableState = 1;
        Motor_ChannelConfig[i].faultState = 0;
    }
}