#include <../include/RCC/RCC.h>

int main(void)
{
    // RCC_SetClk_Status(RCC_enuHSE_CLOCK , RCC_enuCLK_ON);
    // RCC_enuControlSysClock(RCC_enuHSE_CLOCK);
    char value = 0 ;
    RCC_SetClk_Status(RCC_enuPLL_CLOCK , RCC_enuCLK_ON);
    RCC_enuControlSysClock(RCC_enuPLL_CLOCK);
    value = 5 ;
    RCC_enuGetClockRdyStatus(RCC_enuPLL_CLOCK , &value);
    // RCC_SetClk_Status(RCC_enuHSE_CLOCK , RCC_enuCLK_ON);

    while (1)
    {
        /* code */
    }
    return 0;


}