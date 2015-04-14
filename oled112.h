/*
 * oled112.h
 *
 *  Created on: 10/apr/2015
 *      Author: Alessio
 */

#ifndef OLED112_H_
#define OLED112_H_

// OhiGroveOled112 Instruction set addresses

#include "ohigrove.h"
#include "libohiboard.h"
#include "board.h"

#define OhiGroveOled112_Max_X 		            127	//128 Pixels
#define OhiGroveOled112_Max_Y 		            63	//64  Pixels

#define OHIGROVEOLED112_PAGE_MODE			    01
#define OHIGROVEOLED112_HORIZONTAL_MODE			02

#define OhiGroveOled112_Address		            0x78
#define OhiGroveOled112_Command_Mode		    0x80
#define OhiGroveOled112_Data_Mode		        0x40
#define OhiGroveOled112_Display_Off_Cmd	        0xAE
#define OhiGroveOled112_Display_On_Cmd	        0xAF
#define OhiGroveOled112_Normal_Display_Cmd	    0xA6
#define OhiGroveOled112_Inverse_Display_Cmd	    0xA7
#define OhiGroveOled112_Activate_Scroll_Cmd	    0x2F
#define OhiGroveOled112_Dectivate_Scroll_Cmd	0x2E
#define OhiGroveOled112_Set_Brightness_Cmd	    0x81

#define OhiGroveOled112_Scroll_Left			    0x00
#define OhiGroveOled112_Scroll_Right			0x01

#define OhiGroveOled112_Scroll_2Frames			0x7
#define OhiGroveOled112_Scroll_3Frames			0x4
#define OhiGroveOled112_Scroll_4Frames			0x5
#define OhiGroveOled112_Scroll_5Frames			0x0
#define OhiGroveOled112_Scroll_25Frames			0x6
#define OhiGroveOled112_Scroll_64Frames			0x1
#define OhiGroveOled112_Scroll_128Frames		0x2
#define OhiGroveOled112_Scroll_256Frames		0x3

typedef struct _OhiGroveOled112_Device
{
    OhiGrove_Conn connector;

    uint32_t baudrate;

} OhiGroveOled112_Device;

char OhiGroveOled112_addressingMode;

void OhiGroveOled112_init(OhiGroveOled112_Device* dev);

void OhiGroveOled112_setNormalDisplay();
void OhiGroveOled112_setInverseDisplay();

void OhiGroveOled112_sendCommand(unsigned char command);
void OhiGroveOled112_sendData(unsigned char Data);

void OhiGroveOled112_setPageMode();
void OhiGroveOled112_setHorizontalMode();

void OhiGroveOled112_setTextXY(unsigned char Row, unsigned char Column);
void OhiGroveOled112_clearDisplay();
void OhiGroveOled112_setBrightness(unsigned char Brightness);
void OhiGroveOled112_putChar(unsigned char c);
void OhiGroveOled112_putString(const char *String);
unsigned char OhiGroveOled112_putNumber(long n);
unsigned char OhiGroveOled112_putFloat(float floatNumber,unsigned char decimal);
void OhiGroveOled112_drawBitmap(unsigned char *bitmaparray,int bytes);

void OhiGroveOled112_setHorizontalScrollProperties(bool direction,unsigned char startPage, unsigned char endPage, unsigned char scrollSpeed);
void OhiGroveOled112_activateScroll();
void OhiGroveOled112_deactivateScroll();

#endif /* OLED112_H_ */
