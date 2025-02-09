#ifndef NVIC_H
#define NVIC_H

#include "../../COMMON/StdTypes.h"
#include "NVIC_private.h"


#define NVIC_PRIORITY_GROUP_0   (0x00000000U) 
#define NVIC_PRIORITY_GROUP_1   (0x00000100U) 
#define NVIC_PRIORITY_GROUP_2   (0x00000200U) 
#define NVIC_PRIORITY_GROUP_3   (0x00000300U) 
#define NVIC_PRIORITY_GROUP_4   (0x00000400U) 




/*Priority Bits in STM32F401cc*/
#define NVIC_PRIO_BITS          4U

/**************************************************************************/
/*						IRQ Table - STM32F401cc						 	  */
/**************************************************************************/

typedef enum
{
    /* -------------------  Cortex-M4 Processor Exceptions Numbers  ------------------- */
    NVIC_NonMaskableInt_IRQn = -14,   /*  2 Non Maskable Interrupt */
    NVIC_HardFault_IRQn = -13,        /*  3 HardFault Interrupt */
    NVIC_MemoryManagement_IRQn = -12, /*  4 Memory Management Interrupt */
    NVIC_BusFault_IRQn = -11,         /*  5 Bus Fault Interrupt */
    NVIC_UsageFault_IRQn = -10,       /*  6 Usage Fault Interrupt */
    NVIC_SVCall_IRQn = -5,            /* 11 SV Call Interrupt */
    NVIC_DebugMonitor_IRQn = -4,      /* 12 Debug Monitor Interrupt */
    NVIC_PendSV_IRQn = -2,            /* 14 Pend SV Interrupt */
    NVIC_SysTick_IRQn = -1,           /* 15 System Tick Interrupt */

    /* ----------------------  ARMCM4 Specific Interrupt Numbers  --------------------- */
    NVIC_WINDOW_WATCHDOG_TIMER = 0,
    NVIC_EXTERNAL_LINE16 = 1,
    NVIC_EXTERNAL_LINE21 = 2,
    NVIC_EXTERNAL_LINE22 = 3,
    NVIC_FLASH_INTERRUPT = 4,
    NVIC_RCC_INTERRUPT = 5,
    NVIC_EXTI0_INTERRRUPT = 6,
    NVIC_EXTI1_INTERRRUPT = 7,
    NVIC_EXTI2_INTERRRUPT = 8,
    NVIC_EXTI3_INTERRRUPT = 9,
    NVIC_EXTI4_INTERRRUPT = 10,
    NVIC_DMA1_STREAM0 = 11,
    NVIC_DMA1_STREAM1 = 12,
    NVIC_DMA1_STREAM2 = 13,
    NVIC_DMA1_STREAM3 = 14,
    NVIC_DMA1_STREAM4 = 15,
    NVIC_DMA1_STREAM5 = 16,
    NVIC_DMA1_STREAM6 = 17,
    NVIC_ADC_INTERRUPT = 18,
    NVIC_EXTI9_INTERRUPT = 23,
    NVIC_TIM1_BRK_INTERRUPT = 24,
    NVIC_TIM1_UP_INTERRUPT = 25,
    NVIC_TIMI1_TRG_INTERRUPT = 26,
    NVIC_TIMI1_CC_INTERRUPT = 27,
    NVIC_TIMI2_INTERRUPT = 28,
    NVIC_TIMI3_INTERRUPT = 29,
    NVIC_TIMI4_INTERRUPT = 30,
    NVIC_I2C1_EV_INTERRUPT = 31,
    NVIC_I2C1_ER_INTERRUPT = 32,
    NVIC_I2C2_EV_INTERRUPT = 33,
    NVIC_I2C2_ER_INTERRUPT = 34,
    NVIC_SPI1_INTERRUPT = 35,
    NVIC_SPI2_INTERRUPT = 36,
    NVIC_USART1_INTERRUPT = 37,
    NVIC_USART2_INTERRUPT = 38,
    NVIC_EXTI15_INTERRUPT = 40,
    NVIC_EXTI17_INTERRUPT = 41,
    NVIC_EXTI18_INTERRUPT = 42,
    NVIC_DMA1_INTERRUPT = 47,
    NVIC_SDIO_INTERRUPT = 49,
    NVIC_TIM5_INTERRUPT = 50,
    NVIC_SPI3_INTERRUPT = 51,
    NVIC_DMA2_STREAM0_INTERRUPT = 56,
    NVIC_DMA2_STREAM1_INTERRUPT = 57,
    NVIC_DMA2_STREAM2_INTERRUPT = 58,
    NVIC_DMA2_STREAM3_INTERRUPT = 59,
    NVIC_DMA2_STREAM4_INTERRUPT = 60,
    NVIC_OTG_FS_INTERRUPT = 67,
    NVIC_DMA2_STREAM5_INTERRUPT = 68,
    NVIC_DMA2_STREAM6_INTERRUPT = 69,
    NVIC_DMA2_STREAM7_INTERRUPT = 70,
    NVIC_USART6_INTERRUPT = 71,
    NVIC_I2C3_EV_INTERRUPT = 72,
    NVIC_I2C3_ER_INTERRUPT = 73,
    NVIC_FPU_INTERRUPT = 81,
    NVIC_SPI4_INTERRUPT = 84,
    
} NVIC_enumIRQn_Type;

typedef enum
{
    NVIC_enumOk,
    NVIC_enumNOk,
    NVIC_enumErrorIRQNumber,
    NVIC_enumErrorNullPointer,
    NVIC_enumErrorPriorityGroup,
    NVIC_enumErrorPreemptPriority,
    NVIC_enumErrorSubPriority

} NVIC_ErrorStatus_t;

NVIC_ErrorStatus_t NVIC_enumEnableIRQ(NVIC_enumIRQn_Type Copy_enuIRQn);
NVIC_ErrorStatus_t NVIC_enumDisableIRQ(NVIC_enumIRQn_Type Copy_enuIRQn);
NVIC_ErrorStatus_t NVIC_enumSetPendingIRQ(NVIC_enumIRQn_Type Copy_enuIRQn);
NVIC_ErrorStatus_t NVIC_enumClearPendingIRQ(NVIC_enumIRQn_Type Copy_enuIRQn);
NVIC_ErrorStatus_t NVIC_enumGetPendingIRQ(NVIC_enumIRQn_Type Copy_enuIRQn, u8 *Add_pu8GetPendingStatus);
NVIC_ErrorStatus_t NVIC_enumSetPriority(NVIC_enumIRQn_Type Copy_enuIRQn, u32 Copy_u32Priority);
NVIC_ErrorStatus_t NVIC_enumGetPriority(NVIC_enumIRQn_Type Copy_enuIRQn, u32 *Add_pu32GetPriority);
NVIC_ErrorStatus_t NVIC_enumGetActive(NVIC_enumIRQn_Type Copy_enuIRQn, u8 *Add_pu8GetActiveStatus);
NVIC_ErrorStatus_t NVIC_EncodePriority(u32 Copy_u32PriorityGroup, u32 Copy_u32PreemptPriority, u32 Copy_u32SubPriority, u32 *Add_pu8EncodedPriority) ;
NVIC_ErrorStatus_t NVIC_SetPriorityGrouping(u32 Copy_u32PriorityGroup);
NVIC_ErrorStatus_t NVIC_GetPriorityGrouping(u32* Add_pu32PriorityGroup);


#endif /*NVIC_H*/