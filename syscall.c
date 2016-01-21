#include "reg.h"

#define svc(code) asm volatile ("svc %[immediate]"::[immediate] "I" (code))
#define SVC_WRITE_DATA 7

void svc_handler_c(unsigned int *svc_args)
{
	unsigned int svc_number;
	unsigned int svc_r0;
	unsigned int svc_r1;

	svc_number = ((char *)svc_args[6])[-2];
	svc_r0 = ((unsigned long) svc_args[0]);
	svc_r1 = ((unsigned long) svc_args[1]);
	printf("svc number %d\r\n",svc_number);
	printf("%s",svc_r0);
	printf("length %d\r\n",svc_r1);

	svc_args[0] = 128;
}

void SVC_Handler(void)
{
	asm volatile (
		"tst lr, #4\t\n"
		"ite eq\t\n"
		"mrseq r0, msp\t\n"
		"mrsne r0, psp\t\n"
		"b svc_handler_c");
}

int sv_call_write_data(char *string, int length)
{
	int rtn;
	svc(SVC_WRITE_DATA);
	asm volatile ("mov %0, r0\t\n":"=r"(rtn)::);
	return rtn;
}

