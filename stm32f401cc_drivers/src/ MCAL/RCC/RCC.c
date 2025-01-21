

#include "../../../include/COMMON/Utils.h"
#include "../../../include/COMMON/StdTypes.h"


#include "../../../include/MCAL/RCC/RCC.h"
#include "../../../include/MCAL/RCC/RCC_private.h"

RCC_enumErrorStatus_t RCC_enuControlSysClock(RCC_enumSetClk_Source_t Copy_enumSource)
{
    RCC_enumErrorStatus_t Local_enuRetError = RCC_enumOk;
    u16 Local_u16TimeOut = RCC_u16TIME_OUT;
    u32 Local_u32TempReg;

    if ((Copy_enumSource) > (RCC_enumPLL_CLOCK))
    {
        Local_enuRetError = RCC_enumErrorClock;
    }
    else
    {

        switch (Copy_enumSource)
        {
        case RCC_enumHSI_CLOCK:
            if ((RCC->RCC_CR & RCC_HSIRDY_CR_BITMUSK_))
            {
                Local_u32TempReg = (RCC->RCC_CFGR);
                Local_u32TempReg &= RCC_RSTSW_CFGR_BITMUSK_;
                Local_u32TempReg |= Copy_enumSource;
                RCC->RCC_CFGR = Local_u32TempReg;
            }
            else
            {
                Local_enuRetError = RCC_enumErrorClkNotRdy;
            }

            break;

        case RCC_enumHSE_CLOCK:
            if ((RCC->RCC_CR & RCC_HSERDY_CR_BITMUSK_))
            {
                Local_u32TempReg = (RCC->RCC_CFGR);
                Local_u32TempReg &= RCC_RSTSW_CFGR_BITMUSK_;
                Local_u32TempReg |= Copy_enumSource;
                RCC->RCC_CFGR = Local_u32TempReg;
            }
            else
            {
                Local_enuRetError = RCC_enumErrorClkNotRdy;
            }
            break;
        case RCC_enumPLL_CLOCK:

            if ((RCC->RCC_CR & RCC_PLLON_CR_BITMUSK_))
            {

                Local_u32TempReg = (RCC->RCC_CFGR);
                Local_u32TempReg &= RCC_RSTSW_CFGR_BITMUSK_;
                Local_u32TempReg |= Copy_enumSource;
                RCC->RCC_CFGR = Local_u32TempReg;
            }
            else
            {
                Local_enuRetError = RCC_enumErrorClkNotRdy;
            }
            break;
        default:
            break;
        }
        Local_enuRetError = RCC_enumErrorTimedOut; // Timeout error
        //    Wait for the clock switch to complete
        while ((Local_u16TimeOut--) && ((RCC->RCC_CFGR & RCC_SWS_CFGR_BITMUSK_ >> RCC_CFGR_SWS0) != Copy_enumSource))
            ;

        // Check if the switch was successful
        if ((RCC->RCC_CFGR & RCC_SWS_CFGR_BITMUSK_ >> RCC_CFGR_SWS0) == Copy_enumSource)
        {
            Local_enuRetError = RCC_enumOk; // Success
        }
    }
    return Local_enuRetError; // Return the correct error status
}

RCC_enumErrorStatus_t RCC_enuSetClock_Status(RCC_enumSetClk_Source_t Copy_enumSource, RCC_enumSetClk_Status_t Copy_enumStatus)
{
    RCC_enumErrorStatus_t Local_enuRetError = RCC_enumOk;
    u16 Local_u16TimeOut = RCC_u16TIME_OUT;

    if ((Copy_enumSource > RCC_enumPLL_CLOCK))
    {
        Local_enuRetError = RCC_enumErrorClock; // Invalid input
    }
    else if (Copy_enumStatus > RCC_enumCLK_ON)
    {
        Local_enuRetError = RCC_enumErrorSetClkStatus;
    }
    else if ((RCC->RCC_CFGR & RCC_SWS_CFGR_BITMUSK_ >> RCC_CFGR_SWS0) == Copy_enumSource)
    {
        Local_enuRetError = RCC_enumErrorSelectSysClk;
    }
    else if ((RCC->RCC_PLLCFGR & RCC_PLLSRC_PLLCFGR_BITMUSK_) == Copy_enumSource)
    {
        Local_enuRetError = RCC_enumErrorSelectPllClk;
    }
    else
    {
        switch (Copy_enumSource)
        {
        case RCC_enumHSI_CLOCK:
            if (Copy_enumStatus == RCC_enumCLK_ON)
            {
                RCC->RCC_CR |= RCC_HSION_CR_BITMUSK_;      // Set HSION bit
                Local_enuRetError = RCC_enumErrorTimedOut; // Timeout error
                while ((Local_u16TimeOut--) && (!(RCC->RCC_CR & RCC_HSIRDY_CR_BITMUSK_)))
                    ; // Wait for HSIRDY
                if ((RCC->RCC_CR & RCC_HSIRDY_CR_BITMUSK_))
                {
                    Local_enuRetError = RCC_enumOk;
                }
            }
            else
            {
                RCC->RCC_CR &= ~(RCC_HSIRDY_CR_BITMUSK_); // Clear HSION bit
                while (RCC->RCC_CR & (RCC_HSIRDY_CR_BITMUSK_))
                    ; // Wait for HSIRDY to clear
            }
            break;

        case RCC_enumHSE_CLOCK:
            if (Copy_enumStatus == RCC_enumCLK_ON)
            {
                RCC->RCC_CR |= (RCC_HSEON_CR_BITMUSK_);    // Set HSEON bit
                Local_enuRetError = RCC_enumErrorTimedOut; // Timeout error
                while ((Local_u16TimeOut--) && (!(RCC->RCC_CR & (RCC_HSIRDY_CR_BITMUSK_))))
                    ; // Wait for HSERDY
                if ((RCC->RCC_CR & (RCC_HSERDY_CR_BITMUSK_)))
                {
                    Local_enuRetError = RCC_enumOk; // Timeout error
                }
            }
            else
            {
                RCC->RCC_CR &= ~(RCC_HSEON_CR_BITMUSK_); // Clear HSEON bit
                while (RCC->RCC_CR & (RCC_HSERDY_CR_BITMUSK_))
                    ; // Wait for HSERDY to clear
            }
            break;

        case RCC_enumPLL_CLOCK:
            if (Copy_enumStatus == RCC_enumCLK_ON)
            {
                RCC->RCC_CR |= (RCC_PLLON_CR_BITMUSK_);    // Set PLLON bit
                Local_enuRetError = RCC_enumErrorTimedOut; // Timeout error
                while ((Local_u16TimeOut--) && (!(RCC->RCC_CR & (RCC_PLLRDY_CR_BITMUSK_))))
                    ; // Wait for PLLRDY
                if ((RCC->RCC_CR & (RCC_PLLRDY_CR_BITMUSK_)))
                {
                    Local_enuRetError = RCC_enumOk; // Timeout error
                }
            }
            else
            {
                RCC->RCC_CR &= ~(RCC_PLLON_CR_BITMUSK_); // Clear PLLON bit
                while (RCC->RCC_CR & (RCC_PLLRDY_CR_BITMUSK_))
                    ; // Wait for PLLRDY to clear
            }
            break;
        }
    }

    return Local_enuRetError; // Return the correct error status
}

RCC_enumErrorStatus_t RCC_enuPLLConfig(RCC_strPLLConfig_t Copy_strPLLConfig_t)
{

    RCC_enumErrorStatus_t Local_enumReturnError = RCC_enumOk;
    if ((RCC->RCC_CR) & (RCC_PLLON_CFGR_BITMUSK_))
    {
        Local_enumReturnError = RCC_enumErrorPLLON;
    }
    else if ((Copy_strPLLConfig_t.RCC_enumClockSource) > RCC_enumHSE_CLOCK)
    {
        Local_enumReturnError = RCC_enumErrorClock;
    }
    else if ((Copy_strPLLConfig_t.RCC_u16MultFactor_N) > RCC_PLL_N_MAX)
    {

        Local_enumReturnError = RCC_enumErrorPLL_NMulFactor;
    }
    else if ((Copy_strPLLConfig_t.RCC_u32DivisionFactor_M) > RCC_PLL_M_MAX)
    {
        Local_enumReturnError = RCC_enumErrorPLL_MDivFactor;
    }
    else if ((Copy_strPLLConfig_t.RCC_enumPLL_P) > RCC_enum_P_DivBy8)
    {
        Local_enumReturnError = RCC_enumErrorPLL_PDivFactor;
    }
    else if (((Copy_strPLLConfig_t.RCC_enumPLL_Q) < RCC_enum_Q_DivBy2) || ((Copy_strPLLConfig_t.RCC_enumPLL_Q) > RCC_enum_Q_DivBy15))
    {
        Local_enumReturnError = RCC_enumErrorPLL_QDivFactor;
    }
    else
    {
        RCC->RCC_PLLCFGR = (Copy_strPLLConfig_t.RCC_u32DivisionFactor_M) | (Copy_strPLLConfig_t.RCC_u16MultFactor_N << RCC_PLLCFGR_PLLN_0) | (Copy_strPLLConfig_t.RCC_enumPLL_P << RCC_PLLCFGR_PLLP_0) | (Copy_strPLLConfig_t.RCC_enumClockSource << RCC_PLLCFGR_PLLSRC) | (Copy_strPLLConfig_t.RCC_enumPLL_Q << RCC_PLLCFGR_PLLQ_0);
    }
    return Local_enumReturnError;
}

RCC_enumErrorStatus_t RCC_enuEnableClock(u64 Copy_u64peripheral)
{
    u32 Local_u32reg = (Copy_u64peripheral >> 32);
    u32 Local_u32bit = (Copy_u64peripheral & 0xFFFFFFFF);
    u32 Local_u32TempReg;
    RCC_enumErrorStatus_t Local_enumReturnError = RCC_enumOk;

    switch (Local_u32reg)
    {
    case 0x00000001: // AHB1ENR
        Local_u32TempReg  = RCC->RCC_AHB1ENR;
        Local_u32TempReg |= Local_u32bit;
        RCC -> RCC_AHB1ENR= Local_u32TempReg;
        
        break;
    case 0x00000002: // AHB2ENR
        Local_u32TempReg  = RCC->RCC_AHB2ENR;
        Local_u32TempReg |= Local_u32bit;
        RCC -> RCC_AHB1ENR= Local_u32TempReg;
        break;
    case 0x00000003: // APB1ENR
        Local_u32TempReg  = RCC->RCC_APB1ENR;
        Local_u32TempReg |= Local_u32bit;
        RCC -> RCC_AHB1ENR= Local_u32TempReg;
        break;
    case 0x00000004: // APB2ENR
        Local_u32TempReg  = RCC->RCC_APB2ENR;
        Local_u32TempReg |= Local_u32bit;
        RCC -> RCC_AHB1ENR= Local_u32TempReg;
        break;
    default:
        Local_enumReturnError = RCC_enumErrorBus; // Invalid register
        break;
    }

    return Local_enumReturnError; // Return the correct error status
}

RCC_enumErrorStatus_t RCC_enuDisableClock(u64 Copy_u64peripheral)
{
    u32 Local_u32reg = (Copy_u64peripheral >> 32);
    u32 Local_u32bit = (Copy_u64peripheral & 0xFFFFFFFF);
    u32 Local_u32TempReg;
    RCC_enumErrorStatus_t Local_enumReturnError = RCC_enumOk;

    switch (Local_u32reg)
    {
    case 0x00000001: // AHB1ENR
        Local_u32TempReg  = RCC->RCC_AHB1ENR;
        Local_u32TempReg  &= ~Local_u32bit;
        RCC -> RCC_AHB1ENR= Local_u32TempReg;
        
        break;
    case 0x00000002: // AHB2ENR
        Local_u32TempReg  = RCC->RCC_AHB2ENR;
        Local_u32TempReg &= ~Local_u32bit;
        RCC -> RCC_AHB1ENR= Local_u32TempReg;
        break;
    case 0x00000003: // APB1ENR
        Local_u32TempReg  = RCC->RCC_APB1ENR;
        Local_u32TempReg &= ~Local_u32bit;
        RCC -> RCC_AHB1ENR= Local_u32TempReg;
        break;
    case 0x00000004: // APB2ENR
        Local_u32TempReg  = RCC->RCC_APB2ENR;
        Local_u32TempReg &= ~Local_u32bit;
        RCC -> RCC_AHB1ENR= Local_u32TempReg;
        break;
    default:
        Local_enumReturnError = RCC_enumErrorBus; // Invalid register
        break;
    }

    return Local_enumReturnError; // Return the correct error status
}

RCC_enumErrorStatus_t RCC_enuGetClkReadyStatus(RCC_enumSetClk_Source_t Copy_enumSource, u8 *Add_pu8ReadyStatus)
{

    RCC_enumErrorStatus_t Local_enumReturnError = RCC_enumOk;

    if (Copy_enumSource > RCC_enumPLL_CLOCK)
    {
        Local_enumReturnError = RCC_enumErrorClock; // Invalid input
    }
    else if (Add_pu8ReadyStatus == NULL_PTR)
    {
        Local_enumReturnError = RCC_enumErrorNullPointer;
    }
    else
    {
        switch (Copy_enumSource)
        {
        case RCC_enumHSI_CLOCK:
            if (RCC->RCC_CR & RCC_HSIRDY_CR_BITMUSK_)
            {
                *Add_pu8ReadyStatus = RCC_CLK_RDY;
            }
            else
            {
                *Add_pu8ReadyStatus = RCC_CLK_NOTRDY;
            }
            break;
        case RCC_enumHSE_CLOCK:
            if (RCC->RCC_CR & RCC_HSERDY_CR_BITMUSK_)
            {
                *Add_pu8ReadyStatus = RCC_CLK_RDY;
            }
            else
            {
                *Add_pu8ReadyStatus = RCC_CLK_NOTRDY;
            }
            break;
        case RCC_enumPLL_CLOCK:
            if (RCC->RCC_CR & RCC_PLLRDY_CR_BITMUSK_)
            {
                *Add_pu8ReadyStatus = RCC_CLK_RDY;
            }
            else
            {
                *Add_pu8ReadyStatus = RCC_CLK_NOTRDY;
            }
            break;
        }
    }
    return Local_enumReturnError;
}

RCC_enumErrorStatus_t RCC_enuConfigurePreScalarLowSpeedAPB(u32 Copy_u32APB1_Prescalar)
{
    RCC_enumErrorStatus_t Local_enumReturnError;
    u32 Local_u32TempReg = 0x00;

    if (Copy_u32APB1_Prescalar != RCC_APB1_PRE_DIV2 && Copy_u32APB1_Prescalar != RCC_APB1_PRE_DIV4 &&
        Copy_u32APB1_Prescalar != RCC_APB1_PRE_DIV8 && Copy_u32APB1_Prescalar != RCC_APB1_PRE_DIV16)
    {
        Local_enumReturnError = RCC_enumErrorBusPrescaler;
    }
    else
    {
        Local_u32TempReg = RCC->RCC_CFGR;
        Local_u32TempReg &= ~RCC_APB1_CFGR_BITMASK_;
        Local_u32TempReg |= Copy_u32APB1_Prescalar;
        RCC->RCC_CFGR = Local_u32TempReg;
        Local_enumReturnError = RCC_enumOk;
    }

    return Local_enumReturnError;
}

RCC_enumErrorStatus_t RCC_enuConfigurePreScalarHighSpeedAPB(u32 Copy_u32APB2_Prescalar)
{
    RCC_enumErrorStatus_t Local_enumReturnError;
    u32 Local_u32TempReg = 0x00;

    if (Copy_u32APB2_Prescalar != RCC_APB2_PRE_DIV2 && Copy_u32APB2_Prescalar != RCC_APB2_PRE_DIV4 &&
        Copy_u32APB2_Prescalar != RCC_APB2_PRE_DIV8 && Copy_u32APB2_Prescalar != RCC_APB2_PRE_DIV16)
    {
        Local_enumReturnError = RCC_enumErrorBusPrescaler;
    }
    else
    {
        Local_u32TempReg = RCC->RCC_CFGR;
        Local_u32TempReg &= ~RCC_APB2_CFGR_BITMASK_;
        Local_u32TempReg |= Copy_u32APB2_Prescalar;
        RCC->RCC_CFGR = Local_u32TempReg;
        Local_enumReturnError = RCC_enumOk;
    }

    return Local_enumReturnError;
}

RCC_enumErrorStatus_t RCC_enuConfigurePreScalarAHB(u32 Copy_u32AHB_Prescalar)
{
    RCC_enumErrorStatus_t Local_enumReturnError;
    u32 Local_u32TempReg = 0x00;
    if (Copy_u32AHB_Prescalar != RCC_AHB_PRE_DIV2 && Copy_u32AHB_Prescalar != RCC_AHB_PRE_DIV4 &&
        Copy_u32AHB_Prescalar != RCC_AHB_PRE_DIV8 && Copy_u32AHB_Prescalar != RCC_AHB_PRE_DIV16 &&
        Copy_u32AHB_Prescalar != RCC_AHB_PRE_DIV64 && Copy_u32AHB_Prescalar != RCC_AHB_PRE_DIV128 &&
        Copy_u32AHB_Prescalar != RCC_AHB_PRE_DIV256 && Copy_u32AHB_Prescalar != RCC_AHB_PRE_DIV512)
    {
        Local_enumReturnError = RCC_enumErrorBusPrescaler;
    }
    else
    {
        Local_u32TempReg = RCC->RCC_CFGR;
        Local_u32TempReg &= ~RCC_AHB_CFGR_BITMASK_;
        Local_u32TempReg |= Copy_u32AHB_Prescalar;
        RCC->RCC_CFGR = Local_u32TempReg;
        Local_enumReturnError = RCC_enumOk;
    }

    return Local_enumReturnError;
}

RCC_enumErrorStatus_t RCC_enuHES_BYPASS_Status(u32 Copy_u32Bypass_status)
{
    RCC_enumErrorStatus_t Local_enumReturnError;
    u32 Local_u32TempReg = 0x00;

    if (Copy_u32Bypass_status != RCC_enumCLK_BYPASS_ON && Copy_u32Bypass_status != RCC_enumCLK_BYPASS_OFF)
    {
        Local_enumReturnError = RCC_enumErrorHSEBYPASS;
    }
    else if (!(RCC->RCC_CR & RCC_HSERDY_CR_BITMUSK_))
    {
        Local_enumReturnError = RCC_enumErrorClkNotRdy;
    }
    else
    {
        switch (Copy_u32Bypass_status)
        {
        case RCC_enumCLK_BYPASS_ON:
            Local_u32TempReg  = RCC->RCC_CR;
            Local_u32TempReg |= (RCC_HSEBYP_CR_BITMASK_);
            RCC->RCC_CR = Local_u32TempReg;
            Local_enumReturnError = RCC_enumOk;
            break;
        case RCC_enumCLK_BYPASS_OFF:
            Local_u32TempReg  = RCC->RCC_CR;
            Local_u32TempReg &= ~(RCC_HSEBYP_CR_BITMASK_);
            RCC->RCC_CR = Local_u32TempReg;
            Local_enumReturnError = RCC_enumOk;
            break;
        default:
            break;
        }
    }
    return Local_enumReturnError;
}




































































































































































































































































































































































































































































































































































































































