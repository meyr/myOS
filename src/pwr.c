#include "reg.h"
#include "os.h"

void pwr_sleep(void)
{
	/* wakeup by interrupt, so must disable all interrupt */
	/* clear sleepdeep bit */
	SCB->SCR &= 0xfffffffb;

	/* clear sleep on exit bit */
	SCB->SCR &= 0xfffffffd;

	/* request wait for interrupt */
	__WFI();
}

void pwr_sleeponexit(void)
{
	/* wake up by interrupt, and sleep when interrupt finish */
	/* clear sleepdeep bit */
	SCB->SCR &= 0xfffffffb;

	/* set sleep on exit bit */
	SCB->SCR |= 0x00000002;

	/* request wait for interrupt */
	__WFI();
}


void pwr_stopRlow(void)
{
	/* set regulator low */
	PWR->CR |= 0x00000001;

	/* deepsleep mode */
	SCB->SCR |= 0x00000004;

	/* set stop mode when enter deepsleep */
	PWR->CR &= 0xfffffffd;

	/* Request Wait For Interrupt */
	__WFI();
}

void pwr_stopRon(void)
{
	/* set regulator on */
	PWR->CR &= 0xfffffffe;

	/* deepsleep mode */
	SCB->SCR |= 0x00000004;

	/* set stop mode when enter deepsleep */
	PWR->CR &= 0xfffffffd;

	/* Request Wait For Interrupt */
	__WFI();

}

void pwr_standby(void)
{
	/* Enter Standby mode when the CPU enters Deepsleep */
	PWR->CR |= 0x00000002;

	/* Enter Deepsleep when enter sleep mode */
	SCB->SCR |= 0x00000004;

	/* Request Wait For Interrupt */
	__WFI();
}
