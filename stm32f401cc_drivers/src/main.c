#include <../include/RCC/RCC.h>

int main(void)
{
    /*TEST-1 == ACCEPTED*/
    // RCC_enuSetClock_Status(RCC_enumHSI_CLOCK , RCC_enumCLK_ON);
    // RCC_enuControlSysClock(RCC_enumHSI_CLOCK);
    /*TEST-2 == ACCEPTED*/
    // RCC_enuSetClock_Status(RCC_enumHSE_CLOCK , RCC_enumCLK_ON);
    // RCC_enuControlSysClock(RCC_enumHSE_CLOCK);
    // RCC_enuSetClock_Status(RCC_enumHSE_CLOCK , RCC_enumCLK_OFF);
    /*TEST-3 == ACCEPTED*/
    // RCC_enuSetClock_Status(RCC_enumPLL_CLOCK , RCC_enumCLK_ON);
    // RCC_enuControlSysClock(RCC_enumPLL_CLOCK);
    /*TEST-4 == NOT_ACCEPTED*/
    // RCC_enuSetClock_Status(RCC_enumPLL_CLOCK , RCC_enumCLK_ON);
    // RCC_enuControlSysClock(RCC_enumPLL_CLOCK);
    // RCC_enuSetClock_Status(RCC_enumPLL_CLOCK , RCC_enumCLK_OFF);
    /*TEST-5 == ACCEPTED*/
    // RCC_enuSetClock_Status(RCC_enumPLL_CLOCK, RCC_enumCLK_ON);
    // RCC_strPLLConfig_t pllConfig = {
    //     .RCC_u32DivisionFactor_M = 8,
    //     .RCC_enumPLL_P = RCC_enum_P_DivBy6,
    //     .RCC_enumPLL_Q = RCC_enum_Q_DivBy13,
    //     .RCC_u16MultFactor_N = 336,
    //     .RCC_enumClockSource = RCC_enumHSE_CLOCK};

    // RCC_enuSetClock_Status(RCC_enumHSE_CLOCK, RCC_enumCLK_ON);
    
    // RCC_enuSetClock_Status(RCC_enumPLL_CLOCK, RCC_enumCLK_OFF);
    // RCC_enumErrorStatus_t status = RCC_enuPLLConfig(pllConfig);

    /*TEST-6 == ACCEPTED*/
    // RCC_enuSetClock_Status(RCC_enumHSE_CLOCK , RCC_enumCLK_ON);
    // RCC_enuControlSysClock(RCC_enumHSE_CLOCK);
    // RCC_enuHES_BYPASS_Status(RCC_enumCLK_BYPASS_OFF);
    // RCC_enuEnableClock(RCC_AHB1ENR_CRCEN);
    // RCC_enuDisableClock(RCC_AHB1ENR_CRCEN);
    
    /*TEST-7 == ACCEPTED*/
    RCC_enuSetClock_Status(RCC_enumHSE_CLOCK , RCC_enumCLK_ON);
    RCC_enuControlSysClock(RCC_enumHSE_CLOCK);
    RCC_enuHES_BYPASS_Status(RCC_enumCLK_BYPASS_OFF);
    RCC_enuEnableClock(RCC_AHB1ENR_CRCEN);
    RCC_enuConfigurePreScalarAHB(RCC_AHB_PRE_DIV4);
    
    while (1)
    {
        /* code */
    }
    return 0;
}