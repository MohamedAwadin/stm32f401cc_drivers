#ifndef NVIC_H
#define NVIC_H

#include "../../COMMON/StdTypes.h"
#include "NVIC_private.h"





#define NVIC_SUBPRIORITY_GROUP_0       ((u32) 0x00000300)
#define NVIC_SUBPRIORITY_GROUP_1       ((u32) 0x00000400)
#define NVIC_SUBPRIORITY_GROUP_2       ((u32) 0x00000500)
#define NVIC_SUBPRIORITY_GROUP_3       ((u32) 0x00000600)
#define NVIC_SUBPRIORITY_GROUP_4       ((u32) 0x00000700)

#define NVIC_u8PENDING_ON              ((u8)0x01)
#define NVIC_u8PENDING_OFF             ((u8)0x00)
#define NVIC_u8ACTIVE_                 ((u8)0x01)
#define NVIC_u8NOTACTIVE_              ((u8)0x00)



/*Priority Bits in STM32F401cc*/
#define NVIC_PRIO_BITS          4U

/**************************************************************************/
/*						IRQ Table - STM32F401cc						 	  */
/**************************************************************************/
typedef enum
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NVIC_NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  NVIC_MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  NVIC_BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  NVIC_UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  NVIC_SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  NVIC_DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  NVIC_PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  NVIC_SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  NVIC_WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  NVIC_PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  NVIC_TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  NVIC_RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
  NVIC_FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  NVIC_RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  NVIC_EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  NVIC_EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  NVIC_EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  NVIC_EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  NVIC_EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  NVIC_DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
  NVIC_DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
  NVIC_DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
  NVIC_DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
  NVIC_DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
  NVIC_DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
  NVIC_DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
  NVIC_ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  NVIC_EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  NVIC_TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  NVIC_TIM1_UP_TIM10_IRQn          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  NVIC_TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  NVIC_TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  NVIC_TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  NVIC_TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  NVIC_TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
  NVIC_I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  NVIC_I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
  NVIC_I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
  NVIC_I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  NVIC_SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  NVIC_SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  NVIC_USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  NVIC_USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  NVIC_EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  NVIC_RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  NVIC_OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  NVIC_DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
  NVIC_SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
  NVIC_TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
  NVIC_SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  NVIC_DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
  NVIC_DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
  NVIC_DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
  NVIC_DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
  NVIC_DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
  NVIC_OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  NVIC_DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
  NVIC_DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
  NVIC_DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
  NVIC_USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
  NVIC_I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
  NVIC_I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
  NVIC_FPU_IRQn                    = 81,      /*!< FPU global interrupt                                             */
  NVIC_SPI4_IRQn                   = 84       /*!< SPI4 global Interrupt                                            */
} NVIC_enumIRQn_Type;

typedef enum
{
    NVIC_enumOk,
    NVIC_enumNOk,
    NVIC_enumErrorIRQNumber,
    NVIC_enumErrorNullPointer,
    NVIC_enumErrorSubPriorityGroup,
    NVIC_enumErrorPreemptPriority,
    NVIC_enumErrorSubPriority

} NVIC_ErrorStatus_t;
/**
 * @brief Function to Enable Any Interrupt in the System
 * 
 * @param Copy_enuIRQn 
 *        - Options Listed In NVIC_enumIRQn_Type enumeration
 *        
 * @return NVIC_ErrorStatus_t 
 *         -Return Error if Interrupt Number is out of range 
 */
NVIC_ErrorStatus_t NVIC_enumEnableIRQ(NVIC_enumIRQn_Type Copy_enuIRQn);
/**
 * @brief Function to Disable Any Interrupt in the System
 * 
 * @param Copy_enuIRQn 
 *        - Options Listed In NVIC_enumIRQn_Type enumeration
 *        
 * @return NVIC_ErrorStatus_t 
 *         -Return Error if Interrupt Number is out of range 
 */
NVIC_ErrorStatus_t NVIC_enumDisableIRQ(NVIC_enumIRQn_Type Copy_enuIRQn);

/**
 * @brief Function to Set Pending Bit for Any Interrupt in the System
 * 
 * @param Copy_enuIRQn 
 *        - Options Listed In NVIC_enumIRQn_Type enumeration
 * @return NVIC_ErrorStatus_t 
 *        -Return Error if Interrupt Number is out of range
 */
NVIC_ErrorStatus_t NVIC_enumSetPendingIRQ(NVIC_enumIRQn_Type Copy_enuIRQn);
/**
 * @brief Function to Clear Pending Bit for Any Interrupt in the System
 * 
 * @param Copy_enuIRQn 
 *        - Options Listed In NVIC_enumIRQn_Type enumeration
 * @return NVIC_ErrorStatus_t 
 *        -Return Error if Interrupt Number is out of range
 */
NVIC_ErrorStatus_t NVIC_enumClearPendingIRQ(NVIC_enumIRQn_Type Copy_enuIRQn);
/**
 * @brief Function to Get the Pending Bit for Any Interrupt in the System
 * 
 * @param Copy_enuIRQn 
 *        - Options Listed In NVIC_enumIRQn_Type enumeration
 * @param Add_pu8GetPendingStatus 
 *        - Address Of Variable to retuern pending Bit Status(NVIC_u8PENDING_ON , NVIC_u8PENDING_OFF)
 * @return NVIC_ErrorStatus_t 
 *        - Return Error if Interrupt Number is out of range
 *        - Return Error If you send NULL Pointer 
 */
NVIC_ErrorStatus_t NVIC_enumGetPendingIRQ(NVIC_enumIRQn_Type Copy_enuIRQn, u8 *Add_pu8GetPendingStatus);

/**
 * @brief Function to Set Priority for Any Interrupt in the System
 * 
 * @param Copy_enuIRQn 
 *        - Options Listed In NVIC_enumIRQn_Type enumeration
 * @param Copy_u32SubPriorityGroup 
 *        - Takes Sub Priority bits configuration, choose options from:
 *           * NVIC_SUBPRIORITY_GROUP_0
 *           * NVIC_SUBPRIORITY_GROUP_1
 *           * NVIC_SUBPRIORITY_GROUP_2
 *           * NVIC_SUBPRIORITY_GROUP_3
 *           * NVIC_SUBPRIORITY_GROUP_4
 * @param Copy_u32PreemptPriority 
 *        - Takes Preemtion Priority, number must less than 2^(preemption bits)
 *        - Preemtion bits is (Priority bits - Subgroup Bits)
 * @param Copy_u32SubPriority 
 *        - Takes Sub Priority, number must less than 2^(subgroup bits)
 * @return NVIC_ErrorStatus_t 
 *        - Return Error if Interrupt Number is out of range
 *        - NVIC_enumErrorSubPriorityGroup     : SUBPriorityGroupNum + PreemptPriorityNum > NVIC_PRIO_BITS
 *        - NVIC_enumErrorSubPriority          : Copy_u32SubPriority > 2^(subgroup bits)
 *        - NVIC_enumErrorPreemptPriority      : Copy_u32SubPriority > 2^(preemption bits)
 */
NVIC_ErrorStatus_t NVIC_enumSetPriority(NVIC_enumIRQn_Type Copy_enuIRQn, u32 Copy_u32SubPriorityGroup, u32 Copy_u32PreemptPriority, u32 Copy_u32SubPriority);

/**
 * @brief Function to Set Priority for Any Interrupt in the System
 * 
 * @param Copy_enuIRQn
 *        - Options Listed In NVIC_enumIRQn_Type enumeration
 * @param Add_pu32GetPriority
 *        - Address Of Variable to retuern Result  
 * @return NVIC_ErrorStatus_t 
 *        - Return Error if Interrupt Number is out of range
 *        - Return Error If you send NULL Pointer 
 */
NVIC_ErrorStatus_t NVIC_enumGetPriority(NVIC_enumIRQn_Type Copy_enuIRQn, u32 *Add_pu32GetPriority);

/**
 * @brief Function to Check if Any Interrupt in the System is Active Or Not Active
 * 
 * @param Copy_enuIRQn 
 *        - Options Listed In NVIC_enumIRQn_Type enumeration
 * @param Add_pu8GetActiveStatus 
 *        - Address Of Variable to retuern Result 
 *        * NVIC_u8ACTIVE_   
*         * NVIC_u8NOTACTIVE_ 
 * 
 * @return NVIC_ErrorStatus_t 
 *        - Return Error if Interrupt Number is out of range
 *        - Return Error If you send NULL Pointer 
 */
NVIC_ErrorStatus_t NVIC_enumGetActive(NVIC_enumIRQn_Type Copy_enuIRQn, u8 *Add_pu8GetActiveStatus);
/**
 * @brief Sub Group Priority Configuration
 * 
 * @param Copy_u32PriorityGroup 
*        - Takes Sub Group Priority bits configuration, choose options from:
 *           * NVIC_SUBPRIORITY_GROUP_0
 *           * NVIC_SUBPRIORITY_GROUP_1
 *           * NVIC_SUBPRIORITY_GROUP_2
 *           * NVIC_SUBPRIORITY_GROUP_3
 *           * NVIC_SUBPRIORITY_GROUP_4
 * @return NVIC_ErrorStatus_t 
 *        -  Return Error If you use Invalid Sub Group Priority bits Configuration 
 */
NVIC_ErrorStatus_t NVIC_SetSubPriorityGrouping(u32 Copy_u32PriorityGroup);



#endif /*NVIC_H*/