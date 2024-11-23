#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

#include "Queue.hxx"
#include "Type.hxx"

class Logger
{
	public:
		Logger(const string& route);
		~Logger();
		
		None print(const string& message);
	
	private:
		cpp::ofstream stream;
};

#endif