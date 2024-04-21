/**
 *******************************************************************************
 * @file    stm32f1xx_hal_def.h
 * @author  (翻译作者)github.com/Li-4 注：目前只包含我使用的代码
 * @brief   这个文件包含 HAL 库常见的定义、枚举、宏、结构体定义
 *******************************************************************************
*/

/* 防止递归包含的定义 ----------------------------------------------------------*/
#ifndef __STM32F1xx_HAL_DEF
#define __STM32F1xx_HAL_DEF


/* 包含 -----------------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "Legacy/stm32_hal_legacy.h"
#include <stddef.h>


/* 导出 类型 ------------------------------------------------------------------*/

/**
 * @brief  HAL 状态枚举定义
*/
typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

/**
 * @brief HAL 锁定枚举定义
*/
typedef enum
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U
} HAL_LockTypeDef;


/* 导出 宏 --------------------------------------------------------------------*/
#define HAL_MAX_DELAY      0xFFFFFFFFU

#define HAL_IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) != 0U)
#define HAL_IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)

#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)           \
                    do{                                                        \
                          (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__); \
                          (__DMA_HANDLE__).Parent = (__HANDLE__);              \
                      } while(0U)


#if !defined(UNUSED)
#define UNUSED(X) (void)X      /* 避免编译器发出 未使用变量的警告 */
#endif /* UNUSED */


/**
 * @brief  清除句柄的状态字段
 * @param  __HANDLE__ 指定外设句柄
 * @note   这个宏可用于以下目的：
 *          - 当句柄被声明为局部变量时，在把第一次把它当作参数传递给 HAL_PPP_Init()
 *            之前，必须使用此宏将句柄的状态字段设置为 0
 *            此外，状态字段可能时任何随机值，并且第一次调用 HAL_PPP_Init() 时，将错
 *            过 LL 初始化
 *          - 当需要重新配置 LL 硬件时：用户除了可以先调用HAL_PPP_DInit()，再调用
 *            HAL_PPP_Init() 以外，还可以先调用这个宏再调用 HAL_PPP_Init()
 *            在后面的函数中，当句柄的状态域设置为 0 时，它将会执行 HAL_PPP_MspInit()
 *            函数，这个函数可以重新配置 LL 硬件
 * @retval 无
*/
#define __HAL_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = 0U)


#if (USE_RTOS == 1U)
/* 保留以备将来使用 */
#error "在当前的 HAL 发行版中 USE_RTOS 需要被设置为 0"
#else
#define __HAL_LOCK(__HANDLE__)                                                 \
                                do{                                            \
                                    if((__HANDLE__)->Lock == HAL_LOCKED)       \
                                    {                                          \
                                      return HAL_BUSY;                         \
                                    }                                          \
                                    else                                       \
                                    {                                          \
                                      (__HANDLE__)->Lock = HAL_LOCKED;         \
                                    }                                          \
                                  }while (0U)
#define __HAL_UNLOCK(__HANDLE__)                                               \
                                do{                                            \
                                    (__HANDLE__)->Lock = HAL_UNLOCKED;         \
                                  }while (0U)
#endif /* USE_RTOS */


#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#ifndef __weak
#define __weak  __attribute__((weak))
#endif
#ifndef __packed
#define __packed  __attribute__((packed))
#endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
#ifndef __weak
#define __weak   __attribute__((weak))
#endif /* __weak */
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif /* __packed */
#endif /* __GNUC__ */


/* 这个宏使变量按4字节对齐，对于__ICCARM__，则必须使用指令 #pragma data_alignment=4 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
  #ifndef __ALIGN_BEGIN
  #define __ALIGN_BEGIN
  #endif
  #ifndef __ALIGN_END
  #define __ALIGN_END      __attribute__ ((aligned (4)))
  #endif

#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
  #ifndef __ALIGN_BEGIN
  #define __ALIGN_BEGIN
  #endif /* __ALIGN_BEGIN */
  #ifndef __ALIGN_END
  #define __ALIGN_END    __attribute__ ((aligned (4)))
  #endif /* __ALIGN_END */

#else
  #ifndef __ALIGN_BEGIN
  #if defined   (__CC_ARM)      /* ARM Compiler V5*/
  #define __ALIGN_BEGIN    __align(4)
  #elif defined (__ICCARM__)    /* IAR Compiler */
  #define __ALIGN_BEGIN
  #endif /* __CC_ARM */
  #endif /* __ALIGN_BEGIN */
  #ifndef __ALIGN_END
  #define __ALIGN_END
  #endif /* __ALIGN_END */

#endif /* __GNUC__ */


/**
  * @brief  __RAM_FUNC definition
  */
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
/* ARM Compiler V4/V5 and V6
   --------------------------
   RAM functions are defined using the toolchain options.
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const'
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog.
*/
#define __RAM_FUNC

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
   RAM functions are defined using a specific toolchain keyword "__ramfunc".
*/
#define __RAM_FUNC __ramfunc

#elif defined   (  __GNUC__  )
/* GNU Compiler
   ------------
  RAM functions are defined using a specific toolchain attribute
   "__attribute__((section(".RamFunc")))".
*/
#define __RAM_FUNC __attribute__((section(".RamFunc")))

#endif

/**
  * @brief  __NOINLINE definition
  */
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined   (  __GNUC__  )
/* ARM V4/V5 and V6 & GNU Compiler
   -------------------------------
*/
#define __NOINLINE __attribute__ ( (noinline) )

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
*/
#define __NOINLINE _Pragma("optimize = no_inline")

#endif
#endif /* __STM32F1xx_HAL_DEF */