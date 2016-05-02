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
 * @file libohigrove/thumb-joystick.c
 * @author Alessio Paolucci <a.paolucci89@gmail.com>
 * @brief
 */

#include "thumb-joystick.h"

void OhiGroveThumbJoystick_init (OhiGroveThumbJoystick_Device* dev)
{
    dev->pin1 = OhiGrove_getAnalogPin(dev->connector,OHIGROVE_PIN_NUMBER_1);
    dev->pin2 = OhiGrove_getAnalogPin(dev->connector,OHIGROVE_PIN_NUMBER_2);

    if (dev->pin1 != ADC_PINS_NONE)
    {
    	dev->device1 = OhiGrove_getAnalogDevice(dev->connector,OHIGROVE_PIN_NUMBER_1);
    	dev->channel1 = OhiGrove_getAnalogChannel(dev->connector,OHIGROVE_PIN_NUMBER_1);

        Adc_enablePin(dev->device1,dev->pin1);
    }
    else
    {
    	return; /* TODO: add errors! */
    }

    if (dev->pin2 != ADC_PINS_NONE)
    {
    	dev->device2 = OhiGrove_getAnalogDevice(dev->connector,OHIGROVE_PIN_NUMBER_2);
    	dev->channel2 = OhiGrove_getAnalogChannel(dev->connector,OHIGROVE_PIN_NUMBER_2);

        Adc_enablePin(dev->device2,dev->pin2);
    }
    else
    {
    	return; /* TODO: add errors! */
    }
}

void OhiGroveThumbJoystick_get (OhiGroveThumbJoystick_Device* dev, uint16_t *x, uint16_t *y, bool *click)
{
    uint16_t result_x = 0;
    uint16_t result_y = 0;
    bool result_click = 0;

    Adc_readValue(dev->device1,dev->channel1,&result_x,ADC_INPUTTYPE_SINGLE_ENDED);
    Adc_readValue(dev->device2,dev->channel2,&result_y,ADC_INPUTTYPE_SINGLE_ENDED);

    *x = result_x;
    *y = result_y;

    if(result_x > 4090)
    {
    	result_click = 1;
    }
    else
    {
    	result_click = 0;
    }

    *click = result_click;

    return;
}



