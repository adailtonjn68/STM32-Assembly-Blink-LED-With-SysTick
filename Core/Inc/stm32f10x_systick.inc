.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.include "stm32f10x_constants.inc"


@ SysTick constants
.equ SysTick_CTRL_CLKSOURCE,(1 << 2)
.equ SysTick_CTRL_TICKINT,	(1 << 1)
.equ SysTick_CTRL_ENABLE,	(1 << 0)
