#include "../../../include/HAL/HSWITCH_SCHED/HSWITCH_SCHED.h"
#include "../../../include/HAL/HSWITCH_SCHED/HSWITCH_SCHED_Config.h"
#include "../../../include/MCAL/GPIO/GPIO.h"

/* Array to store switch statuses */
static u8 HSWITCH_Status[NUM_OF_SWITCHES] = {0};

/**
 * @brief Initialize the switches.
 */
void HSWITCH_vInit(void)
{
    u8 Local_u8Iter = 0;

    for (Local_u8Iter = 0; Local_u8Iter < NUM_OF_SWITCHES; Local_u8Iter++)
    {
        GPIO_strPinConfig_t Local_strcurrSwitch = {
            .GPIO_pinPort = HSWITCH_strPinConfigArray[Local_u8Iter].HSWITCH_port_Number,
            .GPIO_pinNum = HSWITCH_strPinConfigArray[Local_u8Iter].HSWITCH_pin_Number,
            .GPIO_pinMode = GPIO_MODE_INPUT,
            .GPIO_pinOutType = GPIO_OUTPUT_PUSH_PULL,
            .GPIO_pinSpeed = GPIO_SPEED_HIGH,
            .GPIO_pinPull = HSWITCH_strPinConfigArray[Local_u8Iter].HSWITCH_Pull_State,
            .GPIO_pinAF = GPIO_AF_NONE
        };
        GPIO_enumConfigPin(&Local_strcurrSwitch);
    }
}

/**
 * @brief Get the status of a switch.
 * @param Copy_u8SwitchName - ID of the switch.
 * @param Add_pSwitchStatus - Pointer to store the switch status.
 * @return HSWITCH_enumErrorState_t - Status of the operation.
 */
HSWITCH_enumErrorState_t HSWITCH_enuGetStatus(u32 Copy_u8SwitchName, u8 *Add_pSwitchStatus)
{
    HSWITCH_enumErrorState_t Ret_enumErrorStatus = HSWITCH_enumErrSt_OK;

    if (Copy_u8SwitchName >= NUM_OF_SWITCHES)
    {
        Ret_enumErrorStatus = HSWITCH_enumErrSt_WrongSwitch;
    }
    else if (Add_pSwitchStatus == NULL_PTR)
    {
        Ret_enumErrorStatus = HSWITCH_enumErrSt_NullPtr;
    }
    else
    {
        *Add_pSwitchStatus = HSWITCH_Status[Copy_u8SwitchName];
    }

    return Ret_enumErrorStatus;
}

/**
 * @brief Runnable function for switch debouncing.
 */
void HSWITCH_vRunnable(void)
{
    u8 PinNum = 0;
    u8 PortNum = 0;
    u16 Local_u16Iter = 0;
    u32 Local_u32CurrrentSwitchStatus = 0;
    static u8 Local_u8PrevSwitchStatus[NUM_OF_SWITCHES] = {0};
    static u8 Local_u8Counter[NUM_OF_SWITCHES] = {0};

    for (Local_u16Iter = 0; Local_u16Iter < NUM_OF_SWITCHES; Local_u16Iter++)
    {
        PortNum = HSWITCH_strPinConfigArray[Local_u16Iter].HSWITCH_port_Number;
        PinNum = HSWITCH_strPinConfigArray[Local_u16Iter].HSWITCH_pin_Number;

        GPIO_enumGetPinValue(PortNum, PinNum, &Local_u32CurrrentSwitchStatus);

        if (Local_u32CurrrentSwitchStatus == Local_u8PrevSwitchStatus[Local_u16Iter])
        {
            Local_u8Counter[Local_u16Iter]++;
        }
        else
        {
            Local_u8Counter[Local_u16Iter] = 0;
        }

        if (Local_u8Counter[Local_u16Iter] % HSWITCH_NUM_OF_CHECKS == 0)
        {
            Local_u8Counter[Local_u16Iter] = 0;
            HSWITCH_Status[Local_u16Iter] = Local_u32CurrrentSwitchStatus;
        }

        Local_u8PrevSwitchStatus[Local_u16Iter] = Local_u32CurrrentSwitchStatus;
    }
}