/**
 *******************************************************************************
 * @file    stm32f103xe.h
 * @author  (翻译作者)github.com/Li-4 注：目前只包含我使用的代码
 * @brief   CMSIS Cortex-M3 设备的外设访问层头文件
 *          这个文件包含所有的外设寄存器定义，位定义和 STM32F1xx 设备的内存映射
 * 
 *          这个文件包含：
 *           - 所有外设的数据结构和地址映射
 *           - 外设的寄存器声明和位定义
 *           - 访问外设寄存器硬件的宏
 * 
 *******************************************************************************
*/

#ifndef __STM32F103xE_H
#define __STM32F103xE_H


/**
  * @brief 配置 Cortex-M3 处理器 和 内核外设 
 */
#define __CM3_REV                  0x0200U  /*!< 内核版本 r2p0                                 */
#define __MPU_PRESENT              0U       /*!< 其他 STM32 设备没有提供 MPU 内存保护单元        */
#define __NVIC_PRIO_BITS           4U       /*!< STM32 使用 4 Bits 设置优先级                   */
#define __Vendor_SysTickConfig     0U       /*!< 设置为 1 如果要使用不同的 SysTick 配置          */


/**
 * Peripheral_interrupt_number_definition
 * @brief STM32F10x 中断号定义
*/
typedef enum
{
/******  Cortex-M3 处理器异常号 ********************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt 不可屏蔽中断                 */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt 硬件错误中断         */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt 内存管理中断  */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt 总线错误中断          */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt 使用错误中断        */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt %监督调用中断          */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt 调试监控中断     */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt %挂起服务中断          */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt 系统嘀嗒中断       */

/******  STM32 指定的中断号 ************************************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt 窗口看门狗中断              */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt 电压监控中断*/
  TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt 侵入检测中断                         */
  RTC_IRQn                    = 3,      /*!< RTC global Interrupt 实时时钟中断                     */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt 闪存中断                       */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt 复位与时钟控制中断                */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt 外部中断线 0                     */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt 外部中断线 1                     */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt 外部中断线 2                     */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt 外部中断线 3                     */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt 外部中断线 4                     */
  DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt DMA1 通道1中断        */
  DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt DMA1 通道2中断        */
  DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt DMA1 通道3中断        */
  DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt DMA1 通道4中断        */
  DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt DMA1 通道5中断        */
  DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt DMA1 通道6中断        */
  DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt DMA1 通道7中断        */
  ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt ADC1 和 ADC2 中断      */
  USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
  USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts 外部中断线 5~9          */
  TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt TIM1 刹车中断                    */
  TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt TIM1 更新中断                   */
  TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt TIM1 触发和换相中断  */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt TIM1 捕获比较中断      */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt TIM2中断                       */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt TIM3中断                       */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt TIM4中断                       */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt I2C1 事件中断                    */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt I2C1 错误中断                    */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt I2C2 事件中断                    */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt I2C2 错误中断                    */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt SPI1 中断                      */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt SPI2 中断                      */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt USART1 中断                  */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt USART2 中断                  */
  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt USART3 中断                  */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts 外部中断线 10~15      */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm through EXTI Line Interrupt RTC 闹钟中断    */
  USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
  TIM8_BRK_IRQn               = 43,     /*!< TIM8 Break Interrupt                                 */
  TIM8_UP_IRQn                = 44,     /*!< TIM8 Update Interrupt                                */
  TIM8_TRG_COM_IRQn           = 45,     /*!< TIM8 Trigger and Commutation Interrupt               */
  TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare Interrupt                       */
  ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
  FSMC_IRQn                   = 48,     /*!< FSMC global Interrupt                                */
  SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
  TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                */
  SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
  UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
  UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
  TIM6_IRQn                   = 54,     /*!< TIM6 global Interrupt                                */
  TIM7_IRQn                   = 55,     /*!< TIM7 global Interrupt                                */
  DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
  DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
  DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
  DMA2_Channel4_5_IRQn        = 59,     /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
} IRQn_Type;
#endif /* __STM32F103xE_H */


#include "core_cm3.h"
#include "system_stm32f1xx.h"
#include <stdint.h>


/** 
 * @brief 通用输入输出 GPIO 寄存器结构体定义
*/
typedef struct 
{
  __IO uint32_t CRL;        // 端口配置低寄存器 -> 配置低8位端口的输入输出模式
  __IO uint32_t CRH;        // 端口配置高寄存器 -> 配置高8位端口的输入输出模式
  __IO uint32_t IDR;        // 端口输入数据寄存器 -> 这些位为只读并只能以字(16位)的形式读出,读出的值为对应I/O口的状态
  __IO uint32_t ODR;        // 端口输出数据寄存器 -> 这些位可读可写并只能以字(16位)的形式操作
  __IO uint32_t BSRR;       // 端口位设置/清除寄存器 -> 高16位 BR清除对应的ODR位为0 低16位 BS设置对应的ODR位为1，BR与BS 同时设置时BS有效
  __IO uint32_t BRR;        // 端口位清除寄存器 -> 低16位有效 1清除对应的ODR位为0 0不会产生影响
  __IO uint32_t LCKR;       // 端口配置锁定寄存器 -> 锁定端口的配置
} GPIO_TypeDef;


/** 
 * @brief 备用功能输入输出 AFIO 寄存器结构体定义
*/
typedef struct
{
  __IO uint32_t EVCR;       // 事件控制寄存器
  __IO uint32_t MAPR;       // 复用重映射和调试I/O配置寄存器
  __IO uint32_t EXTICR[4];  // 外部中断配置寄存器
} AFIO_TypeDef;


/** 
 * @brief 复位和时钟控制 RCC 寄存器结构体定义
*/
typedef struct
{
  __IO uint32_t CR;         // 时钟控制寄存器
  __IO uint32_t CFGR;       // 时钟配置寄存器
  __IO uint32_t CIR;        // 时钟中断寄存器
  __IO uint32_t APB2RSTR;   // APB2 外设复位寄存器
  __IO uint32_t APB1RSTR;   // APB1 外设复位寄存器
  __IO uint32_t AHBENR;     // AHB 外设时钟使能寄存器
  __IO uint32_t APB2ENR;    // APB2 外设时钟使能寄存器
  __IO uint32_t APB1ENR;    // APB1 外设时钟使能寄存器
  __IO uint32_t BDCR;       // 备份域控制寄存器
  __IO uint32_t CSR;        // 控制/状态寄存器
} RCC_TypeDef;


/**
 *******************************************************************************
 *                Peripheral_memory_map & Peripheral_declaration
 *                        @brief 外设内存映射 和 外设声明
 *******************************************************************************
*/

/**
 * @brief Peripheral_memory_map
*/
#define FLASH_BASE            0x08000000UL /* FLASH 在别名区的基地址 (0x0800 0000) */
#define FLASH_BANK1_END       0x0807FFFFUL /* FLASH 第一块存储区的结束地址 (0x0807 FFFF) */
#define SRAM_BASE             0x20000000UL /* SRAM 在别名区的基地址 (0x2000 0000) */
#define PERIPH_BASE           0x40000000UL /* 外设在别名区的基地址 (0x4000 0000) */

#define SRAM_BB_BASE          0x22000000UL /* SRAM 在位带区的基地址 (0x2200 0000) */
#define PERIPH_BB_BASE        0x42000000UL /* 外设在位带区的基地址 (0x4200 0000) */

#define FSMC_BASE             0x60000000UL /* FSMC 基地址 (0x6000 0000) */
#define FSMC_R_BASE           0xA0000000UL /* FSMC 寄存器基地址 (0xA000 0000) */

/* 外设内存映射 */
#define APB1PERIPH_BASE       PERIPH_BASE                   /* APB1总线 外设起始地址 (0x4000 0000) */
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)  /* APB2总线 外设起始地址 (0x4001 0000) */
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000UL)  /* AHB总线 外设起始地址 (0x4002 0000) */

#define AFIO_BASE             (APB2PERIPH_BASE + 0x00000000UL)  /* AFIO 复用功能输入/输出 控制寄存器起始地址 */

#define GPIOA_BASE            (APB2PERIPH_BASE + 0x00000800UL)  /* GIPOA 通用输入/输出 控制寄存器起始地址 */
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x00000C00UL)  /* GIPOB 通用输入/输出 控制寄存器起始地址 */
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x00001000UL)  /* GIPOC 通用输入/输出 控制寄存器起始地址 */
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x00001400UL)  /* GIPOD 通用输入/输出 控制寄存器起始地址 */
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x00001800UL)  /* GIPOE 通用输入/输出 控制寄存器起始地址 */
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x00001C00UL)  /* GIPOF 通用输入/输出 控制寄存器起始地址 */
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x00002000UL)  /* GIPOG 通用输入/输出 控制寄存器起始地址 */

#define RCC_BASE              (AHBPERIPH_BASE + 0x00001000UL)   /* RCC 复位和时钟 控制寄存器起始地址 */


/**
 * @brief Peripheral_declaration
*/
#define AFIO                ((AFIO_TypeDef *)AFIO_BASE)         /* AFIO 寄存器声明 */

#define GPIOA               ((GPIO_TypeDef *)GPIOA_BASE)        /* GPIOA 寄存器声明 */
#define GPIOB               ((GPIO_TypeDef *)GPIOB_BASE)        /* GPIOB 寄存器声明 */
#define GPIOC               ((GPIO_TypeDef *)GPIOC_BASE)        /* GPIOC 寄存器声明 */
#define GPIOD               ((GPIO_TypeDef *)GPIOD_BASE)        /* GPIOD 寄存器声明 */
#define GPIOE               ((GPIO_TypeDef *)GPIOE_BASE)        /* GPIOE 寄存器声明 */
#define GPIOF               ((GPIO_TypeDef *)GPIOF_BASE)        /* GPIOF 寄存器声明 */
#define GPIOG               ((GPIO_TypeDef *)GPIOG_BASE)        /* GPIOG 寄存器声明 */

#define RCC                 ((RCC_TypeDef *)RCC_BASE)           /* RTC 寄存器声明 */




/******************************************************************************/
/*                                                                            */
/*                         Reset and Clock Control                            */
/*                                                                            */
/******************************************************************************/

/*************************  RCC_CR 控制寄存器的位定义  **************************/
#define RCC_CR_HSION_Pos                     (0U)                              
#define RCC_CR_HSION_Msk                     (0x1UL << RCC_CR_HSION_Pos)        /* 0x00000001 */
#define RCC_CR_HSION                         RCC_CR_HSION_Msk                   /* 内部高速时钟使能 */
#define RCC_CR_HSIRDY_Pos                    (1U)                              
#define RCC_CR_HSIRDY_Msk                    (0x1UL << RCC_CR_HSIRDY_Pos)       /* 0x00000002 */
#define RCC_CR_HSIRDY                        RCC_CR_HSIRDY_Msk                  /* 内部高速时钟就绪标志 */
#define RCC_CR_HSITRIM_Pos                   (3U)                              
#define RCC_CR_HSITRIM_Msk                   (0x1FUL << RCC_CR_HSITRIM_Pos)     /* 0x000000F8 */
#define RCC_CR_HSITRIM                       RCC_CR_HSITRIM_Msk                 /* 内部高速时钟调整 */
#define RCC_CR_HSICAL_Pos                    (8U)                              
#define RCC_CR_HSICAL_Msk                    (0xFFUL << RCC_CR_HSICAL_Pos)      /* 0x0000FF00 */
#define RCC_CR_HSICAL                        RCC_CR_HSICAL_Msk                  /* 内部高速时钟校准 */
#define RCC_CR_HSEON_Pos                     (16U)                             
#define RCC_CR_HSEON_Msk                     (0x1UL << RCC_CR_HSEON_Pos)        /* 0x00010000 */
#define RCC_CR_HSEON                         RCC_CR_HSEON_Msk                   /* 外部高速时钟使能 */
#define RCC_CR_HSERDY_Pos                    (17U)                             
#define RCC_CR_HSERDY_Msk                    (0x1UL << RCC_CR_HSERDY_Pos)       /* 0x00020000 */
#define RCC_CR_HSERDY                        RCC_CR_HSERDY_Msk                  /* 外部高速时钟就绪标志 */
#define RCC_CR_HSEBYP_Pos                    (18U)                             
#define RCC_CR_HSEBYP_Msk                    (0x1UL << RCC_CR_HSEBYP_Pos)       /* 0x00040000 */
#define RCC_CR_HSEBYP                        RCC_CR_HSEBYP_Msk                  /* 外部高速时钟旁路 */
#define RCC_CR_CSSON_Pos                     (19U)                             
#define RCC_CR_CSSON_Msk                     (0x1UL << RCC_CR_CSSON_Pos)        /* 0x00080000 */
#define RCC_CR_CSSON                         RCC_CR_CSSON_Msk                   /* 时钟安全系统使能 */
#define RCC_CR_PLLON_Pos                     (24U)                             
#define RCC_CR_PLLON_Msk                     (0x1UL << RCC_CR_PLLON_Pos)        /* 0x01000000 */
#define RCC_CR_PLLON                         RCC_CR_PLLON_Msk                   /* PLL使能 */
#define RCC_CR_PLLRDY_Pos                    (25U)                             
#define RCC_CR_PLLRDY_Msk                    (0x1UL << RCC_CR_PLLRDY_Pos)       /* 0x02000000 */
#define RCC_CR_PLLRDY                        RCC_CR_PLLRDY_Msk                  /* PLL时钟就绪标志 */


/*******************  Bit definition for RCC_CFGR register  *******************/
/*!< SW 系统时钟切换 */
#define RCC_CFGR_SW_Pos                      (0U)                              
#define RCC_CFGR_SW_Msk                      (0x3UL << RCC_CFGR_SW_Pos)         /* 0x00000003 */
#define RCC_CFGR_SW                          RCC_CFGR_SW_Msk                    /* SW[1:0] bits (系统时钟切换) */
#define RCC_CFGR_SW_0                        (0x1UL << RCC_CFGR_SW_Pos)         /* 0x00000001 */
#define RCC_CFGR_SW_1                        (0x2UL << RCC_CFGR_SW_Pos)         /* 0x00000002 */

#define RCC_CFGR_SW_HSI                      0x00000000U                        /* 选择 HSI 作为系统时钟 */
#define RCC_CFGR_SW_HSE                      0x00000001U                        /* 选择 HSE 作为系统时钟 */
#define RCC_CFGR_SW_PLL                      0x00000002U                        /* 选择 PLL 作为系统时钟 */

/*!< SWS 系统时钟切换状态 */
#define RCC_CFGR_SWS_Pos                     (2U)                              
#define RCC_CFGR_SWS_Msk                     (0x3UL << RCC_CFGR_SWS_Pos)        /* 0x0000000C */
#define RCC_CFGR_SWS                         RCC_CFGR_SWS_Msk                   /* SWS[1:0] bits (系统时钟切换状态) */
#define RCC_CFGR_SWS_0                       (0x1UL << RCC_CFGR_SWS_Pos)        /* 0x00000004 */
#define RCC_CFGR_SWS_1                       (0x2UL << RCC_CFGR_SWS_Pos)        /* 0x00000008 */

#define RCC_CFGR_SWS_HSI                     0x00000000U                        /* HSI 振荡器作为系统时钟 */
#define RCC_CFGR_SWS_HSE                     0x00000004U                        /* HSE 振荡器作为系统时钟 */
#define RCC_CFGR_SWS_PLL                     0x00000008U                        /* PLL 作为系统时钟 */

/*!< HPRE AHB预分频 */
#define RCC_CFGR_HPRE_Pos                    (4U)                              
#define RCC_CFGR_HPRE_Msk                    (0xFUL << RCC_CFGR_HPRE_Pos)       /* 0x000000F0 */
#define RCC_CFGR_HPRE                        RCC_CFGR_HPRE_Msk                  /* HPRE[3:0] bits (AHB 预分频) */
#define RCC_CFGR_HPRE_0                      (0x1UL << RCC_CFGR_HPRE_Pos)       /* 0x00000010 */
#define RCC_CFGR_HPRE_1                      (0x2UL << RCC_CFGR_HPRE_Pos)       /* 0x00000020 */
#define RCC_CFGR_HPRE_2                      (0x4UL << RCC_CFGR_HPRE_Pos)       /* 0x00000040 */
#define RCC_CFGR_HPRE_3                      (0x8UL << RCC_CFGR_HPRE_Pos)       /* 0x00000080 */

#define RCC_CFGR_HPRE_DIV1                   0x00000000U                        /* SYSCLK 不分频 */
#define RCC_CFGR_HPRE_DIV2                   0x00000080U                        /* SYSCLK 2 分频 */
#define RCC_CFGR_HPRE_DIV4                   0x00000090U                        /* SYSCLK 4 分频 */
#define RCC_CFGR_HPRE_DIV8                   0x000000A0U                        /* SYSCLK 8 分频 */
#define RCC_CFGR_HPRE_DIV16                  0x000000B0U                        /* SYSCLK 16 分频 */
#define RCC_CFGR_HPRE_DIV64                  0x000000C0U                        /* SYSCLK 64 分频 */
#define RCC_CFGR_HPRE_DIV128                 0x000000D0U                        /* SYSCLK 128 分频 */
#define RCC_CFGR_HPRE_DIV256                 0x000000E0U                        /* SYSCLK 256 分频 */
#define RCC_CFGR_HPRE_DIV512                 0x000000F0U                        /* SYSCLK 512 分频 */

/*!< PPRE1 低速APB预分频(APB1) */
#define RCC_CFGR_PPRE1_Pos                   (8U)                              
#define RCC_CFGR_PPRE1_Msk                   (0x7UL << RCC_CFGR_PPRE1_Pos)      /* 0x00000700 */
#define RCC_CFGR_PPRE1                       RCC_CFGR_PPRE1_Msk                 /* PRE1[2:0] bits (APB1 预分频) */
#define RCC_CFGR_PPRE1_0                     (0x1UL << RCC_CFGR_PPRE1_Pos)      /* 0x00000100 */
#define RCC_CFGR_PPRE1_1                     (0x2UL << RCC_CFGR_PPRE1_Pos)      /* 0x00000200 */
#define RCC_CFGR_PPRE1_2                     (0x4UL << RCC_CFGR_PPRE1_Pos)      /* 0x00000400 */

#define RCC_CFGR_PPRE1_DIV1                  0x00000000U                        /* HCLK 不分频 */
#define RCC_CFGR_PPRE1_DIV2                  0x00000400U                        /* HCLK 2 分频 */
#define RCC_CFGR_PPRE1_DIV4                  0x00000500U                        /* HCLK 4 分频 */
#define RCC_CFGR_PPRE1_DIV8                  0x00000600U                        /* HCLK 8 分频 */
#define RCC_CFGR_PPRE1_DIV16                 0x00000700U                        /* HCLK 16 分频 */

/*!< PPRE2 高速APB预分频(APB2) */
#define RCC_CFGR_PPRE2_Pos                   (11U)                             
#define RCC_CFGR_PPRE2_Msk                   (0x7UL << RCC_CFGR_PPRE2_Pos)      /* 0x00003800 */
#define RCC_CFGR_PPRE2                       RCC_CFGR_PPRE2_Msk                 /* PRE2[2:0] bits (APB2 预分频) */
#define RCC_CFGR_PPRE2_0                     (0x1UL << RCC_CFGR_PPRE2_Pos)      /* 0x00000800 */
#define RCC_CFGR_PPRE2_1                     (0x2UL << RCC_CFGR_PPRE2_Pos)      /* 0x00001000 */
#define RCC_CFGR_PPRE2_2                     (0x4UL << RCC_CFGR_PPRE2_Pos)      /* 0x00002000 */

#define RCC_CFGR_PPRE2_DIV1                  0x00000000U                        /* HCLK 不分频 */
#define RCC_CFGR_PPRE2_DIV2                  0x00002000U                        /* HCLK 2 分频 */
#define RCC_CFGR_PPRE2_DIV4                  0x00002800U                        /* HCLK 4 分频 */
#define RCC_CFGR_PPRE2_DIV8                  0x00003000U                        /* HCLK 8 分频 */
#define RCC_CFGR_PPRE2_DIV16                 0x00003800U                        /* HCLK 16 分频 */

/*!< ADCPPRE ADC预分频 */
#define RCC_CFGR_ADCPRE_Pos                  (14U)                             
#define RCC_CFGR_ADCPRE_Msk                  (0x3UL << RCC_CFGR_ADCPRE_Pos)     /* 0x0000C000 */
#define RCC_CFGR_ADCPRE                      RCC_CFGR_ADCPRE_Msk                /* ADCPRE[1:0] bits (ADC 预分频) */
#define RCC_CFGR_ADCPRE_0                    (0x1UL << RCC_CFGR_ADCPRE_Pos)     /* 0x00004000 */
#define RCC_CFGR_ADCPRE_1                    (0x2UL << RCC_CFGR_ADCPRE_Pos)     /* 0x00008000 */

#define RCC_CFGR_ADCPRE_DIV2                 0x00000000U                        /* PCLK2 2分频后作为ADC时钟 */
#define RCC_CFGR_ADCPRE_DIV4                 0x00004000U                        /* PCLK2 4分频后作为ADC时钟 */
#define RCC_CFGR_ADCPRE_DIV6                 0x00008000U                        /* PCLK2 6分频后作为ADC时钟 */
#define RCC_CFGR_ADCPRE_DIV8                 0x0000C000U                        /* PCLK2 8分频后作为ADC时钟 */

#define RCC_CFGR_PLLSRC_Pos                  (16U)                             
#define RCC_CFGR_PLLSRC_Msk                  (0x1UL << RCC_CFGR_PLLSRC_Pos)     /* 0x00010000 */
#define RCC_CFGR_PLLSRC                      RCC_CFGR_PLLSRC_Msk                /* PLL 输入时钟源 */

#define RCC_CFGR_PLLXTPRE_Pos                (17U)                             
#define RCC_CFGR_PLLXTPRE_Msk                (0x1UL << RCC_CFGR_PLLXTPRE_Pos)   /* 0x00020000 */
#define RCC_CFGR_PLLXTPRE                    RCC_CFGR_PLLXTPRE_Msk              /* HSE 分频器作为PLL输入 */

#define RCC_CFGR_PLLXTPRE_HSE                0x00000000U                        /* HSE 不分频作为PLL输入 */
#define RCC_CFGR_PLLXTPRE_HSE_DIV2           0x00020000U                        /* HSE 2分频作为PLL输入 */

/*!< PLLMUL PLL倍频系数 */
#define RCC_CFGR_PLLMULL_Pos                 (18U)                             
#define RCC_CFGR_PLLMULL_Msk                 (0xFUL << RCC_CFGR_PLLMULL_Pos)    /* 0x003C0000 */
#define RCC_CFGR_PLLMULL                     RCC_CFGR_PLLMULL_Msk               /* PLLMUL[3:0] bits (PLL 倍频系数) */
#define RCC_CFGR_PLLMULL_0                   (0x1UL << RCC_CFGR_PLLMULL_Pos)    /* 0x00040000 */
#define RCC_CFGR_PLLMULL_1                   (0x2UL << RCC_CFGR_PLLMULL_Pos)    /* 0x00080000 */
#define RCC_CFGR_PLLMULL_2                   (0x4UL << RCC_CFGR_PLLMULL_Pos)    /* 0x00100000 */
#define RCC_CFGR_PLLMULL_3                   (0x8UL << RCC_CFGR_PLLMULL_Pos)    /* 0x00200000 */

#define RCC_CFGR_PLLMULL2                    0x00000000U                        /* PLL 2倍频输出 */
#define RCC_CFGR_PLLMULL3_Pos                (18U)                             
#define RCC_CFGR_PLLMULL3_Msk                (0x1UL << RCC_CFGR_PLLMULL3_Pos)   /* 0x00040000 */
#define RCC_CFGR_PLLMULL3                    RCC_CFGR_PLLMULL3_Msk              /* PLL 3倍频输出 */
#define RCC_CFGR_PLLMULL4_Pos                (19U)                             
#define RCC_CFGR_PLLMULL4_Msk                (0x1UL << RCC_CFGR_PLLMULL4_Pos)   /* 0x00080000 */
#define RCC_CFGR_PLLMULL4                    RCC_CFGR_PLLMULL4_Msk              /* PLL 4倍频输出 */
#define RCC_CFGR_PLLMULL5_Pos                (18U)                             
#define RCC_CFGR_PLLMULL5_Msk                (0x3UL << RCC_CFGR_PLLMULL5_Pos)   /* 0x000C0000 */
#define RCC_CFGR_PLLMULL5                    RCC_CFGR_PLLMULL5_Msk              /* PLL 5倍频输出 */
#define RCC_CFGR_PLLMULL6_Pos                (20U)                             
#define RCC_CFGR_PLLMULL6_Msk                (0x1UL << RCC_CFGR_PLLMULL6_Pos)   /* 0x00100000 */
#define RCC_CFGR_PLLMULL6                    RCC_CFGR_PLLMULL6_Msk              /* PLL 6倍频输出 */
#define RCC_CFGR_PLLMULL7_Pos                (18U)                             
#define RCC_CFGR_PLLMULL7_Msk                (0x5UL << RCC_CFGR_PLLMULL7_Pos)   /* 0x00140000 */
#define RCC_CFGR_PLLMULL7                    RCC_CFGR_PLLMULL7_Msk              /* PLL 7倍频输出 */
#define RCC_CFGR_PLLMULL8_Pos                (19U)                             
#define RCC_CFGR_PLLMULL8_Msk                (0x3UL << RCC_CFGR_PLLMULL8_Pos)   /* 0x00180000 */
#define RCC_CFGR_PLLMULL8                    RCC_CFGR_PLLMULL8_Msk              /* PLL 8倍频输出 */
#define RCC_CFGR_PLLMULL9_Pos                (18U)                             
#define RCC_CFGR_PLLMULL9_Msk                (0x7UL << RCC_CFGR_PLLMULL9_Pos)   /* 0x001C0000 */
#define RCC_CFGR_PLLMULL9                    RCC_CFGR_PLLMULL9_Msk              /* PLL 9倍频输出 */
#define RCC_CFGR_PLLMULL10_Pos               (21U)                             
#define RCC_CFGR_PLLMULL10_Msk               (0x1UL << RCC_CFGR_PLLMULL10_Pos)  /* 0x00200000 */
#define RCC_CFGR_PLLMULL10                   RCC_CFGR_PLLMULL10_Msk             /* PLL 10倍频输出 */
#define RCC_CFGR_PLLMULL11_Pos               (18U)                             
#define RCC_CFGR_PLLMULL11_Msk               (0x9UL << RCC_CFGR_PLLMULL11_Pos)  /* 0x00240000 */
#define RCC_CFGR_PLLMULL11                   RCC_CFGR_PLLMULL11_Msk             /* PLL 11倍频输出 */
#define RCC_CFGR_PLLMULL12_Pos               (19U)                             
#define RCC_CFGR_PLLMULL12_Msk               (0x5UL << RCC_CFGR_PLLMULL12_Pos)  /* 0x00280000 */
#define RCC_CFGR_PLLMULL12                   RCC_CFGR_PLLMULL12_Msk             /* PLL 12倍频输出 */
#define RCC_CFGR_PLLMULL13_Pos               (18U)                             
#define RCC_CFGR_PLLMULL13_Msk               (0xBUL << RCC_CFGR_PLLMULL13_Pos)  /* 0x002C0000 */
#define RCC_CFGR_PLLMULL13                   RCC_CFGR_PLLMULL13_Msk             /* PLL 13倍频输出 */
#define RCC_CFGR_PLLMULL14_Pos               (20U)                             
#define RCC_CFGR_PLLMULL14_Msk               (0x3UL << RCC_CFGR_PLLMULL14_Pos)  /* 0x00300000 */
#define RCC_CFGR_PLLMULL14                   RCC_CFGR_PLLMULL14_Msk             /* PLL 14倍频输出 */
#define RCC_CFGR_PLLMULL15_Pos               (18U)                             
#define RCC_CFGR_PLLMULL15_Msk               (0xDUL << RCC_CFGR_PLLMULL15_Pos)  /* 0x00340000 */
#define RCC_CFGR_PLLMULL15                   RCC_CFGR_PLLMULL15_Msk             /* PLL 15倍频输出 */
#define RCC_CFGR_PLLMULL16_Pos               (19U)                             
#define RCC_CFGR_PLLMULL16_Msk               (0x7UL << RCC_CFGR_PLLMULL16_Pos)  /* 0x00380000 */
#define RCC_CFGR_PLLMULL16                   RCC_CFGR_PLLMULL16_Msk             /* PLL 16倍频输出 */
#define RCC_CFGR_USBPRE_Pos                  (22U)                             
#define RCC_CFGR_USBPRE_Msk                  (0x1UL << RCC_CFGR_USBPRE_Pos)     /* 0x00400000 */
#define RCC_CFGR_USBPRE                      RCC_CFGR_USBPRE_Msk                /* USB 设备预分频 */

/*!< MCO 微控制器时钟输出 */
#define RCC_CFGR_MCO_Pos                     (24U)                             
#define RCC_CFGR_MCO_Msk                     (0x7UL << RCC_CFGR_MCO_Pos)        /* 0x07000000 */
#define RCC_CFGR_MCO                         RCC_CFGR_MCO_Msk                   /* MCO[2:0] bits (微控制器时钟输出) */
#define RCC_CFGR_MCO_0                       (0x1UL << RCC_CFGR_MCO_Pos)        /* 0x01000000 */
#define RCC_CFGR_MCO_1                       (0x2UL << RCC_CFGR_MCO_Pos)        /* 0x02000000 */
#define RCC_CFGR_MCO_2                       (0x4UL << RCC_CFGR_MCO_Pos)        /* 0x04000000 */

#define RCC_CFGR_MCO_NOCLOCK                 0x00000000U                        /* 没有时钟输出 */
#define RCC_CFGR_MCO_SYSCLK                  0x04000000U                        /* 系统时钟(SYSCLK)输出 */
#define RCC_CFGR_MCO_HSI                     0x05000000U                        /* 内部RC振荡器时钟(HSI)输出 */
#define RCC_CFGR_MCO_HSE                     0x06000000U                        /* 外部振荡器时钟(HSE)输出 */
#define RCC_CFGR_MCO_PLLCLK_DIV2             0x07000000U                        /* PLL时钟2分频后输出 */

 /* Reference defines */
  #define RCC_CFGR_MCOSEL                      RCC_CFGR_MCO
  #define RCC_CFGR_MCOSEL_0                    RCC_CFGR_MCO_0
  #define RCC_CFGR_MCOSEL_1                    RCC_CFGR_MCO_1
  #define RCC_CFGR_MCOSEL_2                    RCC_CFGR_MCO_2
  #define RCC_CFGR_MCOSEL_NOCLOCK              RCC_CFGR_MCO_NOCLOCK
  #define RCC_CFGR_MCOSEL_SYSCLK               RCC_CFGR_MCO_SYSCLK
  #define RCC_CFGR_MCOSEL_HSI                  RCC_CFGR_MCO_HSI
  #define RCC_CFGR_MCOSEL_HSE                  RCC_CFGR_MCO_HSE
  #define RCC_CFGR_MCOSEL_PLL_DIV2             RCC_CFGR_MCO_PLLCLK_DIV2


/*!<******************  Bit definition for RCC_CIR register  ********************/
#define RCC_CIR_LSIRDYF_Pos                  (0U)                              
#define RCC_CIR_LSIRDYF_Msk                  (0x1UL << RCC_CIR_LSIRDYF_Pos)     /*!< 0x00000001 */
#define RCC_CIR_LSIRDYF                      RCC_CIR_LSIRDYF_Msk               /*!< LSI Ready Interrupt flag */
#define RCC_CIR_LSERDYF_Pos                  (1U)                              
#define RCC_CIR_LSERDYF_Msk                  (0x1UL << RCC_CIR_LSERDYF_Pos)     /*!< 0x00000002 */
#define RCC_CIR_LSERDYF                      RCC_CIR_LSERDYF_Msk               /*!< LSE Ready Interrupt flag */
#define RCC_CIR_HSIRDYF_Pos                  (2U)                              
#define RCC_CIR_HSIRDYF_Msk                  (0x1UL << RCC_CIR_HSIRDYF_Pos)     /*!< 0x00000004 */
#define RCC_CIR_HSIRDYF                      RCC_CIR_HSIRDYF_Msk               /*!< HSI Ready Interrupt flag */
#define RCC_CIR_HSERDYF_Pos                  (3U)                              
#define RCC_CIR_HSERDYF_Msk                  (0x1UL << RCC_CIR_HSERDYF_Pos)     /*!< 0x00000008 */
#define RCC_CIR_HSERDYF                      RCC_CIR_HSERDYF_Msk               /*!< HSE Ready Interrupt flag */
#define RCC_CIR_PLLRDYF_Pos                  (4U)                              
#define RCC_CIR_PLLRDYF_Msk                  (0x1UL << RCC_CIR_PLLRDYF_Pos)     /*!< 0x00000010 */
#define RCC_CIR_PLLRDYF                      RCC_CIR_PLLRDYF_Msk               /*!< PLL Ready Interrupt flag */
#define RCC_CIR_CSSF_Pos                     (7U)                              
#define RCC_CIR_CSSF_Msk                     (0x1UL << RCC_CIR_CSSF_Pos)        /*!< 0x00000080 */
#define RCC_CIR_CSSF                         RCC_CIR_CSSF_Msk                  /*!< Clock Security System Interrupt flag */
#define RCC_CIR_LSIRDYIE_Pos                 (8U)                              
#define RCC_CIR_LSIRDYIE_Msk                 (0x1UL << RCC_CIR_LSIRDYIE_Pos)    /*!< 0x00000100 */
#define RCC_CIR_LSIRDYIE                     RCC_CIR_LSIRDYIE_Msk              /*!< LSI Ready Interrupt Enable */
#define RCC_CIR_LSERDYIE_Pos                 (9U)                              
#define RCC_CIR_LSERDYIE_Msk                 (0x1UL << RCC_CIR_LSERDYIE_Pos)    /*!< 0x00000200 */
#define RCC_CIR_LSERDYIE                     RCC_CIR_LSERDYIE_Msk              /*!< LSE Ready Interrupt Enable */
#define RCC_CIR_HSIRDYIE_Pos                 (10U)                             
#define RCC_CIR_HSIRDYIE_Msk                 (0x1UL << RCC_CIR_HSIRDYIE_Pos)    /*!< 0x00000400 */
#define RCC_CIR_HSIRDYIE                     RCC_CIR_HSIRDYIE_Msk              /*!< HSI Ready Interrupt Enable */
#define RCC_CIR_HSERDYIE_Pos                 (11U)                             
#define RCC_CIR_HSERDYIE_Msk                 (0x1UL << RCC_CIR_HSERDYIE_Pos)    /*!< 0x00000800 */
#define RCC_CIR_HSERDYIE                     RCC_CIR_HSERDYIE_Msk              /*!< HSE Ready Interrupt Enable */
#define RCC_CIR_PLLRDYIE_Pos                 (12U)                             
#define RCC_CIR_PLLRDYIE_Msk                 (0x1UL << RCC_CIR_PLLRDYIE_Pos)    /*!< 0x00001000 */
#define RCC_CIR_PLLRDYIE                     RCC_CIR_PLLRDYIE_Msk              /*!< PLL Ready Interrupt Enable */
#define RCC_CIR_LSIRDYC_Pos                  (16U)                             
#define RCC_CIR_LSIRDYC_Msk                  (0x1UL << RCC_CIR_LSIRDYC_Pos)     /*!< 0x00010000 */
#define RCC_CIR_LSIRDYC                      RCC_CIR_LSIRDYC_Msk               /*!< LSI Ready Interrupt Clear */
#define RCC_CIR_LSERDYC_Pos                  (17U)                             
#define RCC_CIR_LSERDYC_Msk                  (0x1UL << RCC_CIR_LSERDYC_Pos)     /*!< 0x00020000 */
#define RCC_CIR_LSERDYC                      RCC_CIR_LSERDYC_Msk               /*!< LSE Ready Interrupt Clear */
#define RCC_CIR_HSIRDYC_Pos                  (18U)                             
#define RCC_CIR_HSIRDYC_Msk                  (0x1UL << RCC_CIR_HSIRDYC_Pos)     /*!< 0x00040000 */
#define RCC_CIR_HSIRDYC                      RCC_CIR_HSIRDYC_Msk               /*!< HSI Ready Interrupt Clear */
#define RCC_CIR_HSERDYC_Pos                  (19U)                             
#define RCC_CIR_HSERDYC_Msk                  (0x1UL << RCC_CIR_HSERDYC_Pos)     /*!< 0x00080000 */
#define RCC_CIR_HSERDYC                      RCC_CIR_HSERDYC_Msk               /*!< HSE Ready Interrupt Clear */
#define RCC_CIR_PLLRDYC_Pos                  (20U)                             
#define RCC_CIR_PLLRDYC_Msk                  (0x1UL << RCC_CIR_PLLRDYC_Pos)     /*!< 0x00100000 */
#define RCC_CIR_PLLRDYC                      RCC_CIR_PLLRDYC_Msk               /*!< PLL Ready Interrupt Clear */
#define RCC_CIR_CSSC_Pos                     (23U)                             
#define RCC_CIR_CSSC_Msk                     (0x1UL << RCC_CIR_CSSC_Pos)        /*!< 0x00800000 */
#define RCC_CIR_CSSC                         RCC_CIR_CSSC_Msk                  /*!< Clock Security System Interrupt Clear */


