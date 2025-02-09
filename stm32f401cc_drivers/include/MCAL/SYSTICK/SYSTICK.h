#ifndef SYSTICK_H
#define SYSTICK_H


#include "../../COMMON/StdTypes.h"
#include "SYSTICK_private.h"
/* Typedef for SysTick callback function pointer */

typedef void (*STK_CallBackFunc_t) (void);

typedef enum
{
    STK_enumOK,
    STK_enumNOk,
    STK_enumInvalidCLKSOURCE,
    STK_enumInvalidLoadVal,
    STK_enumNullPtr,
    STK_enumInvalidTickTime,
    STK_enumAlreadyRunning,
    STK_enumAlreadyStopped
} STK_ErrorStatus_t;



/**
 * @brief Initialize the SysTick timer for a 1ms tick interval.
 * @return STK_ErrorStatus_t - Status of the initialization (STK_enumOK if successful).
 */
STK_ErrorStatus_t STK_enumInit1MS(void);
/**
 * @brief Set a callback function to be executed at a specified interval.
 * @param Add_pCallBackFunc - Pointer to the callback function.
 * @param Copy_u32TickCBF_TimeMs - Interval in milliseconds for the callback execution.
 * @return STK_ErrorStatus_t - Status of the operation (STK_enumOK if successful).
 */
STK_ErrorStatus_t STK_enumSetCallBackFunc(STK_CallBackFunc_t Add_pCallBackFunc, u32 Copy_u32TickCBF_TimeMs);
/**
 * @brief Create a blocking delay for a specified number of milliseconds.
 * @param Copy_u32DelayMS - Delay duration in milliseconds.
 * @return STK_ErrorStatus_t - Status of the operation (STK_enumOK if successful).
 */
STK_ErrorStatus_t STK_enumDelayMS(u32 Copy_u32DelayMS);

/**
 * @brief Start the SysTick timer.
 * @return STK_ErrorStatus_t - Status of the operation (STK_enumOK if successful).
 */
STK_ErrorStatus_t STK_enumStart(void);
/**
 * @brief Stop the SysTick timer.
 * @return STK_ErrorStatus_t - Status of the operation (STK_enumOK if successful).
 */
STK_ErrorStatus_t STK_enumStop(void);


#endif /*SYSTICK_H*/