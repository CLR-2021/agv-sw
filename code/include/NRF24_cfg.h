/******************************************************************************
 * @file    NRF24_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Configuration header file for \ref NRF24.c
 * @version 1.0.0
 * @date    2022-03-20
 * @copyright Copyright (c) 2022
 ******************************************************************************/
#ifndef NRF24_CFG_H
#define NRF24_CFG_H

typedef struct{
    PIN_t   pin;
    PORT_t  port;
}CONNECTIONS_t;

typedef struct{
    CONNECTIONS_t ce;
    CONNECTIONS_t csn;
    CONNECTIONS_t irq;
}PINS_t;

typedef enum{
    RX_PIPE0,  
    RX_PIPE1,
    RX_PIPE2,
    RX_PIPE3,
    RX_PIPE4,
    RX_PIPE5, 
}PIPE_t;

typedef struct{
    PINS_t pins;
    u8     channel;
    u8     payload_len;
    u8     addressWidth;
    u8     txAddress[5];
    u8     txPayload[32];
    u8     rx0Address[5];
    u8     rx0Payload[32];
    u8     rx1Address[5];
    u8     rx1Payload[32];
    u8     rx2Address[5];
    u8     rx2Payload[32];
    u8     rx3Address[5];
    u8     rx3Payload[32];
    u8     rx4Address[5];
    u8     rx4Payload[32];
    u8     rx5Address[5];
    u8     rx5Payload[32];
    PIPE_t rxPipe;


}NRF24_t;

extern NRF24_t NRF24_cfg;


#endif                  
