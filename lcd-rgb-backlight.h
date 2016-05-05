/******************************************************************************
 * Copyright (C) 2016 A. C. Open Hardware Ideas Lab
 *
 * Authors:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
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
 ******************************************************************************/

/**
 * @file libohigrove/lcd-rgb-backlight.h
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief
 */

#ifndef __LED_RGB_BACKLIGHT_H
#define __LED_RGB_BACKLIGHT_H

#include "ohigrove.h"

typedef struct _OhiGroveLcdRgbB_Device
{
    OhiGrove_Conn connector;

    uint8_t cols;
    uint8_t lines;

    uint8_t display;
    uint8_t mode;
    uint8_t function;

    Iic_DeviceHandle device;

    uint32_t baudrate;

} OhiGroveLcdRgbB_Device;

void OhiGroveLcdRgbB_init(OhiGroveLcdRgbB_Device* dev);

void OhiGroveLcdRgbB_write (OhiGroveLcdRgbB_Device* dev, uint8_t ch);

void OhiGroveLcdRgbB_displayOn (OhiGroveLcdRgbB_Device* dev);
void OhiGroveLcdRgbB_displayOff (OhiGroveLcdRgbB_Device* dev);

void OhiGroveLcdRgbB_cursorOn (OhiGroveLcdRgbB_Device* dev);
void OhiGroveLcdRgbB_cursorOff (OhiGroveLcdRgbB_Device* dev);

void OhiGroveLcdRgbB_blinkOn (OhiGroveLcdRgbB_Device* dev);
void OhiGroveLcdRgbB_blinkOff (OhiGroveLcdRgbB_Device* dev);

void OhiGroveLcdRgbB_scrollDisplayLeft (OhiGroveLcdRgbB_Device* dev);
void OhiGroveLcdRgbB_scrollDisplayRight (OhiGroveLcdRgbB_Device* dev);

void OhiGroveLcdRgbB_leftToRight (OhiGroveLcdRgbB_Device* dev);
void OhiGroveLcdRgbB_rightToLeft (OhiGroveLcdRgbB_Device* dev);

void OhiGroveLcdRgbB_autoscrollOn (OhiGroveLcdRgbB_Device* dev);
void OhiGroveLcdRgbB_autoscrollOff (OhiGroveLcdRgbB_Device* dev);

void OhiGroveLcdRgbB_clear (OhiGroveLcdRgbB_Device* dev);
void OhiGroveLcdRgbB_home (OhiGroveLcdRgbB_Device* dev);
void OhiGroveLcdRgbB_setCursor (OhiGroveLcdRgbB_Device* dev, uint8_t column, uint8_t row);

void OhiGroveLcdRgbB_setColor (OhiGroveLcdRgbB_Device* dev, uint8_t red, uint8_t green, uint8_t blue);

void OhiGroveLcdRgbB_blinkLedOn (OhiGroveLcdRgbB_Device* dev);
void OhiGroveLcdRgbB_blinkLedOff (OhiGroveLcdRgbB_Device* dev);

/**
 * This function allow to fill the first 8 CGRAM locations with customs
 * characters.
 *
 * @param[in] dev The handler to LCD device
 * @param[in] location The location where store the new char, must be 0 to 7
 * @param[in] charmap The array of single pixel description of char
 */
void OhiGroveLcdRgbB_createChar (OhiGroveLcdRgbB_Device* dev, uint8_t location, uint8_t charmap[]);


#endif /* __LED_RGB_BACKLIGHT_H */
