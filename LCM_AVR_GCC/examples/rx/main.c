#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include "nrf24l01.h"
#include "nrf24l01-mnemonics.h"
#include "uart.h"

#define CMD_RIGHT       'R'
#define CMD_LEFT        'L'
#define CMD_HAZZARD     'H'
#define CMD_PARK        'P'
#define CMD_KRATKA      'K'
#define CMD_DUGA        'D'

nRF24L01 *setup_rf(void);
void process_message(char *message);
inline void prepare_led_pin(void);
inline void set_led_high(void);
inline void set_led_low(void);

volatile bool rf_interrupt = false;

static FILE mystdout = FDEV_SETUP_STREAM(USART_Transmit, NULL,
                                         _FDEV_SETUP_WRITE);


int main(void)
{
    char cmd = 0;
    uint8_t address[5] = {0x01, 0x01, 0x01, 0x01, 0x01};
    prepare_led_pin();
    sei();
    nRF24L01 *rf = setup_rf();
    nRF24L01_listen(rf, 0, address);
    uint8_t addr[5];
    nRF24L01_read_register(rf, CONFIG, addr, 1);
    USART_Init(9600);
    stdout = &mystdout;

    printf("Starting RX Module\r\n");

    while (true)
    {
        if (rf_interrupt)
        {
            rf_interrupt = false;
            while (nRF24L01_data_received(rf))
            {
                nRF24L01Message msg;
                nRF24L01_read_received_data(rf, &msg);
                process_message((char *)msg.data);
            }

            nRF24L01_listen(rf, 0, address);
        }
    }

    return 0;
}

nRF24L01 *setup_rf(void)
{
    nRF24L01 *rf = nRF24L01_init();
    rf->ss.port = &PORTB;
    rf->ss.pin = PB2;
    rf->ce.port = &PORTB;
    rf->ce.pin = PB1;
    rf->sck.port = &PORTB;
    rf->sck.pin = PB5;
    rf->mosi.port = &PORTB;
    rf->mosi.pin = PB3;
    rf->miso.port = &PORTB;
    rf->miso.pin = PB4;
    // interrupt on falling edge of INT0 (PD2)
    EICRA |= _BV(ISC01);
    EIMSK |= _BV(INT0);
    nRF24L01_begin(rf);
    return rf;
}

void process_message(char *message)
{
    printf("%s\r\n",message);
}

inline void prepare_led_pin(void)
{
    DDRB |= _BV(PB0);
    PORTB &= ~_BV(PB0);
}

inline void set_led_high(void)
{
    PORTB |= _BV(PB0);
}

inline void set_led_low(void)
{
    PORTB &= ~_BV(PB0);
}

// nRF24L01 interrupt
ISR(INT0_vect)
{
    rf_interrupt = true;
}
