#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

class Logger{
public:
	Logger( std::string logpath );
	void Log(std::string message );

private:
	std::string mLogpath;
};
#endif

