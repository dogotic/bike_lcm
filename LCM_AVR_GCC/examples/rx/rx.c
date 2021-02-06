#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include "nrf24l01.h"
#include "nrf24l01-mnemonics.h"
#include "uart.h"
#include "ws2812b.h"
#include "timer.h"

#define CMD_RIGHT       'R'
#define CMD_LEFT        'L'
#define CMD_HAZZARD     'H'
#define CMD_PARK        'P'
#define CMD_KRATKA      'K'
#define CMD_DUGA        'D'

#define TCNT1_VAL 47500

typedef enum 
{
  NONE=0,
  LEFT=1,
  RIGHT=2,
  HAZZARD=3
} direction_t;

// global variable to count the number of overflows
volatile int8_t pixel_number = 0;
volatile color_t color = {0,0,0};
 
volatile direction_t direction = NONE;

volatile uint8_t sequence_left[]  	= {2,1,0};
volatile uint8_t sequence_right[] 	= {4,5,6};

nRF24L01 *setup_rf(void);
void process_message(char *message);

volatile bool rf_interrupt = false;

static FILE mystdout = FDEV_SETUP_STREAM(USART_Transmit, NULL,
                                         _FDEV_SETUP_WRITE);


int main(void)
{
    uint8_t address[5] = {0x01, 0x01, 0x01, 0x01, 0x01};
    int i;
    uint8_t addr[5];

    USART_Init(9600);
    stdout = &mystdout;

    printf("Starting RX Module\r\n");

    WS2812B_Init(7);

    for (i=0; i<7; i++)
    {
        WS2812B_SetPixel(i,color);
    }

    color.red = 0xFF;
    color.green = 0x01;
    color.blue = 0x00;

    TIMER_Init(TCNT1_VAL);

    direction = NONE;

    sei();
    nRF24L01 *rf = setup_rf();
    nRF24L01_listen(rf, 0, address);
    nRF24L01_read_register(rf, CONFIG, addr, 1);

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
    char input = message[0];
    if (input == 'R')
    {
      cli();
      /* clear all leds */
      WS2812B_ClearAll();
      pixel_number = 0;      
      sei(); 

      if (direction != RIGHT)
      {
        direction = RIGHT;
      }
      else
      {
        direction = NONE;
      }

    }
    else if(input == 'L')
    {
      cli();
      /* clear all leds */
      WS2812B_ClearAll();  
      pixel_number = 0;      
      sei(); 

      if (direction != LEFT)
      {
        direction = LEFT;
      }
      else
      {
        direction = NONE;
      }

    }
    else if(input == 'H')
    {
      /* clear all leds */
      cli();
      WS2812B_ClearAll(); 
      pixel_number = 0;
      sei();       

      if (direction != HAZZARD)
      {
        direction = HAZZARD;
      }
      else
      {
        direction = NONE;
      }
    }
}

// nRF24L01 interrupt
ISR(INT0_vect)
{
    rf_interrupt = true;
}

// TIMER1 overflow interrupt service routine
// called whenever TCNT1 overflows
ISR(TIMER1_OVF_vect)
{
  TCNT1 = TCNT1_VAL;
  if (direction == LEFT)
  {
    WS2812B_SetPixel(3, color);
    WS2812B_SetPixel(sequence_left[pixel_number], color);
  }
  else if(direction == RIGHT)
  {
    WS2812B_SetPixel(3, color);    
    WS2812B_SetPixel(sequence_right[pixel_number], color);
  }
  else if (direction == HAZZARD)
  {
    WS2812B_SetPixel(3, color);
    WS2812B_SetPixel(sequence_right[pixel_number], color);
    WS2812B_SetPixel(sequence_left[pixel_number], color);
  }

  if (pixel_number < 3) 
  {
    pixel_number++;
  }
  else
  {
    pixel_number = 0;      
    WS2812B_ClearAll();
  }
}