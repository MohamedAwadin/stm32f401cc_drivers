

#include "../../include/COMMON/Utils.h"
#include "../../include/COMMON/StdTypes.h"

#include "../../include/RCC/RCC_private.h"
#include "../../include/RCC/RCC.h"

RCC_enumErrorStatus_t RCC_SetClk_Status(RCC_enumSetClk_Source_t source, RCC_enumSetClk_Status_t status)
{
    RCC_enumErrorStatus_t Local_enuRetError = RCC_enuOk;
    u16 Local_u16TimeOut = RCC_u16TIME_OUT;

    if ((source > RCC_enuPLL_CLOCK) || (status > RCC_enuCLK_ON))
    {
        Local_enuRetError = RCC_enuErrorClock; // Invalid input
    }
    else
    {
        switch (source)
        {
        case RCC_enuHSI_CLOCK:
            if (status == RCC_enuCLK_ON)
            {
                RCC->RCC_CR |= (0x1 << RCC_CR_HSION); // Set HSION bit
                while ((Local_u16TimeOut--) && (!(RCC->RCC_CR & (0x1 << RCC_CR_HSIRDY))))
                    ; // Wait for HSIRDY
                if (!(RCC->RCC_CR & (0x1 << RCC_CR_HSIRDY)))
                {
                    Local_enuRetError = RCC_enuErrorTimedOut; // Timeout error
                }
            }
            else
            {
                RCC->RCC_CR &= ~(0x1 << RCC_CR_HSION); // Clear HSION bit
                while (RCC->RCC_CR & (0x1 << RCC_CR_HSIRDY))
                    ; // Wait for HSIRDY to clear
            }
            break;

        case RCC_enuHSE_CLOCK:
            if (status == RCC_enuCLK_ON)
            {
                RCC->RCC_CR |= (0x1 << RCC_CR_HSEON); // Set HSEON bit
                while ((Local_u16TimeOut--) && (!(RCC->RCC_CR & (0x1 << RCC_CR_HSERDY)))); // Wait for HSERDY
                if (!(RCC->RCC_CR & (0x1 << RCC_CR_HSERDY)))
                {
                    Local_enuRetError = RCC_enuErrorTimedOut; // Timeout error
                }
            }
            else
            {
                RCC->RCC_CR &= ~(0x1 << RCC_CR_HSEON); // Clear HSEON bit
                while (RCC->RCC_CR & (0x1 << RCC_CR_HSERDY))
                    ; // Wait for HSERDY to clear
            }
            break;

        case RCC_enuPLL_CLOCK:
            if (status == RCC_enuCLK_ON)
            {
                RCC->RCC_CR |= (0x1 << RCC_CR_PLLON); // Set PLLON bit
                while ((Local_u16TimeOut--) && (!(RCC->RCC_CR & (0x1 << RCC_CR_PLLRDY))))
                    ; // Wait for PLLRDY
                if (!(RCC->RCC_CR & (0x1 << RCC_CR_PLLRDY)))
                {
                    Local_enuRetError = RCC_enuErrorTimedOut; // Timeout error
                }
            }
            else
            {
                RCC->RCC_CR &= ~(0x1 << RCC_CR_PLLON); // Clear PLLON bit
                while (RCC->RCC_CR & (0x1 << RCC_CR_PLLRDY))
                    ; // Wait for PLLRDY to clear
            }
            break;
        }
    }

    return Local_enuRetError; // Return the correct error status
}

/*
RCC_enumErrorStatus_t RCC_SetClk_Status(RCC_enumSetClk_Source_t source, RCC_enumSetClk_Status_t status) {
    RCC_enumErrorStatus_t Local_enuRetError = RCC_enuOk;
    if (source > RCC_enuPLL_CLOCK || status > RCC_enuCLK_ON) {
        Local_enuRetError = RCC_enuErrorClock; // Invalid input
    } else {
        switch (source) {
            case RCC_enuHSI_CLOCK:
                if (status == RCC_enuCLK_ON) {
                    SET_BIT(RCC->RCC_CR, RCC_CR_HSION);
                    while (READ_BIT(RCC->RCC_CR, RCC_CR_HSIRDY) == 0);
                } else {
                    CLEAR_BIT(RCC->RCC_CR, RCC_CR_HSION);
                    while (READ_BIT(RCC->RCC_CR, RCC_CR_HSIRDY) == 1);
                }
                break;

            case RCC_enuHSE_CLOCK:
                if (status == RCC_enuCLK_ON) {
                    SET_BIT(RCC->RCC_CR, RCC_CR_HSEON);
                    while (READ_BIT(RCC->RCC_CR, RCC_CR_HSERDY) == 0);
                } else {
                    CLEAR_BIT(RCC->RCC_CR, RCC_CR_HSEON);
                    while (READ_BIT(RCC->RCC_CR, RCC_CR_HSERDY) == 1);
                }
                break;

            case RCC_enuPLL_CLOCK:
                if (status == RCC_enuCLK_ON) {
                    SET_BIT(RCC->RCC_CR, RCC_CR_PLLON);
                    while (READ_BIT(RCC->RCC_CR, RCC_CR_PLLRDY) == 0);
                } else {
                    CLEAR_BIT(RCC->RCC_CR, RCC_CR_PLLON);
                    while (READ_BIT(RCC->RCC_CR, RCC_CR_PLLRDY) == 1);
                }
                break;

            default:
                Local_enuRetError = RCC_enuErrorClock; // Invalid source
        }
    }

    return Local_enuRetError; // Return the correct error status
}
*/

RCC_enumErrorStatus_t RCC_enuControlSysClock(RCC_enumSetClk_Source_t source)
{
    RCC_enumErrorStatus_t Local_enuRetError = RCC_enuOk;
    u16 Local_u16TimeOut = RCC_u16TIME_OUT;
    u8 Local_u8TempReg = (RCC->RCC_CFGR);

    if ((source) > (RCC_enuPLL_CLOCK))
    {
        Local_enuRetError = RCC_enuErrorClock;
    }

    switch (source)
    {
    case RCC_enuHSI_CLOCK:
        if ((RCC->RCC_CR & (0x1 << RCC_CR_HSIRDY)))
        {
            Local_u8TempReg = (RCC->RCC_CFGR);
            Local_u8TempReg &= ~(0x3 << RCC_CFGR_SW0);
            RCC->RCC_CFGR = Local_u8TempReg;
        }
        else
        {
            Local_enuRetError = RCC_enuErrorClkNotRdy;
        }

        break;

    case RCC_enuHSE_CLOCK:
        if ((RCC->RCC_CR & (0x1 << RCC_CR_HSERDY)))
        {
            Local_u8TempReg = (RCC->RCC_CFGR);
            Local_u8TempReg |= (0x1 << RCC_CFGR_SW0);
            RCC->RCC_CFGR = Local_u8TempReg;
        }
        else
        {
            Local_enuRetError = RCC_enuErrorClkNotRdy;
        }
        break;

    case RCC_enuPLL_CLOCK:
        
        if ((RCC->RCC_CR & (0x1 << RCC_CR_PLLRDY)))
        {
            
            Local_u8TempReg = (RCC->RCC_CFGR);
            Local_u8TempReg |= (0x1 << RCC_CFGR_SW1); // Set SW0 bit
            RCC->RCC_CFGR   = Local_u8TempReg ;
            // SET_BIT(RCC->RCC_CFGR, RCC_CFGR_SW1);
            // CLEAR_BIT(RCC->RCC_CFGR, RCC_CFGR_SW0);
        }
        else
        {
            Local_enuRetError = RCC_enuErrorClkNotRdy;
        }
        break;
    }

    //    Wait for the clock switch to complete
    while ((Local_u16TimeOut--) && ((RCC->RCC_CFGR & (0x3 << RCC_CFGR_SWS0)) != (source << RCC_CFGR_SWS0)));

    // Check if the switch was successful
    if ((RCC->RCC_CFGR & (0x3 <<RCC_CFGR_SWS0)) == (source << RCC_CFGR_SWS0))
    {
        Local_enuRetError = RCC_enuOk; // Success
    }
    else
    {
        Local_enuRetError = RCC_enuErrorTimedOut; // Timeout error
    }

    return Local_enuRetError; // Return the correct error status
    }

/*
RCC_enumErrorStatus_t RCC_enuControlSysClock(RCC_enumSetClk_Source_t source)
{
    RCC_enumErrorStatus_t Local_enuRetError = RCC_enuOk;
    if (source > RCC_enuPLL_CLOCK)
    {
        Local_enuRetError = RCC_enuErrorClock; // Invalid source
    }
    else
    {
        switch (source)
        {
        case RCC_enuHSI_CLOCK:
            CLEAR_BIT(RCC->RCC_CFGR, RCC_CFGR_SW1);
            CLEAR_BIT(RCC->RCC_CFGR, RCC_CFGR_SW0);
            break;

        case RCC_enuHSE_CLOCK:
            CLEAR_BIT(RCC->RCC_CFGR, RCC_CFGR_SW1);
            SET_BIT(RCC->RCC_CFGR, RCC_CFGR_SW0);
            break;

        case RCC_enuPLL_CLOCK:
            SET_BIT(RCC->RCC_CFGR, RCC_CFGR_SW1);
            CLEAR_BIT(RCC->RCC_CFGR, RCC_CFGR_SW0);
            break;

        default:
            Local_enuRetError = RCC_enuErrorClock; // Invalid source
        }
    }

    return Local_enuRetError; // Success
}
*/

RCC_enumErrorStatus_t RCC_enuGetClockRdyStatus(RCC_enumSetClk_Source_t source, pu8 Add_pu8RtrnRdyStatus)
{
    RCC_enumErrorStatus_t Local_enuRetError = RCC_enuOk;
    if (Add_pu8RtrnRdyStatus == NULL)
    {
        Local_enuRetError = RCC_enuErrorNullPointer; // Null pointer check
    }

    switch (source)
    {
    case RCC_enuHSI_CLOCK:
        *Add_pu8RtrnRdyStatus = READ_BIT(RCC->RCC_CR, RCC_CR_HSIRDY);
        break;

    case RCC_enuHSE_CLOCK:
        *Add_pu8RtrnRdyStatus = READ_BIT(RCC->RCC_CR, RCC_CR_HSERDY);
        break;

    case RCC_enuPLL_CLOCK:
        *Add_pu8RtrnRdyStatus = READ_BIT(RCC->RCC_CR, RCC_CR_PLLRDY);
        break;
    }

    return Local_enuRetError; // Success
}
RCC_enumErrorStatus_t RCC_PLLConfig(RCC_strPLLConfig_t Copy_strPLLConfig_t)
{

    RCC_enumErrorStatus_t Local_enumReturnError = RCC_enuOk;
    if ((RCC->RCC_CR) & (RCC_PLLON_CFGR_BITMUSK_))
    {
        Local_enumReturnError = RCC_enuErrorPLLON;
    }
    else if ((Copy_strPLLConfig_t.RCC_enumClockSource) > RCC_enuHSE_CLOCK)
    {
        Local_enumReturnError = RCC_enuErrorClock;
    }
    else if ((Copy_strPLLConfig_t.RCC_u16MultFactor_N) > RCC_PLL_N_MAX)
    {
        Local_enumReturnError = RCC_enuErrorNFactor;
    }
    else if ((Copy_strPLLConfig_t.RCC_u32DivisionFactor_M) > RCC_PLL_M_MAX)
    {
        Local_enumReturnError = RCC_enuErrorMDivion;
    }
    else if ((Copy_strPLLConfig_t.RCC_enumPLL_P) > RCC_enu_P_DivBy8)
    {
        Local_enumReturnError = RCC_enuErrorPLLP;
    }
    else if (((Copy_strPLLConfig_t.RCC_enumPLL_P) < RCC_enu_Q_DivBy2) || ((Copy_strPLLConfig_t.RCC_enumPLL_P) < RCC_enu_Q_DivBy15))
    {
        Local_enumReturnError = RCC_enuErrorPLLQ;
    }
    else
    {
        RCC->RCC_PLLCFGR = (Copy_strPLLConfig_t.RCC_u32DivisionFactor_M) | (u16)(Copy_strPLLConfig_t.RCC_u16MultFactor_N << RCC_PLLCFGR_PLLN_0) | (RCC_enumPLL_P_t)(Copy_strPLLConfig_t.RCC_enumPLL_P << RCC_PLLCFGR_PLLP_0) | (RCC_enumSetClk_Source_t)(Copy_strPLLConfig_t.RCC_enumClockSource << RCC_PLLCFGR_PLLSRC) | (u16)(Copy_strPLLConfig_t.RCC_enumPLL_Q << RCC_PLLCFGR_PLLQ_0);
    }
    return Local_enumReturnError;
}

RCC_enumErrorStatus_t RCC_EnableClock(u64 peripheral)
{
    u32 reg = (peripheral >> 32);
    u32 bit = (peripheral & 0xFFFFFFFF);
    RCC_enumErrorStatus_t Local_enumReturnError = RCC_enuOk;

    switch (reg)
    {
    case 0x00000001: // AHB1ENR
        SET_BIT(RCC->RCC_AHB1ENR, bit);
        break;
    case 0x00000002: // AHB2ENR
        SET_BIT(RCC->RCC_AHB2ENR, bit);
        break;
    case 0x00000003: // APB1ENR
        SET_BIT(RCC->RCC_APB1ENR, bit);
        break;
    case 0x00000004: // APB2ENR
        SET_BIT(RCC->RCC_APB2ENR, bit);
        break;
    default:
        Local_enumReturnError = RCC_enuErrorBus; // Invalid register
        break;
    
    }

    return Local_enumReturnError; // Return the correct error status
}

RCC_enumErrorStatus_t RCC_DisableClock(u64 peripheral)
{
    u32 reg = (peripheral >> 32);
    u32 bit = (peripheral & 0xFFFFFFFF);
    RCC_enumErrorStatus_t Local_enumReturnError = RCC_enuOk;

    switch (reg)
    {
    case 0x00000001: // AHB1ENR
        CLEAR_BIT(RCC->RCC_AHB1ENR, bit);
        break;
    case 0x00000002: // AHB2ENR
        CLEAR_BIT(RCC->RCC_AHB2ENR, bit);
        break;
    case 0x00000003: // APB1ENR
        CLEAR_BIT(RCC->RCC_APB1ENR, bit);
        break;
    case 0x00000004: // APB2ENR
        CLEAR_BIT(RCC->RCC_APB2ENR, bit);
        break;
    default:
        Local_enumReturnError = RCC_enuErrorBus; // Invalid register
        break;

    }

    return Local_enumReturnError; // Return the correct error status
}

// RCC_enumErrorStatus_t RCC_AHB1EnableClock(RCC_enumAHB1ENR_Bits_t Copy_enumAHB1_peripheral)
// {
// 	SET_BIT(RCC->RCC_APB1ENR, Copy_enumAHB1_peripheral);
// }
// RCC_enumErrorStatus_t RCC_AHB1DisableClock(RCC_enumAHB1ENR_Bits_t Copy_enumAHB1_peripheral)
// {
// 	CLEAR_BIT(RCC->RCC_AHB1ENR, Copy_enumAHB1_peripheral);
// }

// RCC_enumErrorStatus_t RCC_AHB2EnableClock(RCC_enumAHB1ENR_Bits_t Copy_enumAHB2_peripheral)
// {
// 	SET_BIT(RCC->RCC_APB2ENR, Copy_enumAHB2_peripheral);
// }
// RCC_enumErrorStatus_t RCC_AHB2DisableClock(RCC_enumAHB1ENR_Bits_t Copy_enumAHB2_peripheral)
// {
// 	CLEAR_BIT(RCC->RCC_AHB2ENR, Copy_enumAHB2_peripheral);
// }

// RCC_enumErrorStatus_t RCC_APB1EnableClock(RCC_enumAPB1ENR_Bits_t Copy_enumAPB1_peripheral)
// {
// 	SET_BIT(RCC->RCC_APB1ENR, Copy_enumAPB1_peripheral);
// }
// RCC_enumErrorStatus_t RCC_APB1DisableClock(RCC_enumAPB1ENR_Bits_t Copy_enumAPB1_peripheral)
// {
// 	CLEAR_BIT(RCC->RCC_APB1ENR, Copy_enumAPB1_peripheral);
// }
// RCC_enumErrorStatus_t RCC_APB2EnableClock(RCC_enumAPB2ENR_Bits_t Copy_enumAPB2_peripheral)
// {
// 	SET_BIT(RCC->RCC_APB2ENR, Copy_enumAPB2_peripheral);
// }
// RCC_enumErrorStatus_t RCC_APB2DisableClock(RCC_enumAPB2ENR_Bits_t Copy_enumAPB2_peripheral)
// {
// 	CLEAR_BIT(RCC->RCC_APB2ENR, Copy_enumAPB2_peripheral);
// }
