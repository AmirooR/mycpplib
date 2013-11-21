#include "util/ALogger.h"

#include <iostream>

using namespace std;


int main()
{
	ALogger a("logs.properties","mylogs");
//	ALogger::init("logs.properties","mylogs");
	ALogger::info("salam","khodafez");
	ALogger::error("salam error","mylogs");
	ALogger::info("khodafez","khodafez");
	return 0;
}
