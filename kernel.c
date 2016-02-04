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

void SwitchToUserMode(void)
{
	asm volatile (	
		"mov r0, #3\t\n"
		"msr CONTROL, r0\t\n"
		"ISB\t\n"
	);
}

void SetupPSP(uint32_t address)
{
	asm volatile(
		"mov r0, %0\t\n"
		"msr PSP, r0\t\n"
		::"r"(address):
	);
}

uint32_t GetPSP(void)
{
	uint32_t rtn;
	asm volatile(
		"mrs r0, PSP\t\n"
		"mov %0, r0\t\n"
		:"=r"(rtn)::
	);
	return rtn;
}

uint32_t GetSP(void)
{
	uint32_t rtn;
	asm volatile(
		"mov %0, r13\t\n"
		:"=r"(rtn)::
	);
	return (rtn + 8);
}

int kputc(int c)
{
	while ((USART1->SR & 0x00000080) != 0x00000080);
		USART1->DR = (c & 0xFF);
	
	return 1;
}
        
int kputs(const char *s)
{
	while (*s) {
		while ((USART1->SR & 0x00000080) != 0x00000080);
			USART1->DR = (*s & 0xFF);
			s++;
	}
	return 1;
}
												    

int kprintf(const char *format, ...) 
{
	int translating = 0;
	int ret = 0;
	const char *p = 0;
	char buf[16];
	char **arglist = (char **)(&format);

	for (p = format; *p != '\0'; ++p) {
		switch (*p) {
		case '%':
			if (!translating)
				translating = 1;
			else {
				if (kputc('%') < 0)
					return 0;
				else {
					ret++;
					translating = 0;
				}
			}
			break;
		case 'b':
			if (translating) {
				translating = 0;
				arglist = arglist + 1;
				itoa(*((int *)arglist), buf, 2);
				if (kputs(buf) < 0)
					return 0;
				ret += strlen(buf);
			} else {
				kputc('x');
				ret++;
			}
			break;
	
		case 'x':
			if (translating) {
				translating = 0;
				arglist = arglist + 1;
				itoa(*((int *)arglist), buf, 16);
				if (kputs(buf) < 0)
					return 0;
				ret += strlen(buf);
			} else {
				kputc('x');
				ret++;
			}
			break;
		case 'd':
			if (translating) {
				translating = 0;
				arglist = arglist + 1;
				itoa(*((int *)arglist), buf, 10);
				if (kputs(buf) < 0)
					return 0;
				ret += strlen(buf);
			} else if (kputc('d') < 0)
				return 0;
			else
				ret++;
			break;
		case 's':
			if (translating) {
				arglist = arglist + 1;
				translating = 0;
				kputs(*arglist);
				ret += strlen(*arglist);
			} else 
				kputc('s');
			break;
		default:
			if (translating)
				translating = 0;
			if (*p == '\n')
				kputc('\r');
			kputc(*p);
			ret++;
			break;
		}
	}
	return ret;
}

