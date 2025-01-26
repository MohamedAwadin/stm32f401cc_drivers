#ifndef HLED_H_
#define HLED_H_


#include "../../MCAL/GPIO/GPIO.h"
#include "../../COMMON/StdTypes.h"
#include "../../COMMON/Utils.h"


/* LED Port Number */
typedef enum {
    HLED_PORTA=0,
    HLED_PORTB,
    HLED_PORTC,
    HLED_PORTD,
    HLED_PORTE,
    HLED_PORTH
} HLED_enumPort_t;

/* LED Pin Number */
typedef enum {
    HLED_PIN0=0,
    HLED_PIN1 ,
    HLED_PIN2 ,
    HLED_PIN3 ,
    HLED_PIN4 ,
    HLED_PIN5 ,
    HLED_PIN6 ,
    HLED_PIN7 ,
    HLED_PIN8 ,
    HLED_PIN9 ,
    HLED_PIN10,
    HLED_PIN11,
    HLED_PIN12,
    HLED_PIN13,
    HLED_PIN14,
    HLED_PIN15
} HLED_enumPin_t;

/* LED Logic States */
typedef enum {
    HLED_OFF = GPIO_SET_PIN_LOW,  // LED is off
    HLED_ON  = GPIO_SET_PIN_HIGH       // LED is on
} HLED_enumLogic_t;

/* LED Output Types */
typedef enum{
    HLED_OUTPUT_PUSH_PULL= 0x00,
    HLED_OUTPUT_OPEN_DRAIN= 0x01
}HLED_enumOutType_t;




/* LED Driver Error States */
typedef enum {
    HLED_enumErrSt_NOK = 0,         // Operation failed
    HLED_enumErrSt_OK,              // Operation succeeded
    HLED_enumErrSt_InvalidPin,      // Invalid pin number
    HLED_enumErrSt_InvalidPort,     // Invalid port number
    HLED_enumErrSt_InvalidConfig,   // Invalid configuration
    HLED_enumErrSt_InvalidState,    // Invalid LED state
    HLED_enumErrSt_WrongLED         // Invalid LED name
} HLED_enumErrorState_t;

/* LED Connection Options */
typedef enum {
    HLED_Forward = 0,  // LED anode connected to MCU pin, cathode to GND
    HLED_Reverse       // LED cathode connected to MCU pin, anode to VCC
} HLED_enumConnectOptions_t;

/* LED Configuration Structure */
typedef struct {
    HLED_enumPort_t           HLED_port_Number;            
    HLED_enumPin_t            HLED_pin_Number;             
    HLED_enumOutType_t        HLED_pin_OutType;
    HLED_enumLogic_t          HLED_initState; 
    HLED_enumConnectOptions_t HLED_connection;    // Connection type (Forward/Reverse)
} HLED_strPinConfig_t;

/* Function Prototypes */


void HLED_vInit(void);  


HLED_enumErrorState_t HLED_enuSetValue(u8 Copy_u8LedName, HLED_enumLogic_t CopyHLED_enumLogicValue);  // Set LED state

#endif /* HLED_H_ */