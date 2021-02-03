/**
 * @file ws2812b.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef WS2812B_H
#define WS2812B_H

/**
 * @brief 
 * 
 */
typedef struct __color_t
{
  uint8_t red;              ///<
  uint8_t green;            ///<
  uint8_t blue;             ///<
} color_t;

/**
 * @brief 
 * 
 * @param number_of_leds 
 */
void WS2812B_Init(uint8_t number_of_leds);

/**
 * @brief 
 * 
 */
void WS2812B_Reset(void);

/**
 * @brief 
 * 
 */
void WS2812B_ClearAll(void);

/**
 * @brief 
 * 
 * @param position 
 * @param color 
 */
void WS2812B_SetPixel(uint8_t position, color_t color);

#endif // WS2812B_H