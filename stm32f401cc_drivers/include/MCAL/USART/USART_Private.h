#ifndef _USART_PRIVATE_H_
#define _USART_PRIVATE_H_

#include "USART.h"

#define USART1_BASE_ADDRESS 0x40011000
#define USART6_BASE_ADDRESS 0x40011400
#define USART2_BASE_ADDRESS 0x40004400


typedef struct 
{
    volatile u32 USART_SR ;
    volatile u32 USART_DR ;
    volatile u32 USART_BRR ;
    volatile u32 USART_CR1 ;
    volatile u32 USART_CR2 ;
    volatile u32 USART_CR3 ;
    volatile u32 USART_GTPR ;
}USART_strRegMap_t;


#define USART1 ((USART_strRegMap_t *)USART1_BASE_ADDRESS)
#define USART2 ((USART_strRegMap_t *)USART2_BASE_ADDRESS)
#define USART6 ((USART_strRegMap_t *)USART6_BASE_ADDRESS)



USART_strRegMap_t *USART_BUSES[] = {
    USART1,
    USART2,
    USART6
};

#endif /*_USART_PRIVATE_H_*/