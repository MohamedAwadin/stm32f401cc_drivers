#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H


#include "../../COMMON/StdTypes.h"

#define STK_BASE_ADDRESS                     0xE000E010UL   
#define STK_AHB_CLOCK                        0x00000004UL
#define STK_AHB_CLOCK_DIV_8                  0x00000000UL 



/* Masks for SysTick control */
#define STK_TICK_CLEAR_MASK                        0xFFFFFFFDUL  /* Mask to clear SysTick exception */
#define STK_ENABLE_CLEAR_MASK                      0xFFFFFFFEUL  /* Mask to clear the enable bit */
#define STK_CLKSOURCE_CLEAR_MASK                   0xFFFFFFFBUL  /* Mask to clear the clock source bit */
#define STK_ENTICK_MASK                            0x00000002UL  /* Mask to enable SysTick exception */

/* Clock source limits */
#define STK_MIN_CLKSOURCE                    1000000UL     /* Minimum clock frequency */
#define STK_MAX_CLKSOURCE                    84000000UL    /* Maximum clock frequency */

/* Load value limits */
#define STK_MAX_LOAD_VAL                     0x00FFFFFFUL  /* Maximum reload value */
#define STK_MIN_LOAD_VAL                     0x00000001UL  /* Minimum reload value */

/* Enable/disable bits */
#define STK_ENABLE_BIT                       0x00000001UL  /* Bit to enable SysTick */
#define STK_DISABLE_BIT                      0x00000000UL  /* Bit to disable SysTick */

/**************************************************************************/
/*						SYSTICK Registers Struct			 			  */
/**************************************************************************/
typedef struct
{
    volatile u32 CTRL;    /* Control and Status Register */
    volatile u32 LOAD;    /* Reload Value Register */
    volatile u32 VAL;     /* Current Value Register */
    volatile u32 CALIB;   /* Calibration Value Register */
} STK_strRegMap_t;


#define STK ((STK_strRegMap_t *)STK_BASE_ADDRESS)       

#endif /*SYSTICK_PRIVATE_H*/