#ifndef _GPIO_PRIVATE_H
#define _GPIO_PRIVATE_H

#include "../../COMMON/StdTypes.h"

/************************GPIO_BASE ADRESSES************************* */

#define GPIOA_BASE                         (0x40020000U)
#define GPIOB_BASE                         (0x40020400U)
#define GPIOC_BASE                         (0x40020800U)
#define GPIOD_BASE                         (0x40020C00U)
#define GPIOE_BASE                         (0x40021000U)
#define GPIOH_BASE                         (0x40021C00U)

/********************************************************************* */


/* ***********************GPIO Register Structure*********************** */
typedef struct {
    volatile u32 MODER;    // Mode register
    volatile u32 OTYPER;   // Output type register
    volatile u32 OSPEEDR;  // Output speed register
    volatile u32 PUPDR;    // Pull-up/pull-down register
    volatile u32 IDR;      // Input data register
    volatile u32 ODR;      // Output data register
    volatile u32 BSRR;     // Bit set/reset register
    volatile u32 LCKR;     // Configuration lock register
    volatile u32 AFR[2];   // Alternate function registers (AFRL and AFRH)
} GPIO_strRegMap_t;


/* Array of pointers to GPIO register structures */
static GPIO_strRegMap_t *const GPIO_PORTS[] = {
    (GPIO_strRegMap_t *)(GPIOA_BASE),  // GPIO_PORTA
    (GPIO_strRegMap_t *)(GPIOB_BASE),  // GPIO_PORTB
    (GPIO_strRegMap_t *)(GPIOC_BASE),  // GPIO_PORTC
    (GPIO_strRegMap_t *)(GPIOD_BASE),  // GPIO_PORTD
    (GPIO_strRegMap_t *)(GPIOE_BASE),  // GPIO_PORTE
    (GPIO_strRegMap_t *)(GPIOH_BASE)   // GPIO_PORTH
};

/* ***********************GPIO Register BIT_MASKS*********************** */

#define GPIO_CLRMODE_MODERx_BITMASK_          (u32)(0xFFFFFFFC)
#define GPIO_CLROTYPE_OTYPERx_BITMASK_        (u32)(0xFFFFFFFE)
#define GPIO_CLROSPEED_OSPEEDRx_BITMASK_      (u32)(0xFFFFFFFC)
#define GPIO_CLRPUPD_PUPDRx_BITMASK_          (u32)(0xFFFFFFFC)
#define GPIO_CLRAF_AFRx_BITMASK_              (u32)(0xFFFFFFF0)
#define GPIO_GETBITV_IDRx_BITMASK_            (u32)(0x00000001)






#endif /*_GPIO_PRIVATE_H*/
