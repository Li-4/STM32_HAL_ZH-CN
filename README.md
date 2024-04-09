# HAL Template STM32 HAL库工程模版  

目录结构参照了正点原子，但是想在内容上更加贴近 CubeMX 生成的代码

纯 Template 目录，不会包含任何的项目相关文件

## 目录结构  

```
Template/
| -- Drivers/                 存放与硬件相关的驱动层文件
     | -- BSP/                     存放开发板板级支持包驱动代码（Board Support Packet）
     | -- CMSIS /                  存放 CMSIS 底层代码，如启动文件（.s 文件）等
     | -- STM32F1xx_HAL_Driver/    存放 ST 提供的 F1xx HAL 库驱动代码
     | -- SYSTEM/                  存放系统级核心驱动代码，如 delay.c 等
| -- Middlewares/             存放中间层组件文件和第三方中间层文件
| -- Output/                  存放工程编译输出文件
| -- Projects/                存放 MDK 工程文件
| -- User/                    存放 HAL 库用户配置文件、main.c、stm32f1xx_it.c，以及自己编写的应用程序
| -- README.md
```