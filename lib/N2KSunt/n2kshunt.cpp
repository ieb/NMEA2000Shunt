#include "n2kshunt.h"


// should really be in SmallNMEA2000
void N2kShunt::output1ByteUDouble(double value, double precision, double undefValue) {
    if (value == undefValue) {
        outputByte(0xff);
    } else {
        double vd=value/precision;
        vd = round(vd);
        uint8_t i = (vd>=0 && vd<0xfe)?(uint8_t)vd:0xfe;
        outputByte(i);
    }

}


void N2kShunt::sendDCBatterStatusMessage(
    uint8_t batteryInstance, 
    uint8_t sid,
    double batteryVoltage,  // V
    double batteryTemperature, // K
    double batteryCurrent // A
    ) {
    MessageHeader messageHeader(127508L, 6, getAddress(), SNMEA2000::broadcastAddress);
    startPacket(&messageHeader);
    outputByte(batteryInstance);  
    output2ByteUDouble(batteryVoltage,0.01); // might be unsigned, canbot says unsigned.
    output2ByteDouble(batteryCurrent,0.1);
    output2ByteUDouble(batteryTemperature,0.01);
    outputByte(sid);
    finishPacket();
}




void N2kShunt::sendBatteryConfigurationStatusMessage(
    uint8_t batteryInstance, 
    uint8_t batteryType, // 0 = flooded, 1 = Gel, 2 = AGM, 3 = unknown
    uint8_t supportsEqual, // 0 = no, 1 = yes, 2 = Error, 3 = Unavailable.
    uint8_t nominalVoltage, // 0 = 6v, 1 = 12v, 2= 24v, 3 = 32v, 4 = 62v, 5 = 42v, 6 = 48v.
    uint8_t batteryChemistry, // 0 = LeadAcid, 1 = LiIon, 2 = NiCd, 3 = Zn0, 4 = NiMh
    double batteryCapacity, // in Coulombs 
    int8_t batteryTemperatureCoeficient, // 0-5% in 10s, 100 for 50 for Lipo 
    double peukert, // typically 1.25 for leadAcid adn 1.05 for LiPo.
    int8_t chargeEfficiencyFactor // in percent 95 for leadAcid,  99 for lipo.
	) {
	MessageHeader messageHeader(127513L, 6, getAddress(), SNMEA2000::broadcastAddress);
    startPacket(&messageHeader);
    outputByte(batteryInstance);  
    // xxSSTTTT  xx=reserved, SS=supports, TTTT=batteryType
    outputByte(0x0C | ((supportsEqual & 0x0f)<<4) | (batteryType&0x0f)); 
    // ccccvvvv cccc=chemistry, vvvv=nominal voltage.
    outputByte(((batteryChemistry & 0x0f) << 4) | (nominalVoltage & 0x0f));
    // as amper seconds.
    output2ByteUDouble(batteryCapacity, 3600); 
    outputByte(0xff&batteryTemperatureCoeficient);  // as signed int bits
    if ( peukert<1 || peukert > 1.505) { 
    	outputByte(0xff); 
    } else {
    	// 8 bit unsigned, 1-1.506 === 0-253
    	output1ByteUDouble(peukert-1,0.002,-1);
    }
    outputByte(0xff&chargeEfficiencyFactor); // as signed int bits
    finishPacket();
}

// need to send this when requested.
// not transmitted at a regular interval.
// every 1500ms.
void N2kShunt::sendDCDetailedStatusMessage(
    uint8_t batteryInstance, 
    uint8_t sid,
    uint8_t dcType, // 0 = battery, 1 = alternator, 2 = converter, 3 = solar cell, 4 = wind generator
    uint8_t stateOfCharge, // % stage of charge
    uint8_t stateOfHealth, // % state of health
    double timeRemaining, // time remaining in seconds
    double rippleVoltage, // ripple voltage in V
    double capacity
	) {
	MessageHeader messageHeader(127506L, 6, getAddress(), SNMEA2000::broadcastAddress);
    startPacket(&messageHeader);
    outputByte(sid);  
    outputByte(batteryInstance);  
    outputByte(dcType);
    outputByte(stateOfCharge);
    outputByte(stateOfHealth);
    output2ByteUDouble(timeRemaining,60);
    output2ByteUDouble(rippleVoltage,0.001);
    output2ByteUDouble(capacity,3600);
    finishPacket();

}


