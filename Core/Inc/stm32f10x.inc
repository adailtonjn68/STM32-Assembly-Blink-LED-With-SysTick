.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.include "stm32f10x_constants.inc"
.include "stm32f10x_gpio.inc"
.include "stm32f10x_rcc.inc"
.include "stm32f10x_exti.inc"

.ifndef		STM32F10X_INC_
.equ		STM32F10X_INC_, 1

.equ __CM3_REV,				(0x0200)		@ Core revision r2p0
.equ __MPU_PRESENT,			(0x00)			@ Other STM32 devices do not provide MPU
.equ __NVIC_PRIO_BITS,		(0x04)			@ STM32 uses 4 bits for the priority levels
.equ __Vendor_SysTickConfig,(0x00)			@ Set to 1 if different SysTick Config is used


@*********************************************************
@************** Interrupt number definition **************
@*********************************************************

@ Cortex-M3
.equ NonMaskableInt_IRQn,	(-14)
.equ HardFault_IRQn,		(-13)
.equ MemoryManagement_IRQn,	(-12)
.equ BusFault_IRQn,			(-11)
.equ UsageFault_IRQn,		(-10)
.equ SVCall_IRQn,			(-5)
.equ DebugMonitor_IRQn,		(-4)
.equ PenSV_IRQn,			(-2)
.equ SysTick_IRQn,			(-1)
@ STM32 specific
.equ WWDG_IRQn,				(0)
.equ PVD_IRQn,				(1)
.equ TAMPER_IRQn,			(2)
.equ RTC_IRQn,				(3)
.equ FLASH_IRQn,			(4)
.equ RCC_IRQn,				(5)

@*********************************************************
@********* Preemption Priority Group *********************
@*********************************************************
.equ NVIC_PRIORITYGROUP_0,	(0x7)		@ 0 bits for pre-emption priority; 4 bits for subpriority
.equ NVIC_PRIORITYGROUP_1,	(0x6)		@ 1 bits for pre-emption priority; 3 bits for subpriority
.equ NVIC_PRIORITYGROUP_2,	(0x5)		@ 2 bits for pre-emption priority; 2 bits for subpriority
.equ NVIC_PRIORITYGROUP_3,	(0x4)		@ 3 bits for pre-emption priority; 1 bits for subpriority
.equ NVIC_PRIORITYGROUP_4,	(0x3)		@ 4 bits for pre-emption priority; 0 bits for subpriority

@*********************************************************
@******************** Define bases ***********************
@*********************************************************

@ Core hardware
.equ SCS_BASE,				(0xE000E000)	@ Sytem Control Space Base Address
.equ ITM_BASE,				(0xE0000000)	@ ITM base address
.equ DWT_BASE,				(0xE0001000)
.equ TPI_BASE,				(0xE0040000)
.equ CoreDebug_BASE,		(0xE000EDF0)
.equ SysTick_BASE,			(SCS_BASE + 0x0010)
.equ NVIC_BASE,				(SCS_BASE + 0x0100)
.equ SCB_BASE,				(SCS_BASE + 0x0D00)	@ System Control Block base address


.equ PERIPH_BASE,           (0x40000000)

@ Bus: AHB
.equ FLASH_BASE,            (0x40022000)
.equ RCC_BASE,              (0x40021000)
.equ DMA2_BASE,             (0x40020400)
.equ DMA1_BASE,             (0x40020000)
.equ SDIO_BASE,             (0x40018000)
@ Bus: APB2
.equ TIM11_BASE,            (0x40015400)
.equ TIM10_BASE,            (0x40015000)
.equ TIM9_BASE,             (0x40014C00)
.equ ADC3_BASE,             (0x40013C00)
.equ USART1_BASE,           (0x40013800)
.equ TIM8_BASE,             (0x40013400)
.equ SPI1_BASE,             (0x40013000)
.equ TIM1_BASE,             (0x40012800)
.equ ADC2_BASE,             (0x40012800)
.equ ADC1_BASE,             (0x40012400)
.equ GPIOG_BASE,            (0x40012000)
.equ GPIOF_BASE,            (0x40011C00)
.equ GPIOE_BASE,            (0x40011800)
.equ GPIOD_BASE,            (0x40011400)
.equ GPIOC_BASE,            (0x40011000)
.equ GPIOB_BASE,            (0x40010C00)
.equ GPIOA_BASE,            (0x40010800)
.equ EXTI_BASE,             (0x40010400)
.equ AFIO_BASE,             (0x40010000)
@ Bus: APB1
.equ DAC_BASE,              (0x40007400)
.equ PWR_BASE,              (0x40007000)
.equ BKP_BASE,              (0x40006C00)
.equ bxCAN1_BASE,           (0x40006400)
.equ bxCAN2_BASE,           (0x40006800)
.equ SharedUSBCANSRAM_BASE, (0x40006000)
.equ I2C2_BASE,             (0x40005800)
.equ I2C1_BASE,             (0x40005400)
.equ UART5_BASE,            (0x40005000)
.equ UART4_BASE,            (0x40004C00)
.equ USART3_BASE,           (0x40004800)
.equ USART2_BASE,           (0x40004400)
.equ SPI3_BASE,             (0x40003C00)
.equ SPI2_BASE,             (0x40003800)
.equ IWDG_BASE,             (0x40003000)
.equ WWDG_BASE,             (0x40002C00)
.equ RTC_BASE,              (0x40002800)
.equ TIM14_BASE,            (0x40002000)
.equ TIM13_BASE,            (0x40001C00)
.equ TIM12_BASE,            (0x40001800)
.equ TIM7_BASE,             (0x40001400)
.equ TIM6_BASE,             (0x40001000)
.equ TIM5_BASE,             (0x40000C00)
.equ TIM4_BASE,             (0x40000800)
.equ TIM3_BASE,             (0x40000400)
.equ TIM2_BASE,             (0x40000000)



@*********************************************************
@***************** Register addresses ********************
@*********************************************************

.equ SCB_CPUID,				(SCB_BASE + 0x00)	@ (R/ ) CPUID base register
.equ SCB_ICSR,				(SCB_BASE + 0x04)	@ (R/W) Interrupt Control and State register
.equ SCB_VTOR,				(SCB_BASE + 0x08)	@ (R/W) Vector Table Offset register
.equ SCB_AIRCR,				(SCB_BASE + 0x0C)	@ (R/W) Application Interrrupt and Reset register
.equ SCB_SCR,				(SCB_BASE + 0x10)	@ (R/W) System Control register
.equ SCB_CCR,				(SCB_BASE + 0x14)	@ (R/W) Configuration Control register
.equ SCB_SHP_BASE,			(SCB_BASE + 0x18)	@ (R/W) System Handlers Priority registers
.equ SCB_SHCSR,				(SCB_BASE + 0x24)	@ (R/W) System Handler Control and State register
.equ SCB_CFSR,				(SCB_BASE + 0x28)	@ (R/W) Configurable Fault Status register
.equ SCB_HFSR,				(SCB_BASE + 0x2C)	@ (R/W) HardFault Status register
.equ SCB_DFSR,				(SCB_BASE + 0x30)	@ (R/W) Debug Fault Status register
.equ SCB_MMFAR,				(SCB_BASE + 0x34)	@ (R/W) MemManage Fault address register
.equ SCB_BFAR,				(SCB_BASE + 0x38)	@ (R/W) BusFault address register
.equ SCB_AFSR,				(SCB_BASE + 0x3C)	@ (R/W) Auxiliary Fault Status register
.equ SCB_PFR_BASE,			(SCB_BASE + 0x40)	@ (R/ ) Processor Feature register
.equ SCB_DFR,				(SCB_BASE + 0x48)	@ (R/ ) Debug Feature register
.equ SCB_ADR,				(SCB_BASE + 0x4C)	@ (R/ ) Auxiliary Feature register
.equ SCB_MMFR_BASE,			(SCB_BASE + 0x50)	@ (R/ ) Memory Model Feature register
.equ SCB_ISAR_BASE,			(SCB_BASE + 0x60)	@ (R/ ) Instruction Set Attributes register
.equ SCB_CPACR,				(SCB_BASE + 0x88)	@ (R/ ) Coprocessor Access Control Register

.equ SCB_SHP_SysTick_IRQn,	(SCB_SHP_BASE + ((SysTick_IRQn) & 0xF) - 4)

.equ SysTick_CTRL,			(SysTick_BASE + 0x00)
.equ SysTick_LOAD,			(SysTick_BASE + 0x04)
.equ SysTick_VAL,			(SysTick_BASE + 0x08)
.equ SysTick_CALIB,			(Systick_BASE + 0x0C)

.equ FLASH_ACR,				(FLASH_BASE + 0x00)

.equ CRC_DR,                (CRC_BASE + 0x00)
.equ CRC_IDR,               (CRC_BASE + 0x04)
.equ CRC_CR,                (CRC_BASE + 0x08)

.equ PWR_CR,                (PWR_BASE + 0x00)
.equ PWR_CSR,               (PWR_BASE + 0x04)

.equ BKP_DR1,               (BKP_BASE + 0x04)
.equ BKP_DR2,               (BKP_BASE + 0x08)
.equ BKP_DR3,               (BKP_BASE + 0x0C)
.equ BKP_DR4,               (BKP_BASE + 0x10)
.equ BKP_DR5,               (BKP_BASE + 0x14)
.equ BKP_DR6,               (BKP_BASE + 0x18)
.equ BKP_DR7,               (BKP_BASE + 0x1C)
.equ BKP_DR8,               (BKP_BASE + 0x20)
.equ BKP_DR9,               (BKP_BASE + 0x24)
.equ BKP_DR10,              (BKP_BASE + 0x28)
.equ BKP_RTCCR,             (BKP_BASE + 0x2C)
.equ BKP_CR,                (BKP_BASE + 0x30)
.equ BKP_CSR,               (BKP_BASE + 0x34)
.equ BKP_DR11,              (BKP_BASE + 0x40)
.equ BKP_DR12,              (BKP_BASE + 0x44)
.equ BKP_DR13,              (BKP_BASE + 0x48)
.equ BKP_DR14,              (BKP_BASE + 0x4C)
.equ BKP_DR15,              (BKP_BASE + 0x50)
.equ BKP_DR16,              (BKP_BASE + 0x54)
.equ BKP_DR17,              (BKP_BASE + 0x58)
.equ BKP_DR18,              (BKP_BASE + 0x5C)
.equ BKP_DR19,              (BKP_BASE + 0x60)
.equ BKP_DR20,              (BKP_BASE + 0x64)
.equ BKP_DR21,              (BKP_BASE + 0x68)
.equ BKP_DR22,              (BKP_BASE + 0x6C)
.equ BKP_DR23,              (BKP_BASE + 0x70)
.equ BKP_DR24,              (BKP_BASE + 0x74)
.equ BKP_DR25,              (BKP_BASE + 0x78)
.equ BKP_DR26,              (BKP_BASE + 0x7C)
.equ BKP_DR27,              (BKP_BASE + 0x80)
.equ BKP_DR28,              (BKP_BASE + 0x84)
.equ BKP_DR29,              (BKP_BASE + 0x88)
.equ BKP_DR30,              (BKP_BASE + 0x8C)
.equ BKP_DR31,              (BKP_BASE + 0x90)
.equ BKP_DR32,              (BKP_BASE + 0x94)
.equ BKP_DR33,              (BKP_BASE + 0x98)
.equ BKP_DR34,              (BKP_BASE + 0x9C)
.equ BKP_DR35,              (BKP_BASE + 0xA0)
.equ BKP_DR36,              (BKP_BASE + 0xA4)
.equ BKP_DR37,              (BKP_BASE + 0xA8)
.equ BKP_DR38,              (BKP_BASE + 0xAC)
.equ BKP_DR39,              (BKP_BASE + 0xB0)
.equ BKP_DR40,              (BKP_BASE + 0xB4)
.equ BKP_DR41,              (BKP_BASE + 0xB8)
.equ BKP_DR42,              (BKP_BASE + 0xBC)


.equ RCC_CR,                (RCC_BASE + 0x00)
.equ RCC_CFGR,              (RCC_BASE + 0x04)
.equ RCC_CIR,               (RCC_BASE + 0x08)
.equ RCC_APB2RSTR,          (RCC_BASE + 0x0C)
.equ RCC_APB1RSTR,          (RCC_BASE + 0x10)
.equ RCC_AHBENR,            (RCC_BASE + 0x14)
.equ RCC_APB2ENR,           (RCC_BASE + 0x18)
.equ RCC_APB1ENR,           (RCC_BASE + 0x1C)
.equ RCC_BDCR,              (RCC_BASE + 0x20)
.equ RCC_CSR,               (RCC_BASE + 0x24)


.equ GPIOC_CRL,             (GPIOC_BASE + 0x00)
.equ GPIOC_CRH,             (GPIOC_BASE + 0x04)
.equ GPIOC_IDR,             (GPIOC_BASE + 0x08)
.equ GPIOC_ODR,             (GPIOC_BASE + 0x0C)
.equ GPIOC_BSRR,            (GPIOC_BASE + 0x10)
.equ GPIOC_BRR,             (GPIOC_BASE + 0x14)
.equ GPIOC_LCKR,            (GPIOC_BASE + 0x18)

.equ GPIOB_CRL,             (GPIOB_BASE + 0x00)
.equ GPIOB_CRH,             (GPIOB_BASE + 0x04)
.equ GPIOB_IDR,             (GPIOB_BASE + 0x08)
.equ GPIOB_ODR,             (GPIOB_BASE + 0x0C)
.equ GPIOB_BSRR,            (GPIOB_BASE + 0x10)
.equ GPIOB_BRR,             (GPIOB_BASE + 0x14)
.equ GPIOB_LCKR,            (GPIOB_BASE + 0x18)

.equ GPIOA_CRL,             (GPIOA_BASE + 0x00)
.equ GPIOA_CRH,             (GPIOA_BASE + 0x04)
.equ GPIOA_IDR,             (GPIOA_BASE + 0x08)
.equ GPIOA_ODR,             (GPIOA_BASE + 0x0C)
.equ GPIOA_BSRR,            (GPIOA_BASE + 0x10)
.equ GPIOA_BRR,             (GPIOA_BASE + 0x14)
.equ GPIOA_LCKR,            (GPIOA_BASE + 0x18)

.equ AFIO_EVCR,             (AFIO_BASE + 0x00)
.equ AFIO_MAPR,             (AFIO_BASE + 0x04)
.equ AFIO_EXTICR1,          (AFIO_BASE + 0x08)
.equ AFIO_EXTICR2,          (AFIO_BASE + 0x0C)
.equ AFIO_EXTICR3,          (AFIO_BASE + 0x10)
.equ AFIO_EXTICR4,          (AFIO_BASE + 0x14)
.equ AFIO_MAPR2,            (AFIO_BASE + 0x1C)

.equ EXTI_IMR,              (EXTI_BASE + 0x00)
.equ EXTI_EMR,              (EXTI_BASE + 0x04)
.equ EXTI_RTSR,             (EXTI_BASE + 0x08)
.equ EXTI_FTSR,             (EXTI_BASE + 0x0C)
.equ EXTI_SWIER,            (EXTI_BASE + 0x10)
.equ EXTI_PR,               (EXTI_BASE + 0x14)

.equ ADC1_SR,               (ADC1_BASE + 0x00)
.equ ADC1_CR1,              (ADC1_BASE + 0x04)
.equ ADC1_CR2,              (ADC1_BASE + 0x08)
.equ ADC1_SMPR1,            (ADC1_BASE + 0x0C)
.equ ADC1_SMPR2,            (ADC1_BASE + 0x10)
.equ ADC1_JOFR1,            (ADC1_BASE + 0x14)
.equ ADC1_JOFR2,            (ADC1_BASE + 0x18)
.equ ADC1_JOFR3,            (ADC1_BASE + 0x1C)
.equ ADC1_JOFR4,            (ADC1_BASE + 0x20)
.equ ADC1_HTR,              (ADC1_BASE + 0x24)
.equ ADC1_LTR,              (ADC1_BASE + 0x28)
.equ ADC1_SQR1,             (ADC1_BASE + 0x2C)
.equ ADC1_SQR2,             (ADC1_BASE + 0x30)
.equ ADC1_SQR3,             (ADC1_BASE + 0x34)
.equ ADC1_JSQR,             (ADC1_BASE + 0x38)
.equ ADC1_JDR1,             (ADC1_BASE + 0x3C)
.equ ADC1_JDR2,             (ADC1_BASE + 0x40)
.equ ADC1_JDR3,             (ADC1_BASE + 0x44)
.equ ADC1_JDR4,             (ADC1_BASE + 0x48)
.equ ADC1_DR,               (ADC1_BASE + 0x4C)

.equ ADC2_SR,               (ADC2_BASE + 0x00)
.equ ADC2_CR1,              (ADC2_BASE + 0x04)
.equ ADC2_CR2,              (ADC2_BASE + 0x08)
.equ ADC2_SMPR1,            (ADC2_BASE + 0x0C)
.equ ADC2_SMPR2,            (ADC2_BASE + 0x10)
.equ ADC2_JOFR1,            (ADC2_BASE + 0x14)
.equ ADC2_JOFR2,            (ADC2_BASE + 0x18)
.equ ADC2_JOFR3,            (ADC2_BASE + 0x1C)
.equ ADC2_JOFR4,            (ADC2_BASE + 0x20)
.equ ADC2_HTR,              (ADC2_BASE + 0x24)
.equ ADC2_LTR,              (ADC2_BASE + 0x28)
.equ ADC2_SQR1,             (ADC2_BASE + 0x2C)
.equ ADC2_SQR2,             (ADC2_BASE + 0x30)
.equ ADC2_SQR3,             (ADC2_BASE + 0x34)
.equ ADC2_JSQR,             (ADC2_BASE + 0x38)
.equ ADC2_JDR1,             (ADC2_BASE + 0x3C)
.equ ADC2_JDR2,             (ADC2_BASE + 0x40)
.equ ADC2_JDR3,             (ADC2_BASE + 0x44)
.equ ADC2_JDR4,             (ADC2_BASE + 0x48)
.equ ADC2_DR,               (ADC2_BASE + 0x4C)

.equ ADC3_SR,               (ADC3_BASE + 0x00)
.equ ADC3_CR1,              (ADC3_BASE + 0x04)
.equ ADC3_CR2,              (ADC3_BASE + 0x08)
.equ ADC3_SMPR1,            (ADC3_BASE + 0x0C)
.equ ADC3_SMPR2,            (ADC3_BASE + 0x10)
.equ ADC3_JOFR1,            (ADC3_BASE + 0x14)
.equ ADC3_JOFR2,            (ADC3_BASE + 0x18)
.equ ADC3_JOFR3,            (ADC3_BASE + 0x1C)
.equ ADC3_JOFR4,            (ADC3_BASE + 0x20)
.equ ADC3_HTR,              (ADC3_BASE + 0x24)
.equ ADC3_LTR,              (ADC3_BASE + 0x28)
.equ ADC3_SQR1,             (ADC3_BASE + 0x2C)
.equ ADC3_SQR2,             (ADC3_BASE + 0x30)
.equ ADC3_SQR3,             (ADC3_BASE + 0x34)
.equ ADC3_JSQR,             (ADC3_BASE + 0x38)
.equ ADC3_JDR1,             (ADC3_BASE + 0x3C)
.equ ADC3_JDR2,             (ADC3_BASE + 0x40)
.equ ADC3_JDR3,             (ADC3_BASE + 0x44)
.equ ADC3_JDR4,             (ADC3_BASE + 0x48)
.equ ADC3_DR,               (ADC3_BASE + 0x4C)

.equ TIM1_CR1,              (TIM1_BASE + 0x00)
.equ TIM1_CR2,              (TIM1_BASE + 0x04)
.equ TIM1_SMCR,             (TIM1_BASE + 0x08)
.equ TIM1_DIER,             (TIM1_BASE + 0x0C)
.equ TIM1_SR,               (TIM1_BASE + 0x10)
.equ TIM1_EGR,              (TIM1_BASE + 0x14)
.equ TIM1_CCMR1,            (TIM1_BASE + 0x18)
.equ TIM1_CCMR2,            (TIM1_BASE + 0x1C)
.equ TIM1_CCER,             (TIM1_BASE + 0x20)
.equ TIM1_CNT,              (TIM1_BASE + 0x24)
.equ TIM1_PSC,              (TIM1_BASE + 0x28)
.equ TIM1_ARR,              (TIM1_BASE + 0x2C)
.equ TIM1_RCR,              (TIM1_BASE + 0x30)
.equ TIM1_CCR1,             (TIM1_BASE + 0x34)
.equ TIM1_CCR2,             (TIM1_BASE + 0x38)
.equ TIM1_CCR3,             (TIM1_BASE + 0x3C)
.equ TIM1_CCR4,             (TIM1_BASE + 0x40)
.equ TIM1_BDTR,             (TIM1_BASE + 0x44)
.equ TIM1_DCR,              (TIM1_BASE + 0x48)
.equ TIM1_DMAR,             (TIM1_BASE + 0x4C)

.equ TIM8_CR1,              (TIM8_BASE + 0x00)
.equ TIM8_CR2,              (TIM8_BASE + 0x04)
.equ TIM8_SMCR,             (TIM8_BASE + 0x08)
.equ TIM8_DIER,             (TIM8_BASE + 0x0C)
.equ TIM8_SR,               (TIM8_BASE + 0x10)
.equ TIM8_EGR,              (TIM8_BASE + 0x14)
.equ TIM8_CCMR1,            (TIM8_BASE + 0x18)
.equ TIM8_CCMR2,            (TIM8_BASE + 0x1C)
.equ TIM8_CCER,             (TIM8_BASE + 0x20)
.equ TIM8_CNT,              (TIM8_BASE + 0x24)
.equ TIM8_PSC,              (TIM8_BASE + 0x28)
.equ TIM8_ARR,              (TIM8_BASE + 0x2C)
.equ TIM8_RCR,              (TIM8_BASE + 0x30)
.equ TIM8_CCR1,             (TIM8_BASE + 0x34)
.equ TIM8_CCR2,             (TIM8_BASE + 0x38)
.equ TIM8_CCR3,             (TIM8_BASE + 0x3C)
.equ TIM8_CCR4,             (TIM8_BASE + 0x40)
.equ TIM8_BDTR,             (TIM8_BASE + 0x44)
.equ TIM8_DCR,              (TIM8_BASE + 0x48)
.equ TIM8_DMAR,             (TIM8_BASE + 0x4C)

@*********************************************************
@***************** Defining constants ********************
@*********************************************************

@ SysTick constants
.equ SysTick_CTRL_CLKSOURCE,(1 << 2)
.equ SysTick_CTRL_TICKINT,	(1 << 1)
.equ SysTick_CTRL_ENABLE,	(1 << 0)

@ FLASH constants
.equ FLASH_ACR_PRFTBS,		(BIT5)
.equ FLASH_ACR_PRFTBE,		(BIT4)
.equ FLASH_ACR_HLFCYA,		(BIT3)
.equ FLASH_ACR_LATENCY,		(BIT2 | BIT1 | BIT0)

.equ FLASH_ACR_LATENCY_0,	(BIT0)
.equ FLASH_ACR_LATENCY_1,	(BIT1)
.equ FLASH_ACR_LATENCY_2,	(BIT2)


.endif
