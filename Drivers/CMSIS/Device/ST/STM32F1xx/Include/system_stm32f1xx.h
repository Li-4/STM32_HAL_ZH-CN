/**
 *******************************************************************************
 * @file    system_stm32f1xx.h
 * @author  (翻译作者)github.com/Li-4 注：目前只包含我使用的代码
 * @brief   CMSIS Cortex-M3 设备的外设访问层系统头文件
 *******************************************************************************
*/

#ifndef __SYSTEM_STM32F10X_H
#define __SYSTEM_STM32F10X_H

/**
 * @brief STM32F10x 系统导出类型 STM32F10x_System_Exported_types
*/
extern uint32_t SystemCoreClock;            /* 系统时钟频率 (内核时钟) */
extern const uint8_t  AHBPrescTable[16U];   /* AHB 预先分频表值 */
extern const uint8_t  APBPrescTable[8U];    /* APB 预先分频表值 */

/**
 * @brief STM32F10x_System 导出函数
*/
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#endif /*__SYSTEM_STM32F10X_H */
