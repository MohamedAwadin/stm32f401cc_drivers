#include "COMMON/StdTypes.h"
#include "MCAL/DMA/DMA.h"
#include "MCAL/NVIC/NVIC.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/USART/USART.h"

void dma_callback(void) {
    // Handle transfer complete
}

int main(void) {
    DMA_strConfig_t config = {
        .DMA_u8Number = DMA_u8DMA2_SELECT,
        .DMA_u8Stream = DMA_u8STREAM6_SELECT,
        .DMA_u32Channel = DMA_u32CHANNEL5_SELECT, 
        .DMA_u32Direction = DMA_u32DATA_DIRECTION_MEM_TO_PERI,
        .DMA_u32MemDataSize = DMA_u32MEM_DATA_SIZE_8BITS,
        .DMA_u32PeriDataSize = DMA_u32PERI_DATA_SIZE_8BITS,
        .DMA_u32MemIncMode = DMA_u32MEM_INC_MODE_ON,
        .DMA_u32PeriIncMode = DMA_u32PERI_INC_MODE_FIXED,
        .DMA_u32PriorityLevel = DMA_u32PRIORITY_MEDIUM,
        .DMA_u32CircularMode = DMA_u32CIRCULAR_MODE_DISABLE,
        .DMA_u32TransferCompleteInterruptControl = DMA_u32TRANSFER_COMPLETE_INTERRUPT_ENABLE,
        .DMA_u32FIFOThreshold = 0, // Direct mode
        .DMA_CallbackFunc = dma_callback,
        .DMA_u32TransferSize = 3,
        .DMA_u32PeripheralAddress = (u32)&USART6->USART_DR,
    };

    // Enable DMA2 clock
    RCC_enuEnableClock(RCC_AHB1ENR_DMA2EN);
    // Initialize DMA
    DMA_enumInit(&config);
    // Configure SPI1 here
    
    while (1);
}
// #include "COMMON/StdTypes.h"
// #include "MCAL/NVIC/NVIC.h"

// /* Test Interrupt: EXTI0 */
// #define TEST_IRQ NVIC_EXTI0_IRQn

// int main(void)
// {
//     NVIC_ErrorStatus_t status;
//     u8 pendingStatus;
//     u8 activeStatus;



    
//     status = NVIC_enumEnableIRQ(TEST_IRQ);
//     if (status != NVIC_enumOk)
//     {
//         while (1); /* Error handling */
//     }

    
//     status = NVIC_enumSetPendingIRQ(TEST_IRQ);
//     if (status != NVIC_enumOk)
//     {
//         while (1); /* Error handling */
//     }

    
//     status = NVIC_enumGetPendingIRQ(TEST_IRQ, &pendingStatus);
//     if ((status != NVIC_enumOk) || (pendingStatus != NVIC_u8PENDING_ON))
//     {
//         while (1); /* Error handling */
//     }

    
//     status = NVIC_enumClearPendingIRQ(TEST_IRQ);
//     if (status != NVIC_enumOk)
//     {
//         while (1); /* Error handling */
//     }

    
//     status = NVIC_enumGetPendingIRQ(TEST_IRQ, &pendingStatus);
//     if ((status != NVIC_enumOk) || (pendingStatus != NVIC_u8PENDING_OFF))
//     {
//         while (1); /* Error handling */
//     }

    
//     status = NVIC_enumGetActive(TEST_IRQ, &activeStatus);
//     if (status != NVIC_enumOk)
//     {
//         while (1); /* Error handling */
//     }

    
//     status = NVIC_enumDisableIRQ(TEST_IRQ);
//     if (status != NVIC_enumOk)
//     {
//         while (1); /* Error handling */
//     }

//     while (1)
//     {
//         /* Main loop */
//     }

//     return 0;
// }


// #include "COMMON/StdTypes.h"
// #include "MCAL/RCC/RCC.h"
// #include "MCAL/GPIO/GPIO.h"
// #include "MCAL/NVIC/NVIC.h"
// #include "MCAL/SYSTICK/SYSTICK.h"
// #include "HAL/HSCED/HSCED.h"

// #define LED1_PORT    GPIO_PORTC
// #define LED1_PIN     GPIO_PIN13

// #define LED2_PORT    GPIO_PORTB
// #define LED2_PIN     GPIO_PIN3

// void Runnable1_ToggleLED(void){
//     static u32 var1 = 1 ;
//     GPIO_enumSetPinValue(LED1_PORT, LED1_PIN, var1);
//     if(var1 == 1){
//         var1  = GPIO_SET_PIN_LOW ;
//     }
//     else {
//         var1 = 1;
//     }
//     // var = !var;

// }

// void Runnable2_ToggleLED(void){
//     static u32 var2 = 1 ;
//     GPIO_enumSetPinValue(LED2_PORT, LED2_PIN, var2);
//     if(var2 == 1){
//         var2  = GPIO_SET_PIN_LOW ;
//     }
//     else {
//         var2 = 1;
//     }
//     // var = !var;

// }

// HSCED_RunnableConfig_t Runnable1 = {
//     .HSCED_u32RunnablePriority = 1,
//     .HSCED_u32RunnableCyclicTime = 1000,
//     .HSCED_pfnRunnableCallback = Runnable1_ToggleLED,
//     .HSCED_u32RunnableFirstdelay = 0
// };

// HSCED_RunnableConfig_t Runnable2 = {
//     .HSCED_u32RunnablePriority = 2,
//     .HSCED_u32RunnableCyclicTime = 500,
//     .HSCED_pfnRunnableCallback = Runnable2_ToggleLED,
//     .HSCED_u32RunnableFirstdelay = 100
// };
// int main(void)
// {

//     RCC_enuSetClock_Status(RCC_enumHSE_CLOCK , RCC_enumCLK_ON);
//     RCC_enuControlSysClock(RCC_enumHSE_CLOCK);
//     RCC_enuEnableClock(RCC_AHB1ENR_GPIOBEN);
//     RCC_enuEnableClock(RCC_AHB1ENR_GPIOCEN);

//     GPIO_strPinConfig_t led1Config = {
//         .GPIO_pinPort = LED1_PORT,
//         .GPIO_pinNum = LED1_PIN,
//         .GPIO_pinMode = GPIO_MODE_OUTPUT,
//         .GPIO_pinOutType = GPIO_OUTPUT_PUSH_PULL,
//         .GPIO_pinSpeed = GPIO_SPEED_HIGH,
//         .GPIO_pinPull = GPIO_NO_PULL,
//         .GPIO_pinAF = GPIO_AF_NONE
//     };
//     GPIO_enumConfigPin(&led1Config);

// GPIO_strPinConfig_t led2Config = {
//         .GPIO_pinPort = LED2_PORT,
//         .GPIO_pinNum = LED2_PIN,
//         .GPIO_pinMode = GPIO_MODE_OUTPUT,
//         .GPIO_pinOutType = GPIO_OUTPUT_PUSH_PULL,
//         .GPIO_pinSpeed = GPIO_SPEED_HIGH,
//         .GPIO_pinPull = GPIO_NO_PULL,
//         .GPIO_pinAF = GPIO_AF_NONE
//     };
//     GPIO_enumConfigPin(&led2Config);

//     HSCED_enumInit();

//     HSCED_enumRegisterRunnable(&Runnable1);
//     HSCED_enumRegisterRunnable(&Runnable2);

//     HSCED_enumStart();

//     while (1)
//     {

//     }

//     return 0;
// }
