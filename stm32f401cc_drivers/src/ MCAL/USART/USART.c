

#include "../../../include/COMMON/Utils.h"
#include "../../../include/COMMON/StdTypes.h"
#include "../../../include/MCAL/USART/USART.h"
#include "../../../include/MCAL/USART/USART_Private.h"


#define USART_OVERSAMPLING_16           (u32)(0x00000000)
#define USART_OVERSAMPLING_8            (u32)(0x00008000)


#define USART_WORDLENGTH_8              (u32)(0x00000000)
#define USART_WORDLENGHT_9              (u32)(0x00001000)
#define USART_WORDLENGTH_CLR_MASK            0xFFFFDFFF

#define USART_ENABLE                         0x00002000
#define USART_DISABLE                        0x00000000


#define USART_PARITY_NONE                  0x00000000     
#define USART_PARITY_ODD                   0x00000600   
#define USART_PARITY_EVEN                  0x00000400  
#define USART_PARITY_CLR_MASK              0xFFFFF9FF

#define USART_PEIE_BIT                       8U     
#define USART_TXEIE_BIT                      7U                
#define USART_TCIE_BIT                       6U  
#define USART_RXNEIE_BIT                     5U                
           
#define USART_TX_ENABLE                    0x00000008
#define USART_RX_ENABLE                    0x00000004 


#define USART_DIV_MANTISSA_MASK              0x0000000F
#define USART_DIV_FRACTION_MASK              0x0000FFF0


#define USART_STOP_BIT_1                    0x00000000
#define USART_STOP_BIT_0_5                  0x00001000
#define USART_STOP_BIT_2                    0x00002000
#define USART_STOP_BIT_1_5                  0x00003000
#define USART_STOP_BIT_CLR_MASK             0xFFFFCFFF
#define USART_TXE_FLAG_MASK                 0x00000080



#define _IS_USART_OVERSAMPLING(_USART_OVERSAMPLING_) ((_USART_OVERSAMPLING_ == USART_OVERSAMPLING_16) || (_USART_OVERSAMPLING_ == USART_OVERSAMPLING_8))

#define _IS_USART_WORDLENGTH(_USART_WORDLENGTH_) ((_USART_WORDLENGTH_ == USART_WORDLENGTH_8) || (_USART_WORDLENGTH_ == USART_WORDLENGHT_9))

typedef void (*USART_Callback_t)(void) ;

typedef struct{
    volatile u8* Data ;
    volatile u8  Len ; 
    volatile USART_Callback_t USART_CallbackFunc ;
    volatile u8  Pos;
    volatile u8  Status;
}USART_strBuffer_t;



USART_ErrorStatus_t USART_enumInit(USART_strConfig_t* Add_pstrConfig)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk; 
    u32 Local_u32TempReg = 0;
    f32 USARTDIV             =0;
    f32 Fraction_Boundary    =0;
    u32 DIV_Fraction         =0;
    u32 DIV_Fraction_MAXVALUE=0;
    u32 DIV_Mantissa         =0;

    if(Add_pstrConfig == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr ;

    }
    else if (Add_pstrConfig ->USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel ;
    }
    else if(!_IS_USART_OVERSAMPLING(Add_pstrConfig->USART_u32OverSampling))
    {
        Local_enumErrorRet = USART_enumInvalidOVSampling ;
    }
    else if(!_IS_USART_WORDLENGTH(Add_pstrConfig->USART_u32WordLength))
    {
        Local_enumErrorRet = USART_enumInvalidOVSampling ;
    }
    else
    {
        f32 OVER8 = (Add_pstrConfig->USART_u32OverSampling == USART_OVERSAMPLING_16)?0:1;
        u32 MaxBaudRate = (Add_pstrConfig->USART_u32Freq)/(8*(2-OVER8));
        if (Add_pstrConfig->USART_u32BaudRate > MaxBaudRate)
        {
            Local_enumErrorRet =USART_enumNOk;
        }
        else
        {
            Local_u32TempReg = USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1;
            Local_u32TempReg |= (USART_ENABLE);
            USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1 = Local_u32TempReg ;

            Local_u32TempReg = USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1;
            Local_u32TempReg &= USART_WORDLENGTH_CLR_MASK ;
            Local_u32TempReg |= Add_pstrConfig->USART_u32WordLength ;
            USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1 = Local_u32TempReg ;

            Local_u32TempReg = USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1;
            Local_u32TempReg &= USART_PARITY_CLR_MASK ;
            Local_u32TempReg |= Add_pstrConfig->USART_u32Parity_Select;
            USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1 = Local_u32TempReg ;

            

            /*Select Baud Rate*/
            USARTDIV              = (Add_pstrConfig->USART_u32Freq)/(Add_pstrConfig->USART_u32BaudRate)*(8*(2-OVER8));
            Fraction_Boundary     = (Add_pstrConfig->USART_u32OverSampling == USART_OVERSAMPLING_16)?16:8; 
            DIV_Fraction          = (u32)(Fraction_Boundary*(f32)((f32)USARTDIV - (u32)USARTDIV))+1;
            DIV_Fraction_MAXVALUE = (u32)(Fraction_Boundary-1);
            DIV_Mantissa          = 0;
            if (DIV_Fraction > DIV_Fraction_MAXVALUE)
            {
                DIV_Fraction = 0;
                USARTDIV++;
                DIV_Mantissa = (u32)USARTDIV;
            }
            {
                DIV_Mantissa = (u32)USARTDIV;
            }

            Local_u32TempReg = USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_BRR;
            Local_u32TempReg &= USART_DIV_MANTISSA_MASK;
            Local_u32TempReg |= DIV_Mantissa;
            
            Local_u32TempReg &= USART_DIV_FRACTION_MASK;
            Local_u32TempReg |= DIV_Fraction;
            USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_BRR = Local_u32TempReg ;

            Local_u32TempReg = USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR2;
            Local_u32TempReg &= USART_STOP_BIT_CLR_MASK;
            Local_u32TempReg |= Add_pstrConfig->USART_u32StopBits;
            USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR2 = Local_u32TempReg ;


            Local_u32TempReg = USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1;
            Local_u32TempReg |= USART_TX_ENABLE;
            Local_u32TempReg |= USART_RX_ENABLE;
            USART_BUSES[Add_pstrConfig->USART_u32Bus]->USART_CR1 = Local_u32TempReg ;
        }
        

    }
    return Local_enumErrorRet;

}

USART_ErrorStatus_t USART_enumSendData(u32 USART_u32Bus, u8 USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if(USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else
    {
        USART_BUSES[USART_u32Bus]->USART_DR = USART_u8Data;
    }
    return Local_enumErrorRet;
}

USART_ErrorStatus_t USART_enumReceiveData(u32 USART_u32Bus, u8* USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if(USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else if(USART_u8Data == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr;
    }
    else
    {
        *USART_u8Data = (u8)(USART_BUSES[USART_u32Bus]->USART_DR);
    }
    return Local_enumErrorRet;
}

USART_ErrorStatus_t USART_enumSendString(u32 USART_u32Bus, u8* USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if(USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else if(USART_u8Data == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr;
    }
    else
    {
        while(*USART_u8Data != '\0')
        {
            USART_enumSendData(USART_u32Bus, *USART_u8Data);
            USART_u8Data++;
        }
    }
    return Local_enumErrorRet;
}

USART_ErrorStatus_t USART_enumReceiveString(u32 USART_u32Bus, u8* USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if(USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else if(USART_u8Data == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr;
    }
    else
    {
        do
        {
            USART_enumReceiveData(USART_u32Bus, USART_u8Data);
            USART_u8Data++;
        }while(*USART_u8Data != '\0');
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
    if(USART_u32Bus > USART_CH6)
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
USART_ErrorStatus_t USART_enumReceiveData_IT(u32 USART_u32Bus, u8* USART_u8Data)
{
    USART_ErrorStatus_t Local_enumErrorRet = USART_enumOk;
    if(USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else if(USART_u8Data == NULL_PTR)
    {
        Local_enumErrorRet = USART_enumNullPtr;
    }
    else
    {
        *USART_u8Data = (u8)(USART_BUSES[USART_u32Bus]->USART_DR);
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
    if(USART_u32Bus > USART_CH6)
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
    if(USART_u32Bus > USART_CH6)
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
    if(USART_u32Bus > USART_CH6)
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
    if(USART_u32Bus > USART_CH6)
    {
        Local_enumErrorRet = USART_enumInvalidChannel;
    }
    else
    {
        CLEAR_BIT(USART_BUSES[USART_u32Bus]->USART_SR, USART_u32Interrupt);
    }
    return Local_enumErrorRet;
}




