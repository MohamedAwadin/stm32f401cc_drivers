#ifndef HSWITCH_SCHED_H_
#define HSWITCH_SCHED_H_

#include "../../MCAL/GPIO/GPIO.h"
#include "../../COMMON/StdTypes.h"
#include "../../COMMON/Utils.h"

/* Number of checks for debouncing */
#define HSWITCH_NUM_OF_CHECKS 5

/* Enum for switch ports */
typedef enum {
    HSWITCH_PORTA = 0,
    HSWITCH_PORTB,
    HSWITCH_PORTC,
    HSWITCH_PORTD,
    HSWITCH_PORTE,
    HSWITCH_PORTH
} HSWITCH_enumPort_t;

/* Enum for switch pins */
typedef enum {
    HSWITCH_PIN0 = 0,
    HSWITCH_PIN1,
    HSWITCH_PIN2,
    HSWITCH_PIN3,
    HSWITCH_PIN4,
    HSWITCH_PIN5,
    HSWITCH_PIN6,
    HSWITCH_PIN7,
    HSWITCH_PIN8,
    HSWITCH_PIN9,
    HSWITCH_PIN10,
    HSWITCH_PIN11,
    HSWITCH_PIN12,
    HSWITCH_PIN13,
    HSWITCH_PIN14,
    HSWITCH_PIN15
} HSWITCH_enumPin_t;

/* Enum for switch status */
typedef enum {
    HSWITCH_enuNotPressed,
    HSWITCH_enuPressed,
    HSWITCH_enuPreNotPressed,
    HSWITCH_enuPrePressed,
} HSWITCH_enumStatus_t;

/* Enum for switch pull state */
typedef enum {
    HSWITCH_NO_PULL = GPIO_NO_PULL,
    HSWITCH_PULL_UP = GPIO_PULL_UP,
    HSWITCH_PULL_DOWN = GPIO_PULL_DOWN
} HSWITCH_enumPullState_t;

/* Enum for switch error states */
typedef enum {
    HSWITCH_enumErrSt_NOK = 0,           /* Operation failed */
    HSWITCH_enumErrSt_OK,                /* Operation succeeded */
    HSWITCH_enumErrSt_NullPtr,           /* Null pointer passed */
    HSWITCH_enumErrSt_InvalidPin,        /* Invalid pin number */
    HSWITCH_enumErrSt_InvalidPort,       /* Invalid port number */
    HSWITCH_enumErrSt_InvalidConfig,     /* Invalid configuration */
    HSWITCH_enumErrSt_InvalidState,      /* Invalid switch state */
    HSWITCH_enumErrSt_WrongSwitch        /* Invalid switch name */
} HSWITCH_enumErrorState_t;

/* Structure for switch pin configuration */
typedef struct {
    HSWITCH_enumPort_t HSWITCH_port_Number;  /* GPIO port number */
    HSWITCH_enumPin_t HSWITCH_pin_Number;    /* GPIO pin number */
    HSWITCH_enumPullState_t HSWITCH_Pull_State; /* GPIO pull state */
} HSWITCH_strPinConfig_t;

/* Function prototypes */
void HSWITCH_vInit(void);
HSWITCH_enumErrorState_t HSWITCH_enuGetStatus(u32 Copy_u8SwitchName, u8 *Add_pSwitchStatus);
void HSWITCH_vRunnable(void);

#endif /* HSWITCH_SCHED_H_ */