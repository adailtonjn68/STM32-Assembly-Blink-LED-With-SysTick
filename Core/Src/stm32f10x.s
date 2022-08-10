.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.include "stm32f10x.inc"

@*******************************************
@ Function definitions
@*******************************************
.text

.global delay
delay:
	PUSH	{r1,lr}
	@ Reserve space for local variable on SP
	SUB		sp, sp, #8
	
	LDR		r1, =uwTick
	STR		r0, [r1]

delay_loop:
	LDR		r0, [r1]
	CMP		r0, #0
	BNE		delay_loop
	
	ADD		sp, sp, #8
	POP		{r1,pc}
	BX		lr	
