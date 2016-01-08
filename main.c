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

  /* set MCO to SYSCLK */
 	//RCC->CFGR &= 0xF8FFFFFF;
 	//RCC->CFGR |= 0x04000000;

  /* enable UART1 */
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

void print_str(const char *str)
{
        while (*str) {
                while ((USART1->SR & 0x00000080) != 0x00000080);
	        USART1->DR = (*str & 0xFF);
                str++;
        }
}
						
int main(void)
{
	print_str("Hello World\r\n");

	return 1;
}
