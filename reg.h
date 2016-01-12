#define uint32_t	unsigned int
#define __IO		volatile
#define __I		volatile const

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

/*< System Control Space Base Address  */
#define SCS_BASE            (0xE000E000UL)                           
/*< SysTick Base Address               */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    

struct RCC_STR {
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

struct FLASH_STR {
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

struct USART_STR {
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

struct AFIO_STR {
  __IO uint32_t EVCR;
  __IO uint32_t MAPR;
  __IO uint32_t EXTICR[4];
  uint32_t RESERVED0;
  __IO uint32_t MAPR2;  
};

struct SysTick_STR {
  __IO uint32_t CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
  __IO uint32_t VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
  __I  uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
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
