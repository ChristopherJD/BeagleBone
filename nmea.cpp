/*
 * nmea.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: chris
 */

#include <sstream>

#include "nmea.h"

std::vector<std::string> NMEA::parse(char delimeter, std::string sentence) {

	std::vector<std::string>::size_type pos { 0 };
	std::vector<std::string> temp { };

	while ((pos = sentence.find(delimeter)) != std::string::npos) {
		temp.push_back(sentence.substr(0, pos));
		sentence.erase(0, pos + sizeof(delimeter));
	}

	return temp;
}

bool NMEA::validateChecksum(std::string sentence) {

	int checksum { 0 };
	unsigned int nmeaChecksumLength { 2 };

	for (char x : sentence) {
		if ((x != '*') && (x != '$')) {
			checksum ^= static_cast<int>(x);
		}
		if (x == '*')
			goto endOfChecksum;
	}

	endOfChecksum: std::string temp = sentence.substr(
			static_cast<unsigned int>(sentence.size() - nmeaChecksumLength - 1), //-1 due to '\n' at end of message
			nmeaChecksumLength);
	std::stringstream ss { };
	ss << temp;
	int nmeaChecksum { };
	ss >> std::hex >> nmeaChecksum;

	if (nmeaChecksum == checksum) {
		return true;
	}
	return false;
}

float NMEA::decimalDegrees(std::string coordinate, int degreeLength,
		int minuteLength) {

	std::stringstream ss;
	ss << coordinate.substr(0, degreeLength - 1);
	int degrees { };
	ss >> std::dec >> degrees;
	ss.flush();
	ss << coordinate.substr(degreeLength, degreeLength + minuteLength - 1);
	int minutes { };
	ss >> std::dec >> minutes;
	ss.flush();
	int seconds { };
	ss
			<< coordinate.substr(degreeLength + minuteLength + 1,
					coordinate.length());
	ss >> std::dec >> seconds;

	float longdd = static_cast<float>(degrees)
			+ (static_cast<float>(minutes) / 60.0f)
			+ (static_cast<float>(seconds) * 3600.0f);

	return longdd;
}

void RMC::setData(std::vector<std::string> parsedSentence) {

	if (parsedSentence[0] == "$GPRMC") {
		this->Message_ID = parsedSentence[0];
		this->UTC_Time = parsedSentence[1];
		this->Status = parsedSentence[2];
		this->Latitude = parsedSentence[3];
		this->N_S_Indicator = parsedSentence[4];
		this->Longitude = parsedSentence[5];
		this->E_W_Indicator = parsedSentence[6];
		this->Speed_Over_Ground = parsedSentence[7];
		this->Course_Over_Ground = parsedSentence[8];
		this->Date = parsedSentence[9];
		this->Mode = parsedSentence[10];
		this->Checksum = parsedSentence[11];
	}
}

GGA::GGA(std::vector<std::string> parsedSentence) {

	if (parsedSentence[0] == "$GPGGA") {
		this->Message_ID = parsedSentence[0];
		this->UTC_Time = parsedSentence[1];
		this->Latitude = parsedSentence[2];
		this->N_S_Indicator = parsedSentence[3];
		this->Longitude = parsedSentence[4];
		this->E_W_Indicator = parsedSentence[5];
		this->Fix_Quality = parsedSentence[6];
		this->Num_Satellites = parsedSentence[7];
		this->Horizontal_dilution = parsedSentence[8];
		this->Altitude = parsedSentence[9];
		this->Height_of_Geoid = parsedSentence[11];
		this->Checksum = parsedSentence[13];
	}
}

