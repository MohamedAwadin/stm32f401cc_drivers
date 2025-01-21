#include <../include/MCAL/GPIO/GPIO.h>



int main(void)
{
    GPIO_strPinConfig_t myPinConfig = {
    .GPIO_pinPort = GPIOA,
    .GPIO_pinNum = GPIO_PIN5,
    .GPIO_pinMode = GPIO_MODE_OUTPUT,
    .GPIO_pinOutType = GPIO_OUTPUT_PUSH_PULL,
    .GPIO_pinSpeed = GPIO_SPEED_HIGH,
    .GPIO_pinPull = GPIO_NO_PULL,
    .GPIO_pinAF = GPIO_AF_DISABLED
};

// Set pin PA5 to high
GPIO_enumSetPinValue(&myPinConfig, GPIO_SET_PIN_HIGH);

// Set pin PA5 to low
GPIO_enumSetPinValue(&myPinConfig, GPIO_SET_PIN_LOW);
    
    while (1)
    {
        /* code */
    }
    return 0;
}