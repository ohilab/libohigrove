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
 * @file libohigrove/water-sensor.c
 * @author Alessio Paolucci <a.paolucci89@gmail.com>
 * @brief
 */

#include "water-sensor.h"

void OhiGroveWaterSensor_init (OhiGroveWaterSensor_Device* dev)
{
	if(dev->connectorType == WATERSENSOR_CONNTYPE_ANALOG)
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
	else if(dev->connectorType == WATERSENSOR_CONNTYPE_DIGITAL)
	{
	    dev->pin = OhiGrove_getDigitalPin(dev->connector,OHIGROVE_PIN_NUMBER_1);

	    if (dev->pin != GPIO_PINS_NONE)
	    {
	        Gpio_config(dev->pin,GPIO_PINS_INPUT);
	    }
	    else
	    {
	        return; /* TODO: RETURN ERROR */
	    }
	}
    else
    {
        return; /* TODO: add errors! */
    }

}

uint16_t OhiGroveWaterSensor_getAnalog (OhiGroveWaterSensor_Device* dev)
{
	uint16_t result;

	if(dev->connectorType == WATERSENSOR_CONNTYPE_ANALOG)
	{

		Adc_readValue(dev->device,dev->channel,&result);

		return result; //return a low value if there are water

	}
	else
	{
		return 0;
	}
}

WaterSensor_Level OhiGroveWaterSensor_getDigital (OhiGroveWaterSensor_Device* dev)
{
	WaterSensor_Level result;

	if(dev->connectorType == WATERSENSOR_CONNTYPE_DIGITAL)
	{

		return Gpio_get(dev->pin); //if there are water return GPIO_LOW

	}
	else
	{
		return WATERSENSOR_ERROR; //if return GPIO_TOGGLE, it means that there are an error
	}
}

