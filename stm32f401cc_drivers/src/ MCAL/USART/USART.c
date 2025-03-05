

#include "../../../include/COMMON/Utils.h"
#include "../../../include/COMMON/StdTypes.h"
#include "../../../include/MCAL/USART/USART.h"
#include "../../../include/MCAL/USART/USART_Private.h"

#define USART_OVERSAMPLING_16 (u32)(0x00000000)
#define USART_OVERSAMPLING_8 (u32)(0x00008000)

#define USART_TX_ENABLE_ONLY (u32)(0x00000008)
#define USART_RX_ENABLE_ONLY (u32)(0x00000004)
#define USART_TX_RX_ENABLE (u32)(0x0000000C)
#define USART_TX_RX_DISABLE (u32)(0x00000000)

#define USART_WORDLENGTH_8 (u32)(0x00000000)
#define USART_WORDLENGTH_9 (u32)(0x00001000)
#define USART_WORDLENGTH_CLR_MASK (u32)(0xFFFFEFFF)

#define USART_ENABLE (u32)(0x00002000)
#define USART_DISABLE (u32)(0x00000000)

#define USART_PARITY_NONE (u32)(0x00000000)
#define USART_PARITY_ODD (u32)(0x00000600)
#define USART_PARITY_EVEN (u32)(0x00000400)
#define USART_PARITY_CLR_MASK (u32)(0xFFFFF9FF)

#define USART_PEIE_BIT (8U)
#define USART_TXEIE_BIT (7U)
#define USART_TCIE_BIT (6U)
#define USART_RXNEIE_BIT (5U)

#define USART_TX_ENABLE (u32)(0x00000008)
#define USART_RX_ENABLE (u32)(0x00000004)

#define USART_DIV_MANTISSA_MASK (u32)(0x0000000F)
#define USART_DIV_FRACTION_MASK (u32)(0x0000FFF0)

#define USART_STOP_BIT_1 (u32)(0x00000000)
#define USART_STOP_BIT_0_5 (u32)(0x00001000)
#define USART_STOP_BIT_2 (u32)(0x00002000)
#define USART_STOP_BIT_1_5 (u32)(0x00003000)
#define USART_STOP_BIT_CLR_MASK (u32)(0xFFFFCFFF)

#define USART_TXE_FLAG_MASK (u32)(0x00000080)
#define USART_RXNE_FLAG_MASK (u32)(0x00000020)

// #define IS_USART_OVERSAMPLING(USART_OVERSAMPLING)((USART_OVERSAMPLING == USART_OVERSAMPLING_16) || (USART_OVERSAMPLING == USART_OVERSAMPLING_8))

// #define IS_USART_WORDLENGTH(USART_WORDLENGTH)((USART_WORDLENGTH == USART_WORDLENGTH_8) || (USART_WORDLENGTH == USART_WORDLENGTH_9))

#define IS_USART_OVERSAMPLING(VAL) ((VAL == USART_OVERSAMPLING_16) || (VAL == USART_OVERSAMPLING_8))
#define IS_USART_WORDLENGTH(VAL) ((VAL == USART_WORDLENGTH_8) || (VAL == USART_WORDLENGTH_9))
#define IS_USART_TXRX_MODE(VAL) ((VAL == USART_TX_ENABLE_ONLY) || (VAL == USART_RX_ENABLE_ONLY) || \
                                 (VAL == USART_TX_RX_ENABLE) || (VAL == USART_TX_RX_DISABLE))

typedef void (*USART_Callback_t)(void);

static USART_Callback_t USART_TxCallbacks[3] = {NULL_PTR, NULL_PTR, NULL_PTR}; // For USART1, USART2, USART6
static USART_Callback_t USART_RxCallbacks[3] = {NULL_PTR, NULL_PTR, NULL_PTR};

USART_ErrorStatus_t USART_enumInit(USART_strConfig_t *Add_pstrConfig)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    u32 Local_u32TempReg = 0;
    f32 USARTDIV = 0;
    u32 Fraction_Boundary = 0;
    u32 DIV_Fraction = 0;
    u32 DIV_Fraction_MAXVALUE = 0;
    u32 DIV_Mantissa = 0;

    if (Add_pstrConfig == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr;
    }
    else if (Add_pstrConfig->USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else if (!IS_USART_OVERSAMPLING(Add_pstrConfig->USART_u32OverSampling))
    {
        Local_enumErrorRet = USART_enumInvalidOVSampling;
    }
    else if (!IS_USART_WORDLENGTH(Add_pstrConfig->USART_u32WordLength))
    {
        Local_enumErrorRet = USART_enumInvalidWordLength;
    }
    else if (!IS_USART_TXRX_MODE(Add_pstrConfig->USART_u32TxRxMode))
    {
        Local_enumErrorRet = USART_enumNOk;
    }
    else
    {
        /* Calculate baud rate */

        f32 OVER8 = (Add_pstrConfig->USART_u32OverSampling == USART_OVERSAMPLING_16) ? 0 : 1;

        u32 MaxBaudRate = (Add_pstrConfig->USART_u32Freq) / (8 * (2 - OVER8));
        if (Add_pstrConfig->USART_u32BaudRate > MaxBaudRate)
        {
            Local_enumErrorRet = USART_enumNOk;
        }
        else
        {
            

            /*Select Baud Rate*/
            USARTDIV = (f32)Add_pstrConfig->USART_u32Freq / (Add_pstrConfig->USART_u32BaudRate * 8 * (2 - OVER8));

            Fraction_Boundary = (Add_pstrConfig->USART_u32OverSampling == USART_OVERSAMPLING_16) ? 16 : 8;

            DIV_Mantissa = (u32)USARTDIV;

            DIV_Fraction = (u32)(Fraction_Boundary * (f32)((f32)USARTDIV - (u32)USARTDIV)) + 1;
            DIV_Fraction_MAXVALUE = (u32)(Fraction_Boundary - 1);

            if (DIV_Fraction > DIV_Fraction_MAXVALUE)
            {
                DIV_Fraction = 0;
                USARTDIV++;
                DIV_Mantissa = (u32)USARTDIV;
            }
            else
            {
                DIV_Mantissa = (u32)USARTDIV;
            }

            /* Configure CR1: Enable, Oversampling, Word Length, Parity, TX/RX Mode */
            Local_u32TempReg = USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1;
            Local_u32TempReg &= ~(USART_WORDLENGTH_CLR_MASK | USART_PARITY_CLR_MASK);
            Local_u32TempReg |= USART_ENABLE |
                                Add_pstrConfig->USART_u32OverSampling |
                                Add_pstrConfig->USART_u32WordLength |
                                Add_pstrConfig->USART_u32Parity_Select |
                                Add_pstrConfig->USART_u32TxRxMode;
            USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1 = Local_u32TempReg;

            /* Configure BRR: Baud Rate */
            USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_BRR = (DIV_Mantissa << 4) | (DIV_Fraction & 0x0F);

            /* Configure CR2: Stop Bits */
            Local_u32TempReg = USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR2;
            Local_u32TempReg &= USART_STOP_BIT_CLR_MASK;
            Local_u32TempReg |= Add_pstrConfig->USART_u32StopBits;
            USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR2 = Local_u32TempReg;
        }
    }
    return Local_enumErrorRet;
}

USART_ErrorStatus_t USART_enumSendData(u32 USART_u32Bus, u8 USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if (USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else
    {
        while (!(USART_BUSES[USART_u32Bus]->USART_SR & USART_TXE_FLAG_MASK));
        USART_BUSES[USART_u32Bus]->USART_DR = USART_u8Data;
    }
    return Local_enumErrorRet;
}

USART_ErrorStatus_t USART_enumReceiveData(u32 USART_u32Bus, u8 *USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if (USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else if (USART_u8Data == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr;
    }
    else
    {
        while (!(USART_BUSES[USART_u32Bus]->USART_SR & USART_RXNE_FLAG_MASK));
        *USART_u8Data = (u8)(USART_BUSES[USART_u32Bus]->USART_DR);
    }
    return Local_enumErrorRet;
}

USART_ErrorStatus_t USART_enumSendString(u32 USART_u32Bus, u8 *USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if (USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else if (USART_u8Data == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr;
    }
    else
    {
        while (*USART_u8Data != '\0')
        {
            USART_enumSendData(USART_u32Bus, *USART_u8Data);
            USART_u8Data++;
        }
    }
    return Local_enumErrorRet;
}

USART_ErrorStatus_t USART_enumReceiveString(u32 USART_u32Bus, u8 *USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if (USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else if (USART_u8Data == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr;
    }
    else
    {
        do
        {
            USART_enumReceiveData(USART_u32Bus, USART_u8Data);
            USART_u8Data++;
        } while (*USART_u8Data != '\0');
    }
    return Local_enumErrorRet;
}

/**
 * @brief  This function is used to send data using interrupt
 *
 * @param USART_u32Bus : the bus number
 * @param USART_u8Data : the data to be sent
 * @return USART_ErrorStatus_t : the error status
 */
USART_ErrorStatus_t USART_enumSendData_IT(u32 USART_u32Bus, u8 USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if (USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else
    {
        USART_BUSES[USART_u32Bus]->USART_DR = USART_u8Data;
        SET_BIT(USART_BUSES[USART_u32Bus]->USART_CR1, USART_TXEIE_BIT);
    }
    return Local_enumErrorRet;
}

/**
 * @brief  This function is used to receive data using interrupt
 *
 * @param USART_u32Bus : the bus number
 * @param USART_u8Data : the data to be received
 * @return USART_ErrorStatus_t : the error status
 */
USART_ErrorStatus_t USART_enumReceiveData_IT(u32 USART_u32Bus, u8 *USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if (USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else if (USART_u8Data == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr;
    }
    else
    {
        
        SET_BIT(USART_BUSES[USART_u32Bus]->USART_CR1, USART_RXNEIE_BIT);
    }
    return Local_enumErrorRet;
}

/**
 * @brief  This function is used to enable the interrupt
 *
 * @param USART_u32Bus : the bus number
 * @param USART_u32Interrupt : the interrupt to be enabled (USART_PEIE_BIT, USART_TXEIE_BIT, USART_TCIE_BIT, USART_RXNEIE_BIT)
 * @return USART_ErrorStatus_t : the error status
 */
USART_ErrorStatus_t USART_enumEnableInterrupt(u32 USART_u32Bus, u32 USART_u32Interrupt)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if (USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else
    {
        SET_BIT(USART_BUSES[USART_u32Bus]->USART_CR1, USART_u32Interrupt);
    }
    return Local_enumErrorRet;
}

/**
 * @brief  This function is used to disable the interrupt
 *
 * @param USART_u32Bus : the bus number
 * @param USART_u32Interrupt : the interrupt to be disabled (USART_PEIE_BIT, USART_TXEIE_BIT, USART_TCIE_BIT, USART_RXNEIE_BIT)
 * @return USART_ErrorStatus_t : the error status
 */
USART_ErrorStatus_t USART_enumDisableInterrupt(u32 USART_u32Bus, u32 USART_u32Interrupt)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if (USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else
    {
        CLEAR_BIT(USART_BUSES[USART_u32Bus]->USART_CR1, USART_u32Interrupt);
    }
    return Local_enumErrorRet;
}

/**
 * @brief  This function is used to get the status of the interrupt
 *
 * @param USART_u32Bus : the bus number
 * @param USART_u32Interrupt : the interrupt to get its status (USART_PEIE_BIT, USART_TXEIE_BIT, USART_TCIE_BIT, USART_RXNEIE_BIT)
 * @return u8 : the status of the interrupt
 */
u8 USART_u8GetInterruptStatus(u32 USART_u32Bus, u32 USART_u32Interrupt)
{
    u8 Local_u8InterruptStatus = 0;
    if (USART_u32Bus > USART_CH6)
    {
        Local_u8InterruptStatus = 0;
    }
    else
    {
        Local_u8InterruptStatus = GET_BIT(USART_BUSES[USART_u32Bus]->USART_SR, USART_u32Interrupt);
    }
    return Local_u8InterruptStatus;
}

/**
 * @brief  This function is used to clear the status of the interrupt
 *
 * @param USART_u32Bus : the bus number
 * @param USART_u32Interrupt : the interrupt to be cleared (USART_PEIE_BIT, USART_TXEIE_BIT, USART_TCIE_BIT, USART_RXNEIE_BIT)
 * @return USART_ErrorStatus_t : the error status
 */
USART_ErrorStatus_t USART_enumClearInterruptStatus(u32 USART_u32Bus, u32 USART_u32Interrupt)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if (USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else
    {
        CLEAR_BIT(USART_BUSES[USART_u32Bus]->USART_SR, USART_u32Interrupt);
    }
    return Local_enumErrorRet;
}

 /* Interrupt Handlers (Example, implement as needed) */
 void USART1_IRQHandler(void)
 {
     if (USART1->USART_SR & USART_TXE_FLAG_MASK && USART1->USART_CR1 & (1U << USART_TXEIE_BIT)) {
         CLEAR_BIT(USART1->USART_CR1 , USART_TXEIE_BIT); // Disable TXE interrupt
         if (USART_TxCallbacks[USART_CH1]) {
             USART_TxCallbacks[USART_CH1]();
         }
     }
     if (USART1->USART_SR & USART_RXNE_FLAG_MASK && USART1->USART_CR1 & (1U << USART_RXNEIE_BIT)) {
         CLEAR_BIT(USART1->USART_CR1 , USART_RXNEIE_BIT); // Disable RXNE interrupt
         if (USART_RxCallbacks[USART_CH1]) {
             USART_RxCallbacks[USART_CH1]();
         }
     }
 }


 void USART2_IRQHandler(void)
 {
     if (USART2->USART_SR & USART_TXE_FLAG_MASK && USART2->USART_CR1 & (1U << USART_TXEIE_BIT)) {
         CLEAR_BIT(USART2->USART_CR1 , USART_TXEIE_BIT); // Disable TXE interrupt
         if (USART_TxCallbacks[USART_CH2]) {
             USART_TxCallbacks[USART_CH2]();
         }
     }
     if (USART2->USART_SR & USART_RXNE_FLAG_MASK && USART2->USART_CR1 & (1U << USART_RXNEIE_BIT)) {
         CLEAR_BIT(USART2->USART_CR1 , USART_RXNEIE_BIT); // Disable RXNE interrupt
         if (USART_RxCallbacks[USART_CH2]) {
             USART_RxCallbacks[USART_CH2]();
         }
     }
 }

 void USART6_IRQHandler(void)
 {
     if (USART6->USART_SR & USART_TXE_FLAG_MASK && USART6->USART_CR1 & (1U << USART_TXEIE_BIT)) {
         CLEAR_BIT(USART2->USART_CR1 , USART_TXEIE_BIT); // Disable TXE interrupt
         if (USART_TxCallbacks[USART_CH6]) {
             USART_TxCallbacks[USART_CH6]();
         }
     }
     if (USART6->USART_SR & USART_RXNE_FLAG_MASK && USART6->USART_CR1 & (1U << USART_RXNEIE_BIT)) {
         CLEAR_BIT(USART6->USART_CR1 , USART_RXNEIE_BIT); // Disable RXNE interrupt
         if (USART_RxCallbacks[USART_CH6]) {
             USART_RxCallbacks[USART_CH6]();
         }
     }
 }