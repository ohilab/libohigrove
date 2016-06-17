/* Copyright (C) 2016 A. C. Open Hardware Ideas Lab
 *
 * Authors:
 *   Davide Bolletta
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
 * @file libohigrove/rgbstrip.h
 * @author Davide Bolletta
 * @brief 
 *
 * @link http://www.seeedstudio.com/wiki/Grove_-_LED_Strip_Driver
 */

#ifndef __OHIGROVE_RGBSTRIP_H
#define __OHIGROVE_RGBSTRIP_H

#include "ohigrove.h"

typedef struct _OhiGroveRgbStrip_Device
{
    OhiGrove_Conn connector;
    uint8_t numberDriver;

    Gpio_Pins pinData;
    Gpio_Pins pinClock;

} OhiGroveRgbStrip_Device;

void OhiGroveRgbStrip_init (OhiGroveRgbStrip_Device* dev);

void OhiGroveRgbStrip_start (OhiGroveRgbStrip_Device* dev);
void OhiGroveRgbStrip_end (OhiGroveRgbStrip_Device* dev);
void OhiGroveRgbStrip_setColor (OhiGroveRgbStrip_Device* dev, uint8_t red, uint8_t green, uint8_t blue);

#endif /* __OHIGROVE_RGBSTRIP_H */

