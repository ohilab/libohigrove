/******************************************************************************
 * Copyright (C) 2015 A. C. Open Hardware Ideas Lab
 * 
 * Authors:
 *  Simone Giacomucci <simone.giacomucci@gmail.com>
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
 * @file libohigrove/humidity-sensor.h
 * @author Simone Giacomucci <simone.giacomucci@gmail.com>
 * @brief 
 */

#ifndef __HUMIDITY_SENSOR_H
#define __HUMIDITY_SENSOR_H

#include "ohigrove.h"

typedef struct _OhiGroveHumiditySensor_Device
{
    OhiGrove_Conn connector;

    Gpio_Pins pin;

    Ftm_Pins ftmPin;
    Ftm_Channels channel;
    Ftm_DeviceHandle device;

} OhiGroveHumiditySensor_Device;

void OhiGroveHumiditySensor_init (OhiGroveHumiditySensor_Device* dev);

void OhiGroveHumiditySensor_doMeasure (OhiGroveHumiditySensor_Device* dev);

uint16_t OhiGroveHumiditySensor_getTemperature (OhiGroveHumiditySensor_Device* dev);
uint16_t OhiGroveHumiditySensor_getHumidity (OhiGroveHumiditySensor_Device* dev);

#endif /* __HUMIDITY_SENSOR_H */
