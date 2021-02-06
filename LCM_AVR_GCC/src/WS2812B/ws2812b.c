/**
 * @file ws2812b.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <avr/io.h>
#include <util/delay.h>
#include "ws2812b.h"

static void zero_bit(void);
static void one_bit(void);
static void send_byte(uint8_t byte);
static uint8_t m_number_of_leds = 0;

color_t m_pixels[7];

/**
 * @brief 
 * 
 * @param number_of_leds 
 */
void WS2812B_Init(uint8_t number_of_leds)
{
    m_number_of_leds = number_of_leds;

    DDRB |= (1 << PB0);
    PORTB &= ~(1 << PB0);
}

/**
 * @brief 
 * 
 */
void WS2812B_Reset(void)
{
    _delay_us(75);
}

/**
 * @brief 
 * 
 * @param position 
 * @param color 
 */
void WS2812B_SetPixel(uint8_t position, color_t color)
{
    int i = 0;

    m_pixels[position] = color;

    for (i = 0; i < m_number_of_leds; i++)
    {
        send_byte(m_pixels[i].green);
        send_byte(m_pixels[i].red);
        send_byte(m_pixels[i].blue);
    }
}

/**
 * @brief 
 * 
 */
void WS2812B_ClearAll(void)
{
    int i;

    for (i=0; i<m_number_of_leds; i++)
    {
        m_pixels[i].red     = 0;
        m_pixels[i].green   = 0;
        m_pixels[i].blue    = 0;        
        send_byte(m_pixels[i].green);
        send_byte(m_pixels[i].red);
        send_byte(m_pixels[i].blue);        
    }
}

void zero_bit(void)
{
    PORTB |= (1 << PB0);
    asm("nop");
    asm("nop");

    PORTB &= ~(1 << PB0);
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
}

void one_bit(void)
{
    PORTB |= (1 << PB0);
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");

    PORTB &= ~(1 << PB0);
    asm("nop");
    asm("nop");
    asm("nop");
}

void send_byte(uint8_t byte)
{
    int i = 0;

    for (i = 0; i < 8; i++)
    {
        if (byte & (1 << i))
        {
            one_bit();
        }
        else
        {
            zero_bit();
        }
    }
}