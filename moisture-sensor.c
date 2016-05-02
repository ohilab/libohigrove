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
 * @file libohigrove/moisture-sensor.c
 * @author Alessio Paolucci <a.paolucci89@gmail.com>
 * @brief
 */

#include "moisture-sensor.h"

void OhiGroveMoistureSensor_init (OhiGroveMoistureSensor_Device* dev)
{
    dev->pin = OhiGrove_getAnalogPin(dev->connector,OHIGROVE_PIN_NUMBER_1);

    if (dev->pin != ADC_PINS_NONE)
    {
    	dev->device = OhiGrove_getAnalogDevice(dev->connector,OHIGROVE_PIN_NUMBER_1);
    	dev->channel = OhiGrove_getAnalogChannel(dev->connector,OHIGROVE_PIN_NUMBER_1);

        Adc_enablePin(dev->device,dev->pin);
    }
    else
    {
    	return; /* TODO: add errors! */
    }
}

uint16_t OhiGroveMoistureSensor_get (OhiGroveMoistureSensor_Device* dev)
{
    uint16_t result;

    Adc_readValue(dev->device,dev->channel,&result,ADC_INPUTTYPE_SINGLE_ENDED);
    return result;
}
