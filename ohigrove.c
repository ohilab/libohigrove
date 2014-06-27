/******************************************************************************
 * Copyright (C) 2014 A. C. Open Hardware Ideas Lab
 * 
 * Authors:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 *  Marco Contigiani <marco.contigiani86@gmail.com>
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
 * @file libohigrove/ohigrove.h
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @author Marco Contigiani <marco.contigiani86@gmail.com>
 * @brief 
 */

#include "ohigrove.h"

static Ftm_Config OhiGrove_highFrequency = 
{
    .mode              = FTM_MODE_PWM,

    .timerFrequency    = 1000,
    .initCounter       = 0,

    .pins              = {FTM_PINS_STOP},
//    .duty              = {0.3 * 32768},
    
    .configurationBits = FTM_CONFIG_PWM_EDGE_ALIGNED | FTM_CONFIG_PWM_POLARITY_LOW | 0,
};

static Ftm_Config OhiGrove_lowFrequency = 
{
    .mode              = FTM_MODE_PWM,

    .timerFrequency    = 500,
    .initCounter       = 0,

    .pins              = {FTM_PINS_STOP},
    
    .configurationBits = FTM_CONFIG_PWM_EDGE_ALIGNED | FTM_CONFIG_PWM_POLARITY_LOW | 0,
};

static Ftm_Config OhiGrove_baseTimer = 
{
    .mode              = FTM_MODE_FREE,

    .timerFrequency    = 1000,
    .initCounter       = 0,
};

static uint32_t OhiGrove_milliseconds = 0;
static void OhiGrove_baseTimerInterrupt (void)
{
    OhiGrove_milliseconds++;
}

void OhiGrove_delay (uint32_t msDelay)
{
    uint32_t currTicks = OhiGrove_milliseconds;

    while ((OhiGrove_milliseconds - currTicks) < msDelay);
}

void OhiGrove_initBoard (OhiGrove_Board board)
{
    switch (board)
    {
    case OHIGROVE_BOARD_FRDMKL25:
        /* Enable clock gate for ports to enable pin routing */
        SIM_SCGC5 |= (
                SIM_SCGC5_PORTA_MASK | 
                SIM_SCGC5_PORTB_MASK | 
                SIM_SCGC5_PORTC_MASK | 
                SIM_SCGC5_PORTD_MASK | 
                SIM_SCGC5_PORTE_MASK);

        Ftm_init(FTM0,0,&OhiGrove_highFrequency);
        Ftm_init(FTM1,0,&OhiGrove_lowFrequency);
        Ftm_init(FTM2,OhiGrove_baseTimerInterrupt,&OhiGrove_baseTimer);
        OhiGrove_milliseconds = 0;
        break;
    case OHIGROVE_BOARD_TOPPING_R0:
        
        break;
    default:
        /* Nothing to do! */
        break;
    }
}

void OhiGrove_enableConnector (OhiGrove_Conn conn, 
                               OhiGrove_PinType typePin1, 
                               OhiGrove_PinType typePin2)
{
#if defined (FRDMKL25Z)
    
    switch (conn)
    {
    case OHIGROVE_CONN_D2:
        
        if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTD4,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTD4,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTD4,1);
        }
        
        if (typePin2 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTA12,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTA12,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM1,FTM_PINS_PTA12,1);
        }
        
        break;
    case OHIGROVE_CONN_D3:
        
        if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTA12,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTA12,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM1,FTM_PINS_PTA12,1);
        }
        
        if (typePin2 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTA4,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTA4,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTA4,1);
        }
        
        break;
    case OHIGROVE_CONN_D4:
        
        if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTA4,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTA4,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTA4,1);
        }
        
        if (typePin2 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTA5,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTA5,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTA5,1);
        }
        
        break;
    case OHIGROVE_CONN_D5:
        
        if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTA5,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTA5,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTA5,1);
        }
        
        if (typePin2 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTC8,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTC8,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTC8,1);
        }
        
        break;
    case OHIGROVE_CONN_D6:
        
        if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTC8,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTC8,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTC8,1);
        }
        
        if (typePin2 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTC9,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTC9,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTC9,1);
        }
        
        break;
    case OHIGROVE_CONN_D7:
        
        if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTC9,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTC9,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTC9,1);
        }
        
        if (typePin2 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTA13,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTA13,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM1,FTM_PINS_PTA13,1);
        }
        
        break;
    case OHIGROVE_CONN_D8:
        
        if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTA13,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTA13,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM1,FTM_PINS_PTA13,1);
        }
        
        if (typePin2 == OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT)
        {
            Gpio_config(GPIO_PINS_PTD5,GPIO_PINS_OUTPUT);
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_DIGITAL_INPUT)
        {
            Gpio_config(GPIO_PINS_PTD5,GPIO_PINS_INPUT);            
        }
        else if (typePin1 == OHIGROVE_PIN_TYPE_PWM)
        {
            Ftm_addPwmPin(FTM0,FTM_PINS_PTD5,1);
        }
        
        break;
    default:
        /* Nothing to do! */
        break;
    }
    
#elif defined (OHIBOARD_R1) && defined (GROVETOPPING_R0)

    switch (conn)
    {
    case OHIGROVE_CONN_D2:
        
        break;
    default:
        /* Nothing to do! */
        break;
    }

#endif
}

Gpio_Pins OhiGrove_getDigitalPin (OhiGrove_Conn conn,
                                  OhiGrove_PinNumber number)
{
    Gpio_Pins pin = GPIO_PINS_NONE;
    
#if defined (FRDMKL25Z)
    
    switch (conn)
    {
    case OHIGROVE_CONN_D2:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = GPIO_PINS_PTD4;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = GPIO_PINS_PTA12;

        break;
    case OHIGROVE_CONN_D3:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = GPIO_PINS_PTA12;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = GPIO_PINS_PTA4;

        break;
    case OHIGROVE_CONN_D4:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = GPIO_PINS_PTA4;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = GPIO_PINS_PTA5;
        
        break;
    case OHIGROVE_CONN_D5:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = GPIO_PINS_PTA5;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = GPIO_PINS_PTC8;

        break;
    case OHIGROVE_CONN_D6:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = GPIO_PINS_PTC8;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = GPIO_PINS_PTC9;

        break;
    case OHIGROVE_CONN_D7:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = GPIO_PINS_PTC9;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = GPIO_PINS_PTA13;

        break;
    case OHIGROVE_CONN_D8:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = GPIO_PINS_PTA13;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = GPIO_PINS_PTD5;
        
        break;
    default:
        /* Nothing to do! */
        break;
    }
    
#elif defined (OHIBOARD_R1) && defined (GROVETOPPING_R0)


#endif
    
    return pin;
}

void OhiGrove_setDigital (Gpio_Pins pin, Gpio_Level level)
{
    if (pin != GPIO_PINS_NONE)
    {
        if (level == GPIO_HIGH)
            Gpio_set(pin);
        else if (level == GPIO_TOGGLE)
            Gpio_toggle(pin);
        else
            Gpio_clear(pin);
    }
}

Gpio_Level OhiGrove_getDigital (Gpio_Pins pin)
{    
    if (pin != GPIO_PINS_NONE)
        return Gpio_get(pin);
    else
        return 0;
}

Ftm_Pins OhiGrove_getPwmPin (OhiGrove_Conn conn,
                             OhiGrove_PinNumber number)
{
    Ftm_Pins pin = FTM_PINS_STOP;
    
#if defined (FRDMKL25Z)
    
    switch (conn)
    {
    case OHIGROVE_CONN_D2:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = FTM_PINS_PTD4;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = FTM_PINS_PTA12;

        break;
    case OHIGROVE_CONN_D3:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = FTM_PINS_PTA12;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = FTM_PINS_PTA4;

        break;
    case OHIGROVE_CONN_D4:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = FTM_PINS_PTA4;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = FTM_PINS_PTA5;
        
        break;
    case OHIGROVE_CONN_D5:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = FTM_PINS_PTA5;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = FTM_PINS_PTC8;

        break;
    case OHIGROVE_CONN_D6:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = FTM_PINS_PTC8;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = FTM_PINS_PTC9;

        break;
    case OHIGROVE_CONN_D7:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = FTM_PINS_PTC9;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = FTM_PINS_PTA13;

        break;
    case OHIGROVE_CONN_D8:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            pin = FTM_PINS_PTA13;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            pin = FTM_PINS_PTD5;
        
        break;
    default:
        /* Nothing to do! */
        break;
    }
    
#elif defined (OHIBOARD_R1) && defined (GROVETOPPING_R0)


#endif
    
    return pin;
}

Ftm_Channels OhiGrove_getPwmChannel (OhiGrove_Conn conn,
                                     OhiGrove_PinNumber number)
{
    Ftm_Channels channel;
    
#if defined (FRDMKL25Z)
    
    switch (conn)
    {
    case OHIGROVE_CONN_D2:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            channel = FTM_CHANNELS_CH4;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            channel = FTM_CHANNELS_CH0;

        break;
    case OHIGROVE_CONN_D3:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            channel = FTM_CHANNELS_CH0;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            channel = FTM_CHANNELS_CH1;

        break;
    case OHIGROVE_CONN_D4:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            channel = FTM_CHANNELS_CH1;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            channel = FTM_CHANNELS_CH2;
        
        break;
    case OHIGROVE_CONN_D5:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            channel = FTM_CHANNELS_CH2;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            channel = FTM_CHANNELS_CH4;

        break;
    case OHIGROVE_CONN_D6:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            channel = FTM_CHANNELS_CH4;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            channel = FTM_CHANNELS_CH5;

        break;
    case OHIGROVE_CONN_D7:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            channel = FTM_CHANNELS_CH5;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            channel = FTM_CHANNELS_CH1;

        break;
    case OHIGROVE_CONN_D8:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            channel = FTM_CHANNELS_CH1;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            channel = FTM_CHANNELS_CH5;
        
        break;
    default:
        /* Nothing to do! */
        break;
    }
    
#elif defined (OHIBOARD_R1) && defined (GROVETOPPING_R0)


#endif
    
    return channel;
}

Ftm_DeviceHandle OhiGrove_getPwmDevice (OhiGrove_Conn conn,
                                        OhiGrove_PinNumber number)
{
    Ftm_DeviceHandle dev;
    
#if defined (FRDMKL25Z)
    
    switch (conn)
    {
    case OHIGROVE_CONN_D2:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            dev = FTM0;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            dev = FTM1;

        break;
    case OHIGROVE_CONN_D3:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            dev = FTM1;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            dev = FTM0;

        break;
    case OHIGROVE_CONN_D4:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            dev = FTM0;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            dev = FTM0;
        
        break;
    case OHIGROVE_CONN_D5:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            dev = FTM0;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            dev = FTM0;

        break;
    case OHIGROVE_CONN_D6:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            dev = FTM0;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            dev = FTM0;

        break;
    case OHIGROVE_CONN_D7:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            dev = FTM0;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            dev = FTM1;

        break;
    case OHIGROVE_CONN_D8:
        
        if (number == OHIGROVE_PIN_NUMBER_1)
            dev = FTM1;
        else if (number == OHIGROVE_PIN_NUMBER_2)
            dev = FTM0;
        
        break;
    default:
        /* Nothing to do! */
        break;
    }
    
#elif defined (OHIBOARD_R1) && defined (GROVETOPPING_R0)


#endif
    
    return dev;
}


