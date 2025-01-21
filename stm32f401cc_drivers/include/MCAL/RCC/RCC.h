#ifndef RCC_H
#define RCC_H

#include "../../COMMON/StdTypes.h"
#include "RCC_private.h"

/*****************************MACROS*********************************/
#define	RCC_CLK_NOTRDY           (0x00)
#define RCC_CLK_RDY              (0x01)


#define RCC_APB1_PRE_DIV2	         (0x00001000) 
#define RCC_APB1_PRE_DIV4	         (0x00001400) 
#define RCC_APB1_PRE_DIV8	         (0x00001800) 
#define RCC_APB1_PRE_DIV16	         (0x00001C00) 
         
#define RCC_APB2_PRE_DIV2	         (0x00008000) 
#define RCC_APB2_PRE_DIV4	         (0x0000A000) 
#define RCC_APB2_PRE_DIV8	         (0x0000C000) 
#define RCC_APB2_PRE_DIV16	         (0x0000E000) 
         
#define RCC_AHB_PRE_DIV2	         (0x00000080)	
#define RCC_AHB_PRE_DIV4	         (0x00000090)	
#define RCC_AHB_PRE_DIV8	         (0x000000A0)	
#define RCC_AHB_PRE_DIV16	         (0x000000B0)	
#define RCC_AHB_PRE_DIV64	         (0x000000C0)	
#define RCC_AHB_PRE_DIV128	         (0x000000D0)	
#define RCC_AHB_PRE_DIV256	         (0x000000E0)	
#define RCC_AHB_PRE_DIV512	         (0x000000F0)	


// Peripheral bits (lower 32 bits) musks
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


/************************************************************** */
/**
 * @struct RCC_strREG_type
 * @brief Structure representing the RCC registers.
 */
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
}RCC_strREG_type;

/**
 * @def RCC
 * @brief Macro to access the RCC registers.
 */
#define RCC ((RCC_strREG_type *)(RCC_BASE))



/****************************************************
 ************** Enumerations ************************
 *****************************************************/


/**
 * @enum RCC_enumSetClk_Status_t
 * @brief Enumeration for clock status.
 */
typedef enum{
	RCC_enumHSI_CLOCK =0,
	RCC_enumHSE_CLOCK,
	RCC_enumPLL_CLOCK 
}RCC_enumSetClk_Source_t;

/**
 * @enum RCC_enumSetClk_Status_t
 * @brief Enumeration for clock status.
 */

typedef enum{
	RCC_enumCLK_OFF=0, 
	RCC_enumCLK_ON
}RCC_enumSetClk_Status_t;

/**
 * @enum RCC_enumHSE_BYPASS_Status_t
 * @brief Enumeration for HSE bypass status.
 */
typedef enum{
	RCC_enumCLK_BYPASS_OFF    = 0,
	RCC_enumCLK_BYPASS_ON    
}RCC_enumHSE_BYPASS_Status_t;

/**
 * @enum RCC_enumErrorStatus_t
 * @brief Enumeration for error status.
 */
typedef enum{
	RCC_enumOk = 0,
	RCC_enumErrorClock,
	RCC_enumErrorClkNotRdy,
	RCC_enumErrorSetClkStatus,
	RCC_enumErrorSelectSysClk,
	RCC_enumErrorNullPointer,
	RCC_enumErrorPLLON,
	RCC_enumErrorPLL_MDivFactor,
	RCC_enumErrorPLL_NMulFactor,
	RCC_enumErrorPLL_PDivFactor,
	RCC_enumErrorPLL_QDivFactor,
	RCC_enumErrorHSEBYPASS,
	RCC_enumErrorBus,
	RCC_enumErrorTimedOut,
	RCC_enumErrorBusPrescaler,
	RCC_enumErrorSelectPllClk
}RCC_enumErrorStatus_t;

/**
 * @enum RCC_enumPLL_P_t
 * @brief Enumeration for PLL P division factors.
 */
typedef enum{
	RCC_enum_P_DivBy2,
	RCC_enum_P_DivBy4,
	RCC_enum_P_DivBy6,
	RCC_enum_P_DivBy8
}RCC_enumPLL_P_t;

/**
 * @enum RCC_enumPLL_Q_t
 * @brief Enumeration for PLL Q division factors.
 */
typedef enum{
	RCC_enum_Q_DivBy2,
	RCC_enum_Q_DivBy3,
	RCC_enum_Q_DivBy4,
	RCC_enum_Q_DivBy5,
	RCC_enum_Q_DivBy6,
	RCC_enum_Q_DivBy7,
	RCC_enum_Q_DivBy8,
	RCC_enum_Q_DivBy9,
	RCC_enum_Q_DivBy10,
	RCC_enum_Q_DivBy11,
	RCC_enum_Q_DivBy12,
	RCC_enum_Q_DivBy13,
	RCC_enum_Q_DivBy14,
	RCC_enum_Q_DivBy15
}RCC_enumPLL_Q_t;
/********************************************************************* */

/**
 * @struct RCC_strPLLConfig_t
 * @brief Structure for PLL configuration.
 */
typedef struct{
	u32 					RCC_u32DivisionFactor_M;  /**< PLL M division factor */
	RCC_enumPLL_P_t			RCC_enumPLL_P;  		  /**< PLL P division factor */
	RCC_enumPLL_Q_t			RCC_enumPLL_Q;  		  /**< PLL Q division factor */
	u16 					RCC_u16MultFactor_N;      /**< PLL N multiplication factor */
	RCC_enumSetClk_Source_t	RCC_enumClockSource ;     /**< PLL clock source */
}RCC_strPLLConfig_t;


    

/*****************************************************************************
 * 							Function Prototypes 							 *
 * 																			 *
 ******************************************************************************/
/**
 * @brief Controls the system clock source by selecting the desired clock source (HSI, HSE, or PLL).
 * @details This function switches the system clock to the specified source (HSI, HSE, or PLL) if the clock is ready.
 *          It waits for the clock switch to complete and returns an error status if the switch fails or if the clock is not ready.
 * @param Copy_enumSource The clock source to be selected:
 * 							- RCC_enumHSI_CLOCK  < HSI clock source 
 *							- RCC_enumHSE_CLOCK  < HSE clock source 
 *							- RCC_enumPLL_CLOCK  < PLL clock source
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the clock switch is successful, or an error status if the switch fails.
 */
RCC_enumErrorStatus_t RCC_enuControlSysClock(RCC_enumSetClk_Source_t Copy_enumSource);

/**
 * @brief Sets the status (ON/OFF) of a specific clock source (HSI, HSE, or PLL).
 * @details This function enables or disables the specified clock source (HSI, HSE, or PLL) based on the provided status.
 *          It waits for the clock to stabilize (if enabling) and returns an error status if the operation fails.
 * @param Copy_enumSource The clock source to be selected:
 * 							- RCC_enumHSI_CLOCK  < HSI clock source 
 *							- RCC_enumHSE_CLOCK  < HSE clock source 
 *							- RCC_enumPLL_CLOCK  < PLL clock source
 * @param Copy_enumStatus The desired clock status (`RCC_enumCLK_ON` or `RCC_enumCLK_OFF`).
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the operation is successful, or an error status if it fails.
 */
RCC_enumErrorStatus_t RCC_enuSetClock_Status(RCC_enumSetClk_Source_t Copy_enumSource, RCC_enumSetClk_Status_t Copy_enumStatus);

/**
 * @brief Configures the PLL (Phase-Locked Loop) with the specified parameters.
 * @details This function sets up the PLL with the provided configuration, including the M, N, P, and Q factors, as well as the clock source.
 *          It checks for valid input parameters and returns an error status if any parameter is invalid or if the PLL is already enabled.
 * @param Copy_strPLLConfig_t A structure containing the PLL configuration parameters (M, N, P, Q factors, and clock source).
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the PLL is configured successfully, or an error status if the configuration fails.
 */
RCC_enumErrorStatus_t RCC_enuPLLConfig(RCC_strPLLConfig_t Copy_strPLLConfig_t);

/**
 * @brief Enables the clock for a specific peripheral.
 * @details This function enables the clock for the specified peripheral by setting the corresponding bit in the appropriate clock enable register (AHB1ENR, AHB2ENR, APB1ENR, or APB2ENR).
 * @param Copy_u64peripheral A 64-bit value representing the peripheral to be enabled. The upper 32 bits specify the register, and the lower 32 bits specify the bit position.
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the clock is enabled successfully, or an error status if the register is invalid.
 */
RCC_enumErrorStatus_t RCC_enuEnableClock(u64 Copy_u64peripheral);

/**
 * @brief Disables the clock for a specific peripheral.
 * @details This function disables the clock for the specified peripheral by clearing the corresponding bit in the appropriate clock enable register (AHB1ENR, AHB2ENR, APB1ENR, or APB2ENR).
 * @param Copy_u64peripheral A 64-bit value representing the peripheral to be disabled. The upper 32 bits specify the register, and the lower 32 bits specify the bit position.
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the clock is disabled successfully, or an error status if the register is invalid.
 */
RCC_enumErrorStatus_t RCC_enuDisableClock(u64 Copy_u64peripheral);

/**
 * @brief Retrieves the ready status of a specific clock source (HSI, HSE, or PLL).
 * @details This function checks if the specified clock source is ready and stores the result in the provided pointer.
 *          It returns an error status if the clock source is invalid or if the pointer is null.
 * @param Copy_enumSource The clock source to be selected:
 * 							- RCC_enumHSI_CLOCK  < HSI clock source 
 *							- RCC_enumHSE_CLOCK  < HSE clock source 
 *							- RCC_enumPLL_CLOCK  < PLL clock source
 * @param Add_pu8ReadyStatus A pointer to store the ready status (`RCC_enumCLK_RDY` or `RCC_enumCLK_NOTRDY`).
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the status is retrieved successfully, or an error status if the operation fails.
 */
RCC_enumErrorStatus_t RCC_enuGetClkReadyStatus(RCC_enumSetClk_Source_t Copy_enumSource, u8 *Add_pu8ReadyStatus);

/**
 * @brief Configures the prescaler for the low-speed APB1 bus.
 * @details This function sets the prescaler value for the APB1 bus, which controls the clock speed for peripherals connected to this bus.
 *          It checks for valid prescaler values and returns an error status if the provided value is invalid.
 * @param Copy_u32APB1_Prescalar The prescaler value for the APB1 bus: 
 * 								- RCC_APB1_PRE_DIV2	
 * 								- RCC_APB1_PRE_DIV4	
 * 								- RCC_APB1_PRE_DIV8	
 * 								- RCC_APB1_PRE_DIV16
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the prescaler is configured successfully, or an error status if the value is invalid.
 */
RCC_enumErrorStatus_t RCC_enuConfigurePreScalarLowSpeedAPB(u32 Copy_u8APB1_Prescalar);

/**
 * @brief Configures the prescaler for the high-speed APB2 bus.
 * @details This function sets the prescaler value for the APB2 bus, which controls the clock speed for peripherals connected to this bus.
 *          It checks for valid prescaler values and returns an error status if the provided value is invalid.
 * @param Copy_u32APB2_Prescalar The prescaler value for the APB2 bus: 
 * 								- RCC_APB2_PRE_DIV2	
 * 								- RCC_APB2_PRE_DIV4	
 * 								- RCC_APB2_PRE_DIV8	
 * 								- RCC_APB2_PRE_DIV16	
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the prescaler is configured successfully, or an error status if the value is invalid.
 */
RCC_enumErrorStatus_t RCC_enuConfigurePreScalarHighSpeedAPB(u32 Copy_u32APB2_Prescalar);

/**
 * @brief Configures the prescaler for the AHB bus.
 * @details This function sets the prescaler value for the AHB bus, which controls the clock speed for peripherals connected to this bus.
 *          It checks for valid prescaler values and returns an error status if the provided value is invalid.
 * @param Copy_u32AHB_Prescalar The prescaler value for the AHB bus :
 * 								-RCC_AHB_PRE_DIV2	  
 *								-RCC_AHB_PRE_DIV4	  
 *								-RCC_AHB_PRE_DIV8	  
 *								-RCC_AHB_PRE_DIV16	 
 *								-RCC_AHB_PRE_DIV64	 
 *								-RCC_AHB_PRE_DIV128	
 *								-RCC_AHB_PRE_DIV256	
 *								-RCC_AHB_PRE_DIV512
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the prescaler is configured successfully, or an error status if the value is invalid.
 */
RCC_enumErrorStatus_t RCC_enuConfigurePreScalarAHB(u32 Copy_u32AHB_Prescalar);

/**
 * @brief Sets the HSE (High-Speed External) clock bypass status.
 * @details This function enables or disables the HSE clock bypass, which allows the use of an external clock signal directly.
 *          It checks if the HSE clock is ready before modifying the bypass status and returns an error status if the operation fails.
 * @param Copy_u32Bypass_status The bypass status to be set (`RCC_enumCLK_BYPASS_ON` or `RCC_enumCLK_BYPASS_OFF`).
 * @return RCC_enumErrorStatus_t Returns `RCC_enumOk` if the bypass status is set successfully, or an error status if the operation fails.
 */
RCC_enumErrorStatus_t RCC_enuHES_BYPASS_Status(u32 Copy_u32Bypass_status);


#endif /*RCC_H*/