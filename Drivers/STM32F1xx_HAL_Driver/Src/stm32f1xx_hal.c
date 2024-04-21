/**
 *******************************************************************************
 * @file    stm32f1xx_hal.c
 * @author  (翻译作者)github.com/Li-4 注：目前只包含我使用的代码
 * @brief   HAL 模块驱动
 *          这是 HAL 库初始化的主要部分
 *******************************************************************************
  @verbatim
  ==============================================================================
                          ##### 如何使用这个驱动 ######
  ==============================================================================
    [..]
    公共 HAL 驱动程序包含一组通用和公共 API，PPP 外设驱动程序和用户可以使用这些 API 来开始使用 HAL
    [..]
    HAL 包含两种 API：
        (+) 通用 HAL API
        (+) 服务 HAL API
 *******************************************************************************
  @endverbatim
*/


/* 包含 ----------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

#ifdef HAL_MODULE_ENABLED

/* 私有定义 -------------------------------------------------------------------*/

/**
 * @brief STM32F1xx HAL 驱动版本号
*/
#define __STM32F1xx_HAL_VERSION_MAIN   (0x01U) /* [31:24] 主版本号 */
#define __STM32F1xx_HAL_VERSION_SUB1   (0x01U) /* [23:16] 子版本号 1 */
#define __STM32F1xx_HAL_VERSION_SUB2   (0x09U) /* [15:8]  子版本号 2 */
#define __STM32F1xx_HAL_VERSION_RC     (0x00U) /* [7:0]   发行候选 */
#define __STM32F1xx_HAL_VERSION         ((__STM32F1xx_HAL_VERSION_MAIN << 24)\
                                        |(__STM32F1xx_HAL_VERSION_SUB1 << 16)\
                                        |(__STM32F1xx_HAL_VERSION_SUB2 << 8 )\
                                        |(__STM32F1xx_HAL_VERSION_RC))

#define IDCODE_DEVID_MASK    0x00000FFFU

/* 私有变量 -------------------------------------------------------------------*/
__IO uint32_t uwTick;
uint32_t uwTickPrio = (1UL << __NVIC_PRIO_BITS);          /* Invalid PRIO */
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;   /* 1KHz */

/* 导出的函数 ---------------------------------------------------------*/

/**
 * @brief 初始化 和 反初始化 函数
 * @verbatim
  ==============================================================================
                        ##### 初始化 和 反初始化 函数 #####
  ==============================================================================
    [..]  这一节提供的函数允许：
        (+) 初始化闪存接口，NVIC 分配和初始化时钟配置
            它还会在超时时初始化 SysTick，并使能后备域
        (+) 反初始化 HAL 的公共部分
        (+) 配置时基单元为具有 1ms 的时基 和 专用的 Tick 中断优先级
          (++)  SysTick 定时器作为时基单元的默认源使用，但用户最终可以实现其他合适的时
                基源（例如 通用定时器和其他时基）
                请记住时基持续时间应保持在 1ms，因为 PPP_TIMEOUT_VALUEs 是以毫秒为单
                位定义和处理的
          (++)  时基配置函数（HAL_InitTick()）在程序开始时复位之后通过 HAL_Init() 自
                动调用 或 在时钟配置好后的任何时间由 HAL_RCC_ClockConfig() 调用
          (++)  时基源被配置为以规定的时间间隔生成中断。
                如果从外设的 中断服务程序调用 HAL_Delay()，则必须小心，Tick 中断线的
                优先级必须高于（数值上低于）外设中断 否则，调用方的中断服务进程将被阻塞
          (++)  影响时基配置的函数被声明为 __weak，以便在用户文件中有其他实现时覆盖
 * @endverbatim
*/


/**
 * @brief   这个函数用于初始化 HAL 库；它必须是在 main 函数中运行的第一条指令（在调用
 *          任何其他 HAL 函数之前），它执行以下操作：
 *            配置闪存预取
 *            配置 SysTick 每毫秒生成一次中断，SysTick 由 HSI 时钟驱动（在这个阶段，
 *            时钟还没有配置，因此系统运行在内部的 HSI 时钟 8MHz 下）
 *            设置 NVIC 优先级分组为 4
 *            调用定义在用户文件 "stm32f1xx_hal_msp.c" 中的 HAL_MspInit() 回调函数
 *            进行全局低级别(LL)硬件初始化
 * 
 * @note    SysTick 作为 HAL_Delay() 函数的时基单元使用，应用必须确保 SysTick 的时基
 *          总是设置为 1ms 来保证 HAL 操作正确
 * @retval  HAL 运行状态
*/
HAL_StatusTypeDef HAL_Init(void)
{
  /* 配置闪存预取 */
#if (PREFETCH_ENABLE != 0)
#if defined(STM32F101x6) || defined(STM32F101xB) || defined(STM32F101xE) || defined(STM32F101xG) || \
    defined(STM32F102x6) || defined(STM32F102xB) || \
    defined(STM32F103x6) || defined(STM32F103xB) || defined(STM32F103xE) || defined(STM32F103xG) || \
    defined(STM32F105xC) || defined(STM32F107xC)
  
  /* 预取缓冲区在超值系列设备上不可用 */
  __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif
#endif /* PREFETCH_ENABLE */

  /* 设置中断优先级分组 */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* 使用系统嘀嗒定时器作为时基单元并配置 1ms 的嘀嗒定时 (复位后的默认时钟是 HSI) */
  HAL_InitTick(TICK_INT_PRIORITY);

  /* 初始化 LL 硬件*/
  HAL_MspInit();

  /* 返回函数状态 */
  return HAL_OK;
}


/**
 * @brief  这个函数反初始化 HAL 中 常用部分，并停止时基单元的系统嘀嗒定时器
 * @note   这个函数时可选的
 * @retval HAL 状态
*/
HAL_StatusTypeDef HAL_DeInit(void)
{
  /* 复位所有的外设 */
  __HAL_RCC_APB1_FORCE_RESET();
  __HAL_RCC_APB1_RELEASE_RESET();

  __HAL_RCC_APB2_FORCE_RESET();
  __HAL_RCC_APB2_RELEASE_RESET();

#if defined(STM32F105xC) || defined(STM32F107xC)
  __HAL_RCC_AHB_FORCE_RESET();
  __HAL_RCC_AHB_RELEASE_RESET();
#endif

  /* 反初始化 LL 硬件 */
  HAL_MspDeInit();

  /* 返回函数状态 */
  return HAl_OK;
}


/**
 * @brief  初始化 MSP
 * @retval 无
*/
__weak void HAL_MspInit(void)
{
  /* 注意：不应该修改此函数，当需要回调时，可以在用户文件中实现 HAL_MspInit*/
}


/**
 * @brief  反初始化 MSP
 * @retval 无
*/
__weak void HAL_MspDeInit(void)
{
  /* 注意：不应该修改此函数，当需要回调时，可以在用户文件中实现 HAL_MspDeInit*/
}


/**
 * @brief  这个函数配置时基单元的源
 *         时间源配置为具有 1ms 时基，并具有专用的 Tick 中断优先级
 * @note   这个函数在程序开始时复位后由 HAL_Init() 自动调用
 *         或，任意时刻在时钟被 HAL_RCC_ClockConfig() 重新配置时调用
 * @note   在默认的实现中，系统嘀嗒定时器作为时基单元的源
 *         它用于在规则的时间间隔生成中断
 *         必须小心，如果一个外设的中断服务程序调用 HAL_Delay()，SysTick 中断必须具有
 *         比外设中断更高的优先级（数值上更小）否则，调用方的中断服务程序会被阻塞
 *         该函数被声明为 __weak，便于用户文件名中有其他实现的情况下被覆盖
 * @param  TickPriority Tick 中断优先级
 * @retval HAL 状态
*/
__weak HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  /* 将 SysTick 配置为在 1ms 具有 1ms 的时基中断*/
  if (HAL_SYSTICK_Config(SystemCoreClock / (1000U / uwTickFreq)) > 0U)
  {
    return HAL_ERROR;
  }

  /* 配置 SysTick 中断请求优先级 */
  if (TickPriority < (1UL << __NVIC_PRIO_BITS))
  {
    HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0U);
    uwTickPrio = TickPriority;
  }
  else
  {
    return HAL_ERROR;
  }
  
  /* 返回函数状态 */
  return HAL_OK;
}


/**
 * @brief  HAL 控制函数
 * @verbatim
  ==============================================================================
                              ##### HAL 控制函数 #####
  ==============================================================================
    [..]  这一节提供的函数允许：
        (+) 提供一个以毫秒为单位的嘀嗒值
        (+) 提供一个以毫秒为单位的阻塞延时
        (+) 暂停时基源中断
        (+) 恢复时基源中断
        (+) 获取 HAL API 驱动版本号
        (+) 获取设备标识符
        (+) 获取设备版本标识符
        (+) 在 SLEEP 模式期间使能/失能调试模块
        (+) 在 STOP 模式期间使能/失能调试模块
        (+) 在 STANDBY 模式期间使能/失能调试模块
 * @endverbatim
*/


/**
 * @brief  调用这个函数是为了增加用作应用程序时基的全局变量 uwTick
 * @note   在默认实现中，这个值在 1ms 一次的 SysTick 中断服务程序中递增
 * @note   该函数被声明为 __weak，便于用户文件名中有其他实现的情况下被覆盖
 * @retval 无
*/
__weak void HAL_IncTick(void)
{
  uwTick += uwTickFreq;
}


/**
 * @brief  提供一个以毫秒为单位的嘀嗒值
 * @note   该函数被声明为 __weak，便于用户文件名中有其他实现的情况下被覆盖
 * @retval 嘀嗒值
*/
__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}


/**
 * @brief  这个函数返回嘀嗒优先级
 * @retval 嘀嗒优先级
*/
uint32_t HAL_GetTickPrio(void)
{
  return uwTickPrio;
}


/**
 * @brief  设置新的嘀嗒频率
 * @retval 状态
*/
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq)
{
  HAL_StatusTypeDef status = HAL_OK;
  HAL_TickFreqTypeDef prevTickFreq;

  assert_param(IS_TICKFREQ(Freq));

  if (uwTickFreq != Freq)
  {
    /* 备份 uwTickFreq 频率 */
    prevTickFreq = uwTickFreq;

    /* 更新 HAL_InitTick() 使用的 uwTickFreq 全局变量 */
    uwTickFreq = Freq;

    /* 应用新的 嘀嗒频率 */
    status = HAL_InitTick(uwTickPrio);

    if (status != HAL_OK)
    {
      /* 恢复为先前的嘀嗒频率 */
      uwTickFreq = prevTickFreq;
    }
  }
  
  return status;
}


/**
 * @brief  返回嘀嗒频率
 * @retval 嘀嗒频率，HAL_TickFreqTypeDef 的一个枚举值
*/
HAL_TickFreqTypeDef HAL_GetTickFreq(void)
{
  return uwTickFreq;
}


/**
 * @brief  这个函数提供基于变量增量的最小延时（以毫秒为单位）
 * @note   在默认的实现中，系统嘀嗒定时器作为时基单元的源
 *         它用于在规则的时间间隔生成中断，其中 uwTick 递增
 * @note   该函数被声明为 __weak，便于用户文件名中有其他实现的情况下被覆盖
 * @param  Delay 指定延时时长，以毫秒为单位
 * @retval 无
 * 
*/
__weak void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* 添加频率以保证最短的等待时间 */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)(uwTickFreq);
  }
  
  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}


/**
 * @brief  挂起 Tick 递增
 * @note   在默认的实现中，系统嘀嗒定时器作为时基单元的源
 *         它用于在规则的时间间隔生成中断
 *         一旦 HAL_SuspendTick() 被调用，系统嘀嗒中断将会被禁用，Tick 递增也会被挂起
 * @note   该函数被声明为 __weak，便于用户文件名中有其他实现的情况下被覆盖
 * @retval 无
*/
__weak void HAL_SuspendTick(void)
{
  /* 禁用 SysTick 中断 */
  CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}


/**
 * @brief  恢复 Tick 递增
 * @note   在默认的实现中，系统嘀嗒定时器作为时基单元的源
 *         它用于在规则的时间间隔生成中断
 *         一旦 HAL_ResumeTick() 被调用，系统嘀嗒中断将会被使能，Tick 递增也会被恢复
 * @note   该函数被声明为 __weak，便于用户文件名中有其他实现的情况下被覆盖
 * @retval 无
*/
__weak void HAL_ResumeTick(void)
{
  /* 使能 SysTick 中断 */
  SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}


/**
 * @brief  返回 HAL 修订版本
 * @retval 版本号 0xXYZR
*/
uint32_t HAL_GetHalVersion(void)
{
  return __STM32F1xx_HAL_VERSION;
}


/**
 * @brief  返回设备版本标识符
 * @note   在设备 STM32F10xx8 STM32F10xxB,
 *               STM32F101xC/D/E STM32F103xC/D/E,
 *               STM32F101xF/G STM32F103xF/G
 *               STM32F10xx4 STM32F10xx6 中
 *         调试寄存器 DBGMCU_IDCODE 和 DBGMCU_CR 只在调试模式中可以访问
 *         （用户软件在正常模式下不能访问）
 * @retval 设备版本标识符
*/
uint32_t HAL_GetREVID(void)
{
  return ((DBGMCU->IDCODE) >> DBGMCU_IDCODE_REV_ID_Pos);
}


/**
 * @brief  返回设备标识符
 * @note   在设备 STM32F10xx8 STM32F10xxB,
 *               STM32F101xC/D/E STM32F103xC/D/E,
 *               STM32F101xF/G STM32F103xF/G
 *               STM32F10xx4 STM32F10xx6 中
 *         调试寄存器 DBGMCU_IDCODE 和 DBGMCU_CR 只在调试模式中可以访问
 *         （用户软件在正常模式下不能访问）
 * @retval 设备标识符
*/
uint32_t HAL_GetDEVID(void)
{
  return ((DBGMCU->IDCODE) & IDCODE_DEVID_MASK);
}


/**
 * @brief  返回唯一设备标识符的第一个字（UID有96位）
 * @retval 设备标识符
*/
uint32_t HAL_GetUIDw0(void)
{
   return(READ_REG(*((uint32_t *)UID_BASE)));
}

/**
 * @brief  返回唯一设备标识符的第二个字（UID有96位）
 * @retval 设备标识符
*/
uint32_t HAL_GetUIDw1(void)
{
   return(READ_REG(*((uint32_t *)(UID_BASE + 4U))));
}

/**
 * @brief  返回唯一设备标识符的第三个字（UID有96位）
 * @retval 设备标识符
*/
uint32_t HAL_GetUIDw2(void)
{
   return(READ_REG(*((uint32_t *)(UID_BASE + 8U))));
}



#endif /* HAL_MODULE_ENABLED */