/**
 * @file uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-12-25
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <avr/io.h>
#include "uart.h"

#define FOSC 8000000UL // Clock Speed

void USART_Init(unsigned int BaudRate)
{
    uint16_t ubrr = (FOSC / 8 / BaudRate - 1) / 2;

    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)));
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;
    /* Get and return received data from buffer */
    return UDR0;
}