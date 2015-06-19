/* Copyright (C) 2015 A. C. Open Hardware Ideas Lab
 *
 * Authors:
 *   Marco Giammarini <m.giammarini@warcomeb.it>
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
 * @file libohigrove/rgbled.h
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief 
 *
 * @link http://www.seeedstudio.com/wiki/Grove_-_Chainable_RGB_LED
 */

#ifndef __OHIGROVE_RGBLED_H
#define __OHIGROVE_RGBLED_H

#include "ohigrove.h"

typedef struct _OhiGroveRgbLed_Device
{
    OhiGrove_Conn connector;
    uint8_t numberLeds;

    Gpio_Pins pinData;
    Gpio_Pins pinClock;

} OhiGroveRgbLed_Device;

void OhiGroveRgbLed_init        (OhiGroveRgbLed_Device* dev);

void OhiGroveRgbLed_setRGBColor (OhiGroveRgbLed_Device* dev, uint8_t led, uint8_t red, uint8_t green, uint8_t blue);

#endif /* __OHIGROVE_RGBLED_H */

