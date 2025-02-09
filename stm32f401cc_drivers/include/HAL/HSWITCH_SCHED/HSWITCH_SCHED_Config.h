#ifndef HSWITCH_SCHED_CONFIG_H_
#define HSWITCH_SCHED_CONFIG_H_

#include "HSWITCH_SCHED.h"

/* Number of switches */
#define NUM_OF_SWITCHES 3

/* Switch IDs */
#define HSWITCH_ID_START   0  /* Start switch */
#define HSWITCH_ID_STOP    1  /* Stop switch */
#define HSWITCH_ID_ALERT   2  /* Alert switch */

/* Extern declaration for switch pin configuration array */
extern const HSWITCH_strPinConfig_t HSWITCH_strPinConfigArray[NUM_OF_SWITCHES];

#endif /* HSWITCH_SCHED_CONFIG_H_ */