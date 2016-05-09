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

OhiGroveSerial_Device* device[3];

void OhiGroveSerial_isrUart0()
{
    uint8_t c;

    Uart_getChar(device[0]->device,&c);
    if ((device[0]->rxBufferTail + 1) != device[0]->rxBufferHead)
    {
        device[0]->rxBuffer[device[0]->rxBufferTail] = c;
        device[0]->rxBufferTail++;
        device[0]->rxBufferTail &= OHIGROVESERIAL_BUFFER_SIZE;
    }
}

void OhiGroveSerial_isrUart1()
{
    uint8_t c;

    Uart_getChar(device[1]->device,&c);
    if ((device[1]->rxBufferTail + 1) != device[1]->rxBufferHead)
    {
        device[1]->rxBuffer[device[1]->rxBufferTail] = c;
        device[1]->rxBufferTail++;
        device[1]->rxBufferTail &= OHIGROVESERIAL_BUFFER_SIZE;
    }
}

void OhiGroveSerial_isrUart2()
{
    uint8_t c;

    Uart_getChar(device[2]->device,&c);
    if ((device[2]->rxBufferTail + 1) != device[2]->rxBufferHead)
    {
        device[2]->rxBuffer[device[2]->rxBufferTail] = c;
        device[2]->rxBufferTail++;
        device[2]->rxBufferTail &= OHIGROVESERIAL_BUFFER_SIZE;
    }
}

void OhiGroveSerial_init(OhiGroveSerial_Device* dev)
{
    System_Errors errors = ERRORS_NO_ERROR;

    dev->device = OhiGrove_getUartDevice(dev->connector);
    errors = OhiGrove_uartEnable(dev->connector, dev->baudrate);

    dev->rxBufferHead = 0;
    dev->rxBufferTail = 0;

    /* Default timeout */
    dev->timeout = 1000;

#if defined (LIBOHIBOARD_FRDMKL25Z)

    if (dev->device == UART0)
        device[0] = dev;
    else if (dev->device == UART1)
        device[1] = dev;
    else if (dev->device == UART2)
        device[2] = dev;

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

#endif
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

void OhiGroveSerial_printULong(OhiGroveSerial_Device* dev, uint32_t value)
{
    uint8_t text[11];
    u32td(text,value);

    Uart_sendString(dev->device,text);
}

void OhiGroveSerial_printlnUInt(OhiGroveSerial_Device* dev, uint16_t value)
{
    OhiGroveSerial_printUInt(dev,value);
    Uart_sendString(dev->device,"\r\n");
}

void OhiGroveSerial_printlnULong(OhiGroveSerial_Device* dev, uint32_t value)
{
    OhiGroveSerial_printULong(dev,value);
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

uint8_t OhiGroveSerial_available(OhiGroveSerial_Device* dev)
{
    return (dev->rxBufferTail - dev->rxBufferHead);
}

uint8_t OhiGroveSerial_read(OhiGroveSerial_Device* dev)
{
    if (dev->rxBufferTail != dev->rxBufferHead)
    {
        return dev->rxBuffer[dev->rxBufferHead++];
    }
}

uint8_t OhiGroveSerial_readBytes(OhiGroveSerial_Device* dev, uint8_t buffer[], uint8_t length)
{
    uint32_t currTick = OhiGrove_currentTime();
    uint8_t i = 0;

//    while ((dev->rxBufferTail != dev->rxBufferHead) && (i < length))
//    {
//        buffer[i] = dev->rxBuffer[dev->rxBufferHead++];
//        i++;
//    }
//
//    if (i == length)
//        return i;

    while ((currTick + dev->timeout) >  OhiGrove_currentTime())
    {
        if ((dev->rxBufferTail != dev->rxBufferHead) && (i < length))
        {
            buffer[i] = dev->rxBuffer[dev->rxBufferHead++];
            i++;
        }

        if (i == length)
            return i;
    }
    return i;
}


uint8_t OhiGroveSerial_peek(OhiGroveSerial_Device* dev)
{
    if (dev->rxBufferTail != dev->rxBufferHead)
    {
        return dev->rxBuffer[dev->rxBufferHead];
    }
}

void OhiGroveSerial_setTimeout(OhiGroveSerial_Device* dev, uint32_t timeout)
{
    dev->timeout = timeout;
}
