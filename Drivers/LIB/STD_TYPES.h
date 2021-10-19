/**
 ***********************************************************************************
 *	@brief    Standard data types For Arduino MCUs.
 *	@author   Mahmoud Karam
 *	@date		  7 July 2021
 *	@version  0.1
 ***********************************************************************************
 */

/*
* Hint: 	1. Before the first time use on machine, check those sizes using sizeof() operator.
*		    2. For best code visualization, open with Notepad++
*/

#ifndef 	STD_TYPES_H					/* File guard	*/
#define 	STD_TYPES_H

/* Signed integers	*/
  typedef   signed long         s64;
  typedef 	signed long int   	s32;		
  typedef 	signed int 	        s16;		
  typedef 	signed char         s8;
  

/* Unsigned integers	*/
  typedef   unsigned long long  u64;
  typedef 	unsigned long int	  u32;
/* typedef 	unsigned int 		u16;    ****/   /* Already defined ****/
  typedef 	unsigned char 		  u8;
 
 
/* Float numbers	*/
  typedef 	float 				      f32;
 
 #endif									/* End of File guard	*/
