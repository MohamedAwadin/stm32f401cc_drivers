#ifndef HLED_CONFIG_H_
#define HLED_CONFIG_H_

#include "HLED.h"

/* Number of LEDs in the system */
#define NUM_OF_LEDS 3

/* LED Names (Indices for the configuration array) */
#define LED_START   0  // LED for "Start" indication
#define LED_STOP    1  // LED for "Stop" indication
#define LED_ALERT   2  // LED for "Alert" indication

/* LED Configuration Array (Defined in HLED_Config.c) */
extern const HLED_strPinConfig_t HLED_strPinConfigArray[NUM_OF_LEDS];

#endif /* HLED_CONFIG_H_ */