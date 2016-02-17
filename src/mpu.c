/*  Memory Protect Unit
 *
 *  stm32f103rb not present MPU
 */
#include "reg.h"

void MpuRegionSetup(uint32_t addr, uint32_t region, uint32_t size,
	uint32_t ap, uint32_t MemAttrib, uint32_t srd, uint32_t XN, uint32_t enable)
{
	MPU->RBAR = (addr & 0xffffffe0) | (region & 0xf) | 0x10;
	MPU->RASR = ((XN & 0x1) << 28)  | ((ap & 0x7) << 24) |
		    ((MemAttrib & 0x3f) << 16) | ((srd & 0xff) << 8) |
		    ((size & 0x1f) << 1) | (enable & 0x1);
	
	return;
}

void MpuRegionDisable(uint32_t region)
{
	MPU->RBAR = (region & 0xf) | 0x10;
	MPU->RASR = 0;
	return;
}

void MpuInit(void)
{
	/* check mpu function */
	if ((MPU->TYPE & 0x0000ff00) == 0x00000000)
		return;
	
	/* disable MPU */
	MPU->CTRL = 0;

	/* set MPU region */

	/* enable MPU */
	/* enable default memory map */
	MPU->CTRL = 0x5;

	return;
}
