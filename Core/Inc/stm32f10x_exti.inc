.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.include "stm32f10x_constants.inc"


@ EXTI constants

.equ EXTI_IMR_IMR0,         (BIT0)
.equ EXTI_IMR_IMR1,         (BIT1)
.equ EXTI_IMR_IMR2,         (BIT2)
.equ EXTI_IMR_IMR3,         (BIT3)
.equ EXTI_IMR_IMR4,         (BIT4)
.equ EXTI_IMR_IMR5,         (BIT5)
.equ EXTI_IMR_IMR6,         (BIT6)
.equ EXTI_IMR_IMR7,         (BIT7)
.equ EXTI_IMR_IMR8,         (BIT8)
.equ EXTI_IMR_IMR9,         (BIT9)
.equ EXTI_IMR_IMR10,        (BIT10)
.equ EXTI_IMR_IMR11,        (BIT11)
.equ EXTI_IMR_IMR12,        (BIT11)
.equ EXTI_IMR_IMR13,        (BIT13)
.equ EXTI_IMR_IMR14,        (BIT14)
.equ EXTI_IMR_IMR15,        (BIT15)
.equ EXTI_IMR_IMR16,        (BIT16)
.equ EXTI_IMR_IMR17,        (BIT17)
.equ EXTI_IMR_IMR18,        (BIT18)
.equ EXTI_IMR_IMR19,        (BIT19)

.equ EXTI_RTSR_TR0,         (BIT0)
.equ EXTI_RTSR_TR1,         (BIT1)
.equ EXTI_RTSR_TR2,         (BIT2)
.equ EXTI_RTSR_TR3,         (BIT3)
.equ EXTI_RTSR_TR4,         (BIT4)
.equ EXTI_RTSR_TR5,         (BIT5)
.equ EXTI_RTSR_TR6,         (BIT6)
.equ EXTI_RTSR_TR7,         (BIT7)
.equ EXTI_RTSR_TR8,         (BIT8)
.equ EXTI_RTSR_TR9,         (BIT9)
.equ EXTI_RTSR_TR10,        (BIT10)
.equ EXTI_RTSR_TR11,        (BIT11)
.equ EXTI_RTSR_TR12,        (BIT12)
.equ EXTI_RTSR_TR13,        (BIT13)
.equ EXTI_RTSR_TR14,        (BIT14)
.equ EXTI_RTSR_TR15,        (BIT15)
.equ EXTI_RTSR_TR16,        (BIT16)
.equ EXTI_RTSR_TR17,        (BIT17)
.equ EXTI_RTSR_TR18,        (BIT18)
.equ EXTI_RTSR_TR19,        (BIT19)


.equ EXTI_FTSR_TR0,         (BIT0)
.equ EXTI_FTSR_TR1,         (BIT1)
.equ EXTI_FTSR_TR2,         (BIT2)
.equ EXTI_FTSR_TR3,         (BIT3)
.equ EXTI_FTSR_TR4,         (BIT4)
.equ EXTI_FTSR_TR5,         (BIT5)
.equ EXTI_FTSR_TR6,         (BIT6)
.equ EXTI_FTSR_TR7,         (BIT7)
.equ EXTI_FTSR_TR8,         (BIT8)
.equ EXTI_FTSR_TR9,         (BIT9)
.equ EXTI_FTSR_TR10,        (BIT10)
.equ EXTI_FTSR_TR11,        (BIT11)
.equ EXTI_FTSR_TR12,        (BIT12)
.equ EXTI_FTSR_TR13,        (BIT13)
.equ EXTI_FTSR_TR14,        (BIT14)
.equ EXTI_FTSR_TR15,        (BIT15)
.equ EXTI_FTSR_TR16,        (BIT16)
.equ EXTI_FTSR_TR17,        (BIT17)
.equ EXTI_FTSR_TR18,        (BIT18)
.equ EXTI_FTSR_TR19,        (BIT19)

