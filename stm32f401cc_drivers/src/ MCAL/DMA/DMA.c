

#include "../../../include/MCAL/DMA/DMA.h"

/* Array of DMA controller pointers */
static const DMA_strRegMap_t *DMA_Peripheral[2] = {DMA1, DMA2};


/* Callback array for DMA1 and DMA2, Streams 0-7 */
static DMA_Callback_t DMA_Callbacks[2][8] = {0};


/**
 * @brief Initialize a DMA stream with the provided configuration.
 * @param DMA_strConfig Pointer to the configuration structure.
 * @return DMA_enumErrorStatus_t Status of the initialization.
 * @details Configures the DMA stream registers and enables interrupts if requested.
 */

DMA_enumErrorStatus_t DMA_enumInit(DMA_strConfig_t *DMA_strConfig)
{
    DMA_enumErrorStatus_t Local_enumErrorRet = DMA_enumOk;
    /* Validate input parameters */
    if (DMA_strConfig == NULL_PTR)
    {
        Local_enumErrorRet = DMA_enumNullPtr;
    }
    else if (DMA_strConfig->DMA_u8Number > DMA_u8DMA2_SELECT ||
             DMA_strConfig->DMA_u8Stream > DMA_u8STREAM7_SELECT)
    {
        Local_enumErrorRet = DMA_enumInvalidChannel;
    }
    else if (DMA_strConfig->DMA_pvPeripheralAddress == NULL_PTR)
    {
        Local_enumErrorRet = DMA_enumNullPtr;
    }
    else if (DMA_strConfig->DMA_pvMemoryAddress == NULL_PTR)
    {
        Local_enumErrorRet = DMA_enumNullPtr;
    }

    else
    {
        /* Select DMA controller and stream */
        DMA_strRegMap_t *DMAx = (DMA_strRegMap_t *)DMA_Peripheral[DMA_strConfig->DMA_u8Number];
        DMA_strChannel_t *stream = &DMAx->Channel[DMA_strConfig->DMA_u8Stream];

        /* Disable stream and wait for it to stop */
        stream->SxCR &= ~DMA_u32STREAM_ENABLE;
        while (stream->SxCR & DMA_u32STREAM_ENABLE);

        /* Configure stream control register (SxCR) */
        stream->SxCR = DMA_strConfig->DMA_u32Channel |
                       DMA_strConfig->DMA_u32Direction |
                       DMA_strConfig->DMA_u32MemDataSize |
                       DMA_strConfig->DMA_u32PeriDataSize |
                       DMA_strConfig->DMA_u32MemIncMode |
                       DMA_strConfig->DMA_u32PeriIncMode |
                       DMA_strConfig->DMA_u32CircularMode |
                       DMA_strConfig->DMA_u32PriorityLevel |
                       DMA_strConfig->DMA_u32TransferCompleteInterruptControl |
                       DMA_strConfig->DMA_u32HalfTransferInterruptControl |
                       DMA_strConfig->DMA_u32PeripheralFlowControl;
        
        /* Set transfer size and addresses */
        stream->SxNDTR = DMA_strConfig->DMA_u32TransferSize;
        stream->SxPAR = (u32)DMA_strConfig->DMA_pvPeripheralAddress;
        stream->SxM0AR = (u32)DMA_strConfig->DMA_pvMemoryAddress;
        /* Configure FIFO control register */
        stream->SxFCR = DMA_strConfig->DMA_u32FIFOThreshold;
        /* Enable interrupts if requested */
        if (DMA_strConfig->DMA_u32TransferCompleteInterruptControl == DMA_u32TRANSFER_COMPLETE_INTERRUPT_ENABLE
            || DMA_strConfig->DMA_u32HalfTransferInterruptControl == DMA_u32HALF_TRANSFER_INTERRUPT_ENABLE)
        {
            DMA_Callbacks[DMA_strConfig->DMA_u8Number][DMA_strConfig->DMA_u8Stream] = DMA_strConfig->DMA_CallbackFunc;

            if (DMA_strConfig->DMA_u8Number == DMA_u8DMA1_SELECT)
            {
                NVIC_enumEnableIRQ(NVIC_DMA1_Stream0_IRQn + DMA_strConfig->DMA_u8Stream);
            }
            else
            {
                NVIC_enumEnableIRQ(NVIC_DMA2_Stream0_IRQn + DMA_strConfig->DMA_u8Stream);
            }
        }
        // stream->CCR |= DMA_u32Stream_Enable;
    }

    return Local_enumErrorRet;
}

/**
 * @brief Start a DMA transfer by enabling the specified stream.
 * @param DMA_u8Number DMA controller number (DMA1 or DMA2).
 * @param DMA_u8Stream Stream number (0-7).
 * @return DMA_enumErrorStatus_t Status of the operation.
 * @details Checks if the stream is already enabled before starting.
 */

DMA_enumErrorStatus_t DMA_enumStart(u8 DMA_u8Number, u8 DMA_u8Stream)
{
    DMA_enumErrorStatus_t Local_enumErrorRet = DMA_enumOk;
    if (DMA_u8Number > DMA_u8DMA2_SELECT || DMA_u8Stream > DMA_u8STREAM7_SELECT) {
        Local_enumErrorRet = DMA_enumInvalidChannel;
    }
    else if (DMA_Peripheral[DMA_u8Number]->Channel[DMA_u8Stream].SxCR & DMA_u32STREAM_ENABLE) {
        // Stream already active
        Local_enumErrorRet = DMA_enumNOk;
    }
    else {
        DMA_strRegMap_t *DMAx = (DMA_strRegMap_t *)DMA_Peripheral[DMA_u8Number];
        DMA_strChannel_t *stream = &DMAx->Channel[DMA_u8Stream];
        stream->SxCR |= DMA_u32STREAM_ENABLE; // Enable the stream
    }

    return Local_enumErrorRet;
}

/* Interrupt Handlers for DMA1 Streams 0-3 (LISR/LIFCR) */
void DMA1_Stream0_IRQHandler(void)
{
    if (DMA1->LISR & DMA_u32STREAM0_INT_TRANS_COMPLETEFLAG)
    {
        DMA1->LIFCR |= DMA_u32STREAM0_INT_TRANS_COMPLETEFLAG; // Clear TC flag
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM0_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM0_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA1->LISR & DMA_u32STREAM0_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA1->LIFCR |= DMA_u32STREAM0_INT_HALFTRANS_COMPLETEFLAG; // Clear HT flag
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM0_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM0_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA1_Stream1_IRQHandler(void)
{
    if (DMA1->LISR & DMA_u32STREAM1_INT_TRANS_COMPLETEFLAG)
    {
        DMA1->LIFCR |= DMA_u32STREAM1_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM1_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM1_SELECT]( DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA1->LISR & DMA_u32STREAM1_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA1->LIFCR |= DMA_u32STREAM1_INT_HALFTRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM1_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM1_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA1_Stream2_IRQHandler(void)
{
    if (DMA1->LISR & DMA_u32STREAM2_INT_TRANS_COMPLETEFLAG)
    {
        DMA1->LIFCR |= DMA_u32STREAM2_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM2_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM2_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    // Add handling for other flags (e.g., error, half-transfer) if needed
    if (DMA1->LISR & DMA_u32STREAM2_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA1->LIFCR |= DMA_u32STREAM2_INT_HALFTRANS_COMPLETEFLAG; // Clear flag
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM2_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM2_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA1_Stream3_IRQHandler(void)
{
    if (DMA1->LISR & DMA_u32STREAM3_INT_TRANS_COMPLETEFLAG)
    {
        DMA1->LIFCR |= DMA_u32STREAM3_INT_TRANS_COMPLETEFLAG; // Clear flag
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM3_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM3_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA1->LISR & DMA_u32STREAM3_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA1->LIFCR |= DMA_u32STREAM3_INT_HALFTRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM3_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM3_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}
/* Interrupt Handlers for DMA1 Streams 4-7 (HISR/HIFCR) */
void DMA1_Stream4_IRQHandler(void)
{
    if (DMA1->HISR & DMA_u32STREAM4_INT_TRANS_COMPLETEFLAG)
    {
        DMA1->HIFCR |= DMA_u32STREAM4_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM4_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM4_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA1->HISR & DMA_u32STREAM4_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA1->HIFCR |= DMA_u32STREAM4_INT_HALFTRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM4_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM4_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA1_Stream5_IRQHandler(void)
{
    if (DMA1->HISR & DMA_u32STREAM5_INT_TRANS_COMPLETEFLAG)
    {
        DMA1->HIFCR |= DMA_u32STREAM5_INT_TRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM5_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM5_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA1->HISR & DMA_u32STREAM5_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA1->HIFCR |= DMA_u32STREAM5_INT_HALFTRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM5_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM5_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA1_Stream6_IRQHandler(void)
{
    if (DMA1->HISR & DMA_u32STREAM6_INT_TRANS_COMPLETEFLAG)
    {
        DMA1->HIFCR |= DMA_u32STREAM6_INT_TRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM6_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM6_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA1->HISR & DMA_u32STREAM6_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA1->HIFCR |= DMA_u32STREAM6_INT_HALFTRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM6_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM6_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA1_Stream7_IRQHandler(void)
{
    if (DMA1->HISR & DMA_u32STREAM7_INT_TRANS_COMPLETEFLAG) {
        DMA1->HIFCR |= DMA_u32STREAM7_INT_TRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM7_SELECT]) {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM7_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    if (DMA1->HISR & DMA_u32STREAM7_INT_HALFTRANS_COMPLETEFLAG) {
        DMA1->HIFCR |= DMA_u32STREAM7_INT_HALFTRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM7_SELECT]) {
            DMA_Callbacks[DMA_u8DMA1_SELECT][DMA_u8STREAM7_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

/* Interrupt Handlers for DMA2 Streams 0-3 (LISR/LIFCR) */
void DMA2_Stream0_IRQHandler(void)
{
    if (DMA2->LISR & DMA_u32STREAM0_INT_TRANS_COMPLETEFLAG)
    {
        DMA2->LIFCR |= DMA_u32STREAM0_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM0_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM0_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA2->LISR & DMA_u32STREAM0_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA2->LIFCR |= DMA_u32STREAM0_INT_HALFTRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM0_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM0_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA2_Stream1_IRQHandler(void)
{
    if (DMA2->LISR & DMA_u32STREAM1_INT_TRANS_COMPLETEFLAG)
    {
        DMA2->LIFCR |= DMA_u32STREAM1_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM1_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM1_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA2->LISR & DMA_u32STREAM1_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA2->LIFCR |= DMA_u32STREAM1_INT_HALFTRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM1_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM1_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA2_Stream2_IRQHandler(void)
{
    if (DMA2->LISR & DMA_u32STREAM2_INT_TRANS_COMPLETEFLAG)
    {
        DMA2->LIFCR |= DMA_u32STREAM2_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM2_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM2_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA2->LISR & DMA_u32STREAM2_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA2->LIFCR |= DMA_u32STREAM2_INT_HALFTRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM2_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM2_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA2_Stream3_IRQHandler(void)
{
    if (DMA2->LISR & DMA_u32STREAM3_INT_TRANS_COMPLETEFLAG)
    {
        DMA2->LIFCR |= DMA_u32STREAM3_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM3_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM3_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA2->LISR & DMA_u32STREAM3_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA2->LIFCR |= DMA_u32STREAM3_INT_HALFTRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM3_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM3_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

/* Interrupt Handlers for DMA2 Streams 4-7 (HISR/HIFCR) */
void DMA2_Stream4_IRQHandler(void)
{
    if (DMA2->HISR & DMA_u32STREAM4_INT_TRANS_COMPLETEFLAG)
    {
        DMA2->HIFCR |= DMA_u32STREAM4_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM4_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM4_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }

    if (DMA2->HISR & DMA_u32STREAM4_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA2->HIFCR |= DMA_u32STREAM4_INT_HALFTRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM4_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM4_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA2_Stream5_IRQHandler(void)
{
    if (DMA2->HISR & DMA_u32STREAM5_INT_TRANS_COMPLETEFLAG)
    {
        DMA2->HIFCR |= DMA_u32STREAM5_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM5_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM5_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA2->HISR & DMA_u32STREAM5_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA2->HIFCR |= DMA_u32STREAM5_INT_HALFTRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM5_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM5_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}

void DMA2_Stream6_IRQHandler(void)
{
    if (DMA2->HISR & DMA_u32STREAM6_INT_TRANS_COMPLETEFLAG)
    {
        DMA2->HIFCR |= DMA_u32STREAM6_INT_TRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM6_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM6_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    
    if (DMA2->HISR & DMA_u32STREAM6_INT_HALFTRANS_COMPLETEFLAG)
    {
        DMA2->HIFCR |= DMA_u32STREAM6_INT_HALFTRANS_COMPLETEFLAG; 
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM6_SELECT])
        {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM6_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}


void DMA2_Stream7_IRQHandler(void)
{
    if (DMA2->HISR & DMA_u32STREAM7_INT_TRANS_COMPLETEFLAG) {
        DMA2->HIFCR |= DMA_u32STREAM7_INT_TRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM7_SELECT]) {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM7_SELECT](DMA_enum_EVENT_TRANSFER_COMPLETE);
        }
    }
    if (DMA2->HISR & DMA_u32STREAM7_INT_HALFTRANS_COMPLETEFLAG) {
        DMA2->HIFCR |= DMA_u32STREAM7_INT_HALFTRANS_COMPLETEFLAG;
        if (DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM7_SELECT]) {
            DMA_Callbacks[DMA_u8DMA2_SELECT][DMA_u8STREAM7_SELECT](DMA_enum_EVENT_HALF_TRANSFER);
        }
    }
}