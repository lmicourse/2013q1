/*
 * Logger.cpp
 *
 *  Created on: 2013.04.03.
 *      Author: varrocs
 */


#include "Logger.h"

Logger::Logger() {
	file.open("log.txt");
}

Logger::~Logger() {
	file.close();
}

void Logger::log(const std::string& message) {
	file << message << std::endl;
}


void Logger::log(int i) {
	file << i << std::endl;
}

