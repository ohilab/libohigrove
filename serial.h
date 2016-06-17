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
 * @file libohigrove/serial.h
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief 
 */

#ifndef __SERIAL_H
#define __SERIAL_H

#define OHIGROVESERIAL_BUFFER_SIZE    0x3F

#include "ohigrove.h"

typedef struct _OhiGroveSerial_Device
{

    /* If GROVE connector */
    OhiGrove_Conn connector;

    /* else NO GROVE connector */
    Uart_RxPins rxPin;
    Uart_TxPins txPin;

    Uart_DeviceHandle device;
    uint32_t baudrate;

    uint8_t rxBuffer[OHIGROVESERIAL_BUFFER_SIZE+1];
    uint8_t rxBufferTail;
    uint8_t rxBufferHead;

    uint32_t timeout;

} OhiGroveSerial_Device;

typedef enum
{
    OHIGORVESERIAL_DECIMAL,
    OHIGROVESERIAL_HEX,

} OhiGroveSerial_PrintType;

void OhiGroveSerial_isrUart0();
void OhiGroveSerial_isrUart1();
void OhiGroveSerial_isrUart2();

void OhiGroveSerial_init(OhiGroveSerial_Device* dev);

void OhiGroveSerial_write(OhiGroveSerial_Device* dev, uint8_t value);
void OhiGroveSerial_writeBuffer(OhiGroveSerial_Device* dev, uint8_t* buffer, uint8_t length);

void OhiGroveSerial_print(OhiGroveSerial_Device* dev, char* text);
void OhiGroveSerial_println(OhiGroveSerial_Device* dev, char* text);

void OhiGroveSerial_printUInt(OhiGroveSerial_Device* dev, uint16_t value);
void OhiGroveSerial_printlnUInt(OhiGroveSerial_Device* dev, uint16_t value);

void OhiGroveSerial_printInt(OhiGroveSerial_Device* dev, int16_t value);
void OhiGroveSerial_printlnInt(OhiGroveSerial_Device* dev, int16_t value);

void OhiGroveSerial_printULong(OhiGroveSerial_Device* dev, uint32_t value);
void OhiGroveSerial_printlnULong(OhiGroveSerial_Device* dev, uint32_t value);

System_Errors OhiGroveSerial_printFloat(OhiGroveSerial_Device* dev, float value, uint8_t precision);
System_Errors OhiGroveSerial_printlnFloat(OhiGroveSerial_Device* dev, float value, uint8_t precision);

uint8_t OhiGroveSerial_available(OhiGroveSerial_Device* dev);
uint8_t OhiGroveSerial_read(OhiGroveSerial_Device* dev);
uint8_t OhiGroveSerial_readBytes(OhiGroveSerial_Device* dev, uint8_t buffer[], uint8_t length);
uint8_t OhiGroveSerial_peek(OhiGroveSerial_Device* dev);

void OhiGroveSerial_setTimeout(OhiGroveSerial_Device* dev, uint32_t timeout);

#endif /* __SERIAL_H */

