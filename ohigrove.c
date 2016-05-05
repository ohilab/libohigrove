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

    Gpio_Pins sclGpio;
    Gpio_Pins sdaGpio;

} OhiGrove_IicBusConnector;

const OhiGrove_IicBusConnector OhiGrove_iicBus[] =
{
#if defined (LIBOHIBOARD_FRDMKL25Z)

    {OHIGROVE_CONN_I2C, IIC_PINS_PTC1, IIC_PINS_PTC2, GPIO_PINS_PTC1, GPIO_PINS_PTC2},

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

    {OHIGROVE_CONN_I2C1, IIC_PINS_PTB2,  IIC_PINS_PTB3},
    {OHIGROVE_CONN_I2C2, IIC_PINS_PTC10, IIC_PINS_PTC11},

#endif
};

#if defined (LIBOHIBOARD_FRDMKL25Z)

extern void OhiGroveSerial_isrUart0();
extern void OhiGroveSerial_isrUart1();
extern void OhiGroveSerial_isrUart2();

#elif defined (LIBOHIBOARD_OHIBOARD_R1)


#endif

typedef struct
{
    OhiGrove_Conn connector;   /*< The grove connector of the shield/topping */

    Uart_RxPins rx;
    Uart_TxPins tx;

    OhiGroveCallback callback;

} OhiGrove_UartBusConnector;

const OhiGrove_UartBusConnector OhiGrove_uartBus[] =
{
#if defined (LIBOHIBOARD_FRDMKL25Z)

    {OHIGROVE_CONN_UART, UART_PINS_PTA1, UART_PINS_PTA2, OhiGroveSerial_isrUart0},

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

typedef struct
{
    OhiGrove_Conn connector;   /*< The grove connector of the shield/topping */

    Ftm_Pins pin1;
    Ftm_Channels pin1Channel;
    uint8_t pin1Device;

    OhiGroveCallback callback;
    OhiGroveCallbackParam channelCallback;

    void* target;

} OhiGrove_FtmConnector;


void OhiGrove_isrFtm0();
void OhiGrove_isrFtm1();

static OhiGrove_FtmConnector OhiGrove_ftm[] =
{
#if defined (LIBOHIBOARD_FRDMKL25Z)

    {OHIGROVE_CONN_D2,   FTM_PINS_PTD4,  FTM_CHANNELS_CH4, 0, OhiGrove_isrFtm0, 0, 0},
    {OHIGROVE_CONN_D3,   FTM_PINS_PTA12, FTM_CHANNELS_CH0, 1, OhiGrove_isrFtm1, 0, 0},
    {OHIGROVE_CONN_D4,   FTM_PINS_PTA4,  FTM_CHANNELS_CH1, 0, OhiGrove_isrFtm0, 0, 0},
    {OHIGROVE_CONN_D5,   FTM_PINS_PTA5,  FTM_CHANNELS_CH2, 0, OhiGrove_isrFtm0, 0, 0},
    {OHIGROVE_CONN_D6,   FTM_PINS_PTC8,  FTM_CHANNELS_CH4, 0, OhiGrove_isrFtm0, 0, 0},
    {OHIGROVE_CONN_D7,   FTM_PINS_PTC9,  FTM_CHANNELS_CH5, 0, OhiGrove_isrFtm0, 0, 0},
    {OHIGROVE_CONN_D8,   FTM_PINS_PTA13, FTM_CHANNELS_CH1, 1, OhiGrove_isrFtm1, 0, 0},

#elif defined (LIBOHIBOARD_OHIBOARD_R1)

#endif
};

#define OHIGROVE_DIGITAL_SIZE    ( sizeof OhiGrove_digital / sizeof OhiGrove_digital[0] )
#define OHIGROVE_ANALOG_SIZE     ( sizeof OhiGrove_analog / sizeof OhiGrove_analog[0] )
#define OHIGROVE_IIC_SIZE        ( sizeof OhiGrove_iicBus / sizeof OhiGrove_iicBus[0] )
#define OHIGROVE_UART_SIZE       ( sizeof OhiGrove_uartBus / sizeof OhiGrove_uartBus[0] )
#define OHIGROVE_FTM_SIZE        ( sizeof OhiGrove_ftm / sizeof OhiGrove_ftm[0] )


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
    .txPin        = UART_PINS_TXNONE,
    .rxPin        = UART_PINS_RXNONE,

    .dataBits     = UART_DATABITS_EIGHT,
    .parity       = UART_PARITY_NONE,

    .baudrate     = 9600,
    .oversampling = 16,
};

/* OHI GROVE - Infrared device */
typedef struct
{
    Gpio_Pins pin;
    bool enable;
} OhiGrove_InfraredConnector;

static bool OhiGrove_enableInfraredTx = FALSE;
static uint8_t OhiGrove_infraredTxPinsCount = 0;
static OhiGrove_InfraredConnector OhiGrove_infrared[OHIGROVE_DIGITAL_SIZE];
static Gpio_Level OhiGrove_infraredStatus = GPIO_LOW;

#define OHIGROVE_INFRARED_CYCLE                2//26
#define OHIGROVE_INFRARED_DUTY                 1//5

static Ftm_Config OhiGrove_baseTimer = 
{
    .mode              = FTM_MODE_FREE,

    .timerFrequency    = 100000,
    .initCounter       = 0,
};

static Ftm_Config OhiGrove_otherTimer =
{
	.mode              = FTM_MODE_INPUT_CAPTURE,

	.timerFrequency    = 0,
	.initCounter       = 0,
	.pins              = {FTM_PINS_STOP},
	.configurationBits = 0,
};

static uint32_t OhiGrove_milliseconds = 0;
static uint32_t OhiGrove_10microseconds = 0;

static uint8_t OhiGrove_infraredTimer = 0;

static void OhiGrove_baseTimerInterrupt ()
{
	uint8_t i = 0;

	OhiGrove_10microseconds++;
	OhiGrove_infraredTimer++;

	if (OhiGrove_10microseconds == 100)
	{
		OhiGrove_milliseconds++;
		OhiGrove_10microseconds = 0;
	}

	if (OhiGrove_infraredTimer == OHIGROVE_INFRARED_DUTY)
	{
		OhiGrove_infraredStatus = GPIO_LOW;
	}
	else if (OhiGrove_infraredTimer == OHIGROVE_INFRARED_CYCLE)
	{
		OhiGrove_infraredStatus = GPIO_HIGH;
		OhiGrove_infraredTimer = 0;
	}

	if (OhiGrove_enableInfraredTx == TRUE)
	{
		for (i = 0; i < OhiGrove_infraredTxPinsCount; ++i)
		{
			if ((OhiGrove_infrared[i].enable == TRUE) && (OhiGrove_infraredStatus == GPIO_HIGH))
				Gpio_set(OhiGrove_infrared[i].pin);
			else
				Gpio_clear(OhiGrove_infrared[i].pin);
		}
	}
}

void OhiGrove_delay (uint32_t msDelay)
{
    uint32_t currTicks = OhiGrove_milliseconds;

    while ((OhiGrove_milliseconds - currTicks) < msDelay);
}

void OhiGrove_delay10Microsecond (uint32_t usDelay)
{
    uint32_t currTicks = OhiGrove_10microseconds;

    if (usDelay > 100) return;

    while ((OhiGrove_10microseconds - currTicks) < usDelay);
}

uint32_t OhiGrove_currentTime ()
{
    return OhiGrove_milliseconds;
}

void OhiGrove_initBoard ()
{
    uint32_t foutBUS;
    uint32_t foutSYS;
    System_Errors errors = ERRORS_NO_ERROR;
    uint8_t index = 0;

#if defined (LIBOHIBOARD_FRDMKL25Z)

    /* Enable clock gate for ports to enable pin routing */
    SIM_SCGC5 |= (
            SIM_SCGC5_PORTA_MASK |
            SIM_SCGC5_PORTB_MASK |
            SIM_SCGC5_PORTC_MASK |
            SIM_SCGC5_PORTD_MASK |
            SIM_SCGC5_PORTE_MASK);

    errors = Clock_setDividers(OhiGrove_clockConfig.busDivider, 0,0);
    errors = Clock_Init(&OhiGrove_clockConfig);
    errors = Clock_setDividers(OhiGrove_clockConfig.busDivider, 0,0);
    foutSYS = Clock_getFrequency(CLOCK_SYSTEM);
    foutBUS = Clock_getFrequency(CLOCK_BUS);


    Ftm_init(OB_FTM2,OhiGrove_baseTimerInterrupt,&OhiGrove_baseTimer);
    OhiGrove_milliseconds = 0;

    Adc_init(OB_ADC0,0,&OhiGrove_adcConfig);

    for (index = 0; index < OHIGROVE_DIGITAL_SIZE; ++index)
    {
    	OhiGrove_infrared[index].pin = GPIO_PINS_NONE;
    	OhiGrove_infrared[index].enable = FALSE;
    }

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

#endif
}

Gpio_Pins OhiGrove_getDigitalPin(OhiGrove_Conn connector, OhiGrove_PinNumber number)
{
	uint8_t i = 0;

    for (i = 0; i < OHIGROVE_DIGITAL_SIZE; ++i)
    {
    	if (OhiGrove_digital[i].connector == connector)
    	{
    		if (number == OHIGROVE_PIN_NUMBER_1)
    			return OhiGrove_digital[i].pin1;
    		else if (number == OHIGROVE_PIN_NUMBER_2)
    			return OhiGrove_digital[i].pin2;
    		else
    			return GPIO_PINS_NONE;
    	}
    }
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
		return OB_IIC1;
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

System_Errors OhiGrove_iicEnable (OhiGrove_Conn connector, uint32_t baudrate, bool pullupEnable)
{
	Iic_DeviceHandle device = NULL;

	device = OhiGrove_getIicDevice(connector);
	OhiGrove_iicConfig.sclPin = OhiGrove_getIicSclPin(connector);
	OhiGrove_iicConfig.sdaPin = OhiGrove_getIicSdaPin(connector);
	if (baudrate != 0)
		OhiGrove_iicConfig.baudRate = (baudrate);

	OhiGrove_iicConfig.pullupEnable = pullupEnable;

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

static OhiGroveCallback OhiGrove_getUartCallback (OhiGrove_Conn connector)
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_UART_SIZE; ++i)
    {
        if (OhiGrove_uartBus[i].connector == connector)
            return OhiGrove_uartBus[i].callback;
    }
    return NULL;
}

Uart_DeviceHandle OhiGrove_getUartDevice (OhiGrove_Conn connector)
{

    switch (connector)
    {
#if defined (LIBOHIBOARD_FRDMKL25Z)
    case OHIGROVE_CONN_UART:
        return OB_UART0;
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

    OhiGrove_uartConfig.callbackRx = OhiGrove_getUartCallback(connector);
    OhiGrove_uartConfig.callbackTx = 0;

    return Uart_open(device,&OhiGrove_uartConfig);
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
	    		return OB_ADC0;
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

Ftm_DeviceHandle OhiGrove_getFtmDevice (OhiGrove_Conn connector)
{
	switch (connector)
	{
#if defined (LIBOHIBOARD_FRDMKL25Z)
	case OHIGROVE_CONN_D2:
		return OB_FTM0;
	case OHIGROVE_CONN_D3:
		return OB_FTM1;
	case OHIGROVE_CONN_D4:
		return OB_FTM0;
	case OHIGROVE_CONN_D5:
		return OB_FTM0;
	case OHIGROVE_CONN_D6:
		return OB_FTM0;
	case OHIGROVE_CONN_D7:
		return OB_FTM0;
	case OHIGROVE_CONN_D8:
		return OB_FTM1;
#elif defined (LIBOHIBOARD_OHIBOARD_R1)

#endif
	default:
	    return NULL;
	}

	return NULL;
}

Ftm_Pins OhiGrove_getFtmPin(OhiGrove_Conn connector)
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_FTM_SIZE; ++i)
    {
        if (OhiGrove_ftm[i].connector == connector)
            return OhiGrove_ftm[i].pin1;
        else
            return FTM_PINS_STOP;
    }
    return FTM_PINS_STOP;
}

Ftm_Channels OhiGrove_getFtmChannel (OhiGrove_Conn connector)
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_FTM_SIZE; ++i)
    {
        if (OhiGrove_ftm[i].connector == connector)
            return OhiGrove_ftm[i].pin1Channel;
        else
            return FTM_CHANNELS_NONE;
    }
    return FTM_CHANNELS_NONE;
}

System_Errors OhiGrove_ftmEnable (OhiGrove_Conn connector, Ftm_Mode mode, uint32_t modulo)
{
    Ftm_DeviceHandle device = NULL;
    uint8_t i;

    device = OhiGrove_getFtmDevice(connector);

    if (modulo != 0)
        OhiGrove_otherTimer.timerFrequency = modulo;
    else
        return ERRORS_PARAM_VALUE;

    OhiGrove_otherTimer.configurationBits = 0;

    OhiGrove_otherTimer.mode = mode;

    for (i = 0; i < OHIGROVE_FTM_SIZE; ++i)
    {
        if (OhiGrove_ftm[i].connector == connector)
        {
            Ftm_init(device,OhiGrove_ftm[i].callback,&OhiGrove_otherTimer);
            return ERRORS_NO_ERROR;
        }
    }

    return ERRORS_PARAM_VALUE;
}

System_Errors OhiGrove_enableFtmChannel (OhiGrove_Conn connector, OhiGroveCallbackParam callback, void* target)
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_FTM_SIZE; ++i)
    {
        if (OhiGrove_ftm[i].connector == connector)
        {
            OhiGrove_ftm[i].channelCallback = callback;
            OhiGrove_ftm[i].target = target;

            return ERRORS_NO_ERROR;
        }
    }
    return ERRORS_PARAM_VALUE;
}

void OhiGrove_isrFtm0()
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_FTM_SIZE; ++i)
    {
        if (OhiGrove_ftm[i].pin1Device == 0)
        {
            if (Ftm_isChannelInterrupt(OB_FTM0,OhiGrove_ftm[i].pin1Channel))
            {
                OhiGrove_ftm[i].channelCallback(OhiGrove_ftm[i].target);

                Ftm_clearChannelFlagInterrupt(OB_FTM0,OhiGrove_ftm[i].pin1Channel);
            }
        }
    }
}

void OhiGrove_isrFtm1()
{
    uint8_t i = 0;

    for (i = 0; i < OHIGROVE_FTM_SIZE; ++i)
    {
        if (OhiGrove_ftm[i].pin1Device == 1)
        {
            if (Ftm_isChannelInterrupt(OB_FTM1,OhiGrove_ftm[i].pin1Channel))
            {
                OhiGrove_ftm[i].channelCallback(OhiGrove_ftm[i].target);

                Ftm_clearChannelFlagInterrupt(OB_FTM1,OhiGrove_ftm[i].pin1Channel);
            }
        }
    }
}

void OhiGrove_addInfraredPin (Gpio_Pins pin)
{
	if (OhiGrove_infraredTxPinsCount > OHIGROVE_DIGITAL_SIZE) return;

	OhiGrove_infrared[OhiGrove_infraredTxPinsCount].pin = pin;
	OhiGrove_infrared[OhiGrove_infraredTxPinsCount].enable = FALSE;
	OhiGrove_infraredTxPinsCount++;

	OhiGrove_enableInfraredTx = TRUE;
}

void OhiGrove_enableInfrared (Gpio_Pins pin)
{
	uint8_t index;

    for (index = 0; index < OHIGROVE_DIGITAL_SIZE; ++index)
    {
    	if (OhiGrove_infrared[index].pin == pin)
    	{
        	OhiGrove_infrared[index].enable = TRUE;
    		return;
    	}
    }
}

void OhiGrove_disableInfrared (Gpio_Pins pin)
{
	uint8_t index;

	for (index = 0; index < OHIGROVE_DIGITAL_SIZE; ++index)
    {
    	if (OhiGrove_infrared[index].pin == pin)
    	{
        	OhiGrove_infrared[index].enable = FALSE;
        	Gpio_clear(pin);
    		return;
    	}
    }
}
