
#include <Arduino.h>
#include <Wire.h>



#include "n2kshunt.h"
#include "commandline.h"
#include "ina219.h"
#include "config.h"
#include "ntcsensor.h"

// Hardware
// Vcc chip pin 1
#define TEMP1_PIN PIN_PA4 // chip pin 2
#define CANCS_PIN PIN_PA5 // chip pin 3
#define LED_PIN PIN_PA6 // chip pin 4
// PIN_PA7 not used       // chip pin 5
#define RX0_PIN   PIN_PB3 // chip pin 6, default
#define TX0_PIN   PIN_PB2 // chip pin 7, default
#define SDA_PIN   PIN_PB1 // chip pin 8, cant be moved.
#define SCL_PIN   PIN_PB0 // chip pin 9, cant be moved.
#define UDPI_PIN  PIN_PA0 // chip pin 10, cant be moved.
#define MOSI_PIN  PIN_PB1 // chip pin 11, default
#define MIS0_PIN  PIN_PB2 // chip pin 12, default
#define SCK_PIN   PIN_PB3 // chip pin 13, default
// GND chip pin 14

//  Check and update https://ieb.github.io/notes/ to get a clean address.
#define DEVICE_ADDRESS 26



// default serial for debug, serial 1 not used.
#define debug Serial


// configure CAN device
const SNMEA2000ProductInfo productInfomation PROGMEM={
                                       1300,                        // N2kVersion
                                       45,                         // Manufacturer's product code
                                       "Shunt",    // Manufacturer's Model ID
                                       "1.0.0.1 (2023-04-26)",     // Manufacturer's Software version code
                                       "1.0.0.2 (2023-04-26)",      // Manufacturer's Model version
                                       "0000003",                  // Manufacturer's Model serial code
                                       0,                           // SertificationLevel
                                       1                            // LoadEquivalency
};
const SNMEA2000ConfigInfo configInfo PROGMEM={
      "Battery Shunt",
      "Luna Technical Area",
      "https://github.com/ieb/NMEA2000Shunt"
};

uint8_t pgnEnableRegister = 0xff;


const unsigned long txPGN[] PROGMEM = { 
	127506L, // detailed DC status
	127513L, // battery configuration status
	127508L, // battery status message
    SNMEA200_DEFAULT_TX_PGN
};
const unsigned long rxPGN[] PROGMEM = { 
  SNMEA200_DEFAULT_RX_PGN
};

const SNMEA2000DeviceInfo devInfo = SNMEA2000DeviceInfo(
  02,   // device serial number
  170,  // Battery
  35    // Power
);



ConfigSettings settings;

Ina219 ina219(&debug);
CommandLine commandLine(&debug, &settings);
NtcSensor ntcSensor(&debug, TEMP1_PIN);


bool ina219Ok = false;
bool canOk = false;



N2kShunt n2kShunt = N2kShunt(DEVICE_ADDRESS, 
          &devInfo, 
          &productInfomation, 
          &configInfo, 
          &txPGN[0], 
          &rxPGN[0],
          CANCS_PIN
);
//          CANCS_PIN


void blink() {
	static unsigned long lastBlink = 0;
	static uint8_t led_state = 0;
	static unsigned long nextDelay = 3000;
	unsigned long now = millis();
	if ((now - lastBlink) > nextDelay ) {
		led_state = !led_state;
		digitalWrite(LED_PIN, led_state);
		if ( canOk && ina219Ok ) {
			if (!led_state) {
				// short bink dont block main thread.
				nextDelay = 250;
			} else {
				nextDelay = 6000;
			}
		} else if ( !led_state ) {
			nextDelay = 3000;
			// indicate a fault condition.
			// its ok to block the main thread as something is failing.
			// 3 flashes = can fail.
			// 2 flashes = ina219 fail.
			// 5 flashes == both failed.
			if (!canOk ) {
				for(int i = 0; i < 3; i++) {
					delay(250);
					digitalWrite(LED_PIN, HIGH);
					delay(250);
					digitalWrite(LED_PIN, LOW);
				}
			} 
			if (!ina219Ok) {
				for(int i = 0; i < 2; i++) {
					delay(250);
					digitalWrite(LED_PIN, HIGH);
					delay(250);
					digitalWrite(LED_PIN, LOW);
				}
			}
		    delay(250);
			digitalWrite(LED_PIN, HIGH);
		    delay(250);
			digitalWrite(LED_PIN, LOW);
		}
		lastBlink = millis();

	}

}



void readSensors() {
	debug.print(F(" v="));debug.print(ina219.getVoltage());
	debug.print(F(" mV c="));debug.print(ina219.getCurrent());
	double tempK = ntcSensor.getTemperature();
	debug.print(F(" A t="));debug.print(ntcSensor.getTemperature());
	debug.print(F(" K "));debug.print(ntcSensor.getTemperature()-273.15);
	debug.print(F(" C tons="));debug.print(millis());
	debug.println("");
}

void showStatus() {
	n2kShunt.dumpStatus();
}





void sendReading() {
	static unsigned long lastRead = 0;
	static uint8_t sid = 0;
	unsigned long now = millis();
	if ((now - lastRead) > 1500 ) {
		lastRead = now;
		sid++;
		double batteryTemperature = ntcSensor.getTemperature();
		double batteryVoltage = ina219.getVoltage();
		double batteryCurrent = ina219.getCurrent();
		n2kShunt.sendDCBatterStatusMessage(
			settings.config.batteryInstance,
			sid,
			batteryVoltage,
			batteryTemperature,
			batteryCurrent);
		// Not emitting Detailed DC battery status, as the calculations would almost certainly
		// be wrong. Better to rely on voltage and current and common sense.
	}
}

void sendBatteryConfigurationStatus() {
	static unsigned long lastSend = 0;
	unsigned long now = millis();
	if ((now - lastSend) > 15000 ) {
		lastSend = now;
		n2kShunt.sendBatteryConfigurationStatusMessage(
			NULL,
			settings.config.batteryInstance,
			settings.config.batteryType,
			settings.config.supportsEqualisation,
			settings.config.nominalVoltage,
			settings.config.batteryChemistry,
			settings.config.batteryCapacityAh * 3600.0,
			settings.config.batteryTemperatureCoeficient,
			settings.config.peukert,
			settings.config.chargeEfficiencyFactor);
	}		

}


bool isoRequestHandler(unsigned long requestedPGN, MessageHeader *messageHeader, byte * buffer, int len) {
	if ( requestedPGN == 127513L ) {
		n2kShunt.sendBatteryConfigurationStatusMessage(
			messageHeader,
			settings.config.batteryInstance,
			settings.config.batteryType,
			settings.config.supportsEqualisation,
			settings.config.nominalVoltage,
			settings.config.batteryChemistry,
			settings.config.batteryCapacityAh * 3600.0,
			settings.config.batteryTemperatureCoeficient,
			settings.config.peukert,
			settings.config.chargeEfficiencyFactor);		
		return true;
	}
	return false;
}





void setup() {

  // Open serial communications and wait for port to open:
  debug.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  // try 115200, if that fails drop back to 9600 and set.

  debug.println(F("NMEA2000 Shunt - Booting....."));

  if ( ina219.begin() != I2C_OK) {
  	ina219Ok = false;
	debug.print(F("Failed to find INA219 chip, error:"));
	debug.println(ina219.getError());
 	debug.println(F("INA219 not responding"));
  } else {
  	ina219Ok = true;
  }

  commandLine.setCallbacks(&showStatus, &readSensors);
  commandLine.begin();




  commandLine.diagnosticsEnabled = false;


  debug.print(F("Shunt: "));
  debug.print(settings.config.shuntReading);
  debug.print(F("mV/"));
  debug.print(settings.config.shuntCurrent);
  debug.println(F("A"));
  ina219.setShutRange( settings.config.shuntReading, settings.config.shuntCurrent);

  debug.println(F("Opening CAN"));
  debug.print("CS Pin in main ");debug.println(CANCS_PIN);
  // only set on reboot.
  n2kShunt.setSerialNumber(settings.config.serialNumber);
  n2kShunt.setDeviceAddress(settings.config.deviceAddress);
  n2kShunt.setIsoRequestHandler(&isoRequestHandler);
  if ( !n2kShunt.open() ) {
  	canOk = false;
    debug.println(F("Failed to start NMEA2000, retry in 5s"));
    delay(5000);
  } else {
  	canOk = true;
  }
  debug.println(F("Opened, MCP2515 Operational"));
  debug.println(F("Running..."));
  debug.println(F("Press h for help menu"));


}




void loop() {
  static bool diagnosticsEnabled = false;
  
  if ( !canOk ) {
  	canOk = n2kShunt.open();
  };
  blink();
  sendReading();
  sendBatteryConfigurationStatus();
  n2kShunt.processMessages();
  if ( commandLine.checkCommand() ) {
  	if (!diagnosticsEnabled ) {
	  	n2kShunt.setDiagnostics(true);
	  	ina219.setDiagnostics(true);
	  	ntcSensor.setDiagnostics(true);
		diagnosticsEnabled = true;  		
  	}
  } else {
  	if ( diagnosticsEnabled ) {
	  	n2kShunt.setDiagnostics(false);
	  	ina219.setDiagnostics(false);
	  	ntcSensor.setDiagnostics(false);
		diagnosticsEnabled = false;  		
  	}

  }
}


