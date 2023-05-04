#pragma once

#include "config.h"


const char menuOptions_0[] = "Serial Number";
const char menuOptions_1[] = "Device addres";
const char menuOptions_2[] = "Battery Instance";
const char menuOptions_3[] = "Battery Type";
const char menuOptions_4[] = "Equalisation Support";
const char menuOptions_5[] = "Nominal Voltage";
const char menuOptions_6[] = "Battery Chemisty";
const char menuOptions_7[] = "Charge Efficienct Factor(%)";
const char menuOptions_8[] = "Battery Temperature Coefficient(%)";
const char menuOptions_9[] = "Battery Capacity(Ah)";
const char menuOptions_10[] = "Puerkey Constant";
const char menuOptions_11[] = "Shunt Current(A)";
const char menuOptions_12[] =  "Shunt Measurement(mV)";
const char menuOptions_13[] = "Save settings and restart";
const char menuOptions_14[] = "Quit and restart";

const char * const menuOptions[] PROGMEM = {
    menuOptions_0,
    menuOptions_1,
    menuOptions_2,
    menuOptions_3,
    menuOptions_4,
    menuOptions_5,
    menuOptions_6,
    menuOptions_7,
    menuOptions_8,
    menuOptions_9,
    menuOptions_10,
    menuOptions_11,
    menuOptions_12,
    menuOptions_13,
    menuOptions_14
};
const char menuKey[] PROGMEM = "0123456789abcSQ";


class CommandLine {
    public:
        CommandLine(UartClass * io, ConfigSettings * settings) : 
            io{io},
            settings{settings} {};
        bool diagnosticsEnabled = false;


        void begin() {
            loadSettings();
        };

        void showHelp() {
            io->println(F("Shunt Monitor - key presses"));
            io->println(F("  - 'h' or '?' to show this message"));
            io->println(F("  - 's' show status"));
            io->println(F("  - 'c' show config"));
            io->println(F("  - 'd' toggle diagnostics"));
            io->println(F("  - 'r' read sensor"));            
            io->println(F("  - 'S' setup"));
            io->println(F("  - 'R' reboot"));
            io->println(F("  - 'F' factory reset"));
        };

        bool checkCommand() {
            if (io->available()) {
                char chr = io->read();
                switch ( chr ) {
                    case 'h': showHelp(); return true;
                    case 's': showStatus(); return true;
                    case 'c': showConfig(); return true;
                    case 'r': 
                        if ( readSensors != NULL ) {
                            readSensors();  
                        } else {
                            Serial.println(F("No sensors available"));
                        }
                        return true;
                    case 'S': doSetup(); return true;
                    case 'R': doReset(); return true;
                    case 'F': 
                        settings->factoryReset(); 
                        settings->save();
                        io->println("Reset to Factory Settings");
                        showConfig();
                        return true;
                    case 'd': toggleDiagnostics(); return true;
                }
            }
            return diagnosticsEnabled;
        };

        void setCallbacks(void (*_statusCallback)(void) = NULL, void (*_readSensors)(void) = NULL) {
            statusCallback = _statusCallback;
            readSensors = _readSensors;
        };

    private:
        UartClass * io;
        ConfigSettings *settings;

        void (*statusCallback)(void) = NULL;
        void (*readSensors)(void) = NULL;

        void doReset() {
            _PROTECTED_WRITE(RSTCTRL.SWRR, 1);
        }

        void toggleDiagnostics() {
            diagnosticsEnabled = !diagnosticsEnabled;
        };



        void loadSettings() {
            if ( settings->load() ) {
                io->println(F("Eprom Valid"));
            } else {
                io->println(F("Eprom Not Valid, saving current settings"));
                settings->save();
            }
            showConfig();

        };


        void printHeader(uint8_t id, char end=':' ) {
            io->print((char)pgm_read_byte_near(menuKey + id));
            io->print(". ");
            char buffer[36];
            strcpy_P(buffer, (char*)pgm_read_word(&(menuOptions[id])));
            io->print(buffer);
            if ( end != 0) {
                for (int8_t i = strlen(buffer); i< 35;i++) {
                    io->print(' ');
                }
                io->print(end);
                io->print(' ');
            }
        }

        void printStatus_P(uint8_t id, const char * const lookup[], uint8_t idx ) {
            printHeader(id);
            char buffer[20];
            strcpy_P(buffer, (char*)pgm_read_word(&(lookup[idx])));
            io->println(buffer);
        }

        void printStatus(uint8_t id, int16_t value) {
            printHeader(id);
            io->println(value);
        }
        void printStatus(uint8_t id, uint16_t value) {
            printHeader(id);
            io->println(value);
        }
        void printStatus(uint8_t id, double value) {
            printHeader(id);
            io->println(value);
        }

        void printAllStatus() {
            printStatus(0,settings->config.serialNumber);
            printStatus(1,settings->config.deviceAddress);
            printStatus(2,settings->config.batteryInstance);
            printStatus_P(3,batteryTypes, settings->config.batteryType);
            printStatus_P(4,supportsEquals, settings->config.supportsEqualisation);
            printStatus_P(5,nominalVoltages, settings->config.nominalVoltage);
            printStatus_P(6,batteryChemistries, settings->config.batteryChemistry);
            printStatus(7,settings->config.chargeEfficiencyFactor);
            printStatus(8,settings->config.batteryTemperatureCoeficient);
            printStatus(9,settings->config.batteryCapacityAh);
            printStatus(10,settings->config.peukert);
            printStatus(11,settings->config.shuntCurrent);
            printStatus(12,settings->config.shuntReading);
        }

        void doSetup() {
            showConfig();
            io->setTimeout(30000);
            while(true) {
                while(io->available()) {
                    io->read();
                }
                io->println(F("Setup Menu"));
                printAllStatus();
                printHeader(13,0);io->println("");
                printHeader(14,0);io->println("");
                char option = io->read();
                while (option == -1) {
                    delay(10);
                    option = io->read();
                }
                uint8_t idx = 255;
                for ( int i = 0; i < 15; i++) {
                    if ( option == pgm_read_byte_near(menuKey + i )) {
                        idx = i;
                    }
                }
                if ( idx == 255 ) {
                    Serial.print(F(" not recognised "));
                    Serial.println(option);
                    continue;
                }
                printHeader(idx,0);io->print(" ");
                char *  const * options;
                uint8_t noptions = 0;
                switch(idx) {
                    case 3:
                        options = batteryTypes;
                        noptions = 4;
                        break;
                    case 4:
                        options = supportsEquals;
                        noptions = 4;
                        break;
                    case 5:
                        options = nominalVoltages;
                        noptions = 7;
                        break;
                    case 6:
                        options = batteryChemistries;
                        noptions = 5;
                        break;
                }
                {
                    char buffer[20];
                    for (int i = 0; i < noptions; i++) {
                        io->print(i);
                        io->print(":");
                        strcpy_P(buffer, (char*)pgm_read_word(&(options[i])));
                        io->print(buffer);
                        io->print(", ");
                    }
                }
                io->print(F(" >"));
                switch(idx) {
                    case 0: read(&(settings->config.serialNumber)); break;
                    case 1: read(&(settings->config.deviceAddress)); break;
                    case 2: read(&(settings->config.batteryInstance)); break;
                    case 3: read(&(settings->config.batteryType), 0, noptions); break;
                    case 4: read(&(settings->config.supportsEqualisation), 0, noptions); break;
                    case 5: read(&(settings->config.nominalVoltage), 0, noptions); break;
                    case 6: read(&(settings->config.batteryChemistry), 0, noptions); break;
                    case 7: read(&(settings->config.chargeEfficiencyFactor), 0, 100); break;
                    case 8: read(&(settings->config.batteryTemperatureCoeficient), -100, 100); break;
                    case 9: read(&(settings->config.batteryCapacityAh)); break;
                    case 10: read(&(settings->config.peukert), 1.0, 1.5); break;
                    case 11: read(&(settings->config.shuntCurrent), 0, 500); break;
                    case 12: read(&(settings->config.shuntReading), 0, 200); break;
                    case 13:
                        settings->save();
                        doReset();
                        break;
                    case 14:
                        doReset();
                        break;
                }
            }
            io->setTimeout(0);
        };

        void showConfig() {
            io->println(F("Config"));
            printAllStatus();
        }



        void showStatus() {
            io->println(F("Status"));
            if ( statusCallback != NULL ) {
                statusCallback();
            }
            io->print((F("MCU V=")));
            io->print(readMCUVoltage());
            io->print((F("mV T=")));
            io->print(readMCUTemperature());
            io->println((F("C")));
        };


        int16_t readMCUVoltage() {
            analogReference(INTERNAL1V024);
            delayMicroseconds(100);
            int32_t vddmeasure = analogReadEnh(ADC_VDDDIV10, 12); // Take it at 12 bits
            vddmeasure *= 10; // since we measured 1/10th VDD
            int16_t returnval = vddmeasure >> 2; // divide by 4 to get into millivolts.
            if (vddmeasure & 0x02) {
                // if last two digits were 0b11 or 0b10 we should round up
                returnval++;
            }
            return returnval;
        }

        int16_t readMCUTemperature() {
            int8_t sigrowOffset = SIGROW.TEMPSENSE1;
            uint8_t sigrowGain = SIGROW.TEMPSENSE0;
            analogSampleDuration(128); // must be >= 32µs * f_CLK_ADC per datasheet 30.3.3.7
            analogReference(INTERNAL1V024);
            uint32_t reading = analogRead(ADC_TEMPERATURE);
            reading -= sigrowOffset;
            reading *= sigrowGain;
            reading += 0x80; // Add 1/2 to get correct rounding on division below
            reading >>= 8; // Divide result to get Kelvin
            return reading - 273; // return in C
        }


        bool readLong(long *l) {
            String line = io->readStringUntil('\r');
            line.trim();
            if ( line.length() > 0 ) {
                *l = line.toInt();
                return true;
            }
            return false;
        }

        void read(uint8_t *v, uint8_t min=0, uint8_t max=255) {
            long l;
            if ( readLong(&l) ) {
                if ( l >= min && l <= max ) {
                    *v = l;
                }
            }
        }
        void read(int8_t *v, int8_t min=-127, int8_t max=127) {
            long l;
            if ( readLong(&l) ) {
                if ( l >= min && l <= max ) {
                    *v = l;
                }
            }
        }
        void read(int16_t *v, int16_t min=0, int16_t max=0xffff) {
            long l;
            if ( readLong(&l) ) {
                if ( l >= min && l <= max ) {
                    *v = l;
                }
            }
        }
        void read(double *v, double min=0, double max=1e8) {
            String line = io->readStringUntil('\r');
            line.trim();
            if ( line.length() > 0 ) {
                double d = line.toDouble();
                if ( d >= min && d <= max ) {
                    *v = d;
                }
            }
        }






};


