@ ARM directives: https://sourceware.org/binutils/docs/as/ARM-Directives.html

.syntax unified     @ Use unified ARM/Thumb assembly syntax
.cpu cortex-m3      @ Target processor
.fpu softvfp        @ Software floating-point support (default: sofvfp)
                    @ https://developer.arm.com/documentation/dui0473/j/assembler-command-line-options/--fpu-name
.thumb              @ Use thumb instruction set

.macro IRQ handler
    .word \handler
    .weak \handler
    .set  \handler, Default_Handler
.endm


@ Interrupt service routine vector
.section .isr_vector, "a", %progbits
.type    _isr_vector, %object
.size    _isr_vector, .-_isr_vector

_isr_vector:
    @ Commom to all cortex-m3
    .word _estack
    .word Reset_Handler
    IRQ NMI_Handler
    IRQ HardFault_Handler
    IRQ MemManage_Handler
    IRQ BusFault_Handler
    IRQ UsageFault_Handler
    .word   0
    .word   0
    .word	0
    .word	0
    IRQ SVC_Handler
    IRQ DebugMon_Handler
    .word		0
    IRQ PendSV_Handler
    IRQ SysTick_Handler

    @ Specific to STM32F10xx
    IRQ WWDG_IRQHandler
    IRQ PVD_IRQHandler
    IRQ TAMPER_IRQHandler
    IRQ RTC_IRQHandler
    IRQ FLASH_IRQHandler
    IRQ RCC_IRQHandler
    IRQ EXTI0_IRQHandler
    IRQ EXTI1_IRQHandler
    IRQ EXTI2_IRQHandler
    IRQ EXTI3_IRQHandler
    IRQ EXTI4_IRQHandler
    IRQ DMA1_Channel1_IRQHandler
    IRQ DMA1_Channel2_IRQHandler
    IRQ DMA1_Channel3_IRQHandler
    IRQ DMA1_Channel4_IRQHandler
    IRQ DMA1_Channel5_IRQHandler
    IRQ DMA1_Channel6_IRQHandler
    IRQ DMA1_Channel7_IRQHandler
    IRQ ADC1_2_IRQHandler
    IRQ USB_HP_CAN_TX_IRQHandler
    IRQ USB_LP_CAN_RX0_IRQHandler
    IRQ CAN_RX1_IRQHandler
    IRQ CAN_SCE_IRQHandler
    IRQ EXTI9_5_IRQHandler
    IRQ TIM1_BRK_IRQHandler
    IRQ TIM1_UP_IRQHandler
    IRQ TIM1_TRG_COM_IRQHandler
    IRQ TIM1_CC_IRQHandler
    IRQ TIM2_IRQHandler
    IRQ TIM3_IRQHandler
    IRQ TIM4_IRQHandler
    IRQ I2C1_EV_IRQHandler
    IRQ I2C1_ER_IRQHandler
    IRQ I2C2_EV_IRQHandler
    IRQ I2C2_ER_IRQHandler
    IRQ SPI1_IRQHandler
    IRQ SPI2_IRQHandler
    IRQ USART1_IRQHandler
    IRQ USART2_IRQHandler
    IRQ USART3_IRQHandler
    IRQ EXTI15_10_IRQHandler
    IRQ RTCAlarm_IRQHandler
    IRQ USBWakeup_IRQHandler
    IRQ TIM8_BRK_IRQHandler
    IRQ TIM8_UP_IRQHandler
    IRQ TIM8_TRG_COM_IRQHandler
    IRQ TIM8_CC_IRQHandler
    IRQ ADC3_IRQHandler
    IRQ FSMC_IRQHandler
    IRQ SDIO_IRQHandler
    IRQ TIM5_IRQHandler
    IRQ SPI3_IRQHandler
    IRQ UART4_IRQHandler
    IRQ UART5_IRQHandler
    IRQ TIM6_IRQHandler
    IRQ TIM7_IRQHandler
    IRQ DMA2_Channel1_IRQHandler
    IRQ DMA2_Channel2_IRQHandler
    IRQ DMA2_Channel3_IRQHandler
    IRQ DMA2_Channel4_5_IRQHandler

.section .text.Default_Handler, "ax", %progbits
Default_Handler:
infinite_Loop:
    B       infinite_Loop
.size Default_Handler, .-Default_Handler

.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    @ Set the stack pointer to the end of the stack (_estack is defined in the linker file)
    LDR     r0, =_estack
    MOV     sp, r0

    @ Copy data from flash to RAM data init section
    @ R2 will store the progress along the sidata section
    MOVS    r0, #0
    @ Load the start/end addresses of the data section and the start of the data ini section
    LDR     r1, =_sdata
    LDR     r2, =_edata
    LDR     r3, =_sidata
    B       copy_sidata_loop

copy_sidata:
    @ Offset the data init section by copy progress
    LDR     r4, [r3, r0]
    @ Copy the current word into data, and increment
    STR     r4, [r1, r0]
    ADDS    r0, r0, #4

copy_sidata_loop:
    @ Unless copied the whole data section, copy the next word from sidata->data
    ADDS    r4, r0, r1
    CMP     r4, r2
    BCC     copy_sidata

    @ Once done copying the data section into RAM move to filling the BSS section with 0s
    MOVS    r0, #0
    LDR     r1, =_sbss
    LDR     r2, =_ebss
    B       reset_bss_loop

@ Fill the BSS segment with 0s
reset_bss:
    @ Store 0 and increment by a word
    STR     r0, [r1]
    ADDS    r1, r1, #0

reset_bss_loop:
    @ Use R1 to count progress, if it's not done, reset the next word and increment
    CMP     r1, r2
    BCC     reset_bss
    B       main
.size Reset_Handler, .-Reset_Handler

