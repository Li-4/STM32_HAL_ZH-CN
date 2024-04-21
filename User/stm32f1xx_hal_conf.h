/**
 *******************************************************************************
 * @file    stm32f1xx_hal_conf.h
 * @author  (翻译作者)github.com/Li-4
 * @brief   HAL 配置文件
 *******************************************************************************
*/


/* 防止递归包含 ---------------------------------------------------------------*/
#ifndef __STM32F1xx_HAL_CONF_H
#define __STM32F1xx_HAL_CONF_H


/* 导出 宏定义 ----------------------------------------------------------------*/

/* ################################ 选择模块 ################################# */
/**
 * @brief 这里是 HAL 驱动中要使用的模块列表
*/
#define HAL_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_CAN_MODULE_ENABLED
/* #define HAL_CAN_LEGACY_MODULE_ENABLED */
#define HAL_CEC_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_CRC_MODULE_ENABLED
#define HAL_DAC_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_ETH_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_HCD_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
#define HAL_I2S_MODULE_ENABLED
#define HAL_IRDA_MODULE_ENABLED
#define HAL_IWDG_MODULE_ENABLED
#define HAL_NAND_MODULE_ENABLED
#define HAL_NOR_MODULE_ENABLED
#define HAL_PCCARD_MODULE_ENABLED
#define HAL_PCD_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_RTC_MODULE_ENABLED
#define HAL_SD_MODULE_ENABLED
#define HAL_SMARTCARD_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED
#define HAL_SRAM_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_USART_MODULE_ENABLED
#define HAL_WWDG_MODULE_ENABLED


/* ############################## 震荡器值调整 ############################### */
/**
 * @brief 调整你的应用中使用的外部高速振荡器 (HSE) 的值
 *        RCC 模块使用这个值来计算系统频率（当 HSE 直接或通过 PLL 用作系统时钟源时）
*/
#if !defined (HSE_VALUE)
  #define HSE_VALUE              8000000U  /* 外部振荡器的值 Hz */
#endif /* HSE_VALUE */

#if !defined (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    100U      /* HSE 启振延时，单位是 ms */
#endif /* HSE_STARTUP_TIMEOUT */


/**
 * @brief 内部高速振荡器的值 (HSI)
 *        RCC 模块使用这个值来计算系统频率（当 HSI 直接或通过 PLL 用作系统时钟源时）
*/
#if !defined (HSI_VALUE)
  #define HSI_VALUE              8000000U  /* 内部振荡器的值 Hz */
#endif /* HSI_VALUE */


/**
 * @brief 内部低速振荡器的值 (LSI)
*/
#if !defined (LSI_VALUE) 
 #define LSI_VALUE               40000U    /* LSI 典型值 Hz */
#endif /* LSI_VALUE */                     /* 内部低速振荡器的实际值会随电压和温度
                                              变化而变化 */


/**
 * @brief 外部低速振荡器的值 (LSE)
 *        这个值用于 UART RTC 模块计算系统频率
*/
#if !defined (LSE_VALUE)
  #define LSE_VALUE              32768U    /* 外部振荡器的值 Hz*/
#endif /* LSE_VALUE */

#if !defined (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    5000U     /* LSE 启振延时，单位是 ms */
#endif /* LSE_STARTUP_TIMEOUT */

/* 为了避免在使用不同的 HSE 时都要更改这个文件，你可以在工具链预处理中定义 HSE 的值*/


/* ################################ 系统配置 ################################# */
/**
 * @brief 这是HAL系统配置部分
*/
#define  VDD_VALUE                    3300U /* VDD 的值 mv */
#define  TICK_INT_PRIORITY            0x0FU /* 嘀嗒中断优先级 */
#define  USE_RTOS                     0U    /* 使用 RTOS */
#define  PREFETCH_ENABLE              1U    /* 闪存预取 */

#define  USE_HAL_ADC_REGISTER_CALLBACKS         0U /* ADC 寄存器回调失能       */
#define  USE_HAL_CAN_REGISTER_CALLBACKS         0U /* CAN 寄存器回调失能       */
#define  USE_HAL_CEC_REGISTER_CALLBACKS         0U /* CEC 寄存器回调失能       */
#define  USE_HAL_DAC_REGISTER_CALLBACKS         0U /* DAC 寄存器回调失能       */
#define  USE_HAL_ETH_REGISTER_CALLBACKS         0U /* ETH 寄存器回调失能       */
#define  USE_HAL_HCD_REGISTER_CALLBACKS         0U /* HCD 寄存器回调失能       */
#define  USE_HAL_I2C_REGISTER_CALLBACKS         0U /* I2C 寄存器回调失能       */
#define  USE_HAL_I2S_REGISTER_CALLBACKS         0U /* I2S 寄存器回调失能       */
#define  USE_HAL_MMC_REGISTER_CALLBACKS         0U /* MMC 寄存器回调失能       */
#define  USE_HAL_NAND_REGISTER_CALLBACKS        0U /* NAND 寄存器回调失能      */
#define  USE_HAL_NOR_REGISTER_CALLBACKS         0U /* NOR 寄存器回调失能       */
#define  USE_HAL_PCCARD_REGISTER_CALLBACKS      0U /* PCCARD 寄存器回调失能    */
#define  USE_HAL_PCD_REGISTER_CALLBACKS         0U /* PCD 寄存器回调失能       */
#define  USE_HAL_RTC_REGISTER_CALLBACKS         0U /* RTC 寄存器回调失能       */
#define  USE_HAL_SD_REGISTER_CALLBACKS          0U /* SD 寄存器回调失能        */
#define  USE_HAL_SMARTCARD_REGISTER_CALLBACKS   0U /* SMARTCARD 寄存器回调失能 */
#define  USE_HAL_IRDA_REGISTER_CALLBACKS        0U /* IRDA 寄存器回调失能      */
#define  USE_HAL_SRAM_REGISTER_CALLBACKS        0U /* SRAM 寄存器回调失能      */
#define  USE_HAL_SPI_REGISTER_CALLBACKS         0U /* SPI 寄存器回调失能       */
#define  USE_HAL_TIM_REGISTER_CALLBACKS         0U /* TIM 寄存器回调失能       */
#define  USE_HAL_UART_REGISTER_CALLBACKS        0U /* UART 寄存器回调失能      */
#define  USE_HAL_USART_REGISTER_CALLBACKS       0U /* USART 寄存器回调失能     */
#define  USE_HAL_WWDG_REGISTER_CALLBACKS        0U /* WWDG 寄存器回调失能      */


/* ################################ 断言选择 ################################# */
/**
 * @brief 取消注释下面的行以拓展 HAL 驱动代码中的 "assert_param" 宏
*/
/* #define USE_FULL_ASSERT    1U */


/* ############################## 以太网外设配置 ############################## */
/* 第 1 节: 以太网外设配置 */

/* MAC 地址:  MAC_ADDR0:MAC_ADDR1:MAC_ADDR2:MAC_ADDR3:MAC_ADDR4:MAC_ADDR5 */
#define MAC_ADDR0   2U
#define MAC_ADDR1   0U
#define MAC_ADDR2   0U
#define MAC_ADDR3   0U
#define MAC_ADDR4   0U
#define MAC_ADDR5   0U

/* 定义以太网驱动程序缓冲区大小和数量 */
#define ETH_RX_BUF_SIZE                ETH_MAX_PACKET_SIZE /* 接收缓冲块大小   */
#define ETH_TX_BUF_SIZE                ETH_MAX_PACKET_SIZE /* 发送缓冲块大小   */

#define ETH_RXBUFNB                    8U                  /* 8 Rx 缓冲区，每块大小为 ETH_RX_BUF_SIZE */
#define ETH_TXBUFNB                    4U                  /* 4 Tx 缓冲区，每块大小为 ETH_TX_BUF_SIZE */

// 略过以太网的物理配置 (DP83848)



/* ############################## SPI 外设配置 ############################### */

/**
 * CRC 功能：用于激活 HAL SPI 驱动内的 CRC 功能
 * 激活：驱动中包含 CRC 代码
 * 停用：驱动中不包含 CRC 代码
*/
#define USR_SPI_CRC                    1U



/* 包含 -----------------------------------------------------------------------*/
/**
 * @brief 包含模块的头文件
*/

#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32f1xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32f1xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_EXTI_MODULE_ENABLED
  #include "stm32f1xx_hal_exti.h"
#endif /* HAL_EXTI_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32f1xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_ETH_MODULE_ENABLED
  #include "stm32f1xx_hal_eth.h"
#endif /* HAL_ETH_MODULE_ENABLED */

#ifdef HAL_CAN_MODULE_ENABLED
  #include "stm32f1xx_hal_can.h"
#endif /* HAL_CAN_MODULE_ENABLED */

#ifdef HAL_CAN_LEGACY_MODULE_ENABLED
  #include "Legacy/stm32f1xx_hal_can_legacy.h"
#endif /* HAL_CAN_LEGACY_MODULE_ENABLED */

#ifdef HAL_CEC_MODULE_ENABLED
  #include "stm32f1xx_hal_cec.h"
#endif /* HAL_CEC_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
  #include "stm32f1xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
  #include "stm32f1xx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
  #include "stm32f1xx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_DAC_MODULE_ENABLED
  #include "stm32f1xx_hal_dac.h"
#endif /* HAL_DAC_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
  #include "stm32f1xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_SRAM_MODULE_ENABLED
  #include "stm32f1xx_hal_sram.h"
#endif /* HAL_SRAM_MODULE_ENABLED */

#ifdef HAL_NOR_MODULE_ENABLED
  #include "stm32f1xx_hal_nor.h"
#endif /* HAL_NOR_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
  #include "stm32f1xx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_I2S_MODULE_ENABLED
  #include "stm32f1xx_hal_i2s.h"
#endif /* HAL_I2S_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
  #include "stm32f1xx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
  #include "stm32f1xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
  #include "stm32f1xx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_PCCARD_MODULE_ENABLED
  #include "stm32f1xx_hal_pccard.h"
#endif /* HAL_PCCARD_MODULE_ENABLED */ 

#ifdef HAL_SD_MODULE_ENABLED
  #include "stm32f1xx_hal_sd.h"
#endif /* HAL_SD_MODULE_ENABLED */  

#ifdef HAL_NAND_MODULE_ENABLED
  #include "stm32f1xx_hal_nand.h"
#endif /* HAL_NAND_MODULE_ENABLED */     

#ifdef HAL_SPI_MODULE_ENABLED
  #include "stm32f1xx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
  #include "stm32f1xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
  #include "stm32f1xx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
  #include "stm32f1xx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
  #include "stm32f1xx_hal_irda.h"
#endif /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
  #include "stm32f1xx_hal_smartcard.h"
#endif /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
  #include "stm32f1xx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

#ifdef HAL_PCD_MODULE_ENABLED
  #include "stm32f1xx_hal_pcd.h"
#endif /* HAL_PCD_MODULE_ENABLED */

#ifdef HAL_HCD_MODULE_ENABLED
  #include "stm32f1xx_hal_hcd.h"
#endif /* HAL_HCD_MODULE_ENABLED */ 


/* 导出 宏定义 ----------------------------------------------------------------*/
#ifdef USE_FULL_ASSERT
/**
 * @brief  assert_param 宏用于函数的参数检查
 * @param  expr: 如果 expr 为 False，它调用 assert_failed 函数，这个函数报告造成这个
 *               错误的源文件名字和行数
 *               如果 expr 为 True，它不返回值
 * @retval 无
*/
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* 导出 函数 ----------------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */


#endif /* __STM32F1xx_HAL_CONF_H */