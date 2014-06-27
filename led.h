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
 * @file libohigrove/led.h
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief 
 */

#ifndef __LED_H
#define __LED_H

#include "ohigrove.h"

typedef enum
{
    OHIGROVELED_TYPE_FIXED,
    OHIGROVELED_TYPE_DIMMED,
} OhiGroveLed_Type;

typedef struct _OhiGroveLed_Device
{
    OhiGrove_Conn connector;
    
    Gpio_Pins pin;

    Gpio_Level status;
    
    Ftm_Pins ftmPin;
    Ftm_Channels ftmChannel;
    Ftm_DeviceHandle ftmDevice;
    
    OhiGroveLed_Type type;
    uint8_t dutyCycle;  /* 0 to 100 */

} OhiGroveLed_Device;

void OhiGroveLed_init (OhiGroveLed_Device* dev);

void OhiGroveLed_on     (OhiGroveLed_Device* dev);
void OhiGroveLed_off    (OhiGroveLed_Device* dev);
void OhiGroveLed_toggle (OhiGroveLed_Device* dev);

void OhiGroveLed_setDuty(OhiGroveLed_Device* dev, uint8_t duty);


#endif /* __BUZZER_H */
