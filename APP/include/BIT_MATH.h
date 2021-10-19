/**
 * @file    BIT_MATH.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Common bit manipulation operations
 * @version 0.1
 * @date    2021-07-31
 */

/* Header guard     */
#ifndef 	BIT_MATH_H
#define 	BIT_MATH_H

/**
 *  \brief Read state of a specific bit
 *  \param REGISTER the register includes the bit
 *  \param BIT the required bit number to be read
 *  \return state of the bit: 1 or 0
 */
#define GET_BIT(REGISTER, BIT)      ( 1 & (REGISTER >> BIT) )

/**
 *  \brief Set state of a specific bit (set to 1)
 *  \param REGISTER the register includes the bit
 *  \param BIT the required bit number to be set
 *  \return nothing
 */
#define SET_BIT(REGISTER, BIT)      ( REGISTER |= (1 << BIT) )

/**
 *  \brief Clear state of a specific bit (set to 0)
 *  \param REGISTER the register includes the bit
 *  \param BIT the required bit number to be cleared
 *  \return nothing
 */
#define CLR_BIT(REGISTER, BIT)      ( REGISTER &= ~(1 << BIT) )

/**
 *  \brief Toggle state of a specific bit (set to 0)
 *  \param REGISTER the register includes the bit
 *  \param BIT the required bit number to be toggled
 *  \return nothing
 */
#define TOG_BIT(REGISTER, BIT)      ( REGISTER ^= (1 << BIT) )


#endif									/* End of File guard	*/
