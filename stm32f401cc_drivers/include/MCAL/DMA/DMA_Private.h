#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H


#include "DMA.h"


/* DMA Base Addresses */
#define DMA1_BASE_ADDRESS (u32)(0x40026000) //< DMA1 base address
#define DMA2_BASE_ADDRESS (u32)(0x40026400) //< DMA2 base address

/**
 * @brief Structure for DMA stream registers.
 */
typedef struct
{
    volatile u32 SxCR; // Stream x configuration register
    volatile u32 SxNDTR; // Stream x number of data register
    volatile u32 SxPAR; // Stream x peripheral address register
    volatile u32 SxM0AR; // Stream x memory 0 address register
    volatile u32 SxM1AR; // Stream x memory 1 address register
    volatile u32 SxFCR; // Stream x FIFO control register
}DMA_strChannel_t;

/**
 * @brief Structure for DMA controller registers.
 */
typedef struct
{
    volatile u32 LISR; // Low interrupt status register
    volatile u32 HISR; // High interrupt status register
    volatile u32 LIFCR; // Low interrupt flag clear register
    volatile u32 HIFCR; // High interrupt flag clear register
    DMA_strChannel_t Channel[8]; // 8 DMA channels

}DMA_strRegMap_t;

/* DMA Controller Pointers */
#define DMA1 ((DMA_strRegMap_t*)DMA1_BASE_ADDRESS)
#define DMA2 ((DMA_strRegMap_t*)DMA2_BASE_ADDRESS)


#endif // DMA_PRIVATE_H