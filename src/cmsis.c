#include "reg.h"

void NVIC_SystemReset(void)
{
	/* set sysresetreq bit 0x05fa is a write access key */
	SCB->AIRCR = 0x05fa0004;
	while(1);
}

void NVIC_VectReset(void)
{
	/* set vectreset bit 0x05fa is a write access key */
	SCB->AIRCR = 0x05fa0001;
	while(1);
}

/** \brief  Wait For Interrupt

    Wait For Interrupt is a hint instruction that suspends execution
    until one of a number of events occurs.
 */
void __WFI(void)
{
  asm volatile ("wfi\t\n");
}


/** \brief  Wait For Event

    Wait For Event is a hint instruction that permits the processor to enter
    a low-power state until one of a number of events occurs.
 */
void __WFE(void)
{
  asm volatile ("wfe\t\n");
}


