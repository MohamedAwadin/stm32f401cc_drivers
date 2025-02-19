#include "../../../include/COMMON/Utils.h"
#include "../../../include/COMMON/StdTypes.h"

#include "../../../include/MCAL/NVIC/NVIC.h"
#include "../../../include/MCAL/NVIC/NVIC_private.h"


#define EIGHT_BIT_SHIFT 8
#define FOUR_BIT_SHIFT 4
#define BYTE_MASK       0x000000FF
#define BYTE            8U 
NVIC_ErrorStatus_t NVIC_enumEnableIRQ(NVIC_enumIRQn_Type Copy_enuIRQn)
{
     NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u8 Loc_u8RegNum = (u8)Copy_enuIRQn / NVIC_REGISTER_SIZE;
    u8 Loc_u8BitNum = (u8)Copy_enuIRQn % NVIC_REGISTER_SIZE;

    if (Copy_enuIRQn >= NVIC_IRQn_MAX)
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

    if (Copy_enuIRQn >= NVIC_IRQn_MAX)
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

    if (Copy_enuIRQn >= NVIC_IRQn_MAX)
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

    if (Copy_enuIRQn >= NVIC_IRQn_MAX)
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
    else if ((u8)Copy_enuIRQn >= NVIC_IRQn_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else
    {
        
		if (NVIC->ISPR[Loc_u8RegNum] & (NVIC_SET_MASK << Loc_u8BitNum))
		{
			
			*Add_pu8GetPendingStatus = NVIC_u8PENDING_ON;
		}
		else
		{
			
			*Add_pu8GetPendingStatus = NVIC_u8PENDING_OFF;
		}
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_enumSetPriority(NVIC_enumIRQn_Type Copy_enuIRQn, u32 Copy_u32SubPriorityGroup, u32 Copy_u32PreemptPriority, u32 Copy_u32SubPriority)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u8 Loc_u8Priority_RegNUM  =0 ;
    u8 Loc_u8Priority_ByteNUM  =0  ;
    u32 Loc_u32TempReg = 0 ;

    
    u8 Loc_u8SUBPriorityGroupNum = (u8)(((Copy_u32SubPriorityGroup>>8)&0x07)-0x03);

    u8 Loc_u8PreemptPriorityNum = NVIC_PRIO_BITS - Loc_u8SUBPriorityGroupNum ;

    u8 Loc_u8MaxSubPriority           = ((1U << Loc_u8SUBPriorityGroupNum) - 1 );
    u8 Loc_u8MaxPreemptPriority       = ((1U <<Loc_u8PreemptPriorityNum) - 1 );

    if (Copy_enuIRQn >= NVIC_IRQn_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else if (Loc_u8SUBPriorityGroupNum + Loc_u8PreemptPriorityNum > NVIC_PRIO_BITS)
    {
        Local_enumErrorRet = NVIC_enumErrorSubPriorityGroup;
    }
    else if (Copy_u32SubPriority >Loc_u8MaxSubPriority )
    {
        Local_enumErrorRet = NVIC_enumErrorSubPriority ;
    }
    else if (Copy_u32PreemptPriority >Loc_u8MaxPreemptPriority )
    {
        Local_enumErrorRet = NVIC_enumErrorPreemptPriority ;
    }
    else
    {
        Loc_u8Priority_RegNUM   = Copy_enuIRQn  / 4  ;
        Loc_u8Priority_ByteNUM  = Copy_enuIRQn  % 4  ;
        Loc_u32TempReg =   NVIC->IPR[Loc_u8Priority_RegNUM] ;
        Loc_u32TempReg &= ~(BYTE_MASK << Loc_u8Priority_ByteNUM);
        Loc_u32TempReg |= ((((Copy_u32PreemptPriority<<Loc_u8SUBPriorityGroupNum)|(Copy_u32SubPriority))<<FOUR_BIT_SHIFT)<<(Loc_u8Priority_ByteNUM *8U ));
        NVIC->IPR[Loc_u8Priority_RegNUM] |= Loc_u32TempReg;
        
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
    else if (Copy_enuIRQn >= NVIC_IRQn_MAX)
    {

        
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else
    {
        u8 Loc_u8Priority_RegNUM   = Copy_enuIRQn  / 4  ;
        *Add_pu32GetPriority = NVIC->IPR[Loc_u8Priority_RegNUM];
    }

    return Local_enumErrorRet;
}

NVIC_ErrorStatus_t NVIC_enumGetActive(NVIC_enumIRQn_Type Copy_enuIRQn, u8 *Add_pu8GetActiveStatus)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u8 Loc_u8RegNum = (u8)Copy_enuIRQn / NVIC_REGISTER_SIZE;
    u8 Loc_u8BitNum = (u8)Copy_enuIRQn % NVIC_REGISTER_SIZE;

    if (Copy_enuIRQn >= NVIC_IRQn_MAX)
    {
        Local_enumErrorRet = NVIC_enumErrorIRQNumber;
    }
    else if(Add_pu8GetActiveStatus == NULL_PTR)
    {
        Local_enumErrorRet = NVIC_enumErrorNullPointer;
    }
    else
    {
        
		if (NVIC->IABR[Loc_u8RegNum] & (NVIC_SET_MASK << Loc_u8BitNum))
		{
			
			*Add_pu8GetActiveStatus = NVIC_u8ACTIVE_;
		}
		else
		{
			
			*Add_pu8GetActiveStatus = NVIC_u8NOTACTIVE_;
		}
    }

    return Local_enumErrorRet;
}




NVIC_ErrorStatus_t NVIC_SetSubPriorityGrouping(u32 Copy_u32PriorityGroup)
{
    NVIC_ErrorStatus_t Local_enumErrorRet = NVIC_enumOk;
    u32 Local_u32TempReg = 0 ;
    if (Copy_u32PriorityGroup&SCB_AIRCR_PRIGROUP_VLD_MASK)
    {
        Local_enumErrorRet = NVIC_enumErrorSubPriorityGroup;
    }
    else
    {
        Local_u32TempReg  = SCB->AIRCR ;
        Local_u32TempReg &=  SCB_AIRCR_VECTKEY_CLR_MASK;
        Local_u32TempReg &=  SCB_AIRCR_PRIGROUP_CLR_MASK;
        Local_u32TempReg |=  SCB_AIRCR_VECTKEY_MASK;
        Local_u32TempReg |=  Copy_u32PriorityGroup;
        SCB->AIRCR= Local_u32TempReg ;

        
    }

    return Local_enumErrorRet;
}


