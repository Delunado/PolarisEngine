#include "Debug.h"

#include <iostream>
#include <ctime>

void Log::PrintMessage(std::string message)
{
	time_t timeNow = time(0);
	tm localTime;
	localtime_s(&localTime, &timeNow);

	std::cout << "[" << localTime.tm_hour << ":" << localTime.tm_min << ":" << localTime.tm_sec << "] " << message << std::endl;
}



void Debug::Assert(bool condition, std::string message)
{
	if (!condition)
		Log::PrintMessage(message);

	assert(condition);
}
