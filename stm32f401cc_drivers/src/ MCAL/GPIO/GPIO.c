
#include "../../../include/COMMON/Utils.h"
#include "../../../include/COMMON/StdTypes.h"

#include "../../../include/MCAL/RCC/RCC.h"
#include "../../../include/MCAL/GPIO/GPIO.h"
#include "../../../include/MCAL/GPIO/GPIO_private.h"

GPIO_enumErrorStatus_t GPIO_EnableClock(GPIO_strRegMap_t *GPIO_pstr_x){
    GPIO_enumErrorStatus_t Local_enumErrorRet = GPIO_enumOK;
    if (GPIO_pstr_x == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if (GPIO_pstr_x == GPIOA)
    {
        RCC_enuEnableClock(RCC_AHB1ENR_GPIOAEN);
    }
    else if (GPIO_pstr_x == GPIOB)
    {
        RCC_enuEnableClock(RCC_AHB1ENR_GPIOBEN);
    }
    else if (GPIO_pstr_x == GPIOC)
    {
        RCC_enuEnableClock(RCC_AHB1ENR_GPIOCEN);
    }
    else if (GPIO_pstr_x == GPIOD)
    {
        RCC_enuEnableClock(RCC_AHB1ENR_GPIODEN);
    }
    else if (GPIO_pstr_x == GPIOE)
    {
        RCC_enuEnableClock(RCC_AHB1ENR_GPIOEEN);
    }
    else if (GPIO_pstr_x == GPIOH)
    {
        RCC_enuEnableClock(RCC_AHB1ENR_GPIOHEN);
    }
    else
    {
        Local_enumErrorRet = GPIO_enumErrorPort;
    }
    return Local_enumErrorRet;
}

GPIO_enumErrorStatus_t GPIO_DisableClock(GPIO_strRegMap_t *GPIO_pstr_x)
{
    GPIO_enumErrorStatus_t Local_enumErrorRet = GPIO_enumOK;
    if (GPIO_pstr_x == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if (GPIO_pstr_x == GPIOA)
    {
        RCC_enuDisableClock(RCC_AHB1ENR_GPIOAEN);
    }
    else if (GPIO_pstr_x == GPIOB)
    {
        RCC_enuDisableClock(RCC_AHB1ENR_GPIOBEN);
    }
    else if (GPIO_pstr_x == GPIOC)
    {
        RCC_enuDisableClock(RCC_AHB1ENR_GPIOCEN);
    }
    else if (GPIO_pstr_x == GPIOD)
    {
        RCC_enuDisableClock(RCC_AHB1ENR_GPIODEN);
    }
    else if (GPIO_pstr_x == GPIOE)
    {
        RCC_enuDisableClock(RCC_AHB1ENR_GPIOEEN);
    }
    else if (GPIO_pstr_x == GPIOH)
    {
        RCC_enuDisableClock(RCC_AHB1ENR_GPIOHEN);
    }
    else
    {
        Local_enumErrorRet = GPIO_enumErrorPort;
    }
    return Local_enumErrorRet;
}

GPIO_enumErrorStatus_t GPIO_enumConfigPin(GPIO_strPinConfig_t *Add_pstrPinConfig)
{
    GPIO_enumErrorStatus_t Local_enumErrorRet = GPIO_enumOK;
    u32 Local_u32TempReg;

    // Check if the configuration pointer is NULL
    if (Add_pstrPinConfig == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if (Add_pstrPinConfig->GPIO_pinPort == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if ((Add_pstrPinConfig->GPIO_pinPort != GPIOA) && (Add_pstrPinConfig->GPIO_pinPort != GPIOB) &&
             (Add_pstrPinConfig->GPIO_pinPort != GPIOC) && (Add_pstrPinConfig->GPIO_pinPort != GPIOD) &&
             (Add_pstrPinConfig->GPIO_pinPort != GPIOE) && (Add_pstrPinConfig->GPIO_pinPort != GPIOH))
    {
        Local_enumErrorRet = GPIO_enumErrorPort;
    }
    else if ((Add_pstrPinConfig->GPIO_pinNum < GPIO_PIN0) || (Add_pstrPinConfig->GPIO_pinNum > GPIO_PIN15))
    {
        Local_enumErrorRet = GPIO_enumErrorPinNum;
    }
    else if ((Add_pstrPinConfig->GPIO_pinMode < GPIO_MODE_INPUT) || (Add_pstrPinConfig->GPIO_pinMode > GPIO_MODE_ANALOG))
    {
        Local_enumErrorRet = GPIO_enumErrorPinMode;
    }
    else if ((Add_pstrPinConfig->GPIO_pinOutType < GPIO_OUTPUT_PUSH_PULL) || (Add_pstrPinConfig->GPIO_pinOutType > GPIO_OUTPUT_OPEN_DRAIN))
    {
        Local_enumErrorRet = GPIO_enumErrorPinOutType;
    }
    else if ((Add_pstrPinConfig->GPIO_pinSpeed < GPIO_SPEED_LOW) || (Add_pstrPinConfig->GPIO_pinSpeed > GPIO_SPEED_VERY_HIGH))
    {
        Local_enumErrorRet = GPIO_enumErrorPinSpeed;
    }
    else if ((Add_pstrPinConfig->GPIO_pinPull < GPIO_NO_PULL) || (Add_pstrPinConfig->GPIO_pinPull > GPIO_PULL_DOWN))
    {
        Local_enumErrorRet = GPIO_enumErrorPinPull;
    }
    else if ((Add_pstrPinConfig->GPIO_pinAF < GPIO_AF00) || (Add_pstrPinConfig->GPIO_pinAF > GPIO_AF15))
    {
        Local_enumErrorRet = GPIO_enumErrorPinAF;
    }
    else
    {
        // Enable the clock for the GPIO port
        GPIO_EnableClock(Add_pstrPinConfig->GPIO_pinPort);

        // Configure the pin mode
        Local_u32TempReg = Add_pstrPinConfig->GPIO_pinPort->MODER;
        Local_u32TempReg &= (GPIO_CLRMODE_MODERx_BITMUSK_ << (Add_pstrPinConfig->GPIO_pinNum * 2));     /*Clear the mode bits*/
        Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinMode << (Add_pstrPinConfig->GPIO_pinNum * 2)); /*Set the mode bits*/
        Add_pstrPinConfig->GPIO_pinPort->MODER = Local_u32TempReg;

        // Configure the output type
        Local_u32TempReg = Add_pstrPinConfig->GPIO_pinPort->OTYPER;
        Local_u32TempReg &= (GPIO_CLROTYPE_OTYPERx_BITMUSK_ << (Add_pstrPinConfig->GPIO_pinNum));      /* Clear the output type bit*/
        Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinOutType << (Add_pstrPinConfig->GPIO_pinNum)); /*Set the output type bit*/
        Add_pstrPinConfig->GPIO_pinPort->OTYPER = Local_u32TempReg;

        // Configure the output speed
        Local_u32TempReg = Add_pstrPinConfig->GPIO_pinPort->OSPEEDR;
        Local_u32TempReg &= (GPIO_CLROSPEED_OSPEEDRx_BITMUSK_ << (Add_pstrPinConfig->GPIO_pinNum * 2));  /*Clear the speed bits*/
        Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinSpeed << (Add_pstrPinConfig->GPIO_pinNum * 2)); /*Set the speed bits*/
        Add_pstrPinConfig->GPIO_pinPort->OSPEEDR = Local_u32TempReg;

        // Configure the pull-up/pull-down
        Local_u32TempReg = Add_pstrPinConfig->GPIO_pinPort->PUPDR;
        Local_u32TempReg &= (GPIO_CLRPUPD_PUPDRx_BITMUSK_ << (Add_pstrPinConfig->GPIO_pinNum * 2));     /*Clear the pull bits*/
        Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinPull << (Add_pstrPinConfig->GPIO_pinNum * 2)); /*Set the pull bits*/
        Add_pstrPinConfig->GPIO_pinPort->PUPDR = Local_u32TempReg;

        // Configure the alternate function if needed
        if (Add_pstrPinConfig->GPIO_pinMode == GPIO_MODE_ALTERNATE)
        {
            if (Add_pstrPinConfig->GPIO_pinNum < GPIO_PIN8)
            {
                Local_u32TempReg = Add_pstrPinConfig->GPIO_pinPort->AFR[0];
                Local_u32TempReg &= (GPIO_CLRAF_AFRx_BITMUSK_ << (Add_pstrPinConfig->GPIO_pinNum * 4));       /*Clear the AF bits*/
                Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinAF << (Add_pstrPinConfig->GPIO_pinNum * 4)); /* Set the AF bits*/
                Add_pstrPinConfig->GPIO_pinPort->AFR[0] = Local_u32TempReg;
            }
            else
            {
                Local_u32TempReg = Add_pstrPinConfig->GPIO_pinPort->AFR[1];
                Local_u32TempReg &= (GPIO_CLRAF_AFRx_BITMUSK_ << ((Add_pstrPinConfig->GPIO_pinNum - 8) * 4));       /*Clear the AF bits*/
                Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinAF << ((Add_pstrPinConfig->GPIO_pinNum - 8) * 4)); /* Set the AF bits*/
                Add_pstrPinConfig->GPIO_pinPort->AFR[1] = Local_u32TempReg;
            }
        }
    }

    return Local_enumErrorRet;
}

GPIO_enumErrorStatus_t GPIO_enumSetPinValue(GPIO_strPinConfig_t *Add_pstrPinConfig, u32 Copy_u32PinState)
{
    GPIO_enumErrorStatus_t Local_enumErrorRet = GPIO_enumOK;


    // Check if the configuration pointer is NULL
    if (Add_pstrPinConfig == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if (Add_pstrPinConfig->GPIO_pinPort == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if ((Add_pstrPinConfig->GPIO_pinPort != GPIOA) && (Add_pstrPinConfig->GPIO_pinPort != GPIOB) &&
             (Add_pstrPinConfig->GPIO_pinPort != GPIOC) && (Add_pstrPinConfig->GPIO_pinPort != GPIOD) &&
             (Add_pstrPinConfig->GPIO_pinPort != GPIOE) && (Add_pstrPinConfig->GPIO_pinPort != GPIOH))
    {
        Local_enumErrorRet = GPIO_enumErrorPort;
    }
    else if ((Add_pstrPinConfig->GPIO_pinNum < GPIO_PIN0) || (Add_pstrPinConfig->GPIO_pinNum > GPIO_PIN15))
    {
        Local_enumErrorRet = GPIO_enumErrorPinNum;
    }
    else if ((Copy_u32PinState != GPIO_SET_PIN_HIGH) && (Copy_u32PinState != GPIO_SET_PIN_LOW))
    {
        Local_enumErrorRet = GPIO_enumErrorPinState;
    }
    else
    {
        // Set or reset the pin using the BSRR register
        if (Copy_u32PinState == GPIO_SET_PIN_HIGH)
        {
            // Set the pin by writing to the lower 16 bits of BSRR
            Add_pstrPinConfig->GPIO_pinPort->BSRR = (GPIO_SET_PIN_HIGH << Add_pstrPinConfig->GPIO_pinNum);
        }
        else
        {
            // Reset the pin by writing to the upper 16 bits of BSRR
            Add_pstrPinConfig->GPIO_pinPort->BSRR = (GPIO_SET_PIN_LOW << Add_pstrPinConfig->GPIO_pinNum);
        }
    }

    return Local_enumErrorRet;
}

GPIO_enumErrorStatus_t GPIO_enumGetPinValue(GPIO_strPinConfig_t *Add_pstrPinConfig, u32* Add_pu32PinState)
{
    GPIO_enumErrorStatus_t Local_enumErrorRet = GPIO_enumOK;
    
    u32 Local_u32TempReg;
    // Check if the configuration pointer is NULL
    if (Add_pstrPinConfig == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if (Add_pstrPinConfig->GPIO_pinPort == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if (Add_pu32PinState == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if ((Add_pstrPinConfig->GPIO_pinPort != GPIOA) && (Add_pstrPinConfig->GPIO_pinPort != GPIOB) &&
             (Add_pstrPinConfig->GPIO_pinPort != GPIOC) && (Add_pstrPinConfig->GPIO_pinPort != GPIOD) &&
             (Add_pstrPinConfig->GPIO_pinPort != GPIOE) && (Add_pstrPinConfig->GPIO_pinPort != GPIOH))
    {
        Local_enumErrorRet = GPIO_enumErrorPort;
    }
    else if ((Add_pstrPinConfig->GPIO_pinNum < GPIO_PIN0) || (Add_pstrPinConfig->GPIO_pinNum > GPIO_PIN15))
    {
        Local_enumErrorRet = GPIO_enumErrorPinNum;
    }
    else
    {
        *Add_pu32PinState = (Add_pstrPinConfig->GPIO_pinPort->IDR >> Add_pstrPinConfig->GPIO_pinNum) & (GPIO_GETBITV_IDRx_BITMUSK_); 
        Local_enumErrorRet = GPIO_enumOK;
    }
    return Local_enumErrorRet ;
}
