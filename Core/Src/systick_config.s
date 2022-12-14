.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.include "stm32f10x.inc"


.section .data

.global uwTick
uwTick:		.word	0

.section .text

@ R0 receives the number of ticks 24bits
.type SysTick_Init, %function
.global SysTick_Init
SysTick_Init:
	PUSH	{r4-r5, lr}
	@ Disable SysTick
	LDR		r4, =SysTick_CTRL
	LDR		r5, =#0
	STR		r5, [r4]
	@ Set reload register
	LDR		r4, =SysTick_LOAD
	SUB		r0, #1
	STR		r0, [r4]
	@ Set interrupt priority of SysTick to least urgency (largest priority value)
	LDR		r4, =SCB_SHP_SysTick_IRQn
	LDR		r0, =((15 << (8 - __NVIC_PRIO_BITS)) & 0xFF)
	STR		r0, [r4]
	@ Reset SysTick counter
	LDR		r4, =SysTick_VAL
	LDR		r5, =#0
	STR		r5, [r4]
	@ Select clock: 1 = processor clock; 0 = external clock
	LDR		r4, =SysTick_CTRL
	LDR		r5, [r4]
	ORR		r5, r5, (SysTick_CTRL_CLKSOURCE | SysTick_CTRL_TICKINT | SysTick_CTRL_ENABLE)
	STR		r5, [r4]
	
	POP		{r4-r5,pc}


.type SysTick_Handler, %function
.global SysTick_Handler
SysTick_Handler:
	PUSH	{r4-r5, lr}
	
	LDR		r4, =uwTick
	LDR		r5, [r4]
	CMP		r5, #0
	IT		GT
	SUBGT	r5, r5, #1
	STR		r5, [r4]

	POP		{r4-r5, pc}

