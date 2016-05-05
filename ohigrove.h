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

#define OHIGROVE_ADC_MAX_VALUE             4096

typedef void (*OhiGroveCallback)(void);
typedef void (*OhiGroveCallbackParam)(void* device);

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

//void OhiGrove_baseTimerInterrupt (void);
void OhiGrove_delay (uint32_t msDelay);
void OhiGrove_delay10Microsecond (uint32_t usDelay);
uint32_t OhiGrove_currentTime ();

Gpio_Pins OhiGrove_getDigitalPin (OhiGrove_Conn connector,  OhiGrove_PinNumber number);

Iic_DeviceHandle OhiGrove_getIicDevice (OhiGrove_Conn connector);
System_Errors OhiGrove_iicEnable (OhiGrove_Conn connector, uint32_t baudrate, bool pullupEnable);

Uart_DeviceHandle OhiGrove_getUartDevice (OhiGrove_Conn connector);
System_Errors OhiGrove_uartEnable (OhiGrove_Conn connector, uint32_t baudrate);

Adc_Pins OhiGrove_getAnalogPin (OhiGrove_Conn connector, OhiGrove_PinNumber number);
Adc_ChannelNumber OhiGrove_getAnalogChannel (OhiGrove_Conn connector, OhiGrove_PinNumber number);
Adc_DeviceHandle OhiGrove_getAnalogDevice (OhiGrove_Conn connector, OhiGrove_PinNumber number);

Ftm_DeviceHandle OhiGrove_getFtmDevice (OhiGrove_Conn connector);
Ftm_Pins OhiGrove_getFtmPin(OhiGrove_Conn connector);
Ftm_Channels OhiGrove_getFtmChannel(OhiGrove_Conn connector);
System_Errors OhiGrove_ftmEnable (OhiGrove_Conn connector, Ftm_Mode mode, uint32_t modulo);
System_Errors OhiGrove_enableFtmChannel (OhiGrove_Conn connector, OhiGroveCallbackParam callback, void* target);

void OhiGrove_addInfraredPin (Gpio_Pins pin);
void OhiGrove_enableInfrared (Gpio_Pins pin);
void OhiGrove_disableInfrared (Gpio_Pins pin);

#endif /* __OHIGROVE_H */
