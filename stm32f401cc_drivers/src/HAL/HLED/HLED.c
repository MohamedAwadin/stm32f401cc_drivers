#include "../../../include/HAL/HLED/HLED.h"
#include "../../../include/HAL/HLED/HLED_Config.h"
#include "../../../include/MCAL/GPIO/GPIO.h"   

void HLED_vInit(void)
{
    
    u8 Local_u8Iter= 0;
    //GPIO_strPinConfig_t Local_strcurrLed;

    for(Local_u8Iter = 0 ; Local_u8Iter<NUM_OF_LEDS ; Local_u8Iter++)
    {
        GPIO_strPinConfig_t Local_strcurrLed={
            .GPIO_pinPort = HLED_strPinConfigArray[Local_u8Iter].HLED_port_Number,
            .GPIO_pinNum =  HLED_strPinConfigArray[Local_u8Iter].HLED_pin_Number,
            .GPIO_pinMode = GPIO_MODE_OUTPUT,
            .GPIO_pinOutType = HLED_strPinConfigArray[Local_u8Iter].HLED_pin_OutType,
            .GPIO_pinSpeed = GPIO_SPEED_HIGH,
            .GPIO_pinPull = GPIO_NO_PULL,
            .GPIO_pinAF = GPIO_AF_NONE
        };
        GPIO_enumConfigPin(&Local_strcurrLed);
        GPIO_enumSetPinValue(HLED_strPinConfigArray[Local_u8Iter].HLED_port_Number , HLED_strPinConfigArray[Local_u8Iter].HLED_pin_Number , HLED_strPinConfigArray[Local_u8Iter].HLED_initState);
    }
}


HLED_enumErrorState_t HLED_enuSetValue(u8 Copy_u8LedName, HLED_enumLogic_t CopyHLED_enumLogicValue) {
    HLED_enumErrorState_t Ret_enumErrorStatus = HLED_enumErrSt_NOK;
    u8 Local_u8PinState = 0;

    /* Validate LED name */
    if (Copy_u8LedName >= NUM_OF_LEDS) {
        Ret_enumErrorStatus = HLED_enumErrSt_WrongLED;
    }
    /* Validate LED state */
    else if ((CopyHLED_enumLogicValue != HLED_OFF) && (CopyHLED_enumLogicValue != HLED_ON)) {
        Ret_enumErrorStatus = HLED_enumErrSt_InvalidConfig;
    }
    /* Set LED state */
    else {
        /* Determine pin state based on connection type */
        if (HLED_strPinConfigArray[Copy_u8LedName].HLED_connection == HLED_Forward) {
            Local_u8PinState = CopyHLED_enumLogicValue;
        } else {
            Local_u8PinState = (CopyHLED_enumLogicValue == HLED_ON) ? HLED_OFF : HLED_ON;
        }

        /* Set the pin value */
        Ret_enumErrorStatus = GPIO_enumSetPinValue(HLED_strPinConfigArray[Copy_u8LedName].HLED_port_Number,
                                                  HLED_strPinConfigArray[Copy_u8LedName].HLED_pin_Number,
                                                  Local_u8PinState);
    }

    return Ret_enumErrorStatus;
}