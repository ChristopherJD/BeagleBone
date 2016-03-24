/*
 * UART.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: Christopher Jordan-Denny
 */

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "UART.h"

HardwareSerial::HardwareSerial(std::string id, unsigned long baud) {

	this->device = id;

	struct termios uart;

	fd = open(this->device.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd < 0) {
		exit(-1);
	}

	bzero(&uart, sizeof(uart));
	uart.c_cflag = CS8 | CLOCAL | CREAD;
	uart.c_iflag = IGNPAR;
	uart.c_oflag = 0;
	uart.c_lflag = ICANON;	//Canonical mode, set to 0 if non-canonical desired
	uart.c_ispeed = baud;
	uart.c_ospeed = baud;

//	uart.c_cc[VTIME] = 0;
//	uart.c_cc[VMIN] = 1;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &uart);
}

std::string HardwareSerial::readData() {

	int numRead = 0;

	if((numRead = read(fd, buff, bufferSize)) < 0){
		return std::string();
	}
	buff[numRead] = '\0';
	std::string str(buff);

	return str;
}

size_t HardwareSerial::writeCommand(std::string command){
	return write(fd,command.c_str(),command.length());
}
