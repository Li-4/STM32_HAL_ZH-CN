;******************** (C) COPYRIGHT 2017 STMicroelectronics ********************
;* File Name          : startup_stm32f100xe.s
;* Author             : github.com/Li-4
;* Description        : STM32F100xE 设备的 MDK-ARM 工具链的中断向量表
;*                      该模块执行以下操作：
;*                      - 设置初始 SP 栈顶指针
;*                      - 设置初始程序计数器指向复位处理程序 PC = Reset_Handler
;*                      - 设置具有异常 中断服务程序(ISR-Interrupt Service Routine) 的中断向量表条目
;*                      - （可选项，需要用户使能）配置时钟系统 并且 
;*                        配置挂载在 STM32100E-EVAL 开发板的外部 SRAM 作为数据内存使用
;*                      - 跳转分支到 C 库中的 __main 函数（最终调用 main()） 
;*                      复位后 Cortex-M3 处理器处于线程模式，优先级为特权级，并且堆栈被设置为主堆栈
;*******************************************************************************

; 分配给栈的内存数量（以字节为单位）
; 根据你的应用需求来调整该值
; <h> 栈配置
;   <o> 栈大小（以字节为单位）<0x0-0xFFFFFFFF:8> :8 表示以 8 为步长增加
; </h>

Stack_Size      EQU     0x00000400                          ; 定义栈大小为 0x400B(1KB) 并命名为 Stack_Size

                AREA    STACK, NOINIT, READWRITE, ALIGN=3   ; AREA 定义一个可读写的段，段名为 STACK，不初始化，以 2^3 8 字节对齐
Stack_Mem       SPACE   Stack_Size                          ; SPACE 分配大小为 Stack_Size 字节连续的存储单元给栈空间，并命名栈内存起始位置的符号为 Stack_Mem
__initial_sp                                                ; __initial_sp 是栈空间的结束地址，ARM 使用的是满减栈：栈指针指向最后压入栈的数据，栈由高地址向低地址生长


; <h> 堆配置
;   <o> 堆大小（以字节为单位）<0x0-0xFFFFFFFF:8> :8 表示以 8 为步长增加
; </h>

Heap_Size       EQU     0x00000200                          ; 定义堆大小为 0x200B(512B) 并命名为 Heap_Size

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3    ; AREA 定义一个可读写的段，段名为 HEAP，不初始化，以 2^3 8 字节对齐
__heap_base                                                 ; __heap_base 表示堆的起始地址
Heap_Mem        SPACE   Heap_Size                           ; SPACE 分配大小为 Heap_Size 字节连续的存储单元给堆空间，并命名堆内存起始位置的符号为 Heap_Mem
__heap_limit                                                ; __heap_limit 表示堆的结束地址，ARM 堆由低向高生长

                PRESERVE8                                   ; 指示编译器在生成代码时按照 8 字节对齐生成栈帧
                THUMB                                       ; 指示编译器之后的指令兼容 THUMB 指令


; 复位时映射中断向量表到 0 地址
                AREA    RESET, DATA, READONLY           ; AREA 定义一个只读的数据段，段名为 RESET
                EXPORT  __Vectors                       ; 导出 __Vectors 标号    EXPORT 声明一个标号具有全局属性，可被外部文件使用
                EXPORT  __Vectors_End                   ; 导出 __Vectors_End 标号
                EXPORT  __Vectors_Size                  ; 导出 __Vectors_Size 标号

; __Vectors 为中断向量表起始地址 __Vectors_End 为向量表结束地址
; DCD 定义一个或多个双字（4 字节）的数据，并初始化这些内存
__Vectors       DCD     __initial_sp                    ; Top of Stack 栈顶地址
                DCD     Reset_Handler                   ; Reset Handler 复位处理程序
                DCD     NMI_Handler                     ; NMI(Non-Maskable Interrupt) 不可屏蔽中断处理程序
                DCD     HardFault_Handler               ; Hard Fault Handler 硬件错误处理程序
                DCD     MemManage_Handler               ; MPU Fault Handler 内存保护单元错误处理程序
                DCD     BusFault_Handler                ; Bus Fault Handler 总线错误处理程序
                DCD     UsageFault_Handler              ; Usage Fault Handler 用法错误处理程序
                DCD     0                               ; Reserved 保留
                DCD     0                               ; Reserved 保留
                DCD     0                               ; Reserved 保留
                DCD     0                               ; Reserved 保留
                DCD     SVC_Handler                     ; SVCall Handler 特权级别切换中断处理程序
                DCD     DebugMon_Handler                ; Debug Monitor Handler 程序监控器中断处理程序
                DCD     0                               ; Reserved 保留
                DCD     PendSV_Handler                  ; PendSV Handler 待处理监控中断处理程序
                DCD     SysTick_Handler                 ; SysTick Handler 系统嘀嗒定时器中断处理程序

                ; 外部中断
                DCD     WWDG_IRQHandler                 ; Window Watchdog 窗口看门狗
                DCD     PVD_IRQHandler                  ; PVD through EXTI Line detect 通过外部中断线监控电压监视器
                DCD     TAMPER_IRQHandler               ; Tamper 侵入检测
                DCD     RTC_IRQHandler                  ; RTC 实时时钟
                DCD     FLASH_IRQHandler                ; Flash 闪存
                DCD     RCC_IRQHandler                  ; RCC 复位和时钟控制 
                DCD     EXTI0_IRQHandler                ; EXTI Line 0 外部中断线 0
                DCD     EXTI1_IRQHandler                ; EXTI Line 1 外部中断线 1
                DCD     EXTI2_IRQHandler                ; EXTI Line 2 外部中断线 2
                DCD     EXTI3_IRQHandler                ; EXTI Line 3 外部中断线 3
                DCD     EXTI4_IRQHandler                ; EXTI Line 4 外部中断线 4
                DCD     DMA1_Channel1_IRQHandler        ; DMA1 Channel 1 DMA1 通道 1
                DCD     DMA1_Channel2_IRQHandler        ; DMA1 Channel 2 DMA1 通道 2
                DCD     DMA1_Channel3_IRQHandler        ; DMA1 Channel 3 DMA1 通道 3
                DCD     DMA1_Channel4_IRQHandler        ; DMA1 Channel 4 DMA1 通道 4
                DCD     DMA1_Channel5_IRQHandler        ; DMA1 Channel 5 DMA1 通道 5
                DCD     DMA1_Channel6_IRQHandler        ; DMA1 Channel 6 DMA1 通道 6
                DCD     DMA1_Channel7_IRQHandler        ; DMA1 Channel 7 DMA1 通道 7
                DCD     ADC1_IRQHandler                 ; ADC1 模数转换
                DCD     0                               ; Reserved 保留
                DCD     0                               ; Reserved 保留
                DCD     0                               ; Reserved 保留
                DCD     0                               ; Reserved 保留
                DCD     EXTI9_5_IRQHandler              ; EXTI Line 9..5 外部中断线 5_9
                DCD     TIM1_BRK_TIM15_IRQHandler       ; TIM1 Break and TIM15 TIM1 刹车 和 TIM15
                DCD     TIM1_UP_TIM16_IRQHandler        ; TIM1 Update and TIM16 TIM1 更新 和 TIM16
                DCD     TIM1_TRG_COM_TIM17_IRQHandler   ; TIM1 Trigger and Commutation and TIM17 TIM1 触发和换相 和 TIM17
                DCD     TIM1_CC_IRQHandler              ; TIM1 Capture Compare TIM1 捕获比较
                DCD     TIM2_IRQHandler                 ; TIM2 定时器2
                DCD     TIM3_IRQHandler                 ; TIM3 定时器3
                DCD     TIM4_IRQHandler                 ; TIM4 定时器4
                DCD     I2C1_EV_IRQHandler              ; I2C1 Event I2C1 事件
                DCD     I2C1_ER_IRQHandler              ; I2C1 Error I2C1 错误
                DCD     I2C2_EV_IRQHandler              ; I2C2 Event I2C2 事件
                DCD     I2C2_ER_IRQHandler              ; I2C2 Error I2C2 错误
                DCD     SPI1_IRQHandler                 ; SPI1 串行外设接口1
                DCD     SPI2_IRQHandler                 ; SPI2 串行外设接口2
                DCD     USART1_IRQHandler               ; USART1 通用同步/异步收发器1
                DCD     USART2_IRQHandler               ; USART2 通用同步/异步收发器2
                DCD     USART3_IRQHandler               ; USART3 通用同步/异步收发器3
                DCD     EXTI15_10_IRQHandler            ; EXTI Line 15..10 外部中断线 10_15
                DCD     RTC_Alarm_IRQHandler            ; RTC Alarm through EXTI Line 通过外部中断线的 RTC 闹钟
                DCD     CEC_IRQHandler                  ; HDMI CEC
                DCD     TIM12_IRQHandler                ; TIM12 定时器12
                DCD     TIM13_IRQHandler                ; TIM13 定时器13
                DCD     TIM14_IRQHandler                ; TIM14 定时器14
                DCD     0                               ; Reserved 保留
                DCD     0                               ; Reserved 保留
                DCD     0                               ; Reserved 保留
                DCD     0                               ; Reserved 保留
                DCD     TIM5_IRQHandler                 ; TIM5 定时器5
                DCD     SPI3_IRQHandler                 ; SPI3 串行外设接口3
                DCD     UART4_IRQHandler                ; UART4 通用异步收发器4
                DCD     UART5_IRQHandler                ; UART5 通用异步收发器5
                DCD     TIM6_DAC_IRQHandler             ; TIM6 and DAC underrun TIM6 和 DAC 缓冲区不足
                DCD     TIM7_IRQHandler                 ; TIM7 定时器7
                DCD     DMA2_Channel1_IRQHandler        ; DMA2 Channel1 DMA2 通道 1
                DCD     DMA2_Channel2_IRQHandler        ; DMA2 Channel2 DMA2 通道 2
                DCD     DMA2_Channel3_IRQHandler        ; DMA2 Channel3 DMA2 通道 3
                DCD     DMA2_Channel4_5_IRQHandler      ; DMA2 Channel4 & Channel5 DMA2 通道 4&5
                DCD     DMA2_Channel5_IRQHandler        ; DMA2 Channel5 DMA2 通道 4
__Vectors_End

; __Vectors_Size 表示向量表大小
__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY         ;  AREA 定义一个只读的代码段，段名为 .text

; 复位处理程序
Reset_Handler   PROC                                    ; 定义一个名为 Reset_Handler 的函数
                EXPORT  Reset_Handler             [WEAK]; 声明 Reset_Handler 为全局属性，[WEAK] 表示弱定义 如果外部文件优先定义了该标号则首先引用外部定义的标号
    IMPORT  __main                                      ; 引入外部的 __main 标号
    IMPORT  SystemInit                                  ; 引入外部的 SystemInit 标号 其在 system)stm32f1xx.c 中定义
                LDR     R0, =SystemInit                 ; 把 SystemInit 标号的地址存入 R0
                BLX     R0                              ; 跳转到 R0 执行，并将下一条指令的地址存放到 LR 中
                LDR     R0, =__main                     ; 把 __main 标号的地址存入 R0
                BX      R0                              ; 跳转到 R0 执行
                ENDP                                    ; 函数结束

; 虚拟的异常处理程序（无限循环可修改）

NMI_Handler     PROC                                            ; 定义一个名为 NMI_Handler 的函数
                EXPORT  NMI_Handler                      [WEAK] ; 声明 NMI_Handler 为全局属性，[WEAK] 表示弱定义
                B       .                                       ; 跳转分支到当前标号，也就是无限循环
                ENDP                                            ; 函数结束
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                 [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler               [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                      [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                 [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                   [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                  [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler                  [WEAK]
                EXPORT  PVD_IRQHandler                   [WEAK]
                EXPORT  TAMPER_IRQHandler                [WEAK]
                EXPORT  RTC_IRQHandler                   [WEAK]
                EXPORT  FLASH_IRQHandler                 [WEAK]
                EXPORT  RCC_IRQHandler                   [WEAK]
                EXPORT  EXTI0_IRQHandler                 [WEAK]
                EXPORT  EXTI1_IRQHandler                 [WEAK]
                EXPORT  EXTI2_IRQHandler                 [WEAK]
                EXPORT  EXTI3_IRQHandler                 [WEAK]
                EXPORT  EXTI4_IRQHandler                 [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler         [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler         [WEAK]
                EXPORT  ADC1_IRQHandler                  [WEAK]
                EXPORT  EXTI9_5_IRQHandler               [WEAK]
                EXPORT  TIM1_BRK_TIM15_IRQHandler        [WEAK]
                EXPORT  TIM1_UP_TIM16_IRQHandler         [WEAK]
                EXPORT  TIM1_TRG_COM_TIM17_IRQHandler    [WEAK]
                EXPORT  TIM1_CC_IRQHandler               [WEAK]
                EXPORT  TIM2_IRQHandler                  [WEAK]
                EXPORT  TIM3_IRQHandler                  [WEAK]
                EXPORT  TIM4_IRQHandler                  [WEAK]
                EXPORT  I2C1_EV_IRQHandler               [WEAK]
                EXPORT  I2C1_ER_IRQHandler               [WEAK]
                EXPORT  I2C2_EV_IRQHandler               [WEAK]
                EXPORT  I2C2_ER_IRQHandler               [WEAK]
                EXPORT  SPI1_IRQHandler                  [WEAK]
                EXPORT  SPI2_IRQHandler                  [WEAK]
                EXPORT  USART1_IRQHandler                [WEAK]
                EXPORT  USART2_IRQHandler                [WEAK]
                EXPORT  USART3_IRQHandler                [WEAK]
                EXPORT  EXTI15_10_IRQHandler             [WEAK]
                EXPORT  RTC_Alarm_IRQHandler             [WEAK]
                EXPORT  CEC_IRQHandler                   [WEAK]
                EXPORT  TIM12_IRQHandler                 [WEAK]
                EXPORT  TIM13_IRQHandler                 [WEAK]
                EXPORT  TIM14_IRQHandler                 [WEAK]
                EXPORT  TIM5_IRQHandler                  [WEAK]
                EXPORT  SPI3_IRQHandler                  [WEAK]
                EXPORT  UART4_IRQHandler                 [WEAK]
                EXPORT  UART5_IRQHandler                 [WEAK]
                EXPORT  TIM6_DAC_IRQHandler              [WEAK]
                EXPORT  TIM7_IRQHandler                  [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler         [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler         [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler         [WEAK]
                EXPORT  DMA2_Channel4_5_IRQHandler       [WEAK]
                EXPORT  DMA2_Channel5_IRQHandler         [WEAK]

WWDG_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_TIM15_IRQHandler
TIM1_UP_TIM16_IRQHandler
TIM1_TRG_COM_TIM17_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTC_Alarm_IRQHandler
CEC_IRQHandler
TIM12_IRQHandler
TIM13_IRQHandler
TIM14_IRQHandler
TIM5_IRQHandler
SPI3_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
TIM6_DAC_IRQHandler
TIM7_IRQHandler
DMA2_Channel1_IRQHandler
DMA2_Channel2_IRQHandler
DMA2_Channel3_IRQHandler
DMA2_Channel4_5_IRQHandler
DMA2_Channel5_IRQHandler
                B       .

                ENDP

                ALIGN               ; ALIGN 表示四字节对齐

;*******************************************************************************
;                               用户堆栈初始化
;*******************************************************************************
                IF      :DEF:__MICROLIB                 ; 判断是否定义了 __MICROLIB，MICROLIB 是默认 C 库的备选库，没有源码
                
                EXPORT  __initial_sp                    ; 声明 __initial_sp 栈顶指针 具有全局属性
                EXPORT  __heap_base                     ; 声明 __heap_base 堆起始地址 具有全局属性
                EXPORT  __heap_limit                    ; 声明 __heap_limit 堆结束地址 具有全局属性
                
                ELSE                                    ; 如果没有定义 __MICROLIB
                
                IMPORT  __use_two_region_memory         ; 引入 __use_two_region_memory 使用双区内存
                EXPORT  __user_initial_stackheap        ; 声明 __user_initial_stackheap 具有全局属性
                
__user_initial_stackheap

                LDR     R0, = Heap_Mem                  ; 保存堆起始地址到 R0
                LDR     R1, = (Stack_Mem + Stack_Size)  ; 保存栈结束地址到 R1
                LDR     R2, = (Heap_Mem +  Heap_Size)   ; 保存堆结束地址到 R2
                LDR     R3, = Stack_Mem                 ; 保存栈起始地址到 R3
                BX      LR                              ; 相当于 return

                ALIGN                                   ; 以四字节对齐

                ENDIF

                END                                     ; END 表示到达文件末尾