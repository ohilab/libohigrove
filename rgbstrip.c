/******************************************************************************
 * Copyright (C) 2016 A. C. Open Hardware Ideas Lab
 * 
 * Authors:
 *  Davide Bolletta
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
 * @file libohigrove/rgbstrip.c
 * @author Davide Bolletta
 * @brief 
 */

#include "rgbstrip.h"

static void OhiGroveRgbStrip_clock (OhiGroveRgbStrip_Device* dev)
{
	Gpio_clear(dev->pinClock);
	OhiGrove_delay10Microsecond(2);
	Gpio_set(dev->pinClock);
	OhiGrove_delay10Microsecond(2);
}

static void OhiGroveRgbStrip_sendByte (OhiGroveRgbStrip_Device* dev, uint8_t data)
{
	uint8_t i = 0;

	for (i=0; i<8; i++)
	{
		if ((data & 0x80) != 0)
			Gpio_set(dev->pinData);
		else
			Gpio_clear(dev->pinData);

		OhiGroveRgbStrip_clock(dev);

		data <<= 1;
	}
}

void OhiGroveRgbStrip_init (OhiGroveRgbStrip_Device* dev)
{
	uint8_t i = 0;

	dev->pinClock = OhiGrove_getDigitalPin(dev->connector,OHIGROVE_PIN_NUMBER_1);
	dev->pinData = OhiGrove_getDigitalPin(dev->connector,OHIGROVE_PIN_NUMBER_2);

	if ((dev->pinClock != GPIO_PINS_NONE) && (dev->pinData != GPIO_PINS_NONE))
	{
		Gpio_config(dev->pinClock,GPIO_PINS_OUTPUT);
		Gpio_config(dev->pinData,GPIO_PINS_OUTPUT);
	}
	else
	{
		return; /* TODO: RETURN ERROR */
	}

	OhiGroveRgbStrip_start(dev);
	for(i=0; i < dev->numberDriver; ++i)
	{
		OhiGroveRgbStrip_setColor(dev,0,0,0);
	}
    OhiGroveRgbStrip_end(dev);
}

void OhiGroveRgbStrip_start (OhiGroveRgbStrip_Device* dev)
{
    // Send data frame prefix (32x "0")
    OhiGroveRgbStrip_sendByte(dev,0x00);
    OhiGroveRgbStrip_sendByte(dev,0x00);
    OhiGroveRgbStrip_sendByte(dev,0x00);
    OhiGroveRgbStrip_sendByte(dev,0x00);
}

void OhiGroveRgbStrip_end (OhiGroveRgbStrip_Device* dev)
{
    // Send data frame prefix (32x "0")
    OhiGroveRgbStrip_sendByte(dev,0x00);
    OhiGroveRgbStrip_sendByte(dev,0x00);
    OhiGroveRgbStrip_sendByte(dev,0x00);
    OhiGroveRgbStrip_sendByte(dev,0x00);
}

void OhiGroveRgbStrip_setColor (OhiGroveRgbStrip_Device* dev, uint8_t red, uint8_t green, uint8_t blue)
{
    // Start by sending a byte with the format "1 1 /B7 /B6 /G7 /G6 /R7 /R6"
    uint8_t prefix = 0b11000000;
    if ((blue & 0x80) == 0)     prefix|= 0b00100000;
    if ((blue & 0x40) == 0)     prefix|= 0b00010000;
    if ((green & 0x80) == 0)    prefix|= 0b00001000;
    if ((green & 0x40) == 0)    prefix|= 0b00000100;
    if ((red & 0x80) == 0)      prefix|= 0b00000010;
    if ((red & 0x40) == 0)      prefix|= 0b00000001;

    OhiGroveRgbStrip_sendByte(dev,prefix);

    // Now must send the 3 colors
    OhiGroveRgbStrip_sendByte(dev,blue);
    OhiGroveRgbStrip_sendByte(dev,green);
    OhiGroveRgbStrip_sendByte(dev,red);
}
