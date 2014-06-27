/******************************************************************************
 * Copyright (C) 2014 A. C. Open Hardware Ideas Lab
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
        OhiGrove_enableConnector(dev->connector,
                                 OHIGROVE_PIN_TYPE_PWM,
                                 OHIGROVE_PIN_TYPE_NONE);
//        dev->ftmPin = OhiGrove_getPwmPin(dev->connector,OHIGROVE_PIN_NUMBER_1);
        dev->ftmChannel = OhiGrove_getPwmChannel(dev->connector,OHIGROVE_PIN_NUMBER_1);
        dev->ftmDevice  = OhiGrove_getPwmDevice(dev->connector,OHIGROVE_PIN_NUMBER_1);
    }
    else
    {
        OhiGrove_enableConnector(dev->connector,
                                 OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT,
                                 OHIGROVE_PIN_TYPE_NONE);
        dev->pin = OhiGrove_getDigitalPin(dev->connector,OHIGROVE_PIN_NUMBER_1);        
    }
}

void OhiGroveLed_on (OhiGroveLed_Device* dev)
{
    if (dev->type == OHIGROVELED_TYPE_DIMMED)
    {
        Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,(dev->dutyCycle / 100.0) * 32768);
        dev->status = GPIO_HIGH;
    }
    else
    {
        OhiGrove_setDigital(dev->pin,GPIO_HIGH);
    }
}

void OhiGroveLed_off (OhiGroveLed_Device* dev)
{
    if (dev->type == OHIGROVELED_TYPE_DIMMED)
    {
        Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,1);
        dev->status = GPIO_LOW;
    }
    else
    {
        OhiGrove_setDigital(dev->pin,GPIO_LOW);    
    }
}

void OhiGroveLed_toggle (OhiGroveLed_Device* dev)
{
    if (dev->type == OHIGROVELED_TYPE_DIMMED)
    {
        if (dev->status == GPIO_HIGH)
        {
            Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,1);
            dev->status = GPIO_LOW;
        }
        else
        {
            Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,(dev->dutyCycle / 100.0) * 32768);
            dev->status = GPIO_HIGH;
        }
    }
    else
    {
        OhiGrove_setDigital(dev->pin,GPIO_TOGGLE);    
    }
}

void OhiGroveLed_setDuty(OhiGroveLed_Device* dev, uint8_t duty)
{
    if (duty > 100)
        dev->dutyCycle = 100;
    else
        dev->dutyCycle = duty;
        
    Ftm_setPwm(dev->ftmDevice,dev->ftmChannel,(dev->dutyCycle / 100.0) * 32768);
}
