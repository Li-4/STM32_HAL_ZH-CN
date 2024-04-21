/**
 *******************************************************************************
 * @file    main.c
 * @author  github.com/Li-4
 * @brief   主程序体
 *******************************************************************************
 */

/* 包含 ----------------------------------------------------------------------*/
#include "main.h"

/* 私有函数原型 ---------------------------------------------------------------*/
void SystemClock_Config(void);

/* 私有函数 -------------------------------------------------------------------*/

/**
 * @brief  主程序
 * @param  无
 * @retval 无
 */
int main(void)
{
    /* STM32 HAL 库初始化：
        - 配置闪存预取
        - Systick 计时器默认配置为时基的源时钟，但用户最终可以实现其他适当的时基源（例
            如通用计时器或其他时钟源），请记住时基的持续时间应该保持在 1ms，因为
            PPP_TIMEOUT_VALUEs 被定义为以毫秒为单位处理
        - 将 NVIC 的优先级分组设置为 4
        - LL 库初始化*/
    HAL_Init();

    /* 配置系统时钟到 72 MHz */
    SystemClock_Config();

    while (1)
    {
    }
}

/**
 * @brief  系统时钟配置
 *         系统时钟配置如下：
 *              系统时钟源      = PLL(HSE)
 *              SYSCLK(Hz)     = 72000000
 *              HCLK(Hz)       = 72000000
 *              AHB 预分频器    = 1
 *              APB1 预分频器   = 2
 *              APB2 预分频器   = 1
 *              PLLMUL 倍频因子 = 9
 *              Flash 延迟      = 2
 * @param  无
 * @retval 无
 */
void SystemClock_Config(void)
{
}

// void SystemClock_Config(void)
// {
//     RCC_ClkInitTypeDef clkinitstruct = {0};
//     RCC_OscInitTypeDef oscinitstruct = {0};

//     /* Configure PLL ------------------------------------------------------*/
//     /* PLL configuration: PLLCLK = (HSI / 2) * PLLMUL = (8 / 2) * 16 = 64 MHz */
//     /* PREDIV1 configuration: PREDIV1CLK = PLLCLK / HSEPredivValue = 64 / 1 = 64 MHz */
//     /* Enable HSI and activate PLL with HSi_DIV2 as source */
//     oscinitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
//     oscinitstruct.HSEState = RCC_HSE_OFF;
//     oscinitstruct.LSEState = RCC_LSE_OFF;
//     oscinitstruct.HSIState = RCC_HSI_ON;
//     oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
//     oscinitstruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
//     oscinitstruct.PLL.PLLState = RCC_PLL_ON;
//     oscinitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
//     oscinitstruct.PLL.PLLMUL = RCC_PLL_MUL16;
//     if (HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
//     {
//         /* Initialization Error */
//         while (1)
//             ;
//     }

//     /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
//        clocks dividers */
//     clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//     clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//     clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//     clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
//     clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
//     if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2) != HAL_OK)
//     {
//         /* Initialization Error */
//         while (1)
//             ;
//     }
// }

#ifdef USE_FULL_ASSERT

/**
 * @brief  报告发生 assert_param 错误的源文件的名称和行号
 * @param  file: 指向源文件名的 uint8_t 指针
 * @param  line: assert_param 错误的行号
 * @retval 无
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* 用户可以添加他自己的实现来报告文件名和行号 */
    // printf("Wrong parameters value: file %s on line %d\r\n", file, line);

    while (1)
    {
    }
}

#endif /* USE_FULL_ASSERT */