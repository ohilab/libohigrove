/******************************************************************************
 * Copyright (C) 2015 A. C. Open Hardware Ideas Lab
 *
 * Authors:
 *  Alessio Paolucci <a.paolucci89@gmail.com>
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
 * @file libohigrove/thumb-joystick.h
 * @author Alessio Paolucci <a.paolucci89@gmail.com>
 * @brief
 */

#ifndef THUMB_JOYSTICK_H_
#define THUMB_JOYSTICK_H_

#include "ohigrove.h"

typedef struct _OhiGroveThumbJoystick_Device
{
    OhiGrove_Conn connector;

    Adc_Pins pin1;
    Adc_Pins pin2;
    Adc_ChannelNumber channel1;
    Adc_ChannelNumber channel2;
    Adc_DeviceHandle device1;
    Adc_DeviceHandle device2;

} OhiGroveThumbJoystick_Device;

void OhiGroveThumbJoystick_init (OhiGroveThumbJoystick_Device* dev);

void OhiGroveThumbJoystick_get (OhiGroveThumbJoystick_Device* dev, uint16_t *x, uint16_t *y, bool *click);

#endif /* THUMB_JOYSTICK_H_ */
