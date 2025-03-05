#ifndef _USART_H_
#define _USART_H_

#include "../../COMMON/StdTypes.h"
#include "USART_Private.h"


#define USART_CH1    (0U)
#define USART_CH2    (1U)
#define USART_CH6    (2U)



typedef enum{
    USART_enumNOk,
    USART_enumOk,
    USART_enumNullPtr,
    USART_enumInvalidChannel,
    USART_enumInvalidOVSampling,
    USART_enumInvalidWordLength

    
}USART_ErrorStatus_t;


typedef struct{
    u32  USART_u32Bus;         // Channel selection (USART_CH1, USART_CH2, USART_CH6)
    u32  USART_u32TxRxMode;    // TX/RX mode (e.g., USART_TX_ENABLE_ONLY)
    u32  USART_u32OverSampling;// Oversampling mode (16 or 8)
    u32  USART_u32WordLength;  // Word length (8 or 9 bits)
    u32  USART_u32Parity_Select;// Parity selection (none, odd, even)
    u32  USART_u32StopBits;    // Stop bits (1, 0.5, 2, 1.5)
    u32  USART_u32Freq;        // Peripheral clock frequency (Hz)
    u32  USART_u32BaudRate;    // Baud rate (bps)
}USART_strConfig_t;


USART_ErrorStatus_t USART_enumInit(USART_strConfig_t* Add_pstrConfig);



#endif /*_USART_H_*/