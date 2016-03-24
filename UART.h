/*
 * UART.h
 *
 *  Created on: Mar 12, 2016
 *      Author: chris
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <string>

#define bufferSize 128

class HardwareSerial{
private:
	std::string device;
	int fd;
	char buff[bufferSize];
public:
	HardwareSerial(std::string,unsigned long);
	std::string readData(void);
	int peek(void);
	size_t writeCommand(std::string);
};

size_t serialRead(int,void*,unsigned long int);

#endif /* UART_H_ */
