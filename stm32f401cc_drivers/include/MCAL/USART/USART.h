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

    
}USART_ErrorStatus_t;


typedef struct{
    u32  USART_u32Bus;
    u32  USART_u32ENABLE;
    u32  USART_u32OverSampling;
    u32  USART_u32WordLength;
    u32  USART_u32Parity_Select;
    u32  USART_u32StopBits;
    u32 USART_u32Freq   ;
    u32  USART_u32BaudRate;
}USART_strConfig_t;


USART_ErrorStatus_t USART_enumInit(USART_strConfig_t* Add_pstrConfig);



#endif /*_USART_H_*/