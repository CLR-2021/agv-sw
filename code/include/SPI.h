/******************************************************************************
 * @file    SPI.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Interfaces header file for \ref SPI.c
 * @version 1.0.0
 * @date    2022-03-20
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#ifndef SPI_H       
#define SPI_H       

void SPI_Init(void);
void SPI_EnableInterrupt(void(*ptrCallback)(void));
void SPI_DisableInterrupt(void);
ERROR_STATUS_t SPI_SendByte(const u8 data);
ERROR_STATUS_t SPI_SendString(const u8 *str, u8 length);
ERROR_STATUS_t SPI_ReceiveByte(u8 * const data);
ERROR_STATUS_t SPI_ReceiveString(u8 * const str, u8 length);
void SPI_TrancieveByte(const u8 dataToSend, u8 * const dataReceived);

#endif                  
