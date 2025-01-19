#ifndef STDTYPES_H_
#define STDTYPES_H_
/*	Unsigned Type	*/
typedef unsigned char 	       u8;
typedef unsigned short int     u16;
typedef unsigned long int 	   u32;
typedef unsigned long long     u64;   

/*	Signed Type		*/
typedef signed char 	       s8;
typedef signed short int       s16;
typedef signed long int        s32;
typedef signed long long       s64;   

/*	Unsigned Pointer Type	*/
typedef unsigned char *	       pu8;
typedef unsigned short int *   pu16;
typedef unsigned long int *    pu32;
typedef unsigned long long *   pu64;

/*	Signed Pointer Type		*/
typedef signed char *	        ps8;
typedef signed short int *      ps16;
typedef signed long int *       ps32;
typedef signed long long *      ps64;

/*	Float Type		*/
typedef float                  f32;
typedef double                 f64;
typedef long double            f128;

#define NULL_PTR  ((void*)0)


typedef enum{
	FALSE,
	TRUE
	}bool_type;
typedef enum{
	OK,
	NOK,
	NULL,
	OUTOFRANGE
	}Error_Type;
	
#define MAX_U8  ((u8)255)    //(2^8)-1
#define MIN_U8  ((u8)0)   
#define MAX_S8  ((s8)127)   //(2^(8-1))-1
#define MIN_S8  ((s8)-128)   //-(2^(8-1))

#define MAX_U16  ((u16)65535)   //(2^16)-1
#define MIN_U16  ((u16)0)   
#define MAX_S16  ((s16)32767)  //(2^(16-1))-1
#define MIN_S16  ((s16)-32768)  //-(2^(16-1))

#define MAX_U32  ((u32)4294967295)   //(2^32)-1
#define MIN_U32  ((u32)0)   
#define MAX_S32  ((s32)2147483647)   //(2^(32-1))-1
#define MIN_S32  ((s32)-2147483648)   //-(2^(32-1))

#endif /* STDTYPES_H_ */