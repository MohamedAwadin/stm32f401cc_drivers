

#ifndef UTILS_H_
#define UTILS_H_


/***********************************************************************/
#define SET_BIT(REG, BIT)			(REG |= (1 << BIT))
#define CLEAR_BIT(REG, BIT)			(REG &= (~(1 << BIT)))
#define READ_BIT(REG, BIT)			((REG>>BIT) & 1)
#define TOGGLE_BIT(REG, BIT)        (REG ^= (1 << BIT))
#define WRITE_BIT(REG, BIT, VALUE)  (REG = (REG&(~(1<<BIT)))|(VALUE << BIT))
/***********************************************************************/

// Set high nibble in REG
#define SET_HIGH_NIB(REG)           (REG |=0xF0)
// Clear high nibble in REG          
#define CLR_HIGH_NIB(REG)           (REG &= 0x0F)
// Get high nibble in REG          
#define GET_HIGH_NIB(REG)           ((REG>>4)    & 0x0F)
// Toggle high nibble in REG       
#define TGL_HIGH_NIB(REG)           (REG ^= 0xF0)
// Set low nibble in REG         
#define SET_LOW_NIB(REG)            (REG |= 0x0F)
// Clear low nibble in REG           
#define CLR_LOW_NIB(REG)            (REG &= 0xF0)
// Get low nibble in REG            
#define GET_LOW_NIB(REG)            (REG         & 0x0F)
// Toggle low nibble in REG            
#define TGL_LOW_NIB(REG)            (REG ^= 0x0F)
//Combine High and Low Nibble (8 Byte Value )
#define COMBINE_HIGH_AND_LOW_NIB(HIGH_NIB,LOW_NIB)          ((HIGH_NIB<<4) | LOW_NIB)

/***********************************************************************/

// Assign VALUE to REG
#define ASSIGN_REG(REG,VALUE)       (REG = (REG & 0x00) | VALUE)
// Assign VALUE to high nibble REG
#define ASSIGN_HIGH_NIB(REG, VALUE) ((REG) = ((REG) & 0x0F) | ((VALUE & 0x0F) << 4))
// Assign VALUE to low nibble REG 
#define ASSIGN_LOW_NIB(REG,VALUE)   ((REG) = ((REG) & 0xF0) | ((VALUE & 0x0F)))
// Right shift by NO in REG
#define RSHFT_REG(REG, NO)          (REG = REG >> NO)
// Left shift by NO in REG
#define LSHFT_REG(REG, NO)          (REG = REG << NO) 
// Circular left shift by NO in REG
#define CLSHFT_REG(REG, NO)         (REG = (REG<<NO) | (REG >> (8-NO)))
// Circular right shift by NO in REG
#define CRSHFT_REG(REG,NO)          (REG = (REG>>NO) | (REG << (8-NO)))








#endif /* UTILS_H_ */
