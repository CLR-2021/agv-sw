/**************************************************************************
 * @file    registers.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Registers of ATmega328p MCU
 * @version 1.0.0
 * @date    2021-07-31
 **************************************************************************/
#ifndef REGISTERS_H
#define REGISTERS_H

/**************************************************************************
 *                                 ADC Register
 **************************************************************************/
#define ADC_u8ADMUX_REG       (* ((volatile u8 *) 0x27) )
#define ADC_u8ADCSRA_REG      (* ((volatile u8 *) 0x26) )
#define ADC_u8ADCH_REG        (* ((volatile u8 *) 0x25) )
#define ADC_u8ADCL_REG        (* ((volatile u8 *) 0x24) )
#define ADC_u8ADCSRB_REG      (* ((volatile u8 *) 0x06) )

/**************************************************************************
 *                                 EEPROM Register
 **************************************************************************/
#define EEPROM_u8EECR_REG     (* ((volatile u8 *) 0x3F) )
#define EEPROM_u8EEDR_REG     (* ((volatile u8 *) 0x3E) )
#define EEPROM_u8EEARL_REG    (* ((volatile u8 *) 0x3D) )
#define EEPROM_u8EEARH_REG    (* ((volatile u8 *) 0x3C) )
#define EEPROM_u8EECR_REG     (* ((volatile u8 *) 0x3F) )

#endif    /* REGISTERS_H */