EESchema Schematic File Version 2
LIBS:NMEA2000Shunt-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:NMEA2000Shunt-cache
EELAYER 25 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L C C206
U 1 1 61053BCD
P 6750 1600
F 0 "C206" H 6750 1700 40  0000 L CNN
F 1 "10uF" H 6756 1515 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6788 1450 30  0001 C CNN
F 3 "" H 6750 1600 60  0000 C CNN
	1    6750 1600
	1    0    0    -1  
$EndComp
Text GLabel 6900 1150 2    60   Output ~ 0
5V
$Comp
L GND #PWR01
U 1 1 610553E6
P 6050 2050
F 0 "#PWR01" H 6050 2050 30  0001 C CNN
F 1 "GND" H 6050 1980 30  0001 C CNN
F 2 "" H 6050 2050 60  0001 C CNN
F 3 "" H 6050 2050 60  0001 C CNN
	1    6050 2050
	1    0    0    -1  
$EndComp
Text GLabel 5100 1150 0    60   Input ~ 0
12v
Wire Wire Line
	5100 1150 5650 1150
Wire Wire Line
	5350 1400 5350 1150
Connection ~ 5350 1150
Wire Wire Line
	6050 1450 6050 2050
Connection ~ 6050 1850
Wire Wire Line
	6450 1150 6900 1150
Wire Notes Line
	800  6000 900  6000
Connection ~ 6750 1150
$Comp
L C C201
U 1 1 616443DB
P 3000 3950
F 0 "C201" H 3000 4050 40  0000 L CNN
F 1 "100nF" H 3006 3865 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3038 3800 30  0001 C CNN
F 3 "" H 3000 3950 60  0000 C CNN
	1    3000 3950
	-1   0    0    1   
$EndComp
$Comp
L MCP2515 U101
U 1 1 61686923
P 3050 9450
F 0 "U101" H 3050 9450 60  0000 C CNN
F 1 "MCP2515" H 3050 9450 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-18W_7.5x11.6mm_Pitch1.27mm" H 3050 9450 60  0001 C CNN
F 3 "" H 3050 9450 60  0001 C CNN
	1    3050 9450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 8600 4400 8600
Text GLabel 4600 7800 2    60   Input ~ 0
5V
Wire Wire Line
	4400 9050 4050 9050
Wire Wire Line
	4050 9050 4050 8800
Wire Wire Line
	4050 8800 3900 8800
$Comp
L GND #PWR02
U 1 1 61688C26
P 5800 8650
F 0 "#PWR02" H 5800 8650 30  0001 C CNN
F 1 "GND" H 5800 8580 30  0001 C CNN
F 2 "" H 5800 8650 60  0001 C CNN
F 3 "" H 5800 8650 60  0001 C CNN
	1    5800 8650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 8600 5650 8600
Wire Wire Line
	5800 8250 5800 8650
Text GLabel 1450 10300 0    60   Input ~ 0
5V
$Comp
L GND #PWR03
U 1 1 616890A7
P 2000 10200
F 0 "#PWR03" H 2000 10200 30  0001 C CNN
F 1 "GND" H 2000 10130 30  0001 C CNN
F 2 "" H 2000 10200 60  0001 C CNN
F 3 "" H 2000 10200 60  0001 C CNN
	1    2000 10200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 10100 2000 10100
Wire Wire Line
	2000 10100 2000 10200
$Comp
L CRYSTAL X101
U 1 1 616893E5
P 1450 8650
F 0 "X101" H 1450 8800 60  0000 C CNN
F 1 "8MHz" H 1450 8500 60  0000 C CNN
F 2 "Crystals:Resonator-2pin_w10.0mm_h5.0mm" H 1450 8650 60  0000 C CNN
F 3 "" H 1450 8650 60  0000 C CNN
	1    1450 8650
	0    1    1    0   
$EndComp
$Comp
L C C102
U 1 1 616898F7
P 1100 9100
F 0 "C102" H 1100 9200 40  0000 L CNN
F 1 "22pF" H 1106 9015 40  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 1138 8950 30  0001 C CNN
F 3 "" H 1100 9100 60  0000 C CNN
	1    1100 9100
	0    1    1    0   
$EndComp
$Comp
L C C101
U 1 1 61689DAF
P 1100 8250
F 0 "C101" H 1100 8350 40  0000 L CNN
F 1 "22pF" H 1106 8165 40  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 1138 8100 30  0001 C CNN
F 3 "" H 1100 8250 60  0000 C CNN
	1    1100 8250
	0    1    1    0   
$EndComp
$Comp
L GND #PWR04
U 1 1 61689FE3
P 600 8850
F 0 "#PWR04" H 600 8850 30  0001 C CNN
F 1 "GND" H 600 8780 30  0001 C CNN
F 2 "" H 600 8850 60  0001 C CNN
F 3 "" H 600 8850 60  0001 C CNN
	1    600  8850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 8550 1700 8550
Wire Wire Line
	1700 8550 1700 8250
Wire Wire Line
	1700 8250 1300 8250
Wire Wire Line
	900  8250 800  8250
Wire Wire Line
	800  8250 800  9100
Wire Wire Line
	800  8700 600  8700
Wire Wire Line
	600  8700 600  8850
Wire Wire Line
	800  9100 900  9100
Connection ~ 800  8700
Wire Wire Line
	1300 9100 1700 9100
Wire Wire Line
	1700 9100 1700 8750
Wire Wire Line
	1700 8750 2200 8750
Wire Wire Line
	1450 8950 1450 9100
Connection ~ 1450 9100
Wire Wire Line
	1450 8350 1450 8250
Connection ~ 1450 8250
Text GLabel 2100 9100 0    60   Input ~ 0
SCK
Text GLabel 2100 9300 0    60   Output ~ 0
MISO
Text GLabel 2100 9200 0    60   Input ~ 0
MOSI
Text GLabel 2100 9000 0    60   Input ~ 0
CANCS
Wire Wire Line
	2100 9300 2200 9300
Wire Wire Line
	2100 9200 2200 9200
Wire Wire Line
	2100 9100 2200 9100
Wire Wire Line
	2100 9000 2200 9000
$Comp
L R R101
U 1 1 6168BE61
P 1850 9900
F 0 "R101" V 1930 9900 40  0000 C CNN
F 1 "10K" V 1857 9901 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1780 9900 30  0001 C CNN
F 3 "" H 1850 9900 30  0000 C CNN
	1    1850 9900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 9500 1850 9500
Wire Wire Line
	1850 9500 1850 9650
NoConn ~ 2200 9600
NoConn ~ 2200 9700
NoConn ~ 2200 9800
NoConn ~ 3900 10150
NoConn ~ 3900 10000
NoConn ~ 3900 9600
NoConn ~ 3900 9150
$Comp
L C C105
U 1 1 6168C8B8
P 5000 8250
F 0 "C105" H 5000 8350 40  0000 L CNN
F 1 "100nF" H 5006 8165 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5038 8100 30  0001 C CNN
F 3 "" H 5000 8250 60  0000 C CNN
	1    5000 8250
	0    1    1    0   
$EndComp
$Comp
L C C104
U 1 1 6168C998
P 1900 10650
F 0 "C104" H 1900 10750 40  0000 L CNN
F 1 "100nF" H 1906 10565 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1938 10500 30  0001 C CNN
F 3 "" H 1900 10650 60  0000 C CNN
	1    1900 10650
	-1   0    0    1   
$EndComp
$Comp
L C C103
U 1 1 6168CA4E
P 1650 10650
F 0 "C103" H 1650 10750 40  0000 L CNN
F 1 "10uF" H 1656 10565 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1688 10500 30  0001 C CNN
F 3 "" H 1650 10650 60  0000 C CNN
	1    1650 10650
	-1   0    0    1   
$EndComp
Wire Wire Line
	1450 10300 2200 10300
Wire Wire Line
	1850 10150 1850 10300
Connection ~ 1850 10300
Wire Wire Line
	1650 10450 1650 10300
Connection ~ 1650 10300
Wire Wire Line
	1900 10450 1900 10300
Connection ~ 1900 10300
Connection ~ 2150 10300
Wire Wire Line
	1900 11000 1650 11000
Wire Wire Line
	1650 11000 1650 10850
Wire Wire Line
	1900 10850 1900 11100
Connection ~ 1900 11000
$Comp
L GND #PWR05
U 1 1 6168D5B4
P 1900 11100
F 0 "#PWR05" H 1900 11100 30  0001 C CNN
F 1 "GND" H 1900 11030 30  0001 C CNN
F 2 "" H 1900 11100 60  0001 C CNN
F 3 "" H 1900 11100 60  0001 C CNN
	1    1900 11100
	1    0    0    -1  
$EndComp
NoConn ~ 5650 9050
$Comp
L ATTINY3224-SS IC101
U 1 1 62C1D72E
P 4550 4350
F 0 "IC101" H 3800 5100 60  0000 C CNN
F 1 "ATTINY3224-SS" H 5100 3600 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 3850 3600 60  0001 C CNN
F 3 "" H 4550 4350 60  0001 C CNN
	1    4550 4350
	1    0    0    -1  
$EndComp
$Comp
L NCP1117ST50T3G U103
U 1 1 62C2068C
P 6050 1200
F 0 "U103" H 6200 1004 40  0000 C CNN
F 1 "NCP1117ST50T3G" H 6050 1400 40  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-223-3Lead_TabPin2" H 6050 1200 60  0001 C CNN
F 3 "" H 6050 1200 60  0000 C CNN
	1    6050 1200
	1    0    0    -1  
$EndComp
$Comp
L C C106
U 1 1 62C20795
P 5350 1600
F 0 "C106" H 5350 1700 40  0000 L CNN
F 1 "10uF" H 5356 1515 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5388 1450 30  0001 C CNN
F 3 "" H 5350 1600 60  0000 C CNN
	1    5350 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1800 5350 1850
$Comp
L TJA1050 U102
U 1 1 62C1D654
P 5050 8550
F 0 "U102" H 5050 8450 60  0000 C CNN
F 1 "TJA1050" H 5050 8150 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 5050 8550 60  0001 C CNN
F 3 "" H 5050 8550 60  0001 C CNN
	1    5050 8550
	1    0    0    -1  
$EndComp
Text GLabel 5650 8750 2    60   BiDi ~ 0
CANH
Text GLabel 5650 8900 2    60   BiDi ~ 0
CANL
Text GLabel 5600 3900 2    60   Output ~ 0
SCK
Text GLabel 5600 4200 2    60   Output ~ 0
MOSI
Text GLabel 5600 4050 2    60   Input ~ 0
MISO
Text GLabel 3500 3900 0    60   Output ~ 0
CANCS
Text GLabel 5600 4500 2    60   Output ~ 0
SCL
Text GLabel 5600 4650 2    60   BiDi ~ 0
SDA
Wire Wire Line
	2850 3750 3500 3750
Wire Wire Line
	4250 8900 4400 8900
Wire Wire Line
	4250 7800 4250 8900
Wire Wire Line
	5800 8250 5200 8250
Connection ~ 5800 8600
Wire Wire Line
	4800 8250 4250 8250
Connection ~ 4250 8250
Wire Wire Line
	4400 8750 4350 8750
Wire Wire Line
	4350 8750 4350 8400
Wire Wire Line
	4350 8400 5800 8400
Connection ~ 5800 8400
Wire Wire Line
	4600 7800 4250 7800
$Comp
L CONN_4 P103
U 1 1 62C24D79
P 1200 6750
F 0 "P103" V 1150 6750 50  0000 C CNN
F 1 "CAN" V 1250 6750 50  0000 C CNN
F 2 "Connect:bornier4" H 1200 6750 60  0001 C CNN
F 3 "" H 1200 6750 60  0001 C CNN
	1    1200 6750
	-1   0    0    1   
$EndComp
Text GLabel 1550 6600 2    60   BiDi ~ 0
CANH
Text GLabel 1550 6700 2    60   BiDi ~ 0
CANL
Text GLabel 1550 6900 2    60   Input ~ 0
12v
$Comp
L GND #PWR06
U 1 1 62C251B0
P 4000 3250
F 0 "#PWR06" H 4000 3250 30  0001 C CNN
F 1 "GND" H 4000 3180 30  0001 C CNN
F 2 "" H 4000 3250 60  0001 C CNN
F 3 "" H 4000 3250 60  0001 C CNN
	1    4000 3250
	1    0    0    -1  
$EndComp
Text GLabel 5700 6550 2    60   BiDi ~ 0
SDA
Text GLabel 5700 6650 2    60   BiDi ~ 0
SCL
Text GLabel 5700 6850 2    60   Input ~ 0
5V
Text GLabel 3500 4500 0    60   Input ~ 0
RX
Text GLabel 3500 4650 0    60   Output ~ 0
TX
Text GLabel 5600 4350 2    60   BiDi ~ 0
UDPI
$Comp
L CONN_5 P102
U 1 1 62C279DC
P 1200 4200
F 0 "P102" V 1150 4200 50  0000 C CNN
F 1 "Prog" V 1250 4200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05" H 1200 4200 60  0001 C CNN
F 3 "" H 1200 4200 60  0001 C CNN
	1    1200 4200
	-1   0    0    1   
$EndComp
Text GLabel 1600 4100 2    60   Output ~ 0
RX
Text GLabel 1600 4000 2    60   Input ~ 0
TX
Text GLabel 2300 4200 2    60   BiDi ~ 0
UDPI
$Comp
L GND #PWR07
U 1 1 62C27C2B
P 1700 4500
F 0 "#PWR07" H 1700 4500 30  0001 C CNN
F 1 "GND" H 1700 4430 30  0001 C CNN
F 2 "" H 1700 4500 60  0001 C CNN
F 3 "" H 1700 4500 60  0001 C CNN
	1    1700 4500
	1    0    0    -1  
$EndComp
Text GLabel 1600 4300 2    60   Output ~ 0
5V
$Comp
L R R102
U 1 1 62C27FC6
P 1950 4200
F 0 "R102" V 2030 4200 40  0000 C CNN
F 1 "270R" V 1957 4201 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1880 4200 30  0001 C CNN
F 3 "" H 1950 4200 30  0000 C CNN
	1    1950 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	1600 4200 1700 4200
Wire Wire Line
	2200 4200 2300 4200
Wire Wire Line
	1700 4500 1700 4400
Wire Wire Line
	1700 4400 1600 4400
Text GLabel 2850 3750 0    60   Input ~ 0
5V
$Comp
L GND #PWR08
U 1 1 62C28E26
P 5600 3750
F 0 "#PWR08" H 5600 3750 30  0001 C CNN
F 1 "GND" H 5600 3680 30  0001 C CNN
F 2 "" H 5600 3750 60  0001 C CNN
F 3 "" H 5600 3750 60  0001 C CNN
	1    5600 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 62C28F15
P 5700 6750
F 0 "#PWR09" H 5700 6750 30  0001 C CNN
F 1 "GND" H 5700 6680 30  0001 C CNN
F 2 "" H 5700 6750 60  0001 C CNN
F 3 "" H 5700 6750 60  0001 C CNN
	1    5700 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1850 6750 1850
Wire Wire Line
	6750 1850 6750 1800
Wire Wire Line
	6750 1400 6750 1150
$Comp
L INA219-module U104
U 1 1 6448C178
P 5100 6600
F 0 "U104" H 5100 6600 60  0000 C CNN
F 1 "INA219-module" H 5100 6600 60  0000 C CNN
F 2 "Divers:INA219Module" H 5100 6600 60  0001 C CNN
F 3 "" H 5100 6600 60  0001 C CNN
	1    5100 6600
	1    0    0    -1  
$EndComp
Text GLabel 5700 6350 2    60   BiDi ~ 0
IN+
Text GLabel 5700 6450 2    60   BiDi ~ 0
IN-
Text GLabel 3500 4050 0    60   Input ~ 0
TEMP1
Text GLabel 3500 4200 0    60   Output ~ 0
LED
$Comp
L R R103
U 1 1 6448D116
P 2900 6600
F 0 "R103" V 2980 6600 40  0000 C CNN
F 1 "10K" V 2907 6601 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2830 6600 30  0001 C CNN
F 3 "" H 2900 6600 30  0000 C CNN
	1    2900 6600
	-1   0    0    1   
$EndComp
$Comp
L R R104
U 1 1 6448D260
P 3450 6600
F 0 "R104" V 3530 6600 40  0000 C CNN
F 1 "10K" V 3457 6601 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3380 6600 30  0001 C CNN
F 3 "" H 3450 6600 30  0000 C CNN
	1    3450 6600
	-1   0    0    1   
$EndComp
Text GLabel 2900 6850 0    60   Output ~ 0
TEMP1
Text GLabel 3450 7250 0    60   Input ~ 0
LED
Text GLabel 3450 6350 2    60   Input ~ 0
5V
Wire Wire Line
	3450 6350 2900 6350
Text GLabel 1550 5600 2    60   BiDi ~ 0
IN+
Text GLabel 1550 5700 2    60   BiDi ~ 0
IN-
$Comp
L GND #PWR010
U 1 1 6448D721
P 1550 5800
F 0 "#PWR010" H 1550 5800 30  0001 C CNN
F 1 "GND" H 1550 5730 30  0001 C CNN
F 2 "" H 1550 5800 60  0001 C CNN
F 3 "" H 1550 5800 60  0001 C CNN
	1    1550 5800
	-1   0    0    -1  
$EndComp
$Comp
L CONN_4 P105
U 1 1 6448D7CD
P 1200 7300
F 0 "P105" V 1150 7300 50  0000 C CNN
F 1 "OLED" V 1250 7300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 1200 7300 60  0001 C CNN
F 3 "" H 1200 7300 60  0001 C CNN
	1    1200 7300
	-1   0    0    1   
$EndComp
Text GLabel 1550 7150 2    60   BiDi ~ 0
SDA
Text GLabel 1550 7250 2    60   BiDi ~ 0
SCL
$Comp
L GND #PWR011
U 1 1 6448D8EF
P 1550 7350
F 0 "#PWR011" H 1550 7350 30  0001 C CNN
F 1 "GND" H 1550 7280 30  0001 C CNN
F 2 "" H 1550 7350 60  0001 C CNN
F 3 "" H 1550 7350 60  0001 C CNN
	1    1550 7350
	1    0    0    -1  
$EndComp
Text GLabel 1550 7450 2    60   Input ~ 0
5V
$Comp
L CONN_2 P101
U 1 1 6448DB6A
P 1200 5050
F 0 "P101" V 1150 5050 40  0000 C CNN
F 1 "Temp1" V 1250 5050 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 1200 5050 60  0001 C CNN
F 3 "" H 1200 5050 60  0001 C CNN
	1    1200 5050
	-1   0    0    1   
$EndComp
Text GLabel 1550 4950 2    60   Output ~ 0
TEMP1
$Comp
L GND #PWR012
U 1 1 6448DD33
P 1550 5150
F 0 "#PWR012" H 1550 5150 30  0001 C CNN
F 1 "GND" H 1550 5080 30  0001 C CNN
F 2 "" H 1550 5150 60  0001 C CNN
F 3 "" H 1550 5150 60  0001 C CNN
	1    1550 5150
	1    0    0    -1  
$EndComp
Connection ~ 3000 3750
$Comp
L GND #PWR013
U 1 1 6448E6C2
P 3000 4150
F 0 "#PWR013" H 3000 4150 30  0001 C CNN
F 1 "GND" H 3000 4080 30  0001 C CNN
F 2 "" H 3000 4150 60  0001 C CNN
F 3 "" H 3000 4150 60  0001 C CNN
	1    3000 4150
	1    0    0    -1  
$EndComp
$Comp
L LED D101
U 1 1 644D43C8
P 3450 7050
F 0 "D101" H 3450 7150 50  0000 C CNN
F 1 "LED" H 3450 6950 50  0000 C CNN
F 2 "LEDs:LED_0805" H 3450 7050 60  0001 C CNN
F 3 "" H 3450 7050 60  0000 C CNN
	1    3450 7050
	0    1    1    0   
$EndComp
$Comp
L CONN_3 K101
U 1 1 644D4D79
P 1200 5700
F 0 "K101" V 1150 5700 50  0000 C CNN
F 1 "Battery" V 1250 5700 40  0000 C CNN
F 2 "Connect:bornier3" H 1200 5700 60  0001 C CNN
F 3 "" H 1200 5700 60  0001 C CNN
	1    1200 5700
	-1   0    0    1   
$EndComp
$Comp
L R R105
U 1 1 644E00AC
P 4150 2900
F 0 "R105" V 4230 2900 40  0000 C CNN
F 1 "10K" V 4157 2901 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4080 2900 30  0001 C CNN
F 3 "" H 4150 2900 30  0000 C CNN
	1    4150 2900
	1    0    0    -1  
$EndComp
Text Notes 750  3450 0    60   ~ 0
The aim of this board is to measure \nthe battery at its terminals so it needs\nto be using a reference gnd connection \nof the negative terminal of the battery. \nFor this reason the CAN GND is isolated \nby a resistor ensure its not connected \ndirectly to the battery GND as there may \nbe small constant volage differences \nbetween the 2 and we dont want the \nCAN GND to become the boad GND \nsupply line carying significant current.  
$Comp
L C C107
U 1 1 644E044D
P 3900 2900
F 0 "C107" H 3900 3000 40  0000 L CNN
F 1 "100nF" H 3906 2815 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3938 2750 30  0001 C CNN
F 3 "" H 3900 2900 60  0000 C CNN
	1    3900 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3900 2700 3900 2600
Wire Wire Line
	3900 2600 4150 2600
Wire Wire Line
	4150 2600 4150 2650
Wire Wire Line
	3900 3150 4150 3150
Wire Wire Line
	3900 3150 3900 3100
Wire Wire Line
	4000 3150 4000 3250
Connection ~ 4000 3150
Text GLabel 3900 2600 0    60   UnSpc ~ 0
CANGND
Text GLabel 1550 6800 2    60   UnSpc ~ 0
CANGND
$EndSCHEMATC
