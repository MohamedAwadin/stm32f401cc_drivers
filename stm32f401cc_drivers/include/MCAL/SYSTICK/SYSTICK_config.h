#ifndef SYSTICK_CONFIG_H_
#define SYSTICK_CONFIG_H_





/* Configure this value according to your system's AHB clock frequency */
#define STK_AHB_FREQUENCY     16000000
#if (STK_AHB_FREQUENCY == 0)
#error "Invalid AHB frequency: cannot be zero!"
#endif

/*Choose SysTick Frequency from
 *      - STK_AHB_CLOCK
 *      - STK_AHB_CLOCK_DIV_8
 */

#define STK_CLOCK_SRC      STK_AHB_CLOCK


#endif 