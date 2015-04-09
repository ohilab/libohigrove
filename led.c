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
 * @file libohigrove/led.c
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief 
 */

#include "led.h"

void OhiGroveLed_init (OhiGroveLed_Device* dev)
{
    if (dev->type == OHIGROVELED_TYPE_DIMMED)
    {
//        OhiGrove_enableConnector(dev->connector,
//                                 OHIGROVE_PIN_TYPE_PWM,
//                                 OHIGROVE_PIN_TYPE_NONE);
//        dev->ftmChannel = OhiGrove_getPwmChannel(dev->connector,OHIGROVE_PIN_NUMBER_1);
//        dev->ftmDevice  = OhiGrove_getPwmDevice(dev->connector,OHIGROVE_PIN_NUMBER_1);
    }
    else
    {
        dev->pin = OhiGrove_getDigitalPin(dev->connector);

        if (dev->pin != GPIO_PINS_NONE)
        {
            Gpio_config(dev->pin,GPIO_PINS_OUTPUT);
        }
        else
        {
            return; /* TODO: RETURN ERROR */
        }
    }
}


void OhiGroveLed_on (OhiGroveLed_Device* dev)
{
    if (dev->type == OHIGROVELED_TYPE_DIMMED)
    {
//        Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,(dev->dutyCycle / 100.0) * 32768);
//        dev->status = GPIO_HIGH;
    }
    else
    {
        Gpio_set(dev->pin);
    }
}

void OhiGroveLed_off (OhiGroveLed_Device* dev)
{
    if (dev->type == OHIGROVELED_TYPE_DIMMED)
    {
//        Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,1);
//        dev->status = GPIO_LOW;
    }
    else
    {
        Gpio_clear(dev->pin);
    }
}

void OhiGroveLed_toggle (OhiGroveLed_Device* dev)
{
    if (dev->type == OHIGROVELED_TYPE_DIMMED)
    {
//        if (dev->status == GPIO_HIGH)
//        {
//            Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,1);
//            dev->status = GPIO_LOW;
//        }
//        else
//        {
//            Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,(dev->dutyCycle / 100.0) * 32768);
//            dev->status = GPIO_HIGH;
//        }
    }
    else
    {
        Gpio_toggle(dev->pin);
    }
}

void OhiGroveLed_setDuty(OhiGroveLed_Device* dev, uint8_t duty)
{
//    if (duty > 100)
//        dev->dutyCycle = 100;
//    else
//        dev->dutyCycle = duty;
//
//    Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,(dev->dutyCycle / 100.0) * 32768);
}
