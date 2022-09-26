.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.include "stm32f10x_constants.inc"

@ RCC constants

.equ RCC_APB2ENR_IOPGEN,    (BIT8)
.equ RCC_APB2ENR_IOPFEN,    (BIT7)
.equ RCC_APB2ENR_IOPEEN,    (BIT6)
.equ RCC_APB2ENR_IOPDEN,    (BIT5)
.equ RCC_APB2ENR_IOPCEN,    (BIT4)
.equ RCC_APB2ENR_IOPBEN,    (BIT3)
.equ RCC_APB2ENR_IOPAEN,    (BIT2)
