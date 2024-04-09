/**
 *******************************************************************************
 * @file    system_stm32f1xx.c
 * @author  (翻译作者)github.com/Li-4 注：目前只包含我使用的代码
 * @brief   CMSIS Cortex-M3 设备的外设访问层源文件
 * 
 * 1.  这个文件提供了两个可以被用户应用调用的函数和一个全局变量：
 *      - SystemInit(): 设置系统时钟（系统时钟源，PLL 倍频因子，AHB/APBx 预分频器 和 Flash 设置）
 *                      这个函数在启动时被调用，就在复位之后跳转到 main 程序之前调用
 *                      这个调用在 "startup_stm32f1xx_xx.s" 文件中
 *      - SystemCoreClock 全局变量: 包含当前的内核时钟 (HCLK)，它可以被用户程序用于
 *                                 设置 SysTick 定时器或配置其他参数
 *      - SystemCoreClockUpdate(): 用于更新 SystemCoreClock 变量，必须在程序执行
 *                                 过程中改变内核时钟后调用这个函数
 * 
 * 2.  在每个设备复位后，HSI(8MHz) 高速内部时钟作为系统时钟源。
 *     SystemInit() 函数在 "startup_stm32f1xx_xx.s" 文件中调用，用于在跳转到 main 
 *     程序之前配置系统时钟
 * 
 * 3.  HSE 高速外部时钟默认被设置为 8MHz（或根据产品的晶振设置）通过 "HSE_VALUE" 引用
 *     当 HSE 直接或通过 PLL 用于系统时钟源，并且使用不同的晶振时，必须根据自己的配置
 *     调整 HSE 的值
 * 
 *******************************************************************************
*/

#include "stm32f1xx.h"


#if !defined  (HSE_VALUE) 
  #define HSE_VALUE               8000000U /* 外部振荡器的默认值(单位为Hz)
                                              这个值可以由用户应用提供或调整 */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE               8000000U /* 内部振荡器的默认值(单位为Hz) */
#endif /* HSI_VALUE */


/* 如果需要外部 SRAM 的话，请取消注释下面的行  */ 
/* 这个大容量(256K~512K:命名中的C D E) STM32 设备可以使用 FSMC */
#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
/* #define DATA_IN_ExtSRAM */
#endif /* STM32F100xE || STM32F101xE || STM32F101xG || STM32F103xE || STM32F103xG */


/* 注意：以下向量表地址必须根据链接器配置进行定义 */
/* 如果你需要将向量表重定位到 Flash 或 SRAM 中的任何位置，请取消下面的注释，否则向量表
    将保持在引导地址选择的自动重映射处 */
/* #define USER_VECT_TAB_ADDRESS */

#if defined(USER_VECT_TAB_ADDRESS)
/* 如果需要将你的向量表重定位到 SRAM 中，请取消下行的注释，否则用户重映射将在 Flash 中进行 */
/* #define VECT_TAB_SRAM */
#if defined(VECT_TAB_SRAM)
#define VECT_TAB_BASE_ADDRESS   SRAM_BASE       /* 向量表基地址字段，这个值必须是 0x200 的倍数 */
#define VECT_TAB_OFFSET         0x00000000U     /* 向量表基址偏移字段，这个值必须是 0x200 的倍数 */
#else
#define VECT_TAB_BASE_ADDRESS   FLASH_BASE      /* 向量表基地址字段，这个值必须是 0x200 的倍数 */
#define VECT_TAB_OFFSET         0x00000000U     /* 向量表基址偏移字段，这个值必须是 0x200 的倍数 */
#endif /* VECT_TAB_SRAM */
#endif /* USER_VECT_TAB_ADDRESS */


  /* This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetHCLKFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency 
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
  */
/**
 * 这个变量可以通过三种方式更新：
 *  1) 通过调用 CMSIS 函数 SystemCoreClockUpdate()
 *  2) 通过调用 HAL API 函数 HAL_RCC_GetHCLKFreq()
 *  3) 每次通过调用 HAL_RCC_ClockConfig() 配置系统时钟频率
 *     注意：如果你使用这个函数配置系统时钟，不需要调用上面列出的前两个函数，因为 SystemCoreClock 变量会自动更新
*/
uint32_t SystemCoreClock = 16000000;
const uint8_t AHBPrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8U] =  {0, 0, 0, 0, 1, 2, 3, 4};


#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
#ifdef DATA_IN_ExtSRAM
  static void SystemInit_ExtMemCtl(void); 
#endif /* DATA_IN_ExtSRAM */
#endif /* STM32F100xE || STM32F101xE || STM32F101xG || STM32F103xE || STM32F103xG */


/**
 * @brief  设置微控制器系统
 *         初始化内置的 Flash 接口，PLL 和 更新 SystemCoreClock 变量
 * @note   这个函数只能在复位后使用
 * @param  无
 * @retval 无
*/
void SystemInit (void)
{
#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
  #ifdef DATA_IN_ExtSRAM
    SystemInit_ExtMemCtl(); 
  #endif /* DATA_IN_ExtSRAM */
#endif 

/* ------------------------------ 配置向量表位置 ------------------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* 向量表重定位到内部 SRAM */
#endif /* USER_VECT_TAB_ADDRESS */
}




/**
 * @brief  根据时钟寄存器的值更新 SystemCoreClock 变量，这个变量包含了内核时钟 (HCLK)
 *         它可以被用于用户程序来设置系统嘀嗒定时器或设置其他参数
 * 
 * @note   每当内核时钟 (HCLK) 改变，这个函数必须被调用以更新 SystemCoreClock 变量值
 *         此外，任何基于此变量的配置都是不正确的
 * 
 * @note   - 通过这个函数计算的系统频率不是芯片内部的真实频率，它是基于先前定义的常数和
 *           选择的时钟源计算出来的：
 *           - 如果 SYSCLK 时钟源是 HSI，SystemCoreClock 将包含 HSI_VALUE(*)
 *           - 如果 SYSCLK 时钟源是 HSE，SystemCoreClock 将包含 HSE_VALUE(**)
 *           - 如果 SYSCLK 时钟源是 PLL，SystemCoreClock 将包含 HSE_VALUE(**) 或  
 *             HSI_VALUE(*) 乘 PLL 倍频因子的倍数
 * 
 *         (*) HSI_VALUE 是一个定义在 stm32f1xx.h 文件中的常数（默认值为 8 MHz）
 *             但是实际值会随电压和温度的变化而变化
 *         (**) HSE_VALUE 是一个定义在 stm32f1xx.h 文件中的常数（默认值为 8 MHz 或 根据产品使用的晶振）
 *              用户必须确保 HSE_VALUE 和用的晶振频率一致，否则这个函数会有错误的结果
 *         - 当使用 HSE 晶体的分数值时，该函数的结果可能不正确
 * @param  无
 * @retval 无
*/
void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0U, pllmull = 0U, pllsource = 0U;

#if defined(STM32F105xC) || defined(STM32F107xC)
  uint32_t prediv1source = 0U, prediv1factor = 0U, prediv2factor = 0U, pll2mull = 0U;
#endif /* STM32F105xC */

#if defined(STM32F100xB) || defined(STM32F100xE)
  uint32_t prediv1factor = 0U;
#endif /* STM32F100xB or STM32F100xE */
    
  /* 获取系统时钟源 -----------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  /**
   * SWS = RCC->CFGR[3:2]: 系统时钟切换状态
   * 00: HSI 作为系统时钟
   * 01: HSE 作为系统时钟
   * 10: PLL 输出作为系统时钟
  */

  switch (tmp)
  {
    case 0x00U:  /* HSI 作为系统时钟 */
      SystemCoreClock = HSI_VALUE;
      break;
    case 0x04U:  /* HSE 作为系统时钟 */
      SystemCoreClock = HSE_VALUE;
      break;
    case 0x08U:  /* PLL 作为系统时钟 */

      /* 获取 PLL 时钟源和倍频系数 ---------------------------------------------*/
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;       /* PLLMUL = RCC->CFGR[21:18] PLL 倍频系数 */
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;      /* PLLSRC = RCC->CFGR[16] 输入时钟源 */
      
#if !defined(STM32F105xC) && !defined(STM32F107xC)  // 非互联型
      pllmull = (pllmull >> 18U) + 2U;              // 计算倍频系数
      
      if (pllsource == 0x00U)                       // 如果 PLL 时钟源是 HSI 二分频
      {
        /* HSI 振荡器时钟经2分频后作为 PLL 输入时钟 */
        SystemCoreClock = (HSI_VALUE >> 1U) * pllmull;
      }
      else
      {
  #if defined(STM32F100xB) || defined(STM32F100xE)  // STM32F100 超值系列的 HSE 有一个预分频器
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1U;
        /* HSE 振荡器时钟作为 PREDIV1 输入时钟 */
        SystemCoreClock = (HSE_VALUE / prediv1factor) * pllmull; 
  #else
        if ((RCC->CFGR & RCC_CFGR_PLLXTPRE) != (uint32_t)RESET)
        {/* HSE 2分频后作为 PLL 输入时钟 */
          SystemCoreClock = (HSE_VALUE >> 1U) * pllmull;
        }
        else
        {/* HSE 作为 PLL 输入时钟 */
          SystemCoreClock = HSE_VALUE * pllmull;
        }
  #endif
      }
#else // 互联型
      pllmull = pllmull >> 18U;
      
      if (pllmull != 0x0DU)
      {
        pllmull += 2U;
      }
      else
      { /* PLL 倍频系数为 = PLL 输入时钟 * 6.5 */
        pllmull = 13U / 2U; 
      }
            
      if (pllsource == 0x00U)
      {
        /* HSI 振荡器时钟经2分频后作为 PLL 输入时钟 */
        SystemCoreClock = (HSI_VALUE >> 1U) * pllmull;
      }
      else
      {/* PREDIV1 输出作为 PLL 输入时钟 */
        
        /* 获取 PREDIV1 时钟源 和 分频因子 */
        prediv1source = RCC->CFGR2 & RCC_CFGR2_PREDIV1SRC;
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1U;
        
        if (prediv1source == 0U)
        { 
          /* HSE 振荡器时钟作为 PREDIV1 的时钟源 */
          SystemCoreClock = (HSE_VALUE / prediv1factor) * pllmull;          
        }
        else
        {/* PLL2 作为 PREDIV1 的时钟源 */
          
          /* 获取 PREDIV2 分频因子 和 PLL2 倍频系数 */
          prediv2factor = ((RCC->CFGR2 & RCC_CFGR2_PREDIV2) >> 4U) + 1U;
          pll2mull = ((RCC->CFGR2 & RCC_CFGR2_PLL2MUL) >> 8U) + 2U; 
          SystemCoreClock = (((HSE_VALUE / prediv2factor) * pll2mull) / prediv1factor) * pllmull;                         
        }
      }
#endif /* STM32F105xC */ 
      break;

    /* 默认的系统时钟是 HSI 8MHz */
    default:
      SystemCoreClock = HSI_VALUE;
      break;
  }
  
  /* 计算 HCLK 时钟频率 ----------------*/
  /* 获取 HCLK 预分频值 */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4U)];
  /* HCLK 时钟频率 */
  SystemCoreClock >>= tmp;  
}




#if defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F101xG) || defined(STM32F103xE) || defined(STM32F103xG)
/**
  * @brief  设置外部内存控制器，于 __main 之前在 startup_stm32f1xx.s 中调用
  * @param  无
  * @retval 无
  */ 
#ifdef DATA_IN_ExtSRAM
/**
  * @brief  设置外部内存控制器
  *         在跳转到 main 函数之前于 startup_stm32f1xx_xx.s/.c 中调用
  *         这个函数配置挂载到 STM3210E-EVAL 开发板上的 外部SRAM
  *         这个 SRAM 将作为程序数据内存使用（包括堆栈区域）
  * @param  无
  * @retval 无
  */ 
void SystemInit_ExtMemCtl(void) 
{
  __IO uint32_t tmpreg;
  /* FSMC 存储块1 NOR/SRAM3 被用于 STM3210E-EVAL, 如果需要其他存储块则要调整寄存器地址 */

  /* 使能 FSMC 时钟 */
  RCC->AHBENR = 0x00000114U;

  /* RCC 外设时钟使能后的延迟 */
  tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_FSMCEN);
  
  /* 使能 GPIOD, GPIOE, GPIOF, GPIOG 时钟 */
  RCC->APB2ENR = 0x000001E0U;
  
  /* RCC 外设时钟使能后的延迟 */
  tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPDEN);

  (void)(tmpreg);
  
/* -----------  SRAM Data lines 数据线, NOE 输出使能, NWE 写使能 配置 ----------*/
/*------------  SRAM Address lines 地址线配置 ---------------------------------*/
/*------------  NOE 输出使能 和 NWE 写使能 配置 --------------------------------*/  
/*------------  NE3 输出片选配置 ----------------------------------------------*/
/*------------  NBL0 低字节使能, NBL1 高字节使能 配置 --------------------------*/
  
  GPIOD->CRL = 0x44BB44BBU;  
  GPIOD->CRH = 0xBBBBBBBBU;

  GPIOE->CRL = 0xB44444BBU;  
  GPIOE->CRH = 0xBBBBBBBBU;

  GPIOF->CRL = 0x44BBBBBBU;  
  GPIOF->CRH = 0xBBBB4444U;

  GPIOG->CRL = 0x44BBBBBBU;  
  GPIOG->CRH = 0x444B4B44U;

/*----------------  FSMC Configuration ---------------------------------------*/  
/*----------------  Enable FSMC Bank1_SRAM Bank ------------------------------*/
  
  FSMC_Bank1->BTCR[4U] = 0x00001091U;
  FSMC_Bank1->BTCR[5U] = 0x00110212U;
}
#endif /* DATA_IN_ExtSRAM */
#endif /* STM32F100xE || STM32F101xE || STM32F101xG || STM32F103xE || STM32F103xG */