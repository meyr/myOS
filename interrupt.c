#include "reg.h"

void PendSV_Handler(void)
{

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


