#pragma once;

#include <Arduino.h>
#include <avr/eeprom.h>


typedef struct Config {
    uint8_t serialNumber;
    uint8_t deviceAddress;
    uint8_t batteryInstance;
    uint8_t batteryType;
    uint8_t supportsEqualisation;
    uint8_t nominalVoltage;
    uint8_t batteryChemistry;
    int8_t  chargeEfficiencyFactor;
    int8_t  batteryTemperatureCoeficient; 
    uint16_t batteryCapacityAh; // in Ah
    double peukert;
    double shuntReading;
    double shuntCurrent;
    uint16_t crc;
} _Config;





class ConfigSettings {
    public:
        ConfigSettings() {
            factoryReset();
        };
        bool load() {
            Config epromConfig;
            eeprom_read_block((void*)&epromConfig, (const void*)0, sizeof(Config));
            uint16_t crcv =  modbus_crc16((uint8_t *)&config, sizeof(Config)-2);
            if ( crcv == epromConfig.crc ) {
                memcpy( &config, &epromConfig, sizeof(Config));
                return true;
            }
            return false;
        }
        void save() {
            config.crc =  modbus_crc16((uint8_t *)&config, sizeof(Config)-2);
            eeprom_update_block((const void*)&config, (void*)(0), sizeof(Config));
        }

        void factoryReset() {
            config.serialNumber = 2;
            config.deviceAddress = 26;
            config.batteryInstance = 1;
            config.batteryType = 2; // AGM
            config.supportsEqualisation = 0; // no
            config.nominalVoltage = 1; // 12v
            config.batteryChemistry = 0; // leadAcig
            config.chargeEfficiencyFactor = 95; // % lead acid
            config.batteryTemperatureCoeficient = 5; // %
            config.batteryCapacityAh = 300;  // in Ah
            config.peukert = 1.25;
            config.shuntReading = 75;
            config.shuntCurrent = 100;
        }




        /**
         * @brief crc for mdbus, polynomial = 0x8005, reverse in, reverse out, init 0xffff;
         * 
         * @param array 
         * @param length 
         * @return uint16_t 
         */
        uint16_t modbus_crc16(const uint8_t *array, uint16_t length) {
            uint16_t crc = 0xffff;
            while (length--) {
                if ((length & 0xFF) == 0) yield();  // RTOS
                uint8_t data = *array++;
                data = (((data & 0xAA) >> 1) | ((data & 0x55) << 1));
                data = (((data & 0xCC) >> 2) | ((data & 0x33) << 2));
                data =          ((data >> 4) | (data << 4));
                crc ^= ((uint16_t)data) << 8;
                for (uint8_t i = 8; i; i--) {
                if (crc & (1 << 15)) {
                    crc <<= 1;
                    crc ^= 0x8005;
                } else {
                    crc <<= 1;
                }
                }
            }
            crc = (((crc & 0XAAAA) >> 1) | ((crc & 0X5555) << 1));
            crc = (((crc & 0xCCCC) >> 2) | ((crc & 0X3333) << 2));
            crc = (((crc & 0xF0F0) >> 4) | ((crc & 0X0F0F) << 4));
            //  crc = (( crc >> 8) | (crc << 8));
            //  crc ^= endmask;
            return crc;
        };

        Config config;
};