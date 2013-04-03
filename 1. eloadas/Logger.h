/*
 * Logger.h
 *
 *  Created on: 2013.04.03.
 *      Author: varrocs
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>

class Logger {
	std::ofstream file;
public:
	Logger();
	virtual ~Logger();

	void log(const std::string& message);
	void log(int i);
};

#endif /* LOGGER_H_ */
