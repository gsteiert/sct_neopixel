/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Greg Steiert
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef _SCT_NEOPIXEL_H_
#define _SCT_NEOPIXEL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

//--------------------------------------------------------------------+
// Neopixel Driver
//--------------------------------------------------------------------+
// NeoPixel Types
#define NEO_RGB  ((0<<6) | (0<<4) | (1<<2) | (2)) ///< Transmit as R,G,B
#define NEO_GRB  ((1<<6) | (1<<4) | (0<<2) | (2)) ///< Transmit as G,R,B
#define NEO_RGBW ((3<<6) | (0<<4) | (1<<2) | (2)) ///< Transmit as R,G,B,W

#define NEO_SCT           SCT0
#define NEO_MATCH_RISE    12
#define NEO_MATCH_PERIOD  13
#define NEO_MATCH_RESET   15
#define NEO_MATCH_0       0
#define NEO_MATCH_1       11
#define NEO_EVENT_RISE    12
// Use events 0-9 for channel specific events
#define NEO_EVENT_CH_0    0
#define NEO_EVENT_CH_1    1
#define NEO_EVENT_CH_2    2
#define NEO_EVENT_CH_3    3
#define NEO_EVENT_CH_4    4
#define NEO_EVENT_CH_5    5
#define NEO_EVENT_CH_6    6
#define NEO_EVENT_CH_7    7
#define NEO_EVENT_CH_8    8
#define NEO_EVENT_CH_9    9
#define NEO_EVENT_FALL_1  11
#define NEO_EVENT_NEXT    13
#define NEO_EVENT_LAST    14
#define NEO_EVENT_RESET   15
#define NEO_COUNT_RISE    1
#define NEO_COUNT_FALL0   31
#define NEO_COUNT_FALL1   61
#define NEO_COUNT_PERIOD  120
#define NEO_COUNT_RESET   8120
// State used for first bit
#define NEO_FIRST_BIT     23
#define NEO_SCT_OUTPUTS   10

/*!
  @brief  Initializes the SCTimer for driving NeoPixels
          This initializes all channels to inactive.  
          Channels must be added with sctpix_addCh
  @param  neoPixelType  Specifies the type of NeoPixel (GRB etc...)
          Only 3byte per pixels are currently implemented.
*/
void sctpix_init(uint32_t neoPixelType);

/*!
  @brief  Adds channels to the SCTimer NeoPixel configuration
  @param  ch  Specifies which channel to be used.  Channel number 
          coresponds with the SCTimer output number, which determines
          which pin the output will go to.  This does not configure 
          the pin.  The pin needs to be configured for SCTimer output 
          separately.
  @param  *data  Pointer to the data buffer to be used for this channel
          This library does not allocate buffers for channel data.  It 
          lets the application create the buffers for more flexibility.
  @param  size  The number of pixels on this channel.
*/
void sctpix_addCh(uint32_t ch, uint32_t *data, uint32_t size);

/*!
  @brief  Removes a channel from the configuration.  This allows for time 
          sharing the controller with different channel configurations.
  @param  ch  The channel to be removed
*/
void sctpix_rmCh(uint32_t ch);

/*!
  @brief  This initiates the transfer of data on all the configured channels
*/
void sctpix_show(void);

/*!
  @brief  This indicates that no transaction is active so data can be updated 
          synchronously.
*/
bool sctpix_canShow(void);

/*!
  @brief  This sets the value of the respective pixel data
  @param  ch  The channel of the pixel to be set
  @param  pixel  The pixel in the specified channel
  @param  color  The raw pixel value to be stored
*/
void sctpix_setPixel(uint32_t ch, uint32_t pixel, uint32_t color);

/*!
  @brief  This sets the value of the respective pixel data
  @param  ch  The channel of the pixel to be set
  @param  pixel  The pixel in the specified channel
  @param  r  8 bit red value to be stored
  @param  g  8 bit green value to be stored
  @param  b  8 bit blue value to be stored
*/
void sctpix_setPixelRGB(uint32_t ch, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b);

/*!
  @brief  This sets the value of the respective pixel data
  @param  ch  The channel of the pixel to be set
  @param  pixel  The pixel in the specified channel
  @param  r  8 bit red value to be stored
  @param  g  8 bit green value to be stored
  @param  b  8 bit blue value to be stored
  @param  w  8 bit blue value to be stored
*/
void sctpix_setPixelRGBW(uint32_t ch, uint32_t pixel, uint8_t r, uint8_t g, uint8_t b, uint8_t w);

/*!
  @brief  This will update the pixel type
  @param  neoPixelType  The type of NeoPixel (GRB etc...)
*/
void sctpix_updateType(uint32_t neoPixelType);


#ifdef __cplusplus
 }
#endif

#endif