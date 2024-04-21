/**
 *******************************************************************************
 * @file    stm32f1xx.h
 * @author  (翻译作者)github.com/Li-4 注：目前只包含我使用的代码
 * @brief   CMSIS STM32F1xx 设备的外设访问层头文件
 *          这个文件是应用开发者在 C 源码中使用的唯一包含文件，通常包含在 main.c 中
 *          这个文件包含：
 *            - 配置部分，这允许选择：
 *              - 目标应用程序中使用的 STM32F1xx 设备
 *              - 在应用代码中时发作使用外设驱动（例如：代码将基于对外设寄存器的直接访问
 *                ，而不是对驱动程序 API 的访问）
 *                这个选项可以通过 `#define USE_HAL_DRIVER` 配置
 * 
 *******************************************************************************
*/

#ifndef __STM32F1XX_H
#define __STM32F1XX_H


/**
 * @brief STM32 系列
*/
#if !defined (STM32F1)
#define STM32F1
#endif /* STM32F1 */


/* 根据应用程序中使用的目标 STM32 设备，取消注释下面的行 */

#if !defined (STM32F100xB) && !defined (STM32F100xE) && !defined (STM32F101x6) && \
    !defined (STM32F101xB) && !defined (STM32F101xE) && !defined (STM32F101xG) && !defined (STM32F102x6) && !defined (STM32F102xB) && !defined (STM32F103x6) && \
    !defined (STM32F103xB) && !defined (STM32F103xE) && !defined (STM32F103xG) && !defined (STM32F105xC) && !defined (STM32F107xC)
  /* #define STM32F100xB  */   /*!< STM32F100C4, STM32F100R4, STM32F100C6, STM32F100R6, STM32F100C8, STM32F100R8, STM32F100V8, STM32F100CB, STM32F100RB and STM32F100VB */
  /* #define STM32F100xE */    /*!< STM32F100RC, STM32F100VC, STM32F100ZC, STM32F100RD, STM32F100VD, STM32F100ZD, STM32F100RE, STM32F100VE and STM32F100ZE */
  /* #define STM32F101x6  */   /*!< STM32F101C4, STM32F101R4, STM32F101T4, STM32F101C6, STM32F101R6 and STM32F101T6 Devices */
  /* #define STM32F101xB  */   /*!< STM32F101C8, STM32F101R8, STM32F101T8, STM32F101V8, STM32F101CB, STM32F101RB, STM32F101TB and STM32F101VB */
  /* #define STM32F101xE */    /*!< STM32F101RC, STM32F101VC, STM32F101ZC, STM32F101RD, STM32F101VD, STM32F101ZD, STM32F101RE, STM32F101VE and STM32F101ZE */ 
  /* #define STM32F101xG  */   /*!< STM32F101RF, STM32F101VF, STM32F101ZF, STM32F101RG, STM32F101VG and STM32F101ZG */
  /* #define STM32F102x6 */    /*!< STM32F102C4, STM32F102R4, STM32F102C6 and STM32F102R6 */
  /* #define STM32F102xB  */   /*!< STM32F102C8, STM32F102R8, STM32F102CB and STM32F102RB */
  /* #define STM32F103x6  */   /*!< STM32F103C4, STM32F103R4, STM32F103T4, STM32F103C6, STM32F103R6 and STM32F103T6 */
  /* #define STM32F103xB  */   /*!< STM32F103C8, STM32F103R8, STM32F103T8, STM32F103V8, STM32F103CB, STM32F103RB, STM32F103TB and STM32F103VB */
  /* #define STM32F103xE */    /*!< STM32F103RC, STM32F103VC, STM32F103ZC, STM32F103RD, STM32F103VD, STM32F103ZD, STM32F103RE, STM32F103VE and STM32F103ZE */
  /* #define STM32F103xG  */   /*!< STM32F103RF, STM32F103VF, STM32F103ZF, STM32F103RG, STM32F103VG and STM32F103ZG */
  /* #define STM32F105xC */    /*!< STM32F105R8, STM32F105V8, STM32F105RB, STM32F105VB, STM32F105RC and STM32F105VC */
  /* #define STM32F107xC  */   /*!< STM32F107RB, STM32F107VB, STM32F107RC and STM32F107VC */  
#endif

/*  提示：为了避免每次在更换这些设置的时候修改这个文件，你可以在你工具链的编译器预处理中定义设备  */


#if !defined (USE_HAL_DRIVER)
/**
 * @brief 如果你不使用外设驱动，请注释下行
 * 在这种情况下，这些驱动将不会被包含并且应用代码将会基于直接访问外设寄存器
*/
  /*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */


/**
 * @brief CMSIS 设备版本号
*/
#define __STM32F1_CMSIS_VERSION_MAIN    (0x04) /*!< [31:24] 主版本号 */
#define __STM32F1_CMSIS_VERSION_SUB1    (0x03) /*!< [23:16] 子版本号 1 */
#define __STM32F1_CMSIS_VERSION_SUB2    (0x04) /*!< [15:8]  子版本号 2 */
#define __STM32F1_CMSIS_VERSION_RC      (0x00) /*!< [7:0]   发行候选版本 */ 
#define __STM32F1_CMSIS_VERSION         ((__STM32F1_CMSIS_VERSION_MAIN << 24)\
                                        |(__STM32F1_CMSIS_VERSION_SUB1 << 16)\
                                        |(__STM32F1_CMSIS_VERSION_SUB2 << 8 )\
                                        |(__STM32F1_CMSIS_VERSION_RC))


/**
 * @brief 设备引入
*/
#if defined(STM32F100xB)
  #include "stm32f100xb.h"
#elif defined(STM32F100xE)
  #include "stm32f100xe.h"
#elif defined(STM32F101x6)
  #include "stm32f101x6.h"
#elif defined(STM32F101xB)
  #include "stm32f101xb.h"
#elif defined(STM32F101xE)
  #include "stm32f101xe.h"
#elif defined(STM32F101xG)
  #include "stm32f101xg.h"
#elif defined(STM32F102x6)
  #include "stm32f102x6.h"
#elif defined(STM32F102xB)
  #include "stm32f102xb.h"
#elif defined(STM32F103x6)
  #include "stm32f103x6.h"
#elif defined(STM32F103xB)
  #include "stm32f103xb.h"
#elif defined(STM32F103xE)
  #include "stm32f103xe.h"
#elif defined(STM32F103xG)
  #include "stm32f103xg.h"
#elif defined(STM32F105xC)
  #include "stm32f105xc.h"
#elif defined(STM32F107xC)
  #include "stm32f107xc.h"
#else
  #error "请首先选择应用程序中使用的目标 STM32F1xx 设备 (在 stm32f1xx.h 文件中)"
#endif


/**
 * @brief 定义标志位状态 和 中断状态
*/
typedef enum 
{
  RESET = 0, 
  SET = !RESET
} FlagStatus, ITStatus;

/**
 * @brief 定义功能状态，并定义检查状态是否是功能状态的宏
*/
typedef enum 
{
  DISABLE = 0, 
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

/**
 * @brief 定义错误状态
*/
typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;

/**
 * @brief 导出 宏定义
*/
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 
/**
 *******************************************************************************
 *                            中间略过了一些原子宏定义
 *******************************************************************************
*/

#if defined (USE_HAL_DRIVER)
  #include "stm32f1xx_hal.h"
#endif /* USE_HAL_DRIVER */

#endif /* __STM32F1XX_H */