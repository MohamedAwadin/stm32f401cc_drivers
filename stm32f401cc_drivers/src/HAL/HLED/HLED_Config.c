#include "../../../include/HAL/HLED/HLED.h"
#include "../../../include/HAL/HLED/HLED_Config.h"

/* LED Configuration Array */
const HLED_strPinConfig_t HLED_strPinConfigArray[NUM_OF_LEDS] = {
    /* LED 0: Start LED (Port A, Pin 1, Forward Connection) */
    {
        HLED_PORTA,
        HLED_PIN1,
        HLED_OUTPUT_PUSH_PULL,
        HLED_OFF,
        HLED_Forward
    },
    /* LED 1: Stop LED (Port A, Pin 2, Forward Connection) */
    {
        HLED_PORTA,
        HLED_PIN2,
        HLED_OUTPUT_PUSH_PULL,
        HLED_OFF,
        HLED_Forward
    },
    /* LED 2: Alert LED (Port A, Pin 3, Forward Connection) */
    {
        HLED_PORTA,
        HLED_PIN3,
        HLED_OUTPUT_PUSH_PULL,
        HLED_OFF,
        HLED_Forward
    }
};