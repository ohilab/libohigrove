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

#include "humidity-sensor.h"

/**< we hope a 1us of basetime */
#define OHIGROVE_HUMIDITYSENSOR_BASETIME  1000000

static uint16_t OhiGroveHumiditySensor_decisionLevel = 0;

static uint16_t tempCont = 0;

void OhiGroveHumiditySensor_init (OhiGroveHumiditySensor_Device* dev)
{
    dev->pin = OhiGrove_getDigitalPin(dev->connector,OHIGROVE_PIN_NUMBER_1);
    dev->ftmPin = OhiGrove_getFtmPin(dev->connector);
    
    if ((dev->pin != GPIO_PINS_NONE) && (dev->ftmPin != FTM_PINS_STOP))
    {
        dev->device = OhiGrove_getFtmDevice(dev->connector);
        dev->channel = OhiGrove_getFtmChannel(dev->connector);

        OhiGrove_ftmEnable(dev->connector,FTM_MODE_INPUT_CAPTURE,OHIGROVE_HUMIDITYSENSOR_BASETIME);
        Ftm_stopCount(dev->device);
        Ftm_resetCounter(dev->device);

        OhiGrove_enableFtmChannel(dev->connector,OhiGroveHumiditySensor_isr,dev);

        OhiGroveHumiditySensor_decisionLevel = Clock_getFrequency(CLOCK_SYSTEM)/OHIGROVE_HUMIDITYSENSOR_BASETIME;

        if (OhiGroveHumiditySensor_decisionLevel > 64)
            OhiGroveHumiditySensor_decisionLevel = 128;
        else if (OhiGroveHumiditySensor_decisionLevel > 32)
            OhiGroveHumiditySensor_decisionLevel = 64;
        else if (OhiGroveHumiditySensor_decisionLevel > 16)
            OhiGroveHumiditySensor_decisionLevel = 32;
        else if (OhiGroveHumiditySensor_decisionLevel > 8)
            OhiGroveHumiditySensor_decisionLevel = 16;
        else if (OhiGroveHumiditySensor_decisionLevel > 4)
            OhiGroveHumiditySensor_decisionLevel = 8;
        else if (OhiGroveHumiditySensor_decisionLevel > 2)
            OhiGroveHumiditySensor_decisionLevel = 4;
        else if (OhiGroveHumiditySensor_decisionLevel > 1)
            OhiGroveHumiditySensor_decisionLevel = 2;
        else
            OhiGroveHumiditySensor_decisionLevel = 1;
    }
    else
    {
    	return; /* TODO: add errors! */
    }
}

void OhiGroveHumiditySensor_doMeasure (OhiGroveHumiditySensor_Device* dev)
{
    uint8_t i;

    /* disable timer */
    Ftm_disableChannelInterrupt(dev->device,dev->channel);
    dev->bitCounted = 0;

    dev->data1 = 0;
    dev->data2 = 0;

    Gpio_config(dev->pin,GPIO_PINS_OUTPUT);
    Gpio_clear(dev->pin);
    OhiGrove_delay(20);
    Gpio_set(dev->pin);

    Ftm_addInputCapturePin(dev->device,dev->ftmPin,FTM_CONFIG_INPUT_FALLING_EDGE);

    Ftm_enableChannelInterrupt(dev->device,dev->channel);
    OhiGrove_delay10Microsecond(2);

    while (dev->bitCounted < 41);

    Ftm_disableChannelInterrupt(dev->device,dev->channel);
    Gpio_config(dev->pin,GPIO_PINS_OUTPUT);

    for (i = 1; i < 17; ++i)
    {
        dev->data1 <<= 1;
        if ((dev->countValue[i] - dev->countValue[i-1]) > OhiGroveHumiditySensor_decisionLevel)
            dev->data1 |= 1;
    }

    for (i = 17; i < 33; ++i)
    {
        dev->data2 <<= 1;
        if ((dev->countValue[i] - dev->countValue[i-1]) > OhiGroveHumiditySensor_decisionLevel)
            dev->data2 |= 1;
    }
}

void OhiGroveHumiditySensor_isr (OhiGroveHumiditySensor_Device* dev)
{
    dev->countValue[dev->bitCounted++] = Ftm_getChannelCount(dev->device,dev->channel);
}

uint16_t OhiGroveHumiditySensor_getTemperature (OhiGroveHumiditySensor_Device* dev)
{
    return dev->data2;
}

uint16_t OhiGroveHumiditySensor_getHumidity (OhiGroveHumiditySensor_Device* dev)
{
    return dev->data1;
}

