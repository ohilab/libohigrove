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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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
            /* TODO: ... */
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

void OhiGrove_initBoard (OhiGrove_Board board)
{
    switch (board)
    {
    case OHIGROVE_BOARD_FRDMKL25:
        
        break;
    case OHIGROVE_BOARD_TOPPING_R0:
        
        break;
    default:
        /* Nothing to do! */
        break;
    }
}

void OhiGrove_setDigital (OhiGrove_Conn conn, 
                          Gpio_Level level, 
                          OhiGrove_PinNumber number)
{
#if defined (FRDMKL25Z)
    Gpio_Pins pin;
    
    
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
    
    if (level == GPIO_HIGH)
        Gpio_set(pin);
    else if (level == GPIO_TOGGLE)
        Gpio_toggle(pin);
    else
        Gpio_clear(pin);

#elif defined (OHIBOARD_R1) && defined (GROVETOPPING_R0)


#endif
}
