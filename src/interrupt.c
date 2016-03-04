#include "reg.h"
#include "os.h"

extern struct task *now_task;
uint8_t enablePendSV;
__IO uint32_t uwTick;

void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
	uint32_t reg_value;
  	/* only values 0..7 are used          */
  	uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);             

	/* read old register configuration    */
	reg_value  =  SCB->AIRCR;                                                   
	/* clear bits to change               */
	reg_value &= ~((uint32_t)(0xffff0000 | 0x00000300));             
	/* Insert write key and priorty group */
	reg_value  =  (reg_value                |
	              ((uint32_t)0x5FAUL << 16) |
	              (PriorityGroupTmp << 8)   );             
	SCB->AIRCR =  reg_value;
}


void PendSV_Handler(void)
{

	if (now_task->next != now_task->prev) {
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
	printk("[%d] btn push!\r\n",uwTick);
}



void initSysTick(void)
{
	/* disable systick and clear configuration */
	SysTick->CTRL = 0x0;

	/* select clock source to AHB/8 */
	SysTick->CTRL &= 0xfffffffb;

	/* enable assert SysTick exception request if count down to zero */
	SysTick->CTRL |= 0x00000002;

	/* set RELOAD value to 8000
	 * clock source 64Mhz/ 8 = 8Mhz
	 * 8M / 8000 = 1Khz => 1ms 
	 */
	SysTick->LOAD = 0x00001f40;

	/* enable the counter */
	SysTick->CTRL |= 0x00000001;
}

void SysTick_Handler(void)
{
	uwTick++;

	/* set pendsv pending bit to 
	 * triggle pendsv
	 */
	//if ((uwTick % 10 == 9) & enablePendSV)	
	if(enablePendSV)
		SCB->ICSR |= 0x10000000;
}

void delay(int ms)
{
	int now;

	now = uwTick;
	while (uwTick - now < ms);
}


void interrupt_init(void)
{
	/* setup interrupt priority group */
	//NVIC_SetPriorityGrouping(4);

	/* init system tick */
	initSysTick();

	/* set systick interrupt priority to 0*/
	//SCB->SHP[11] = 0x0; 

	/* set pendsv priority */
	//SCB->SHP[10] = 0xff;

	/* set syscall priority */
	//SCB->SHP[7] = 0xfe;
}


