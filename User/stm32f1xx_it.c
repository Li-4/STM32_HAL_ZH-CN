/**
 *******************************************************************************
 * @file    stm32f1xx_it.c
 * @author  github.com/Li-4
 * @brief   主要的中断服务例程
 *******************************************************************************
*/

/* 包含 ----------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"

/* 导出 函数 ------------------------------------------------------------------*/

/******************************************************************************/
/*                         Cortex-M3 处理器异常处理程序                         */
/******************************************************************************/

/**
 * @brief  这个函数处理 NMI 不可屏蔽中断异常
 * @param  无
 * @retval 无
*/
void NMI_Handler(void)
{
}


/**
 * @brief  这个函数处理 硬件错误异常
 * @param  无
 * @retval 无
*/
void HardFault_Handler(void)
{
    /* 当 硬件错误异常 出现时，进入无限循环 */
    while (1)
    {
    }
}


/**
 * @brief  这个函数处理 内存管理异常
 * @param  无
 * @retval 无
*/
void MemManage_Handler(void)
{
    /* 当 内存管理异常 出现时，进入无限循环 */
    while (1)
    {
    }
}


/**
 * @brief  这个函数处理 总线错误异常
 * @param  无
 * @retval 无
*/
void BusFault_Handler(void)
{
    /* 当 总线错误异常 出现时，进入无限循环 */
    while (1)
    {
    }
}


/**
 * @brief  这个函数处理 用法错误异常
 * @param  无
 * @retval 无
*/
void UsageFault_Handler(void)
{
    /* 当 用法错误异常 出现时，进入无限循环 */
    while (1)
    {
    }
}


/**
 * @brief  这个函数处理 SVCall 系统服务调用异常
 * @param  无
 * @retval 无
*/
void SVC_Handler(void)
{
}


/**
 * @brief  这个函数处理 调试监控异常
 * @param  无
 * @retval 无
*/
void DebugMon_Handler(void)
{
}


/**
 * @brief  这个函数处理 可挂起的系统调用异常
 * @param  无
 * @retval 无
*/
void PendSV_Handler(void)
{
}


/**
 * @brief  这个函数处理 SysTick
 * @param  无
 * @retval 无
*/
void SysTick_Handler(void)
{
    HAL_IncTick();
}


/******************************************************************************/
/*                         STM32F1xx 外设 中断处理程序                         */
/*          在这里添加使用的 PPP 外设的中断处理程序                              */
/*          可用的外设中断处理程序名请参照启动文件 startup_stm32f1xx.s           */
/******************************************************************************/

/**
 * @brief  这个函数处理 PPP 外设的中断请求
 * @param  无
 * @retval 无
*/
// void PPP_IRQHandler(void)
// {
// }