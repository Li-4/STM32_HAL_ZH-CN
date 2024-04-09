/**
 *******************************************************************************
 * @file    stm32f1xx_hal.h
 * @author  (翻译作者)github.com/Li-4 注：目前只包含我使用的代码
 * @brief   这个文件包含 HAL 模块驱动程序的所有功能原型
 *******************************************************************************
*/

/* 防止递归包含的定义 ----------------------------------------------------------*/
#ifndef __STM32F1xx_HAL_H
#define __STM32F1xx_HAL_H

/* 包含 -----------------------------------------------------------------------*/
#include "stm32f1xx_hal_conf.h"

/* 导出常量 -------------------------------------------------------------------*/

/**
 * @brief HAL_TICK_FREQ $感觉是默认情况下的系统嘀嗒定时器分频因子（默认 SysTick 1MHz）
*/
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;

#define IS_TICKFREQ(FREQ)  (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                            ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                            ((FREQ) == HAL_TICK_FREQ_1KHZ))

/* 导出类型 -------------------------------------------------------------------*/
extern __IO uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;


// 省略 DEBUG 模式宏定义，暂时不用


/* 初始化 和 反初始化函数 ***********************************************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);


/* 外设控制函数 ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);
void HAL_DBGMCU_EnableDBGSleepMode(void);
void HAL_DBGMCU_DisableDBGSleepMode(void);
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);


#endif /* __STM32F1xx_HAL_H */