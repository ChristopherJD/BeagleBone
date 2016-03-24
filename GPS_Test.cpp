#include <iostream>

#include "GPS.h"
#include "nmea.h"

int main() {

	GPS gps = GPS(RMCONLY);
	RMC rmc = RMC();
	std::string gpsData;

	while (1) {
		gpsData = gps.read();
		rmc.setData(gps.parse(',',gpsData));

		std::cout << "Latitude: " << rmc.Latitude << std::endl;
	}
}
