/************************************************************************************
*	Description	: standard data types For Arduino IDE.
*	Author		: Mahmoud Karam
*	Date		: 7 July 2021
*	Version		: 2
*   Modified    : u64 and s64 types added.
************************************************************************************/
#ifndef 	STD_TYPES_H					/* File guard	*/
#define 	STD_TYPES_H

/* Signed integers	*/
  typedef   signed long         s64;
  typedef 	signed long int  	s32;		
  typedef 	signed int 	        s16;		
  typedef 	signed char         s8;
  

/* Unsigned integers	*/
  typedef   unsigned long long  u64;
  typedef 	unsigned long int	u32;
/* typedef 	unsigned int 		u16;    ****/   /* Already defined ****/
  typedef 	unsigned char 		u8;
 
 
/* Float numbers	*/
  typedef 	float 				f32;

/* General types  */
#undef HIGH
#undef LOW
typedef enum{
  LOW,
  HIGH
}STATE_t;
 
#endif									/* End of File guard	*/
