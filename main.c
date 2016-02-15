#include "reg.h"

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
	/* clear interrupt mask */
	EXTI->IMR |= 0x00002000;
	/* clear EXTI interrupt pending register */
	EXTI->PR = 0x00002000;
	/* clear NVIC interuput pending register */
	NVIC->ICPR[1] |= 0x00000100;	/* IRQ NO 40 */
	/* set interrupt enable */
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

void user1_main(void)
{
	uint8_t toggle = 0;
	printf("Hello World\n");
	toggleLED(1);
	/* system call */
	while (1) {
		toggleLED(toggle);
		delay(1000);
		toggle = toggle ? 0 : 1;
		printf("user1_main\n");
	}

}

void user2_main(void)
{
	while(1) {
		delay(1000);
		printf("user2_main\n");

	}
}

void create_task(uint32_t *address, void (*start)(void))
{
	uint8_t i;
	for (i = 1; i < 11; i++)
		*(address - i) = 0x0;

	*(address - 1) = start;		
}


int kernel_main(void)
{
	MpuInit();
	initSysTick();
	initUART();
	initLED();
	initUserBtn();
	
	create_task((uint32_t *)(0x20002800), user1_main);
	create_task((uint32_t *)(0x20002900), user2_main);
	activate(0x20002800 - 0x28);
	//SetupPSP(0x20002800);
	//SwitchToUserMode();
	//user_main();

	return 1;
}


