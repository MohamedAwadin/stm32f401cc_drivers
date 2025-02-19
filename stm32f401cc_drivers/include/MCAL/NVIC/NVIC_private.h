#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_




#define NVIC_REGISTER_SIZE              ((u8)32)

/*Cortex M4 Maximum IRQ Numbers*/
#define NVIC_IRQn_MAX                   ((u8)240)

#define NVIC_SET_MASK				    ((u32) 0x01)
#define NVIC_CLR_MASK				    ((u32) 0x00)
#define NVIC_SET_PRIORITY_MASK          ((u32) 0xF0) 
#define NVIC_CLR_PRIORITY_MASK          ((u32)0xFFFFFFFF)
#define NVIC_ERROR_PRIORITY_MSK  	    ((u32) 0xFFFFFFFF)

#define NVIC_PRIORITY_START_BIT         ((u8)0x04)


#define SCB_AIRCR_VECTKEY_MASK                   ((u32)0x05FA)   
#define SCB_AIRCR_VECTKEY_CLR_MASK               ((u32)0x0000FFFF)
#define SCB_AIRCR_PRIGROUP_CLR_MASK		         ((u32) 0xFFFFF8FF)
#define SCB_AIRCR_PRIGROUP_VLD_MASK              ((u32)0xFFFFF8FF)




/* NVIC Base Address */
#define NVIC_BASE_ADDRESS  0xE000E100

/* NVIC Register Map Structure */
typedef struct {
    volatile u32 ISER[8]        ;
    volatile u32 RESERVED_0[24] ;
    volatile u32 ICER[8]        ;
    volatile u32 RESERVED_1[24] ;
    volatile u32 ISPR[8]        ;
    volatile u32 RESERVED_2[24] ;
    volatile u32 ICPR[8]        ;
    volatile u32 RESERVED_3[24] ;
    volatile u32 IABR[8]        ;
    volatile u32 RESERVED_4[56] ;
    volatile u8  IPR[240]        ;
    volatile u32 RESERVED_5[644];
    volatile u32 STIR           ;
} NVIC_strRegMap_t;

/* NVIC Register Pointer */
#define NVIC ((NVIC_strRegMap_t *)NVIC_BASE_ADDRESS)




/* SCB Base Address */
#define SCB_BASE_ADDRESS  0xE000ED00

/* SCB Register Map Structure */
typedef struct {
    volatile  u32 CPUID  ;
    volatile  u32 ICSR   ;
    volatile  u32 VTOR   ;
    volatile  u32 AIRCR  ;
    volatile  u32 SCR    ;
    volatile  u32 CCR    ;
    volatile  u32 SHPR[3];    
    volatile  u32 SHCRS  ;
    volatile  u32 CFSR   ;
    volatile  u32 MMSR   ;
    volatile  u32 BFSR   ;
    volatile  u32 UFSR   ;
    volatile  u32 HFSR   ;
    volatile  u32 MMAR   ;
    volatile  u32 BFAR   ;
    volatile  u32 AFSR   ;
} SCB_strRegMap_t;

/* SCB Register Pointer */
#define SCB ((SCB_strRegMap_t *)SCB_BASE_ADDRESS)






















































































#endif /*NVIC_PRIVATE_H_*/