#include "reg.h"

#define svc(code) asm volatile ("svc %[immediate]"::[immediate] "I" (code))
#define SVC_WRITE_STRING 7

void __serial_putc(const char c)
{
	while ((USART1->SR & 0x00000080) != 0x00000080);
		USART1->DR = (c & 0xFF);

	/* If \n, also do \r */
	if (c == '\n')
		__serial_putc('\r');
}

void __serial_puts(const char *s)
{
        while (*s)
		__serial_putc (*s++);
}

void svc_handler_c(unsigned int *svc_args)
{
	unsigned int svc_number;
	unsigned int svc_r0;
	//unsigned int svc_r1;

	svc_number = ((char *)svc_args[6])[-2];
	svc_r0 = ((unsigned long) svc_args[0]);
	//svc_r1 = ((unsigned long) svc_args[1]);
	switch (svc_number) {
		case SVC_WRITE_STRING :
			//svc_args[0] = __serial_puts((const char *)svc_r0);						
			__serial_puts((const char *)svc_r0);						
			break;
		default :
			break;
	};
	
}

void SVC_Handler(void)
{
	/* save stack pointer to r0, 
	 * then pass parameter to function svc_handler_c by r0 */
	asm volatile (
		"tst lr, #4\t\n"
		"ite eq\t\n"
		"mrseq r0, msp\t\n"
		"mrsne r0, psp\t\n"
		"b svc_handler_c");
}

int svc_call_write_string(char *string)
{
	int rtn;
	svc(SVC_WRITE_STRING);
	asm volatile ("mov %0, r0\t\n":"=r"(rtn)::);
	return rtn;
}

