
#include "../../../include/COMMON/Utils.h"
#include "../../../include/COMMON/StdTypes.h"

#include "../../../include/MCAL/RCC/RCC.h"
#include "../../../include/MCAL/GPIO/GPIO.h"
#include "../../../include/MCAL/GPIO/GPIO_private.h"


GPIO_enumErrorStatus_t GPIO_enumConfigPin(GPIO_strPinConfig_t *Add_pstrPinConfig)
{
    GPIO_enumErrorStatus_t Local_enumErrorRet = GPIO_enumOK;
    u32 Local_u32TempReg;
    GPIO_strRegMap_t *Local_GPIO_Port;
    


    // Check if the configuration pointer is NULL
    if (Add_pstrPinConfig == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if(Add_pstrPinConfig->GPIO_pinPort >= (sizeof(GPIO_PORTS) / sizeof(GPIO_PORTS[GPIO_PORTA])))
    {
        return GPIO_enumErrorPort;
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
    else if ((Add_pstrPinConfig->GPIO_pinAF < GPIO_AF00) || (Add_pstrPinConfig->GPIO_pinAF > GPIO_AF_NONE))
    {
        Local_enumErrorRet = GPIO_enumErrorPinAF;
    }
    else
    {
        
        Local_GPIO_Port = GPIO_PORTS[Add_pstrPinConfig->GPIO_pinPort];
        
        // Configure the pin mode
        Local_u32TempReg = Local_GPIO_Port->MODER;
        Local_u32TempReg &= (GPIO_CLRMODE_MODERx_BITMASK_ << (Add_pstrPinConfig->GPIO_pinNum * 2));     /*Clear the mode bits*/
        Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinMode << (Add_pstrPinConfig->GPIO_pinNum * 2)); /*Set the mode bits*/
        Local_GPIO_Port->MODER = Local_u32TempReg;

        // Configure the output type
        Local_u32TempReg = Local_GPIO_Port->OTYPER;
        Local_u32TempReg &= (GPIO_CLROTYPE_OTYPERx_BITMASK_ << (Add_pstrPinConfig->GPIO_pinNum));      /* Clear the output type bit*/
        Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinOutType << (Add_pstrPinConfig->GPIO_pinNum)); /*Set the output type bit*/
        Local_GPIO_Port->OTYPER = Local_u32TempReg;

        // Configure the output speed
        Local_u32TempReg = Local_GPIO_Port->OSPEEDR;
        Local_u32TempReg &= (GPIO_CLROSPEED_OSPEEDRx_BITMASK_ << (Add_pstrPinConfig->GPIO_pinNum * 2));  /*Clear the speed bits*/
        Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinSpeed << (Add_pstrPinConfig->GPIO_pinNum * 2)); /*Set the speed bits*/
        Local_GPIO_Port->OSPEEDR = Local_u32TempReg;

        // Configure the pull-up/pull-down
        Local_u32TempReg = Local_GPIO_Port->PUPDR;
        Local_u32TempReg &= (GPIO_CLRPUPD_PUPDRx_BITMASK_ << (Add_pstrPinConfig->GPIO_pinNum * 2));     /*Clear the pull bits*/
        Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinPull << (Add_pstrPinConfig->GPIO_pinNum * 2)); /*Set the pull bits*/
        Local_GPIO_Port->PUPDR = Local_u32TempReg;

        // Configure the alternate function if needed
        if (Add_pstrPinConfig->GPIO_pinMode == GPIO_MODE_ALTERNATE)
        {
            if (Add_pstrPinConfig->GPIO_pinNum < GPIO_PIN8)
            {
                Local_u32TempReg = Local_GPIO_Port->AFR[0];
                Local_u32TempReg &= (GPIO_CLRAF_AFRx_BITMASK_ << (Add_pstrPinConfig->GPIO_pinNum * 4));       /*Clear the AF bits*/
                Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinAF << (Add_pstrPinConfig->GPIO_pinNum * 4)); /* Set the AF bits*/
                Local_GPIO_Port->AFR[0] = Local_u32TempReg;
            }
            else
            {
                Local_u32TempReg = Local_GPIO_Port->AFR[1];
                Local_u32TempReg &= (GPIO_CLRAF_AFRx_BITMASK_ << ((Add_pstrPinConfig->GPIO_pinNum - 8) * 4));       /*Clear the AF bits*/
                Local_u32TempReg |= (Add_pstrPinConfig->GPIO_pinAF << ((Add_pstrPinConfig->GPIO_pinNum - 8) * 4)); /* Set the AF bits*/
                Local_GPIO_Port->AFR[1] = Local_u32TempReg;
            }
        }
    }

    return Local_enumErrorRet;
}

GPIO_enumErrorStatus_t GPIO_enumSetPinValue(u32 Copy_u32pin_port, u32 Copy_u32pinNum,  u32 Copy_u32PinState)
{
    GPIO_enumErrorStatus_t Local_enumErrorRet = GPIO_enumOK;
    GPIO_strRegMap_t *Local_GPIO_Port;
    Local_GPIO_Port = GPIO_PORTS[Copy_u32pin_port];   

    if( Copy_u32pin_port >= (sizeof(GPIO_PORTS) / sizeof(GPIO_PORTS[GPIO_PORTA])))
    {
        return GPIO_enumErrorPort;
    }
    else if ((Copy_u32pinNum < GPIO_PIN0) || (Copy_u32pinNum > GPIO_PIN15))
    {
        Local_enumErrorRet = GPIO_enumErrorPinNum;
    }
    else if ((Copy_u32PinState != GPIO_SET_PIN_HIGH) && (Copy_u32PinState != GPIO_SET_PIN_LOW))
    {
        Local_enumErrorRet = GPIO_enumErrorPinState;
    }
    else if ((((Local_GPIO_Port ->MODER)>>(Copy_u32pinNum * 2)) & (~GPIO_CLRMODE_MODERx_BITMASK_)) != GPIO_MODE_OUTPUT)
    {
        Local_enumErrorRet = GPIO_enumErrorPinMode;
    }
    
    else
    {
        
        // Set or reset the pin using the BSRR register
        if (Copy_u32PinState == GPIO_SET_PIN_HIGH)
        {
            // Set the pin by writing to the lower 16 bits of BSRR
            Local_GPIO_Port->BSRR = (GPIO_SET_PIN_HIGH << Copy_u32pinNum);
        }
        else
        {
            // Reset the pin by writing to the upper 16 bits of BSRR
            Local_GPIO_Port->BSRR = (GPIO_SET_PIN_LOW << Copy_u32pinNum);
        }
    }

    return Local_enumErrorRet;
}

GPIO_enumErrorStatus_t GPIO_enumGetPinValue(u32 Copy_u32pin_port, u32 Copy_u32pinNum,  u32* Add_pu32PinState)
{
    GPIO_enumErrorStatus_t Local_enumErrorRet = GPIO_enumOK;
    GPIO_strRegMap_t *Local_GPIO_Port;
    Local_GPIO_Port = GPIO_PORTS[Copy_u32pin_port];  
    
    if (Add_pu32PinState == NULL_PTR)
    {
        Local_enumErrorRet = GPIO_enumErrorNullPointer;
    }
    else if( Copy_u32pin_port >= (sizeof(GPIO_PORTS) / sizeof(GPIO_PORTS[GPIO_PORTA])))
    {
        return GPIO_enumErrorPort;
    }
    else if ((Copy_u32pinNum < GPIO_PIN0) || (Copy_u32pinNum > GPIO_PIN15))
    {
        Local_enumErrorRet = GPIO_enumErrorPinNum;
    }
    else if ((((Local_GPIO_Port ->MODER)>>(Copy_u32pinNum * 2)) & (~GPIO_CLRMODE_MODERx_BITMASK_)) != GPIO_MODE_INPUT)
    {
        Local_enumErrorRet = GPIO_enumErrorPinMode;
    }
    else
    {
         
        *Add_pu32PinState = (Local_GPIO_Port->IDR >> Copy_u32pinNum) & (GPIO_GETBITV_IDRx_BITMASK_); 
        Local_enumErrorRet = GPIO_enumOK;
    }
    return Local_enumErrorRet ;
}
