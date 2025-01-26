#ifndef _GPIO_H_
#define _GPIO_H_

#include "../../COMMON/StdTypes.h"
#include "GPIO_private.h"


/************************************************************* */

/*************************MACROS - GPIO Ports*************************/
/**
 * User-facing macros to represent GPIO ports
 */
#define GPIO_PORTA      (0)
#define GPIO_PORTB      (1)
#define GPIO_PORTC      (2)
#define GPIO_PORTD      (3)
#define GPIO_PORTE      (4)
#define GPIO_PORTH      (5)

/******************ENUM - ERRORS return type********************/

typedef enum{
    GPIO_enumOK = 0,
    GPIO_enumErrorNullPointer,
    GPIO_enumErrorPort,
    GPIO_enumErrorPinNum,
    GPIO_enumErrorPinMode,
    GPIO_enumErrorPinOutType,
    GPIO_enumErrorPinSpeed,
    GPIO_enumErrorPinPull,
    GPIO_enumErrorPinAF,
    GPIO_enumErrorPinState
}GPIO_enumErrorStatus_t;

/* ********************************************************** */
/* ******************MACROS - Config GPIO Pin**************** */

/* ------------------ GPIO Pins Position ---------------------*/
#define GPIO_PIN0               (u8)0
#define GPIO_PIN1               (u8)1
#define GPIO_PIN2               (u8)2
#define GPIO_PIN3               (u8)3
#define GPIO_PIN4               (u8)4
#define GPIO_PIN5               (u8)5
#define GPIO_PIN6               (u8)6
#define GPIO_PIN7               (u8)7
#define GPIO_PIN8               (u8)8
#define GPIO_PIN9               (u8)9
#define GPIO_PIN10              (u8)10
#define GPIO_PIN11              (u8)11
#define GPIO_PIN12              (u8)12
#define GPIO_PIN13              (u8)13
#define GPIO_PIN14              (u8)14
#define GPIO_PIN15              (u8)15

/*------------------- GPIO Pin Modes -------------------------*/
#define    GPIO_MODE_INPUT         0x00
#define    GPIO_MODE_OUTPUT        0x01
#define    GPIO_MODE_ALTERNATE     0x02
#define    GPIO_MODE_ANALOG        0x03


/*----------------  GPIO Pin Output Mode --------------------*/
#define    GPIO_OUTPUT_PUSH_PULL   0x00
#define    GPIO_OUTPUT_OPEN_DRAIN  0x01


/*----------------  GPIO Pin Speed Modes --------------------*/
#define    GPIO_SPEED_LOW          0x00
#define    GPIO_SPEED_MEDIUM       0x01
#define    GPIO_SPEED_HIGH         0x02
#define    GPIO_SPEED_VERY_HIGH    0x03


/*----------------  GPIO Pin PULL Modes --------------------*/
#define    GPIO_NO_PULL            0x00
#define    GPIO_PULL_UP            0x01
#define    GPIO_PULL_DOWN          0x02

/*------------------- Alternative Functions -----------------*/
#define GPIO_AF00                  (u8)(0)
#define GPIO_AF01                  (u8)(1)
#define GPIO_AF02                  (u8)(2)
#define GPIO_AF03                  (u8)(3)
#define GPIO_AF04                  (u8)(4)
#define GPIO_AF05                  (u8)(5)
#define GPIO_AF06                  (u8)(6)
#define GPIO_AF07                  (u8)(7)
#define GPIO_AF08                  (u8)(8)
#define GPIO_AF09                  (u8)(9)
#define GPIO_AF10                  (u8)(10)
#define GPIO_AF11                  (u8)(11)
#define GPIO_AF12                  (u8)(12)
#define GPIO_AF13                  (u8)(13)
#define GPIO_AF14                  (u8)(14)
#define GPIO_AF15                  (u8)(15)
#define GPIO_AF_NONE               (u8)(16)

/*------------------- GPIO Value Pin (State) -----------------
 * These Masks used to set/reset the output value of GPIO Pins
 * using BSRR Register    
 */
#define GPIO_SET_PIN_HIGH       (u32)(0x00000001UL)  /* BSRR Bit0:Bit15*/
#define GPIO_SET_PIN_LOW        (u32)(0x00010000UL)  /* BSRR Bit16:Bit31*/

/******************************************************************************************
 *                                       Data Types                                       *
 ******************************************************************************************/

/**
  * @brief  Configuration structure for GPIO initialization.
  */
typedef struct 
{
    volatile u32 GPIO_pinPort;          /*< GPIO_pinPort value (GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH) */
    volatile u32 GPIO_pinNum;           /*< GPIO_pinNum (GPIO_PIN0 to GPIO_PIN15) */
    volatile u32 GPIO_pinMode;          /*< GPIO pin mode:
                                            - GPIO_MODE_INPUT
                                            - GPIO_MODE_OUTPUT
                                            - GPIO_MODE_ALTERNATE
                                            - GPIO_MODE_ANALOG */
    volatile u32 GPIO_pinOutType;       /*< GPIO Output Type (Only for Output Mode):
                                            - GPIO_OUTPUT_PUSH_PULL 
                                            - GPIO_OUTPUT_OPEN_DRAIN */
    volatile u32 GPIO_pinSpeed;         /*< GPIO Output Speed (Only for Output Mode):
                                            - GPIO_SPEED_LOW      
                                            - GPIO_SPEED_MEDIUM   
                                            - GPIO_SPEED_HIGH     
                                            - GPIO_SPEED_VERY_HIGH */
    volatile u32 GPIO_pinPull;          /*< GPIO Input Pull-Up / Pull-Down (Only for Input Mode):
                                            - GPIO_NO_PULL  
                                            - GPIO_PULL_UP  
                                            - GPIO_PULL_DOWN */
    volatile u32 GPIO_pinAF;            /*< GPIO pin Alternative Function: 
                                            - GPIO_AF00
                                            - GPIO_AF01
                                            - GPIO_AF02
                                            - GPIO_AF03
                                            - GPIO_AF04
                                            - GPIO_AF05
                                            - GPIO_AF06
                                            - GPIO_AF07
                                            - GPIO_AF08
                                            - GPIO_AF09
                                            - GPIO_AF10
                                            - GPIO_AF11
                                            - GPIO_AF12
                                            - GPIO_AF13
                                            - GPIO_AF14
                                            - GPIO_AF15
                                            - GPIO_AF_NONE */
}GPIO_strPinConfig_t;         


/*****************************************************************************
 * 							Function Prototypes 							 *
 ******************************************************************************/
/**
 * @brief Configures a GPIO pin based on the provided configuration.
 * 
 * @param Add_pstrPinConfig Pointer to the GPIO pin configuration structure.
 * @return GPIO_enumErrorStatus_t Returns `GPIO_enumOK` if successful, or an error code if failed.
 */
extern GPIO_enumErrorStatus_t GPIO_enumConfigPin(GPIO_strPinConfig_t *Add_pstrPinConfig);
/**
 * @brief Sets the value of a GPIO OutPut pin (high or low).
 * 
 * @param Copy_u32pin_port GPIO_pinPort value (GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH)
 * @param Copy_u32pinNum Pin number (GPIO_PIN0 to GPIO_PIN15).
 * @param Copy_u32PinState Pin state (`GPIO_SET_PIN_HIGH` or `GPIO_SET_PIN_LOW`).
 * @return GPIO_enumErrorStatus_t Returns `GPIO_enumOK` if successful, or an error code if failed.
 */
extern GPIO_enumErrorStatus_t GPIO_enumSetPinValue(u32 Copy_u32pin_port, u32 Copy_u32pinNum,  u32 Copy_u32PinState);
/**
 * @brief Reads the value of a GPIO INPUT pin.
 * 
 * @param Copy_u32pin_port GPIO_pinPort value (GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE, GPIO_PORTH)
 * @param Copy_u32pinNum Pin number (GPIO_PIN0 to GPIO_PIN15).
 * @param Add_pu32PinState Pointer to store the pin state (0(LOW) or 1(HIGH)).
 * @return GPIO_enumErrorStatus_t Returns `GPIO_enumOK` if successful, or an error code if failed.
 */
extern GPIO_enumErrorStatus_t GPIO_enumGetPinValue(u32 Copy_u32pin_port, u32 Copy_u32pinNum,  u32* Add_pu32PinState);







#endif /*_GPIO_H_*/