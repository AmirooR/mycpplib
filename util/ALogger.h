#ifndef _ALogger_H_
#define _ALogger_H_

#include <string>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>

using namespace std;
using namespace log4cplus;

class ALogger
{
protected:
	string log_properties;
	//string log_name;
public:
	ALogger(string log_properties, string log_name):log_properties(log_properties)
	{
		PropertyConfigurator log_config(log_properties);
		log_config.configure();
		//ALogger::log_name = log_name;
	}

	static void info(string str, string log_name)
	{
		Logger logger = Logger::getInstance(log_name);
		LOG4CPLUS_INFO(logger,str);
	}

	static void error(string str, string log_name)
	{
		Logger logger = Logger::getInstance(log_name);
		LOG4CPLUS_ERROR(logger,str);
	}
};

#endif
