#pragma once

#include <cassert>
#include <string>

class Log {
private:


public:
	static void PrintMessage(std::string message);

};

class Debug {
private:

public:
	static void Assert(bool condition, std::string message);

};