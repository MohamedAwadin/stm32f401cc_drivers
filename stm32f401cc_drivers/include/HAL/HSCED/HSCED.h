#ifndef HSCED_H
#define HSCED_H

#include "../../MCAL/SYSTICK/SYSTICK.h"
#include "../../COMMON/StdTypes.h"
#include "../../COMMON/Utils.h"

/* Maximum number of runnables that can be registered */
#define HSCED_MAX_RUNNABLES 100 




/* Scheduler error status */
typedef enum
{
    HSCED_enumOk,                   /* Operation successful */                  
    HSCED_enumNOk,                  /* General error */
    HSCED_enumExceedsMaxRunnable,   /* Runnable priority exceeds maximum */
    HSCED_enumNullPtr,              /* Null pointer passed */
    HSCED_enumPriorityTaken,        /* Priority slot already occupied */
    HSCED_enumSTKInit_ERROR,        /* SysTick initialization failed */
    HSCED_enumSTKSet_ERROR,         /* SysTick callback registration failed */
    HSCED_enumSTKStart_ERROR,       /* SysTick start failed */
    HSCED_enumSTKStop_ERROR,        /* SysTick stop failed */
    

} HSCED_ErrorStatus_t;

/* Typedef for scheduler callback function */
typedef void (*HSCED_CallBackFunc_t) (void); 




/* Structure to define a runnable configuration */
typedef struct 
{
    u32 volatile                 HSCED_u32RunnablePriority;    /* Priority of the runnable */
    u32 volatile                 HSCED_u32RunnableCyclicTime;  /* Cyclic time in milliseconds */ 
    HSCED_CallBackFunc_t         HSCED_pfnRunnableCallback;    /* Callback function to be executed */
    u32 volatile                 HSCED_u32RunnableFirstdelay;  /* Initial delay in milliseconds */ 
} HSCED_RunnableConfig_t;


/* *******************Function prototypes *************************************/


/**
 * @brief Initialize the scheduler.
 * @return HSCED_ErrorStatus_t - Status of the initialization.
 */

HSCED_ErrorStatus_t HSCED_enumInit(void); 


/**
 * @brief Register a runnable with the scheduler.
 * @param runnable - Pointer to the runnable configuration.
 * @return HSCED_ErrorStatus_t - Status of the operation.
 */
HSCED_ErrorStatus_t HSCED_enumRegisterRunnable(const HSCED_RunnableConfig_t *Add_pstrRunnable); 


/**
 * @brief Start the scheduler.
 * @return HSCED_ErrorStatus_t - Status of the operation.
 */
HSCED_ErrorStatus_t HSCED_enumStart(void);

/**
 * @brief Stop the scheduler.
 * @return HSCED_ErrorStatus_t - Status of the operation.
 */
HSCED_ErrorStatus_t HSCED_enumStop(void);  

#endif /* HSCED_H */    