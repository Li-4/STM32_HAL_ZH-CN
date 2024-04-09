# Drivers

该文件夹下存放驱动层代码

## 目录结构

```
Drivers/
| -- BSP/                   存放开发板板级支持包驱动代码（Board Support Packet）如：LED、BEEP、KEY、IIC、SPI、TIMER、WDG...等
| -- CMSIS/                 存放 ARM 提供的 CMSIS 代码（主要包括各种头文件和启动文件，为了方便使用以及减少占用空间，只保留了必要的文件）
     | -- Device/ST/STM32F1xx/     
          | -- Include/             外设访问层头文件 包含所有的外设寄存器定义、一些宏定义和头文件包含、以及外设访问层系统的头文件
               | -- stm32f1xx.h         外设访问层头文件：包含一些宏定义，用于指定设备和包含 HAL 库等
               | -- stm32f103xe.h       外设访问层头文件：包含 STM32F1xx 设置的所有 外设寄存器定义、位定义 和 内存映射
               | -- system_stm32f1xx.h  外设访问层系统头文件：包含两个函数声明
          | -- Source/Templates/    包含启动文件 和 系统初始化、更新时钟变量的源文件
               | -- arm/startup_stm32f103xe.s   启动文件
               | -- system_stm32f1xx.c          外设访问层系统的源文件：包含一个核心时钟 HCLK 的全局变量 和 两个函数定义用于系统初始化时钟和更新核心时钟全局变量
     | -- Include/                  编译器、CMSIS 版本、以及内核相关的头文件
          | -- cmsis_armcc.h            Arm Compiler 5 头文件
          | -- cmsis_armclang.h         Arm Compiler 6 头文件
          | -- cmsis_compiler.h         编译器通用头文件
          | -- cmsis_version.h          CMSIS Core(M) 版本定义
          | -- core_cm3.h               CMSIS 内核外设访问层头文件 包含 NVIC SCB SysTick 等
          | -- mpu_armv7.h              Armv7-M 架构的 MPU(Memory Protection Unit) 内存保护单元头文件
| -- STM32F1xx_HAL_Driver/  存放 ST 提供的 F1xx HAL 库驱动代码
| -- SYSTEM/                存放系统级核心驱动代码，如 delay.c 等
```