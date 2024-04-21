/**
 *******************************************************************************
 * @file    stm32f1xx_it.h
 * @author  github.com/Li-4
 * @brief   这个文件包含中断处理函数的声明
 *******************************************************************************
*/

/* 防止递归包含 ---------------------------------------------------------------*/
#ifndef __STM32F1xx_IT_H
#define __STM32F1xx_IT_H

/* 导出 函数 ------------------------------------------------------------------*/

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif /* __STM32F1xx_IT_H */