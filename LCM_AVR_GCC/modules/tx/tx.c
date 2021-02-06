#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "nrf24l01.h"
#include "uart.h"

#define CMD_RIGHT       'R'
#define CMD_LEFT        'L'
#define CMD_HAZZARD     'H'
#define CMD_POZICIJA    'P'
#define CMD_KRATKA      'K'
#define CMD_DUGA        'D'

nRF24L01 *setup_rf(void);

volatile bool rf_interrupt = false;
volatile bool send_message = false;

static FILE mystdout = FDEV_SETUP_STREAM(USART_Transmit, NULL,
                                         _FDEV_SETUP_WRITE);


int main(void)
{
    uint8_t to_address[5] = {0x01, 0x01, 0x01, 0x01, 0x01};
    sei();
    nRF24L01 *rf = setup_rf();
    USART_Init(9600);
    stdout = &mystdout;
    char cmd = 0;

    printf("Starting TX Module\r\n");

    while (true)
    {
        /* check if there is a command from uart */
        char ch  = USART_Receive();
        switch(ch)
        {
            case 'L':
                cmd = CMD_LEFT;
                send_message = true;
                break;
            case 'R':
                cmd = CMD_RIGHT;
                send_message = true;                
                break;
            case 'D':
                cmd = CMD_DUGA;     
                send_message = true;                       
                break;
            case 'K':
                cmd = CMD_KRATKA;   
                send_message = true;                         
                break;                
            case 'H':
                cmd = CMD_HAZZARD;  
                send_message = true;                                      
                break;  
            case 'P':
                cmd = CMD_POZICIJA;
                send_message = true;                
                break;              
        }


        if (rf_interrupt)
        {
            rf_interrupt = false;
            int success = nRF24L01_transmit_success(rf);
            if (success != 0)
                nRF24L01_flush_transmit_message(rf);
        }

        if (send_message)
        {
            send_message = false;
            nRF24L01Message msg;
            //memcpy(msg.data, &cmd, 1);
            msg.data[0] = cmd;
            msg.length = 1;
            nRF24L01_transmit(rf, to_address, &msg);
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

// nRF24L01 interrupt
ISR(INT0_vect)
{
    rf_interrupt = true;
}
