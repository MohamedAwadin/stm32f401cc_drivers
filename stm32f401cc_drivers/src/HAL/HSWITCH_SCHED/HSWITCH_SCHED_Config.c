#include "../../../include/HAL/HSWITCH_SCHED/HSWITCH_SCHED.h"
#include "../../../include/HAL/HSWITCH_SCHED/HSWITCH_SCHED_Config.h"

/* Switch pin configuration array */
const HSWITCH_strPinConfig_t HSWITCH_strPinConfigArray[NUM_OF_SWITCHES] = {
    {HSWITCH_PORTA, HSWITCH_PIN1, HSWITCH_PULL_UP},  /* Start switch */
    {HSWITCH_PORTA, HSWITCH_PIN2, HSWITCH_PULL_UP},  /* Stop switch */
    {HSWITCH_PORTA, HSWITCH_PIN3, HSWITCH_PULL_UP}   /* Alert switch */
};