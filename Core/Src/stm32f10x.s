.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.include "stm32f10x.inc"

@*******************************************
@ Function definitions
@*******************************************
.section .text

.type delay, %function
.global delay
delay:
	PUSH	{r4,lr}

	LDR		r4, =uwTick
	STR		r0, [r4]

delay_loop:
	LDR		r0, [r4]
	CMP		r0, #0
	BNE		delay_loop
	
	POP		{r4, pc}	
