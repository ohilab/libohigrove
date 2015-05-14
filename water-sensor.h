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
 * @file libohigrove/water-sensor.h
 * @author Alessio Paolucci <a.paolucci89@gmail.com>
 * @brief
 */

#ifndef WATER_SENSOR_H_
#define WATER_SENSOR_H_

#include "ohigrove.h"

typedef enum _WaterSensor_ConnType
{
	WATERSENSOR_CONNTYPE_ANALOG,
	WATERSENSOR_CONNTYPE_DIGITAL,
} WaterSensor_ConnType;

typedef struct _OhiGroveWaterSensor_Device
{
    OhiGrove_Conn connector;

    WaterSensor_ConnType connectorType;

    Adc_Pins pin;
    Adc_ChannelNumber channel;
    Adc_DeviceHandle device;

} OhiGroveWaterSensor_Device;

typedef enum
{
    WATERSENSOR_WATER = 0x00,
    WATERSENSOR_NOWATER = 0x01,
    WATERSENSOR_ERROR = 0xFF,
} WaterSensor_Level;

void OhiGroveWaterSensor_init (OhiGroveWaterSensor_Device* dev);

uint16_t OhiGroveWaterSensor_getAnalog (OhiGroveWaterSensor_Device* dev);

WaterSensor_Level OhiGroveWaterSensor_getDigital (OhiGroveWaterSensor_Device* dev);



#endif /* WATER_SENSOR_H_ */
