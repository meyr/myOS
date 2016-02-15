#ifndef __REG_H
#define __REG_H
#define uint32_t	unsigned int
#define uint8_t		unsigned char
#define int32_t		int
#define __IO		volatile
#define __I		volatile const
#define __O		volatile

/*< Peripheral base address in the alias region */
#define PERIPH_BASE           ((uint32_t)0x40000000) 

#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)  /* 0x40021000 */
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000)  /* 0x40022000 */
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800) /* 0x40013800 */
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800) /* 0x40010800 */
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400) /* 0x40011400 */
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000) /* 0x40010000 */
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400) /* 0x40010400 */
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000) /* 0x40007000 */

/*< System Control Space Base Address  */
#define SCS_BASE            (0xE000E000UL)                           
/*< SysTick Base Address               */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    
#define NVIC_BASE           (SCS_BASE +  0x0100UL) /* 0xe000e100 */
#define SCB_BASE            (SCS_BASE +  0x0D00UL) /* 0xe000ed00 */
#define MPU_BASE            (SCS_BASE +  0x0D90UL) /* 0xe000ed90 */

struct PWR_STR
{
  __IO uint32_t CR;
  __IO uint32_t CSR;
};


struct RCC_STR
{
  __IO uint32_t CR;			/* 0x40021000 */
  __IO uint32_t CFGR;			/* 0x40021004 */
  __IO uint32_t CIR;			/* 0x40021008 */
  __IO uint32_t APB2RSTR;		/* 0x4002100c */
  __IO uint32_t APB1RSTR;		/* 0x40021010 */
  __IO uint32_t AHBENR;                 /* 0x40021014 */
  __IO uint32_t APB2ENR;                /* 0x40021018 */
  __IO uint32_t APB1ENR;                /* 0x4002101c */
  __IO uint32_t BDCR;
  __IO uint32_t CSR;
};

struct FLASH_STR
{
  __IO uint32_t ACR;
  __IO uint32_t KEYR;
  __IO uint32_t OPTKEYR;
  __IO uint32_t SR;
  __IO uint32_t CR;
  __IO uint32_t AR;
  __IO uint32_t RESERVED;
  __IO uint32_t OBR;
  __IO uint32_t WRPR;
};

struct USART_STR
{
  __IO uint32_t SR;         /* Status register,   0x40013800      */
  __IO uint32_t DR;         /* Data register,     0x40013804      */
  __IO uint32_t BRR;        /* Baud rate register,0x40013808      */
  __IO uint32_t CR1;        /* Control register 1,0x4001380c      */
  __IO uint32_t CR2;        /* Control register 2,0x40013810      */
  __IO uint32_t CR3;        /* Control register 3,0x40013814      */
  __IO uint32_t GTPR;       /* Guard time and prescaler register, */
};

struct GPIO_STR
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
};

struct AFIO_STR
{
  __IO uint32_t EVCR;
  __IO uint32_t MAPR;
  __IO uint32_t EXTICR[4];
  uint32_t RESERVED0;
  __IO uint32_t MAPR2;  
};

struct SysTick_STR
{
  __IO uint32_t CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
  __IO uint32_t VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
  __I  uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
};

struct EXTI_STR
{
  __IO uint32_t IMR;
  __IO uint32_t EMR;
  __IO uint32_t RTSR;
  __IO uint32_t FTSR;
  __IO uint32_t SWIER;
  __IO uint32_t PR;
};

struct NVIC_STR
{
  __IO uint32_t ISER[8];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
       uint32_t RESERVED0[24];
  __IO uint32_t ICER[8];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register         */
       uint32_t RSERVED1[24];
  __IO uint32_t ISPR[8];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register          */
       uint32_t RESERVED2[24];
  __IO uint32_t ICPR[8];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register        */
       uint32_t RESERVED3[24];
  __IO uint32_t IABR[8];                 /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register           */
       uint32_t RESERVED4[56];
  __IO uint8_t  IP[240];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644];
  __O  uint32_t STIR;                    /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register     */
};

/** \brief  Structure type to access the System Control Block (SCB).
 */
struct SCB_STR
{
  __I  uint32_t CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
  __IO uint32_t ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
  __IO uint32_t VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
  __IO uint32_t AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
  __IO uint32_t SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
  __IO uint32_t CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
  __IO uint8_t  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IO uint32_t SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
  __IO uint32_t CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
  __IO uint32_t HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
  __IO uint32_t DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
  __IO uint32_t MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
  __IO uint32_t BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
  __IO uint32_t AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
  __I  uint32_t PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
  __I  uint32_t DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
  __I  uint32_t ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
  __I  uint32_t MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
  __I  uint32_t ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
       uint32_t RESERVED0[5];
  __IO uint32_t CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
};


/** \brief  Structure type to access the Memory Protection Unit (MPU).
 */
struct MPU_STR
{
  __I  uint32_t TYPE;                    /*!< Offset: 0x000 (R/ )  MPU Type Register                              */
  __IO uint32_t CTRL;                    /*!< Offset: 0x004 (R/W)  MPU Control Register                           */
  __IO uint32_t RNR;                     /*!< Offset: 0x008 (R/W)  MPU Region RNRber Register                     */
  __IO uint32_t RBAR;                    /*!< Offset: 0x00C (R/W)  MPU Region Base Address Register               */
  __IO uint32_t RASR;                    /*!< Offset: 0x010 (R/W)  MPU Region Attribute and Size Register         */
  __IO uint32_t RBAR_A1;                 /*!< Offset: 0x014 (R/W)  MPU Alias 1 Region Base Address Register       */
  __IO uint32_t RASR_A1;                 /*!< Offset: 0x018 (R/W)  MPU Alias 1 Region Attribute and Size Register */
  __IO uint32_t RBAR_A2;                 /*!< Offset: 0x01C (R/W)  MPU Alias 2 Region Base Address Register       */
  __IO uint32_t RASR_A2;                 /*!< Offset: 0x020 (R/W)  MPU Alias 2 Region Attribute and Size Register */
  __IO uint32_t RBAR_A3;                 /*!< Offset: 0x024 (R/W)  MPU Alias 3 Region Base Address Register       */
  __IO uint32_t RASR_A3;                 /*!< Offset: 0x028 (R/W)  MPU Alias 3 Region Attribute and Size Register */
};

#define RCC                 ((struct RCC_STR *) RCC_BASE)
#define FLASH               ((struct FLASH_STR *) FLASH_R_BASE)
#define USART1              ((struct USART_STR *) USART1_BASE)
#define GPIOA               ((struct GPIO_STR *) GPIOA_BASE)
#define GPIOB               ((struct GPIO_STR *) GPIOB_BASE)
#define GPIOC               ((struct GPIO_STR *) GPIOC_BASE)
#define GPIOD               ((struct GPIO_STR *) GPIOD_BASE)
#define GPIOE               ((struct GPIO_STR *) GPIOE_BASE)
#define AFIO                ((struct AFIO_STR *) AFIO_BASE)
#define SysTick             ((struct SysTick_STR *) SysTick_BASE)   /*!< SysTick configuration struct       */
#define EXTI                ((struct EXTI_STR *) EXTI_BASE)
#define NVIC                ((struct NVIC_STR *) NVIC_BASE)   /*!< NVIC configuration struct          */
#define SCB                 ((struct SCB_STR *)  SCB_BASE)   /*!< SCB configuration struct           */
#define MPU		    ((struct MPU_STR *)  MPU_BASE)   /*!< Memory Protection Unit */ 
#define PWR                 ((struct PWR_STR *) PWR_BASE)

/* global variable */

extern __IO uint32_t uwTick;

/* kernel */
uint32_t GetPSP(void);
uint32_t GetSP(void);
void SetupPSP(uint32_t address);
void SwitchToUserMode(void);
int kprintf(const char *format, ...);
void activate(uint32_t address);
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
