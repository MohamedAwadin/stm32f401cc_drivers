#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_



#define RCC_PLLON_CFGR_BITMUSK_  ((u32) 0x01000000)
#define RCC_PLLRDY_CFGR_BITMUSK_ ((u32) 0x02000000)



#define RCC_PLL_N_MAX 			 432
#define RCC_PLL_N_MIN 			 192

#define RCC_PLL_M_MAX 			 63
#define RCC_PLL_M_MIN 			 2
#define RCC_u16TIME_OUT		((u16) 500)

#define RCC_CFGR_SW01_SHIFT	  0x3				
#define RCC_CFGR_SW_SHIFT	  0x1				

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Clock control register (RCC_CR_) PINS			   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum{
	RCC_CR_HSION=0,
	RCC_CR_HSIRDY,
	RCC_CR_HSITRIM0=3,
	RCC_CR_HSITRIM1,
	RCC_CR_HSITRIM2,
	RCC_CR_HSITRIM3,
	RCC_CR_HSITRIM4,
	RCC_CR_HSICAL0,
	RCC_CR_HSICAL1,
	RCC_CR_HSICAL2,
	RCC_CR_HSICAL3,
	RCC_CR_HSICAL4,
	RCC_CR_HSICAL5,
	RCC_CR_HSICAL6,
	RCC_CR_HSICAL7,
	RCC_CR_HSEON,
	RCC_CR_HSERDY,
	RCC_CR_HSEBYP,
	RCC_CR_CSSON,
	RCC_CR_PLLON = 24,
	RCC_CR_PLLRDY,
	RCC_CR_PLLI2SON , 
	RCC_CR_PLLI2SRDY
}RCC_CR_Bits;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Clock configuration register (RCC_CFGR_) PINS	   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum{
	RCC_CFGR_SW0			=0,
	RCC_CFGR_SW1			=1,
	RCC_CFGR_SWS0		=2,
	RCC_CFGR_SWS1		=3,
	RCC_CFGR_HPRE0		=4,
	RCC_CFGR_HPRE1		=5,
	RCC_CFGR_HPRE2		=6,
	RCC_CFGR_HPRE3		=7,
	RCC_CFGR_PPRE1_0		=10,
	RCC_CFGR_PPRE1_1		=11,
	RCC_CFGR_PPRE1_2		=12,
	RCC_CFGR_PPRE2_0		=13,
	RCC_CFGR_PPRE2_1		=14,
	RCC_CFGR_PPRE2_2		=15,
	RCC_CFGR_RTCPRE_0 	=16,
	RCC_CFGR_RTCPRE_1 	=17,
	RCC_CFGR_RTCPRE_2    =18,
	RCC_CFGR_RTCPRE_3    =19,
	RCC_CFGR_RTCPRE_4    =20,
	RCC_CFGR_MCO1_0      =21,
	RCC_CFGR_MCO1_1      =22,
	RCC_CFGR_I2SSRC      =23,
	RCC_CFGR_MCO1PRE_0   =24,
	RCC_CFGR_MCO1PRE_1   =25,
	RCC_CFGR_MCO1PRE_2   =26,
	RCC_CFGR_MCO2PRE_0   =27,
	RCC_CFGR_MCO2PRE_1   =28,
	RCC_CFGR_MCO2PRE_2   =29,
	RCC_CFGR_MCO2_0   	=30,
	RCC_CFGR_MCO2_1   	=31	
}RCC_CFGR_Bits;


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Clock interrupt register (RCC_CIR_) PINS	           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum{
	RCC_CIR_LSIRDYF			=0,
	RCC_CIR_LSERDYF			=1,
	RCC_CIR_HSIRDYF			=2,
	RCC_CIR_HSERDYF			=3,
	RCC_CIR_PLLRDYF			=4,
	RCC_CIR_PLLI2SRDYF		=5,
	RCC_CIR_CSSF 			=7,
	RCC_CIR_LSIRDYIE		=8,
	RCC_CIR_LSERDYIE		=9,
	RCC_CIR_HSIRDYIE		=10,
	RCC_CIR_HSERDYIE		=11,
	RCC_CIR_PLLRDYIE		=12,
	RCC_CIR_PLLI2SRDYIE		=13,
	RCC_CIR_LSIRDYC 		= 16,
	RCC_CIR_LSERDYC 		= 17,
	RCC_CIR_HSIRDYC 		= 18,
	RCC_CIR_HSERDYC 		= 19,
	RCC_CIR_PLLRDYC 		= 20,
	RCC_CIR_PLLI2SRDYC 		= 21,
	RCC_CIR_CSSC 			= 23
}RCC_CIR_Bits;


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		RCC PLL configuration register (RCC_PLLCFGR) PINS	   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
typedef enum {
    RCC_PLLCFGR_PLLM_0  = 0,  // PLLM bit 0
    RCC_PLLCFGR_PLLM_1  ,  // PLLM bit 1
    RCC_PLLCFGR_PLLM_2  ,  // PLLM bit 2
    RCC_PLLCFGR_PLLM_3  ,  // PLLM bit 3
    RCC_PLLCFGR_PLLM_4  ,  // PLLM bit 4
    RCC_PLLCFGR_PLLM_5  ,  // PLLM bit 5

    RCC_PLLCFGR_PLLN_0  ,  // PLLN bit 0
    RCC_PLLCFGR_PLLN_1  ,  // PLLN bit 1
    RCC_PLLCFGR_PLLN_2  ,  // PLLN bit 2
    RCC_PLLCFGR_PLLN_3  ,  // PLLN bit 3
    RCC_PLLCFGR_PLLN_4  ,  // PLLN bit 4
    RCC_PLLCFGR_PLLN_5  ,  // PLLN bit 5
    RCC_PLLCFGR_PLLN_6  ,  // PLLN bit 6
    RCC_PLLCFGR_PLLN_7  ,  // PLLN bit 7
    RCC_PLLCFGR_PLLN_8  ,  // PLLN bit 8
    RCC_PLLCFGR_PLLN_9  ,  // PLLN bit 9
    RCC_PLLCFGR_PLLN_10 ,  // PLLN bit 10
    RCC_PLLCFGR_PLLN_11 ,  // PLLN bit 11
    RCC_PLLCFGR_PLLN_12 ,  // PLLN bit 12
    RCC_PLLCFGR_PLLN_13 ,  // PLLN bit 13
    RCC_PLLCFGR_PLLN_14 ,  // PLLN bit 14

    RCC_PLLCFGR_PLLP_0  ,  // PLLP bit 0
    RCC_PLLCFGR_PLLP_1  ,  // PLLP bit 1

    RCC_PLLCFGR_PLLSRC  = 22,  // PLLSRC bit (22)

    RCC_PLLCFGR_PLLQ_0  = 24,  // PLLQ bit 0
    RCC_PLLCFGR_PLLQ_1  ,  // PLLQ bit 1
    RCC_PLLCFGR_PLLQ_2  ,  // PLLQ bit 2
    RCC_PLLCFGR_PLLQ_3  ,  // PLLQ bit 3
} RCC_PLLCFGR_Bits;


#endif/* RCC_PRIVATE_H_*/
