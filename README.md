# Nmea2000 Battery Sensor.

Mk1 used the ADC on an Attiny3224. Fine for voltage but not really accurate enough for low levels of current on a 75mV 100A shunt. 

This version is built arround a INA219 which is far easier to use. It speaks CAN to communicate with a NMEA2000 bus.



A BLE version was created, but in the end I felt it was overcomplicated and would need to deep sleep to avoid draining the battery.

A Modbus version was also created, but since it adds annother bus I decided to rebuild as a NMEA2000 device using the SmallNMEA2000 library that was used in the CanPressure sensor and EngineManagement modules. Both have been in service for 2 years with no issues.




# megaTinyCore 

This code needs megaTiny core 2.6.4 to work as there are some timing bugs that cause it to fail with the default platform IO 2.5.11 version. Upgrading is a pain as it requires installing a custom package. Installs from github fail as the layout of the source repo is wrong and missing files. 

The hacky way is to install manually as its not possible to install from a git repo due to a bug in the pio code that parses versions numbers.

		cd ~/src
		git clone https://github.com/SpenceKonde/megaTinyCore.git
		cd megaTinyCore
		git co -b 2.6.4
		mkdir ~/.platformio/packages/framework-arduino-megaavr-megatinycore@2.6.4
		cd ~/.platformio/packages/framework-arduino-megaavr-megatinycore@2.6.4
		cat << EOF > .piopm
		{"type": "tool", "name": "framework-arduino-megaavr-megatinycore", "version": "2.6.4", "spec": {"owner": "platformio", "id": 11448, "name": "framework-arduino-megaavr-megatinycore", "requirements": null, "uri": null}}
		EOF
		cat << EOF > package.json
		{
		  "name": "framework-arduino-megaavr-megatinycore",
		  "version": "2.6.4",
		  "description": "Arduino Wiring-based Framework for Microchip tinyAVR 0-series and 1-series chips (megaTinyCore)",
		  "keywords": [
		    "framework",
		    "arduino",
		    "microchip",
		    "tinyAVR"
		  ],
		  "repository": {
		    "type": "git",
		    "url": "https://github.com/ieb/megaTinyCore"
		  }
		}
		EOF
		ln -s ~/megaTinyCore/megaavr/* .
		ln -s ~/megaTinyCore/ChangeLog.md .
		ln -s ~/megaTinyCore/Installation.md .
		ln -s ~/megaTinyCore/MakeUPDIProgrammer.md .
		ln -s ~/megaTinyCore/README.md .
		ln -s ~/megaTinyCore/Wiring.md .


# Oled display

There is a i2c header but at this time the oled display was removed as it served minimal purpose and consumes more current.

# LED status

normal operation is on for 250ms, off for 6s. Error states are indetified by a number of 250ms flashes followed by on for 3s off for 3s.  ^ == short flash -3s- == 3s on for 3 . _3s_ off for 3s. Cycle repeats after 6s

|   flashes   | condition                                   |
|+++++++++++++|+++++++++++++++++++++++++++++++++++++++++++++|
| ^           | normal                                      |
| ^^ -3s-     | INA219 chip failure                         |
| ^^^ -s3-    | Can bus not connected or failing to respond |
| ^^^^^ -s3-  | Both Can and INA219 failing                 |

# ToDo

* [x] Basic implementation, with CAN.
* [x] Average current and voltage over time period, eg 30s
* [ ] Test CAN using a CandelLite adapter.
* [x] Calibrate NTC sensors.
* [x] --Add 1.3 inch Oled display--
* [ ] Implement current monitoring with auto scaling for different ranges using features of the INA219
