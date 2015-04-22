/******************************************************************************
 * Copyright (C) 2015 A. C. Open Hardware Ideas Lab
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
 * @file libohigrove/serial.c
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief
 */

#include "serial.h"

void OhiGroveSerial_init(OhiGroveSerial_Device* dev)
{
    System_Errors errors = ERRORS_NO_ERROR;

    dev->device = OhiGrove_getUartDevice(dev->connector);
    errors = OhiGrove_uartEnable(dev->connector, dev->baudrate);
}

void OhiGroveSerial_write(OhiGroveSerial_Device* dev, uint8_t value)
{
    Uart_putChar(dev->device,value);
}

void OhiGroveSerial_writeBuffer(OhiGroveSerial_Device* dev, uint8_t* buffer, uint8_t length)
{
    Uart_sendData(dev->device,buffer,length);
}

void OhiGroveSerial_print(OhiGroveSerial_Device* dev, char* text)
{
    Uart_sendString(dev->device,text);
}

void OhiGroveSerial_println(OhiGroveSerial_Device* dev, char* text)
{
    Uart_sendString(dev->device,text);
    Uart_sendString(dev->device,"\r\n");
}

void OhiGroveSerial_printUInt(OhiGroveSerial_Device* dev, uint16_t value)
{
    uint8_t text[6];
    u16td(text,value);

    Uart_sendString(dev->device,text);
}

void OhiGroveSerial_printlnUInt(OhiGroveSerial_Device* dev, uint16_t value)
{
    OhiGroveSerial_printUInt(dev,value);
    Uart_sendString(dev->device,"\r\n");
}

void OhiGroveSerial_printInt(OhiGroveSerial_Device* dev, int16_t value)
{
    uint8_t text[7];
    i16td(text,value);

    Uart_sendString(dev->device,text);
}

void OhiGroveSerial_printlnInt(OhiGroveSerial_Device* dev, int16_t value)
{
    OhiGroveSerial_printInt(dev,value);
    Uart_sendString(dev->device,"\r\n");
}

System_Errors OhiGroveSerial_printFloat(OhiGroveSerial_Device* dev, float value, uint8_t precision)
{
    uint8_t text[12];
    System_Errors errors = ERRORS_NO_ERROR;

    errors = ftstr(value,text,precision);

    if (errors != ERRORS_UTILITY_CONVERSION_OK)
        return errors;

    Uart_sendString(dev->device,text);
    return ERRORS_NO_ERROR;
}

System_Errors OhiGroveSerial_printlnFloat(OhiGroveSerial_Device* dev, float value, uint8_t precision)
{
    System_Errors errors = ERRORS_NO_ERROR;

    errors = OhiGroveSerial_printFloat(dev,value,precision);
    if (errors != ERRORS_NO_ERROR)
        return errors;

    Uart_sendString(dev->device,"\r\n");
    return ERRORS_NO_ERROR;
}

