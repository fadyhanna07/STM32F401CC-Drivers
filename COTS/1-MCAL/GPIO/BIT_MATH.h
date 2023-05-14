#ifndef BIT_MATH_H_
#define BIT_MATH_H_
#define SET_BIT(REG,Bit_NO)     (REG) |= (1<<(Bit_NO))

#define CLR_BIT(REG,Bit_NO)     (REG) &= ~(1<<(Bit_NO))

#define TGL_BIT(REG,Bit_NO)		(REG) ^= (1<<Bit_NO)

#define GET_BIT(REG,Bit_NO)	    ((REG)>>(Bit_NO)) & 1

#define SET_PORT(REG)		(REG) | (0xFF)

#define ASSIGN_REG(REG,VALUE)	(REG=VALUE)

// Set The High Nibble in a Register
#define SET_H_NIB(REG)		(REG) |= (0xF0)

// Clear The High Nibble in a Register
#define CLR_H_NIB(REG)		(REG) & (0x0F)

// Get The High Nibble in a Register
#define GET_H_NIB(REG)		((REG) >> 4 )& 0x0F

// Toggle the High Nibble in a Register
#define TGL_H_NIB(REG)			(REG ^(0XF0))

// Set The Low Nibble in a Register
#define SET_L_NIB(REG)		(REG) |= (0x0F)

// Clear The Low Nibble in a Register
#define CLR_L_NIB(REG)              ((REG) &= ~0xF)

// Get The Low Nibble in a Register
#define GET_L_NIB(REG)		(REG) & 0x0F

// Toggle the Low Nibble in a Register
#define TGL_L_NIB(REG)			(REG ^=(0X0F))

// Assign a Value to a Register
#define ASSIGN_REG(REG,VALUE)	(REG=VALUE)

// Assign The High Nibble in a Register
#define ASSIGN_H_NIB(REG,VALUE)		((REG & 0x0F)|=VALUE<<4)

#define ASSIGN_L_NIB(REG,VALUE)	    ((REG & 0xF0)|=VALUE)

// Right Shift by No
#define RSHFT_REG(REG,NO)	     (REG>>NO)


// Left Shift by NO
#define LSHFT_REG(REG,NO)	     (REG<<NO)

// Circular Right Shift
#define CRSHFT_REG(REG,NO)		((REG>>NO ) | REG<<(CHAR_BIT*sizeof(REG)-NO) 

// Circular Left Shift
#define CLSHFT_REG(REG,NO)		(REG<<NO  | REG>>(CHAR_BIT*sizeof(REG)-NO)

#endif
