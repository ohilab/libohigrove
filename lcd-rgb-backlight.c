/******************************************************************************
 * Copyright (C) 2016 A. C. Open Hardware Ideas Lab
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
 * @file libohigrove/lcd-rgb-backlight.c
 * @author Marco Giammarini <m.giammarini@warcomeb.it>
 * @brief
 *
 * @see http://www.seeedstudio.com/wiki/Grove_-_LCD_RGB_Backlight
 * @see http://www.seeedstudio.com/wiki/images/0/03/JHD1214Y_YG_1.0.pdf
 * @see http://www.seeedstudio.com/wiki/images/1/1c/PCA9633.pdf
 */

#include "lcd-rgb-backlight.h"

#define OHIGROVELCDRGBB_LCD_ADDRESS          0x7C
#define OHIGROVELCDRGBB_RGB_ADDRESS          0xC4

#define OHIGROVELCDRGBB_CMD_CLEAR_DISPLAY    0x01
#define OHIGROVELCDRGBB_CMD_RETURN_HOME      0x02
#define OHIGROVELCDRGBB_CMD_ENTRY_MODE_SET   0x04
#define OHIGROVELCDRGBB_CMD_DISPLAY_CONTROL  0x08
#define OHIGROVELCDRGBB_CMD_CURSOR_SHIFT     0x10
#define OHIGROVELCDRGBB_CMD_FUNCTION_SET     0x30
#define OHIGROVELCDRGBB_CMD_SET_CGRAM_ADDR   0x40
#define OHIGROVELCDRGBB_CMD_SET_DDRAM_ADDR   0x80

#define OHIGROVELCDRGBB_DISPLAY_ON           0x04
#define OHIGROVELCDRGBB_DISPLAY_OFF          0x00

#define OHIGROVELCDRGBB_CURSOR_ON            0x02
#define OHIGROVELCDRGBB_CURSOR_OFF           0x00

#define OHIGROVELCDRGBB_BLINK_ON             0x01
#define OHIGROVELCDRGBB_BLINK_OFF            0x00

#define OHIGROVELCDRGBB_MODE_8BIT            0x10
#define OHIGROVELCDRGBB_MODE_4BIT            0x00

#define OHIGROVELCDRGBB_LINE_2               0x08
#define OHIGROVELCDRGBB_LINE_1               0x00

#define OHIGROVELCDRGBB_DOTS_5x10            0x04
#define OHIGROVELCDRGBB_DOTS_5x8             0x00

#define OHIGROVELCDRGBB_ENTRY_RIGHT          0x00
#define OHIGROVELCDRGBB_ENTRY_LEFT           0x02
#define OHIGROVELCDRGBB_SHIFT_INCREMENT      0x01
#define OHIGROVELCDRGBB_SHIFT_DECREMENT      0x00

#define OHIGROVELCDRGBB_MOVE_DISPLAY         0x08
#define OHIGROVELCDRGBB_MOVE_CURSOR          0x00
#define OHIGROVELCDRGBB_MOVE_RIGHT           0x04
#define OHIGROVELCDRGBB_MOVE_LEFT            0x00

/* RGB control register */
#define OHIGROVELCDRGBB_RGBREG_MODE1         0x00
#define OHIGROVELCDRGBB_RGBREG_MODE2         0x01
#define OHIGROVELCDRGBB_RGBREG_PWM0          0x02 /* BLUE */
#define OHIGROVELCDRGBB_RGBREG_PWM1          0x03 /* GREEN */
#define OHIGROVELCDRGBB_RGBREG_PWM2          0x04 /* RED */
#define OHIGROVELCDRGBB_RGBREG_PWM3          0x05
#define OHIGROVELCDRGBB_RGBREG_PWMDUTY       0x06
#define OHIGROVELCDRGBB_RGBREG_PWMFREQ       0x07
#define OHIGROVELCDRGBB_RGBREG_LEDOUT        0x08

static void OhiGroveLcdRgbB_sendLcdCommand (OhiGroveLcdRgbB_Device* dev, uint8_t command, bool write)
{
    System_Errors error,error1,error2;
    Iic_start(dev->device);
    error = Iic_writeByte(dev->device, OHIGROVELCDRGBB_LCD_ADDRESS);
    if (!write)
        error1 = Iic_writeByte(dev->device, 0x80);
    else
        error1 = Iic_writeByte(dev->device, 0x40);
    error2 = Iic_writeByte(dev->device, command);
    Iic_stop(dev->device);
}

static void OhiGroveLcdRgbB_setRgbRegister (OhiGroveLcdRgbB_Device* dev, uint8_t address, uint8_t data)
{
    Iic_start(dev->device);
    Iic_writeByte(dev->device, OHIGROVELCDRGBB_RGB_ADDRESS);
    Iic_writeByte(dev->device, address);
    Iic_writeByte(dev->device, data);
    Iic_stop(dev->device);
}

void OhiGroveLcdRgbB_init (OhiGroveLcdRgbB_Device* dev)
{
    System_Errors errors = ERRORS_NO_ERROR;

    dev->device = OhiGrove_getIicDevice(dev->connector);
    errors = OhiGrove_iicEnable(dev->connector, 250000, TRUE);
    if (errors != ERRORS_NO_ERROR) return;

    if (dev->lines == 1) dev->function = OHIGROVELCDRGBB_LINE_1;
    else dev->function = OHIGROVELCDRGBB_LINE_2;

    /* according to datasheet, we need at least 30ms after power rises above 2.7V */
    OhiGrove_delay(50);

    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_FUNCTION_SET | dev->function,
                                   FALSE);
    OhiGrove_delay(4);

    dev->display = OHIGROVELCDRGBB_DISPLAY_ON |
                   OHIGROVELCDRGBB_CURSOR_OFF |
                   OHIGROVELCDRGBB_BLINK_OFF;
    OhiGroveLcdRgbB_displayOn(dev);
    OhiGrove_delay(4);

    /* The delay is included into function clear */
    OhiGroveLcdRgbB_clear(dev);

    /* Romance languages */
    dev->mode = OHIGROVELCDRGBB_ENTRY_LEFT |
                OHIGROVELCDRGBB_SHIFT_DECREMENT;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_ENTRY_MODE_SET | dev->mode,
                                   FALSE);

    /* Init LED driver */
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_MODE1,0);
    /* Set LEDs controllable by both PWM and GRPPWM registers */
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_LEDOUT,0xFF);
    /* MODE2: DMBLNK to 1, blinking mode */
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_MODE2,0x20);
}

void OhiGroveLcdRgbB_write (OhiGroveLcdRgbB_Device* dev, uint8_t ch)
{
    OhiGroveLcdRgbB_sendLcdCommand(dev,ch,TRUE);
}

void OhiGroveLcdRgbB_displayOn (OhiGroveLcdRgbB_Device* dev)
{
    dev->display |= OHIGROVELCDRGBB_DISPLAY_ON;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_DISPLAY_CONTROL | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_displayOff (OhiGroveLcdRgbB_Device* dev)
{
    dev->display &= ~OHIGROVELCDRGBB_DISPLAY_ON;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_DISPLAY_CONTROL | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_cursorOn (OhiGroveLcdRgbB_Device* dev)
{
    dev->display |= OHIGROVELCDRGBB_CURSOR_ON;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_DISPLAY_CONTROL | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_cursorOff (OhiGroveLcdRgbB_Device* dev)
{
    dev->display &= ~OHIGROVELCDRGBB_CURSOR_ON;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_DISPLAY_CONTROL | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_blinkOn (OhiGroveLcdRgbB_Device* dev)
{
    dev->display |= OHIGROVELCDRGBB_BLINK_ON;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_DISPLAY_CONTROL | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_blinkOff (OhiGroveLcdRgbB_Device* dev)
{
    dev->display &= ~OHIGROVELCDRGBB_BLINK_ON;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_DISPLAY_CONTROL | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_scrollDisplayLeft (OhiGroveLcdRgbB_Device* dev)
{
    OhiGroveLcdRgbB_sendLcdCommand(
        dev,
        OHIGROVELCDRGBB_CMD_CURSOR_SHIFT | OHIGROVELCDRGBB_MOVE_DISPLAY | OHIGROVELCDRGBB_MOVE_LEFT,
        FALSE
    );
}

void OhiGroveLcdRgbB_scrollDisplayRight (OhiGroveLcdRgbB_Device* dev)
{
    OhiGroveLcdRgbB_sendLcdCommand(
        dev,
        OHIGROVELCDRGBB_CMD_CURSOR_SHIFT | OHIGROVELCDRGBB_MOVE_DISPLAY | OHIGROVELCDRGBB_MOVE_RIGHT,
        FALSE
    );
}

void OhiGroveLcdRgbB_leftToRight (OhiGroveLcdRgbB_Device* dev)
{
    dev->display |= OHIGROVELCDRGBB_ENTRY_LEFT;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_ENTRY_MODE_SET | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_rightToLeft (OhiGroveLcdRgbB_Device* dev)
{
    dev->display &= ~OHIGROVELCDRGBB_ENTRY_LEFT;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_ENTRY_MODE_SET | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_autoscrollOn (OhiGroveLcdRgbB_Device* dev)
{
    dev->display |= OHIGROVELCDRGBB_SHIFT_INCREMENT;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_ENTRY_MODE_SET | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_autoscrollOff (OhiGroveLcdRgbB_Device* dev)
{
    dev->display &= ~OHIGROVELCDRGBB_SHIFT_INCREMENT;
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_ENTRY_MODE_SET | dev->display,
                                   FALSE);
}

void OhiGroveLcdRgbB_clear (OhiGroveLcdRgbB_Device* dev)
{
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_CLEAR_DISPLAY,
                                   FALSE);
    OhiGrove_delay(2);
}

void OhiGroveLcdRgbB_home (OhiGroveLcdRgbB_Device* dev)
{
    OhiGroveLcdRgbB_sendLcdCommand(dev,
                                   OHIGROVELCDRGBB_CMD_RETURN_HOME,
                                   FALSE);
    OhiGrove_delay(2);
}

void OhiGroveLcdRgbB_setCursor (OhiGroveLcdRgbB_Device* dev, uint8_t column, uint8_t row)
{
    uint8_t position = (row == 0 ? column|0x80 : column|0xC0);
    OhiGroveLcdRgbB_sendLcdCommand(dev,position,FALSE);
    OhiGrove_delay(2);
}

void OhiGroveLcdRgbB_setColor (OhiGroveLcdRgbB_Device* dev, uint8_t red, uint8_t green, uint8_t blue)
{
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_PWM2,red);
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_PWM1,green);
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_PWM0,blue);
}

void OhiGroveLcdRgbB_blinkLedOn (OhiGroveLcdRgbB_Device* dev)
{
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_PWMFREQ, 0x17);  /* PERIOD = <23>+1/24, blink every second  */
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_PWMDUTY, 0x7F);  /* DC = <127>/256, half on and half off */
}

void OhiGroveLcdRgbB_blinkLedOff (OhiGroveLcdRgbB_Device* dev)
{
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_PWMFREQ, 0x00);
    OhiGroveLcdRgbB_setRgbRegister(dev,OHIGROVELCDRGBB_RGBREG_PWMDUTY, 0xFF);
}
