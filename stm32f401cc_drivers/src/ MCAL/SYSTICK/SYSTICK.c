#include "../../../include/COMMON/Utils.h"
#include "../../../include/COMMON/StdTypes.h"
#include "../../../include/MCAL/SYSTICK/SYSTICK.h"
#include "../../../include/MCAL/SYSTICK/SYSTICK_private.h"
#include "../../../include/MCAL/SYSTICK/SYSTICK_config.h"

static STK_CallBackFunc_t STK_pfCallBackSaved = NULL_PTR;
static volatile u32 STK_u32TickCBF_TimeSaved = 0;
static volatile u32 STK_u32PassedTickCount = 0;

STK_ErrorStatus_t STK_enumInit1MS(void)
{
    STK_ErrorStatus_t Local_enumErrorRet = STK_enumOK;
    u32 Local_u32CurrentSTKCLK = ((STK_CLOCK_SRC == STK_AHB_CLOCK) ? STK_AHB_FREQUENCY : (STK_AHB_FREQUENCY / 8));

    u32 Local_u32CurrentReloadVal = ((u32)(Local_u32CurrentSTKCLK) / (u32)1000) - (u32)1;

    u32 Local_u32TempCTRL_REG = 0;

    if ((Local_u32CurrentSTKCLK <= STK_MIN_CLKSOURCE) || (Local_u32CurrentSTKCLK >= STK_MAX_CLKSOURCE))
    {
        Local_enumErrorRet = STK_enumInvalidCLKSOURCE;
    }
    else if ((Local_u32CurrentReloadVal < STK_MIN_LOAD_VAL) || (Local_u32CurrentReloadVal > STK_MAX_LOAD_VAL))
    {
        Local_enumErrorRet = STK_enumInvalidLoadVal; 
    }
    else
    {

        /* Set Clock Source */
        Local_u32TempCTRL_REG = STK->CTRL;
        Local_u32TempCTRL_REG &= STK_CLKSOURCE_CLEAR_MASK;
        Local_u32TempCTRL_REG |= STK_CLOCK_SRC;

        /*Set Reload Value Register*/
        STK->LOAD = Local_u32CurrentReloadVal;

        /*Reset Current value register */
        STK->VAL = 0;

        Local_u32TempCTRL_REG &= STK_TICK_CLEAR_MASK;
        Local_u32TempCTRL_REG |= STK_ENTICK_MASK;

        STK->CTRL = Local_u32TempCTRL_REG;
    }

    return Local_enumErrorRet;
}

STK_ErrorStatus_t STK_enumSetCallBackFunc(STK_CallBackFunc_t Add_pCallBackFunc, u32 Copy_u32TickCBF_TimeMs)
{
    STK_ErrorStatus_t Local_enumErrorRet = STK_enumOK;

    if (Add_pCallBackFunc == NULL_PTR)
    {
        Local_enumErrorRet = STK_enumNullPtr;
    }
    else if (Copy_u32TickCBF_TimeMs <= 0)
    {
        Local_enumErrorRet = STK_enumInvalidTickTime;
    }
    else
    {
        STK_pfCallBackSaved = Add_pCallBackFunc;
        STK_u32TickCBF_TimeSaved = Copy_u32TickCBF_TimeMs;
    }
    return Local_enumErrorRet;
}

static void STK_vHandler(void)
{
    STK_u32PassedTickCount++;
    if ((STK_u32PassedTickCount % STK_u32TickCBF_TimeSaved) == 0)
    {
        if (STK_pfCallBackSaved != NULL_PTR)
        {
            STK_pfCallBackSaved();
        }
    }
}

STK_ErrorStatus_t STK_enumDelayMS(u32 Copy_u32DelayMS)
{
    STK_ErrorStatus_t Local_enumErrorRet = STK_enumOK;
    u32 Local_u32DelayStartTime = STK_u32PassedTickCount;
    while ((STK_u32PassedTickCount - Local_u32DelayStartTime) < Copy_u32DelayMS)
    {
        // Wait until the delay has passed
    }
    return Local_enumErrorRet;
}

STK_ErrorStatus_t STK_enumStart(void)
{
    STK_ErrorStatus_t Local_enumErrorRet = STK_enumOK;
    if ((STK->CTRL & STK_ENABLE_BIT) == STK_ENABLE_BIT)
    {
        Local_enumErrorRet = STK_enumAlreadyRunning;
    }
    else
    {
        /* Enable SysTick */
        u32 Local_u32TempCTRL_REG = STK->CTRL;
        Local_u32TempCTRL_REG &= STK_ENABLE_CLEAR_MASK;
        Local_u32TempCTRL_REG |= STK_ENABLE_BIT;
        STK->CTRL = Local_u32TempCTRL_REG;
    }

    return Local_enumErrorRet;
}

STK_ErrorStatus_t STK_enumStop(void)
{
    STK_ErrorStatus_t Local_enumErrorRet = STK_enumOK;
    if ((STK->CTRL & STK_ENABLE_BIT) == STK_DISABLE_BIT)
    {
        Local_enumErrorRet = STK_enumAlreadyStopped;
    }
    else{
        
        /* Disable SysTick */
        u32 Local_u32TempCTRL_REG = STK->CTRL;
        Local_u32TempCTRL_REG &= STK_ENABLE_CLEAR_MASK;
        Local_u32TempCTRL_REG &= ~STK_ENABLE_BIT;
        STK->CTRL = Local_u32TempCTRL_REG;
    }
    return Local_enumErrorRet;
    
}
