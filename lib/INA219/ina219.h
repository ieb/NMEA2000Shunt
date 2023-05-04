#pragma once

#include "Arduino.h"

#include <Wire.h>


// config bit map, register 0, only settings of interest
#define INA219_ADDRESS 0x40


// datasheet page 19 https://www.ti.com/lit/ds/symlink/ina219.pdf
# define IMA219_CONFIG_RUNNING 0b0000111001100111
//                       no reset|||-|---|---|--|
//                        not used|| |   |   |  |
//                          16v____| |   |   |  |
//                01 == 80mV shunt___|   |   |  |
//    1100 = 12bit 16samples 8.5ms_______|   |  |
//    1100 = 12bit 16samples 8.5ms___________|  |
//     Continuous_______________________________|
# define IMA219_CONFIG_STOPPED 0b0000111001100000
//                       no reset|||-|---|---|--|
//                        not used|| |   |   |  |
//                          16v____| |   |   |  |
//                01 == 80mV shunt___|   |   |  |
//    1100 = 12bit 16samples 8.5ms_______|   |  |
//    1100 = 12bit 16samples 8.5ms___________|  |
//     Power down_______________________________|

// registers
#define INA219_REG_CONFIG        0x00
#define INA219_REG_SHUNTVOLTAGE  0x01
#define INA219_REG_BUSVOLTAGE    0x02
#define INA219_REG_POWER         0x03
#define INA219_REG_CURRENT       0x04
#define INA219_REG_CALIBRATION   0x05


#define I2C_OK                   0 // OK
#define I2C_TX_TOO_LONG          1 //: data too long to fit in transmit buffer.
#define I2C_ADDR_NAC             2 //: received NACK on transmit of address.
#define I2C_TX_NAC               3 //: received NACK on transmit of address.
#define I2C_ERROR_OTHER          4 //: other error.
#define I2C_TIMEOUT              5 //: timeout
#define I2C_READ_INCOMPLETE     16 //: incomplete read




class Ina219 {
  public:
    Ina219(UartClass *_debug, uint8_t _address=INA219_ADDRESS): 
      debug{_debug},
      address{_address} {};
    uint8_t begin() {
      Wire.begin();
      return powerDown(false);
    };
    /**
     * Get voltage in V
     */
    double getVoltage() {
      int16_t raw = readRegister(INA219_REG_BUSVOLTAGE);
      if ( error == I2C_OK ) {

        int16_t value  = raw >> 3;
        double v =  0.001f * (int16_t)(value * 4);
        if ( diagnostics ) {
          printId();
          debug->print(F("Voltage raw=")); 
          debug->print(raw,BIN);
          debug->print(F(" ready=")); 
          debug->print(value, BIN); 
          debug->print(F(" V=")); 
          debug->print(v,6);
          if ( raw&0x01 == 0x01 ) {
            debug->println(F("V overflow ")); 
          } else if ( raw&0x02 == 0x00 ) {
            debug->println(F("V not ready")); 
          } else {
            debug->println(F("V ok")); 
          }
        }
        return v;
      } else {
        printId();
        debug->print(F("I2C read voltage failed:"));
        debug->println(error);
        return 0;
      }
    }

    /**
     * Get current in A
     * This uses the shunt voltage directly, since the internals of the INA219 
     * only have 16 bit resolution when performing calculations from the shunt voltage
     * using the calibration register, and frankly, the datasheet is so badly written
     * at explaining how the whole thing works its simpler to do it here. Life's too short.
     */ 
    double getCurrent() {
      int16_t raw = readRegister(INA219_REG_SHUNTVOLTAGE);
      if ( error == I2C_OK ) {
        // PGA == /2 FSD +-80mV, lsb=10uV Figure 22, description is above the Figure.
        // best to look at table 7 page 22 to understand how the register is formatted.
        // and try entering decimal numbers in https://www.binaryconvert.com/result_signed_short.html
        // to convince yourself that its simply a int16 in the register. 
        // Datasheet is has a terrible explanation.
        // Would have been so simple to say.... its a 16bit signed int with LSB of 10uV, but it explains
        // how the value from the Shunt ADC is converted to the register to make it a 16bit signed int.
        // The accuracy of the reading is still 12bit.
        // page 21 of the datasheet https://www.ti.com/lit/ds/symlink/ina219.pdf
        double value = 0.01f*(raw+1); // in mV
        double c = currentFactor * value; // in A
        if ( diagnostics ) {
          printId();
          debug->print(F("Current  raw=")); 
          debug->print(raw); 
          debug->print(F(" V=")); 
          debug->print(value,6); 
          debug->print(F("mV C=")); 
          debug->print(c,6);
          debug->println(F("A")); 
        }
        return c;

      } else {
        printId();
        debug->print(F("I2C Error read current failed:"));
        debug->println(error);
        return 0;
      }
    };


    uint8_t getError() {
      return error;
    };

    uint8_t powerDown(bool down) {
      Wire.beginTransmission(address);
      int16_t config = down?IMA219_CONFIG_STOPPED:IMA219_CONFIG_RUNNING;
      Wire.write(INA219_REG_CONFIG);
      Wire.write(config>>8);
      Wire.write(config&0xff);      
      error =  Wire.endTransmission();

      if ( !down ) {
        int16_t value = readRegister(INA219_REG_CONFIG);
        if ( error == I2C_OK ) {
          if ( value == config ) {
            printId();
            debug->print(F("Config confirmed as "));
            debug->println(config);
          } else {
            printId();
            debug->print(F("Config failed requested: "));
            debug->print(config);
            debug->print(F(" set:"));
            debug->println(value);
          }
        } else {
          printId();
          debug->print(F("Failed to read back confg register "));
          debug->println(error);
        }
      }

      return error;
    };

    void setShutRange(double maxShutmV, double maxCurrent) {

        currentFactor = maxCurrent/maxShutmV;
    }

    void setDiagnostics(bool enabled) {
        diagnostics = enabled;
    };

private:
  UartClass *debug;
  uint8_t error;
  int8_t address;

  bool diagnostics = false;
  double currentFactor = 1.333333f; // A/mV 100/75 = 1.3333

  void printId() {
      debug->print(F("INA219:"));
  }

  int16_t readRegister(int8_t r) {
      Wire.beginTransmission(address);
      Wire.write(r);
      error = Wire.endTransmission();
      if ( error != 0) {
        printId();
        debug->print(F("I2C Failed to select register"));
        debug->println(r, HEX);
        return 0;
      }
      if ( Wire.requestFrom(address, 2) == 2 ) {
        error = I2C_OK;
        int16_t value = Wire.read()<<8 | Wire.read();
        if ( diagnostics ) {
          printId();
          debug->print(F("reg="));
          debug->print(r);
          debug->print(F(" v="));
          debug->println(value);

        }
        return value;
      } else {
        printId();
        debug->println(F("I2C Error read current incomplete"));
        error = I2C_READ_INCOMPLETE;
        return 0;
      }
  };

};




