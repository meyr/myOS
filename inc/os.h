#ifndef __OS_H
#define __OS_H
#include "stddef.h"

/* os setting */
#define HEAP_START 0x20002800
#define MAX_HEAPS 4096

struct task {
	uint32_t sp;
	uint8_t  priority;
	struct task *next;
	struct task *prev;
};


/* global variable */

extern __IO uint32_t uwTick;

/* kernel */
uint32_t GetPSP(void);
uint32_t GetSP(void);
void SetupPSP(uint32_t address);
void SwitchToUserMode(void);
int kprintf(const char *format, ...);
void create_task(uint32_t *address, void (*start)(void));
void thread_start(void);
void task_show(void);
void *kmalloc(unsigned int nbytes);
void kfree(void *ap);
/* global function */
void initSysTick(void);
void delay(int ms);
void MpuInit(void);
/* cmsis */
void NVIC_SystemReset(void);
void NVIC_VectReset(void);
void __WFI(void);
void __WFE(void);
/* power */
void pwr_standby(void);
void pwr_sleep(void);
void pwr_sleeponexit(void);
void pwr_stopRon(void);
void pwr_stopRlow(void);
/* libc */
unsigned int strlen(char *str);
int printf(const char *format, ...);
void memcpy(uint8_t *dest, uint8_t *src, uint32_t size);
char *itoa(int n, char *str, int radix);
/* svc */
int svc_call_write_string(char *string);
/* led */
void toggleLED(char cmd);
#endif
