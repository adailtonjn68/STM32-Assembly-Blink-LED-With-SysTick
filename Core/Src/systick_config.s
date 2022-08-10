.include "stm32f10x.inc"

.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.data

.global uwTick
uwTick:		.word	0

.text
@ R0 receives the number of ticks 24bits
.global SysTick_Init
SysTick_Init:
	PUSH	{r1-r2, lr}
	@ Disable SysTick
	LDR		r1, =SysTick_CTRL
	LDR		r2, =#0
	STR		r2, [r1]
	@ Set reload register
	LDR		r1, =SysTick_LOAD
	SUB		r0, #1
	STR		r0, [r1]
	@ Set interrupt priority of SysTick to least urgency (largest priority value)
	LDR		r1, =SCB_SHP_SysTick_IRQn
	LDR		r0, =((15 << (8 - __NVIC_PRIO_BITS)) & 0xFF)
	STR		r0, [r1]
	@ Reset SysTick counter
	LDR		r1, =SysTick_VAL
	LDR		r2, =#0
	STR		r2, [r1]
	@ Select clock: 1 = processor clock; 0 = external clock
	LDR		r1, =SysTick_CTRL
	LDR		r2, [r1]
	ORR		r2, r2, (SysTick_CTRL_CLKSOURCE | SysTick_CTRL_TICKINT | SysTick_CTRL_ENABLE)
	STR		r2, [r1]
	
	POP		{r1-r2,pc}
	BX		lr


.global SysTick_Handler
SysTick_Handler:
	PUSH	{r0-r1, lr}
	
	LDR		r0, =uwTick
	LDR		r1, [r0]
	CMP		r1, #0
	IT		GT
	SUBGT	r1, r1, #1
	
	STR		r1, [r0]

	POP		{r0-r1, pc}
