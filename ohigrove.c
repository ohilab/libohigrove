/******************************************************************************
 * Copyright (C) 2014-2015 A. C. Open Hardware Ideas Lab
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


typedef struct
{
    OhiGrove_Conn connector;   /*< The grove connector of the shield/topping */

    Gpio_Pins pin1;
    Gpio_Pins pin2;
} OhiGrove_DigitalConnector;

const OhiGrove_DigitalConnector OhiGrove_Digital[] =
{
#if defined (LIBOHIBOARD_FRDMKL25Z)

    {OHIGROVE_CONN_UART, GPIO_PINS_PTA1, GPIO_PINS_PTA2},
    {OHIGROVE_CONN_D2,   GPIO_PINS_PTD4, GPIO_PINS_PTA12},

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

#endif
};

#if defined (LIBOHIBOARD_FRDMKL25Z)

    Clock_Config OhiGrove_clockConfig = {
        .source = CLOCK_CRYSTAL,
        .fext = 8000000,
        .foutSys = 40000000,
        .busDivider = 2,
    };

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

#endif

//static Ftm_Config OhiGrove_highFrequency =
//{
//    .mode              = FTM_MODE_PWM,
//
//    .timerFrequency    = 1000,
//    .initCounter       = 0,
//
//    .pins              = {FTM_PINS_STOP},
//
//    .configurationBits = FTM_CONFIG_PWM_EDGE_ALIGNED | FTM_CONFIG_PWM_POLARITY_LOW | 0,
//};
//
//static Ftm_Config OhiGrove_lowFrequency =
//{
//    .mode              = FTM_MODE_PWM,
//
//    .timerFrequency    = 500,
//    .initCounter       = 0,
//
//    .pins              = {FTM_PINS_STOP},
//
//    .configurationBits = FTM_CONFIG_PWM_EDGE_ALIGNED | FTM_CONFIG_PWM_POLARITY_LOW | 0,
//};

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

void OhiGrove_initBoard ()
{
    uint32_t foutBUS;
    uint32_t foutSYS;
    System_Errors errors = ERRORS_NO_ERROR;

#if defined (LIBOHIBOARD_FRDMKL25Z)

    /* Enable clock gate for ports to enable pin routing */
    SIM_SCGC5 |= (
            SIM_SCGC5_PORTA_MASK |
            SIM_SCGC5_PORTB_MASK |
            SIM_SCGC5_PORTC_MASK |
            SIM_SCGC5_PORTD_MASK |
            SIM_SCGC5_PORTE_MASK);

    errors = Clock_Init(&OhiGrove_clockConfig);
    errors = Clock_setDividers(OhiGrove_clockConfig.busDivider, 0,0);
    foutSYS = Clock_getFrequency(CLOCK_SYSTEM);
    foutBUS = Clock_getFrequency(CLOCK_BUS);


//    Ftm_init(FTM0,0,&OhiGrove_highFrequency);
//    Ftm_init(FTM1,0,&OhiGrove_lowFrequency);
    Ftm_init(FTM2,OhiGrove_baseTimerInterrupt,&OhiGrove_baseTimer);
    OhiGrove_milliseconds = 0;

#elif defined (LIBOHIBOARD_OHIBOARD_R1)
    
#endif
}

Gpio_Pins OhiGrove_getDigitalPin(OhiGrove_Conn connector)
{
    if (OhiGrove_Digital[connector].connector == connector)
        return OhiGrove_Digital[connector].pin1;
    else
        return GPIO_PINS_NONE;
}

