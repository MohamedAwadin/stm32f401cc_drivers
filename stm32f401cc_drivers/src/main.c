

#include "COMMON/StdTypes.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/NVIC/NVIC.h"
#include "MCAL/SYSTICK/SYSTICK.h"
#include "HAL/HSCED/HSCED.h"



#define LED1_PORT    GPIO_PORTC
#define LED1_PIN     GPIO_PIN13


#define LED2_PORT    GPIO_PORTB
#define LED2_PIN     GPIO_PIN3




void Runnable1_ToggleLED(void){
    static u32 var1 = 1 ; 
    GPIO_enumSetPinValue(LED1_PORT, LED1_PIN, var1); 
    if(var1 == 1){
        var1  = GPIO_SET_PIN_LOW ;
    }
    else {
        var1 = 1;
    }
    // var = !var;

}

void Runnable2_ToggleLED(void){
    static u32 var2 = 1 ; 
    GPIO_enumSetPinValue(LED2_PORT, LED2_PIN, var2); 
    if(var2 == 1){
        var2  = GPIO_SET_PIN_LOW ;
    }
    else {
        var2 = 1;
    }
    // var = !var;

}


HSCED_RunnableConfig_t Runnable1 = {
    .HSCED_u32RunnablePriority = 1,
    .HSCED_u32RunnableCyclicTime = 1000, 
    .HSCED_pfnRunnableCallback = Runnable1_ToggleLED,
    .HSCED_u32RunnableFirstdelay = 0 
};

HSCED_RunnableConfig_t Runnable2 = {
    .HSCED_u32RunnablePriority = 2,
    .HSCED_u32RunnableCyclicTime = 500, 
    .HSCED_pfnRunnableCallback = Runnable2_ToggleLED,
    .HSCED_u32RunnableFirstdelay = 100 
};
int main(void)
{

    RCC_enuSetClock_Status(RCC_enumHSE_CLOCK , RCC_enumCLK_ON);
    RCC_enuControlSysClock(RCC_enumHSE_CLOCK);
    RCC_enuEnableClock(RCC_AHB1ENR_GPIOBEN); 
    RCC_enuEnableClock(RCC_AHB1ENR_GPIOCEN); 

    
    GPIO_strPinConfig_t led1Config = {
        .GPIO_pinPort = LED1_PORT,
        .GPIO_pinNum = LED1_PIN,
        .GPIO_pinMode = GPIO_MODE_OUTPUT,
        .GPIO_pinOutType = GPIO_OUTPUT_PUSH_PULL,
        .GPIO_pinSpeed = GPIO_SPEED_HIGH,
        .GPIO_pinPull = GPIO_NO_PULL,
        .GPIO_pinAF = GPIO_AF_NONE
    };
    GPIO_enumConfigPin(&led1Config);

    
GPIO_strPinConfig_t led2Config = {
        .GPIO_pinPort = LED2_PORT,
        .GPIO_pinNum = LED2_PIN,
        .GPIO_pinMode = GPIO_MODE_OUTPUT,
        .GPIO_pinOutType = GPIO_OUTPUT_PUSH_PULL,
        .GPIO_pinSpeed = GPIO_SPEED_HIGH,
        .GPIO_pinPull = GPIO_NO_PULL,
        .GPIO_pinAF = GPIO_AF_NONE
    };
    GPIO_enumConfigPin(&led2Config);

    HSCED_enumInit(); 

    
    HSCED_enumRegisterRunnable(&Runnable1);
    HSCED_enumRegisterRunnable(&Runnable2);

    HSCED_enumStart(); 

    while (1)
    {
        
        
        

        
    }

    return 0;
}
