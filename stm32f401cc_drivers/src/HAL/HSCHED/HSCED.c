#include "../../../include/HAL/HSCED/HSCED.h"

/* Array to store registered runnables */
static volatile HSCED_RunnableConfig_t *HSCED_Runnable_Array[HSCED_MAX_RUNNABLES];
/* Variable to keep track of scheduler ticks */
static volatile u64 HSCED_u64Ticks = 0;


/**
 * @brief  **Private** Cyclic function called by SysTick interrupt.
 * @details This function is called every 1ms and executes the registered runnables based on their cyclic time and initial delay.
 */
static void HSCED_vSchedulerHandler(void)
{

    HSCED_u64Ticks++;
    u32 Local_u32Iter  = 0 ;

    for (Local_u32Iter = 0; Local_u32Iter < HSCED_MAX_RUNNABLES; Local_u32Iter++)
    {
        if (HSCED_Runnable_Array[Local_u32Iter] != NULL_PTR && HSCED_Runnable_Array[Local_u32Iter]->HSCED_pfnRunnableCallback != NULL_PTR)
        {

            if ((HSCED_Runnable_Array[Local_u32Iter]->HSCED_u32RunnableFirstdelay == 0) &&
                (HSCED_Runnable_Array[Local_u32Iter]->HSCED_u32RunnableCyclicTime > 0) &&
                ((HSCED_u64Ticks % HSCED_Runnable_Array[Local_u32Iter]->HSCED_u32RunnableCyclicTime) == 0))

            {
                HSCED_Runnable_Array[Local_u32Iter]->HSCED_pfnRunnableCallback();
            }
            else if (HSCED_Runnable_Array[Local_u32Iter]->HSCED_u32RunnableFirstdelay != 0)
            {
                HSCED_Runnable_Array[Local_u32Iter]->HSCED_u32RunnableFirstdelay--;
            }
        }
    }
}



HSCED_ErrorStatus_t HSCED_enumRegisterRunnable(const HSCED_RunnableConfig_t *Add_pstrRunnable)
{
    HSCED_ErrorStatus_t Local_enumErrorRet = HSCED_enumOk;
    if (Add_pstrRunnable == NULL_PTR)
    {
        Local_enumErrorRet = HSCED_enumNullPtr;
    }
    else if ((Add_pstrRunnable->HSCED_u32RunnablePriority) >= HSCED_MAX_RUNNABLES)
    {
        Local_enumErrorRet = HSCED_enumExceedsMaxRunnable;
    }
    else if (HSCED_Runnable_Array[Add_pstrRunnable->HSCED_u32RunnablePriority] != NULL_PTR)
    {
        Local_enumErrorRet = HSCED_enumPriorityTaken;
    }
    else
    {
        HSCED_Runnable_Array[Add_pstrRunnable->HSCED_u32RunnablePriority] = (HSCED_RunnableConfig_t *)Add_pstrRunnable;
    }
    return Local_enumErrorRet;
}


HSCED_ErrorStatus_t HSCED_enumInit(void)
{
    HSCED_ErrorStatus_t Local_enumErrorRet = HSCED_enumOk;
    Local_enumErrorRet = STK_enumInit1MS();
    if (Local_enumErrorRet != STK_enumOK)
    {
        return HSCED_enumSTKInit_ERROR;
    }

    Local_enumErrorRet = STK_enumSetCallBackFunc(&HSCED_vSchedulerHandler, 1);

    if (Local_enumErrorRet != STK_enumOK)
    {
        return HSCED_enumSTKSet_ERROR;
    }

    return HSCED_enumOk;
}

HSCED_ErrorStatus_t HSCED_enumStart(void)
{

    HSCED_ErrorStatus_t Local_enumErrorRet = HSCED_enumOk;
    HSCED_u64Ticks = 0;
    Local_enumErrorRet = STK_enumStart();
    if (Local_enumErrorRet != STK_enumOK)
    {
        Local_enumErrorRet = HSCED_enumSTKStart_ERROR;
    }
    return Local_enumErrorRet;
}

HSCED_ErrorStatus_t HSCED_enumStop(void)
{
    HSCED_ErrorStatus_t Local_enumErrorRet = HSCED_enumOk;
    HSCED_u64Ticks = 0;

    Local_enumErrorRet = STK_enumStop();
    if (Local_enumErrorRet != STK_enumOK)
    {
        Local_enumErrorRet = HSCED_enumSTKStop_ERROR;
    }
    return Local_enumErrorRet;
}