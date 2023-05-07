#include "n2kshunt.h"




void N2kShunt::sendDCBatterStatusMessage(
    uint8_t batteryInstance, 
    uint8_t sid,
    double batteryVoltage,  // V
    double batteryTemperature, // K
    double batteryCurrent // A
    ) {
    MessageHeader messageHeader(127508L, 6, getAddress(), SNMEA2000::broadcastAddress);
    // single frame message
    startPacket(&messageHeader);
    outputByte(batteryInstance);  
    output2ByteUDouble(batteryVoltage,0.01); // might be unsigned, canbot says unsigned.
    output2ByteDouble(batteryCurrent,0.1);
    output2ByteUDouble(batteryTemperature,0.01);
    outputByte(sid);
    finishPacket();
}


/**
 * There is some confusion over the length of this message.
 * CanBoat says its a 10byte fast packet https://github.com/canboat/canboat/issues/316
 * NMEA2000 libraries say its an 8 byte packet, https://github.com/ttlappalainen/NMEA2000/blob/master/src/N2kMessages.cpp#L793
 * The CanBoat code has had more work done on it and is more recent therfore I am defaulting to that
 */

void N2kShunt::sendBatteryConfigurationStatusMessage(
	MessageHeader *requestMessageHeader,
    uint8_t batteryInstance, 
    uint8_t batteryType, // 0 = flooded, 1 = Gel, 2 = AGM, 3 = unknown
    uint8_t supportsEqual, // 0 = no, 1 = yes, 2 = Error, 3 = Unavailable.
    uint8_t nominalVoltage, // 0 = 6v, 1 = 12v, 2= 24v, 3 = 32v, 4 = 62v, 5 = 42v, 6 = 48v.
    uint8_t batteryChemistry, // 0 = LeadAcid, 1 = LiIon, 2 = NiCd, 3 = Zn0, 4 = NiMh
    double batteryCapacity, // in C  
    int8_t batteryTemperatureCoeficient, // 0-5% in 10s, 100 for 50 for Lipo 
    double peukert, // typically 1.25 for leadAcid adn 1.05 for LiPo.
    int8_t chargeEfficiencyFactor // in percent 95 for leadAcid,  99 for lipo.
	) {
	uint8_t target = SNMEA2000::broadcastAddress;
	if ( requestMessageHeader != NULL ) {
		target = requestMessageHeader->source;
	}
	MessageHeader messageHeader(127513L, 6, getAddress(), target);
	// 127513L defaults to Fast packet messages
    startFastPacket(&messageHeader, 8);

    outputByte(batteryInstance);  
    // xxSSTTTT  xx=reserved, SS=supports, TTTT=batteryType
    outputByte(0xC0 | ((supportsEqual & 0x0f)<<4) | (batteryType&0x0f)); 
    // ccccvvvv cccc=chemistry, vvvv=nominal voltage.
    outputByte(((batteryChemistry & 0x0f) << 4) | (nominalVoltage & 0x0f));
    output2ByteUDouble(batteryCapacity, 3600 ); // send in Ah not C, if it was C then 300Ah is > 1E6 C which doesnt fit in 16bits.
    outputByte(0xff&batteryTemperatureCoeficient);  // as signed int bits
    if ( peukert<1 || peukert > 1.505) { 
    	outputByte(0xff); 
    } else {
    	// 8 bit unsigned, 1-1.506 === 0-253
    	// or 1 bit == 0.002 with an offset of 500.
    	outputByte(0xff&((int)(peukert/0.002)-500));
    }
    outputByte(0xff&chargeEfficiencyFactor); // as signed int bits
    finishFastPacket();

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
    double capacity // in C
	) {
	MessageHeader messageHeader(127506L, 6, getAddress(), SNMEA2000::broadcastAddress);
	// fast packet message
    startFastPacket(&messageHeader,11);
    outputByte(sid);  
    outputByte(batteryInstance);  
    outputByte(dcType);
    outputByte(stateOfCharge);
    outputByte(stateOfHealth);
    output2ByteUDouble(timeRemaining,60);
    output2ByteUDouble(rippleVoltage,0.001);
    output2ByteUDouble(capacity,3600);
    finishFastPacket();
}


