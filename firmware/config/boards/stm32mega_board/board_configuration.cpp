/**
 * @file boards/core48/board_configuration.cpp
 *
 * @brief Configuration defaults for the core48 board
 *
 * @author Ben Brazdziunas,  2022
 */

#include "pch.h"

static void setInjectorPins() {
	engineConfiguration->injectionPinMode = OM_DEFAULT;

	engineConfiguration->injectionPins[0] = Gpio::B15;
	engineConfiguration->injectionPins[1] = Gpio::B14;
	engineConfiguration->injectionPins[2] = Gpio::B12;
	engineConfiguration->injectionPins[3] = Gpio::B13;
	engineConfiguration->injectionPins[4] = Gpio::A8;
	engineConfiguration->injectionPins[5] = Gpio::E7;
	engineConfiguration->injectionPins[6] = Gpio::E13;
	engineConfiguration->injectionPins[7] = Gpio::E10;
}

static void setIgnitionPins() {
	engineConfiguration->ignitionPinMode = OM_DEFAULT;

	engineConfiguration->ignitionPins[0] = Gpio::E2;
	engineConfiguration->ignitionPins[1] = Gpio::E3;
	engineConfiguration->ignitionPins[2] = Gpio::C13;
	engineConfiguration->ignitionPins[3] = Gpio::E6;
	engineConfiguration->ignitionPins[4] = Gpio::E4;
	engineConfiguration->ignitionPins[5] = Gpio::E5;
	engineConfiguration->ignitionPins[6] = Gpio::E0;
	engineConfiguration->ignitionPins[7] = Gpio::B9;
}


// TODO change !!! PE3 is error LED, configured in board.mk
Gpio getCommsLedPin() {
	return Gpio::G13;
}

Gpio getRunningLedPin() {
	return Gpio::G10;
}

Gpio getWarningLedPin() {
	return Gpio::G11;
}

static void 
setupVbatt() {
	// 5.6k high side/10k low side = 1.56 ratio divider
	engineConfiguration->analogInputDividerCoefficient = 1.56f;
	
	// 6.34k high side/ 1k low side
	engineConfiguration->vbattDividerCoeff = (6.34 + 1) / 1; 

	// Battery sense on PA7
	engineConfiguration->vbattAdcChannel = EFI_ADC_9;

	engineConfiguration->adcVcc = 3.3f;
}

static void setStepperConfig() {
	engineConfiguration->idle.stepperDirectionPin = Gpio::A8;
	engineConfiguration->idle.stepperStepPin = Gpio::C6;
	engineConfiguration->stepperEnablePin = Gpio::C7;
}

static void setupSdCard() {
	
	//SD CARD overwrites
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_3;		

	engineConfiguration->is_enabled_spi_3 = true;
	engineConfiguration->spi3sckPin = Gpio::C10;
	engineConfiguration->spi3misoPin = Gpio::C11;
	engineConfiguration->spi3mosiPin = Gpio::C12;
}

static void setupEGT() {
	
	//EGT overwrites

	engineConfiguration->spi2sckPin = Gpio::B13;
	engineConfiguration->spi2misoPin = Gpio::B14;
	engineConfiguration->spi2mosiPin = Gpio::B15;
	engineConfiguration->is_enabled_spi_2 = true;

	engineConfiguration->max31855spiDevice = SPI_DEVICE_2;
	engineConfiguration->max31855_cs[0] = Gpio::C8;
	engineConfiguration->max31855_cs[1] = Gpio::C9;
}


void setBoardConfigOverrides() {
	setupVbatt();
	setupSdCard();
	setStepperConfig();
	setupEGT();

	engineConfiguration->clt.config.bias_resistor = 2490;
	engineConfiguration->iat.config.bias_resistor = 2490;

	//SERIAL 
	engineConfiguration->binarySerialTxPin = Gpio::A9;
	engineConfiguration->binarySerialRxPin = Gpio::A10;
	engineConfiguration->tunerStudioSerialSpeed = SERIAL_SPEED;
	engineConfiguration->uartConsoleSerialSpeed = SERIAL_SPEED;



	//CAN 1 bus overwrites
	engineConfiguration->canRxPin = Gpio::D0;
	engineConfiguration->canTxPin = Gpio::D1;

	//CAN 2 bus overwrites
	engineConfiguration->can2RxPin = Gpio::B5;
	engineConfiguration->can2TxPin = Gpio::B6;

	//onboard lps22 barometer
	engineConfiguration->lps25BaroSensorScl = Gpio::B10;
	engineConfiguration->lps25BaroSensorSda = Gpio::B11;
}

static void setupDefaultSensorInputs() {

	engineConfiguration->afr.hwChannel = EFI_ADC_13; //PC3
	engineConfiguration->afr.hwChannel2 = EFI_ADC_0; //PA0
	setEgoSensor(ES_14Point7_Free);
	
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_2; //PB0
	engineConfiguration->map.sensor.type = MT_MPXH6400;
	
	engineConfiguration->baroSensor.hwChannel = EFI_ADC_NONE;

}


void setBoardDefaultConfiguration(void) {
	setInjectorPins();
	setIgnitionPins();
	setupDefaultSensorInputs();


	engineConfiguration->canWriteEnabled = true;
	engineConfiguration->canReadEnabled = true;
	engineConfiguration->canSleepPeriodMs = 50;

	engineConfiguration->canBaudRate = B500KBPS;
	engineConfiguration->can2BaudRate = B500KBPS;

	//ECU has two SD cards one fixed ine removable
	engineConfiguration->sdCardCsPin = Gpio::B3;
		
	strncpy(config->luaScript, R"(

	function onTick()

	end

    )", efi::size(config->luaScript));
}