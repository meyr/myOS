#include "reg.h"

void SystemInit(void)
{
	/* Reset the RCC clock configuration to the default reset state(for debug purpose) */
	/* Set HSION bit */
	RCC->CR |= (uint32_t)0x00000001;
	
	/* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
	RCC->CFGR &= (uint32_t)0xF8FF0000;
	
	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t)0xFEF6FFFF;
	
	/* Reset HSEBYP bit */
	RCC->CR &= (uint32_t)0xFFFBFFFF;
	
	/* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
	RCC->CFGR &= (uint32_t)0xFF80FFFF;
	
	/* Disable all interrupts and clear pending bits  */
	//RCC->CIR = 0x009F0000;
	RCC->CIR = 0x00000000;
    
	/* config HSI */
		/* enable HSI */
		RCC->CR |= 0x00000001;
		/* wait HSI RDY */
		while ((RCC->CR & 0x00000002) != 0x00000002);

	/* config PLL */
		/* set PLL source to HSI/2 */
		RCC->CFGR &= 0xFFFEFFFF;
		
		/* set PLLMUL to x16 */
		RCC->CFGR |= 0x00380000;
		
		/* set PLL ON */
		RCC->CR |= 0x01000000;
		
		/* wait PLL RDY */
		while ((RCC->CR & 0x02000000) != 0x02000000);

	/* set APB1 prescaler to 2 */
	RCC->CFGR |= 0x00000400;
	
	/* enable prefetch */
	FLASH->ACR |= 0x00000010;
	
	/* set wait 2 cyccle for 64Mhz */
	FLASH->ACR &= 0xfffffff8;
	FLASH->ACR |= 0x00000002;

	/* set SYSCLK to PLLCLK */
	RCC->CFGR &= 0xFFFFFFFC;
	RCC->CFGR |= 0x00000002;

 	/*  stm32f103rb nucleo board PD0/MCO pin connect to
	 *  stm32f103cbt6 jtag ic mco output the freq. is the same
	 *  to this IC input external oscillator freq.
	 */
	
 	/* enable GPIOD */
 	//RCC->APB2ENR |= 0x00000020;
 	/* enable AFIO */
 	RCC->APB2ENR |= 0x00000001;
 	/* remap pd0/pd1 to OSC_IN/OSC_OUT */
 	//AFIO->MAPR |= 0x00008000; 
 	/* set MCO to SYSCLK */
 	//RCC->CFGR &= 0xF8FFFFFF;
 	//RCC->CFGR |= 0x04000000;

}

void initUART(void)
{

	/* UART1 configure */
	/* enable UART1 clock */
	RCC->APB2ENR |= 0x00004000;
		
	/* set UART1 parameter */
	USART1->SR   = 0x000000c0;	
	USART1->DR   = 0x00000000;
	USART1->BRR  = 0x0000022c;	/* 0x22 = 34, 0xc = 12 => 34 + 12/16 = 34.75, baud = 64/(16*34.75) = 1151079 hz */
	USART1->CR1  = 0x0000100c;	/* 8 data bit , parity none, even parity*/ 
	USART1->CR2  = 0x00000000;
	USART1->CR3  = 0x00000000;
	USART1->GTPR = 0x00000000; 
	/* enable UART1 */
	USART1->CR1 |= 0x00002000;

	/* enable GPIOA */
	RCC->APB2ENR |= 0x00000004;
	/* switch pa9/pa10 to uart1 */
	GPIOA->CRH &= 0xfffff00f;
	GPIOA->CRH |= 0x000008b0;
}

void initLED(void)
{
	/* enable GPIOA */
	RCC->APB2ENR |= 0x00000004;
	/* set PA5 to output push-pull mode */
	GPIOA->CRL &= 0xff0fffff;
	GPIOA->CRL |= 0x00300000;
	/* set PA5 to High */
	GPIOA->ODR |= 0x00000020;
}

void initUserBtn(void)
{
	/* enable GPIOC */
	RCC->APB2ENR |= 0x00000010;
	/* set PC13 to flating input mode */
	GPIOC->CRH &= 0xff0fffff;
	GPIOC->CRH |= 0x00400000;
	/* select PC13 to EXTI13 */
	AFIO->EXTICR[3] |= 0x00000020;
	/* set falling trigger */
	EXTI->FTSR |= 0x00002000;
	/* enable EXTI13 */
	EXTI->IMR |= 0x00002000;
	NVIC->ICPR[1] |= 0x00000100;	/* IRQ NO 40 */
	NVIC->ISER[1] |= 0x00000100;	/* IRQ NO 40 */
}

char getUserBtnValue(void)
{
	int rtn = 0;
	
	if ( (GPIOC->IDR &= 0x00002000) == 0x00002000)
		rtn = 1;
	else
		rtn = 0;
	
	return rtn;
}

void toggleLED(char cmd)
{
	if (cmd)
		GPIOA->ODR |= 0x00000020;
	else
		GPIOA->ODR &= 0xffffffdf;
}

void Default_Handler(void)
{
	static char cmd;
	while (1) {
		toggleLED(cmd);
		cmd ^= 1;
		delay(500);
	}
}

void EXTI15_10_IRQHandler(void)
{	
	/* clean pending register */
	EXTI->PR = 0x00002000;

	printf("btn push!\r\n");
	//toggleLED(0);
}

int main(void)
{
	char string[] = "hi cortex m3\r\n";
	int rtn;
	initSysTick();
	initUART();
	initLED();
	initUserBtn();


	/* system call */
	rtn = sv_call_write_data(string, strlen(string));
	printf("return value from sv_call_write_data %d\r\n", rtn);
	//syscall(3);

	printf("Hello World\r\n");
	toggleLED(1);
	while (1) {

		//printf("[%x] %d %b\r\n",uwTick,uwTick,uwTick);
		//delay(500);
	}

	return 1;
}
