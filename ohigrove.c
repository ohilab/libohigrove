/******************************************************************************
 * Copyright (C) 2014-2015 A. C. Open Hardware Ideas Lab
 * 
 * Authors:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 *  Marco Contigiani <marco.contigiani86@gmail.com>
 *  Alessio Paolucci <a.paolucci89@gmail.com>
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
 * @author Alessio Paolucci <a.paolucci89@gmail.com>
 * @brief 
 */

#include "ohigrove.h"


typedef struct
{
    OhiGrove_Conn connector;   /*< The grove connector of the shield/topping */

    Gpio_Pins pin1;
    Gpio_Pins pin2;

} OhiGrove_DigitalConnector;

const OhiGrove_DigitalConnector OhiGrove_digital[] =
{
#if defined (LIBOHIBOARD_FRDMKL25Z)

    {OHIGROVE_CONN_UART, GPIO_PINS_PTA1,  GPIO_PINS_PTA2},
    {OHIGROVE_CONN_D2,   GPIO_PINS_PTD4,  GPIO_PINS_PTA12},
    {OHIGROVE_CONN_D3,   GPIO_PINS_PTA12, GPIO_PINS_PTA4},
    {OHIGROVE_CONN_D4,   GPIO_PINS_PTA4,  GPIO_PINS_PTA5},
    {OHIGROVE_CONN_D5,   GPIO_PINS_PTA5,  GPIO_PINS_PTC8},
    {OHIGROVE_CONN_D6,   GPIO_PINS_PTC8,  GPIO_PINS_PTC9},
    {OHIGROVE_CONN_D7,   GPIO_PINS_PTC9,  GPIO_PINS_PTA13},
    {OHIGROVE_CONN_D8,   GPIO_PINS_PTA13, GPIO_PINS_PTD5},

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

    {OHIGROVE_CONN_UART1,   UART_PINS_PTB10,  UART_PINS_PTB11},
    {OHIGROVE_CONN_UART2,   UART_PINS_PTB16,  UART_PINS_PTB17},
    {OHIGROVE_CONN_UART3,   UART_PINS_PTC14,  UART_PINS_PTC15},
    {OHIGROVE_CONN_D1,   GPIO_PINS_PTC1,  GPIO_PINS_PTC2},
    {OHIGROVE_CONN_D2,   GPIO_PINS_PTC3,  GPIO_PINS_PTC4},
    {OHIGROVE_CONN_D3,   GPIO_PINS_PTD2,  GPIO_PINS_PTD3},
    {OHIGROVE_CONN_D4,   GPIO_PINS_PTD4,  GPIO_PINS_PTD7},
    {OHIGROVE_CONN_D5,   GPIO_PINS_PTA12,  GPIO_PINS_PTA13},
    {OHIGROVE_CONN_D6,   GPIO_PINS_PTB18,  GPIO_PINS_PTB19},

#endif
};

typedef struct
{
    OhiGrove_Conn connector;   /*< The grove connector of the shield/topping */

    Iic_SclPins scl;
    Iic_SdaPins sda;

} OhiGrove_IicBusConnector;

const OhiGrove_IicBusConnector OhiGrove_iicBus[] =
{
#if defined (LIBOHIBOARD_FRDMKL25Z)

    {OHIGROVE_CONN_I2C, IIC_PINS_PTC1, IIC_PINS_PTC2},

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

    {OHIGROVE_CONN_I2C1, IIC_PINS_PTB2,  IIC_PINS_PTB3},
    {OHIGROVE_CONN_I2C2, IIC_PINS_PTC10, IIC_PINS_PTC11},

#endif
};

typedef struct
{
    OhiGrove_Conn connector;   /*< The grove connector of the shield/topping */

    Uart_RxPins rx;
    Uart_TxPins tx;

} OhiGrove_UartBusConnector;

const OhiGrove_UartBusConnector OhiGrove_uartBus[] =
{
#if defined (LIBOHIBOARD_FRDMKL25Z)

    {OHIGROVE_CONN_UART, UART_PINS_PTA1, UART_PINS_PTA2},

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

#endif
};

typedef struct
{
    OhiGrove_Conn connector;   /*< The grove connector of the shield/topping */

    Adc_Pins pin1;
    Adc_ChannelNumber pin1Channel;
    uint8_t pin1Device;

    Adc_Pins pin2;
    Adc_ChannelNumber pin2Channel;
    uint8_t pin2Device;

} OhiGrove_AnalogConnector;

static OhiGrove_AnalogConnector OhiGrove_analog[] =
{
#if defined (LIBOHIBOARD_FRDMKL25Z)

    {OHIGROVE_CONN_A0, ADC_PINS_PTB0, ADC_CH_SE8,  0, ADC_PINS_PTB1, ADC_CH_SE9,  0},
    {OHIGROVE_CONN_A1, ADC_PINS_PTB1, ADC_CH_SE9,  0, ADC_PINS_PTB2, ADC_CH_SE12, 0},
    {OHIGROVE_CONN_A2, ADC_PINS_PTB2, ADC_CH_SE12, 0, ADC_PINS_PTB3, ADC_CH_SE13, 0},
    {OHIGROVE_CONN_A3, ADC_PINS_PTB3, ADC_CH_SE13, 0, ADC_PINS_PTC2, ADC_CH_SE11, 0},

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

    {OHIGROVE_CONN_A1, ADC_PINS_ADC0_DP1, ADC_CH_DP1,  0,  0,  0,  0},
    {OHIGROVE_CONN_A2, ADC_PINS_ADC1_DP1, ADC_CH_DP1,  1,  0,  0,  0},
    {OHIGROVE_CONN_A3, ADC_PINS_ADC0_DP0, ADC_CH_DP0,  0,  0,  0,  0},
    {OHIGROVE_CONN_A4, ADC_PINS_ADC1_DP0, ADC_CH_DP0,  1,  0,  0,  0},

#endif
};

#define OHIGROVE_DIGITAL_SIZE    ( sizeof OhiGrove_digital / sizeof OhiGrove_digital[0] )
#define OHIGROVE_ANALOG_SIZE     ( sizeof OhiGrove_analog / sizeof OhiGrove_analog[0] )
#define OHIGROVE_IIC_SIZE        ( sizeof OhiGrove_iicBus / sizeof OhiGrove_iicBus[0] )
#define OHIGROVE_UART_SIZE       ( sizeof OhiGrove_uartBus / sizeof OhiGrove_uartBus[0] )


#if defined (LIBOHIBOARD_FRDMKL25Z)

Clock_Config OhiGrove_clockConfig = {
	.source = CLOCK_CRYSTAL,
	.fext = 8000000,
	.foutSys = 40000000,
	.busDivider = 2,
};

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

Clock_Config OhiGrove_clockConfig = {
		.source = CLOCK_CRYSTAL,
		.fext = 16000000,
		.foutSys = 100000000,
		.busDivider = 2,
		.flexbusDivider = 2,
		.flashDivider = 4,
};

#endif

static Adc_Config OhiGrove_adcConfig = {
	.clkDiv             = 1,
	.clkSource          = ADC_BUS_CLOCK,
	.sampleLength       = ADC_LONG_SAMPLE_2,
	.covertionSpeed     = ADC_NORMAL_CONVERTION,
	.resolution         = ADC_RESOLUTION_12BIT,
	.average            = ADC_AVERAGE_1_SAMPLES,
	.contConv           = ADC_SINGLE_CONVERTION,
	.voltRef            = ADC_VREF,
};

static Iic_Config OhiGrove_iicConfig = {
    .sclPin       = IIC_PINS_SCLNONE,
    .sdaPin       = IIC_PINS_SDANONE,

    .baudRate     = 100000,
    .devType      = IIC_MASTER_MODE,
    .addressMode  = IIC_SEVEN_BIT,
};

static Uart_Config OhiGrove_uartConfig = {
    .txPin       = UART_PINS_TXNONE,
    .rxPin       = UART_PINS_RXNONE,

    .dataBits    = UART_DATABITS_EIGHT,
    .parity      = UART_PARITY_NONE,

    .baudrate    = 9600,
};

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

    Adc_init(ADC0,&OhiGrove_adcConfig);

#elif defined (LIBOHIBOARD_OHIBOARD_R1)
    
	SIM_SCGC5 |= (
			SIM_SCGC5_PORTA_MASK |
			SIM_SCGC5_PORTB_MASK |
			SIM_SCGC5_PORTC_MASK |
			SIM_SCGC5_PORTD_MASK |
			SIM_SCGC5_PORTE_MASK);

	errors = Clock_Init(&OhiGrove_clockConfig);
    errors = Clock_setDividers(OhiGrove_clockConfig.busDivider, OhiGrove_clockConfig.flexbusDivider, OhiGrove_clockConfig.flashDivider);
	foutSYS = Clock_getFrequency(CLOCK_SYSTEM);
    foutBUS = Clock_getFrequency(CLOCK_BUS);

//    Ftm_init(FTM2,OhiGrove_baseTimerInterrupt,&OhiGrove_baseTimer);
//    OhiGrove_milliseconds = 0;
//
//    Adc_init(ADC0,&OhiGrove_adcConfig);

#endif
}

Gpio_Pins OhiGrove_getDigitalPin(OhiGrove_Conn connector)
{
    if (OhiGrove_digital[connector].connector == connector)
        return OhiGrove_digital[connector].pin1;
    else
        return GPIO_PINS_NONE;
}

static Iic_SclPins OhiGrove_getIicSclPin (OhiGrove_Conn connector)
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_IIC_SIZE; ++i)
    {
        if (OhiGrove_iicBus[i].connector == connector)
            return OhiGrove_iicBus[i].scl;
    }
    return IIC_PINS_SCLNONE;
}

static Iic_SdaPins OhiGrove_getIicSdaPin (OhiGrove_Conn connector)
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_IIC_SIZE; ++i)
    {
        if (OhiGrove_iicBus[i].connector == connector)
            return OhiGrove_iicBus[i].sda;
    }
    return IIC_PINS_SDANONE;
}

Iic_DeviceHandle OhiGrove_getIicDevice (OhiGrove_Conn connector)
{

	switch (connector)
	{
#if defined (LIBOHIBOARD_FRDMKL25Z)
	case OHIGROVE_CONN_I2C:
		return IIC1;
#elif defined (LIBOHIBOARD_OHIBOARD_R1)
	case OHIGROVE_CONN_I2C1:
		return IIC0;
	case OHIGROVE_CONN_I2C2:
		return IIC1;
#endif
	default:
	    return NULL;
	}

	return NULL;
}

System_Errors OhiGrove_iicEnable (OhiGrove_Conn connector, uint32_t baudrate)
{
	Iic_DeviceHandle device = NULL;

	device = OhiGrove_getIicDevice(connector);
	OhiGrove_iicConfig.sclPin = OhiGrove_getIicSclPin(connector);
	OhiGrove_iicConfig.sdaPin = OhiGrove_getIicSdaPin(connector);
	if (baudrate != 0)
		OhiGrove_iicConfig.baudRate = (baudrate);

	return Iic_init(device, &OhiGrove_iicConfig);
}

static Uart_RxPins OhiGrove_getUartRxPin (OhiGrove_Conn connector)
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_UART_SIZE; ++i)
    {
        if (OhiGrove_uartBus[i].connector == connector)
            return OhiGrove_uartBus[i].rx;
    }
    return UART_PINS_RXNONE;
}

static Uart_TxPins OhiGrove_getUartTxPin (OhiGrove_Conn connector)
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_UART_SIZE; ++i)
    {
        if (OhiGrove_uartBus[i].connector == connector)
            return OhiGrove_uartBus[i].tx;
    }
    return UART_PINS_TXNONE;
}

Uart_DeviceHandle OhiGrove_getUartDevice (OhiGrove_Conn connector)
{

    switch (connector)
    {
#if defined (LIBOHIBOARD_FRDMKL25Z)
    case OHIGROVE_CONN_UART:
        return UART0;
#elif defined (LIBOHIBOARD_OHIBOARD_R1)

#endif
    default:
        return NULL;
    }

    return NULL;
}

System_Errors OhiGrove_uartEnable (OhiGrove_Conn connector, uint32_t baudrate)
{
    Uart_DeviceHandle device = NULL;

    device = OhiGrove_getUartDevice(connector);
    OhiGrove_uartConfig.rxPin = OhiGrove_getUartRxPin(connector);
    OhiGrove_uartConfig.txPin = OhiGrove_getUartTxPin(connector);
    if (baudrate != 0)
        OhiGrove_uartConfig.baudrate = baudrate;

    return Uart_open(device,0,&OhiGrove_uartConfig);
}

Adc_Pins OhiGrove_getAnalogPin(OhiGrove_Conn connector, OhiGrove_PinNumber number)
{
	uint8_t i = 0;

	for (i = 0; i < OHIGROVE_ANALOG_SIZE; ++i)
	{
	    if (OhiGrove_analog[i].connector == connector)
	    {
	    	if (number == OHIGROVE_PIN_NUMBER_1)
	    		return OhiGrove_analog[i].pin1;
	    	else
	    		return OhiGrove_analog[i].pin2;
	    }
	}
	return ADC_PINS_NONE;
}

Adc_ChannelNumber OhiGrove_getAnalogChannel (OhiGrove_Conn connector, OhiGrove_PinNumber number)
{
	uint8_t i = 0;

	for (i = 0; i < OHIGROVE_ANALOG_SIZE; ++i)
	{
	    if (OhiGrove_analog[i].connector == connector)
	    {
	    	if (number == OHIGROVE_PIN_NUMBER_1)
	    		return OhiGrove_analog[i].pin1Channel;
	    	else
	    		return OhiGrove_analog[i].pin2Channel;
	    }
	}
	return ADC_CH_DISABLE;
}

Adc_DeviceHandle OhiGrove_getAnalogDevice (OhiGrove_Conn connector, OhiGrove_PinNumber number)
{
	uint8_t i = 0;
	uint8_t device = 0;

	for (i = 0; i < OHIGROVE_ANALOG_SIZE; ++i)
	{
	    if (OhiGrove_analog[i].connector == connector)
	    {
	    	if (number == OHIGROVE_PIN_NUMBER_1)
	    		device = OhiGrove_analog[i].pin1Device;
	    	else
	    		device = OhiGrove_analog[i].pin2Device;

	    	switch (device)
	    	{
	    	case 0:
	    		return ADC0;
#if defined (LIBOHIBOARD_OHIBOARD_R1)
	    	case 1:
	    		return ADC1;
#endif
	    	default:
	    		return NULL;
	    	}
	    }
	}
	return NULL;
}
