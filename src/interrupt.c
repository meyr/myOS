#include "reg.h"
#include "os.h"

extern struct task *now_task;
extern uint8_t enablePendSV;

void PendSV_Handler(void)
{

	if ((enablePendSV == 1) && (now_task->next != now_task->prev)) {
		/* save the old task's context */
		asm volatile("mrs r0, psp\t\n");
		asm volatile("stmdb r0!, {r4-r11, lr}\t\n");

		/* save the old task's stack pointer address*/
		asm volatile("mov %0, r0\t\n" : "=r" (now_task->sp));

		/* switc to next task */
		now_task = now_task->next;
		/* get new task's stack pointer address */
		asm volatile("mov r0, %0\t\n" : : "r" (now_task->sp));
		/* restore the new task's context and jump to the stack */
		asm volatile("ldmia r0!, {r4-r11, lr}\t\n");
		asm volatile("msr psp, r0\t\n");
	}
}

void Default_Handler(void)
{
	while (1) {
		toggleLED(1);
		delay(500);
	}
}

void EXTI15_10_IRQHandler(void)
{	
	/* clean pending register */
	EXTI->PR = 0x00002000;

	/* can triggle svc in interrupt mode */
	kprintf("[%d] btn push!\r\n",uwTick);
}


