#include "../../../include/COMMON/Utils.h"
#include "../../../include/COMMON/StdTypes.h"

#include "../../../include/MCAL/NVIC/NVIC.h"
#include "../../../include/MCAL/NVIC/NVIC_private.h"

NVIC_ErrorStatus_t NVIC_enumEnableIRQ(NVIC_enumIRQn_Type Copy_enuIRQn)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u8 Loc_u8RegNum = (u8)Copy_enuIRQn / NVIC_REGISTER_SIZE;
    u8 Loc_u8BitNum = (u8)Copy_enuIRQn % NVIC_REGISTER_SIZE;

    if ((u8)Copy_enuIRQn > NVIC_IRQn_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else
    {
        NVIC->ISER[Loc_u8RegNum] = (NVIC_SET_MASK << Loc_u8BitNum);
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_enumDisableIRQ(NVIC_enumIRQn_Type Copy_enuIRQn)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u8 Loc_u8RegNum = (u8)Copy_enuIRQn / NVIC_REGISTER_SIZE;
    u8 Loc_u8BitNum = (u8)Copy_enuIRQn % NVIC_REGISTER_SIZE;

    if ((u8)Copy_enuIRQn > NVIC_IRQn_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else
    {
        NVIC->ICER[Loc_u8RegNum] = (NVIC_SET_MASK << Loc_u8BitNum);
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_enumSetPendingIRQ(NVIC_enumIRQn_Type Copy_enuIRQn)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u8 Loc_u8RegNum = (u8)Copy_enuIRQn / NVIC_REGISTER_SIZE;
    u8 Loc_u8BitNum = (u8)Copy_enuIRQn % NVIC_REGISTER_SIZE;

    if ((u8)Copy_enuIRQn > NVIC_IRQn_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else
    {
        NVIC->ISPR[Loc_u8RegNum] = (NVIC_SET_MASK << Loc_u8BitNum);
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_enumClearPendingIRQ(NVIC_enumIRQn_Type Copy_enuIRQn)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u8 Loc_u8RegNum = (u8)Copy_enuIRQn / NVIC_REGISTER_SIZE;
    u8 Loc_u8BitNum = (u8)Copy_enuIRQn % NVIC_REGISTER_SIZE;

    if ((u8)Copy_enuIRQn > NVIC_IRQn_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else
    {
        NVIC->ICPR[Loc_u8RegNum] = (NVIC_SET_MASK << Loc_u8BitNum);
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_enumGetPendingIRQ(NVIC_enumIRQn_Type Copy_enuIRQn, u8 *Add_pu8GetPendingStatus)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u8 Loc_u8RegNum = (u8)Copy_enuIRQn / NVIC_REGISTER_SIZE;
    u8 Loc_u8BitNum = (u8)Copy_enuIRQn % NVIC_REGISTER_SIZE;

    if (Add_pu8GetPendingStatus == NULL_PTR)
    {
        Local_enumErrorRet = NVIC_enumErrorNullPointer;
    }
    else if ((u8)Copy_enuIRQn > NVIC_IRQn_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else
    {
        *Add_pu8GetPendingStatus = READ_BIT(NVIC->ICPR[Loc_u8RegNum], Loc_u8BitNum);
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_enumSetPriority(NVIC_enumIRQn_Type Copy_enuIRQn, u32 Copy_u32Priority)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;

    if ((u32)Copy_enuIRQn < NVIC_IRQn_MAX)
    {

        NVIC->IPR[Copy_enuIRQn] = Copy_u32Priority & NVIC_SET_PRIORITY_MASK;
    }
    else
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_enumGetPriority(NVIC_enumIRQn_Type Copy_enuIRQn, u32 *Add_pu32GetPriority)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;

    if (Add_pu32GetPriority == NULL_PTR)
    {
        Local_enumErrorRet = NVIC_enumErrorNullPointer;
    }
    else if ((u32)Copy_enuIRQn < NVIC_IRQn_MAX)
    {

        *Add_pu32GetPriority = NVIC->IPR[Copy_enuIRQn];
    }
    else
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_enumGetActive(NVIC_enumIRQn_Type Copy_enuIRQn, u8 *Add_pu8GetActiveStatus)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u8 Loc_u8RegNum = (u8)Copy_enuIRQn / NVIC_REGISTER_SIZE;
    u8 Loc_u8BitNum = (u8)Copy_enuIRQn % NVIC_REGISTER_SIZE;

    if ((u8)Copy_enuIRQn > NVIC_IRQn_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else
    {
        *Add_pu8GetActiveStatus = READ_BIT(NVIC->IABR[Loc_u8RegNum], Loc_u8BitNum);
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_EncodePriority(u32 Copy_u32PriorityGroup, u32 Copy_u32PreemptPriority, u32 Copy_u32SubPriority, u32 *Add_pu8EncodedPriority)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;

    // Calculate the number of bits for PreemptPriority and SubPriority
    u32 Local_u32PreemptPriorityBits = Copy_u32PriorityGroup;
    u32 Local_u32SubPriorityBits = NVIC_PRIO_BITS - Copy_u32PriorityGroup; // Total priority bits = 4 (STM32F401CC)

    // Validate PriorityGroup (0 to 7)
    if (Copy_u32PriorityGroup > NVIC_PRIORITY_GROUP_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorPriorityGroup;
    }
    else if (Copy_u32PreemptPriority >= (1 << Local_u32PreemptPriorityBits))
    {
        Local_enumErrorRet = NVIC_enumErrorPreemptPriority;
    }
    else if (Copy_u32SubPriority >= (1 << Local_u32SubPriorityBits))
    {
        Local_enumErrorRet = NVIC_enumErrorSubPriority;
    }
    else
    {
        // Encode the priority
        *Add_pu8EncodedPriority = (Copy_u32PreemptPriority << Local_u32SubPriorityBits) | Copy_u32SubPriority;
    }

    return Local_enumErrorRet;
}





NVIC_ErrorStatus_t NVIC_SetPriorityGrouping(u32 Copy_u32PriorityGroup)
{
    u32 Local_u32reg_value;

    // Ensure Priority Group is within valid range (0-4)
    if (Copy_u32PriorityGroup > NVIC_PRIORITY_GROUP_4)
    {
        return NVIC_enumErrorPriorityGroup;
    }

    // Read current AIRCR value
    Local_u32reg_value = SCB->AIRCR;

    // Clear VECTKEY and PRIGROUP fields
    Local_u32reg_value &= ~((u32)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk));

    // Insert VECTKEY and new priority group
    Local_u32reg_value |= (SCB_VECTKEY_MASK << SCB_AIRCR_VECTKEY_Pos) | (Copy_u32PriorityGroup & NVIC_PRIORITY_GROUP_MASK);

    // Write to AIRCR register
    SCB->AIRCR = Local_u32reg_value;

    return NVIC_enumOk;
}


NVIC_ErrorStatus_t NVIC_GetPriorityGrouping(u32* Add_pu32PriorityGroup)
{
    return ((u32)((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos));
}