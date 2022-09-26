.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.include "stm32f10x.inc"


.equ DELAY1,		1000

.section .text
.global main
main:
	LDR		r0, =#8000
	BL		SysTick_Init

	@ Enable clock to GPIOC
	LDR		r1, =RCC_APB2ENR
	LDR		r0, [r1]
	ORR		r0, r0, RCC_APB2ENR_IOPCEN
	STR		r0, [r1]
	@ Set GPIOC13 as output, push-pull (CNF: 00) and speed of 50 MHz (MODE: 11)
	LDR		r1, =GPIOC_CRH
	LDR		r0, [r1]
	AND		r0, r0, ~(GPIO_CRH_CNF13_1 | GPIO_CRH_CNF13_0)
	ORR		r0, r0, (GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0)
	STR		r0, [r1]

loop:
	@ Turn on GPIOC13
	LDR		r1, =GPIOC_BSRR
	LDR		r0, [r1]
	ORR		r0, r0, GPIO_BSRR_BS13
	STR		r0, [r1]

	LDR		r0, =DELAY1
	BL		delay

	@ Turn off GPIOC13
	LDR		r1, =GPIOC_BSRR
	LDR		r0, [r1]
	ORR		r0, r0, GPIO_BSRR_BR13
	STR		r0, [r1]

	LDR		r0, =DELAY1
	BL		delay

	B		loop
