#ifndef _GPIO_H_
#define _GPIO_H_

#include "../../COMMON/StdTypes.h"
#include "GPIO_private.h"


/*************************MACROS - GPIO Ports*************************/
/**
 * @def GPIOA
 * @brief Macro to access the GPIOA registers.
 */
#define GPIOA ((GPIO_strRegMap_t *)(GPIOA_BASE))

/**
 * @def GPIOB
 * @brief Macro to access the GPIOB registers.
 */
#define GPIOB ((GPIO_strRegMap_t *)(GPIOB_BASE))

/**
 * @def GPIOC
 * @brief Macro to access the GPIOC registers.
 */
#define GPIOC ((GPIO_strRegMap_t *)(GPIOC_BASE))

/**
 * @def GPIOD
 * @brief Macro to access the GPIOD registers.
 */
#define GPIOD ((GPIO_strRegMap_t *)(GPIOD_BASE))

/**
 * @def GPIOE
 * @brief Macro to access the GPIOE registers.
 */
#define GPIOE ((GPIO_strRegMap_t *)(GPIOE_BASE))


/**
 * @def GPIOH
 * @brief Macro to access the GPIOH registers.
 */
#define GPIOH ((GPIO_strRegMap_t *)(GPIOH_BASE))
/************************************************************* */

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
#define GPIO_PIN0               0
#define GPIO_PIN1               1
#define GPIO_PIN2               2
#define GPIO_PIN3               3
#define GPIO_PIN4               4
#define GPIO_PIN5               5
#define GPIO_PIN6               6
#define GPIO_PIN7               7
#define GPIO_PIN8               8
#define GPIO_PIN9               9
#define GPIO_PIN10              10
#define GPIO_PIN11              11
#define GPIO_PIN12              12
#define GPIO_PIN13              13
#define GPIO_PIN14              14
#define GPIO_PIN15              15

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
#define GPIO_AF00                  (0)
#define GPIO_AF01                  (1)
#define GPIO_AF02                  (2)
#define GPIO_AF03                  (3)
#define GPIO_AF04                  (4)
#define GPIO_AF05                  (5)
#define GPIO_AF06                  (6)
#define GPIO_AF07                  (7)
#define GPIO_AF08                  (8)
#define GPIO_AF09                  (9)
#define GPIO_AF10                  (10)
#define GPIO_AF11                  (11)
#define GPIO_AF12                  (12)
#define GPIO_AF13                  (13)
#define GPIO_AF14                  (14)
#define GPIO_AF15                  (15)
#define GPIO_AF_DISABLED                  (16)

/*------------------- GPIO Value Pin (State) -----------------
 * These Masks used to set/reset the output value of GPIO Pins
 * using BSRR Register    
 */
#define GPIO_SET_PIN_HIGH       (0x00000001UL)  /* BSRR Bit0:Bit15*/
#define GPIO_SET_PIN_LOW        (0x00010000UL)  /* BSRR Bit16:Bit31*/

/* **************Struct - Pin Configurations**************** */

typedef struct 
{
    volatile GPIO_strRegMap_t *GPIO_pinPort;
    volatile u32 GPIO_pinNum;
    volatile u32 GPIO_pinMode;
    volatile u32 GPIO_pinOutType;
    volatile u32 GPIO_pinSpeed;
    volatile u32 GPIO_pinPull;
    volatile u32 GPIO_pinAF;
}GPIO_strPinConfig_t;


/********************Functions Prototype********************* */
GPIO_enumErrorStatus_t GPIO_enumConfigPin(GPIO_strPinConfig_t *Add_pstrPinConfig);
GPIO_enumErrorStatus_t GPIO_enumSetPinValue(GPIO_strPinConfig_t *Add_pstrPinConfig, u32 Copy_u32PinState);
GPIO_enumErrorStatus_t GPIO_enumGetPinValue(GPIO_strPinConfig_t *Add_pstrPinConfig, u32* Add_pu32PinState);







#endif /*_GPIO_H_*/