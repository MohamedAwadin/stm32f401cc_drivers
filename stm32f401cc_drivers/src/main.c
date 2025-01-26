#ifdef GPIO_TEST

#include "COMMON/StdTypes.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"


#define LED_PORT    GPIO_PORTB
#define LED_PIN     GPIO_PIN5


#define BUTTON_PORT GPIO_PORTC
#define BUTTON_PIN  GPIO_PIN13


void delay(u32 count)
{
    for (u32 i = 0; i < count; i++);
}

int main(void)
{

    RCC_enuSetClock_Status(RCC_enumHSI_CLOCK , RCC_enumCLK_ON);
    RCC_enuControlSysClock(RCC_enumHSI_CLOCK);
    RCC_enuEnableClock(RCC_AHB1ENR_GPIOBEN); 
    RCC_enuEnableClock(RCC_AHB1ENR_GPIOCEN); 

    
    GPIO_strPinConfig_t ledConfig = {
        .GPIO_pinPort = LED_PORT,
        .GPIO_pinNum = LED_PIN,
        .GPIO_pinMode = GPIO_MODE_OUTPUT,
        .GPIO_pinOutType = GPIO_OUTPUT_PUSH_PULL,
        .GPIO_pinSpeed = GPIO_SPEED_HIGH,
        .GPIO_pinPull = GPIO_NO_PULL,
        .GPIO_pinAF = GPIO_AF_NONE
    };
    GPIO_enumConfigPin(&ledConfig);

    
    GPIO_strPinConfig_t buttonConfig = {
        .GPIO_pinPort = BUTTON_PORT,
        .GPIO_pinNum = BUTTON_PIN,
        .GPIO_pinMode = GPIO_MODE_INPUT,
        .GPIO_pinOutType = GPIO_OUTPUT_PUSH_PULL, 
        .GPIO_pinSpeed = GPIO_SPEED_LOW,          
        .GPIO_pinPull = GPIO_PULL_UP,             
        .GPIO_pinAF = GPIO_AF_NONE                
    };
    GPIO_enumConfigPin(&buttonConfig);

    
    while (1)
    {
        /*TEST Case 1 = Accepted*/
        // Toggle the LED
        // GPIO_enumSetPinValue(LED_PORT, LED_PIN, GPIO_SET_PIN_HIGH); // Turn LED on
        // delay(1000000); // Delay for visibility
        // GPIO_enumSetPinValue(LED_PORT, LED_PIN, GPIO_SET_PIN_LOW);  // Turn LED off
        // delay(1000000); // Delay for visibility

        /*TEST Case 2 = Accepted*/
        
        // Read the button state
        u32 buttonState;
        GPIO_enumGetPinValue(BUTTON_PORT, BUTTON_PIN, &buttonState);

        // If the button is pressed (active low, since pull-up is enabled)
        if (buttonState == 0)
        {
            // Turn the LED on as long as the button is pressed
            GPIO_enumSetPinValue(LED_PORT, LED_PIN, GPIO_SET_PIN_HIGH);
            while (buttonState == 0){
                GPIO_enumGetPinValue(BUTTON_PORT, BUTTON_PIN, &buttonState);
            }
            
        }
        else
        {
            // Turn the LED off when the button is not pressed
            GPIO_enumSetPinValue(LED_PORT, LED_PIN, GPIO_SET_PIN_LOW);
        }
    }

    return 0;
}
#endif

#ifdef HLED_TEST

#include "COMMON/StdTypes.h"
#include "MCAL/RCC/RCC.h"
#include "HAL/HLED/HLED.h"
#include "HAL/HLED/HLED_Config.h"


int main(void) {
    HLED_enumErrorState_t errorStatus;
    RCC_enuSetClock_Status(RCC_enumHSE_CLOCK , RCC_enumCLK_ON);
    RCC_enuControlSysClock(RCC_enumHSE_CLOCK);
    RCC_enuEnableClock(RCC_AHB1ENR_GPIOAEN); 
    RCC_enuEnableClock(RCC_AHB1ENR_GPIOCEN); 

    /* Initialize the LED driver */
    HLED_vInit();

    
    errorStatus = HLED_enuSetValue(LED_START, HLED_ON);
    if (errorStatus != HLED_enumErrSt_OK) {
        
    }
    errorStatus = HLED_enuSetValue(LED_STOP, HLED_ON);
    if (errorStatus != HLED_enumErrSt_OK) {
        
    }
    errorStatus = HLED_enuSetValue(LED_ALERT, HLED_ON);
    if (errorStatus != HLED_enumErrSt_OK) {
        
    }

    
    

    
    while (1) {
        
    }
}

#endif

