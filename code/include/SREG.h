/**************************************************************************
 * @file    SREG.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Status Registers of ATmega328p MCU
 * @version 1.0.0
 * @date    2021-07-31
 **************************************************************************/
#ifndef SREG_H
#define SREG_H

#define SREG            (* ((volatile u8 *) 0x5F) )

enum{
    C_BIT,      /* Carry Flag */
    Z_BIT,      /* Zero Flag */
    N_BIT,      /* Negative Flag */
    V_BIT,      /* Two's Complement Overflow Flag */
    S_BIT,      /* Sign Flag */
    H_BIT,      /* Half Carry Flag */
    T_BIT,      /* Bit Copy Storage */
    I_BIT,      /* Global Interrupt Enable */
};  /* SREG: Status Register */

#endif    /* SREG_H */