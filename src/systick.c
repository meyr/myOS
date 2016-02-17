#include "reg.h"

__IO uint32_t uwTick;
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

uint8_t enablePendSV;
void SysTick_Handler(void)
{
	uwTick++;

	/* set pendsv pending bit to 
	 * triggle pendsv
	 */
	//if ((uwTick % 10 == 9) & enablePendSV)	
		SCB->ICSR |= 0x10000000;
}

void delay(int ms)
{
	int now;

	now = uwTick;
	while (uwTick - now < ms);
}


