#ifndef DMA_H
#define DMA_H


#include "../../../include/COMMON/Utils.h"
#include "../../../include/COMMON/StdTypes.h"
#include "../../../include/MCAL/DMA/DMA_Private.h"
#include "../../../include/MCAL/NVIC/NVIC.h"


/* Channel Selection for SxCR.CHSEL (bits 25-27) */
#define DMA_u32CHANNEL0_SELECT (0x00000000UL)
#define DMA_u32CHANNEL1_SELECT (0x02000000UL)
#define DMA_u32CHANNEL2_SELECT (0x04000000UL)
#define DMA_u32CHANNEL3_SELECT (0x06000000UL)
#define DMA_u32CHANNEL4_SELECT (0x08000000UL)
#define DMA_u32CHANNEL5_SELECT (0x0A000000UL)
#define DMA_u32CHANNEL6_SELECT (0x0C000000UL)
#define DMA_u32CHANNEL7_SELECT (0x0E000000UL)

/* Stream Enable/Disable for SxCR.EN (bit 0) */
#define DMA_u32STREAM_ENABLE  (0x00000001UL)
#define DMA_u32STREAM_DISABLE (0x00000000UL)

/* Stream Selection Indices */
#define DMA_u8STREAM0_SELECT (u8)(0x00)
#define DMA_u8STREAM1_SELECT (u8)(0x01)
#define DMA_u8STREAM2_SELECT (u8)(0x02)
#define DMA_u8STREAM3_SELECT (u8)(0x03)
#define DMA_u8STREAM4_SELECT (u8)(0x04)
#define DMA_u8STREAM5_SELECT (u8)(0x05)
#define DMA_u8STREAM6_SELECT (u8)(0x06)
#define DMA_u8STREAM7_SELECT (u8)(0x07)

/* DMA Controller Selection */
#define DMA_u8DMA1_SELECT (u8)(0x00)
#define DMA_u8DMA2_SELECT (u8)(0x01)

/* Interrupt Flags for LISR (Streams 0-3) and HISR (Streams 4-7) */
#define DMA_u32STREAM0_INT_TRANS_COMPLETEFLAG (0x00000020UL)
#define DMA_u32STREAM1_INT_TRANS_COMPLETEFLAG (0x00000800UL)
#define DMA_u32STREAM2_INT_TRANS_COMPLETEFLAG (0x00200000UL)
#define DMA_u32STREAM3_INT_TRANS_COMPLETEFLAG (0x08000000UL)

#define DMA_u32STREAM4_INT_TRANS_COMPLETEFLAG (0x00000020UL)
#define DMA_u32STREAM5_INT_TRANS_COMPLETEFLAG (0x00000800UL)
#define DMA_u32STREAM6_INT_TRANS_COMPLETEFLAG (0x00200000UL)
#define DMA_u32STREAM7_INT_TRANS_COMPLETEFLAG (0x08000000UL)

#define DMA_u32STREAM0_INT_HALFTRANS_COMPLETEFLAG (0x00000010UL)
#define DMA_u32STREAM1_INT_HALFTRANS_COMPLETEFLAG (0x00000400UL)
#define DMA_u32STREAM2_INT_HALFTRANS_COMPLETEFLAG (0x00100000UL)
#define DMA_u32STREAM3_INT_HALFTRANS_COMPLETEFLAG (0x00400000UL)

#define DMA_u32STREAM4_INT_HALFTRANS_COMPLETEFLAG (0x00000010UL)
#define DMA_u32STREAM5_INT_HALFTRANS_COMPLETEFLAG (0x00000400UL)
#define DMA_u32STREAM6_INT_HALFTRANS_COMPLETEFLAG (0x00100000UL)
#define DMA_u32STREAM7_INT_HALFTRANS_COMPLETEFLAG (0x00400000UL)

/* Memory Data Size for SxCR.MSIZE (bits 13-14) */
#define DMA_u32MEM_DATA_SIZE_8BITS   (0x00000000UL)
#define DMA_u32MEM_DATA_SIZE_16BITS  (0x00002000UL)
#define DMA_u32MEM_DATA_SIZE_32BITS  (0x00004000UL)

/* Peripheral Data Size for SxCR.PSIZE (bits 11-12) */
#define DMA_u32PERI_DATA_SIZE_8BITS (0x00000000UL)
#define DMA_u32PERI_DATA_SIZE_16BITS (0x00000800UL)
#define DMA_u32PERI_DATA_SIZE_32BITS  (0x00001000UL)

/* Increment Modes for SxCR.MINC (bit 10) and SxCR.PINC (bit 9) */
#define DMA_u32MEM_INC_MODE_FIXED   (0x00000000UL)
#define DMA_u32MEM_INC_MODE_ON      (0x00000400UL)
#define DMA_u32PERI_INC_MODE_FIXED  (0x00000000UL)
#define DMA_u32PERI_INC_MODE_ON     (0x00000200UL)

/* Circular Mode for SxCR.CIRC (bit 8) */
#define DMA_u32CIRCULAR_MODE_DISABLE (0x00000000UL)
#define DMA_u32CIRCULAR_MODE_ENABLE  (0x00000100UL)

/* Data Direction for SxCR.DIR (bits 6-7) */
#define DMA_u32DATA_DIRECTION_PERI_TO_MEM (0x00000000UL)
#define DMA_u32DATA_DIRECTION_MEM_TO_PERI (0x00000040UL)
#define DMA_u32DATA_DIRECTION_MEM_TO_MEM  (0x00000080UL)

/* Priority Levels for SxCR.PL (bits 16-17) */
#define DMA_u32PRIORITY_LOW        (0x00000000UL)
#define DMA_u32PRIORITY_MEDIUM    (0x00001000UL)
#define DMA_u32PRIORITY_HIGH      (0x00002000UL)
#define DMA_u32PRIORITY_VERYHIGH   (0x00003000UL)

/* Peripheral Burst for SxCR.PBURST (bits 21-22) */
#define DMA_u32PERI_BURST_SINGLE   (0x00000000UL)
#define DMA_u32PERI_BURST_INC4    (0x00200000UL)
#define DMA_u32PERI_BURST_INC8     (0x00400000UL)
#define DMA_u32PERI_BURST_INC16    (0x00600000UL)

/* Memory Burst for SxCR.MBURST (bits 23-24) */
#define DMA_u32MEM_BURST_SINGLE   (0x00000000UL)
#define DMA_u32MEM_BURST_INC4     (0x00800000UL)
#define DMA_u32MEM_BURST_INC8     (0x01000000UL)
#define DMA_u32MEM_BURST_INC16    (0x01800000UL)

/* Interrupt Control for SxCR.TCIE (bit 4) and SxCR.HTIE (bit 3) */
#define DMA_u32TRANSFER_COMPLETE_INTERRUPT_DISABLE  (0x00000000UL)
#define DMA_u32TRANSFER_COMPLETE_INTERRUPT_ENABLE   (0x00000010UL)
#define DMA_u32HALF_TRANSFER_INTERRUPT_ENABLE       (0x00000008UL)
#define DMA_u32HALF_TRANSFER_INTERRUPT_DISABLE      (0x00000000UL)

/* FIFO Threshold for SxFCR.FTH (bits 0-1) */
#define DMA_u32FIFO_THRESHOLD_1QUARTER  (0x00000000UL)
#define DMA_u32FIFO_THRESHOLD_HALF      (0x00000001UL)
#define DMA_u32FIFO_THRESHOLD_3QUARTERS (0x00000002UL)
#define DMA_u32FIFO_THRESHOLD_FULL      (0x00000003UL)






//typedef void (*DMA_Callback_t)(void);

/**
 * @brief Enum for DMA event types passed to callback functions.
 */

typedef enum
{
    DMA_enum_EVENT_TRANSFER_COMPLETE,
    DMA_enum_EVENT_HALF_TRANSFER,
}DMA_enum_EVENT_t;

/**
 * @brief Callback function type for DMA events.
 * @param event The event type (TC or HT).
 */
typedef void (*DMA_Callback_t)(DMA_enum_EVENT_t event);

/**
 * @brief Enum for DMA operation status.
 */
typedef enum
{
    DMA_enumNOk,
    DMA_enumOk,
    DMA_enumNullPtr,
    DMA_enumInvalidChannel

    
}DMA_enumErrorStatus_t;

/**
 * @brief Structure for DMA stream configuration.
 * @details Contains all parameters needed to configure a DMA stream on the STM32F401CC.
 */
typedef struct {
    u8 DMA_u8Number;                           ///< DMA controller selection
                                               ///< - DMA_u8DMA1_SELECT: Selects DMA1 controller 
                                               ///< - DMA_u8DMA2_SELECT: Selects DMA2 controller 

    u8 DMA_u8Stream;                           ///< Stream number selection (0-7)
                                               ///< - DMA_u8STREAM0_SELECT: Stream 0 
                                               ///< - DMA_u8STREAM1_SELECT: Stream 1 
                                               ///< - DMA_u8STREAM2_SELECT: Stream 2 
                                               ///< - DMA_u8STREAM3_SELECT: Stream 3 
                                               ///< - DMA_u8STREAM4_SELECT: Stream 4 
                                               ///< - DMA_u8STREAM5_SELECT: Stream 5 
                                               ///< - DMA_u8STREAM6_SELECT: Stream 6 
                                               ///< - DMA_u8STREAM7_SELECT: Stream 7 

    u32 DMA_u32Channel;                        ///< Channel selection (SxCR.CHSEL, bits 25-27)
                                               ///< - DMA_u32CHANNEL0_SELECT: Channel 0 
                                               ///< - DMA_u32CHANNEL1_SELECT: Channel 1 
                                               ///< - DMA_u32CHANNEL2_SELECT: Channel 2 
                                               ///< - DMA_u32CHANNEL3_SELECT: Channel 3 
                                               ///< - DMA_u32CHANNEL4_SELECT: Channel 4 
                                               ///< - DMA_u32CHANNEL5_SELECT: Channel 5 
                                               ///< - DMA_u32CHANNEL6_SELECT: Channel 6 
                                               ///< - DMA_u32CHANNEL7_SELECT: Channel 7 

    u32 DMA_u32Direction;                      ///< Transfer direction (SxCR.DIR, bits 6-7)
                                               ///< - DMA_u32DATA_DIRECTION_PERI_TO_MEM: Peripheral-to-memory 
                                               ///< - DMA_u32DATA_DIRECTION_MEM_TO_PERI: Memory-to-peripheral 
                                               ///< - DMA_u32DATA_DIRECTION_MEM_TO_MEM: Memory-to-memory      

    u32 DMA_u32MemDataSize;                    ///< Memory data size (SxCR.MSIZE, bits 13-14)
                                               ///< - DMA_u32MEM_DATA_SIZE_8BITS: 8-bit data   
                                               ///< - DMA_u32MEM_DATA_SIZE_16BITS: 16-bit data 
                                               ///< - DMA_u32MEM_DATA_SIZE_32BITS: 32-bit data 

    u32 DMA_u32PeriDataSize;                   ///< Peripheral data size (SxCR.PSIZE, bits 11-12)
                                               ///< - DMA_u32PERI_DATA_SIZE_8BITS: 8-bit data   
                                               ///< - DMA_u32PERI_DATA_SIZE_16BITS: 16-bit data 
                                               ///< - DMA_u32PERI_DATA_SIZE_32BITS: 32-bit data 

    u32 DMA_u32MemIncMode;                     ///< Memory increment mode (SxCR.MINC, bit 10)
                                               ///< - DMA_u32MEM_INC_MODE_FIXED: Fixed address 
                                               ///< - DMA_u32MEM_INC_MODE_ON: Increment address 

    u32 DMA_u32PeriIncMode;                    ///< Peripheral increment mode (SxCR.PINC, bit 9)
                                               ///< - DMA_u32PERI_INC_MODE_FIXED: Fixed address  
                                               ///< - DMA_u32PERI_INC_MODE_ON: Increment address 

    u32 DMA_u32PriorityLevel;                  ///< Priority level (SxCR.PL, bits 16-17)
                                               ///< - DMA_u32PRIORITY_LOW: Low priority            
                                               ///< - DMA_u32PRIORITY_MEDIUM: Medium priority      
                                               ///< - DMA_u32PRIORITY_HIGH: High priority          
                                               ///< - DMA_u32PRIORITY_VERYHIGH: Very high priority 

    u32 DMA_u32CircularMode;                   ///< Circular mode (SxCR.CIRC, bit 8)
                                               ///< - DMA_u32CIRCULAR_MODE_DISABLE: Circular mode disabled
                                               ///< - DMA_u32CIRCULAR_MODE_ENABLE: Circular mode enabled  

    u32 DMA_u32PeripheralFlowControl;          ///< Peripheral flow control (SxCR.PFCTRL, bit 5)
                                               ///< -  DMA controls flow
                                               ///< -  Peripheral controls flow

    u32 DMA_u32TransferCompleteInterruptControl; ///< Transfer complete interrupt control (SxCR.TCIE, bit 4)
                                               ///< - DMA_u32TRANSFER_COMPLETE_INTERRUPT_DISABLE: TC interrupt disabled 
                                               ///< - DMA_u32TRANSFER_COMPLETE_INTERRUPT_ENABLE: TC interrupt enabled   

    u32 DMA_u32HalfTransferInterruptControl;   ///< Half-transfer interrupt control (SxCR.HTIE, bit 3)
                                               ///< - DMA_u32HALF_TRANSFER_INTERRUPT_DISABLE: HT interrupt disabled 
                                               ///< - DMA_u32HALF_TRANSFER_INTERRUPT_ENABLE: HT interrupt enabled   

    u32 DMA_u32FIFOThreshold;                  ///< FIFO threshold (SxFCR.FTH, bits 0-1)
                                               ///< - DMA_u32FIFO_THRESHOLD_1QUARTER: 1/4 full  
                                               ///< - DMA_u32FIFO_THRESHOLD_HALF: 1/2 full      
                                               ///< - DMA_u32FIFO_THRESHOLD_3QUARTERS: 3/4 full 
                                               ///< - DMA_u32FIFO_THRESHOLD_FULL: Full          

    DMA_Callback_t DMA_CallbackFunc;           ///< Callback function for interrupts
                                               ///< - Pointer to a function taking DMA_enum_EVENT_t as parameter
                                               ///< - Set to NULL if no callback is needed

    u32 DMA_u32TransferSize;                   ///< Number of data items to transfer (SxNDTR, 16-bit value)
                                               

    void *DMA_pvPeripheralAddress;             ///< Peripheral address pointer (SxPAR)
                                               ///< - Points to the peripheral data register (e.g., &USART1->DR)

    void *DMA_pvMemoryAddress;                 ///< Memory address pointer (SxM0AR)
                                               ///< - Points to the memory buffer (e.g., &buffer[0])
} DMA_strConfig_t;



/**
 * @brief Initialize a DMA stream with the given configuration.
 * @param DMA_strConfig Pointer to the configuration structure.
 * @return DMA_enumErrorStatus_t Operation status.
 */
DMA_enumErrorStatus_t DMA_enumInit(DMA_strConfig_t* DMA_strConfig);
/**
 * @brief Start a DMA transfer by enabling the specified stream.
 * @param DMA_u8Number DMA controller number (DMA1 or DMA2).
 * @param DMA_u8Stream Stream number (0-7).
 * @return DMA_enumErrorStatus_t Operation status.
 */
DMA_enumErrorStatus_t DMA_enumStart(u8 DMA_u8Number, u8 DMA_u8Stream) ;






#endif // DMA_H