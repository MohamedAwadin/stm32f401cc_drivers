#ifndef _GPIO_PRIVATE_H
#define _GPIO_PRIVATE_H

#include "../../COMMON/StdTypes.h"

/************************GPIO_BASE ADRESSES************************* */

#define GPIOA_BASE (0x40020000U)
#define GPIOB_BASE (0x40020400U)
#define GPIOC_BASE (0x40020800U)
#define GPIOD_BASE (0x40020C00U)
#define GPIOE_BASE (0x40021000U)
#define GPIOH_BASE (0x40021C00U)

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

/* ***********************GPIO Register BIT_MUSKS*********************** */

#define GPIO_CLRMODE_MODERx_BITMUSK_        (0xFFFFFFFC)
#define GPIO_CLROTYPE_OTYPERx_BITMUSK_      (0xFFFFFFFE)
#define GPIO_CLROSPEED_OSPEEDRx_BITMUSK_    (0xFFFFFFFC)
#define GPIO_CLRPUPD_PUPDRx_BITMUSK_        (0xFFFFFFFC)
#define GPIO_CLRAF_AFRx_BITMUSK_            (0xFFFFFFF0)
#define GPIO_GETBITV_IDRx_BITMUSK_            (0x00000001)






#endif /*_GPIO_PRIVATE_H*/
