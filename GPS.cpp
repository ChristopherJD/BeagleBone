/*
 * GPS.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: chris
 */

//#include <string>
#include <string.h>
#include <sstream>

#include "UART.h"
#include "GPS.h"

#define	ttyO1 "/dev/ttyO1"
#define	ttyO2 "/dev/ttyO2"
#define	ttyO4 "/dev/ttyO4"
#define ttyO5 "/dev/ttyO5"

#define baud 9600

HardwareSerial serial(ttyO1, baud);

GPS::GPS(){
	//
}

GPS::GPS(std::string command) {
	serial.writeCommand(command);
	serial.writeCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	serial.writeCommand(PMTK_API_SET_FIX_CTL_1HZ);
}

const std::string GPS::read(void) {
	std::string RxData = { };

	while((RxData = serial.readData()) == std::string()){
		//Wait for GPS data to be read
	}

	return RxData;
}

