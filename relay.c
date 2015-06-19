/******************************************************************************
 * Copyright (C) 2014-2015 A. C. Open Hardware Ideas Lab
 * 
 * Authors:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
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
 * @file libohigrove/relay.c
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief 
 */
#include "relay.h"

void OhiGroveRelay_init (OhiGroveRelay_Device* dev)
{
    dev->pin = OhiGrove_getDigitalPin(dev->connector,OHIGROVE_PIN_NUMBER_1);

    if (dev->pin != GPIO_PINS_NONE)
    {
        Gpio_config(dev->pin,GPIO_PINS_OUTPUT);
    }
    else
    {
        return; /* TODO: RETURN ERROR */
    }
}

void OhiGroveRelay_on (OhiGroveRelay_Device* dev)
{
    Gpio_set(dev->pin);
}

void OhiGroveRelay_off (OhiGroveRelay_Device* dev)
{
    Gpio_clear(dev->pin);
}

void OhiGroveRelay_toggle (OhiGroveRelay_Device* dev)
{
    Gpio_toggle(dev->pin);
}

