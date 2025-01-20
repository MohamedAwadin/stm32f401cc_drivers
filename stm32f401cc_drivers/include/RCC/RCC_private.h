#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_


// RCC Base Address
#define RCC_BASE 0x40023800U

// Register identifiers (upper 32 bits)
#define    RCC_AHB1ENR_REG  (0x0000000100000000ULL) // AHB1ENR register
#define    RCC_AHB2ENR_REG  (0x0000000200000000ULL) // AHB2ENR register
#define    RCC_APB1ENR_REG  (0x0000000300000000ULL) // APB1ENR register
#define    RCC_APB2ENR_REG  (0x0000000400000000ULL) // APB2ENR register
/**************************************************************/



/*************************Registers Musks********************************* */
#define RCC_PLLON_CFGR_BITMUSK_  			(0x1000000)
#define RCC_PLLRDY_CFGR_BITMUSK_ 			(0x2000000)
#define RCC_PLLSRC_PLLCFGR_BITMUSK_ 		(0x400000)


#define RCC_HSION_CR_BITMUSK_				(0x00000001)
#define RCC_HSIRDY_CR_BITMUSK_				(0x00000002)
#define RCC_HSEON_CR_BITMUSK_				(0x00010000)
#define RCC_HSERDY_CR_BITMUSK_				(0x00020000)
#define RCC_PLLON_CR_BITMUSK_				(0x01000000)
#define RCC_PLLRDY_CR_BITMUSK_				(0x02000000)

#define RCC_APB1_CFGR_BITMASK_	            (0X00001C00) 
#define RCC_APB2_CFGR_BITMASK_	            (0x0000E000) 
#define RCC_AHB_CFGR_BITMASK_	            (0x000000F0) 
#define RCC_HSEBYP_CR_BITMASK_	            (0x00040000) 


#define RCC_RSTSW_CFGR_BITMUSK_		        (0xFFFFFFFC)
#define RCC_SWS_CFGR_BITMUSK_				(0x0000000C)


/******************************************************************** */

#define RCC_PLL_N_MAX 			 432
#define RCC_PLL_N_MIN 			 192

#define RCC_PLL_M_MAX 			 63
#define RCC_PLL_M_MIN 			 2
#define RCC_u16TIME_OUT		    (u16)(500)

#define RCC_CFGR_SW01_SHIFT	  	0x3				
#define RCC_CFGR_SW_SHIFT	  	0x1				

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Clock control register (RCC_CR_) PINS			   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define 	RCC_CR_HSION		(u8)(0)
#define 	RCC_CR_HSIRDY		(u8)(1)
#define 	RCC_CR_HSITRIM0		(u8)(3)
#define 	RCC_CR_HSITRIM2		(u8)(4)	
#define 	RCC_CR_HSITRIM3		(u8)(5)	
#define 	RCC_CR_HSITRIM1		(u8)(6)	
#define 	RCC_CR_HSITRIM4		(u8)(7)	
#define 	RCC_CR_HSICAL0      (u8)(8)
#define 	RCC_CR_HSICAL1		(u8)(9)
#define 	RCC_CR_HSICAL2		(u8)(10)
#define 	RCC_CR_HSICAL3      (u8)(11)
#define 	RCC_CR_HSICAL4		(u8)(12)
#define 	RCC_CR_HSICAL5		(u8)(13)
#define 	RCC_CR_HSICAL6		(u8)(14)
#define 	RCC_CR_HSICAL7   	(u8)(15)
#define 	RCC_CR_HSEON		(u8)(16)
#define 	RCC_CR_HSERDY		(u8)(17)
#define 	RCC_CR_HSEBYP		(u8)(18)
#define 	RCC_CR_CSSON		(u8)(19)
#define 	RCC_CR_PLLON        (u8)(24)
#define 	RCC_CR_PLLRDY 		(u8)(25)
#define 	RCC_CR_PLLI2SON  	(u8)(26)
#define 	RCC_CR_PLLI2SRDY 	(u8)(27)


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Clock configuration register (RCC_CFGR_) PINS	   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define 	RCC_CFGR_SW0			(u8)(0 ) 
#define 	RCC_CFGR_SW1			(u8)(1 ) 
#define 	RCC_CFGR_SWS0			(u8)(2 ) 
#define 	RCC_CFGR_SWS1			(u8)(3 ) 
#define 	RCC_CFGR_HPRE0			(u8)(4 ) 
#define 	RCC_CFGR_HPRE1			(u8)(5 ) 
#define 	RCC_CFGR_HPRE2			(u8)(6 ) 
#define 	RCC_CFGR_HPRE3			(u8)(7 ) 
#define 	RCC_CFGR_PPRE1_0		(u8)(10)
#define 	RCC_CFGR_PPRE1_1		(u8)(11)
#define 	RCC_CFGR_PPRE1_2		(u8)(12)
#define 	RCC_CFGR_PPRE2_0		(u8)(13)
#define 	RCC_CFGR_PPRE2_1		(u8)(14)
#define 	RCC_CFGR_PPRE2_2		(u8)(15)
#define 	RCC_CFGR_RTCPRE_0 		(u8)(16)
#define 	RCC_CFGR_RTCPRE_1 		(u8)(17)
#define 	RCC_CFGR_RTCPRE_2    	(u8)(18)
#define 	RCC_CFGR_RTCPRE_3    	(u8)(19)
#define 	RCC_CFGR_RTCPRE_4    	(u8)(20)
#define 	RCC_CFGR_MCO1_0      	(u8)(21)
#define 	RCC_CFGR_MCO1_1      	(u8)(22)
#define 	RCC_CFGR_I2SSRC      	(u8)(23)
#define 	RCC_CFGR_MCO1PRE_0   	(u8)(24)
#define 	RCC_CFGR_MCO1PRE_1   	(u8)(25)
#define 	RCC_CFGR_MCO1PRE_2   	(u8)(26)
#define 	RCC_CFGR_MCO2PRE_0   	(u8)(27)
#define 	RCC_CFGR_MCO2PRE_1   	(u8)(28)
#define 	RCC_CFGR_MCO2PRE_2   	(u8)(29)
#define 	RCC_CFGR_MCO2_0   		(u8)(30)
#define 	RCC_CFGR_MCO2_1   		(u8)(31)	



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		Clock interrupt register (RCC_CIR_) PINS	           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define 	RCC_CIR_LSIRDYF			(u8)(0)
#define 	RCC_CIR_LSERDYF			(u8)(1)
#define 	RCC_CIR_HSIRDYF			(u8)(2)
#define 	RCC_CIR_HSERDYF			(u8)(3)
#define 	RCC_CIR_PLLRDYF			(u8)(4)
#define 	RCC_CIR_PLLI2SRDYF		(u8)(5)
#define 	RCC_CIR_CSSF 			(u8)(7)
#define 	RCC_CIR_LSIRDYIE		(u8)(8)
#define 	RCC_CIR_LSERDYIE		(u8)(9)
#define 	RCC_CIR_HSIRDYIE		(u8)(10)
#define 	RCC_CIR_HSERDYIE		(u8)(11)
#define 	RCC_CIR_PLLRDYIE		(u8)(12)
#define 	RCC_CIR_PLLI2SRDYIE		(u8)(13)
#define 	RCC_CIR_LSIRDYC 		(u8)(16)
#define 	RCC_CIR_LSERDYC 		(u8)(17)
#define 	RCC_CIR_HSIRDYC 		(u8)(18)
#define 	RCC_CIR_HSERDYC 		(u8)(19)
#define 	RCC_CIR_PLLRDYC 		(u8)(20)
#define 	RCC_CIR_PLLI2SRDYC 		(u8)(21)
#define 	RCC_CIR_CSSC 			(u8)(23)



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *		RCC PLL configuration register (RCC_PLLCFGR) PINS	   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define    RCC_PLLCFGR_PLLM_0       (u8)(0) 
#define    RCC_PLLCFGR_PLLM_1       (u8)(1)
#define    RCC_PLLCFGR_PLLM_2       (u8)(2)
#define    RCC_PLLCFGR_PLLM_3       (u8)(3)
#define    RCC_PLLCFGR_PLLM_4       (u8)(4)
#define    RCC_PLLCFGR_PLLM_5       (u8)(5)
#define    RCC_PLLCFGR_PLLN_0       (u8)(6)
#define    RCC_PLLCFGR_PLLN_1       (u8)(7)
#define    RCC_PLLCFGR_PLLN_2       (u8)(8)
#define    RCC_PLLCFGR_PLLN_3       (u8)(9)
#define    RCC_PLLCFGR_PLLN_4       (u8)(10)
#define    RCC_PLLCFGR_PLLN_5       (u8)(11)
#define    RCC_PLLCFGR_PLLN_6       (u8)(12)
#define    RCC_PLLCFGR_PLLN_7       (u8)(13)
#define    RCC_PLLCFGR_PLLN_8       (u8)(14)
#define    RCC_PLLCFGR_PLLP_0       (u8)(16)  
#define    RCC_PLLCFGR_PLLP_1       (u8)(17)     
#define    RCC_PLLCFGR_PLLSRC       (u8)(22)
#define    RCC_PLLCFGR_PLLQ_0       (u8)(24)
#define    RCC_PLLCFGR_PLLQ_1       (u8)(25)
#define    RCC_PLLCFGR_PLLQ_2       (u8)(26)
#define    RCC_PLLCFGR_PLLQ_3       (u8)(27)



#endif/* RCC_PRIVATE_H_*/
