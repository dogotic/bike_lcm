#ifndef UART_H
#define UART_H

/**
 * @file uart.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-25
 * 
 * @copyright Copyright (c) 2020
 * 
 */


/**
 * @brief 
 * 
 * @param ubrr 
 */
void USART_Init(unsigned int ubrr);

/**
 * @brief 
 * 
 * @param data 
 */
void USART_Transmit(unsigned char data);

/**
 * @brief 
 * 
 * @return unsigned char 
 */
unsigned char USART_Receive(void);

#endif // UART_H