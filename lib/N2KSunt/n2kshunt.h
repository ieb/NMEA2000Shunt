#pragma once
#include "SmallNMEA2000.h"


const char batteryTypes_0[] = "flooded";
const char batteryTypes_1[] = "Gel";
const char batteryTypes_2[] = "AGM";
const char batteryTypes_3[] = "unknown";

const char * const batteryTypes[] PROGMEM = {
    batteryTypes_0,
    batteryTypes_1,
    batteryTypes_2,
    batteryTypes_3,
};
const char supportsEquals_0[] = "no";
const char supportsEquals_1[] = "yes";
const char supportsEquals_2[] = "Error";
const char supportsEquals_3[] = "Unavailable";
const char * const supportsEquals[] PROGMEM = {
    supportsEquals_0,
    supportsEquals_1,
    supportsEquals_2,
    supportsEquals_3,
};
const char nominalVoltages_0[] = "6v";
const char nominalVoltages_1[] = "12v";
const char nominalVoltages_2[] = "24v";
const char nominalVoltages_3[] = "32v";
const char nominalVoltages_4[] = "62v";
const char nominalVoltages_5[] = "42v";
const char nominalVoltages_6[] = "48v";
const char * const nominalVoltages[] PROGMEM = {
    nominalVoltages_0,
    nominalVoltages_1,
    nominalVoltages_2,
    nominalVoltages_3,
    nominalVoltages_4,
    nominalVoltages_5,
    nominalVoltages_6
};
const char batteryChemistries_0[] = "Lead Acid";
const char batteryChemistries_1[] = "LiIon";
const char batteryChemistries_2[] = "NiCd";
const char batteryChemistries_3[] = "ZnO";
const char batteryChemistries_4[] = "NiMh";
const char * const batteryChemistries[] PROGMEM = {
    batteryChemistries_0,
    batteryChemistries_1,
    batteryChemistries_2,
    batteryChemistries_3,
    batteryChemistries_4
};

class N2kShunt : public SNMEA2000 {
    public:
      N2kShunt(byte addr,
        SNMEA2000DeviceInfo * devInfo, 
        const SNMEA2000ProductInfo * pinfo, 
        const SNMEA2000ConfigInfo * cinfo,
        const unsigned long *tx,
        const unsigned long *rx,
        const uint8_t csPin
        ): SNMEA2000{addr, devInfo, pinfo, cinfo, tx, rx, csPin} {};

    /**
     * DC Battery Status PGN 127508
     * batteryInstance starting a 0
     * SID sequence id 
     * batterVoltage in volts
     * batterTemperature in K
     * batteryCurrent in A
     * 
     * Transmitted every 1500ms
     */ 
    void sendDCBatterStatusMessage(
            uint8_t batteryInstance=0, 
            uint8_t sid=0,
            double batteryVoltage = SNMEA2000::n2kDoubleNA, // V
            double batteryTemperature = SNMEA2000::n2kDoubleNA, // K
            double batteryCurrent = SNMEA2000::n2kDoubleNA // A
        );

    /**
     * batteryInstance starting a 0
     * batteryType default 2, 0 = flooded, 1 = Gel, 2 = AGM, 3 = unknown
     * supportsEqual default 0, 0 = no, 1 = yes, 2 = Error, 3 = Unavailable.
     * nominalVoltage default 1, 1 = 12v, 2= 24v, 3 = 32v, 4 = 62v, 5 = 42v, 6 = 48v.
     * batterChemistry 
     * batteryCapacity in Coulombs multiply Ah by 0.000277778 to get Coulmbs
     * batteryTemperatureCoeficient in percent, signed int
     * peukert Peurket exponent calculated from datasheet 1.10-1.25 for lead acid
     * chargeEfficiencyFactor in percent, signed int
     * 
     * 
     * Peurket equation, for info
     *  k = (log(t2)-log(t1))/(log(c1/t1)) - log(c1/t2))
     * where k - peurket exponent, 1.0-1.5  for lead acid 1.10-1.25,
     *       t1, c1 - discarge rate 1 and capacity. eg C5 
     *       t2, c2 - discharge rate 2 and capacity eg C20
     * 
     * This message is not sent periodically, only when available or requested.
     * see https://canboat.github.io/canboat/canboat.html for additional details 
     */ 
    void sendBatteryConfigurationStatusMessage(
            uint8_t batteryInstance = 0, 
            uint8_t batteryType = 2, 
            uint8_t supportsEqual = 0,
            uint8_t nominalVoltage = 1, 
            uint8_t batteryChemistry = 1, 
            double batteryCapacity  = SNMEA2000::n2kDoubleNA, 
            int8_t batteryTemperatureCoeficient = SNMEA2000::n2kInt8NA, 
            double peukert = SNMEA2000::n2kDoubleNA,
            int8_t chargeEfficiencyFactor =  SNMEA2000::n2kInt8NA);

    /**
     * batteryInstance starting a 0
     * sid sequence id
     * dcType default 0, 0 = battery, 1 = alternator, 2 = converter, 3 = solar cell, 4 = wind generator
     * stateOfCharge in %
     * stateOfHealth in %
     * timeRemaining in seconds
     * rippleVoltage in V
     * batteryCapacity in Coulombs multiply Ah by 0.000277778 to get Coulmbs
     * 
     * Transmitted every 1500ms
     */ 
    void N2kShunt::sendDCDetailedStatusMessage(
            uint8_t batteryInstance = 0, 
            uint8_t sid = 0,
            uint8_t dcType = 0, 
            uint8_t stateOfCharge = SNMEA2000::n2kInt8NA, 
            uint8_t stateOfHealth = SNMEA2000::n2kInt8NA,
            double timeRemaining = SNMEA2000::n2kDoubleNA, 
            double rippleVoltage = SNMEA2000::n2kDoubleNA, 
            double capacity = SNMEA2000::n2kDoubleNA);


    private:
        void output1ByteUDouble(double value, double precision, double undefValue);

};






