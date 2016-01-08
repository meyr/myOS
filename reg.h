#define uint32_t	unsigned int
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
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)

struct RCC_STR {
  volatile uint32_t CR;			/* 0x40021000 */
  volatile uint32_t CFGR;		/* 0x40021004 */
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
};

struct FLASH_STR {
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
};

struct USART_STR {
  volatile uint32_t SR;         /* Status register,   0x40013800      */
  volatile uint32_t DR;         /* Data register,     0x40013804      */
  volatile uint32_t BRR;        /* Baud rate register,0x40013808      */
  volatile uint32_t CR1;        /* Control register 1,0x4001380c      */
  volatile uint32_t CR2;        /* Control register 2,0x40013810      */
  volatile uint32_t CR3;        /* Control register 3,0x40013814      */
  volatile uint32_t GTPR;       /* Guard time and prescaler register, */
};

struct GPIO_STR
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
};


#define RCC                 ((struct RCC_STR *) RCC_BASE)
#define FLASH               ((struct FLASH_STR *) FLASH_R_BASE)
#define USART1              ((struct USART_STR *) USART1_BASE)
#define GPIOA               ((struct GPIO_STR *) GPIOA_BASE)
#define GPIOB               ((struct GPIO_STR *) GPIOB_BASE)
#define GPIOC               ((struct GPIO_STR *) GPIOC_BASE)
#define GPIOD               ((struct GPIO_STR *) GPIOD_BASE)
#define GPIOE               ((struct GPIO_STR *) GPIOE_BASE)
