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

#ifndef __OHIGROVE_H
#define __OHIGROVE_H

#include "libohiboard.h"

typedef enum _OhiGrove_Board
{
    OHIGROVE_BOARD_FRDMKL25,
    OHIGROVE_BOARD_TOPPING_R0,
} OhiGrove_Board;

typedef enum _OhiGrove_Conn
{
#if defined(LIBOHIBOARD_FRDMKL25Z)
    OHIGROVE_CONN_UART = 0,
    OHIGROVE_CONN_D2,
    OHIGROVE_CONN_D3,
    OHIGROVE_CONN_D4,
    OHIGROVE_CONN_D5,
    OHIGROVE_CONN_D6,
    OHIGROVE_CONN_D7,
    OHIGROVE_CONN_D8,
    OHIGROVE_CONN_I2C,
    OHIGROVE_CONN_A0,
    OHIGROVE_CONN_A1,
    OHIGROVE_CONN_A2,
    OHIGROVE_CONN_A3,
#elif defined (LIBOHIBOARD_OHIBOARD_R1)
    OHIGROVE_CONN_UART1,
    OHIGROVE_CONN_UART2,
    OHIGROVE_CONN_UART3,
    OHIGROVE_CONN_D1,
    OHIGROVE_CONN_D2,
    OHIGROVE_CONN_D3,
    OHIGROVE_CONN_D4,
    OHIGROVE_CONN_D5,
    OHIGROVE_CONN_D6,
    OHIGROVE_CONN_I2C1,
    OHIGROVE_CONN_I2C2,
    OHIGROVE_CONN_A1,
    OHIGROVE_CONN_A2,
    OHIGROVE_CONN_A3,
    OHIGROVE_CONN_A4,
#endif
} OhiGrove_Conn;

typedef enum _OhiGrove_PinType
{
    OHIGROVE_PIN_TYPE_DIGITAL_INPUT,
    OHIGROVE_PIN_TYPE_DIGITAL_OUTPUT,
    OHIGROVE_PIN_TYPE_ANALOG_INPUT,
    OHIGROVE_PIN_TYPE_PWM,
    OHIGROVE_PIN_TYPE_I2C,
    OHIGROVE_PIN_TYPE_UART,

    OHIGROVE_PIN_TYPE_NONE,
} OhiGrove_PinType;

typedef enum _OhiGrove_PinNumber
{
    OHIGROVE_PIN_NUMBER_1,
    OHIGROVE_PIN_NUMBER_2,    
} OhiGrove_PinNumber;

void OhiGrove_initBoard();

void OhiGrove_delay (uint32_t msDelay);

Gpio_Pins OhiGrove_getDigitalPin(OhiGrove_Conn connector);

#endif /* __OHIGROVE_H */
