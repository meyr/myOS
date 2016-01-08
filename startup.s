.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global g_pfnVectors
.global Default_Handler

.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss

.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
	/* Copy the data segment initializers from flash to SRAM */
	movs r1, #0
  	b LoopCopyDataInit

CopyDataInit:
	ldr r3, =_sidata
	ldr r3, [r3, r1]
	str r3, [r0, r1]
	adds r1, r1, #4

LoopCopyDataInit:
	ldr r0, =_sdata
	ldr r3, =_edata
	adds r2, r0, r1
	cmp r2, r3
	bcc CopyDataInit
	ldr r2, =_sbss
	b LoopFillZerobss

	/* Zero fill the bss segment. */
FillZerobss:
	movs r3, #0
	str r3, [r2], #4

LoopFillZerobss:
	ldr r3, = _ebss
	cmp r2, r3
	bcc FillZerobss

	/* Call the clock system intitialization function.*/
	bl  SystemInit
	/* Call the application's entry point.*/
  	bl main
  	bx lr
.size Reset_Handler, .-Reset_Handler

.section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
	b Infinite_Loop

.size Default_Handler, .-Default_Handler

.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word _estack
  .word Reset_Handler
