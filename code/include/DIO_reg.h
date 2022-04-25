/**************************************************************************
 * @file    DIO_reg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   DIO Registers of ATmega328p microcontroller.
 * @version 1.0.0
 * @date    2021-07-31
 **************************************************************************/
#ifndef DIO_REG_H
#define DIO_REG_H

#define PINA        (* ((volatile u8 *) 0x39) )     /*!< Port A Input Pins */
#define DDRA        (* ((volatile u8 *) 0x3A) )     /*!< Port A Data Direction Register */
#define PORTA       (* ((volatile u8 *) 0x3B) )     /*!< Port A Data Register */

#define PINB        (* ((volatile u8 *) 0x36) )     /*!< Port B Input Pins */
#define DDRB        (* ((volatile u8 *) 0x37) )     /*!< Port B Data Direction Register */
#define PORTB       (* ((volatile u8 *) 0x38) )     /*!< Port B Data Register */

#define PINC        (* ((volatile u8 *) 0x33) )     /*!< Port C Input Pins */
#define DDRC        (* ((volatile u8 *) 0x34) )     /*!< Port C Data Direction Register */
#define PORTC       (* ((volatile u8 *) 0x35) )     /*!< Port C Data Register */

#define PIND        (* ((volatile u8 *) 0x30) )     /*!< Port D Input Pins */
#define DDRD        (* ((volatile u8 *) 0x31) )     /*!< Port D Data Direction Register */
#define PORTD       (* ((volatile u8 *) 0x32) )     /*!< Port D Data Register */

#define PINE        (* ((volatile u8 *) 0x21) )     /*!< Port E Input Pins */
#define DDRE        (* ((volatile u8 *) 0x22) )     /*!< Port E Data Direction Register */
#define PORTE       (* ((volatile u8 *) 0x23) )     /*!< Port E Data Register */

#define PINF        (* ((volatile u8 *) 0x20) )     /*!< Port F Input Pins */
#define DDRF        (* ((volatile u8 *) 0x61) )     /*!< Port F Data Direction Register */
#define PORTF       (* ((volatile u8 *) 0x62) )     /*!< Port F Data Register */

#define PING        (* ((volatile u8 *) 0x63) )     /*!< Port G Input Pins */
#define DDRG        (* ((volatile u8 *) 0x64) )     /*!< Port G Data Direction Register */
#define PORTG       (* ((volatile u8 *) 0x65) )     /*!< Port G Data Register */

#endif    /* DIO_REG_H */