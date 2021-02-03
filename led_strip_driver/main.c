#include <avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>

#include "ws2812b.h"
#include "timer.h"
#include "uart.h"

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
 

int main(void)
{
  int i;
  char input;

  WS2812B_Init(7);

  for (i=0; i<7; i++)
  {
    WS2812B_SetPixel(i,color);
  }

  color.red = 0xFF;
  color.green = 0x01;
  color.blue = 0x00;

  USART_Init(9600);
  USART_Puts("WS2812B Test Bench\r\n");

  TIMER_Init(TCNT1_VAL);

  direction = NONE;

  while (1)
  {
    input = USART_Receive();
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

  return 0;
}