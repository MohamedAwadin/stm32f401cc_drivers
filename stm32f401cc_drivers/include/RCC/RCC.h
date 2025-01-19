#ifndef RCC_H
#define RCC_H

#include "../COMMON/StdTypes.h"


#define RCC_BASE 0x40023800U


#define RCC_PLL_EN_MSK 0x300000
#define RCC_PLL_EN_MSK 0x300000

typedef struct{
	volatile u32 RCC_CR ;
	volatile u32 RCC_PLLCFGR ;
	volatile u32 RCC_CFGR ;
	volatile u32 RCC_CIR ;
	volatile u32 RCC_AHB1RSTR ;
	volatile u32 RCC_AHB2RSTR ;
	volatile u32 RESERVER0[2] ; /*reserved*/
	volatile u32 RCC_APB1RSTR ;
	volatile u32 RCC_APB2RSTR ;
	volatile u32 RESERVER1[2] ; /*reserved*/
	volatile u32 RCC_AHB1ENR ;
	volatile u32 RCC_AHB2ENR ;
	volatile u32 RESERVER2[2] ; /*reserved*/
	volatile u32 RCC_APB1ENR ;
	volatile u32 RCC_APB2ENR ;
	volatile u32 RESERVER3[2] ; /*reserved*/
	volatile u32 RCC_AHB1LPENR ;
	volatile u32 RCC_AHB2LPENR ;
	volatile u32 RESERVER4[2] ; /*reserved*/
	volatile u32 RCC_APB1LPENR ;
	volatile u32 RCC_APB2LPENR ;
	volatile u32 RESERVER5[2] ; /*reserved*/
	volatile u32 RCC_BDCR ;
	volatile u32 RCC_CSR ;
	volatile u32 RCC_SSCGR ;
	volatile u32 RCC_PLLI2SCFGR ;
	volatile u32 RESERVER6 ;/*reserved*/
	volatile u32 RCC_DCKCFGR;
}RCC_REG_type;


#define RCC ((RCC_REG_type *)(RCC_BASE))



typedef enum{
	RCC_enuHSI_CLOCK =0,
	RCC_enuHSE_CLOCK,
	RCC_enuPLL_CLOCK 
}RCC_enumSetClk_Source_t;


typedef enum{
	RCC_enuCLK_OFF=0, 
	RCC_enuCLK_ON
}RCC_enumSetClk_Status_t;

typedef enum{
	RCC_enuCLK_NOTRDY = 0x00,
	RCC_enuCLK_RDY    = 0x01 
}RCC_enumREADYStatus_t;

typedef enum{
	RCC_enuCLK_BYPASS_ON     = 0,
	RCC_enuCLK_BYPASS_OFF    = 1 
}RCC_enumHSE_BYPASS_Status_t;


typedef enum{
	RCC_enuOk = 0,
	RCC_enuErrorClock,
	RCC_enuErrorClkNotRdy,
	RCC_enuErrorContrlStatus,
	RCC_enuErrorSelectedSysClk,
	RCC_enuErrorNullPointer,
	RCC_enuErrorPLLON,
	RCC_enuErrorMDivion,
	RCC_enuErrorNFactor,
	RCC_enuErrorPLLP,
	RCC_enuErrorPLLQ,
	RCC_enuErrorBus,
	RCC_enuErrorTimedOut,
	RCC_enuErrorBusPrescaler,
	RCC_enuErrorSelectedPllClk
}RCC_enumErrorStatus_t;


typedef enum{
	RCC_enu_P_DivBy2,
	RCC_enu_P_DivBy4,
	RCC_enu_P_DivBy6,
	RCC_enu_P_DivBy8
}RCC_enumPLL_P_t;


typedef enum{
	RCC_enu_Q_DivBy2,
	RCC_enu_Q_DivBy3,
	RCC_enu_Q_DivBy4,
	RCC_enu_Q_DivBy5,
	RCC_enu_Q_DivBy6,
	RCC_enu_Q_DivBy7,
	RCC_enu_Q_DivBy8,
	RCC_enu_Q_DivBy9,
	RCC_enu_Q_DivBy10,
	RCC_enu_Q_DivBy11,
	RCC_enu_Q_DivBy12,
	RCC_enu_Q_DivBy13,
	RCC_enu_Q_DivBy14,
	RCC_enu_Q_DivBy15
}RCC_enumPLL_Q_t;


typedef struct{
	u32 					RCC_u32DivisionFactor_M;
	RCC_enumPLL_P_t			RCC_enumPLL_P;
	RCC_enumPLL_Q_t			RCC_enumPLL_Q;
	u16 					RCC_u16MultFactor_N;
	RCC_enumSetClk_Source_t	RCC_enumClockSource ; 
}RCC_strPLLConfig_t;

// Register identifiers (upper 32 bits)
#define    RCC_AHB1ENR_REG  (0x0000000100000000ULL) // AHB1ENR register
#define    RCC_AHB2ENR_REG  (0x0000000200000000ULL) // AHB2ENR register
#define    RCC_APB1ENR_REG  (0x0000000300000000ULL) // APB1ENR register
#define    RCC_APB2ENR_REG  (0x0000000400000000ULL) // APB2ENR register



    
// Peripheral bits (lower 32 bits)
#define    RCC_AHB1ENR_GPIOAEN  (RCC_AHB1ENR_REG | 0x00000001)  // GPIOA clock enable
#define    RCC_AHB1ENR_GPIOBEN  (RCC_AHB1ENR_REG | 0x00000002)  // GPIOB clock enable
#define    RCC_AHB1ENR_GPIOCEN  (RCC_AHB1ENR_REG | 0x00000004)  // GPIOC clock enable
#define    RCC_AHB1ENR_GPIODEN  (RCC_AHB1ENR_REG | 0x00000008)  // GPIOD clock enable
#define    RCC_AHB1ENR_GPIOEEN  (RCC_AHB1ENR_REG | 0x00000010)  // GPIOE clock enable
#define    RCC_AHB1ENR_GPIOHEN  (RCC_AHB1ENR_REG | 0x00000080)  // GPIOH clock enable
#define    RCC_AHB1ENR_CRCEN    (RCC_AHB1ENR_REG | 0x00001000)  // CRC clock enable
#define    RCC_AHB1ENR_DMA1EN   (RCC_AHB1ENR_REG | 0x00200000)  // DMA1 clock enable
#define    RCC_AHB1ENR_DMA2EN   (RCC_AHB1ENR_REG | 0x00400000)  // DMA2 clock enable

#define    RCC_AHB2ENR_OTGFSEN  (RCC_AHB2ENR_REG | 0x00000080)  // USB OTG FS clock enable

#define    RCC_APB1ENR_TIM2EN    (RCC_APB1ENR_REG | 0x00000001)  // TIM2 clock enable
#define    RCC_APB1ENR_TIM3EN    (RCC_APB1ENR_REG | 0x00000002)  // TIM3 clock enable
#define    RCC_APB1ENR_TIM4EN    (RCC_APB1ENR_REG | 0x00000004)  // TIM4 clock enable
#define    RCC_APB1ENR_TIM5EN    (RCC_APB1ENR_REG | 0x00000008)  // TIM5 clock enable
#define    RCC_APB1ENR_WWDGEN    (RCC_APB1ENR_REG | 0x00000800)  // WWDG clock enable
#define    RCC_APB1ENR_SPI2EN    (RCC_APB1ENR_REG | 0x00004000)  // SPI2 clock enable
#define    RCC_APB1ENR_SPI3EN    (RCC_APB1ENR_REG | 0x00008000)  // SPI3 clock enable
#define    RCC_APB1ENR_USART2EN  (RCC_APB1ENR_REG | 0x00020000)  // USART2 clock enable
#define    RCC_APB1ENR_I2C1EN    (RCC_APB1ENR_REG | 0x00200000)  // I2C1 clock enable
#define    RCC_APB1ENR_I2C2EN    (RCC_APB1ENR_REG | 0x00400000)  // I2C2 clock enable
#define    RCC_APB1ENR_I2C3EN    (RCC_APB1ENR_REG | 0x00800000)  // I2C3 clock enable
#define    RCC_APB1ENR_PWREN     (RCC_APB1ENR_REG | 0x10000000)  // PWR clock enable

#define    RCC_APB2ENR_TIM1EN    (RCC_APB2ENR_REG | 0x00000001)  // TIM1 clock enable
#define    RCC_APB2ENR_USART1EN  (RCC_APB2ENR_REG | 0x00000010)  // USART1 clock enable
#define    RCC_APB2ENR_USART6EN  (RCC_APB2ENR_REG | 0x00000020)  // USART6 clock enable
#define    RCC_APB2ENR_ADC1EN    (RCC_APB2ENR_REG | 0x00000100)  // ADC1 clock enable
#define    RCC_APB2ENR_SDIOEN    (RCC_APB2ENR_REG | 0x00000800)  // SDIO clock enable
#define    RCC_APB2ENR_SPI1EN    (RCC_APB2ENR_REG | 0x00001000)  // SPI1 clock enable
#define    RCC_APB2ENR_SPI4EN    (RCC_APB2ENR_REG | 0x00002000)  // SPI4 clock enable
#define    RCC_APB2ENR_SYSCFGEN  (RCC_APB2ENR_REG | 0x00004000)  // SYSCFG clock enable
#define    RCC_APB2ENR_TIM9EN    (RCC_APB2ENR_REG | 0x00010000)  // TIM9 clock enable
#define    RCC_APB2ENR_TIM10EN   (RCC_APB2ENR_REG | 0x00020000)  // TIM10 clock enable
#define    RCC_APB2ENR_TIM11EN   (RCC_APB2ENR_REG | 0x00040000)  // TIM11 clock enable

/*===========================================================*/
/*
		Function Prototypes 
*/
/*===========================================================*/

RCC_enumErrorStatus_t RCC_SetClk_Status (RCC_enumSetClk_Source_t source ,RCC_enumSetClk_Status_t status );

RCC_enumErrorStatus_t RCC_enuControlSysClock(RCC_enumSetClk_Source_t source);

RCC_enumErrorStatus_t RCC_enuGetClockRdyStatus(RCC_enumSetClk_Source_t source , pu8 Add_pu8RtrnRdyStatus);

RCC_enumErrorStatus_t RCC_PLLConfig(RCC_strPLLConfig_t Copy_strPLLConfig_t );

RCC_enumErrorStatus_t RCC_EnableClock(u64 peripheral) ;
RCC_enumErrorStatus_t RCC_DisableClock(u64 peripheral);



// RCC_enumErrorStatus_t RCC_AHB1EnableClock(RCC_enumAHB1ENR_Bits_t Copy_enumAHB1_peripheral);
// RCC_enumErrorStatus_t RCC_AHB1DisableClock(RCC_enumAHB1ENR_Bits_t Copy_enumAHB1_peripheral);
// RCC_enumErrorStatus_t RCC_AHB2EnableClock(RCC_enumAHB2ENR_Bits_t Copy_enumAHB2_peripheral);
// RCC_enumErrorStatus_t RCC_AHB2DisableClock(RCC_enumAHB2ENR_Bits_t Copy_enumAHB2_peripheral);

// RCC_enumErrorStatus_t RCC_APB1EnableClock(RCC_enumAPB1ENR_Bits_t Copy_enumAPB1_peripheral);
// RCC_enumErrorStatus_t RCC_APB1DisableClock(RCC_enumAPB1ENR_Bits_t Copy_enumAPB1_peripheral);


// RCC_enumErrorStatus_t RCC_APB2EnableClock(RCC_enumAPB2ENR_Bits_t Copy_enumAPB2_peripheral);
// RCC_enumErrorStatus_t RCC_APB2DisableClock(RCC_enumAPB2ENR_Bits_t Copy_enumAPB2_peripheral);

#endif /*RCC_H*/