/*
 * nmea.h
 *
 *  Created on: Mar 15, 2016
 *      Author: chris
 */

#ifndef NMEA_H_
#define NMEA_H_

#include <string>
#include <vector>

class NMEA {
public:
	/*RMC*/
	std::string Message_ID; /* RMC Protocol header */
	std::string UTC_Time; /* hhmmss.sss */
	std::string Status; /* A = data valid, V = data NOT valid */
	std::string Latitude; /* ddmm.mmmm */
	std::string N_S_Indicator; /* N = North, S = South */
	std::string Longitude; /* dddmm.mmmm */
	std::string E_W_Indicator; /* E = East, W = West */
	std::string Speed_Over_Ground; /* In Knots */
	std::string Course_Over_Ground; /* Degrees */
	std::string Date; /* ddmmyy */
	std::string Mode; /* A = autonomous mode, D = Differential mode, E = Estimated mode */
	std::string Checksum; /* checksum value that starts with '*' */

	/*GGA*/
	std::string Fix_Quality;
	std::string Num_Satellites;
	std::string Horizontal_dilution;
	std::string Altitude;
	std::string Height_of_Geoid;

	std::vector<std::string> parse(char, std::string);
	bool validateChecksum(std::string);
	float decimalDegrees(std::string, int, int);
};

class RMC: public NMEA{
public:
	void setData(std::vector<std::string>);
};

class GGA: public NMEA{
public:
	GGA(std::vector<std::string>);
};

#endif /* NMEA_H_ */
